<?php

namespace Rubix\Tensor;

use Rubix\Tensor\Exceptions\DimensionalityMismatchException;
use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;
use Exception;
use Closure;

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
     * @param array $a
     * @return mixed
     */
    public static function build(array $a = [])
    {
        return new static($a, true);
    }

    /**
     * Build a vector foregoing any validation for quicker instantiation.
     *
     * @param array $a
     * @return mixed
     */
    public static function quick(array $a = [])
    {
        return new static($a, false);
    }

    /**
     * Build a vector of zeros with n elements.
     *
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function zeros(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

        return self::quick(array_fill(0, $n, 0));
    }

    /**
     * Build a vector of ones with n elements.
     *
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function ones(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

        return self::quick(array_fill(0, $n, 1));
    }

    /**
     * Fill a vector with a given value.
     *
     * @param mixed $value
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill($value, int $n) : self
    {
        if (!is_int($value) and !is_float($value)) {
            throw new InvalidArgumentException('Fill value expects an'
                . ' integer or float, ' . gettype($value) . ' found.');
        }

        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

        return self::quick(array_fill(0, $n, $value));
    }

    /**
     * Return a random uniform vector with values between 0 and 1.
     *
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function rand(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

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
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function gaussian(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

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
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function uniform(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

        $a = [];

        for ($i = 0; $i < $n; $i++) {
            $a[] = rand(-PHP_INT_MAX, PHP_INT_MAX) / PHP_INT_MAX;
        }

        return self::quick($a);
    }

    /**
     * Return evenly spaced values within a given interval.
     *
     * @param float $start
     * @param float $end
     * @param float $interval
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function range(float $start, float $end, float $interval = 1.) : self
    {
        if ($interval <= 0.) {
            throw new InvalidArgumentException('Interval must be greater'
                 . " than 0, $interval given.");
        }

        return self::quick(range($start, $end, $interval));
    }

    /**
     * Return evenly spaced numbers over a specified interval.
     *
     * @param float $start
     * @param float $end
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function linspace(float $start, float $end, int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('The number of elements'
                . " must be greater than 0, $n given.");
        }

        $range = abs($end - $start);

        $interval = ($range / ($n - 1)) - (self::EPSILON * $range);

        return self::range($start, $end, $interval);
    }

    /**
     * Return the elementwise maximum of two vectors.
     *
     * @param \Rubix\Tensor\Vector $a
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public static function maximum(Vector $a, Vector $b) : self
    {
        if ($a->n() !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " {$a->n()} elements but Vector B has{$b->n()}.");
        }

        $c = array_map('max', $a->asArray(), $b->asArray());

        return self::quick($c);
    }

    /**
     * Return the elementwise minimum of two vectors.
     *
     * @param \Rubix\Tensor\Vector $a
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public static function minimum(Vector $a, Vector $b) : self
    {
        if ($a->n() !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " {$a->n()} elements but Vector B has {$b->n()}.");
        }

        $c = array_map('min', $a->asArray(), $b->asArray());

        return self::quick($c);
    }

    /**
     * @param array $a
     * @param bool $validate
     * @throws \InvalidArgumentException
     */
    public function __construct(array $a = [], bool $validate = true)
    {
        if ($validate === true) {
            $a = array_values($a);

            foreach ($a as $value) {
                if (!is_int($value) and !is_float($value)) {
                    throw new InvalidArgumentException('Element must be'
                        . ' an integer or float, ' . gettype($value)
                        . ' found.');
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
        return [1, $this->n];
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
     * Return the number of rows in the vector.
     *
     * @return int
     */
    public function m() : int
    {
        return 1;
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
        $b = [];

        foreach ($this->a as $value) {
            $b[] = [$value];
        }

        return Matrix::quick($b);
    }

    /**
     * Return a matrix in the shape specified.
     *
     * @param int $m
     * @param int $n
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    public function reshape(int $m, int $n) : Matrix
    {
        if (($m * $n) !== $this->n) {
            throw new DimensionalityMismatchException("($m * $n) elements"
                . " are needed but vector has $this->n.");
        }

        $k = 0;

        $b = [];

        for ($i = 0; $i < $m; $i++) {
            $temp = [];

            for ($j = 0; $j < $n; $j++) {
                $temp[] = $this->a[$k++];
            }

            $b[] = $temp;
        }

        return Matrix::quick($b);
    }

    /**
     * Transpose the vector i.e. rotate it.
     *
     * @return mixed
     */
    public function transpose()
    {
        return ColumnVector::quick($this->a);
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
     * Map a function over the elements in the vector and return a new
     * vector.
     *
     * @param callable $fn
     * @return self
     */
    public function map(callable $fn) : self
    {
        $validate = $fn instanceof Closure;

        return new static(array_map($fn, $this->a), $validate);
    }

    /**
     * Reduce the vector down to a scalar.
     *
     * @param callable $fn
     * @param mixed $initial
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function reduce(callable $fn, $initial = 0)
    {
        if (!is_int($initial) and !is_float($initial)) {
            throw new InvalidArgumentException('Initial value must'
                . ' be an integer or float, ' . gettype($initial)
                . ' found.');
        }

        return array_reduce($this->a, $fn, $initial);
    }

    /**
     * Compute the dot product of this vector and another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return int|float
     */
    public function dot(Vector $b)
    {
        if ($this->n !== $b->size()) {
            throw new DimensionalityMismatchException('Vector A'
                . " requires $this->n elements but B has {$b->size()}.");
        }

        $sigma = 0.;

        foreach ($this->a as $i => $value) {
            $sigma += $value * $b[$i];
        }

        return $sigma;
    }

    /**
     * Compute the vector-matrix product of this vector and matrix a.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @return \Rubix\Tensor\Matrix
     */
    public function matmul(Matrix $b) : Matrix
    {
        return $this->asRowMatrix()->matmul($b);
    }

    /**
     * Return the inner product of two vectors.
     *
     * @param \Rubix\Tensor\Vector $b
     * @return int|float
     */
    public function inner(Vector $b)
    {
        return $this->dot($b);
    }

    /**
     * Calculate the outer product of this and another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @return \Rubix\Tensor\Matrix
     */
    public function outer(Vector $b) : Matrix
    {
        $n = $b->n();

        $c = [];

        foreach ($this->a as $i => $value) {
            $temp = [];

            for ($j = 0; $j < $n; $j++) {
                $temp[] = $value * $b[$j];
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Calculate the cross product between two 3 dimensional vectors.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public function cross(Vector $b) : self
    {
        if ($this->n !== 3 or $b->size() !== 3) {
            throw new DimensionalityMismatchException('Cross product is'
                . ' only defined for vectors of 3 dimensions.');
        }

        $c = [];

        $c[] = ($this->a[1] * $b[2]) - ($this->a[2] * $b[1]);
        $c[] = ($this->a[2] * $b[0]) - ($this->a[0] * $b[2]);
        $c[] = ($this->a[0] * $b[1]) - ($this->a[1] * $b[0]);

        return self::quick($c);
    }

    /**
     * Convolve this vector with another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @param int $stride
     * @throws \InvalidArgumentException
     * @return self
     */
    public function convolve(Vector $b, int $stride = 1) : self
    {
        if ($b->size() > $this->n) {
            throw new InvalidArgumentException('Vector B cannot be'
                . ' longer than Vector A.');
        }

        if ($stride < 1) {
            throw new InvalidArgumentException('Stride cannot be'
                . " less than 1, $stride given.");
        }

        $c = [];

        for ($i = 0; $i < $this->n; $i += $stride) {
            $sigma = 0;

            foreach ($b as $j => $valueB) {
                $sigma += ($this->a[$i - (int) $j] ?? 0) * $valueB;
            }

            $c[] = $sigma;
        }

        return self::quick($c);
    }

    /**
     * Project this vector on another vector.
     *
     * @param \Rubix\Tensor\Vector $b
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
     * @param float $p
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function pNorm(float $p = 3.)
    {
        if ($p <= 0.) {
            throw new InvalidArgumentException('P must be greater'
                . " than 0, $p given.");
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
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function multiply($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->multiplyVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->multiplyMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->multiplyScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot multiply vector'
                    . ' with a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to divide this vector by another tensor
     * element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->divideVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->divideMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->divideScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot divide vector'
                    . ' with a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to add this vector with another tensor
     * element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->addVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->addMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->addScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot add vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to subtract this vector from another tensor
     * element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->subtractVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->subtractMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->subtractScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot subtract a '
                    . gettype($b) . ' from vector.');
        }

        return $c;
    }

    /**
     * A universal function to raise this vector to the power of another
     * tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->powVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->powMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->powScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot raise vector'
                    . ' to a power of a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the modulus of this vector and
     * another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->modVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->modMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->modScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot mod vector'
                    . ' with a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the equality comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function equal($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->equalVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->equalMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->equalScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot compare vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the not equal comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function notEqual($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->notEqualVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->notEqualMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->notEqualScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot compare vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the greater than comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greater($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->greaterVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->greaterMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->greaterScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot compare vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the greater than or equal to
     * comparison of this vector and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greaterEqual($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->greaterEqualVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->greaterEqualMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->greaterEqualScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot compare vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the less than comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function less($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->lessVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->lessMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->lessScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot compare vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * A universal function to compute the less than or equal to
     * comparison of this vector and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function lessEqual($b)
    {
        switch (true) {
            case $b instanceof Vector:
                $c = $this->lessEqualVector($b);
                break;

            case $b instanceof Matrix:
                $c = $this->lessEqualMatrix($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->lessEqualScalar($b);
                break;

            default:
                throw new InvalidArgumentException('Cannot compare vector'
                    . ' to a ' . gettype($b) . '.');
        }

        return $c;
    }

    /**
     * Return the reciprocal of the vector element-wise.
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
     * @param float $base
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
     * @throws \RuntimeException
     * @return int|float
     */
    public function mean()
    {
        if ($this->n === 0) {
            throw new RuntimeException('Mean is not defined for vectors'
            . ' with less than 1 element.');
        }

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
        if ($this->n < 1) {
            throw new RuntimeException('Median is not defined for vectors'
                . ' with less than 1 element.');
        }

        $mid = intdiv($this->n, 2);

        $a = $this->a;

        sort($a);

        if ($this->n % 2 === 1) {
            $median = $a[$mid];
        } else {
            $median = ($a[$mid - 1] + $a[$mid]) / 2.;
        }

        return $median;
    }

    /**
     * Return the pth percentile of the vector.
     *
     * @param float $p
     * @throws \InvalidArgumentException
     * @throws \RuntimeException
     * @return float
     */
    public function percentile(float $p) : float
    {
        if ($p < 0. or $p > 100.) {
            throw new InvalidArgumentException('P must be between 0 and 100,'
                . " $p given.");
        }

        if ($this->n < 1) {
            throw new RuntimeException('Percentile is not defined for vectors'
                . ' with less than 1 element.');
        }

        $a = $this->a;

        sort($a);

        $x = ($p / 100) * ($this->n - 1) + 1;

        $xHat = (int) $x;

        $remainder = $x - $xHat;

        $t = $a[$xHat - 1];

        return $t + $remainder * ($a[$xHat] - $t);
    }

    /**
     * Return the variance of the vector.
     *
     * @return int|float
     */
    public function variance()
    {
        if ($this->n === 0) {
            throw new RuntimeException('Variance is not defined for vectors'
            . ' with less than 1 element.');
        }

        $ssd = $this->subtract($this->mean())
            ->square()
            ->sum();

        return $ssd / $this->n;
    }

    /**
     * Round the elements in the matrix to a given decimal place.
     *
     * @param int $precision
     * @throws \InvalidArgumentException
     * @return self
     */
    public function round(int $precision = 0) : self
    {
        if ($precision < 0) {
            throw new InvalidArgumentException('Decimal precision cannot'
                . " be less than 0, $precision given.");
        }

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
     * @param float $min
     * @param float $max
     * @throws \InvalidArgumentException
     * @return self
     */
    public function clip(float $min, float $max) : self
    {
        if ($min > $max) {
            throw new InvalidArgumentException('Minimum cannot be'
                . ' greater than maximum.');
        }

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
     * Clip the tensor to be lower bounded by a given minimum.
     *
     * @param float $min
     * @return mixed
     */
    public function clipLower(float $min)
    {
        $b = [];

        foreach ($this->a as $value) {
            if ($value < $min) {
                $b[] = $min;

                continue 1;
            }

            $b[] = $value;
        }

        return self::quick($b);
    }

    /**
     * Clip the tensor to be upper bounded by a given maximum.
     *
     * @param float $max
     * @return mixed
     */
    public function clipUpper(float $max)
    {
        $b = [];

        foreach ($this->a as $value) {
            if ($value > $max) {
                $b[] = $max;

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
                $b[] = 1;
            } elseif ($value < 0) {
                $b[] = -1;
            } else {
                $b[] = 0;
            }
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
     * Multiply this vector with a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function multiplyMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] * $value;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Divide this vector with a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function divideMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] / $value;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Add this vector to a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function addMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] + $value;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Subtract a matrix from this vector.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function subtractMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] - $value;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Raise this vector to the power of a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function powMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] ** $value;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Mod this vector with a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function modMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] % $value;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this vector and a
     * matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function equalMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] == $value ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this vector and a
     * matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function notEqualMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] != $value ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this vector
     * and a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function greaterMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] > $value ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this vector and a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function greaterEqualMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] >= $value ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this vector
     * and a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function lessMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] < $value ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this vector and a matrix.
     *
     * @param \Rubix\Tensor\Matrix $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return \Rubix\Tensor\Matrix
     */
    protected function lessEqualMatrix(Matrix $b) : Matrix
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($b as $row) {
            $temp = [];

            foreach ($row as $j => $value) {
                $temp[] = $this->a[$j] <= $value ? 1 : 0;
            }

            $c[] = $temp;
        }

        return Matrix::quick($c);
    }

    /**
     * Multiply this vector with another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function multiplyVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
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
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function divideVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
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
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function addVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value + $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Subtract a vector from this vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function subtractVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
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
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function powVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
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
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function modVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value % $b[$i];
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this vector and a
     * another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function equalVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value == $b[$i] ? 1 : 0;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this vector and a
     * another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function notEqualVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value != $b[$i] ? 1 : 0;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this vector
     * and a another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function greaterVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value > $b[$i] ? 1 : 0;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this vector and a another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function greaterEqualVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value >= $b[$i] ? 1 : 0;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this vector
     * and a another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function lessVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value < $b[$i] ? 1 : 0;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this vector and a another vector.
     *
     * @param \Rubix\Tensor\Vector $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function lessEqualVector(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException('Vector A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        $c = [];

        foreach ($this->a as $i => $value) {
            $c[] = $value <= $b[$i] ? 1 : 0;
        }

        return self::quick($c);
    }

    /**
     * Multiply this vector by a scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
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
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
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
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
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
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
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
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
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
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value % $scalar;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise equality comparison of this vector and a
     * scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value == $scalar ? 1 : 0;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise not equal comparison of this vector and a
     * scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value != $scalar ? 1 : 0;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise greater than comparison of this vector
     * and a scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value > $scalar ? 1 : 0;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this vector and a scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value >= $scalar ? 1 : 0;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise less than comparison of this vector
     * and a scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value < $scalar ? 1 : 0;
        }

        return self::quick($b);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this vector and a scalar.
     *
     * @param mixed $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException('Scalar must be an integer'
                . ' or float, ' . gettype($scalar) . ' found.');
        }

        $b = [];

        foreach ($this->a as $value) {
            $b[] = $value <= $scalar ? 1 : 0;
        }

        return self::quick($b);
    }

    /**
     * Count method to implement countable interface.
     *
     * @return int
     */
    public function count() : int
    {
        return $this->n;
    }

    /**
     * @param mixed $index
     * @param array $values
     * @throws \RuntimeException
     */
    public function offsetSet($index, $values) : void
    {
        throw new RuntimeException('Vector cannot be mutated directly.');
    }

    /**
     * Does a given column exist in the matrix.
     *
     * @param mixed $index
     * @return bool
     */
    public function offsetExists($index) : bool
    {
        return isset($this->a[$index]);
    }

    /**
     * @param mixed $index
     * @throws \RuntimeException
     */
    public function offsetUnset($index) : void
    {
        throw new RuntimeException('Vector cannot be mutated directly.');
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param mixed $index
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function offsetGet($index)
    {
        if (!isset($this->a[$index])) {
            throw new InvalidArgumentException('Element not found at the'
                . " given offset $index.");
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
     * Magic getters for tensor properties.
     *
     * @param string $name
     * @throws \Exception
     * @return mixed
     */
    public function __get(string $name)
    {
        switch ($name) {
            case 'm':
                return $this->m();

            case 'n':
                return $this->n();

            case 'T':
                return $this->transpose();
            
            default:
                throw new Exception('Property does not exist.');
        }
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
