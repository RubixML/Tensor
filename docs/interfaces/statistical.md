# Statistical

Statistical measures.

- **Namespace:** `Tensor\Statistical`

## Overview

`Statistical` defines statistical measures computed over the elements of a tensor.

```php
interface Statistical
```

## Methods

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