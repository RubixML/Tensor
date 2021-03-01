<?php

namespace Tensor\Tests;

use Tensor\Tensor;
use Tensor\Vector;
use Tensor\Matrix;
use Tensor\ArrayLike;
use Tensor\Arithmetic;
use Tensor\Comparable;
use Tensor\Functional;
use Tensor\Statistical;
use Tensor\ColumnVector;
use Tensor\Trigonometric;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Vector
 */
class VectorTest extends TestCase
{
    /**
     * @var \Tensor\Vector
     */
    protected $a;

    /**
     * @var \Tensor\Vector
     */
    protected $b;

    /**
     * @var \Tensor\Vector
     */
    protected $c;

    /**
     * @var \Tensor\Matrix
     */
    protected $d;

    /**
     * @before
     */
    public function setUp() : void
    {
        $this->a = Vector::build([-15.0, 25.0, 35.0, -36.0, -72.0, 89.0, 106.0, 45.0]);

        $this->b = Vector::quick([0.25, 0.1, 2.0, -0.5, -1.0, -3.0, 3.3, 2.0]);

        $this->c = Vector::quick([4.0, 6.5, 2.9, 20.0, 2.6, 11.9]);

        $this->d = Matrix::quick([
            [6.23, -1.0, 0.03, -0.01, -0.5, 2.0],
            [0.01, 2.01, 1.0, 0.02, 0.05, -1.0],
            [1.1, 5.0, -5.0, 30, -0.005, -0.001],
        ]);
    }

    /**
     * @test
     */
    public function build() : void
    {
        $this->assertInstanceOf(Vector::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Arithmetic::class, $this->a);
        $this->assertInstanceOf(Comparable::class, $this->a);
        $this->assertInstanceOf(Functional::class, $this->a);
        $this->assertInstanceOf(Trigonometric::class, $this->a);
        $this->assertInstanceOf(Statistical::class, $this->a);
        $this->assertInstanceOf(ArrayLike::class, $this->a);
    }

    /**
     * @test
     */
    public function zeros() : void
    {
        $z = Vector::zeros(4);

        $expected = [0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function ones() : void
    {
        $z = Vector::ones(4);

        $expected = [1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function fill() : void
    {
        $z = Vector::fill(16, 4);

        $expected = [16, 16, 16, 16];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function rand() : void
    {
        $z = Vector::rand(4);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(4, $z);
    }

    /**
     * @test
     */
    public function gaussian() : void
    {
        $z = Vector::gaussian(4);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(4, $z);
    }

    /**
     * @test
     */
    public function poisson() : void
    {
        $z = Vector::poisson(10, 2.);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(10, $z);
    }

    /**
     * @test
     */
    public function uniform() : void
    {
        $z = Vector::uniform(5);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(5, $z);
    }

    /**
     * @test
     */
    public function range() : void
    {
        $z = Vector::range(5.0, 12.0, 2.0);

        $expected = [5.0, 7.0, 9.0, 11.0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function linspace() : void
    {
        $z = Vector::linspace(-5, 5, 10);

        $expected = [
            -5.0, -3.888888888888889, -2.7777777777777777, -1.6666666666666665, -0.5555555555555554,
            0.5555555555555558, 1.666666666666667, 2.777777777777778, 3.8888888888888893, 5.0,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(10, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function maximum() : void
    {
        $z = Vector::maximum($this->a, $this->b);

        $expected = [0.25, 25, 35, -0.5, -1.0, 89, 106, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function minimum() : void
    {
        $z = Vector::minimum($this->a, $this->b);

        $expected = [-15, 0.1, 2.0, -36, -72, -3.0, 3.3, 2.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function shape() : void
    {
        $this->assertEquals([8], $this->a->shape());
        $this->assertEquals([8], $this->b->shape());
        $this->assertEquals([6], $this->c->shape());
    }

    /**
     * @test
     */
    public function shapeString() : void
    {
        $this->assertEquals('8', $this->a->shapeString());
        $this->assertEquals('8', $this->b->shapeString());
        $this->assertEquals('6', $this->c->shapeString());
    }

    /**
     * @test
     */
    public function size() : void
    {
        $this->assertEquals(8, $this->a->size());
        $this->assertEquals(8, $this->b->size());
        $this->assertEquals(6, $this->c->size());
    }

    /**
     * @test
     */
    public function m() : void
    {
        $this->assertEquals(1, $this->a->m());
        $this->assertEquals(1, $this->b->m());
        $this->assertEquals(1, $this->c->m());
    }

    /**
     * @test
     */
    public function n() : void
    {
        $this->assertEquals(8, $this->a->n());
        $this->assertEquals(8, $this->b->n());
        $this->assertEquals(6, $this->c->n());
    }

    /**
     * @test
     */
    public function asArray() : void
    {
        $z = $this->a->asArray();

        $expected = [-15, 25, 35, -36, -72, 89, 106, 45];

        $this->assertEquals($expected, $z);
    }

    /**
     * @test
     */
    public function asRowMatrix() : void
    {
        $z = $this->a->asRowMatrix();

        $expected = [[-15, 25, 35, -36, -72, 89, 106, 45]];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function asColumnMatrix() : void
    {
        $z = $this->a->asColumnMatrix();

        $expected = [[-15], [25], [35], [-36], [-72], [89], [106], [45]];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function reshape() : void
    {
        $z = $this->a->reshape(4, 2);

        $expected = [
            [-15, 25],
            [35, -36],
            [-72, 89],
            [106, 45],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals([4, 2], $z->shape());
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function transpose() : void
    {
        $z = $this->a->transpose();

        $outcome = [-15, 25, 35, -36, -72, 89, 106, 45];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($outcome, $z->asArray());
    }

    /**
     * @test
     */
    public function map() : void
    {
        $z = $this->a->map(function ($value) {
            return $value > 0. ? 1 : 0;
        });

        $expected = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function reduce() : void
    {
        $scalar = $this->a->reduce(function ($value, $carry) {
            return $carry + ($value / 2.);
        });

        $this->assertEquals(110.3671875, $scalar);
    }

    /**
     * @test
     */
    public function reciprocal() : void
    {
        $z = $this->a->reciprocal();

        $expected = [
            -0.06666666666666667, 0.04, 0.02857142857142857, -0.027777777777777776,
            -0.013888888888888888, 0.011235955056179775, 0.009433962264150943, 0.022222222222222223,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function argmin() : void
    {
        $this->assertEquals(4, $this->a->argmin());
        $this->assertEquals(5, $this->b->argmin());
        $this->assertEquals(4, $this->c->argmin());
    }

    /**
     * @test
     */
    public function argmax() : void
    {
        $this->assertEquals(6, $this->a->argmax());
        $this->assertEquals(6, $this->b->argmax());
        $this->assertEquals(3, $this->c->argmax());
    }

    /**
     * @test
     */
    public function dot() : void
    {
        $this->assertEquals(331.54999999999995, $this->a->dot($this->b));
    }

    /**
     * @test
     */
    public function matmul() : void
    {
        $expected = [
            [40.807, 4.634999999999993, 622.3751],
        ];

        $this->assertEquals($expected, $this->c->matmul($this->d->transpose())->asArray());
    }

    /**
     * @test
     */
    public function inner() : void
    {
        $this->assertEquals(331.54999999999995, $this->a->inner($this->b));
    }

    /**
     * @test
     */
    public function outer() : void
    {
        $z = $this->a->outer($this->b);

        $expected = [
            [-3.75, -1.5, -30.0, 7.5, 15.0, 45.0, -49.5, -30.],
            [6.25, 2.5, 50.0, -12.5, -25.0, -75.0, 82.5, 50.],
            [8.75, 3.5, 70.0, -17.5, -35.0, -105.0, 115.5, 70.],
            [-9.0, -3.6, -72.0, 18.0, 36.0, 108.0, -118.8, -72.],
            [-18.0, -7.2, -144.0, 36.0, 72.0, 216.0, -237.6, -144.],
            [22.25, 8.9, 178.0, -44.5, -89.0, -267.0, 293.7, 178.],
            [26.5, 10.600000000000001, 212.0, -53.0, -106.0, -318.0, 349.79999999999995, 212.],
            [11.25, 4.5, 90.0, -22.5, -45.0, -135.0, 148.5, 90.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function cross() : void
    {
        $a = new Vector([1.0, -0.5, 6.]);

        $b = new Vector([2.0, 0.0, 3.]);

        $z = $a->cross($b);

        $expected = [-1.5, 9.0, 1.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function convolve() : void
    {
        $z = $this->a->convolve($this->c, 1);

        $expected = [
            -60, 2.5, 259, -144, 40.5, 370.1, 462.20000000000005,
            10, 1764.3000000000002, 1625.1, 2234.7000000000003, 1378.4, 535.5,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function project() : void
    {
        $z = $this->a->project($this->b);

        $expected = [
            2.8373983739837394, 1.1349593495934958, 22.699186991869915, -5.674796747967479,
            -11.349593495934958, -34.048780487804876, 37.45365853658536, 22.699186991869915,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyMatrix() : void
    {
        $z = $this->c->multiply($this->d);

        $expected = [
            [24.92, -6.5, 0.087, -0.2, -1.3, 23.8],
            [0.04, 13.064999999999998, 2.9, 0.4, 0.13, -11.9],
            [4.4, 32.5, -14.5, 600.0, -0.013000000000000001, -0.0119],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideMatrix() : void
    {
        $z = $this->c->divide($this->d);

        $expected = [
            [0.6420545746388443, -6.5, 96.66666666666667, -2000.0, -5.2, 5.95],
            [400.0, 3.2338308457711444, 2.9, 1000.0, 52.0, -11.9],
            [3.6363636363636362, 1.3, -0.58, 0.6666666666666666, -520.0, -11900.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addMatrix() : void
    {
        $z = $this->c->add($this->d);

        $expected = [
            [10.23, 5.5, 2.9299999999999997, 19.99, 2.1, 13.9],
            [4.01, 8.51, 3.9, 20.02, 2.65, 10.9],
            [5.1, 11.5, -2.1, 50.0, 2.595, 11.899000000000001],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractMatrix() : void
    {
        $z = $this->c->subtract($this->d);

        $expected = [
            [-2.2300000000000004, 7.5, 2.87, 20.01, 3.1, 9.9],
            [3.99, 4.49, 1.9, 19.98, 2.5500000000000003, 12.9],
            [2.9, 1.5, 7.9, -10.0, 2.605, 11.901],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function powMatrix() : void
    {
        $z = $this->c->pow($this->d);

        $expected = [
            [5634.219287100394, 0.15384615384615385, 1.0324569211337775, 0.9704869503929601, 0.6201736729460423, 141.61],
            [1.013959479790029, 43.048284263459465, 2.9, 1.0617459178549786, 1.0489352187366092, 0.08403361344537814],
            [4.59479341998814, 11602.90625, 0.004875397277841432, 1.073741824E+39, 0.9952338371484033, 0.9975265256911376],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalMatrix() : void
    {
        $z = $this->c->equal($this->d);

        $expected = [
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualMatrix() : void
    {
        $z = $this->c->notEqual($this->d);

        $expected = [
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterMatrix() : void
    {
        $z = $this->c->greater($this->d);

        $expected = [
            [0, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualMatrix() : void
    {
        $z = $this->c->greaterEqual($this->d);

        $expected = [
            [0, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessMatrix() : void
    {
        $z = $this->c->less($this->d);

        $expected = [
            [1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualMatrix() : void
    {
        $z = $this->c->lessEqual($this->d);

        $expected = [
            [1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyVector() : void
    {
        $z = $this->a->multiply($this->b);

        $expected = [-3.75, 2.5, 70.0, 18.0, 72.0, -267.0, 349.79999999999995, 90.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideVector() : void
    {
        $z = $this->a->divide($this->b);

        $expected = [-60.0, 250.0, 17.5, 72.0, 72.0, -29.666666666666668, 32.121212121212125, 22.5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addVector() : void
    {
        $z = $this->a->add($this->b);

        $expected = [-14.75, 25.1, 37.0, -36.5, -73.0, 86.0, 109.3, 47.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractVector() : void
    {
        $z = $this->a->subtract($this->b);

        $expected = [-15.25, 24.9, 33.0, -35.5, -71.0, 92.0, 102.7, 43.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function powVector() : void
    {
        $z = $this->b->pow($this->a);

        $expected = [
            1073741824.0, 1.0000000000000014E-25, 34359738368.0, 68719476736.0,
            1.0, -2.909321189362571E+42, 9.172286825801562E+54, 35184372088832.0,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function modVector() : void
    {
        $z = $this->b->mod($this->a);

        $expected = [0, 0, 2, 0, -1, -3, 3, 2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalVector() : void
    {
        $z = $this->b->equal($this->a);

        $expected = [0, 0, 0, 0, 0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualVector() : void
    {
        $z = $this->b->notEqual($this->a);

        $expected = [1, 1, 1, 1, 1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterVector() : void
    {
        $z = $this->b->greater($this->a);

        $expected = [1, 0, 0, 1, 1, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualVector() : void
    {
        $z = $this->b->greaterEqual($this->a);

        $expected = [1, 0, 0, 1, 1, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessVector() : void
    {
        $z = $this->b->less($this->a);

        $expected = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualVector() : void
    {
        $z = $this->b->lessEqual($this->a);

        $expected = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyScalar() : void
    {
        $z = $this->a->multiply(2);

        $expected = [-30, 50, 70, -72, -144, 178, 212, 90];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideScalar() : void
    {
        $z = $this->a->divide(2);

        $expected = [-7.5, 12.5, 17.5, -18, -36, 44.5, 53, 22.5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addScalar() : void
    {
        $z = $this->a->add(10);

        $expected = [-5, 35, 45, -26, -62, 99, 116, 55];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractScalar() : void
    {
        $z = $this->a->subtract(10);

        $expected = [-25, 15, 25, -46, -82, 79, 96, 35];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function powScalar() : void
    {
        $z = $this->a->pow(4);

        $expected = [
            50625, 390625, 1500625, 1679616, 26873856, 62742241, 126247696, 4100625
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function modScalar() : void
    {
        $z = $this->a->mod(4);

        $expected = [-3, 1, 3, 0, 0, 1, 2, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalScalar() : void
    {
        $z = $this->a->equal(25);

        $expected = [0, 1, 0, 0, 0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualScalar() : void
    {
        $z = $this->a->notEqual(25);

        $expected = [1, 0, 1, 1, 1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterScalar() : void
    {
        $z = $this->b->greater(1);

        $expected = [0, 0, 1, 0, 0, 0, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualScalar() : void
    {
        $z = $this->b->greaterEqual(1);

        $expected = [0, 0, 1, 0, 0, 0, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessScalar() : void
    {
        $z = $this->b->less(1);

        $expected = [1, 1, 0, 1, 1, 1, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualScalar() : void
    {
        $z = $this->b->lessEqual(1);

        $expected = [1, 1, 0, 1, 1, 1, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function abs() : void
    {
        $z = $this->a->abs();

        $expected = [15, 25, 35, 36, 72, 89, 106, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function square() : void
    {
        $z = $this->a->square();

        $expected = [225, 625, 1225, 1296, 5184, 7921, 11236, 2025];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function pow() : void
    {
        $z = $this->a->pow(3);

        $expected = [-3375, 15625, 42875, -46656, -373248, 704969, 1191016, 91125];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sqrt() : void
    {
        $z = $this->c->sqrt();

        $expected = [
            2.0, 2.5495097567963922, 1.70293863659264, 4.47213595499958,
            1.61245154965971, 3.449637662132068,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function exp() : void
    {
        $z = $this->a->exp();

        $expected = [
            3.059023205018258E-7, 72004899337.38588, 1586013452313430.8,
            2.3195228302435696E-16, 5.380186160021138E-32, 4.4896128191743455E+38,
            1.0844638552900231E+46, 3.4934271057485095E+19,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function log() : void
    {
        $z = $this->c->log();

        $expected = [
            1.3862943611198906, 1.8718021769015913, 1.0647107369924282,
            2.995732273553991, 0.9555114450274363, 2.4765384001174837,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sin() : void
    {
        $z = $this->c->sin();

        $expected = [
            -0.7568024953079282, 0.21511998808781552, 0.23924932921398243,
            0.9129452507276277, 0.5155013718214642, -0.6181371122370333,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function asin() : void
    {
        $z = Vector::quick([0.1, 0.3, -0.5])->asin();

        $expected = [
            0.1001674211615598, 0.3046926540153975, -0.5235987755982989,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function cos() : void
    {
        $z = $this->c->cos();

        $expected = [
            -0.6536436208636119, 0.9765876257280235, -0.9709581651495905,
            0.40808206181339196, -0.8568887533689473, 0.7860702961410393,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function acos() : void
    {
        $z = Vector::quick([0.1, 0.3, -0.5])->acos();

        $expected = [
            1.4706289056333368, 1.2661036727794992, 2.0943951023931957,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function tan() : void
    {
        $z = $this->c->tan();

        $expected = [
            1.1578212823495777, 0.22027720034589682, -0.24640539397196634,
            2.237160944224742, -0.6015966130897586, -0.7863636563696398,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function atan() : void
    {
        $z = $this->c->atan();

        $expected = [
            1.3258176636680326, 1.4181469983996315, 1.2387368592520112,
            1.5208379310729538, 1.2036224929766774, 1.486959684726482,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function rad2deg() : void
    {
        $z = $this->c->rad2deg();

        $expected = [
            229.1831180523293, 372.42256683503507, 166.15776058793872,
            1145.9155902616465, 148.96902673401405, 681.8197762056797,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function deg2rad() : void
    {
        $z = $this->c->deg2rad();

        $expected = [
            0.06981317007977318, 0.11344640137963141, 0.05061454830783556,
            0.3490658503988659, 0.04537856055185257, 0.2076941809873252,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sum() : void
    {
        $this->assertEquals(177.0, $this->a->sum());
        $this->assertEquals(3.15, $this->b->sum());
        $this->assertEquals(47.9, $this->c->sum());
    }

    /**
     * @test
     */
    public function product() : void
    {
        $this->assertEquals(-14442510600000.0, $this->a->product());
        $this->assertEquals(-0.49500000000000005, $this->b->product());
        $this->assertEquals(46657.52, $this->c->product());
    }

    /**
     * @test
     */
    public function min() : void
    {
        $this->assertEquals(-72, $this->a->min());
        $this->assertEquals(-3, $this->b->min());
        $this->assertEquals(2.6, $this->c->min());
    }

    /**
     * @test
     */
    public function max() : void
    {
        $this->assertEquals(106, $this->a->max());
        $this->assertEquals(3.3, $this->b->max());
        $this->assertEquals(20.0, $this->c->max());
    }

    /**
     * @test
     */
    public function mean() : void
    {
        $this->assertEquals(22.125, $this->a->mean());
        $this->assertEquals(0.39375, $this->b->mean());
        $this->assertEquals(7.983333333333333, $this->c->mean());
    }

    /**
     * @test
     */
    public function median() : void
    {
        $this->assertEquals(30.0, $this->a->median());
        $this->assertEquals(0.175, $this->b->median());
        $this->assertEquals(5.25, $this->c->median());
    }

    /**
     * @test
     */
    public function quantile() : void
    {
        $this->assertEquals(30.0, $this->a->quantile(0.5));
        $this->assertEquals(-0.625, $this->b->quantile(0.25));
        $this->assertEquals(10.55, $this->c->quantile(0.75));
    }

    /**
     * @test
     */
    public function variance() : void
    {
        $this->assertEquals(3227.609375, $this->a->variance());
        $this->assertEquals(3.4965234374999996, $this->b->variance());
        $this->assertEquals(38.77138888888888, $this->c->variance());
    }

    /**
     * @test
     */
    public function round() : void
    {
        $z = $this->c->round(2);

        $expected = [4.0, 6.5, 2.9, 20.0, 2.6, 11.9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function floor() : void
    {
        $z = $this->c->floor();

        $expected = [4.0, 6.0, 2.0, 20.0, 2.0, 11.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function ceil() : void
    {
        $z = $this->c->ceil();

        $expected = [4.0, 7.0, 3.0, 20.0, 3.0, 12.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function l1Norm() : void
    {
        $this->assertEquals(423.0, $this->a->l1Norm());
        $this->assertEquals(12.149999999999999, $this->b->l1Norm());
        $this->assertEquals(47.9, $this->c->l1Norm());
    }

    /**
     * @test
     */
    public function l2Norm() : void
    {
        $this->assertEquals(172.4441938715247, $this->a->l2Norm());
        $this->assertEquals(5.404858925078433, $this->b->l2Norm());
        $this->assertEquals(24.799798386277256, $this->c->l2Norm());
    }

    /**
     * @test
     */
    public function pNorm() : void
    {
        $this->assertEquals(135.15554088861361, $this->a->pNorm(3.));
        $this->assertEquals(3.7063242195906976, $this->b->pNorm(5.));
        $this->assertEquals(20.01112107057168, $this->c->pNorm(10.));
    }

    /**
     * @test
     */
    public function maxNorm() : void
    {
        $this->assertEquals(106.0, $this->a->maxNorm());
        $this->assertEquals(3.3, $this->b->maxNorm());
        $this->assertEquals(20.0, $this->c->maxNorm());
    }

    /**
     * @test
     */
    public function clip() : void
    {
        $z = $this->a->clip(0.0, 100);

        $expected = [0.0, 25, 35, 0.0, 0.0, 89, 100.0, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function clipLower() : void
    {
        $z = $this->a->clipLower(60.);

        $expected = [60.0, 60.0, 60.0, 60.0, 60.0, 89, 106.0, 60.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function clipUpper() : void
    {
        $z = $this->a->clipUpper(50.);

        $expected = [-15.0, 25, 35, -36.0, -72.0, 50.0, 50.0, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sign() : void
    {
        $z = $this->a->sign();

        $expected = [-1, 1, 1, -1, -1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function negate() : void
    {
        $z = $this->a->negate();

        $expected = [15, -25, -35, 36, 72, -89, -106, -45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function testToString() : void
    {
        $outcome = '[ -15 25 35 -36 -72 89 106 45 ]' . PHP_EOL;

        $this->assertEquals($outcome, (string) $this->a);
    }
}
