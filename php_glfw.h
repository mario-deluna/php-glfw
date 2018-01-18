#ifndef PHP_GLFW_H
#define PHP_GLFW_H 1
#define PHP_GLFW_VERSION "1.0"
#define PHP_GLFW_EXTNAME "glfw"

PHP_FUNCTION(hello_world);

extern zend_module_entry glfw_module_entry;
#define phpext_hello_ptr &glfw_module_entry

#endif