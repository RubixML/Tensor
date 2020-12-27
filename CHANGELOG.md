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

