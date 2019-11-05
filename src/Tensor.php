<?php

namespace Tensor;

interface Tensor extends ArrayLike
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
     * A universal function to multiply this tensor with another tensor
     * element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function multiply($b);

    /**
     * A universal function to divide this tensor by another tensor
     * element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function divide($b);

    /**
     * A universal function to add this tensor with another tensor
     * element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function add($b);

    /**
     * A universal function to subtract this tensor from another tensor
     * element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function subtract($b);

    /**
     * A universal function to raise this tensor to the power of another
     * tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function pow($b);

    /**
     * A universal function to compute the integer modulus of this tensor
     * and another tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function mod($b);

    /**
    * A universal function to compute the equality comparison of a tensor
    * and another tensor element-wise.
    *
    * @param  mixed  $b
    * @return mixed
    */
    public function equal($b);

    /**
     * A universal function to compute the not equal comparison of
     * this tensor and another tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function notEqual($b);

    /**
     * A universal function to compute the greater than comparison of a
     * tensor and another tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function greater($b);

    /**
     * A universal function to compute the greater than or equal to
     * comparison of a tensor and another tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function greaterEqual($b);

    /**
     * A universal function to compute the less than comparison of a
     * tensor and another tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function less($b);

    /**
     * A universal function to compute the less than or equal to
     * comparison of a tensor and another tensor element-wise.
     *
     * @param mixed $b
     * @return mixed
     */
    public function lessEqual($b);

    /**
     * Take the absolute value of the tensor.
     *
     * @return mixed
     */
    public function abs();

    /**
     * Square the tensor.
     *
     * @return mixed
     */
    public function square();

    /**
     * Return the square root of the tensor.
     *
     * @return mixed
     */
    public function sqrt();

    /**
     * Return the exponential of the tensor.
     *
     * @return mixed
     */
    public function exp();

    /**
     * Return the logarithm of the tensor in a specified base.
     *
     * @param float $base
     * @return mixed
     */
    public function log(float $base = M_E);

    /**
     * Sum the tensor.
     *
     * @return mixed
     */
    public function sum();

    /**
     * Calculate the product of the tensor.
     *
     * @return mixed
     */
    public function product();

    /**
     * Return the minimum of the tensor.
     *
     * @return mixed
     */
    public function min();

    /**
     * Return the maximum of the tensor.
     *
     * @return mixed
     */
    public function max();

    /**
     * Round the elements in the tensor to a given decimal place.
     *
     * @param int $precision
     * @return self
     */
    public function round(int $precision = 0);

    /**
     * Round the tensor down to the nearest integer.
     *
     * @return mixed
     */
    public function floor();

    /**
     * Round the tensor up to the nearest integer.
     *
     * @return mixed
     */
    public function ceil();

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
     * Return the element-wise sign indication.
     *
     * @return mixed
     */
    public function sign();

    /**
     * Negate the tensor i.e take the negative.
     *
     * @return mixed
     */
    public function negate();

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
