# RREF

The reduced row echelon form (RREF) of a matrix.

- **Namespace:** `Tensor\Reductions\RREF`

## Overview

Reduces a matrix to its reduced row echelon form — the row echelon form with fully reduced pivot columns. Computed internally from the [`REF`](ref.md) of the matrix.

## Factory

### `RREF::reduce(Matrix $a) : self`

Factory method to reduce a matrix.

- **Parameters:** `$a` — the matrix to reduce
- **Returns:** `RREF`

## Accessors

### `__construct(Matrix $a)`

Instantiate from the reduced matrix.

### `a() : Matrix`

Return the reduced matrix in reduced row echelon form.