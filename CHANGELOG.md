- 3.0.5
    - Upgraded Zephir dependency to 0.17

- 3.0.4
    - Fixed bug in Vector less equal operation

- 3.0.3
    - Added PHP 8.2 extension compatibility

- 3.0.2
    - Added PHP 8.1 extension compatibility

- 3.0.1
    - Add positive semi-definite typehinting

- 3.0.0
    - No changes

- 3.0.0-beta
    - Add support for PHP 8.0 in the extension
    - Drop extension support for PHP 7.2 and 7.3
    - Tensors only compute floating point operations
    - Remove dependency on JAMA library
    - Remove previously deprecated items
    - Matrix returns vector on row access
    - Added Algebraic and Special function interfaces

- 2.2.3
    - Remove dependency on pthreads

-2.2.2
    - Compensate for PSR-4 issues

- 2.2.1
    - Optimize 2D convolution operation
    - Fix and optimize vector convolve 1D operation

- 2.2.0
    - Implemented Singular Value Decomposition (SVD)
    - Implemented matrix (Moore-Penrose) pseudoinverse
    - Tensor objects now throw namespaced exceptions
    - Optimized Reduced Row Echelon Form (RREF)
    - Optimize eigendecomposition for symmetric matrices

- 2.1.4
    - Implemented Eigen decomposition in extension
    - Optimize row echelon form (REF) of matrix
    - Optimize Cholesky decomposition
    - Fix memory leak in matrix inverse
    - Optimize LU decomposition

- 2.1.3
    - Use BLAS DGEMM for matrix multiplication
    - Optimize matrix inverse

- 2.1.2
    - Optimize scalar arithmetic and comparisons

- 2.1.1
    - Zephir redux
    - Blanket extension optimizations
    - Added array arithmetic and comparison functions

- 2.1.0
    - Extension now compiles directly from C source code
    - Remove Zephir extension code
    - Update instructions for extension compilation using PHPize

- 2.0.5
    - Percentile method changed to quantile
    - Fixed Vector linspace precision

- 2.0.4
    - Individual Arithmetic and Comparison methods now public
    - Matrix reductions have their own namespace
    - Optimized Matrix structural operations
    - Added argmin and argmax custom optimizers
    - Added matrix/sub matrix insertion

- 2.0.3
    - Matrix decomp methods now return decomp objects
    - Optimized matrix statistical operations
    - Optimized vector outer product
    - Optimized Matrix flatten
    - Cannot instantiate null/empty tensors

- 2.0.2
    - Optimized random number generation

- 2.0.1
    - Added benchmarks
    - Matrix stacking now row or column-wise
    - Changed method signature and behavior of repeat matrix

- 2.0.0
    - Implemented the library as an extension using Zephir lang
    - Changed namespace from Rubix\Tensor to \Tensor
    - Matrix decompositions are now a separate abstraction
    - Removed Dimensionality Mismatch exception
    - Added inverse trigonometric methods to Trigonometric interface
    - Added Array-Like interface
    - Removed Column/Row exclude methods from Matrix
    - Changed method signature of matrix determinant
    - Added return sub matrix
    - Added positive definite and semi-definite methods to Matrix
    - Added is symmetric method to Matrix
    - Added Statistical and Trigonometric interfaces
    - Added Arithmetic and Comparable interfaces
    - Added log1p and expm1 methods to the Arithmetic interface
    - Added matrix full rank method
    - Added generate random Poisson distribution
    - Added Cholesky decomposition
    - Variance now takes an optional mean argument

- 1.0.4
    - Added transpose to Tensor API
    - Reduced memory footprint of matmul operation
    - Removed magic getters
    - Added shape string method to Tensor API
    - Improved error messages for matrix dimensionality mismatch

- 1.0.3
    - Added clip upper and lower bounds
    - Added isSquare method to Matrix
    - Added vector late static binding

- 1.0.2
    - Added ref using row elimination method
    - Added universal comparison methods to tensor API
    - Added convolve operation to Vector and Matrix

- 1.0.1
    - Added Column Vector
    - Implemented Eigenvalue decomposition
    - Added solve system of linear equations
    - Integration with 3rd party JAMA library
    - Fixed variance covariance calculation
    - Added percentile calculation for Vector and Matrix

- 1.0.0
    - Implemented LU decomposition
    - Added vector projection
    - Implemented Matrix inverse
    - Implemented Row Echelon and Reduced Row Echelon decomposition
    - Added Matrix determinant
    - Added Matrix rank
    - Added Matrix/Vector products
    - Implemented universal element-wise tensor operations
    - Added statistical functions
    - Added trigonometric functions
    - Added exponential and logarithmic functions
    - Added tensor factories

