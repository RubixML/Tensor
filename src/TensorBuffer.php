<?php

namespace Tensor;

use Tensor\Exceptions\InvalidArgumentException;

use function is_float;
use function array_values;
use function count;

/**
 * TensorBuffer
 *
 * A decorator that wraps the underlying element array and provides additional
 * operations such as sorting and slicing.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class TensorBuffer
{
    /**
     * The underlying buffer being decorated.
     *
     * @var list<float>
     */
    protected array $a;

    /**
     * @param (int|float)[] $a
     */
    public function __construct(array $a = [])
    {
        if ($a) {
            $a = array_values($a);

            foreach ($a as &$valueA) {
                if (!is_float($valueA)) {
                    $valueA = (float) $valueA;
                }
            }
        }

        $this->a = $a;
    }

    /**
     * Return the buffer as a PHP array.
     *
     * @return list<float>
     */
    public function toArray() : array
    {
        return $this->a;
    }

    /**
     * Return the underlying buffer (this polyfill instance).
     *
     * @return self
     */
    public function asBuffer() : self
    {
        return $this;
    }

    /**
     * Return the number of elements in the buffer.
     *
     * @return int
     */
    public function count() : int
    {
        return count($this->a);
    }

    /**
     * Return the element at the given index.
     *
     * @param int $index
     * @throws InvalidArgumentException
     * @return float
     */
    public function get(int $index) : float
    {
        if ($index < 0 || $index >= count($this->a)) {
            throw new InvalidArgumentException(
                "Element not found at offset $index."
            );
        }

        return $this->a[$index];
    }
}
