<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\SVD;
use Tensor\Exceptions\NotImplemented;
use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(SVD::class)]
class SVDTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    #[\PHPUnit\Framework\Attributes\Test]
    public function decomposeThrowsNotImplemented() : void
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Extension tensor is loaded.');
        }

        $this->expectException(NotImplemented::class);

        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        SVD::decompose($a);
    }

    #[\PHPUnit\Framework\Attributes\Test]
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
}
