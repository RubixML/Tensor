<?php

namespace Rubix\Tensor;

use IteratorAggregate;
use ArrayAccess;
use Countable;

interface Tensor extends ArrayAccess, IteratorAggregate, Countable
{
    const TWO_PI = 2. * M_PI;

    const EPSILON = 1e-8;

    /**
     * Return a tuple with the dimensionality of the tensor.
     *
     * @return int[]
     */
    public function shape() : array;

    /**
     * Return the number of elements in the tensor.
     *
     * @return int
     */
    public function size() : int;

    /**
     * Map a function over all of the elements in the tensor.
     *
     * @param  callable  $fn
     * @return mixed
     */
    public function map(callable $fn);

    /**
     * Reduce the tensor down to a scalar.
     *
     * @param  callable  $fn
     * @param  float  $initial
     * @return float
     */
    public function reduce(callable $fn, float $initial = 0.) : float;

    /**
     * A universal function to multiply this tensor with another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function multiply($b);

    /**
     * A universal function to divide this tensor by another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide($b);

    /**
     * A universal function to add this tensor with another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add($b);

    /**
     * A universal function to subtract this tensor from another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract($b);

    /**
     * A universal function to raise this tensor to the power of another
     * tensor element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow($b);

    /**
     * A universal function to compute the modulus of this tensor and
     * another tensor element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod($b);

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
     * @param  float  $base
     * @return mixed
     */
    public function log(float $base = M_E);

    /**
     * Return the sine of the tensor.
     *
     * @return mixed
     */
    public function sin();

    /**
     * Return the cosine of the tensor.
     *
     * @return mixed
     */
    public function cos();

    /**
     * Return the tangent of the tensor.
     *
     * @return mixed
     */
    public function tan();

    /**
     * Convert angles from radians to degrees.
     *
     * @return mixed
     */
    public function degrees();

    /**
     * Convert angles from degrees to radians.
     *
     * @return mixed
     */
    public function radians();

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
     * @param  int  $precision
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
     * @param  float  $min
     * @param  float  $max
     * @return mixed
     */
    public function clip(float $min, float $max);

    /**
     * Negate the tensor i.e take the negative.
     *
     * @return mixed
     */
    public function negate();

    /**
     * Return the elements of the tensor in an array.
     *
     * @return array
     */
    public function asArray() : array;

    /**
     * Convert the tensor into a string representation.
     *
     * @return string
     */
    public function __toString() : string;
}
