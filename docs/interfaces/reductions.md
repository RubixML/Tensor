# Reductions

Reduction operations.

- **Namespace:** `Tensor\Reductions`

## Overview

`Reductions` defines aggregate reductions.

```php
interface Reductions
```

- For `Vector`, reductions return a `float` scalar.
- For `Matrix`, the reductions `sum`, `product`, `min`, and `max` operate per-row and return a `ColumnVector`.

## Methods

### `sum() : mixed`

Sum the tensor.

### `product() : mixed`

Calculate the product of the tensor.

### `min() : mixed`

Return the minimum of the tensor.

### `max() : mixed`

Return the maximum of the tensor.