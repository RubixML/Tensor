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
 * @covers \Tensor\ColumnVector
 */
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

    /**
     * @before
     */
    public function setUp() : void
    {
        $this->a = ColumnVector::build([-15, 25, 35]);

        $this->b = Vector::quick([0.25, 0.1, 2.]);

        $this->c = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);
    }

    /**
     * @test
     */
    public function build() : void
    {
        $this->assertInstanceOf(ColumnVector::class, $this->a);
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
    public function shape() : void
    {
        $this->assertEquals([3], $this->a->shape());
    }

    /**
     * @test
     */
    public function shapeString() : void
    {
        $this->assertEquals('3', $this->a->shapeString());
    }

    /**
     * @test
     */
    public function size() : void
    {
        $this->assertEquals(3, $this->a->size());
    }

    /**
     * @test
     */
    public function m() : void
    {
        $this->assertEquals(3, $this->a->m());
    }

    /**
     * @test
     */
    public function n() : void
    {
        $this->assertEquals(1, $this->a->n());
    }

    /**
     * @test
     */
    public function multiplyMatrix() : void
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

    /**
     * @test
     */
    public function divideMatrix() : void
    {
        $z = $this->a->divide($this->c);

        $expected = [
            [-2.407704654895666, 15, -500.],
            [2500.0, 12.437810945273633, 25],
            [31.818181818181817, 7, -7],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addMatrix() : void
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

    /**
     * @test
     */
    public function subtractMatrix() : void
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

    /**
     * @test
     */
    public function equalMatrix() : void
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

    /**
     * @test
     */
    public function notEqualMatrix() : void
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

    /**
     * @test
     */
    public function greaterMatrix() : void
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

    /**
     * @test
     */
    public function greaterEqualMatrix() : void
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

    /**
     * @test
     */
    public function lessMatrix() : void
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

    /**
     * @test
     */
    public function lessEqualMatrix() : void
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
