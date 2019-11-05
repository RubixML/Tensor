<?php

namespace Tensor;

interface Arithmetic
{
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
     * Return the exponential of the tensor minus 1.
     *
     * @return mixed
     */
    public function expm1();

    /**
     * Return the logarithm of the tensor in a specified base.
     *
     * @param float $base
     * @return mixed
     */
    public function log(float $base = M_E);

    /**
     * Return the log of 1 plus the tensor i.e. a transform.
     *
     * @return mixed
     */
    public function log1p();

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
}
