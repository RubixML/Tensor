# Tensor API Reference

Tensor is a library for scientific computing in PHP. It provides an object-oriented API consisting of a `Tensor` interface (composed of several sub-interfaces) implemented by three concrete classes, plus decomposition and reduction result objects.

## Namespace Map

```
Tensor \
├── Tensor (interface)
├── Vector
├── ColumnVector (extends Vector)
├── Matrix
│
├── ArrayLike (interface)
├── Arithmetic (interface)
├── Comparable (interface)
├── Unary (interface)
├── Trigonometric (interface)
├── Statistical (interface)
├── Reductions (interface)
│
├── Decompositions
│   ├── Cholesky
│   ├── Eigen
│   ├── LU
│   └── SVD
└── Reductions
    ├── REF
    └── RREF
```

## Classes

| Class | Description |
| --- | --- |
| [Vector](Vector.md) | A one dimensional (rank 1) tensor with integer and/or floating point elements. |
| [ColumnVector](ColumnVector.md) | A vertical one dimensional tensor; extends `Vector` with matrix-facing operations. |
| [Matrix](Matrix.md) | A two dimensional (rank 2) tensor with integer and/or floating point elements. |

## Interfaces

| Interface | Description |
| --- | --- |
| [Tensor](interfaces/tensor.md) | The top-level tensor marker — extends the interfaces below. |
| [ArrayLike](interfaces/arraylike.md) | Array-like access, iteration, counting, and mapping. |
| [Arithmetic](interfaces/arithmetic.md) | Universal element-wise arithmetic functions. |
| [Comparable](interfaces/comparable.md) | Universal element-wise comparison functions. |
| [Unary](interfaces/unary.md) | Element-wise Unary functions. |
| [Trigonometric](interfaces/trigonometric.md) | Element-wise trigonometric functions. |
| [Statistical](interfaces/statistical.md) | Statistical measures. |
| [Reductions](interfaces/reductions.md) | Reduction operations. |

## Decompositions

| Class | Description |
| --- | --- |
| [Cholesky](decompositions/cholesky.md) | The Cholesky decomposition of a square, positive definite matrix. |
| [Eigen](decompositions/eigen.md) | The eigendecomposition (spectral decomposition) of a matrix. |
| [LU](decompositions/lu.md) | The LU decomposition of a matrix with permutation. |
| [SVD](decompositions/svd.md) | The singular value decomposition of a matrix. |

## Reductions

| Class | Description |
| --- | --- |
| [REF](reductions/ref.md) | The row echelon form of a matrix. |
| [RREF](reductions/rref.md) | The reduced row echelon form of a matrix. |

## Design Notes

- **Math is float-only.** Element arrays are returned as `list<float>`; integers are cast to floats on construction.
- **Immutable.** Tensors cannot be mutated in place — `offsetSet()` and `offsetUnset()` throw `RuntimeException`. Every operation returns a new tensor.
- **Universal functions.** `Arithmetic` and `Comparable` methods dispatch on the operand type (scalar, `Vector`, `Matrix`) and are implemented by the concrete typed operators (e.g. `addScalar`, `addVector`, `addMatrix`, `addColumnVector`).

## Getting Started

New to Tensor? See the [Getting Started](getting-started.md) guide for installation and a complete example.