<?php

namespace Tensor\Reductions;

use Tensor\Matrix;

/**
 * RREF
 *
 * The reduced row echelon form (RREF) of a matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class RREF
{
    /**
     * The reduced matrix in reduced row echelon form.
     *
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * Factory method to reduce a matrix.
     *
     * @param \Tensor\Matrix $a
     * @return self
     */
    public static function reduce(Matrix $a) : self
    {
        $ref = $a->ref();

        $b = $ref->a();

        [$m, $n] = $b->shape();

        $b = $b->asArray();

        $row = $col = 0;

        while ($row < $m and $col < $n) {
            $t = $b[$row];

            if (abs($t[$col]) == 0) {
                ++$col;

                continue 1;
            }

            $divisor = $t[$col];

            if ($divisor != 1) {
                for ($i = 0; $i < $n; ++$i) {
                    $t[$i] /= $divisor;
                }
            }

            for ($i = $row - 1; $i >= 0; --$i) {
                $scale = $b[$i][$col];

                if ($scale != 0) {
                    for ($j = 0; $j < $n; ++$j) {
                        $b[$i][$j] -= $scale * $t[$j];
                    }
                }
            }

            $b[$row] = $t;

            ++$row;
            ++$col;
        }

        return new self(Matrix::quick($b));
    }

    /**
     * @param \Tensor\Matrix $a
     * @throws \InvalidArgumentException
     */
    public function __construct(Matrix $a)
    {
        $this->a = $a;
    }

    /**
     * Return the reduced matrix in reduced row echelon form.
     *
     * @return \Tensor\Matrix
     */
    public function a() : Matrix
    {
        return $this->a;
    }
}
