<?php

namespace Tensor\Tests;

use Tensor\Tensor;
use Tensor\Vector;
use Tensor\Matrix;
use Tensor\Special;
use Tensor\ArrayLike;
use Tensor\Algebraic;
use Tensor\Arithmetic;
use Tensor\Comparable;
use Tensor\Statistical;
use Tensor\ColumnVector;
use Tensor\Trigonometric;
use PHPUnit\Framework\TestCase;
use Generator;

/**
 * @covers \Tensor\Vector
 */
class VectorTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    /**
     * @test
     */
    public function build() : void
    {
        $vector = Vector::build([1, 2, 3, 4, 5]);

        $this->assertInstanceOf(Vector::class, $vector);
        $this->assertInstanceOf(Tensor::class, $vector);
        $this->assertInstanceOf(ArrayLike::class, $vector);
        $this->assertInstanceOf(Arithmetic::class, $vector);
        $this->assertInstanceOf(Comparable::class, $vector);
        $this->assertInstanceOf(Algebraic::class, $vector);
        $this->assertInstanceOf(Trigonometric::class, $vector);
        $this->assertInstanceOf(Statistical::class, $vector);
        $this->assertInstanceOf(Special::class, $vector);
    }

    /**
     * @test
     */
    public function zeros() : void
    {
        $zeros = Vector::zeros(4);

        $expected = Vector::quick([0, 0, 0, 0]);

        $this->assertEquals($expected, $zeros);
    }

    /**
     * @test
     */
    public function ones() : void
    {
        $ones = Vector::ones(4);

        $expected = Vector::quick([1, 1, 1, 1]);

        $this->assertEquals($expected, $ones);
    }

    /**
     * @test
     */
    public function fill() : void
    {
        $vector = Vector::fill(16, 4);

        $expected = Vector::quick([16, 16, 16, 16]);

        $this->assertEquals($expected, $vector);
    }

    /**
     * @test
     */
    public function rand() : void
    {
        $vector = Vector::rand(4);

        $this->assertCount(4, $vector);
    }

    /**
     * @test
     */
    public function gaussian() : void
    {
        $vector = Vector::gaussian(4);

        $this->assertCount(4, $vector);
    }

    /**
     * @test
     */
    public function poisson() : void
    {
        $vector = Vector::poisson(4, 2.0);

        $this->assertCount(4, $vector);
    }

    /**
     * @test
     */
    public function uniform() : void
    {
        $vector = Vector::uniform(4);

        $this->assertCount(4, $vector);
    }

    /**
     * @test
     */
    public function range() : void
    {
        $vector = Vector::range(5.0, 12.0, 2.0);

        $expected = Vector::quick([5.0, 7.0, 9.0, 11.0]);

        $this->assertEquals($expected, $vector);
    }

    /**
     * @test
     */
    public function linspace() : void
    {
        $vector = Vector::linspace(-5.0, 5.0, 10);

        $expected = Vector::quick([
            -5.0, -3.888888888888889, -2.7777777777777777, -1.6666666666666665, -0.5555555555555554,
            0.5555555555555558, 1.666666666666667, 2.777777777777778, 3.8888888888888893, 5.0,
        ]);

        $this->assertEquals($expected, $vector);
    }

    /**
     * @test
     * @dataProvider shapeProvider
     *
     * @param Vector $vector
     * @param array<int> $expected
     */
    public function shape(Vector $vector, array $expected) : void
    {
        $this->assertEquals($expected, $vector->shape());
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function shapeProvider() : Generator
    {
        yield [Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]), [8]];

        yield [Vector::quick([0.25]), [1]];

        yield [Vector::quick([]), [0]];
    }

    /**
     * @test
     */
    public function shapeString() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals('8', $vector->shapeString());
    }

    /**
     * @test
     */
    public function size() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals(8, $vector->size());
    }

    /**
     * @test
     */
    public function m() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals(1, $vector->m());
    }

    /**
     * @test
     */
    public function n() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals(8, $vector->n());
    }

    /**
     * @test
     */
    public function asArray() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $expected = [-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0];

        $this->assertEquals($expected, $vector->asArray());
    }

    /**
     * @test
     */
    public function asRowMatrix() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $matrix = $vector->asRowMatrix();

        $expected = Matrix::quick([
            [-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function asColumnMatrix() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $matrix = $vector->asColumnMatrix();

        $expected = Matrix::quick([[-15.0], [25.0], [35.0], [-36.0], [-72.0], [89.0], [106.0], [45.0]]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function reshape() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $matrix = $vector->reshape(4, 2);

        $expected = Matrix::quick([
            [-15.0, 25.0],
            [35.0, -36.0],
            [-72.0, 89.0],
            [106.0, 45.0],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function transpose() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $vector = $vector->transpose();

        $expected = ColumnVector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals($expected, $vector);
    }

    /**
     * @test
     */
    public function map() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $sign = function ($value) {
            return $value >= 0.0 ? 1 : 0;
        };

        $vector = $vector->map($sign);

        $expected = Vector::quick([0, 1, 1, 0, 0, 1, 1, 1]);

        $this->assertEquals($expected, $vector);
    }

    /**
     * @test
     */
    public function reciprocal() : void
    {
        $vector = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $vector = $vector->reciprocal();

        $expected = Vector::quick([
            -0.06666666666666667, 0.04, 0.02857142857142857, -0.027777777777777776,
            -0.013888888888888888, 0.011235955056179775, 0.009433962264150943, 0.022222222222222223,
        ]);

        $this->assertEqualsWithDelta($expected, $vector, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function dot() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]);

        $c = $a->dot($b);

        $this->assertEqualsWithDelta(331.54999999999995, $c, self::MAX_DELTA);
    }

    public function matmul() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = Matrix::quick([
            [1.1, 0.01, 6.23],
            [5.0, 2.01, -1.0],
            [-5.0, 1.0, 0.03],
            [30.0, 0.02, -0.01],
            [-0.005, 0.05, -0.5],
            [-0.001, -1.0, 2.0],
        ]);

        $c = $a->matmul($b);

        $expected = Matrix::quick([
            [622.3751, 4.634999999999993, 40.807],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function inner() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]);

        $c = $a->inner($b);

        $this->assertEqualsWithDelta(331.54999999999995, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function outer() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]);

        $c = $a->outer($b);

        $expected = Matrix::quick([
            [-3.75, -1.5, -30.0, 7.5, 15.0, 45.0, -49.5, -30.],
            [6.25, 2.5, 50.0, -12.5, -25.0, -75.0, 82.5, 50.],
            [8.75, 3.5, 70.0, -17.5, -35.0, -105.0, 115.5, 70.],
            [-9.0, -3.6, -72.0, 18.0, 36.0, 108.0, -118.8, -72.],
            [-18.0, -7.2, -144.0, 36.0, 72.0, 216.0, -237.6, -144.],
            [22.25, 8.9, 178.0, -44.5, -89.0, -267.0, 293.7, 178.],
            [26.5, 10.600000000000001, 212.0, -53.0, -106.0, -318.0, 349.79999999999995, 212.],
            [11.25, 4.5, 90.0, -22.5, -45.0, -135.0, 148.5, 90.],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function convolve() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $c = $a->convolve($b, 1);

        $expected = Vector::quick([
            -60.0, 2.5, 259.0, -144.0, 40.5, 370.1, 462.20000000000005,
            10.000000000000114, 1764.3000000000002, 1625.1, 2234.7, 1378.4, 535.5,
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     * @dataProvider multiplyProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function multiply(Vector $a, $b, $expected) : void
    {
        $c = $a->multiply($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function multiplyProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [6.23, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 0.02, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, -0.001],
            ]),
            Matrix::quick([
                [24.92, -6.5, 0.087, -0.2, -1.3, 23.8],
                [0.04, 13.064999999999998, 2.9, 0.4, 0.13, -11.9],
                [4.4, 32.5, -14.5, 600.0, -0.013000000000000001, -0.0119],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([-3.75, 2.5, 70.0, 18.0, 72.0, -267.0, 349.79999999999995, 90.0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            2.0,
            Vector::quick([-30.0, 50.0, 70.0, -72.0, -144.0, 178.0, 212.0, 90.0]),
        ];
    }

    /**
     * @test
     * @dataProvider divideProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function divide(Vector $a, $b, $expected) : void
    {
        $c = $a->divide($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function divideProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [6.23, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 0.02, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, -0.001],
            ]),
            Matrix::quick([
                [0.6420545746388443, -6.5, 96.66666666666667, -2000.0, -5.2, 5.95],
                [400.0, 3.2338308457711444, 2.9, 1000.0, 52.0, -11.9],
                [3.6363636363636362, 1.3, -0.58, 0.6666666666666666, -520.0, -11900.],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([-60.0, 250.0, 17.5, 72.0, 72.0, -29.666666666666668, 32.121212121212125, 22.5]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            2.0,
            Vector::quick([-7.5, 12.5, 17.5, -18.0, -36.0, 44.5, 53, 22.5]),
        ];
    }

    /**
     * @test
     * @dataProvider addProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function add(Vector $a, $b, $expected) : void
    {
        $c = $a->add($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function addProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [6.23, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 0.02, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, -0.001],
            ]),
            Matrix::quick([
                [10.23, 5.5, 2.9299999999999997, 19.99, 2.1, 13.9],
                [4.01, 8.51, 3.9, 20.02, 2.65, 10.9],
                [5.1, 11.5, -2.1, 50.0, 2.595, 11.899000000000001],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([-14.75, 25.1, 37.0, -36.5, -73.0, 86.0, 109.3, 47.0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            10.0,
            Vector::quick([-5.0, 35.0, 45.0, -26.0, -62.0, 99.0, 116.0, 55.0]),
        ];
    }

    /**
     * @test
     * @dataProvider subtractProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function subtract(Vector $a, $b, $expected) : void
    {
        $c = $a->subtract($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function subtractProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [6.23, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 0.02, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, -0.001],
            ]),
            Matrix::quick([
                [-2.2300000000000004, 7.5, 2.87, 20.01, 3.1, 9.9],
                [3.99, 4.49, 1.9, 19.98, 2.5500000000000003, 12.9],
                [2.9, 1.5, 7.9, -10.0, 2.605, 11.901],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([-15.25, 24.9, 33.0, -35.5, -71.0, 92.0, 102.7, 43.0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            10.0,
            Vector::quick([-25.0, 15.0, 25.0, -46.0, -82.0, 79.0, 96.0, 35.0]),
        ];
    }

    /**
     * @test
     * @dataProvider powProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function power(Vector $a, $b, $expected) : void
    {
        $c = $a->pow($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function powProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [6.23, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 0.02, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, -0.001],
            ]),
            Matrix::quick([
                [5634.219287100394, 0.15384615384615385, 1.0324569211337775, 0.9704869503929601, 0.6201736729460423, 141.61],
                [1.013959479790029, 43.048284263459465, 2.9, 1.0617459178549786, 1.0489352187366092, 0.08403361344537814],
                [4.59479341998814, 11602.90625, 0.004875397277841432, 1.073741824E+39, 0.9952338371484033, 0.9975265256911376],
            ]),
        ];

        yield [
            Vector::quick([3.0, 6.0, 9.0]),
            Vector::quick([3.0, 2.0, 1.0]),
            Vector::quick([27.0, 36.0, 9.0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            4.0,
            Vector::quick([
                50625, 390625, 1500625, 1679616, 26873856, 62742241, 126247696, 4100625
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider equalProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function equal(Vector $a, $b, $expected) : void
    {
        $c = $a->equal($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function equalProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [4.0, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 20.0, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, 11.9],
            ]),
            Matrix::quick([
                [1, 0, 0, 0, 0, 0],
                [0, 0, 0, 1, 0, 0],
                [0, 0, 0, 0, 0, 1],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -36.0, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([0, 0, 0, 1, 0, 0, 0, 0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            25.0,
            Vector::quick([0, 1, 0, 0, 0, 0, 0, 0]),
        ];
    }

    /**
     * @test
     * @dataProvider notEqualProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function notEqual(Vector $a, $b, $expected) : void
    {
        $c = $a->notEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function notEqualProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [4.0, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 20.0, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, 11.9],
            ]),
            Matrix::quick([
                [0, 1, 1, 1, 1, 1],
                [1, 1, 1, 0, 1, 1],
                [1, 1, 1, 1, 1, 0],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -36.0, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([1, 1, 1, 0, 1, 1, 1, 1]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            25.0,
            Vector::quick([1, 0, 1, 1, 1, 1, 1, 1]),
        ];
    }

    /**
     * @test
     * @dataProvider greaterProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function greater(Vector $a, $b, $expected) : void
    {
        $c = $a->greater($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function greaterProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [4.0, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 20.0, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, 11.9],
            ]),
            Matrix::quick([
                [0, 1, 1, 1, 1, 1],
                [1, 1, 1, 0, 1, 1],
                [1, 1, 1, 0, 1, 0],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -36.0, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([0, 1, 1, 0, 0, 1, 1, 1]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            1.0,
            Vector::quick([0, 1, 1, 0, 0, 1, 1, 1]),
        ];
    }

    /**
     * @test
     * @dataProvider greaterEqualProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function greaterEqual(Vector $a, $b, $expected) : void
    {
        $c = $a->greaterEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function greaterEqualProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [4.0, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 20.0, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, 11.9],
            ]),
            Matrix::quick([
                [1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 1, 1, 0, 1, 1],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -36.0, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([0, 1, 1, 1, 0, 1, 1, 1]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            25.0,
            Vector::quick([0, 1, 1, 0, 0, 1, 1, 1]),
        ];
    }

    /**
     * @test
     * @dataProvider lessProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function less(Vector $a, $b, $expected) : void
    {
        $c = $a->less($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function lessProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [4.0, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 20.0, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, 11.9],
            ]),
            Matrix::quick([
                [0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0],
                [0, 0, 0, 1, 0, 0],
            ]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -36.0, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([1, 0, 0, 0, 1, 0, 0, 0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            25.0,
            Vector::quick([1, 0, 0, 1, 1, 0, 0, 0]),
        ];
    }

    /**
     * @test
     * @dataProvider lessEqualProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function lessEqual(Vector $a, $b, $expected) : void
    {
        $c = $a->lessEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function lessEqualProvider() : Generator
    {
        yield [
            Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]),
            Matrix::quick([
                [4.0, -1.0, 0.03, -0.01, -0.5, 2.0],
                [0.01, 2.01, 1.0, 20.0, 0.05, -1.0],
                [1.1, 5.0, -5.0, 30, -0.005, 11.9],
            ]),
            Matrix::quick([
                [1, 0, 0, 0, 0, 0],
                [0, 0, 0, 1, 0, 0],
                [0, 0, 0, 1, 0, 1],
            ]),

        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0.25, 0.1, 2.0, -36.0, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([1, 0, 0, 1, 1, 0, 0, 0]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            25.0,
            Vector::quick([1, 1, 0, 1, 1, 0, 0, 0]),
        ];
    }

    /**
     * @test
     * @dataProvider modProvider
     *
     * @param Vector $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function mod(Vector $a, $b, $expected) : void
    {
        $c = $a->mod($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function modProvider() : Generator
    {
        yield [
            Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]),
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            Vector::quick([0, 0, 2, 0, -1, -3, 3, 2]),
        ];

        yield [
            Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]),
            4,
            Vector::quick([-3, 1, 3, 0, 0, 1, 2, 1]),
        ];
    }

    /**
     * @test
     */
    public function abs() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->abs();

        $expected = Vector::quick([15, 25, 35, 36, 72, 89, 106, 45]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function square() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->square();

        $expected = Vector::quick([225, 625, 1225, 1296, 5184, 7921, 11236, 2025]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function pow() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->pow(3);

        $expected = Vector::quick([-3375, 15625, 42875, -46656, -373248, 704969, 1191016, 91125]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function sqrt() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->sqrt();

        $expected = Vector::quick([
            2.0, 2.5495097567963922, 1.70293863659264, 4.47213595499958,
            1.61245154965971, 3.449637662132068,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function exp() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->exp();

        $expected = Vector::quick([
            54.598150033144236, 665.1416330443618, 18.17414536944306,
            485165195.4097903, 13.463738035001692, 147266.6252405527,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function log() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->log();

        $expected = Vector::quick([
            1.3862943611198906, 1.8718021769015913, 1.0647107369924282,
            2.995732273553991, 0.9555114450274363, 2.4765384001174837,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function sin() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->sin();

        $expected = Vector::quick([
            -0.7568024953079282, 0.21511998808781552, 0.23924932921398243,
            0.9129452507276277, 0.5155013718214642, -0.6181371122370333,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function asin() : void
    {
        $a = Vector::quick([0.1, 0.3, -0.5]);

        $b = $a->asin();

        $expected = Vector::quick([
            0.1001674211615598, 0.3046926540153975, -0.5235987755982989,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function cos() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->cos();

        $expected = Vector::quick([
            -0.6536436208636119, 0.9765876257280235, -0.9709581651495905,
            0.40808206181339196, -0.8568887533689473, 0.7860702961410393,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function acos() : void
    {
        $a = Vector::quick([0.1, 0.3, -0.5]);

        $b = $a->acos();

        $expected = Vector::quick([
            1.4706289056333368, 1.2661036727794992, 2.0943951023931957,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function tan() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->tan();

        $expected = Vector::quick([
            1.1578212823495777, 0.22027720034589682, -0.24640539397196634,
            2.237160944224742, -0.6015966130897586, -0.7863636563696398,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function atan() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->atan();

        $expected = Vector::quick([
            1.3258176636680326, 1.4181469983996315, 1.2387368592520112,
            1.5208379310729538, 1.2036224929766774, 1.486959684726482,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function rad2deg() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->rad2deg();

        $expected = Vector::quick([
            229.1831180523293, 372.42256683503507, 166.15776058793872,
            1145.9155902616465, 148.96902673401405, 681.8197762056797,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function deg2rad() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->deg2rad();

        $expected = Vector::quick([
            0.06981317007977318, 0.11344640137963141, 0.05061454830783556,
            0.3490658503988659, 0.04537856055185257, 0.2076941809873252,
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function sum() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(177.0, $a->sum(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function product() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(-14442510600000.0, $a->product(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function min() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals(-72, $a->min());
    }

    /**
     * @test
     */
    public function max() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals(106, $a->max());
    }

    /**
     * @test
     */
    public function mean() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(22.125, $a->mean(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function median() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEquals(30.0, $a->median());
    }

    /**
     * @test
     */
    public function quantile() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(30.0, $a->quantile(0.5), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function variance() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(3227.609375, $a->variance(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function round() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->round(2);

        $expected = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function floor() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->floor();

        $expected = Vector::quick([4.0, 6.0, 2.0, 20.0, 2.0, 11.0]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function ceil() : void
    {
        $a = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $b = $a->ceil();

        $expected = Vector::quick([4.0, 7.0, 3.0, 20.0, 3.0, 12.0]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function l1Norm() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(423.0, $a->l1Norm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function l2Norm() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(172.4441938715247, $a->l2Norm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function pNorm() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(135.15554088861361, $a->pNorm(3.0), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function maxNorm() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->assertEqualsWithDelta(106.0, $a->maxNorm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function clip() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->clip(0.0, 100);

        $expected = Vector::quick([0.0, 25, 35, 0.0, 0.0, 89, 100.0, 45]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function clipLower() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->clipLower(60.0);

        $expected = Vector::quick([60.0, 60.0, 60.0, 60.0, 60.0, 89, 106.0, 60.0]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function clipUpper() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->clipUpper(50.0);

        $expected = Vector::quick([-15.0, 25, 35, -36.0, -72.0, 50.0, 50.0, 45]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function sign() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->sign();

        $expected = Vector::quick([-1, 1, 1, -1, -1, 1, 1, 1]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function negate() : void
    {
        $a = Vector::quick([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $b = $a->negate();

        $expected = Vector::quick([15, -25, -35, 36, 72, -89, -106, -45]);

        $this->assertEquals($expected, $b);
    }
}
