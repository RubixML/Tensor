<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\Cholesky;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;
use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\CoversClass;
use PHPUnit\Framework\Attributes\Test;

#[CoversClass(Cholesky::class)]
class CholeskyTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    #[Test]
    public function decompose2x2() : void
    {
        $a = Matrix::fromArray([
            [9.0, 3.0],
            [3.0, 5.0],
        ], false);

        $ch = Cholesky::decompose($a);

        $l = Matrix::fromArray([
            [3.0, 0.0],
            [1.0, 2.0],
        ], false);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);

        // Cross-check: L * L^T reconstructs A.
        $this->assertEqualsWithDelta($a, $ch->l()->matmul($ch->lT()), self::MAX_DELTA);
    }

    #[Test]
    public function decompose3x3() : void
    {
        $a = Matrix::fromArray([
            [2.0, -1.0,  0.0],
            [-1.0, 2.0, -1.0],
            [0.0, -1.0, 2.0],
        ], false);

        $ch = Cholesky::decompose($a);

        $l = Matrix::fromArray([
            [1.4142135623730951, 0, 0],
            [-0.7071067811865475, 1.224744871391589, 0],
            [0, -0.8164965809277261, 1.1547005383792515],
        ], false);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);
    }

    #[Test]
    public function decompose1x1() : void
    {
        $a = Matrix::fromArray([[9.0]], false);

        $ch = Cholesky::decompose($a);

        $l = Matrix::fromArray([[3.0]], false);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);
    }

    #[Test]
    public function decomposeDiagonal() : void
    {
        $a = Matrix::fromArray([
            [4.0, 0.0, 0.0],
            [0.0, 9.0, 0.0],
            [0.0, 0.0, 16.0],
        ], false);

        $ch = Cholesky::decompose($a);

        $l = Matrix::fromArray([
            [2.0, 0.0, 0.0],
            [0.0, 3.0, 0.0],
            [0.0, 0.0, 4.0],
        ], false);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $ch, self::MAX_DELTA);
    }

    #[Test]
    public function decomposeNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Cholesky::decompose(Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false));
    }

    #[Test]
    public function decomposeIndefiniteThrows() : void
    {
        $this->expectException(RuntimeException::class);

        Cholesky::decompose(Matrix::fromArray([
            [1.0, 2.0],
            [2.0, 1.0],
        ], false));
    }

    #[Test]
    public function decomposeZeroPivotThrows() : void
    {
        $this->expectException(RuntimeException::class);

        Cholesky::decompose(Matrix::fromArray([
            [0.0, 1.0],
            [1.0, 1.0],
        ], false));
    }

    #[Test]
    public function decomposeSingularThrows() : void
    {
        $this->expectException(RuntimeException::class);

        Cholesky::decompose(Matrix::fromArray([
            [1.0, 2.0],
            [2.0, 4.0],
        ], false));
    }

    #[Test]
    public function lTIsTranspose() : void
    {
        $l = Matrix::fromArray([
            [3.0, 0.0],
            [1.0, 2.0],
        ], false);

        $ch = new Cholesky($l);

        $this->assertEqualsWithDelta($l->transpose(), $ch->lT(), self::MAX_DELTA);
    }

    #[Test]
    public function accessorsReturnMatrices() : void
    {
        $l = Matrix::fromArray([
            [1.0, 0.0],
            [0.5, 1.0],
        ], false);

        $ch = new Cholesky($l);

        $this->assertEquals($l, $ch->l());

        $expectedT = Matrix::fromArray([
            [1.0, 0.5],
            [0.0, 1.0],
        ], false);

        $this->assertEqualsWithDelta($expectedT, $ch->lT(), self::MAX_DELTA);
    }
}
