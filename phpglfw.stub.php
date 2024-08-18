<?php 

/** 
 * @generate-function-entries
 * ##generate-class-entries
 */

namespace GL\Geometry
{
    class ObjFileParser
    {   
        public readonly array $materials;
        public readonly array $groups;
        public readonly array $objects;

        /**
         * Obj. file parser constructor.
         * IMPORTANT: This obj. file parser does ONLY support triangulated meshes!
         */
        public function __construct(string $file) {}
        public function getVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Buffer\FloatBuffer {}
        public function getIndexedVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Geometry\ObjFileParser\Mesh {}
        public function getMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}
        public function getIndexedMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}
    }
}

namespace GL\Geometry\ObjFileParser
{
    class Resource {}

    class Mesh {
        public readonly ?Material $material;
        public readonly FloatBuffer $vertices;
        public readonly ?UIntBuffer $indices;
        public readonly ?\GL\Buffer\Vec3 $aabbMin;
        public readonly ?\GL\Buffer\Vec3 $aabbMax;
    }

    class Material
    {
        public readonly string $name;
        public function __construct() {}
    }

    class Group
    {
        public readonly string $name;
        public function __construct() {}
    }

    class Texture
    {
        public function __construct() {}
    }
}

namespace GL\Texture
{
    class Texture2D {
        // public const CHANNEL_R = 1;
        // public const CHANNEL_GRAY = 1;
        // public const CHANNEL_RG = 2;
        // public const CHANNEL_GRAY_ALPHA = 2;
        // public const CHANNEL_RGB = 3;
        // public const CHANNEL_RGBA = 4;

        public static function fromDisk(string $path, int $requestedChannelCount = 0, bool $flipVertically = true) : Texture2D {}
        public static function fromBuffer(int $width, int $height, \GL\Buffer\UByteBuffer $buffer, int $channels = Texture2D::CHANNEL_RGBA) : Texture2D {} 
        public function buffer() : \GL\Buffer\UByteBuffer {}
        public function width() : int {}
        public function height() : int {}
        public function channels() : int {}

        public function writeJPG(string $path, int $quality = 100) : void {}
        public function writePNG(string $path) : void {}
        public function writeBMP(string $path) : void {}
        public function writeTGA(string $path) : void {}
    }
}

namespace GL
{
    class Noise {
        public static function perlin(float $x, float $y, float $z, int $wrapX = 0, int $wrapY = 0, int $wrapZ = 0, int $seed = 0) : float {}
        public static function ridge(float $x, float $y, float $z, float $lacunarity = 2.0, float $gain = 0.5, float $offset = 1.0, int $octaves = 6) : float {}
        public static function fbm(float $x, float $y, float $z, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : float {}
        public static function turbulence(float $x, float $y, float $z, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : float {}

        public static function perlinFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, int $wrapX = 0, int $wrapY = 0, int $seed = 0) : void {}
        public static function ridgeFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, float $lacunarity = 2.0, float $gain = 0.5, float $offset = 1.0, int $octaves = 6) : void {}
        public static function fbmFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : void {}
        public static function turbulenceFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : void {}
        public static function islandFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, int $islandseed = 42, float $scale = 1.0, float $islandmix = 0.7, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : void {}
    }
}

namespace GL\Math 
{
    class GLM {
        public static function radians(float $degrees) : float {}
        public static function angle(float $radians) : float {}
        public static function triangleNormal(Vec3 $p1, Vec3 $p2, Vec3 $p3) : Vec3 {}
        public static function normalize(Vec2|Vec3|Vec4 $vec) : Vec2|Vec3|Vec4 {}
    }

 
    class Vec2 {
        public function __construct(?float $x = null, ?float $y = null) {}
        public function copy() : Vec2 {}
        // static
        public static function normalized(Vec2 $vec) : Vec2 {}
        public static function distance(Vec2 $left, Vec2 $right) : float {}
        public static function distance2(Vec2 $left, Vec2 $right) : float {}
        public static function dot(Vec2 $left, Vec2 $right) : float {}
        public static function mix(Vec2 $left, Vec2 $right, float $t) : Vec2 {}
        public static function lerp(Vec2 $left, Vec2 $right, float $t) : Vec2 {}
        public static function slerp(Vec2 $left, Vec2 $right, float $t) : Vec2 {}

        // member function
        public function length() : float {}
        public function distanceTo(Vec2 $right) : float {}
        public function distance2To(Vec2 $right) : float {}
        public function normalize() : void {}
        public function abs() : void {}
        public function __toString() : string {}
    }
 
    class Vec3 {
        public function __construct(?float $x = null, ?float $y = null, ?float $z = null) {}
        public function copy() : Vec3 {}
        // static
        public static function normalized(Vec3 $vec) : Vec3 {}
        public static function distance(Vec3 $left, Vec3 $right) : float {}
        public static function distance2(Vec3 $left, Vec3 $right) : float {}
        public static function dot(Vec3 $left, Vec3 $right) : float {}
        public static function mix(Vec3 $left, Vec3 $right, float $t) : Vec3 {}
        public static function lerp(Vec3 $left, Vec3 $right, float $t) : Vec3 {}
        public static function slerp(Vec3 $left, Vec3 $right, float $t) : Vec3 {}

        // member function
        public function length() : float {}
        public function distanceTo(Vec3 $right) : float {}
        public function distance2To(Vec3 $right) : float {}
        public function normalize() : void {}
        public function abs() : void {}
        public static function cross(Vec3 $left, Vec3 $right) : Vec3 {}
        public static function multiplyQuat(Vec3 $left, Quat $right) : Vec3 {}
        public function __toString() : string {}
    }
 
    class Vec4 {
        public function __construct(?float $x = null, ?float $y = null, ?float $z = null, ?float $w = null) {}
        public function copy() : Vec4 {}
        // static
        public static function normalized(Vec4 $vec) : Vec4 {}
        public static function distance(Vec4 $left, Vec4 $right) : float {}
        public static function distance2(Vec4 $left, Vec4 $right) : float {}
        public static function dot(Vec4 $left, Vec4 $right) : float {}
        public static function mix(Vec4 $left, Vec4 $right, float $t) : Vec4 {}
        public static function lerp(Vec4 $left, Vec4 $right, float $t) : Vec4 {}
        public static function slerp(Vec4 $left, Vec4 $right, float $t) : Vec4 {}

        // member function
        public function length() : float {}
        public function distanceTo(Vec4 $right) : float {}
        public function distance2To(Vec4 $right) : float {}
        public function normalize() : void {}
        public function abs() : void {}
        public function __toString() : string {}
    }
 
    class Quat {
        public function __construct(?float $w = null, ?float $x = null, ?float $y = null, ?float $z = null) {}
        public function copy() : Quat {}
        public static function fromMat4(Mat4 $matrix) : Quat {}
        public static function fromVec4(Vec4 $vec) : Quat {}
        public static function inverted(Quat $quat) : Quat {}
        public static function normalized(Quat $quat) : Quat {} 
        public static function mix(Quat $left, Quat $right, float $t) : Quat {}
        public static function lerp(Quat $left, Quat $right, float $t) : Quat {}
        public static function slerp(Quat $left, Quat $right, float $t) : Quat {}
        public static function dot(Quat $left, Quat $right) : float {}
        public static function multiply(Quat $left, Quat $right) : Quat {}
        public static function multiplyVec3(Quat $quat, Vec3 $vec) : Vec3 {}
        public static function multiplyMat4(Quat $quat, Mat4 $mat) : Mat4 {}
        public function normalize() : void {}
        public function length() : float {}
        public function eulerAngles() : Vec3 {}
        public function rotate(float $angle, Vec3 $axis) : void {}
        public function inverse() : void {}
        public function mat4() : Mat4 {}
        public function __toString() : string {}
    }
 
    class Mat4 {
        public function __construct() {}
        public function copy() : Mat4 {}
        public static function fromArray(array $values) : Mat4 {}
        public static function inverted(Mat4 $matrix) : Mat4 {}
        public static function multiplyQuat(Mat4 $left, Quat $right) : Mat4 {}
        public function row(int $index) : Vec4 {}
        public function setRow(int $index, Vec4 $row) : void {}
        public function col(int $index) : Vec4 {}
        public function setCol(int $index, Vec4 $col) : void {}
        public function lookAt(Vec3 $eye, Vec3 $center, Vec3 $up) : void {}
        public function perspective(float $fov, float $aspect, float $near, float $far) : void {}
        public function ortho(float $left, float $right, float $bottom, float $top, float $near, float $far) : void {}
        public function transpose() : void {}
        public function inverse() : void {}
        public function scale(Vec3 $scale) : void {}
        public function translate(Vec3 $translation) : void {}
        public function rotate(float $angle, Vec3 $axis) : void {}
        public function determinant() : float {}
        public function __toString() : string {}
    }
};

namespace GL\Buffer 
{   
    interface BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
    }

    class FloatBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(float $value) : void {}
        public function pushArray(array $values) : void {}
        public function pushVec2(GL\Math\Vec2 $vec) : void {}
        public function pushVec3(GL\Math\Vec3 $vec) : void {}
        public function pushVec4(GL\Math\Vec4 $vec) : void {}
        public function pushMat4(GL\Math\Mat4 $matrix) : void {}
        public function quantizeToUChar(bool $autoNormalize = true, float $lowerBound = 0.0, float $upperBound = 1.0) : \GL\Buffer\UByteBuffer {}
        public function fill(int $count, float $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class HFloatBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class DoubleBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(float $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, float $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class IntBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class UIntBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class ShortBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class UShortBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class ByteBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }

    class UByteBuffer implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(int $value) : void {}
        public function pushArray(array $values) : void {}
        public function pushString(string $str) : void {}
        public function fill(int $count, int $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
        public function dump() : string {}
    }
};

namespace GL\VectorGraphics
{
    class VGColor {
        public static function rgb(float $r, float $g, float $b) : VGColor {}
        public static function rgba(float $r, float $g, float $b, float $a) : VGColor {}
        public static function hsl(float $h, float $s, float $l) : VGColor {}
        public static function hsla(float $h, float $s, float $l, float $a) : VGColor {}
        public static function irgb(int $r, int $g, int $b) : VGColor {}
        public static function irgba(int $r, int $g, int $b, int $a) : VGColor {}
        //public static function fromVec4(\GL\Math\Vec4 $vec) : VGColor {}
        //public static function fromVec3(\GL\Math\Vec3 $vec) : VGColor {}

        public static function hex(string $hex) : VGColor {}

        public static function red() : VGColor {}
        public static function green() : VGColor {}
        public static function blue() : VGColor {}
        public static function white() : VGColor {}
        public static function black() : VGColor {}
        public static function transparent() : VGColor {}
        public static function yellow() : VGColor {}
        public static function cyan() : VGColor {}
        public static function magenta() : VGColor {}
        public static function orange() : VGColor {}
        public static function pink() : VGColor {}
        public static function purple() : VGColor {}
        public static function brown() : VGColor {}
        public static function gray() : VGColor {}
        public static function darkGray() : VGColor {}
        public static function lightGray() : VGColor {}
        public static function random() : VGColor {}
        public static function randomGray() : VGColor {}

        public float $r;
        public float $g;
        public float $b;
        public float $a;

        public function __construct(float $r, float $g, float $b, float $a) {}

        public function getHSLA() : \GL\Math\Vec4 {}
        public function getHSL() : \GL\Math\Vec3 {}
        public function getVec4() : \GL\Math\Vec4 {}
        public function getVec3() : \GL\Math\Vec3 {}

        public function darken(float $amount) : VGColor {}
        public function lighten(float $amount) : VGColor {}
        public function invert() : VGColor {}
    }
    
    class VGPaint {
        //public static function fromImage(VGImage $image, float $cx, float $cy, float $w, float $h, float $angle, float $alpha = 1.0) : VGPaint {}
    }

    class VGImage {
        // public const REPEAT_NONE = 0;
        // public const REPEAT_X = 1;
        // public const REPEAT_Y = 2;
        // public const REPEAT_XY = 3;

        // public const FILTER_LINEAR = 0;
        // public const FILTER_NEAREST = 1;

        public function makePaint(float $x, float $y, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : VGPaint {}
        public function makePaintCentered(float $cx, float $cy, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : VGPaint {}
        //public function makePaintAABB(float $minx, float $miny, float $maxx, float $maxy, float $angle = 0.0, float $alpha = 1.0) : VGPaint {}
    }

    class VGAlign {
        // public const LEFT = 1;
        // public const CENTER = 2;
        // public const RIGHT = 4;
        // public const TOP = 8;
        // public const MIDDLE = 16;
        // public const BOTTOM = 32;
        // public const BASELINE = 64;
    }

    class VGContext {
        // public const ANTIALIAS = 1;
        // public const STENCIL_STROKES = 2;
        // public const DEBUG = 4;

        // public const CCW = 1;
        // public const CW = 2;

        // public const SOLID = 1;
        // public const HOLE = 2;

        // public const LINECAP_BUTT = 0;
        // public const LINECAP_ROUND = 1;
        // public const LINECAP_SQUARE = 2;
        // public const LINEJOIN_BEVEL = 3;
        // public const LINEJOIN_MITER = 4;

        public function __construct(int $flags = 0) {}
        public function fillColori(int $r, int $g, int $b, int $a) : void {}
        public function strokeColori(int $r, int $g, int $b, int $a) : void {}
        public function fillColorVec4(\GL\Math\Vec4 $vec) : void {}
        public function strokeColorVec4(\GL\Math\Vec4 $vec) : void {}
        public function transformPoint(float $x, float $y) : \GL\Math\Vec2 {}
        public function transformVec2(\GL\Math\Vec2 $vec) : \GL\Math\Vec2 {}

        public function imageFromTexture(
            \GL\Texture\Texture2D $texture,
            int $repeatMode = VGImage::REPEAT_NONE,
            int $filterMode = VGImage::FILTER_LINEAR
        ) : VGImage {}

        public function imageFromHandle(
            int $handle,
            int $width,
            int $height,
            int $repeatMode = VGImage::REPEAT_NONE,
            int $filterMode = VGImage::FILTER_LINEAR
        ) : VGImage {}

        public function linearGradient(float $sx, float $sy, float $ex, float $ey, VGColor $icol, VGColor $ocol) : VGPaint {}
        public function boxGradient(float $x, float $y, float $w, float $h, float $r, float $f, VGColor $icol, VGColor $ocol) : VGPaint {}
        public function radialGradient(float $cx, float $cy, float $inr, float $outr, VGColor $icol, VGColor $ocol) : VGPaint {}
        //public function imagePattern(float $cx, float $cy, float $w, float $h, float $angle, float $alpha) : VGPaint {}

        public function beginFrame(float $windowWidth, float $windowHeight, float $devicePixelRatio) : void {}
        public function cancelFrame() : void {}
        public function endFrame() : void {}
        public function globalCompositeOperation(int $op) : void {}
        public function globalCompositeBlendFunc(int $sfactor, int $dfactor) : void {}
        public function globalCompositeBlendFuncSeparate(int $srcRGB, int $dstRGB, int $srcAlpha, int $dstAlpha) : void {}
        public function save() : void {}
        public function restore() : void {}
        public function reset() : void {}
        public function shapeAntiAlias(int $enabled) : void {}
        public function strokeColor(\GL\VectorGraphics\VGColor $color) : void {}
        public function strokePaint(\GL\VectorGraphics\VGPaint $paint) : void {}
        public function fillColor(\GL\VectorGraphics\VGColor $color) : void {}
        public function fillPaint(\GL\VectorGraphics\VGPaint $paint) : void {}
        public function miterLimit(float $limit) : void {}
        public function strokeWidth(float $size) : void {}
        public function lineCap(int $cap) : void {}
        public function lineJoin(int $join) : void {}
        public function globalAlpha(float $alpha) : void {}
        public function resetTransform() : void {}
        public function transform(float $a, float $b, float $c, float $d, float $e, float $f) : void {}
        public function translate(float $x, float $y) : void {}
        public function rotate(float $angle) : void {}
        public function skewX(float $angle) : void {}
        public function skewY(float $angle) : void {}
        public function scale(float $x, float $y) : void {}
        public function currentTransform(\GL\Buffer\FloatBuffer $buffer) : void {}
        public function transformPointCurrent(float &$dstx, float &$dsty, float $srcx, float $srcy) : void {}
        public function imageSize(int $image, int &$w, int &$h) : void {}
        public function deleteImage(int $image) : void {}
        public function scissor(float $x, float $y, float $w, float $h) : void {}
        public function intersectScissor(float $x, float $y, float $w, float $h) : void {}
        public function resetScissor() : void {}
        public function beginPath() : void {}
        public function moveTo(float $x, float $y) : void {}
        public function lineTo(float $x, float $y) : void {}
        public function bezierTo(float $c1x, float $c1y, float $c2x, float $c2y, float $x, float $y) : void {}
        public function quadTo(float $cx, float $cy, float $x, float $y) : void {}
        public function arcTo(float $x1, float $y1, float $x2, float $y2, float $radius) : void {}
        public function closePath() : void {}
        public function pathWinding(int $dir) : void {}
        public function arc(float $cx, float $cy, float $r, float $a0, float $a1, int $dir) : void {}
        public function rect(float $x, float $y, float $w, float $h) : void {}
        public function roundedRect(float $x, float $y, float $w, float $h, float $r) : void {}
        public function roundedRectVarying(float $x, float $y, float $w, float $h, float $radTopLeft, float $radTopRight, float $radBottomRight, float $radBottomLeft) : void {}
        public function ellipse(float $cx, float $cy, float $rx, float $ry) : void {}
        public function circle(float $cx, float $cy, float $r) : void {}
        public function fill() : void {}
        public function stroke() : void {}
        public function createFont(string $name, string $filename) : int {}
        public function createFontAtIndex(string $name, string $filename, int $fontIndex) : int {}
        public function findFont(string $name) : int {}
        public function addFallbackFontId(int $baseFont, int $fallbackFont) : int {}
        public function addFallbackFont(string $baseFont, string $fallbackFont) : int {}
        public function resetFallbackFontsId(int $baseFont) : void {}
        public function resetFallbackFonts(string $baseFont) : void {}
        public function fontSize(float $size) : void {}
        public function fontBlur(float $blur) : void {}
        public function textLetterSpacing(float $spacing) : void {}
        public function textLineHeight(float $lineHeight) : void {}
        public function textAlign(int $align) : void {}
        public function fontFaceId(int $font) : void {}
        public function fontFace(string $font) : void {}
        public function text(float $x, float $y, string $string) : float {}
        public function textBox(float $x, float $y, float $breakRowWidth, string $string) : void {}
        public function textBounds(float $x, float $y, string $string, ?\GL\Math\Vec4 &$bounds = NULL) : float {}
        public function textBoxBounds(float $x, float $y, float $breakRowWidth, string $string, ?\GL\Math\Vec4 &$bounds = NULL) : void {}
        public function textMetrics(float &$ascender, float &$descender, float &$lineh) : void {}
        public function deleteInternal() : void {}
        public function debugDumpPathCache() : void {}
 
    }
};

namespace {
    /**
     * Constants
     * ----------------------------------------------------------------------------
     */
    // const PHPGLFW_COMPILED_API = 'gl';
    // const PHPGLFW_COMPILED_API_VERSION = '4.1';
    // const GL_SIZEOF_BYTE = 1;
    // const GL_SIZEOF_UNSIGNED_BYTE = 1;
    // const GL_SIZEOF_SHORT = 2;
    // const GL_SIZEOF_UNSIGNED_SHORT = 2;
    // const GL_SIZEOF_INT = 4;
    // const GL_SIZEOF_UNSIGNED_INT = 4;
    // const GL_SIZEOF_FLOAT = 4;
    // const GL_SIZEOF_HALF_FLOAT = 2;
    // const GL_SIZEOF_DOUBLE = 8;
    // const GL_DEPTH_BUFFER_BIT = 0x00000100;
    // const GL_STENCIL_BUFFER_BIT = 0x00000400;
    // const GL_COLOR_BUFFER_BIT = 0x00004000;
    // const GL_CURRENT_BIT = 0x00000001;
    // const GL_POINT_BIT = 0x00000002;
    // const GL_LINE_BIT = 0x00000004;
    // const GL_POLYGON_BIT = 0x00000008;
    // const GL_POLYGON_STIPPLE_BIT = 0x00000010;
    // const GL_PIXEL_MODE_BIT = 0x00000020;
    // const GL_LIGHTING_BIT = 0x00000040;
    // const GL_FOG_BIT = 0x00000080;
    // const GL_ACCUM_BUFFER_BIT = 0x00000200;
    // const GL_VIEWPORT_BIT = 0x00000800;
    // const GL_TRANSFORM_BIT = 0x00001000;
    // const GL_ENABLE_BIT = 0x00002000;
    // const GL_HINT_BIT = 0x00008000;
    // const GL_EVAL_BIT = 0x00010000;
    // const GL_LIST_BIT = 0x00020000;
    // const GL_TEXTURE_BIT = 0x00040000;
    // const GL_SCISSOR_BIT = 0x00080000;
    // const GL_ALL_ATTRIB_BITS = 0xFFFFFFFF;
    // const GL_MULTISAMPLE_BIT = 0x20000000;
    // const GL_FALSE = false;
    // const GL_TRUE = true;
    // const GL_ZERO = GL_ZERO;
    // const GL_ONE = 1;
    // const GL_NONE = GL_NONE;
    // const GL_NO_ERROR = GL_NO_ERROR;
    // const GL_INVALID_INDEX = 0xFFFFFFFF;
    // const GL_TIMEOUT_IGNORED = 0xFFFFFFFFFFFFFFFF;
    // const GL_POINTS = 0x0000;
    // const GL_LINES = 0x0001;
    // const GL_LINE_LOOP = 0x0002;
    // const GL_LINE_STRIP = 0x0003;
    // const GL_TRIANGLES = 0x0004;
    // const GL_TRIANGLE_STRIP = 0x0005;
    // const GL_TRIANGLE_FAN = 0x0006;
    // const GL_QUADS = 0x0007;
    // const GL_NEVER = 0x0200;
    // const GL_LESS = 0x0201;
    // const GL_EQUAL = 0x0202;
    // const GL_LEQUAL = 0x0203;
    // const GL_GREATER = 0x0204;
    // const GL_NOTEQUAL = 0x0205;
    // const GL_GEQUAL = 0x0206;
    // const GL_ALWAYS = 0x0207;
    // const GL_SRC_COLOR = 0x0300;
    // const GL_ONE_MINUS_SRC_COLOR = 0x0301;
    // const GL_SRC_ALPHA = 0x0302;
    // const GL_ONE_MINUS_SRC_ALPHA = 0x0303;
    // const GL_DST_ALPHA = 0x0304;
    // const GL_ONE_MINUS_DST_ALPHA = 0x0305;
    // const GL_DST_COLOR = 0x0306;
    // const GL_ONE_MINUS_DST_COLOR = 0x0307;
    // const GL_SRC_ALPHA_SATURATE = 0x0308;
    // const GL_FRONT_LEFT = 0x0400;
    // const GL_FRONT_RIGHT = 0x0401;
    // const GL_BACK_LEFT = 0x0402;
    // const GL_BACK_RIGHT = 0x0403;
    // const GL_FRONT = 0x0404;
    // const GL_BACK = 0x0405;
    // const GL_LEFT = 0x0406;
    // const GL_RIGHT = 0x0407;
    // const GL_FRONT_AND_BACK = 0x0408;
    // const GL_INVALID_ENUM = 0x0500;
    // const GL_INVALID_VALUE = 0x0501;
    // const GL_INVALID_OPERATION = 0x0502;
    // const GL_OUT_OF_MEMORY = 0x0505;
    // const GL_CW = 0x0900;
    // const GL_CCW = 0x0901;
    // const GL_POINT_SIZE = 0x0B11;
    // const GL_POINT_SIZE_RANGE = 0x0B12;
    // const GL_POINT_SIZE_GRANULARITY = 0x0B13;
    // const GL_LINE_SMOOTH = 0x0B20;
    // const GL_LINE_WIDTH = 0x0B21;
    // const GL_LINE_WIDTH_RANGE = 0x0B22;
    // const GL_LINE_WIDTH_GRANULARITY = 0x0B23;
    // const GL_POLYGON_MODE = 0x0B40;
    // const GL_POLYGON_SMOOTH = 0x0B41;
    // const GL_CULL_FACE = 0x0B44;
    // const GL_CULL_FACE_MODE = 0x0B45;
    // const GL_FRONT_FACE = 0x0B46;
    // const GL_DEPTH_RANGE = 0x0B70;
    // const GL_DEPTH_TEST = 0x0B71;
    // const GL_DEPTH_WRITEMASK = 0x0B72;
    // const GL_DEPTH_CLEAR_VALUE = 0x0B73;
    // const GL_DEPTH_FUNC = 0x0B74;
    // const GL_STENCIL_TEST = 0x0B90;
    // const GL_STENCIL_CLEAR_VALUE = 0x0B91;
    // const GL_STENCIL_FUNC = 0x0B92;
    // const GL_STENCIL_VALUE_MASK = 0x0B93;
    // const GL_STENCIL_FAIL = 0x0B94;
    // const GL_STENCIL_PASS_DEPTH_FAIL = 0x0B95;
    // const GL_STENCIL_PASS_DEPTH_PASS = 0x0B96;
    // const GL_STENCIL_REF = 0x0B97;
    // const GL_STENCIL_WRITEMASK = 0x0B98;
    // const GL_VIEWPORT = 0x0BA2;
    // const GL_DITHER = 0x0BD0;
    // const GL_BLEND_DST = 0x0BE0;
    // const GL_BLEND_SRC = 0x0BE1;
    // const GL_BLEND = 0x0BE2;
    // const GL_LOGIC_OP_MODE = 0x0BF0;
    // const GL_DRAW_BUFFER = 0x0C01;
    // const GL_READ_BUFFER = 0x0C02;
    // const GL_SCISSOR_BOX = 0x0C10;
    // const GL_SCISSOR_TEST = 0x0C11;
    // const GL_COLOR_CLEAR_VALUE = 0x0C22;
    // const GL_COLOR_WRITEMASK = 0x0C23;
    // const GL_DOUBLEBUFFER = 0x0C32;
    // const GL_STEREO = 0x0C33;
    // const GL_LINE_SMOOTH_HINT = 0x0C52;
    // const GL_POLYGON_SMOOTH_HINT = 0x0C53;
    // const GL_UNPACK_SWAP_BYTES = 0x0CF0;
    // const GL_UNPACK_LSB_FIRST = 0x0CF1;
    // const GL_UNPACK_ROW_LENGTH = 0x0CF2;
    // const GL_UNPACK_SKIP_ROWS = 0x0CF3;
    // const GL_UNPACK_SKIP_PIXELS = 0x0CF4;
    // const GL_UNPACK_ALIGNMENT = 0x0CF5;
    // const GL_PACK_SWAP_BYTES = 0x0D00;
    // const GL_PACK_LSB_FIRST = 0x0D01;
    // const GL_PACK_ROW_LENGTH = 0x0D02;
    // const GL_PACK_SKIP_ROWS = 0x0D03;
    // const GL_PACK_SKIP_PIXELS = 0x0D04;
    // const GL_PACK_ALIGNMENT = 0x0D05;
    // const GL_MAX_TEXTURE_SIZE = 0x0D33;
    // const GL_MAX_VIEWPORT_DIMS = 0x0D3A;
    // const GL_SUBPIXEL_BITS = 0x0D50;
    // const GL_TEXTURE_1D = 0x0DE0;
    // const GL_TEXTURE_2D = 0x0DE1;
    // const GL_TEXTURE_WIDTH = 0x1000;
    // const GL_TEXTURE_HEIGHT = 0x1001;
    // const GL_TEXTURE_BORDER_COLOR = 0x1004;
    // const GL_DONT_CARE = 0x1100;
    // const GL_FASTEST = 0x1101;
    // const GL_NICEST = 0x1102;
    // const GL_BYTE = 0x1400;
    // const GL_UNSIGNED_BYTE = 0x1401;
    // const GL_SHORT = 0x1402;
    // const GL_UNSIGNED_SHORT = 0x1403;
    // const GL_INT = 0x1404;
    // const GL_UNSIGNED_INT = 0x1405;
    // const GL_FLOAT = 0x1406;
    // const GL_STACK_OVERFLOW = 0x0503;
    // const GL_STACK_UNDERFLOW = 0x0504;
    // const GL_CLEAR = 0x1500;
    // const GL_AND = 0x1501;
    // const GL_AND_REVERSE = 0x1502;
    // const GL_COPY = 0x1503;
    // const GL_AND_INVERTED = 0x1504;
    // const GL_NOOP = 0x1505;
    // const GL_XOR = 0x1506;
    // const GL_OR = 0x1507;
    // const GL_NOR = 0x1508;
    // const GL_EQUIV = 0x1509;
    // const GL_INVERT = 0x150A;
    // const GL_OR_REVERSE = 0x150B;
    // const GL_COPY_INVERTED = 0x150C;
    // const GL_OR_INVERTED = 0x150D;
    // const GL_NAND = 0x150E;
    // const GL_SET = 0x150F;
    // const GL_TEXTURE = 0x1702;
    // const GL_COLOR = 0x1800;
    // const GL_DEPTH = 0x1801;
    // const GL_STENCIL = 0x1802;
    // const GL_STENCIL_INDEX = 0x1901;
    // const GL_DEPTH_COMPONENT = 0x1902;
    // const GL_RED = 0x1903;
    // const GL_GREEN = 0x1904;
    // const GL_BLUE = 0x1905;
    // const GL_ALPHA = 0x1906;
    // const GL_RGB = 0x1907;
    // const GL_RGBA = 0x1908;
    // const GL_POINT = 0x1B00;
    // const GL_LINE = 0x1B01;
    // const GL_FILL = 0x1B02;
    // const GL_KEEP = 0x1E00;
    // const GL_REPLACE = 0x1E01;
    // const GL_INCR = 0x1E02;
    // const GL_DECR = 0x1E03;
    // const GL_VENDOR = 0x1F00;
    // const GL_RENDERER = 0x1F01;
    // const GL_VERSION = 0x1F02;
    // const GL_EXTENSIONS = 0x1F03;
    // const GL_NEAREST = 0x2600;
    // const GL_LINEAR = 0x2601;
    // const GL_NEAREST_MIPMAP_NEAREST = 0x2700;
    // const GL_LINEAR_MIPMAP_NEAREST = 0x2701;
    // const GL_NEAREST_MIPMAP_LINEAR = 0x2702;
    // const GL_LINEAR_MIPMAP_LINEAR = 0x2703;
    // const GL_TEXTURE_MAG_FILTER = 0x2800;
    // const GL_TEXTURE_MIN_FILTER = 0x2801;
    // const GL_TEXTURE_WRAP_S = 0x2802;
    // const GL_TEXTURE_WRAP_T = 0x2803;
    // const GL_REPEAT = 0x2901;
    // const GL_QUAD_STRIP = 0x0008;
    // const GL_POLYGON = 0x0009;
    // const GL_ACCUM = 0x0100;
    // const GL_LOAD = 0x0101;
    // const GL_RETURN = 0x0102;
    // const GL_MULT = 0x0103;
    // const GL_ADD = 0x0104;
    // const GL_AUX0 = 0x0409;
    // const GL_AUX1 = 0x040A;
    // const GL_AUX2 = 0x040B;
    // const GL_AUX3 = 0x040C;
    // const GL_2D = 0x0600;
    // const GL_3D = 0x0601;
    // const GL_3D_COLOR = 0x0602;
    // const GL_3D_COLOR_TEXTURE = 0x0603;
    // const GL_4D_COLOR_TEXTURE = 0x0604;
    // const GL_PASS_THROUGH_TOKEN = 0x0700;
    // const GL_POINT_TOKEN = 0x0701;
    // const GL_LINE_TOKEN = 0x0702;
    // const GL_POLYGON_TOKEN = 0x0703;
    // const GL_BITMAP_TOKEN = 0x0704;
    // const GL_DRAW_PIXEL_TOKEN = 0x0705;
    // const GL_COPY_PIXEL_TOKEN = 0x0706;
    // const GL_LINE_RESET_TOKEN = 0x0707;
    // const GL_EXP = 0x0800;
    // const GL_EXP2 = 0x0801;
    // const GL_COEFF = 0x0A00;
    // const GL_ORDER = 0x0A01;
    // const GL_DOMAIN = 0x0A02;
    // const GL_PIXEL_MAP_I_TO_I = 0x0C70;
    // const GL_PIXEL_MAP_S_TO_S = 0x0C71;
    // const GL_PIXEL_MAP_I_TO_R = 0x0C72;
    // const GL_PIXEL_MAP_I_TO_G = 0x0C73;
    // const GL_PIXEL_MAP_I_TO_B = 0x0C74;
    // const GL_PIXEL_MAP_I_TO_A = 0x0C75;
    // const GL_PIXEL_MAP_R_TO_R = 0x0C76;
    // const GL_PIXEL_MAP_G_TO_G = 0x0C77;
    // const GL_PIXEL_MAP_B_TO_B = 0x0C78;
    // const GL_PIXEL_MAP_A_TO_A = 0x0C79;
    // const GL_CURRENT_COLOR = 0x0B00;
    // const GL_CURRENT_INDEX = 0x0B01;
    // const GL_CURRENT_NORMAL = 0x0B02;
    // const GL_CURRENT_TEXTURE_COORDS = 0x0B03;
    // const GL_CURRENT_RASTER_COLOR = 0x0B04;
    // const GL_CURRENT_RASTER_INDEX = 0x0B05;
    // const GL_CURRENT_RASTER_TEXTURE_COORDS = 0x0B06;
    // const GL_CURRENT_RASTER_POSITION = 0x0B07;
    // const GL_CURRENT_RASTER_POSITION_VALID = 0x0B08;
    // const GL_CURRENT_RASTER_DISTANCE = 0x0B09;
    // const GL_POINT_SMOOTH = 0x0B10;
    // const GL_LINE_STIPPLE = 0x0B24;
    // const GL_LINE_STIPPLE_PATTERN = 0x0B25;
    // const GL_LINE_STIPPLE_REPEAT = 0x0B26;
    // const GL_LIST_MODE = 0x0B30;
    // const GL_MAX_LIST_NESTING = 0x0B31;
    // const GL_LIST_BASE = 0x0B32;
    // const GL_LIST_INDEX = 0x0B33;
    // const GL_POLYGON_STIPPLE = 0x0B42;
    // const GL_EDGE_FLAG = 0x0B43;
    // const GL_LIGHTING = 0x0B50;
    // const GL_LIGHT_MODEL_LOCAL_VIEWER = 0x0B51;
    // const GL_LIGHT_MODEL_TWO_SIDE = 0x0B52;
    // const GL_LIGHT_MODEL_AMBIENT = 0x0B53;
    // const GL_SHADE_MODEL = 0x0B54;
    // const GL_COLOR_MATERIAL_FACE = 0x0B55;
    // const GL_COLOR_MATERIAL_PARAMETER = 0x0B56;
    // const GL_COLOR_MATERIAL = 0x0B57;
    // const GL_FOG = 0x0B60;
    // const GL_FOG_INDEX = 0x0B61;
    // const GL_FOG_DENSITY = 0x0B62;
    // const GL_FOG_START = 0x0B63;
    // const GL_FOG_END = 0x0B64;
    // const GL_FOG_MODE = 0x0B65;
    // const GL_FOG_COLOR = 0x0B66;
    // const GL_ACCUM_CLEAR_VALUE = 0x0B80;
    // const GL_MATRIX_MODE = 0x0BA0;
    // const GL_NORMALIZE = 0x0BA1;
    // const GL_MODELVIEW_STACK_DEPTH = 0x0BA3;
    // const GL_PROJECTION_STACK_DEPTH = 0x0BA4;
    // const GL_TEXTURE_STACK_DEPTH = 0x0BA5;
    // const GL_MODELVIEW_MATRIX = 0x0BA6;
    // const GL_PROJECTION_MATRIX = 0x0BA7;
    // const GL_TEXTURE_MATRIX = 0x0BA8;
    // const GL_ATTRIB_STACK_DEPTH = 0x0BB0;
    // const GL_ALPHA_TEST = 0x0BC0;
    // const GL_ALPHA_TEST_FUNC = 0x0BC1;
    // const GL_ALPHA_TEST_REF = 0x0BC2;
    // const GL_LOGIC_OP = 0x0BF1;
    // const GL_AUX_BUFFERS = 0x0C00;
    // const GL_INDEX_CLEAR_VALUE = 0x0C20;
    // const GL_INDEX_WRITEMASK = 0x0C21;
    // const GL_INDEX_MODE = 0x0C30;
    // const GL_RGBA_MODE = 0x0C31;
    // const GL_RENDER_MODE = 0x0C40;
    // const GL_PERSPECTIVE_CORRECTION_HINT = 0x0C50;
    // const GL_POINT_SMOOTH_HINT = 0x0C51;
    // const GL_FOG_HINT = 0x0C54;
    // const GL_TEXTURE_GEN_S = 0x0C60;
    // const GL_TEXTURE_GEN_T = 0x0C61;
    // const GL_TEXTURE_GEN_R = 0x0C62;
    // const GL_TEXTURE_GEN_Q = 0x0C63;
    // const GL_PIXEL_MAP_I_TO_I_SIZE = 0x0CB0;
    // const GL_PIXEL_MAP_S_TO_S_SIZE = 0x0CB1;
    // const GL_PIXEL_MAP_I_TO_R_SIZE = 0x0CB2;
    // const GL_PIXEL_MAP_I_TO_G_SIZE = 0x0CB3;
    // const GL_PIXEL_MAP_I_TO_B_SIZE = 0x0CB4;
    // const GL_PIXEL_MAP_I_TO_A_SIZE = 0x0CB5;
    // const GL_PIXEL_MAP_R_TO_R_SIZE = 0x0CB6;
    // const GL_PIXEL_MAP_G_TO_G_SIZE = 0x0CB7;
    // const GL_PIXEL_MAP_B_TO_B_SIZE = 0x0CB8;
    // const GL_PIXEL_MAP_A_TO_A_SIZE = 0x0CB9;
    // const GL_MAP_COLOR = 0x0D10;
    // const GL_MAP_STENCIL = 0x0D11;
    // const GL_INDEX_SHIFT = 0x0D12;
    // const GL_INDEX_OFFSET = 0x0D13;
    // const GL_RED_SCALE = 0x0D14;
    // const GL_RED_BIAS = 0x0D15;
    // const GL_ZOOM_X = 0x0D16;
    // const GL_ZOOM_Y = 0x0D17;
    // const GL_GREEN_SCALE = 0x0D18;
    // const GL_GREEN_BIAS = 0x0D19;
    // const GL_BLUE_SCALE = 0x0D1A;
    // const GL_BLUE_BIAS = 0x0D1B;
    // const GL_ALPHA_SCALE = 0x0D1C;
    // const GL_ALPHA_BIAS = 0x0D1D;
    // const GL_DEPTH_SCALE = 0x0D1E;
    // const GL_DEPTH_BIAS = 0x0D1F;
    // const GL_MAX_EVAL_ORDER = 0x0D30;
    // const GL_MAX_LIGHTS = 0x0D31;
    // const GL_MAX_CLIP_PLANES = 0x0D32;
    // const GL_MAX_PIXEL_MAP_TABLE = 0x0D34;
    // const GL_MAX_ATTRIB_STACK_DEPTH = 0x0D35;
    // const GL_MAX_MODELVIEW_STACK_DEPTH = 0x0D36;
    // const GL_MAX_NAME_STACK_DEPTH = 0x0D37;
    // const GL_MAX_PROJECTION_STACK_DEPTH = 0x0D38;
    // const GL_MAX_TEXTURE_STACK_DEPTH = 0x0D39;
    // const GL_INDEX_BITS = 0x0D51;
    // const GL_RED_BITS = 0x0D52;
    // const GL_GREEN_BITS = 0x0D53;
    // const GL_BLUE_BITS = 0x0D54;
    // const GL_ALPHA_BITS = 0x0D55;
    // const GL_DEPTH_BITS = 0x0D56;
    // const GL_STENCIL_BITS = 0x0D57;
    // const GL_ACCUM_RED_BITS = 0x0D58;
    // const GL_ACCUM_GREEN_BITS = 0x0D59;
    // const GL_ACCUM_BLUE_BITS = 0x0D5A;
    // const GL_ACCUM_ALPHA_BITS = 0x0D5B;
    // const GL_NAME_STACK_DEPTH = 0x0D70;
    // const GL_AUTO_NORMAL = 0x0D80;
    // const GL_MAP1_COLOR_4 = 0x0D90;
    // const GL_MAP1_INDEX = 0x0D91;
    // const GL_MAP1_NORMAL = 0x0D92;
    // const GL_MAP1_TEXTURE_COORD_1 = 0x0D93;
    // const GL_MAP1_TEXTURE_COORD_2 = 0x0D94;
    // const GL_MAP1_TEXTURE_COORD_3 = 0x0D95;
    // const GL_MAP1_TEXTURE_COORD_4 = 0x0D96;
    // const GL_MAP1_VERTEX_3 = 0x0D97;
    // const GL_MAP1_VERTEX_4 = 0x0D98;
    // const GL_MAP2_COLOR_4 = 0x0DB0;
    // const GL_MAP2_INDEX = 0x0DB1;
    // const GL_MAP2_NORMAL = 0x0DB2;
    // const GL_MAP2_TEXTURE_COORD_1 = 0x0DB3;
    // const GL_MAP2_TEXTURE_COORD_2 = 0x0DB4;
    // const GL_MAP2_TEXTURE_COORD_3 = 0x0DB5;
    // const GL_MAP2_TEXTURE_COORD_4 = 0x0DB6;
    // const GL_MAP2_VERTEX_3 = 0x0DB7;
    // const GL_MAP2_VERTEX_4 = 0x0DB8;
    // const GL_MAP1_GRID_DOMAIN = 0x0DD0;
    // const GL_MAP1_GRID_SEGMENTS = 0x0DD1;
    // const GL_MAP2_GRID_DOMAIN = 0x0DD2;
    // const GL_MAP2_GRID_SEGMENTS = 0x0DD3;
    // const GL_TEXTURE_COMPONENTS = 0x1003;
    // const GL_TEXTURE_BORDER = 0x1005;
    // const GL_AMBIENT = 0x1200;
    // const GL_DIFFUSE = 0x1201;
    // const GL_SPECULAR = 0x1202;
    // const GL_POSITION = 0x1203;
    // const GL_SPOT_DIRECTION = 0x1204;
    // const GL_SPOT_EXPONENT = 0x1205;
    // const GL_SPOT_CUTOFF = 0x1206;
    // const GL_CONSTANT_ATTENUATION = 0x1207;
    // const GL_LINEAR_ATTENUATION = 0x1208;
    // const GL_QUADRATIC_ATTENUATION = 0x1209;
    // const GL_COMPILE = 0x1300;
    // const GL_COMPILE_AND_EXECUTE = 0x1301;
    // const GL_2_BYTES = 0x1407;
    // const GL_3_BYTES = 0x1408;
    // const GL_4_BYTES = 0x1409;
    // const GL_EMISSION = 0x1600;
    // const GL_SHININESS = 0x1601;
    // const GL_AMBIENT_AND_DIFFUSE = 0x1602;
    // const GL_COLOR_INDEXES = 0x1603;
    // const GL_MODELVIEW = 0x1700;
    // const GL_PROJECTION = 0x1701;
    // const GL_COLOR_INDEX = 0x1900;
    // const GL_LUMINANCE = 0x1909;
    // const GL_LUMINANCE_ALPHA = 0x190A;
    // const GL_BITMAP = 0x1A00;
    // const GL_RENDER = 0x1C00;
    // const GL_FEEDBACK = 0x1C01;
    // const GL_SELECT = 0x1C02;
    // const GL_FLAT = 0x1D00;
    // const GL_SMOOTH = 0x1D01;
    // const GL_S = 0x2000;
    // const GL_T = 0x2001;
    // const GL_R = 0x2002;
    // const GL_Q = 0x2003;
    // const GL_MODULATE = 0x2100;
    // const GL_DECAL = 0x2101;
    // const GL_TEXTURE_ENV_MODE = 0x2200;
    // const GL_TEXTURE_ENV_COLOR = 0x2201;
    // const GL_TEXTURE_ENV = 0x2300;
    // const GL_EYE_LINEAR = 0x2400;
    // const GL_OBJECT_LINEAR = 0x2401;
    // const GL_SPHERE_MAP = 0x2402;
    // const GL_TEXTURE_GEN_MODE = 0x2500;
    // const GL_OBJECT_PLANE = 0x2501;
    // const GL_EYE_PLANE = 0x2502;
    // const GL_CLAMP = 0x2900;
    // const GL_CLIP_PLANE0 = 0x3000;
    // const GL_CLIP_PLANE1 = 0x3001;
    // const GL_CLIP_PLANE2 = 0x3002;
    // const GL_CLIP_PLANE3 = 0x3003;
    // const GL_CLIP_PLANE4 = 0x3004;
    // const GL_CLIP_PLANE5 = 0x3005;
    // const GL_LIGHT0 = 0x4000;
    // const GL_LIGHT1 = 0x4001;
    // const GL_LIGHT2 = 0x4002;
    // const GL_LIGHT3 = 0x4003;
    // const GL_LIGHT4 = 0x4004;
    // const GL_LIGHT5 = 0x4005;
    // const GL_LIGHT6 = 0x4006;
    // const GL_LIGHT7 = 0x4007;
    // const GL_COLOR_LOGIC_OP = 0x0BF2;
    // const GL_POLYGON_OFFSET_UNITS = 0x2A00;
    // const GL_POLYGON_OFFSET_POINT = 0x2A01;
    // const GL_POLYGON_OFFSET_LINE = 0x2A02;
    // const GL_TEXTURE_INTERNAL_FORMAT = 0x1003;
    // const GL_DOUBLE = 0x140A;
    // const GL_R3_G3_B2 = 0x2A10;
    // const GL_FEEDBACK_BUFFER_POINTER = 0x0DF0;
    // const GL_SELECTION_BUFFER_POINTER = 0x0DF3;
    // const GL_CLIENT_ATTRIB_STACK_DEPTH = 0x0BB1;
    // const GL_INDEX_LOGIC_OP = 0x0BF1;
    // const GL_MAX_CLIENT_ATTRIB_STACK_DEPTH = 0x0D3B;
    // const GL_FEEDBACK_BUFFER_SIZE = 0x0DF1;
    // const GL_FEEDBACK_BUFFER_TYPE = 0x0DF2;
    // const GL_SELECTION_BUFFER_SIZE = 0x0DF4;
    // const GL_V2F = 0x2A20;
    // const GL_V3F = 0x2A21;
    // const GL_C4UB_V2F = 0x2A22;
    // const GL_C4UB_V3F = 0x2A23;
    // const GL_C3F_V3F = 0x2A24;
    // const GL_N3F_V3F = 0x2A25;
    // const GL_C4F_N3F_V3F = 0x2A26;
    // const GL_T2F_V3F = 0x2A27;
    // const GL_T4F_V4F = 0x2A28;
    // const GL_T2F_C4UB_V3F = 0x2A29;
    // const GL_T2F_C3F_V3F = 0x2A2A;
    // const GL_T2F_N3F_V3F = 0x2A2B;
    // const GL_T2F_C4F_N3F_V3F = 0x2A2C;
    // const GL_T4F_C4F_N3F_V4F = 0x2A2D;
    // const GL_SMOOTH_POINT_SIZE_RANGE = 0x0B12;
    // const GL_SMOOTH_POINT_SIZE_GRANULARITY = 0x0B13;
    // const GL_SMOOTH_LINE_WIDTH_RANGE = 0x0B22;
    // const GL_SMOOTH_LINE_WIDTH_GRANULARITY = 0x0B23;
    // const GL_CLIP_DISTANCE0 = 0x3000;
    // const GL_CLIP_DISTANCE1 = 0x3001;
    // const GL_CLIP_DISTANCE2 = 0x3002;
    // const GL_CLIP_DISTANCE3 = 0x3003;
    // const GL_CLIP_DISTANCE4 = 0x3004;
    // const GL_CLIP_DISTANCE5 = 0x3005;
    // const GL_CLIP_DISTANCE6 = 0x3006;
    // const GL_CLIP_DISTANCE7 = 0x3007;
    // const GL_MAX_CLIP_DISTANCES = 0x0D32;
    // const GL_INVALID_FRAMEBUFFER_OPERATION = 0x0506;
    // const GL_HALF_FLOAT = 0x140B;
    // const GL_LINES_ADJACENCY = 0x000A;
    // const GL_LINE_STRIP_ADJACENCY = 0x000B;
    // const GL_TRIANGLES_ADJACENCY = 0x000C;
    // const GL_TRIANGLE_STRIP_ADJACENCY = 0x000D;
    // const GL_PATCHES = 0x000E;
    // const GL_FIXED = 0x140C;
    // const GL_POLYGON_OFFSET_FILL = 0x8037;
    // const GL_POLYGON_OFFSET_FACTOR = 0x8038;
    // const GL_TEXTURE_BINDING_1D = 0x8068;
    // const GL_TEXTURE_BINDING_2D = 0x8069;
    // const GL_TEXTURE_RED_SIZE = 0x805C;
    // const GL_TEXTURE_GREEN_SIZE = 0x805D;
    // const GL_TEXTURE_BLUE_SIZE = 0x805E;
    // const GL_TEXTURE_ALPHA_SIZE = 0x805F;
    // const GL_PROXY_TEXTURE_1D = 0x8063;
    // const GL_PROXY_TEXTURE_2D = 0x8064;
    // const GL_RGB4 = 0x804F;
    // const GL_RGB5 = 0x8050;
    // const GL_RGB8 = 0x8051;
    // const GL_RGB10 = 0x8052;
    // const GL_RGB12 = 0x8053;
    // const GL_RGB16 = 0x8054;
    // const GL_RGBA2 = 0x8055;
    // const GL_RGBA4 = 0x8056;
    // const GL_RGB5_A1 = 0x8057;
    // const GL_RGBA8 = 0x8058;
    // const GL_RGB10_A2 = 0x8059;
    // const GL_RGBA12 = 0x805A;
    // const GL_RGBA16 = 0x805B;
    // const GL_VERTEX_ARRAY_POINTER = 0x808E;
    // const GL_NORMAL_ARRAY_POINTER = 0x808F;
    // const GL_COLOR_ARRAY_POINTER = 0x8090;
    // const GL_INDEX_ARRAY_POINTER = 0x8091;
    // const GL_TEXTURE_COORD_ARRAY_POINTER = 0x8092;
    // const GL_EDGE_FLAG_ARRAY_POINTER = 0x8093;
    // const GL_VERTEX_ARRAY = 0x8074;
    // const GL_NORMAL_ARRAY = 0x8075;
    // const GL_COLOR_ARRAY = 0x8076;
    // const GL_INDEX_ARRAY = 0x8077;
    // const GL_TEXTURE_COORD_ARRAY = 0x8078;
    // const GL_EDGE_FLAG_ARRAY = 0x8079;
    // const GL_VERTEX_ARRAY_SIZE = 0x807A;
    // const GL_VERTEX_ARRAY_TYPE = 0x807B;
    // const GL_VERTEX_ARRAY_STRIDE = 0x807C;
    // const GL_NORMAL_ARRAY_TYPE = 0x807E;
    // const GL_NORMAL_ARRAY_STRIDE = 0x807F;
    // const GL_COLOR_ARRAY_SIZE = 0x8081;
    // const GL_COLOR_ARRAY_TYPE = 0x8082;
    // const GL_COLOR_ARRAY_STRIDE = 0x8083;
    // const GL_INDEX_ARRAY_TYPE = 0x8085;
    // const GL_INDEX_ARRAY_STRIDE = 0x8086;
    // const GL_TEXTURE_COORD_ARRAY_SIZE = 0x8088;
    // const GL_TEXTURE_COORD_ARRAY_TYPE = 0x8089;
    // const GL_TEXTURE_COORD_ARRAY_STRIDE = 0x808A;
    // const GL_EDGE_FLAG_ARRAY_STRIDE = 0x808C;
    // const GL_TEXTURE_LUMINANCE_SIZE = 0x8060;
    // const GL_TEXTURE_INTENSITY_SIZE = 0x8061;
    // const GL_TEXTURE_PRIORITY = 0x8066;
    // const GL_TEXTURE_RESIDENT = 0x8067;
    // const GL_ALPHA4 = 0x803B;
    // const GL_ALPHA8 = 0x803C;
    // const GL_ALPHA12 = 0x803D;
    // const GL_ALPHA16 = 0x803E;
    // const GL_LUMINANCE4 = 0x803F;
    // const GL_LUMINANCE8 = 0x8040;
    // const GL_LUMINANCE12 = 0x8041;
    // const GL_LUMINANCE16 = 0x8042;
    // const GL_LUMINANCE4_ALPHA4 = 0x8043;
    // const GL_LUMINANCE6_ALPHA2 = 0x8044;
    // const GL_LUMINANCE8_ALPHA8 = 0x8045;
    // const GL_LUMINANCE12_ALPHA4 = 0x8046;
    // const GL_LUMINANCE12_ALPHA12 = 0x8047;
    // const GL_LUMINANCE16_ALPHA16 = 0x8048;
    // const GL_INTENSITY = 0x8049;
    // const GL_INTENSITY4 = 0x804A;
    // const GL_INTENSITY8 = 0x804B;
    // const GL_INTENSITY12 = 0x804C;
    // const GL_INTENSITY16 = 0x804D;
    // const GL_UNSIGNED_BYTE_3_3_2 = 0x8032;
    // const GL_UNSIGNED_SHORT_4_4_4_4 = 0x8033;
    // const GL_UNSIGNED_SHORT_5_5_5_1 = 0x8034;
    // const GL_UNSIGNED_INT_8_8_8_8 = 0x8035;
    // const GL_UNSIGNED_INT_10_10_10_2 = 0x8036;
    // const GL_TEXTURE_BINDING_3D = 0x806A;
    // const GL_PACK_SKIP_IMAGES = 0x806B;
    // const GL_PACK_IMAGE_HEIGHT = 0x806C;
    // const GL_UNPACK_SKIP_IMAGES = 0x806D;
    // const GL_UNPACK_IMAGE_HEIGHT = 0x806E;
    // const GL_TEXTURE_3D = 0x806F;
    // const GL_PROXY_TEXTURE_3D = 0x8070;
    // const GL_TEXTURE_DEPTH = 0x8071;
    // const GL_TEXTURE_WRAP_R = 0x8072;
    // const GL_MAX_3D_TEXTURE_SIZE = 0x8073;
    // const GL_RESCALE_NORMAL = 0x803A;
    // const GL_MULTISAMPLE = 0x809D;
    // const GL_SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
    // const GL_SAMPLE_ALPHA_TO_ONE = 0x809F;
    // const GL_SAMPLE_COVERAGE = 0x80A0;
    // const GL_SAMPLE_BUFFERS = 0x80A8;
    // const GL_SAMPLES = 0x80A9;
    // const GL_SAMPLE_COVERAGE_VALUE = 0x80AA;
    // const GL_SAMPLE_COVERAGE_INVERT = 0x80AB;
    // const GL_BLEND_COLOR = 0x8005;
    // const GL_BLEND_EQUATION = 0x8009;
    // const GL_CONSTANT_COLOR = 0x8001;
    // const GL_ONE_MINUS_CONSTANT_COLOR = 0x8002;
    // const GL_CONSTANT_ALPHA = 0x8003;
    // const GL_ONE_MINUS_CONSTANT_ALPHA = 0x8004;
    // const GL_FUNC_ADD = 0x8006;
    // const GL_FUNC_REVERSE_SUBTRACT = 0x800B;
    // const GL_FUNC_SUBTRACT = 0x800A;
    // const GL_MIN = 0x8007;
    // const GL_MAX = 0x8008;
    // const GL_BLEND_EQUATION_RGB = 0x8009;
    // const GL_CLIENT_PIXEL_STORE_BIT = 0x00000001;
    // const GL_CLIENT_VERTEX_ARRAY_BIT = 0x00000002;
    // const GL_CLIENT_ALL_ATTRIB_BITS = 0xFFFFFFFF;
    // const GL_UNSIGNED_BYTE_2_3_3_REV = 0x8362;
    // const GL_UNSIGNED_SHORT_5_6_5 = 0x8363;
    // const GL_UNSIGNED_SHORT_5_6_5_REV = 0x8364;
    // const GL_UNSIGNED_SHORT_4_4_4_4_REV = 0x8365;
    // const GL_UNSIGNED_SHORT_1_5_5_5_REV = 0x8366;
    // const GL_UNSIGNED_INT_8_8_8_8_REV = 0x8367;
    // const GL_UNSIGNED_INT_2_10_10_10_REV = 0x8368;
    // const GL_BGR = 0x80E0;
    // const GL_BGRA = 0x80E1;
    // const GL_MAX_ELEMENTS_VERTICES = 0x80E8;
    // const GL_MAX_ELEMENTS_INDICES = 0x80E9;
    // const GL_CLAMP_TO_EDGE = 0x812F;
    // const GL_TEXTURE_MIN_LOD = 0x813A;
    // const GL_TEXTURE_MAX_LOD = 0x813B;
    // const GL_TEXTURE_BASE_LEVEL = 0x813C;
    // const GL_TEXTURE_MAX_LEVEL = 0x813D;
    // const GL_CLAMP_TO_BORDER = 0x812D;
    // const GL_POINT_FADE_THRESHOLD_SIZE = 0x8128;
    // const GL_POINT_SIZE_MIN = 0x8126;
    // const GL_POINT_SIZE_MAX = 0x8127;
    // const GL_POINT_DISTANCE_ATTENUATION = 0x8129;
    // const GL_ALIASED_LINE_WIDTH_RANGE = 0x846E;
    // const GL_ALIASED_POINT_SIZE_RANGE = 0x846D;
    // const GL_FOG_COORDINATE_SOURCE = 0x8450;
    // const GL_FOG_COORDINATE = 0x8451;
    // const GL_FRAGMENT_DEPTH = 0x8452;
    // const GL_CURRENT_FOG_COORDINATE = 0x8453;
    // const GL_FOG_COORDINATE_ARRAY_TYPE = 0x8454;
    // const GL_FOG_COORDINATE_ARRAY_STRIDE = 0x8455;
    // const GL_FOG_COORDINATE_ARRAY_POINTER = 0x8456;
    // const GL_FOG_COORDINATE_ARRAY = 0x8457;
    // const GL_COLOR_SUM = 0x8458;
    // const GL_CURRENT_SECONDARY_COLOR = 0x8459;
    // const GL_SECONDARY_COLOR_ARRAY_SIZE = 0x845A;
    // const GL_SECONDARY_COLOR_ARRAY_TYPE = 0x845B;
    // const GL_SECONDARY_COLOR_ARRAY_STRIDE = 0x845C;
    // const GL_SECONDARY_COLOR_ARRAY_POINTER = 0x845D;
    // const GL_SECONDARY_COLOR_ARRAY = 0x845E;
    // const GL_FOG_COORD_SRC = 0x8450;
    // const GL_FOG_COORD = 0x8451;
    // const GL_CURRENT_FOG_COORD = 0x8453;
    // const GL_FOG_COORD_ARRAY_TYPE = 0x8454;
    // const GL_FOG_COORD_ARRAY_STRIDE = 0x8455;
    // const GL_FOG_COORD_ARRAY_POINTER = 0x8456;
    // const GL_FOG_COORD_ARRAY = 0x8457;
    // const GL_CURRENT_RASTER_SECONDARY_COLOR = 0x845F;
    // const GL_LIGHT_MODEL_COLOR_CONTROL = 0x81F8;
    // const GL_SINGLE_COLOR = 0x81F9;
    // const GL_SEPARATE_SPECULAR_COLOR = 0x81FA;
    // const GL_TEXTURE0 = 0x84C0;
    // const GL_TEXTURE1 = 0x84C1;
    // const GL_TEXTURE2 = 0x84C2;
    // const GL_TEXTURE3 = 0x84C3;
    // const GL_TEXTURE4 = 0x84C4;
    // const GL_TEXTURE5 = 0x84C5;
    // const GL_TEXTURE6 = 0x84C6;
    // const GL_TEXTURE7 = 0x84C7;
    // const GL_TEXTURE8 = 0x84C8;
    // const GL_TEXTURE9 = 0x84C9;
    // const GL_TEXTURE10 = 0x84CA;
    // const GL_TEXTURE11 = 0x84CB;
    // const GL_TEXTURE12 = 0x84CC;
    // const GL_TEXTURE13 = 0x84CD;
    // const GL_TEXTURE14 = 0x84CE;
    // const GL_TEXTURE15 = 0x84CF;
    // const GL_TEXTURE16 = 0x84D0;
    // const GL_TEXTURE17 = 0x84D1;
    // const GL_TEXTURE18 = 0x84D2;
    // const GL_TEXTURE19 = 0x84D3;
    // const GL_TEXTURE20 = 0x84D4;
    // const GL_TEXTURE21 = 0x84D5;
    // const GL_TEXTURE22 = 0x84D6;
    // const GL_TEXTURE23 = 0x84D7;
    // const GL_TEXTURE24 = 0x84D8;
    // const GL_TEXTURE25 = 0x84D9;
    // const GL_TEXTURE26 = 0x84DA;
    // const GL_TEXTURE27 = 0x84DB;
    // const GL_TEXTURE28 = 0x84DC;
    // const GL_TEXTURE29 = 0x84DD;
    // const GL_TEXTURE30 = 0x84DE;
    // const GL_TEXTURE31 = 0x84DF;
    // const GL_ACTIVE_TEXTURE = 0x84E0;
    // const GL_COMPRESSED_RGB = 0x84ED;
    // const GL_COMPRESSED_RGBA = 0x84EE;
    // const GL_TEXTURE_COMPRESSION_HINT = 0x84EF;
    // const GL_CLIENT_ACTIVE_TEXTURE = 0x84E1;
    // const GL_MAX_TEXTURE_UNITS = 0x84E2;
    // const GL_TRANSPOSE_MODELVIEW_MATRIX = 0x84E3;
    // const GL_TRANSPOSE_PROJECTION_MATRIX = 0x84E4;
    // const GL_TRANSPOSE_TEXTURE_MATRIX = 0x84E5;
    // const GL_TRANSPOSE_COLOR_MATRIX = 0x84E6;
    // const GL_COMPRESSED_ALPHA = 0x84E9;
    // const GL_COMPRESSED_LUMINANCE = 0x84EA;
    // const GL_COMPRESSED_LUMINANCE_ALPHA = 0x84EB;
    // const GL_COMPRESSED_INTENSITY = 0x84EC;
    // const GL_SUBTRACT = 0x84E7;
    // const GL_MAX_RENDERBUFFER_SIZE = 0x84E8;
    // const GL_TEXTURE_CUBE_MAP = 0x8513;
    // const GL_TEXTURE_BINDING_CUBE_MAP = 0x8514;
    // const GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
    // const GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
    // const GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
    // const GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
    // const GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
    // const GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
    // const GL_PROXY_TEXTURE_CUBE_MAP = 0x851B;
    // const GL_MAX_CUBE_MAP_TEXTURE_SIZE = 0x851C;
    // const GL_NORMAL_MAP = 0x8511;
    // const GL_REFLECTION_MAP = 0x8512;
    // const GL_MAX_TEXTURE_LOD_BIAS = 0x84FD;
    // const GL_TEXTURE_LOD_BIAS = 0x8501;
    // const GL_INCR_WRAP = 0x8507;
    // const GL_DECR_WRAP = 0x8508;
    // const GL_TEXTURE_FILTER_CONTROL = 0x8500;
    // const GL_DEPTH_STENCIL = 0x84F9;
    // const GL_UNSIGNED_INT_24_8 = 0x84FA;
    // const GL_TEXTURE_RECTANGLE = 0x84F5;
    // const GL_TEXTURE_BINDING_RECTANGLE = 0x84F6;
    // const GL_PROXY_TEXTURE_RECTANGLE = 0x84F7;
    // const GL_MAX_RECTANGLE_TEXTURE_SIZE = 0x84F8;
    // const GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER = 0x84F0;
    // const GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER = 0x84F1;
    // const GL_TEXTURE_COMPRESSED_IMAGE_SIZE = 0x86A0;
    // const GL_TEXTURE_COMPRESSED = 0x86A1;
    // const GL_NUM_COMPRESSED_TEXTURE_FORMATS = 0x86A2;
    // const GL_COMPRESSED_TEXTURE_FORMATS = 0x86A3;
    // const GL_DOT3_RGB = 0x86AE;
    // const GL_DOT3_RGBA = 0x86AF;
    // const GL_COMBINE = 0x8570;
    // const GL_COMBINE_RGB = 0x8571;
    // const GL_COMBINE_ALPHA = 0x8572;
    // const GL_SOURCE0_RGB = 0x8580;
    // const GL_SOURCE1_RGB = 0x8581;
    // const GL_SOURCE2_RGB = 0x8582;
    // const GL_SOURCE0_ALPHA = 0x8588;
    // const GL_SOURCE1_ALPHA = 0x8589;
    // const GL_SOURCE2_ALPHA = 0x858A;
    // const GL_OPERAND0_RGB = 0x8590;
    // const GL_OPERAND1_RGB = 0x8591;
    // const GL_OPERAND2_RGB = 0x8592;
    // const GL_OPERAND0_ALPHA = 0x8598;
    // const GL_OPERAND1_ALPHA = 0x8599;
    // const GL_OPERAND2_ALPHA = 0x859A;
    // const GL_RGB_SCALE = 0x8573;
    // const GL_ADD_SIGNED = 0x8574;
    // const GL_INTERPOLATE = 0x8575;
    // const GL_CONSTANT = 0x8576;
    // const GL_PRIMARY_COLOR = 0x8577;
    // const GL_PREVIOUS = 0x8578;
    // const GL_SRC1_ALPHA = 0x8589;
    // const GL_SRC0_RGB = 0x8580;
    // const GL_SRC1_RGB = 0x8581;
    // const GL_SRC2_RGB = 0x8582;
    // const GL_SRC0_ALPHA = 0x8588;
    // const GL_SRC2_ALPHA = 0x858A;
    // const GL_BLEND_DST_RGB = 0x80C8;
    // const GL_BLEND_SRC_RGB = 0x80C9;
    // const GL_BLEND_DST_ALPHA = 0x80CA;
    // const GL_BLEND_SRC_ALPHA = 0x80CB;
    // const GL_DEPTH_COMPONENT16 = 0x81A5;
    // const GL_DEPTH_COMPONENT24 = 0x81A6;
    // const GL_DEPTH_COMPONENT32 = 0x81A7;
    // const GL_GENERATE_MIPMAP = 0x8191;
    // const GL_GENERATE_MIPMAP_HINT = 0x8192;
    // const GL_MIRRORED_REPEAT = 0x8370;
    // const GL_TEXTURE_DEPTH_SIZE = 0x884A;
    // const GL_TEXTURE_COMPARE_MODE = 0x884C;
    // const GL_TEXTURE_COMPARE_FUNC = 0x884D;
    // const GL_DEPTH_TEXTURE_MODE = 0x884B;
    // const GL_COMPARE_R_TO_TEXTURE = 0x884E;
    // const GL_COMPARE_REF_TO_TEXTURE = 0x884E;
    // const GL_TEXTURE_CUBE_MAP_SEAMLESS = 0x884F;
    // const GL_BUFFER_SIZE = 0x8764;
    // const GL_BUFFER_USAGE = 0x8765;
    // const GL_STENCIL_BACK_FUNC = 0x8800;
    // const GL_STENCIL_BACK_FAIL = 0x8801;
    // const GL_STENCIL_BACK_PASS_DEPTH_FAIL = 0x8802;
    // const GL_STENCIL_BACK_PASS_DEPTH_PASS = 0x8803;
    // const GL_MAX_DRAW_BUFFERS = 0x8824;
    // const GL_DRAW_BUFFER0 = 0x8825;
    // const GL_DRAW_BUFFER1 = 0x8826;
    // const GL_DRAW_BUFFER2 = 0x8827;
    // const GL_DRAW_BUFFER3 = 0x8828;
    // const GL_DRAW_BUFFER4 = 0x8829;
    // const GL_DRAW_BUFFER5 = 0x882A;
    // const GL_DRAW_BUFFER6 = 0x882B;
    // const GL_DRAW_BUFFER7 = 0x882C;
    // const GL_DRAW_BUFFER8 = 0x882D;
    // const GL_DRAW_BUFFER9 = 0x882E;
    // const GL_DRAW_BUFFER10 = 0x882F;
    // const GL_DRAW_BUFFER11 = 0x8830;
    // const GL_DRAW_BUFFER12 = 0x8831;
    // const GL_DRAW_BUFFER13 = 0x8832;
    // const GL_DRAW_BUFFER14 = 0x8833;
    // const GL_DRAW_BUFFER15 = 0x8834;
    // const GL_BLEND_EQUATION_ALPHA = 0x883D;
    // const GL_RGBA32F = 0x8814;
    // const GL_RGB32F = 0x8815;
    // const GL_RGBA16F = 0x881A;
    // const GL_RGB16F = 0x881B;
    // const GL_NUM_PROGRAM_BINARY_FORMATS = 0x87FE;
    // const GL_PROGRAM_BINARY_FORMATS = 0x87FF;
    // const GL_QUERY_COUNTER_BITS = 0x8864;
    // const GL_CURRENT_QUERY = 0x8865;
    // const GL_QUERY_RESULT = 0x8866;
    // const GL_QUERY_RESULT_AVAILABLE = 0x8867;
    // const GL_ARRAY_BUFFER = 0x8892;
    // const GL_ELEMENT_ARRAY_BUFFER = 0x8893;
    // const GL_ARRAY_BUFFER_BINDING = 0x8894;
    // const GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
    // const GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;
    // const GL_READ_ONLY = 0x88B8;
    // const GL_WRITE_ONLY = 0x88B9;
    // const GL_READ_WRITE = 0x88BA;
    // const GL_BUFFER_ACCESS = 0x88BB;
    // const GL_BUFFER_MAPPED = 0x88BC;
    // const GL_BUFFER_MAP_POINTER = 0x88BD;
    // const GL_STREAM_DRAW = 0x88E0;
    // const GL_STREAM_READ = 0x88E1;
    // const GL_STREAM_COPY = 0x88E2;
    // const GL_STATIC_DRAW = 0x88E4;
    // const GL_STATIC_READ = 0x88E5;
    // const GL_STATIC_COPY = 0x88E6;
    // const GL_DYNAMIC_DRAW = 0x88E8;
    // const GL_DYNAMIC_READ = 0x88E9;
    // const GL_DYNAMIC_COPY = 0x88EA;
    // const GL_SAMPLES_PASSED = 0x8914;
    // const GL_VERTEX_ARRAY_BUFFER_BINDING = 0x8896;
    // const GL_NORMAL_ARRAY_BUFFER_BINDING = 0x8897;
    // const GL_COLOR_ARRAY_BUFFER_BINDING = 0x8898;
    // const GL_INDEX_ARRAY_BUFFER_BINDING = 0x8899;
    // const GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING = 0x889A;
    // const GL_EDGE_FLAG_ARRAY_BUFFER_BINDING = 0x889B;
    // const GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING = 0x889C;
    // const GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING = 0x889D;
    // const GL_WEIGHT_ARRAY_BUFFER_BINDING = 0x889E;
    // const GL_FOG_COORD_ARRAY_BUFFER_BINDING = 0x889D;
    // const GL_MAX_VERTEX_ATTRIBS = 0x8869;
    // const GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A;
    // const GL_MAX_TEXTURE_IMAGE_UNITS = 0x8872;
    // const GL_POINT_SPRITE = 0x8861;
    // const GL_COORD_REPLACE = 0x8862;
    // const GL_MAX_TEXTURE_COORDS = 0x8871;
    // const GL_PIXEL_PACK_BUFFER = 0x88EB;
    // const GL_PIXEL_UNPACK_BUFFER = 0x88EC;
    // const GL_PIXEL_PACK_BUFFER_BINDING = 0x88ED;
    // const GL_PIXEL_UNPACK_BUFFER_BINDING = 0x88EF;
    // const GL_VERTEX_ATTRIB_ARRAY_INTEGER = 0x88FD;
    // const GL_MAX_ARRAY_TEXTURE_LAYERS = 0x88FF;
    // const GL_MIN_PROGRAM_TEXEL_OFFSET = 0x8904;
    // const GL_MAX_PROGRAM_TEXEL_OFFSET = 0x8905;
    // const GL_CLAMP_READ_COLOR = 0x891C;
    // const GL_FIXED_ONLY = 0x891D;
    // const GL_DEPTH24_STENCIL8 = 0x88F0;
    // const GL_TEXTURE_STENCIL_SIZE = 0x88F1;
    // const GL_CLAMP_VERTEX_COLOR = 0x891A;
    // const GL_CLAMP_FRAGMENT_COLOR = 0x891B;
    // const GL_GEOMETRY_VERTICES_OUT = 0x8916;
    // const GL_GEOMETRY_INPUT_TYPE = 0x8917;
    // const GL_GEOMETRY_OUTPUT_TYPE = 0x8918;
    // const GL_VERTEX_ATTRIB_ARRAY_DIVISOR = 0x88FE;
    // const GL_SRC1_COLOR = 0x88F9;
    // const GL_ONE_MINUS_SRC1_COLOR = 0x88FA;
    // const GL_ONE_MINUS_SRC1_ALPHA = 0x88FB;
    // const GL_MAX_DUAL_SOURCE_DRAW_BUFFERS = 0x88FC;
    // const GL_SAMPLER_BINDING = 0x8919;
    // const GL_TIME_ELAPSED = 0x88BF;
    // const GL_GEOMETRY_SHADER_INVOCATIONS = 0x887F;
    // const GL_MAX_TESS_CONTROL_INPUT_COMPONENTS = 0x886C;
    // const GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS = 0x886D;
    // const GL_VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622;
    // const GL_VERTEX_ATTRIB_ARRAY_SIZE = 0x8623;
    // const GL_VERTEX_ATTRIB_ARRAY_STRIDE = 0x8624;
    // const GL_VERTEX_ATTRIB_ARRAY_TYPE = 0x8625;
    // const GL_CURRENT_VERTEX_ATTRIB = 0x8626;
    // const GL_VERTEX_PROGRAM_POINT_SIZE = 0x8642;
    // const GL_VERTEX_ATTRIB_ARRAY_POINTER = 0x8645;
    // const GL_VERTEX_PROGRAM_TWO_SIDE = 0x8643;
    // const GL_PROGRAM_POINT_SIZE = 0x8642;
    // const GL_DEPTH_CLAMP = 0x864F;
    // const GL_FRAGMENT_SHADER = 0x8B30;
    // const GL_VERTEX_SHADER = 0x8B31;
    // const GL_MAX_FRAGMENT_UNIFORM_COMPONENTS = 0x8B49;
    // const GL_MAX_VERTEX_UNIFORM_COMPONENTS = 0x8B4A;
    // const GL_MAX_VARYING_FLOATS = 0x8B4B;
    // const GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C;
    // const GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
    // const GL_SHADER_TYPE = 0x8B4F;
    // const GL_MAX_VARYING_COMPONENTS = 0x8B4B;
    // const GL_FLOAT_VEC2 = 0x8B50;
    // const GL_FLOAT_VEC3 = 0x8B51;
    // const GL_FLOAT_VEC4 = 0x8B52;
    // const GL_INT_VEC2 = 0x8B53;
    // const GL_INT_VEC3 = 0x8B54;
    // const GL_INT_VEC4 = 0x8B55;
    // const GL_BOOL = 0x8B56;
    // const GL_BOOL_VEC2 = 0x8B57;
    // const GL_BOOL_VEC3 = 0x8B58;
    // const GL_BOOL_VEC4 = 0x8B59;
    // const GL_FLOAT_MAT2 = 0x8B5A;
    // const GL_FLOAT_MAT3 = 0x8B5B;
    // const GL_FLOAT_MAT4 = 0x8B5C;
    // const GL_SAMPLER_1D = 0x8B5D;
    // const GL_SAMPLER_2D = 0x8B5E;
    // const GL_SAMPLER_3D = 0x8B5F;
    // const GL_SAMPLER_CUBE = 0x8B60;
    // const GL_SAMPLER_1D_SHADOW = 0x8B61;
    // const GL_SAMPLER_2D_SHADOW = 0x8B62;
    // const GL_FLOAT_MAT2x3 = 0x8B65;
    // const GL_FLOAT_MAT2x4 = 0x8B66;
    // const GL_FLOAT_MAT3x2 = 0x8B67;
    // const GL_FLOAT_MAT3x4 = 0x8B68;
    // const GL_FLOAT_MAT4x2 = 0x8B69;
    // const GL_FLOAT_MAT4x3 = 0x8B6A;
    // const GL_SAMPLER_2D_RECT = 0x8B63;
    // const GL_SAMPLER_2D_RECT_SHADOW = 0x8B64;
    // const GL_DELETE_STATUS = 0x8B80;
    // const GL_COMPILE_STATUS = 0x8B81;
    // const GL_LINK_STATUS = 0x8B82;
    // const GL_VALIDATE_STATUS = 0x8B83;
    // const GL_INFO_LOG_LENGTH = 0x8B84;
    // const GL_ATTACHED_SHADERS = 0x8B85;
    // const GL_ACTIVE_UNIFORMS = 0x8B86;
    // const GL_ACTIVE_UNIFORM_MAX_LENGTH = 0x8B87;
    // const GL_SHADER_SOURCE_LENGTH = 0x8B88;
    // const GL_ACTIVE_ATTRIBUTES = 0x8B89;
    // const GL_ACTIVE_ATTRIBUTE_MAX_LENGTH = 0x8B8A;
    // const GL_FRAGMENT_SHADER_DERIVATIVE_HINT = 0x8B8B;
    // const GL_SHADING_LANGUAGE_VERSION = 0x8B8C;
    // const GL_CURRENT_PROGRAM = 0x8B8D;
    // const GL_POINT_SPRITE_COORD_ORIGIN = 0x8CA0;
    // const GL_LOWER_LEFT = 0x8CA1;
    // const GL_UPPER_LEFT = 0x8CA2;
    // const GL_STENCIL_BACK_REF = 0x8CA3;
    // const GL_STENCIL_BACK_VALUE_MASK = 0x8CA4;
    // const GL_STENCIL_BACK_WRITEMASK = 0x8CA5;
    // const GL_DEPTH_COMPONENT32F = 0x8CAC;
    // const GL_DEPTH32F_STENCIL8 = 0x8CAD;
    // const GL_FRAMEBUFFER_BINDING = 0x8CA6;
    // const GL_DRAW_FRAMEBUFFER_BINDING = 0x8CA6;
    // const GL_RENDERBUFFER_BINDING = 0x8CA7;
    // const GL_READ_FRAMEBUFFER = 0x8CA8;
    // const GL_DRAW_FRAMEBUFFER = 0x8CA9;
    // const GL_READ_FRAMEBUFFER_BINDING = 0x8CAA;
    // const GL_RENDERBUFFER_SAMPLES = 0x8CAB;
    // const GL_SRGB = 0x8C40;
    // const GL_SRGB8 = 0x8C41;
    // const GL_SRGB_ALPHA = 0x8C42;
    // const GL_SRGB8_ALPHA8 = 0x8C43;
    // const GL_COMPRESSED_SRGB = 0x8C48;
    // const GL_COMPRESSED_SRGB_ALPHA = 0x8C49;
    // const GL_SLUMINANCE_ALPHA = 0x8C44;
    // const GL_SLUMINANCE8_ALPHA8 = 0x8C45;
    // const GL_SLUMINANCE = 0x8C46;
    // const GL_SLUMINANCE8 = 0x8C47;
    // const GL_COMPRESSED_SLUMINANCE = 0x8C4A;
    // const GL_COMPRESSED_SLUMINANCE_ALPHA = 0x8C4B;
    // const GL_TEXTURE_1D_ARRAY = 0x8C18;
    // const GL_PROXY_TEXTURE_1D_ARRAY = 0x8C19;
    // const GL_TEXTURE_2D_ARRAY = 0x8C1A;
    // const GL_PROXY_TEXTURE_2D_ARRAY = 0x8C1B;
    // const GL_TEXTURE_BINDING_1D_ARRAY = 0x8C1C;
    // const GL_TEXTURE_BINDING_2D_ARRAY = 0x8C1D;
    // const GL_R11F_G11F_B10F = 0x8C3A;
    // const GL_UNSIGNED_INT_10F_11F_11F_REV = 0x8C3B;
    // const GL_RGB9_E5 = 0x8C3D;
    // const GL_UNSIGNED_INT_5_9_9_9_REV = 0x8C3E;
    // const GL_TEXTURE_SHARED_SIZE = 0x8C3F;
    // const GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = 0x8C76;
    // const GL_TRANSFORM_FEEDBACK_BUFFER_MODE = 0x8C7F;
    // const GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = 0x8C80;
    // const GL_TRANSFORM_FEEDBACK_VARYINGS = 0x8C83;
    // const GL_TRANSFORM_FEEDBACK_BUFFER_START = 0x8C84;
    // const GL_TRANSFORM_FEEDBACK_BUFFER_SIZE = 0x8C85;
    // const GL_PRIMITIVES_GENERATED = 0x8C87;
    // const GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = 0x8C88;
    // const GL_RASTERIZER_DISCARD = 0x8C89;
    // const GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = 0x8C8A;
    // const GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = 0x8C8B;
    // const GL_INTERLEAVED_ATTRIBS = 0x8C8C;
    // const GL_SEPARATE_ATTRIBS = 0x8C8D;
    // const GL_TRANSFORM_FEEDBACK_BUFFER = 0x8C8E;
    // const GL_TRANSFORM_FEEDBACK_BUFFER_BINDING = 0x8C8F;
    // const GL_TEXTURE_RED_TYPE = 0x8C10;
    // const GL_TEXTURE_GREEN_TYPE = 0x8C11;
    // const GL_TEXTURE_BLUE_TYPE = 0x8C12;
    // const GL_TEXTURE_ALPHA_TYPE = 0x8C13;
    // const GL_TEXTURE_DEPTH_TYPE = 0x8C16;
    // const GL_UNSIGNED_NORMALIZED = 0x8C17;
    // const GL_TEXTURE_LUMINANCE_TYPE = 0x8C14;
    // const GL_TEXTURE_INTENSITY_TYPE = 0x8C15;
    // const GL_TEXTURE_BUFFER = 0x8C2A;
    // const GL_MAX_TEXTURE_BUFFER_SIZE = 0x8C2B;
    // const GL_TEXTURE_BINDING_BUFFER = 0x8C2C;
    // const GL_TEXTURE_BUFFER_DATA_STORE_BINDING = 0x8C2D;
    // const GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = 0x8C29;
    // const GL_ANY_SAMPLES_PASSED = 0x8C2F;
    // const GL_SAMPLE_SHADING = 0x8C36;
    // const GL_MIN_SAMPLE_SHADING_VALUE = 0x8C37;
    // const GL_MAJOR_VERSION = 0x821B;
    // const GL_MINOR_VERSION = 0x821C;
    // const GL_NUM_EXTENSIONS = 0x821D;
    // const GL_CONTEXT_FLAGS = 0x821E;
    // const GL_COMPRESSED_RED = 0x8225;
    // const GL_COMPRESSED_RG = 0x8226;
    // const GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = 0x8210;
    // const GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = 0x8211;
    // const GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE = 0x8212;
    // const GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = 0x8213;
    // const GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = 0x8214;
    // const GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = 0x8215;
    // const GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = 0x8216;
    // const GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = 0x8217;
    // const GL_FRAMEBUFFER_DEFAULT = 0x8218;
    // const GL_FRAMEBUFFER_UNDEFINED = 0x8219;
    // const GL_DEPTH_STENCIL_ATTACHMENT = 0x821A;
    // const GL_INDEX = 0x8222;
    // const GL_RG = 0x8227;
    // const GL_RG_INTEGER = 0x8228;
    // const GL_R8 = 0x8229;
    // const GL_R16 = 0x822A;
    // const GL_RG8 = 0x822B;
    // const GL_RG16 = 0x822C;
    // const GL_R16F = 0x822D;
    // const GL_R32F = 0x822E;
    // const GL_RG16F = 0x822F;
    // const GL_RG32F = 0x8230;
    // const GL_R8I = 0x8231;
    // const GL_R8UI = 0x8232;
    // const GL_R16I = 0x8233;
    // const GL_R16UI = 0x8234;
    // const GL_R32I = 0x8235;
    // const GL_R32UI = 0x8236;
    // const GL_RG8I = 0x8237;
    // const GL_RG8UI = 0x8238;
    // const GL_RG16I = 0x8239;
    // const GL_RG16UI = 0x823A;
    // const GL_RG32I = 0x823B;
    // const GL_RG32UI = 0x823C;
    // const GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = 0x00000001;
    // const GL_RGBA32UI = 0x8D70;
    // const GL_RGB32UI = 0x8D71;
    // const GL_RGBA16UI = 0x8D76;
    // const GL_RGB16UI = 0x8D77;
    // const GL_RGBA8UI = 0x8D7C;
    // const GL_RGB8UI = 0x8D7D;
    // const GL_RGBA32I = 0x8D82;
    // const GL_RGB32I = 0x8D83;
    // const GL_RGBA16I = 0x8D88;
    // const GL_RGB16I = 0x8D89;
    // const GL_RGBA8I = 0x8D8E;
    // const GL_RGB8I = 0x8D8F;
    // const GL_RED_INTEGER = 0x8D94;
    // const GL_GREEN_INTEGER = 0x8D95;
    // const GL_BLUE_INTEGER = 0x8D96;
    // const GL_RGB_INTEGER = 0x8D98;
    // const GL_RGBA_INTEGER = 0x8D99;
    // const GL_BGR_INTEGER = 0x8D9A;
    // const GL_BGRA_INTEGER = 0x8D9B;
    // const GL_SAMPLER_1D_ARRAY = 0x8DC0;
    // const GL_SAMPLER_2D_ARRAY = 0x8DC1;
    // const GL_SAMPLER_1D_ARRAY_SHADOW = 0x8DC3;
    // const GL_SAMPLER_2D_ARRAY_SHADOW = 0x8DC4;
    // const GL_SAMPLER_CUBE_SHADOW = 0x8DC5;
    // const GL_UNSIGNED_INT_VEC2 = 0x8DC6;
    // const GL_UNSIGNED_INT_VEC3 = 0x8DC7;
    // const GL_UNSIGNED_INT_VEC4 = 0x8DC8;
    // const GL_INT_SAMPLER_1D = 0x8DC9;
    // const GL_INT_SAMPLER_2D = 0x8DCA;
    // const GL_INT_SAMPLER_3D = 0x8DCB;
    // const GL_INT_SAMPLER_CUBE = 0x8DCC;
    // const GL_INT_SAMPLER_1D_ARRAY = 0x8DCE;
    // const GL_INT_SAMPLER_2D_ARRAY = 0x8DCF;
    // const GL_UNSIGNED_INT_SAMPLER_1D = 0x8DD1;
    // const GL_UNSIGNED_INT_SAMPLER_2D = 0x8DD2;
    // const GL_UNSIGNED_INT_SAMPLER_3D = 0x8DD3;
    // const GL_UNSIGNED_INT_SAMPLER_CUBE = 0x8DD4;
    // const GL_UNSIGNED_INT_SAMPLER_1D_ARRAY = 0x8DD6;
    // const GL_UNSIGNED_INT_SAMPLER_2D_ARRAY = 0x8DD7;
    // const GL_FLOAT_32_UNSIGNED_INT_24_8_REV = 0x8DAD;
    // const GL_FRAMEBUFFER_SRGB = 0x8DB9;
    // const GL_COMPRESSED_RED_RGTC1 = 0x8DBB;
    // const GL_COMPRESSED_SIGNED_RED_RGTC1 = 0x8DBC;
    // const GL_COMPRESSED_RG_RGTC2 = 0x8DBD;
    // const GL_COMPRESSED_SIGNED_RG_RGTC2 = 0x8DBE;
    // const GL_ALPHA_INTEGER = 0x8D97;
    // const GL_SAMPLER_BUFFER = 0x8DC2;
    // const GL_INT_SAMPLER_2D_RECT = 0x8DCD;
    // const GL_INT_SAMPLER_BUFFER = 0x8DD0;
    // const GL_UNSIGNED_INT_SAMPLER_2D_RECT = 0x8DD5;
    // const GL_UNSIGNED_INT_SAMPLER_BUFFER = 0x8DD8;
    // const GL_FRAMEBUFFER_ATTACHMENT_LAYERED = 0x8DA7;
    // const GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = 0x8DA8;
    // const GL_GEOMETRY_SHADER = 0x8DD9;
    // const GL_MAX_GEOMETRY_UNIFORM_COMPONENTS = 0x8DDF;
    // const GL_MAX_GEOMETRY_OUTPUT_VERTICES = 0x8DE0;
    // const GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS = 0x8DE1;
    // const GL_INT_2_10_10_10_REV = 0x8D9F;
    // const GL_ACTIVE_SUBROUTINES = 0x8DE5;
    // const GL_ACTIVE_SUBROUTINE_UNIFORMS = 0x8DE6;
    // const GL_MAX_SUBROUTINES = 0x8DE7;
    // const GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS = 0x8DE8;
    // const GL_QUERY_WAIT = 0x8E13;
    // const GL_QUERY_NO_WAIT = 0x8E14;
    // const GL_QUERY_BY_REGION_WAIT = 0x8E15;
    // const GL_QUERY_BY_REGION_NO_WAIT = 0x8E16;
    // const GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION = 0x8E4C;
    // const GL_FIRST_VERTEX_CONVENTION = 0x8E4D;
    // const GL_LAST_VERTEX_CONVENTION = 0x8E4E;
    // const GL_PROVOKING_VERTEX = 0x8E4F;
    // const GL_SAMPLE_POSITION = 0x8E50;
    // const GL_SAMPLE_MASK = 0x8E51;
    // const GL_SAMPLE_MASK_VALUE = 0x8E52;
    // const GL_MAX_SAMPLE_MASK_WORDS = 0x8E59;
    // const GL_TEXTURE_SWIZZLE_R = 0x8E42;
    // const GL_TEXTURE_SWIZZLE_G = 0x8E43;
    // const GL_TEXTURE_SWIZZLE_B = 0x8E44;
    // const GL_TEXTURE_SWIZZLE_A = 0x8E45;
    // const GL_TEXTURE_SWIZZLE_RGBA = 0x8E46;
    // const GL_TIMESTAMP = 0x8E28;
    // const GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5E;
    // const GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET = 0x8E5F;
    // const GL_MAX_GEOMETRY_SHADER_INVOCATIONS = 0x8E5A;
    // const GL_MIN_FRAGMENT_INTERPOLATION_OFFSET = 0x8E5B;
    // const GL_MAX_FRAGMENT_INTERPOLATION_OFFSET = 0x8E5C;
    // const GL_FRAGMENT_INTERPOLATION_OFFSET_BITS = 0x8E5D;
    // const GL_MAX_VERTEX_STREAMS = 0x8E71;
    // const GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS = 0x8E47;
    // const GL_ACTIVE_SUBROUTINE_MAX_LENGTH = 0x8E48;
    // const GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH = 0x8E49;
    // const GL_NUM_COMPATIBLE_SUBROUTINES = 0x8E4A;
    // const GL_COMPATIBLE_SUBROUTINES = 0x8E4B;
    // const GL_PATCH_VERTICES = 0x8E72;
    // const GL_PATCH_DEFAULT_INNER_LEVEL = 0x8E73;
    // const GL_PATCH_DEFAULT_OUTER_LEVEL = 0x8E74;
    // const GL_TESS_CONTROL_OUTPUT_VERTICES = 0x8E75;
    // const GL_TESS_GEN_MODE = 0x8E76;
    // const GL_TESS_GEN_SPACING = 0x8E77;
    // const GL_TESS_GEN_VERTEX_ORDER = 0x8E78;
    // const GL_TESS_GEN_POINT_MODE = 0x8E79;
    // const GL_ISOLINES = 0x8E7A;
    // const GL_FRACTIONAL_ODD = 0x8E7B;
    // const GL_FRACTIONAL_EVEN = 0x8E7C;
    // const GL_MAX_PATCH_VERTICES = 0x8E7D;
    // const GL_MAX_TESS_GEN_LEVEL = 0x8E7E;
    // const GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E7F;
    // const GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E80;
    // const GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS = 0x8E81;
    // const GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS = 0x8E82;
    // const GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS = 0x8E83;
    // const GL_MAX_TESS_PATCH_COMPONENTS = 0x8E84;
    // const GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS = 0x8E85;
    // const GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS = 0x8E86;
    // const GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS = 0x8E89;
    // const GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS = 0x8E8A;
    // const GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS = 0x8E1E;
    // const GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS = 0x8E1F;
    // const GL_TESS_EVALUATION_SHADER = 0x8E87;
    // const GL_TESS_CONTROL_SHADER = 0x8E88;
    // const GL_TRANSFORM_FEEDBACK = 0x8E22;
    // const GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED = 0x8E23;
    // const GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE = 0x8E24;
    // const GL_TRANSFORM_FEEDBACK_BINDING = 0x8E25;
    // const GL_MAX_TRANSFORM_FEEDBACK_BUFFERS = 0x8E70;
    // const GL_BUFFER_ACCESS_FLAGS = 0x911F;
    // const GL_BUFFER_MAP_LENGTH = 0x9120;
    // const GL_BUFFER_MAP_OFFSET = 0x9121;
    // const GL_MAX_VERTEX_OUTPUT_COMPONENTS = 0x9122;
    // const GL_MAX_GEOMETRY_INPUT_COMPONENTS = 0x9123;
    // const GL_MAX_GEOMETRY_OUTPUT_COMPONENTS = 0x9124;
    // const GL_MAX_FRAGMENT_INPUT_COMPONENTS = 0x9125;
    // const GL_CONTEXT_PROFILE_MASK = 0x9126;
    // const GL_MAX_SERVER_WAIT_TIMEOUT = 0x9111;
    // const GL_OBJECT_TYPE = 0x9112;
    // const GL_SYNC_CONDITION = 0x9113;
    // const GL_SYNC_STATUS = 0x9114;
    // const GL_SYNC_FLAGS = 0x9115;
    // const GL_SYNC_FENCE = 0x9116;
    // const GL_SYNC_GPU_COMMANDS_COMPLETE = 0x9117;
    // const GL_UNSIGNALED = 0x9118;
    // const GL_SIGNALED = 0x9119;
    // const GL_ALREADY_SIGNALED = 0x911A;
    // const GL_TIMEOUT_EXPIRED = 0x911B;
    // const GL_CONDITION_SATISFIED = 0x911C;
    // const GL_WAIT_FAILED = 0x911D;
    // const GL_TEXTURE_2D_MULTISAMPLE = 0x9100;
    // const GL_PROXY_TEXTURE_2D_MULTISAMPLE = 0x9101;
    // const GL_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9102;
    // const GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9103;
    // const GL_TEXTURE_BINDING_2D_MULTISAMPLE = 0x9104;
    // const GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = 0x9105;
    // const GL_TEXTURE_SAMPLES = 0x9106;
    // const GL_TEXTURE_FIXED_SAMPLE_LOCATIONS = 0x9107;
    // const GL_SAMPLER_2D_MULTISAMPLE = 0x9108;
    // const GL_INT_SAMPLER_2D_MULTISAMPLE = 0x9109;
    // const GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = 0x910A;
    // const GL_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910B;
    // const GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910C;
    // const GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = 0x910D;
    // const GL_MAX_COLOR_TEXTURE_SAMPLES = 0x910E;
    // const GL_MAX_DEPTH_TEXTURE_SAMPLES = 0x910F;
    // const GL_MAX_INTEGER_SAMPLES = 0x9110;
    // const GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
    // const GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
    // const GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2;
    // const GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3;
    // const GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER = 0x8CD4;
    // const GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
    // const GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
    // const GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
    // const GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER = 0x8CDB;
    // const GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER = 0x8CDC;
    // const GL_FRAMEBUFFER_UNSUPPORTED = 0x8CDD;
    // const GL_MAX_COLOR_ATTACHMENTS = 0x8CDF;
    // const GL_COLOR_ATTACHMENT0 = 0x8CE0;
    // const GL_COLOR_ATTACHMENT1 = 0x8CE1;
    // const GL_COLOR_ATTACHMENT2 = 0x8CE2;
    // const GL_COLOR_ATTACHMENT3 = 0x8CE3;
    // const GL_COLOR_ATTACHMENT4 = 0x8CE4;
    // const GL_COLOR_ATTACHMENT5 = 0x8CE5;
    // const GL_COLOR_ATTACHMENT6 = 0x8CE6;
    // const GL_COLOR_ATTACHMENT7 = 0x8CE7;
    // const GL_COLOR_ATTACHMENT8 = 0x8CE8;
    // const GL_COLOR_ATTACHMENT9 = 0x8CE9;
    // const GL_COLOR_ATTACHMENT10 = 0x8CEA;
    // const GL_COLOR_ATTACHMENT11 = 0x8CEB;
    // const GL_COLOR_ATTACHMENT12 = 0x8CEC;
    // const GL_COLOR_ATTACHMENT13 = 0x8CED;
    // const GL_COLOR_ATTACHMENT14 = 0x8CEE;
    // const GL_COLOR_ATTACHMENT15 = 0x8CEF;
    // const GL_COLOR_ATTACHMENT16 = 0x8CF0;
    // const GL_COLOR_ATTACHMENT17 = 0x8CF1;
    // const GL_COLOR_ATTACHMENT18 = 0x8CF2;
    // const GL_COLOR_ATTACHMENT19 = 0x8CF3;
    // const GL_COLOR_ATTACHMENT20 = 0x8CF4;
    // const GL_COLOR_ATTACHMENT21 = 0x8CF5;
    // const GL_COLOR_ATTACHMENT22 = 0x8CF6;
    // const GL_COLOR_ATTACHMENT23 = 0x8CF7;
    // const GL_COLOR_ATTACHMENT24 = 0x8CF8;
    // const GL_COLOR_ATTACHMENT25 = 0x8CF9;
    // const GL_COLOR_ATTACHMENT26 = 0x8CFA;
    // const GL_COLOR_ATTACHMENT27 = 0x8CFB;
    // const GL_COLOR_ATTACHMENT28 = 0x8CFC;
    // const GL_COLOR_ATTACHMENT29 = 0x8CFD;
    // const GL_COLOR_ATTACHMENT30 = 0x8CFE;
    // const GL_COLOR_ATTACHMENT31 = 0x8CFF;
    // const GL_DEPTH_ATTACHMENT = 0x8D00;
    // const GL_STENCIL_ATTACHMENT = 0x8D20;
    // const GL_FRAMEBUFFER = 0x8D40;
    // const GL_RENDERBUFFER = 0x8D41;
    // const GL_RENDERBUFFER_WIDTH = 0x8D42;
    // const GL_RENDERBUFFER_HEIGHT = 0x8D43;
    // const GL_RENDERBUFFER_INTERNAL_FORMAT = 0x8D44;
    // const GL_STENCIL_INDEX1 = 0x8D46;
    // const GL_STENCIL_INDEX4 = 0x8D47;
    // const GL_STENCIL_INDEX8 = 0x8D48;
    // const GL_STENCIL_INDEX16 = 0x8D49;
    // const GL_RENDERBUFFER_RED_SIZE = 0x8D50;
    // const GL_RENDERBUFFER_GREEN_SIZE = 0x8D51;
    // const GL_RENDERBUFFER_BLUE_SIZE = 0x8D52;
    // const GL_RENDERBUFFER_ALPHA_SIZE = 0x8D53;
    // const GL_RENDERBUFFER_DEPTH_SIZE = 0x8D54;
    // const GL_RENDERBUFFER_STENCIL_SIZE = 0x8D55;
    // const GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = 0x8D56;
    // const GL_MAX_SAMPLES = 0x8D57;
    // const GL_MAP_READ_BIT = 0x0001;
    // const GL_MAP_WRITE_BIT = 0x0002;
    // const GL_MAP_INVALIDATE_RANGE_BIT = 0x0004;
    // const GL_MAP_INVALIDATE_BUFFER_BIT = 0x0008;
    // const GL_MAP_FLUSH_EXPLICIT_BIT = 0x0010;
    // const GL_MAP_UNSYNCHRONIZED_BIT = 0x0020;
    // const GL_VERTEX_ARRAY_BINDING = 0x85B5;
    // const GL_R8_SNORM = 0x8F94;
    // const GL_RG8_SNORM = 0x8F95;
    // const GL_RGB8_SNORM = 0x8F96;
    // const GL_RGBA8_SNORM = 0x8F97;
    // const GL_R16_SNORM = 0x8F98;
    // const GL_RG16_SNORM = 0x8F99;
    // const GL_RGB16_SNORM = 0x8F9A;
    // const GL_RGBA16_SNORM = 0x8F9B;
    // const GL_SIGNED_NORMALIZED = 0x8F9C;
    // const GL_PRIMITIVE_RESTART = 0x8F9D;
    // const GL_PRIMITIVE_RESTART_INDEX = 0x8F9E;
    // const GL_COPY_READ_BUFFER = 0x8F36;
    // const GL_COPY_WRITE_BUFFER = 0x8F37;
    // const GL_DRAW_INDIRECT_BUFFER = 0x8F3F;
    // const GL_DRAW_INDIRECT_BUFFER_BINDING = 0x8F43;
    // const GL_DOUBLE_MAT2 = 0x8F46;
    // const GL_DOUBLE_MAT3 = 0x8F47;
    // const GL_DOUBLE_MAT4 = 0x8F48;
    // const GL_DOUBLE_MAT2x3 = 0x8F49;
    // const GL_DOUBLE_MAT2x4 = 0x8F4A;
    // const GL_DOUBLE_MAT3x2 = 0x8F4B;
    // const GL_DOUBLE_MAT3x4 = 0x8F4C;
    // const GL_DOUBLE_MAT4x2 = 0x8F4D;
    // const GL_DOUBLE_MAT4x3 = 0x8F4E;
    // const GL_UNIFORM_BUFFER = 0x8A11;
    // const GL_UNIFORM_BUFFER_BINDING = 0x8A28;
    // const GL_UNIFORM_BUFFER_START = 0x8A29;
    // const GL_UNIFORM_BUFFER_SIZE = 0x8A2A;
    // const GL_MAX_VERTEX_UNIFORM_BLOCKS = 0x8A2B;
    // const GL_MAX_GEOMETRY_UNIFORM_BLOCKS = 0x8A2C;
    // const GL_MAX_FRAGMENT_UNIFORM_BLOCKS = 0x8A2D;
    // const GL_MAX_COMBINED_UNIFORM_BLOCKS = 0x8A2E;
    // const GL_MAX_UNIFORM_BUFFER_BINDINGS = 0x8A2F;
    // const GL_MAX_UNIFORM_BLOCK_SIZE = 0x8A30;
    // const GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = 0x8A31;
    // const GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = 0x8A32;
    // const GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = 0x8A33;
    // const GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT = 0x8A34;
    // const GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = 0x8A35;
    // const GL_ACTIVE_UNIFORM_BLOCKS = 0x8A36;
    // const GL_UNIFORM_TYPE = 0x8A37;
    // const GL_UNIFORM_SIZE = 0x8A38;
    // const GL_UNIFORM_NAME_LENGTH = 0x8A39;
    // const GL_UNIFORM_BLOCK_INDEX = 0x8A3A;
    // const GL_UNIFORM_OFFSET = 0x8A3B;
    // const GL_UNIFORM_ARRAY_STRIDE = 0x8A3C;
    // const GL_UNIFORM_MATRIX_STRIDE = 0x8A3D;
    // const GL_UNIFORM_IS_ROW_MAJOR = 0x8A3E;
    // const GL_UNIFORM_BLOCK_BINDING = 0x8A3F;
    // const GL_UNIFORM_BLOCK_DATA_SIZE = 0x8A40;
    // const GL_UNIFORM_BLOCK_NAME_LENGTH = 0x8A41;
    // const GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS = 0x8A42;
    // const GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = 0x8A43;
    // const GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = 0x8A44;
    // const GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER = 0x8A45;
    // const GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = 0x8A46;
    // const GL_CONTEXT_CORE_PROFILE_BIT = 0x00000001;
    // const GL_CONTEXT_COMPATIBILITY_PROFILE_BIT = 0x00000002;
    // const GL_SYNC_FLUSH_COMMANDS_BIT = 0x00000001;
    // const GL_RGB10_A2UI = 0x906F;
    // const GL_TEXTURE_CUBE_MAP_ARRAY = 0x9009;
    // const GL_TEXTURE_BINDING_CUBE_MAP_ARRAY = 0x900A;
    // const GL_PROXY_TEXTURE_CUBE_MAP_ARRAY = 0x900B;
    // const GL_SAMPLER_CUBE_MAP_ARRAY = 0x900C;
    // const GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW = 0x900D;
    // const GL_INT_SAMPLER_CUBE_MAP_ARRAY = 0x900E;
    // const GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY = 0x900F;
    // const GL_DOUBLE_VEC2 = 0x8FFC;
    // const GL_DOUBLE_VEC3 = 0x8FFD;
    // const GL_DOUBLE_VEC4 = 0x8FFE;
    // const GL_IMPLEMENTATION_COLOR_READ_TYPE = 0x8B9A;
    // const GL_IMPLEMENTATION_COLOR_READ_FORMAT = 0x8B9B;
    // const GL_LOW_FLOAT = 0x8DF0;
    // const GL_MEDIUM_FLOAT = 0x8DF1;
    // const GL_HIGH_FLOAT = 0x8DF2;
    // const GL_LOW_INT = 0x8DF3;
    // const GL_MEDIUM_INT = 0x8DF4;
    // const GL_HIGH_INT = 0x8DF5;
    // const GL_SHADER_COMPILER = 0x8DFA;
    // const GL_SHADER_BINARY_FORMATS = 0x8DF8;
    // const GL_NUM_SHADER_BINARY_FORMATS = 0x8DF9;
    // const GL_MAX_VERTEX_UNIFORM_VECTORS = 0x8DFB;
    // const GL_MAX_VARYING_VECTORS = 0x8DFC;
    // const GL_MAX_FRAGMENT_UNIFORM_VECTORS = 0x8DFD;
    // const GL_RGB565 = 0x8D62;
    // const GL_PROGRAM_BINARY_RETRIEVABLE_HINT = 0x8257;
    // const GL_PROGRAM_SEPARABLE = 0x8258;
    // const GL_ACTIVE_PROGRAM = 0x8259;
    // const GL_PROGRAM_PIPELINE_BINDING = 0x825A;
    // const GL_MAX_VIEWPORTS = 0x825B;
    // const GL_VIEWPORT_SUBPIXEL_BITS = 0x825C;
    // const GL_VIEWPORT_BOUNDS_RANGE = 0x825D;
    // const GL_LAYER_PROVOKING_VERTEX = 0x825E;
    // const GL_VIEWPORT_INDEX_PROVOKING_VERTEX = 0x825F;
    // const GL_UNDEFINED_VERTEX = 0x8260;
    // const GL_PROGRAM_BINARY_LENGTH = 0x8741;
    // const GL_VERTEX_SHADER_BIT = 0x00000001;
    // const GL_FRAGMENT_SHADER_BIT = 0x00000002;
    // const GL_GEOMETRY_SHADER_BIT = 0x00000004;
    // const GL_TESS_CONTROL_SHADER_BIT = 0x00000008;
    // const GL_TESS_EVALUATION_SHADER_BIT = 0x00000010;
    // const GL_ALL_SHADER_BITS = 0xFFFFFFFF;
    // const GLFW_VERSION_MAJOR = 3;
    // const GLFW_VERSION_MINOR = 3;
    // const GLFW_VERSION_REVISION = 8;
    // const GLFW_TRUE = true;
    // const GLFW_FALSE = false;
    // const GLFW_RELEASE = GLFW_RELEASE;
    // const GLFW_PRESS = 1;
    // const GLFW_REPEAT = 2;
    // const GLFW_HAT_CENTERED = GLFW_HAT_CENTERED;
    // const GLFW_HAT_UP = 1;
    // const GLFW_HAT_RIGHT = 2;
    // const GLFW_HAT_DOWN = 4;
    // const GLFW_HAT_LEFT = 8;
    // const GLFW_KEY_UNKNOWN = -1;
    // const GLFW_KEY_SPACE = 32;
    // const GLFW_KEY_APOSTROPHE = 39;
    // const GLFW_KEY_COMMA = 44;
    // const GLFW_KEY_MINUS = 45;
    // const GLFW_KEY_PERIOD = 46;
    // const GLFW_KEY_SLASH = 47;
    // const GLFW_KEY_0 = 48;
    // const GLFW_KEY_1 = 49;
    // const GLFW_KEY_2 = 50;
    // const GLFW_KEY_3 = 51;
    // const GLFW_KEY_4 = 52;
    // const GLFW_KEY_5 = 53;
    // const GLFW_KEY_6 = 54;
    // const GLFW_KEY_7 = 55;
    // const GLFW_KEY_8 = 56;
    // const GLFW_KEY_9 = 57;
    // const GLFW_KEY_SEMICOLON = 59;
    // const GLFW_KEY_EQUAL = 61;
    // const GLFW_KEY_A = 65;
    // const GLFW_KEY_B = 66;
    // const GLFW_KEY_C = 67;
    // const GLFW_KEY_D = 68;
    // const GLFW_KEY_E = 69;
    // const GLFW_KEY_F = 70;
    // const GLFW_KEY_G = 71;
    // const GLFW_KEY_H = 72;
    // const GLFW_KEY_I = 73;
    // const GLFW_KEY_J = 74;
    // const GLFW_KEY_K = 75;
    // const GLFW_KEY_L = 76;
    // const GLFW_KEY_M = 77;
    // const GLFW_KEY_N = 78;
    // const GLFW_KEY_O = 79;
    // const GLFW_KEY_P = 80;
    // const GLFW_KEY_Q = 81;
    // const GLFW_KEY_R = 82;
    // const GLFW_KEY_S = 83;
    // const GLFW_KEY_T = 84;
    // const GLFW_KEY_U = 85;
    // const GLFW_KEY_V = 86;
    // const GLFW_KEY_W = 87;
    // const GLFW_KEY_X = 88;
    // const GLFW_KEY_Y = 89;
    // const GLFW_KEY_Z = 90;
    // const GLFW_KEY_LEFT_BRACKET = 91;
    // const GLFW_KEY_BACKSLASH = 92;
    // const GLFW_KEY_RIGHT_BRACKET = 93;
    // const GLFW_KEY_GRAVE_ACCENT = 96;
    // const GLFW_KEY_WORLD_1 = 161;
    // const GLFW_KEY_WORLD_2 = 162;
    // const GLFW_KEY_ESCAPE = 256;
    // const GLFW_KEY_ENTER = 257;
    // const GLFW_KEY_TAB = 258;
    // const GLFW_KEY_BACKSPACE = 259;
    // const GLFW_KEY_INSERT = 260;
    // const GLFW_KEY_DELETE = 261;
    // const GLFW_KEY_RIGHT = 262;
    // const GLFW_KEY_LEFT = 263;
    // const GLFW_KEY_DOWN = 264;
    // const GLFW_KEY_UP = 265;
    // const GLFW_KEY_PAGE_UP = 266;
    // const GLFW_KEY_PAGE_DOWN = 267;
    // const GLFW_KEY_HOME = 268;
    // const GLFW_KEY_END = 269;
    // const GLFW_KEY_CAPS_LOCK = 280;
    // const GLFW_KEY_SCROLL_LOCK = 281;
    // const GLFW_KEY_NUM_LOCK = 282;
    // const GLFW_KEY_PRINT_SCREEN = 283;
    // const GLFW_KEY_PAUSE = 284;
    // const GLFW_KEY_F1 = 290;
    // const GLFW_KEY_F2 = 291;
    // const GLFW_KEY_F3 = 292;
    // const GLFW_KEY_F4 = 293;
    // const GLFW_KEY_F5 = 294;
    // const GLFW_KEY_F6 = 295;
    // const GLFW_KEY_F7 = 296;
    // const GLFW_KEY_F8 = 297;
    // const GLFW_KEY_F9 = 298;
    // const GLFW_KEY_F10 = 299;
    // const GLFW_KEY_F11 = 300;
    // const GLFW_KEY_F12 = 301;
    // const GLFW_KEY_F13 = 302;
    // const GLFW_KEY_F14 = 303;
    // const GLFW_KEY_F15 = 304;
    // const GLFW_KEY_F16 = 305;
    // const GLFW_KEY_F17 = 306;
    // const GLFW_KEY_F18 = 307;
    // const GLFW_KEY_F19 = 308;
    // const GLFW_KEY_F20 = 309;
    // const GLFW_KEY_F21 = 310;
    // const GLFW_KEY_F22 = 311;
    // const GLFW_KEY_F23 = 312;
    // const GLFW_KEY_F24 = 313;
    // const GLFW_KEY_F25 = 314;
    // const GLFW_KEY_KP_0 = 320;
    // const GLFW_KEY_KP_1 = 321;
    // const GLFW_KEY_KP_2 = 322;
    // const GLFW_KEY_KP_3 = 323;
    // const GLFW_KEY_KP_4 = 324;
    // const GLFW_KEY_KP_5 = 325;
    // const GLFW_KEY_KP_6 = 326;
    // const GLFW_KEY_KP_7 = 327;
    // const GLFW_KEY_KP_8 = 328;
    // const GLFW_KEY_KP_9 = 329;
    // const GLFW_KEY_KP_DECIMAL = 330;
    // const GLFW_KEY_KP_DIVIDE = 331;
    // const GLFW_KEY_KP_MULTIPLY = 332;
    // const GLFW_KEY_KP_SUBTRACT = 333;
    // const GLFW_KEY_KP_ADD = 334;
    // const GLFW_KEY_KP_ENTER = 335;
    // const GLFW_KEY_KP_EQUAL = 336;
    // const GLFW_KEY_LEFT_SHIFT = 340;
    // const GLFW_KEY_LEFT_CONTROL = 341;
    // const GLFW_KEY_LEFT_ALT = 342;
    // const GLFW_KEY_LEFT_SUPER = 343;
    // const GLFW_KEY_RIGHT_SHIFT = 344;
    // const GLFW_KEY_RIGHT_CONTROL = 345;
    // const GLFW_KEY_RIGHT_ALT = 346;
    // const GLFW_KEY_RIGHT_SUPER = 347;
    // const GLFW_KEY_MENU = 348;
    // const GLFW_KEY_LAST = GLFW_KEY_MENU;
    // const GLFW_MOD_SHIFT = 0x0001;
    // const GLFW_MOD_CONTROL = 0x0002;
    // const GLFW_MOD_ALT = 0x0004;
    // const GLFW_MOD_SUPER = 0x0008;
    // const GLFW_MOD_CAPS_LOCK = 0x0010;
    // const GLFW_MOD_NUM_LOCK = 0x0020;
    // const GLFW_MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1;
    // const GLFW_MOUSE_BUTTON_2 = 1;
    // const GLFW_MOUSE_BUTTON_3 = 2;
    // const GLFW_MOUSE_BUTTON_4 = 3;
    // const GLFW_MOUSE_BUTTON_5 = 4;
    // const GLFW_MOUSE_BUTTON_6 = 5;
    // const GLFW_MOUSE_BUTTON_7 = 6;
    // const GLFW_MOUSE_BUTTON_8 = 7;
    // const GLFW_MOUSE_BUTTON_LAST = GLFW_MOUSE_BUTTON_8;
    // const GLFW_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_1;
    // const GLFW_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_2;
    // const GLFW_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_3;
    // const GLFW_JOYSTICK_1 = GLFW_JOYSTICK_1;
    // const GLFW_JOYSTICK_2 = 1;
    // const GLFW_JOYSTICK_3 = 2;
    // const GLFW_JOYSTICK_4 = 3;
    // const GLFW_JOYSTICK_5 = 4;
    // const GLFW_JOYSTICK_6 = 5;
    // const GLFW_JOYSTICK_7 = 6;
    // const GLFW_JOYSTICK_8 = 7;
    // const GLFW_JOYSTICK_9 = 8;
    // const GLFW_JOYSTICK_10 = 9;
    // const GLFW_JOYSTICK_11 = 10;
    // const GLFW_JOYSTICK_12 = 11;
    // const GLFW_JOYSTICK_13 = 12;
    // const GLFW_JOYSTICK_14 = 13;
    // const GLFW_JOYSTICK_15 = 14;
    // const GLFW_JOYSTICK_16 = 15;
    // const GLFW_JOYSTICK_LAST = GLFW_JOYSTICK_16;
    // const GLFW_GAMEPAD_BUTTON_A = GLFW_GAMEPAD_BUTTON_A;
    // const GLFW_GAMEPAD_BUTTON_B = 1;
    // const GLFW_GAMEPAD_BUTTON_X = 2;
    // const GLFW_GAMEPAD_BUTTON_Y = 3;
    // const GLFW_GAMEPAD_BUTTON_LEFT_BUMPER = 4;
    // const GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER = 5;
    // const GLFW_GAMEPAD_BUTTON_BACK = 6;
    // const GLFW_GAMEPAD_BUTTON_START = 7;
    // const GLFW_GAMEPAD_BUTTON_GUIDE = 8;
    // const GLFW_GAMEPAD_BUTTON_LEFT_THUMB = 9;
    // const GLFW_GAMEPAD_BUTTON_RIGHT_THUMB = 10;
    // const GLFW_GAMEPAD_BUTTON_DPAD_UP = 11;
    // const GLFW_GAMEPAD_BUTTON_DPAD_RIGHT = 12;
    // const GLFW_GAMEPAD_BUTTON_DPAD_DOWN = 13;
    // const GLFW_GAMEPAD_BUTTON_DPAD_LEFT = 14;
    // const GLFW_GAMEPAD_BUTTON_LAST = GLFW_GAMEPAD_BUTTON_DPAD_LEFT;
    // const GLFW_GAMEPAD_BUTTON_CROSS = GLFW_GAMEPAD_BUTTON_A;
    // const GLFW_GAMEPAD_BUTTON_CIRCLE = GLFW_GAMEPAD_BUTTON_B;
    // const GLFW_GAMEPAD_BUTTON_SQUARE = GLFW_GAMEPAD_BUTTON_X;
    // const GLFW_GAMEPAD_BUTTON_TRIANGLE = GLFW_GAMEPAD_BUTTON_Y;
    // const GLFW_GAMEPAD_AXIS_LEFT_X = GLFW_GAMEPAD_AXIS_LEFT_X;
    // const GLFW_GAMEPAD_AXIS_LEFT_Y = 1;
    // const GLFW_GAMEPAD_AXIS_RIGHT_X = 2;
    // const GLFW_GAMEPAD_AXIS_RIGHT_Y = 3;
    // const GLFW_GAMEPAD_AXIS_LEFT_TRIGGER = 4;
    // const GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER = 5;
    // const GLFW_GAMEPAD_AXIS_LAST = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER;
    // const GLFW_NO_ERROR = GLFW_NO_ERROR;
    // const GLFW_NOT_INITIALIZED = 0x00010001;
    // const GLFW_NO_CURRENT_CONTEXT = 0x00010002;
    // const GLFW_INVALID_ENUM = 0x00010003;
    // const GLFW_INVALID_VALUE = 0x00010004;
    // const GLFW_OUT_OF_MEMORY = 0x00010005;
    // const GLFW_API_UNAVAILABLE = 0x00010006;
    // const GLFW_VERSION_UNAVAILABLE = 0x00010007;
    // const GLFW_PLATFORM_ERROR = 0x00010008;
    // const GLFW_FORMAT_UNAVAILABLE = 0x00010009;
    // const GLFW_NO_WINDOW_CONTEXT = 0x0001000A;
    // const GLFW_FOCUSED = 0x00020001;
    // const GLFW_ICONIFIED = 0x00020002;
    // const GLFW_RESIZABLE = 0x00020003;
    // const GLFW_VISIBLE = 0x00020004;
    // const GLFW_DECORATED = 0x00020005;
    // const GLFW_AUTO_ICONIFY = 0x00020006;
    // const GLFW_FLOATING = 0x00020007;
    // const GLFW_MAXIMIZED = 0x00020008;
    // const GLFW_CENTER_CURSOR = 0x00020009;
    // const GLFW_TRANSPARENT_FRAMEBUFFER = 0x0002000A;
    // const GLFW_HOVERED = 0x0002000B;
    // const GLFW_FOCUS_ON_SHOW = 0x0002000C;
    // const GLFW_RED_BITS = 0x00021001;
    // const GLFW_GREEN_BITS = 0x00021002;
    // const GLFW_BLUE_BITS = 0x00021003;
    // const GLFW_ALPHA_BITS = 0x00021004;
    // const GLFW_DEPTH_BITS = 0x00021005;
    // const GLFW_STENCIL_BITS = 0x00021006;
    // const GLFW_ACCUM_RED_BITS = 0x00021007;
    // const GLFW_ACCUM_GREEN_BITS = 0x00021008;
    // const GLFW_ACCUM_BLUE_BITS = 0x00021009;
    // const GLFW_ACCUM_ALPHA_BITS = 0x0002100A;
    // const GLFW_AUX_BUFFERS = 0x0002100B;
    // const GLFW_STEREO = 0x0002100C;
    // const GLFW_SAMPLES = 0x0002100D;
    // const GLFW_SRGB_CAPABLE = 0x0002100E;
    // const GLFW_REFRESH_RATE = 0x0002100F;
    // const GLFW_DOUBLEBUFFER = 0x00021010;
    // const GLFW_CLIENT_API = 0x00022001;
    // const GLFW_CONTEXT_VERSION_MAJOR = 0x00022002;
    // const GLFW_CONTEXT_VERSION_MINOR = 0x00022003;
    // const GLFW_CONTEXT_REVISION = 0x00022004;
    // const GLFW_CONTEXT_ROBUSTNESS = 0x00022005;
    // const GLFW_OPENGL_FORWARD_COMPAT = 0x00022006;
    // const GLFW_OPENGL_DEBUG_CONTEXT = 0x00022007;
    // const GLFW_OPENGL_PROFILE = 0x00022008;
    // const GLFW_CONTEXT_RELEASE_BEHAVIOR = 0x00022009;
    // const GLFW_CONTEXT_NO_ERROR = 0x0002200A;
    // const GLFW_CONTEXT_CREATION_API = 0x0002200B;
    // const GLFW_SCALE_TO_MONITOR = 0x0002200C;
    // const GLFW_COCOA_RETINA_FRAMEBUFFER = 0x00023001;
    // const GLFW_COCOA_FRAME_NAME = 0x00023002;
    // const GLFW_COCOA_GRAPHICS_SWITCHING = 0x00023003;
    // const GLFW_X11_CLASS_NAME = 0x00024001;
    // const GLFW_X11_INSTANCE_NAME = 0x00024002;
    // const GLFW_NO_API = GLFW_NO_API;
    // const GLFW_OPENGL_API = 0x00030001;
    // const GLFW_OPENGL_ES_API = 0x00030002;
    // const GLFW_NO_ROBUSTNESS = GLFW_NO_ROBUSTNESS;
    // const GLFW_NO_RESET_NOTIFICATION = 0x00031001;
    // const GLFW_LOSE_CONTEXT_ON_RESET = 0x00031002;
    // const GLFW_OPENGL_ANY_PROFILE = GLFW_OPENGL_ANY_PROFILE;
    // const GLFW_OPENGL_CORE_PROFILE = 0x00032001;
    // const GLFW_OPENGL_COMPAT_PROFILE = 0x00032002;
    // const GLFW_CURSOR = 0x00033001;
    // const GLFW_STICKY_KEYS = 0x00033002;
    // const GLFW_STICKY_MOUSE_BUTTONS = 0x00033003;
    // const GLFW_LOCK_KEY_MODS = 0x00033004;
    // const GLFW_RAW_MOUSE_MOTION = 0x00033005;
    // const GLFW_CURSOR_NORMAL = 0x00034001;
    // const GLFW_CURSOR_HIDDEN = 0x00034002;
    // const GLFW_CURSOR_DISABLED = 0x00034003;
    // const GLFW_ANY_RELEASE_BEHAVIOR = GLFW_ANY_RELEASE_BEHAVIOR;
    // const GLFW_RELEASE_BEHAVIOR_FLUSH = 0x00035001;
    // const GLFW_RELEASE_BEHAVIOR_NONE = 0x00035002;
    // const GLFW_NATIVE_CONTEXT_API = 0x00036001;
    // const GLFW_EGL_CONTEXT_API = 0x00036002;
    // const GLFW_OSMESA_CONTEXT_API = 0x00036003;
    // const GLFW_ARROW_CURSOR = 0x00036001;
    // const GLFW_IBEAM_CURSOR = 0x00036002;
    // const GLFW_CROSSHAIR_CURSOR = 0x00036003;
    // const GLFW_HAND_CURSOR = 0x00036004;
    // const GLFW_HRESIZE_CURSOR = 0x00036005;
    // const GLFW_VRESIZE_CURSOR = 0x00036006;
    // const GLFW_CONNECTED = 0x00040001;
    // const GLFW_DISCONNECTED = 0x00040002;
    // const GLFW_JOYSTICK_HAT_BUTTONS = 0x00050001;
    // const GLFW_COCOA_CHDIR_RESOURCES = 0x00051001;
    // const GLFW_COCOA_MENUBAR = 0x00051002;
    // const GLFW_DONT_CARE = -1;

    /**
     * Functions
     * ----------------------------------------------------------------------------
     */
    function glCullFace(int $mode) : void {}
    function glFrontFace(int $mode) : void {}
    function glHint(int $target, int $mode) : void {}
    function glLineWidth(float $width) : void {}
    function glPointSize(float $size) : void {}
    function glPolygonMode(int $face, int $mode) : void {}
    function glScissor(int $x, int $y, int $width, int $height) : void {}
    function glTexParameterf(int $target, int $pname, float $param) : void {}
    function glTexParameterfv(int $target, int $pname, \GL\Buffer\FloatBuffer|array $params) : void {}
    function glTexParameteri(int $target, int $pname, int $param) : void {}
    function glTexParameteriv(int $target, int $pname, \GL\Buffer\IntBuffer|array $params) : void {}
    function glTexImage2D(int $target, int $level, int $internalformat, int $width, int $height, int $border, int $format, int $type, ?\GL\Buffer\BufferInterface $data) : void {}
    function glDrawBuffer(int $buf) : void {}
    function glClear(int $mask) : void {}
    function glClearColor(float $red, float $green, float $blue, float $alpha) : void {}
    function glClearStencil(int $s) : void {}
    function glClearDepth(float $depth) : void {}
    function glStencilMask(int $mask) : void {}
    function glColorMask(bool $red, bool $green, bool $blue, bool $alpha) : void {}
    function glDepthMask(bool $flag) : void {}
    function glDisable(int $cap) : void {}
    function glEnable(int $cap) : void {}
    function glFinish() : void {}
    function glFlush() : void {}
    function glBlendFunc(int $sfactor, int $dfactor) : void {}
    function glLogicOp(int $opcode) : void {}
    function glStencilFunc(int $func, int $ref, int $mask) : void {}
    function glStencilOp(int $fail, int $zfail, int $zpass) : void {}
    function glDepthFunc(int $func) : void {}
    function glPixelStoref(int $pname, float $param) : void {}
    function glPixelStorei(int $pname, int $param) : void {}
    function glReadBuffer(int $src) : void {}
    function glReadPixels(int $x, int $y, int $width, int $height, int $format, int $type, \GL\Buffer\BufferInterface $pixels) : void {}
    function glGetBooleanv(int $pname, ?bool &...$data) : void {}
    function glGetDoublev(int $pname, ?bool &...$data) : void {}
    function glGetError() : int {}
    function glGetFloatv(int $pname, ?bool &...$data) : void {}
    function glGetIntegerv(int $pname, ?bool &...$data) : void {}
    function glGetString(int $name) : string {}
    function glGetTexImage(int $target, int $level, int $format, int $type, \GL\Buffer\BufferInterface $pixels) : void {}
    function glGetTexParameterfv(int $target, int $pname, ?bool &...$params) : void {}
    function glGetTexParameteriv(int $target, int $pname, ?bool &...$params) : void {}
    function glGetTexLevelParameterfv(int $target, int $level, int $pname, float &$params) : void {}
    function glGetTexLevelParameteriv(int $target, int $level, int $pname, int &$params) : void {}
    function glIsEnabled(int $cap) : bool {}
    function glDepthRange(float $n, float $f) : void {}
    function glViewport(int $x, int $y, int $width, int $height) : void {}
    function glDrawArrays(int $mode, int $first, int $count) : void {}
    function glPolygonOffset(float $factor, float $units) : void {}
    function glCopyTexImage1D(int $target, int $level, int $internalformat, int $x, int $y, int $width, int $border) : void {}
    function glCopyTexImage2D(int $target, int $level, int $internalformat, int $x, int $y, int $width, int $height, int $border) : void {}
    function glCopyTexSubImage1D(int $target, int $level, int $xoffset, int $x, int $y, int $width) : void {}
    function glCopyTexSubImage2D(int $target, int $level, int $xoffset, int $yoffset, int $x, int $y, int $width, int $height) : void {}
    function glBindTexture(int $target, int $texture) : void {}
    function glDeleteTextures(int $n, ?int ...$textures) : void {}
    function glGenTextures(int $n, ?int &...$textures) : void {}
    function glIsTexture(int $texture) : bool {}
    function glCopyTexSubImage3D(int $target, int $level, int $xoffset, int $yoffset, int $zoffset, int $x, int $y, int $width, int $height) : void {}
    function glActiveTexture(int $texture) : void {}
    function glSampleCoverage(float $value, bool $invert) : void {}
    function glBlendFuncSeparate(int $sfactorRGB, int $dfactorRGB, int $sfactorAlpha, int $dfactorAlpha) : void {}
    function glPointParameterf(int $pname, float $param) : void {}
    function glPointParameterfv(int $pname, \GL\Buffer\FloatBuffer|array $params) : void {}
    function glPointParameteri(int $pname, int $param) : void {}
    function glPointParameteriv(int $pname, \GL\Buffer\IntBuffer|array $params) : void {}
    function glBlendColor(float $red, float $green, float $blue, float $alpha) : void {}
    function glBlendEquation(int $mode) : void {}
    function glGenQueries(int $n, ?int &...$ids) : void {}
    function glDeleteQueries(int $n, ?int ...$ids) : void {}
    function glIsQuery(int $id) : bool {}
    function glBeginQuery(int $target, int $id) : void {}
    function glEndQuery(int $target) : void {}
    function glGetQueryiv(int $target, int $pname, int &$params) : void {}
    function glGetQueryObjectiv(int $id, int $pname, int &$params) : void {}
    function glGetQueryObjectuiv(int $id, int $pname, int &$params) : void {}
    function glBindBuffer(int $target, int $buffer) : void {}
    function glDeleteBuffers(int $n, ?int ...$buffers) : void {}
    function glGenBuffers(int $n, ?int &...$buffers) : void {}
    function glIsBuffer(int $buffer) : bool {}
    function glUnmapBuffer(int $target) : bool {}
    function glGetBufferParameteriv(int $target, int $pname, int &$params) : void {}
    function glBlendEquationSeparate(int $modeRGB, int $modeAlpha) : void {}
    function glDrawBuffers(int $n, ?int ...$bufs) : void {}
    function glStencilOpSeparate(int $face, int $sfail, int $dpfail, int $dppass) : void {}
    function glStencilFuncSeparate(int $face, int $func, int $ref, int $mask) : void {}
    function glStencilMaskSeparate(int $face, int $mask) : void {}
    function glAttachShader(int $program, int $shader) : void {}
    function glBindAttribLocation(int $program, int $index, string $name) : void {}
    function glCompileShader(int $shader) : void {}
    function glCreateProgram() : int {}
    function glCreateShader(int $type) : int {}
    function glDeleteProgram(int $program) : void {}
    function glDeleteShader(int $shader) : void {}
    function glDetachShader(int $program, int $shader) : void {}
    function glDisableVertexAttribArray(int $index) : void {}
    function glEnableVertexAttribArray(int $index) : void {}
    function glGetAttachedShaders(int $program, int $maxCount, int &$count, int &$shaders) : void {}
    function glGetAttribLocation(int $program, string $name) : int {}
    function glGetProgramiv(int $program, int $pname, int &$params) : void {}
    function glGetProgramInfoLog(int $program, int $bufSize) : string {}
    function glGetShaderiv(int $shader, int $pname, int &$params) : void {}
    function glGetShaderInfoLog(int $shader, int $bufSize) : string {}
    function glGetUniformLocation(int $program, string $name) : int {}
    function glGetUniformfv(int $program, int $location, float &$params) : void {}
    function glGetUniformiv(int $program, int $location, int &$params) : void {}
    function glGetVertexAttribdv(int $index, int $pname, float &$params) : void {}
    function glGetVertexAttribfv(int $index, int $pname, float &$params) : void {}
    function glGetVertexAttribiv(int $index, int $pname, int &$params) : void {}
    function glIsProgram(int $program) : bool {}
    function glIsShader(int $shader) : bool {}
    function glLinkProgram(int $program) : void {}
    function glUseProgram(int $program) : void {}
    function glUniform1f(int $location, float $v0) : void {}
    function glUniform2f(int $location, float $v0, float $v1) : void {}
    function glUniform3f(int $location, float $v0, float $v1, float $v2) : void {}
    function glUniform4f(int $location, float $v0, float $v1, float $v2, float $v3) : void {}
    function glUniform1i(int $location, int $v0) : void {}
    function glUniform2i(int $location, int $v0, int $v1) : void {}
    function glUniform3i(int $location, int $v0, int $v1, int $v2) : void {}
    function glUniform4i(int $location, int $v0, int $v1, int $v2, int $v3) : void {}
    function glUniform1fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniform2fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniform3fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniform4fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniform1iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glUniform2iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glUniform3iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glUniform4iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glUniformMatrix2fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix3fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix4fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glValidateProgram(int $program) : void {}
    function glVertexAttrib1d(int $index, float $x) : void {}
    function glVertexAttrib1dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttrib1f(int $index, float $x) : void {}
    function glVertexAttrib1fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {}
    function glVertexAttrib1s(int $index, int $x) : void {}
    function glVertexAttrib1sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {}
    function glVertexAttrib2d(int $index, float $x, float $y) : void {}
    function glVertexAttrib2dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttrib2f(int $index, float $x, float $y) : void {}
    function glVertexAttrib2fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {}
    function glVertexAttrib2s(int $index, int $x, int $y) : void {}
    function glVertexAttrib2sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {}
    function glVertexAttrib3d(int $index, float $x, float $y, float $z) : void {}
    function glVertexAttrib3dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttrib3f(int $index, float $x, float $y, float $z) : void {}
    function glVertexAttrib3fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {}
    function glVertexAttrib3s(int $index, int $x, int $y, int $z) : void {}
    function glVertexAttrib3sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {}
    function glVertexAttrib4Nbv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {}
    function glVertexAttrib4Niv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glVertexAttrib4Nsv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {}
    function glVertexAttrib4Nub(int $index, int $x, int $y, int $z, int $w) : void {}
    function glVertexAttrib4Nubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {}
    function glVertexAttrib4Nuiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {}
    function glVertexAttrib4Nusv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {}
    function glVertexAttrib4bv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {}
    function glVertexAttrib4d(int $index, float $x, float $y, float $z, float $w) : void {}
    function glVertexAttrib4dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttrib4f(int $index, float $x, float $y, float $z, float $w) : void {}
    function glVertexAttrib4fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {}
    function glVertexAttrib4iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glVertexAttrib4s(int $index, int $x, int $y, int $z, int $w) : void {}
    function glVertexAttrib4sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {}
    function glVertexAttrib4ubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {}
    function glVertexAttrib4uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {}
    function glVertexAttrib4usv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {}
    function glVertexAttribPointer(int $index, int $size, int $type, bool $normalized, int $stride, int $offset) : void {}
    function glUniformMatrix2x3fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix3x2fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix2x4fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix4x2fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix3x4fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glUniformMatrix4x3fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glColorMaski(int $index, bool $r, bool $g, bool $b, bool $a) : void {}
    function glGetBooleani_v(int $target, int $index, ?bool &...$data) : void {}
    function glGetIntegeri_v(int $target, int $index, ?bool &...$data) : void {}
    function glEnablei(int $target, int $index) : void {}
    function glDisablei(int $target, int $index) : void {}
    function glIsEnabledi(int $target, int $index) : bool {}
    function glBeginTransformFeedback(int $primitiveMode) : void {}
    function glEndTransformFeedback() : void {}
    function glBindBufferRange(int $target, int $index, int $buffer, int $offset, int $size) : void {}
    function glBindBufferBase(int $target, int $index, int $buffer) : void {}
    function glClampColor(int $target, int $clamp) : void {}
    function glBeginConditionalRender(int $id, int $mode) : void {}
    function glEndConditionalRender() : void {}
    function glGetVertexAttribIiv(int $index, int $pname, int &$params) : void {}
    function glGetVertexAttribIuiv(int $index, int $pname, int &$params) : void {}
    function glVertexAttribI1i(int $index, int $x) : void {}
    function glVertexAttribI2i(int $index, int $x, int $y) : void {}
    function glVertexAttribI3i(int $index, int $x, int $y, int $z) : void {}
    function glVertexAttribI4i(int $index, int $x, int $y, int $z, int $w) : void {}
    function glVertexAttribI1ui(int $index, int $x) : void {}
    function glVertexAttribI2ui(int $index, int $x, int $y) : void {}
    function glVertexAttribI3ui(int $index, int $x, int $y, int $z) : void {}
    function glVertexAttribI4ui(int $index, int $x, int $y, int $z, int $w) : void {}
    function glVertexAttribI1iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glVertexAttribI2iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glVertexAttribI3iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glVertexAttribI4iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glVertexAttribI1uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {}
    function glVertexAttribI2uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {}
    function glVertexAttribI3uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {}
    function glVertexAttribI4uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {}
    function glVertexAttribI4bv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {}
    function glVertexAttribI4sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {}
    function glVertexAttribI4ubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {}
    function glVertexAttribI4usv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {}
    function glGetUniformuiv(int $program, int $location, int &$params) : void {}
    function glBindFragDataLocation(int $program, int $color, string $name) : void {}
    function glGetFragDataLocation(int $program, string $name) : int {}
    function glUniform1ui(int $location, int $v0) : void {}
    function glUniform2ui(int $location, int $v0, int $v1) : void {}
    function glUniform3ui(int $location, int $v0, int $v1, int $v2) : void {}
    function glUniform4ui(int $location, int $v0, int $v1, int $v2, int $v3) : void {}
    function glUniform1uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glUniform2uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glUniform3uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glUniform4uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glTexParameterIiv(int $target, int $pname, \GL\Buffer\IntBuffer|array $params) : void {}
    function glTexParameterIuiv(int $target, int $pname, \GL\Buffer\UIntBuffer|array $params) : void {}
    function glGetTexParameterIiv(int $target, int $pname, ?bool &...$params) : void {}
    function glGetTexParameterIuiv(int $target, int $pname, ?bool &...$params) : void {}
    function glClearBufferiv(int $buffer, int $drawbuffer, \GL\Buffer\IntBuffer|array $value) : void {}
    function glClearBufferuiv(int $buffer, int $drawbuffer, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glClearBufferfv(int $buffer, int $drawbuffer, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glClearBufferfi(int $buffer, int $drawbuffer, float $depth, int $stencil) : void {}
    function glGetStringi(int $name, int $index) : string {}
    function glIsRenderbuffer(int $renderbuffer) : bool {}
    function glBindRenderbuffer(int $target, int $renderbuffer) : void {}
    function glDeleteRenderbuffers(int $n, ?int ...$renderbuffers) : void {}
    function glGenRenderbuffers(int $n, ?int &...$renderbuffers) : void {}
    function glRenderbufferStorage(int $target, int $internalformat, int $width, int $height) : void {}
    function glGetRenderbufferParameteriv(int $target, int $pname, int &$params) : void {}
    function glIsFramebuffer(int $framebuffer) : bool {}
    function glBindFramebuffer(int $target, int $framebuffer) : void {}
    function glDeleteFramebuffers(int $n, ?int ...$framebuffers) : void {}
    function glGenFramebuffers(int $n, ?int &...$framebuffers) : void {}
    function glCheckFramebufferStatus(int $target) : int {}
    function glFramebufferTexture1D(int $target, int $attachment, int $textarget, int $texture, int $level) : void {}
    function glFramebufferTexture2D(int $target, int $attachment, int $textarget, int $texture, int $level) : void {}
    function glFramebufferTexture3D(int $target, int $attachment, int $textarget, int $texture, int $level, int $zoffset) : void {}
    function glFramebufferRenderbuffer(int $target, int $attachment, int $renderbuffertarget, int $renderbuffer) : void {}
    function glGetFramebufferAttachmentParameteriv(int $target, int $attachment, int $pname, int &$params) : void {}
    function glGenerateMipmap(int $target) : void {}
    function glBlitFramebuffer(int $srcX0, int $srcY0, int $srcX1, int $srcY1, int $dstX0, int $dstY0, int $dstX1, int $dstY1, int $mask, int $filter) : void {}
    function glRenderbufferStorageMultisample(int $target, int $samples, int $internalformat, int $width, int $height) : void {}
    function glFramebufferTextureLayer(int $target, int $attachment, int $texture, int $level, int $layer) : void {}
    function glFlushMappedBufferRange(int $target, int $offset, int $length) : void {}
    function glBindVertexArray(int $array) : void {}
    function glDeleteVertexArrays(int $n, ?int ...$arrays) : void {}
    function glGenVertexArrays(int $n, ?int &...$arrays) : void {}
    function glIsVertexArray(int $array) : bool {}
    function glDrawArraysInstanced(int $mode, int $first, int $count, int $instancecount) : void {}
    function glTexBuffer(int $target, int $internalformat, int $buffer) : void {}
    function glPrimitiveRestartIndex(int $index) : void {}
    function glCopyBufferSubData(int $readTarget, int $writeTarget, int $readOffset, int $writeOffset, int $size) : void {}
    function glGetUniformBlockIndex(int $program, string $uniformBlockName) : int {}
    function glGetActiveUniformBlockiv(int $program, int $uniformBlockIndex, int $pname, int &$params) : void {}
    function glUniformBlockBinding(int $program, int $uniformBlockIndex, int $uniformBlockBinding) : void {}
    function glProvokingVertex(int $mode) : void {}
    function glIsSync(int $sync) : bool {}
    function glDeleteSync(int $sync) : void {}
    function glClientWaitSync(int $sync, int $flags, int $timeout) : int {}
    function glWaitSync(int $sync, int $flags, int $timeout) : void {}
    function glGetInteger64v(int $pname, int &$data) : void {}
    function glGetInteger64i_v(int $target, int $index, int &$data) : void {}
    function glGetBufferParameteri64v(int $target, int $pname, int &$params) : void {}
    function glFramebufferTexture(int $target, int $attachment, int $texture, int $level) : void {}
    function glTexImage2DMultisample(int $target, int $samples, int $internalformat, int $width, int $height, bool $fixedsamplelocations) : void {}
    function glTexImage3DMultisample(int $target, int $samples, int $internalformat, int $width, int $height, int $depth, bool $fixedsamplelocations) : void {}
    function glGetMultisamplefv(int $pname, int $index, float &$val) : void {}
    function glSampleMaski(int $maskNumber, int $mask) : void {}
    function glBindFragDataLocationIndexed(int $program, int $colorNumber, int $index, string $name) : void {}
    function glGetFragDataIndex(int $program, string $name) : int {}
    function glGenSamplers(int $count, ?int &...$samplers) : void {}
    function glDeleteSamplers(int $count, ?int ...$samplers) : void {}
    function glIsSampler(int $sampler) : bool {}
    function glBindSampler(int $unit, int $sampler) : void {}
    function glSamplerParameteri(int $sampler, int $pname, int $param) : void {}
    function glSamplerParameteriv(int $sampler, int $pname, \GL\Buffer\IntBuffer|array $param) : void {}
    function glSamplerParameterf(int $sampler, int $pname, float $param) : void {}
    function glSamplerParameterfv(int $sampler, int $pname, \GL\Buffer\FloatBuffer|array $param) : void {}
    function glSamplerParameterIiv(int $sampler, int $pname, \GL\Buffer\IntBuffer|array $param) : void {}
    function glSamplerParameterIuiv(int $sampler, int $pname, \GL\Buffer\UIntBuffer|array $param) : void {}
    function glGetSamplerParameteriv(int $sampler, int $pname, int &$params) : void {}
    function glGetSamplerParameterIiv(int $sampler, int $pname, int &$params) : void {}
    function glGetSamplerParameterfv(int $sampler, int $pname, float &$params) : void {}
    function glGetSamplerParameterIuiv(int $sampler, int $pname, int &$params) : void {}
    function glQueryCounter(int $id, int $target) : void {}
    function glGetQueryObjecti64v(int $id, int $pname, int &$params) : void {}
    function glGetQueryObjectui64v(int $id, int $pname, int &$params) : void {}
    function glVertexAttribDivisor(int $index, int $divisor) : void {}
    function glVertexAttribP1ui(int $index, int $type, bool $normalized, int $value) : void {}
    function glVertexAttribP1uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glVertexAttribP2ui(int $index, int $type, bool $normalized, int $value) : void {}
    function glVertexAttribP2uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glVertexAttribP3ui(int $index, int $type, bool $normalized, int $value) : void {}
    function glVertexAttribP3uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glVertexAttribP4ui(int $index, int $type, bool $normalized, int $value) : void {}
    function glVertexAttribP4uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glVertexP2ui(int $type, int $value) : void {}
    function glVertexP2uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glVertexP3ui(int $type, int $value) : void {}
    function glVertexP3uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glVertexP4ui(int $type, int $value) : void {}
    function glVertexP4uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glTexCoordP1ui(int $type, int $coords) : void {}
    function glTexCoordP1uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glTexCoordP2ui(int $type, int $coords) : void {}
    function glTexCoordP2uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glTexCoordP3ui(int $type, int $coords) : void {}
    function glTexCoordP3uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glTexCoordP4ui(int $type, int $coords) : void {}
    function glTexCoordP4uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glMultiTexCoordP1ui(int $texture, int $type, int $coords) : void {}
    function glMultiTexCoordP1uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glMultiTexCoordP2ui(int $texture, int $type, int $coords) : void {}
    function glMultiTexCoordP2uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glMultiTexCoordP3ui(int $texture, int $type, int $coords) : void {}
    function glMultiTexCoordP3uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glMultiTexCoordP4ui(int $texture, int $type, int $coords) : void {}
    function glMultiTexCoordP4uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glNormalP3ui(int $type, int $coords) : void {}
    function glNormalP3uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {}
    function glColorP3ui(int $type, int $color) : void {}
    function glColorP3uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {}
    function glColorP4ui(int $type, int $color) : void {}
    function glColorP4uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {}
    function glSecondaryColorP3ui(int $type, int $color) : void {}
    function glSecondaryColorP3uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {}
    function glMinSampleShading(float $value) : void {}
    function glBlendEquationi(int $buf, int $mode) : void {}
    function glBlendEquationSeparatei(int $buf, int $modeRGB, int $modeAlpha) : void {}
    function glBlendFunci(int $buf, int $src, int $dst) : void {}
    function glBlendFuncSeparatei(int $buf, int $srcRGB, int $dstRGB, int $srcAlpha, int $dstAlpha) : void {}
    function glUniform1d(int $location, float $x) : void {}
    function glUniform2d(int $location, float $x, float $y) : void {}
    function glUniform3d(int $location, float $x, float $y, float $z) : void {}
    function glUniform4d(int $location, float $x, float $y, float $z, float $w) : void {}
    function glUniform1dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniform2dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniform3dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniform4dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix2dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix3dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix4dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix2x3dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix2x4dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix3x2dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix3x4dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix4x2dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glUniformMatrix4x3dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glGetUniformdv(int $program, int $location, float &$params) : void {}
    function glGetSubroutineUniformLocation(int $program, int $shadertype, string $name) : int {}
    function glGetSubroutineIndex(int $program, int $shadertype, string $name) : int {}
    function glGetActiveSubroutineUniformiv(int $program, int $shadertype, int $index, int $pname, int &$values) : void {}
    function glUniformSubroutinesuiv(int $shadertype, \GL\Buffer\UIntBuffer|array $indices) : void {}
    function glGetUniformSubroutineuiv(int $shadertype, int $location, int &$params) : void {}
    function glGetProgramStageiv(int $program, int $shadertype, int $pname, int &$values) : void {}
    function glPatchParameteri(int $pname, int $value) : void {}
    function glPatchParameterfv(int $pname, \GL\Buffer\FloatBuffer|array $values) : void {}
    function glBindTransformFeedback(int $target, int $id) : void {}
    function glDeleteTransformFeedbacks(int $n, ?int ...$ids) : void {}
    function glGenTransformFeedbacks(int $n, ?int &...$ids) : void {}
    function glIsTransformFeedback(int $id) : bool {}
    function glPauseTransformFeedback() : void {}
    function glResumeTransformFeedback() : void {}
    function glDrawTransformFeedback(int $mode, int $id) : void {}
    function glDrawTransformFeedbackStream(int $mode, int $id, int $stream) : void {}
    function glBeginQueryIndexed(int $target, int $index, int $id) : void {}
    function glEndQueryIndexed(int $target, int $index) : void {}
    function glGetQueryIndexediv(int $target, int $index, int $pname, int &$params) : void {}
    function glReleaseShaderCompiler() : void {}
    function glGetShaderPrecisionFormat(int $shadertype, int $precisiontype, int &$range, int &$precision) : void {}
    function glDepthRangef(float $n, float $f) : void {}
    function glClearDepthf(float $d) : void {}
    function glProgramParameteri(int $program, int $pname, int $value) : void {}
    function glUseProgramStages(int $pipeline, int $stages, int $program) : void {}
    function glActiveShaderProgram(int $pipeline, int $program) : void {}
    function glBindProgramPipeline(int $pipeline) : void {}
    function glDeleteProgramPipelines(int $n, ?int ...$pipelines) : void {}
    function glGenProgramPipelines(int $n, ?int &...$pipelines) : void {}
    function glIsProgramPipeline(int $pipeline) : bool {}
    function glGetProgramPipelineiv(int $pipeline, int $pname, int &$params) : void {}
    function glProgramUniform1i(int $program, int $location, int $v0) : void {}
    function glProgramUniform1iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glProgramUniform1f(int $program, int $location, float $v0) : void {}
    function glProgramUniform1fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniform1d(int $program, int $location, float $v0) : void {}
    function glProgramUniform1dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniform1ui(int $program, int $location, int $v0) : void {}
    function glProgramUniform1uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glProgramUniform2i(int $program, int $location, int $v0, int $v1) : void {}
    function glProgramUniform2iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glProgramUniform2f(int $program, int $location, float $v0, float $v1) : void {}
    function glProgramUniform2fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniform2d(int $program, int $location, float $v0, float $v1) : void {}
    function glProgramUniform2dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniform2ui(int $program, int $location, int $v0, int $v1) : void {}
    function glProgramUniform2uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glProgramUniform3i(int $program, int $location, int $v0, int $v1, int $v2) : void {}
    function glProgramUniform3iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glProgramUniform3f(int $program, int $location, float $v0, float $v1, float $v2) : void {}
    function glProgramUniform3fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniform3d(int $program, int $location, float $v0, float $v1, float $v2) : void {}
    function glProgramUniform3dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniform3ui(int $program, int $location, int $v0, int $v1, int $v2) : void {}
    function glProgramUniform3uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glProgramUniform4i(int $program, int $location, int $v0, int $v1, int $v2, int $v3) : void {}
    function glProgramUniform4iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {}
    function glProgramUniform4f(int $program, int $location, float $v0, float $v1, float $v2, float $v3) : void {}
    function glProgramUniform4fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniform4d(int $program, int $location, float $v0, float $v1, float $v2, float $v3) : void {}
    function glProgramUniform4dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniform4ui(int $program, int $location, int $v0, int $v1, int $v2, int $v3) : void {}
    function glProgramUniform4uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {}
    function glProgramUniformMatrix2fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix3fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix4fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix2dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix3dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix4dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix2x3fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix3x2fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix2x4fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix4x2fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix3x4fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix4x3fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {}
    function glProgramUniformMatrix2x3dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix3x2dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix2x4dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix4x2dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix3x4dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glProgramUniformMatrix4x3dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {}
    function glValidateProgramPipeline(int $pipeline) : void {}
    function glVertexAttribL1d(int $index, float $x) : void {}
    function glVertexAttribL2d(int $index, float $x, float $y) : void {}
    function glVertexAttribL3d(int $index, float $x, float $y, float $z) : void {}
    function glVertexAttribL4d(int $index, float $x, float $y, float $z, float $w) : void {}
    function glVertexAttribL1dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttribL2dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttribL3dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glVertexAttribL4dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glGetVertexAttribLdv(int $index, int $pname, float &$params) : void {}
    function glViewportArrayv(int $first, \GL\Buffer\FloatBuffer|array $v) : void {}
    function glViewportIndexedf(int $index, float $x, float $y, float $w, float $h) : void {}
    function glViewportIndexedfv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {}
    function glScissorArrayv(int $first, \GL\Buffer\IntBuffer|array $v) : void {}
    function glScissorIndexed(int $index, int $left, int $bottom, int $width, int $height) : void {}
    function glScissorIndexedv(int $index, \GL\Buffer\IntBuffer|array $v) : void {}
    function glDepthRangeArrayv(int $first, \GL\Buffer\DoubleBuffer|array $v) : void {}
    function glDepthRangeIndexed(int $index, float $n, float $f) : void {}
    function glGetFloati_v(int $target, int $index, ?bool &...$data) : void {}
    function glGetDoublei_v(int $target, int $index, ?bool &...$data) : void {}
    function glfwInit() : int {}
    function glfwTerminate() : void {}
    function glfwInitHint(int $hint, int $value) : void {}
    function glfwGetVersion(int &$major, int &$minor, int &$rev) : void {}
    function glfwGetVersionString() : string {}
    function glfwGetPrimaryMonitor() : GLFWmonitor {}
    function glfwGetMonitorPos(GLFWmonitor $monitor, int &$xpos, int &$ypos) : void {}
    function glfwGetMonitorWorkarea(GLFWmonitor $monitor, int &$xpos, int &$ypos, int &$width, int &$height) : void {}
    function glfwGetMonitorPhysicalSize(GLFWmonitor $monitor, int &$widthMM, int &$heightMM) : void {}
    function glfwGetMonitorContentScale(GLFWmonitor $monitor, float &$xscale, float &$yscale) : void {}
    function glfwGetMonitorName(GLFWmonitor $monitor) : string {}
    function glfwSetGamma(GLFWmonitor $monitor, float $gamma) : void {}
    function glfwDefaultWindowHints() : void {}
    function glfwWindowHint(int $hint, int $value) : void {}
    function glfwWindowHintString(int $hint, string $value) : void {}
    function glfwCreateWindow(int $width, int $height, string $title, ?GLFWmonitor $monitor = NULL, ?GLFWwindow $share = NULL) : GLFWwindow {}
    function glfwDestroyWindow(GLFWwindow $window) : void {}
    function glfwWindowShouldClose(GLFWwindow $window) : int {}
    function glfwSetWindowShouldClose(GLFWwindow $window, int $value) : void {}
    function glfwSetWindowTitle(GLFWwindow $window, string $title) : void {}
    function glfwGetWindowPos(GLFWwindow $window, int &$xpos, int &$ypos) : void {}
    function glfwSetWindowPos(GLFWwindow $window, int $xpos, int $ypos) : void {}
    function glfwGetWindowSize(GLFWwindow $window, int &$width, int &$height) : void {}
    function glfwSetWindowSizeLimits(GLFWwindow $window, int $minwidth, int $minheight, int $maxwidth, int $maxheight) : void {}
    function glfwSetWindowAspectRatio(GLFWwindow $window, int $numer, int $denom) : void {}
    function glfwSetWindowSize(GLFWwindow $window, int $width, int $height) : void {}
    function glfwGetFramebufferSize(GLFWwindow $window, int &$width, int &$height) : void {}
    function glfwGetWindowFrameSize(GLFWwindow $window, int &$left, int &$top, int &$right, int &$bottom) : void {}
    function glfwGetWindowContentScale(GLFWwindow $window, float &$xscale, float &$yscale) : void {}
    function glfwGetWindowOpacity(GLFWwindow $window) : float {}
    function glfwSetWindowOpacity(GLFWwindow $window, float $opacity) : void {}
    function glfwIconifyWindow(GLFWwindow $window) : void {}
    function glfwRestoreWindow(GLFWwindow $window) : void {}
    function glfwMaximizeWindow(GLFWwindow $window) : void {}
    function glfwShowWindow(GLFWwindow $window) : void {}
    function glfwHideWindow(GLFWwindow $window) : void {}
    function glfwFocusWindow(GLFWwindow $window) : void {}
    function glfwRequestWindowAttention(GLFWwindow $window) : void {}
    function glfwGetWindowMonitor(GLFWwindow $window) : GLFWmonitor {}
    function glfwSetWindowMonitor(GLFWwindow $window, GLFWmonitor $monitor, int $xpos, int $ypos, int $width, int $height, int $refreshRate) : void {}
    function glfwGetWindowAttrib(GLFWwindow $window, int $attrib) : int {}
    function glfwSetWindowAttrib(GLFWwindow $window, int $attrib, int $value) : void {}
    function glfwSetWindowPosCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowSizeCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowCloseCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowRefreshCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowFocusCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowIconifyCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowMaximizeCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetFramebufferSizeCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetWindowContentScaleCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwPollEvents() : void {}
    function glfwWaitEvents() : void {}
    function glfwWaitEventsTimeout(float $timeout) : void {}
    function glfwPostEmptyEvent() : void {}
    function glfwGetInputMode(GLFWwindow $window, int $mode) : int {}
    function glfwSetInputMode(GLFWwindow $window, int $mode, int $value) : void {}
    function glfwRawMouseMotionSupported() : int {}
    function glfwGetKeyName(int $key, int $scancode) : string {}
    function glfwGetKeyScancode(int $key) : int {}
    function glfwGetKey(GLFWwindow $window, int $key) : int {}
    function glfwGetMouseButton(GLFWwindow $window, int $button) : int {}
    function glfwGetCursorPos(GLFWwindow $window, float &$xpos, float &$ypos) : void {}
    function glfwSetCursorPos(GLFWwindow $window, float $xpos, float $ypos) : void {}
    function glfwCreateStandardCursor(int $shape) : GLFWcursor {}
    function glfwDestroyCursor(GLFWcursor $cursor) : void {}
    function glfwSetCursor(GLFWwindow $window, GLFWcursor $cursor) : void {}
    function glfwSetKeyCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetCharCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetCharModsCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetMouseButtonCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetCursorPosCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetCursorEnterCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetScrollCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwSetDropCallback(GLFWwindow $window, callable $callback) : void {}
    function glfwJoystickPresent(int $jid) : int {}
    function glfwGetJoystickName(int $jid) : string {}
    function glfwGetJoystickGUID(int $jid) : string {}
    function glfwJoystickIsGamepad(int $jid) : int {}
    function glfwUpdateGamepadMappings(string $string) : int {}
    function glfwGetGamepadName(int $jid) : string {}
    function glfwSetClipboardString(GLFWwindow $window, string $string) : void {}
    function glfwGetClipboardString(GLFWwindow $window) : string {}
    function glfwGetTime() : float {}
    function glfwSetTime(float $time) : void {}
    function glfwMakeContextCurrent(GLFWwindow $window) : void {}
    function glfwGetCurrentContext() : GLFWwindow {}
    function glfwSwapBuffers(GLFWwindow $window) : void {}
    function glfwSwapInterval(int $interval) : void {}
    function glfwExtensionSupported(string $extension) : int {}
    function glfwVulkanSupported() : int {}
    function glShaderSource(int $shader, string $source) : void {}
    function glBufferData(int $target, \GL\Buffer\BufferInterface $buffer, int $usage) : void {}
    function glUniformMatrix4f(int $location, bool $transpose, \GL\Math\Mat4 $matrix) : void {}
    function glUniformVec2f(int $location, \GL\Math\Vec2 $vec) : void {}
    function glUniformVec3f(int $location, \GL\Math\Vec3 $vec) : void {}
    function glUniformVec4f(int $location, \GL\Math\Vec4 $vec) : void {}
 
}
