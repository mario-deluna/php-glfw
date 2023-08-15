dnl $Id$
dnl config.m4 for extension glfw

PHP_ARG_ENABLE([glfw],
  [enable glfw],
  [AS_HELP_STRING([--enable-glfw],
    [Enable glfw support])], [no], [no])  

PHP_ARG_WITH([glfw-dir],
  [dir of glfw],
  [AS_HELP_STRING([[--with-glfw-dir[=DIR]]],
    [Path to the glfw library directory])], [no], [no])

AC_MSG_CHECKING([for os target])
AC_CANONICAL_HOST
build_linux=no
build_mac=no

case "${host_os}" in
  linux*)
      build_linux=yes
      ;;
  darwin*)
      build_mac=yes
      ;;
  *)
      AC_MSG_ERROR(["OS $host_os is not supported"])
      ;;
esac

if test "$build_mac" = "yes"; then
  AC_MSG_RESULT([building for MacOS])
else 
  AC_MSG_RESULT([building for Linux])
fi

check_for_glfw3() {
  for i in /usr/local /usr /opt /opt/local; do
    if test -r "$i/include/GLFW/glfw3.h"; then
      GLFW_DIR=$i
      return 0
    fi
  done
  return 1
}

if test "$PHP_GLFW" != "no"; then
	
	AC_MSG_CHECKING([for glfw installation])
	
  if test "x$PHP_GLFW_DIR" != "xno"; then
    if test -r "$PHP_GLFW_DIR/include/GLFW/glfw3.h"; then
      GLFW_DIR=$PHP_GLFW_DIR
    else
      check_for_glfw3
    fi
  else
    check_for_glfw3
  fi

  if test "x$GLFW_DIR" = "x"; then
    AC_MSG_RESULT([GLFW lib not found, trying to build])
    # Build glfw
    cd vendor/glfw
    # cmake . -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=./ && make install
    cmake . -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_DOCS=OFF -DBUILD_SHARED_LIBS=ON && sudo make install
    if test "$build_linux" = "yes"; then
      sudo ldconfig 
    fi
    cd ./../../
    check_for_glfw3
  fi

  if test "x$GLFW_DIR" = "x"; then
    AC_MSG_ERROR([GLFW lib could not be located or build])
  fi

  AC_MSG_RESULT([found in $GLFW_DIR ($PHP_LIBDIR)])

  # GLFW lib common sources
  GLFWLIB_SRC_FILES=""
  GLFWPLATTFORMARGS=""

  if test "$build_mac" = "yes"; then
    AC_DEFINE(_GLFW_COCOA, 1, [Cocoa support])
    GLFWPLATTFORMARGS="-D_GLFW_COCOA"
    # GLFWLIB_SRC_FILES="$GLFWLIB_SRC_FILES \
    #   vendor/glfw/src/cocoa_init.m \
    #   vendor/glfw/src/cocoa_joystick.m \
    #   vendor/glfw/src/cocoa_monitor.m \
    #   vendor/glfw/src/cocoa_window.m \
    #   vendor/glfw/src/cocoa_time.c \
    #   vendor/glfw/src/posix_thread.c \
    #   vendor/glfw/src/nsgl_context.m \
    #   vendor/glfw/src/egl_context.c \
    #   vendor/glfw/src/osmesa_context.c"
  else 
    AC_DEFINE(_GLFW_X11, 1, [X11 support])
    GLFWPLATTFORMARGS="-D_GLFW_X11"
    # GLFWLIB_SRC_FILES="vendor/glfw/src/context.c \
    #   vendor/glfw/src/init.c \
    #   vendor/glfw/src/input.c \
    #   vendor/glfw/src/monitor.c \
    #   vendor/glfw/src/vulkan.c \
    #   vendor/glfw/src/window.c"

    # GLFWLIB_SRC_FILES="$GLFWLIB_SRC_FILES \
    #   vendor/glfw/src/x11_init.c \
    #   vendor/glfw/src/x11_monitor.c \
    #   vendor/glfw/src/x11_window.c \x
    #   vendor/glfw/src/xkb_unicode.c \
    #   vendor/glfw/src/posix_time.c \
    #   vendor/glfw/src/posix_thread.c \
    #   vendor/glfw/src/glx_context.c \
    #   vendor/glfw/src/egl_context.c \
    #   vendor/glfw/src/osmesa_context.c \
    #   vendor/glfw/src/null_joystick.c"
    
    # PHP_ADD_BUILD_DIR($ext_builddir/vendor/glfw/src)
  fi

  PHPGLFW_SRC_FILES="phpglfw.c \
    phpglfw_constants.c \
    phpglfw_functions.c \
    phpglfw_math.c \
    phpglfw_buffer.c \
    phpglfw_texture.c \
    phpglfw_objparser.c \
    vendor/fastobj/fast_obj.c \
    vendor/glad/src/glad.c"

  PHP_ADD_LIBRARY_WITH_PATH(glfw, [$GLFW_DIR/lib], GLFW_SHARED_LIBADD)
  AC_DEFINE(HAVE_GLFW, 1, [Whether you have glfw])
  PHP_SUBST(GLFW_SHARED_LIBADD)
    
  PHP_NEW_EXTENSION(glfw, $PHPGLFW_SRC_FILES $GLFWLIB_SRC_FILES, $ext_shared, , $GLFWPLATTFORMARGS -Wall)

  PHP_ADD_INCLUDE([$ext_srcdir])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/glad/include])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/cvector])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/stb])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/fastobj])
  PHP_ADD_INCLUDE([$GLFW_DIR/include])

  PHP_INSTALL_HEADERS([ext/glfw], [*.h \
        vendor/glad/include/*.h \
        vendor/cvector/*.h \
        vendor/stb/*.h \
        vendor/fastobj/*.h])

  PHP_ADD_BUILD_DIR($ext_builddir/src)

fi