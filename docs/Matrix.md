# Matrix

A two dimensional (rank 2) tensor with integer and/or floating point elements.

- **Namespace:** `Tensor\Matrix`
- **Implements:** `Tensor` — i.e. `ArrayLike`, `Arithmetic`, `Comparable`, `Algebraic`, `Trigonometric`, `Statistical`, `Special`
- **Also implements:** `ArrayAccess`, `IteratorAggregate`, `Countable`

## Overview

`Matrix` stores its elements in a 2-dimensional sequential array of rows, exposed as `list<list<float>>`. It is **immutable**: mutating methods return new instances, and `offsetSet()` / `offsetUnset()` throw `Tensor\Exceptions\RuntimeException`.

Interface methods are implemented by Matrices with **row-wise** semantics:

- Reductions (`sum`, `product`, `min`, `max`, `mean`, `median`, `quantile`, `variance`) operate on each row and return a `ColumnVector`.
- Element-wise functions return a new `Matrix` of the same shape.

## Constructors & Factories

### `__construct(array $a, bool $validate = true)`

Instantiate a matrix directly.

- **Parameters:**
  - `$a` — the 2-dimensional element array `array<array<int|float>>`
  - `$validate` — whether to validate rectangularity and cast elements to floats (default `true`)
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if rows have unequal column counts
- **Note:** Prefer the factory methods below.

### `Matrix::build(array $a = []) : Matrix`

Factory method to build a new matrix from an array, running validation.

### `Matrix::quick(array $a = []) : Matrix`

Build a new matrix foregoing any validation for quicker instantiation.

### `Matrix::identity(int $n) : Matrix`

Return an identity matrix with the given dimensions.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Matrix::zeros(int $m, int $n) : Matrix`

Return a zero matrix with the given dimensions.

### `Matrix::ones(int $m, int $n) : Matrix`

Return a one matrix with the given dimensions.

### `Matrix::diagonal(array $elements) : Matrix`

Build a diagonal matrix with the value of each element along the diagonal and 0s everywhere else.

- **Parameters:** `$elements` — `float[]` of diagonal values

### `Matrix::fill(float $value, int $m, int $n) : Matrix`

Fill a matrix with a given value at each element.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$m < 1` or `$n < 1`

### `Matrix::rand(int $m, int $n) : Matrix`

Return a random uniform matrix with values between 0 and 1.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$m < 1` or `$n < 1`

### `Matrix::gaussian(int $m, int $n) : Matrix`

Return a standard normally distributed random matrix, i.e. values between -1 and 1.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$m < 1` or `$n < 1`

### `Matrix::poisson(int $m, int $n, float $lambda = 1.0) : Matrix`

Generate an m x n matrix with elements from a Poisson distribution.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$m < 1` or `$n < 1`

### `Matrix::uniform(int $m, int $n) : Matrix`

Return a uniform random matrix with mean 0 and unit variance.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$m < 1` or `$n < 1`

## Structure & Accessors

### `shape() : array`

Return a tuple with the dimensionality of the tensor.

- **Returns:** `array{int<0,max>,int<0,max>}` — e.g. `[2, 3]`

### `shapeString() : string`

Return the shape of the tensor as a string.

- **Returns:** `string` — e.g. `"2 x 3"`

### `isSquare() : bool`

Is this a square matrix (`m === n`)?

### `size() : int`

Return the number of elements in the tensor (`m * n`).

### `m() : int`

Return the number of rows in the matrix.

### `n() : int`

Return the number of columns in the matrix.

### `rowAsVector(int $index) : Vector`

Return a row as a vector from the matrix.

### `columnAsVector(int $index) : ColumnVector`

Return a column as a vector from the matrix.

### `diagonalAsVector() : Vector`

Return the diagonal elements of a square matrix as a vector.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if the matrix is not square

### `asArray() : array`

Return the elements of the matrix in a 2-d array.

- **Returns:** `list<list<float>>`

### `asVectors() : array`

Return each row as a vector in an array.

- **Returns:** `Vector[]`

### `asColumnVectors() : array`

Return each column as a column vector in an array.

- **Returns:** `ColumnVector[]`

### `flatten() : Vector`

Flatten, i.e. unravel, the matrix into a vector.

- **Returns:** `Vector` of length `size()`

### `map(callable $callback) : Matrix`

Run a function over all of the elements in the matrix.

- **Returns:** a new `Matrix` of the same shape

### `reduce(callable $callback, float $initial = 0.0) : float`

Reduce the matrix down to a scalar.

- **Parameters:** `$callback` — `function (float $carry, float $value): float`, `$initial` — the initial carry (default `0.0`)
- **Returns:** `float`

### `transpose() : Matrix`

Transpose the matrix, i.e. rows become columns and columns become rows.

## Linear Algebra

### `inverse() : Matrix`

Compute the inverse of the matrix.

- **Throws:** `Tensor\Exceptions\RuntimeException` if the matrix is singular (surfacing from the row echelon reduction)

### `pseudoinverse() : Matrix`

Compute the (Moore-Penrose) pseudo inverse of the general matrix.

- **Note:** Not implemented in the pure-PHP library — throws `Tensor\Exceptions\NotImplemented`. Available when the extension is loaded.

### `det() : float`

Calculate the determinant of the matrix.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if the matrix is not square

### `trace() : float`

Return the trace of the matrix, i.e. the sum of all diagonal elements of a square matrix.

### `rank() : int`

Calculate the rank of the matrix, i.e. the number of pivots in its reduced row echelon form.

### `fullRank() : bool`

Is the matrix full rank (`rank() === min(shape())`)?

### `symmetric() : bool`

Is the matrix symmetric, i.e. is it equal to its own transpose?

### `matmul(Matrix $b) : Matrix`

Multiply this matrix with another matrix (matrix-matrix product).

- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if `$this->n !== $b->m()`

### `dot(Vector $b) : ColumnVector`

Compute the dot product of this matrix and a vector.

- **Returns:** `ColumnVector` (product of `$this` and `$b` reshaped as a column matrix)
- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if `$this->n !== $b->size()`

### `convolve(Matrix $b, int $stride = 1) : Matrix`

Return the 2D convolution of this matrix and a kernel matrix with the given stride, using the "same" method for zero padding.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$b` is larger than this matrix or `$stride < 1`

### `ref() : REF`

Calculate the row echelon form (REF) of the matrix.

- **Returns:** [`Tensor\Reductions\REF`](reductions/ref.md)

### `rref() : RREF`

Return the reduced row echelon (RREF) form of the matrix.

- **Returns:** [`Tensor\Reductions\RREF`](reductions/rref.md)

### `lu() : LU`

Return the LU decomposition of the matrix.

- **Returns:** [`Tensor\Decompositions\LU`](decompositions/lu.md)

### `cholesky() : Cholesky`

Return the lower triangular matrix of the Cholesky decomposition.

- **Returns:** [`Tensor\Decompositions\Cholesky`](decompositions/cholesky.md)

### `eig(bool $symmetric = false) : Eigen`

Compute the eigenvalues and eigenvectors of the matrix.

- **Parameters:** `$symmetric` — whether the matrix is known to be symmetric (default `false`)
- **Returns:** [`Tensor\Decompositions\Eigen`](decompositions/eigen.md)
- **Note:** Not implemented in the pure-PHP library — throws `Tensor\Exceptions\NotImplemented`. Available when the extension is loaded.

### `svd() : SVD`

Return the singular value decomposition (SVD) of the matrix.

- **Returns:** [`Tensor\Decompositions\SVD`](decompositions/svd.md)
- **Note:** Not implemented in the pure-PHP library — throws `Tensor\Exceptions\NotImplemented`. Available when the extension is loaded.

### `augmentAbove(Matrix $b) : Matrix`

Attach matrix `$b` above this matrix.

- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if column counts differ

### `augmentBelow(Matrix $b) : Matrix`

Attach matrix `$b` below this matrix.

- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if column counts differ

### `augmentLeft(Matrix $b) : Matrix`

Attach matrix `$b` to the left of this matrix.

- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if row counts differ

### `augmentRight(Matrix $b) : Matrix`

Attach matrix `$b` to the right of this matrix.

- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if row counts differ

### `repeat(int $m, int $n) : Matrix`

Repeat the matrix `$m` times along the vertical axis and `$n` times along the horizontal axis.

## Norms

- `l1Norm() : float` — the L1 norm of the matrix
- `l2Norm() : float` — the L2 norm of the matrix
- `infinityNorm() : float` — the infinity norm of the matrix
- `maxNorm() : float` — the max norm of the matrix

## Universal Arithmetic Functions

These dispatch on the operand type (see [Arithmetic](interfaces/arithmetic.md)). `*` is one of `multiply`, `divide`, `add`, `subtract`, `pow`, `mod`.

### `*($b) : mixed`

- **Parameters:** `$b` — a `float`, `int`, `Vector`, `ColumnVector`, or `Matrix`
- **Returns:** a `Matrix` of the same shape (scalar, vector, or column-vector operands) or the element-wise result (matrix operands)
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` for unsupported types, `Tensor\Exceptions\DimensionalityMismatch` for shape mismatches

## Universal Comparison Functions

These dispatch on the operand type (see [Comparable](interfaces/comparable.md)). `*` is one of `equal`, `notEqual`, `greater`, `greaterEqual`, `less`, `lessEqual`.

### `*($b) : mixed`

- **Parameters:** `$b` — a `float`, `int`, `Vector`, `ColumnVector`, or `Matrix`
- **Returns:** a `Matrix` of `1`/`0` elements
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` for unsupported types, `Tensor\Exceptions\DimensionalityMismatch` for shape mismatches

## Element-Wise Operations With a Matrix

`*` is one of the operations below; every method requires both matrices to share the same shape, returns a new `Matrix`, and throws `Tensor\Exceptions\DimensionalityMismatch` otherwise.

- `multiplyMatrix(Matrix $b) : self` — element-wise product of two matrices
- `divideMatrix(Matrix $b) : self` — division of two elements, element-wise
- `addMatrix(Matrix $b) : self` — add this matrix together with another matrix
- `subtractMatrix(Matrix $b) : self` — subtract a matrix from this matrix element-wise
- `powMatrix(Matrix $b) : self` — raise this matrix to the power of the element-wise entry in another matrix
- `modMatrix(Matrix $b) : self` — modulus (remainder of division) between this matrix and another matrix
- `equalMatrix(Matrix $b) : self` — element-wise equality comparison
- `notEqualMatrix(Matrix $b) : self` — element-wise not-equal comparison
- `greaterMatrix(Matrix $b) : self` — element-wise greater-than comparison
- `greaterEqualMatrix(Matrix $b) : self` — element-wise greater-than-or-equal comparison
- `lessMatrix(Matrix $b) : self` — element-wise less-than comparison
- `lessEqualMatrix(Matrix $b) : self` — element-wise less-than-or-equal comparison

## Element-Wise Operations With a Vector

The vector is broadcast along the columns of the matrix. `*` is one of the operations below; every method requires `$b->n() === $this->n`, returns a new `Matrix`, and throws `Tensor\Exceptions\DimensionalityMismatch` otherwise.

- `multiplyVector(Vector $b) : self` — multiply this matrix by a vector
- `divideVector(Vector $b) : self` — divide this matrix by a vector
- `addVector(Vector $b) : self` — add this matrix by a vector
- `subtractVector(Vector $b) : self` — subtract a vector from this matrix
- `powVector(Vector $b) : self` — raise this matrix to the power of a vector
- `modVector(Vector $b) : self` — modulus of this matrix with a vector
- `equalVector(Vector $b) : self` — element-wise equality comparison
- `notEqualVector(Vector $b) : self` — element-wise not-equal comparison
- `greaterVector(Vector $b) : self` — element-wise greater-than comparison
- `greaterEqualVector(Vector $b) : self` — element-wise greater-than-or-equal comparison
- `lessVector(Vector $b) : self` — element-wise less-than comparison
- `lessEqualVector(Vector $b) : self` — element-wise less-than-or-equal comparison

## Element-Wise Operations With a ColumnVector

The column vector is broadcast along the rows of the matrix. `*` is one of the operations below; every method requires `$b->m() === $this->m`, returns a new `Matrix`, and throws `Tensor\Exceptions\DimensionalityMismatch` otherwise.

- `multiplyColumnVector(ColumnVector $b) : self` — multiply this matrix with a column vector
- `divideColumnVector(ColumnVector $b) : self` — divide this matrix with a column vector
- `addColumnVector(ColumnVector $b) : self` — add this matrix to a column vector
- `subtractColumnVector(ColumnVector $b) : self` — subtract a column vector from this matrix
- `powColumnVector(ColumnVector $b) : self` — raise this matrix to the power of a column vector
- `modColumnVector(ColumnVector $b) : self` — mod this matrix with a column vector
- `equalColumnVector(ColumnVector $b) : self` — element-wise equality comparison
- `notEqualColumnVector(ColumnVector $b) : self` — element-wise not-equal comparison
- `greaterColumnVector(ColumnVector $b) : self` — element-wise greater-than comparison
- `greaterEqualColumnVector(ColumnVector $b) : self` — element-wise greater-than-or-equal comparison
- `lessColumnVector(ColumnVector $b) : self` — element-wise less-than comparison
- `lessEqualColumnVector(ColumnVector $b) : self` — element-wise less-than-or-equal comparison

## Element-Wise Operations With a Scalar

`*` is one of the operations below; every method returns a new `Matrix`.

- `multiplyScalar(float $b) : self` — multiply this matrix by a scalar
- `divideScalar(float $b) : self` — divide this matrix by a scalar
- `addScalar(float $b) : self` — add this matrix by a scalar
- `subtractScalar(float $b) : self` — subtract a scalar from this matrix
- `powScalar(float $b) : self` — raise the matrix to a given scalar power
- `modScalar(float $b) : self` — modulus of this matrix with a scalar
- `equalScalar(float $b) : self` — element-wise equality comparison
- `notEqualScalar(float $b) : self` — element-wise not-equal comparison
- `greaterScalar(float $b) : self` — element-wise greater-than comparison
- `greaterEqualScalar(float $b) : self` — element-wise greater-than-or-equal comparison
- `lessScalar(float $b) : self` — element-wise less-than comparison
- `lessEqualScalar(float $b) : self` — element-wise less-than-or-equal comparison

## Algebraic

See [Algebraic](interfaces/algebraic.md). Each method returns a new `Matrix`.

- `abs() : self` — absolute value of each element
- `square() : self` — square of the matrix element-wise
- `sqrt() : self` — square root of the matrix
- `reciprocal() : self` — element-wise reciprocal of the matrix
- `exp() : self` — exponential of the matrix
- `expm1() : self` — exponential of each element minus 1
- `log(float $base = M_E) : self` — logarithm of the matrix in the specified base
- `log1p() : self` — log of 1 plus each element
- `round(int $precision = 0) : self` — round the elements to a given decimal place (throws `InvalidArgumentException` if `$precision < 0`)
- `floor() : self` — round down to the nearest integer
- `ceil() : self` — round up to the nearest integer
- `sign() : self` — element-wise sign indication (`1.0`, `-1.0`, `0.0`)
- `negate() : self` — take the negative of each value element-wise

## Trigonometric

See [Trigonometric](interfaces/trigonometric.md). Each method returns a new `Matrix`.

- `sin()` — sine of the matrix
- `asin()` — arc sine of the matrix
- `cos()` — cosine of the matrix
- `acos()` — arc cosine of the matrix
- `tan()` — tangent of the matrix
- `atan()` — arc tangent of the matrix
- `rad2deg()` — convert angles from radians to degrees
- `deg2rad()` — convert angles from degrees to radians

## Statistical & Reductions

See [Statistical](interfaces/statistical.md) and [Special](interfaces/special.md). For a `Matrix`, row-wise reductions return a `ColumnVector`.

- `sum() : ColumnVector` — sum the rows of the matrix
- `product() : ColumnVector` — calculate the row product of the matrix
- `min() : ColumnVector` — minimum of each row
- `max() : ColumnVector` — maximum of each row
- `mean() : ColumnVector` — means of each row
- `median() : ColumnVector` — median vector of this matrix
- `quantile(float $q) : ColumnVector` — q'th quantile of each row (throws `InvalidArgumentException` if `$q` is outside `[0, 1]`)
- `variance($mean = null) : ColumnVector` — row variance of the matrix; `$mean` optionally provides a pre-computed mean `ColumnVector` (throws `DimensionalityMismatch` if `$mean->m() !== $this->m`)
- `covariance(?ColumnVector $mean = null) : self` — compute the covariance matrix (throws `DimensionalityMismatch` if `$mean->m() !== $this->m`)

## Clipping

- `clip(float $min, float $max) : self` — clip the elements between the given minimum and maximum (throws `InvalidArgumentException` if `$min > $max`)
- `clipLower(float $min) : self` — clip the tensor to be lower bounded by a given minimum
- `clipUpper(float $max) : self` — clip the tensor to be upper bounded by a given maximum

## Array Access

The matrix is a read-only, zero-indexed array of its **rows**, each returned as a `Vector`.

```
$matrix[int $index] : Vector
```

- `offsetGet($index) : Vector` — return the row at the given offset as a `Vector`; throws `InvalidArgumentException` if the offset does not exist
- `offsetExists($index) : bool` — does the given offset exist?
- `offsetSet($index, $values) : void` — **throws** `Tensor\Exceptions\RuntimeException` (matrices are immutable)
- `offsetUnset($index) : void` — **throws** `Tensor\Exceptions\RuntimeException` (matrices are immutable)
- `count() : int` — returns `size()`
- `getIterator() : Traversable` — iterate over the rows (`Generator<int, Vector>`)