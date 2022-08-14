<?php

/**
 * Class containing extension supported types
 */
class ExtType
{
    public const T_VOID = 'void';
    public const T_LONG = 'long';
    public const T_DOUBLE = 'double';
    public const T_BOOL = 'bool';
    public const T_STRING = 'string';
    public const T_NULL = 'null';
    public const T_IPO = '@ibo'; // internal pointer object (ex. GLFWwindow)
    public const T_CE = '@ce'; // class entry (object)
    public const T_VARIADIC = '@variadic'; // variadic argument
    public const T_FUNC = '@func';
    public const T_RESOURCE = '@res';

    /**
     * Returns the php type from a extension type
     */
    public static function getPHPType(string $type) : string
    {
        switch($type) {
            case 'long':
            case 'int':
                return 'int';
            break;
            case 'double':
            case 'float':
                return 'float';
            break;
            case 'bool':
                return 'bool';
            break;
            case 'void':
                return 'void';
            break;
            case 'string':
                return 'string';
            break;
            case '@func':
                return 'callable';
            break;
            case '@res':
                return 'resource';
            break;
            default: 
                throw new \Exception("Unmappable type {$type}");
        }
    }
}
