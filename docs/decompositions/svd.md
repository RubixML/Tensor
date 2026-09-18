# SVD

The singular value decomposition of a matrix.

- **Namespace:** `Tensor\Decompositions\SVD`

## Overview

The singular value decomposition factors a matrix `A` into `U * S * Vᵀ`, where `U` and `V` are orthogonal matrices and `S` is a diagonal matrix of the singular values.

> **Note:** The pure-PHP library does not compute the singular value decomposition — `decompose()` throws `Tensor\Exceptions\NotImplemented`. It is available when the [extension is installed](../getting-started.md). An `SVD` object can still be constructed manually via `__construct()`.

## Factory

### `SVD::decompose(Matrix $a) : self`

Factory method to decompose a matrix.

- **Parameters:** `$a` — the matrix to decompose
- **Returns:** `SVD`
- **Throws:** `Tensor\Exceptions\NotImplemented` in the pure-PHP library

## Accessors

### `__construct(Matrix $u, array $singularValues, Matrix $vT)`

Instantiate from the orthogonal matrices and singular values.

- **Parameters:** `$singularValues` — `list<int|float>`

### `u() : Matrix`

Return the U matrix.

### `singularValues() : array`

Return the singular values of matrix A.

- **Returns:** `list<float>`

### `s() : Matrix`

Return the singular value matrix — a diagonal matrix of the singular values.

- **Returns:** `Matrix`

### `v() : Matrix`

Return the V matrix (transpose of `vT`).

### `vT() : Matrix`

Return the V transposed matrix.