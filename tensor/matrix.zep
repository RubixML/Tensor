namespace Tensor;

use Tensor\Reductions\Ref;
use Tensor\Reductions\Rref;
use Tensor\Decompositions\Lu;
use Tensor\Decompositions\Svd;
use Tensor\Decompositions\Eigen;
use Tensor\Decompositions\Cholesky;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\DimensionalityMismatch;
use Tensor\Exceptions\RuntimeException;
use ArrayIterator;

/**
 * Matrix
 *
 * A two dimensional (rank 2) tensor with integer and/or floating point elements.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Matrix implements Tensor
{
    /**
     * A 2-dimensional sequential array that holds the values of the matrix.
     *
     * @var array[]
     */
    protected a;

    /**
     * The number of rows in the matrix.
     *
     * @var int
     */
    protected m;

    /**
     * The number of columns in the matrix.
     *
     * @var int
     */
    protected n;

    /**
     * Factory method to build a new matrix from an array.
     *
     * @param array[] a
     * @return self
     */
    public static function build(const array a = []) -> <Matrix>
    {
        return new self(a, true);
    }
 
    /**
     * Build a new matrix foregoing any validation for quicker instantiation.
     *
     * @param array[] a
     * @return self
     */
    public static function quick(const array a = []) -> <Matrix>
    {
        return new self(a, false);
    }

    /**
     * Return an identity matrix with dimensionality n x n.
     *
     * @param int n
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function identity(const int n) -> <Matrix>
    {
        if unlikely n < 1 {
            throw new InvalidArgumentException("N must be"
                . " greater than 0, " . strval(n) . " given.");
        }
 
        int i, j;

        array a = [];
        array rowA = [];
 
        for i in range(0, n - 1) {
            let rowA = [];

            for j in range(0, n - 1) {
                let rowA[] = i === j ? 1 : 0;
            }
 
            let a[] = rowA;
        }
 
        return self::quick(a);
    }
 
    /**
     * Return a zero matrix with the specified dimensionality.
     *
     * @param int m
     * @param int n
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function zeros(const int m, const int n) -> <Matrix>
    {
        return self::fill(0, m, n);
    }
 
    /**
     * Return a one matrix with the given dimensions.
     *
     * @param int m
     * @param int n
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function ones(const int m, const int n) -> <Matrix>
    {
        return self::fill(1, m, n);
    }
 
    /**
     * Build a matrix with the value of each element along the diagonal
     * and zeros everywhere else.
     *
     * @param (int|float)[] elements
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function diagonal(const array elements) -> <Matrix>
    {
        int n = count(elements);
 
        if unlikely n < 1 {
            throw new InvalidArgumentException("Number of elements must be"
                . " greater than 0, " . strval(n) . " given.");
        }

        var element;
 
        for element in elements {
            if !is_int(element) && !is_float(element) {
                throw new InvalidArgumentException("Diagonal element"
                    . " must be an integer or floating point number, "
                    . gettype(element) . " given.");
            }
        }

        int i, j;

        array a = [];
        array rowA = [];
 
        for i in range(0, n - 1) {
            let rowA = [];
 
            for j in range(0, n - 1) {
                let rowA[] = i === j ? elements[i] : 0;
            }
 
            let a[] = rowA;
        }
 
        return self::quick(a);
    }
 
    /**
     * Fill a matrix with a given value at each element.
     *
     * @param int|float value
     * @param int m
     * @param int n
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function fill(const value, const int m, const int n) -> <Matrix>
    {
        if unlikely !is_int(value) && !is_float(value) {
            throw new InvalidArgumentException("Value must be an"
                . " integer or floating point number, "
                . gettype(value) . " given.");
        }
 
        if unlikely m < 1 {
            throw new InvalidArgumentException("M must be"
                . " greater than 0, " . strval(m) . " given.");
        }

        if unlikely n < 1 {
            throw new InvalidArgumentException("N must be"
                . " greater than 0, " . strval(n) . " given.");
        }
 
        return self::quick(array_fill(0, m, array_fill(0, n, value)));
    }
 
     /**
      * Return a random uniform matrix with values between 0 and 1.
      *
      * @param int m
      * @param int n
      * @throws \Tensor\Exceptions\InvalidArgumentException
      * @return self
      */
    public static function rand(const int m, const int n) -> <Matrix>
    {
        if unlikely m < 1 {
            throw new InvalidArgumentException("M must be"
                . " greater than 0, " . strval(m) . " given.");
        }

        if unlikely n < 1 {
            throw new InvalidArgumentException("N must be"
                . " greater than 0, " . strval(n) . " given.");
        }

        array a = [];
        array rowA = [];

        int max = (int) getrandmax();
 
        while count(a) < m {
            let rowA = [];
 
            while count(rowA) < n {
                let rowA[] = rand() / max;
            }
 
            let a[] = rowA;
        }
 
        return self::quick(a);
    }
 
    /**
     * Return a standard normally (Gaussian( distributed random matrix of specified dimensionality.
     *
     * @param int m
     * @param int n
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function gaussian(const int m, const int n) -> <Matrix>
    {
        if unlikely m < 1 {
            throw new InvalidArgumentException("M must be"
                . " greater than 0, " . strval(m) . " given.");
        }

        if unlikely n < 1 {
            throw new InvalidArgumentException("N must be"
                . " greater than 0, " . strval(n) . " given.");
        }

        float r, phi;
        
        array a = [];
        array rowA = [];
        array extras = [];

        int max = (int) getrandmax();
 
        while count(a) < m {
            let rowA = [];
             
            if !empty extras {
                let rowA[] = array_pop(extras);
            }
 
            while count(rowA) < n {
                let r = sqrt(-2.0 * log(rand() / max));
 
                let phi = rand() / max * self::TWO_PI;
 
                let rowA[] = r * sin(phi);
                let rowA[] = r * cos(phi);
            }
 
            if count(rowA) > n {
                let extras[] = array_pop(rowA);
            }
 
            let a[] = rowA;
        }
 
        return self::quick(a);
    }

    /**
     * Generate a m x n matrix with elements from a Poisson distribution.
     *
     * @param int m
     * @param int n
     * @param float lambda
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function poisson(const int m, const int n, const float lambda = 1.0) -> <Matrix>
    {
        if unlikely m < 1 {
            throw new InvalidArgumentException("M must be"
                . " greater than 0, " . strval(m) . " given.");
        }

        if unlikely n < 1 {
            throw new InvalidArgumentException("N must be"
                . " greater than 0, " . strval(n) . " given.");
        }

        int k;
        float l, p;

        array a = [];
        array rowA = [];

        let l = (float) exp(-lambda);

        int max = (int) getrandmax();

        while count(a) < m {
            let rowA = [];

            while count(rowA) < n {
                let k = 0;
                let p = 1.0;

                while p > l {
                    let k++;

                    let p *= rand() / max;
                }

                let rowA[] = k - 1;
            }

            let a[] = rowA;
        }

        return self::quick(a);
    }

    /**
     * Return a random uniformly distributed matrix with values between -1 and 1.
     *
     * @param int m
     * @param int n
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function uniform(const int m, const int n) -> <Matrix>
    {
        if unlikely m < 1 {
            throw new InvalidArgumentException("M must be"
                . " greater than 0, " . strval(m) . " given.");
        }

        if unlikely n < 1 {
            throw new InvalidArgumentException("N must be"
                . " greater than 0, " . strval(n) . " given.");
        }

        array a = [];
        array rowA = [];

        int max = (int) getrandmax();
    
        while count(a) < m {
            let rowA = [];
    
            while count(rowA) < n {
                let rowA[] = rand(-max, max) / max;
            }
    
            let a[] = rowA;
        }
    
        return self::quick(a);
    }

    /**
     * Return the elementwise minimum of two matrices.
     *
     * @param \Tensor\Matrix a
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public static function minimum(const <Matrix> a, const <Matrix> b) -> <Matrix>
    {
        if unlikely a->m() !== b->m() {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) a->m() . " rows but Matrix B has "
                . (string) b->m() . ".");
        }

        if unlikely a->n() !== b->n() {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) a->n() . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var i, rowA;

        array c = [];

        for i, rowA in a->asArray() {
            let c[] = array_map("min", rowA, b[i]);
        }

        return self::quick(c);
    }

    /**
     * Return the elementwise maximum of two matrices.
     *
     * @param \Tensor\Matrix a
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public static function maximum(const <Matrix> a, const <Matrix> b) -> <Matrix>
    {
        if unlikely a->m() !== b->m() {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) a->m() . " rows but Matrix B has "
                . (string) b->m() . ".");
        }

        if unlikely a->n() !== b->n() {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) a->n() . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var i, rowA;

        array c = [];

        for i, rowA in a->asArray() {
            let c[] = array_map("max", rowA, b[i]);
        }

        return self::quick(c);
    }

    /**
     * Build a matrix by stacking an array of vectors.
     *
     * @param \Tensor\Vector[] vectors
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public static function stack(const array vectors) -> <Matrix>
    {
        if unlikely empty vectors {
            return self::quick();
        }

        var vector;

        var proto = reset(vectors);

        var size = proto->size();

        bool columnwise = proto instanceof ColumnVector;

        array a = [];

        for vector in vectors {
            if unlikely !(vector instanceof Vector) {
                throw new InvalidArgumentException("Cannot stack a non"
                    . " vector, " . gettype(vector) . " found.");
            }

            if unlikely columnwise && !(vector instanceof ColumnVector) {
                throw new InvalidArgumentException("Cannot stack a non"
                    . " column vector, " . gettype(vector) . " found.");
            }

            if unlikely vector->size() !== size {
                throw new InvalidArgumentException("Vectors must"
                    . " all be the same size.");
            }

            let a[] = vector->asArray();
        }

        var b = self::quick(a);

        return columnwise ? b->transpose() : b;
    }

    /**
     * @param array[] a
     * @param bool validate
     * @throws \Tensor\Exceptions\InvalidArgumentException
     */
    public function __construct(array a, const bool validate = true)
    {
        if unlikely empty a {
            throw new InvalidArgumentException("Matrix must contain at least 1 element.");
        }

        var i, rowA, valueA;

        int m = count(a);
        int n = count(current(a));
 
        if validate {
            let a = array_values(a);

            for i, rowA in a {
                if unlikely count(rowA) !== n {
                    throw new InvalidArgumentException("The number of columns"
                        . " must be equal for all rows, " . strval(n)
                        . " needed but " . count(rowA) . " given"
                        . " at row offset " . i . ".");
                }

                for valueA in rowA {
                    if unlikely !is_int(valueA) && !is_float(valueA) {
                        throw new InvalidArgumentException("Matrix element must"
                            . " be an integer or floating point number, "
                            . gettype(valueA) . " given.");
                    }
                }

                let rowA[] = array_values(rowA);
            }
        }
 
        let this->a = a;
        let this->m = m;
        let this->n = n;
    }

    /**
     * Return a tuple with the dimensionality of the tensor.
     *
     * @return int[]
     */
    public function shape() -> array
    {
        return [this->m, this->n];
    }

    /**
     * Return the shape of the tensor as a string.
     *
     * @return string
     */
    public function shapeString() -> string
    {
        return (string) this->m . " x " . (string) this->n;
    }

    /**
     * Is this a square matrix?
     *
     * @return bool
     */
    public function isSquare() -> bool
    {
        return this->m === this->n;
    }

    /**
     * Return the number of elements in the tensor.
     *
     * @return int
     */
    public function size() -> int
    {
        return this->m * this->n;
    }

    /**
     * Return the number of rows in the matrix.
     *
     * @return int
     */
    public function m() -> int
    {
        return this->m;
    }
 
    /**
     * Return the number of columns in the matrix.
     *
     * @return int
     */
    public function n() -> int
    {
        return this->n;
    }

    /**
     * Return a row from the matrix.
     *
     * @param int index
     * @return (int|float)[]
     */
    public function row(const int index) -> array
    {
        return this->offsetGet(index);
    }

    /**
     * Return a row as a vector from the matrix.
     *
     * @param int index
     * @return \Tensor\Vector
     */
    public function rowAsVector(const int index) -> <Vector>
    {
        return Vector::quick(this->row(index));
    }

    /**
     * Return a column from the matrix.
     *
     * @param int index
     * @return (int|float)[]
     */
    public function column(const int index) -> array
    {
        return array_column(this->a, index);
    }

    /**
     * Return a column as a vector from the matrix.
     *
     * @param int index
     * @return \Tensor\ColumnVector
     */
    public function columnAsVector(const int index) -> <ColumnVector>
    {
        return ColumnVector::quick(this->column(index));
    }

    /**
     * Return the diagonal elements of a square matrix as a vector.
     *
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return \Tensor\Vector
     */
    public function diagonalAsVector() -> <Vector>
    {
        if unlikely !this->isSquare() {
            throw new InvalidArgumentException("Matrix must be"
                . " square, " . this->shapeString() .  " given.");
        }

        var i, rowA;

        array b = [];

        for i, rowA in this->a {
            let b[] = rowA[i];
        }

        return Vector::quick(b);
    }

    /**
     * Return the elements of the matrix in a 2-d array.
     *
     * @return array[]
     */
    public function asArray() -> array
    {
        return this->a;
    }

    /**
     * Return each row as a vector in an array.
     *
     * @return \Tensor\Vector[]
     */
    public function asVectors() -> array
    {
        return array_map(["Tensor\\Vector", "quick"], this->a);
    }

    /**
     * Return each column as a column vector in an array.
     *
     * @return \Tensor\ColumnVector[]
     */
    public function asColumnVectors() -> array
    {
        int i;

        array vectors = [];

        for i in range(0, this->n - 1) {
            let vectors[] = this->columnAsVector(i);
        }

        return vectors;
    }

    /**
     * Flatten i.e unravel the matrix into a vector.
     *
     * @return \Tensor\Vector
     */
    public function flatten() -> <Vector>
    {
        return Vector::quick(call_user_func_array("array_merge", this->a));
    }

    /**
     * Return the index of the minimum element in every row of the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function argmin() -> <ColumnVector>
    {
        var rowA;

        array b = [];

        for rowA in this->a {
            let b[] = tensor_argmin(rowA);
        }

        return ColumnVector::quick(b);
    }

    /**
     * Return the index of the maximum element in every row of the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function argmax() -> <ColumnVector>
    {
        var rowA;

        array b = [];

        for rowA in this->a {
            let b[] = tensor_argmax(rowA);
        }

        return ColumnVector::quick(b);
    }

    /**
     * Run a function over all of the elements in the matrix.
     *
     * @param callable callback
     * @return self
     */
    public function map(const var callback) -> <Matrix>
    {
        var rowA;

        array b = [];
 
        for rowA in this->a {
            let b[] = array_map(callback, rowA);
        }
 
        return self::quick(b);
    }
    
    /**
     * Reduce the matrix down to a scalar using a callback function.
     *
     * @param callable callback
     * @param int|float initial
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return int|float
     */
    public function reduce(const var callback, const var initial = 0) -> int|float
    {
        if unlikely !is_int(initial) && !is_float(initial) {
            throw new InvalidArgumentException("Initial value must"
                . " be an integer or floating point number, "
                . gettype(initial) . " given.");
        }
 
        var rowA, valueA;

        var carry = initial;
 
        for rowA in this->a {
            for valueA in rowA {
                let carry = {callback}(valueA, carry);
            }
        }
 
        return carry;
    }
 
    /**
     * Transpose the matrix i.e row become columns and columns become rows.
     *
     * @return self
     */
    public function transpose() -> <Matrix>
    {
        int i;
        
        array b = [];
 
        for i in range(0, this->n - 1) {
            let b[] = array_column(this->a, i);
        }
 
        return self::quick(b);
    }

    /**
     * Compute the inverse of the square matrix.
     *
     * @return self
     */
    public function inverse() -> <Matrix>
    {
        if unlikely !this->isSquare() {
            throw new InvalidArgumentException("Matrix must be"
                . " square, " . this->shapeString() .  " given.");
        }

        return self::quick(tensor_inverse(this->a));
    }

    /**
     * Compute the (Moore-Penrose) pseudoinverse of the general matrix.
     *
     * @return self
     */
     public function pseudoinverse() -> <Matrix>
    {
        return self::quick(tensor_pseudoinverse(this->a));
    }

    /**
     * Calculate the determinant of the matrix.
     *
     * @throws \Tensor\Exceptions\RuntimeException
     * @return int|float
     */
    public function det() -> int|float
    {
        if unlikely !this->isSquare() {
            throw new InvalidArgumentException("Matrix must be"
                . " square, " . this->shapeString() .  " given.");
        }

        var ref = this->ref();

        var pi = ref->a()->diagonalAsVector()->product();

        return pi * pow(-1.0, ref->swaps());
    }

    /**
     * Calculate the rank of the matrix i.e the number of pivots in its reduced row echelon form.
     *
     * @return int
     */
    public function rank() -> int
    {
        var rowA, valueA;
        
        array a = [];

        let a = (array) this->rref()->a()->asArray();

        int pivots = 0;

        for rowA in a {
            for valueA in rowA {
                if valueA != 0 {
                    let pivots++;

                    continue;
                }
            }
        }

        return pivots;
    }

    /**
     * Is the matrix full rank?
     * 
     * @return bool
     */
     public function fullRank() -> bool
    {
        return this->rank() === min(this->shape());
    }

    /**
     * Is the matrix symmetric i.e. is it equal to its transpose.
     * 
     * @return bool
     */
    public function symmetric() -> bool
    {
        if !this->isSquare() {
            return false;
        }

        int i, j;
        
        var rowA;

        for i in range(0, this->m - 2) {
            let rowA = this->a[i];

            for j in range(i + 1, this->n - 1) {
                if rowA[j] != this->a[j][i] {
                    return false;
                }
            }
        }

        return true;
    }

    /**
     * Is the matrix positive definite i.e. do all of its principal minor matrices have a determinant greater than 0.
     * 
     * @return bool
     */
    public function positiveDefinite() -> bool
    {
        if !this->symmetric() {
            return false;
        }

        int i;

        for i in range(1, this->n) {
            var b = this->subMatrix(0, 0, i, i);

            if b->det() <= 0 {
                return false;
            }
        }

        return true;
    }

    /**
     * Is the matrix positive semidefinite i.e. do all of its principal minor matrices have a determinant greater or equal to 0.
     * 
     * @return bool
     */
    public function positiveSemidefinite() -> bool
    {
        if !this->symmetric() {
            return false;
        }

        int i;

        for i in range(1, this->n) {
            var b = this->subMatrix(0, 0, i, i);

            if b->det() < 0 {
                return false;
            }
        }

        return true;
    }

    /**
     * Multiply this matrix with another matrix (matrix-matrix product).
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function matmul(const <Matrix> b) -> <Matrix>
    {
        if unlikely this->n !== b->m() {
            throw new DimensionalityMismatch("Matrix A requires "
                . (string) this->n . " rows but Matrix B has "
                . (string) b->m() . ".");
        }
         
        return self::quick(tensor_matmul(this->a, b->asArray()));
    }

    /**
     * Compute the dot product of this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return \Tensor\ColumnVector
     */
    public function dot(const <Vector> b) -> <ColumnVector>
    {
        if unlikely this->n !== b->size() {
            throw new DimensionalityMismatch("Matrix A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        return this->matmul(b->asColumnMatrix())->columnAsVector(0);
    }

    /**
     * Return the 2D convolution of this matrix and a kernel matrix with given stride using the "same" method for zero padding.
     *
     * @param \Tensor\Matrix b
     * @param int stride
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function convolve(const <Matrix> b, const int stride = 1) -> <Matrix>
    {
        if unlikely b->m() > this->m || b->n() > this->n {
            throw new InvalidArgumentException("Matrix B cannot be"
                . " larger than Matrix A.");
        }

        if unlikely stride < 1 {
            throw new InvalidArgumentException("Stride cannot be"
                . " less than 1, " . strval(stride) . " given.");
        }

        return self::quick(tensor_convolve_2d(this->a, b->asArray(), stride));
    }

    /**
     * Calculate the row echelon form (REF) of the matrix. Return the reduced
     * matrix and the number of swaps needed to compute the REF.
     *
     * @return \Tensor\Reductions\Ref
     */
    public function ref() -> <Ref>
    {
        return Ref::reduce(this);
    }

    /**
     * Return the reduced row echelon (RREF) form of the matrix.
     *
     * @return \Tensor\Reductions\Rref
     */
    public function rref() -> <Rref>
    {
        return Rref::reduce(this);
    }

    /**
     * Return the LU decomposition of the matrix in a tuple where l is
     * the lower triangular matrix, u is the upper triangular matrix,
     * and p is the permutation matrix.
     *
     * @return \Tensor\Decompositions\Lu
     */
    public function lu() -> <Lu>
    {
        return Lu::decompose(this);
    }

    /**
     * Return the lower triangular matrix of the Cholesky decomposition.
     * 
     * @return \Tensor\Decompositions\Cholesky;
     */
    public function cholesky() -> <Cholesky>
    {
        return Cholesky::decompose(this);
    }

    /**
     * Compute the eigenvalues and eigenvectors of the matrix and return them in a tuple.
     *
     * @param bool symmetric
     * @return \Tensor\Decompositions\Eigen
     */
    public function eig(bool symmetric = false) -> <Eigen>
    {
        return Eigen::decompose(this, symmetric);
    }

    /**
     * Compute the singluar value decomposition of this matrix.
     *
     * @return \Tensor\Decompositions\Svd
     */
    public function svd() -> <Svd>
    {
        return Svd::decompose(this);
    }

    /**
     * Solve a linear system of equations given the matrix and a solution vector b.
     * Returns the column vector x that satisfies the solution.
     *
     * @param \Tensor\Vector b
     * @return \Tensor\ColumnVector
     */
    public function solve(const <Vector> b) -> <ColumnVector>
    {
        int i, j;
        float sigma;
        
        array l = [];
        array u = [];
        array pb = [];

        var lu = this->lu();

        let l = (array) lu->l()->asArray();
        let u = (array) lu->u()->asArray();
        let pb = (array) lu->p()->dot(b)->asArray();

        int k = (int) (this->m - 1);

        array y = [0: pb[0] / (l[0][0] ?: self::EPSILON)];

        for i in range(1, k) {
            let sigma = 0.0;

            for j in range(0, i - 1) {
                let sigma += l[i][j] * y[j];
            }

            let y[] = (pb[i] - sigma) / l[i][i];
        }
 
        array x = [k: y[k] / (l[k][k] ?: self::EPSILON)];

        for i in reverse range(0, k - 1) {
            let sigma = 0.0;

            for j in range(i + 1, k) {
                let sigma += u[i][j] * x[j];
            }

            let x[i] = (y[i] - sigma) / u[i][i];
        }

        return ColumnVector::quick(array_reverse(x));
    }

    /**
     * Return the L1 norm of the matrix.
     *
     * @return int|float
     */
    public function l1Norm() -> int|float
    {
        return this->transpose()->abs()->sum()->max();
    }
 
    /**
     * Return the L2 norm of the matrix.
     *    
     * @return int|float
     */
    public function l2Norm() -> int|float
    {
        return sqrt(this->square()->sum()->sum());
    }
 
    /**
     * Retrn the infinity norm of the matrix.
     *
     * @return int|float
     */
    public function infinityNorm() -> int|float
    {
        return this->abs()->sum()->max();
    }
 
    /**
     * Return the max norm of the matrix.
     *
     * @return int|float
     */
    public function maxNorm() -> int|float
    {
        return this->abs()->max()->max();
    }

    /**
     * A universal function to multiply this matrix with another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function multiply(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->multiplyMatrix(b);

                    case b instanceof ColumnVector:
                        return this->multiplyColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->multiplyVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->multiplyScalar(b);
        }

        throw new InvalidArgumentException("Cannot multiply"
            . " matrix by the given input.");
    }

    /**
     * A universal function to divide this matrix by another tensor sdfsdfelement-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function divide(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->divideMatrix(b);

                    case b instanceof ColumnVector:
                        return this->divideColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->divideVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->divideScalar(b);
        }

        throw new InvalidArgumentException("Cannot divide"
            . " matrix by the given input.");
    }

    /**
     * A universal function to add this matrix with another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function add(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->addMatrix(b);

                    case b instanceof ColumnVector:
                        return this->addColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->addVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->addScalar(b);
        }

        throw new InvalidArgumentException("Cannot add"
            . " matrix with the given input.");
    }

    /**
     * A universal function to subtract this matrix from another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function subtract(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->subtractMatrix(b);

                    case b instanceof ColumnVector:
                        return this->subtractColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->subtractVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->subtractScalar(b);
        }

        throw new InvalidArgumentException("Cannot multiply"
            . " matrix by the given input.");
    }

    /**
     * A universal function to raise this matrix to the power of another
     * tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function pow(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->powMatrix(b);

                    case b instanceof ColumnVector:
                        return this->powColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->powVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->powScalar(b);
        }

        throw new InvalidArgumentException("Cannot raise"
            . " matrix to the power of the given input.");
    }

    /**
     * A universal function to compute the integer modulus of this matrix
     * and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function mod(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->modMatrix(b);

                    case b instanceof ColumnVector:
                        return this->modColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->modVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->modScalar(b);
        }

        throw new InvalidArgumentException("Cannot mod"
            . " matrix with the given input.");
    }

    /**
     * A universal function to compute the equality comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function equal(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->equalMatrix(b);

                    case b instanceof ColumnVector:
                        return this->equalColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->equalVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->equalScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare"
            . " matrix to the given input.");
    }

    /**
     * A universal function to compute the not equal comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function notEqual(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->notEqualMatrix(b);

                    case b instanceof ColumnVector:
                        return this->notEqualColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->notEqualVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->notEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare"
            . " matrix to the given input.");
    }

    /**
     * A universal function to compute the greater than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function greater(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->greaterMatrix(b);

                    case b instanceof ColumnVector:
                        return this->greaterColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->greaterVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->greaterScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare"
            . " matrix to the given input.");
    }

    /**
     * A universal function to compute the greater than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function greaterEqual(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->greaterEqualMatrix(b);

                    case b instanceof ColumnVector:
                        return this->greaterEqualColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->greaterEqualVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->greaterEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare"
            . " matrix to the given input.");
    }

    /**
     * A universal function to compute the less than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function less(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->lessMatrix(b);

                    case b instanceof ColumnVector:
                        return this->lessColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->lessVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->lessScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare"
            . " matrix to the given input.");
    }

    /**
     * A universal function to compute the less than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return mixed
     */
    public function lessEqual(const var b)
    {
        switch (gettype(b)) {
            case "object":
                switch true {
                    case b instanceof Matrix:
                        return this->lessEqualMatrix(b);

                    case b instanceof ColumnVector:
                        return this->lessEqualColumnVector(b);
                    
                    case b instanceof Vector:
                        return this->lessEqualVector(b);
                }

                break;

            case "double":
            case "integer":
                return this->lessEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare"
            . " matrix to the given input.");
    }

    /**
     * Return the element-wise reciprocal of the matrix.
     *
     * @return self
     */
    public function reciprocal() -> <Matrix>
    {
        return self::ones(this->m, this->n)
            ->divideMatrix(this);
    }

    /**
     * Return the absolute value of each element in the matrix.
     *
     * @return self
     */
    public function abs() -> <Matrix>
    {
        return this->map("abs");
    }

    /**
     * Return the square of the matrix elementwise.
     *
     * @return self
     */
    public function square() -> <Matrix>
    {
        return this->multiplyMatrix(this);
    }
 
    /**
     * Return the square root of the matrix.
     *
     * @return self
     */
    public function sqrt() -> <Matrix>
    {
        return this->map("sqrt");
    }
 
    /**
     * Return the exponential of the matrix.
     *
     * @return self
     */
    public function exp() -> <Matrix>
    {
        return this->map("exp");
    }

    /**
    * Return the exponential of the tensor minus 1.
    *
    * @return self
    */
    public function expm1() -> <Matrix>
    {
        return this->map("expm1");
    }

    /**
     * Return the logarithm of the matrix in specified base.
     *
     * @param float base
     * @return self
     */
    public function log(const float base = self::M_E) -> <Matrix>
    {
        if base === self::M_E {
            return this->map("log");
        }

        var rowA, valueA;

        array rowB = [];
        array b = [];
 
        for rowA in this->a {
            let rowB = [];
 
            for valueA in rowA {
                let rowB[] = log(valueA, base);
            }
 
            let b[] = rowB;
        }
 
        return self::quick(b);
    }

    /**
    * Return the log of 1 plus the tensor i.e. a transform.
    *
    * @return self
    */
    public function log1p() -> <Matrix>
    {
        return this->map("log1p");
    }
 
    /**
     * Return the sine of the matrix.
     *
     * @return self
     */
    public function sin() -> <Matrix>
    {
        return this->map("sin");
    }

    /**
     * Compute the arc sine of the matrix.
     *
     * @return self
     */
    public function asin() -> <Matrix>
    {
        return this->map("asin");
    }
 
    /**
     * Return the cosine of the matrix.
     *
     * @return self
     */
    public function cos() -> <Matrix>
    {
        return this->map("cos");
    }

    /**
     * Compute the arc cosine of the matrix.
     *
     * @return self
     */
    public function acos() -> <Matrix>
    {
        return this->map("acos");
    }
 
    /**
     * Return the tangent of the matrix.
     *
     * @return self
     */
    public function tan() -> <Matrix>
    {
        return this->map("tan");
    }

    /**
     * Compute the arc tangent of the matrix.
     *
     * @return self
     */
    public function atan() -> <Matrix>
    {
        return this->map("atan");
    }
 
    /**
     * Convert angles from radians to degrees.
     *
     * @return self
     */
    public function rad2deg() -> <Matrix>
    {
        return this->map("rad2deg");
    }
 
    /**
     * Convert angles from degrees to radians.
     *
     * @return self
     */
    public function deg2rad() -> <Matrix>
    {
      return this->map("deg2rad");
    }

    /**
     * Sum the rows of the matrix and return a vector.
     *
     * @return \Tensor\ColumnVector
     */
    public function sum() -> <ColumnVector>
    {
        return ColumnVector::quick(array_map("array_sum", this->a));
    }

    /**
     * Calculate the row product of the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function product() -> <ColumnVector>
    {
        return ColumnVector::quick(array_map("array_product", this->a));
    }

    /**
     * Return the minimum of each row in the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function min() -> <ColumnVector>
    {
        return ColumnVector::quick(array_map("min", this->a));
    }

    /**
     * Return the maximum of each row in the matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function max() -> <ColumnVector>
    {
        return ColumnVector::quick(array_map("max", this->a));
    }

    /**
     * Compute the means of each row and return them in a vector.
     *
     * @return \Tensor\ColumnVector
     */
    public function mean() -> <ColumnVector>
    {
        return this->sum()->divideScalar(this->n);
    }

    /**
     * Return the median vector of this matrix.
     *
     * @return \Tensor\ColumnVector
     */
    public function median() -> <ColumnVector>
    {
        var rowA, median;
        array b = [];

        int mid = (int) intdiv(this->n, 2);

        bool odd = this->n % 2 === 1;

        for rowA in this->a {
            sort(rowA);

            if odd {
                let median = rowA[mid];
            } else {
                let median = (rowA[mid - 1] + rowA[mid]) / 2.0;
            }

            let b[] = median;
        }

        return ColumnVector::quick(b);
    }

    /**
     * Return the q'th quantile of this matrix.
     *
     * @param float q
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return \Tensor\ColumnVector
     */
    public function quantile(const float q) -> <ColumnVector>
    {
        if unlikely q < 0.0 || q > 1.0 {
            throw new InvalidArgumentException("Q must be between"
                . " 0 and 1, " . strval(q) . " given.");
        }

        float t;
        var rowA;
        
        array b = [];

        float x = q * (this->n - 1) + 1;

        int xHat = (int) x;
    
        float remainder = x - xHat;

        for rowA in this->a {
            sort(rowA);
    
            let t = (float) rowA[xHat - 1];
    
            let b[] = t + remainder * (rowA[xHat] - t);
        }

        return ColumnVector::quick(b);
    }

    /**
     * Compute the row variance of the matrix.
     *
     * @param \Tensor\ColumnVector|null mean
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return \Tensor\ColumnVector
     */
    public function variance(var mean = null) -> <ColumnVector>
    {
        if !is_null(mean) {
            if unlikely !(mean instanceof ColumnVector) {
                throw new InvalidArgumentException("Mean must be a"
                . " column vector " . gettype(mean) . " given.");
            }

            if unlikely mean->m() !== this->m {
                throw new DimensionalityMismatch("Mean vector must"
                    . " have " . (string) this->m . " rows, "
                    . (string) mean->m() . " given.");
            }
        } else {
            let mean = this->mean();
        }

        return this->subtractColumnVector(mean)
            ->square()
            ->sum()
            ->divideScalar(this->m);
    }

    /**
     * Compute the covariance of the matrix.
     *
     * @param \Tensor\ColumnVector mean
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function covariance(<ColumnVector> mean = null) -> <Matrix>
    {   
        if !is_null(mean) {
            if mean->m() !== this->m {
                throw new DimensionalityMismatch("Mean vector must"
                    . " have " . (string) this->m . " rows, "
                    . (string) mean->m() . " given.");
            }
        } else {
            let mean = this->mean();
        }

        var b = this->subtractColumnVector(mean);

        return b->matmul(b->transpose())
            ->divideScalar(this->m);
    }

    /**
     * Round the elements in the matrix to a given decimal place.
     *
     * @param int precision
     * @return self
     */
    public function round(const int precision = 0) -> <Matrix>
    {
        if precision === 0 {
            return this->map("round");
        }

        if unlikely precision < 0 {
            throw new InvalidArgumentException("Decimal precision cannot"
                . " be less than 0, ". strval(precision) . " given.");
        }

        var rowA, valueA;

        array b = [];
        array rowB = [];

        for rowA in this->a {
            let rowB = [];

            for valueA in rowA {
                let rowB[] = round(valueA, precision);
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Round the elements in the matrix down to the nearest integer.
     *
     * @return self
     */
    public function floor() -> <Matrix>
    {
        return this->map("floor");
    }

    /**
     * Round the elements in the matrix up to the nearest integer.
     *
     * @return self
     */
    public function ceil() -> <Matrix>
    {
        return this->map("ceil");
    }

    /**
     * Clip the elements in the matrix to be between given minimum and maximum
     * and return a new matrix.
     *
     * @param float min
     * @param float max
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function clip(const float min, const float max) -> <Matrix>
    {
        if unlikely min > max {
            throw new InvalidArgumentException("Minimum cannot be"
                . " greater than maximum.");
        }

        var rowA, valueA;

        array b = [];
        array rowB = [];

        for rowA in this->a {
            let rowB = [];

            for valueA in rowA {
                if valueA > max {
                    let rowB[] = max;

                    continue;
                }

                if valueA < min {
                    let rowB[] = min;

                    continue;
                }

                let rowB[] = valueA;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Clip the tensor to be lower bounded by a given minimum.
     *
     * @param float min
     * @return self
     */
    public function clipLower(const float min) -> <Matrix>
    {
        var rowA, valueA;

        array b = [];
        array rowB = [];

        for rowA in this->a {
            let rowB = [];

            for valueA in rowA {
                if valueA < min {
                    let rowB[] = min;

                    continue;
                }

                let rowB[] = valueA;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Clip the tensor to be upper bounded by a given maximum.
     *
     * @param float max
     * @return self
     */
    public function clipUpper(const float max) -> <Matrix>
    {
        var rowA, valueA;

        array b = [];
        array rowB = [];

        for rowA in this->a {
            let rowB = [];

            for valueA in rowA {
                if valueA > max {
                    let rowB[] = max;

                    continue;
                }

                let rowB[] = valueA;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise sign indication.
     *
     * @return self
     */
    public function sign() -> <Matrix>
    {
        var rowA, valueA;
        
        array b = [];
        array rowB = [];

        for rowA in this->a {
            let rowB = [];

            for valueA in rowA {
                if valueA > 0 {
                    let rowB[] = 1;
                } elseif valueA < 0 {
                    let rowB[] = -1;
                } else {
                    let rowB[] = 0;
                }
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Negate the matrix i.e take the negative of each value elementwise.
     *
     * @return self
     */
    public function negate() -> <Matrix>
    {
        var rowA, valueA;

        array b = [];
        array rowB = [];

        for rowA in this->a {
            let rowB = [];

            for valueA in rowA {
                let rowB[] = -valueA;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Insert a smaller matrix b into this matrix.
     * 
     * @param \Tensor\Matrix b
     * @param int rowOffset
     * @param int columnOffset
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function insert(const <Matrix> b, const int rowOffset, const int columnOffset) -> <Matrix>
    {
        if (b->m() + rowOffset > this->m) {
            throw new InvalidArgumentException("Matrix b does not fit"
                . " into matrix a with row offset "
                . strval(rowOffset) . ".");
        }

        if (b->n() + columnOffset > this->n) {
            throw new InvalidArgumentException("Matrix b does not fit"
                . " into matrix a with column offset "
                . strval(columnOffset) . ".");
        }

        int ii, jj;
        var i, j, rowB, valueB;

        array c = [];

        let c = (array) this->a;

        for i, rowB in b->asArray() {
            let ii = rowOffset + i;

            for j, valueB in rowB {
                let jj = columnOffset + j;

                let c[ii][jj] = valueB;
            }
        }

        return self::quick(c);
    }

    /**
     * Return the sub matrix starting at row and column offset.
     *
     * @param int startRow
     * @param int startColumn
     * @param int endRow
     * @param int endColumn
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function subMatrix(
        const int startRow,
        const int startColumn,
        const int endRow,
        const int endColumn
    ) -> <Matrix> {
        if unlikely startRow < 0 {
            throw new InvalidArgumentException("Start row must be"
                . " greater than 0, " . strval(startRow) . " given.");
        }

        if unlikely startColumn < 0 {
            throw new InvalidArgumentException("Start column must be"
                . " greater than 0, " . strval(startColumn) . " given.");
        }

        if unlikely endRow < startRow {
            throw new InvalidArgumentException("End row must be"
                . " greater than start row.");
        }

        if unlikely endColumn < startColumn {
            throw new InvalidArgumentException("End column must be"
                . " greater than start column.");
        }

        if unlikely endRow > this->m {
            throw new InvalidArgumentException("End row is out"
                . " of bounds of matrix.");
        }

        if unlikely endColumn > this->n {
            throw new InvalidArgumentException("End column is out"
                . " of bounds of matrix.");
        }

        int i, j;
        var rowA;
        array b = [];
        array rowB = [];

        int k = endRow - startRow;
        int l = endColumn - startColumn;

        for i in range(startRow, k) {
            let rowA = this->a[i];

            let rowB = [];

            for j in range(startColumn, l) {
                let rowB[] = rowA[j];
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Attach matrix b above this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function augmentAbove(const <Matrix> b) -> <Matrix>
    {
        if unlikely this->m > 0 && b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A requires"
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        return self::quick(array_merge(b->asArray(), this->a));
    }

    /**
     * Attach matrix b below this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function augmentBelow(const <Matrix> b) -> <Matrix>
    {
        if unlikely this->m > 0 && b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A requires"
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        return self::quick(array_merge(this->a, b->asArray()));
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function augmentLeft(const <Matrix> b) -> <Matrix>
    {
        if unlikely this->m > 0 && b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A requires"
                . (string) this->m . " rows but Matrix B has "
                . (string) b->m() . ".");
        }

        return self::quick(array_map("array_merge", b->asArray(), this->a));
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function augmentRight(const <Matrix> b) -> <Matrix>
    {
        if unlikely this->m > 0 && b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A requires"
                . (string) this->m . " rows but Matrix B has "
                . (string) b->m() . ".");
        }
        
        return self::quick(array_map("array_merge", this->a, b->asArray()));
    }

    /**
     * Repeat the matrix m times along the vertival axes and n times along the
     * horizontal axes.
     *
     * @param int m
     * @param int n
     * @return self
     */
    public function repeat(const int m, const int n) -> <Matrix>
    {
        var rowA;
        array b = [];
        array temp = [];

        if n > 0 {
            for rowA in this->a {
                let temp = [];

                while count(temp) <= n {
                    let temp[] = rowA;
                }

                let b[] = call_user_func_array("array_merge", temp);
            }
        }

        let temp = [];

        while count(temp) <= m {
            let temp[] = b;
        }

        return self::quick(call_user_func_array("array_merge", temp));
    }

    /**
     * Return the element-wise product between this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function multiplyMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;

        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_multiply(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the division of two elements, element-wise.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function divideMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_divide(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Add this matrix together with another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function addMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_add(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Subtract a matrix from this matrix element-wise.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function subtractMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_subtract(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Raise this matrix to the power of the elementwise entry in another
     * matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function powMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_pow(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Calculate the modulus i.e remainder of division between this matri and
     * another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function modMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_mod(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and
     * another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function equalMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_equal(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and
     * another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function notEqualMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_not_equal(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix
     * and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function greaterMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_greater(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function greaterEqualMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_greater_equal(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function lessMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_less(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function lessEqualMatrix(const <Matrix> b) -> <Matrix>
    {
        if unlikely b->shape() !== this->shape() {
            throw new DimensionalityMismatch(this->shapeString()
                . " matrix expected but " . b->shapeString() . " given.");
        }

        var i, rowB;
        
        array c = [];

        for i, rowB in b->asArray() {
            let c[] = tensor_less_equal(this->a[i], rowB);
        }

        return self::quick(c);
    }

    /**
     * Multiply this matrix by a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function multiplyVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_multiply(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Divide this matrix by a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function divideVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_divide(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Add this matrix by a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function addVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_add(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Subtract a vector from this matrix.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function subtractVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_subtract(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Raise this matrix to the power of a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function powVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_pow(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Calculate the modulus of this matrix with a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function modVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_mod(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a
     * vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function equalVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_equal(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function notEqualVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_not_equal(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function greaterVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_greater(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function greaterEqualVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_greater_equal(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function lessVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_less(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function lessEqualVector(const <Vector> b) -> <Matrix>
    {
        if unlikely b->n() !== this->n {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var rowA;

        array c = [];

        var bHat = b->asArray();
    
        for rowA in this->a {
            let c[] = tensor_less_equal(rowA, bHat);
        }
    
        return self::quick(c);
    }

    /**
     * Multiply this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function multiplyColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_multiply_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Divide this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function divideColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_divide_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Add this matrix to a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function addColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_add_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Subtract a column vector from this matrix.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function subtractColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_subtract_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Raise this matrix to the power of a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function powColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_pow_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Mod this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function modColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_mod_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function equalColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_equal_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function notEqualColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_not_equal_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function greaterColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_greater_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function greaterEqualColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_greater_equal_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function lessColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_less_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \Tensor\Exceptions\DimensionalityMismatch
     * @return self
     */
    public function lessEqualColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if unlikely b->m() !== this->m {
            throw new DimensionalityMismatch("Matrix A expects "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, valueB;

        array c = [];

        for i, valueB in b->asArray() {
            let c[] = tensor_less_equal_scalar(this->a[i], valueB);
        }

        return self::quick(c);
    }

    /**
     * Multiply this matrix by a scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function multiplyScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_multiply_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Divide this matrix by a scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function divideScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_divide_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Add this matrix by a scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function addScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_add_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Subtract a scalar from this matrix.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function subtractScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_subtract_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Raise the matrix to a given scalar power.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function powScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_pow_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Calculate the modulus of this matrix with a scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function modScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_mod_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a
     * scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function equalScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_equal_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a
     * scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function notEqualScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_not_equal_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and a
     * scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function greaterScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_greater_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function greaterEqualScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_greater_equal_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and a
     * scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function lessScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_less_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a scalar.
     *
     * @param mixed b
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return self
     */
    public function lessEqualScalar(const var b) -> <Matrix>
    {
        if unlikely !is_int(b) && !is_float(b) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(b) . " given.");
        }

        var rowA;

        array c = [];

        for rowA in this->a {
            let c[] = tensor_less_equal_scalar(rowA, b);
        }

        return self::quick(c);
    }

    /**
     * @return int
     */
    public function count() -> int
    {
        return this->size();
    }

    /**
     * @param mixed index
     * @param array values
     * @throws \Tensor\Exceptions\RuntimeException
     */
    public function offsetSet(const var index, const var values) -> void
    {
        throw new RuntimeException("Matrix cannot be mutated directly.");
    }

    /**
     * Does a given column exist in the matrix.
     *
     * @param mixed index
     * @return bool
     */
    public function offsetExists(const var index) -> bool
    {
        return isset this->a[index];
    }

    /**
     * @param mixed index
     * @throws \Tensor\Exceptions\RuntimeException
     */
    public function offsetUnset(const var index) -> void
    {
        throw new RuntimeException("Matrix cannot be mutated directly.");
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param mixed index
     * @throws \Tensor\Exceptions\InvalidArgumentException
     * @return array
     */
    public function offsetGet(const var index) -> array
    {
        var value;

        if likely fetch value, this->a[index] {
            return value;
        }

        throw new InvalidArgumentException("Element not found at"
            . " offset " . (string) index . ".");
    }

    /**
     * Get an iterator for the rows in the matrix.
     *
     * @return \ArrayIterator
     */
    public function getIterator()
    {
        return new ArrayIterator(this->a);
    }

    /**
     * Convert the tensor into a string representation.
     *
     * @return string
     */
    public function __toString() -> string
    {
        return array_reduce(this->a, ["Tensor\\Matrix", "implodeRow"], "") . PHP_EOL;
    }

    /**
     * Implode a row of the matrix and return the output.
     *
     * @param string carry
     * @param array row
     * @return string
     */
    protected static function implodeRow(const string carry, const array row) -> string
    {
        return carry . PHP_EOL . "[ " . implode(" ", row) . " ]";
    }
}