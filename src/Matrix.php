<?php

namespace Tensor;

use Tensor\Decompositions\LU;
use Tensor\Decompositions\REF;
use Tensor\Decompositions\RREF;
use Tensor\Decompositions\Eigen;
use Tensor\Decompositions\Cholesky;
use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;
use Exception;
use Closure;

use function count;
use function is_null;

use const Tensor\EPSILON;
use const Tensor\TWO_PI;

/**
 * Matrix
 *
 * A two dimensional (rank 2) tensor with integer and/or floating point elements.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Matrix implements Tensor
{
    /**
     * A 2-dimensional sequential array that holds the values of the matrix.
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
     * @param mixed[] $a
     * @return self
     */
    public static function build(array $a = []) : self
    {
        return new self($a, true);
    }

    /**
     * Build a new matrix foregoing any validation for quicker instantiation.
     *
     * @param mixed[] $a
     * @return self
     */
    public static function quick(array $a = []) : self
    {
        return new self($a, false);
    }

    /**
     * Return an identity matrix with the given dimensions.
     *
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function identity(int $n) : self
    {
        if ($n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        $a = [];

        for ($i = 0; $i < $n; ++$i) {
            $rowA = [];

            for ($j = 0; $j < $n; ++$j) {
                $rowA[] = $i === $j ? 1 : 0;
            }

            $a[] = $rowA;
        }

        return self::quick($a);
    }

    /**
     * Return a zero matrix with the given dimensions.
     *
     * @param int $m
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function zeros(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        return self::fill(0, $m, $n);
    }

    /**
     * Return a one matrix with the given dimensions.
     *
     * @param int $m
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function ones(int $m, int $n) : self
    {
        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }
    
        return self::fill(1, $m, $n);
    }

    /**
     * Build a diagonal matrix with the value of each element along the
     * diagonal and 0s everywhere else.
     *
     * @param mixed[] $elements
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
                throw new InvalidArgumentException('Diagonal element'
                    . ' must be an integer or float, '
                    . gettype($element) . ' found.');
            }
        }

        $a = [];

        for ($i = 0; $i < $n; ++$i) {
            $rowA = [];

            for ($j = 0; $j < $n; ++$j) {
                $rowA[] = $i === $j ? $elements[$i] : 0;
            }

            $a[] = $rowA;
        }

        return self::quick($a);
    }

    /**
     * Fill a matrix with a given value at each element.
     *
     * @param mixed $value
     * @param int $m
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill($value, int $m, int $n) : self
    {
        if (!is_int($value) and !is_float($value)) {
            throw new InvalidArgumentException('Fill value must be an'
                . ' integer or float, ' . gettype($value) . ' found.');
        }

        if ($m < 1 or $n < 1) {
            throw new InvalidArgumentException('Dimensionality must be'
                . ' greater than 0 on all axes.');
        }

        return self::quick(array_fill(0, $m, array_fill(0, $n, $value)));
    }

    /**
     * Return a random uniform matrix with values between 0 and 1.
     *
     * @param int $m
     * @param int $n
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

        while (count($a) < $m) {
            $rowA = [];

            while (count($rowA) < $n) {
                $rowA[] = rand(0, PHP_INT_MAX)
                    / PHP_INT_MAX;
            }

            $a[] = $rowA;
        }

        return self::quick($a);
    }

    /**
     * Return a standard normally distributed random matrix i.e values
     * between -1 and 1.
     *
     * @param int $m
     * @param int $n
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

        while (count($a) < $m) {
            $rowA = [];
            
            if ($extras) {
                $rowA[] = array_pop($extras);
            }

            while (count($rowA) < $n) {
                $r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
                $r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;

                $r = sqrt(-2. * log($r1));

                $phi = $r2 * TWO_PI;

                $rowA[] = $r * sin($phi);
                $rowA[] = $r * cos($phi);
            }

            if (count($rowA) > $n) {
                $extras[] = array_pop($rowA);
            }

            $a[] = $rowA;
        }

        return self::quick($a);
    }

    /**
     * Generate a m x n matrix with elements from a Poisson distribution.
     *
     * @param int $m
     * @param int $n
     * @param float $lambda
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function poisson(int $m, int $n, float $lambda = 1.) : self
    {
        $l = exp(-$lambda);

        $a = [];

        while (count($a) < $m) {
            $rowA = [];

            while (count($rowA) < $n) {
                $k = 0;
                $p = 1.;

                while ($p > $l) {
                    ++$k;
                    
                    $p *= rand(0, PHP_INT_MAX)
                        / PHP_INT_MAX;
                }

                $rowA[] = $k - 1;
            }

            $a[] = $rowA;
        }

        return self::quick($a);
    }

    /**
     * Return a uniform random matrix with mean 0 and unit variance.
     *
     * @param int $m
     * @param int $n
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

        while (count($a) < $m) {
            $rowA = [];

            while (count($rowA) < $n) {
                $rowA[] = rand(-PHP_INT_MAX, PHP_INT_MAX)
                    / PHP_INT_MAX;
            }

            $a[] = $rowA;
        }

        return self::quick($a);
    }

    /**
     * Return the elementwise minimum of two matrices.
     *
     * @param \Tensor\Matrix $a
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function minimum(Matrix $a, Matrix $b) : self
    {
        if ($a->m() !== $b->m()) {
            throw new InvalidArgumentException('Matrix A needs'
                . " {$a->m()} rows but Matrix B has {$b->m()}.");
        }

        if ($a->n() !== $b->n()) {
            throw new InvalidArgumentException('Matrix A needs'
                . " {$a->n()} columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($a as $i => $rowA) {
            $c[] = array_map('min', $rowA, $b[$i]);
        }

        return self::quick($c);
    }

    /**
     * Return the elementwise maximum of two matrices.
     *
     * @param \Tensor\Matrix $a
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function maximum(Matrix $a, Matrix $b) : self
    {
        if ($a->m() !== $b->m()) {
            throw new InvalidArgumentException('Matrix A needs'
                . " {$a->m()} rows but Matrix B has {$b->m()}.");
        }

        if ($a->n() !== $b->n()) {
            throw new InvalidArgumentException('Matrix A needs'
                . " {$a->n()} columns but Matrix B has {$b->n()}.");
        }

        $c = [];

        foreach ($a as $i => $rowA) {
            $c[] = array_map('max', $rowA, $b[$i]);
        }

        return self::quick($c);
    }

    /**
     * Build a matrix by stacking an array of vectors.
     *
     * @param mixed[] $vectors
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function stack(array $vectors) : self
    {
        if (empty($vectors)) {
            return self::quick();
        }

        $proto = reset($vectors);

        $size = $proto instanceof Vector ? $proto->size() : 0;

        $columnwise = $proto instanceof ColumnVector;

        $a = [];

        foreach ($vectors as $vector) {
            if (!$vector instanceof Vector) {
                throw new InvalidArgumentException('Cannot stack a non'
                    . ' vector, ' . gettype($vector) . ' found.');
            }

            if ($columnwise and !$vector instanceof ColumnVector) {
                throw new InvalidArgumentException('Cannot stack a non'
                    . ' column vector, ' . gettype($vector) . ' found.');
            }

            if ($vector->size() !== $size) {
                throw new InvalidArgumentException('Vectors must all'
                    . ' be the same size.');
            }

            $a[] = $vector->asArray();
        }

        $a = self::quick($a);

        return $columnwise ? $a->transpose() : $a;
    }

    /**
     * @param mixed[] $a
     * @param bool $validate
     * @throws \InvalidArgumentException
     */
    public function __construct(array $a = [], bool $validate = true)
    {
        $m = count($a);

        $n = is_array(current($a)) ? count(current($a)) : 1;
        $n = $m === 0 ? 0 : $n;

        if ($validate) {
            $a = array_values($a);

            foreach ($a as &$row) {
                $row = is_array($row) ? array_values($row) : [$row];

                if (count($row) !== $n) {
                    throw new InvalidArgumentException('The number of columns'
                        . ' must be equal for all rows, $n needed but '
                        . count($row) . ' found.');
                }

                foreach ($row as $value) {
                    if (!is_int($value) and !is_float($value)) {
                        throw new InvalidArgumentException('Matrix element must'
                            . ' be an integer or float, ' . gettype($value)
                            . ' found.');
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
     * Return the shape of the tensor as a string.
     *
     * @return string
     */
    public function shapeString() : string
    {
        return (string) $this->m . ' x ' . (string) $this->n;
    }

    /**
     * Is this a square matrix?
     *
     * @return bool
     */
    public function isSquare() : bool
    {
        return $this->m === $this->n;
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
     * @param int $index
     * @return (int|float)[]
     */
    public function row(int $index) : array
    {
        return $this->offsetGet($index);
    }

    /**
     * Return a row as a vector from the matrix.
     *
     * @param int $index
     * @return \Tensor\Vector
     */
    public function rowAsVector(int $index) : Vector
    {
        return Vector::quick($this->offsetGet($index));
    }

    /**
     * Return a column from the matrix.
     *
     * @param int $index
     * @return (int|float)[]
     */
    public function column(int $index) : array
    {
        return array_column($this->a, $index);
    }

    /**
     * Return a column as a vector from the matrix.
     *
     * @param int $index
     * @return \Tensor\ColumnVector
     */
    public function columnAsVector(int $index) : ColumnVector
    {
        return ColumnVector::quick($this->column($index));
    }

    /**
     * Return the diagonal elements of a square matrix as a vector.
     *
     * @throws \RuntimeException
     * @return \Tensor\Vector
     */
    public function diagonalAsVector() : Vector
    {
        if (!$this->isSquare()) {
            throw new RuntimeException('Cannot trace diagonal of a'
                . ' non square matrix.');
        }

        $b = [];

        foreach ($this->a as $i => $rowA) {
            $b[] = $rowA[$i];
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
     * @return \Tensor\Vector[]
     */
    public function asVectors() : array
    {
        return array_map([Vector::class, 'quick'], $this->a);
    }

    /**
     * Return each column as a column vector in an array.
     *
     * @return \Tensor\ColumnVector[]
     */
    public function asColumnVectors() : array
    {
        $vectors = [];

        for ($i = 0; $i < $this->n; ++$i) {
            $vectors[] = $this->columnAsVector($i);
        }

        return $vectors;
    }

    /**
     * Flatten i.e unravel the matrix into a vector.
     *
     * @return \Tensor\Vector
     */
    public function flatten() : Vector
    {
        return Vector::quick(array_reduce($this->a, 'array_merge', []));
    }

    /**
     * Return the index of the minimum element in every row of the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function argmin() : ColumnVector
    {
        $b = [];

        foreach ($this->a as $rowA) {
            $b[] = (int) array_search(min($rowA), $rowA);
        }

        return ColumnVector::quick($b);
    }

    /**
     * Return the index of the maximum element in every row of the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function argmax() : ColumnVector
    {
        $b = [];

        foreach ($this->a as $rowA) {
            $b[] = (int) array_search(max($rowA), $rowA);
        }

        return ColumnVector::quick($b);
    }

    /**
     * Run a function over all of the elements in the matrix.
     *
     * @param callable $callback
     * @return self
     */
    public function map(callable $callback) : self
    {
        $validate = $callback instanceof Closure;

        $b = [];

        foreach ($this->a as $rowA) {
            $b[] = array_map($callback, $rowA);
        }

        return new self($b, $validate);
    }

    /**
     * Reduce the matrix down to a scalar.
     *
     * @param callable $callback
     * @param mixed $initial
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function reduce(callable $callback, $initial = 0)
    {
        if (!is_int($initial) and !is_float($initial)) {
            throw new InvalidArgumentException('Initial value must'
                . ' be an integer or float, ' . gettype($initial)
                . ' found.');
        }

        $carry = $initial;

        foreach ($this->a as $rowA) {
            foreach ($rowA as $valueA) {
                $carry = $callback($valueA, $carry);
            }
        }

        return $carry;
    }

    /**
     * Transpose the matrix i.e row become columns and columns become rows.
     *
     * @return self
     */
    public function transpose() : self
    {
        if ($this->m > 1) {
            return self::quick(array_map(null, ...$this->a));
        }
        
        $b = [];

        for ($i = 0; $i < $this->n; ++$i) {
            $b[] = array_column($this->a, $i);
        }

        return self::quick($b);
    }

    /**
     * Compute the inverse of the matrix.
     *
     * @return self
     */
    public function inverse() : self
    {
        $b = self::identity($this->m)
            ->augmentLeft($this)
            ->rref();

        $c = [];

        foreach ($b as $rowB) {
            $c[] = array_slice($rowB, $this->n);
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
        if (!$this->isSquare()) {
            throw new RuntimeException('Determinant is undefined'
                . ' for a non square matrix.');
        }

        [$b, $swaps] = $this->ref();

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
        if (!$this->isSquare()) {
            throw new InvalidArgumentException('Trace is undefined'
                . ' for a non square matrix.');
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
        $b = $this->rref();

        $pivots = 0;

        foreach ($b as $rowB) {
            foreach ($rowB as $valueB) {
                if ($valueB != 0) {
                    ++$pivots;

                    continue 2;
                }
            }
        }

        return $pivots;
    }

    /**
     * Is the matrix full rank?
     *
     * @return bool
     */
    public function fullRank() : bool
    {
        return $this->rank() === min($this->shape());
    }

    /**
     * Is the matrix symmetric i.e. is it equal to its own transpose?
     *
     * @return bool
     */
    public function symmetric() : bool
    {
        if (!$this->isSquare()) {
            return false;
        }

        for ($i = 0; $i < $this->m - 1; ++$i) {
            $rowA = $this->a[$i];

            for ($j = $i + 1; $j < $this->n; ++$j) {
                if ($rowA[$j] != $this->a[$j][$i]) {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * Is the matrix positive definite i.e. do all of its principal
     * minor matrices have a determinant greater than 0.
     *
     * @return bool
     */
    public function positiveDefinite() : bool
    {
        if (!$this->symmetric()) {
            return false;
        }

        for ($i = 1; $i <= $this->n; ++$i) {
            $b = $this->subMatrix(0, $i);

            if ($b->det() <= 0) {
                return false;
            }
        }

        return true;
    }

    /**
     * Is the matrix positive semidefinite i.e. do all of its principal
     * minor matrices have a determinant greater or equal to 0.
     *
     * @return bool
     */
    public function positiveSemidefinite() : bool
    {
        if (!$this->symmetric()) {
            return false;
        }

        for ($i = 1; $i <= $this->n; ++$i) {
            $b = $this->subMatrix(0, $i);

            if ($b->det() < 0) {
                return false;
            }
        }

        return true;
    }

    /**
     * Multiply this matrix with another matrix (matrix-matrix product).
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function matmul(Matrix $b) : self
    {
        if ($this->n !== $b->m()) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n rows but Matrix B has {$b->m()}.");
        }

        $p = $b->n();

        $bT = $b->transpose()->asArray();
        
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            for ($j = 0; $j < $p; ++$j) {
                $columnB = $bT[$j];
                
                $sigma = 0;

                foreach ($rowA as $k => $valueA) {
                    $sigma += $valueA * $columnB[$k];
                }

                $rowC[] = $sigma;
            }

            $c[] = $rowC;
        }
        
        return self::quick($c);
    }

    /**
     * Compute the dot product of this matrix and a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return \Tensor\ColumnVector
     */
    public function dot(Vector $b) : ColumnVector
    {
        if ($this->n !== $b->size()) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n elements but Vector B has {$b->size()}.");
        }

        return $this->matmul($b->asColumnMatrix())->columnAsVector(0);
    }

    /**
     * Convolve this matrix with another matrix.
     *
     * @param \Tensor\Matrix $b
     * @param int $stride
     * @throws \InvalidArgumentException
     * @return self
     */
    public function convolve(Matrix $b, int $stride = 1) : self
    {
        [$m, $n] = $b->shape();

        if ($m > $this->m or $n > $this->n) {
            throw new InvalidArgumentException('Matrix B cannot be'
                . ' larger than Matrix A.');
        }

        if ($stride < 1) {
            throw new InvalidArgumentException('Stride cannot be'
                . " less than 1, $stride given.");
        }

        $b = $b->asArray();

        $p = intdiv($m, 2);
        $q = intdiv($n, 2);

        $c = [];

        for ($i = 0; $i < $this->m; $i += $stride) {
            $rowC = [];

            for ($j = 0; $j < $this->n; $j += $stride) {
                $sigma = 0;

                foreach ($b as $k => $rowB) {
                    $x = $i + $p - (int) $k;

                    if ($x < 0 or $x >= $this->m) {
                        continue 1;
                    }

                    $rowA = $this->a[$x];

                    foreach ($rowB as $l => $valueB) {
                        $y = $j + $q - (int) $l;

                        if ($y < 0 or $y >= $this->n) {
                            continue 1;
                        }

                        $sigma += $rowA[$y] * $valueB;
                    }
                }

                $rowC[] = $sigma;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Calculate the row echelon form (REF) of the matrix. Return the reduced
     * matrix and the number of swaps needed to compute the REF.
     *
     * @return mixed[]
     */
    public function ref() : array
    {
        $ref = REF::decompose($this);

        return [
            $ref->a(),
            $ref->swaps(),
        ];
    }

    /**
     * Return the reduced row echelon (RREF) form of the matrix. Return the
     * reduced matrix and the number of swaps needed to compute the RREF.
     *
     * @return self
     */
    public function rref() : self
    {
        return RREF::decompose($this)->a();
    }

    /**
     * Return the LU decomposition of the matrix.
     *
     * @throws \RuntimeException
     * @return self[]
     */
    public function lu() : array
    {
        $lup = LU::decompose($this);

        return [
            $lup->l(),
            $lup->u(),
            $lup->p(),
        ];
    }

    /**
     * Return the lower triangular matrix of the Cholesky decomposition.
     *
     * @return self
     */
    public function cholesky() : self
    {
        return Cholesky::decompose($this)->l();
    }

    /**
     * Compute the eigenvalues and eigenvectors of the matrix and return
     * them in a tuple.
     *
     * @param bool $normalize
     * @return mixed[]
     */
    public function eig(bool $normalize = true) : array
    {
        $eig = Eigen::decompose($this);

        $eigenvectors = $eig->eigenvectors();
        $eigenvalues = $eig->eigenvalues();

        if ($normalize) {
            $norm = $eigenvectors
                ->transpose()
                ->square()
                ->sum()
                ->sqrt();
        
            $eigenvectors = $eigenvectors
                ->divide($norm->transpose());
        }

        return [$eigenvalues, $eigenvectors];
    }

    /**
     * Solve a linear system of equations given the matrix and a
     * solution vector b. Returns the column vector x that satisfies
     * the solution.
     *
     * @param \Tensor\Vector $b
     * @return \Tensor\ColumnVector
     */
    public function solve(Vector $b) : ColumnVector
    {
        [$l, $u, $p] = $this->lu();

        $k = $this->m - 1;

        $pb = $p->dot($b);

        $y = [$pb[0] / ($l[0][0] ?: EPSILON)];

        for ($i = 1; $i < $this->m; ++$i) {
            $sigma = 0;

            for ($j = 0; $j <= $i - 1; ++$j) {
                $sigma += $l[$i][$j] * $y[$j];
            }

            $y[] = ($pb[$i] - $sigma)
                / $l[$i][$i];
        }

        $x = [$k => $y[$k] / ($l[$k][$k] ?: EPSILON)];

        for ($i = $this->m - 2; $i >= 0; --$i) {
            $sigma = 0;

            for ($j = $i + 1; $j < $this->m; ++$j) {
                $sigma += $u[$i][$j] * $x[$j];
            }

            $x[$i] = ($y[$i] - $sigma)
                / $u[$i][$i];
        }

        return ColumnVector::quick(array_reverse($x));
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
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function multiply($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->multiplyMatrix($b);

            case $b instanceof ColumnVector:
                return $this->multiplyColumnVector($b);
            
            case $b instanceof Vector:
                return $this->multiplyVector($b);

            case is_int($b) or is_float($b):
                return $this->multiplyScalar($b);

            default:
                throw new InvalidArgumentException('Cannot multiply matrix'
                    . ' by a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to divide this matrix by another tensor
     * element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->divideMatrix($b);

            case $b instanceof ColumnVector:
                return $this->divideColumnVector($b);
            
            case $b instanceof Vector:
                return $this->divideVector($b);

            case is_int($b) or is_float($b):
                return $this->divideScalar($b);

            default:
                throw new InvalidArgumentException('Cannot divide matrix'
                    . ' with a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to add this matrix with another tensor
     * element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->addMatrix($b);

            case $b instanceof ColumnVector:
                return $this->addColumnVector($b);
            
            case $b instanceof Vector:
                return $this->addVector($b);

            case is_int($b) or is_float($b):
                return $this->addScalar($b);

            default:
                throw new InvalidArgumentException('Cannot add matrix'
                    . ' with a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to subtract this matrix from another tensor
     * element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->subtractMatrix($b);

            case $b instanceof ColumnVector:
                return $this->subtractColumnVector($b);
                
            case $b instanceof Vector:
                return $this->subtractVector($b);

            case is_int($b) or is_float($b):
                return $this->subtractScalar($b);

            default:
                throw new InvalidArgumentException('Cannot subtract a '
                    . gettype($b) . ' from a matrix.');
        }
    }

    /**
     * A universal function to raise this matrix to the power of another
     * tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->powMatrix($b);

            case $b instanceof ColumnVector:
                return $this->powColumnVector($b);
            
            case $b instanceof Vector:
                return $this->powVector($b);

            case is_int($b) or is_float($b):
                return $this->powScalar($b);

            default:
                throw new InvalidArgumentException('Cannot raise matrix'
                    . ' to the power of a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the integer modulus of this matrix
     * and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->modMatrix($b);
            
            case $b instanceof ColumnVector:
                return $this->modColumnVector($b);
            
            case $b instanceof Vector:
                return $this->modVector($b);

            case is_int($b) or is_float($b):
                return $this->modScalar($b);

            default:
                throw new InvalidArgumentException('Cannot mod matrix'
                    . ' with a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the equality comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function equal($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->equalMatrix($b);

            case $b instanceof ColumnVector:
                return $this->equalColumnVector($b);

            case $b instanceof Vector:
                return $this->equalVector($b);

            case is_int($b) or is_float($b):
                return $this->equalScalar($b);

            default:
                throw new InvalidArgumentException('Cannot compare matrix'
                    . ' to a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the not equal comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function notEqual($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->notEqualMatrix($b);

            case $b instanceof ColumnVector:
                return $this->notEqualColumnVector($b);

            case $b instanceof Vector:
                return $this->notEqualVector($b);

            case is_int($b) or is_float($b):
                return $this->notEqualScalar($b);

            default:
                throw new InvalidArgumentException('Cannot compare matrix'
                    . ' to a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the greater than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greater($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->greaterMatrix($b);

            case $b instanceof ColumnVector:
                return $this->greaterColumnVector($b);

            case $b instanceof Vector:
                return $this->greaterVector($b);

            case is_int($b) or is_float($b):
                return $this->greaterScalar($b);

            default:
                throw new InvalidArgumentException('Cannot compare matrix'
                    . ' to a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the greater than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greaterEqual($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->greaterEqualMatrix($b);

            case $b instanceof ColumnVector:
                return $this->greaterEqualColumnVector($b);

            case $b instanceof Vector:
                return $this->greaterEqualVector($b);

            case is_int($b) or is_float($b):
                return $this->greaterEqualScalar($b);

            default:
                throw new InvalidArgumentException('Cannot compare matrix'
                    . ' to a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the less than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function less($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->lessMatrix($b);
            
            case $b instanceof ColumnVector:
                return $this->lessColumnVector($b);

            case $b instanceof Vector:
                return $this->lessVector($b);

            case is_int($b) or is_float($b):
                return $this->lessScalar($b);

            default:
                throw new InvalidArgumentException('Cannot compare matrix'
                    . ' to a ' . gettype($b) . '.');
        }
    }

    /**
     * A universal function to compute the less than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed $b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function lessEqual($b)
    {
        switch (true) {
            case $b instanceof Matrix:
                return $this->lessEqualMatrix($b);

            case $b instanceof ColumnVector:
                return $this->lessEqualColumnVector($b);
            
            case $b instanceof Vector:
                return $this->lessEqualVector($b);

            case is_int($b) or is_float($b):
                return $this->lessEqualScalar($b);

            default:
                throw new InvalidArgumentException('Cannot compare matrix'
                    . ' to a ' . gettype($b) . '.');
        }
    }

    /**
     * Return the element-wise reciprocal of the matrix.
     *
     * @return self
     */
    public function reciprocal() : self
    {
        return self::ones(...$this->shape())
            ->divideMatrix($this);
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
        return $this->multiply($this);
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
     * Return the exponential of the tensor minus 1.
     *
     * @return mixed
     */
    public function expm1()
    {
        return $this->map('expm1');
    }

    /**
     * Return the logarithm of the matrix in specified base.
     *
     * @param float $base
     * @return self
     */
    public function log(float $base = M_E) : self
    {
        $b = [];

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                $rowB[] = log($valueA, $base);
            }

            $b[] = $rowB;
        }

        return self::quick($b);
    }

    /**
     * Return the log of 1 plus the tensor i.e. a transform.
     *
     * @return self
     */
    public function log1p() : self
    {
        return $this->map('log1p');
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
     * Compute the arc sine of the matrix.
     *
     * @return self
     */
    public function asin() : self
    {
        return $this->map('asin');
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
     * Compute the arc cosine of the matrix.
     *
     * @return self
     */
    public function acos() : self
    {
        return $this->map('acos');
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
     * Compute the arc tangent of the matrix.
     *
     * @return self
     */
    public function atan() : self
    {
        return $this->map('atan');
    }

    /**
     * Convert angles from radians to degrees.
     *
     * @return self
     */
    public function rad2deg() : self
    {
        return $this->map('rad2deg');
    }

    /**
     * Convert angles from degrees to radians.
     *
     * @return self
     */
    public function deg2rad() : self
    {
        return $this->map('deg2rad');
    }

    /**
     * Sum the rows of the matrix and return a vector.
     *
     * @return \Tensor\ColumnVector
     */
    public function sum() : ColumnVector
    {
        return ColumnVector::quick(array_map('array_sum', $this->a));
    }

    /**
     * Calculate the row product of the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function product() : ColumnVector
    {
        return ColumnVector::quick(array_map('array_product', $this->a));
    }

    /**
     * Return the minimum of each row in the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function min() : ColumnVector
    {
        return ColumnVector::quick(array_map('min', $this->a));
    }

    /**
     * Return the maximum of each row in the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function max() : ColumnVector
    {
        return ColumnVector::quick(array_map('max', $this->a));
    }

    /**
     * Compute the means of each row and return them in a vector.
     *
     * @throws \InvalidArgumentException
     * @return \Tensor\ColumnVector
     */
    public function mean() : ColumnVector
    {
        if ($this->n < 1) {
            throw new RuntimeException('Mean is not defined for'
                . ' matrices with less than 1 column.');
        }

        return $this->sum()->divide($this->n);
    }

    /**
     * Return the median vector of this matrix.
     *
     * @throws \RuntimeException
     * @return \Tensor\ColumnVector
     */
    public function median() : ColumnVector
    {
        if ($this->n < 1) {
            throw new RuntimeException('Median is not defined for'
                . ' matrices with less than 1 column.');
        }

        $b = [];

        foreach ($this->a as $rowA) {
            $mid = intdiv($this->n, 2);

            sort($rowA);

            if ($this->n % 2 === 1) {
                $median = $rowA[$mid];
            } else {
                $median = ($rowA[$mid - 1] + $rowA[$mid]) / 2.;
            }

            $b[] = $median;
        }

        return ColumnVector::quick($b);
    }

    /**
     * Return a percentile vector of this matrix.
     *
     * @param float $p
     * @throws \InvalidArgumentException
     * @throws \RuntimeException
     * @return \Tensor\ColumnVector
     */
    public function percentile(float $p) : ColumnVector
    {
        if ($p < 0. or $p > 100.) {
            throw new InvalidArgumentException('P must be between 0 and 100,'
                . " $p given.");
        }

        if ($this->n < 1) {
            throw new RuntimeException('Percentile is not defined for matrices'
                . ' with less than 1 column.');
        }

        $b = [];

        foreach ($this->a as $rowA) {
            sort($rowA);

            $x = ($p / 100) * ($this->n - 1) + 1;

            $xHat = (int) $x;
    
            $remainder = $x - $xHat;
    
            $t = $rowA[$xHat - 1];
    
            $b[] = $t + $remainder * ($rowA[$xHat] - $t);
        }

        return ColumnVector::quick($b);
    }

    /**
     * Compute the row variance of the matrix.
     *
     * @param mixed $mean
     * @throws \InvalidArgumentException
     * @return \Tensor\ColumnVector
     */
    public function variance($mean = null) : ColumnVector
    {
        if (isset($mean)) {
            if (!$mean instanceof ColumnVector) {
                throw new InvalidArgumentException('Mean must be a'
                . ' column vector ' . gettype($mean) . ' given.');
            }

            if ($mean->m() !== $this->m) {
                throw new InvalidArgumentException('Mean vector must'
                    . " have $this->m rows, {$mean->m()} given.");
            }
        }

        if (is_null($mean)) {
            $mean = $this->mean();
        }

        return $this->subtract($mean)
            ->square()
            ->sum()
            ->divide($this->m);
    }

    /**
     * Compute the empirical covariance of this matrix and return it in a tuple
     * along with the computed mean.
     *
     * @return self
     */
    public function covariance() : self
    {
        $b = $this->subtract($this->mean());

        return $b->matmul($b->transpose())
            ->divide($this->m);
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

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                $rowB[] = round($valueA, $precision);
            }

            $b[] = $rowB;
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
        return $this->map('ceil');
    }

    /**
     * Clip the elements in the matrix to be between given minimum and maximum
     * and return a new matrix.
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

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                if ($valueA > $max) {
                    $rowB[] = $max;

                    continue 1;
                }

                if ($valueA < $min) {
                    $rowB[] = $min;

                    continue 1;
                }

                $rowB[] = $valueA;
            }

            $b[] = $rowB;
        }

        return self::quick($b);
    }

    /**
     * Clip the tensor to be lower bounded by a given minimum.
     *
     * @param float $min
     * @return self
     */
    public function clipLower(float $min) : self
    {
        $b = [];

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                if ($valueA < $min) {
                    $rowB[] = $min;

                    continue 1;
                }

                $rowB[] = $valueA;
            }

            $b[] = $rowB;
        }

        return self::quick($b);
    }

    /**
     * Clip the tensor to be upper bounded by a given maximum.
     *
     * @param float $max
     * @return self
     */
    public function clipUpper(float $max) : self
    {
        $b = [];

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                if ($valueA > $max) {
                    $rowB[] = $max;

                    continue 1;
                }

                $rowB[] = $valueA;
            }

            $b[] = $rowB;
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

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                if ($valueA > 0) {
                    $rowB[] = 1;
                } elseif ($valueA < 0) {
                    $rowB[] = -1;
                } else {
                    $rowB[] = 0;
                }
            }

            $b[] = $rowB;
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

        foreach ($this->a as $rowA) {
            $rowB = [];

            foreach ($rowA as $valueA) {
                $rowB[] = -$valueA;
            }

            $b[] = $rowB;
        }

        return self::quick($b);
    }

    /**
     * Return the square submatrix starting at an offset on the diagonal
     * and excluding the last n rows and columns.
     *
     * @param int $offset
     * @param int $n
     * @throws InvalidArgumentException
     * @return self
     */
    public function subMatrix(int $offset = 0, int $n = 1) : self
    {
        if ($offset < 0) {
            throw new InvalidArgumentException(' Offset cannot be less'
                . " than 0, $offset given.");
        }

        if ($n < 0) {
            throw new InvalidArgumentException('N cannot be less than'
                . " 0, $n given.");
        }

        $last = $offset + $n;

        if ($last > $this->m or $last > $this->n) {
            throw new InvalidArgumentException('Sub matrix is out of'
                . ' bounds of matrix A.');
        }

        $k = $this->n - $n;

        $b = [];

        for ($i = $offset; $i < $k; ++$i) {
            $rowA = $this->a[$i];

            $rowB = [];

            for ($j = $offset; $j < $k; ++$j) {
                $rowB[] = $rowA[$j];
            }

            $b[] = $rowB;
        }

        return self::quick($b);
    }

    /**
     * Attach matrix b above this matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentAbove(Matrix $b) : self
    {
        if ($this->m > 0 and $b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        return self::quick(array_merge($b->asArray(), $this->a));
    }

    /**
     * Attach matrix b below this matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentBelow(Matrix $b) : self
    {
        if ($this->m > 0 and $b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Matrix B has {$b->n()}.");
        }

        return self::quick(array_merge($this->a, $b->asArray()));
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentLeft(Matrix $b) : self
    {
        if ($this->m > 0 and $b->m() !== $this->m()) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m rows but Matrix B has {$b->m()}.");
        }

        return self::quick(array_map('array_merge', $b->asArray(), $this->a));
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentRight(Matrix $b) : self
    {
        if ($this->m > 0 and $b->m() !== $this->m()) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m rows but Matrix B has {$b->m()}.");
        }
        
        return self::quick(array_map('array_merge', $this->a, $b->asArray()));
    }

    /**
     * Repeat the matrix m times along the vertival axes and n times along the
     * horizontal axes.
     *
     * @param int $m
     * @param int $n
     * @throws \InvalidArgumentException
     * @return self
     */
    public function repeat(int $m, int $n) : self
    {
        $b = $this->a;

        if ($n > 0) {
            foreach ($this->a as $i => $rowA) {
                for ($j = 0; $j < $n; ++$j) {
                    $b[$i] = array_merge($b[$i], $rowA);
                }
            }
        }

        $c = $b;

        for ($i = 0; $i < $m; ++$i) {
            $c = array_merge($c, $b);
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise product between this matrix and another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA * $rowB[$j];
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the division of two elements, element-wise.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA / $rowB[$j];
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Add this matrix together with another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA + $rowB[$j];
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Subtract a matrix from this matrix element-wise.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA - $rowB[$j];
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Raise this matrix to the power of the elementwise entry in another
     * matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA ** $rowB[$j];
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Calculate the modulus i.e remainder of division between this matri and
     * another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA % $rowB[$j];
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and
     * another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA == $rowB[$j] ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and
     * another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA != $rowB[$j] ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix
     * and another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA > $rowB[$j] ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA >= $rowB[$j] ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this matrix
     * and another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA < $rowB[$j] ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and another matrix.
     *
     * @param \Tensor\Matrix $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualMatrix(Matrix $b) : self
    {
        if ($b->shape() !== $this->shape()) {
            throw new InvalidArgumentException(
                "{$this->shapeString()}"
                . " matrix needed but {$b->shapeString()} given."
            );
        }

        $c = [];

        foreach ($b->asArray() as $i => $rowB) {
            $rowA = $this->a[$i];

            $rowC = [];

            foreach ($rowA as $j => $valueA) {
                $rowC[] = $valueA <= $rowB[$j] ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Multiply this matrix by a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] * $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Divide this matrix by a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] / $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Add this matrix by a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] + $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Subtract a vector from this matrix.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] - $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Raise this matrix to the power of a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] ** $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Calculate the modulus of this matrix with a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] % $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a
     * vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function equalVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] == $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a
     * vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function notEqualVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] != $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix
     * and a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function greaterVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] > $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function greaterEqualVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] >= $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this matrix
     * and a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function lessVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] < $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a vector.
     *
     * @param \Tensor\Vector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function lessEqualVector(Vector $b) : self
    {
        if ($b->n() !== $this->n) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->n columns but Vector B has {$b->n()}.");
        }

        $b = $b->asArray();

        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($b as $j => $valueB) {
                $rowC[] = $rowA[$j] <= $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Multiply this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m rows but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA * $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Divide this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA / $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Add this matrix to a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA + $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Subtract a column vector from this matrix.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA - $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Raise this matrix to the power of a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA ** $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Mod this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA % $valueB;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA == $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA != $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA > $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA >= $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA < $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualColumnVector(ColumnVector $b) : self
    {
        if ($b->m() !== $this->m) {
            throw new InvalidArgumentException('Matrix A requires'
                . " $this->m row but Vector B has {$b->m()}.");
        }

        $c = [];

        foreach ($b->asArray() as $i => $valueB) {
            $rowA = $this->a[$i];
            
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA <= $valueB ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Multiply this matrix by a scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA * $b;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Divide this matrix by a scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA / $b;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Add this matrix by a scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA + $b;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Subtract a scalar from this matrix.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA - $b;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Raise the matrix to a given scalar power.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA ** $b;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Calculate the modulus of this matrix with a scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA % $b;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a
     * scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA == $b ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a
     * scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA != $b ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and a
     * scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA > $b ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA >= $b ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and a
     * scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA < $b ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a scalar.
     *
     * @param int|float $b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualScalar($b) : self
    {
        $c = [];

        foreach ($this->a as $rowA) {
            $rowC = [];

            foreach ($rowA as $valueA) {
                $rowC[] = $valueA <= $b ? 1 : 0;
            }

            $c[] = $rowC;
        }

        return self::quick($c);
    }

    /**
     * @return int
     */
    public function count() : int
    {
        return $this->size();
    }

    /**
     * @param mixed $index
     * @param (int|float)[] $values
     * @throws \RuntimeException
     */
    public function offsetSet($index, $values) : void
    {
        throw new RuntimeException('Matrix cannot be mutated directly.');
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
        throw new RuntimeException('Matrix cannot be mutated directly.');
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param mixed $index
     * @throws \InvalidArgumentException
     * @return (int|float)[]
     */
    public function offsetGet($index) : array
    {
        if (isset($this->a[$index])) {
            return $this->a[$index];
        }

        throw new InvalidArgumentException('Element not found at'
            . " offset $index.");
    }

    /**
     * Get an iterator for the rows in the matrix.
     *
     * @return \ArrayIterator<int, array>
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
        return trim(array_reduce($this->a, [self::class, 'implodeRow'], ''));
    }

    /**
     * Implode a row of the matrix and return the output.
     *
     * @param string $carry
     * @param (int|float)[] $row
     * @return string
     */
    protected static function implodeRow(string $carry, array $row) : string
    {
        return $carry . PHP_EOL . '[ ' . implode(' ', $row) . ' ]';
    }
}
