<?php

namespace Tensor\Tests\Decompositions;

use Tensor\Matrix;
use Tensor\Decompositions\Eigen;
use Tensor\Exceptions\InvalidArgumentException;
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
    public function decomposeGeneral3x3() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $eig = Eigen::decompose($a);

        $this->assertEigenpairIdentity($a, $eig);

        $expectedEigenvalues = [
            -15.09633114832,
            13.987624627869,
            25.10870652045,
        ];

        $eigenvalues = $eig->eigenvalues();

        sort($eigenvalues);

        $this->assertEqualsWithDelta($expectedEigenvalues, $eigenvalues, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeSymmetric3x3() : void
    {
        $a = Matrix::quick([
            [3.0, -1.0, 0.0],
            [-1.0, 2.0, -1.0],
            [0.0, -1.0, 3.0],
        ]);

        $eig = Eigen::decompose($a, true);

        $this->assertEigenpairIdentity($a, $eig);

        $expectedEigenvalues = [1.0, 3.0, 4.0];

        $this->assertEqualsWithDelta($expectedEigenvalues, $eig->eigenvalues(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeSymmetric2x2() : void
    {
        $a = Matrix::quick([
            [9.0, 3.0],
            [3.0, 5.0],
        ]);

        $eig = Eigen::decompose($a, true);

        $this->assertEigenpairIdentity($a, $eig);

        $this->assertEqualsWithDelta([3.3944487241610, 10.605551275464], $eig->eigenvalues(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeGeneralAndSymmetricAgree() : void
    {
        $a = Matrix::quick([
            [3.0, -1.0, 0.0],
            [-1.0, 2.0, -1.0],
            [0.0, -1.0, 3.0],
        ]);

        $general = $eig = Eigen::decompose($a);

        $symmetric = Eigen::decompose($a, true);

        $this->assertEqualsWithDelta($general->eigenvalues(), $symmetric->eigenvalues(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decompose1x1() : void
    {
        $a = Matrix::quick([[9.0]]);

        $eig = Eigen::decompose($a);

        $this->assertEigenpairIdentity($a, $eig);

        $this->assertEquals([9.0], $eig->eigenvalues());

        $this->assertEqualsWithDelta(Matrix::quick([[1.0]]), $eig->eigenvectors(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeDiagonal() : void
    {
        $a = Matrix::quick([
            [2.0, 0.0, 0.0],
            [0.0, 3.0, 0.0],
            [0.0, 0.0, 5.0],
        ]);

        $eig = Eigen::decompose($a);

        $this->assertEigenpairIdentity($a, $eig);

        $this->assertEqualsWithDelta([2.0, 3.0, 5.0], $eig->eigenvalues(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function decomposeNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Eigen::decompose(Matrix::quick([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ]));
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

    /**
     * Assert that each eigenpair satisfies A * v = lambda * v.
     *
     * @param Matrix $a
     * @param Eigen $eig
     */
    protected function assertEigenpairIdentity(Matrix $a, Eigen $eig) : void
    {
        $aa = $a->asArray();

        $eigenvalues = $eig->eigenvalues();

        $eigenvectors = $eig->eigenvectors()->asArray();

        $n = $a->n();

        $this->assertCount($n, $eigenvalues);

        for ($j = 0; $j < $n; ++$j) {
            for ($i = 0; $i < $n; ++$i) {
                $sum = 0.0;

                for ($k = 0; $k < $n; ++$k) {
                    $sum += $aa[$i][$k] * $eigenvectors[$j][$k];
                }

                $this->assertEqualsWithDelta(
                    $eigenvalues[$j] * $eigenvectors[$j][$i],
                    $sum,
                    self::MAX_DELTA
                );
            }
        }
    }
}
