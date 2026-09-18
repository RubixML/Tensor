<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;

use const Tensor\EPSILON;

/**
 * Cholesky
 *
 * An efficient decomposition of a square positive definite matrix into a
 * lower triangular matrix and its conjugate transpose.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Cholesky
{
    /**
     * The lower triangular matrix.
     *
     * @var Matrix
     */
    protected Matrix $l;

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

        $m = $a->m();

        $a = $a->asArray();

        $l = Matrix::zeros($m, $m)->asArray();

        for ($i = 0; $i < $m; ++$i) {
            for ($j = 0; $j < $i + 1; ++$j) {
                $sigma = 0;

                for ($k = 0; $k < $j; ++$k) {
                    $sigma += $l[$i][$k] * $l[$j][$k];
                }

                if ($i === $j) {
                    $delta = $a[$i][$i] - $sigma;

                    if ($delta <= EPSILON) {
                        throw new RuntimeException('Cannot compute Cholesky decomposition'
                            . ' of a non-positive definite matrix.');
                    }

                    $l[$i][$j] = sqrt($delta);
                } else {
                    $l[$i][$j] = 1 / $l[$j][$j] * ($a[$i][$j] - $sigma);
                }
            }
        }

        $l = Matrix::quick($l);

        return new self($l);
    }

    /**
     * @param Matrix $l
     */
    public function __construct(Matrix $l)
    {
        $this->l = $l;
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
     * Return the transpose of the lower triangular matrix.
     *
     * @return Matrix
     */
    public function lT() : Matrix
    {
        return $this->l->transpose();
    }
}
