<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\SVD;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Decompositions\SVD
 */
class SVDTest extends TestCase
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
    public function decomposeSquare3x3() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $svd = SVD::decompose($a);

        $this->assertCount(3, $svd->singularValues());

        $this->assertEqualsWithDelta(34.66917512262571, $svd->singularValues()[0], self::MAX_DELTA);
        $this->assertEqualsWithDelta(17.12630582468919, $svd->singularValues()[1], self::MAX_DELTA);
        $this->assertEqualsWithDelta(8.929610580306822, $svd->singularValues()[2], self::MAX_DELTA);

        // The decomposition must reconstruct the original matrix.
        $this->assertEqualsWithDelta($a, $this->reconstruct($svd, 3, 3), self::MAX_DELTA);

        // Both U and V must be orthogonal matrices.
        $this->assertEqualsWithDelta(Matrix::identity(3), $svd->u()->transpose()->matmul($svd->u()), self::MAX_DELTA);
        $this->assertEqualsWithDelta(Matrix::identity(3), $svd->vT()->matmul($svd->vT()->transpose()), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeSquare2x2() : void
    {
        $a = Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
        ]);

        $svd = SVD::decompose($a);

        $this->assertCount(2, $svd->singularValues());

        $this->assertEqualsWithDelta($a, $this->reconstruct($svd, 2, 2), self::MAX_DELTA);

        $this->assertEqualsWithDelta(Matrix::identity(2), $svd->u()->transpose()->matmul($svd->u()), self::MAX_DELTA);
        $this->assertEqualsWithDelta(Matrix::identity(2), $svd->vT()->matmul($svd->vT()->transpose()), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeTall() : void
    {
        $a = Matrix::quick([
            [1.0, 2.0],
            [3.0, 4.0],
            [5.0, 6.0],
            [7.0, 8.0],
        ]);

        $svd = SVD::decompose($a);

        $this->assertCount(2, $svd->singularValues());

        $this->assertSame([4, 4], $svd->u()->shape());
        $this->assertSame([2, 2], $svd->vT()->shape());

        $this->assertEqualsWithDelta($a, $this->reconstruct($svd, 4, 2), self::MAX_DELTA);

        $this->assertEqualsWithDelta(Matrix::identity(4), $svd->u()->transpose()->matmul($svd->u()), self::MAX_DELTA);
        $this->assertEqualsWithDelta(Matrix::identity(2), $svd->vT()->matmul($svd->vT()->transpose()), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeWide() : void
    {
        $a = Matrix::quick([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ]);

        $svd = SVD::decompose($a);

        $this->assertCount(2, $svd->singularValues());

        $this->assertSame([2, 2], $svd->u()->shape());
        $this->assertSame([3, 3], $svd->vT()->shape());

        $this->assertEqualsWithDelta($a, $this->reconstruct($svd, 2, 3), self::MAX_DELTA);

        $this->assertEqualsWithDelta(Matrix::identity(2), $svd->u()->transpose()->matmul($svd->u()), self::MAX_DELTA);
        $this->assertEqualsWithDelta(Matrix::identity(3), $svd->vT()->matmul($svd->vT()->transpose()), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decompose1x1() : void
    {
        $a = Matrix::quick([[9.0]]);

        $svd = SVD::decompose($a);

        $this->assertEqualsWithDelta([9.0], $svd->singularValues(), self::MAX_DELTA);

        $this->assertEqualsWithDelta($a, $this->reconstruct($svd, 1, 1), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeRankDeficient() : void
    {
        $a = Matrix::quick([
            [1.0, 1.0],
            [2.0, 2.0],
        ]);

        $svd = SVD::decompose($a);

        $this->assertCount(2, $svd->singularValues());

        $this->assertEqualsWithDelta(sqrt(10.0), $svd->singularValues()[0], self::MAX_DELTA);
        $this->assertEqualsWithDelta(0.0, $svd->singularValues()[1], self::MAX_DELTA);

        $this->assertEqualsWithDelta($a, $this->reconstruct($svd, 2, 2), self::MAX_DELTA);

        $this->assertEqualsWithDelta(Matrix::identity(2), $svd->u()->transpose()->matmul($svd->u()), self::MAX_DELTA);
        $this->assertEqualsWithDelta(Matrix::identity(2), $svd->vT()->matmul($svd->vT()->transpose()), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function constructAndAccess() : void
    {
        $u = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $singularValues = [5.0, 3.0];

        $vT = Matrix::quick([
            [1.0, 0.0],
            [0.0, 1.0],
        ]);

        $svd = new SVD($u, $singularValues, $vT);

        $this->assertEqualsWithDelta($u, $svd->u(), self::MAX_DELTA);
        $this->assertEquals($singularValues, $svd->singularValues());
        $this->assertEqualsWithDelta($vT, $svd->vT(), self::MAX_DELTA);

        // v is the transpose of vT.
        $this->assertEqualsWithDelta($vT->transpose(), $svd->v(), self::MAX_DELTA);

        // The singular value matrix is the diagonal of the singular values.
        $expectedS = Matrix::quick([
            [5.0, 0.0],
            [0.0, 3.0],
        ]);

        $this->assertEqualsWithDelta($expectedS, $svd->s(), self::MAX_DELTA);
    }

    /**
     * Reconstruct matrix A = U * S * V^T padded to the shape of A.
     *
     * @param SVD $svd
     * @param int $m
     * @param int $n
     * @return Matrix
     */
    private function reconstruct(SVD $svd, int $m, int $n) : Matrix
    {
        $s = Matrix::zeros($m, $n)->asArray();

        foreach ($svd->singularValues() as $i => $value) {
            $s[$i][$i] = $value;
        }

        return $svd->u()->matmul(Matrix::quick($s))->matmul($svd->vT());
    }
}
