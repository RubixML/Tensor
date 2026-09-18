# REF

The row echelon form (REF) of a matrix.

- **Namespace:** `Tensor\Reductions\REF`

## Overview

Reduces a matrix to its row echelon form, tracking the number of row swaps performed.

- **Reference:** M. Rogoyski (2019). *Math PHP: Powerful modern math library for PHP*. https://github.com/markrogoyski/math-php

## Factory

### `REF::reduce(Matrix $a) : self`

Factory method to reduce a matrix.

- **Parameters:** `$a` — the matrix to reduce
- **Returns:** `REF`
- **Note:** Falls back to the row reduction method when Gaussian elimination fails on a singular matrix.

### `REF::gaussianElimination(Matrix $a) : self`

Calculate the row echelon form (REF) of the matrix using Gaussian elimination.

- **Throws:** `Tensor\Exceptions\RuntimeException` if the matrix is singular

### `REF::rowReductionMethod(Matrix $a) : self`

Calculate the row echelon form (REF) of the matrix using the row reduction method.

## Accessors

### `__construct(Matrix $a, int $swaps)`

Instantiate from the reduced matrix and swap count.

- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$swaps < 0`

### `a() : Matrix`

Return the reduced matrix in row echelon form.

### `swaps() : int`

Return the number of swaps made to reduce the matrix to REF.