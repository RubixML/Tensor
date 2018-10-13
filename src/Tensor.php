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
