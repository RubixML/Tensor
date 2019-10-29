- Unreleased
    - Implemented the library as a PHP extension using Zephir lang
    - Changed namespace from Rubix\Tensor to \Tensor
    - Matrix decompositions are now a separate abstraction
    - Removed Dimensionality Mismatch exception

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
    - Integration with 3rd party JAMA libray
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

