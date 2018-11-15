<?php

namespace Rubix\Tensor\Tests;

use Rubix\Tensor\Tensor;
use Rubix\Tensor\Vector;
use Rubix\Tensor\Matrix;
use Rubix\Tensor\ColumnVector;
use PHPUnit\Framework\TestCase;

class ColumnVectorTest extends TestCase
{
    protected $a;

    protected $b;

    protected $c;

    public function setUp()
    {
        $this->a = ColumnVector::build([-15, 25, 35]);

        $this->b = Vector::quick([0.25, 0.1, 2.]);

        $this->c = Matrix::quick([
            [6.23, -1, 0.03],
            [0.01, 2.01, 1],
            [1.1, 5, -5,],
        ]);
    }

    public function test_build_vector()
    {
        $this->assertInstanceOf(ColumnVector::class, $this->a);
        $this->assertInstanceOf(Vector::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
    }

    public function test_shape()
    {
        $this->assertEquals([3, 1], $this->a->shape());

    }

    public function test_size()
    {
        $this->assertEquals(3, $this->a->size());
    }

    public function test_get_m()
    {
        $this->assertEquals(3, $this->a->m());
    }

    public function test_get_n()
    {
        $this->assertEquals(1, $this->a->n());
    }

    public function test_multiply_matrix()
    {
        $z = $this->a->multiply($this->c);

        $y = [
            [-93.45, 15, -0.44999999999999996],
            [0.25, 50.24999999999999, 25],
            [38.5, 175, -175],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_matrix()
    {
        $z = $this->a->divide($this->c);

        $y = [
            [-2.407704654895666, 15, -500.],
            [2500., 12.437810945273633, 25],
            [31.818181818181817, 7, -7],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_matrix()
    {
        $z = $this->a->add($this->c);

        $y = [
            [-8.77, -16, -14.97],
            [25.01, 27.009999999999998, 26],
            [36.1, 40, 30],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_matrix()
    {
        $z = $this->a->subtract($this->c);

        $y = [
            [-21.23, -14, -15.03],
            [24.99, 22.990000000000002, 24],
            [33.9, 30, 40],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_equal_matrix()
    {
        $z = $this->a->equal($this->c);

        $y = [
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_matrix()
    {
        $z = $this->a->greater($this->c);

        $y = [
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_equal_matrix()
    {
        $z = $this->a->greaterEqual($this->c);

        $y = [
            [0, 0, 0],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_matrix()
    {
        $z = $this->a->less($this->c);

        $y = [
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_equal_matrix()
    {
        $z = $this->a->lessEqual($this->c);

        $y = [
            [1, 1, 1],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }
}
