<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLVectorSetterFunctionAdjustment implements AdjustmentInterface
{

    private function patchVectorSetterFunction(ExtGenerator $gen, string $functionName) : void
    {   
        $func = new class($functionName) extends ExtFunction 
        {
            public ExtArgument $initalDataArg;
            public int $countArgIndex = -1;
            
            public function getFunctionImplementationBody() : string
            {
                $b = '';

                // define var declaration
                // one thing different from the default is we declare
                // an additional hash table for the value because we 
                // support both, a hashtable or a buffer object
                foreach($this->arguments as $arg) {
                    $b .= $arg->getVariableDeclaration() . PHP_EOL;
                }

                // $b .= 'GLsizei count_of_el = 0;' . PHP_EOL;
                
                // add the hash table declaration
                $lastArg = $this->arguments[count($this->arguments) - 1];
                $htvar = $lastArg->name . '_ht';
                $b .= 'HashTable *' . $htvar . ' = NULL;' . PHP_EOL;

                $argChars = $this->getArgumentTypeCharList();
                $argAssignList = $this->getArgumentAssignmentList();

                // try to parse the arguments with an object
                $b .= PHP_EOL . sprintf('if (zend_parse_parameters(ZEND_NUM_ARGS() , "%s", %s) == FAILURE) {', $argChars, $argAssignList) . PHP_EOL;
                
                // update the paramater parser arguments to try
                // to parse a hash table instead of the buffer object
                $argChars = substr($argChars, 0, -1) . 'h';
                $argAssignList = explode(',', $argAssignList);
                array_pop($argAssignList);
                array_pop($argAssignList);
                $argAssignList[] = ' &' . $htvar;
                $argAssignList = implode(',', $argAssignList);

                $b .= PHP_EOL . sprintf('    if (zend_parse_parameters(ZEND_NUM_ARGS() , "%s", %s) == FAILURE) {', $argChars, $argAssignList) . PHP_EOL;
                $b .= PHP_EOL . '        return;' . PHP_EOL;
                $b .= PHP_EOL . '    }' . PHP_EOL; // closing HT scope
                
                // build hashtable function call code
                $callArgs = [];
                foreach($this->arguments as $arg) {
                    $callArgs[] = $arg->getUsableVariable();
                }
            
                // replace the last arg
                array_pop($callArgs);
                $callArgs[] = 'tmpvec';

                // if this function contains a count variable we need to
                // verify the data size is in line with the requirements of the function
                $sizeValidationCode = '';
                $elementCountDivisor = 1;
                switch($this->name) {
                    case 'glUniform2fv':
                    case 'glUniform2iv':
                    case 'glUniform2uiv':
                        $elementCountDivisor = 2;
                        break;
                    case 'glUniform3fv':
                    case 'glUniform3iv':
                    case 'glUniform3uiv':
                        $elementCountDivisor = 3;
                        break;
                    case 'glUniform4fv':
                    case 'glUniform4iv':
                    case 'glUniform4uiv':
                        $elementCountDivisor = 4;
                        break;
                    case 'glUniformMatrix2fv':
                        $elementCountDivisor = 4;
                        break;
                    case 'glUniformMatrix3fv':
                        $elementCountDivisor = 9;
                        break;
                    case 'glUniformMatrix4fv':
                        $elementCountDivisor = 16;
                        break;
                    case 'glUniformMatrix2x3fv':
                    case 'glUniformMatrix3x2fv':
                        $elementCountDivisor = 6;
                        break;
                    case 'glUniformMatrix2x4fv':
                    case 'glUniformMatrix4x2fv':
                        $elementCountDivisor = 8;
                        break;
                    case 'glUniformMatrix3x4fv':
                    case 'glUniformMatrix4x3fv':
                        $elementCountDivisor = 12;
                        break;
                }

                if ($this->countArgIndex !== -1) 
                {
                    if ($elementCountDivisor > 1) {
                        // inject the count argument into the call
                        array_splice($callArgs, $this->countArgIndex, 0, 'cvector_size(tmpvec) / ' . $elementCountDivisor); 
                        
                        $sizeValidationCode = 'if (cvector_size(tmpvec) % '.$elementCountDivisor.' != 0) {' . PHP_EOL;
                        $sizeValidationCode .= '    zend_throw_error(NULL, "Invalid data size for ' . $this->name . ', the number of values must be dividable by '.$elementCountDivisor.'.");' . PHP_EOL;
                        $sizeValidationCode .= '    return;' . PHP_EOL;
                        $sizeValidationCode .= '}' . PHP_EOL;
                    }
                    else {

                        // inject the count argument into the call
                        array_splice($callArgs, $this->countArgIndex, 0, 'cvector_size(tmpvec)'); 
                    }
                }

                // generate the code to iterate of the hash table
                // add all values to a vector and call the internal function
                // using a pointer to that vector
                $phpType = ExtType::getPHPType($this->initalDataArg->argumentType);
                $funcCall = $this->internalCallFunc . '('. implode(', ', $callArgs) .');';
 
                $tsizeValidationCode = tabulate($sizeValidationCode);

                $b .= <<<EOD
    
    zval *data;
    cvector_vector_type({$this->initalDataArg->getPureFromType()}) tmpvec = NULL;
    ZEND_HASH_FOREACH_VAL({$htvar}, data)
        if (Z_TYPE_P(data) == {$this->initalDataArg->getZvalTypeComparisonConst()}) {
            cvector_push_back(tmpvec, {$this->initalDataArg->getValueFromZvalPointerConst()}(data));
        } else {
            zend_throw_error(NULL, "All elements of the given array have to be of type: {$phpType}");
        }
    ZEND_HASH_FOREACH_END();
{$tsizeValidationCode}
    {$funcCall}
    cvector_free(tmpvec);

EOD;
                $b .= '    return;' . PHP_EOL;

                $b .= "}" . PHP_EOL; // closing buffer parser scope

                // now we generate the code that handles the case where the 
                // argument is a buffer object.
                $callArgs = [];
                foreach($this->arguments as $arg) {
                    $callArgs[] = $arg->getUsableVariable();
                }

                // replace the last arg
                array_pop($callArgs);
                $callArgs[] = 'bufferobj->vec';

                // also inject the count argument if needed
                if ($this->countArgIndex !== -1) {
                    if ($elementCountDivisor > 1) {
                        array_splice($callArgs, $this->countArgIndex, 0, 'cvector_size(bufferobj->vec) / ' . $elementCountDivisor); 
                    } else {
                        array_splice($callArgs, $this->countArgIndex, 0, 'cvector_size(bufferobj->vec)'); 
                    }
                }
                
                $b .= PHP_EOL . $lastArg->getObjectFetchCode($lastArg->getZValName());

                if ($this->countArgIndex !== -1 && $elementCountDivisor > 1) {
                    $b .= PHP_EOL . 'if (cvector_size(bufferobj->vec) % '.$elementCountDivisor.' != 0) {' . PHP_EOL;
                    $b .= '    zend_throw_error(NULL, "Invalid data size for ' . $this->name . ', the number of values must be dividable by '.$elementCountDivisor.'.");' . PHP_EOL;
                    $b .= '    return;' . PHP_EOL;
                    $b .= '}' . PHP_EOL;
                }

                $b .= PHP_EOL . $this->internalCallFunc . '('. implode(', ', $callArgs) .');';

                return $b;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        // find the value count argument index
        $countArgIndex = -1;
        foreach($func->arguments as $i => $arg) {
            if ($arg->name == 'count') {
                $countArgIndex = $i;
                break;
            }
        }

        // remove the count argument from the function
        $func->arguments = array_values(array_filter($func->arguments, function($arg) {
            return $arg->name != 'count';
        }));

        // get the last argument with the assumption 
        // that it is the buffer object / array
        $lastArg = $func->arguments[count($func->arguments) - 1];

        $func->arguments[count($func->arguments) - 1] = new class($lastArg->name, ExtType::T_CE) extends CEObjectArgument {
            public ExtArgument $initalDataArg;

            public function getClassEntryPointer() : string {
                if ($this->initalDataArg->getPureFromType() === 'GLfloat') {
                    return 'phpglfw_get_buffer_glfloat_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLuint') {
                    return 'phpglfw_get_buffer_gluint_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLint') {
                    return 'phpglfw_get_buffer_glint_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLdouble') {
                    return 'phpglfw_get_buffer_gldouble_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLshort') {
                    return 'phpglfw_get_buffer_glshort_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLushort') {
                    return 'phpglfw_get_buffer_glushort_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLbyte') {
                    return 'phpglfw_get_buffer_glbyte_ce()';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLubyte') {
                    return 'phpglfw_get_buffer_glubyte_ce()';
                }

                return 'phpglfw_get_buffer_interface_ce()';
            }

            public function getPHPClassName() : string {
                if ($this->initalDataArg->getPureFromType() === 'GLfloat') {
                    return '\\GL\\Buffer\\FloatBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLuint') {
                    return '\\GL\\Buffer\\UIntBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLint') {
                    return '\\GL\\Buffer\\IntBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLdouble') {
                    return '\\GL\\Buffer\\DoubleBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLshort') {
                    return '\\GL\\Buffer\\ShortBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLushort') {
                    return '\\GL\\Buffer\\UShortBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLbyte') {
                    return '\\GL\\Buffer\\ByteBuffer|array';
                } elseif ($this->initalDataArg->getPureFromType() === 'GLubyte') {
                    return '\\GL\\Buffer\\UbyteBuffer|array';
                }

                return "\\GL\\Buffer\\BufferInterface|array";
            }

            public function getObjectFetchCode(string $dataZval) : string {
                $pt = strtolower($this->initalDataArg->getPureFromType());
                return sprintf('phpglfw_buffer_%s_object *bufferobj = phpglfw_buffer_%s_objectptr_from_zobj_p(Z_OBJ_P(%s));',
                    $pt,
                    $pt,
                    $dataZval
                );
            }
        };

        // inject the original argument into the argument and func decl
        $func->initalDataArg = $lastArg;
        $func->countArgIndex = $countArgIndex;
        $func->arguments[count($func->arguments) - 1]->initalDataArg = $lastArg;
        
        // replace
        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $vectorSetterFunctions = [];

        // we iterate over all methods to locate functions 
        // that follow the expected pattern of settings a vector of data
        foreach($gen->methods as $func) 
        {
            // last character of the function name must be a 'v'
            if (substr($func->name, -1) !== 'v') {
                continue;
            }
            // function should be incomplete
            if (!$func->incomplete) continue;

            // the func cannot return anything...
            if ($func->returnType !== ExtFunction::RETURN_VOID) continue;

            // last argument must be a pointer
            $lastArg = $func->arguments[count($func->arguments) - 1];
            if (strpos($lastArg->argumentTypeFrom, '*') === false) continue;

            // argument should also be const..
            if (strpos($lastArg->argumentTypeFrom, 'const') === false) continue;

            // the func cannot return anything...
            if ($func->returnType !== ExtFunction::RETURN_VOID) continue;

            $vectorSetterFunctions[] = $func->name;
        }

        // now patch the matched functions
        foreach($vectorSetterFunctions as $funcName) {
            $this->patchVectorSetterFunction($gen, $funcName);
        }
    }
}
