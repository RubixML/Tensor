# SVD

The singular value decomposition of a matrix.

- **Namespace:** `Tensor\Decompositions\SVD`

## Overview

The singular value decomposition factors a matrix `A` into `U * S * Vᵀ`, where `U` and `V` are orthogonal matrices and `S` is an `m` by `n` matrix with the singular values on the diagonal. The product `u() * s() * vT()` reconstructs the original matrix even for rectangular inputs, because `S` is zero-padded to the shape of `A`.

## Factory

### `SVD::decompose(Matrix $a) : self`

Factory method to decompose a matrix.

- **Parameters:** `$a` — the matrix to decompose
- **Returns:** `SVD`
- **Throws:** `Tensor\Exceptions\RuntimeException` if the decomposition fails to converge

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

Return the singular value matrix — an `m` by `n` matrix with the singular values on the diagonal, zero-padded such that `u() * s() * vT()` reconstructs the original matrix.

- **Returns:** `Matrix`

### `v() : Matrix`

Return the V matrix (transpose of `vT`).

### `vT() : Matrix`

Return the V transposed matrix.