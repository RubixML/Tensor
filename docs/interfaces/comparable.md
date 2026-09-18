# Comparable

Universal element-wise comparison functions.

- **Namespace:** `Tensor\Comparable`

## Overview

`Comparable` defines universal functions that compare each element against another tensor element-wise. Comparisons are expressed numerically: they return a tensor of the same shape as `$this` where each element is `1` (`true`) or `0` (`false`).

```php
interface Comparable
```

## Methods

### `equal($b) : mixed`

A universal function to compute the equality comparison of a tensor and another tensor element-wise.

### `notEqual($b) : mixed`

A universal function to compute the not equal comparison of this tensor and another tensor element-wise.

### `greater($b) : mixed`

A universal function to compute the greater than comparison of a tensor and another tensor element-wise.

### `greaterEqual($b) : mixed`

A universal function to compute the greater than or equal to comparison of a tensor and another tensor element-wise.

### `less($b) : mixed`

A universal function to compute the less than comparison of a tensor and another tensor element-wise.

### `lessEqual($b) : mixed`

A universal function to compute the less than or equal to comparison of a tensor and another tensor element-wise.

## Shared Signature

- **Parameter:** `$b` — the operand: `float`, `int`, `Vector`, `ColumnVector`, or `Matrix`
- **Returns:** a tensor of the same shape as `$this`; each element is `1` or `0`
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` for unsupported operand types, `Tensor\Exceptions\DimensionalityMismatch` for incompatible shapes

## Typed Operators

Like [Arithmetic](arithmetic.md), concrete classes expose typed operators:

- **Scalar:** `*Scalar(float $b)`
- **Vector:** `*Vector(Vector $b)`
- **ColumnVector:** `*ColumnVector(ColumnVector $b)` (for `Matrix`)
- **Matrix:** `*Matrix(Matrix $b)`

Where `*` is one of `equal`, `notEqual`, `greater`, `greaterEqual`, `less`, `lessEqual`.