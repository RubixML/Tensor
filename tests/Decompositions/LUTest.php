<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\LU;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;
use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\CoversClass;
use PHPUnit\Framework\Attributes\Test;

#[CoversClass(LU::class)]
class LUTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    #[Test]
    public function decompose3x3() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $lu = LU::decompose($a);

        $l = Matrix::fromArray([
            [1.0, 0.0, 0.0],
            [0.18181818181818182, 1.0, 0.0],
            [0.9090909090909091, 0.6709677419354838, 1.0],
        ], false);

        $u = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [0.0, 14.09090909090909, -4.181818181818182],
            [0.0, 0.0, -17.10322580645161],
        ], false);

        $p = Matrix::fromArray([
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0],
        ], false);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);

        // And, cross-check the factors are consistent: P * A == L * U.
        $pa = $lu->p()->matmul($a);
        $luProd = $lu->l()->matmul($lu->u());

        $this->assertEqualsWithDelta($pa, $luProd, self::MAX_DELTA);
    }

    #[Test]
    public function decomposeRequiresPivoting() : void
    {
        $a = Matrix::fromArray([
            [0.0,  1.0,  0.0,  0.0],
            [-1.0, 0.0,  0.0,  0.0],
            [0.0,  0.0,  0.0,  2.0],
            [0.0,  0.0,  3.0,  1.0],
        ], false);

        $lu = LU::decompose($a);

        // With row pivoting, P * A must be reproduced by L * U.
        $pa = $lu->p()->matmul($a);
        $luProd = $lu->l()->matmul($lu->u());

        $this->assertEqualsWithDelta($pa, $luProd, self::MAX_DELTA);
    }

    #[Test]
    public function decompose1x1() : void
    {
        $a = Matrix::fromArray([[9.0]], false);

        $lu = LU::decompose($a);

        $l = Matrix::fromArray([[1.0]], false);
        $u = Matrix::fromArray([[9.0]], false);
        $p = Matrix::fromArray([[1.0]], false);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);
    }

    #[Test]
    public function decomposeDiagonal() : void
    {
        $a = Matrix::fromArray([
            [2.0, 0.0],
            [0.0, 3.0],
        ], false);

        $lu = LU::decompose($a);

        $l = Matrix::fromArray([
            [1.0, 0.0],
            [0.0, 1.0],
        ], false);

        $u = Matrix::fromArray([
            [2.0, 0.0],
            [0.0, 3.0],
        ], false);

        $p = Matrix::fromArray([
            [1.0, 0.0],
            [0.0, 1.0],
        ], false);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);
    }

    #[Test]
    public function decomposeNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        LU::decompose(Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false));
    }

    #[Test]
    public function decomposeSingularThrows() : void
    {
        $this->expectException(RuntimeException::class);

        LU::decompose(Matrix::fromArray([
            [1.0, 2.0],
            [2.0, 4.0],
        ], false));
    }

    #[Test]
    public function accessorsReturnMatrices() : void
    {
        $l = Matrix::fromArray([
            [1.0, 0.0],
            [0.5, 1.0],
        ], false);

        $u = Matrix::fromArray([
            [2.0, 3.0],
            [0.0, 4.0],
        ], false);

        $p = Matrix::fromArray([
            [0.0, 1.0],
            [1.0, 0.0],
        ], false);

        $lu = new LU($l, $u, $p);

        $this->assertEquals($l, $lu->l());
        $this->assertEquals($u, $lu->u());
        $this->assertEquals($p, $lu->p());
    }
}
