<?php

namespace Rubix\Tensor;

use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;

/**
 * Matrix
 *
 * Two dimensional tensor with integer and/or floating point elements.
 *
 * @category    Linear Algebra
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Matrix implements Tensor
{
    /**
     * The 2-dimensional array that holds the values of the matrix.
     *
     * @var array
     */
    protected $a = [
        //
    ];

    /**
     * The number of rows in the matrix.
     *
     * @var int
     */
    protected $m;

    /**
     * The number of columns in the matrix.
     *
     * @var int
     */
    protected $n;

    /**
     * Factory method to build a new matrix from an array.
     *
     * @param  array[]  $a
     * @return self
     */
    public static function build(array $a = []) : self
    {
        return new self($a, true);
    }

    /**
     * Build a new matrix foregoing any validation for quicker instantiation.
     *
     * @param  array[]  $a
     * @return self
     */
    public static function quick(array $a = []) : self
    {
        return new self($a, false);
    }

    /**
     * Return an identity matrix with the given dimensions.
     *
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function identity(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 along both axis.');
        }

        $a = [[]];

        for ($i = 0; $i < $n; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][$j] = $i === $j ? 1 : 0;
            }
        }

        return new self($a, false);
    }

    /**
     * Return a zero matrix with the given dimensions.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function zeros(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 along both axis.');
        }

        return new self(array_fill(0, $m, array_fill(0, $n, 0)), false);
    }

    /**
     * Return a one matrix with the given dimensions.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function ones(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 along both axis.');
        }

        return new self(array_fill(0, $m, array_fill(0, $n, 1)), false);
    }

    /**
     * Build a diagonal matrix with the value of each element along the
     * diagonal and 0s everywhere else.
     *
     * @param  array  $elements
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function diagonal(array $elements) : self
    {
        $n = count($elements);

        if ($n === 0) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 along both axis.');
        }

        $a = [[]];

        for ($i = 0; $i < $n; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][$j] = ($i === $j) ? $elements[$i] : 0;
            }
        }

        return new self($a, false);
    }

    /**
     * Fill a matrix with a given value at each element.
     *
     * @param  int|float  $value
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill($value, int $m, int $n) : self
    {
        if (!is_int($value) and !is_float($value)) {
            throw new InvalidArgumentException('Fill value must be an integer'
                . ' or float, ' . gettype($value) . ' found.');
        }

        return new self(array_fill(0, $m, array_fill(0, $n, $value)), false);
    }

    /**
     * Return a random uniform matrix with values between 0 and 1.
     *
     * @param  int  $m
     * @param  int  $n
     * @return self
     */
    public static function rand(int $m, int $n) : self
    {
        $a = [[]];

        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][$j] = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            }
        }

        return new self($a, false);
    }

    /**
     * Return a standard normally distributed random matrix i.e values between
     * -1 and 1.
     *
     * @param  int  $m
     * @param  int  $n
     * @return self
     */
    public static function gaussian(int $m, int $n) : self
    {
        $a = [[]];

        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
                $r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;

                $a[$i][$j] = sqrt(-2. * log($r1)) * cos(self::TWO_PI * $r2);
            }
        }

        return new self($a, false);
    }

    /**
     * Return a uniform random matrix with mean 0 and unit variance.
     *
     * @param  int  $m
     * @param  int  $n
     * @return self
     */
    public static function uniform(int $m, int $n) : self
    {
        $a = [[]];

        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][$j] = rand(-PHP_INT_MAX, PHP_INT_MAX) / PHP_INT_MAX;
            }
        }

        return new self($a, false);
    }

    /**
     * Return the elementwise maximum of two matrices.
     *
     * @param  \Rubix\Tensor\Matrix  $a
     * @param  \Rubix\Tensor\Matrix  $b
     * @return self
     */
    public static function maximum(Matrix $a, Matrix $b) : self
    {
        if ($a->m() !== $b->m()) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $a->m() . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($a->n() !== $b->n()) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $a->n() . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($a as $i => $row) {
            $c[] = array_map('max', $row, $b[$i]);
        }

        return new self($c, false);
    }

    /**
     * Return the elementwise minimum of two matrices.
     *
     * @param  \Rubix\Tensor\Matrix  $a
     * @param  \Rubix\Tensor\Matrix  $b
     * @return self
     */
    public static function minimum(Matrix $a, Matrix $b) : self
    {
        if ($a->m() !== $b->m()) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $a->m() . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($a->n() !== $b->n()) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $a->n() . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($a as $i => $row) {
            $c[] = array_map('min', $row, $b[$i]);
        }

        return new self($c, false);
    }

    /**
     * @param  array[]  $a
     * @param  bool  $validate
     * @throws \InvalidArgumentException
     * @return void
     */
    public function __construct(array $a = [], bool $validate = true)
    {
        $m = count($a);

        $n = is_array(current($a)) ? count(current($a)) : 1;
        $n = $m === 0 ? 0 : $n;

        if ($validate === true) {
            $a = array_values($a);

            foreach ($a as &$row) {
                if (is_array($row)) {
                    $row = array_values($row);
                } else {
                    $row = [$row];
                }

                if (count($row) !== $n) {
                    throw new InvalidArgumentException('The number of columns'
                        . ' must be equal for all rows.');
                }

                foreach ($row as $value) {
                    if (!is_int($value) and !is_float($value)) {
                        throw new InvalidArgumentException('Matrix element must'
                            . ' be an integer or float, '
                            . gettype($value) . ' found.');
                    }
                }
            }
        }

        $this->a = $a;
        $this->m = $m;
        $this->n = $n;
    }

    /**
     * Return a tuple with the dimensionality of the tensor.
     *
     * @return int[]
     */
    public function shape() : array
    {
        return [$this->m, $this->n];
    }

    /**
     * Return the number of elements in the tensor.
     *
     * @return int
     */
    public function size() : int
    {
        return $this->m * $this->n;
    }

    /**
     * Return the number of rows in the matrix.
     *
     * @return int
     */
    public function m() : int
    {
        return $this->m;
    }

    /**
     * Return the number of columns in the matrix.
     *
     * @return int
     */
    public function n() : int
    {
        return $this->n;
    }

    /**
     * Return a row from the matrix.
     *
     * @param  int  $index
     * @return array
     */
    public function row(int $index) : array
    {
        return $this->offsetGet($index);
    }

    /**
     * Return a row as a vector from the matrix.
     *
     * @param  int  $index
     * @return \Rubix\Tensor\Vector
     */
    public function rowAsVector(int $index) : Vector
    {
        return new Vector($this->row($index));
    }

    /**
     * Return a column from the matrix.
     *
     * @param  int  $index
     * @return array
     */
    public function column(int $index) : array
    {
        return array_column($this->a, $index);
    }

    /**
     * Return a column as a vector from the matrix.
     *
     * @param  int  $index
     * @return \Rubix\Tensor\Vector
     */
    public function columnAsVector(int $index) : Vector
    {
        return new Vector($this->column($index));
    }

    /**
     * Return the elements of the matrix in a 2-d array.
     *
     * @return array
     */
    public function asArray() : array
    {
        return $this->a;
    }

    /**
     * Return each row as a vector in an array.
     *
     * @return array
     */
    public function asVectors() : array
    {
        return array_map(function ($row) {
            return new Vector($row, false);
        }, $this->a);
    }

    /**
     * Flatten the matrix into a vector.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function flatten() : Vector
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[] = $value;
            }
        }

        return new Vector($b, false);
    }

    /**
     * Trace the matrix along the diagonal i.e return the sum of all diagonal
     * elements of a square matrix.
     *
     * @throws \InvalidArgumentException
     * @return float
     */
    public function trace() : float
    {
        if ($this->m !== $this->n) {
            throw new InvalidArgumentException('Cannot trace a non square'
                . ' matrix.');
        }

        $sigma = 0.;

        for ($i = 0; $i < $this->m; $i++) {
            $sigma += $this->a[$i][$i];
        }

        return $sigma;
    }

    /**
     * Run a function over all of the elements in the matrix.
     *
     * @param  callable  $fn
     * @param  bool  $validate
     * @return self
     */
    public function map(callable $fn, bool $validate = false) : self
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = array_map($fn, $row);
        }

        return new self($b, $validate);
    }

    /**
     * Reduce the matrix down to a scalar.
     *
     * @param  callable  $fn
     * @param  float  $initial
     * @return float
     */
    public function reduce(callable $fn, float $initial = 0.) : float
    {
        $carry = $initial;

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $carry = $fn($value, $carry);
            }
        }

        return $carry;
    }

    /**
     * Transpose the matrix.
     *
     * @return self
     */
    public function transpose() : self
    {
        if ($this->m > 1) {
            $b = array_map(null, ...$this->a);
        } else {
            $b = [];

            for ($i = 0; $i < $this->n; $i++) {
                $b[$i] = array_column($this->a, $i);
            }
        }

        return new self($b, false);
    }

    /**
     * Return the elementwise reciprocal of the matrix.
     *
     * @return self
     */
    public function reciprocal() : self
    {
        return self::ones(...$this->shape())->divide($this);
    }

    /**
     * Return the index of the minimum element in every row of the matrix.
     * 
     * @return \Rubix\Tensor\Vector
     */
    public function argmin() : Vector
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = (int) array_search(min($row), $row);
        }

        return new Vector($b, false);
    }

    /**
     * Return the index of the maximum element in every row of the matrix.
     * 
     * @return \Rubix\Tensor\Vector
     */
    public function argmax() : Vector
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = (int) array_search(max($row), $row);
        }

        return new Vector($b, false);
    }

    /**
     * Dot this matrix with another tensor elementwise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function dot($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->dotMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->dotVector($b);
        }

        throw new InvalidArgumentException('Cannot dot matrix with a'
            . gettype($b) . '.');
    }

    /**
     * Multiply this matrix with another tensor elementwise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function multiply($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->multiplyMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->multiplyVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->multiplyScalar($b);
        }

        throw new InvalidArgumentException('Cannot multiply matrix with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Divide this matrix with another tensor elementwise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function divide($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->divideMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->divideVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->divideScalar($b);
        }

        throw new InvalidArgumentException('Cannot divide matrix with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Add this matrix to another tensor elementwise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function add($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->addMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->addVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->addScalar($b);
        }

        throw new InvalidArgumentException('Cannot sdd matrix to a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Subtract this matrix from another tensor elementwise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function subtract($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->subtractMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->subtractVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->subtractScalar($b);
        }

        throw new InvalidArgumentException('Cannot subtract matrix from a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Subtract this matrix from another tensor elementwise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function pow($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->powMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->powVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->powScalar($b);
        }

        throw new InvalidArgumentException('Cannot raise matrix to power of a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Calculate the modulus of the matrix with another tensor.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function mod($b) : self
    {
        if ($b instanceof Matrix) {
            return $this->modMatrix($b);
        } else if ($b instanceof Vector) {
            return $this->modVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->modScalar($b);
        }

        throw new InvalidArgumentException('Cannot mod matrix with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Take the dot product of this matrix and another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function dotMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->n) {
            throw new InvalidArgumentException('Matrix dimensions do not'
                . ' match. ' . (string) $this->n . ' rows needed but found'
                . ' ' . (string) $b->m() . '.');
        }

        $bT = $b->transpose();

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($bT as $j => $column) {
                $sigma = 0;

                foreach ($row as $k => $value) {
                    $sigma += $value * $column[$k];
                }

                $c[$i][$j] = $sigma;
            }
        }

        return new self($c, false);
    }

    /**
     * Return the elementwise product between this matrix and another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function multiplyMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $this->m . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $this->n . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][$j] = $value * $rowB[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Return the division of two elements, elementwise.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function divideMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $this->m . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $this->n . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][$j] = $value / $rowB[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Add this matrix together with another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function addMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $this->m . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $this->n . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][$j] = $value + $rowB[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Subtract this matrix from another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function subtractMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $this->m . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $this->n . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][$j] = $value - $rowB[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Raise this matrix to the power of the elementwise entry in another
     * matrix.
     *
     * @param \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function powMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $this->m . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $this->n . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][$j] = $value ** $rowB[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Calculate the modulus i.e remainder of division between this matri and
     * another matrix.
     *
     * @param \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function modMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of rows. ' . (string) $this->m . ' needed but found '
                . (string) $b->m() . '.');
        }

        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices have different number'
                . ' of columns. ' . (string) $this->n . ' needed but found '
                . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][$j] = $value % $rowB[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Take the dot product of this matrix and another matrix.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function dotVector(Vector $b) : self
    {
        if ($b->size() !== $this->n) {
            throw new InvalidArgumentException('Vector dimensions do not'
                . ' match. ' . (string) $this->n . ' rows needed but found'
                . ' ' . (string) $b->size() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($b as $j => $column) {
                $sigma = 0;

                foreach ($row as $value) {
                    $sigma += $value * $column;
                }

                $c[$i][$j] = $sigma;
            }
        }

        return new self($c, false);
    }

    /**
     * Multiply this matrix by a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function multiplyVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector does not have the same'
            . ' number of columns. ' . (string) $this->n . ' needed but found '
            . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][$j] = $value * $b[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Divide this matrix by a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function divideVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector does not have the same'
            . ' number of columns. ' . (string) $this->n . ' needed but found '
            . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][$j] = $value / $b[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Add this matrix by a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function addVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector does not have the same'
            . ' number of columns. ' . (string) $this->n . ' needed but found '
            . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][$j] = $value + $b[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Subtract this matrix to the power of a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function subtractVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector does not have the same'
            . ' number of columns. ' . (string) $this->n . ' needed but found '
            . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][$j] = $value - $b[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Raise this matrix to a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function powVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector does not have the same'
            . ' number of columns. ' . (string) $this->n . ' needed but found '
            . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][$j] = $value ** $b[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Calculate the modulus of this matrix with a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function modVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector does not have the same'
            . ' number of columns. ' . (string) $this->n . ' needed but found '
            . (string) $b->n() . '.');
        }

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][$j] = $value % $b[$j];
            }
        }

        return new self($c, false);
    }

    /**
     * Multiply this matrix by a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    public function multiplyScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = $value * $scalar;
            }
        }

        return new self($b, false);
    }

    /**
     * Divide this matrix by a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    public function divideScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = $value / $scalar;
            }
        }

        return new self($b, false);
    }

    /**
     * Add this matrix by a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    public function addScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = $value + $scalar;
            }
        }

        return new self($b, false);
    }

    /**
     * Subtract this matrix by a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    public function subtractScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = $value - $scalar;
            }
        }

        return new self($b, false);
    }

    /**
     * Raise the matrix to a given scalar power.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    public function powScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Exponent must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = $value ** $scalar;
            }
        }

        return new self($b, false);
    }

    /**
     * Calculate the modulus of this matrix with a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    public function modScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Exponent must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = $value % $scalar;
            }
        }

        return new self($b, false);
    }

    /**
     * Return the absolute value of each element in the matrix.
     *
     * @return self
     */
    public function abs() : self
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = array_map('abs', $row);
        }

        return new self($b, false);
    }

    /**
     * Return the square of the matrix elementwise.
     *
     * @return self
     */
    public function square() : self
    {
        return $this->powScalar(2);
    }

    /**
     * Return the square root of the matrix.
     *
     * @return self
     */
    public function sqrt() : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            $b[] = array_map('sqrt', $row);
        }

        return new self($b, false);
    }

    /**
     * Return the exponential of the matrix.
     *
     * @return self
     */
    public function exp() : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            $b[] = array_map('exp', $row);
        }

        return new self($b, false);
    }

    /**
     * Return the logarithm of the matrix in specified base.
     *
     * @param  float  $base
     * @return self
     */
    public function log(float $base = M_E) : self
    {
        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = log($value, $base);
            }
        }

        return new self($b, false);
    }

    /**
     * Return the sine of the matrix.
     *
     * @return self
     */
    public function sin() : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            $b[] = array_map('sin', $row);
        }

        return new self($b, false);
    }

    /**
     * Return the cosine of the matrix.
     *
     * @return self
     */
    public function cos() : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            $b[] = array_map('cos', $row);
        }

        return new self($b, false);
    }

    /**
     * Sum the rows of the matrix and return a vector.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function sum() : Vector
    {
        return new Vector(array_map('array_sum', $this->a), false);
    }

    /**
     * Calculate the row product of the matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function product() : Vector
    {
        return new Vector(array_map('array_product', $this->a), false);
    }

    /**
     * Return the minimum of each row in the matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function min() : Vector
    {
        return new Vector(array_map('min', $this->a), false);
    }

    /**
     * Return the maximum of each row in the matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function max() : Vector
    {
        return new Vector(array_map('max', $this->a), false);
    }

    /**
     * Compute the means of each row and return them in a vector.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function mean() : Vector
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = array_sum($row) / $this->m;
        }

        return new Vector($b, false);
    }

    /**
     * Return the median vector of this matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function median() : Vector
    {
        $b = [];

        foreach ($this->a as $row) {
            $mid = intdiv($this->n, 2);

            sort($row);

            if ($this->n % 2 === 1) {
                $median = $row[$mid];
            } else {
                $median = ($row[$mid - 1] + $row[$mid]) / 2.;
            }

            $b[] = $median;
        }

        return new Vector($b, false);
    }

    /**
     * Compute the row variance of the matrix and return it in a tuple along
     * with the mean.
     *
     * @return array
     */
    public function variance() : array
    {
        $mean = $this->mean();

        $variance = $this->subtractVector($mean)->square()->sum();

        return [$variance, $mean];
    }

    /**
     * Compute the covariance of this matrix and return it in a tuple along with
     * the computed mean.
     *
     * @return array
     */
    public function covariance() : array
    {
        $mean = $this->transpose()->mean();

        $b = $this->subtractVector($mean);

        $b = $b->dot($b->transpose())
            ->divideScalar($this->n);

        return [$b, $mean];
    }

    /**
     * Round the elements in the matrix to a given decimal place.
     *
     * @param  int  $precision
     * @return self
     */
    public function round(int $precision = 0) : self
    {
        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = round($value, $precision);
            }
        }

        return new self($b, false);
    }

    /**
     * Round the elements in the matrix down to the nearest integer.
     *
     * @return self
     */
    public function floor() : self
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = array_map('floor', $row);
        }

        return new self($b, false);
    }

    /**
     * Round the elements in the matrix up to the nearest integer.
     *
     * @return self
     */
    public function ceil() : self
    {
        $b = [];

        foreach ($this->a as $row) {
            $b[] = array_map('ceil', $row);
        }

        return new self($b, false);
    }

    /**
     * Return the L1 norm of the matrix.
     *
     * @return float
     */
    public function l1Norm() : float
    {
        $norm = 0.;

        foreach ($this->transpose() as $column) {
            $norm = max($norm, array_sum(array_map('abs', $column)));
        }

        return $norm;
    }

    /**
     * Return the L2 norm of the matrix.
     *
     * @return float
     */
    public function l2Norm() : float
    {
        $norm = 0.;

        foreach ($this->a as $row) {
            foreach ($row as $value) {
                $norm += $value ** 2;
            }
        }

        return sqrt($norm);
    }

    /**
     * Retrn the infinity norm of the matrix.
     *
     * @return float
     */
    public function infinityNorm() : float
    {
        $norm = 0.;

        foreach ($this->a as $row) {
            $norm = max($norm, array_sum(array_map('abs', $row)));
        }

        return $norm;
    }

    /**
     * Return the max norm of the matrix.
     *
     * @return float
     */
    public function maxNorm() : float
    {
        $norm = 0.;

        foreach ($this->a as $row) {
            foreach ($row as $value) {
                $norm = max($norm, abs($value));
            }
        }

        return $norm;
    }

    /**
     * Clip the elements in the matrix to be between given minimum and maximum
     * and return a new matrix.
     *
     * @param  float  $min
     * @param  float  $max
     * @return self
     */
    public function clip(float $min, float $max) : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                if ($value > $max) {
                    $b[$i][] = $max;

                    continue 1;
                }

                if ($value < $min) {
                    $b[$i][] = $min;

                    continue 1;
                }

                $b[$i][] = $value;
            }
        }

        return new self($b, false);
    }

    /**
     * Negate the matrix i.e take the negative of each value elementwise.
     *
     * @return self
     */
    public function negate() : self
    {
        $b = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $b[$i][$j] = -$value;
            }
        }

        return new self($b, false);
    }

    /**
     * Exclude a row from the matrix.
     *
     * @param  int  $index
     * @return self
     */
    public function rowExclude(int $index) : self
    {
        $b = $this->a;

        unset($b[$index]);

        return new self(array_values($b), false);
    }

    /**
     * Exclude a column from the matrix.
     *
     * @param  int  $index
     * @return self
     */
    public function columnExclude(int $index) : self
    {
        $b = $this->a;

        foreach ($b as $i => &$row) {
            unset($row[$index]);

            $row = array_values($row);
        }

        return new self($b, false);
    }

    /**
     * Attach matrix b above this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentAbove(Matrix $b) : self
    {
        if ($this->m > 0 and $b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices must have the same'
                . ' number of columns.');
        }

        return new self(array_merge($b->asArray(), $this->a), false);
    }

    /**
     * Attach matrix b below this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentBelow(Matrix $b) : self
    {
        if ($this->m > 0 and $b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrices must have the same'
                . ' number of columns.');
        }

        return new self(array_merge($this->a, $b->asArray()), false);
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentLeft(Matrix $b) : self
    {
        if ($this->m > 0 and $b->m() !== $this->m()) {
            throw new InvalidArgumentException('Matrices must have the same'
                . ' number of rows.');
        }

        return new self(array_map('array_merge',
            $b->asArray(), $this->a), false);
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentRight(Matrix $b) : self
    {
        if ($this->m > 0 and $b->m() !== $this->m()) {
            throw new InvalidArgumentException('Matrices must have the same'
                . ' number of rows.');
        }

        return new self(array_map('array_merge',
            $this->a, $b->asArray()), false);
    }

    /**
     * Repeat the matrix m times along the vertival axis and n times along the
     * horizontal axis.
     *
     * @param  int  $m
     * @param  int  $n
     * @return self
     */
    public function repeat(int $m = 1, int $n = 1) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Cannot repeat less than 1 row'
                . ' or column.');
        }

        $n -= 1;

        $b = $this->a;

        if ($n > 0) {
            foreach ($this->a as $i => $row) {
                for ($j = 0; $j < $n; $j++) {
                    $b[$i] = array_merge($b[$i], $row);
                }
            }
        }

        $c = [];

        for ($i = 0; $i < $m; $i++) {
            $c = array_merge($c, $b);
        }

        return new self($c, false);
    }

    /**
     * @return int
     */
    public function count() : int
    {
        return $this->size();
    }

    /**
     * @param  mixed  $index
     * @param  array  $values
     * @throws \RuntimeException
     * @return void
     */
    public function offsetSet($index, $values) : void
    {
        throw new RuntimeException('Matrix cannot be mutated directly.');
    }

    /**
     * Does a given column exist in the matrix.
     *
     * @param  mixed  $index
     * @return bool
     */
    public function offsetExists($index) : bool
    {
        return isset($this->a[$index]);
    }

    /**
     * @param  mixed  $index
     * @throws \RuntimeException
     * @return void
     */
    public function offsetUnset($index) : void
    {
        throw new RuntimeException('Matrix cannot be mutated directly.');
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param  mixed  $index
     * @throws \InvalidArgumentException
     * @return array
     */
    public function offsetGet($index) : array
    {
        if (!isset($this->a[$index])) {
            throw new InvalidArgumentException('Element not found at index '
                . (string) $index . '.');
        }

        return $this->a[$index];
    }

    /**
     * Get an iterator for the rows in the matrix.
     *
     * @return \ArrayIterator
     */
    public function getIterator()
    {
        return new ArrayIterator($this->a);
    }
}
