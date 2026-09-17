<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\Eigen;
use Tensor\Exceptions\NotImplemented;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Decompositions\Eigen
 */
class EigenTest extends TestCase
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

        Eigen::decompose($a);
    }

    /**
     * @test
     */
    public function decomposeWithSymmetricFlagThrowsNotImplemented() : void
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

        Eigen::decompose($a, true);
    }

    /**
     * @test
     */
    public function constructAndAccess() : void
    {
        $eigenvalues = [1.0, 2.0, 3.0];

        $eigenvectors = Matrix::quick([
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0],
        ]);

        $eig = new Eigen($eigenvalues, $eigenvectors);

        $this->assertEquals($eigenvalues, $eig->eigenvalues());
        $this->assertEqualsWithDelta($eigenvectors, $eig->eigenvectors(), self::MAX_DELTA);
    }
}
