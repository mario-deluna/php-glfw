dnl $Id$
dnl config.m4 for extension glfw

PHP_ARG_ENABLE(glfw, whether to enable glfw support,
[  --enable-glfw           Enable glfw support])

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
  for i in /usr/local /usr /opt /opt/homebrew /opt/local; do
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
    AC_MSG_RESULT([GLFW lib not found, building from vendor source with Vulkan support])
    cd vendor/glfw
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

  dnl Check for Vulkan/MoltenVK support
  AC_MSG_CHECKING([for Vulkan/MoltenVK support])
  VULKAN_FOUND=no
  if test "$build_mac" = "yes"; then
    dnl macOS: check for MoltenVK via Homebrew
    for vulkan_dir in /opt/homebrew /usr/local /usr; do
      if test -r "$vulkan_dir/lib/libvulkan.dylib"; then
        VULKAN_DIR=$vulkan_dir
        VULKAN_FOUND=yes
        break
      fi
    done
  else
    dnl Linux: check for libvulkan
    for vulkan_dir in /usr /usr/local /opt; do
      if test -r "$vulkan_dir/lib/libvulkan.so" -o -r "$vulkan_dir/lib/x86_64-linux-gnu/libvulkan.so"; then
        VULKAN_DIR=$vulkan_dir
        VULKAN_FOUND=yes
        break
      fi
    done
  fi

  if test "$VULKAN_FOUND" = "yes"; then
    AC_MSG_RESULT([found in $VULKAN_DIR])
    AC_DEFINE(PHPGLFW_VULKAN_SUPPORT, 1, [Vulkan/MoltenVK support available])
  else
    AC_MSG_RESULT([not found — Vulkan features will be unavailable])
  fi

  # GLFW lib common sources
  GLFWLIB_SRC_FILES=""
  GLFWPLATTFORMARGS=""

  if test "$build_mac" = "yes"; then
    AC_DEFINE(_GLFW_COCOA, 1, [Cocoa support])
    GLFWPLATTFORMARGS="-D_GLFW_COCOA"
  else
    AC_DEFINE(_GLFW_X11, 1, [X11 support])
    GLFWPLATTFORMARGS="-D_GLFW_X11"
  fi

  PHPGLFW_SRC_FILES="phpglfw.c \
    phpglfw_constants.c \
    phpglfw_functions.c \
    phpglfw_math.c \
    phpglfw_buffer.c \
    phpglfw_texture.c \
    phpglfw_objparser.c \
    phpglfw_voxparser.c \
    phpglfw_svgparser.c \
    src/ogt_vox_c_wrapper.cpp \
    phpglfw_vg.c \
    phpglfw_audio.c \
    phpglfw_drawcall_assembler.c \
    vendor/fastobj/fast_obj.c \
    vendor/glad/src/glad.c \
    vendor/nanovg/src/nanovg.c"

  # we already use stb libs in phpglfw so we need to stop nanovg from implementing them
  GLFWPLATTFORMARGS="-DNVG_NO_STB=1 $GLFWPLATTFORMARGS"

  # the generated arginfo file has unicode issues because we have classes like "\\UInt"
  # im just going to supress those warnings for now, please don't judge me
  GLFWPLATTFORMARGS="-Wno-unicode $GLFWPLATTFORMARGS"

  PHP_ADD_LIBRARY_WITH_PATH(glfw, [$GLFW_DIR/lib], GLFW_SHARED_LIBADD)
  AC_DEFINE(HAVE_GLFW, 1, [Whether you have glfw])
  PHP_SUBST(GLFW_SHARED_LIBADD)

  PHP_REQUIRE_CXX()
  PHP_NEW_EXTENSION(glfw, $PHPGLFW_SRC_FILES $GLFWLIB_SRC_FILES, $ext_shared, , $GLFWPLATTFORMARGS -Wall)


  PHP_ADD_INCLUDE([$ext_srcdir])
  PHP_ADD_INCLUDE([$ext_srcdir/include])
  PHP_ADD_INCLUDE([$ext_srcdir/src])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/glad/include])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/cvector])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/stb])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/fastobj])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/nanosvg/src])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/nanovg/src])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/miniaudio])
  PHP_ADD_INCLUDE([$ext_srcdir/vendor/opengametools/src])
  PHP_ADD_INCLUDE([$GLFW_DIR/include])

  PHP_INSTALL_HEADERS([ext/glfw], [*.h \
        include/*.h \
        vendor/glad/include/glad/*.h \
        vendor/glad/include/KHR/*.h \
        vendor/cvector/*.h \
        vendor/stb/*.h \
        vendor/fastobj/*.h \
        vendor/nanosvg/src/*.h \
        vendor/nanovg/src/*.h \
        vendor/miniaudio/*.h \
        vendor/opengametools/src/*.h \
        vendor/glfw/include/GLFW/*.h])

  PHP_ADD_BUILD_DIR($ext_builddir/src)

fi
