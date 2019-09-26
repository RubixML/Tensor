<?php

namespace Tensor;

use InvalidArgumentException;

class ColumnVector extends Vector
{
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
     * Compute the vector-matrix product of this vector and matrix a.
     *
     * @param \Tensor\Matrix $b
     * @return \Tensor\Matrix
     */
    public function matmul(Matrix $b) : Matrix
    {
        return $this->asColumnMatrix()->matmul($b);
    }

    /**
     * Multiply this column vector with a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function multiplyMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA * $valueB;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Divide this column vector with a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function divideMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA / $valueB;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Add this column vector to a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function addMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA + $valueB;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Subtract a matrix from this column vector.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function subtractMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA - $valueB;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Raise this column vector to the power of a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function powMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA ** $valueB;
            }

            $c[] = $temp;
        }
        
        return Matrix::quick($c);
    }
 
    /**
     * Mod this column vector with a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function modMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA % $valueB;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this column vector
     * and a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function equalMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA == $valueB ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this column vector
     * and a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function notEqualMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA != $valueB ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this column
     * vector and a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function greaterMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA > $valueB ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this column vector and a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function greaterEqualMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA >= $valueB ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this column
     * vector and a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function lessMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA < $valueB ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this column vector and a matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function lessEqualMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Vector A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $c = [];

        foreach ($b as $i => $row) {
            $valueA = $this->a[$i];

            $temp = [];

            foreach ($row as $valueB) {
                $temp[] = $valueA <= $valueB ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }
}
