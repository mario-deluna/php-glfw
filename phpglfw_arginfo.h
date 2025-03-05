/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 8b5a0cc01502c19f354de06ca8620ed8b72f1e74 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCullFace, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glFrontFace arginfo_glCullFace

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glHint, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glLineWidth, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPointSize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPolygonMode, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, face, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glScissor, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexParameterf, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexParameterfv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, params, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexParameteri, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexParameteriv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, params, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexImage2D, 0, 9, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, border, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, data, GL\\Buffer\\BufferInterface, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDrawBuffer, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buf, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClear, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearColor, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, red, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, green, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, blue, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearStencil, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearDepth, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glStencilMask arginfo_glClear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glColorMask, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, red, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, green, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, blue, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDepthMask, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, flag, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDisable, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, cap, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glEnable arginfo_glDisable

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFinish, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

#define arginfo_glFlush arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendFunc, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sfactor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dfactor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glLogicOp, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, opcode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glStencilFunc, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, func, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ref, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glStencilOp, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, fail, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, zfail, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, zpass, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDepthFunc, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, func, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPixelStoref, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPixelStorei, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glReadBuffer, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glReadPixels, 0, 7, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, pixels, GL\\Buffer\\BufferInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetBooleanv, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, data, _IS_BOOL, 1)
ZEND_END_ARG_INFO()

#define arginfo_glGetDoublev arginfo_glGetBooleanv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetError, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetFloatv arginfo_glGetBooleanv

#define arginfo_glGetIntegerv arginfo_glGetBooleanv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetString, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetTexImage, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, pixels, GL\\Buffer\\BufferInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetTexParameterfv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, params, _IS_BOOL, 1)
ZEND_END_ARG_INFO()

#define arginfo_glGetTexParameteriv arginfo_glGetTexParameterfv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetTexLevelParameterfv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetTexLevelParameteriv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsEnabled, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, cap, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDepthRange, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, f, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glViewport arginfo_glScissor

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDrawArrays, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPolygonOffset, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, factor, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, units, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCopyTexImage1D, 0, 7, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, border, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCopyTexImage2D, 0, 8, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, border, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCopyTexSubImage1D, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xoffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCopyTexSubImage2D, 0, 8, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xoffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, yoffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindTexture, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteTextures, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, textures, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenTextures, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, textures, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsTexture, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCopyTexSubImage3D, 0, 9, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, xoffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, yoffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, zoffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glActiveTexture, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSampleCoverage, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, invert, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendFuncSeparate, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sfactorRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dfactorRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sfactorAlpha, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dfactorAlpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glPointParameterf arginfo_glPixelStoref

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPointParameterfv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, params, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glPointParameteri arginfo_glPixelStorei

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPointParameteriv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, params, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glBlendColor arginfo_glClearColor

#define arginfo_glBlendEquation arginfo_glCullFace

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenQueries, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, ids, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteQueries, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, ids, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsQuery, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBeginQuery, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glEndQuery, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetQueryiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetQueryObjectiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetQueryObjectuiv arginfo_glGetQueryObjectiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindBuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteBuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, buffers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenBuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, buffers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsBuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUnmapBuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetBufferParameteriv arginfo_glGetQueryiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendEquationSeparate, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, modeRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, modeAlpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDrawBuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, bufs, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glStencilOpSeparate, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, face, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sfail, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dpfail, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dppass, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glStencilFuncSeparate, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, face, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, func, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ref, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glStencilMaskSeparate, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, face, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glAttachShader, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindAttribLocation, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCompileShader, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glCreateProgram arginfo_glGetError

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCreateShader, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteProgram, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glDeleteShader arginfo_glCompileShader

#define arginfo_glDetachShader arginfo_glAttachShader

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDisableVertexAttribArray, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glEnableVertexAttribArray arginfo_glDisableVertexAttribArray

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetAttachedShaders, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxCount, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, count, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, shaders, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetAttribLocation, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetProgramiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetProgramInfoLog, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bufSize, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetShaderiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetShaderInfoLog, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bufSize, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetUniformLocation arginfo_glGetAttribLocation

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetUniformfv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetUniformiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetVertexAttribdv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetVertexAttribfv arginfo_glGetVertexAttribdv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetVertexAttribiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsProgram, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsShader, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glLinkProgram arginfo_glDeleteProgram

#define arginfo_glUseProgram arginfo_glDeleteProgram

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1f, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform2f, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform3f, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform4f, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v3, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1i, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform2i, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform3i, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform4i, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v3, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1fv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glUniform2fv arginfo_glUniform1fv

#define arginfo_glUniform3fv arginfo_glUniform1fv

#define arginfo_glUniform4fv arginfo_glUniform1fv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1iv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glUniform2iv arginfo_glUniform1iv

#define arginfo_glUniform3iv arginfo_glUniform1iv

#define arginfo_glUniform4iv arginfo_glUniform1iv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformMatrix2fv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transpose, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glUniformMatrix3fv arginfo_glUniformMatrix2fv

#define arginfo_glUniformMatrix4fv arginfo_glUniformMatrix2fv

#define arginfo_glValidateProgram arginfo_glDeleteProgram

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1d, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1dv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\DoubleBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib1f arginfo_glVertexAttrib1d

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1fv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1s, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1sv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\ShortBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib2d, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib2dv arginfo_glVertexAttrib1dv

#define arginfo_glVertexAttrib2f arginfo_glVertexAttrib2d

#define arginfo_glVertexAttrib2fv arginfo_glVertexAttrib1fv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib2s, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib2sv arginfo_glVertexAttrib1sv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib3d, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib3dv arginfo_glVertexAttrib1dv

#define arginfo_glVertexAttrib3f arginfo_glVertexAttrib3d

#define arginfo_glVertexAttrib3fv arginfo_glVertexAttrib1fv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib3s, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib3sv arginfo_glVertexAttrib1sv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Nbv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\ByteBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Niv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib4Nsv arginfo_glVertexAttrib1sv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Nub, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Nubv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\\125byteBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Nuiv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Nusv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\\125ShortBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib4bv arginfo_glVertexAttrib4Nbv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4d, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib4dv arginfo_glVertexAttrib1dv

#define arginfo_glVertexAttrib4f arginfo_glVertexAttrib4d

#define arginfo_glVertexAttrib4fv arginfo_glVertexAttrib1fv

#define arginfo_glVertexAttrib4iv arginfo_glVertexAttrib4Niv

#define arginfo_glVertexAttrib4s arginfo_glVertexAttrib4Nub

#define arginfo_glVertexAttrib4sv arginfo_glVertexAttrib1sv

#define arginfo_glVertexAttrib4ubv arginfo_glVertexAttrib4Nubv

#define arginfo_glVertexAttrib4uiv arginfo_glVertexAttrib4Nuiv

#define arginfo_glVertexAttrib4usv arginfo_glVertexAttrib4Nusv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttribPointer, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, normalized, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, stride, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glUniformMatrix2x3fv arginfo_glUniformMatrix2fv

#define arginfo_glUniformMatrix3x2fv arginfo_glUniformMatrix2fv

#define arginfo_glUniformMatrix2x4fv arginfo_glUniformMatrix2fv

#define arginfo_glUniformMatrix4x2fv arginfo_glUniformMatrix2fv

#define arginfo_glUniformMatrix3x4fv arginfo_glUniformMatrix2fv

#define arginfo_glUniformMatrix4x3fv arginfo_glUniformMatrix2fv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glColorMaski, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, g, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, b, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, a, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetBooleani_v, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, data, _IS_BOOL, 1)
ZEND_END_ARG_INFO()

#define arginfo_glGetIntegeri_v arginfo_glGetBooleani_v

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glEnablei, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glDisablei arginfo_glEnablei

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsEnabledi, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBeginTransformFeedback, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, primitiveMode, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glEndTransformFeedback arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindBufferRange, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindBufferBase, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClampColor, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, clamp, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBeginConditionalRender, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glEndConditionalRender arginfo_glFinish

#define arginfo_glGetVertexAttribIiv arginfo_glGetVertexAttribiv

#define arginfo_glGetVertexAttribIuiv arginfo_glGetVertexAttribiv

#define arginfo_glVertexAttribI1i arginfo_glVertexAttrib1s

#define arginfo_glVertexAttribI2i arginfo_glVertexAttrib2s

#define arginfo_glVertexAttribI3i arginfo_glVertexAttrib3s

#define arginfo_glVertexAttribI4i arginfo_glVertexAttrib4Nub

#define arginfo_glVertexAttribI1ui arginfo_glVertexAttrib1s

#define arginfo_glVertexAttribI2ui arginfo_glVertexAttrib2s

#define arginfo_glVertexAttribI3ui arginfo_glVertexAttrib3s

#define arginfo_glVertexAttribI4ui arginfo_glVertexAttrib4Nub

#define arginfo_glVertexAttribI1iv arginfo_glVertexAttrib4Niv

#define arginfo_glVertexAttribI2iv arginfo_glVertexAttrib4Niv

#define arginfo_glVertexAttribI3iv arginfo_glVertexAttrib4Niv

#define arginfo_glVertexAttribI4iv arginfo_glVertexAttrib4Niv

#define arginfo_glVertexAttribI1uiv arginfo_glVertexAttrib4Nuiv

#define arginfo_glVertexAttribI2uiv arginfo_glVertexAttrib4Nuiv

#define arginfo_glVertexAttribI3uiv arginfo_glVertexAttrib4Nuiv

#define arginfo_glVertexAttribI4uiv arginfo_glVertexAttrib4Nuiv

#define arginfo_glVertexAttribI4bv arginfo_glVertexAttrib4Nbv

#define arginfo_glVertexAttribI4sv arginfo_glVertexAttrib1sv

#define arginfo_glVertexAttribI4ubv arginfo_glVertexAttrib4Nubv

#define arginfo_glVertexAttribI4usv arginfo_glVertexAttrib4Nusv

#define arginfo_glGetUniformuiv arginfo_glGetUniformiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindFragDataLocation, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetFragDataLocation arginfo_glGetAttribLocation

#define arginfo_glUniform1ui arginfo_glUniform1i

#define arginfo_glUniform2ui arginfo_glUniform2i

#define arginfo_glUniform3ui arginfo_glUniform3i

#define arginfo_glUniform4ui arginfo_glUniform4i

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1uiv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glUniform2uiv arginfo_glUniform1uiv

#define arginfo_glUniform3uiv arginfo_glUniform1uiv

#define arginfo_glUniform4uiv arginfo_glUniform1uiv

#define arginfo_glTexParameterIiv arginfo_glTexParameteriv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexParameterIuiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, params, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glGetTexParameterIiv arginfo_glGetTexParameterfv

#define arginfo_glGetTexParameterIuiv arginfo_glGetTexParameterfv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearBufferiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, drawbuffer, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearBufferuiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, drawbuffer, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearBufferfv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, drawbuffer, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearBufferfi, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, drawbuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, stencil, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetStringi, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsRenderbuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderbuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindRenderbuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderbuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteRenderbuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, renderbuffers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenRenderbuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, renderbuffers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glRenderbufferStorage, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetRenderbufferParameteriv arginfo_glGetQueryiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsFramebuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, framebuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindFramebuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, framebuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteFramebuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, framebuffers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenFramebuffers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, framebuffers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCheckFramebufferStatus, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFramebufferTexture1D, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attachment, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, textarget, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glFramebufferTexture2D arginfo_glFramebufferTexture1D

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFramebufferTexture3D, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attachment, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, textarget, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, zoffset, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFramebufferRenderbuffer, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attachment, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderbuffertarget, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderbuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetFramebufferAttachmentParameteriv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attachment, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGenerateMipmap arginfo_glEndQuery

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlitFramebuffer, 0, 10, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, srcX0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, srcY0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, srcX1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, srcY1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstX0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstY0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstX1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstY1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, filter, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glRenderbufferStorageMultisample, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, samples, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFramebufferTextureLayer, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attachment, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, layer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFlushMappedBufferRange, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, offset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, length, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindVertexArray, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, array, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteVertexArrays, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, arrays, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenVertexArrays, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, arrays, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsVertexArray, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, array, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDrawArraysInstanced, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, first, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, instancecount, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexBuffer, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glPrimitiveRestartIndex arginfo_glDisableVertexAttribArray

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glCopyBufferSubData, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, readTarget, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, writeTarget, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, readOffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, writeOffset, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetUniformBlockIndex, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uniformBlockName, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetActiveUniformBlockiv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uniformBlockIndex, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformBlockBinding, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uniformBlockIndex, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uniformBlockBinding, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProvokingVertex arginfo_glCullFace

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsSync, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, sync, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteSync, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sync, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClientWaitSync, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sync, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glWaitSync, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sync, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetInteger64v, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, data, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetInteger64i_v, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, data, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetBufferParameteri64v arginfo_glGetQueryiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFramebufferTexture, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, attachment, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexImage2DMultisample, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, samples, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fixedsamplelocations, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexImage3DMultisample, 0, 7, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, samples, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fixedsamplelocations, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetMultisamplefv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, val, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSampleMaski, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, maskNumber, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mask, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindFragDataLocationIndexed, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, colorNumber, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetFragDataIndex arginfo_glGetAttribLocation

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenSamplers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, samplers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteSamplers, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, samplers, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsSampler, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindSampler, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, unit, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSamplerParameteri, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSamplerParameteriv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, param, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSamplerParameterf, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSamplerParameterfv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, param, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glSamplerParameterIiv arginfo_glSamplerParameteriv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSamplerParameterIuiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, param, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetSamplerParameteriv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetSamplerParameterIiv arginfo_glGetSamplerParameteriv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetSamplerParameterfv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetSamplerParameterIuiv arginfo_glGetSamplerParameteriv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glQueryCounter, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetQueryObjecti64v arginfo_glGetQueryObjectiv

#define arginfo_glGetQueryObjectui64v arginfo_glGetQueryObjectiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttribDivisor, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, divisor, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttribP1ui, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, normalized, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttribP1uiv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, normalized, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttribP2ui arginfo_glVertexAttribP1ui

#define arginfo_glVertexAttribP2uiv arginfo_glVertexAttribP1uiv

#define arginfo_glVertexAttribP3ui arginfo_glVertexAttribP1ui

#define arginfo_glVertexAttribP3uiv arginfo_glVertexAttribP1uiv

#define arginfo_glVertexAttribP4ui arginfo_glVertexAttribP1ui

#define arginfo_glVertexAttribP4uiv arginfo_glVertexAttribP1uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexP2ui, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexP2uiv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glVertexP3ui arginfo_glVertexP2ui

#define arginfo_glVertexP3uiv arginfo_glVertexP2uiv

#define arginfo_glVertexP4ui arginfo_glVertexP2ui

#define arginfo_glVertexP4uiv arginfo_glVertexP2uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexCoordP1ui, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, coords, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexCoordP1uiv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, coords, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glTexCoordP2ui arginfo_glTexCoordP1ui

#define arginfo_glTexCoordP2uiv arginfo_glTexCoordP1uiv

#define arginfo_glTexCoordP3ui arginfo_glTexCoordP1ui

#define arginfo_glTexCoordP3uiv arginfo_glTexCoordP1uiv

#define arginfo_glTexCoordP4ui arginfo_glTexCoordP1ui

#define arginfo_glTexCoordP4uiv arginfo_glTexCoordP1uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glMultiTexCoordP1ui, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, coords, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glMultiTexCoordP1uiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, coords, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glMultiTexCoordP2ui arginfo_glMultiTexCoordP1ui

#define arginfo_glMultiTexCoordP2uiv arginfo_glMultiTexCoordP1uiv

#define arginfo_glMultiTexCoordP3ui arginfo_glMultiTexCoordP1ui

#define arginfo_glMultiTexCoordP3uiv arginfo_glMultiTexCoordP1uiv

#define arginfo_glMultiTexCoordP4ui arginfo_glMultiTexCoordP1ui

#define arginfo_glMultiTexCoordP4uiv arginfo_glMultiTexCoordP1uiv

#define arginfo_glNormalP3ui arginfo_glTexCoordP1ui

#define arginfo_glNormalP3uiv arginfo_glTexCoordP1uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glColorP3ui, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glColorP3uiv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, color, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glColorP4ui arginfo_glColorP3ui

#define arginfo_glColorP4uiv arginfo_glColorP3uiv

#define arginfo_glSecondaryColorP3ui arginfo_glColorP3ui

#define arginfo_glSecondaryColorP3uiv arginfo_glColorP3uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glMinSampleShading, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendEquationi, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buf, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendEquationSeparatei, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buf, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, modeRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, modeAlpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendFunci, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buf, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, src, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dst, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendFuncSeparatei, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buf, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, srcRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, srcAlpha, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstAlpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1d, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform2d, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform3d, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform4d, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniform1dv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\DoubleBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glUniform2dv arginfo_glUniform1dv

#define arginfo_glUniform3dv arginfo_glUniform1dv

#define arginfo_glUniform4dv arginfo_glUniform1dv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformMatrix2dv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transpose, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\DoubleBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glUniformMatrix3dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix4dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix2x3dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix2x4dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix3x2dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix3x4dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix4x2dv arginfo_glUniformMatrix2dv

#define arginfo_glUniformMatrix4x3dv arginfo_glUniformMatrix2dv

#define arginfo_glGetUniformdv arginfo_glGetUniformfv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetSubroutineUniformLocation, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetSubroutineIndex arginfo_glGetSubroutineUniformLocation

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetActiveSubroutineUniformiv, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, values, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformSubroutinesuiv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, indices, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetUniformSubroutineuiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetProgramStageiv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, values, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPatchParameteri, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPatchParameterfv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, values, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glBindTransformFeedback arginfo_glBeginQuery

#define arginfo_glDeleteTransformFeedbacks arginfo_glDeleteQueries

#define arginfo_glGenTransformFeedbacks arginfo_glGenQueries

#define arginfo_glIsTransformFeedback arginfo_glIsQuery

#define arginfo_glPauseTransformFeedback arginfo_glFinish

#define arginfo_glResumeTransformFeedback arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDrawTransformFeedback, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDrawTransformFeedbackStream, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stream, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBeginQueryIndexed, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glEndQueryIndexed arginfo_glEnablei

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetQueryIndexediv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glReleaseShaderCompiler arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetShaderPrecisionFormat, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, precisiontype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, range, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, precision, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glDepthRangef arginfo_glDepthRange

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearDepthf, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, d, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramParameteri, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUseProgramStages, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pipeline, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, stages, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glActiveShaderProgram, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pipeline, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindProgramPipeline, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDeleteProgramPipelines, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(0, pipelines, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGenProgramPipelines, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_VARIADIC_TYPE_INFO(1, pipelines, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsProgramPipeline, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetProgramPipelineiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pipeline, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, params, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1i, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1iv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1f, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1fv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform1d arginfo_glProgramUniform1f

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1dv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\DoubleBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform1ui arginfo_glProgramUniform1i

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1uiv, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\\125IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform2i, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform2iv arginfo_glProgramUniform1iv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform2f, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform2fv arginfo_glProgramUniform1fv

#define arginfo_glProgramUniform2d arginfo_glProgramUniform2f

#define arginfo_glProgramUniform2dv arginfo_glProgramUniform1dv

#define arginfo_glProgramUniform2ui arginfo_glProgramUniform2i

#define arginfo_glProgramUniform2uiv arginfo_glProgramUniform1uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform3i, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform3iv arginfo_glProgramUniform1iv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform3f, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform3fv arginfo_glProgramUniform1fv

#define arginfo_glProgramUniform3d arginfo_glProgramUniform3f

#define arginfo_glProgramUniform3dv arginfo_glProgramUniform1dv

#define arginfo_glProgramUniform3ui arginfo_glProgramUniform3i

#define arginfo_glProgramUniform3uiv arginfo_glProgramUniform1uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform4i, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v3, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform4iv arginfo_glProgramUniform1iv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform4f, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v3, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform4fv arginfo_glProgramUniform1fv

#define arginfo_glProgramUniform4d arginfo_glProgramUniform4f

#define arginfo_glProgramUniform4dv arginfo_glProgramUniform1dv

#define arginfo_glProgramUniform4ui arginfo_glProgramUniform4i

#define arginfo_glProgramUniform4uiv arginfo_glProgramUniform1uiv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniformMatrix2fv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transpose, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniformMatrix3fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix4fv arginfo_glProgramUniformMatrix2fv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniformMatrix2dv, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transpose, _IS_BOOL, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, value, GL\\Buffer\\DoubleBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniformMatrix3dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix4dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix2x3fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix3x2fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix2x4fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix4x2fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix3x4fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix4x3fv arginfo_glProgramUniformMatrix2fv

#define arginfo_glProgramUniformMatrix2x3dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix3x2dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix2x4dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix4x2dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix3x4dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glProgramUniformMatrix4x3dv arginfo_glProgramUniformMatrix2dv

#define arginfo_glValidateProgramPipeline arginfo_glBindProgramPipeline

#define arginfo_glVertexAttribL1d arginfo_glVertexAttrib1d

#define arginfo_glVertexAttribL2d arginfo_glVertexAttrib2d

#define arginfo_glVertexAttribL3d arginfo_glVertexAttrib3d

#define arginfo_glVertexAttribL4d arginfo_glVertexAttrib4d

#define arginfo_glVertexAttribL1dv arginfo_glVertexAttrib1dv

#define arginfo_glVertexAttribL2dv arginfo_glVertexAttrib1dv

#define arginfo_glVertexAttribL3dv arginfo_glVertexAttrib1dv

#define arginfo_glVertexAttribL4dv arginfo_glVertexAttrib1dv

#define arginfo_glGetVertexAttribLdv arginfo_glGetVertexAttribdv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glViewportArrayv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, first, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\FloatBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glViewportIndexedf, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glViewportIndexedfv arginfo_glVertexAttrib1fv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glScissorArrayv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, first, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\IntBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glScissorIndexed, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, left, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bottom, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glScissorIndexedv arginfo_glVertexAttrib4Niv

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDepthRangeArrayv, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, first, IS_LONG, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, v, GL\\Buffer\\DoubleBuffer, MAY_BE_ARRAY, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDepthRangeIndexed, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, f, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetFloati_v arginfo_glGetBooleani_v

#define arginfo_glGetDoublei_v arginfo_glGetBooleani_v

#define arginfo_glfwInit arginfo_glGetError

#define arginfo_glfwTerminate arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwInitHint, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetVersion, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(1, major, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, minor, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, rev, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetVersionString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetPrimaryMonitor, 0, 0, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorWorkarea, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorPhysicalSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, widthMM, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, heightMM, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorContentScale, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(1, xscale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(1, yscale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMonitorName, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetVideoModes, 0, 1, GLFWvidmode, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetVideoMode arginfo_glfwGetVideoModes

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetGamma, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
	ZEND_ARG_TYPE_INFO(0, gamma, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwDefaultWindowHints arginfo_glFinish

#define arginfo_glfwWindowHint arginfo_glfwInitHint

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwWindowHintString, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, hint, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwCreateWindow, 0, 3, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, monitor, GLFWmonitor, 1, "NULL")
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, share, GLFWwindow, 1, "NULL")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwDestroyWindow, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwWindowShouldClose, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowShouldClose, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowTitle, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, title, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowSizeLimits, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, minwidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minheight, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxwidth, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, maxheight, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowAspectRatio, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, numer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, denom, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetFramebufferSize arginfo_glfwGetWindowSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowFrameSize, 0, 5, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, left, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, top, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, right, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, bottom, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowContentScale, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, xscale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(1, yscale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowOpacity, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowOpacity, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, opacity, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwIconifyWindow arginfo_glfwDestroyWindow

#define arginfo_glfwRestoreWindow arginfo_glfwDestroyWindow

#define arginfo_glfwMaximizeWindow arginfo_glfwDestroyWindow

#define arginfo_glfwShowWindow arginfo_glfwDestroyWindow

#define arginfo_glfwHideWindow arginfo_glfwDestroyWindow

#define arginfo_glfwFocusWindow arginfo_glfwDestroyWindow

#define arginfo_glfwRequestWindowAttention arginfo_glfwDestroyWindow

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetWindowMonitor, 0, 1, GLFWmonitor, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowMonitor, 0, 7, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 1)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, refreshRate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetWindowAttrib, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, attrib, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowAttrib, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, attrib, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetWindowPosCallback, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, callback, IS_CALLABLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwSetWindowSizeCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowCloseCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowRefreshCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowFocusCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowIconifyCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowMaximizeCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetFramebufferSizeCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetWindowContentScaleCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwPollEvents arginfo_glFinish

#define arginfo_glfwWaitEvents arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwWaitEventsTimeout, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, timeout, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwPostEmptyEvent arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetInputMode, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetInputMode, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, mode, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwRawMouseMotionSupported arginfo_glGetError

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetKeyName, 0, 2, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scancode, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetKeyScancode, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetKey, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetMouseButton, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, button, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetCursorPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(1, xpos, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(1, ypos, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetCursorPos, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, xpos, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ypos, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwCreateStandardCursor, 0, 1, GLFWcursor, 0)
	ZEND_ARG_TYPE_INFO(0, shape, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwDestroyCursor, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, cursor, GLFWcursor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetCursor, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_OBJ_INFO(0, cursor, GLFWcursor, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwSetKeyCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetCharCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetCharModsCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetMouseButtonCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetCursorPosCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetCursorEnterCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetScrollCallback arginfo_glfwSetWindowPosCallback

#define arginfo_glfwSetDropCallback arginfo_glfwSetWindowPosCallback

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwJoystickPresent, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetJoystickAxes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetJoystickButtons arginfo_glfwGetJoystickAxes

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetJoystickName, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetJoystickGUID arginfo_glfwGetJoystickName

#define arginfo_glfwJoystickIsGamepad arginfo_glfwJoystickPresent

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwUpdateGamepadMappings, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetGamepadName arginfo_glfwGetJoystickName

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetClipboardString, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetClipboardString, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, window, GLFWwindow, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetTime, 0, 0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSetTime, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, time, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwMakeContextCurrent arginfo_glfwDestroyWindow

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_glfwGetCurrentContext, 0, 0, GLFWwindow, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwSwapBuffers arginfo_glfwDestroyWindow

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwSwapInterval, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, interval, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwExtensionSupported, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, extension, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwVulkanSupported arginfo_glGetError

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwGetGamepadAxes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, joystick, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glfwGetGamepadButtons arginfo_glfwGetGamepadAxes

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glShaderSource, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, source, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBufferData, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\BufferInterface, 0)
	ZEND_ARG_TYPE_INFO(0, usage, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformMatrix4f, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, transpose, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, GL\\Math\\Mat4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformVec2f, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec2, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformVec3f, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformVec4f, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Geometry_ObjFileParser___construct, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Geometry_ObjFileParser_getVertices, 0, 1, GL\\Buffer\\FloatBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, layout, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, group, GL\\Geometry\\ObjFileParser\\Group, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Geometry_ObjFileParser_getIndexedVertices, 0, 1, GL\\Geometry\\ObjFileParser\\Mesh, 0)
	ZEND_ARG_TYPE_INFO(0, layout, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, group, GL\\Geometry\\ObjFileParser\\Group, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Geometry_ObjFileParser_getMeshes, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, layout, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, group, GL\\Geometry\\ObjFileParser\\Group, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Geometry_ObjFileParser_getIndexedMeshes arginfo_class_GL_Geometry_ObjFileParser_getMeshes

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Geometry_ObjFileParser_Material___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Geometry_ObjFileParser_Group___construct arginfo_class_GL_Geometry_ObjFileParser_Material___construct

#define arginfo_class_GL_Geometry_ObjFileParser_Texture___construct arginfo_class_GL_Geometry_ObjFileParser_Material___construct

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Texture_Texture2D_fromDisk, 0, 1, GL\\Texture\\Texture2D, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, requestedChannelCount, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, flipVertically, _IS_BOOL, 0, "true")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Texture_Texture2D_fromBuffer, 0, 3, GL\\Texture\\Texture2D, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\\125ByteBuffer, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, channels, IS_LONG, 0, "GL\\Texture\\Texture2D::CHANNEL_RGBA")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Texture_Texture2D_buffer, 0, 0, GL\\Buffer\\\125ByteBuffer, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Texture_Texture2D_width arginfo_glGetError

#define arginfo_class_GL_Texture_Texture2D_height arginfo_glGetError

#define arginfo_class_GL_Texture_Texture2D_channels arginfo_glGetError

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Texture_Texture2D_writeJPG, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, quality, IS_LONG, 0, "100")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Texture_Texture2D_writePNG, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Texture_Texture2D_writeBMP arginfo_class_GL_Texture_Texture2D_writePNG

#define arginfo_class_GL_Texture_Texture2D_writeTGA arginfo_class_GL_Texture_Texture2D_writePNG

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_perlin, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, wrapX, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, wrapY, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, wrapZ, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, seed, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_ridge, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, lacunarity, IS_DOUBLE, 0, "2.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gain, IS_DOUBLE, 0, "0.5")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offset, IS_DOUBLE, 0, "1.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, octaves, IS_LONG, 0, "6")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_fbm, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, lacunarity, IS_DOUBLE, 0, "2.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gain, IS_DOUBLE, 0, "0.5")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, octaves, IS_LONG, 0, "6")
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Noise_turbulence arginfo_class_GL_Noise_fbm

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_perlinFill2D, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\FloatBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offsetX, IS_DOUBLE, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offsetY, IS_DOUBLE, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, wrapX, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, wrapY, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, seed, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_ridgeFill2D, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\FloatBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offsetX, IS_DOUBLE, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offsetY, IS_DOUBLE, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, lacunarity, IS_DOUBLE, 0, "2.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gain, IS_DOUBLE, 0, "0.5")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offset, IS_DOUBLE, 0, "1.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, octaves, IS_LONG, 0, "6")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_fbmFill2D, 0, 4, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\FloatBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offsetX, IS_DOUBLE, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, offsetY, IS_DOUBLE, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, lacunarity, IS_DOUBLE, 0, "2.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gain, IS_DOUBLE, 0, "0.5")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, octaves, IS_LONG, 0, "6")
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Noise_turbulenceFill2D arginfo_class_GL_Noise_fbmFill2D

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Noise_islandFill2D, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\FloatBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, islandseed, IS_LONG, 0, "42")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, scale, IS_DOUBLE, 0, "1.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, islandmix, IS_DOUBLE, 0, "0.7")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, lacunarity, IS_DOUBLE, 0, "2.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, gain, IS_DOUBLE, 0, "0.5")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, octaves, IS_LONG, 0, "6")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_GLM_radians, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, degrees, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_GLM_angle, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, radians, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_GLM_triangleNormal, 0, 3, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, p1, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, p2, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, p3, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_TYPE_MASK_EX(arginfo_class_GL_Math_GLM_normalize, 0, 1, GL\\Math\\Vec2|GL\\Math\\Vec3|GL\\Math\\Vec4, 0)
	ZEND_ARG_OBJ_TYPE_MASK(0, vec, GL\\Math\\Vec2|GL\\Math\\Vec3|GL\\Math\\Vec4, 0, NULL)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Math_Vec2___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_DOUBLE, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec2_copy, 0, 0, GL\\Math\\Vec2, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec2_normalized, 0, 1, GL\\Math\\Vec2, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec2, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Vec2_distance, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec2, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec2, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec2_distance2 arginfo_class_GL_Math_Vec2_distance

#define arginfo_class_GL_Math_Vec2_dot arginfo_class_GL_Math_Vec2_distance

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec2_mix, 0, 3, GL\\Math\\Vec2, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec2, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec2, 0)
	ZEND_ARG_TYPE_INFO(0, t, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec2_lerp arginfo_class_GL_Math_Vec2_mix

#define arginfo_class_GL_Math_Vec2_slerp arginfo_class_GL_Math_Vec2_mix

#define arginfo_class_GL_Math_Vec2_length arginfo_glfwGetTime

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Vec2_distanceTo, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec2, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec2_distance2To arginfo_class_GL_Math_Vec2_distanceTo

#define arginfo_class_GL_Math_Vec2_normalize arginfo_glFinish

#define arginfo_class_GL_Math_Vec2_abs arginfo_glFinish

#define arginfo_class_GL_Math_Vec2___toString arginfo_glfwGetVersionString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Math_Vec3___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, z, IS_DOUBLE, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec3_copy, 0, 0, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec3_normalized, 0, 1, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Vec3_distance, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec3_distance2 arginfo_class_GL_Math_Vec3_distance

#define arginfo_class_GL_Math_Vec3_dot arginfo_class_GL_Math_Vec3_distance

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec3_mix, 0, 3, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec3, 0)
	ZEND_ARG_TYPE_INFO(0, t, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec3_lerp arginfo_class_GL_Math_Vec3_mix

#define arginfo_class_GL_Math_Vec3_slerp arginfo_class_GL_Math_Vec3_mix

#define arginfo_class_GL_Math_Vec3_length arginfo_glfwGetTime

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Vec3_distanceTo, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec3_distance2To arginfo_class_GL_Math_Vec3_distanceTo

#define arginfo_class_GL_Math_Vec3_normalize arginfo_glFinish

#define arginfo_class_GL_Math_Vec3_abs arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec3_cross, 0, 2, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec3_multiplyQuat, 0, 2, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Quat, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec3___toString arginfo_glfwGetVersionString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Math_Vec4___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, z, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, w, IS_DOUBLE, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec4_copy, 0, 0, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec4_normalized, 0, 1, GL\\Math\\Vec4, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Vec4_distance, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec4, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec4_distance2 arginfo_class_GL_Math_Vec4_distance

#define arginfo_class_GL_Math_Vec4_dot arginfo_class_GL_Math_Vec4_distance

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Vec4_mix, 0, 3, GL\\Math\\Vec4, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Vec4, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec4, 0)
	ZEND_ARG_TYPE_INFO(0, t, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec4_lerp arginfo_class_GL_Math_Vec4_mix

#define arginfo_class_GL_Math_Vec4_slerp arginfo_class_GL_Math_Vec4_mix

#define arginfo_class_GL_Math_Vec4_length arginfo_glfwGetTime

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Vec4_distanceTo, 0, 1, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Vec4_distance2To arginfo_class_GL_Math_Vec4_distanceTo

#define arginfo_class_GL_Math_Vec4_normalize arginfo_glFinish

#define arginfo_class_GL_Math_Vec4_abs arginfo_glFinish

#define arginfo_class_GL_Math_Vec4___toString arginfo_glfwGetVersionString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Math_Quat___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, w, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, x, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, y, IS_DOUBLE, 1, "null")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, z, IS_DOUBLE, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_copy, 0, 0, GL\\Math\\Quat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_fromMat4, 0, 1, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, GL\\Math\\Mat4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_fromVec4, 0, 1, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_inverted, 0, 1, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, quat, GL\\Math\\Quat, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Quat_normalized arginfo_class_GL_Math_Quat_inverted

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_mix, 0, 3, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Quat, 0)
	ZEND_ARG_TYPE_INFO(0, t, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Quat_lerp arginfo_class_GL_Math_Quat_mix

#define arginfo_class_GL_Math_Quat_slerp arginfo_class_GL_Math_Quat_mix

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Quat_dot, 0, 2, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Quat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_multiply, 0, 2, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Quat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_multiplyVec3, 0, 2, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, quat, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_multiplyMat4, 0, 2, GL\\Math\\Mat4, 0)
	ZEND_ARG_OBJ_INFO(0, quat, GL\\Math\\Quat, 0)
	ZEND_ARG_OBJ_INFO(0, mat, GL\\Math\\Mat4, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Quat_normalize arginfo_glFinish

#define arginfo_class_GL_Math_Quat_length arginfo_glfwGetTime

#define arginfo_class_GL_Math_Quat_eulerAngles arginfo_class_GL_Math_Vec3_copy

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Quat_rotate, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, axis, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Quat_inverse arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Quat_mat4, 0, 0, GL\\Math\\Mat4, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Quat___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Math_Mat4___construct arginfo_class_GL_Geometry_ObjFileParser_Material___construct

#define arginfo_class_GL_Math_Mat4_copy arginfo_class_GL_Math_Quat_mat4

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Mat4_fromArray, 0, 1, GL\\Math\\Mat4, 0)
	ZEND_ARG_TYPE_INFO(0, values, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Mat4_inverted, 0, 1, GL\\Math\\Mat4, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, GL\\Math\\Mat4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Mat4_multiplyQuat, 0, 2, GL\\Math\\Mat4, 0)
	ZEND_ARG_OBJ_INFO(0, left, GL\\Math\\Mat4, 0)
	ZEND_ARG_OBJ_INFO(0, right, GL\\Math\\Quat, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Math_Mat4_row, 0, 1, GL\\Math\\Vec4, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_setRow, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, row, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Mat4_col arginfo_class_GL_Math_Mat4_row

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_setCol, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, col, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_lookAt, 0, 3, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, eye, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, center, GL\\Math\\Vec3, 0)
	ZEND_ARG_OBJ_INFO(0, up, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_perspective, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, fov, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, aspect, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, near, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, far, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_ortho, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, left, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, right, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, bottom, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, top, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, near, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, far, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Mat4_transpose arginfo_glFinish

#define arginfo_class_GL_Math_Mat4_inverse arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_scale, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, scale, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Math_Mat4_translate, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, translation, GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Math_Mat4_rotate arginfo_class_GL_Math_Quat_rotate

#define arginfo_class_GL_Math_Mat4_determinant arginfo_glfwGetTime

#define arginfo_class_GL_Math_Mat4___toString arginfo_glfwGetVersionString

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_Buffer_BufferInterface___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, initalData, IS_ARRAY, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Buffer_BufferInterface_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_BufferInterface_size arginfo_glGetError

#define arginfo_class_GL_Buffer_BufferInterface_capacity arginfo_glGetError

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_BufferInterface_reserve, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, size, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Buffer_FloatBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_FloatBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_FloatBuffer_push arginfo_glMinSampleShading

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_pushArray, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, values, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_pushVec2, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Buffer\\GL\\Math\\Vec2, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_pushVec3, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Buffer\\GL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_pushVec4, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Buffer\\GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_pushMat4, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, matrix, GL\\Buffer\\GL\\Math\\Mat4, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_quantizeToUChar, 0, 0, GL\\Buffer\\\125ByteBuffer, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, autoNormalize, _IS_BOOL, 0, "true")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, lowerBound, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, upperBound, IS_DOUBLE, 0, "1.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_FloatBuffer_fill, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Buffer_FloatBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_FloatBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_FloatBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_FloatBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_FloatBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_HFloatBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_HFloatBuffer___toString arginfo_glfwGetVersionString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_HFloatBuffer_push, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Buffer_HFloatBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_HFloatBuffer_fill, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Buffer_HFloatBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_HFloatBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_HFloatBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_HFloatBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_HFloatBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_DoubleBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_DoubleBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_DoubleBuffer_push arginfo_glMinSampleShading

#define arginfo_class_GL_Buffer_DoubleBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

#define arginfo_class_GL_Buffer_DoubleBuffer_fill arginfo_class_GL_Buffer_FloatBuffer_fill

#define arginfo_class_GL_Buffer_DoubleBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_DoubleBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_DoubleBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_DoubleBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_DoubleBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_IntBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_IntBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_IntBuffer_push arginfo_class_GL_Buffer_HFloatBuffer_push

#define arginfo_class_GL_Buffer_IntBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

#define arginfo_class_GL_Buffer_IntBuffer_fill arginfo_class_GL_Buffer_HFloatBuffer_fill

#define arginfo_class_GL_Buffer_IntBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_IntBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_IntBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_IntBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_IntBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_UIntBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_UIntBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_UIntBuffer_push arginfo_class_GL_Buffer_HFloatBuffer_push

#define arginfo_class_GL_Buffer_UIntBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

#define arginfo_class_GL_Buffer_UIntBuffer_fill arginfo_class_GL_Buffer_HFloatBuffer_fill

#define arginfo_class_GL_Buffer_UIntBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_UIntBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_UIntBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_UIntBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_UIntBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_ShortBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_ShortBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_ShortBuffer_push arginfo_class_GL_Buffer_HFloatBuffer_push

#define arginfo_class_GL_Buffer_ShortBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

#define arginfo_class_GL_Buffer_ShortBuffer_fill arginfo_class_GL_Buffer_HFloatBuffer_fill

#define arginfo_class_GL_Buffer_ShortBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_ShortBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_ShortBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_ShortBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_ShortBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_UShortBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_UShortBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_UShortBuffer_push arginfo_class_GL_Buffer_HFloatBuffer_push

#define arginfo_class_GL_Buffer_UShortBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

#define arginfo_class_GL_Buffer_UShortBuffer_fill arginfo_class_GL_Buffer_HFloatBuffer_fill

#define arginfo_class_GL_Buffer_UShortBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_UShortBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_UShortBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_UShortBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_UShortBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_ByteBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_ByteBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_ByteBuffer_push arginfo_class_GL_Buffer_HFloatBuffer_push

#define arginfo_class_GL_Buffer_ByteBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

#define arginfo_class_GL_Buffer_ByteBuffer_fill arginfo_class_GL_Buffer_HFloatBuffer_fill

#define arginfo_class_GL_Buffer_ByteBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_ByteBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_ByteBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_ByteBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_ByteBuffer_dump arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_UByteBuffer___construct arginfo_class_GL_Buffer_BufferInterface___construct

#define arginfo_class_GL_Buffer_UByteBuffer___toString arginfo_glfwGetVersionString

#define arginfo_class_GL_Buffer_UByteBuffer_push arginfo_class_GL_Buffer_HFloatBuffer_push

#define arginfo_class_GL_Buffer_UByteBuffer_pushArray arginfo_class_GL_Buffer_FloatBuffer_pushArray

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_Buffer_UByteBuffer_pushString, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_Buffer_UByteBuffer_fill arginfo_class_GL_Buffer_HFloatBuffer_fill

#define arginfo_class_GL_Buffer_UByteBuffer_clear arginfo_glFinish

#define arginfo_class_GL_Buffer_UByteBuffer_size arginfo_glGetError

#define arginfo_class_GL_Buffer_UByteBuffer_capacity arginfo_glGetError

#define arginfo_class_GL_Buffer_UByteBuffer_reserve arginfo_class_GL_Buffer_BufferInterface_reserve

#define arginfo_class_GL_Buffer_UByteBuffer_dump arginfo_glfwGetVersionString

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_rgb, 0, 3, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_rgba, 0, 4, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_hsl, 0, 3, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, l, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_hsla, 0, 4, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, s, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, l, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_irgb, 0, 3, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_irgba, 0, 4, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_hex, 0, 1, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, hex, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_red, 0, 0, GL\\VectorGraphics\\VGColor, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGColor_green arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_blue arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_white arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_black arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_transparent arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_yellow arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_cyan arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_magenta arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_orange arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_pink arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_purple arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_brown arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_gray arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_darkGray arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_lightGray arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_random arginfo_class_GL_VectorGraphics_VGColor_red

#define arginfo_class_GL_VectorGraphics_VGColor_randomGray arginfo_class_GL_VectorGraphics_VGColor_red

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor___construct, 0, 0, 4)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGColor_getHSLA arginfo_class_GL_Math_Vec4_copy

#define arginfo_class_GL_VectorGraphics_VGColor_getHSL arginfo_class_GL_Math_Vec3_copy

#define arginfo_class_GL_VectorGraphics_VGColor_getVec4 arginfo_class_GL_Math_Vec4_copy

#define arginfo_class_GL_VectorGraphics_VGColor_getVec3 arginfo_class_GL_Math_Vec3_copy

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGColor_darken, 0, 1, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_TYPE_INFO(0, amount, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGColor_lighten arginfo_class_GL_VectorGraphics_VGColor_darken

#define arginfo_class_GL_VectorGraphics_VGColor_invert arginfo_class_GL_VectorGraphics_VGColor_red

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGImage_makePaint, 0, 4, GL\\VectorGraphics\\VGPaint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, angle, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, alpha, IS_DOUBLE, 0, "1.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGImage_makePaintCentered, 0, 4, GL\\VectorGraphics\\VGPaint, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, angle, IS_DOUBLE, 0, "0.0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, alpha, IS_DOUBLE, 0, "1.0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext___construct, 0, 0, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, flags, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_fillColori, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, g, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_strokeColori arginfo_class_GL_VectorGraphics_VGContext_fillColori

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_fillColorVec4, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, vec, GL\\Math\\Vec4, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_strokeColorVec4 arginfo_class_GL_VectorGraphics_VGContext_fillColorVec4

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_transformPoint, 0, 2, GL\\Math\\Vec2, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_transformVec2 arginfo_class_GL_Math_Vec2_normalized

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_imageFromTexture, 0, 1, GL\\VectorGraphics\\VGImage, 0)
	ZEND_ARG_OBJ_INFO(0, texture, GL\\Texture\\Texture2D, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, repeatMode, IS_LONG, 0, "GL\\VectorGraphics\\VGImage::REPEAT_NONE")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, filterMode, IS_LONG, 0, "GL\\VectorGraphics\\VGImage::FILTER_LINEAR")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_imageFromHandle, 0, 3, GL\\VectorGraphics\\VGImage, 0)
	ZEND_ARG_TYPE_INFO(0, handle, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, repeatMode, IS_LONG, 0, "GL\\VectorGraphics\\VGImage::REPEAT_NONE")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, filterMode, IS_LONG, 0, "GL\\VectorGraphics\\VGImage::FILTER_LINEAR")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_linearGradient, 0, 6, GL\\VectorGraphics\\VGPaint, 0)
	ZEND_ARG_TYPE_INFO(0, sx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ex, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ey, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, icol, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_OBJ_INFO(0, ocol, GL\\VectorGraphics\\VGColor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_boxGradient, 0, 8, GL\\VectorGraphics\\VGPaint, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, f, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, icol, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_OBJ_INFO(0, ocol, GL\\VectorGraphics\\VGColor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_radialGradient, 0, 6, GL\\VectorGraphics\\VGPaint, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, inr, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, outr, IS_DOUBLE, 0)
	ZEND_ARG_OBJ_INFO(0, icol, GL\\VectorGraphics\\VGColor, 0)
	ZEND_ARG_OBJ_INFO(0, ocol, GL\\VectorGraphics\\VGColor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_beginFrame, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, windowWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, windowHeight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, devicePixelRatio, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_cancelFrame arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_endFrame arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_globalCompositeOperation, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, op, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_globalCompositeBlendFunc arginfo_glBlendFunc

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_globalCompositeBlendFuncSeparate, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, srcRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, srcAlpha, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dstAlpha, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_save arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_restore arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_reset arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_shapeAntiAlias, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, enabled, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_strokeColor, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, color, GL\\VectorGraphics\\VGColor, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_strokePaint, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, paint, GL\\VectorGraphics\\VGPaint, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_fillColor arginfo_class_GL_VectorGraphics_VGContext_strokeColor

#define arginfo_class_GL_VectorGraphics_VGContext_fillPaint arginfo_class_GL_VectorGraphics_VGContext_strokePaint

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_miterLimit, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, limit, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_strokeWidth arginfo_glPointSize

#define arginfo_class_GL_VectorGraphics_VGContext_lineCap arginfo_glDisable

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_lineJoin, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, join, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_globalAlpha, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, alpha, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_resetTransform arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_transform, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, c, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, d, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, e, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, f, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_translate, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_rotate, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, angle, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_skewX arginfo_class_GL_VectorGraphics_VGContext_rotate

#define arginfo_class_GL_VectorGraphics_VGContext_skewY arginfo_class_GL_VectorGraphics_VGContext_rotate

#define arginfo_class_GL_VectorGraphics_VGContext_scale arginfo_class_GL_VectorGraphics_VGContext_translate

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_currentTransform, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, buffer, GL\\Buffer\\FloatBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_transformPointCurrent, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(1, dstx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(1, dsty, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, srcx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, srcy, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_imageSize, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, image, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, w, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(1, h, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_deleteImage, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, image, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_scissor, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_intersectScissor arginfo_class_GL_VectorGraphics_VGContext_scissor

#define arginfo_class_GL_VectorGraphics_VGContext_resetScissor arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_beginPath arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_moveTo arginfo_class_GL_VectorGraphics_VGContext_translate

#define arginfo_class_GL_VectorGraphics_VGContext_lineTo arginfo_class_GL_VectorGraphics_VGContext_translate

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_bezierTo, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, c1x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, c1y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, c2x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, c2y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_quadTo, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_arcTo, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, radius, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_closePath arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_pathWinding, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, dir, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_arc, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dir, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_svgArcTo, 0, 9, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, xAxisRotation, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, largeArcFlag, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, sweepFlag, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_rect arginfo_class_GL_VectorGraphics_VGContext_scissor

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_roundedRect, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_roundedRectVarying, 0, 8, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, radTopLeft, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, radTopRight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, radBottomRight, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, radBottomLeft, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_ellipse, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, rx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ry, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_circle, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, cx, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, cy, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_fill arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_stroke arginfo_glFinish

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_createFont, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, filename, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_createFontAtIndex, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, filename, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, fontIndex, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_findFont, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_addFallbackFontId, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, baseFont, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, fallbackFont, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_addFallbackFont, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, baseFont, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, fallbackFont, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_resetFallbackFontsId, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, baseFont, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_resetFallbackFonts, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, baseFont, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_fontSize arginfo_glPointSize

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_fontBlur, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, blur, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textLetterSpacing, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, spacing, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textLineHeight, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, lineHeight, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textAlign, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, align, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_fontFaceId, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, font, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_fontFace, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, font, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_text, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textBox, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, breakRowWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textBounds, 0, 3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(1, bounds, GL\\Math\\Vec4, 1, "NULL")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textBoxBounds, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, breakRowWidth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, string, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(1, bounds, GL\\Math\\Vec4, 1, "NULL")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_GL_VectorGraphics_VGContext_textMetrics, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(1, ascender, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(1, descender, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(1, lineh, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_GL_VectorGraphics_VGContext_deleteInternal arginfo_glFinish

#define arginfo_class_GL_VectorGraphics_VGContext_debugDumpPathCache arginfo_glFinish


ZEND_FUNCTION(glCullFace);
ZEND_FUNCTION(glFrontFace);
ZEND_FUNCTION(glHint);
ZEND_FUNCTION(glLineWidth);
ZEND_FUNCTION(glPointSize);
ZEND_FUNCTION(glPolygonMode);
ZEND_FUNCTION(glScissor);
ZEND_FUNCTION(glTexParameterf);
ZEND_FUNCTION(glTexParameterfv);
ZEND_FUNCTION(glTexParameteri);
ZEND_FUNCTION(glTexParameteriv);
ZEND_FUNCTION(glTexImage2D);
ZEND_FUNCTION(glDrawBuffer);
ZEND_FUNCTION(glClear);
ZEND_FUNCTION(glClearColor);
ZEND_FUNCTION(glClearStencil);
ZEND_FUNCTION(glClearDepth);
ZEND_FUNCTION(glStencilMask);
ZEND_FUNCTION(glColorMask);
ZEND_FUNCTION(glDepthMask);
ZEND_FUNCTION(glDisable);
ZEND_FUNCTION(glEnable);
ZEND_FUNCTION(glFinish);
ZEND_FUNCTION(glFlush);
ZEND_FUNCTION(glBlendFunc);
ZEND_FUNCTION(glLogicOp);
ZEND_FUNCTION(glStencilFunc);
ZEND_FUNCTION(glStencilOp);
ZEND_FUNCTION(glDepthFunc);
ZEND_FUNCTION(glPixelStoref);
ZEND_FUNCTION(glPixelStorei);
ZEND_FUNCTION(glReadBuffer);
ZEND_FUNCTION(glReadPixels);
ZEND_FUNCTION(glGetBooleanv);
ZEND_FUNCTION(glGetDoublev);
ZEND_FUNCTION(glGetError);
ZEND_FUNCTION(glGetFloatv);
ZEND_FUNCTION(glGetIntegerv);
ZEND_FUNCTION(glGetString);
ZEND_FUNCTION(glGetTexImage);
ZEND_FUNCTION(glGetTexParameterfv);
ZEND_FUNCTION(glGetTexParameteriv);
ZEND_FUNCTION(glGetTexLevelParameterfv);
ZEND_FUNCTION(glGetTexLevelParameteriv);
ZEND_FUNCTION(glIsEnabled);
ZEND_FUNCTION(glDepthRange);
ZEND_FUNCTION(glViewport);
ZEND_FUNCTION(glDrawArrays);
ZEND_FUNCTION(glPolygonOffset);
ZEND_FUNCTION(glCopyTexImage1D);
ZEND_FUNCTION(glCopyTexImage2D);
ZEND_FUNCTION(glCopyTexSubImage1D);
ZEND_FUNCTION(glCopyTexSubImage2D);
ZEND_FUNCTION(glBindTexture);
ZEND_FUNCTION(glDeleteTextures);
ZEND_FUNCTION(glGenTextures);
ZEND_FUNCTION(glIsTexture);
ZEND_FUNCTION(glCopyTexSubImage3D);
ZEND_FUNCTION(glActiveTexture);
ZEND_FUNCTION(glSampleCoverage);
ZEND_FUNCTION(glBlendFuncSeparate);
ZEND_FUNCTION(glPointParameterf);
ZEND_FUNCTION(glPointParameterfv);
ZEND_FUNCTION(glPointParameteri);
ZEND_FUNCTION(glPointParameteriv);
ZEND_FUNCTION(glBlendColor);
ZEND_FUNCTION(glBlendEquation);
ZEND_FUNCTION(glGenQueries);
ZEND_FUNCTION(glDeleteQueries);
ZEND_FUNCTION(glIsQuery);
ZEND_FUNCTION(glBeginQuery);
ZEND_FUNCTION(glEndQuery);
ZEND_FUNCTION(glGetQueryiv);
ZEND_FUNCTION(glGetQueryObjectiv);
ZEND_FUNCTION(glGetQueryObjectuiv);
ZEND_FUNCTION(glBindBuffer);
ZEND_FUNCTION(glDeleteBuffers);
ZEND_FUNCTION(glGenBuffers);
ZEND_FUNCTION(glIsBuffer);
ZEND_FUNCTION(glUnmapBuffer);
ZEND_FUNCTION(glGetBufferParameteriv);
ZEND_FUNCTION(glBlendEquationSeparate);
ZEND_FUNCTION(glDrawBuffers);
ZEND_FUNCTION(glStencilOpSeparate);
ZEND_FUNCTION(glStencilFuncSeparate);
ZEND_FUNCTION(glStencilMaskSeparate);
ZEND_FUNCTION(glAttachShader);
ZEND_FUNCTION(glBindAttribLocation);
ZEND_FUNCTION(glCompileShader);
ZEND_FUNCTION(glCreateProgram);
ZEND_FUNCTION(glCreateShader);
ZEND_FUNCTION(glDeleteProgram);
ZEND_FUNCTION(glDeleteShader);
ZEND_FUNCTION(glDetachShader);
ZEND_FUNCTION(glDisableVertexAttribArray);
ZEND_FUNCTION(glEnableVertexAttribArray);
ZEND_FUNCTION(glGetAttachedShaders);
ZEND_FUNCTION(glGetAttribLocation);
ZEND_FUNCTION(glGetProgramiv);
ZEND_FUNCTION(glGetProgramInfoLog);
ZEND_FUNCTION(glGetShaderiv);
ZEND_FUNCTION(glGetShaderInfoLog);
ZEND_FUNCTION(glGetUniformLocation);
ZEND_FUNCTION(glGetUniformfv);
ZEND_FUNCTION(glGetUniformiv);
ZEND_FUNCTION(glGetVertexAttribdv);
ZEND_FUNCTION(glGetVertexAttribfv);
ZEND_FUNCTION(glGetVertexAttribiv);
ZEND_FUNCTION(glIsProgram);
ZEND_FUNCTION(glIsShader);
ZEND_FUNCTION(glLinkProgram);
ZEND_FUNCTION(glUseProgram);
ZEND_FUNCTION(glUniform1f);
ZEND_FUNCTION(glUniform2f);
ZEND_FUNCTION(glUniform3f);
ZEND_FUNCTION(glUniform4f);
ZEND_FUNCTION(glUniform1i);
ZEND_FUNCTION(glUniform2i);
ZEND_FUNCTION(glUniform3i);
ZEND_FUNCTION(glUniform4i);
ZEND_FUNCTION(glUniform1fv);
ZEND_FUNCTION(glUniform2fv);
ZEND_FUNCTION(glUniform3fv);
ZEND_FUNCTION(glUniform4fv);
ZEND_FUNCTION(glUniform1iv);
ZEND_FUNCTION(glUniform2iv);
ZEND_FUNCTION(glUniform3iv);
ZEND_FUNCTION(glUniform4iv);
ZEND_FUNCTION(glUniformMatrix2fv);
ZEND_FUNCTION(glUniformMatrix3fv);
ZEND_FUNCTION(glUniformMatrix4fv);
ZEND_FUNCTION(glValidateProgram);
ZEND_FUNCTION(glVertexAttrib1d);
ZEND_FUNCTION(glVertexAttrib1dv);
ZEND_FUNCTION(glVertexAttrib1f);
ZEND_FUNCTION(glVertexAttrib1fv);
ZEND_FUNCTION(glVertexAttrib1s);
ZEND_FUNCTION(glVertexAttrib1sv);
ZEND_FUNCTION(glVertexAttrib2d);
ZEND_FUNCTION(glVertexAttrib2dv);
ZEND_FUNCTION(glVertexAttrib2f);
ZEND_FUNCTION(glVertexAttrib2fv);
ZEND_FUNCTION(glVertexAttrib2s);
ZEND_FUNCTION(glVertexAttrib2sv);
ZEND_FUNCTION(glVertexAttrib3d);
ZEND_FUNCTION(glVertexAttrib3dv);
ZEND_FUNCTION(glVertexAttrib3f);
ZEND_FUNCTION(glVertexAttrib3fv);
ZEND_FUNCTION(glVertexAttrib3s);
ZEND_FUNCTION(glVertexAttrib3sv);
ZEND_FUNCTION(glVertexAttrib4Nbv);
ZEND_FUNCTION(glVertexAttrib4Niv);
ZEND_FUNCTION(glVertexAttrib4Nsv);
ZEND_FUNCTION(glVertexAttrib4Nub);
ZEND_FUNCTION(glVertexAttrib4Nubv);
ZEND_FUNCTION(glVertexAttrib4Nuiv);
ZEND_FUNCTION(glVertexAttrib4Nusv);
ZEND_FUNCTION(glVertexAttrib4bv);
ZEND_FUNCTION(glVertexAttrib4d);
ZEND_FUNCTION(glVertexAttrib4dv);
ZEND_FUNCTION(glVertexAttrib4f);
ZEND_FUNCTION(glVertexAttrib4fv);
ZEND_FUNCTION(glVertexAttrib4iv);
ZEND_FUNCTION(glVertexAttrib4s);
ZEND_FUNCTION(glVertexAttrib4sv);
ZEND_FUNCTION(glVertexAttrib4ubv);
ZEND_FUNCTION(glVertexAttrib4uiv);
ZEND_FUNCTION(glVertexAttrib4usv);
ZEND_FUNCTION(glVertexAttribPointer);
ZEND_FUNCTION(glUniformMatrix2x3fv);
ZEND_FUNCTION(glUniformMatrix3x2fv);
ZEND_FUNCTION(glUniformMatrix2x4fv);
ZEND_FUNCTION(glUniformMatrix4x2fv);
ZEND_FUNCTION(glUniformMatrix3x4fv);
ZEND_FUNCTION(glUniformMatrix4x3fv);
ZEND_FUNCTION(glColorMaski);
ZEND_FUNCTION(glGetBooleani_v);
ZEND_FUNCTION(glGetIntegeri_v);
ZEND_FUNCTION(glEnablei);
ZEND_FUNCTION(glDisablei);
ZEND_FUNCTION(glIsEnabledi);
ZEND_FUNCTION(glBeginTransformFeedback);
ZEND_FUNCTION(glEndTransformFeedback);
ZEND_FUNCTION(glBindBufferRange);
ZEND_FUNCTION(glBindBufferBase);
ZEND_FUNCTION(glClampColor);
ZEND_FUNCTION(glBeginConditionalRender);
ZEND_FUNCTION(glEndConditionalRender);
ZEND_FUNCTION(glGetVertexAttribIiv);
ZEND_FUNCTION(glGetVertexAttribIuiv);
ZEND_FUNCTION(glVertexAttribI1i);
ZEND_FUNCTION(glVertexAttribI2i);
ZEND_FUNCTION(glVertexAttribI3i);
ZEND_FUNCTION(glVertexAttribI4i);
ZEND_FUNCTION(glVertexAttribI1ui);
ZEND_FUNCTION(glVertexAttribI2ui);
ZEND_FUNCTION(glVertexAttribI3ui);
ZEND_FUNCTION(glVertexAttribI4ui);
ZEND_FUNCTION(glVertexAttribI1iv);
ZEND_FUNCTION(glVertexAttribI2iv);
ZEND_FUNCTION(glVertexAttribI3iv);
ZEND_FUNCTION(glVertexAttribI4iv);
ZEND_FUNCTION(glVertexAttribI1uiv);
ZEND_FUNCTION(glVertexAttribI2uiv);
ZEND_FUNCTION(glVertexAttribI3uiv);
ZEND_FUNCTION(glVertexAttribI4uiv);
ZEND_FUNCTION(glVertexAttribI4bv);
ZEND_FUNCTION(glVertexAttribI4sv);
ZEND_FUNCTION(glVertexAttribI4ubv);
ZEND_FUNCTION(glVertexAttribI4usv);
ZEND_FUNCTION(glGetUniformuiv);
ZEND_FUNCTION(glBindFragDataLocation);
ZEND_FUNCTION(glGetFragDataLocation);
ZEND_FUNCTION(glUniform1ui);
ZEND_FUNCTION(glUniform2ui);
ZEND_FUNCTION(glUniform3ui);
ZEND_FUNCTION(glUniform4ui);
ZEND_FUNCTION(glUniform1uiv);
ZEND_FUNCTION(glUniform2uiv);
ZEND_FUNCTION(glUniform3uiv);
ZEND_FUNCTION(glUniform4uiv);
ZEND_FUNCTION(glTexParameterIiv);
ZEND_FUNCTION(glTexParameterIuiv);
ZEND_FUNCTION(glGetTexParameterIiv);
ZEND_FUNCTION(glGetTexParameterIuiv);
ZEND_FUNCTION(glClearBufferiv);
ZEND_FUNCTION(glClearBufferuiv);
ZEND_FUNCTION(glClearBufferfv);
ZEND_FUNCTION(glClearBufferfi);
ZEND_FUNCTION(glGetStringi);
ZEND_FUNCTION(glIsRenderbuffer);
ZEND_FUNCTION(glBindRenderbuffer);
ZEND_FUNCTION(glDeleteRenderbuffers);
ZEND_FUNCTION(glGenRenderbuffers);
ZEND_FUNCTION(glRenderbufferStorage);
ZEND_FUNCTION(glGetRenderbufferParameteriv);
ZEND_FUNCTION(glIsFramebuffer);
ZEND_FUNCTION(glBindFramebuffer);
ZEND_FUNCTION(glDeleteFramebuffers);
ZEND_FUNCTION(glGenFramebuffers);
ZEND_FUNCTION(glCheckFramebufferStatus);
ZEND_FUNCTION(glFramebufferTexture1D);
ZEND_FUNCTION(glFramebufferTexture2D);
ZEND_FUNCTION(glFramebufferTexture3D);
ZEND_FUNCTION(glFramebufferRenderbuffer);
ZEND_FUNCTION(glGetFramebufferAttachmentParameteriv);
ZEND_FUNCTION(glGenerateMipmap);
ZEND_FUNCTION(glBlitFramebuffer);
ZEND_FUNCTION(glRenderbufferStorageMultisample);
ZEND_FUNCTION(glFramebufferTextureLayer);
ZEND_FUNCTION(glFlushMappedBufferRange);
ZEND_FUNCTION(glBindVertexArray);
ZEND_FUNCTION(glDeleteVertexArrays);
ZEND_FUNCTION(glGenVertexArrays);
ZEND_FUNCTION(glIsVertexArray);
ZEND_FUNCTION(glDrawArraysInstanced);
ZEND_FUNCTION(glTexBuffer);
ZEND_FUNCTION(glPrimitiveRestartIndex);
ZEND_FUNCTION(glCopyBufferSubData);
ZEND_FUNCTION(glGetUniformBlockIndex);
ZEND_FUNCTION(glGetActiveUniformBlockiv);
ZEND_FUNCTION(glUniformBlockBinding);
ZEND_FUNCTION(glProvokingVertex);
ZEND_FUNCTION(glIsSync);
ZEND_FUNCTION(glDeleteSync);
ZEND_FUNCTION(glClientWaitSync);
ZEND_FUNCTION(glWaitSync);
ZEND_FUNCTION(glGetInteger64v);
ZEND_FUNCTION(glGetInteger64i_v);
ZEND_FUNCTION(glGetBufferParameteri64v);
ZEND_FUNCTION(glFramebufferTexture);
ZEND_FUNCTION(glTexImage2DMultisample);
ZEND_FUNCTION(glTexImage3DMultisample);
ZEND_FUNCTION(glGetMultisamplefv);
ZEND_FUNCTION(glSampleMaski);
ZEND_FUNCTION(glBindFragDataLocationIndexed);
ZEND_FUNCTION(glGetFragDataIndex);
ZEND_FUNCTION(glGenSamplers);
ZEND_FUNCTION(glDeleteSamplers);
ZEND_FUNCTION(glIsSampler);
ZEND_FUNCTION(glBindSampler);
ZEND_FUNCTION(glSamplerParameteri);
ZEND_FUNCTION(glSamplerParameteriv);
ZEND_FUNCTION(glSamplerParameterf);
ZEND_FUNCTION(glSamplerParameterfv);
ZEND_FUNCTION(glSamplerParameterIiv);
ZEND_FUNCTION(glSamplerParameterIuiv);
ZEND_FUNCTION(glGetSamplerParameteriv);
ZEND_FUNCTION(glGetSamplerParameterIiv);
ZEND_FUNCTION(glGetSamplerParameterfv);
ZEND_FUNCTION(glGetSamplerParameterIuiv);
ZEND_FUNCTION(glQueryCounter);
ZEND_FUNCTION(glGetQueryObjecti64v);
ZEND_FUNCTION(glGetQueryObjectui64v);
ZEND_FUNCTION(glVertexAttribDivisor);
ZEND_FUNCTION(glVertexAttribP1ui);
ZEND_FUNCTION(glVertexAttribP1uiv);
ZEND_FUNCTION(glVertexAttribP2ui);
ZEND_FUNCTION(glVertexAttribP2uiv);
ZEND_FUNCTION(glVertexAttribP3ui);
ZEND_FUNCTION(glVertexAttribP3uiv);
ZEND_FUNCTION(glVertexAttribP4ui);
ZEND_FUNCTION(glVertexAttribP4uiv);
ZEND_FUNCTION(glVertexP2ui);
ZEND_FUNCTION(glVertexP2uiv);
ZEND_FUNCTION(glVertexP3ui);
ZEND_FUNCTION(glVertexP3uiv);
ZEND_FUNCTION(glVertexP4ui);
ZEND_FUNCTION(glVertexP4uiv);
ZEND_FUNCTION(glTexCoordP1ui);
ZEND_FUNCTION(glTexCoordP1uiv);
ZEND_FUNCTION(glTexCoordP2ui);
ZEND_FUNCTION(glTexCoordP2uiv);
ZEND_FUNCTION(glTexCoordP3ui);
ZEND_FUNCTION(glTexCoordP3uiv);
ZEND_FUNCTION(glTexCoordP4ui);
ZEND_FUNCTION(glTexCoordP4uiv);
ZEND_FUNCTION(glMultiTexCoordP1ui);
ZEND_FUNCTION(glMultiTexCoordP1uiv);
ZEND_FUNCTION(glMultiTexCoordP2ui);
ZEND_FUNCTION(glMultiTexCoordP2uiv);
ZEND_FUNCTION(glMultiTexCoordP3ui);
ZEND_FUNCTION(glMultiTexCoordP3uiv);
ZEND_FUNCTION(glMultiTexCoordP4ui);
ZEND_FUNCTION(glMultiTexCoordP4uiv);
ZEND_FUNCTION(glNormalP3ui);
ZEND_FUNCTION(glNormalP3uiv);
ZEND_FUNCTION(glColorP3ui);
ZEND_FUNCTION(glColorP3uiv);
ZEND_FUNCTION(glColorP4ui);
ZEND_FUNCTION(glColorP4uiv);
ZEND_FUNCTION(glSecondaryColorP3ui);
ZEND_FUNCTION(glSecondaryColorP3uiv);
ZEND_FUNCTION(glMinSampleShading);
ZEND_FUNCTION(glBlendEquationi);
ZEND_FUNCTION(glBlendEquationSeparatei);
ZEND_FUNCTION(glBlendFunci);
ZEND_FUNCTION(glBlendFuncSeparatei);
ZEND_FUNCTION(glUniform1d);
ZEND_FUNCTION(glUniform2d);
ZEND_FUNCTION(glUniform3d);
ZEND_FUNCTION(glUniform4d);
ZEND_FUNCTION(glUniform1dv);
ZEND_FUNCTION(glUniform2dv);
ZEND_FUNCTION(glUniform3dv);
ZEND_FUNCTION(glUniform4dv);
ZEND_FUNCTION(glUniformMatrix2dv);
ZEND_FUNCTION(glUniformMatrix3dv);
ZEND_FUNCTION(glUniformMatrix4dv);
ZEND_FUNCTION(glUniformMatrix2x3dv);
ZEND_FUNCTION(glUniformMatrix2x4dv);
ZEND_FUNCTION(glUniformMatrix3x2dv);
ZEND_FUNCTION(glUniformMatrix3x4dv);
ZEND_FUNCTION(glUniformMatrix4x2dv);
ZEND_FUNCTION(glUniformMatrix4x3dv);
ZEND_FUNCTION(glGetUniformdv);
ZEND_FUNCTION(glGetSubroutineUniformLocation);
ZEND_FUNCTION(glGetSubroutineIndex);
ZEND_FUNCTION(glGetActiveSubroutineUniformiv);
ZEND_FUNCTION(glUniformSubroutinesuiv);
ZEND_FUNCTION(glGetUniformSubroutineuiv);
ZEND_FUNCTION(glGetProgramStageiv);
ZEND_FUNCTION(glPatchParameteri);
ZEND_FUNCTION(glPatchParameterfv);
ZEND_FUNCTION(glBindTransformFeedback);
ZEND_FUNCTION(glDeleteTransformFeedbacks);
ZEND_FUNCTION(glGenTransformFeedbacks);
ZEND_FUNCTION(glIsTransformFeedback);
ZEND_FUNCTION(glPauseTransformFeedback);
ZEND_FUNCTION(glResumeTransformFeedback);
ZEND_FUNCTION(glDrawTransformFeedback);
ZEND_FUNCTION(glDrawTransformFeedbackStream);
ZEND_FUNCTION(glBeginQueryIndexed);
ZEND_FUNCTION(glEndQueryIndexed);
ZEND_FUNCTION(glGetQueryIndexediv);
ZEND_FUNCTION(glReleaseShaderCompiler);
ZEND_FUNCTION(glGetShaderPrecisionFormat);
ZEND_FUNCTION(glDepthRangef);
ZEND_FUNCTION(glClearDepthf);
ZEND_FUNCTION(glProgramParameteri);
ZEND_FUNCTION(glUseProgramStages);
ZEND_FUNCTION(glActiveShaderProgram);
ZEND_FUNCTION(glBindProgramPipeline);
ZEND_FUNCTION(glDeleteProgramPipelines);
ZEND_FUNCTION(glGenProgramPipelines);
ZEND_FUNCTION(glIsProgramPipeline);
ZEND_FUNCTION(glGetProgramPipelineiv);
ZEND_FUNCTION(glProgramUniform1i);
ZEND_FUNCTION(glProgramUniform1iv);
ZEND_FUNCTION(glProgramUniform1f);
ZEND_FUNCTION(glProgramUniform1fv);
ZEND_FUNCTION(glProgramUniform1d);
ZEND_FUNCTION(glProgramUniform1dv);
ZEND_FUNCTION(glProgramUniform1ui);
ZEND_FUNCTION(glProgramUniform1uiv);
ZEND_FUNCTION(glProgramUniform2i);
ZEND_FUNCTION(glProgramUniform2iv);
ZEND_FUNCTION(glProgramUniform2f);
ZEND_FUNCTION(glProgramUniform2fv);
ZEND_FUNCTION(glProgramUniform2d);
ZEND_FUNCTION(glProgramUniform2dv);
ZEND_FUNCTION(glProgramUniform2ui);
ZEND_FUNCTION(glProgramUniform2uiv);
ZEND_FUNCTION(glProgramUniform3i);
ZEND_FUNCTION(glProgramUniform3iv);
ZEND_FUNCTION(glProgramUniform3f);
ZEND_FUNCTION(glProgramUniform3fv);
ZEND_FUNCTION(glProgramUniform3d);
ZEND_FUNCTION(glProgramUniform3dv);
ZEND_FUNCTION(glProgramUniform3ui);
ZEND_FUNCTION(glProgramUniform3uiv);
ZEND_FUNCTION(glProgramUniform4i);
ZEND_FUNCTION(glProgramUniform4iv);
ZEND_FUNCTION(glProgramUniform4f);
ZEND_FUNCTION(glProgramUniform4fv);
ZEND_FUNCTION(glProgramUniform4d);
ZEND_FUNCTION(glProgramUniform4dv);
ZEND_FUNCTION(glProgramUniform4ui);
ZEND_FUNCTION(glProgramUniform4uiv);
ZEND_FUNCTION(glProgramUniformMatrix2fv);
ZEND_FUNCTION(glProgramUniformMatrix3fv);
ZEND_FUNCTION(glProgramUniformMatrix4fv);
ZEND_FUNCTION(glProgramUniformMatrix2dv);
ZEND_FUNCTION(glProgramUniformMatrix3dv);
ZEND_FUNCTION(glProgramUniformMatrix4dv);
ZEND_FUNCTION(glProgramUniformMatrix2x3fv);
ZEND_FUNCTION(glProgramUniformMatrix3x2fv);
ZEND_FUNCTION(glProgramUniformMatrix2x4fv);
ZEND_FUNCTION(glProgramUniformMatrix4x2fv);
ZEND_FUNCTION(glProgramUniformMatrix3x4fv);
ZEND_FUNCTION(glProgramUniformMatrix4x3fv);
ZEND_FUNCTION(glProgramUniformMatrix2x3dv);
ZEND_FUNCTION(glProgramUniformMatrix3x2dv);
ZEND_FUNCTION(glProgramUniformMatrix2x4dv);
ZEND_FUNCTION(glProgramUniformMatrix4x2dv);
ZEND_FUNCTION(glProgramUniformMatrix3x4dv);
ZEND_FUNCTION(glProgramUniformMatrix4x3dv);
ZEND_FUNCTION(glValidateProgramPipeline);
ZEND_FUNCTION(glVertexAttribL1d);
ZEND_FUNCTION(glVertexAttribL2d);
ZEND_FUNCTION(glVertexAttribL3d);
ZEND_FUNCTION(glVertexAttribL4d);
ZEND_FUNCTION(glVertexAttribL1dv);
ZEND_FUNCTION(glVertexAttribL2dv);
ZEND_FUNCTION(glVertexAttribL3dv);
ZEND_FUNCTION(glVertexAttribL4dv);
ZEND_FUNCTION(glGetVertexAttribLdv);
ZEND_FUNCTION(glViewportArrayv);
ZEND_FUNCTION(glViewportIndexedf);
ZEND_FUNCTION(glViewportIndexedfv);
ZEND_FUNCTION(glScissorArrayv);
ZEND_FUNCTION(glScissorIndexed);
ZEND_FUNCTION(glScissorIndexedv);
ZEND_FUNCTION(glDepthRangeArrayv);
ZEND_FUNCTION(glDepthRangeIndexed);
ZEND_FUNCTION(glGetFloati_v);
ZEND_FUNCTION(glGetDoublei_v);
ZEND_FUNCTION(glfwInit);
ZEND_FUNCTION(glfwTerminate);
ZEND_FUNCTION(glfwInitHint);
ZEND_FUNCTION(glfwGetVersion);
ZEND_FUNCTION(glfwGetVersionString);
ZEND_FUNCTION(glfwGetPrimaryMonitor);
ZEND_FUNCTION(glfwGetMonitorPos);
ZEND_FUNCTION(glfwGetMonitorWorkarea);
ZEND_FUNCTION(glfwGetMonitorPhysicalSize);
ZEND_FUNCTION(glfwGetMonitorContentScale);
ZEND_FUNCTION(glfwGetMonitorName);
ZEND_FUNCTION(glfwGetVideoModes);
ZEND_FUNCTION(glfwGetVideoMode);
ZEND_FUNCTION(glfwSetGamma);
ZEND_FUNCTION(glfwDefaultWindowHints);
ZEND_FUNCTION(glfwWindowHint);
ZEND_FUNCTION(glfwWindowHintString);
ZEND_FUNCTION(glfwCreateWindow);
ZEND_FUNCTION(glfwDestroyWindow);
ZEND_FUNCTION(glfwWindowShouldClose);
ZEND_FUNCTION(glfwSetWindowShouldClose);
ZEND_FUNCTION(glfwSetWindowTitle);
ZEND_FUNCTION(glfwGetWindowPos);
ZEND_FUNCTION(glfwSetWindowPos);
ZEND_FUNCTION(glfwGetWindowSize);
ZEND_FUNCTION(glfwSetWindowSizeLimits);
ZEND_FUNCTION(glfwSetWindowAspectRatio);
ZEND_FUNCTION(glfwSetWindowSize);
ZEND_FUNCTION(glfwGetFramebufferSize);
ZEND_FUNCTION(glfwGetWindowFrameSize);
ZEND_FUNCTION(glfwGetWindowContentScale);
ZEND_FUNCTION(glfwGetWindowOpacity);
ZEND_FUNCTION(glfwSetWindowOpacity);
ZEND_FUNCTION(glfwIconifyWindow);
ZEND_FUNCTION(glfwRestoreWindow);
ZEND_FUNCTION(glfwMaximizeWindow);
ZEND_FUNCTION(glfwShowWindow);
ZEND_FUNCTION(glfwHideWindow);
ZEND_FUNCTION(glfwFocusWindow);
ZEND_FUNCTION(glfwRequestWindowAttention);
ZEND_FUNCTION(glfwGetWindowMonitor);
ZEND_FUNCTION(glfwSetWindowMonitor);
ZEND_FUNCTION(glfwGetWindowAttrib);
ZEND_FUNCTION(glfwSetWindowAttrib);
ZEND_FUNCTION(glfwSetWindowPosCallback);
ZEND_FUNCTION(glfwSetWindowSizeCallback);
ZEND_FUNCTION(glfwSetWindowCloseCallback);
ZEND_FUNCTION(glfwSetWindowRefreshCallback);
ZEND_FUNCTION(glfwSetWindowFocusCallback);
ZEND_FUNCTION(glfwSetWindowIconifyCallback);
ZEND_FUNCTION(glfwSetWindowMaximizeCallback);
ZEND_FUNCTION(glfwSetFramebufferSizeCallback);
ZEND_FUNCTION(glfwSetWindowContentScaleCallback);
ZEND_FUNCTION(glfwPollEvents);
ZEND_FUNCTION(glfwWaitEvents);
ZEND_FUNCTION(glfwWaitEventsTimeout);
ZEND_FUNCTION(glfwPostEmptyEvent);
ZEND_FUNCTION(glfwGetInputMode);
ZEND_FUNCTION(glfwSetInputMode);
ZEND_FUNCTION(glfwRawMouseMotionSupported);
ZEND_FUNCTION(glfwGetKeyName);
ZEND_FUNCTION(glfwGetKeyScancode);
ZEND_FUNCTION(glfwGetKey);
ZEND_FUNCTION(glfwGetMouseButton);
ZEND_FUNCTION(glfwGetCursorPos);
ZEND_FUNCTION(glfwSetCursorPos);
ZEND_FUNCTION(glfwCreateStandardCursor);
ZEND_FUNCTION(glfwDestroyCursor);
ZEND_FUNCTION(glfwSetCursor);
ZEND_FUNCTION(glfwSetKeyCallback);
ZEND_FUNCTION(glfwSetCharCallback);
ZEND_FUNCTION(glfwSetCharModsCallback);
ZEND_FUNCTION(glfwSetMouseButtonCallback);
ZEND_FUNCTION(glfwSetCursorPosCallback);
ZEND_FUNCTION(glfwSetCursorEnterCallback);
ZEND_FUNCTION(glfwSetScrollCallback);
ZEND_FUNCTION(glfwSetDropCallback);
ZEND_FUNCTION(glfwJoystickPresent);
ZEND_FUNCTION(glfwGetJoystickAxes);
ZEND_FUNCTION(glfwGetJoystickButtons);
ZEND_FUNCTION(glfwGetJoystickName);
ZEND_FUNCTION(glfwGetJoystickGUID);
ZEND_FUNCTION(glfwJoystickIsGamepad);
ZEND_FUNCTION(glfwUpdateGamepadMappings);
ZEND_FUNCTION(glfwGetGamepadName);
ZEND_FUNCTION(glfwSetClipboardString);
ZEND_FUNCTION(glfwGetClipboardString);
ZEND_FUNCTION(glfwGetTime);
ZEND_FUNCTION(glfwSetTime);
ZEND_FUNCTION(glfwMakeContextCurrent);
ZEND_FUNCTION(glfwGetCurrentContext);
ZEND_FUNCTION(glfwSwapBuffers);
ZEND_FUNCTION(glfwSwapInterval);
ZEND_FUNCTION(glfwExtensionSupported);
ZEND_FUNCTION(glfwVulkanSupported);
ZEND_FUNCTION(glfwGetGamepadAxes);
ZEND_FUNCTION(glfwGetGamepadButtons);
ZEND_FUNCTION(glShaderSource);
ZEND_FUNCTION(glBufferData);
ZEND_FUNCTION(glUniformMatrix4f);
ZEND_FUNCTION(glUniformVec2f);
ZEND_FUNCTION(glUniformVec3f);
ZEND_FUNCTION(glUniformVec4f);
ZEND_METHOD(GL_Geometry_ObjFileParser, __construct);
ZEND_METHOD(GL_Geometry_ObjFileParser, getVertices);
ZEND_METHOD(GL_Geometry_ObjFileParser, getIndexedVertices);
ZEND_METHOD(GL_Geometry_ObjFileParser, getMeshes);
ZEND_METHOD(GL_Geometry_ObjFileParser, getIndexedMeshes);
ZEND_METHOD(GL_Geometry_ObjFileParser_Material, __construct);
ZEND_METHOD(GL_Geometry_ObjFileParser_Group, __construct);
ZEND_METHOD(GL_Geometry_ObjFileParser_Texture, __construct);
ZEND_METHOD(GL_Texture_Texture2D, fromDisk);
ZEND_METHOD(GL_Texture_Texture2D, fromBuffer);
ZEND_METHOD(GL_Texture_Texture2D, buffer);
ZEND_METHOD(GL_Texture_Texture2D, width);
ZEND_METHOD(GL_Texture_Texture2D, height);
ZEND_METHOD(GL_Texture_Texture2D, channels);
ZEND_METHOD(GL_Texture_Texture2D, writeJPG);
ZEND_METHOD(GL_Texture_Texture2D, writePNG);
ZEND_METHOD(GL_Texture_Texture2D, writeBMP);
ZEND_METHOD(GL_Texture_Texture2D, writeTGA);
ZEND_METHOD(GL_Noise, perlin);
ZEND_METHOD(GL_Noise, ridge);
ZEND_METHOD(GL_Noise, fbm);
ZEND_METHOD(GL_Noise, turbulence);
ZEND_METHOD(GL_Noise, perlinFill2D);
ZEND_METHOD(GL_Noise, ridgeFill2D);
ZEND_METHOD(GL_Noise, fbmFill2D);
ZEND_METHOD(GL_Noise, turbulenceFill2D);
ZEND_METHOD(GL_Noise, islandFill2D);
ZEND_METHOD(GL_Math_GLM, radians);
ZEND_METHOD(GL_Math_GLM, angle);
ZEND_METHOD(GL_Math_GLM, triangleNormal);
ZEND_METHOD(GL_Math_GLM, normalize);
ZEND_METHOD(GL_Math_Vec2, __construct);
ZEND_METHOD(GL_Math_Vec2, copy);
ZEND_METHOD(GL_Math_Vec2, normalized);
ZEND_METHOD(GL_Math_Vec2, distance);
ZEND_METHOD(GL_Math_Vec2, distance2);
ZEND_METHOD(GL_Math_Vec2, dot);
ZEND_METHOD(GL_Math_Vec2, mix);
ZEND_METHOD(GL_Math_Vec2, lerp);
ZEND_METHOD(GL_Math_Vec2, slerp);
ZEND_METHOD(GL_Math_Vec2, length);
ZEND_METHOD(GL_Math_Vec2, distanceTo);
ZEND_METHOD(GL_Math_Vec2, distance2To);
ZEND_METHOD(GL_Math_Vec2, normalize);
ZEND_METHOD(GL_Math_Vec2, abs);
ZEND_METHOD(GL_Math_Vec2, __toString);
ZEND_METHOD(GL_Math_Vec3, __construct);
ZEND_METHOD(GL_Math_Vec3, copy);
ZEND_METHOD(GL_Math_Vec3, normalized);
ZEND_METHOD(GL_Math_Vec3, distance);
ZEND_METHOD(GL_Math_Vec3, distance2);
ZEND_METHOD(GL_Math_Vec3, dot);
ZEND_METHOD(GL_Math_Vec3, mix);
ZEND_METHOD(GL_Math_Vec3, lerp);
ZEND_METHOD(GL_Math_Vec3, slerp);
ZEND_METHOD(GL_Math_Vec3, length);
ZEND_METHOD(GL_Math_Vec3, distanceTo);
ZEND_METHOD(GL_Math_Vec3, distance2To);
ZEND_METHOD(GL_Math_Vec3, normalize);
ZEND_METHOD(GL_Math_Vec3, abs);
ZEND_METHOD(GL_Math_Vec3, cross);
ZEND_METHOD(GL_Math_Vec3, multiplyQuat);
ZEND_METHOD(GL_Math_Vec3, __toString);
ZEND_METHOD(GL_Math_Vec4, __construct);
ZEND_METHOD(GL_Math_Vec4, copy);
ZEND_METHOD(GL_Math_Vec4, normalized);
ZEND_METHOD(GL_Math_Vec4, distance);
ZEND_METHOD(GL_Math_Vec4, distance2);
ZEND_METHOD(GL_Math_Vec4, dot);
ZEND_METHOD(GL_Math_Vec4, mix);
ZEND_METHOD(GL_Math_Vec4, lerp);
ZEND_METHOD(GL_Math_Vec4, slerp);
ZEND_METHOD(GL_Math_Vec4, length);
ZEND_METHOD(GL_Math_Vec4, distanceTo);
ZEND_METHOD(GL_Math_Vec4, distance2To);
ZEND_METHOD(GL_Math_Vec4, normalize);
ZEND_METHOD(GL_Math_Vec4, abs);
ZEND_METHOD(GL_Math_Vec4, __toString);
ZEND_METHOD(GL_Math_Quat, __construct);
ZEND_METHOD(GL_Math_Quat, copy);
ZEND_METHOD(GL_Math_Quat, fromMat4);
ZEND_METHOD(GL_Math_Quat, fromVec4);
ZEND_METHOD(GL_Math_Quat, inverted);
ZEND_METHOD(GL_Math_Quat, normalized);
ZEND_METHOD(GL_Math_Quat, mix);
ZEND_METHOD(GL_Math_Quat, lerp);
ZEND_METHOD(GL_Math_Quat, slerp);
ZEND_METHOD(GL_Math_Quat, dot);
ZEND_METHOD(GL_Math_Quat, multiply);
ZEND_METHOD(GL_Math_Quat, multiplyVec3);
ZEND_METHOD(GL_Math_Quat, multiplyMat4);
ZEND_METHOD(GL_Math_Quat, normalize);
ZEND_METHOD(GL_Math_Quat, length);
ZEND_METHOD(GL_Math_Quat, eulerAngles);
ZEND_METHOD(GL_Math_Quat, rotate);
ZEND_METHOD(GL_Math_Quat, inverse);
ZEND_METHOD(GL_Math_Quat, mat4);
ZEND_METHOD(GL_Math_Quat, __toString);
ZEND_METHOD(GL_Math_Mat4, __construct);
ZEND_METHOD(GL_Math_Mat4, copy);
ZEND_METHOD(GL_Math_Mat4, fromArray);
ZEND_METHOD(GL_Math_Mat4, inverted);
ZEND_METHOD(GL_Math_Mat4, multiplyQuat);
ZEND_METHOD(GL_Math_Mat4, row);
ZEND_METHOD(GL_Math_Mat4, setRow);
ZEND_METHOD(GL_Math_Mat4, col);
ZEND_METHOD(GL_Math_Mat4, setCol);
ZEND_METHOD(GL_Math_Mat4, lookAt);
ZEND_METHOD(GL_Math_Mat4, perspective);
ZEND_METHOD(GL_Math_Mat4, ortho);
ZEND_METHOD(GL_Math_Mat4, transpose);
ZEND_METHOD(GL_Math_Mat4, inverse);
ZEND_METHOD(GL_Math_Mat4, scale);
ZEND_METHOD(GL_Math_Mat4, translate);
ZEND_METHOD(GL_Math_Mat4, rotate);
ZEND_METHOD(GL_Math_Mat4, determinant);
ZEND_METHOD(GL_Math_Mat4, __toString);
ZEND_METHOD(GL_Buffer_FloatBuffer, __construct);
ZEND_METHOD(GL_Buffer_FloatBuffer, __toString);
ZEND_METHOD(GL_Buffer_FloatBuffer, push);
ZEND_METHOD(GL_Buffer_FloatBuffer, pushArray);
ZEND_METHOD(GL_Buffer_FloatBuffer, pushVec2);
ZEND_METHOD(GL_Buffer_FloatBuffer, pushVec3);
ZEND_METHOD(GL_Buffer_FloatBuffer, pushVec4);
ZEND_METHOD(GL_Buffer_FloatBuffer, pushMat4);
ZEND_METHOD(GL_Buffer_FloatBuffer, quantizeToUChar);
ZEND_METHOD(GL_Buffer_FloatBuffer, fill);
ZEND_METHOD(GL_Buffer_FloatBuffer, clear);
ZEND_METHOD(GL_Buffer_FloatBuffer, size);
ZEND_METHOD(GL_Buffer_FloatBuffer, capacity);
ZEND_METHOD(GL_Buffer_FloatBuffer, reserve);
ZEND_METHOD(GL_Buffer_FloatBuffer, dump);
ZEND_METHOD(GL_Buffer_HFloatBuffer, __construct);
ZEND_METHOD(GL_Buffer_HFloatBuffer, __toString);
ZEND_METHOD(GL_Buffer_HFloatBuffer, push);
ZEND_METHOD(GL_Buffer_HFloatBuffer, pushArray);
ZEND_METHOD(GL_Buffer_HFloatBuffer, fill);
ZEND_METHOD(GL_Buffer_HFloatBuffer, clear);
ZEND_METHOD(GL_Buffer_HFloatBuffer, size);
ZEND_METHOD(GL_Buffer_HFloatBuffer, capacity);
ZEND_METHOD(GL_Buffer_HFloatBuffer, reserve);
ZEND_METHOD(GL_Buffer_HFloatBuffer, dump);
ZEND_METHOD(GL_Buffer_DoubleBuffer, __construct);
ZEND_METHOD(GL_Buffer_DoubleBuffer, __toString);
ZEND_METHOD(GL_Buffer_DoubleBuffer, push);
ZEND_METHOD(GL_Buffer_DoubleBuffer, pushArray);
ZEND_METHOD(GL_Buffer_DoubleBuffer, fill);
ZEND_METHOD(GL_Buffer_DoubleBuffer, clear);
ZEND_METHOD(GL_Buffer_DoubleBuffer, size);
ZEND_METHOD(GL_Buffer_DoubleBuffer, capacity);
ZEND_METHOD(GL_Buffer_DoubleBuffer, reserve);
ZEND_METHOD(GL_Buffer_DoubleBuffer, dump);
ZEND_METHOD(GL_Buffer_IntBuffer, __construct);
ZEND_METHOD(GL_Buffer_IntBuffer, __toString);
ZEND_METHOD(GL_Buffer_IntBuffer, push);
ZEND_METHOD(GL_Buffer_IntBuffer, pushArray);
ZEND_METHOD(GL_Buffer_IntBuffer, fill);
ZEND_METHOD(GL_Buffer_IntBuffer, clear);
ZEND_METHOD(GL_Buffer_IntBuffer, size);
ZEND_METHOD(GL_Buffer_IntBuffer, capacity);
ZEND_METHOD(GL_Buffer_IntBuffer, reserve);
ZEND_METHOD(GL_Buffer_IntBuffer, dump);
ZEND_METHOD(GL_Buffer_UIntBuffer, __construct);
ZEND_METHOD(GL_Buffer_UIntBuffer, __toString);
ZEND_METHOD(GL_Buffer_UIntBuffer, push);
ZEND_METHOD(GL_Buffer_UIntBuffer, pushArray);
ZEND_METHOD(GL_Buffer_UIntBuffer, fill);
ZEND_METHOD(GL_Buffer_UIntBuffer, clear);
ZEND_METHOD(GL_Buffer_UIntBuffer, size);
ZEND_METHOD(GL_Buffer_UIntBuffer, capacity);
ZEND_METHOD(GL_Buffer_UIntBuffer, reserve);
ZEND_METHOD(GL_Buffer_UIntBuffer, dump);
ZEND_METHOD(GL_Buffer_ShortBuffer, __construct);
ZEND_METHOD(GL_Buffer_ShortBuffer, __toString);
ZEND_METHOD(GL_Buffer_ShortBuffer, push);
ZEND_METHOD(GL_Buffer_ShortBuffer, pushArray);
ZEND_METHOD(GL_Buffer_ShortBuffer, fill);
ZEND_METHOD(GL_Buffer_ShortBuffer, clear);
ZEND_METHOD(GL_Buffer_ShortBuffer, size);
ZEND_METHOD(GL_Buffer_ShortBuffer, capacity);
ZEND_METHOD(GL_Buffer_ShortBuffer, reserve);
ZEND_METHOD(GL_Buffer_ShortBuffer, dump);
ZEND_METHOD(GL_Buffer_UShortBuffer, __construct);
ZEND_METHOD(GL_Buffer_UShortBuffer, __toString);
ZEND_METHOD(GL_Buffer_UShortBuffer, push);
ZEND_METHOD(GL_Buffer_UShortBuffer, pushArray);
ZEND_METHOD(GL_Buffer_UShortBuffer, fill);
ZEND_METHOD(GL_Buffer_UShortBuffer, clear);
ZEND_METHOD(GL_Buffer_UShortBuffer, size);
ZEND_METHOD(GL_Buffer_UShortBuffer, capacity);
ZEND_METHOD(GL_Buffer_UShortBuffer, reserve);
ZEND_METHOD(GL_Buffer_UShortBuffer, dump);
ZEND_METHOD(GL_Buffer_ByteBuffer, __construct);
ZEND_METHOD(GL_Buffer_ByteBuffer, __toString);
ZEND_METHOD(GL_Buffer_ByteBuffer, push);
ZEND_METHOD(GL_Buffer_ByteBuffer, pushArray);
ZEND_METHOD(GL_Buffer_ByteBuffer, fill);
ZEND_METHOD(GL_Buffer_ByteBuffer, clear);
ZEND_METHOD(GL_Buffer_ByteBuffer, size);
ZEND_METHOD(GL_Buffer_ByteBuffer, capacity);
ZEND_METHOD(GL_Buffer_ByteBuffer, reserve);
ZEND_METHOD(GL_Buffer_ByteBuffer, dump);
ZEND_METHOD(GL_Buffer_UByteBuffer, __construct);
ZEND_METHOD(GL_Buffer_UByteBuffer, __toString);
ZEND_METHOD(GL_Buffer_UByteBuffer, push);
ZEND_METHOD(GL_Buffer_UByteBuffer, pushArray);
ZEND_METHOD(GL_Buffer_UByteBuffer, pushString);
ZEND_METHOD(GL_Buffer_UByteBuffer, fill);
ZEND_METHOD(GL_Buffer_UByteBuffer, clear);
ZEND_METHOD(GL_Buffer_UByteBuffer, size);
ZEND_METHOD(GL_Buffer_UByteBuffer, capacity);
ZEND_METHOD(GL_Buffer_UByteBuffer, reserve);
ZEND_METHOD(GL_Buffer_UByteBuffer, dump);
ZEND_METHOD(GL_VectorGraphics_VGColor, rgb);
ZEND_METHOD(GL_VectorGraphics_VGColor, rgba);
ZEND_METHOD(GL_VectorGraphics_VGColor, hsl);
ZEND_METHOD(GL_VectorGraphics_VGColor, hsla);
ZEND_METHOD(GL_VectorGraphics_VGColor, irgb);
ZEND_METHOD(GL_VectorGraphics_VGColor, irgba);
ZEND_METHOD(GL_VectorGraphics_VGColor, hex);
ZEND_METHOD(GL_VectorGraphics_VGColor, red);
ZEND_METHOD(GL_VectorGraphics_VGColor, green);
ZEND_METHOD(GL_VectorGraphics_VGColor, blue);
ZEND_METHOD(GL_VectorGraphics_VGColor, white);
ZEND_METHOD(GL_VectorGraphics_VGColor, black);
ZEND_METHOD(GL_VectorGraphics_VGColor, transparent);
ZEND_METHOD(GL_VectorGraphics_VGColor, yellow);
ZEND_METHOD(GL_VectorGraphics_VGColor, cyan);
ZEND_METHOD(GL_VectorGraphics_VGColor, magenta);
ZEND_METHOD(GL_VectorGraphics_VGColor, orange);
ZEND_METHOD(GL_VectorGraphics_VGColor, pink);
ZEND_METHOD(GL_VectorGraphics_VGColor, purple);
ZEND_METHOD(GL_VectorGraphics_VGColor, brown);
ZEND_METHOD(GL_VectorGraphics_VGColor, gray);
ZEND_METHOD(GL_VectorGraphics_VGColor, darkGray);
ZEND_METHOD(GL_VectorGraphics_VGColor, lightGray);
ZEND_METHOD(GL_VectorGraphics_VGColor, random);
ZEND_METHOD(GL_VectorGraphics_VGColor, randomGray);
ZEND_METHOD(GL_VectorGraphics_VGColor, __construct);
ZEND_METHOD(GL_VectorGraphics_VGColor, getHSLA);
ZEND_METHOD(GL_VectorGraphics_VGColor, getHSL);
ZEND_METHOD(GL_VectorGraphics_VGColor, getVec4);
ZEND_METHOD(GL_VectorGraphics_VGColor, getVec3);
ZEND_METHOD(GL_VectorGraphics_VGColor, darken);
ZEND_METHOD(GL_VectorGraphics_VGColor, lighten);
ZEND_METHOD(GL_VectorGraphics_VGColor, invert);
ZEND_METHOD(GL_VectorGraphics_VGImage, makePaint);
ZEND_METHOD(GL_VectorGraphics_VGImage, makePaintCentered);
ZEND_METHOD(GL_VectorGraphics_VGContext, __construct);
ZEND_METHOD(GL_VectorGraphics_VGContext, fillColori);
ZEND_METHOD(GL_VectorGraphics_VGContext, strokeColori);
ZEND_METHOD(GL_VectorGraphics_VGContext, fillColorVec4);
ZEND_METHOD(GL_VectorGraphics_VGContext, strokeColorVec4);
ZEND_METHOD(GL_VectorGraphics_VGContext, transformPoint);
ZEND_METHOD(GL_VectorGraphics_VGContext, transformVec2);
ZEND_METHOD(GL_VectorGraphics_VGContext, imageFromTexture);
ZEND_METHOD(GL_VectorGraphics_VGContext, imageFromHandle);
ZEND_METHOD(GL_VectorGraphics_VGContext, linearGradient);
ZEND_METHOD(GL_VectorGraphics_VGContext, boxGradient);
ZEND_METHOD(GL_VectorGraphics_VGContext, radialGradient);
ZEND_METHOD(GL_VectorGraphics_VGContext, beginFrame);
ZEND_METHOD(GL_VectorGraphics_VGContext, cancelFrame);
ZEND_METHOD(GL_VectorGraphics_VGContext, endFrame);
ZEND_METHOD(GL_VectorGraphics_VGContext, globalCompositeOperation);
ZEND_METHOD(GL_VectorGraphics_VGContext, globalCompositeBlendFunc);
ZEND_METHOD(GL_VectorGraphics_VGContext, globalCompositeBlendFuncSeparate);
ZEND_METHOD(GL_VectorGraphics_VGContext, save);
ZEND_METHOD(GL_VectorGraphics_VGContext, restore);
ZEND_METHOD(GL_VectorGraphics_VGContext, reset);
ZEND_METHOD(GL_VectorGraphics_VGContext, shapeAntiAlias);
ZEND_METHOD(GL_VectorGraphics_VGContext, strokeColor);
ZEND_METHOD(GL_VectorGraphics_VGContext, strokePaint);
ZEND_METHOD(GL_VectorGraphics_VGContext, fillColor);
ZEND_METHOD(GL_VectorGraphics_VGContext, fillPaint);
ZEND_METHOD(GL_VectorGraphics_VGContext, miterLimit);
ZEND_METHOD(GL_VectorGraphics_VGContext, strokeWidth);
ZEND_METHOD(GL_VectorGraphics_VGContext, lineCap);
ZEND_METHOD(GL_VectorGraphics_VGContext, lineJoin);
ZEND_METHOD(GL_VectorGraphics_VGContext, globalAlpha);
ZEND_METHOD(GL_VectorGraphics_VGContext, resetTransform);
ZEND_METHOD(GL_VectorGraphics_VGContext, transform);
ZEND_METHOD(GL_VectorGraphics_VGContext, translate);
ZEND_METHOD(GL_VectorGraphics_VGContext, rotate);
ZEND_METHOD(GL_VectorGraphics_VGContext, skewX);
ZEND_METHOD(GL_VectorGraphics_VGContext, skewY);
ZEND_METHOD(GL_VectorGraphics_VGContext, scale);
ZEND_METHOD(GL_VectorGraphics_VGContext, currentTransform);
ZEND_METHOD(GL_VectorGraphics_VGContext, transformPointCurrent);
ZEND_METHOD(GL_VectorGraphics_VGContext, imageSize);
ZEND_METHOD(GL_VectorGraphics_VGContext, deleteImage);
ZEND_METHOD(GL_VectorGraphics_VGContext, scissor);
ZEND_METHOD(GL_VectorGraphics_VGContext, intersectScissor);
ZEND_METHOD(GL_VectorGraphics_VGContext, resetScissor);
ZEND_METHOD(GL_VectorGraphics_VGContext, beginPath);
ZEND_METHOD(GL_VectorGraphics_VGContext, moveTo);
ZEND_METHOD(GL_VectorGraphics_VGContext, lineTo);
ZEND_METHOD(GL_VectorGraphics_VGContext, bezierTo);
ZEND_METHOD(GL_VectorGraphics_VGContext, quadTo);
ZEND_METHOD(GL_VectorGraphics_VGContext, arcTo);
ZEND_METHOD(GL_VectorGraphics_VGContext, closePath);
ZEND_METHOD(GL_VectorGraphics_VGContext, pathWinding);
ZEND_METHOD(GL_VectorGraphics_VGContext, arc);
ZEND_METHOD(GL_VectorGraphics_VGContext, svgArcTo);
ZEND_METHOD(GL_VectorGraphics_VGContext, rect);
ZEND_METHOD(GL_VectorGraphics_VGContext, roundedRect);
ZEND_METHOD(GL_VectorGraphics_VGContext, roundedRectVarying);
ZEND_METHOD(GL_VectorGraphics_VGContext, ellipse);
ZEND_METHOD(GL_VectorGraphics_VGContext, circle);
ZEND_METHOD(GL_VectorGraphics_VGContext, fill);
ZEND_METHOD(GL_VectorGraphics_VGContext, stroke);
ZEND_METHOD(GL_VectorGraphics_VGContext, createFont);
ZEND_METHOD(GL_VectorGraphics_VGContext, createFontAtIndex);
ZEND_METHOD(GL_VectorGraphics_VGContext, findFont);
ZEND_METHOD(GL_VectorGraphics_VGContext, addFallbackFontId);
ZEND_METHOD(GL_VectorGraphics_VGContext, addFallbackFont);
ZEND_METHOD(GL_VectorGraphics_VGContext, resetFallbackFontsId);
ZEND_METHOD(GL_VectorGraphics_VGContext, resetFallbackFonts);
ZEND_METHOD(GL_VectorGraphics_VGContext, fontSize);
ZEND_METHOD(GL_VectorGraphics_VGContext, fontBlur);
ZEND_METHOD(GL_VectorGraphics_VGContext, textLetterSpacing);
ZEND_METHOD(GL_VectorGraphics_VGContext, textLineHeight);
ZEND_METHOD(GL_VectorGraphics_VGContext, textAlign);
ZEND_METHOD(GL_VectorGraphics_VGContext, fontFaceId);
ZEND_METHOD(GL_VectorGraphics_VGContext, fontFace);
ZEND_METHOD(GL_VectorGraphics_VGContext, text);
ZEND_METHOD(GL_VectorGraphics_VGContext, textBox);
ZEND_METHOD(GL_VectorGraphics_VGContext, textBounds);
ZEND_METHOD(GL_VectorGraphics_VGContext, textBoxBounds);
ZEND_METHOD(GL_VectorGraphics_VGContext, textMetrics);
ZEND_METHOD(GL_VectorGraphics_VGContext, deleteInternal);
ZEND_METHOD(GL_VectorGraphics_VGContext, debugDumpPathCache);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(glCullFace, arginfo_glCullFace)
	ZEND_FE(glFrontFace, arginfo_glFrontFace)
	ZEND_FE(glHint, arginfo_glHint)
	ZEND_FE(glLineWidth, arginfo_glLineWidth)
	ZEND_FE(glPointSize, arginfo_glPointSize)
	ZEND_FE(glPolygonMode, arginfo_glPolygonMode)
	ZEND_FE(glScissor, arginfo_glScissor)
	ZEND_FE(glTexParameterf, arginfo_glTexParameterf)
	ZEND_FE(glTexParameterfv, arginfo_glTexParameterfv)
	ZEND_FE(glTexParameteri, arginfo_glTexParameteri)
	ZEND_FE(glTexParameteriv, arginfo_glTexParameteriv)
	ZEND_FE(glTexImage2D, arginfo_glTexImage2D)
	ZEND_FE(glDrawBuffer, arginfo_glDrawBuffer)
	ZEND_FE(glClear, arginfo_glClear)
	ZEND_FE(glClearColor, arginfo_glClearColor)
	ZEND_FE(glClearStencil, arginfo_glClearStencil)
	ZEND_FE(glClearDepth, arginfo_glClearDepth)
	ZEND_FE(glStencilMask, arginfo_glStencilMask)
	ZEND_FE(glColorMask, arginfo_glColorMask)
	ZEND_FE(glDepthMask, arginfo_glDepthMask)
	ZEND_FE(glDisable, arginfo_glDisable)
	ZEND_FE(glEnable, arginfo_glEnable)
	ZEND_FE(glFinish, arginfo_glFinish)
	ZEND_FE(glFlush, arginfo_glFlush)
	ZEND_FE(glBlendFunc, arginfo_glBlendFunc)
	ZEND_FE(glLogicOp, arginfo_glLogicOp)
	ZEND_FE(glStencilFunc, arginfo_glStencilFunc)
	ZEND_FE(glStencilOp, arginfo_glStencilOp)
	ZEND_FE(glDepthFunc, arginfo_glDepthFunc)
	ZEND_FE(glPixelStoref, arginfo_glPixelStoref)
	ZEND_FE(glPixelStorei, arginfo_glPixelStorei)
	ZEND_FE(glReadBuffer, arginfo_glReadBuffer)
	ZEND_FE(glReadPixels, arginfo_glReadPixels)
	ZEND_FE(glGetBooleanv, arginfo_glGetBooleanv)
	ZEND_FE(glGetDoublev, arginfo_glGetDoublev)
	ZEND_FE(glGetError, arginfo_glGetError)
	ZEND_FE(glGetFloatv, arginfo_glGetFloatv)
	ZEND_FE(glGetIntegerv, arginfo_glGetIntegerv)
	ZEND_FE(glGetString, arginfo_glGetString)
	ZEND_FE(glGetTexImage, arginfo_glGetTexImage)
	ZEND_FE(glGetTexParameterfv, arginfo_glGetTexParameterfv)
	ZEND_FE(glGetTexParameteriv, arginfo_glGetTexParameteriv)
	ZEND_FE(glGetTexLevelParameterfv, arginfo_glGetTexLevelParameterfv)
	ZEND_FE(glGetTexLevelParameteriv, arginfo_glGetTexLevelParameteriv)
	ZEND_FE(glIsEnabled, arginfo_glIsEnabled)
	ZEND_FE(glDepthRange, arginfo_glDepthRange)
	ZEND_FE(glViewport, arginfo_glViewport)
	ZEND_FE(glDrawArrays, arginfo_glDrawArrays)
	ZEND_FE(glPolygonOffset, arginfo_glPolygonOffset)
	ZEND_FE(glCopyTexImage1D, arginfo_glCopyTexImage1D)
	ZEND_FE(glCopyTexImage2D, arginfo_glCopyTexImage2D)
	ZEND_FE(glCopyTexSubImage1D, arginfo_glCopyTexSubImage1D)
	ZEND_FE(glCopyTexSubImage2D, arginfo_glCopyTexSubImage2D)
	ZEND_FE(glBindTexture, arginfo_glBindTexture)
	ZEND_FE(glDeleteTextures, arginfo_glDeleteTextures)
	ZEND_FE(glGenTextures, arginfo_glGenTextures)
	ZEND_FE(glIsTexture, arginfo_glIsTexture)
	ZEND_FE(glCopyTexSubImage3D, arginfo_glCopyTexSubImage3D)
	ZEND_FE(glActiveTexture, arginfo_glActiveTexture)
	ZEND_FE(glSampleCoverage, arginfo_glSampleCoverage)
	ZEND_FE(glBlendFuncSeparate, arginfo_glBlendFuncSeparate)
	ZEND_FE(glPointParameterf, arginfo_glPointParameterf)
	ZEND_FE(glPointParameterfv, arginfo_glPointParameterfv)
	ZEND_FE(glPointParameteri, arginfo_glPointParameteri)
	ZEND_FE(glPointParameteriv, arginfo_glPointParameteriv)
	ZEND_FE(glBlendColor, arginfo_glBlendColor)
	ZEND_FE(glBlendEquation, arginfo_glBlendEquation)
	ZEND_FE(glGenQueries, arginfo_glGenQueries)
	ZEND_FE(glDeleteQueries, arginfo_glDeleteQueries)
	ZEND_FE(glIsQuery, arginfo_glIsQuery)
	ZEND_FE(glBeginQuery, arginfo_glBeginQuery)
	ZEND_FE(glEndQuery, arginfo_glEndQuery)
	ZEND_FE(glGetQueryiv, arginfo_glGetQueryiv)
	ZEND_FE(glGetQueryObjectiv, arginfo_glGetQueryObjectiv)
	ZEND_FE(glGetQueryObjectuiv, arginfo_glGetQueryObjectuiv)
	ZEND_FE(glBindBuffer, arginfo_glBindBuffer)
	ZEND_FE(glDeleteBuffers, arginfo_glDeleteBuffers)
	ZEND_FE(glGenBuffers, arginfo_glGenBuffers)
	ZEND_FE(glIsBuffer, arginfo_glIsBuffer)
	ZEND_FE(glUnmapBuffer, arginfo_glUnmapBuffer)
	ZEND_FE(glGetBufferParameteriv, arginfo_glGetBufferParameteriv)
	ZEND_FE(glBlendEquationSeparate, arginfo_glBlendEquationSeparate)
	ZEND_FE(glDrawBuffers, arginfo_glDrawBuffers)
	ZEND_FE(glStencilOpSeparate, arginfo_glStencilOpSeparate)
	ZEND_FE(glStencilFuncSeparate, arginfo_glStencilFuncSeparate)
	ZEND_FE(glStencilMaskSeparate, arginfo_glStencilMaskSeparate)
	ZEND_FE(glAttachShader, arginfo_glAttachShader)
	ZEND_FE(glBindAttribLocation, arginfo_glBindAttribLocation)
	ZEND_FE(glCompileShader, arginfo_glCompileShader)
	ZEND_FE(glCreateProgram, arginfo_glCreateProgram)
	ZEND_FE(glCreateShader, arginfo_glCreateShader)
	ZEND_FE(glDeleteProgram, arginfo_glDeleteProgram)
	ZEND_FE(glDeleteShader, arginfo_glDeleteShader)
	ZEND_FE(glDetachShader, arginfo_glDetachShader)
	ZEND_FE(glDisableVertexAttribArray, arginfo_glDisableVertexAttribArray)
	ZEND_FE(glEnableVertexAttribArray, arginfo_glEnableVertexAttribArray)
	ZEND_FE(glGetAttachedShaders, arginfo_glGetAttachedShaders)
	ZEND_FE(glGetAttribLocation, arginfo_glGetAttribLocation)
	ZEND_FE(glGetProgramiv, arginfo_glGetProgramiv)
	ZEND_FE(glGetProgramInfoLog, arginfo_glGetProgramInfoLog)
	ZEND_FE(glGetShaderiv, arginfo_glGetShaderiv)
	ZEND_FE(glGetShaderInfoLog, arginfo_glGetShaderInfoLog)
	ZEND_FE(glGetUniformLocation, arginfo_glGetUniformLocation)
	ZEND_FE(glGetUniformfv, arginfo_glGetUniformfv)
	ZEND_FE(glGetUniformiv, arginfo_glGetUniformiv)
	ZEND_FE(glGetVertexAttribdv, arginfo_glGetVertexAttribdv)
	ZEND_FE(glGetVertexAttribfv, arginfo_glGetVertexAttribfv)
	ZEND_FE(glGetVertexAttribiv, arginfo_glGetVertexAttribiv)
	ZEND_FE(glIsProgram, arginfo_glIsProgram)
	ZEND_FE(glIsShader, arginfo_glIsShader)
	ZEND_FE(glLinkProgram, arginfo_glLinkProgram)
	ZEND_FE(glUseProgram, arginfo_glUseProgram)
	ZEND_FE(glUniform1f, arginfo_glUniform1f)
	ZEND_FE(glUniform2f, arginfo_glUniform2f)
	ZEND_FE(glUniform3f, arginfo_glUniform3f)
	ZEND_FE(glUniform4f, arginfo_glUniform4f)
	ZEND_FE(glUniform1i, arginfo_glUniform1i)
	ZEND_FE(glUniform2i, arginfo_glUniform2i)
	ZEND_FE(glUniform3i, arginfo_glUniform3i)
	ZEND_FE(glUniform4i, arginfo_glUniform4i)
	ZEND_FE(glUniform1fv, arginfo_glUniform1fv)
	ZEND_FE(glUniform2fv, arginfo_glUniform2fv)
	ZEND_FE(glUniform3fv, arginfo_glUniform3fv)
	ZEND_FE(glUniform4fv, arginfo_glUniform4fv)
	ZEND_FE(glUniform1iv, arginfo_glUniform1iv)
	ZEND_FE(glUniform2iv, arginfo_glUniform2iv)
	ZEND_FE(glUniform3iv, arginfo_glUniform3iv)
	ZEND_FE(glUniform4iv, arginfo_glUniform4iv)
	ZEND_FE(glUniformMatrix2fv, arginfo_glUniformMatrix2fv)
	ZEND_FE(glUniformMatrix3fv, arginfo_glUniformMatrix3fv)
	ZEND_FE(glUniformMatrix4fv, arginfo_glUniformMatrix4fv)
	ZEND_FE(glValidateProgram, arginfo_glValidateProgram)
	ZEND_FE(glVertexAttrib1d, arginfo_glVertexAttrib1d)
	ZEND_FE(glVertexAttrib1dv, arginfo_glVertexAttrib1dv)
	ZEND_FE(glVertexAttrib1f, arginfo_glVertexAttrib1f)
	ZEND_FE(glVertexAttrib1fv, arginfo_glVertexAttrib1fv)
	ZEND_FE(glVertexAttrib1s, arginfo_glVertexAttrib1s)
	ZEND_FE(glVertexAttrib1sv, arginfo_glVertexAttrib1sv)
	ZEND_FE(glVertexAttrib2d, arginfo_glVertexAttrib2d)
	ZEND_FE(glVertexAttrib2dv, arginfo_glVertexAttrib2dv)
	ZEND_FE(glVertexAttrib2f, arginfo_glVertexAttrib2f)
	ZEND_FE(glVertexAttrib2fv, arginfo_glVertexAttrib2fv)
	ZEND_FE(glVertexAttrib2s, arginfo_glVertexAttrib2s)
	ZEND_FE(glVertexAttrib2sv, arginfo_glVertexAttrib2sv)
	ZEND_FE(glVertexAttrib3d, arginfo_glVertexAttrib3d)
	ZEND_FE(glVertexAttrib3dv, arginfo_glVertexAttrib3dv)
	ZEND_FE(glVertexAttrib3f, arginfo_glVertexAttrib3f)
	ZEND_FE(glVertexAttrib3fv, arginfo_glVertexAttrib3fv)
	ZEND_FE(glVertexAttrib3s, arginfo_glVertexAttrib3s)
	ZEND_FE(glVertexAttrib3sv, arginfo_glVertexAttrib3sv)
	ZEND_FE(glVertexAttrib4Nbv, arginfo_glVertexAttrib4Nbv)
	ZEND_FE(glVertexAttrib4Niv, arginfo_glVertexAttrib4Niv)
	ZEND_FE(glVertexAttrib4Nsv, arginfo_glVertexAttrib4Nsv)
	ZEND_FE(glVertexAttrib4Nub, arginfo_glVertexAttrib4Nub)
	ZEND_FE(glVertexAttrib4Nubv, arginfo_glVertexAttrib4Nubv)
	ZEND_FE(glVertexAttrib4Nuiv, arginfo_glVertexAttrib4Nuiv)
	ZEND_FE(glVertexAttrib4Nusv, arginfo_glVertexAttrib4Nusv)
	ZEND_FE(glVertexAttrib4bv, arginfo_glVertexAttrib4bv)
	ZEND_FE(glVertexAttrib4d, arginfo_glVertexAttrib4d)
	ZEND_FE(glVertexAttrib4dv, arginfo_glVertexAttrib4dv)
	ZEND_FE(glVertexAttrib4f, arginfo_glVertexAttrib4f)
	ZEND_FE(glVertexAttrib4fv, arginfo_glVertexAttrib4fv)
	ZEND_FE(glVertexAttrib4iv, arginfo_glVertexAttrib4iv)
	ZEND_FE(glVertexAttrib4s, arginfo_glVertexAttrib4s)
	ZEND_FE(glVertexAttrib4sv, arginfo_glVertexAttrib4sv)
	ZEND_FE(glVertexAttrib4ubv, arginfo_glVertexAttrib4ubv)
	ZEND_FE(glVertexAttrib4uiv, arginfo_glVertexAttrib4uiv)
	ZEND_FE(glVertexAttrib4usv, arginfo_glVertexAttrib4usv)
	ZEND_FE(glVertexAttribPointer, arginfo_glVertexAttribPointer)
	ZEND_FE(glUniformMatrix2x3fv, arginfo_glUniformMatrix2x3fv)
	ZEND_FE(glUniformMatrix3x2fv, arginfo_glUniformMatrix3x2fv)
	ZEND_FE(glUniformMatrix2x4fv, arginfo_glUniformMatrix2x4fv)
	ZEND_FE(glUniformMatrix4x2fv, arginfo_glUniformMatrix4x2fv)
	ZEND_FE(glUniformMatrix3x4fv, arginfo_glUniformMatrix3x4fv)
	ZEND_FE(glUniformMatrix4x3fv, arginfo_glUniformMatrix4x3fv)
	ZEND_FE(glColorMaski, arginfo_glColorMaski)
	ZEND_FE(glGetBooleani_v, arginfo_glGetBooleani_v)
	ZEND_FE(glGetIntegeri_v, arginfo_glGetIntegeri_v)
	ZEND_FE(glEnablei, arginfo_glEnablei)
	ZEND_FE(glDisablei, arginfo_glDisablei)
	ZEND_FE(glIsEnabledi, arginfo_glIsEnabledi)
	ZEND_FE(glBeginTransformFeedback, arginfo_glBeginTransformFeedback)
	ZEND_FE(glEndTransformFeedback, arginfo_glEndTransformFeedback)
	ZEND_FE(glBindBufferRange, arginfo_glBindBufferRange)
	ZEND_FE(glBindBufferBase, arginfo_glBindBufferBase)
	ZEND_FE(glClampColor, arginfo_glClampColor)
	ZEND_FE(glBeginConditionalRender, arginfo_glBeginConditionalRender)
	ZEND_FE(glEndConditionalRender, arginfo_glEndConditionalRender)
	ZEND_FE(glGetVertexAttribIiv, arginfo_glGetVertexAttribIiv)
	ZEND_FE(glGetVertexAttribIuiv, arginfo_glGetVertexAttribIuiv)
	ZEND_FE(glVertexAttribI1i, arginfo_glVertexAttribI1i)
	ZEND_FE(glVertexAttribI2i, arginfo_glVertexAttribI2i)
	ZEND_FE(glVertexAttribI3i, arginfo_glVertexAttribI3i)
	ZEND_FE(glVertexAttribI4i, arginfo_glVertexAttribI4i)
	ZEND_FE(glVertexAttribI1ui, arginfo_glVertexAttribI1ui)
	ZEND_FE(glVertexAttribI2ui, arginfo_glVertexAttribI2ui)
	ZEND_FE(glVertexAttribI3ui, arginfo_glVertexAttribI3ui)
	ZEND_FE(glVertexAttribI4ui, arginfo_glVertexAttribI4ui)
	ZEND_FE(glVertexAttribI1iv, arginfo_glVertexAttribI1iv)
	ZEND_FE(glVertexAttribI2iv, arginfo_glVertexAttribI2iv)
	ZEND_FE(glVertexAttribI3iv, arginfo_glVertexAttribI3iv)
	ZEND_FE(glVertexAttribI4iv, arginfo_glVertexAttribI4iv)
	ZEND_FE(glVertexAttribI1uiv, arginfo_glVertexAttribI1uiv)
	ZEND_FE(glVertexAttribI2uiv, arginfo_glVertexAttribI2uiv)
	ZEND_FE(glVertexAttribI3uiv, arginfo_glVertexAttribI3uiv)
	ZEND_FE(glVertexAttribI4uiv, arginfo_glVertexAttribI4uiv)
	ZEND_FE(glVertexAttribI4bv, arginfo_glVertexAttribI4bv)
	ZEND_FE(glVertexAttribI4sv, arginfo_glVertexAttribI4sv)
	ZEND_FE(glVertexAttribI4ubv, arginfo_glVertexAttribI4ubv)
	ZEND_FE(glVertexAttribI4usv, arginfo_glVertexAttribI4usv)
	ZEND_FE(glGetUniformuiv, arginfo_glGetUniformuiv)
	ZEND_FE(glBindFragDataLocation, arginfo_glBindFragDataLocation)
	ZEND_FE(glGetFragDataLocation, arginfo_glGetFragDataLocation)
	ZEND_FE(glUniform1ui, arginfo_glUniform1ui)
	ZEND_FE(glUniform2ui, arginfo_glUniform2ui)
	ZEND_FE(glUniform3ui, arginfo_glUniform3ui)
	ZEND_FE(glUniform4ui, arginfo_glUniform4ui)
	ZEND_FE(glUniform1uiv, arginfo_glUniform1uiv)
	ZEND_FE(glUniform2uiv, arginfo_glUniform2uiv)
	ZEND_FE(glUniform3uiv, arginfo_glUniform3uiv)
	ZEND_FE(glUniform4uiv, arginfo_glUniform4uiv)
	ZEND_FE(glTexParameterIiv, arginfo_glTexParameterIiv)
	ZEND_FE(glTexParameterIuiv, arginfo_glTexParameterIuiv)
	ZEND_FE(glGetTexParameterIiv, arginfo_glGetTexParameterIiv)
	ZEND_FE(glGetTexParameterIuiv, arginfo_glGetTexParameterIuiv)
	ZEND_FE(glClearBufferiv, arginfo_glClearBufferiv)
	ZEND_FE(glClearBufferuiv, arginfo_glClearBufferuiv)
	ZEND_FE(glClearBufferfv, arginfo_glClearBufferfv)
	ZEND_FE(glClearBufferfi, arginfo_glClearBufferfi)
	ZEND_FE(glGetStringi, arginfo_glGetStringi)
	ZEND_FE(glIsRenderbuffer, arginfo_glIsRenderbuffer)
	ZEND_FE(glBindRenderbuffer, arginfo_glBindRenderbuffer)
	ZEND_FE(glDeleteRenderbuffers, arginfo_glDeleteRenderbuffers)
	ZEND_FE(glGenRenderbuffers, arginfo_glGenRenderbuffers)
	ZEND_FE(glRenderbufferStorage, arginfo_glRenderbufferStorage)
	ZEND_FE(glGetRenderbufferParameteriv, arginfo_glGetRenderbufferParameteriv)
	ZEND_FE(glIsFramebuffer, arginfo_glIsFramebuffer)
	ZEND_FE(glBindFramebuffer, arginfo_glBindFramebuffer)
	ZEND_FE(glDeleteFramebuffers, arginfo_glDeleteFramebuffers)
	ZEND_FE(glGenFramebuffers, arginfo_glGenFramebuffers)
	ZEND_FE(glCheckFramebufferStatus, arginfo_glCheckFramebufferStatus)
	ZEND_FE(glFramebufferTexture1D, arginfo_glFramebufferTexture1D)
	ZEND_FE(glFramebufferTexture2D, arginfo_glFramebufferTexture2D)
	ZEND_FE(glFramebufferTexture3D, arginfo_glFramebufferTexture3D)
	ZEND_FE(glFramebufferRenderbuffer, arginfo_glFramebufferRenderbuffer)
	ZEND_FE(glGetFramebufferAttachmentParameteriv, arginfo_glGetFramebufferAttachmentParameteriv)
	ZEND_FE(glGenerateMipmap, arginfo_glGenerateMipmap)
	ZEND_FE(glBlitFramebuffer, arginfo_glBlitFramebuffer)
	ZEND_FE(glRenderbufferStorageMultisample, arginfo_glRenderbufferStorageMultisample)
	ZEND_FE(glFramebufferTextureLayer, arginfo_glFramebufferTextureLayer)
	ZEND_FE(glFlushMappedBufferRange, arginfo_glFlushMappedBufferRange)
	ZEND_FE(glBindVertexArray, arginfo_glBindVertexArray)
	ZEND_FE(glDeleteVertexArrays, arginfo_glDeleteVertexArrays)
	ZEND_FE(glGenVertexArrays, arginfo_glGenVertexArrays)
	ZEND_FE(glIsVertexArray, arginfo_glIsVertexArray)
	ZEND_FE(glDrawArraysInstanced, arginfo_glDrawArraysInstanced)
	ZEND_FE(glTexBuffer, arginfo_glTexBuffer)
	ZEND_FE(glPrimitiveRestartIndex, arginfo_glPrimitiveRestartIndex)
	ZEND_FE(glCopyBufferSubData, arginfo_glCopyBufferSubData)
	ZEND_FE(glGetUniformBlockIndex, arginfo_glGetUniformBlockIndex)
	ZEND_FE(glGetActiveUniformBlockiv, arginfo_glGetActiveUniformBlockiv)
	ZEND_FE(glUniformBlockBinding, arginfo_glUniformBlockBinding)
	ZEND_FE(glProvokingVertex, arginfo_glProvokingVertex)
	ZEND_FE(glIsSync, arginfo_glIsSync)
	ZEND_FE(glDeleteSync, arginfo_glDeleteSync)
	ZEND_FE(glClientWaitSync, arginfo_glClientWaitSync)
	ZEND_FE(glWaitSync, arginfo_glWaitSync)
	ZEND_FE(glGetInteger64v, arginfo_glGetInteger64v)
	ZEND_FE(glGetInteger64i_v, arginfo_glGetInteger64i_v)
	ZEND_FE(glGetBufferParameteri64v, arginfo_glGetBufferParameteri64v)
	ZEND_FE(glFramebufferTexture, arginfo_glFramebufferTexture)
	ZEND_FE(glTexImage2DMultisample, arginfo_glTexImage2DMultisample)
	ZEND_FE(glTexImage3DMultisample, arginfo_glTexImage3DMultisample)
	ZEND_FE(glGetMultisamplefv, arginfo_glGetMultisamplefv)
	ZEND_FE(glSampleMaski, arginfo_glSampleMaski)
	ZEND_FE(glBindFragDataLocationIndexed, arginfo_glBindFragDataLocationIndexed)
	ZEND_FE(glGetFragDataIndex, arginfo_glGetFragDataIndex)
	ZEND_FE(glGenSamplers, arginfo_glGenSamplers)
	ZEND_FE(glDeleteSamplers, arginfo_glDeleteSamplers)
	ZEND_FE(glIsSampler, arginfo_glIsSampler)
	ZEND_FE(glBindSampler, arginfo_glBindSampler)
	ZEND_FE(glSamplerParameteri, arginfo_glSamplerParameteri)
	ZEND_FE(glSamplerParameteriv, arginfo_glSamplerParameteriv)
	ZEND_FE(glSamplerParameterf, arginfo_glSamplerParameterf)
	ZEND_FE(glSamplerParameterfv, arginfo_glSamplerParameterfv)
	ZEND_FE(glSamplerParameterIiv, arginfo_glSamplerParameterIiv)
	ZEND_FE(glSamplerParameterIuiv, arginfo_glSamplerParameterIuiv)
	ZEND_FE(glGetSamplerParameteriv, arginfo_glGetSamplerParameteriv)
	ZEND_FE(glGetSamplerParameterIiv, arginfo_glGetSamplerParameterIiv)
	ZEND_FE(glGetSamplerParameterfv, arginfo_glGetSamplerParameterfv)
	ZEND_FE(glGetSamplerParameterIuiv, arginfo_glGetSamplerParameterIuiv)
	ZEND_FE(glQueryCounter, arginfo_glQueryCounter)
	ZEND_FE(glGetQueryObjecti64v, arginfo_glGetQueryObjecti64v)
	ZEND_FE(glGetQueryObjectui64v, arginfo_glGetQueryObjectui64v)
	ZEND_FE(glVertexAttribDivisor, arginfo_glVertexAttribDivisor)
	ZEND_FE(glVertexAttribP1ui, arginfo_glVertexAttribP1ui)
	ZEND_FE(glVertexAttribP1uiv, arginfo_glVertexAttribP1uiv)
	ZEND_FE(glVertexAttribP2ui, arginfo_glVertexAttribP2ui)
	ZEND_FE(glVertexAttribP2uiv, arginfo_glVertexAttribP2uiv)
	ZEND_FE(glVertexAttribP3ui, arginfo_glVertexAttribP3ui)
	ZEND_FE(glVertexAttribP3uiv, arginfo_glVertexAttribP3uiv)
	ZEND_FE(glVertexAttribP4ui, arginfo_glVertexAttribP4ui)
	ZEND_FE(glVertexAttribP4uiv, arginfo_glVertexAttribP4uiv)
	ZEND_FE(glVertexP2ui, arginfo_glVertexP2ui)
	ZEND_FE(glVertexP2uiv, arginfo_glVertexP2uiv)
	ZEND_FE(glVertexP3ui, arginfo_glVertexP3ui)
	ZEND_FE(glVertexP3uiv, arginfo_glVertexP3uiv)
	ZEND_FE(glVertexP4ui, arginfo_glVertexP4ui)
	ZEND_FE(glVertexP4uiv, arginfo_glVertexP4uiv)
	ZEND_FE(glTexCoordP1ui, arginfo_glTexCoordP1ui)
	ZEND_FE(glTexCoordP1uiv, arginfo_glTexCoordP1uiv)
	ZEND_FE(glTexCoordP2ui, arginfo_glTexCoordP2ui)
	ZEND_FE(glTexCoordP2uiv, arginfo_glTexCoordP2uiv)
	ZEND_FE(glTexCoordP3ui, arginfo_glTexCoordP3ui)
	ZEND_FE(glTexCoordP3uiv, arginfo_glTexCoordP3uiv)
	ZEND_FE(glTexCoordP4ui, arginfo_glTexCoordP4ui)
	ZEND_FE(glTexCoordP4uiv, arginfo_glTexCoordP4uiv)
	ZEND_FE(glMultiTexCoordP1ui, arginfo_glMultiTexCoordP1ui)
	ZEND_FE(glMultiTexCoordP1uiv, arginfo_glMultiTexCoordP1uiv)
	ZEND_FE(glMultiTexCoordP2ui, arginfo_glMultiTexCoordP2ui)
	ZEND_FE(glMultiTexCoordP2uiv, arginfo_glMultiTexCoordP2uiv)
	ZEND_FE(glMultiTexCoordP3ui, arginfo_glMultiTexCoordP3ui)
	ZEND_FE(glMultiTexCoordP3uiv, arginfo_glMultiTexCoordP3uiv)
	ZEND_FE(glMultiTexCoordP4ui, arginfo_glMultiTexCoordP4ui)
	ZEND_FE(glMultiTexCoordP4uiv, arginfo_glMultiTexCoordP4uiv)
	ZEND_FE(glNormalP3ui, arginfo_glNormalP3ui)
	ZEND_FE(glNormalP3uiv, arginfo_glNormalP3uiv)
	ZEND_FE(glColorP3ui, arginfo_glColorP3ui)
	ZEND_FE(glColorP3uiv, arginfo_glColorP3uiv)
	ZEND_FE(glColorP4ui, arginfo_glColorP4ui)
	ZEND_FE(glColorP4uiv, arginfo_glColorP4uiv)
	ZEND_FE(glSecondaryColorP3ui, arginfo_glSecondaryColorP3ui)
	ZEND_FE(glSecondaryColorP3uiv, arginfo_glSecondaryColorP3uiv)
	ZEND_FE(glMinSampleShading, arginfo_glMinSampleShading)
	ZEND_FE(glBlendEquationi, arginfo_glBlendEquationi)
	ZEND_FE(glBlendEquationSeparatei, arginfo_glBlendEquationSeparatei)
	ZEND_FE(glBlendFunci, arginfo_glBlendFunci)
	ZEND_FE(glBlendFuncSeparatei, arginfo_glBlendFuncSeparatei)
	ZEND_FE(glUniform1d, arginfo_glUniform1d)
	ZEND_FE(glUniform2d, arginfo_glUniform2d)
	ZEND_FE(glUniform3d, arginfo_glUniform3d)
	ZEND_FE(glUniform4d, arginfo_glUniform4d)
	ZEND_FE(glUniform1dv, arginfo_glUniform1dv)
	ZEND_FE(glUniform2dv, arginfo_glUniform2dv)
	ZEND_FE(glUniform3dv, arginfo_glUniform3dv)
	ZEND_FE(glUniform4dv, arginfo_glUniform4dv)
	ZEND_FE(glUniformMatrix2dv, arginfo_glUniformMatrix2dv)
	ZEND_FE(glUniformMatrix3dv, arginfo_glUniformMatrix3dv)
	ZEND_FE(glUniformMatrix4dv, arginfo_glUniformMatrix4dv)
	ZEND_FE(glUniformMatrix2x3dv, arginfo_glUniformMatrix2x3dv)
	ZEND_FE(glUniformMatrix2x4dv, arginfo_glUniformMatrix2x4dv)
	ZEND_FE(glUniformMatrix3x2dv, arginfo_glUniformMatrix3x2dv)
	ZEND_FE(glUniformMatrix3x4dv, arginfo_glUniformMatrix3x4dv)
	ZEND_FE(glUniformMatrix4x2dv, arginfo_glUniformMatrix4x2dv)
	ZEND_FE(glUniformMatrix4x3dv, arginfo_glUniformMatrix4x3dv)
	ZEND_FE(glGetUniformdv, arginfo_glGetUniformdv)
	ZEND_FE(glGetSubroutineUniformLocation, arginfo_glGetSubroutineUniformLocation)
	ZEND_FE(glGetSubroutineIndex, arginfo_glGetSubroutineIndex)
	ZEND_FE(glGetActiveSubroutineUniformiv, arginfo_glGetActiveSubroutineUniformiv)
	ZEND_FE(glUniformSubroutinesuiv, arginfo_glUniformSubroutinesuiv)
	ZEND_FE(glGetUniformSubroutineuiv, arginfo_glGetUniformSubroutineuiv)
	ZEND_FE(glGetProgramStageiv, arginfo_glGetProgramStageiv)
	ZEND_FE(glPatchParameteri, arginfo_glPatchParameteri)
	ZEND_FE(glPatchParameterfv, arginfo_glPatchParameterfv)
	ZEND_FE(glBindTransformFeedback, arginfo_glBindTransformFeedback)
	ZEND_FE(glDeleteTransformFeedbacks, arginfo_glDeleteTransformFeedbacks)
	ZEND_FE(glGenTransformFeedbacks, arginfo_glGenTransformFeedbacks)
	ZEND_FE(glIsTransformFeedback, arginfo_glIsTransformFeedback)
	ZEND_FE(glPauseTransformFeedback, arginfo_glPauseTransformFeedback)
	ZEND_FE(glResumeTransformFeedback, arginfo_glResumeTransformFeedback)
	ZEND_FE(glDrawTransformFeedback, arginfo_glDrawTransformFeedback)
	ZEND_FE(glDrawTransformFeedbackStream, arginfo_glDrawTransformFeedbackStream)
	ZEND_FE(glBeginQueryIndexed, arginfo_glBeginQueryIndexed)
	ZEND_FE(glEndQueryIndexed, arginfo_glEndQueryIndexed)
	ZEND_FE(glGetQueryIndexediv, arginfo_glGetQueryIndexediv)
	ZEND_FE(glReleaseShaderCompiler, arginfo_glReleaseShaderCompiler)
	ZEND_FE(glGetShaderPrecisionFormat, arginfo_glGetShaderPrecisionFormat)
	ZEND_FE(glDepthRangef, arginfo_glDepthRangef)
	ZEND_FE(glClearDepthf, arginfo_glClearDepthf)
	ZEND_FE(glProgramParameteri, arginfo_glProgramParameteri)
	ZEND_FE(glUseProgramStages, arginfo_glUseProgramStages)
	ZEND_FE(glActiveShaderProgram, arginfo_glActiveShaderProgram)
	ZEND_FE(glBindProgramPipeline, arginfo_glBindProgramPipeline)
	ZEND_FE(glDeleteProgramPipelines, arginfo_glDeleteProgramPipelines)
	ZEND_FE(glGenProgramPipelines, arginfo_glGenProgramPipelines)
	ZEND_FE(glIsProgramPipeline, arginfo_glIsProgramPipeline)
	ZEND_FE(glGetProgramPipelineiv, arginfo_glGetProgramPipelineiv)
	ZEND_FE(glProgramUniform1i, arginfo_glProgramUniform1i)
	ZEND_FE(glProgramUniform1iv, arginfo_glProgramUniform1iv)
	ZEND_FE(glProgramUniform1f, arginfo_glProgramUniform1f)
	ZEND_FE(glProgramUniform1fv, arginfo_glProgramUniform1fv)
	ZEND_FE(glProgramUniform1d, arginfo_glProgramUniform1d)
	ZEND_FE(glProgramUniform1dv, arginfo_glProgramUniform1dv)
	ZEND_FE(glProgramUniform1ui, arginfo_glProgramUniform1ui)
	ZEND_FE(glProgramUniform1uiv, arginfo_glProgramUniform1uiv)
	ZEND_FE(glProgramUniform2i, arginfo_glProgramUniform2i)
	ZEND_FE(glProgramUniform2iv, arginfo_glProgramUniform2iv)
	ZEND_FE(glProgramUniform2f, arginfo_glProgramUniform2f)
	ZEND_FE(glProgramUniform2fv, arginfo_glProgramUniform2fv)
	ZEND_FE(glProgramUniform2d, arginfo_glProgramUniform2d)
	ZEND_FE(glProgramUniform2dv, arginfo_glProgramUniform2dv)
	ZEND_FE(glProgramUniform2ui, arginfo_glProgramUniform2ui)
	ZEND_FE(glProgramUniform2uiv, arginfo_glProgramUniform2uiv)
	ZEND_FE(glProgramUniform3i, arginfo_glProgramUniform3i)
	ZEND_FE(glProgramUniform3iv, arginfo_glProgramUniform3iv)
	ZEND_FE(glProgramUniform3f, arginfo_glProgramUniform3f)
	ZEND_FE(glProgramUniform3fv, arginfo_glProgramUniform3fv)
	ZEND_FE(glProgramUniform3d, arginfo_glProgramUniform3d)
	ZEND_FE(glProgramUniform3dv, arginfo_glProgramUniform3dv)
	ZEND_FE(glProgramUniform3ui, arginfo_glProgramUniform3ui)
	ZEND_FE(glProgramUniform3uiv, arginfo_glProgramUniform3uiv)
	ZEND_FE(glProgramUniform4i, arginfo_glProgramUniform4i)
	ZEND_FE(glProgramUniform4iv, arginfo_glProgramUniform4iv)
	ZEND_FE(glProgramUniform4f, arginfo_glProgramUniform4f)
	ZEND_FE(glProgramUniform4fv, arginfo_glProgramUniform4fv)
	ZEND_FE(glProgramUniform4d, arginfo_glProgramUniform4d)
	ZEND_FE(glProgramUniform4dv, arginfo_glProgramUniform4dv)
	ZEND_FE(glProgramUniform4ui, arginfo_glProgramUniform4ui)
	ZEND_FE(glProgramUniform4uiv, arginfo_glProgramUniform4uiv)
	ZEND_FE(glProgramUniformMatrix2fv, arginfo_glProgramUniformMatrix2fv)
	ZEND_FE(glProgramUniformMatrix3fv, arginfo_glProgramUniformMatrix3fv)
	ZEND_FE(glProgramUniformMatrix4fv, arginfo_glProgramUniformMatrix4fv)
	ZEND_FE(glProgramUniformMatrix2dv, arginfo_glProgramUniformMatrix2dv)
	ZEND_FE(glProgramUniformMatrix3dv, arginfo_glProgramUniformMatrix3dv)
	ZEND_FE(glProgramUniformMatrix4dv, arginfo_glProgramUniformMatrix4dv)
	ZEND_FE(glProgramUniformMatrix2x3fv, arginfo_glProgramUniformMatrix2x3fv)
	ZEND_FE(glProgramUniformMatrix3x2fv, arginfo_glProgramUniformMatrix3x2fv)
	ZEND_FE(glProgramUniformMatrix2x4fv, arginfo_glProgramUniformMatrix2x4fv)
	ZEND_FE(glProgramUniformMatrix4x2fv, arginfo_glProgramUniformMatrix4x2fv)
	ZEND_FE(glProgramUniformMatrix3x4fv, arginfo_glProgramUniformMatrix3x4fv)
	ZEND_FE(glProgramUniformMatrix4x3fv, arginfo_glProgramUniformMatrix4x3fv)
	ZEND_FE(glProgramUniformMatrix2x3dv, arginfo_glProgramUniformMatrix2x3dv)
	ZEND_FE(glProgramUniformMatrix3x2dv, arginfo_glProgramUniformMatrix3x2dv)
	ZEND_FE(glProgramUniformMatrix2x4dv, arginfo_glProgramUniformMatrix2x4dv)
	ZEND_FE(glProgramUniformMatrix4x2dv, arginfo_glProgramUniformMatrix4x2dv)
	ZEND_FE(glProgramUniformMatrix3x4dv, arginfo_glProgramUniformMatrix3x4dv)
	ZEND_FE(glProgramUniformMatrix4x3dv, arginfo_glProgramUniformMatrix4x3dv)
	ZEND_FE(glValidateProgramPipeline, arginfo_glValidateProgramPipeline)
	ZEND_FE(glVertexAttribL1d, arginfo_glVertexAttribL1d)
	ZEND_FE(glVertexAttribL2d, arginfo_glVertexAttribL2d)
	ZEND_FE(glVertexAttribL3d, arginfo_glVertexAttribL3d)
	ZEND_FE(glVertexAttribL4d, arginfo_glVertexAttribL4d)
	ZEND_FE(glVertexAttribL1dv, arginfo_glVertexAttribL1dv)
	ZEND_FE(glVertexAttribL2dv, arginfo_glVertexAttribL2dv)
	ZEND_FE(glVertexAttribL3dv, arginfo_glVertexAttribL3dv)
	ZEND_FE(glVertexAttribL4dv, arginfo_glVertexAttribL4dv)
	ZEND_FE(glGetVertexAttribLdv, arginfo_glGetVertexAttribLdv)
	ZEND_FE(glViewportArrayv, arginfo_glViewportArrayv)
	ZEND_FE(glViewportIndexedf, arginfo_glViewportIndexedf)
	ZEND_FE(glViewportIndexedfv, arginfo_glViewportIndexedfv)
	ZEND_FE(glScissorArrayv, arginfo_glScissorArrayv)
	ZEND_FE(glScissorIndexed, arginfo_glScissorIndexed)
	ZEND_FE(glScissorIndexedv, arginfo_glScissorIndexedv)
	ZEND_FE(glDepthRangeArrayv, arginfo_glDepthRangeArrayv)
	ZEND_FE(glDepthRangeIndexed, arginfo_glDepthRangeIndexed)
	ZEND_FE(glGetFloati_v, arginfo_glGetFloati_v)
	ZEND_FE(glGetDoublei_v, arginfo_glGetDoublei_v)
	ZEND_FE(glfwInit, arginfo_glfwInit)
	ZEND_FE(glfwTerminate, arginfo_glfwTerminate)
	ZEND_FE(glfwInitHint, arginfo_glfwInitHint)
	ZEND_FE(glfwGetVersion, arginfo_glfwGetVersion)
	ZEND_FE(glfwGetVersionString, arginfo_glfwGetVersionString)
	ZEND_FE(glfwGetPrimaryMonitor, arginfo_glfwGetPrimaryMonitor)
	ZEND_FE(glfwGetMonitorPos, arginfo_glfwGetMonitorPos)
	ZEND_FE(glfwGetMonitorWorkarea, arginfo_glfwGetMonitorWorkarea)
	ZEND_FE(glfwGetMonitorPhysicalSize, arginfo_glfwGetMonitorPhysicalSize)
	ZEND_FE(glfwGetMonitorContentScale, arginfo_glfwGetMonitorContentScale)
	ZEND_FE(glfwGetMonitorName, arginfo_glfwGetMonitorName)
	ZEND_FE(glfwGetVideoModes, arginfo_glfwGetVideoModes)
	ZEND_FE(glfwGetVideoMode, arginfo_glfwGetVideoMode)
	ZEND_FE(glfwSetGamma, arginfo_glfwSetGamma)
	ZEND_FE(glfwDefaultWindowHints, arginfo_glfwDefaultWindowHints)
	ZEND_FE(glfwWindowHint, arginfo_glfwWindowHint)
	ZEND_FE(glfwWindowHintString, arginfo_glfwWindowHintString)
	ZEND_FE(glfwCreateWindow, arginfo_glfwCreateWindow)
	ZEND_FE(glfwDestroyWindow, arginfo_glfwDestroyWindow)
	ZEND_FE(glfwWindowShouldClose, arginfo_glfwWindowShouldClose)
	ZEND_FE(glfwSetWindowShouldClose, arginfo_glfwSetWindowShouldClose)
	ZEND_FE(glfwSetWindowTitle, arginfo_glfwSetWindowTitle)
	ZEND_FE(glfwGetWindowPos, arginfo_glfwGetWindowPos)
	ZEND_FE(glfwSetWindowPos, arginfo_glfwSetWindowPos)
	ZEND_FE(glfwGetWindowSize, arginfo_glfwGetWindowSize)
	ZEND_FE(glfwSetWindowSizeLimits, arginfo_glfwSetWindowSizeLimits)
	ZEND_FE(glfwSetWindowAspectRatio, arginfo_glfwSetWindowAspectRatio)
	ZEND_FE(glfwSetWindowSize, arginfo_glfwSetWindowSize)
	ZEND_FE(glfwGetFramebufferSize, arginfo_glfwGetFramebufferSize)
	ZEND_FE(glfwGetWindowFrameSize, arginfo_glfwGetWindowFrameSize)
	ZEND_FE(glfwGetWindowContentScale, arginfo_glfwGetWindowContentScale)
	ZEND_FE(glfwGetWindowOpacity, arginfo_glfwGetWindowOpacity)
	ZEND_FE(glfwSetWindowOpacity, arginfo_glfwSetWindowOpacity)
	ZEND_FE(glfwIconifyWindow, arginfo_glfwIconifyWindow)
	ZEND_FE(glfwRestoreWindow, arginfo_glfwRestoreWindow)
	ZEND_FE(glfwMaximizeWindow, arginfo_glfwMaximizeWindow)
	ZEND_FE(glfwShowWindow, arginfo_glfwShowWindow)
	ZEND_FE(glfwHideWindow, arginfo_glfwHideWindow)
	ZEND_FE(glfwFocusWindow, arginfo_glfwFocusWindow)
	ZEND_FE(glfwRequestWindowAttention, arginfo_glfwRequestWindowAttention)
	ZEND_FE(glfwGetWindowMonitor, arginfo_glfwGetWindowMonitor)
	ZEND_FE(glfwSetWindowMonitor, arginfo_glfwSetWindowMonitor)
	ZEND_FE(glfwGetWindowAttrib, arginfo_glfwGetWindowAttrib)
	ZEND_FE(glfwSetWindowAttrib, arginfo_glfwSetWindowAttrib)
	ZEND_FE(glfwSetWindowPosCallback, arginfo_glfwSetWindowPosCallback)
	ZEND_FE(glfwSetWindowSizeCallback, arginfo_glfwSetWindowSizeCallback)
	ZEND_FE(glfwSetWindowCloseCallback, arginfo_glfwSetWindowCloseCallback)
	ZEND_FE(glfwSetWindowRefreshCallback, arginfo_glfwSetWindowRefreshCallback)
	ZEND_FE(glfwSetWindowFocusCallback, arginfo_glfwSetWindowFocusCallback)
	ZEND_FE(glfwSetWindowIconifyCallback, arginfo_glfwSetWindowIconifyCallback)
	ZEND_FE(glfwSetWindowMaximizeCallback, arginfo_glfwSetWindowMaximizeCallback)
	ZEND_FE(glfwSetFramebufferSizeCallback, arginfo_glfwSetFramebufferSizeCallback)
	ZEND_FE(glfwSetWindowContentScaleCallback, arginfo_glfwSetWindowContentScaleCallback)
	ZEND_FE(glfwPollEvents, arginfo_glfwPollEvents)
	ZEND_FE(glfwWaitEvents, arginfo_glfwWaitEvents)
	ZEND_FE(glfwWaitEventsTimeout, arginfo_glfwWaitEventsTimeout)
	ZEND_FE(glfwPostEmptyEvent, arginfo_glfwPostEmptyEvent)
	ZEND_FE(glfwGetInputMode, arginfo_glfwGetInputMode)
	ZEND_FE(glfwSetInputMode, arginfo_glfwSetInputMode)
	ZEND_FE(glfwRawMouseMotionSupported, arginfo_glfwRawMouseMotionSupported)
	ZEND_FE(glfwGetKeyName, arginfo_glfwGetKeyName)
	ZEND_FE(glfwGetKeyScancode, arginfo_glfwGetKeyScancode)
	ZEND_FE(glfwGetKey, arginfo_glfwGetKey)
	ZEND_FE(glfwGetMouseButton, arginfo_glfwGetMouseButton)
	ZEND_FE(glfwGetCursorPos, arginfo_glfwGetCursorPos)
	ZEND_FE(glfwSetCursorPos, arginfo_glfwSetCursorPos)
	ZEND_FE(glfwCreateStandardCursor, arginfo_glfwCreateStandardCursor)
	ZEND_FE(glfwDestroyCursor, arginfo_glfwDestroyCursor)
	ZEND_FE(glfwSetCursor, arginfo_glfwSetCursor)
	ZEND_FE(glfwSetKeyCallback, arginfo_glfwSetKeyCallback)
	ZEND_FE(glfwSetCharCallback, arginfo_glfwSetCharCallback)
	ZEND_FE(glfwSetCharModsCallback, arginfo_glfwSetCharModsCallback)
	ZEND_FE(glfwSetMouseButtonCallback, arginfo_glfwSetMouseButtonCallback)
	ZEND_FE(glfwSetCursorPosCallback, arginfo_glfwSetCursorPosCallback)
	ZEND_FE(glfwSetCursorEnterCallback, arginfo_glfwSetCursorEnterCallback)
	ZEND_FE(glfwSetScrollCallback, arginfo_glfwSetScrollCallback)
	ZEND_FE(glfwSetDropCallback, arginfo_glfwSetDropCallback)
	ZEND_FE(glfwJoystickPresent, arginfo_glfwJoystickPresent)
	ZEND_FE(glfwGetJoystickAxes, arginfo_glfwGetJoystickAxes)
	ZEND_FE(glfwGetJoystickButtons, arginfo_glfwGetJoystickButtons)
	ZEND_FE(glfwGetJoystickName, arginfo_glfwGetJoystickName)
	ZEND_FE(glfwGetJoystickGUID, arginfo_glfwGetJoystickGUID)
	ZEND_FE(glfwJoystickIsGamepad, arginfo_glfwJoystickIsGamepad)
	ZEND_FE(glfwUpdateGamepadMappings, arginfo_glfwUpdateGamepadMappings)
	ZEND_FE(glfwGetGamepadName, arginfo_glfwGetGamepadName)
	ZEND_FE(glfwSetClipboardString, arginfo_glfwSetClipboardString)
	ZEND_FE(glfwGetClipboardString, arginfo_glfwGetClipboardString)
	ZEND_FE(glfwGetTime, arginfo_glfwGetTime)
	ZEND_FE(glfwSetTime, arginfo_glfwSetTime)
	ZEND_FE(glfwMakeContextCurrent, arginfo_glfwMakeContextCurrent)
	ZEND_FE(glfwGetCurrentContext, arginfo_glfwGetCurrentContext)
	ZEND_FE(glfwSwapBuffers, arginfo_glfwSwapBuffers)
	ZEND_FE(glfwSwapInterval, arginfo_glfwSwapInterval)
	ZEND_FE(glfwExtensionSupported, arginfo_glfwExtensionSupported)
	ZEND_FE(glfwVulkanSupported, arginfo_glfwVulkanSupported)
	ZEND_FE(glfwGetGamepadAxes, arginfo_glfwGetGamepadAxes)
	ZEND_FE(glfwGetGamepadButtons, arginfo_glfwGetGamepadButtons)
	ZEND_FE(glShaderSource, arginfo_glShaderSource)
	ZEND_FE(glBufferData, arginfo_glBufferData)
	ZEND_FE(glUniformMatrix4f, arginfo_glUniformMatrix4f)
	ZEND_FE(glUniformVec2f, arginfo_glUniformVec2f)
	ZEND_FE(glUniformVec3f, arginfo_glUniformVec3f)
	ZEND_FE(glUniformVec4f, arginfo_glUniformVec4f)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Geometry_ObjFileParser_methods[] = {
	ZEND_ME(GL_Geometry_ObjFileParser, __construct, arginfo_class_GL_Geometry_ObjFileParser___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Geometry_ObjFileParser, getVertices, arginfo_class_GL_Geometry_ObjFileParser_getVertices, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Geometry_ObjFileParser, getIndexedVertices, arginfo_class_GL_Geometry_ObjFileParser_getIndexedVertices, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Geometry_ObjFileParser, getMeshes, arginfo_class_GL_Geometry_ObjFileParser_getMeshes, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Geometry_ObjFileParser, getIndexedMeshes, arginfo_class_GL_Geometry_ObjFileParser_getIndexedMeshes, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Geometry_ObjFileParser_Resource_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_GL_Geometry_ObjFileParser_Mesh_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_GL_Geometry_ObjFileParser_Material_methods[] = {
	ZEND_ME(GL_Geometry_ObjFileParser_Material, __construct, arginfo_class_GL_Geometry_ObjFileParser_Material___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Geometry_ObjFileParser_Group_methods[] = {
	ZEND_ME(GL_Geometry_ObjFileParser_Group, __construct, arginfo_class_GL_Geometry_ObjFileParser_Group___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Geometry_ObjFileParser_Texture_methods[] = {
	ZEND_ME(GL_Geometry_ObjFileParser_Texture, __construct, arginfo_class_GL_Geometry_ObjFileParser_Texture___construct, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Texture_Texture2D_methods[] = {
	ZEND_ME(GL_Texture_Texture2D, fromDisk, arginfo_class_GL_Texture_Texture2D_fromDisk, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Texture_Texture2D, fromBuffer, arginfo_class_GL_Texture_Texture2D_fromBuffer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Texture_Texture2D, buffer, arginfo_class_GL_Texture_Texture2D_buffer, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, width, arginfo_class_GL_Texture_Texture2D_width, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, height, arginfo_class_GL_Texture_Texture2D_height, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, channels, arginfo_class_GL_Texture_Texture2D_channels, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, writeJPG, arginfo_class_GL_Texture_Texture2D_writeJPG, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, writePNG, arginfo_class_GL_Texture_Texture2D_writePNG, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, writeBMP, arginfo_class_GL_Texture_Texture2D_writeBMP, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Texture_Texture2D, writeTGA, arginfo_class_GL_Texture_Texture2D_writeTGA, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Noise_methods[] = {
	ZEND_ME(GL_Noise, perlin, arginfo_class_GL_Noise_perlin, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, ridge, arginfo_class_GL_Noise_ridge, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, fbm, arginfo_class_GL_Noise_fbm, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, turbulence, arginfo_class_GL_Noise_turbulence, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, perlinFill2D, arginfo_class_GL_Noise_perlinFill2D, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, ridgeFill2D, arginfo_class_GL_Noise_ridgeFill2D, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, fbmFill2D, arginfo_class_GL_Noise_fbmFill2D, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, turbulenceFill2D, arginfo_class_GL_Noise_turbulenceFill2D, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Noise, islandFill2D, arginfo_class_GL_Noise_islandFill2D, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Math_GLM_methods[] = {
	ZEND_ME(GL_Math_GLM, radians, arginfo_class_GL_Math_GLM_radians, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_GLM, angle, arginfo_class_GL_Math_GLM_angle, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_GLM, triangleNormal, arginfo_class_GL_Math_GLM_triangleNormal, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_GLM, normalize, arginfo_class_GL_Math_GLM_normalize, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Math_Vec2_methods[] = {
	ZEND_ME(GL_Math_Vec2, __construct, arginfo_class_GL_Math_Vec2___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, copy, arginfo_class_GL_Math_Vec2_copy, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, normalized, arginfo_class_GL_Math_Vec2_normalized, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, distance, arginfo_class_GL_Math_Vec2_distance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, distance2, arginfo_class_GL_Math_Vec2_distance2, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, dot, arginfo_class_GL_Math_Vec2_dot, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, mix, arginfo_class_GL_Math_Vec2_mix, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, lerp, arginfo_class_GL_Math_Vec2_lerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, slerp, arginfo_class_GL_Math_Vec2_slerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec2, length, arginfo_class_GL_Math_Vec2_length, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, distanceTo, arginfo_class_GL_Math_Vec2_distanceTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, distance2To, arginfo_class_GL_Math_Vec2_distance2To, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, normalize, arginfo_class_GL_Math_Vec2_normalize, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, abs, arginfo_class_GL_Math_Vec2_abs, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec2, __toString, arginfo_class_GL_Math_Vec2___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Math_Vec3_methods[] = {
	ZEND_ME(GL_Math_Vec3, __construct, arginfo_class_GL_Math_Vec3___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, copy, arginfo_class_GL_Math_Vec3_copy, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, normalized, arginfo_class_GL_Math_Vec3_normalized, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, distance, arginfo_class_GL_Math_Vec3_distance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, distance2, arginfo_class_GL_Math_Vec3_distance2, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, dot, arginfo_class_GL_Math_Vec3_dot, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, mix, arginfo_class_GL_Math_Vec3_mix, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, lerp, arginfo_class_GL_Math_Vec3_lerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, slerp, arginfo_class_GL_Math_Vec3_slerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, length, arginfo_class_GL_Math_Vec3_length, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, distanceTo, arginfo_class_GL_Math_Vec3_distanceTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, distance2To, arginfo_class_GL_Math_Vec3_distance2To, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, normalize, arginfo_class_GL_Math_Vec3_normalize, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, abs, arginfo_class_GL_Math_Vec3_abs, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec3, cross, arginfo_class_GL_Math_Vec3_cross, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, multiplyQuat, arginfo_class_GL_Math_Vec3_multiplyQuat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec3, __toString, arginfo_class_GL_Math_Vec3___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Math_Vec4_methods[] = {
	ZEND_ME(GL_Math_Vec4, __construct, arginfo_class_GL_Math_Vec4___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, copy, arginfo_class_GL_Math_Vec4_copy, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, normalized, arginfo_class_GL_Math_Vec4_normalized, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, distance, arginfo_class_GL_Math_Vec4_distance, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, distance2, arginfo_class_GL_Math_Vec4_distance2, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, dot, arginfo_class_GL_Math_Vec4_dot, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, mix, arginfo_class_GL_Math_Vec4_mix, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, lerp, arginfo_class_GL_Math_Vec4_lerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, slerp, arginfo_class_GL_Math_Vec4_slerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Vec4, length, arginfo_class_GL_Math_Vec4_length, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, distanceTo, arginfo_class_GL_Math_Vec4_distanceTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, distance2To, arginfo_class_GL_Math_Vec4_distance2To, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, normalize, arginfo_class_GL_Math_Vec4_normalize, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, abs, arginfo_class_GL_Math_Vec4_abs, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Vec4, __toString, arginfo_class_GL_Math_Vec4___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Math_Quat_methods[] = {
	ZEND_ME(GL_Math_Quat, __construct, arginfo_class_GL_Math_Quat___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, copy, arginfo_class_GL_Math_Quat_copy, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, fromMat4, arginfo_class_GL_Math_Quat_fromMat4, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, fromVec4, arginfo_class_GL_Math_Quat_fromVec4, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, inverted, arginfo_class_GL_Math_Quat_inverted, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, normalized, arginfo_class_GL_Math_Quat_normalized, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, mix, arginfo_class_GL_Math_Quat_mix, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, lerp, arginfo_class_GL_Math_Quat_lerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, slerp, arginfo_class_GL_Math_Quat_slerp, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, dot, arginfo_class_GL_Math_Quat_dot, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, multiply, arginfo_class_GL_Math_Quat_multiply, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, multiplyVec3, arginfo_class_GL_Math_Quat_multiplyVec3, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, multiplyMat4, arginfo_class_GL_Math_Quat_multiplyMat4, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Quat, normalize, arginfo_class_GL_Math_Quat_normalize, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, length, arginfo_class_GL_Math_Quat_length, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, eulerAngles, arginfo_class_GL_Math_Quat_eulerAngles, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, rotate, arginfo_class_GL_Math_Quat_rotate, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, inverse, arginfo_class_GL_Math_Quat_inverse, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, mat4, arginfo_class_GL_Math_Quat_mat4, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Quat, __toString, arginfo_class_GL_Math_Quat___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Math_Mat4_methods[] = {
	ZEND_ME(GL_Math_Mat4, __construct, arginfo_class_GL_Math_Mat4___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, copy, arginfo_class_GL_Math_Mat4_copy, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, fromArray, arginfo_class_GL_Math_Mat4_fromArray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Mat4, inverted, arginfo_class_GL_Math_Mat4_inverted, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Mat4, multiplyQuat, arginfo_class_GL_Math_Mat4_multiplyQuat, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_Math_Mat4, row, arginfo_class_GL_Math_Mat4_row, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, setRow, arginfo_class_GL_Math_Mat4_setRow, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, col, arginfo_class_GL_Math_Mat4_col, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, setCol, arginfo_class_GL_Math_Mat4_setCol, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, lookAt, arginfo_class_GL_Math_Mat4_lookAt, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, perspective, arginfo_class_GL_Math_Mat4_perspective, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, ortho, arginfo_class_GL_Math_Mat4_ortho, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, transpose, arginfo_class_GL_Math_Mat4_transpose, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, inverse, arginfo_class_GL_Math_Mat4_inverse, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, scale, arginfo_class_GL_Math_Mat4_scale, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, translate, arginfo_class_GL_Math_Mat4_translate, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, rotate, arginfo_class_GL_Math_Mat4_rotate, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, determinant, arginfo_class_GL_Math_Mat4_determinant, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Math_Mat4, __toString, arginfo_class_GL_Math_Mat4___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_BufferInterface_methods[] = {
	ZEND_ABSTRACT_ME_WITH_FLAGS(GL_Buffer_BufferInterface, __construct, arginfo_class_GL_Buffer_BufferInterface___construct, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(GL_Buffer_BufferInterface, clear, arginfo_class_GL_Buffer_BufferInterface_clear, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(GL_Buffer_BufferInterface, size, arginfo_class_GL_Buffer_BufferInterface_size, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(GL_Buffer_BufferInterface, capacity, arginfo_class_GL_Buffer_BufferInterface_capacity, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_ABSTRACT_ME_WITH_FLAGS(GL_Buffer_BufferInterface, reserve, arginfo_class_GL_Buffer_BufferInterface_reserve, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_FloatBuffer_methods[] = {
	ZEND_ME(GL_Buffer_FloatBuffer, __construct, arginfo_class_GL_Buffer_FloatBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, __toString, arginfo_class_GL_Buffer_FloatBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, push, arginfo_class_GL_Buffer_FloatBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, pushArray, arginfo_class_GL_Buffer_FloatBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, pushVec2, arginfo_class_GL_Buffer_FloatBuffer_pushVec2, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, pushVec3, arginfo_class_GL_Buffer_FloatBuffer_pushVec3, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, pushVec4, arginfo_class_GL_Buffer_FloatBuffer_pushVec4, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, pushMat4, arginfo_class_GL_Buffer_FloatBuffer_pushMat4, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, quantizeToUChar, arginfo_class_GL_Buffer_FloatBuffer_quantizeToUChar, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, fill, arginfo_class_GL_Buffer_FloatBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, clear, arginfo_class_GL_Buffer_FloatBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, size, arginfo_class_GL_Buffer_FloatBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, capacity, arginfo_class_GL_Buffer_FloatBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, reserve, arginfo_class_GL_Buffer_FloatBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_FloatBuffer, dump, arginfo_class_GL_Buffer_FloatBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_HFloatBuffer_methods[] = {
	ZEND_ME(GL_Buffer_HFloatBuffer, __construct, arginfo_class_GL_Buffer_HFloatBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, __toString, arginfo_class_GL_Buffer_HFloatBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, push, arginfo_class_GL_Buffer_HFloatBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, pushArray, arginfo_class_GL_Buffer_HFloatBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, fill, arginfo_class_GL_Buffer_HFloatBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, clear, arginfo_class_GL_Buffer_HFloatBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, size, arginfo_class_GL_Buffer_HFloatBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, capacity, arginfo_class_GL_Buffer_HFloatBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, reserve, arginfo_class_GL_Buffer_HFloatBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_HFloatBuffer, dump, arginfo_class_GL_Buffer_HFloatBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_DoubleBuffer_methods[] = {
	ZEND_ME(GL_Buffer_DoubleBuffer, __construct, arginfo_class_GL_Buffer_DoubleBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, __toString, arginfo_class_GL_Buffer_DoubleBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, push, arginfo_class_GL_Buffer_DoubleBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, pushArray, arginfo_class_GL_Buffer_DoubleBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, fill, arginfo_class_GL_Buffer_DoubleBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, clear, arginfo_class_GL_Buffer_DoubleBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, size, arginfo_class_GL_Buffer_DoubleBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, capacity, arginfo_class_GL_Buffer_DoubleBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, reserve, arginfo_class_GL_Buffer_DoubleBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_DoubleBuffer, dump, arginfo_class_GL_Buffer_DoubleBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_IntBuffer_methods[] = {
	ZEND_ME(GL_Buffer_IntBuffer, __construct, arginfo_class_GL_Buffer_IntBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, __toString, arginfo_class_GL_Buffer_IntBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, push, arginfo_class_GL_Buffer_IntBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, pushArray, arginfo_class_GL_Buffer_IntBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, fill, arginfo_class_GL_Buffer_IntBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, clear, arginfo_class_GL_Buffer_IntBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, size, arginfo_class_GL_Buffer_IntBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, capacity, arginfo_class_GL_Buffer_IntBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, reserve, arginfo_class_GL_Buffer_IntBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_IntBuffer, dump, arginfo_class_GL_Buffer_IntBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_UIntBuffer_methods[] = {
	ZEND_ME(GL_Buffer_UIntBuffer, __construct, arginfo_class_GL_Buffer_UIntBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, __toString, arginfo_class_GL_Buffer_UIntBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, push, arginfo_class_GL_Buffer_UIntBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, pushArray, arginfo_class_GL_Buffer_UIntBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, fill, arginfo_class_GL_Buffer_UIntBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, clear, arginfo_class_GL_Buffer_UIntBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, size, arginfo_class_GL_Buffer_UIntBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, capacity, arginfo_class_GL_Buffer_UIntBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, reserve, arginfo_class_GL_Buffer_UIntBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UIntBuffer, dump, arginfo_class_GL_Buffer_UIntBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_ShortBuffer_methods[] = {
	ZEND_ME(GL_Buffer_ShortBuffer, __construct, arginfo_class_GL_Buffer_ShortBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, __toString, arginfo_class_GL_Buffer_ShortBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, push, arginfo_class_GL_Buffer_ShortBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, pushArray, arginfo_class_GL_Buffer_ShortBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, fill, arginfo_class_GL_Buffer_ShortBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, clear, arginfo_class_GL_Buffer_ShortBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, size, arginfo_class_GL_Buffer_ShortBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, capacity, arginfo_class_GL_Buffer_ShortBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, reserve, arginfo_class_GL_Buffer_ShortBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ShortBuffer, dump, arginfo_class_GL_Buffer_ShortBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_UShortBuffer_methods[] = {
	ZEND_ME(GL_Buffer_UShortBuffer, __construct, arginfo_class_GL_Buffer_UShortBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, __toString, arginfo_class_GL_Buffer_UShortBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, push, arginfo_class_GL_Buffer_UShortBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, pushArray, arginfo_class_GL_Buffer_UShortBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, fill, arginfo_class_GL_Buffer_UShortBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, clear, arginfo_class_GL_Buffer_UShortBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, size, arginfo_class_GL_Buffer_UShortBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, capacity, arginfo_class_GL_Buffer_UShortBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, reserve, arginfo_class_GL_Buffer_UShortBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UShortBuffer, dump, arginfo_class_GL_Buffer_UShortBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_ByteBuffer_methods[] = {
	ZEND_ME(GL_Buffer_ByteBuffer, __construct, arginfo_class_GL_Buffer_ByteBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, __toString, arginfo_class_GL_Buffer_ByteBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, push, arginfo_class_GL_Buffer_ByteBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, pushArray, arginfo_class_GL_Buffer_ByteBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, fill, arginfo_class_GL_Buffer_ByteBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, clear, arginfo_class_GL_Buffer_ByteBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, size, arginfo_class_GL_Buffer_ByteBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, capacity, arginfo_class_GL_Buffer_ByteBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, reserve, arginfo_class_GL_Buffer_ByteBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_ByteBuffer, dump, arginfo_class_GL_Buffer_ByteBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_Buffer_UByteBuffer_methods[] = {
	ZEND_ME(GL_Buffer_UByteBuffer, __construct, arginfo_class_GL_Buffer_UByteBuffer___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, __toString, arginfo_class_GL_Buffer_UByteBuffer___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, push, arginfo_class_GL_Buffer_UByteBuffer_push, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, pushArray, arginfo_class_GL_Buffer_UByteBuffer_pushArray, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, pushString, arginfo_class_GL_Buffer_UByteBuffer_pushString, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, fill, arginfo_class_GL_Buffer_UByteBuffer_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, clear, arginfo_class_GL_Buffer_UByteBuffer_clear, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, size, arginfo_class_GL_Buffer_UByteBuffer_size, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, capacity, arginfo_class_GL_Buffer_UByteBuffer_capacity, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, reserve, arginfo_class_GL_Buffer_UByteBuffer_reserve, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_Buffer_UByteBuffer, dump, arginfo_class_GL_Buffer_UByteBuffer_dump, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_VectorGraphics_VGColor_methods[] = {
	ZEND_ME(GL_VectorGraphics_VGColor, rgb, arginfo_class_GL_VectorGraphics_VGColor_rgb, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, rgba, arginfo_class_GL_VectorGraphics_VGColor_rgba, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, hsl, arginfo_class_GL_VectorGraphics_VGColor_hsl, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, hsla, arginfo_class_GL_VectorGraphics_VGColor_hsla, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, irgb, arginfo_class_GL_VectorGraphics_VGColor_irgb, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, irgba, arginfo_class_GL_VectorGraphics_VGColor_irgba, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, hex, arginfo_class_GL_VectorGraphics_VGColor_hex, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, red, arginfo_class_GL_VectorGraphics_VGColor_red, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, green, arginfo_class_GL_VectorGraphics_VGColor_green, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, blue, arginfo_class_GL_VectorGraphics_VGColor_blue, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, white, arginfo_class_GL_VectorGraphics_VGColor_white, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, black, arginfo_class_GL_VectorGraphics_VGColor_black, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, transparent, arginfo_class_GL_VectorGraphics_VGColor_transparent, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, yellow, arginfo_class_GL_VectorGraphics_VGColor_yellow, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, cyan, arginfo_class_GL_VectorGraphics_VGColor_cyan, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, magenta, arginfo_class_GL_VectorGraphics_VGColor_magenta, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, orange, arginfo_class_GL_VectorGraphics_VGColor_orange, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, pink, arginfo_class_GL_VectorGraphics_VGColor_pink, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, purple, arginfo_class_GL_VectorGraphics_VGColor_purple, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, brown, arginfo_class_GL_VectorGraphics_VGColor_brown, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, gray, arginfo_class_GL_VectorGraphics_VGColor_gray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, darkGray, arginfo_class_GL_VectorGraphics_VGColor_darkGray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, lightGray, arginfo_class_GL_VectorGraphics_VGColor_lightGray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, random, arginfo_class_GL_VectorGraphics_VGColor_random, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, randomGray, arginfo_class_GL_VectorGraphics_VGColor_randomGray, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(GL_VectorGraphics_VGColor, __construct, arginfo_class_GL_VectorGraphics_VGColor___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, getHSLA, arginfo_class_GL_VectorGraphics_VGColor_getHSLA, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, getHSL, arginfo_class_GL_VectorGraphics_VGColor_getHSL, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, getVec4, arginfo_class_GL_VectorGraphics_VGColor_getVec4, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, getVec3, arginfo_class_GL_VectorGraphics_VGColor_getVec3, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, darken, arginfo_class_GL_VectorGraphics_VGColor_darken, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, lighten, arginfo_class_GL_VectorGraphics_VGColor_lighten, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGColor, invert, arginfo_class_GL_VectorGraphics_VGColor_invert, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_VectorGraphics_VGPaint_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_GL_VectorGraphics_VGImage_methods[] = {
	ZEND_ME(GL_VectorGraphics_VGImage, makePaint, arginfo_class_GL_VectorGraphics_VGImage_makePaint, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGImage, makePaintCentered, arginfo_class_GL_VectorGraphics_VGImage_makePaintCentered, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};


static const zend_function_entry class_GL_VectorGraphics_VGAlign_methods[] = {
	ZEND_FE_END
};


static const zend_function_entry class_GL_VectorGraphics_VGContext_methods[] = {
	ZEND_ME(GL_VectorGraphics_VGContext, __construct, arginfo_class_GL_VectorGraphics_VGContext___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fillColori, arginfo_class_GL_VectorGraphics_VGContext_fillColori, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, strokeColori, arginfo_class_GL_VectorGraphics_VGContext_strokeColori, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fillColorVec4, arginfo_class_GL_VectorGraphics_VGContext_fillColorVec4, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, strokeColorVec4, arginfo_class_GL_VectorGraphics_VGContext_strokeColorVec4, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, transformPoint, arginfo_class_GL_VectorGraphics_VGContext_transformPoint, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, transformVec2, arginfo_class_GL_VectorGraphics_VGContext_transformVec2, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, imageFromTexture, arginfo_class_GL_VectorGraphics_VGContext_imageFromTexture, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, imageFromHandle, arginfo_class_GL_VectorGraphics_VGContext_imageFromHandle, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, linearGradient, arginfo_class_GL_VectorGraphics_VGContext_linearGradient, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, boxGradient, arginfo_class_GL_VectorGraphics_VGContext_boxGradient, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, radialGradient, arginfo_class_GL_VectorGraphics_VGContext_radialGradient, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, beginFrame, arginfo_class_GL_VectorGraphics_VGContext_beginFrame, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, cancelFrame, arginfo_class_GL_VectorGraphics_VGContext_cancelFrame, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, endFrame, arginfo_class_GL_VectorGraphics_VGContext_endFrame, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, globalCompositeOperation, arginfo_class_GL_VectorGraphics_VGContext_globalCompositeOperation, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, globalCompositeBlendFunc, arginfo_class_GL_VectorGraphics_VGContext_globalCompositeBlendFunc, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, globalCompositeBlendFuncSeparate, arginfo_class_GL_VectorGraphics_VGContext_globalCompositeBlendFuncSeparate, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, save, arginfo_class_GL_VectorGraphics_VGContext_save, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, restore, arginfo_class_GL_VectorGraphics_VGContext_restore, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, reset, arginfo_class_GL_VectorGraphics_VGContext_reset, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, shapeAntiAlias, arginfo_class_GL_VectorGraphics_VGContext_shapeAntiAlias, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, strokeColor, arginfo_class_GL_VectorGraphics_VGContext_strokeColor, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, strokePaint, arginfo_class_GL_VectorGraphics_VGContext_strokePaint, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fillColor, arginfo_class_GL_VectorGraphics_VGContext_fillColor, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fillPaint, arginfo_class_GL_VectorGraphics_VGContext_fillPaint, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, miterLimit, arginfo_class_GL_VectorGraphics_VGContext_miterLimit, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, strokeWidth, arginfo_class_GL_VectorGraphics_VGContext_strokeWidth, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, lineCap, arginfo_class_GL_VectorGraphics_VGContext_lineCap, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, lineJoin, arginfo_class_GL_VectorGraphics_VGContext_lineJoin, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, globalAlpha, arginfo_class_GL_VectorGraphics_VGContext_globalAlpha, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, resetTransform, arginfo_class_GL_VectorGraphics_VGContext_resetTransform, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, transform, arginfo_class_GL_VectorGraphics_VGContext_transform, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, translate, arginfo_class_GL_VectorGraphics_VGContext_translate, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, rotate, arginfo_class_GL_VectorGraphics_VGContext_rotate, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, skewX, arginfo_class_GL_VectorGraphics_VGContext_skewX, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, skewY, arginfo_class_GL_VectorGraphics_VGContext_skewY, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, scale, arginfo_class_GL_VectorGraphics_VGContext_scale, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, currentTransform, arginfo_class_GL_VectorGraphics_VGContext_currentTransform, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, transformPointCurrent, arginfo_class_GL_VectorGraphics_VGContext_transformPointCurrent, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, imageSize, arginfo_class_GL_VectorGraphics_VGContext_imageSize, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, deleteImage, arginfo_class_GL_VectorGraphics_VGContext_deleteImage, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, scissor, arginfo_class_GL_VectorGraphics_VGContext_scissor, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, intersectScissor, arginfo_class_GL_VectorGraphics_VGContext_intersectScissor, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, resetScissor, arginfo_class_GL_VectorGraphics_VGContext_resetScissor, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, beginPath, arginfo_class_GL_VectorGraphics_VGContext_beginPath, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, moveTo, arginfo_class_GL_VectorGraphics_VGContext_moveTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, lineTo, arginfo_class_GL_VectorGraphics_VGContext_lineTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, bezierTo, arginfo_class_GL_VectorGraphics_VGContext_bezierTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, quadTo, arginfo_class_GL_VectorGraphics_VGContext_quadTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, arcTo, arginfo_class_GL_VectorGraphics_VGContext_arcTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, closePath, arginfo_class_GL_VectorGraphics_VGContext_closePath, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, pathWinding, arginfo_class_GL_VectorGraphics_VGContext_pathWinding, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, arc, arginfo_class_GL_VectorGraphics_VGContext_arc, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, svgArcTo, arginfo_class_GL_VectorGraphics_VGContext_svgArcTo, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, rect, arginfo_class_GL_VectorGraphics_VGContext_rect, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, roundedRect, arginfo_class_GL_VectorGraphics_VGContext_roundedRect, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, roundedRectVarying, arginfo_class_GL_VectorGraphics_VGContext_roundedRectVarying, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, ellipse, arginfo_class_GL_VectorGraphics_VGContext_ellipse, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, circle, arginfo_class_GL_VectorGraphics_VGContext_circle, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fill, arginfo_class_GL_VectorGraphics_VGContext_fill, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, stroke, arginfo_class_GL_VectorGraphics_VGContext_stroke, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, createFont, arginfo_class_GL_VectorGraphics_VGContext_createFont, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, createFontAtIndex, arginfo_class_GL_VectorGraphics_VGContext_createFontAtIndex, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, findFont, arginfo_class_GL_VectorGraphics_VGContext_findFont, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, addFallbackFontId, arginfo_class_GL_VectorGraphics_VGContext_addFallbackFontId, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, addFallbackFont, arginfo_class_GL_VectorGraphics_VGContext_addFallbackFont, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, resetFallbackFontsId, arginfo_class_GL_VectorGraphics_VGContext_resetFallbackFontsId, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, resetFallbackFonts, arginfo_class_GL_VectorGraphics_VGContext_resetFallbackFonts, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fontSize, arginfo_class_GL_VectorGraphics_VGContext_fontSize, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fontBlur, arginfo_class_GL_VectorGraphics_VGContext_fontBlur, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textLetterSpacing, arginfo_class_GL_VectorGraphics_VGContext_textLetterSpacing, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textLineHeight, arginfo_class_GL_VectorGraphics_VGContext_textLineHeight, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textAlign, arginfo_class_GL_VectorGraphics_VGContext_textAlign, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fontFaceId, arginfo_class_GL_VectorGraphics_VGContext_fontFaceId, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, fontFace, arginfo_class_GL_VectorGraphics_VGContext_fontFace, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, text, arginfo_class_GL_VectorGraphics_VGContext_text, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textBox, arginfo_class_GL_VectorGraphics_VGContext_textBox, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textBounds, arginfo_class_GL_VectorGraphics_VGContext_textBounds, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textBoxBounds, arginfo_class_GL_VectorGraphics_VGContext_textBoxBounds, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, textMetrics, arginfo_class_GL_VectorGraphics_VGContext_textMetrics, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, deleteInternal, arginfo_class_GL_VectorGraphics_VGContext_deleteInternal, ZEND_ACC_PUBLIC)
	ZEND_ME(GL_VectorGraphics_VGContext, debugDumpPathCache, arginfo_class_GL_VectorGraphics_VGContext_debugDumpPathCache, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
