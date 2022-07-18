<?php

use GLSpec\GLConstantGroup;

class GLSpecReader 
{
    /**
     * Parse the xml at the given path
     * 
     * @param GLSpec            $spec
     * @param string            $pathToXml
     */
    public function parse(GLSpec $spec, string $pathToXml)
    {
        if (!file_exists($pathToXml)) {
            throw new \Exception("GL Spec file could not be loaded at: " . $pathToXml);
        }

        $xml = simplexml_load_file($pathToXml);

        foreach($xml->children() as $el) 
        {
            $name = $el->getName();

            if ($name === 'types') {
                $this->parseTypes($spec, $el);
            } elseif ($name === 'commands') {
                $this->parseCommands($spec, $el);
            } elseif ($name === 'feature') {
                $this->parseFeatures($spec, $el);
            } elseif ($name === 'enums') {
                $this->parseEnums($spec, $el);
            }
        }
    }

    /**
     * Parse an element of types
     * 
     * @param GLSpec                $spec
     * @param SimpleXMLElement      $types
     */
    private function parseTypes(GLSpec $spec, SimpleXMLElement $types)
    {
    }

    /**
     * Parse an element of enums
     * 
     * @param GLSpec                $spec
     * @param SimpleXMLElement      $enums
     */
    private function parseEnums(GLSpec $spec, SimpleXMLElement $enums)
    {
        $constGroup = new GLConstantGroup;
        $constGroup->group = $enums->attributes()->group;
        $constGroup->vendor = $enums->attributes()->vendor;
        $constGroup->comment = $enums->attributes()->comment;

        foreach($enums->children() as $enumDef) 
        {
            if ($enumDef->getName() === 'enum') {
                $const = $spec->makeConstant($enumDef->attributes()->name, (string) $enumDef->attributes()->value);
                $const->constGroup = $constGroup;

                if ($group = (string) $enumDef->attributes()->group) {
                    $const->groups = explode(',', $group);
                }

                if ($comment = (string) $enumDef->attributes()->comment) {
                    $const->comment = $comment;
                }
            }
        }
    }

    /**
     * Parse an element of commands
     * 
     * @param GLSpec                $spec
     * @param SimpleXMLElement      $feature
     */
    private function parseFeatures(GLSpec $spec, SimpleXMLElement $feature)
    {
        $version = $spec->makeVersion($feature->attributes()->name);
        $version->versionString = $feature->attributes()->number;
        $version->api = $feature->attributes()->api;

        foreach($feature->children() as $child) 
        {
            if ($child->getName() === 'require') 
            {
                // required features
                foreach($child->children() as $cat) 
                {   
                    if ($cat->getName() === 'enum') {
                        $version->enums[] = (string) $cat->attributes()->name;
                    }

                    elseif ($cat->getName() === 'command') {
                        $version->functions[] = (string) $cat->attributes()->name;
                    }
                }
            }
            elseif ($child->getName() === 'remove') 
            {
                // required features
                foreach($child->children() as $cat) 
                {   
                    if ($cat->getName() === 'enum') {
                        $version->removedEnums[] = (string) $cat->attributes()->name;
                    }

                    elseif ($cat->getName() === 'command') {
                        $version->removedFunctions[] = (string) $cat->attributes()->name;
                    }
                }
            }
        }
    }

    /**
     * Parse an element of commands
     * 
     * @param GLSpec                $spec
     * @param SimpleXMLElement      $commands
     */
    private function parseCommands(GLSpec $spec, SimpleXMLElement $commands)
    {
        foreach($commands->children() as $commandDef) 
        {
            if (!$commandDef->proto) {
                continue;
            }

            $proto = $commandDef->proto;

            $func = $spec->makeFunction((string)$proto->name);
            $func->class = $proto->attributes()->class;
            $func->group = $proto->attributes()->group;

            $funcPtype = trim((string) $proto->ptype);
            $func->returnTypeString = $funcPtype ?: trim((string) $proto);
            $func->fullReturnTypeString = substr(strip_tags((string) $proto->asXML()), 0, -strlen($func->name));

            // go over arguments
            foreach($commandDef->param as $argDef) 
            {
                $arg = $func->makeArg();
                $arg->name = (string) $argDef->name;
                $arg->typeString = (string) $argDef->ptype;
                $arg->fullTypeString = trim(substr(trim(strip_tags((string) $argDef->asXML())), 0, strlen($arg->name) * -1));
                $arg->class = $argDef->attributes()->class;
                $arg->group = $argDef->attributes()->group;
            }
        }
    }
}
