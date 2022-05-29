/**
 * PHP-glfw 
 * 
 * Extension functions
 *
 * Copyright (c) 2018-2022 Mario Döring
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "phpglfw_functions.h"

#include "php.h"
#include "phpglfw.h"
#include <zend_API.h>

/**
 * glCullFace 
 *  */
PHP_FUNCTION(glCullFace)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
       return;
    }
    glCullFace(mode);
}

/**
 * glFrontFace 
 *  */
PHP_FUNCTION(glFrontFace)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
       return;
    }
    glFrontFace(mode);
}

/**
 * glHint 
 *  */
PHP_FUNCTION(glHint)
{
    zend_long target;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &mode) == FAILURE) {
       return;
    }
    glHint(target, mode);
}

/**
 * glLineWidth 
 *  */
PHP_FUNCTION(glLineWidth)
{
    double width;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &width) == FAILURE) {
       return;
    }
    glLineWidth(width);
}

/**
 * glPointSize 
 *  */
PHP_FUNCTION(glPointSize)
{
    double size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &size) == FAILURE) {
       return;
    }
    glPointSize(size);
}

/**
 * glPolygonMode 
 *  */
PHP_FUNCTION(glPolygonMode)
{
    zend_long face;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &face, &mode) == FAILURE) {
       return;
    }
    glPolygonMode(face, mode);
}

/**
 * glScissor 
 *  */
PHP_FUNCTION(glScissor)
{
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &x, &y, &width, &height) == FAILURE) {
       return;
    }
    glScissor(x, y, width, height);
}

/**
 * glTexParameterf 
 *  */
PHP_FUNCTION(glTexParameterf)
{
    zend_long target;
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lld", &target, &pname, &param) == FAILURE) {
       return;
    }
    glTexParameterf(target, pname, param);
}

/**
 * glTexParameteri 
 *  */
PHP_FUNCTION(glTexParameteri)
{
    zend_long target;
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &pname, &param) == FAILURE) {
       return;
    }
    glTexParameteri(target, pname, param);
}

/**
 * glDrawBuffer 
 *  */
PHP_FUNCTION(glDrawBuffer)
{
    zend_long buf;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &buf) == FAILURE) {
       return;
    }
    glDrawBuffer(buf);
}

/**
 * glClear 
 *  */
PHP_FUNCTION(glClear)
{
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mask) == FAILURE) {
       return;
    }
    glClear(mask);
}

/**
 * glClearColor 
 *  */
PHP_FUNCTION(glClearColor)
{
    double red;
    double green;
    double blue;
    double alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &red, &green, &blue, &alpha) == FAILURE) {
       return;
    }
    glClearColor(red, green, blue, alpha);
}

/**
 * glClearStencil 
 *  */
PHP_FUNCTION(glClearStencil)
{
    zend_long s;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &s) == FAILURE) {
       return;
    }
    glClearStencil(s);
}

/**
 * glClearDepth 
 *  */
PHP_FUNCTION(glClearDepth)
{
    double depth;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &depth) == FAILURE) {
       return;
    }
    glClearDepth(depth);
}

/**
 * glStencilMask 
 *  */
PHP_FUNCTION(glStencilMask)
{
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mask) == FAILURE) {
       return;
    }
    glStencilMask(mask);
}

/**
 * glColorMask 
 *  */
PHP_FUNCTION(glColorMask)
{
    bool red;
    bool green;
    bool blue;
    bool alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "bbbb", &red, &green, &blue, &alpha) == FAILURE) {
       return;
    }
    glColorMask(red, green, blue, alpha);
}

/**
 * glDepthMask 
 *  */
PHP_FUNCTION(glDepthMask)
{
    bool flag;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "b", &flag) == FAILURE) {
       return;
    }
    glDepthMask(flag);
}

/**
 * glDisable 
 *  */
PHP_FUNCTION(glDisable)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
       return;
    }
    glDisable(cap);
}

/**
 * glEnable 
 *  */
PHP_FUNCTION(glEnable)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
       return;
    }
    glEnable(cap);
}

/**
 * glFinish 
 *  */
PHP_FUNCTION(glFinish)
{
    glFinish();
}

/**
 * glFlush 
 *  */
PHP_FUNCTION(glFlush)
{
    glFlush();
}

/**
 * glBlendFunc 
 *  */
PHP_FUNCTION(glBlendFunc)
{
    zend_long sfactor;
    zend_long dfactor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &sfactor, &dfactor) == FAILURE) {
       return;
    }
    glBlendFunc(sfactor, dfactor);
}

/**
 * glLogicOp 
 *  */
PHP_FUNCTION(glLogicOp)
{
    zend_long opcode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &opcode) == FAILURE) {
       return;
    }
    glLogicOp(opcode);
}

/**
 * glStencilFunc 
 *  */
PHP_FUNCTION(glStencilFunc)
{
    zend_long func;
    zend_long ref;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &func, &ref, &mask) == FAILURE) {
       return;
    }
    glStencilFunc(func, ref, mask);
}

/**
 * glStencilOp 
 *  */
PHP_FUNCTION(glStencilOp)
{
    zend_long fail;
    zend_long zfail;
    zend_long zpass;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &fail, &zfail, &zpass) == FAILURE) {
       return;
    }
    glStencilOp(fail, zfail, zpass);
}

/**
 * glDepthFunc 
 *  */
PHP_FUNCTION(glDepthFunc)
{
    zend_long func;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &func) == FAILURE) {
       return;
    }
    glDepthFunc(func);
}

/**
 * glPixelStoref 
 *  */
PHP_FUNCTION(glPixelStoref)
{
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &pname, &param) == FAILURE) {
       return;
    }
    glPixelStoref(pname, param);
}

/**
 * glPixelStorei 
 *  */
PHP_FUNCTION(glPixelStorei)
{
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &pname, &param) == FAILURE) {
       return;
    }
    glPixelStorei(pname, param);
}

/**
 * glReadBuffer 
 *  */
PHP_FUNCTION(glReadBuffer)
{
    zend_long src;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &src) == FAILURE) {
       return;
    }
    glReadBuffer(src);
}

/**
 * glGetError 
 *  */
PHP_FUNCTION(glGetError)
{
    RETURN_LONG(glGetError());
}

/**
 * glIsEnabled 
 *  */
PHP_FUNCTION(glIsEnabled)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsEnabled(cap));
}

/**
 * glDepthRange 
 *  */
PHP_FUNCTION(glDepthRange)
{
    double n;
    double f;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &n, &f) == FAILURE) {
       return;
    }
    glDepthRange(n, f);
}

/**
 * glViewport 
 *  */
PHP_FUNCTION(glViewport)
{
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &x, &y, &width, &height) == FAILURE) {
       return;
    }
    glViewport(x, y, width, height);
}

/**
 * glDrawArrays 
 *  */
PHP_FUNCTION(glDrawArrays)
{
    zend_long mode;
    zend_long first;
    zend_long count;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &mode, &first, &count) == FAILURE) {
       return;
    }
    glDrawArrays(mode, first, count);
}

/**
 * glPolygonOffset 
 *  */
PHP_FUNCTION(glPolygonOffset)
{
    double factor;
    double units;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &factor, &units) == FAILURE) {
       return;
    }
    glPolygonOffset(factor, units);
}

/**
 * glCopyTexImage1D 
 *  */
PHP_FUNCTION(glCopyTexImage1D)
{
    zend_long target;
    zend_long level;
    zend_long internalformat;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long border;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllllll", &target, &level, &internalformat, &x, &y, &width, &border) == FAILURE) {
       return;
    }
    glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}

/**
 * glCopyTexImage2D 
 *  */
PHP_FUNCTION(glCopyTexImage2D)
{
    zend_long target;
    zend_long level;
    zend_long internalformat;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    zend_long border;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllll", &target, &level, &internalformat, &x, &y, &width, &height, &border) == FAILURE) {
       return;
    }
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

/**
 * glCopyTexSubImage1D 
 *  */
PHP_FUNCTION(glCopyTexSubImage1D)
{
    zend_long target;
    zend_long level;
    zend_long xoffset;
    zend_long x;
    zend_long y;
    zend_long width;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllll", &target, &level, &xoffset, &x, &y, &width) == FAILURE) {
       return;
    }
    glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

/**
 * glCopyTexSubImage2D 
 *  */
PHP_FUNCTION(glCopyTexSubImage2D)
{
    zend_long target;
    zend_long level;
    zend_long xoffset;
    zend_long yoffset;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllll", &target, &level, &xoffset, &yoffset, &x, &y, &width, &height) == FAILURE) {
       return;
    }
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

/**
 * glBindTexture 
 *  */
PHP_FUNCTION(glBindTexture)
{
    zend_long target;
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &texture) == FAILURE) {
       return;
    }
    glBindTexture(target, texture);
}

/**
 * glIsTexture 
 *  */
PHP_FUNCTION(glIsTexture)
{
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &texture) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsTexture(texture));
}

/**
 * glCopyTexSubImage3D 
 *  */
PHP_FUNCTION(glCopyTexSubImage3D)
{
    zend_long target;
    zend_long level;
    zend_long xoffset;
    zend_long yoffset;
    zend_long zoffset;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllllllll", &target, &level, &xoffset, &yoffset, &zoffset, &x, &y, &width, &height) == FAILURE) {
       return;
    }
    glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

/**
 * glActiveTexture 
 *  */
PHP_FUNCTION(glActiveTexture)
{
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &texture) == FAILURE) {
       return;
    }
    glActiveTexture(texture);
}

/**
 * glSampleCoverage 
 *  */
PHP_FUNCTION(glSampleCoverage)
{
    double value;
    bool invert;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "db", &value, &invert) == FAILURE) {
       return;
    }
    glSampleCoverage(value, invert);
}

/**
 * glBlendFuncSeparate 
 *  */
PHP_FUNCTION(glBlendFuncSeparate)
{
    zend_long sfactorRGB;
    zend_long dfactorRGB;
    zend_long sfactorAlpha;
    zend_long dfactorAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &sfactorRGB, &dfactorRGB, &sfactorAlpha, &dfactorAlpha) == FAILURE) {
       return;
    }
    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

/**
 * glPointParameterf 
 *  */
PHP_FUNCTION(glPointParameterf)
{
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &pname, &param) == FAILURE) {
       return;
    }
    glPointParameterf(pname, param);
}

/**
 * glPointParameteri 
 *  */
PHP_FUNCTION(glPointParameteri)
{
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &pname, &param) == FAILURE) {
       return;
    }
    glPointParameteri(pname, param);
}

/**
 * glBlendColor 
 *  */
PHP_FUNCTION(glBlendColor)
{
    double red;
    double green;
    double blue;
    double alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &red, &green, &blue, &alpha) == FAILURE) {
       return;
    }
    glBlendColor(red, green, blue, alpha);
}

/**
 * glBlendEquation 
 *  */
PHP_FUNCTION(glBlendEquation)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
       return;
    }
    glBlendEquation(mode);
}

/**
 * glIsQuery 
 *  */
PHP_FUNCTION(glIsQuery)
{
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &id) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsQuery(id));
}

/**
 * glBeginQuery 
 *  */
PHP_FUNCTION(glBeginQuery)
{
    zend_long target;
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &id) == FAILURE) {
       return;
    }
    glBeginQuery(target, id);
}

/**
 * glEndQuery 
 *  */
PHP_FUNCTION(glEndQuery)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
       return;
    }
    glEndQuery(target);
}

/**
 * glBindBuffer 
 *  */
PHP_FUNCTION(glBindBuffer)
{
    zend_long target;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &buffer) == FAILURE) {
       return;
    }
    glBindBuffer(target, buffer);
}

/**
 * glIsBuffer 
 *  */
PHP_FUNCTION(glIsBuffer)
{
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &buffer) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsBuffer(buffer));
}

/**
 * glUnmapBuffer 
 *  */
PHP_FUNCTION(glUnmapBuffer)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
       return;
    }
    RETURN_BOOL(glUnmapBuffer(target));
}

/**
 * glBlendEquationSeparate 
 *  */
PHP_FUNCTION(glBlendEquationSeparate)
{
    zend_long modeRGB;
    zend_long modeAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &modeRGB, &modeAlpha) == FAILURE) {
       return;
    }
    glBlendEquationSeparate(modeRGB, modeAlpha);
}

/**
 * glStencilOpSeparate 
 *  */
PHP_FUNCTION(glStencilOpSeparate)
{
    zend_long face;
    zend_long sfail;
    zend_long dpfail;
    zend_long dppass;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &face, &sfail, &dpfail, &dppass) == FAILURE) {
       return;
    }
    glStencilOpSeparate(face, sfail, dpfail, dppass);
}

/**
 * glStencilFuncSeparate 
 *  */
PHP_FUNCTION(glStencilFuncSeparate)
{
    zend_long face;
    zend_long func;
    zend_long ref;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &face, &func, &ref, &mask) == FAILURE) {
       return;
    }
    glStencilFuncSeparate(face, func, ref, mask);
}

/**
 * glStencilMaskSeparate 
 *  */
PHP_FUNCTION(glStencilMaskSeparate)
{
    zend_long face;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &face, &mask) == FAILURE) {
       return;
    }
    glStencilMaskSeparate(face, mask);
}

/**
 * glAttachShader 
 *  */
PHP_FUNCTION(glAttachShader)
{
    zend_long program;
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &program, &shader) == FAILURE) {
       return;
    }
    glAttachShader(program, shader);
}

/**
 * glCompileShader 
 *  */
PHP_FUNCTION(glCompileShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shader) == FAILURE) {
       return;
    }
    glCompileShader(shader);
}

/**
 * glCreateProgram 
 *  */
PHP_FUNCTION(glCreateProgram)
{
    RETURN_LONG(glCreateProgram());
}

/**
 * glCreateShader 
 *  */
PHP_FUNCTION(glCreateShader)
{
    zend_long type;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &type) == FAILURE) {
       return;
    }
    RETURN_LONG(glCreateShader(type));
}

/**
 * glDeleteProgram 
 *  */
PHP_FUNCTION(glDeleteProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
       return;
    }
    glDeleteProgram(program);
}

/**
 * glDeleteShader 
 *  */
PHP_FUNCTION(glDeleteShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shader) == FAILURE) {
       return;
    }
    glDeleteShader(shader);
}

/**
 * glDetachShader 
 *  */
PHP_FUNCTION(glDetachShader)
{
    zend_long program;
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &program, &shader) == FAILURE) {
       return;
    }
    glDetachShader(program, shader);
}

/**
 * glDisableVertexAttribArray 
 *  */
PHP_FUNCTION(glDisableVertexAttribArray)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) == FAILURE) {
       return;
    }
    glDisableVertexAttribArray(index);
}

/**
 * glEnableVertexAttribArray 
 *  */
PHP_FUNCTION(glEnableVertexAttribArray)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) == FAILURE) {
       return;
    }
    glEnableVertexAttribArray(index);
}

/**
 * glIsProgram 
 *  */
PHP_FUNCTION(glIsProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsProgram(program));
}

/**
 * glIsShader 
 *  */
PHP_FUNCTION(glIsShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shader) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsShader(shader));
}

/**
 * glLinkProgram 
 *  */
PHP_FUNCTION(glLinkProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
       return;
    }
    glLinkProgram(program);
}

/**
 * glUseProgram 
 *  */
PHP_FUNCTION(glUseProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
       return;
    }
    glUseProgram(program);
}

/**
 * glUniform1f 
 *  */
PHP_FUNCTION(glUniform1f)
{
    zend_long location;
    double v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &location, &v0) == FAILURE) {
       return;
    }
    glUniform1f(location, v0);
}

/**
 * glUniform2f 
 *  */
PHP_FUNCTION(glUniform2f)
{
    zend_long location;
    double v0;
    double v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &location, &v0, &v1) == FAILURE) {
       return;
    }
    glUniform2f(location, v0, v1);
}

/**
 * glUniform3f 
 *  */
PHP_FUNCTION(glUniform3f)
{
    zend_long location;
    double v0;
    double v1;
    double v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &location, &v0, &v1, &v2) == FAILURE) {
       return;
    }
    glUniform3f(location, v0, v1, v2);
}

/**
 * glUniform4f 
 *  */
PHP_FUNCTION(glUniform4f)
{
    zend_long location;
    double v0;
    double v1;
    double v2;
    double v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &location, &v0, &v1, &v2, &v3) == FAILURE) {
       return;
    }
    glUniform4f(location, v0, v1, v2, v3);
}

/**
 * glUniform1i 
 *  */
PHP_FUNCTION(glUniform1i)
{
    zend_long location;
    zend_long v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &location, &v0) == FAILURE) {
       return;
    }
    glUniform1i(location, v0);
}

/**
 * glUniform2i 
 *  */
PHP_FUNCTION(glUniform2i)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &location, &v0, &v1) == FAILURE) {
       return;
    }
    glUniform2i(location, v0, v1);
}

/**
 * glUniform3i 
 *  */
PHP_FUNCTION(glUniform3i)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &location, &v0, &v1, &v2) == FAILURE) {
       return;
    }
    glUniform3i(location, v0, v1, v2);
}

/**
 * glUniform4i 
 *  */
PHP_FUNCTION(glUniform4i)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    zend_long v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &location, &v0, &v1, &v2, &v3) == FAILURE) {
       return;
    }
    glUniform4i(location, v0, v1, v2, v3);
}

/**
 * glValidateProgram 
 *  */
PHP_FUNCTION(glValidateProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
       return;
    }
    glValidateProgram(program);
}

/**
 * glVertexAttrib1d 
 *  */
PHP_FUNCTION(glVertexAttrib1d)
{
    zend_long index;
    double x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &index, &x) == FAILURE) {
       return;
    }
    glVertexAttrib1d(index, x);
}

/**
 * glVertexAttrib1f 
 *  */
PHP_FUNCTION(glVertexAttrib1f)
{
    zend_long index;
    double x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &index, &x) == FAILURE) {
       return;
    }
    glVertexAttrib1f(index, x);
}

/**
 * glVertexAttrib1s 
 *  */
PHP_FUNCTION(glVertexAttrib1s)
{
    zend_long index;
    zend_long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &x) == FAILURE) {
       return;
    }
    glVertexAttrib1s(index, x);
}

/**
 * glVertexAttrib2d 
 *  */
PHP_FUNCTION(glVertexAttrib2d)
{
    zend_long index;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &index, &x, &y) == FAILURE) {
       return;
    }
    glVertexAttrib2d(index, x, y);
}

/**
 * glVertexAttrib2f 
 *  */
PHP_FUNCTION(glVertexAttrib2f)
{
    zend_long index;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &index, &x, &y) == FAILURE) {
       return;
    }
    glVertexAttrib2f(index, x, y);
}

/**
 * glVertexAttrib2s 
 *  */
PHP_FUNCTION(glVertexAttrib2s)
{
    zend_long index;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &index, &x, &y) == FAILURE) {
       return;
    }
    glVertexAttrib2s(index, x, y);
}

/**
 * glVertexAttrib3d 
 *  */
PHP_FUNCTION(glVertexAttrib3d)
{
    zend_long index;
    double x;
    double y;
    double z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &index, &x, &y, &z) == FAILURE) {
       return;
    }
    glVertexAttrib3d(index, x, y, z);
}

/**
 * glVertexAttrib3f 
 *  */
PHP_FUNCTION(glVertexAttrib3f)
{
    zend_long index;
    double x;
    double y;
    double z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &index, &x, &y, &z) == FAILURE) {
       return;
    }
    glVertexAttrib3f(index, x, y, z);
}

/**
 * glVertexAttrib3s 
 *  */
PHP_FUNCTION(glVertexAttrib3s)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &index, &x, &y, &z) == FAILURE) {
       return;
    }
    glVertexAttrib3s(index, x, y, z);
}

/**
 * glVertexAttrib4Nub 
 *  */
PHP_FUNCTION(glVertexAttrib4Nub)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
       return;
    }
    glVertexAttrib4Nub(index, x, y, z, w);
}

/**
 * glVertexAttrib4d 
 *  */
PHP_FUNCTION(glVertexAttrib4d)
{
    zend_long index;
    double x;
    double y;
    double z;
    double w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &index, &x, &y, &z, &w) == FAILURE) {
       return;
    }
    glVertexAttrib4d(index, x, y, z, w);
}

/**
 * glVertexAttrib4f 
 *  */
PHP_FUNCTION(glVertexAttrib4f)
{
    zend_long index;
    double x;
    double y;
    double z;
    double w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &index, &x, &y, &z, &w) == FAILURE) {
       return;
    }
    glVertexAttrib4f(index, x, y, z, w);
}

/**
 * glVertexAttrib4s 
 *  */
PHP_FUNCTION(glVertexAttrib4s)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
       return;
    }
    glVertexAttrib4s(index, x, y, z, w);
}

/**
 * glColorMaski 
 *  */
PHP_FUNCTION(glColorMaski)
{
    zend_long index;
    bool r;
    bool g;
    bool b;
    bool a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbbbb", &index, &r, &g, &b, &a) == FAILURE) {
       return;
    }
    glColorMaski(index, r, g, b, a);
}

/**
 * glEnablei 
 *  */
PHP_FUNCTION(glEnablei)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
       return;
    }
    glEnablei(target, index);
}

/**
 * glDisablei 
 *  */
PHP_FUNCTION(glDisablei)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
       return;
    }
    glDisablei(target, index);
}

/**
 * glIsEnabledi 
 *  */
PHP_FUNCTION(glIsEnabledi)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsEnabledi(target, index));
}

/**
 * glBeginTransformFeedback 
 *  */
PHP_FUNCTION(glBeginTransformFeedback)
{
    zend_long primitiveMode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &primitiveMode) == FAILURE) {
       return;
    }
    glBeginTransformFeedback(primitiveMode);
}

/**
 * glEndTransformFeedback 
 *  */
PHP_FUNCTION(glEndTransformFeedback)
{
    glEndTransformFeedback();
}

/**
 * glBindBufferRange 
 *  */
PHP_FUNCTION(glBindBufferRange)
{
    zend_long target;
    zend_long index;
    zend_long buffer;
    zend_long offset;
    zend_long size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &index, &buffer, &offset, &size) == FAILURE) {
       return;
    }
    glBindBufferRange(target, index, buffer, offset, size);
}

/**
 * glBindBufferBase 
 *  */
PHP_FUNCTION(glBindBufferBase)
{
    zend_long target;
    zend_long index;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &index, &buffer) == FAILURE) {
       return;
    }
    glBindBufferBase(target, index, buffer);
}

/**
 * glClampColor 
 *  */
PHP_FUNCTION(glClampColor)
{
    zend_long target;
    zend_long clamp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &clamp) == FAILURE) {
       return;
    }
    glClampColor(target, clamp);
}

/**
 * glBeginConditionalRender 
 *  */
PHP_FUNCTION(glBeginConditionalRender)
{
    zend_long id;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &id, &mode) == FAILURE) {
       return;
    }
    glBeginConditionalRender(id, mode);
}

/**
 * glEndConditionalRender 
 *  */
PHP_FUNCTION(glEndConditionalRender)
{
    glEndConditionalRender();
}

/**
 * glVertexAttribI1i 
 *  */
PHP_FUNCTION(glVertexAttribI1i)
{
    zend_long index;
    zend_long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &x) == FAILURE) {
       return;
    }
    glVertexAttribI1i(index, x);
}

/**
 * glVertexAttribI2i 
 *  */
PHP_FUNCTION(glVertexAttribI2i)
{
    zend_long index;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &index, &x, &y) == FAILURE) {
       return;
    }
    glVertexAttribI2i(index, x, y);
}

/**
 * glVertexAttribI3i 
 *  */
PHP_FUNCTION(glVertexAttribI3i)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &index, &x, &y, &z) == FAILURE) {
       return;
    }
    glVertexAttribI3i(index, x, y, z);
}

/**
 * glVertexAttribI4i 
 *  */
PHP_FUNCTION(glVertexAttribI4i)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
       return;
    }
    glVertexAttribI4i(index, x, y, z, w);
}

/**
 * glVertexAttribI1ui 
 *  */
PHP_FUNCTION(glVertexAttribI1ui)
{
    zend_long index;
    zend_long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &x) == FAILURE) {
       return;
    }
    glVertexAttribI1ui(index, x);
}

/**
 * glVertexAttribI2ui 
 *  */
PHP_FUNCTION(glVertexAttribI2ui)
{
    zend_long index;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &index, &x, &y) == FAILURE) {
       return;
    }
    glVertexAttribI2ui(index, x, y);
}

/**
 * glVertexAttribI3ui 
 *  */
PHP_FUNCTION(glVertexAttribI3ui)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &index, &x, &y, &z) == FAILURE) {
       return;
    }
    glVertexAttribI3ui(index, x, y, z);
}

/**
 * glVertexAttribI4ui 
 *  */
PHP_FUNCTION(glVertexAttribI4ui)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
       return;
    }
    glVertexAttribI4ui(index, x, y, z, w);
}

/**
 * glUniform1ui 
 *  */
PHP_FUNCTION(glUniform1ui)
{
    zend_long location;
    zend_long v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &location, &v0) == FAILURE) {
       return;
    }
    glUniform1ui(location, v0);
}

/**
 * glUniform2ui 
 *  */
PHP_FUNCTION(glUniform2ui)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &location, &v0, &v1) == FAILURE) {
       return;
    }
    glUniform2ui(location, v0, v1);
}

/**
 * glUniform3ui 
 *  */
PHP_FUNCTION(glUniform3ui)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &location, &v0, &v1, &v2) == FAILURE) {
       return;
    }
    glUniform3ui(location, v0, v1, v2);
}

/**
 * glUniform4ui 
 *  */
PHP_FUNCTION(glUniform4ui)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    zend_long v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &location, &v0, &v1, &v2, &v3) == FAILURE) {
       return;
    }
    glUniform4ui(location, v0, v1, v2, v3);
}

/**
 * glClearBufferfi 
 *  */
PHP_FUNCTION(glClearBufferfi)
{
    zend_long buffer;
    zend_long drawbuffer;
    double depth;
    zend_long stencil;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lldl", &buffer, &drawbuffer, &depth, &stencil) == FAILURE) {
       return;
    }
    glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

/**
 * glIsRenderbuffer 
 *  */
PHP_FUNCTION(glIsRenderbuffer)
{
    zend_long renderbuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &renderbuffer) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsRenderbuffer(renderbuffer));
}

/**
 * glBindRenderbuffer 
 *  */
PHP_FUNCTION(glBindRenderbuffer)
{
    zend_long target;
    zend_long renderbuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &renderbuffer) == FAILURE) {
       return;
    }
    glBindRenderbuffer(target, renderbuffer);
}

/**
 * glRenderbufferStorage 
 *  */
PHP_FUNCTION(glRenderbufferStorage)
{
    zend_long target;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &target, &internalformat, &width, &height) == FAILURE) {
       return;
    }
    glRenderbufferStorage(target, internalformat, width, height);
}

/**
 * glIsFramebuffer 
 *  */
PHP_FUNCTION(glIsFramebuffer)
{
    zend_long framebuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &framebuffer) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsFramebuffer(framebuffer));
}

/**
 * glBindFramebuffer 
 *  */
PHP_FUNCTION(glBindFramebuffer)
{
    zend_long target;
    zend_long framebuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &framebuffer) == FAILURE) {
       return;
    }
    glBindFramebuffer(target, framebuffer);
}

/**
 * glCheckFramebufferStatus 
 *  */
PHP_FUNCTION(glCheckFramebufferStatus)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
       return;
    }
    RETURN_LONG(glCheckFramebufferStatus(target));
}

/**
 * glFramebufferTexture1D 
 *  */
PHP_FUNCTION(glFramebufferTexture1D)
{
    zend_long target;
    zend_long attachment;
    zend_long textarget;
    zend_long texture;
    zend_long level;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &attachment, &textarget, &texture, &level) == FAILURE) {
       return;
    }
    glFramebufferTexture1D(target, attachment, textarget, texture, level);
}

/**
 * glFramebufferTexture2D 
 *  */
PHP_FUNCTION(glFramebufferTexture2D)
{
    zend_long target;
    zend_long attachment;
    zend_long textarget;
    zend_long texture;
    zend_long level;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &attachment, &textarget, &texture, &level) == FAILURE) {
       return;
    }
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

/**
 * glFramebufferTexture3D 
 *  */
PHP_FUNCTION(glFramebufferTexture3D)
{
    zend_long target;
    zend_long attachment;
    zend_long textarget;
    zend_long texture;
    zend_long level;
    zend_long zoffset;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllll", &target, &attachment, &textarget, &texture, &level, &zoffset) == FAILURE) {
       return;
    }
    glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}

/**
 * glFramebufferRenderbuffer 
 *  */
PHP_FUNCTION(glFramebufferRenderbuffer)
{
    zend_long target;
    zend_long attachment;
    zend_long renderbuffertarget;
    zend_long renderbuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &target, &attachment, &renderbuffertarget, &renderbuffer) == FAILURE) {
       return;
    }
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

/**
 * glGenerateMipmap 
 *  */
PHP_FUNCTION(glGenerateMipmap)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
       return;
    }
    glGenerateMipmap(target);
}

/**
 * glBlitFramebuffer 
 *  */
PHP_FUNCTION(glBlitFramebuffer)
{
    zend_long srcX0;
    zend_long srcY0;
    zend_long srcX1;
    zend_long srcY1;
    zend_long dstX0;
    zend_long dstY0;
    zend_long dstX1;
    zend_long dstY1;
    zend_long mask;
    zend_long filter;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllllll", &srcX0, &srcY0, &srcX1, &srcY1, &dstX0, &dstY0, &dstX1, &dstY1, &mask, &filter) == FAILURE) {
       return;
    }
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

/**
 * glRenderbufferStorageMultisample 
 *  */
PHP_FUNCTION(glRenderbufferStorageMultisample)
{
    zend_long target;
    zend_long samples;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &samples, &internalformat, &width, &height) == FAILURE) {
       return;
    }
    glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

/**
 * glFramebufferTextureLayer 
 *  */
PHP_FUNCTION(glFramebufferTextureLayer)
{
    zend_long target;
    zend_long attachment;
    zend_long texture;
    zend_long level;
    zend_long layer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &attachment, &texture, &level, &layer) == FAILURE) {
       return;
    }
    glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

/**
 * glFlushMappedBufferRange 
 *  */
PHP_FUNCTION(glFlushMappedBufferRange)
{
    zend_long target;
    zend_long offset;
    zend_long length;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &offset, &length) == FAILURE) {
       return;
    }
    glFlushMappedBufferRange(target, offset, length);
}

/**
 * glBindVertexArray 
 *  */
PHP_FUNCTION(glBindVertexArray)
{
    zend_long array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &array) == FAILURE) {
       return;
    }
    glBindVertexArray(array);
}

/**
 * glIsVertexArray 
 *  */
PHP_FUNCTION(glIsVertexArray)
{
    zend_long array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &array) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsVertexArray(array));
}

/**
 * glDrawArraysInstanced 
 *  */
PHP_FUNCTION(glDrawArraysInstanced)
{
    zend_long mode;
    zend_long first;
    zend_long count;
    zend_long instancecount;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &mode, &first, &count, &instancecount) == FAILURE) {
       return;
    }
    glDrawArraysInstanced(mode, first, count, instancecount);
}

/**
 * glTexBuffer 
 *  */
PHP_FUNCTION(glTexBuffer)
{
    zend_long target;
    zend_long internalformat;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &internalformat, &buffer) == FAILURE) {
       return;
    }
    glTexBuffer(target, internalformat, buffer);
}

/**
 * glPrimitiveRestartIndex 
 *  */
PHP_FUNCTION(glPrimitiveRestartIndex)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) == FAILURE) {
       return;
    }
    glPrimitiveRestartIndex(index);
}

/**
 * glCopyBufferSubData 
 *  */
PHP_FUNCTION(glCopyBufferSubData)
{
    zend_long readTarget;
    zend_long writeTarget;
    zend_long readOffset;
    zend_long writeOffset;
    zend_long size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &readTarget, &writeTarget, &readOffset, &writeOffset, &size) == FAILURE) {
       return;
    }
    glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

/**
 * glUniformBlockBinding 
 *  */
PHP_FUNCTION(glUniformBlockBinding)
{
    zend_long program;
    zend_long uniformBlockIndex;
    zend_long uniformBlockBinding;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &program, &uniformBlockIndex, &uniformBlockBinding) == FAILURE) {
       return;
    }
    glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

/**
 * glProvokingVertex 
 *  */
PHP_FUNCTION(glProvokingVertex)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
       return;
    }
    glProvokingVertex(mode);
}

/**
 * glFenceSync 
 *  */
PHP_FUNCTION(glFenceSync)
{
    zend_long condition;
    zend_long flags;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &condition, &flags) == FAILURE) {
       return;
    }
    RETURN_LONG(glFenceSync(condition, flags));
}

/**
 * glIsSync 
 *  */
PHP_FUNCTION(glIsSync)
{
    zend_long sync;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &sync) == FAILURE) {
       return;
    }
    RETURN_BOOL(glIsSync(sync));
}

/**
 * glDeleteSync 
 *  */
PHP_FUNCTION(glDeleteSync)
{
    zend_long sync;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &sync) == FAILURE) {
       return;
    }
    glDeleteSync(sync);
}

/**
 * glClientWaitSync 
 *  */
PHP_FUNCTION(glClientWaitSync)
{
    zend_long sync;
    zend_long flags;
    zend_long timeout;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &sync, &flags, &timeout) == FAILURE) {
       return;
    }
    RETURN_LONG(glClientWaitSync(sync, flags, timeout));
}

/**
 * glWaitSync 
 *  */
PHP_FUNCTION(glWaitSync)
{
    zend_long sync;
    zend_long flags;
    zend_long timeout;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &sync, &flags, &timeout) == FAILURE) {
       return;
    }
    glWaitSync(sync, flags, timeout);
}

/**
 * glFramebufferTexture 
 *  */
PHP_FUNCTION(glFramebufferTexture)
{
    zend_long target;
    zend_long attachment;
    zend_long texture;
    zend_long level;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &target, &attachment, &texture, &level) == FAILURE) {
       return;
    }
    glFramebufferTexture(target, attachment, texture, level);
}

/**
 * glTexImage2DMultisample 
 *  */
PHP_FUNCTION(glTexImage2DMultisample)
{
    zend_long target;
    zend_long samples;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    bool fixedsamplelocations;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllllb", &target, &samples, &internalformat, &width, &height, &fixedsamplelocations) == FAILURE) {
       return;
    }
    glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

/**
 * glTexImage3DMultisample 
 *  */
PHP_FUNCTION(glTexImage3DMultisample)
{
    zend_long target;
    zend_long samples;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    zend_long depth;
    bool fixedsamplelocations;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllb", &target, &samples, &internalformat, &width, &height, &depth, &fixedsamplelocations) == FAILURE) {
       return;
    }
    glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

/**
 * glSampleMaski 
 *  */
PHP_FUNCTION(glSampleMaski)
{
    zend_long maskNumber;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &maskNumber, &mask) == FAILURE) {
       return;
    }
    glSampleMaski(maskNumber, mask);
}

/**
 * glfwInit 
 *  */
PHP_FUNCTION(glfwInit)
{
    RETURN_LONG(glfwInit());
}

/**
 * glfwTerminate 
 *  */
PHP_FUNCTION(glfwTerminate)
{
    glfwTerminate();
}

/**
 * glfwDefaultWindowHints 
 *  */
PHP_FUNCTION(glfwDefaultWindowHints)
{
    glfwDefaultWindowHints();
}

/**
 * glfwPollEvents 
 *  */
PHP_FUNCTION(glfwPollEvents)
{
    glfwPollEvents();
}

/**
 * glfwWaitEvents 
 *  */
PHP_FUNCTION(glfwWaitEvents)
{
    glfwWaitEvents();
}

/**
 * glfwPostEmptyEvent 
 *  */
PHP_FUNCTION(glfwPostEmptyEvent)
{
    glfwPostEmptyEvent();
}

/**
 * glfwRawMouseMotionSupported 
 *  */
PHP_FUNCTION(glfwRawMouseMotionSupported)
{
    RETURN_LONG(glfwRawMouseMotionSupported());
}

/**
 * glfwGetTime 
 *  */
PHP_FUNCTION(glfwGetTime)
{
    RETURN_DOUBLE(glfwGetTime());
}

/**
 * glfwVulkanSupported 
 *  */
PHP_FUNCTION(glfwVulkanSupported)
{
    RETURN_LONG(glfwVulkanSupported());
}

