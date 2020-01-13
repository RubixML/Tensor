<?php

namespace Tensor\Tests;

use Tensor\Tensor;
use Tensor\Vector;
use Tensor\Matrix;
use Tensor\ArrayLike;
use Tensor\Arithmetic;
use Tensor\Comparable;
use Tensor\Statistical;
use Tensor\ColumnVector;
use Tensor\Trigonometric;
use PHPUnit\Framework\TestCase;

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

    public function setUp() : void
    {
        $this->a = Vector::build([-15, 25, 35, -36, -72, 89, 106, 45]);

        $this->b = Vector::quick([0.25, 0.1, 2., -0.5, -1., -3.0, 3.3, 2.0]);

        $this->c = Vector::quick([4., 6.5, 2.9, 20., 2.6, 11.9]);

        $this->d = Matrix::quick([
            [6.23, -1., 0.03, -0.01, -0.5, 2.],
            [0.01, 2.01, 1.0, 0.02, 0.05, -1.],
            [1.1, 5., -5., 30, -0.005, -0.001],
        ]);
    }

    public function testBuildVector() : void
    {
        $this->assertInstanceOf(Vector::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Arithmetic::class, $this->a);
        $this->assertInstanceOf(Comparable::class, $this->a);
        $this->assertInstanceOf(Trigonometric::class, $this->a);
        $this->assertInstanceOf(Statistical::class, $this->a);
        $this->assertInstanceOf(ArrayLike::class, $this->a);
    }

    public function testBuildZeros() : void
    {
        $z = Vector::zeros(4);

        $expected = [0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testBuildOnes() : void
    {
        $z = Vector::ones(4);

        $expected = [1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }
    
    public function testBuildFill() : void
    {
        $z = Vector::fill(16, 4);

        $expected = [16, 16, 16, 16];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testBuildRand() : void
    {
        $z = Vector::rand(4);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(4, $z);
    }

    public function testBuildGaussian() : void
    {
        $z = Vector::gaussian(4);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(4, $z);
    }

    public function testBuildPoisson() : void
    {
        $z = Vector::poisson(10, 2.);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(10, $z);
    }

    public function testBuildUniform() : void
    {
        $z = Vector::uniform(5);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(5, $z);
    }

    public function testBuildRange() : void
    {
        $z = Vector::range(5., 12., 2.);

        $expected = [5., 7., 9., 11.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testBuildLinspace() : void
    {
        $z = Vector::linspace(-5, 5, 9);

        $expected = [
            -5., -3.7500001000000003, -2.5000002, -1.2500003, -4.0000000023354687E-7,
            1.2499994999999995, 2.4999994, 3.749999299999999, 4.9999991999999995,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(9, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testMaximum() : void
    {
        $z = Vector::maximum($this->a, $this->b);

        $expected = [0.25, 25, 35, -0.5, -1.0, 89, 106, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testMinimum() : void
    {
        $z = Vector::minimum($this->a, $this->b);

        $expected = [-15, 0.1, 2.0, -36, -72, -3., 3.3, 2.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testShape() : void
    {
        $this->assertEquals([8], $this->a->shape());
        $this->assertEquals([8], $this->b->shape());
        $this->assertEquals([6], $this->c->shape());
    }

    public function testShapeString() : void
    {
        $this->assertEquals('8', $this->a->shapeString());
        $this->assertEquals('8', $this->b->shapeString());
        $this->assertEquals('6', $this->c->shapeString());
    }

    public function testSize() : void
    {
        $this->assertEquals(8, $this->a->size());
        $this->assertEquals(8, $this->b->size());
        $this->assertEquals(6, $this->c->size());
    }

    public function testGetM() : void
    {
        $this->assertEquals(1, $this->a->m());
        $this->assertEquals(1, $this->b->m());
        $this->assertEquals(1, $this->c->m());
    }

    public function testGetN() : void
    {
        $this->assertEquals(8, $this->a->n());
        $this->assertEquals(8, $this->b->n());
        $this->assertEquals(6, $this->c->n());
    }

    public function testAsArray() : void
    {
        $z = $this->a->asArray();

        $expected = [-15, 25, 35, -36, -72, 89, 106, 45];

        $this->assertEquals($expected, $z);
    }

    public function testAsRowMatrix() : void
    {
        $z = $this->a->asRowMatrix();

        $expected = [[-15, 25, 35, -36, -72, 89, 106, 45]];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAsColumnMatrix() : void
    {
        $z = $this->a->asColumnMatrix();

        $expected = [[-15], [25], [35], [-36], [-72], [89], [106], [45]];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testReshape() : void
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

    public function testTranspose() : void
    {
        $z = $this->a->transpose();

        $outcome = [-15, 25, 35, -36, -72, 89, 106, 45];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($outcome, $z->asArray());
    }

    public function testMap() : void
    {
        $z = $this->a->map(function ($value) {
            return $value > 0. ? 1 : 0;
        });

        $expected = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testReduce() : void
    {
        $scalar = $this->a->reduce(function ($value, $carry) {
            return $carry + ($value / 2.);
        });

        $this->assertEquals(110.3671875, $scalar);
    }

    public function testReciprocal() : void
    {
        $z = $this->a->reciprocal();

        $expected = [
            -0.06666666666666667, 0.04, 0.02857142857142857, -0.027777777777777776,
            -0.013888888888888888, 0.011235955056179775, 0.009433962264150943, 0.022222222222222223,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testArgmin() : void
    {
        $this->assertEquals(4, $this->a->argmin());
        $this->assertEquals(5, $this->b->argmin());
        $this->assertEquals(4, $this->c->argmin());
    }

    public function testArgmax() : void
    {
        $this->assertEquals(6, $this->a->argmax());
        $this->assertEquals(6, $this->b->argmax());
        $this->assertEquals(3, $this->c->argmax());
    }

    public function testDot() : void
    {
        $this->assertEquals(331.54999999999995, $this->a->dot($this->b));
    }

    public function testInner() : void
    {
        $this->assertEquals(331.54999999999995, $this->a->inner($this->b));
    }

    public function testOuter() : void
    {
        $z = $this->a->outer($this->b);

        $expected = [
            [-3.75, -1.5, -30., 7.5, 15., 45., -49.5, -30.],
            [6.25, 2.5, 50., -12.5, -25., -75., 82.5, 50.],
            [8.75, 3.5, 70., -17.5, -35., -105., 115.5, 70.],
            [-9.0, -3.6, -72., 18., 36., 108., -118.8, -72.],
            [-18., -7.2, -144., 36., 72., 216., -237.6, -144.],
            [22.25, 8.9, 178., -44.5, -89., -267., 293.7, 178.],
            [26.5, 10.600000000000001, 212., -53., -106., -318., 349.79999999999995, 212.],
            [11.25, 4.5, 90., -22.5, -45., -135., 148.5, 90.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testCross() : void
    {
        $a = new Vector([1., -0.5, 6.]);

        $b = new Vector([2., 0., 3.]);

        $z = $a->cross($b);

        $expected = [-1.5, 9., 1.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testConvolve() : void
    {
        $z = $this->a->convolve($this->c, 1);

        $expected = [-60.0, 2.5, 259.0, -144., 40.5, 370.1, 462.20000000000005, 9.999999999999886];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testProject() : void
    {
        $z = $this->a->project($this->b);

        $expected = [
            2.8373983739837394, 1.1349593495934958, 22.699186991869915, -5.674796747967479,
            -11.349593495934958, -34.048780487804876, 37.45365853658536, 22.699186991869915,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testMultiplyMatrix() : void
    {
        $z = $this->c->multiply($this->d);

        $expected = [
            [24.92, -6.5, 0.087, -0.2,-1.3, 23.8],
            [0.04, 13.064999999999998, 2.9, 0.4, 0.13, -11.9],
            [4.4, 32.5, -14.5, 600., -0.013000000000000001, -0.0119],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testDivideMatrix() : void
    {
        $z = $this->c->divide($this->d);

        $expected = [
            [0.6420545746388443, -6.5, 96.66666666666667, -2000., -5.2, 5.95],
            [400., 3.2338308457711444, 2.9, 1000., 52., -11.9],
            [3.6363636363636362, 1.3, -0.58, 0.6666666666666666, -520., -11900.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAddMatrix() : void
    {
        $z = $this->c->add($this->d);

        $expected = [
            [10.23, 5.5, 2.9299999999999997, 19.99, 2.1, 13.9],
            [4.01, 8.51, 3.9, 20.02, 2.65, 10.9],
            [5.1, 11.5, -2.1, 50., 2.595, 11.899000000000001],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSubtractMatrix() : void
    {
        $z = $this->c->subtract($this->d);

        $expected = [
            [-2.2300000000000004, 7.5, 2.87, 20.01, 3.1, 9.9],
            [3.99, 4.49, 1.9, 19.98, 2.5500000000000003, 12.9],
            [2.9, 1.5, 7.9, -10., 2.605, 11.901],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testPowMatrix() : void
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

    public function testEqualMatrix() : void
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

    public function testNotEqualMatrix() : void
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

    public function testGreaterMatrix() : void
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

    public function testGreaterEqualMatrix() : void
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

    public function testLessMatrix() : void
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

    public function testLessEqualMatrix() : void
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

    public function testMultiplyVector() : void
    {
        $z = $this->a->multiply($this->b);

        $expected = [-3.75, 2.5, 70., 18., 72., -267., 349.79999999999995, 90.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testDivideVector() : void
    {
        $z = $this->a->divide($this->b);

        $expected = [-60., 250., 17.5, 72., 72., -29.666666666666668, 32.121212121212125, 22.5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAddVector() : void
    {
        $z = $this->a->add($this->b);

        $expected = [-14.75, 25.1, 37., -36.5, -73., 86., 109.3, 47.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSubtractVector() : void
    {
        $z = $this->a->subtract($this->b);

        $expected = [-15.25, 24.9, 33., -35.5, -71., 92., 102.7, 43.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testPowVector() : void
    {
        $z = $this->b->pow($this->a);

        $expected = [
            1073741824.0, 1.0000000000000014E-25, 34359738368.0, 68719476736.0,
            1., -2.909321189362571E+42, 9.172286825801562E+54, 35184372088832.0,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testModVector() : void
    {
        $z = $this->b->mod($this->a);

        $expected = [0, 0, 2, 0, -1, -3, 3, 2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testEqualVector() : void
    {
        $z = $this->b->equal($this->a);

        $expected = [0, 0, 0, 0, 0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testNotEqualVector() : void
    {
        $z = $this->b->notEqual($this->a);

        $expected = [1, 1, 1, 1, 1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testGreaterVector() : void
    {
        $z = $this->b->greater($this->a);

        $expected = [1, 0, 0, 1, 1, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testGreaterEqualVector() : void
    {
        $z = $this->b->greaterEqual($this->a);

        $expected = [1, 0, 0, 1, 1, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testLessVector() : void
    {
        $z = $this->b->less($this->a);

        $expected = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testLessEqualVector() : void
    {
        $z = $this->b->lessEqual($this->a);

        $expected = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testMultiplyScalar() : void
    {
        $z = $this->a->multiply(2);
        
        $expected = [-30, 50, 70, -72, -144, 178, 212, 90];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testDivideScalar() : void
    {
        $z = $this->a->divide(2);

        $expected = [-7.5, 12.5, 17.5, -18, -36, 44.5, 53, 22.5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAddScalar() : void
    {
        $z = $this->a->add(10);

        $expected = [-5, 35, 45, -26, -62, 99, 116, 55];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSubtractScalar() : void
    {
        $z = $this->a->subtract(10);

        $expected = [-25, 15, 25, -46, -82, 79, 96, 35];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testPowScalar() : void
    {
        $z = $this->a->pow(4);

        $expected = [
            50625, 390625, 1500625, 1679616, 26873856, 62742241, 126247696, 4100625
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testModScalar() : void
    {
        $z = $this->a->mod(4);

        $expected = [-3, 1, 3,0, 0, 1, 2, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testEqualScalar() : void
    {
        $z = $this->a->equal(25);

        $expected = [0, 1, 0, 0, 0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testNotEqualScalar() : void
    {
        $z = $this->a->notEqual(25);

        $expected = [1, 0, 1, 1, 1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testGreaterScalar() : void
    {
        $z = $this->b->greater(1);

        $expected = [0, 0, 1, 0, 0, 0, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testGreaterEqualScalar() : void
    {
        $z = $this->b->greaterEqual(1);

        $expected = [0, 0, 1, 0, 0, 0, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testLessScalar() : void
    {
        $z = $this->b->less(1);

        $expected = [1, 1, 0, 1, 1, 1, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testLessEqualScalar() : void
    {
        $z = $this->b->lessEqual(1);

        $expected = [1, 1, 0, 1, 1, 1, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAbs() : void
    {
        $z = $this->a->abs();

        $expected = [15, 25, 35, 36, 72, 89, 106, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSquare() : void
    {
        $z = $this->a->square();

        $expected = [225, 625, 1225, 1296, 5184, 7921, 11236, 2025];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testPow() : void
    {
        $z = $this->a->pow(3);

        $expected = [-3375, 15625, 42875, -46656, -373248, 704969, 1191016, 91125];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSqrt() : void
    {
        $z = $this->c->sqrt();

        $expected = [
            2., 2.5495097567963922, 1.70293863659264, 4.47213595499958,
            1.61245154965971, 3.449637662132068,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testExp() : void
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

    public function testLog() : void
    {
        $z = $this->c->log();

        $expected = [
            1.3862943611198906, 1.8718021769015913, 1.0647107369924282,
            2.995732273553991, 0.9555114450274363, 2.4765384001174837,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSin() : void
    {
        $z = $this->c->sin();

        $expected = [
            -0.7568024953079282, 0.21511998808781552, 0.23924932921398243,
            0.9129452507276277, 0.5155013718214642, -0.6181371122370333,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAsin() : void
    {
        $z = Vector::quick([0.1, 0.3, -0.5])->asin();

        $expected = [
            0.1001674211615598, 0.3046926540153975, -0.5235987755982989,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testCos() : void
    {
        $z = $this->c->cos();

        $expected = [
            -0.6536436208636119, 0.9765876257280235, -0.9709581651495905,
            0.40808206181339196, -0.8568887533689473, 0.7860702961410393,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAcos() : void
    {
        $z = Vector::quick([0.1, 0.3, -0.5])->acos();

        $expected = [
            1.4706289056333368, 1.2661036727794992, 2.0943951023931957,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testTan() : void
    {
        $z = $this->c->tan();

        $expected = [
            1.1578212823495777, 0.22027720034589682, -0.24640539397196634,
            2.237160944224742, -0.6015966130897586, -0.7863636563696398,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAtan() : void
    {
        $z = $this->c->atan();

        $expected = [
            1.3258176636680326, 1.4181469983996315, 1.2387368592520112,
            1.5208379310729538, 1.2036224929766774, 1.486959684726482,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testRad2deg() : void
    {
        $z = $this->c->rad2deg();

        $expected = [
            229.1831180523293, 372.42256683503507, 166.15776058793872,
            1145.9155902616465, 148.96902673401405, 681.8197762056797,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testDeg2rad() : void
    {
        $z = $this->c->deg2rad();

        $expected = [
            0.06981317007977318, 0.11344640137963141, 0.05061454830783556,
            0.3490658503988659, 0.04537856055185257, 0.2076941809873252,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSum() : void
    {
        $this->assertEquals(177., $this->a->sum());
        $this->assertEquals(3.15, $this->b->sum());
        $this->assertEquals(47.9, $this->c->sum());
    }

    public function testProduct() : void
    {
        $this->assertEquals(-14442510600000.0, $this->a->product());
        $this->assertEquals(-0.49500000000000005, $this->b->product());
        $this->assertEquals(46657.52, $this->c->product());
    }

    public function testMin() : void
    {
        $this->assertEquals(-72, $this->a->min());
        $this->assertEquals(-3, $this->b->min());
        $this->assertEquals(2.6, $this->c->min());
    }

    public function testMax() : void
    {
        $this->assertEquals(106, $this->a->max());
        $this->assertEquals(3.3, $this->b->max());
        $this->assertEquals(20., $this->c->max());
    }

    public function testMean() : void
    {
        $this->assertEquals(22.125, $this->a->mean());
        $this->assertEquals(0.39375, $this->b->mean());
        $this->assertEquals(7.983333333333333, $this->c->mean());
    }

    public function testMedian() : void
    {
        $this->assertEquals(30., $this->a->median());
        $this->assertEquals(0.175, $this->b->median());
        $this->assertEquals(5.25, $this->c->median());
    }

    public function testPercentile() : void
    {
        $this->assertEquals(30., $this->a->percentile(50));
        $this->assertEquals(-0.625, $this->b->percentile(25));
        $this->assertEquals(10.55, $this->c->percentile(75));
    }

    public function testVariance() : void
    {
        $this->assertEquals(3227.609375, $this->a->variance());
        $this->assertEquals(3.4965234374999996, $this->b->variance());
        $this->assertEquals(38.77138888888888, $this->c->variance());
    }

    public function testRound() : void
    {
        $z = $this->c->round(2);

        $expected = [4.0, 6.5, 2.9, 20., 2.6, 11.9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testFloor() : void
    {
        $z = $this->c->floor();

        $expected = [4., 6., 2., 20., 2., 11.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testCeil() : void
    {
        $z = $this->c->ceil();

        $expected = [4., 7., 3., 20., 3., 12.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testL1Norm() : void
    {
        $this->assertEquals(423., $this->a->l1Norm());
        $this->assertEquals(12.149999999999999, $this->b->l1Norm());
        $this->assertEquals(47.9, $this->c->l1Norm());
    }

    public function testL2Norm() : void
    {
        $this->assertEquals(172.4441938715247, $this->a->l2Norm());
        $this->assertEquals(5.404858925078433, $this->b->l2Norm());
        $this->assertEquals(24.799798386277256, $this->c->l2Norm());
    }

    public function testPNorm() : void
    {
        $this->assertEquals(135.15554088861361, $this->a->pNorm(3.));
        $this->assertEquals(3.7063242195906976, $this->b->pNorm(5.));
        $this->assertEquals(20.01112107057168, $this->c->pNorm(10.));
    }

    public function testMaxNorm() : void
    {
        $this->assertEquals(106., $this->a->maxNorm());
        $this->assertEquals(3.3, $this->b->maxNorm());
        $this->assertEquals(20., $this->c->maxNorm());
    }

    public function testClip() : void
    {
        $z = $this->a->clip(0., 100);

        $expected = [0., 25, 35, 0., 0., 89, 100., 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testClipLower() : void
    {
        $z = $this->a->clipLower(60.);

        $expected = [60., 60., 60., 60., 60., 89, 106., 60.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testClipUpper() : void
    {
        $z = $this->a->clipUpper(50.);

        $expected = [-15., 25, 35, -36., -72., 50., 50., 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSign() : void
    {
        $z = $this->a->sign();

        $expected = [-1, 1, 1, -1, -1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testNegate() : void
    {
        $z = $this->a->negate();

        $expected = [15, -25, -35, 36, 72, -89, -106, -45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testToString() : void
    {
        $outcome = '[ -15 25 35 -36 -72 89 106 45 ]' . PHP_EOL;
        
        $this->assertEquals($outcome, (string) $this->a);
    }
}
