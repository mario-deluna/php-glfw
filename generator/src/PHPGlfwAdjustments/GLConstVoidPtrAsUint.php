<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\LongArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLConstVoidPtrAsUint implements AdjustmentInterface
{
    public function handle(ExtGenerator $gen) : void
    {
        // functions that contain a const void* argument that should be treated as an offset pointer 
        // this in our case is a uint indicating the byte offset
        foreach([
            'glVertexAttribPointer' => 'offset',
            'glIsSync' => 'sync',
            'glWaitSync' => 'sync',
            'glDeleteSync' => 'sync',
            'glFenceSync' => 'sync',
            'glClientWaitSync' => 'sync',
        ] as $fname => $argname) {
            $func = $gen->getFunctionByName($fname);

            if (!$func) {
                continue;
            }

            // find the argument called offset
            foreach($func->arguments as $k => $arg) {
                if($arg->name == $argname) {
                    $oldArg = $arg;
                    $newArg = new class($oldArg->name, $oldArg->argumentType) extends LongArgument
                    {
                        public function getUsableVariable() : string
                        {
                            return '(const void*)(uintptr_t)' . $this->name;
                        }
                    };

                    $newArg->charid = $oldArg->charid;
                    $newArg->comment = $oldArg->comment;

                    // replace the argument
                    $func->arguments[$k] = $newArg;
                }
            }
        }
    }
}
