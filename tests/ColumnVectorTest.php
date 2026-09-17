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
use Tensor\Exceptions\DimensionalityMismatch;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\ColumnVector
 */
class ColumnVectorTest extends TestCase
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
        $vector = ColumnVector::build([-15, 25, 35]);

        $this->assertInstanceOf(ColumnVector::class, $vector);
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
    public function shape() : void
    {
        $vector = ColumnVector::quick([-15, 25, 35]);

        $this->assertEquals([3], $vector->shape());
    }

    /**
     * @test
     */
    public function shapeString() : void
    {
        $vector = ColumnVector::quick([-15, 25, 35]);

        $this->assertEquals('3', $vector->shapeString());
    }

    /**
     * @test
     */
    public function size() : void
    {
        $vector = ColumnVector::quick([-15, 25, 35]);

        $this->assertEquals(3, $vector->size());
    }

    /**
     * @test
     */
    public function m() : void
    {
        $vector = ColumnVector::quick([-15, 25, 35]);

        $this->assertEquals(3, $vector->m());
    }

    /**
     * @test
     */
    public function n() : void
    {
        $vector = ColumnVector::quick([-15, 25, 35]);

        $this->assertEquals(1, $vector->n());
    }

    /**
     * @test
     */
    public function multiply() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->multiply($b);

        $expected = Matrix::quick([
            [-93.45, 15, -0.44999999999999996],
            [0.25, 50.24999999999999, 25],
            [38.5, 175, -175],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function divide() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->divide($b);

        $expected = Matrix::quick([
            [-2.407704654895666, 15, -500.],
            [2500.0, 12.437810945273633, 25],
            [31.818181818181817, 7, -7],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function add() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->add($b);

        $expected = Matrix::quick([
            [-8.77, -16, -14.97],
            [25.01, 27.009999999999998, 26],
            [36.1, 40, 30],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function subtract() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->subtract($b);

        $expected = Matrix::quick([
            [-21.23, -14, -15.03],
            [24.99, 22.990000000000002, 24],
            [33.9, 30, 40],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function equal() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->equal($b);

        $expected = Matrix::quick([
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function notEqual() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->notEqual($b);

        $expected = Matrix::quick([
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function greater() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->greater($b);

        $expected = Matrix::quick([
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function greaterEqual() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->greaterEqual($b);

        $expected = Matrix::quick([
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function less() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->less($b);

        $expected = Matrix::quick([
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function lessEqual() : void
    {
        $a = ColumnVector::quick([-15, 25, 35]);

        $b = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ]);

        $c = $a->lessEqual($b);

        $expected = Matrix::quick([
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function transposeReturnsVector() : void
    {
        $a = ColumnVector::quick([1.0, 2.0, 3.0]);

        $b = $a->transpose();

        $this->assertInstanceOf(Vector::class, $b);
        $this->assertEquals(Vector::quick([1.0, 2.0, 3.0]), $b);
    }

    /**
     * @test
     */
    public function sizes() : void
    {
        $a = ColumnVector::quick([1.0, 2.0, 3.0]);

        $this->assertEquals(3, $a->m());
        $this->assertEquals(1, $a->n());
        $this->assertEquals(3, $a->size());
    }

    /**
     * @test
     */
    public function matmul() : void
    {
        $a = ColumnVector::quick([1.0, 2.0, 3.0]);

        $b = Matrix::quick([
            [1.0, 2.0, 3.0],
        ]);

        $c = $a->matmul($b);

        $expected = Matrix::quick([
            [1.0, 2.0, 3.0],
            [2.0, 4.0, 6.0],
            [3.0, 6.0, 9.0],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function matmulDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::quick([1.0, 2.0, 3.0])->matmul(Matrix::quick([
            [1.0, 2.0, 3.0, 4.0],
            [5.0, 6.0, 7.0, 8.0],
            [9.0, 10.0, 11.0, 12.0],
        ]));
    }

    /**
     * @test
     */
    public function powMatrix() : void
    {
        $a = ColumnVector::quick([2.0, 3.0, 4.0]);

        $b = Matrix::quick([
            [1.0, 2.0, 3.0],
            [1.0, 1.0, 1.0],
            [2.0, 0.0, 1.0],
        ]);

        $c = $a->powMatrix($b);

        $expected = Matrix::quick([
            [2.0, 4.0, 8.0],
            [3.0, 3.0, 3.0],
            [16.0, 1.0, 4.0],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function powMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::quick([1.0, 2.0, 3.0])->powMatrix(Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]));
    }

    /**
     * @test
     */
    public function modMatrix() : void
    {
        $a = ColumnVector::quick([10.0, 12.0, 15.0]);

        $b = Matrix::quick([
            [3.0, 4.0, 5.0],
            [2.0, 3.0, 4.0],
            [5.0, 6.0, 7.0],
        ]);

        $c = $a->modMatrix($b);

        $expected = Matrix::quick([
            [1.0, 2.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.0, 3.0, 1.0],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function modMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::quick([1.0, 2.0, 3.0])->modMatrix(Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]));
    }

    /**
     * @test
     */
    public function multiplyMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::quick([1.0, 2.0, 3.0])->multiplyMatrix(Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]));
    }

    /**
     * @test
     */
    public function divideMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::quick([1.0, 2.0, 3.0])->divideMatrix(Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]));
    }
}
