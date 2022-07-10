/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: e493e7f65006aecbc06e11ddcccdfa0a3a906d50 */

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexParameteri, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_LONG, 0)
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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetError, 0, 0, IS_LONG, 0)
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

#define arginfo_glPointParameteri arginfo_glPixelStorei

#define arginfo_glBlendColor arginfo_glClearColor

#define arginfo_glBlendEquation arginfo_glCullFace

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindBuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsBuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUnmapBuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBlendEquationSeparate, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, modeRGB, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, modeAlpha, IS_LONG, 0)
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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetAttribLocation, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetUniformLocation arginfo_glGetAttribLocation

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

#define arginfo_glValidateProgram arginfo_glDeleteProgram

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1d, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib1f arginfo_glVertexAttrib1d

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib1s, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib2d, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib2f arginfo_glVertexAttrib2d

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib2s, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib3d, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib3f arginfo_glVertexAttrib3d

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib3s, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4Nub, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexAttrib4d, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, z, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexAttrib4f arginfo_glVertexAttrib4d

#define arginfo_glVertexAttrib4s arginfo_glVertexAttrib4Nub

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glColorMaski, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, r, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, g, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, b, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, a, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

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

#define arginfo_glVertexAttribI1i arginfo_glVertexAttrib1s

#define arginfo_glVertexAttribI2i arginfo_glVertexAttrib2s

#define arginfo_glVertexAttribI3i arginfo_glVertexAttrib3s

#define arginfo_glVertexAttribI4i arginfo_glVertexAttrib4Nub

#define arginfo_glVertexAttribI1ui arginfo_glVertexAttrib1s

#define arginfo_glVertexAttribI2ui arginfo_glVertexAttrib2s

#define arginfo_glVertexAttribI3ui arginfo_glVertexAttrib3s

#define arginfo_glVertexAttribI4ui arginfo_glVertexAttrib4Nub

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glClearBufferfi, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, buffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, drawbuffer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, depth, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, stencil, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsRenderbuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, renderbuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindRenderbuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, renderbuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glRenderbufferStorage, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, internalformat, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsFramebuffer, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, framebuffer, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glBindFramebuffer, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, framebuffer, IS_LONG, 0)
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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glUniformBlockBinding, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uniformBlockIndex, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, uniformBlockBinding, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProvokingVertex arginfo_glCullFace

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glFenceSync, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, condition, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, flags, IS_LONG, 0)
ZEND_END_ARG_INFO()

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glSamplerParameterf, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sampler, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, param, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glQueryCounter, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, target, IS_LONG, 0)
ZEND_END_ARG_INFO()

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

#define arginfo_glVertexAttribP2ui arginfo_glVertexAttribP1ui

#define arginfo_glVertexAttribP3ui arginfo_glVertexAttribP1ui

#define arginfo_glVertexAttribP4ui arginfo_glVertexAttribP1ui

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glVertexP2ui, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glVertexP3ui arginfo_glVertexP2ui

#define arginfo_glVertexP4ui arginfo_glVertexP2ui

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glTexCoordP1ui, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, coords, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glTexCoordP2ui arginfo_glTexCoordP1ui

#define arginfo_glTexCoordP3ui arginfo_glTexCoordP1ui

#define arginfo_glTexCoordP4ui arginfo_glTexCoordP1ui

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glMultiTexCoordP1ui, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, texture, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, coords, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glMultiTexCoordP2ui arginfo_glMultiTexCoordP1ui

#define arginfo_glMultiTexCoordP3ui arginfo_glMultiTexCoordP1ui

#define arginfo_glMultiTexCoordP4ui arginfo_glMultiTexCoordP1ui

#define arginfo_glNormalP3ui arginfo_glTexCoordP1ui

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glColorP3ui, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, color, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glColorP4ui arginfo_glColorP3ui

#define arginfo_glSecondaryColorP3ui arginfo_glColorP3ui

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glGetSubroutineUniformLocation, 0, 3, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, shadertype, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_glGetSubroutineIndex arginfo_glGetSubroutineUniformLocation

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glPatchParameteri, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, pname, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_glBindTransformFeedback arginfo_glBeginQuery

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

#define arginfo_glReleaseShaderCompiler arginfo_glFinish

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glIsProgramPipeline, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, pipeline, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1i, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform1f, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform1d arginfo_glProgramUniform1f

#define arginfo_glProgramUniform1ui arginfo_glProgramUniform1i

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform2i, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform2f, 0, 4, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform2d arginfo_glProgramUniform2f

#define arginfo_glProgramUniform2ui arginfo_glProgramUniform2i

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform3i, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform3f, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform3d arginfo_glProgramUniform3f

#define arginfo_glProgramUniform3ui arginfo_glProgramUniform3i

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform4i, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v3, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glProgramUniform4f, 0, 6, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, program, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, location, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, v0, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, v3, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_glProgramUniform4d arginfo_glProgramUniform4f

#define arginfo_glProgramUniform4ui arginfo_glProgramUniform4i

#define arginfo_glValidateProgramPipeline arginfo_glBindProgramPipeline

#define arginfo_glVertexAttribL1d arginfo_glVertexAttrib1d

#define arginfo_glVertexAttribL2d arginfo_glVertexAttrib2d

#define arginfo_glVertexAttribL3d arginfo_glVertexAttrib3d

#define arginfo_glVertexAttribL4d arginfo_glVertexAttrib4d

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glViewportIndexedf, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, y, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, w, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, h, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glScissorIndexed, 0, 5, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, left, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, bottom, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, width, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, height, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glDepthRangeIndexed, 0, 3, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, f, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

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
	ZEND_ARG_OBJ_INFO(0, monitor, GLFWmonitor, 0)
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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glfwJoystickPresent, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, jid, IS_LONG, 0)
ZEND_END_ARG_INFO()

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

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_glShaderSource, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, shader, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, source, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PGL_Math_Vec3_length arginfo_glfwGetTime

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_PGL_Math_Vec3_normalize, 0, 0, PGL\\Math\\Vec3, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_PGL_Math_Vec3_abs arginfo_class_PGL_Math_Vec3_normalize

#define arginfo_class_PGL_Math_Vec3___toString arginfo_glfwGetVersionString


ZEND_FUNCTION(glCullFace);
ZEND_FUNCTION(glFrontFace);
ZEND_FUNCTION(glHint);
ZEND_FUNCTION(glLineWidth);
ZEND_FUNCTION(glPointSize);
ZEND_FUNCTION(glPolygonMode);
ZEND_FUNCTION(glScissor);
ZEND_FUNCTION(glTexParameterf);
ZEND_FUNCTION(glTexParameteri);
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
ZEND_FUNCTION(glGetError);
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
ZEND_FUNCTION(glIsTexture);
ZEND_FUNCTION(glCopyTexSubImage3D);
ZEND_FUNCTION(glActiveTexture);
ZEND_FUNCTION(glSampleCoverage);
ZEND_FUNCTION(glBlendFuncSeparate);
ZEND_FUNCTION(glPointParameterf);
ZEND_FUNCTION(glPointParameteri);
ZEND_FUNCTION(glBlendColor);
ZEND_FUNCTION(glBlendEquation);
ZEND_FUNCTION(glIsQuery);
ZEND_FUNCTION(glBeginQuery);
ZEND_FUNCTION(glEndQuery);
ZEND_FUNCTION(glBindBuffer);
ZEND_FUNCTION(glIsBuffer);
ZEND_FUNCTION(glUnmapBuffer);
ZEND_FUNCTION(glBlendEquationSeparate);
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
ZEND_FUNCTION(glGetAttribLocation);
ZEND_FUNCTION(glGetUniformLocation);
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
ZEND_FUNCTION(glValidateProgram);
ZEND_FUNCTION(glVertexAttrib1d);
ZEND_FUNCTION(glVertexAttrib1f);
ZEND_FUNCTION(glVertexAttrib1s);
ZEND_FUNCTION(glVertexAttrib2d);
ZEND_FUNCTION(glVertexAttrib2f);
ZEND_FUNCTION(glVertexAttrib2s);
ZEND_FUNCTION(glVertexAttrib3d);
ZEND_FUNCTION(glVertexAttrib3f);
ZEND_FUNCTION(glVertexAttrib3s);
ZEND_FUNCTION(glVertexAttrib4Nub);
ZEND_FUNCTION(glVertexAttrib4d);
ZEND_FUNCTION(glVertexAttrib4f);
ZEND_FUNCTION(glVertexAttrib4s);
ZEND_FUNCTION(glColorMaski);
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
ZEND_FUNCTION(glVertexAttribI1i);
ZEND_FUNCTION(glVertexAttribI2i);
ZEND_FUNCTION(glVertexAttribI3i);
ZEND_FUNCTION(glVertexAttribI4i);
ZEND_FUNCTION(glVertexAttribI1ui);
ZEND_FUNCTION(glVertexAttribI2ui);
ZEND_FUNCTION(glVertexAttribI3ui);
ZEND_FUNCTION(glVertexAttribI4ui);
ZEND_FUNCTION(glBindFragDataLocation);
ZEND_FUNCTION(glGetFragDataLocation);
ZEND_FUNCTION(glUniform1ui);
ZEND_FUNCTION(glUniform2ui);
ZEND_FUNCTION(glUniform3ui);
ZEND_FUNCTION(glUniform4ui);
ZEND_FUNCTION(glClearBufferfi);
ZEND_FUNCTION(glIsRenderbuffer);
ZEND_FUNCTION(glBindRenderbuffer);
ZEND_FUNCTION(glRenderbufferStorage);
ZEND_FUNCTION(glIsFramebuffer);
ZEND_FUNCTION(glBindFramebuffer);
ZEND_FUNCTION(glCheckFramebufferStatus);
ZEND_FUNCTION(glFramebufferTexture1D);
ZEND_FUNCTION(glFramebufferTexture2D);
ZEND_FUNCTION(glFramebufferTexture3D);
ZEND_FUNCTION(glFramebufferRenderbuffer);
ZEND_FUNCTION(glGenerateMipmap);
ZEND_FUNCTION(glBlitFramebuffer);
ZEND_FUNCTION(glRenderbufferStorageMultisample);
ZEND_FUNCTION(glFramebufferTextureLayer);
ZEND_FUNCTION(glFlushMappedBufferRange);
ZEND_FUNCTION(glBindVertexArray);
ZEND_FUNCTION(glIsVertexArray);
ZEND_FUNCTION(glDrawArraysInstanced);
ZEND_FUNCTION(glTexBuffer);
ZEND_FUNCTION(glPrimitiveRestartIndex);
ZEND_FUNCTION(glCopyBufferSubData);
ZEND_FUNCTION(glGetUniformBlockIndex);
ZEND_FUNCTION(glUniformBlockBinding);
ZEND_FUNCTION(glProvokingVertex);
ZEND_FUNCTION(glFenceSync);
ZEND_FUNCTION(glIsSync);
ZEND_FUNCTION(glDeleteSync);
ZEND_FUNCTION(glClientWaitSync);
ZEND_FUNCTION(glWaitSync);
ZEND_FUNCTION(glFramebufferTexture);
ZEND_FUNCTION(glTexImage2DMultisample);
ZEND_FUNCTION(glTexImage3DMultisample);
ZEND_FUNCTION(glSampleMaski);
ZEND_FUNCTION(glBindFragDataLocationIndexed);
ZEND_FUNCTION(glGetFragDataIndex);
ZEND_FUNCTION(glIsSampler);
ZEND_FUNCTION(glBindSampler);
ZEND_FUNCTION(glSamplerParameteri);
ZEND_FUNCTION(glSamplerParameterf);
ZEND_FUNCTION(glQueryCounter);
ZEND_FUNCTION(glVertexAttribDivisor);
ZEND_FUNCTION(glVertexAttribP1ui);
ZEND_FUNCTION(glVertexAttribP2ui);
ZEND_FUNCTION(glVertexAttribP3ui);
ZEND_FUNCTION(glVertexAttribP4ui);
ZEND_FUNCTION(glVertexP2ui);
ZEND_FUNCTION(glVertexP3ui);
ZEND_FUNCTION(glVertexP4ui);
ZEND_FUNCTION(glTexCoordP1ui);
ZEND_FUNCTION(glTexCoordP2ui);
ZEND_FUNCTION(glTexCoordP3ui);
ZEND_FUNCTION(glTexCoordP4ui);
ZEND_FUNCTION(glMultiTexCoordP1ui);
ZEND_FUNCTION(glMultiTexCoordP2ui);
ZEND_FUNCTION(glMultiTexCoordP3ui);
ZEND_FUNCTION(glMultiTexCoordP4ui);
ZEND_FUNCTION(glNormalP3ui);
ZEND_FUNCTION(glColorP3ui);
ZEND_FUNCTION(glColorP4ui);
ZEND_FUNCTION(glSecondaryColorP3ui);
ZEND_FUNCTION(glMinSampleShading);
ZEND_FUNCTION(glBlendEquationi);
ZEND_FUNCTION(glBlendEquationSeparatei);
ZEND_FUNCTION(glBlendFunci);
ZEND_FUNCTION(glBlendFuncSeparatei);
ZEND_FUNCTION(glUniform1d);
ZEND_FUNCTION(glUniform2d);
ZEND_FUNCTION(glUniform3d);
ZEND_FUNCTION(glUniform4d);
ZEND_FUNCTION(glGetSubroutineUniformLocation);
ZEND_FUNCTION(glGetSubroutineIndex);
ZEND_FUNCTION(glPatchParameteri);
ZEND_FUNCTION(glBindTransformFeedback);
ZEND_FUNCTION(glIsTransformFeedback);
ZEND_FUNCTION(glPauseTransformFeedback);
ZEND_FUNCTION(glResumeTransformFeedback);
ZEND_FUNCTION(glDrawTransformFeedback);
ZEND_FUNCTION(glDrawTransformFeedbackStream);
ZEND_FUNCTION(glBeginQueryIndexed);
ZEND_FUNCTION(glEndQueryIndexed);
ZEND_FUNCTION(glReleaseShaderCompiler);
ZEND_FUNCTION(glDepthRangef);
ZEND_FUNCTION(glClearDepthf);
ZEND_FUNCTION(glProgramParameteri);
ZEND_FUNCTION(glUseProgramStages);
ZEND_FUNCTION(glActiveShaderProgram);
ZEND_FUNCTION(glBindProgramPipeline);
ZEND_FUNCTION(glIsProgramPipeline);
ZEND_FUNCTION(glProgramUniform1i);
ZEND_FUNCTION(glProgramUniform1f);
ZEND_FUNCTION(glProgramUniform1d);
ZEND_FUNCTION(glProgramUniform1ui);
ZEND_FUNCTION(glProgramUniform2i);
ZEND_FUNCTION(glProgramUniform2f);
ZEND_FUNCTION(glProgramUniform2d);
ZEND_FUNCTION(glProgramUniform2ui);
ZEND_FUNCTION(glProgramUniform3i);
ZEND_FUNCTION(glProgramUniform3f);
ZEND_FUNCTION(glProgramUniform3d);
ZEND_FUNCTION(glProgramUniform3ui);
ZEND_FUNCTION(glProgramUniform4i);
ZEND_FUNCTION(glProgramUniform4f);
ZEND_FUNCTION(glProgramUniform4d);
ZEND_FUNCTION(glProgramUniform4ui);
ZEND_FUNCTION(glValidateProgramPipeline);
ZEND_FUNCTION(glVertexAttribL1d);
ZEND_FUNCTION(glVertexAttribL2d);
ZEND_FUNCTION(glVertexAttribL3d);
ZEND_FUNCTION(glVertexAttribL4d);
ZEND_FUNCTION(glViewportIndexedf);
ZEND_FUNCTION(glScissorIndexed);
ZEND_FUNCTION(glDepthRangeIndexed);
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
ZEND_FUNCTION(glfwJoystickPresent);
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
ZEND_FUNCTION(glShaderSource);
ZEND_METHOD(PGL_Math_Vec3, length);
ZEND_METHOD(PGL_Math_Vec3, normalize);
ZEND_METHOD(PGL_Math_Vec3, abs);
ZEND_METHOD(PGL_Math_Vec3, __toString);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(glCullFace, arginfo_glCullFace)
	ZEND_FE(glFrontFace, arginfo_glFrontFace)
	ZEND_FE(glHint, arginfo_glHint)
	ZEND_FE(glLineWidth, arginfo_glLineWidth)
	ZEND_FE(glPointSize, arginfo_glPointSize)
	ZEND_FE(glPolygonMode, arginfo_glPolygonMode)
	ZEND_FE(glScissor, arginfo_glScissor)
	ZEND_FE(glTexParameterf, arginfo_glTexParameterf)
	ZEND_FE(glTexParameteri, arginfo_glTexParameteri)
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
	ZEND_FE(glGetError, arginfo_glGetError)
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
	ZEND_FE(glIsTexture, arginfo_glIsTexture)
	ZEND_FE(glCopyTexSubImage3D, arginfo_glCopyTexSubImage3D)
	ZEND_FE(glActiveTexture, arginfo_glActiveTexture)
	ZEND_FE(glSampleCoverage, arginfo_glSampleCoverage)
	ZEND_FE(glBlendFuncSeparate, arginfo_glBlendFuncSeparate)
	ZEND_FE(glPointParameterf, arginfo_glPointParameterf)
	ZEND_FE(glPointParameteri, arginfo_glPointParameteri)
	ZEND_FE(glBlendColor, arginfo_glBlendColor)
	ZEND_FE(glBlendEquation, arginfo_glBlendEquation)
	ZEND_FE(glIsQuery, arginfo_glIsQuery)
	ZEND_FE(glBeginQuery, arginfo_glBeginQuery)
	ZEND_FE(glEndQuery, arginfo_glEndQuery)
	ZEND_FE(glBindBuffer, arginfo_glBindBuffer)
	ZEND_FE(glIsBuffer, arginfo_glIsBuffer)
	ZEND_FE(glUnmapBuffer, arginfo_glUnmapBuffer)
	ZEND_FE(glBlendEquationSeparate, arginfo_glBlendEquationSeparate)
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
	ZEND_FE(glGetAttribLocation, arginfo_glGetAttribLocation)
	ZEND_FE(glGetUniformLocation, arginfo_glGetUniformLocation)
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
	ZEND_FE(glValidateProgram, arginfo_glValidateProgram)
	ZEND_FE(glVertexAttrib1d, arginfo_glVertexAttrib1d)
	ZEND_FE(glVertexAttrib1f, arginfo_glVertexAttrib1f)
	ZEND_FE(glVertexAttrib1s, arginfo_glVertexAttrib1s)
	ZEND_FE(glVertexAttrib2d, arginfo_glVertexAttrib2d)
	ZEND_FE(glVertexAttrib2f, arginfo_glVertexAttrib2f)
	ZEND_FE(glVertexAttrib2s, arginfo_glVertexAttrib2s)
	ZEND_FE(glVertexAttrib3d, arginfo_glVertexAttrib3d)
	ZEND_FE(glVertexAttrib3f, arginfo_glVertexAttrib3f)
	ZEND_FE(glVertexAttrib3s, arginfo_glVertexAttrib3s)
	ZEND_FE(glVertexAttrib4Nub, arginfo_glVertexAttrib4Nub)
	ZEND_FE(glVertexAttrib4d, arginfo_glVertexAttrib4d)
	ZEND_FE(glVertexAttrib4f, arginfo_glVertexAttrib4f)
	ZEND_FE(glVertexAttrib4s, arginfo_glVertexAttrib4s)
	ZEND_FE(glColorMaski, arginfo_glColorMaski)
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
	ZEND_FE(glVertexAttribI1i, arginfo_glVertexAttribI1i)
	ZEND_FE(glVertexAttribI2i, arginfo_glVertexAttribI2i)
	ZEND_FE(glVertexAttribI3i, arginfo_glVertexAttribI3i)
	ZEND_FE(glVertexAttribI4i, arginfo_glVertexAttribI4i)
	ZEND_FE(glVertexAttribI1ui, arginfo_glVertexAttribI1ui)
	ZEND_FE(glVertexAttribI2ui, arginfo_glVertexAttribI2ui)
	ZEND_FE(glVertexAttribI3ui, arginfo_glVertexAttribI3ui)
	ZEND_FE(glVertexAttribI4ui, arginfo_glVertexAttribI4ui)
	ZEND_FE(glBindFragDataLocation, arginfo_glBindFragDataLocation)
	ZEND_FE(glGetFragDataLocation, arginfo_glGetFragDataLocation)
	ZEND_FE(glUniform1ui, arginfo_glUniform1ui)
	ZEND_FE(glUniform2ui, arginfo_glUniform2ui)
	ZEND_FE(glUniform3ui, arginfo_glUniform3ui)
	ZEND_FE(glUniform4ui, arginfo_glUniform4ui)
	ZEND_FE(glClearBufferfi, arginfo_glClearBufferfi)
	ZEND_FE(glIsRenderbuffer, arginfo_glIsRenderbuffer)
	ZEND_FE(glBindRenderbuffer, arginfo_glBindRenderbuffer)
	ZEND_FE(glRenderbufferStorage, arginfo_glRenderbufferStorage)
	ZEND_FE(glIsFramebuffer, arginfo_glIsFramebuffer)
	ZEND_FE(glBindFramebuffer, arginfo_glBindFramebuffer)
	ZEND_FE(glCheckFramebufferStatus, arginfo_glCheckFramebufferStatus)
	ZEND_FE(glFramebufferTexture1D, arginfo_glFramebufferTexture1D)
	ZEND_FE(glFramebufferTexture2D, arginfo_glFramebufferTexture2D)
	ZEND_FE(glFramebufferTexture3D, arginfo_glFramebufferTexture3D)
	ZEND_FE(glFramebufferRenderbuffer, arginfo_glFramebufferRenderbuffer)
	ZEND_FE(glGenerateMipmap, arginfo_glGenerateMipmap)
	ZEND_FE(glBlitFramebuffer, arginfo_glBlitFramebuffer)
	ZEND_FE(glRenderbufferStorageMultisample, arginfo_glRenderbufferStorageMultisample)
	ZEND_FE(glFramebufferTextureLayer, arginfo_glFramebufferTextureLayer)
	ZEND_FE(glFlushMappedBufferRange, arginfo_glFlushMappedBufferRange)
	ZEND_FE(glBindVertexArray, arginfo_glBindVertexArray)
	ZEND_FE(glIsVertexArray, arginfo_glIsVertexArray)
	ZEND_FE(glDrawArraysInstanced, arginfo_glDrawArraysInstanced)
	ZEND_FE(glTexBuffer, arginfo_glTexBuffer)
	ZEND_FE(glPrimitiveRestartIndex, arginfo_glPrimitiveRestartIndex)
	ZEND_FE(glCopyBufferSubData, arginfo_glCopyBufferSubData)
	ZEND_FE(glGetUniformBlockIndex, arginfo_glGetUniformBlockIndex)
	ZEND_FE(glUniformBlockBinding, arginfo_glUniformBlockBinding)
	ZEND_FE(glProvokingVertex, arginfo_glProvokingVertex)
	ZEND_FE(glFenceSync, arginfo_glFenceSync)
	ZEND_FE(glIsSync, arginfo_glIsSync)
	ZEND_FE(glDeleteSync, arginfo_glDeleteSync)
	ZEND_FE(glClientWaitSync, arginfo_glClientWaitSync)
	ZEND_FE(glWaitSync, arginfo_glWaitSync)
	ZEND_FE(glFramebufferTexture, arginfo_glFramebufferTexture)
	ZEND_FE(glTexImage2DMultisample, arginfo_glTexImage2DMultisample)
	ZEND_FE(glTexImage3DMultisample, arginfo_glTexImage3DMultisample)
	ZEND_FE(glSampleMaski, arginfo_glSampleMaski)
	ZEND_FE(glBindFragDataLocationIndexed, arginfo_glBindFragDataLocationIndexed)
	ZEND_FE(glGetFragDataIndex, arginfo_glGetFragDataIndex)
	ZEND_FE(glIsSampler, arginfo_glIsSampler)
	ZEND_FE(glBindSampler, arginfo_glBindSampler)
	ZEND_FE(glSamplerParameteri, arginfo_glSamplerParameteri)
	ZEND_FE(glSamplerParameterf, arginfo_glSamplerParameterf)
	ZEND_FE(glQueryCounter, arginfo_glQueryCounter)
	ZEND_FE(glVertexAttribDivisor, arginfo_glVertexAttribDivisor)
	ZEND_FE(glVertexAttribP1ui, arginfo_glVertexAttribP1ui)
	ZEND_FE(glVertexAttribP2ui, arginfo_glVertexAttribP2ui)
	ZEND_FE(glVertexAttribP3ui, arginfo_glVertexAttribP3ui)
	ZEND_FE(glVertexAttribP4ui, arginfo_glVertexAttribP4ui)
	ZEND_FE(glVertexP2ui, arginfo_glVertexP2ui)
	ZEND_FE(glVertexP3ui, arginfo_glVertexP3ui)
	ZEND_FE(glVertexP4ui, arginfo_glVertexP4ui)
	ZEND_FE(glTexCoordP1ui, arginfo_glTexCoordP1ui)
	ZEND_FE(glTexCoordP2ui, arginfo_glTexCoordP2ui)
	ZEND_FE(glTexCoordP3ui, arginfo_glTexCoordP3ui)
	ZEND_FE(glTexCoordP4ui, arginfo_glTexCoordP4ui)
	ZEND_FE(glMultiTexCoordP1ui, arginfo_glMultiTexCoordP1ui)
	ZEND_FE(glMultiTexCoordP2ui, arginfo_glMultiTexCoordP2ui)
	ZEND_FE(glMultiTexCoordP3ui, arginfo_glMultiTexCoordP3ui)
	ZEND_FE(glMultiTexCoordP4ui, arginfo_glMultiTexCoordP4ui)
	ZEND_FE(glNormalP3ui, arginfo_glNormalP3ui)
	ZEND_FE(glColorP3ui, arginfo_glColorP3ui)
	ZEND_FE(glColorP4ui, arginfo_glColorP4ui)
	ZEND_FE(glSecondaryColorP3ui, arginfo_glSecondaryColorP3ui)
	ZEND_FE(glMinSampleShading, arginfo_glMinSampleShading)
	ZEND_FE(glBlendEquationi, arginfo_glBlendEquationi)
	ZEND_FE(glBlendEquationSeparatei, arginfo_glBlendEquationSeparatei)
	ZEND_FE(glBlendFunci, arginfo_glBlendFunci)
	ZEND_FE(glBlendFuncSeparatei, arginfo_glBlendFuncSeparatei)
	ZEND_FE(glUniform1d, arginfo_glUniform1d)
	ZEND_FE(glUniform2d, arginfo_glUniform2d)
	ZEND_FE(glUniform3d, arginfo_glUniform3d)
	ZEND_FE(glUniform4d, arginfo_glUniform4d)
	ZEND_FE(glGetSubroutineUniformLocation, arginfo_glGetSubroutineUniformLocation)
	ZEND_FE(glGetSubroutineIndex, arginfo_glGetSubroutineIndex)
	ZEND_FE(glPatchParameteri, arginfo_glPatchParameteri)
	ZEND_FE(glBindTransformFeedback, arginfo_glBindTransformFeedback)
	ZEND_FE(glIsTransformFeedback, arginfo_glIsTransformFeedback)
	ZEND_FE(glPauseTransformFeedback, arginfo_glPauseTransformFeedback)
	ZEND_FE(glResumeTransformFeedback, arginfo_glResumeTransformFeedback)
	ZEND_FE(glDrawTransformFeedback, arginfo_glDrawTransformFeedback)
	ZEND_FE(glDrawTransformFeedbackStream, arginfo_glDrawTransformFeedbackStream)
	ZEND_FE(glBeginQueryIndexed, arginfo_glBeginQueryIndexed)
	ZEND_FE(glEndQueryIndexed, arginfo_glEndQueryIndexed)
	ZEND_FE(glReleaseShaderCompiler, arginfo_glReleaseShaderCompiler)
	ZEND_FE(glDepthRangef, arginfo_glDepthRangef)
	ZEND_FE(glClearDepthf, arginfo_glClearDepthf)
	ZEND_FE(glProgramParameteri, arginfo_glProgramParameteri)
	ZEND_FE(glUseProgramStages, arginfo_glUseProgramStages)
	ZEND_FE(glActiveShaderProgram, arginfo_glActiveShaderProgram)
	ZEND_FE(glBindProgramPipeline, arginfo_glBindProgramPipeline)
	ZEND_FE(glIsProgramPipeline, arginfo_glIsProgramPipeline)
	ZEND_FE(glProgramUniform1i, arginfo_glProgramUniform1i)
	ZEND_FE(glProgramUniform1f, arginfo_glProgramUniform1f)
	ZEND_FE(glProgramUniform1d, arginfo_glProgramUniform1d)
	ZEND_FE(glProgramUniform1ui, arginfo_glProgramUniform1ui)
	ZEND_FE(glProgramUniform2i, arginfo_glProgramUniform2i)
	ZEND_FE(glProgramUniform2f, arginfo_glProgramUniform2f)
	ZEND_FE(glProgramUniform2d, arginfo_glProgramUniform2d)
	ZEND_FE(glProgramUniform2ui, arginfo_glProgramUniform2ui)
	ZEND_FE(glProgramUniform3i, arginfo_glProgramUniform3i)
	ZEND_FE(glProgramUniform3f, arginfo_glProgramUniform3f)
	ZEND_FE(glProgramUniform3d, arginfo_glProgramUniform3d)
	ZEND_FE(glProgramUniform3ui, arginfo_glProgramUniform3ui)
	ZEND_FE(glProgramUniform4i, arginfo_glProgramUniform4i)
	ZEND_FE(glProgramUniform4f, arginfo_glProgramUniform4f)
	ZEND_FE(glProgramUniform4d, arginfo_glProgramUniform4d)
	ZEND_FE(glProgramUniform4ui, arginfo_glProgramUniform4ui)
	ZEND_FE(glValidateProgramPipeline, arginfo_glValidateProgramPipeline)
	ZEND_FE(glVertexAttribL1d, arginfo_glVertexAttribL1d)
	ZEND_FE(glVertexAttribL2d, arginfo_glVertexAttribL2d)
	ZEND_FE(glVertexAttribL3d, arginfo_glVertexAttribL3d)
	ZEND_FE(glVertexAttribL4d, arginfo_glVertexAttribL4d)
	ZEND_FE(glViewportIndexedf, arginfo_glViewportIndexedf)
	ZEND_FE(glScissorIndexed, arginfo_glScissorIndexed)
	ZEND_FE(glDepthRangeIndexed, arginfo_glDepthRangeIndexed)
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
	ZEND_FE(glfwJoystickPresent, arginfo_glfwJoystickPresent)
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
	ZEND_FE(glShaderSource, arginfo_glShaderSource)
	ZEND_FE_END
};


static const zend_function_entry class_PGL_Math_Vec3_methods[] = {
	ZEND_ME(PGL_Math_Vec3, length, arginfo_class_PGL_Math_Vec3_length, ZEND_ACC_PUBLIC)
	ZEND_ME(PGL_Math_Vec3, normalize, arginfo_class_PGL_Math_Vec3_normalize, ZEND_ACC_PUBLIC)
	ZEND_ME(PGL_Math_Vec3, abs, arginfo_class_PGL_Math_Vec3_abs, ZEND_ACC_PUBLIC)
	ZEND_ME(PGL_Math_Vec3, __toString, arginfo_class_PGL_Math_Vec3___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};
