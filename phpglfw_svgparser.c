/**
 * PHP-glfw
 *
 * Extension: SVG file parser (nanosvg)
 *
 * Copyright (c) 2018-2024 Mario Döring
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
// nanosvg keeps its implementation inside the NANOSVG_H include guard, so the
// NANOSVG_IMPLEMENTATION define must be set BEFORE nanosvg.h is first pulled in
// (which happens transitively through phpglfw_svgparser.h). This is the single
// translation unit that compiles the implementation.
//
// nanosvg uses libc malloc/free internally. The parsed NSVGimage is a one-shot
// allocation freed in the object destructor via nsvgDelete(), so it does not
// participate in PHP's request memory management.
#define NANOSVG_IMPLEMENTATION
#include "phpglfw_svgparser.h"
#include "phpglfw_arginfo.h"
#include "php_streams.h"

zend_class_entry *phpglfw_svgimage_ce;

zend_class_entry *phpglfw_get_vg_svgimage_ce() {
    return phpglfw_svgimage_ce;
}

phpglfw_svgimage_object* phpglfw_svgimage_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_svgimage_object *) ((char *) (obj) - XtOffsetOf(phpglfw_svgimage_object, std));
}

static zend_object_handlers phpglfw_svgimage_handlers;

zend_object *phpglfw_svgimage_create_handler(zend_class_entry *class_type)
{
    phpglfw_svgimage_object *intern = zend_object_alloc(sizeof(phpglfw_svgimage_object), class_type);

    intern->image = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_svgimage_handlers;

    return &intern->std;
}

static void phpglfw_svgimage_free_handler(zend_object *object)
{
    phpglfw_svgimage_object *intern = phpglfw_svgimage_objectptr_from_zobj_p(object);

    if (intern->image != NULL) {
        nsvgDelete(intern->image);
        intern->image = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

static HashTable *phpglfw_svgimage_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_svgimage_object *intern = phpglfw_svgimage_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, intern->image != NULL ? intern->image->width : 0.0);
    zend_hash_str_update(ht, "width", sizeof("width") - 1, &zv);

    ZVAL_DOUBLE(&zv, intern->image != NULL ? intern->image->height : 0.0);
    zend_hash_str_update(ht, "height", sizeof("height") - 1, &zv);

    return ht;
}

static zval *phpglfw_svgimage_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv)
{
    phpglfw_svgimage_object *intern = phpglfw_svgimage_objectptr_from_zobj_p(object);

    if (zend_string_equals_literal(member, "width")) {
        ZVAL_DOUBLE(rv, intern->image != NULL ? intern->image->width : 0.0);
        return rv;
    }
    else if (zend_string_equals_literal(member, "height")) {
        ZVAL_DOUBLE(rv, intern->image != NULL ? intern->image->height : 0.0);
        return rv;
    }

    return zend_std_read_property(object, member, type, cache_slot, rv);
}

static int phpglfw_svgimage_has_prop_handler(zend_object *object, zend_string *member, int has_set_exists, void **cache_slot)
{
    phpglfw_svgimage_object *intern = phpglfw_svgimage_objectptr_from_zobj_p(object);

    // width & height are native-backed readonly props; report them set whenever
    // an image has been parsed so isset() reflects the read_property hook.
    if (zend_string_equals_literal(member, "width") || zend_string_equals_literal(member, "height")) {
        return intern->image != NULL;
    }

    return zend_std_has_property(object, member, has_set_exists, cache_slot);
}

/**
 * SVGImage::fromDisk(string $path) : SVGImage
 */
PHP_METHOD(GL_VectorGraphics_SVGImage, fromDisk)
{
    char *path;
    size_t path_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "p", &path, &path_size) == FAILURE) {
        RETURN_THROWS();
    }

    // load through the PHP stream layer so open_basedir and stream wrappers are
    // honoured, then reuse the buffer-based parse path (same as fromString).
    php_stream *stream = php_stream_open_wrapper_ex(path, "rb", REPORT_ERRORS, NULL, NULL);
    if (!stream) {
        zend_throw_error(NULL, "Could not open the SVG file at '%s'.", path);
        return;
    }

    zend_string *buffer = php_stream_copy_to_mem(stream, PHP_STREAM_COPY_ALL, 0);
    php_stream_close(stream);
    if (!buffer) {
        zend_throw_error(NULL, "Could not read the SVG file at '%s'.", path);
        return;
    }

    // nsvgParse mutates its (null-terminated) input buffer; the zend_string from
    // php_stream_copy_to_mem is a private, writable copy we own.
    NSVGimage *image = nsvgParse(ZSTR_VAL(buffer), "px", 96.0f);
    zend_string_release(buffer);

    if (image == NULL) {
        zend_throw_error(NULL, "Could not parse the SVG file at '%s'. The file might be malformed.", path);
        return;
    }

    object_init_ex(return_value, phpglfw_get_vg_svgimage_ce());
    phpglfw_svgimage_object *intern = phpglfw_svgimage_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    intern->image = image;
}

/**
 * SVGImage::fromString(string $svg) : SVGImage
 */
PHP_METHOD(GL_VectorGraphics_SVGImage, fromString)
{
    const char *svg;
    size_t svg_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &svg, &svg_size) == FAILURE) {
        RETURN_THROWS();
    }

    // nsvgParse mutates its input buffer, so we hand it a private copy.
    char *buffer = estrndup(svg, svg_size);
    NSVGimage *image = nsvgParse(buffer, "px", 96.0f);
    efree(buffer);

    if (image == NULL) {
        zend_throw_error(NULL, "Could not parse the given SVG string. The markup might be malformed.");
        return;
    }

    object_init_ex(return_value, phpglfw_get_vg_svgimage_ce());
    phpglfw_svgimage_object *intern = phpglfw_svgimage_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    intern->image = image;
}

void phpglfw_register_svgparser_module(INIT_FUNC_ARGS)
{
    phpglfw_svgimage_ce = register_class_GL_VectorGraphics_SVGImage();
    phpglfw_svgimage_ce->create_object = phpglfw_svgimage_create_handler;

    memcpy(&phpglfw_svgimage_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpglfw_svgimage_handlers.offset = XtOffsetOf(phpglfw_svgimage_object, std);
    phpglfw_svgimage_handlers.free_obj = phpglfw_svgimage_free_handler;
    phpglfw_svgimage_handlers.get_debug_info = phpglfw_svgimage_debug_info_handler;
    phpglfw_svgimage_handlers.read_property = phpglfw_svgimage_read_prop_handler;
    phpglfw_svgimage_handlers.has_property = phpglfw_svgimage_has_prop_handler;
}
