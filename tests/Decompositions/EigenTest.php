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

        $general = Eigen::decompose($a);
        $symmetric = Eigen::decompose($a, true);

        $generalEigenvalues = $general->eigenvalues();
        $symmetricEigenvalues = $symmetric->eigenvalues();

        sort($generalEigenvalues);
        sort($symmetricEigenvalues);

        $this->assertEqualsWithDelta($generalEigenvalues, $symmetricEigenvalues, self::MAX_DELTA);
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
     * A complex matrix with a pair of purely imaginary eigenvalues.
     *
     * @test
     */
    public function decomposeComplexPair() : void
    {
        $a = Matrix::quick([
            [0.0, -1.0],
            [1.0, 0.0],
        ]);

        $eig = Eigen::decompose($a);

        $eigenvalues = $eig->eigenvalues();

        $this->assertCount(2, $eigenvalues);

        $this->assertEqualsWithDelta([0.0, 0.0], $eigenvalues, self::MAX_DELTA);

        $eigenvectors = $eig->eigenvectors()->asArray();

        foreach ($eigenvectors as $row) {
            $norm = 0.0;

            foreach ($row as $value) {
                $norm += $value ** 2;
            }

            $this->assertGreaterThan(0.0, $norm);
        }

        $aa = $a->asArray();

        $alpha = ($aa[0][0] + $aa[1][1]) / 2.0;

        $beta = sqrt(abs($aa[0][0] * $aa[1][1] - $aa[0][1] * $aa[1][0] - $alpha ** 2));

        $residuals = [
            $this->conjugatePairResidual($aa, $eigenvectors[0], $eigenvectors[1], $alpha, $beta, 1),
            $this->conjugatePairResidual($aa, $eigenvectors[1], $eigenvectors[0], $alpha, $beta, 1),
        ];

        $this->assertLessThanOrEqual(self::MAX_DELTA, min($residuals));
    }

    /**
     * A matrix with a conjugate pair and a distinct real eigenvalue.
     *
     * @test
     */
    public function decomposeComplexPairWithReal() : void
    {
        $a = Matrix::quick([
            [0.0, -1.0, 0.0],
            [1.0, 0.0, 0.0],
            [0.0, 0.0, 2.0],
        ]);

        $eig = Eigen::decompose($a);

        $originalEigenvalues = $eig->eigenvalues();

        $eigenvalues = $originalEigenvalues;

        sort($eigenvalues);

        $this->assertEqualsWithDelta([0.0, 0.0, 2.0], $eigenvalues, self::MAX_DELTA);

        $eigenvectors = $eig->eigenvectors()->asArray();

        $pair = [];

        for ($j = 0; $j < $a->n(); ++$j) {
            if (abs($originalEigenvalues[$j] - 2.0) < self::MAX_DELTA) {
                $this->assertEigenpair($a, $eigenvectors[$j], $originalEigenvalues[$j]);
            } else {
                $pair[] = $eigenvectors[$j];
            }
        }

        $this->assertCount(2, $pair);

        foreach ($pair as $row) {
            $norm = 0.0;

            foreach ($row as $value) {
                $norm += $value ** 2;
            }

            $this->assertGreaterThan(0.0, $norm);
        }

        $aa = $a->asArray();

        $residuals = [
            $this->conjugatePairResidual($aa, $pair[0], $pair[1], 0.0, 1.0, 1),
            $this->conjugatePairResidual($aa, $pair[1], $pair[0], 0.0, 1.0, 1),
        ];

        $this->assertLessThanOrEqual(self::MAX_DELTA, min($residuals));
    }

    /**
     * Assert that each eigenpair satisfies A * v = lambda * v.
     *
     * @param Matrix $a
     * @param Eigen $eig
     */
    protected function assertEigenpairIdentity(Matrix $a, Eigen $eig) : void
    {
        $eigenvalues = $eig->eigenvalues();

        $eigenvectors = $eig->eigenvectors()->asArray();

        $n = $a->n();

        $this->assertCount($n, $eigenvalues);

        for ($j = 0; $j < $n; ++$j) {
            $this->assertEigenpair($a, $eigenvectors[$j], $eigenvalues[$j]);
        }
    }

    /**
     * Assert that a single eigenpair satisfies A * v = lambda * v.
     *
     * @param Matrix $a
     * @param list<float> $eigenvector
     * @param float $eigenvalue
     */
    protected function assertEigenpair(Matrix $a, array $eigenvector, float $eigenvalue) : void
    {
        $aa = $a->asArray();

        $n = $a->n();

        for ($i = 0; $i < $n; ++$i) {
            $sum = 0.0;

            for ($k = 0; $k < $n; ++$k) {
                $sum += $aa[$i][$k] * $eigenvector[$k];
            }

            $this->assertEqualsWithDelta($eigenvalue * $eigenvector[$i], $sum, self::MAX_DELTA);
        }
    }

    /**
     * The residual of a complex conjugate eigenpair alpha +- i * beta with
     * real part u and imaginary part w: the maximum of |A u - (alpha u -
     * sign * beta w)| and |A w - (sign * beta u + alpha w)|.
     *
     * @param list<list<float>> $a
     * @param list<float> $u
     * @param list<float> $w
     * @param float $alpha
     * @param float $beta
     * @param int $sign
     * @return float
     */
    protected function conjugatePairResidual(array $a, array $u, array $w, float $alpha, float $beta, int $sign) : float
    {
        $residual = 0.0;

        for ($i = 0, $n = count($u); $i < $n; ++$i) {
            $au = 0.0;
            $aw = 0.0;

            for ($k = 0; $k < $n; ++$k) {
                $au += $a[$i][$k] * $u[$k];
                $aw += $a[$i][$k] * $w[$k];
            }

            $residual = max($residual, abs($au - ($alpha * $u[$i] - $sign * $beta * $w[$i])));
            $residual = max($residual, abs($aw - ($sign * $beta * $u[$i] + $alpha * $w[$i])));
        }

        return $residual;
    }
}
