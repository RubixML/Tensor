<?php

namespace Rubix\Tensor;

use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;

/**
 * Vector
 *
 * A one dimensional (rank 1) tensor with integer and/or floating point elements.
 *
 * @category    Linear Algebra
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Vector implements Tensor
{
    /**
     * The 1-d sequential array that holds the values of the vector.
     *
     * @var (int|float)[]
     */
    protected $a = [
        //
    ];

    /**
     * The number of elements in the vector.
     *
     * @var int
     */
    protected $n;

    /**
     * Factory method to build a new vector from an array.
     *
     * @param  array  $a
     * @return self
     */
    public static function build(array $a = []) : self
    {
        return new self($a, true);
    }

    /**
     * Build a vector foregoing any validation for quicker instantiation.
     *
     * @param  array  $a
     * @return self
     */
    public static function quick(array $a = []) : self
    {
        return new self($a, false);
    }

    /**
     * Build a vector of zeros with n elements.
     *
     * @param  int  $n
     * @return self
     */
    public static function zeros(int $n) : self
    {
        return self::quick(array_fill(0, $n, 0));
    }

    /**
     * Build a vector of ones with n elements.
     *
     * @param  int  $n
     * @return self
     */
    public static function ones(int $n) : self
    {
        return self::quick(array_fill(0, $n, 1));
    }

    /**
     * Fill a vector with a given value.
     *
     * @param  mixed  $value
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill($value, int $n) : self
    {
        if (!is_int($value) and !is_float($value)) {
            throw new InvalidArgumentException('Fill value must be an integer'
                . ' or float, ' . gettype($value) . ' found.');
        }

        return self::quick(array_fill(0, $n, $value));
    }

    /**
     * Return a random uniform vector with values between 0 and 1.
     *
     * @param  int  $n
     * @return self
     */
    public static function rand(int $n) : self
    {
        $a = [];

        for ($i = 0; $i < $n; $i++) {
            $a[] = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
        }

        return self::quick($a);
    }

    /**
     * Return a standard normally distributed random vector i.e values between
     * -1 and 1.
     *
     * @param  int  $n
     * @return self
     */
    public static function gaussian(int $n) : self
    {
        $a = [];

        for ($i = 0; $i < $n; $i += 2) {
            $r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            $r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            
            $r = sqrt(-2. * log($r1));

            $a[] = $r * sin($r2 * self::TWO_PI);
            $a[] = $r * cos($r2 * self::TWO_PI);
        }

        if (count($a) > $n) {
            $a = array_slice($a, 0, $n);
        }

        return self::quick($a);
    }

    /**
     * Return a uniform random vector with mean 0 and unit variance.
     *
     * @param  int  $n
     * @return self
     */
    public static function uniform(int $n) : self
    {
        $a = [];

        for ($i = 0; $i < $n; $i++) {
            $a[] = rand(-PHP_INT_MAX, PHP_INT_MAX) / PHP_INT_MAX;
        }

        return self::quick($a);
    }

    /**
     * Return evenly spaced values within a given interval.
     *
     * @param  float  $start
     * @param  float  $end
     * @param  float  $interval
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function range(float $start, float $end, float $interval = 1.) : self
    {
        if ($interval <= 0.) {
            throw new InvalidArgumentException('Interval must be greater than'
                 . ' 0.');
        }

        return self::quick(range($start, $end, $interval));
    }

    /**
     * Return evenly spaced numbers over a specified interval.
     *
     * @param  float  $start
     * @param  float  $end
     * @param  int  $n
     * @return self
     */
    public static function linspace(float $start, float $end, int $n) : self
    {
        $range = abs($end - $start);

        $interval = ($range / ($n - 1)) - (self::EPSILON * $range);

        return self::range($start, $end, $interval);
    }

    /**
     * Return the elementwise maximum of two vectors.
     *
     * @param  \Rubix\Tensor\Vector  $a
     * @param  \Rubix\Tensor\Vector  $b
     * @return self
     */
    public static function maximum(Vector $a, Vector $b) : self
    {
        if ($a->n() !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $a->n() . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = array_map('max', $a->asArray(), $b->asArray());

        return self::quick($c);
    }

    /**
     * Return the elementwise minimum of two vectors.
     *
     * @param  \Rubix\Tensor\Vector  $a
     * @param  \Rubix\Tensor\Vector  $b
     * @return self
     */
    public static function minimum(Vector $a, Vector $b) : self
    {
        if ($a->n() !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $a->n() . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = array_map('min', $a->asArray(), $b->asArray());

        return self::quick($c);
    }

    /**
     * @param  array  $a
     * @param  bool  $validate
     * @throws \InvalidArgumentException
     * @return void
     */
    public function __construct(array $a = [], bool $validate = true)
    {
        if ($validate === true) {
            $a = array_values($a);

            foreach ($a as $value) {
                if (!is_int($value) and !is_float($value)) {
                    throw new InvalidArgumentException('Vector element must'
                        . ' be an integer or float, '
                        . gettype($value) . ' found.');
                }
            }
        }

        $this->a = $a;
        $this->n = count($a);
    }

    /**
     * Return a tuple with the dimensionality of the tensor.
     *
     * @return int[]
     */
    public function shape() : array
    {
        return [$this->n];
    }

    /**
     * Return the number of elements in the vector.
     *
     * @return int
     */
    public function size() : int
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
        return $this->n;
    }

    /**
     * Return the vector as an array.
     *
     * @return array
     */
    public function asArray() : array
    {
        return $this->a;
    }

    /**
     * Return this vector as a row matrix.
     *
     * @return \Rubix\Tensor\Matrix
     */
    public function asRowMatrix() : Matrix
    {
        return Matrix::quick([$this->a]);
    }

    /**
     * Return this vector as a column matrix.
     *
     * @return \Rubix\Tensor\Matrix
     */
    public function asColumnMatrix() : Matrix
    {
        return Matrix::quick(array_map(function ($value) {
            return [$value];
        }, $this->a));
    }

    /**
     * Return a matrix in the shape specified.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return \Rubix\Tensor\Matrix
     */
    public function reshape(int $m, int $n) : Matrix
    {
        if (($m * $n) !== $this->size()) {
            throw new InvalidArgumentException('The shape of the new matrix is'
                . ' incompatible with the current vector.');
        }

        $index = 0;

        $b = [];

        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $b[$i][] = $this->a[$index++];
            }
        }

        return Matrix::quick($b);
    }

    /**
     * Return the index of the minimum element in the vector.
     * 
     * @return int
     */
    public function argmin() : int
    {
        return (int) array_search(min($this->a), $this->a);
    }

    /**
     * Return the index of the maximum element in the vector.
     * 
     * @return int
     */
    public function argmax() : int
    {
        return (int) array_search(max($this->a), $this->a);
    }

    /**
     * Map a function over the elements in the vector and return a new vector.
     *
     * @param  callable  $fn
     * @return self
     */
    public function map(callable $fn) : self
    {
        $validate = is_object($fn) ? true : false;

        return new self(array_map($fn, $this->a), $validate);
    }

    /**
     * Reduce the vector down to a scalar.
     *
     * @param  callable  $fn
     * @param  mixed  $initial
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function reduce(callable $fn, $initial = 0)
    {
        if (!is_int($initial) and !is_float($initial)) {
            throw new InvalidArgumentException('Initial value must'
                . ' be an integer or float.');
        }

        return array_reduce($this->a, $fn, $initial);
    }

    /**
     * Compute the dot product of this vector and another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function dot(Vector $b)
    {
        if ($this->n !== $b->size()) {
            throw new InvalidArgumentException('Vectors do not have the same'
                . ' dimensionality.');
        }

        $sigma = 0.;

        foreach ($this->a as $i => $value) {
            $sigma += $value * $b[$i];
        }

        return $sigma;
    }

    /**
     * Return the inner product of two vectors.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @return int|float
     */
    public function inner(Vector $b)
    {
        return $this->dot($b);
    }

    /**
     * Calculate the outer product of this and another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @return \Rubix\Tensor\Matrix
     */
    public function outer(Vector $b) : Matrix
    {
        $n = $b->n();

        $c = [];

        foreach ($this->a as $i => $value) {
            for ($j = 0; $j < $n; $j++) {
                $c[$i][] = $value * $b[$j];
            }
        }

        return Matrix::quick($c);
    }

    /**
     * Calculate the cross product between two 3 dimensional vectors.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @return self
     */
    public function cross(Vector $b) : self
    {
        if ($this->n !== 3 or $b->n() !== 3) {
            throw new InvalidArgumentException('Cross product is only defined'
                . ' for vectors in 3 dimensions.');
        }

        $c = [];

        $c[] = ($this->a[1] * $b[2]) - ($this->a[2] * $b[1]);
        $c[] = ($this->a[2] * $b[0]) - ($this->a[0] * $b[2]);
        $c[] = ($this->a[0] * $b[1]) - ($this->a[1] * $b[0]);

        return self::quick($c);
    }

    /**
     * Project this vector on another vector.
     * 
     * @param  \Rubix\Tensor\Vector  $b
     * @return self
     */
    public function project(Vector $b) : self
    {
        $bHat = $this->dot($b) / ($b->l2Norm() ** 2);

        return $b->multiply($bHat);
    }

        /**
     * Calculate the L1 or Manhattan norm of the vector.
     *
     * @return int|float
     */
    public function l1Norm()
    {
        return $this->abs()->sum();
    }

    /**
     * Calculate the L2 or Euclidean norm of the vector.
     *
     * @return int|float
     */
    public function l2Norm()
    {
        return sqrt($this->square()->sum());
    }

    /**
     * Calculate the p-norm of the vector.
     *
     * @param  float  $p
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function pNorm(float $p = 3.)
    {
        if ($p < 0.) {
            throw new InvalidArgumentException('P must be greater'
                . ' than 0.');
        }

        return $this->abs()->powScalar($p)->sum() ** (1. / $p);
    }

    /**
     * Calculate the max norm of the vector.
     *
     * @return int|float
     */
    public function maxNorm()
    {
        return $this->abs()->max();
    }

    /**
     * A universal function to multiply this vector with another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function multiply($b) : self
    {
        if ($b instanceof Vector) {
            return $this->multiplyVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->multiplyScalar($b);
        }

        throw new InvalidArgumentException('Cannot multiply vector with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * A universal function to divide this vector by another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function divide($b) : self
    {
        if ($b instanceof Vector) {
            return $this->divideVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->divideScalar($b);
        }

        throw new InvalidArgumentException('Cannot multiply vector with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * A universal function to add this vector with another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function add($b) : self
    {
        if ($b instanceof Vector) {
            return $this->addVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->addScalar($b);
        }

        throw new InvalidArgumentException('Cannot add vector to a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * A universal function to subtract this vector from another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function subtract($b) : self
    {
        if ($b instanceof Vector) {
            return $this->subtractVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->subtractScalar($b);
        }

        throw new InvalidArgumentException('Cannot subtract vector from a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * A universal function to raise this vector to the power of another
     * tensor element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function pow($b) : self
    {
        if ($b instanceof Vector) {
            return $this->powVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->powScalar($b);
        }

        throw new InvalidArgumentException('Cannot multiply vector with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * A universal function to compute the modulus of this vector and
     * another tensor element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function mod($b) : self
    {
        if ($b instanceof Vector) {
            return $this->modVector($b);
        } else if (is_int($b) or is_float($b)) {
            return $this->modScalar($b);
        }

        throw new InvalidArgumentException('Cannot mod vector with a'
            . ' ' . gettype($b) . '.');
    }

    /**
     * Return the reciprocal of the vector.
     *
     * @return self
     */
    public function reciprocal() : self
    {
        return self::ones($this->n)->divide($this);
    }

    /**
     * Return the absolute value of the vector.
     *
     * @return self
     */
    public function abs() : self
    {
        return $this->map('abs');
    }

    /**
     * Square the vector.
     *
     * @return self
     */
    public function square() : self
    {
        return $this->pow(2);
    }

    /**
     * Take the square root of the vector.
     *
     * @return self
     */
    public function sqrt() : self
    {
        return $this->map('sqrt');
    }

    /**
     * Exponentiate each element in the vector.
     *
     * @return self
     */
    public function exp() : self
    {
        return $this->map('exp');
    }

    /**
     * Take the log to the given base of each element in the vector.
     *
     * @param  float  $base
     * @return self
     */
    public function log(float $base = M_E) : self
    {
        $b = [];

        foreach ($this->a as $value) {
            $b[] = log($value, $base);
        }

        return self::quick($b);
    }

    /**
     * Return the sine of this vector.
     *
     * @return self
     */
    public function sin() : self
    {
        return $this->map('sin');
    }

    /**
     * Return the cosine of this vector.
     *
     * @return self
     */
    public function cos() : self
    {
        return $this->map('cos');
    }

    /**
     * Return the tangent of this vector.
     *
     * @return self
     */
    public function tan() : self
    {
        return $this->map('tan');
    }

    /**
     * Convert angles from radians to degrees.
     *
     * @return self
     */
    public function degrees() : self
    {
        return $this->map('rad2deg');
    }

    /**
     * Convert angles from degrees to radians.
     *
     * @return self
     */
    public function radians() : self
    {
        return $this->map('deg2rad');
    }

    /**
     * The sum of the vector.
     *
     * @return int|float
     */
    public function sum()
    {
        return array_sum($this->a);
    }

    /**
     * Return the product of the vector.
     *
     * @return int|float
     */
    public function product()
    {
        return array_product($this->a);
    }

    /**
     * Return the minimum element in the vector.
     *
     * @return int|float
     */
    public function min()
    {
        return min($this->a);
    }

    /**
     * Return the maximum element in the vector.
     *
     * @return int|float
     */
    public function max()
    {
        return max($this->a);
    }

    /**
     * Return the mean of the vector.
     *
     * @return int|float
     */
    public function mean()
    {
        return $this->sum() / $this->n;
    }

    /**
     * Return the median of the vector.
     *
     * @throws \RuntimeException
     * @return int|float
     */
    public function median()
    {
        $n = $this->size();

        if ($n < 1) {
            throw new RuntimeException('Median is not defined for vectors with'
                . ' less than 1 element.');
        }

        $mid = intdiv($n, 2);

        $a = $this->a;

        sort($a);

        if ($n % 2 === 1) {
            $median = $a[$mid];
        } else {
            $median = ($a[$mid - 1] + $a[$mid]) / 2.;
        }

        return $median;
    }

    /**
     * Return the variance of the vector.
     *
     * @return int|float
     */
    public function variance()
    {
        $mu = $this->mean();

        return $this->subtract($mu)->square()->sum()
            / $this->n;
    }

    /**
     * Round the elements in the matrix to a given decimal place.
     *
     * @param  int  $precision
     * @return self
     */
    public function round(int $precision = 0) : self
    {
        $b = [];

        foreach ($this->a as $value) {
            $b[] = round($value, $precision);
        }

        return self::quick($b);
    }

    /**
     * Round the elements in the vector down to the nearest integer.
     *
     * @return self
     */
    public function floor() : self
    {
        return $this->map('floor');
    }

    /**
     * Round the elements in the vector up to the nearest integer.
     *
     * @return self
     */
    public function ceil() : self
    {
        return $this->map('ceil');
    }

    /**
     * Clip the elements in the vector to be between given minimum and maximum
     * and return a new vector.
     *
     * @param  float  $min
     * @param  float  $max
     * @return self
     */
    public function clip(float $min, float $max) : self
    {
        $b = [];

        foreach ($this->a as $value) {
            if ($value > $max) {
                $b[] = $max;

                continue 1;
            }

            if ($value < $min) {
                $b[] = $min;

                continue 1;
            }

            $b[] = $value;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise sign indication.
     * 
     * @return self
     */
    public function sign() : self
    {
        $b = [];

        foreach ($this->a as $value) {
            if ($value > 0) {
                $sign = 1;
            } else if ($value < 0) {
                $sign = -1;
            } else {
                $sign = 0;
            }

            $b[] = $sign;
        }

        return self::quick($b);
    }

    /**
     * Negate the vector i.e take the negative of each value elementwise.
     *
     * @return self
     */
    public function negate() : self
    {
        $b = [];

        foreach ($this->a as $value) {
            $b[] = -$value;
        }

        return self::quick($b);
    }

    /**
     * Multiply this vector with another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $this->n . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value * $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Divide this vector by another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $this->n . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value / $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Add this vector to another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $this->n . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value + $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Subtract this vector from another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $this->n . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value - $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Raise this vector to a power of another vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $this->n . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value ** $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Calculate the modulus of this vector with another vector elementwise.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new InvalidArgumentException('Vector dimensionality does not'
                . ' match.' . (string) $this->n . ' needed but'
                . ' found ' . (string) $b->n() . '.');
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value % $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Multiply this vector by a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value * $scalar;
        }

        return self::quick($b);
    }

    /**
     * Divide this vector by a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value / $scalar;
        }

        return self::quick($b);
    }

    /**
     * Add a scalar to this vector.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Factor must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value + $scalar;
        }

        return self::quick($b);
    }

    /**
     * Subtract a scalar from this vector.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value - $scalar;
        }

        return self::quick($b);
    }

    /**
     * Raise the vector to a the power of a scalar value.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value ** $scalar;
        }

        return self::quick($b);
    }

    /**
     * Calculate the modulus of this vector with a scalar.
     *
     * @param  int|float  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer or'
                . ' float ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value % $scalar;
        }

        return self::quick($b);
    }

    /**
     * @return int
     */
    public function count() : int
    {
        return $this->n;
    }

    /**
     * @param  mixed  $index
     * @param  array  $values
     * @throws \RuntimeException
     * @return void
     */
    public function offsetSet($index, $values) : void
    {
        throw new RuntimeException('Vector cannot be mutated directly.');
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
        throw new RuntimeException('Vector cannot be mutated directly.');
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param  mixed  $index
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function offsetGet($index)
    {
        if (!isset($this->a[$index])) {
            throw new InvalidArgumentException('Element not found at index'
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

    /**
     * Convert the tensor into a string representation.
     *
     * @return string
     */
    public function __toString() : string
    {
        return '[ ' . implode(' ', $this->a) . ' ]';
    }
}
