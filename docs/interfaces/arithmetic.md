# Arithmetic

Universal element-wise arithmetic functions.

- **Namespace:** `Tensor\Arithmetic`

## Overview

`Arithmetic` defines univeral functions that operate element-wise, dispatching on the operand type. Implementations accept a scalar (`float`/`int`), a same-shaped `Vector`, or a compatible `Matrix` and return the appropriate tensor type. Passing any other input throws `Tensor\Exceptions\InvalidArgumentException`.

```php
interface Arithmetic
```

## Methods

### `multiply($b) : mixed`

A universal function to multiply this tensor with another tensor element-wise.

### `divide($b) : mixed`

A universal function to divide this tensor by another tensor element-wise.

### `add($b) : mixed`

A universal function to add this tensor with another tensor element-wise.

### `subtract($b) : mixed`

A universal function to subtract a tensor from this tensor element-wise.

### `pow($b) : mixed`

A universal function to raise this tensor to the power of another tensor element-wise.

### `mod($b) : mixed`

A universal function to compute the integer modulus of this tensor and another tensor element-wise.

## Shared Signature

- **Parameter:** `$b` — the operand: `float`, `int`, `Vector`, `ColumnVector`, or `Matrix`
- **Returns:** a new tensor of the same type/shape as `$this` (scalar operands), broadcast against a `ColumnVector`/`Vector`/`Matrix` operand
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` for unsupported operand types, `Tensor\Exceptions\DimensionalityMismatch` for incompatible shapes

## Typed Operators

Concrete classes implement these universal functions using typed operator methods, which are themselves public and documented on the class pages:

- **Scalar:** `*Scalar(float $b)`
- **Vector:** `*Vector(Vector $b)` (for `Matrix`, broadcast along columns)
- **ColumnVector:** `*ColumnVector(ColumnVector $b)` (for `Matrix`, broadcast along rows)
- **Matrix:** `*Matrix(Matrix $b)`

Where `*` is one of `multiply`, `divide`, `add`, `subtract`, `pow`, `mod`.