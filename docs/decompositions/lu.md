# LU

The LU decomposition of a Matrix as the product of a lower and upper triangular matrix as well as a permutation matrix.

- **Namespace:** `Tensor\Decompositions\LU`

## Overview

The LU decomposition factors a square matrix `A` into `P * L * U`, where:

- `P` — a permutation matrix (row swaps),
- `L` — a lower triangular matrix,
- `U` — an upper triangular matrix.

## Factory

### `LU::decompose(Matrix $a) : self`

Factory method to decompose a matrix.

- **Parameters:** `$a` — the matrix to decompose
- **Returns:** `LU`
- **Throws:**
  - `Tensor\Exceptions\InvalidArgumentException` if `$a` is not square
  - `Tensor\Exceptions\RuntimeException` if `$a` is singular

## Accessors

### `__construct(Matrix $l, Matrix $u, Matrix $p)`

Instantiate from the lower, upper, and permutation matrices.

### `l() : Matrix`

Return the lower triangular matrix.

### `u() : Matrix`

Return the upper triangular matrix.

### `p() : Matrix`

Return the permutation matrix.