dnl $Id$
dnl config.m4 for extension glfw

PHP_ARG_ENABLE(glfw, whether to enable glfw support,
[  --enable-glfw           Enable glfw support])

PHP_ARG_WITH(glfw-dir, for glfw library,
[  --with-glfw-dir[=DIR]   Set the path to glfw install prefix.], yes)

if test "$PHP_GLFW" != "no"; then
	
	AC_MSG_CHECKING([for glfw installation])
	
	if test "x$PHP_GLFW_DIR" != "xno" && test "x$PHP_GLFW_DIR" != "xyes"; then
    if test -r "$PHP_GLFW_DIR/include/GLFW/glfw3.h"; then
      GLFW_DIR=$PHP_GLFW_DIR
      break
    fi
  else
    for i in /usr/local /usr /opt /opt/local; do
      if test -r "$i/include/GLFW/glfw3.h"; then
        GLFW_DIR=$i
        break
      fi
    done
  fi

  if test "x$GLFW_DIR" = "x"; then
    AC_MSG_ERROR([not found])
  fi

  AC_MSG_RESULT([found in $GLFW_DIR])

  # GLAD
  #PHP_ADD_LIBRARY_WITH_PATH(glad, glad/$PHP_LIBDIR, GLFW_SHARED_LIBADD)
  PHP_ADD_INCLUDE(glad/include)
  
  # GLFW
  PHP_ADD_LIBRARY_WITH_PATH(glfw, [$GLFW_DIR/$PHP_LIBDIR], GLFW_SHARED_LIBADD)
  PHP_ADD_INCLUDE([$GLFW_DIR/include])

  # STB Image
  PHP_ADD_INCLUDE([$GLFW_DIR/stb_image])

  AC_DEFINE(HAVE_GLFW, 1, [Whether you have glfw])
  PHP_SUBST(GLFW_SHARED_LIBADD)

  PHP_NEW_EXTENSION(glfw, glfw_gen.c glad/src/glad.c, $ext_shared)
fi