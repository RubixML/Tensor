# Reductions

Reductions and clipping operations.

- **Namespace:** `Tensor\Reductions`

## Overview

`Reductions` defines aggregate reductions and interval-clipping operations.

```php
interface Reductions
```

- For `Vector`, reductions return a `float` scalar.
- For `Matrix`, the reductions `sum`, `product`, `min`, and `max` operate per-row and return a `ColumnVector`; clipping returns a new `Matrix` of the same shape.

## Methods

### `sum() : mixed`

Sum the tensor.

### `product() : mixed`

Calculate the product of the tensor.

### `min() : mixed`

Return the minimum of the tensor.

### `max() : mixed`

Return the maximum of the tensor.

### `clip(float $min, float $max) : mixed`

Clip the tensor to be between the given minimum and maximum.

- **Parameters:** `$min`, `$max` — the clip interval bounds.
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$min` is greater than `$max`.

### `clipLower(float $min) : mixed`

Clip the tensor to be lower bounded by a given minimum.

### `clipUpper(float $max) : mixed`

Clip the tensor to be upper bounded by a given maximum.