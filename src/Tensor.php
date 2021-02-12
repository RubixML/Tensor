<?php

namespace Tensor;

interface Tensor extends ArrayLike, Arithmetic, Comparable, Functional, Trigonometric, Statistical
{
    /**
     * Map a function over all of the elements in the tensor.
     *
     * @param callable $callback
     * @return mixed
     */
    public function map(callable $callback);

    /**
     * Reduce the tensor down to a scalar.
     *
     * @param callable $callback
     * @param mixed $initial
     * @return mixed
     */
    public function reduce(callable $callback, $initial = 0);

    /**
     * Transpose the tensor.
     *
     * @return mixed
     */
    public function transpose();

    /**
     * Clip the tensor to be between the given minimum and maximum.
     *
     * @param float $min
     * @param float $max
     * @return mixed
     */
    public function clip(float $min, float $max);

    /**
     * Clip the tensor to be lower bounded by a given minimum.
     *
     * @param float $min
     * @return mixed
     */
    public function clipLower(float $min);

    /**
     * Clip the tensor to be upper bounded by a given maximum.
     *
     * @param float $max
     * @return mixed
     */
    public function clipUpper(float $max);

    /**
     * Return the shape of the tensor as a string.
     *
     * @return string
     */
    public function shapeString() : string;

    /**
     * Convert the tensor into a string representation.
     *
     * @return string
     */
    public function __toString() : string;
}
