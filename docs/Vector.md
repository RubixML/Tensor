# Vector

A one dimensional (rank 1) tensor with integer and/or floating point elements.

- **Namespace:** `Tensor\Vector`
- **Implements:** `Tensor` — i.e. `ArrayLike`, `Arithmetic`, `Comparable`, `Algebraic`, `Trigonometric`, `Statistical`, `Special`
- **Also implements:** `ArrayAccess`, `IteratorAggregate`, `Countable`

## Overview

`Vector` stores its elements in a sequential, zero-indexed array that is exposed as `list<float>`. It is **immutable**: mutating methods return new instances, and `offsetSet()` / `offsetUnset()` throw `Tensor\Exceptions\RuntimeException`.

Interface methods are implemented by Vectors with scalar-level semantics — reductions such as `sum()`, `mean()`, and `min()` return a `float`, and element-wise functions return a new `Vector` of the same length.

## Constructors & Factories

### `__construct(array $a, bool $validate = true)`

Instantiate a vector directly.

- **Parameters:**
  - `$a` — the 1-dimensional element array `(int|float)[]`
  - `$validate` — whether to validate and cast elements to floats (default `true`)
- **Note:** Prefer the factory methods below.

### `Vector::build(array $a = [])`

Factory method to build a new vector from an array, running validation.

- **Parameters:** `$a` — `(int|float)[]`
- **Returns:** `mixed` (a `Vector`/`static`)

### `Vector::quick(array $a = [])`

Build a vector foregoing any validation for quicker instantiation.

- **Parameters:** `$a` — `(int|float)[]`
- **Returns:** `mixed` (a `Vector`/`static`)

### `Vector::zeros(int $n) : Vector`

Build a vector of `n` zeros.

- **Parameters:** `$n` — the number of elements
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::ones(int $n) : Vector`

Build a vector of `n` ones.

- **Parameters:** `$n` — the number of elements
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::fill(float $value, int $n) : Vector`

Fill a vector with a given value.

- **Parameters:** `$value` — the fill value, `$n` — the number of elements
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::rand(int $n) : Vector`

Return a random uniform vector with values between 0 and 1.

- **Parameters:** `$n` — the number of elements
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::gaussian(int $n) : Vector`

Return a standard normally distributed (Gaussian) random vector with mean 0 and unit variance.

- **Parameters:** `$n` — the number of elements
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::poisson(int $n, float $lambda = 1.0) : Vector`

Generate a vector with `n` elements from a Poisson distribution.

- **Parameters:** `$n` — the number of elements, `$lambda` — rate parameter (default `1.0`)
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::uniform(int $n) : Vector`

Return a uniform random vector with mean 0 and unit variance.

- **Parameters:** `$n` — the number of elements
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$n < 1`

### `Vector::range(float $start, float $end, float $interval = 1.0) : Vector`

Return evenly spaced values within a given interval.

- **Parameters:** `$start`, `$end` — the interval bounds, `$interval` — the step (default `1.0`)
- **Returns:** `Vector`

### `Vector::linspace(float $min, float $max, int $n) : Vector`

Return a vector of `n` evenly spaced numbers between minimum and maximum.

- **Parameters:** `$min`, `$max` — the interval bounds, `$n` — the element count
- **Returns:** `Vector`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$min > $max` or `$n < 2`

## Structure & Accessors

### `shape() : array`

Return a tuple with the dimensionality of the tensor.

- **Returns:** `array{int<0,max>}` — e.g. `[3]`

### `shapeString() : string`

Return the shape of the tensor as a string.

- **Returns:** `string` — e.g. `"3"`

### `size() : int`

Return the number of elements in the vector.

### `m() : int`

Return the number of rows in the vector. Always `1`.

### `n() : int`

Return the number of columns in the vector. Equals `size()`.

### `asArray() : array`

Return the vector as an array.

- **Returns:** `list<float>`

### `asRowMatrix() : Matrix`

Return this vector as a 1 x n row matrix.

### `asColumnMatrix() : Matrix`

Return this vector as an n x 1 column matrix.

### `reshape(int $m, int $n) : Matrix`

Return a matrix in the shape specified, filled from the vector's elements.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$m * $n` does not equal the vector size

### `transpose() : mixed`

Transpose the vector, i.e. rotate it into a `ColumnVector`.

- **Returns:** `ColumnVector`

### `convolve(Vector $b, int $stride = 1) : Vector`

Return the 1D convolution of this vector and a kernel vector with the given stride.

- **Parameters:** `$b` — the kernel vector, `$stride` — the stride (default `1`)
- **Returns:** `Vector` of length `n + nB - 1` (sampled by stride)
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$b` is larger than this vector or `$stride < 1`

### `count() : int`

Count method to implement the `Countable` interface. Returns `size()`.

## Higher-Order Functions

### `map(callable $callback) : Vector`

Map a function over the elements in the vector and return a new vector.

### `reduce(callable $callback, float $initial = 0.0) : float`

Reduce the vector down to a scalar.

- **Parameters:** `$callback` — `function (float $carry, float $value): float`, `$initial` — the initial carry (default `0.0`)
- **Returns:** `float`

## Linear Algebra & Geometry

### `dot(Vector $b) : float`

Compute the dot product of this vector and another vector.

- **Throws:** `Tensor\Exceptions\DimensionalityMismatch` if sizes differ

### `matmul(Matrix $b) : Matrix`

Compute the vector-matrix product of this vector and matrix `$b`. This is equivalent to multiplying the vector reshaped as a row matrix.

- **Returns:** `Matrix`

### `inner(Vector $b) : float`

Return the inner product of two vectors. Equivalent to `dot()`.

### `outer(Vector $b) : Matrix`

Calculate the outer product of this and another vector.

- **Returns:** `Matrix` of shape `n x nB`

### `l1Norm() : float`

Calculate the L1 or Manhattan norm of the vector.

### `l2Norm() : float`

Calculate the L2 or Euclidean norm of the vector.

### `pNorm(float $p = 3.0) : float`

Calculate the p-norm of the vector.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$p <= 0`

### `maxNorm() : float`

Calculate the max norm of the vector.

## Universal Arithmetic Functions

These dispatch on the operand type (see [Arithmetic](interfaces/arithmetic.md)). `*` is one of `multiply`, `divide`, `add`, `subtract`, `pow`, `mod`.

### `*($b) : mixed`

- **Parameters:** `$b` — a `float`, `int`, `Vector`, or `Matrix`
- **Returns:** a `Vector` (vector/scalar operands) or `Matrix` (matrix operand)
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` for unsupported types, `Tensor\Exceptions\DimensionalityMismatch` for size mismatches

## Universal Comparison Functions

These dispatch on the operand type (see [Comparable](interfaces/comparable.md)). `*` is one of `equal`, `notEqual`, `greater`, `greaterEqual`, `less`, `lessEqual`.

- **Parameters:** `$b` — a `float`, `int`, `Vector`, or `Matrix`
- **Returns:** a `Vector` or `Matrix` of `1`/`0` elements
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` for unsupported types, `Tensor\Exceptions\DimensionalityMismatch` for size mismatches

## Element-Wise Operations With a Matrix

The vector is applied to each row of the matrix, broadcasting along columns. `*` is one of the operations below; every method returns a `Matrix` and throws `Tensor\Exceptions\DimensionalityMismatch` if `$b->n() !== $this->n`.

- `multiplyMatrix(Matrix $b) : Matrix` — multiply this vector with a matrix
- `divideMatrix(Matrix $b) : Matrix` — divide this vector with a matrix
- `addMatrix(Matrix $b) : Matrix` — add this vector to a matrix
- `subtractMatrix(Matrix $b) : Matrix` — subtract a matrix from this vector
- `powMatrix(Matrix $b) : Matrix` — raise this vector to the power of a matrix
- `modMatrix(Matrix $b) : Matrix` — mod this vector with a matrix
- `equalMatrix(Matrix $b) : Matrix` — element-wise equality comparison
- `notEqualMatrix(Matrix $b) : Matrix` — element-wise not-equal comparison
- `greaterMatrix(Matrix $b) : Matrix` — element-wise greater-than comparison
- `greaterEqualMatrix(Matrix $b) : Matrix` — element-wise greater-than-or-equal comparison
- `lessMatrix(Matrix $b) : Matrix` — element-wise less-than comparison
- `lessEqualMatrix(Matrix $b) : Matrix` — element-wise less-than-or-equal comparison

## Element-Wise Operations With a Vector

`*` is one of the operations below; every method requires equal sizes, returns a new `Vector` (`static`), and throws `Tensor\Exceptions\DimensionalityMismatch` otherwise.

- `multiplyVector(Vector $b) : self` — multiply this vector with another vector
- `divideVector(Vector $b) : self` — divide this vector by another vector
- `addVector(Vector $b) : self` — add this vector to another vector
- `subtractVector(Vector $b) : self` — subtract a vector from this vector
- `powVector(Vector $b) : self` — raise this vector to the power of another vector
- `modVector(Vector $b) : self` — modulus of this vector with another vector, element-wise
- `equalVector(Vector $b) : self` — element-wise equality comparison
- `notEqualVector(Vector $b) : self` — element-wise not-equal comparison
- `greaterVector(Vector $b) : self` — element-wise greater-than comparison
- `greaterEqualVector(Vector $b) : self` — element-wise greater-than-or-equal comparison
- `lessVector(Vector $b) : self` — element-wise less-than comparison
- `lessEqualVector(Vector $b) : self` — element-wise less-than-or-equal comparison

## Element-Wise Operations With a Scalar

`*` is one of the operations below; every method returns a new `Vector` (`static`).

- `multiplyScalar(float $b) : self` — multiply this vector by a scalar
- `divideScalar(float $b) : self` — divide this vector by a scalar
- `addScalar(float $b) : self` — add a scalar to this vector
- `subtractScalar(float $b) : self` — subtract a scalar from this vector
- `powScalar(float $b) : self` — raise this vector to the power of a scalar
- `modScalar(float $b) : self` — modulus of this vector with a scalar
- `equalScalar(float $b) : self` — element-wise equality comparison
- `notEqualScalar(float $b) : self` — element-wise not-equal comparison
- `greaterScalar(float $b) : self` — element-wise greater-than comparison
- `greaterEqualScalar(float $b) : self` — element-wise greater-than-or-equal comparison
- `lessScalar(float $b) : self` — element-wise less-than comparison
- `lessEqualScalar(float $b) : self` — element-wise less-than-or-equal comparison

## Algebraic

See [Algebraic](interfaces/algebraic.md). Each method returns a new `Vector`.

- `abs() : self` — absolute value of the vector
- `square() : self` — square the vector
- `sqrt() : self` — square root of the vector
- `reciprocal() : self` — element-wise reciprocal of the vector
- `exp() : self` — exponentiate each element
- `expm1() : self` — exponential of each element minus 1
- `log(float $base = M_E) : self` — log to the given base of each element
- `log1p() : self` — log of 1 plus each element
- `round(int $precision = 0) : self` — round the elements to a given decimal place (throws `InvalidArgumentException` if `$precision < 0`)
- `floor() : self` — round down to the nearest integer
- `ceil() : self` — round up to the nearest integer
- `sign() : self` — element-wise sign indication (`1.0`, `-1.0`, `0.0`)
- `negate() : self` — negate each value

## Trigonometric

See [Trigonometric](interfaces/trigonometric.md). Each method returns a new `Vector`.

- `sin()` — sine of the vector
- `asin()` — arc sine of the vector
- `cos()` — cosine of the vector
- `acos()` — arc cosine of the vector
- `tan()` — tangent of the vector
- `atan()` — arc tangent of the vector
- `rad2deg()` — convert angles from radians to degrees
- `deg2rad()` — convert angles from degrees to radians

## Statistical & Reductions

See [Statistical](interfaces/statistical.md) and [Special](interfaces/special.md). For a `Vector` these return scalar `float`s.

- `sum() : float` — the sum of the vector
- `product() : float` — the product of the vector
- `min() : float` — the minimum element
- `max() : float` — the maximum element
- `mean() : float` — the mean of the vector
- `median() : float` — the median of the vector
- `quantile(float $q) : float` — the q'th quantile (throws `InvalidArgumentException` if `$q` is outside `[0, 1]`)
- `variance($mean = null) : float` — the variance; `$mean` optionally provides a pre-computed mean

## Clipping

- `clip(float $min, float $max) : self` — clip the elements between the given minimum and maximum (throws `InvalidArgumentException` if `$min > $max`)
- `clipLower(float $min) : self` — clip the tensor to be lower bounded by a given minimum
- `clipUpper(float $max) : self` — clip the tensor to be upper bounded by a given maximum

## Array Access

The vector is a read-only, zero-indexed array of its elements.

```
$vector[int $index] : float
```

- `offsetGet($index)` — return an element at the given offset; throws `InvalidArgumentException` if the offset does not exist
- `offsetExists($index) : bool` — does the given offset exist?
- `offsetSet($index, $values) : void` — **throws** `Tensor\Exceptions\RuntimeException` (vectors are immutable)
- `offsetUnset($index) : void` — **throws** `Tensor\Exceptions\RuntimeException` (vectors are immutable)
- `getIterator() : Traversable` — iterate over the elements (`ArrayIterator<int,float>`)