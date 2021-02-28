<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\InvalidArgumentException;
use JAMA\Matrix as JAMA;

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
    protected $eigenvalues;

    /**
     * The eigenvectors of the eigendecomposition.
     *
     * @var \Tensor\Matrix
     */
    protected $eigenvectors;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix $a
     * @param bool $symmetric
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public static function decompose(Matrix $a, bool $symmetric = false) : self
    {
        if (!$a->isSquare()) {
            throw new InvalidArgumentException('Matrix must be'
                . " square, {$a->shapeString()} given.");
        }

        $jama = new JAMA($a->asArray());

        $eig = $jama->eig();

        $eigenvalues = $eig->getRealEigenvalues();
        $eigenvectors = $eig->getV()->getArray();

        $eigenvectors = Matrix::quick($eigenvectors)->transpose();

        return new self($eigenvalues, $eigenvectors);
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
