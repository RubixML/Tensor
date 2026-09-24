<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\RuntimeException;

use const Tensor\EPSILON;

use function abs;
use function arsort;
use function array_fill;
use function array_keys;
use function array_slice;
use function count;
use function min;
use function sqrt;

/**
 * SVD
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class SVD
{
    /**
     * The U matrix.
     *
     * @var Matrix
     */
    protected Matrix $u;

    /**
     * The singular values of the matrix A.
     *
     * @var list<float>
     */
    protected array $singularValues;

    /**
     * The V transposed matrix.
     *
     * @var Matrix
     */
    protected Matrix $vT;

    /**
     * Factory method to decompose a matrix.
     *
     * @param Matrix $a
     * @throws RuntimeException
     * @return self
     */
    public static function decompose(Matrix $a) : self
    {
        $m = $a->m();

        $n = $a->n();

        if ($m < $n) {
            $svd = self::decompose($a->transpose());

            return new self(
                $svd->v(),
                $svd->singularValues(),
                $svd->u()->transpose()
            );
        }

        $k = min($m, $n);

        $w = $a->asArray();

        $v = [];

        for ($j = 0; $j < $n; ++$j) {
            $v[$j] = array_fill(0, $n, 0.0);

            $v[$j][$j] = 1.0;
        }

        $sweeps = 0;

        do {
            $converged = true;

            ++$sweeps;

            for ($p = 0; $p < $n - 1; ++$p) {
                for ($q = $p + 1; $q < $n; ++$q) {
                    $alpha = 0.0;
                    $beta = 0.0;
                    $gamma = 0.0;

                    for ($i = 0; $i < $m; ++$i) {
                        $alpha += $w[$i][$p] * $w[$i][$p];
                        $beta += $w[$i][$q] * $w[$i][$q];
                        $gamma += $w[$i][$p] * $w[$i][$q];
                    }

                    if ($gamma != 0.0 and abs($gamma) > 1e-15 * sqrt($alpha * $beta)) {
                        $zeta = ($beta - $alpha) / (2.0 * $gamma);

                        $t = $zeta >= 0.0
                            ? 1.0 / ($zeta + sqrt(1.0 + $zeta * $zeta))
                            : -1.0 / (-$zeta + sqrt(1.0 + $zeta * $zeta));

                        $c = 1.0 / sqrt(1.0 + $t * $t);

                        $s = $c * $t;

                        for ($i = 0; $i < $m; ++$i) {
                            $wip = $c * $w[$i][$p] - $s * $w[$i][$q];
                            $wiq = $s * $w[$i][$p] + $c * $w[$i][$q];

                            $w[$i][$p] = $wip;
                            $w[$i][$q] = $wiq;
                        }

                        for ($i = 0; $i < $n; ++$i) {
                            $vip = $c * $v[$i][$p] - $s * $v[$i][$q];
                            $viq = $s * $v[$i][$p] + $c * $v[$i][$q];

                            $v[$i][$p] = $vip;
                            $v[$i][$q] = $viq;
                        }

                        $converged = false;
                    }
                }
            }
        } while (!$converged and $sweeps < 100);

        if (!$converged) {
            throw new RuntimeException('Failed to decompose matrix.');
        }

        $sigma = [];
        $u = [];

        for ($j = 0; $j < $n; ++$j) {
            $norm = 0.0;

            for ($i = 0; $i < $m; ++$i) {
                $norm += $w[$i][$j] * $w[$i][$j];
            }

            $sigma[$j] = sqrt($norm);

            if ($sigma[$j] > 0.0) {
                $column = [];

                for ($i = 0; $i < $m; ++$i) {
                    $column[] = $w[$i][$j] / $sigma[$j];
                }

                $u[$j] = $column;
            } else {
                $u[$j] = null;
            }
        }

        arsort($sigma, SORT_NUMERIC);

        $singularValues = [];
        $uColumns = [];
        $vT = [];

        foreach (array_keys($sigma) as $j) {
            $singularValues[] = $sigma[$j];

            $uColumns[] = $u[$j];

            $rowVt = [];

            for ($i = 0; $i < $n; ++$i) {
                $rowVt[] = $v[$i][$j];
            }

            $vT[] = $rowVt;
        }

        $u = [];
        $basis = [];

        for ($j = 0; $j < $k; ++$j) {
            $column = $uColumns[$j];

            if ($column !== null) {
                $u[] = $column;

                $basis[] = $column;
            }
        }

        if (count($u) < $m) {
            $candidate = 0;

            while (count($u) < $m and $candidate < $m) {
                $vec = array_fill(0, $m, 0.0);

                $vec[$candidate] = 1.0;

                foreach ($basis as $column) {
                    $projection = 0.0;

                    for ($i = 0; $i < $m; ++$i) {
                        $projection += $vec[$i] * $column[$i];
                    }

                    for ($i = 0; $i < $m; ++$i) {
                        $vec[$i] -= $projection * $column[$i];
                    }
                }

                $norm = 0.0;

                for ($i = 0; $i < $m; ++$i) {
                    $norm += $vec[$i] * $vec[$i];
                }

                $norm = sqrt($norm);

                if ($norm > EPSILON) {
                    for ($i = 0; $i < $m; ++$i) {
                        $vec[$i] /= $norm;
                    }

                    $u[] = $vec;

                    $basis[] = $vec;
                }

                ++$candidate;
            }
        }

        $uMatrix = [];

        for ($i = 0; $i < $m; ++$i) {
            $rowU = [];

            foreach ($u as $column) {
                $rowU[] = $column[$i];
            }

            $uMatrix[] = $rowU;
        }

        return new self(
            Matrix::fromArray($uMatrix, false),
            array_slice($singularValues, 0, $k),
            Matrix::fromArray($vT, false)
        );
    }

    /**
     * @param Matrix $u
     * @param list<int|float> $singularValues
     * @param Matrix $vT
     */
    public function __construct(Matrix $u, array $singularValues, Matrix $vT)
    {
        $this->u = $u;
        $this->singularValues = $singularValues;
        $this->vT = $vT;
    }

    /**
     * Return the U matrix.
     *
     * @return Matrix
     */
    public function u() : Matrix
    {
        return $this->u;
    }

    /**
     * Return the singular values of matrix A.
     *
     * @return list<float>
     */
    public function singularValues() : array
    {
        return $this->singularValues;
    }

    /**
     * Return the singular value matrix — an m by n matrix with the singular
     * values on the diagonal, zero-padded so that multiplying it by the U and
     * vT matrices reconstructs the original matrix.
     *
     * @return Matrix
     */
    public function s() : Matrix
    {
        $m = $this->u->m();

        $n = $this->vT->n();

        $s = Matrix::zeros($m, $n)->asArray();

        foreach ($this->singularValues as $i => $value) {
            $s[$i][$i] = $value;
        }

        return Matrix::fromArray($s, false);
    }

    /**
     * Return the V matrix.
     *
     * @return Matrix
     */
    public function v() : Matrix
    {
        return $this->vT->transpose();
    }

    /**
     * Return the V transposed matrix.
     *
     * @return Matrix
     */
    public function vT() : Matrix
    {
        return $this->vT;
    }
}
