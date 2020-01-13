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

class ColumnVectorTest extends TestCase
{
    /**
     * @var \Tensor\ColumnVector
     */
    protected $a;

    /**
     * @var \Tensor\Vector
     */
    protected $b;

    /**
     * @var \Tensor\Matrix
     */
    protected $c;

    public function setUp() : void
    {
        $this->a = ColumnVector::build([-15, 25, 35]);

        $this->b = Vector::quick([0.25, 0.1, 2.]);

        $this->c = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5,],
        ]);
    }

    public function testBuildVector() : void
    {
        $this->assertInstanceOf(ColumnVector::class, $this->a);
        $this->assertInstanceOf(Vector::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Arithmetic::class, $this->a);
        $this->assertInstanceOf(Comparable::class, $this->a);
        $this->assertInstanceOf(Trigonometric::class, $this->a);
        $this->assertInstanceOf(Statistical::class, $this->a);
        $this->assertInstanceOf(ArrayLike::class, $this->a);
    }

    public function testShape() : void
    {
        $this->assertEquals([3], $this->a->shape());
    }

    public function testShapeString() : void
    {
        $this->assertEquals('3', $this->a->shapeString());
    }

    public function testSize() : void
    {
        $this->assertEquals(3, $this->a->size());
    }

    public function testGetM() : void
    {
        $this->assertEquals(3, $this->a->m());
    }

    public function testGetN() : void
    {
        $this->assertEquals(1, $this->a->n());
    }

    public function testMultiplyMatrix() : void
    {
        $z = $this->a->multiply($this->c);

        $expected = [
            [-93.45, 15, -0.44999999999999996],
            [0.25, 50.24999999999999, 25],
            [38.5, 175, -175],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testDivideMatrix() : void
    {
        $z = $this->a->divide($this->c);

        $expected = [
            [-2.407704654895666, 15, -500.],
            [2500., 12.437810945273633, 25],
            [31.818181818181817, 7, -7],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testAddMatrix() : void
    {
        $z = $this->a->add($this->c);

        $expected = [
            [-8.77, -16, -14.97],
            [25.01, 27.009999999999998, 26],
            [36.1, 40, 30],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testSubtractMatrix() : void
    {
        $z = $this->a->subtract($this->c);

        $expected = [
            [-21.23, -14, -15.03],
            [24.99, 22.990000000000002, 24],
            [33.9, 30, 40],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testEqualMatrix() : void
    {
        $z = $this->a->equal($this->c);

        $expected = [
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testNotEqualMatrix() : void
    {
        $z = $this->a->notEqual($this->c);

        $expected = [
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testGreaterMatrix() : void
    {
        $z = $this->a->greater($this->c);

        $expected = [
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testGreaterEqualMatrix() : void
    {
        $z = $this->a->greaterEqual($this->c);

        $expected = [
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testLessMatrix() : void
    {
        $z = $this->a->less($this->c);

        $expected = [
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function testLessEqualMatrix() : void
    {
        $z = $this->a->lessEqual($this->c);

        $expected = [
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }
}
