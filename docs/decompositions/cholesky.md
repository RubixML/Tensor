# Cholesky

An efficient decomposition of a square positive definite matrix into a lower triangular matrix and its conjugate transpose.

- **Namespace:** `Tensor\Decompositions\Cholesky`

## Overview

The Cholesky decomposition factors a square, positive definite matrix `A` into `L * Lᵀ`, where `L` is a lower triangular matrix. The decomposition is symmetric and hence the transpose `Lᵀ` can be reconstructed from `L` without additional storage.

## Factory

### `Cholesky::decompose(Matrix $a) : self`

Factory method to decompose a matrix.

- **Parameters:** `$a` — the matrix to decompose
- **Returns:** `Cholesky`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$a` is not square

## Accessors

### `__construct(Matrix $l)`

Instantiate from a lower triangular matrix.

### `l() : Matrix`

Return the lower triangular matrix.

### `lT() : Matrix`

Return the transpose of the lower triangular matrix (the conjugate transpose `Lᵀ`).