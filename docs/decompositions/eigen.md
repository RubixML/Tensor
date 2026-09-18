# Eigen

The eigendecomposition (or spectral decomposition) of a matrix.

- **Namespace:** `Tensor\Decompositions\Eigen`

## Overview

The eigendecomposition is a matrix factorization resulting in a matrix of eigenvectors and a corresponding array of eigenvalues.

> **Note:** The pure-PHP library does not compute the eigendecomposition — `decompose()` throws `Tensor\Exceptions\NotImplemented`. It is available when the [extension is installed](../getting-started.md). An `Eigen` object can still be constructed manually via `__construct()`.

## Factory

### `Eigen::decompose(Matrix $a, bool $symmetric = false) : self`

Factory method to decompose a matrix.

- **Parameters:**
  - `$a` — the matrix to decompose
  - `$symmetric` — whether the matrix is known to be symmetric (default `false`), which selects a faster solver
- **Returns:** `Eigen`
- **Throws:** `Tensor\Exceptions\NotImplemented` in the pure-PHP library

## Accessors

### `__construct(array $eigenvalues, Matrix $eigenvectors)`

Instantiate from eigenvalues and eigenvectors.

- **Parameters:** `$eigenvalues` — `(int|float)[]`, `$eigenvectors` — `Matrix`

### `eigenvalues() : array`

Return the eigenvalues of the eigendecomposition.

- **Returns:** `(int|float)[]`

### `eigenvectors() : Matrix`

Return the eigenvectors of the eigendecomposition.

- **Returns:** `Matrix`