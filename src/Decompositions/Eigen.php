<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\NotImplemented;

/**
 * Eigen
 *
 * The Eigendecompositon or (Spectral decomposition) is a matrix factorization resulting in a matrix of eigenvectors and a
 * corresponding array of eigenvalues.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Eigen
{
    /**
     * The computed eigenvalues.
     *
     * @var (int|float)[]
     */
    protected array $eigenvalues;

    /**
     * The eigenvectors of the eigendecomposition.
     *
     * @var \Tensor\Matrix
     */
    protected \Tensor\Matrix $eigenvectors;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix $a
     * @param bool $symmetric
     * @throws \Tensor\Exceptions\NotImplemented
     * @return self
     */
    public static function decompose(Matrix $a, bool $symmetric = false) : self
    {
        throw new NotImplemented('Use the extension for Eigen decomposition.');
    }

    /**
     * @param (int|float)[] $eigenvalues
     * @param \Tensor\Matrix $eigenvectors
     */
    public function __construct(array $eigenvalues, Matrix $eigenvectors)
    {
        $this->eigenvalues = $eigenvalues;
        $this->eigenvectors = $eigenvectors;
    }

    /**
     * Return the eigenvalues of the eigendecomposition.
     *
     * @return (int|float)[]
     */
    public function eigenvalues() : array
    {
        return $this->eigenvalues;
    }

    /**
     * Return the eigenvectors of the eigendecomposition.
     *
     * @return \Tensor\Matrix
     */
    public function eigenvectors() : Matrix
    {
        return $this->eigenvectors;
    }
}
