<?php 

namespace GL\Tests\Noise;

use GL\Buffer\FloatBuffer;
use GL\Buffer\UByteBuffer;
use GL\Math\Vec3;
use GL\Noise;
use GL\Texture\Texture2D;

class NoiseTest extends \PHPUnit\Framework\TestCase
{
    // we need to ensure that the genrated noise is static
    // as someone might build something based on this it is SUPER important
    // that these values are consietent and NEVER change.
    // Which is why we have them in a unittest even though
    // the noise is implemented in a external library..
    // public function testGenTestValues()
    // {
    //     echo str_repeat('-', 80) . PHP_EOL;
    //     $precision = 2;
    //     for($i=0; $i<20; $i++) {
    //         $vec = new Vec3(
    //             mt_rand() / mt_getrandmax() * 2 - 1,
    //             mt_rand() / mt_getrandmax() * 2 - 1,
    //             mt_rand() / mt_getrandmax() * 2 - 1
    //         );

    //         // 50/50 change of beeing -1 to 1 or larger
    //         if (mt_rand() % 2 == 0) {
    //             $vec->x = $vec->x + mt_rand(-32768, 32768);
    //             $vec->y = $vec->y + mt_rand(-32768, 32768);
    //             $vec->z = $vec->z + mt_rand(-32768, 32768);
    //         }

    //         $vec->x = round($vec->x, $precision);
    //         $vec->y = round($vec->y, $precision);
    //         $vec->z = round($vec->z, $precision);

    //         $val = Noise::turbulence($vec->x, $vec->y, $vec->z);

    //         $xStr = str_pad(round($vec->x, $precision), 9, ' ', STR_PAD_LEFT);
    //         $yStr = str_pad(round($vec->y, $precision), 9, ' ', STR_PAD_LEFT);
    //         $zStr = str_pad(round($vec->z, $precision), 9, ' ', STR_PAD_LEFT);
    //         $valStr = str_pad(round($val, 4), 7, ' ', STR_PAD_LEFT);

    //         echo "['pos' => new Vec3($xStr, $yStr, $zStr), 'val' => $valStr],".PHP_EOL;
    //     }
        
    //     echo str_repeat('-', 80) . PHP_EOL;
    //     die;
    // }

    public function testPerlin()
    {
        $data = [
            ['pos' => new Vec3(  32040.5,   29064.8,  24620.75), 'val' =>  0.3746],
            ['pos' => new Vec3(     0.08,      0.25,     -0.69), 'val' =>  0.1577],
            ['pos' => new Vec3(     0.57,     -0.66,     -0.07), 'val' =>  0.4016],
            ['pos' => new Vec3(      0.7,      0.92,      0.09), 'val' => -0.1781],
            ['pos' => new Vec3(     0.61,     -0.65,      0.52), 'val' =>  0.3688],
            ['pos' => new Vec3( 25628.44, -25551.85, -25407.63), 'val' =>  0.0491],
            ['pos' => new Vec3(     0.62,      0.11,     -0.81), 'val' =>  0.3695],
            ['pos' => new Vec3(     0.36,     -0.16,     -0.06), 'val' =>  0.3544],
            ['pos' => new Vec3(  5518.27,  10367.97,  31164.48), 'val' =>  0.2496],
            ['pos' => new Vec3( 23708.88,   -4628.4,  12133.12), 'val' => -0.1772],
            ['pos' => new Vec3(  1347.71,  10719.36,   5439.13), 'val' =>  0.2484],
            ['pos' => new Vec3(    -0.45,      0.57,     -0.98), 'val' => -0.2988],
            ['pos' => new Vec3(     0.66,     -0.76,      0.88), 'val' =>  0.3502],
            ['pos' => new Vec3(     0.26,      0.18,     -0.27), 'val' =>  0.1673],
            ['pos' => new Vec3(  1983.15,  -4793.38,  30170.52), 'val' =>  0.2857],
            ['pos' => new Vec3( 28325.03,   16507.2,  20610.73), 'val' => -0.3192],
            ['pos' => new Vec3(     0.97,      0.98,      0.76), 'val' => -0.3116],
            ['pos' => new Vec3(     0.89,     -0.65,      0.32), 'val' => -0.0207],
            ['pos' => new Vec3(   199.79,   2256.48,  -26577.8), 'val' =>  0.0736],
            ['pos' => new Vec3( -4049.25,  16867.48, -19879.49), 'val' => -0.2304],
        ];

        foreach($data as $d) {
            $this->assertEqualsWithDelta($d['val'], Noise::perlin($d['pos']->x, $d['pos']->y, $d['pos']->z), 0.01);
        }

        // different seed should produce different results  
        $this->assertNotEquals(Noise::perlin(0.1, 0.2, 0.3), Noise::perlin(0.1, 0.2, 0.3, 0, 0, 0, 1));

        // tests for perlin with seed 42
        $data = [
            ['pos' => new Vec3(-19094.89,  13836.41, -18556.06), 'val' => -0.3535],
            ['pos' => new Vec3(     0.75,      0.71,      0.12), 'val' => -0.2418],
            ['pos' => new Vec3( -21221.6,   3354.96,  -7366.87), 'val' =>  0.2592],
            ['pos' => new Vec3( -3973.75,   8988.31, -22312.22), 'val' =>  0.3754],
            ['pos' => new Vec3(    -0.95,      0.55,      -0.6), 'val' => -0.5007],
            ['pos' => new Vec3(  6681.99,  27187.25,  17316.73), 'val' => -0.2896],
            ['pos' => new Vec3(    -0.08,      0.19,      0.17), 'val' => -0.1702],
            ['pos' => new Vec3(  5056.22, -14295.81,  32316.27), 'val' => -0.1096],
            ['pos' => new Vec3( 13551.89, -21344.49,  14162.44), 'val' => -0.1895],
            ['pos' => new Vec3(    -0.79,      0.83,      0.68), 'val' =>  0.1642],
            ['pos' => new Vec3( 14120.56,  -7589.38,  -8473.53), 'val' =>  0.6263],
            ['pos' => new Vec3( 26284.15,  -7312.05,  11828.85), 'val' =>  0.1956],
            ['pos' => new Vec3(     0.01,     -0.25,     -0.72), 'val' =>  0.2204],
            ['pos' => new Vec3(     0.22,      0.36,     -0.71), 'val' => -0.1243],
            ['pos' => new Vec3(      0.9,     -0.59,      0.79), 'val' =>  0.3189],
            ['pos' => new Vec3(  4552.64, -13244.38,  -9872.69), 'val' =>   0.054],
            ['pos' => new Vec3(-27313.67,  28745.66, -10488.15), 'val' => -0.1717],
            ['pos' => new Vec3(-30453.33,  -3075.07, -26830.04), 'val' =>  0.2992],
            ['pos' => new Vec3(     0.27,       0.5,      0.73), 'val' =>  0.1054],
            ['pos' => new Vec3(    -0.77,      0.38,      0.14), 'val' =>  0.0407],
        ];

        foreach($data as $d) {
            $this->assertEqualsWithDelta($d['val'], Noise::perlin($d['pos']->x, $d['pos']->y, $d['pos']->z, 0, 0, 0, 42), 0.01);
        }
    }

    public function testRidge()
    {
        $data = [
            ['pos' => new Vec3(    -0.32,      0.07,        -1), 'val' =>  0.5673],
            ['pos' => new Vec3(     0.34,     -0.45,     -0.57), 'val' =>  0.1347],
            ['pos' => new Vec3(     0.48,      -0.8,      0.59), 'val' =>  0.2432],
            ['pos' => new Vec3(  9107.35,  15331.24,  -1845.93), 'val' =>  0.5031],
            ['pos' => new Vec3(     -0.8,     -0.74,     -0.31), 'val' =>  0.3863],
            ['pos' => new Vec3( -8873.97,  -9574.93, -32395.34), 'val' =>  0.4498],
            ['pos' => new Vec3(    -0.33,     -0.22,      0.58), 'val' =>  0.6386],
            ['pos' => new Vec3(  6979.96,   8225.32, -10369.87), 'val' =>  0.2255],
            ['pos' => new Vec3( 27971.92,   1787.71,  30859.22), 'val' =>  0.3452],
            ['pos' => new Vec3(    -0.45,     -0.65,      0.69), 'val' =>  0.4644],
            ['pos' => new Vec3(-19285.08,   7295.78, -14628.77), 'val' =>  0.5656],
            ['pos' => new Vec3(  6535.78, -28356.01,  13288.53), 'val' =>  0.6549],
            ['pos' => new Vec3( -3972.71,  20538.52,  -8948.38), 'val' =>  0.5615],
            ['pos' => new Vec3(  5655.23,  -18510.7,   6356.87), 'val' =>  0.7317],
            ['pos' => new Vec3( 20140.65,   2490.82,  20677.14), 'val' =>  0.5516],
            ['pos' => new Vec3(  4704.63,  -2340.19,  -2692.89), 'val' =>  0.4658],
            ['pos' => new Vec3(  8749.15,   -1947.9,  27929.42), 'val' =>  0.7276],
            ['pos' => new Vec3( 29529.03, -19754.41,  19928.83), 'val' =>  0.8489],
            ['pos' => new Vec3( 27143.64, -26260.08, -15354.26), 'val' =>  0.1846],
            ['pos' => new Vec3(     0.68,      0.82,       0.1), 'val' =>   0.458],
        ];

        foreach($data as $d) {
            $this->assertEqualsWithDelta($d['val'], Noise::ridge($d['pos']->x, $d['pos']->y, $d['pos']->z), 0.01);
        }
    }

    public function testFbm()
    {
        $data = [
            ['pos' => new Vec3(     0.41,       0.7,     -0.26), 'val' => -0.3938],
            ['pos' => new Vec3(     9049,   5375.33,  -18778.4), 'val' => -0.2687],
            ['pos' => new Vec3( 12209.31, -25210.13,  19329.38), 'val' => -0.1224],
            ['pos' => new Vec3(     0.22,      0.27,      0.96), 'val' =>  0.2104],
            ['pos' => new Vec3(    -0.05,      0.68,     -0.84), 'val' =>  0.1776],
            ['pos' => new Vec3(     0.58,      -0.7,      0.64), 'val' =>  0.3798],
            ['pos' => new Vec3(    -0.89,     -0.06,      0.38), 'val' =>  0.6392],
            ['pos' => new Vec3( 10873.98,   -837.55,   7739.27), 'val' => -0.1308],
            ['pos' => new Vec3(     -0.3,         0,     -0.65), 'val' =>  0.3625],
            ['pos' => new Vec3( 10704.67,   3008.12,   2279.54), 'val' => -0.0747],
            ['pos' => new Vec3(    -0.13,     -0.29,     -0.15), 'val' =>  0.6481],
            ['pos' => new Vec3(     -0.6,      0.39,     -0.52), 'val' => -0.0348],
            ['pos' => new Vec3(    -0.51,     -0.11,     -0.48), 'val' =>   0.619],
            ['pos' => new Vec3(-28410.36,  26136.26, -30562.37), 'val' =>  0.1016],
            ['pos' => new Vec3(    -0.69,      0.43,      -0.3), 'val' => -0.4864],
            ['pos' => new Vec3(-14743.82, -18331.38, -21522.39), 'val' => -0.2004],
            ['pos' => new Vec3( -5479.39,  29147.91,  23889.92), 'val' =>  0.1491],
            ['pos' => new Vec3(     -0.1,      0.37,     -0.39), 'val' => -0.0478],
            ['pos' => new Vec3(     -0.9,     -0.37,     -0.41), 'val' =>  0.2644],
            ['pos' => new Vec3(     0.85,      0.81,      0.11), 'val' => -0.4913],
        ];

        foreach($data as $d) {
            $this->assertEqualsWithDelta($d['val'], Noise::fbm($d['pos']->x, $d['pos']->y, $d['pos']->z), 0.01);
        }
    }

    public function testTurbluence()
    {
        $data = [
            ['pos' => new Vec3(    -0.38,     -0.05,     -0.07), 'val' =>  0.6463],
            ['pos' => new Vec3( -1460.89,  29120.75, -14319.96), 'val' =>  0.4688],
            ['pos' => new Vec3( 26272.07,  -7166.86, -30301.69), 'val' =>  0.2574],
            ['pos' => new Vec3(  3896.23,  15442.09,   6519.79), 'val' =>  0.6583],
            ['pos' => new Vec3(-24264.25, -29763.82,  -6899.45), 'val' =>  0.2612],
            ['pos' => new Vec3( -4368.32, -32502.24, -18114.55), 'val' =>  0.6517],
            ['pos' => new Vec3(     0.82,     -0.62,      -0.5), 'val' =>  0.5227],
            ['pos' => new Vec3( -3333.97, -23620.77,   28683.7), 'val' =>  0.3102],
            ['pos' => new Vec3(     0.86,     -0.67,      0.15), 'val' =>   0.284],
            ['pos' => new Vec3(-11270.61,  -5560.72,   -1549.5), 'val' =>   0.363],
            ['pos' => new Vec3(     0.86,      0.83,     -0.82), 'val' =>  0.4843],
            ['pos' => new Vec3( 28788.08,  12425.12,   -946.06), 'val' =>  0.2703],
            ['pos' => new Vec3(-22873.92,  20340.95,   5988.07), 'val' =>  0.3248],
            ['pos' => new Vec3(      0.5,     -0.26,     -0.58), 'val' =>    0.95],
            ['pos' => new Vec3(     0.03,      0.98,     -0.19), 'val' =>  0.4461],
            ['pos' => new Vec3(     0.27,      0.49,      0.07), 'val' =>   0.708],
            ['pos' => new Vec3(     0.98,     -0.37,     -0.84), 'val' =>  0.2781],
            ['pos' => new Vec3(     0.49,      0.22,     -0.95), 'val' =>  0.5034],
            ['pos' => new Vec3(     0.81,     -0.55,      0.71), 'val' =>  0.5713],
            ['pos' => new Vec3(     0.02,     -0.97,     -0.24), 'val' =>  0.2272],
        ];

        foreach($data as $d) {
            $this->assertEqualsWithDelta($d['val'], Noise::turbulence($d['pos']->x, $d['pos']->y, $d['pos']->z), 0.01);
        }
    }

    public function testPerlinFill2D()
    {
        $size = 1024;
        $buffer = new FloatBuffer();
        Noise::perlinFill2D($buffer, $size, $size, 8.0);
        // Noise::islandFill2D($buffer, $size, $size, 6, 1.0, 2.0);
        // Texture2D::fromBuffer($size, $size, $buffer->quantizeToUChar(), Texture2D::CHANNEL_R)->writePNG('perlinFill2D.png');

        // sample first, last and some in the middle
        $this->assertEqualsWithDelta( 0.000, $buffer[0], 0.01);
        $this->assertEqualsWithDelta(-0.101, $buffer[100_000], 0.01);
        $this->assertEqualsWithDelta( 0.227, $buffer[200_000], 0.01);
        $this->assertEqualsWithDelta( 0.363, $buffer[300_000], 0.01);
        $this->assertEqualsWithDelta(-0.045, $buffer[400_000], 0.01);
        $this->assertEqualsWithDelta( 0.178, $buffer[500_000], 0.01);
        $this->assertEqualsWithDelta(-0.087, $buffer[600_000], 0.01);
        $this->assertEqualsWithDelta( 0.247, $buffer[700_000], 0.01);
        $this->assertEqualsWithDelta( 0.108, $buffer[800_000], 0.01);
        $this->assertEqualsWithDelta(-0.123, $buffer[900_000], 0.01);
        $this->assertEqualsWithDelta( 0.015, $buffer[$size * $size - 2], 0.01);
    }
}