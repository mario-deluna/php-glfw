dnl $Id$
dnl config.m4 for extension glfw

PHP_ARG_ENABLE(glfw, whether to enable glfw support,
[  --enable-glfw           Enable glfw support])

if test "$PHP_GLFW" != "no"; then
  PHP_NEW_EXTENSION(glfw, phpglfw.c, $ext_shared)
fi