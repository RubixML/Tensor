<?php

namespace Tensor;

use IteratorAggregate;
use ArrayAccess;
use Countable;

/**
 * @extends ArrayAccess<int, mixed>
 * @extends IteratorAggregate<mixed>
 */
interface ArrayLike extends ArrayAccess, IteratorAggregate, Countable
{
    /**
     * Return a tuple with the dimensionality of the array-like.
     *
     * @return int[]
     */
    public function shape() : array;

    /**
     * Return the number of elements in the array-like object.
     *
     * @return int
     */
    public function size() : int;

    /**
     * Return the elements of the array-like as a PHP array.
     *
     * @return mixed[]
     */
    public function asArray() : array;
}
