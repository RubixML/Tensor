<?php

namespace Rubix\Tensor;

use JAMA\Matrix as JAMA;
use Rubix\Tensor\Exceptions\DimensionalityMismatchException;
use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;

/**
 * Matrix
 *
 * A two dimensional (rank 2) tensor with integer and/or floating point elements.
 *
 * @category    Linear Algebra
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Matrix implements Tensor
{
    /**
     * The 2-dimensional sequential array that holds the values of the matrix.
     *
     * @var array[]
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
     * @param  array  $a
     * @return self
     */
    public static function build(array $a = []) : self
    {
        return new self($a, true);
    }

    /**
     * Build a new matrix foregoing any validation for quicker instantiation.
     *
     * @param  array  $a
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
                . ' greater than 0 on all axes.');
        }

        $a = [[]];

        for ($i = 0; $i < $n; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][$j] = $i === $j ? 1 : 0;
            }
        }

        return self::quick($a);
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
                . ' greater than 0 on all axes.');
        }

        $a = array_fill(0, $m, array_fill(0, $n, 0));

        return self::quick($a);
        
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
                . ' greater than 0 on all axes.');
        }

        $a = array_fill(0, $m, array_fill(0, $n, 1));
    
        return self::quick($a);
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

        if ($n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        foreach ($elements as $element) {
            if (!is_int($element) and !is_float($element)) {
                throw new InvalidArgumentException("Diagonal element"
                    . " must be an integer or float, "
                    . gettype($element) . " found.");
            }
        }

        $a = [];

        for ($i = 0; $i < $n; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][] = ($i === $j) ? $elements[$i] : 0;
            }
        }

        return self::quick($a);
    }

    /**
     * Fill a matrix with a given value at each element.
     *
     * @param  mixed  $value
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill($value, int $m, int $n) : self
    {
        if (!is_int($value) and !is_float($value)) {
            throw new InvalidArgumentException("Fill value must be an"
                . " integer or float, " . gettype($value) . " found.");
        }

        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        $a = array_fill(0, $m, array_fill(0, $n, $value));

        return self::quick($a);
    }

    /**
     * Return a random uniform matrix with values between 0 and 1.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function rand(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        $a = [];

        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][] = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            }
        }

        return self::quick($a);
    }

    /**
     * Return a standard normally distributed random matrix i.e values
     * between -1 and 1.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function gaussian(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        $a = $extras = []; 

        for ($i = 0; $i < $m; $i++) {
            $row = [];
            
            if (!empty($extras)) {
                $row[] = array_pop($extras);
            }

            for ($j = count($row); $j < $n; $j += 2) {
                $r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
                $r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;

                $r = sqrt(-2. * log($r1));

                $row[] = $r * sin($r2 * self::TWO_PI);
                $row[] = $r * cos($r2 * self::TWO_PI);
            }

            if (count($row) > $n) {
                $extras[] = array_pop($row);
            }

            $a[] = $row;
        }

        return self::quick($a);
    }

    /**
     * Return a uniform random matrix with mean 0 and unit variance.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function uniform(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        $a = [];

        for ($i = 0; $i < $m; $i++) {
            for ($j = 0; $j < $n; $j++) {
                $a[$i][] = rand(-PHP_INT_MAX, PHP_INT_MAX) / PHP_INT_MAX;
            }
        }

        return self::quick($a);
    }

        /**
     * Return the elementwise minimum of two matrices.
     *
     * @param  \Rubix\Tensor\Matrix  $a
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public static function minimum(Matrix $a, Matrix $b) : self
    {
        if ($a->m() !== $b->m()) {
            throw new DimensionalityMismatchException("Matrix A needs"
                . " {$a->m()} rows but Matrix B has {$b->m()}.");
        }

        if ($a->n() !== $b->n()) {
            throw new DimensionalityMismatchException("Matrix A needs"
                . " {$a->n()} columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($a as $i => $row) {
            $c[] = array_map('min', $row, $b[$i]);
        }

        return self::quick($c);
    }

    /**
     * Return the elementwise maximum of two matrices.
     *
     * @param  \Rubix\Tensor\Matrix  $a
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public static function maximum(Matrix $a, Matrix $b) : self
    {
        if ($a->m() !== $b->m()) {
            throw new DimensionalityMismatchException("Matrix A needs"
                . " {$a->m()} rows but Matrix B has {$b->m()}.");
        }

        if ($a->n() !== $b->n()) {
            throw new DimensionalityMismatchException("Matrix A needs"
                . " {$a->n()} columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($a as $i => $row) {
            $c[] = array_map('max', $row, $b[$i]);
        }

        return self::quick($c);
    }

    /**
     * Build a matrix from an array of row vectors.
     * 
     * @param  \Rubix\Tensor\Vector[]  $vectors
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fromVectors(array $vectors) : self
    {
        $a = [];

        foreach ($vectors as $vector) {
            if (!$vector instanceof Vector) {
                throw new InvalidArgumentException("Cannot build matrix"
                    . " from a non vector, " . gettype($vector)
                    . " found.");
            }

            $a[] = $vector->asArray();
        }

        return self::quick($a);
    }

    /**
     * @param  array  $a
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
                    throw new InvalidArgumentException("The number of columns"
                        . " must be equal for all rows, $n needed but"
                        . count($row) . " found.");
                }

                foreach ($row as $value) {
                    if (!is_int($value) and !is_float($value)) {
                        throw new InvalidArgumentException("Matrix element must"
                            . " be an integer or float, " . gettype($value)
                            . " found.");
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
     * @return (int|float)[]
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
        return Vector::quick($this->offsetGet($index));
    }

    /**
     * Return a column from the matrix.
     *
     * @param  int  $index
     * @return (int|float)[]
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
        return Vector::quick($this->column($index));
    }

    /**
     * Return the diagonal elements of a square matrix as a vector.
     * 
     * @throws \RuntimeException
     * @return \Rubix\Tensor\Vector
     */
    public function diagonalAsVector() : Vector
    {
        if ($this->m !== $this->n) {
            throw new RuntimeException('Cannot trace diagonal of a'
                . ' non square matrix.');
        }

        $b = [];

        for ($i = 0; $i < $this->m; $i++) {
            $b[] = $this->a[$i][$i];
        }

        return Vector::quick($b);
    }

    /**
     * Return the elements of the matrix in a 2-d array.
     *
     * @return array[]
     */
    public function asArray() : array
    {
        return $this->a;
    }

    /**
     * Return each row as a vector in an array.
     *
     * @return \Rubix\Tensor\Vector[]
     */
    public function asVectors() : array
    {
        $vectors = [];

        foreach ($this->a as $row) {
            $vectors[] = Vector::quick($row);
        }

        return $vectors;
    }

    /**
     * Flatten i.e unravel the matrix into a vector.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function flatten() : Vector
    {
        $b = [];

        foreach ($this->a as $row) {
            foreach ($row as $value) {
                $b[] = $value;
            }
        }

        return Vector::quick($b);
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

        return Vector::quick($b);
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

        return Vector::quick($b);
    }

    /**
     * Run a function over all of the elements in the matrix.
     *
     * @param  callable  $fn
     * @return self
     */
    public function map(callable $fn) : self
    {
        $validate = is_object($fn) ? true : false;

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
     * @param  mixed  $initial
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function reduce(callable $fn, $initial = 0)
    {
        if (!is_int($initial) and !is_float($initial)) {
            throw new InvalidArgumentException("Initial value must"
                . " be an integer or float, " . gettype($initial)
                . " found.");
        }

        $carry = $initial;

        foreach ($this->a as $row) {
            foreach ($row as $value) {
                $carry = $fn($value, $carry);
            }
        }

        return $carry;
    }

    /**
     * Transpose the matrix i.e row become columns and columns
     * become rows.
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
                $b[] = array_column($this->a, $i);
            }
        }

        return self::quick($b);
    }

    /**
     * Compute the inverse form of the matrix.
     * 
     * @return self
     */
    public function inverse() : self
    {
        $b = self::identity($this->m)
            ->augmentLeft($this)
            ->rref();

        $c = [];

        foreach ($b as $row) {
            $c[] = array_slice($row, $this->n);
        }

        return self::quick($c);
    }

    /**
     * Calculate the determinant of the matrix.
     * 
     * @throws \RuntimeException
     * @return int|float
     */
    public function det()
    {
        if ($this->m !== $this->n) {
            throw new RuntimeException('Determinant is undefined for a'
                . ' non square matrix.');
        }

        list($b, $swaps) = $this->ref();

        $pi = $b->diagonalAsVector()->product();

        return $pi * (-1.) ** $swaps;
    }

    /**
     * Return the trace of the matrix i.e the sum of all diagonal
     * elements of a square matrix.
     *
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function trace()
    {
        if ($this->m !== $this->n) {
            throw new InvalidArgumentException('Trace is undefined for a'
                . ' non square matrix.');
        }

        return $this->diagonalAsVector()->sum();
    }

    /**
     * Calculate the rank of the matrix i.e the number of pivots
     * in its reduced row echelon form.
     * 
     * @return int
     */
    public function rank() : int
    {
        $pivots = 0;

        foreach ($this->rref() as $row) {
            foreach ($row as $value) {
                if ($value != 0) {
                    $pivots++;

                    continue 2;
                }
            }
        }

        return $pivots;
    }

    /**
     * Multiply this matrix with another matrix (matrix-matrix product).
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public function matmul(Matrix $b) : self
    {
        if ($this->n !== $b->m()) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $bT = $b->transpose();

        $c = [[]];

        foreach ($this->a as $i => $row) {
            foreach ($bT as $column) {
                $sigma = 0;

                foreach ($row as $k => $value) {
                    $sigma += $value * $column[$k];
                }

                $c[$i][] = $sigma;
            }
        }

        return self::quick($c);
    }

    /**
     * Compute the dot product of this matrix and a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function dot(Vector $b) : self
    {
        if ($this->n !== $b->n()) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n rows but Vector B has {$b->n()}.");
        }

        return $this->matmul($b->asColumnMatrix());
    }

    /**
     * Calculate the row echelon form (REF) of the matrix using Gaussian
     * elimination. Return the matrix and the number of swaps in a tuple.
     * 
     * @throws \RuntimeException
     * @return array
     */
    public function ref() : array
    {
        $minDim = min($this->shape());

        $b = $this->a;

        $swaps = 0;

        for ($k = 0; $k < $minDim; $k++) {
            $index = $k;

            for ($i = $k; $i < $this->m; $i++) {
                if (abs($b[$i][$k]) > abs($b[$index][$k])) {
                    $index = $i;
                }
            } 

            if ($b[$index][$k] == 0) {
                throw new RuntimeException('Cannot compute row echelon form'
                    . ' of a singular matrix.');
            }

            if ($k !== $index) {
                $temp = $b[$k];

                $b[$k] = $b[$index];
                $b[$index] = $temp;

                $swaps++;
            }

            $diag = $b[$k][$k];

            for ($i = $k + 1; $i < $this->m; $i++) {
                $scale = $diag != 0 ? $b[$i][$k] / $diag : 1;
                
                for ($j = $k + 1; $j < $this->n; $j++) {
                    $b[$i][$j] -= $scale * $b[$k][$j];
                }
                
                $b[$i][$k] = 0;
            }
        }

        $b = self::quick($b);

        return [$b, $swaps];
    }

    /**
     * Return the reduced row echelon (RREF) form of the matrix.
     * 
     * @return self
     */
    public function rref() : self
    {
        list($b, $swaps) = $this->ref();

        $b = $b->asArray();

        $row = $col = 0;

        while ($row < $this->m and $col < $this->n) {
            if (abs($b[$row][$col]) == 0) {
                $col++;

                continue 1;
            }

            $divisor = $b[$row][$col];

            if ($divisor != 1) {
                for ($i = 0; $i < $this->n; $i++) {
                    $b[$row][$i] /= $divisor;
                }
            }

            for ($i = $row - 1; $i >= 0; $i--) {
                $scale = $b[$i][$col];

                if ($scale != 0) {
                    for ($j = 0; $j < $this->n; $j++) {
                        $b[$i][$j] += -$scale * $b[$row][$j];
                    }
                }
            }

            $row++;
            $col++;
        }

        return self::quick($b);
    }

    /**
     * Return the LU decomposition of the matrix in a tuple where l is
     * the lower triangular matrix, u is the upper triangular matrix,
     * and p is the permutation matrix.
     * 
     * @throws \RuntimeException
     * @return self[]
     */
    public function lu() : array
    {
        if ($this->m !== $this->n) {
            throw new RuntimeException('Cannot decompose a non square'
                . ' matrix.');
        }

        $pa = $this->a;

        $l = self::identity($this->n)->asArray();
        $u = self::zeros($this->n, $this->n)->asArray();

        for ($i = 0; $i < $this->n; $i++) {
            $max = $this->a[$i][$i];

            $row = $i;

            for ($j = $i; $j < $this->n; $j++) {
                if ($this->a[$j][$i] > $max) {
                    $max = $this->a[$j][$i];
                    
                    $row = $j;
                }
            }
            
            if ($i !== $row) {
                $temp = $pa[$i];

                $pa[$i] = $pa[$row];
                $pa[$row] = $temp;
            }
        }

        for ($i = 0; $i < $this->n; $i++) {
            for ($j = 0; $j <= $i; $j++) {
                $sigma = 0;

                for ($k = 0; $k < $j; $k++) {
                    $sigma += $u[$k][$i] * $l[$j][$k];
                }

                $u[$j][$i] = $pa[$j][$i] - $sigma;
            }

            for ($j = $i; $j < $this->n; $j++) {
                $sigma = 0;

                for ($k = 0; $k < $i; $k++) {
                    $sigma += $u[$k][$i] * $l[$j][$k];
                }

                $l[$j][$i] = ($pa[$j][$i] - $sigma)
                    / ($u[$i][$i] ?: self::EPSILON);
            }
        }

        $l = self::quick($l);
        $u = self::quick($u);

        return [$l, $u];
    }

    /**
     * Compute the eigenvalues and normalized eigenvectors of the matrix
     * and return them in a tuple.
     * 
     * @throws \RuntimeException
     * @return array
     */
    public function eig() : array
    {
        if ($this->m !== $this->n) {
            throw new RuntimeException('Cannot decompose a non square'
                . ' matrix.');
        }

        $b = new JAMA($this->a);

        $t = $b->eig();

        $values = $t->getRealEigenvalues();

        $v = self::quick($t->getV()->getArray());

        $norm = $v->transpose()->square()->sum()->sqrt();
    
        $vHat = $v->divide($norm);

        return [$values, $vHat];
    }

    /**
     * Return the L1 norm of the matrix.
     *
     * @return int|float
     */
    public function l1Norm()
    {
        return $this->transpose()->abs()->sum()->max();
    }

    /**
     * Return the L2 norm of the matrix.
     *
     * @return int|float
     */
    public function l2Norm()
    {
        return sqrt($this->square()->sum()->sum());
    }

    /**
     * Retrn the infinity norm of the matrix.
     *
     * @return int|float
     */
    public function infinityNorm()
    {
        return $this->abs()->sum()->max();
    }

    /**
     * Return the max norm of the matrix.
     *
     * @return int|float
     */
    public function maxNorm()
    {
        return $this->abs()->max()->max();
    }

    /**
     * A universal function to multiply this matrix with another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function multiply($b)
    {
        switch(true) {
            case $b instanceof Matrix:
                $c = $this->multiplyMatrix($b);
                break;
            
            case $b instanceof Vector:
                $c = $this->multiplyVector($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->multiplyScalar($b);
                break;

            default:
                throw new InvalidArgumentException("Cannot multiply matrix"
                    . " with a " . gettype($b) . ".");
        }

        return $c;
    }

    /**
     * A universal function to divide this matrix by another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide($b)
    {
        switch(true) {
            case $b instanceof Matrix:
                $c = $this->divideMatrix($b);
                break;
            
            case $b instanceof Vector:
                $c = $this->divideVector($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->divideScalar($b);
                break;

            default:
                throw new InvalidArgumentException("Cannot divide matrix"
                    . " with a " . gettype($b) . ".");
        }

        return $c;
    }

    /**
     * A universal function to add this matrix with another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add($b)
    {
        switch(true) {
            case $b instanceof Matrix:
                $c = $this->addMatrix($b);
                break;
            
            case $b instanceof Vector:
                $c = $this->addVector($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->addScalar($b);
                break;

            default:
                throw new InvalidArgumentException("Cannot add matrix"
                    . " to a " . gettype($b) . ".");
        }

        return $c;
    }

    /**
     * A universal function to subtract this matrix from another tensor
     * element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract($b)
    {
        switch(true) {
            case $b instanceof Matrix:
                $c = $this->subtractMatrix($b);
                break;
            
            case $b instanceof Vector:
                $c = $this->subtractVector($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->subtractScalar($b);
                break;

            default:
                throw new InvalidArgumentException("Cannot subtract a "
                    . gettype($b) . " from a matrix.");
        }

        return $c;
    }

    /**
     * A universal function to raise this matrix to the power of another
     * tensor element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow($b)
    {
        switch(true) {
            case $b instanceof Matrix:
                $c = $this->powMatrix($b);
                break;
            
            case $b instanceof Vector:
                $c = $this->powVector($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->powScalar($b);
                break;

            default:
                throw new InvalidArgumentException("Cannot raise matrix"
                    . " to the power of a " . gettype($b) . ".");
        }

        return $c;
    }

    /**
     * A universal function to compute the integer modulus of this matrix
     * and another tensor element-wise.
     *
     * @param  mixed  $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod($b)
    {
        switch(true) {
            case $b instanceof Matrix:
                $c = $this->modMatrix($b);
                break;
            
            case $b instanceof Vector:
                $c = $this->modVector($b);
                break;

            case is_int($b) or is_float($b):
                $c = $this->modScalar($b);
                break;

            default:
                throw new InvalidArgumentException("Cannot mod matrix"
                    . " with a " . gettype($b) . ".");
        }

        return $c;
    }

    /**
     * Return the element-wise reciprocal of the matrix.
     *
     * @return self
     */
    public function reciprocal() : self
    {
        return self::ones(...$this->shape())->divide($this);
    }

    /**
     * Return the absolute value of each element in the matrix.
     *
     * @return self
     */
    public function abs() : self
    {
        return $this->map('abs');
    }

    /**
     * Return the square of the matrix elementwise.
     *
     * @return self
     */
    public function square() : self
    {
        return $this->pow(2);
    }

    /**
     * Return the square root of the matrix.
     *
     * @return self
     */
    public function sqrt() : self
    {
        return $this->map('sqrt');
    }

    /**
     * Return the exponential of the matrix.
     *
     * @return self
     */
    public function exp() : self
    {
        return $this->map('exp');
    }

    /**
     * Return the logarithm of the matrix in specified base.
     *
     * @param  float  $base
     * @return self
     */
    public function log(float $base = M_E) : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = log($value, $base);
            }
        }

        return self::quick($b);
    }

    /**
     * Return the sine of the matrix.
     *
     * @return self
     */
    public function sin() : self
    {
        return $this->map('sin');
    }

    /**
     * Return the cosine of the matrix.
     *
     * @return self
     */
    public function cos() : self
    {
        return $this->map('cos');
    }

    /**
     * Return the tangent of the matrix.
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
     * Sum the rows of the matrix and return a vector.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function sum() : Vector
    {
        return Vector::quick(array_map('array_sum', $this->a));
    }

    /**
     * Calculate the row product of the matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function product() : Vector
    {
        return Vector::quick(array_map('array_product', $this->a));
    }

    /**
     * Return the minimum of each row in the matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function min() : Vector
    {
        return Vector::quick(array_map('min', $this->a));
    }

    /**
     * Return the maximum of each row in the matrix.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function max() : Vector
    {
        return Vector::quick(array_map('max', $this->a));
    }

    /**
     * Compute the means of each row and return them in a vector.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function mean() : Vector
    {
        return $this->sum()->divide($this->n);
    }

    /**
     * Return the median vector of this matrix.
     *
     * @throws \RuntimeException
     * @return \Rubix\Tensor\Vector
     */
    public function median() : Vector
    {
        if ($this->n < 1) {
            throw new RuntimeException('Median is not defined for matrices'
                . ' with less than 1 column.');
        }

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

        return Vector::quick($b);
    }

    /**
     * Compute the row variance of the matrix and return it in a tuple along
     * with the mean.
     *
     * @return \Rubix\Tensor\Vector
     */
    public function variance() : Vector
    {
        $mu = $this->transpose()->mean();

        return $this->subtract($mu)
            ->transpose()
            ->square()
            ->sum()
            ->divide($this->n);
    }

    /**
     * Compute the covariance of this matrix and return it in a tuple along with
     * the computed mean.
     *
     * @return self
     */
    public function covariance() : self
    {
        $mu = $this->transpose()->mean();

        $b = $this->subtract($mu)->transpose();

        return $b->matmul($b->transpose())
            ->divide($this->n);
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

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = round($value, $precision);
            }
        }

        return self::quick($b);
    }

    /**
     * Round the elements in the matrix down to the nearest integer.
     *
     * @return self
     */
    public function floor() : self
    {
        return $this->map('floor');
    }

    /**
     * Round the elements in the matrix up to the nearest integer.
     *
     * @return self
     */
    public function ceil() : self
    {
        return $this->map('ceil');;
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

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                if ($value > 0) {
                    $sign = 1;
                } else if ($value < 0) {
                    $sign = -1;
                } else {
                    $sign = 0;
                }

                $b[$i][] = $sign;
            }
        }

        return self::quick($b);
    }

    /**
     * Negate the matrix i.e take the negative of each value elementwise.
     *
     * @return self
     */
    public function negate() : self
    {
        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = -$value;
            }
        }

        return self::quick($b);
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

        $b = array_values($b);

        return self::quick($b);
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

        foreach ($b as &$row) {
            unset($row[$index]);

            $row = array_values($row);
        }

        return self::quick($b);
    }

    /**
     * Attach matrix b above this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public function augmentAbove(Matrix $b) : self
    {
        if ($this->m > 0 and $b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $b = array_merge($b->asArray(), $this->a);

        return self::quick($b);
    }

    /**
     * Attach matrix b below this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public function augmentBelow(Matrix $b) : self
    {
        if ($this->m > 0 and $b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $b = array_merge($this->a, $b->asArray());

        return self::quick($b);
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    public function augmentLeft(Matrix $b) : self
    {
        if ($this->m > 0 and $b->m() !== $this->m()) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m columns but Matrix B has {$b->m()}.");
        }

        $b = array_map('array_merge', $b->asArray(), $this->a);

        return self::quick($b);
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
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m columns but Matrix B has {$b->m()}.");
        }

        $b = array_map('array_merge', $this->a, $b->asArray());
        
        return self::quick($b);
    }

    /**
     * Repeat the matrix m times along the vertival axes and n times along the
     * horizontal axes.
     *
     * @param  int  $m
     * @param  int  $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public function repeat(int $m = 1, int $n = 1) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Cannot repeat less than 1'
                . ' row or column.');
        }

        $b = $this->a;

        $n -= 1;

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

        return self::quick($c);
    }

    /**
     * Return the element-wise product between this matrix and another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function multiplyMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][] = $value * $rowB[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Return the division of two elements, element-wise.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function divideMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][] = $value / $rowB[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Add this matrix together with another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function addMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][] = $value + $rowB[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Subtract a matrix from this matrix element-wise.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function subtractMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][] = $value - $rowB[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Raise this matrix to the power of the elementwise entry in another
     * matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function powMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][] = $value ** $rowB[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Calculate the modulus i.e remainder of division between this matri and
     * another matrix.
     *
     * @param  \Rubix\Tensor\Matrix  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function modMatrix(Matrix $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $rowA) {
            $rowB = $b[$i];

            foreach ($rowA as $j => $value) {
                $c[$i][] = $value % $rowB[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Multiply this matrix by a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function multiplyVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][] = $value * $b[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Divide this matrix by a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function divideVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][] = $value / $b[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Add this matrix by a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function addVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][] = $value + $b[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Subtract a vector from this matrix.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function subtractVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][] = $value - $b[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Raise this matrix to the power of a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function powVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][] = $value ** $b[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Calculate the modulus of this matrix with a vector.
     *
     * @param  \Rubix\Tensor\Vector  $b
     * @throws \Rubix\Tensor\Exceptions\DimensionalityMismatchException
     * @return self
     */
    protected function modVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new DimensionalityMismatchException("Matrix A requires"
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $c = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $j => $value) {
                $c[$i][] = $value % $b[$j];
            }
        }

        return self::quick($c);
    }

    /**
     * Multiply this matrix by a scalar.
     *
     * @param  mixed  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer"
                . " or float, " . gettype($scalar) . " found.");
        }

        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = $value * $scalar;
            }
        }

        return self::quick($b);
    }

    /**
     * Divide this matrix by a scalar.
     *
     * @param  mixed  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer"
                . " or float, " . gettype($scalar) . " found.");
        }

        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = $value / $scalar;
            }
        }

        return self::quick($b);
    }

    /**
     * Add this matrix by a scalar.
     *
     * @param  mixed  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer"
                . " or float, " . gettype($scalar) . " found.");
        }

        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = $value + $scalar;
            }
        }

        return self::quick($b);
    }

    /**
     * Subtract a scalar from this matrix.
     *
     * @param  mixed  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer"
                . " or float, " . gettype($scalar) . " found.");
        }

        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = $value - $scalar;
            }
        }

        return self::quick($b);
    }

    /**
     * Raise the matrix to a given scalar power.
     *
     * @param  mixed  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer"
                . " or float, " . gettype($scalar) . " found.");
        }

        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = $value ** $scalar;
            }
        }

        return self::quick($b);
    }

    /**
     * Calculate the modulus of this matrix with a scalar.
     *
     * @param  mixed  $scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modScalar($scalar) : self
    {
        if (!is_int($scalar) and !is_float($scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer"
                . " or float, " . gettype($scalar) . " found.");
        }

        $b = [];

        foreach ($this->a as $i => $row) {
            foreach ($row as $value) {
                $b[$i][] = $value % $scalar;
            }
        }

        return self::quick($b);
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
            throw new InvalidArgumentException("Element not found at"
                . " offset $index.");
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
        return trim(array_reduce($this->a, function ($carry, $row) {
            return $carry . PHP_EOL . '[ ' . implode(' ', $row) . ' ]';
        }, ''));
    }
}
