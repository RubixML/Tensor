# Special

Special tensor functions.

- **Namespace:** `Tensor\Special`

## Overview

`Special` defines higher-order transcendental functions — element-wise transforms (`sigmoid`, `softplus`) and row-wise normalizations (`softmax`).

```php
interface Special
```

## Methods

### `sigmoid() : mixed`

Return the element-wise sigmoid of the tensor, i.e. `1 / (1 + exp(-x))`.

The result is always in the open interval `(0, 1)` and saturates to `1.0` and `0.0` for large positive and negative inputs respectively.

### `softplus() : mixed`

Return the element-wise softplus of the tensor: `log(1 + exp(x))`.

A smooth approximation of `max(0, x)` whose derivative is the sigmoid. Computed as `x < 0: log(1 + exp(x))` and `x >= 0: x + log(1 + exp(-x))` so the exponentially large argument never overflows.

### `softmax() : mixed`

Return the softmax of the tensor.

The maximum of each normalized row is subtracted before exponentiating, so the result stays finite for large-magnitude inputs and is invariant to adding a constant to a row.

- For `Matrix` each row is normalized independently, so the elements of every row sum to `1.0` and the shape is preserved. Normalization is across the columns *within* each row, never across rows.
- For `Vector` the whole vector is a single row, so its elements sum to `1.0`.
- For `ColumnVector` the whole column is a single row, so its elements sum to `1.0`.

### `erf() : mixed`

Return the element-wise error function of the tensor: `erf(x) = (2 / sqrt(pi)) * integral_0^x exp(-t^2) dt`.

The result is in the range `[-1.0, 1.0]` and is an odd function: `erf(-x) = -erf(x)`. For `|x| >= 5.0` the value saturates to `sign(x)`.
