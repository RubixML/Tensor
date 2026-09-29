# Reductions

Reduction and statistical operations.

- **Namespace:** `Tensor\Reductions`

## Overview

`Reductions` defines aggregate reductions along with the statistical measures computed over the elements of a tensor.

```php
interface Reductions
```

- For `Vector`, reductions return a `float` scalar.
- For `Matrix`, every reduction here operates per-row and returns a `ColumnVector`.

## Methods

### `sum() : mixed`

Sum the tensor.

### `product() : mixed`

Calculate the product of the tensor.

### `min() : mixed`

Return the minimum of the tensor.

### `max() : mixed`

Return the maximum of the tensor.

### `mean() : mixed`

Return the mean of the tensor.

### `variance($mean = null) : mixed`

Compute the variance of the tensor.

- **Parameters:** `$mean` — an optional pre-computed mean to avoid recomputation. If omitted, the mean is computed internally.

### `median() : mixed`

Return the median of the tensor.

### `quantile(float $q) : mixed`

Return the q'th quantile of the tensor.

- **Parameters:** `$q` — the quantile in the range `[0, 1]`.
- **Throws:** `Tensor\Exceptions\InvalidArgumentException` if `$q` is outside `[0, 1]`.
