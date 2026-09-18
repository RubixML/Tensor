# Eigen

The eigendecomposition (or spectral decomposition) of a matrix.

- **Namespace:** `Tensor\Decompositions\Eigen`

## Overview

The eigendecomposition is a matrix factorization resulting in a matrix of eigenvectors and a corresponding array of eigenvalues.

> **Note:** For matrices with complex eigenvalues, only the real parts of the eigenvalues and eigenvectors are returned, mirroring the [extension](getting-started.md). The eigenvector at row `i` of `eigenvectors()` corresponds to the eigenvalue at index `i` of `eigenvalues()`. Each eigenvector is normalized to unit length.

## Factory

### `Eigen::decompose(Matrix $a, bool $symmetric = false) : self`

Factory method to decompose a matrix.

- **Parameters:**
  - `$a` — the matrix to decompose
  - `$symmetric` — whether the matrix is known to be symmetric (default `false`), which selects a faster solver
- **Returns:** `Eigen`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if the matrix is not square, `Tensor\Exceptions\RuntimeException` if the decomposition fails to converge

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