<?php

namespace Tensor\Tests\Reductions;

use Tensor\Matrix;
use Tensor\Reductions\REF;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\SingularMatrix;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Reductions\REF
 */
class REFTest extends TestCase
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
    public function reduce2x2() : void
    {
        $a = Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]);

        $ref = REF::reduce($a);

        // Partial pivoting selects the largest magnitude in each column, so the
        // rows are swapped to bring 3 (col 0) to the top and 4 (col 1) to the right.
        $expectedA = Matrix::quick([
            [3.0, 4.0],
            [0.0, 2.0 / 3.0],
        ]);

        $this->assertEquals(1, $ref->swaps());
        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduce3x3() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $ref = REF::reduce($a);

        $expectedA = Matrix::quick([
            [22.0, -17.0, 12.0],
            [0.0, 14.09090909090909, -4.181818181818182],
            [0.0, 0.0, -17.10322580645161],
        ]);

        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduce2x3Rectangular() : void
    {
        $a = Matrix::quick([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ]);

        $ref = REF::reduce($a);

        // Partial pivoting brings 4 to the top of column 0.
        $expectedA = Matrix::quick([
            [4.0, 5.0, 6.0],
            [0.0, 0.75, 1.5],
        ]);

        $this->assertEquals(1, $ref->swaps());
        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduceRequiresPivoting() : void
    {
        // First column is [0, 5] - a row swap is required to pivot.
        $a = Matrix::quick([
            [0.0, 1.0],
            [5.0, 2.0],
        ]);

        $ref = REF::reduce($a);

        // REF should still be valid: the second row's leading element
        // should be used as the pivot, and the first row below it zeroed.
        $this->assertGreaterThanOrEqual(1, $ref->swaps());

        $expectedA = Matrix::quick([
            [5.0, 2.0],
            [0.0, 1.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduce1x1() : void
    {
        $a = Matrix::quick([[7.0]]);

        $ref = REF::reduce($a);

        $expectedA = Matrix::quick([[7.0]]);

        $this->assertEquals(0, $ref->swaps());
        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduceDiagonal() : void
    {
        $a = Matrix::quick([
            [2.0, 0.0],
            [0.0, 3.0],
        ]);

        $ref = REF::reduce($a);

        // Diagonal is already in row echelon form.
        $expectedA = Matrix::quick([
            [2.0, 0.0],
            [0.0, 3.0],
        ]);

        $this->assertEquals(0, $ref->swaps());
        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function reduceZeroRow() : void
    {
        // One zero row at the top, non-zero row at the bottom.
        $a = Matrix::quick([
            [0.0, 0.0],
            [1.0, 2.0],
        ]);

        $ref = REF::reduce($a);

        // The zero row remains zero. After reduction the pivots should appear
        // in the first column of the non-zero row and the zero row should have
        // all-zero entries.
        $aOut = $ref->a()->asArray();

        $this->assertEquals([0.0, 0.0], $aOut[1]);
    }

    /**
     * @test
     */
    public function reduceSingularKeepsPivotScale() : void
    {
        // A rank-1 matrix is singular: Gaussian elimination must fail and the
        // row reduction fallback must produce the same (non-normalised) REF
        // convention as Gaussian elimination - the pivot keeps its value.
        $a = Matrix::quick([
            [2.0, 4.0],
            [1.0, 2.0],
        ]);

        $ref = REF::reduce($a);

        $expectedA = Matrix::quick([
            [2.0, 4.0],
            [0.0, 0.0],
        ]);

        $this->assertEqualsWithDelta($expectedA, $ref->a(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function constructorWithNegativeSwapsThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        new REF(Matrix::quick([[1.0]]), -1);
    }

    /**
     * @test
     */
    public function constructorWithZeroSwaps() : void
    {
        $a = Matrix::quick([[1.0]]);

        $ref = new REF($a, 0);

        $this->assertEqualsWithDelta($a, $ref->a(), self::MAX_DELTA);
        $this->assertEquals(0, $ref->swaps());
    }

    /**
     * @test
     */
    public function constructorWithPositiveSwaps() : void
    {
        $a = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $ref = new REF($a, 2);

        $this->assertEqualsWithDelta($a, $ref->a(), self::MAX_DELTA);

        $this->assertEquals(2, $ref->swaps());
    }

    /**
     * @test
     */
    public function reduceExactlySingular4x4GaussianThrowsSingularMatrix() : void
    {
        if (extension_loaded('tensor')) {
            // The extension exposes only reduce(), which handles the singular
            // case via a C fallback and does not expose gaussianElimination().
            $this->markTestSkipped('Extension REF has no gaussianElimination method.');
        }

        // Exactly singular (column 3 = column 0 - column 1 + column 2); the
        // pure-PHP gaussian elimination path must detect the tiny residual
        // (a ~1e-16 diagonal entry) as singular and route through the row
        // reduction fallback.
        $a = Matrix::quick([
            [2.0, 1.0, 0.0, 1.0],
            [1.0, 2.0, 1.0, 0.0],
            [0.0, 1.0, 2.0, 1.0],
            [1.0, 0.0, 1.0, 2.0],
        ]);

        $this->expectException(SingularMatrix::class);

        REF::gaussianElimination($a);
    }
}
