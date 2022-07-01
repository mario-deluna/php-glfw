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
    public const T_RESOURCE = '@res';
}
