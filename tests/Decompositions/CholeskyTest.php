<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\Cholesky;
use Tensor\Exceptions\InvalidArgumentException;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Decompositions\Cholesky
 */
class CholeskyTest extends TestCase
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
    public function decompose2x2() : void
    {
        $a = Matrix::quick([
            [9.0, 3.0],
            [3.0, 5.0],
        ]);

        $ch = Cholesky::decompose($a);

        $l = Matrix::quick([
            [3.0, 0.0],
            [1.0, 2.0],
        ]);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);

        // Cross-check: L * L^T reconstructs A.
        $this->assertEqualsWithDelta($a, $ch->l()->matmul($ch->lT()), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decompose3x3() : void
    {
        $a = Matrix::quick([
            [2.0, -1.0,  0.0],
            [-1.0, 2.0, -1.0],
            [0.0, -1.0, 2.0],
        ]);

        $ch = Cholesky::decompose($a);

        $l = Matrix::quick([
            [1.4142135623730951, 0, 0],
            [-0.7071067811865475, 1.224744871391589, 0],
            [0, -0.8164965809277261, 1.1547005383792515],
        ]);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decompose1x1() : void
    {
        $a = Matrix::quick([[9.0]]);

        $ch = Cholesky::decompose($a);

        $l = Matrix::quick([[3.0]]);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeDiagonal() : void
    {
        $a = Matrix::quick([
            [4.0, 0.0, 0.0],
            [0.0, 9.0, 0.0],
            [0.0, 0.0, 16.0],
        ]);

        $ch = Cholesky::decompose($a);

        $l = Matrix::quick([
            [2.0, 0.0, 0.0],
            [0.0, 3.0, 0.0],
            [0.0, 0.0, 4.0],
        ]);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Cholesky::decompose(Matrix::quick([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ]));
    }

    /**
     * @test
     */
    public function lTIsTranspose() : void
    {
        $l = Matrix::quick([
            [3.0, 0.0],
            [1.0, 2.0],
        ]);

        $ch = new Cholesky($l);

        $this->assertEqualsWithDelta($l->transpose(), $ch->lT(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function accessorsReturnMatrices() : void
    {
        $l = Matrix::quick([
            [1.0, 0.0],
            [0.5, 1.0],
        ]);

        $ch = new Cholesky($l);

        $this->assertEquals($l, $ch->l());

        $expectedT = Matrix::quick([
            [1.0, 0.5],
            [0.0, 1.0],
        ]);

        $this->assertEqualsWithDelta($expectedT, $ch->lT(), self::MAX_DELTA);
    }
}
