<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\LU;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;
use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(LU::class)]
class LUTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    #[\PHPUnit\Framework\Attributes\Test]
    public function decompose3x3() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $lu = LU::decompose($a);

        $l = Matrix::quick([
            [1.0, 0, 0],
            [0.18181818181818182, 1.0, 0],
            [0.9090909090909091, 0.6709677419354838, 1.0],
        ]);

        $u = Matrix::quick([
            [22.0, -17.0, 12.0],
            [0.0, 14.09090909090909, -4.181818181818182],
            [0.0, 0.0, -17.10322580645161],
        ]);

        $p = Matrix::quick([
            [1.0, 0, 0],
            [0.0, 1.0, 0],
            [0.0, 0.0, 1.0],
        ]);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);

        // And, cross-check the factors are consistent: P * A == L * U.
        $pa = $lu->p()->matmul($a);
        $luProd = $lu->l()->matmul($lu->u());

        $this->assertEqualsWithDelta($pa, $luProd, self::MAX_DELTA);
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function decomposeRequiresPivoting() : void
    {
        $a = Matrix::quick([
            [0.0,  1.0,  0.0,  0.0],
            [-1.0, 0.0,  0.0,  0.0],
            [0.0,  0.0,  0.0,  2.0],
            [0.0,  0.0,  3.0,  1.0],
        ]);

        $lu = LU::decompose($a);

        // With row pivoting, P * A must be reproduced by L * U.
        $pa = $lu->p()->matmul($a);
        $luProd = $lu->l()->matmul($lu->u());

        $this->assertEqualsWithDelta($pa, $luProd, self::MAX_DELTA);
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function decompose1x1() : void
    {
        $a = Matrix::quick([[9.0]]);

        $lu = LU::decompose($a);

        $l = Matrix::quick([[1.0]]);
        $u = Matrix::quick([[9.0]]);
        $p = Matrix::quick([[1.0]]);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function decomposeDiagonal() : void
    {
        $a = Matrix::quick([
            [2.0, 0.0],
            [0.0, 3.0],
        ]);

        $lu = LU::decompose($a);

        $l = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $u = Matrix::quick([
            [2.0, 0.0],
            [0.0, 3.0],
        ]);

        $p = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function decomposeNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        LU::decompose(Matrix::quick([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ]));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function decomposeSingularThrows() : void
    {
        $this->expectException(RuntimeException::class);

        LU::decompose(Matrix::quick([
            [1.0, 2.0],
            [2.0, 4.0],
        ]));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function accessorsReturnMatrices() : void
    {
        $l = Matrix::quick([
            [1.0, 0.0],
            [0.5, 1.0],
        ]);

        $u = Matrix::quick([
            [2.0, 3.0],
            [0.0, 4.0],
        ]);

        $p = Matrix::quick([
            [0.0, 1.0],
            [1.0, 0.0],
        ]);

        $lu = new LU($l, $u, $p);

        $this->assertEquals($l, $lu->l());
        $this->assertEquals($u, $lu->u());
        $this->assertEquals($p, $lu->p());
    }
}
