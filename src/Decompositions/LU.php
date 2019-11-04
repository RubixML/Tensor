<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use RuntimeException;

use const Tensor\EPSILON;

/**
 * LU
 *
 * The LU decomposition is a factorization of a Matrix as the product of a
 * lower and upper triangular matrix as well as a permutation matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class LU implements Decomposition
{
    /**
     * The lower triangular matrix.
     *
     * @var \Tensor\Matrix
     */
    protected $l;

    /**
     * The upper triangular matrix.
     *
     * @var \Tensor\Matrix
     */
    protected $u;

    /**
     * The permutation matrix.
     *
     * @var \Tensor\Matrix
     */
    protected $p;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix $a
     * @return self
     */
    public static function decompose(Matrix $a) : self
    {
        if (!$a->isSquare()) {
            throw new RuntimeException('Cannot decompose a non square matrix.');
        }

        $n = $a->n();

        $l = Matrix::identity($n)->asArray();
        $u = Matrix::zeros($n, $n)->asArray();
        $p = Matrix::identity($n)->asArray();

        for ($i = 0; $i < $n; ++$i) {
            $max = $a[$i][$i];

            $row = $i;

            for ($j = $i; $j < $n; ++$j) {
                if ($a[$j][$i] > $max) {
                    $max = $a[$j][$i];
                    
                    $row = $j;
                }
            }
            
            if ($i !== $row) {
                $temp = $p[$i];

                $p[$i] = $p[$row];
                $p[$row] = $temp;
            }
        }

        $p = Matrix::quick($p);

        $pa = $p->matmul($a);

        for ($i = 0; $i < $n; ++$i) {
            for ($j = 0; $j <= $i; ++$j) {
                $sigma = 0;

                for ($k = 0; $k < $j; ++$k) {
                    $sigma += $u[$k][$i] * $l[$j][$k];
                }

                $u[$j][$i] = $pa[$j][$i] - $sigma;
            }

            for ($j = $i; $j < $n; ++$j) {
                $sigma = 0;

                for ($k = 0; $k < $i; ++$k) {
                    $sigma += $u[$k][$i] * $l[$j][$k];
                }

                $l[$j][$i] = ($pa[$j][$i] - $sigma)
                    / ($u[$i][$i] ?: EPSILON);
            }
        }

        $l = Matrix::quick($l);
        $u = Matrix::quick($u);

        return new self($l, $u, $p);
    }

    /**
     * @param \Tensor\Matrix $l
     * @param \Tensor\Matrix $u
     * @param \Tensor\Matrix $p
     */
    public function __construct(Matrix $l, Matrix $u, Matrix $p)
    {
        $this->l = $l;
        $this->u = $u;
        $this->p = $p;
    }

    /**
     * Return the lower triangular matrix.
     *
     * @return \Tensor\Matrix
     */
    public function l() : Matrix
    {
        return $this->l;
    }

    /**
     * Return the upper triangular matrix.
     *
     * @return \Tensor\Matrix
     */
    public function u() : Matrix
    {
        return $this->u;
    }

    /**
     * Return the permutation matrix.
     *
     * @return \Tensor\Matrix
     */
    public function p() : Matrix
    {
        return $this->p;
    }
}
