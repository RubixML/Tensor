<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\NotImplemented;

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
     * @var \Tensor\Matrix
     */
    protected $u;

    /**
     * The singular values of the matrix A.
     *
     * @var list<float>
     */
    protected $singularValues;

    /**
     * The V transposed matrix.
     *
     * @var \Tensor\Matrix
     */
    protected $vT;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix $a
     * @return self
     */
    public static function decompose(Matrix $a) : self
    {
        throw new NotImplemented('SVD is not implemented in Tensor PHP.');
    }

    /**
     * @param \Tensor\Matrix $u
     * @param list<int|float> $singularValues
     * @param \Tensor\Matrix $vT
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
     * @return \Tensor\Matrix
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
     * Return the singular value matrix.
     *
     * @return \Tensor\Matrix
     */
    public function s() : Matrix
    {
        return Matrix::diagonal($this->singularValues);
    }

    /**
     * Return the V matrix.
     *
     * @return \Tensor\Matrix
     */
    public function v() : Matrix
    {
        return $this->vT->transpose();
    }

    /**
     * Return the V transposed matrix.
     *
     * @return \Tensor\Matrix
     */
    public function vT() : Matrix
    {
        return $this->vT;
    }
}
