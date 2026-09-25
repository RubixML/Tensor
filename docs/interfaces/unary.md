# Unary

Element-wise Unary functions.

- **Namespace:** `Tensor\Unary`

## Overview

`Unary` defines element-wise Unary operations. Each method returns a new tensor of the same shape as `$this`.

```php
interface Unary
```

## Methods

### `abs() : mixed`

Take the absolute value of the tensor.

### `square() : mixed`

Square the tensor.

### `sqrt() : mixed`

Return the square root of the tensor.

### `reciprocal() : mixed`

Return the element-wise reciprocal of the tensor.

### `exp() : mixed`

Return the exponential of the tensor.

### `expm1() : mixed`

Return the exponential of the tensor minus 1.

### `log(float $base = M_E) : mixed`

Return the logarithm of the tensor in a specified base.

- **Parameters:** `$base` — the logarithm base (default `M_E`, i.e. the natural logarithm).

### `log1p() : mixed`

Return the log of 1 plus the tensor, i.e. a transform.

### `round(int $precision = 0) : self`

Round the elements in the tensor to a given decimal place.

- **Parameters:** `$precision` — the number of decimal places (default `0`).
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$precision` is negative.

### `floor() : mixed`

Round the tensor down to the nearest integer.

### `ceil() : mixed`

Round the tensor up to the nearest integer.

### `clip(float $min, float $max) : mixed`

Clip the tensor to be between the given minimum and maximum.

- **Parameters:** `$min`, `$max` — the clip interval bounds.
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$min` is greater than `$max`.

### `clipLower(float $min) : mixed`

Clip the tensor to be lower bounded by a given minimum.

### `clipUpper(float $max) : mixed`

Clip the tensor to be upper bounded by a given maximum.

### `sign() : mixed`

Return the element-wise sign indication (`1.0`, `-1.0`, or `0.0`).

### `negate() : mixed`

Negate the tensor, i.e. take the negative.