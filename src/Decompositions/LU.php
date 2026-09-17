<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;

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
class LU
{
    /**
     * The lower triangular matrix.
     *
     * @var Matrix
     */
    protected Matrix $l;

    /**
     * The upper triangular matrix.
     *
     * @var Matrix
     */
    protected Matrix $u;

    /**
     * The permutation matrix.
     *
     * @var Matrix
     */
    protected Matrix $p;

    /**
     * Factory method to decompose a matrix.
     *
     * @param Matrix $a
     * @throws InvalidArgumentException
     * @throws RuntimeException
     * @return self
     */
    public static function decompose(Matrix $a) : self
    {
        if (!$a->isSquare()) {
            throw new InvalidArgumentException('Matrix must be'
                . " square, {$a->shapeString()} given.");
        }

        $n = $a->n();

        $w = $a->asArray();

        $p = [];

        for ($i = 0; $i < $n; ++$i) {
            $p[$i] = array_fill(0, $n, 0.0);

            $p[$i][$i] = 1.0;
        }

        for ($i = 0; $i < $n; ++$i) {
            $row = $i;

            for ($j = $i + 1; $j < $n; ++$j) {
                if (abs($w[$j][$i]) > abs($w[$row][$i])) {
                    $row = $j;
                }
            }

            if ($w[$row][$i] == 0.) {
                throw new RuntimeException('Cannot compute LU decomposition'
                    . ' of a singular matrix.');
            }

            if ($i !== $row) {
                $temp = $w[$i];

                $w[$i] = $w[$row];
                $w[$row] = $temp;

                $temp = $p[$i];

                $p[$i] = $p[$row];
                $p[$row] = $temp;
            }

            for ($j = $i + 1; $j < $n; ++$j) {
                $w[$j][$i] /= $w[$i][$i];

                for ($k = $i + 1; $k < $n; ++$k) {
                    $w[$j][$k] -= $w[$j][$i] * $w[$i][$k];
                }
            }
        }

        $l = [];
        $u = [];

        for ($i = 0; $i < $n; ++$i) {
            for ($j = 0; $j < $n; ++$j) {
                if ($i > $j) {
                    $l[$i][$j] = $w[$i][$j];

                    $u[$i][$j] = 0.0;
                } elseif ($i === $j) {
                    $l[$i][$j] = 1.0;

                    $u[$i][$j] = $w[$i][$i];
                } else {
                    $l[$i][$j] = 0.0;

                    $u[$i][$j] = $w[$i][$j];
                }
            }
        }

        return new self(
            Matrix::quick($l),
            Matrix::quick($u),
            Matrix::quick($p)
        );
    }

    /**
     * @param Matrix $l
     * @param Matrix $u
     * @param Matrix $p
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
     * @return Matrix
     */
    public function l() : Matrix
    {
        return $this->l;
    }

    /**
     * Return the upper triangular matrix.
     *
     * @return Matrix
     */
    public function u() : Matrix
    {
        return $this->u;
    }

    /**
     * Return the permutation matrix.
     *
     * @return Matrix
     */
    public function p() : Matrix
    {
        return $this->p;
    }
}
