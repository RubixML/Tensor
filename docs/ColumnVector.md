# ColumnVector

A one dimensional (rank 1) tensor expanded along the vertical axis, paired with matrix-facing operations.

- **Namespace:** `Tensor\ColumnVector`
- **Extends:** [`Tensor\Vector`](Vector.md)
- **Implements:** `Tensor` — i.e. `ArrayLike`, `Arithmetic`, `Comparable`, `Algebraic`, `Trigonometric`, `Statistical`, `Special`

## Overview

`ColumnVector` is a `Vector` oriented vertically. It inherits the entire `Vector` API — see [Vector](Vector.md) — including all factories, scalar/vector element-wise operators, algebraic, trigonometric, and statistical methods.

This page documents only the methods **defined on `ColumnVector`** and how they differ from `Vector`:

- `m()` returns the number of elements; `n()` is always `1`.
- Element-wise operations against a `Matrix` broadcast **down the rows** of the matrix (each matrix row is scaled by one vector element), whereas a `Vector` broadcasts **across the columns**.
- `transpose()` rotates the column vector into a horizontal `Vector`.
- All inherited factory/operators operate on `static`, so they return `ColumnVector` instances where applicable.

## Dimensionality

### `m() : int`

Return the number of rows in the vector. Equals `size()`.

### `n() : int`

Return the number of columns in the vector. Always `1`.

## Transpose

### `transpose() : mixed`

Transpose the vector, i.e. rotate it into a horizontal `Vector`.

- **Returns:** `Tensor\Vector`

## Vector-Matrix Product

### `matmul(Matrix $b) : Matrix`

Compute the vector-matrix product of this vector and matrix `$b`. Equivalent to multiplying the vector reshaped as a column matrix.

- **Parameters:** `$b` — a `Matrix`
- **Returns:** `Matrix`

## Element-Wise Operations With a Matrix

Each operation requires `$b->m() === $this->m` and throws `Tensor\Exceptions\DimensionalityMismatch` otherwise. Each returns a `Matrix` of the same shape as `$b`.

- `multiplyMatrix(Matrix $b) : Matrix` — multiply this column vector with a matrix (each row of the matrix is multiplied by the element at the corresponding row offset)
- `divideMatrix(Matrix $b) : Matrix` — divide this column vector with a matrix
- `addMatrix(Matrix $b) : Matrix` — add this column vector to a matrix
- `subtractMatrix(Matrix $b) : Matrix` — subtract a matrix from this column vector
- `powMatrix(Matrix $b) : Matrix` — raise this column vector to the power of a matrix
- `modMatrix(Matrix $b) : Matrix` — mod this column vector with a matrix
- `equalMatrix(Matrix $b) : Matrix` — element-wise equality comparison
- `notEqualMatrix(Matrix $b) : Matrix` — element-wise not-equal comparison
- `greaterMatrix(Matrix $b) : Matrix` — element-wise greater-than comparison
- `greaterEqualMatrix(Matrix $b) : Matrix` — element-wise greater-than-or-equal comparison
- `lessMatrix(Matrix $b) : Matrix` — element-wise less-than comparison
- `lessEqualMatrix(Matrix $b) : Matrix` — element-wise less-than-or-equal comparison

## Inherited API

Everything else — factories, structure accessors, higher-order functions, linear algebra (`dot`, `inner`, `outer`, norms), universal arithmetic/comparison functions, vector and scalar element-wise operators, algebraic, trigonometric, statistical, and clipping methods, plus array access — is inherited from [`Tensor\Vector`](Vector.md).