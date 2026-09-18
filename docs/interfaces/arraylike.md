# ArrayLike

Array-like access to a tensor.

- **Namespace:** `Tensor\ArrayLike`

## Overview

`ArrayLike` describes tensors that behave like (read-only) PHP arrays. It extends the built-in `ArrayAccess`, `IteratorAggregate`, and `Countable` interfaces and adds structured accessors and higher-order functions.

```php
interface ArrayLike extends ArrayAccess, IteratorAggregate, Countable
```

- **Array-access:** `$tensor[$i]` — read access via `offsetGet()`. Writing (`offsetSet`) and unsetting (`offsetUnset`) throw `RuntimeException` because tensors are immutable.
- **Iteration:** `foreach ($tensor as $value)` iterates elements (rows for a `Matrix`, elements for a `Vector`).
- **Counting:** `count($tensor)` returns the number of elements.

## Methods

### `shape() : array`

Return a tuple with the dimensionality of the array-like.

- **Returns:** `int[]` — e.g. `[3]` for a vector of 3, `[2, 3]` for a 2 x 3 matrix.

### `shapeString() : string`

Return the shape of the tensor as a string.

- **Returns:** `string` — e.g. `"3"` or `"2 x 3"`.

### `size() : int`

Return the number of elements in the tensor.

- **Returns:** `int`

### `map(callable $callback) : mixed`

Map a function over all of the elements in the tensor.

- **Parameters:** `$callback` — `callable` applied to each element.
- **Returns:** a new tensor of the same shape with the mapped values.

### `reduce(callable $callback, float $initial = 0.0) : float`

Reduce the tensor down to a scalar.

- **Parameters:**
  - `$callback` — `callable` of the form `function (float $carry, float $value): float`
  - `$initial` — start value of the carry (default `0.0`)
- **Returns:** `float`

### `asArray() : array`

Return the elements of the tensor as an array.

- **Returns:** `mixed[]` — `list<float>` for vectors, `list<list<float>>` for matrices.

## Implementors

Concrete implementations are provided by `Tensor\Vector` and `Tensor\Matrix`.