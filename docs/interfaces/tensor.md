# Tensor

Interface implemented by all tensor objects.

- **Namespace:** `Tensor\Tensor`

## Overview

`Tensor` is the top-level marker interface for every tensor type in the library. It has no methods of its own; it composes the entire tensor API by extending the capable sub-interfaces below. See `docs/README.md` for the full surface.

```php
interface Tensor extends ArrayLike, Arithmetic, Comparable,
    Unary, Trigonometric, Statistical, Reductions
```

## Inherited Method Groups

| Interface | Methods |
| --- | --- |
| [ArrayLike](arraylike.md) | `shape`, `shapeString`, `size`, `map`, `reduce`, `asArray` |
| [Arithmetic](arithmetic.md) | `multiply`, `divide`, `add`, `subtract`, `pow`, `mod` |
| [Comparable](comparable.md) | `equal`, `notEqual`, `greater`, `greaterEqual`, `less`, `lessEqual` |
| [Unary](unary.md) | `abs`, `square`, `sqrt`, `reciprocal`, `exp`, `expm1`, `log`, `log1p`, `round`, `floor`, `ceil`, `clip`, `clipLower`, `clipUpper`, `sign`, `negate` |
| [Trigonometric](trigonometric.md) | `sin`, `asin`, `cos`, `acos`, `tan`, `atan`, `rad2deg`, `deg2rad` |
| [Statistical](statistical.md) | `mean`, `variance`, `median`, `quantile` |
| [Reductions](reductions.md) | `sum`, `product`, `min`, `max` |

Additionally, because `ArrayLike` extends `ArrayAccess`, `IteratorAggregate`, and `Countable`, every tensor is array-accessible, iterable, and countable.

## Implementations

- [`Tensor\Vector`](../Vector.md)
- [`Tensor\ColumnVector`](../ColumnVector.md)
- [`Tensor\Matrix`](../Matrix.md)