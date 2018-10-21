<?php

namespace Rubix\Tensor;

use Rubix\Tensor\Exceptions\DimensionalityMismatchException;

class ColumnVector extends Vector
{
    /**
     * Return a tuple with the dimensionality of the tensor.
     *
     * @return int[]
     */
    public function shape() : array
    {
        return [$this->n, 1];
    }

    /**
     * Return the number of rows in the vector.
     *
     * @return int
     */
    public function m() : int
    {
        return $this->n;
    }

    /**
     * Return the number of columns in the vector.
     *
     * @return int
     */
    public function n() : int
    {
        return 1;
    }

    /**
     * Transpose the vector i.e. rotate it.
     * 
     * @return mixed
     */
    public function transpose()
    {
        return Vector::quick($this->a);
    }

    /**
     * Multiply this column vector with a matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function multiplyMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Vector A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            foreach ($row as $value) {
                $c[$i][] = $this->a[$i] * $value;
            }
        }

        return Matrix::quick($c);
    }

    /**
     * Divide this column vector with a matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function divideMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Vector A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            foreach ($row as $value) {
                $c[$i][] = $this->a[$i] / $value;
            }
        }

        return Matrix::quick($c);
    }

    /**
     * Add this column vector to a matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function addMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Vector A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            foreach ($row as $value) {
                $c[$i][] = $this->a[$i] + $value;
            }
        }

        return Matrix::quick($c);
    }

    
    /**
     * Subtract a matrix from this column vector.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function subtractMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Vector A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            foreach ($row as $value) {
                $c[$i][] = $this->a[$i] - $value;
            }
        }

        return Matrix::quick($c);
    }

    
    /**
     * Raise this column vector to the power of a matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function powMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Vector A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            foreach ($row as $value) {
                $c[$i][] = $this->a[$i] ** $value;
            }
        }

        return Matrix::quick($c);
    }
 
    /**
     * Mod this column vector with a matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function modMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Vector A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            foreach ($row as $value) {
                $c[$i][] = $this->a[$i] % $value;
            }
        }

        return Matrix::quick($c);
    }
}