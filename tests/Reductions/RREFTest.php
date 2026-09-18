<?php

namespace Tensor\Tests\Reductions;

use Tensor\Matrix;
use Tensor\Reductions\RREF;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Reductions\RREF
 */
class RREFTest extends TestCase
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
    public function reduceDiagonalIsIdentity() : void
    {
        // A non-singular diagonal matrix reduces to the identity.
        $a = Matrix::quick([
            [1.0, 0.0, 0.0],
            [0.0, 2.0, 0.0],
            [0.0, 0.0, 3.0],
        ]);

        $rref = RREF::reduce($a);

        $expectedA = Matrix::quick([
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $rref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduce2x2() : void
    {
        $a = Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]);

        $rref = RREF::reduce($a);

        $expectedA = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $rref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduceDiagonal2x2() : void
    {
        $a = Matrix::quick([
            [2.0, 0.0],
            [0.0, 3.0],
        ]);

        $rref = RREF::reduce($a);

        $expectedA = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $rref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduce1x1() : void
    {
        $a = Matrix::quick([[7.0]]);

        $rref = RREF::reduce($a);

        $this->assertEqualsWithDelta(Matrix::quick([[1.0]]), $rref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduceSingular2x2() : void
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Pure-PHP REF fallback; extension tensor is loaded.');
        }

        // A rank-1 matrix has a zero row and one free variable.
        $a = Matrix::quick([
            [1.0, 2.0],
            [2.0, 4.0],
        ]);

        $rref = RREF::reduce($a);

        $expectedA = Matrix::quick([
            [1.0, 2.0],
            [0.0, 0.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $rref->a(), self::MAX_DELTA);

        $aOut = $rref->a()->asArray();

        $this->assertEquals([0.0, 0.0], $aOut[1]);
    }

    /**
     * @test
     */
    public function reduceZeroRow() : void
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Pure-PHP REF fallback; extension tensor is loaded.');
        }

        // A leading zero row is swapped down; the result has a zero row.
        $a = Matrix::quick([
            [0.0, 0.0],
            [1.0, 2.0],
        ]);

        $rref = RREF::reduce($a);

        $expectedA = Matrix::quick([
            [1.0, 2.0],
            [0.0, 0.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $rref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function rankMatchesNumberNonZeroRows() : void
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Pure-PHP REF fallback; extension tensor is loaded.');
        }

        $a = Matrix::quick([
            [1.0, 2.0, 3.0],
            [2.0, 4.0, 6.0],
            [4.0, 8.0, 12.0],
        ]);

        $rref = RREF::reduce($a);

        // Rank is the number of non-zero rows in RREF.
        $aOut = $rref->a()->asArray();

        $rank = 0;

        foreach ($aOut as $row) {
            $isNonZero = false;

            foreach ($row as $v) {
                if (abs($v) > 0.0) {
                    $isNonZero = true;

                    break;
                }
            }

            if ($isNonZero) {
                ++$rank;
            }
        }

        $this->assertEquals(1, $rank);
    }

    /**
     * @test
     */
    public function reduceExactlySingular4x4Has3NonZeroRows() : void
    {
        // Exactly singular (column 3 = column 0 - column 1 + column 2); the
        // RREF must contain exactly three non-zero rows, the fourth being zero.
        // Before the float-tolerance fix, floating-point residual of ~1e-16
        // on the diagonal would cause RREF to report a fourth non-zero row.
        $a = Matrix::quick([
            [2.0, 1.0, 0.0, 1.0],
            [1.0, 2.0, 1.0, 0.0],
            [0.0, 1.0, 2.0, 1.0],
            [1.0, 0.0, 1.0, 2.0],
        ]);

        $rref = RREF::reduce($a);

        $aOut = $rref->a()->asArray();

        $nonZero = 0;

        foreach ($aOut as $row) {
            $isNonZero = false;

            foreach ($row as $v) {
                if (abs($v) > 0.0) {
                    $isNonZero = true;

                    break;
                }
            }

            if ($isNonZero) {
                ++$nonZero;
            }
        }

        $this->assertEquals(3, $nonZero);
    }

    /**
     * @test
     */
    public function accessorsReturnMatrices() : void
    {
        $a = Matrix::quick([
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0],
        ]);

        $rref = new RREF($a);

        $this->assertEqualsWithDelta($a, $rref->a(), self::MAX_DELTA);
    }
}
