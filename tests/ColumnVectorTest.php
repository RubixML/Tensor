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
use PHPUnit\Framework\Attributes\CoversClass;
use PHPUnit\Framework\Attributes\Test;

#[CoversClass(ColumnVector::class)]
class ColumnVectorTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    #[Test]
    public function fromArray() : void
    {
        $vector = ColumnVector::fromArray([-15, 25, 35]);

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

    #[Test]
    public function shape() : void
    {
        $vector = ColumnVector::fromArray([-15, 25, 35], false);

        $this->assertEquals([3], $vector->shape());
    }

    #[Test]
    public function shapeString() : void
    {
        $vector = ColumnVector::fromArray([-15, 25, 35], false);

        $this->assertEquals('3', $vector->shapeString());
    }

    #[Test]
    public function testSize() : void
    {
        $vector = ColumnVector::fromArray([-15, 25, 35], false);

        $this->assertEquals(3, $vector->size());
    }

    #[Test]
    public function m() : void
    {
        $vector = ColumnVector::fromArray([-15, 25, 35], false);

        $this->assertEquals(3, $vector->m());
    }

    #[Test]
    public function n() : void
    {
        $vector = ColumnVector::fromArray([-15, 25, 35], false);

        $this->assertEquals(1, $vector->n());
    }

    #[Test]
    public function multiply() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->multiply($b);

        $expected = Matrix::fromArray([
            [-93.45, 15, -0.44999999999999996],
            [0.25, 50.24999999999999, 25],
            [38.5, 175, -175],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function divide() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->divide($b);

        $expected = Matrix::fromArray([
            [-2.407704654895666, 15, -500.],
            [2500.0, 12.437810945273633, 25],
            [31.818181818181817, 7, -7],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function add() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->add($b);

        $expected = Matrix::fromArray([
            [-8.77, -16, -14.97],
            [25.01, 27.009999999999998, 26],
            [36.1, 40, 30],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function subtract() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->subtract($b);

        $expected = Matrix::fromArray([
            [-21.23, -14, -15.03],
            [24.99, 22.990000000000002, 24],
            [33.9, 30, 40],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function equal() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->equal($b);

        $expected = Matrix::fromArray([
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function notEqual() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->notEqual($b);

        $expected = Matrix::fromArray([
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function greater() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->greater($b);

        $expected = Matrix::fromArray([
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function greaterEqual() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->greaterEqual($b);

        $expected = Matrix::fromArray([
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function less() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->less($b);

        $expected = Matrix::fromArray([
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function lessEqual() : void
    {
        $a = ColumnVector::fromArray([-15, 25, 35], false);

        $b = Matrix::fromArray([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5],
        ], false);

        $c = $a->lessEqual($b);

        $expected = Matrix::fromArray([
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function transposeReturnsVector() : void
    {
        $a = ColumnVector::fromArray([1.0, 2.0, 3.0], false);

        $b = $a->transpose();

        $this->assertInstanceOf(Vector::class, $b);
        $this->assertEquals(Vector::fromArray([1.0, 2.0, 3.0], false), $b);
    }

    #[Test]
    public function sizes() : void
    {
        $a = ColumnVector::fromArray([1.0, 2.0, 3.0], false);

        $this->assertEquals(3, $a->m());
        $this->assertEquals(1, $a->n());
        $this->assertEquals(3, $a->size());
    }

    #[Test]
    public function matmul() : void
    {
        $a = ColumnVector::fromArray([1.0, 2.0, 3.0], false);

        $b = Matrix::fromArray([
            [1.0, 2.0, 3.0],
        ], false);

        $c = $a->matmul($b);

        $expected = Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [2.0, 4.0, 6.0],
            [3.0, 6.0, 9.0],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function matmulDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::fromArray([1.0, 2.0, 3.0], false)->matmul(Matrix::fromArray([
            [1.0, 2.0, 3.0, 4.0],
            [5.0, 6.0, 7.0, 8.0],
            [9.0, 10.0, 11.0, 12.0],
        ], false));
    }

    #[Test]
    public function powMatrix() : void
    {
        $a = ColumnVector::fromArray([2.0, 3.0, 4.0], false);

        $b = Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [1.0, 1.0, 1.0],
            [2.0, 0.0, 1.0],
        ], false);

        $c = $a->powMatrix($b);

        $expected = Matrix::fromArray([
            [2.0, 4.0, 8.0],
            [3.0, 3.0, 3.0],
            [16.0, 1.0, 4.0],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function powMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::fromArray([1.0, 2.0, 3.0], false)->powMatrix(Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false));
    }

    #[Test]
    public function modMatrix() : void
    {
        $a = ColumnVector::fromArray([10.0, 12.0, 15.0], false);

        $b = Matrix::fromArray([
            [3.0, 4.0, 5.0],
            [2.0, 3.0, 4.0],
            [5.0, 6.0, 7.0],
        ], false);

        $c = $a->modMatrix($b);

        $expected = Matrix::fromArray([
            [1.0, 2.0, 0.0],
            [0.0, 0.0, 0.0],
            [0.0, 3.0, 1.0],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function modMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::fromArray([1.0, 2.0, 3.0], false)->modMatrix(Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false));
    }

    #[Test]
    public function multiplyMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::fromArray([1.0, 2.0, 3.0], false)->multiplyMatrix(Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false));
    }

    #[Test]
    public function divideMatrixDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        ColumnVector::fromArray([1.0, 2.0, 3.0], false)->divideMatrix(Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false));
    }

    #[Test]
    public function serializeRoundTripPreservesColumnVector() : void
    {
        $vector = ColumnVector::fromArray([1.0, 2.0, 3.0]);

        $unserialised = unserialize(serialize($vector));

        $this->assertInstanceOf(ColumnVector::class, $unserialised);
        $this->assertEquals($vector->asArray(), $unserialised->asArray());
        $this->assertEquals($vector->shape(), $unserialised->shape());

        // The serialised payload must still be a Vector subclass so it stays
        // byte-compatible with the Tensor-Ext ColumnVector.
        $this->assertStringStartsWith(
            'O:19:"Tensor\\ColumnVector":2:{',
            serialize($vector)
        );
    }

    #[Test]
    public function asTensorBuffer() : void
    {
        $vector = ColumnVector::fromArray([1.0, 2.0, 3.0], false);

        $buffer = $vector->asTensorBuffer();

        $this->assertInstanceOf(\Tensor\TensorBuffer::class, $buffer);
        $this->assertEquals([1.0, 2.0, 3.0], $buffer->toArray());
        $this->assertSame(3, $buffer->count());
        $this->assertEquals(3.0, $buffer->get(2));
    }
}
