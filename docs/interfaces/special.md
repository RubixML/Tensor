# Special

Special tensor functions.

- **Namespace:** `Tensor\Special`

## Overview

`Special` defines higher-level functions that combine a transform with a normalization across more than one element.

```php
interface Special
```

## Methods

### `softmax() : mixed`

Return the softmax of the tensor.

The maximum of each normalized row is subtracted before exponentiating, so the result stays finite for large-magnitude inputs and is invariant to adding a constant to a row.

- For `Matrix` each row is normalized independently, so the elements of every row sum to `1.0` and the shape is preserved. Normalization is across the columns *within* each row, never across rows.
- For `Vector` the whole vector is a single row, so its elements sum to `1.0`.
- For `ColumnVector` the whole column is a single row, so its elements sum to `1.0`.
