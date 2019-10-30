namespace Tensor;

use Tensor\Decompositions\Lu;
use Tensor\Decompositions\Ref;
use Tensor\Decompositions\Rref;
use InvalidArgumentException;
use RuntimeException;
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
    const EPSILON = 0.00000001;

    const M_PI = 3.14159265358979323846;

    const TWO_PI = 6.28318530718;

    const M_E = 2.7182818284590452354;

    /**
     * A 2-dimensional sequential array that holds the values of the matrix.
     *
     * @var array[]
     */
    protected a = [
        //
    ];

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
     * @param array a
     * @return self
     */
    public static function build(array a = []) -> <Matrix>
    {
        return new self(a, true);
    }
 
    /**
     * Build a new matrix foregoing any validation for quicker instantiation.
     *
     * @param array a
     * @return self
     */
    public static function quick(array a = []) -> <Matrix>
    {
        return new self(a, false);
    }

    /**
     * Return an identity matrix with dimensionality n x n.
     *
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function identity(const int n) -> <Matrix>
    {
        if n < 1 {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 on all axes.");
        }
 
        uint i, j;

        array a = [];
 
        for i in range(0, n - 1) {
            array rowA = [];
 
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
     * @throws \InvalidArgumentException
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
     * @throws \InvalidArgumentException
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
     * @param array elements
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function diagonal(const array elements) -> <Matrix>
    {
        int n = count(elements);
 
        if n < 1 {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 on all axes.");
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
 
        for i in range(0, n - 1) {
             array rowA = [];
 
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
     * @param mixed value
     * @param int m
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill(const value, const int m, const int n) -> <Matrix>
    {
        if !is_int(value) && !is_float(value) {
            throw new InvalidArgumentException("Value must be an"
                . " integer or floating point number, "
                . gettype(value) . " given.");
        }
 
        if m < 1 || n < 1 {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }
 
        return self::quick(array_fill(0, m, array_fill(0, n, value)));
    }
 
     /**
      * Return a random uniform matrix with values between 0 and 1.
      *
      * @param int m
      * @param int n
      * @throws \InvalidArgumentException
      * @return self
      */
    public static function rand(const int m, const int n) -> <Matrix>
    {
        if m < 1 || n < 1 {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }

        array a = [];
 
        while count(a) < m {
            array rowA = [];
 
            while count(rowA) < n {
                let rowA[] = rand(0, PHP_INT_MAX)
                    / PHP_INT_MAX;
            }
 
            let a[] = rowA;
        }
 
        return self::quick(a);
    }
 
    /**
     * Return a standard normally (Gaussian( distributed random matrix of
     * specified dimensionality.
     *
     * @param int m
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function gaussian(const int m, const int n) -> <Matrix>
    {
        if m < 1 || n < 1 {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }

        array a = [];

        array extras = [];
 
        while count(a) < m {
            array rowA = [];
             
            if !empty(extras) {
                let rowA[] = array_pop(extras);
            }
 
            while count(rowA) < n {
                float r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
                float r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
 
                float r = sqrt(-2.0 * log(r1));
 
                float phi = r2 * self::TWO_PI;
 
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
     * Return a random uniformly distributed matrix with values between -1 and 1.
     *
     * @param int m
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function uniform(const int m, const int n) -> <Matrix>
    {
        if m < 1 || n < 1 {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }
    
        array a = [];
    
        while count(a) < m {
            array rowA = [];
    
            while count(rowA) < n {
                let rowA[] = rand(-PHP_INT_MAX, PHP_INT_MAX)
                    / PHP_INT_MAX;
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
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function minimum(const <Matrix> a, const <Matrix> b) -> <Matrix>
    {
        if a->shape() !== b->shape() {
            throw new InvalidArgumentException("Matrix A is " . a->shapeString()
                . " but Matrix B is " . b->shapeString() . ".");
        }

        var i, rowA;

        array c = [];

        for i, rowA in iterator(a) {
            let c[] = array_map("min", rowA, b[i]);
        }

        return self::quick(c);
    }

    /**
     * Return the elementwise maximum of two matrices.
     *
     * @param \Tensor\Matrix a
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function maximum(const <Matrix> a, const <Matrix> b) -> <Matrix>
    {
        if a->shape() !== b->shape() {
            throw new InvalidArgumentException("Matrix A is " . a->shapeString()
                . " but Matrix B is " . b->shapeString() . ".");
        }

        var i, rowA;

        array c = [];

        for i, rowA in iterator(a) {
            let c[] = array_map("max", rowA, b[i]);
        }

        return self::quick(c);
    }

    /**
     * Build a matrix by stacking an array of vectors.
     *
     * @param \Tensor\Vector[] vectors
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function stack(const array vectors) -> <Matrix>
    {
        var vector;

        if empty(vectors) {
            return self::quick();
        }

        var size = reset(vectors)->size();

        array a = [];

        for vector in vectors {
            if likely vector instanceof Vector {
                if unlikely vector->size() !== size {
                    throw new InvalidArgumentException("Vectors must"
                        . " all be the same size.");
                }

                let a[] = vector->asArray();

                continue;
            }

            throw new InvalidArgumentException("Cannot stack a non"
                . " vector, " . gettype(vector) . " found.");
        }

        return self::quick(a);
    }

    /**
     * @param array a
     * @param bool validate
     * @throws \InvalidArgumentException
     */
    public function __construct(array a = [], const bool validate = true)
    {
        var row, value;

        int m = count(a);
        uint n = is_array(current(a)) ? count(current(a)) : 1;

        let n = m === 0 ? 0 : n;
 
        if (validate) {
            let a = array_values(a);
 
            for row in a {
                if unlikely count(row) !== n {
                    throw new InvalidArgumentException("The number of columns"
                        . " must be equal for all rows, " . strval(n)  . " needed but "
                        . count(row) . " given.");
                }
 
                for value in row {
                    if unlikely !is_int(value) && !is_float(value) {
                        throw new InvalidArgumentException("Matrix element must"
                            . " be an integer or float, " . gettype(value)
                            . " given.");
                    }
                }
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
        return Vector::quick(this->offsetGet(index));
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
     * @throws \RuntimeException
     * @return \Tensor\Vector
     */
    public function diagonalAsVector() -> <Vector>
    {
        if !this->isSquare() {
            throw new RuntimeException("Cannot trace diagonal of a"
                . " non square matrix.");
        }

        int i;

        array b = [];

        for i in range(0, this->m - 1) {
            let b[] = this->a[i][i];
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
        uint i;

        array vectors = [];

        for i in range(0, this->m - 1) {
            let vectors[] = ColumnVector::quick(array_column(this->a, i));
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
        return Vector::quick(array_reduce(this->a, "array_merge", []));
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
            let b[] = (int) array_search(min(rowA), rowA);
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
            let b[] = (int) array_search(max(rowA), rowA);
        }

        return ColumnVector::quick(b);
    }

    /**
     * Run a function over all of the elements in the matrix.
     *
     * @param callable callback
     * @return self
     */
    public function map(const callback) -> <Matrix>
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
     * @param mixed initial
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function reduce(const callback, const initial = 0)
    {
        if !is_int(initial) && !is_float(initial) {
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
        uint i;

        array b = [];
 
        for i in range(0, this->n - 1) {
            let b[] = array_column(this->a, i);
        }
 
        return self::quick(b);
    }

    /**
     * Compute the inverse of the matrix.
     *
     * @return self
     */
    public function inverse() -> <Matrix>
    {
        var rowB;

        var b = self::identity(this->m)
            ->augmentLeft(this)
            ->rref();

        array c = [];

        for rowB in iterator(b) {
            let c[] = array_slice(rowB, this->n);
        }

        return self::quick(c);
    }

    /**
     * Calculate the determinant of the matrix.
     *
     * @throws \RuntimeException
     * @return int|float
     */
    public function determinant()
    {
        if !this->isSquare() {
            throw new RuntimeException("Determinant is undefined"
                . " for non square matrices.");
        }

        var ref = this->ref();

        var b = ref[0];
        var swaps = ref[1];

        var pi = b->diagonalAsVector()->product();

        return pi * pow(-1.0, swaps);
    }

    /**
     * Calculate the rank of the matrix i.e the number of pivots in its reduced row
     * echelon form.
     *
     * @return int
     */
    public function rank() -> int
    {
        var row, value;

        var rref = this->rref();

        uint pivots = 0;

        for row in iterator(rref) {
            for value in row {
                if value != 0 {
                    let pivots++;

                    continue;
                }
            }
        }

        return pivots;
    }

    /**
     * Multiply this matrix with another matrix (matrix-matrix product).
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function matmul(const <Matrix> b) -> <Matrix>
    {
        if this->n !== b->m() {
            throw new InvalidArgumentException("Matrix A requires "
                . this->n . " rows but Matrix B has " . b->m() . ".");
        }

        int j;
        float sigma;
        var k, rowA, valueA;

        var p = b->n();

        var bHat = b->transpose()->asArray();
         
        array c = [];
 
        for rowA in this->a {
            array rowC = [];
 
            for j in range(0, p - 1) {
                var columnB = bHat[j];
                 
                let sigma = 0.0;
 
                for k, valueA in rowA {
                    let sigma += valueA * columnB[k];
                }
 
                let rowC[] = sigma;
             }
 
             let c[] = rowC;
         }
         
         return self::quick(c);
    }

    /**
     * Compute the dot product of this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return \Tensor\ColumnVector
     */
    public function dot(const <Vector> b) -> <ColumnVector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        return this->matmul(b->asColumnMatrix())->columnAsVector(0);
    }

    /**
     * Convolve this matrix with another matrix.
     *
     * @param \Tensor\Matrix b
     * @param int stride
     * @throws \InvalidArgumentException
     * @return self
     */
    public function convolve(const <Matrix> b, const int stride = 1) -> <Matrix>
    {
        var m = b->m();
        var n = b->n();

        if m > this->m || n > this->n {
            throw new InvalidArgumentException("Matrix B cannot be"
                . " larger than Matrix A.");
        }

        if stride < 1 {
            throw new InvalidArgumentException("Stride cannot be"
                . " less than 1, " . strval(stride) . " given.");
        }

        uint i, j;
        var k, l, rowB, valueB;

        var p = intdiv(m, 2);
        var q = intdiv(n, 2);

        array c = [];

        for i in range(0, this->m - 1, stride) {
            array rowC = [];

            for j in range(0, this->n - 1, stride) {
                var sigma = 0;

                for k, rowB in iterator(b) {
                    for l, valueB in rowB {
                        int x = i + p - (int) k;
                        int y = j + q - (int) l;

                        if unlikely x < 0 || x >= this->n || y < 0 || y >= this->m {
                            continue;
                        }

                        let sigma += this->a[x][y] * valueB;
                    }
                }

                let rowC[] = sigma;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Calculate the row echelon form (REF) of the matrix. Return the reduced
     * matrix and the number of swaps needed to compute the REF.
     *
     * @return array
     */
    public function ref() -> array
    {
        var ref = Ref::decompose(this);

        var a = ref->a();
        var swaps = ref->swaps();

        return [a, swaps];
    }

    /**
     * Return the reduced row echelon (RREF) form of the matrix.
     *
     * @return self
     */
    public function rref() -> <self>
    {
        var a = Rref::decompose(this)->a();

        return a;
    }

    /**
     * Return the LU decomposition of the matrix in a tuple where l is
     * the lower triangular matrix, u is the upper triangular matrix,
     * and p is the permutation matrix.
     *
     * @throws \RuntimeException
     * @return self[]
     */
    public function lu() -> array
    {
        var lup = Lu::decompose(this);

        var l = lup->l();
        var u = lup->u();
        var p = lup->p();
        
        return [l, u, p];
    }

    /**
     * Compute the eigenvalues and eigenvectors of the matrix and return
     * them in a tuple.
     *
     * @param bool normalize
     * @throws \RuntimeException
     * @return array
     */
    public function eig(bool normalize = true) -> array
    {
        throw new RuntimeException("Not implemented yet.");
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
        int i, j, k;

        let k = this->m - 1;

        var lup = this->lu();

        var l = lup[0];
        var u = lup[1];
        var p = lup[2];

        var pb = p->dot(b);

        array y = [0: pb[0] / (l[0][0] ?: self::EPSILON)];

        for i in range(1, this->m - 1) {
            var sigma = 0.0;

            for j in range(0, i - 1) {
                let sigma += l[i][j] * y[j];
            }

            let y[] = (pb[i] - sigma) / l[i][i];
        }

        array x = [k: y[k] / (l[k][k] ?: self::EPSILON)];

        for i in reverse range(0, this->m - 2) {
            var sigma = 0.0;

            for j in range(i + 1, this->m - 1) {
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
    public function l1Norm()
    {
        return this->transpose()->abs()->sum()->max();
    }
 
    /**
     * Return the L2 norm of the matrix.
     *    
     * @return int|float
     */
    public function l2Norm()
    {
        return sqrt(this->square()->sum()->sum());
    }
 
    /**
     * Retrn the infinity norm of the matrix.
     *
     * @return int|float
     */
    public function infinityNorm()
    {
        return this->abs()->sum()->max();
    }
 
    /**
     * Return the max norm of the matrix.
     *
     * @return int|float
     */
    public function maxNorm()
    {
        return this->abs()->max()->max();
    }

    /**
     * A universal function to multiply this matrix with another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function multiply(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->multiplyMatrix(b);

                case b instanceof ColumnVector:
                    return this->multiplyColumnVector(b);
                
                case b instanceof Vector:
                    return this->multiplyVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->multiplyScalar(b);
        }

        throw new InvalidArgumentException("Cannot multiply matrix"
            . " by a " . gettype(b) . ".");
    }

    /**
     * A universal function to divide this matrix by another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->divideMatrix(b);

                case b instanceof ColumnVector:
                    return this->divideColumnVector(b);
                
                case b instanceof Vector:
                    return this->divideVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->divideScalar(b);
        }

        throw new InvalidArgumentException("Cannot divide matrix"
            . " by a " . gettype(b) . ".");
    }

    /**
     * A universal function to add this matrix with another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->addMatrix(b);

                case b instanceof ColumnVector:
                    return this->addColumnVector(b);
                
                case b instanceof Vector:
                    return this->addVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->addScalar(b);
        }

        throw new InvalidArgumentException("Cannot add matrix"
            . " with a " . gettype(b) . ".");
    }

    /**
     * A universal function to subtract this matrix from another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->subtractMatrix(b);

                case b instanceof ColumnVector:
                    return this->subtractColumnVector(b);
                
                case b instanceof Vector:
                    return this->subtractVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->subtractScalar(b);
        }

        throw new InvalidArgumentException("Cannot subtract a "
            . gettype(b) . " from matrix.");
    }

    /**
     * A universal function to raise this matrix to the power of another
     * tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->powMatrix(b);

                case b instanceof ColumnVector:
                    return this->powColumnVector(b);
                
                case b instanceof Vector:
                    return this->powVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->powScalar(b);
        }

        throw new InvalidArgumentException("Cannot raise matrix"
            . " to the power of a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the integer modulus of this matrix
     * and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->modMatrix(b);

                case b instanceof ColumnVector:
                    return this->modColumnVector(b);
                
                case b instanceof Vector:
                    return this->modVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->modScalar(b);
        }

        throw new InvalidArgumentException("Cannot mod matrix"
            . " with a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the equality comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function equal(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->equalMatrix(b);

                case b instanceof ColumnVector:
                    return this->equalColumnVector(b);
                
                case b instanceof Vector:
                    return this->equalVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->equalScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare matrix"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the not equal comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function notEqual(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->notEqualMatrix(b);

                case b instanceof ColumnVector:
                    return this->notEqualColumnVector(b);
                
                case b instanceof Vector:
                    return this->notEqualVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->notEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare matrix"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the greater than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greater(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->greaterMatrix(b);

                case b instanceof ColumnVector:
                    return this->greaterColumnVector(b);
                
                case b instanceof Vector:
                    return this->greaterVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->greaterScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare matrix"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the greater than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greaterEqual(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->greaterEqualMatrix(b);

                case b instanceof ColumnVector:
                    return this->greaterEqualColumnVector(b);
                
                case b instanceof Vector:
                    return this->greaterEqualVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->greaterEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare matrix"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the less than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function less(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->lessMatrix(b);

                case b instanceof ColumnVector:
                    return this->lessColumnVector(b);
                
                case b instanceof Vector:
                    return this->lessVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->lessScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare matrix"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the less than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function lessEqual(const b)
    {
        if is_object(b) {
            switch true {
                case b instanceof Matrix:
                    return this->lessEqualMatrix(b);

                case b instanceof ColumnVector:
                    return this->lessEqualColumnVector(b);
                
                case b instanceof Vector:
                    return this->lessEqualVector(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->lessEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare matrix"
            . " to a " . gettype(b) . ".");
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
        return this->powScalar(2);
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
     * Return the logarithm of the matrix in specified base.
     *
     * @param float base
     * @return self
     */
    public function log(const float base = self::M_E) -> <Matrix>
    {
        var row, value;

        array b = [];
 
        for row in this->a {
            array rowB = [];
 
            for value in row {
                let rowB[] = log(value, base);
            }
 
            let b[] = rowB;
        }
 
        return self::quick(b);
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
     * Return the cosine of the matrix.
     *
     * @return self
     */
    public function cos() -> <Matrix>
    {
        return this->map("cos");
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
     * @throws \InvalidArgumentException
     * @return \Tensor\ColumnVector
     */
    public function mean() -> <ColumnVector>
    {
        if this->n < 1 {
            throw new RuntimeException("Mean is not defined for"
                . " matrices with less than 1 column.");
        }

        return this->sum()->divide(this->n);
    }

    /**
     * Return the median vector of this matrix.
     *
     * @throws \RuntimeException
     * @return \Tensor\ColumnVector
     */
    public function median() -> <ColumnVector>
    {
        if this->n < 1 {
            throw new RuntimeException("Median is not defined for"
                . " with less than 1 column.");
        }

        var rowA, median;

        array b = [];

        for rowA in this->a {
            var mid = intdiv(this->n, 2);

            sort(rowA);

            if this->n % 2 === 1 {
                let median = rowA[mid];
            } else {
                let median = (rowA[mid - 1] + rowA[mid]) / 2.0;
            }

            let b[] = median;
        }

        return ColumnVector::quick(b);
    }

    /**
     * Return the pth percentile vector of this matrix.
     *
     * @param float p
     * @throws \InvalidArgumentException
     * @throws \RuntimeException
     * @return \Tensor\ColumnVector
     */
    public function percentile(const float p) -> <ColumnVector>
    {
        if p < 0.0 || p > 100.0 {
            throw new InvalidArgumentException("P must be between"
                . " 0 and 100, " . strval(p) . " given.");
        }

        if this->n < 1 {
            throw new RuntimeException("Percentile is not defined for"
                . " with less than 1 column.");
        }

        var rowA;

        array b = [];

        for rowA in this->a {
            sort(rowA);

            float x = (p / 100) * (this->n - 1) + 1;

            int xHat = (int) x;
    
            float remainder = x - xHat;
    
            var t = rowA[xHat - 1];
    
            let b[] = (float) t + remainder * (rowA[xHat] - t);
        }

        return ColumnVector::quick(b);
    }

    /**
     * Compute the row variance of the matrix and return it in a tuple along
     * with the mean.
     *
     * @return \Tensor\ColumnVector
     */
    public function variance() -> <ColumnVector>
    {
        return this->subtract(this->mean())
            ->square()
            ->sum()
            ->divide(this->m);
    }

    /**
     * Compute the covariance of this matrix and return it in a tuple along with
     * the computed mean.
     *
     * @return self
     */
    public function covariance() -> <Matrix>
    {
        var b = this->subtract(this->mean());

        return b->matmul(b->transpose())
            ->divide(this->m);
    }

    /**
     * Round the elements in the matrix to a given decimal place.
     *
     * @param int precision
     * @return self
     */
    public function round(const int precision = 0) -> <Matrix>
    {
        if precision < 0 {
            throw new InvalidArgumentException("Decimal precision cannot"
                . " be less than 0, ". strval(precision) . " given.");
        }

        var row, value;

        array b = [];

        for row in this->a {
            array rowB = [];

            for value in row {
                let rowB[] = round(value, precision);
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
     * @throws \InvalidArgumentException
     * @return self
     */
    public function clip(const float min, const float max) -> <Matrix>
    {
        if min > max {
            throw new InvalidArgumentException("Minimum cannot be"
                . " greater than maximum.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

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

        for rowA in this->a {
            array rowB = [];

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

        for rowA in this->a {
            array rowB = [];

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

        for rowA in this->a {
            array rowB = [];

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

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = -valueA;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Exclude a row from the matrix.
     *
     * @param int index
     * @return self
     */
    public function rowExclude(const int index) -> <Matrix>
    {
        var b = this->a;

        unset(b[index]);

        return self::quick(array_values(b));
    }

    /**
     * Exclude a column from the matrix.
     *
     * @param int index
     * @return self
     */
    public function columnExclude(const int index) -> <Matrix>
    {
        var rowA;

        array b = [];

        for rowA in this->a {
            unset(rowA[index]);

            let b[] = array_values(rowA);
        }

        return self::quick(b);
    }

    /**
     * Attach matrix b above this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentAbove(const <Matrix> b) -> <Matrix>
    {
        if this->m > 0 && b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires"
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        return self::quick(array_merge(b->asArray(), this->a));
    }

    /**
     * Attach matrix b below this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentBelow(const <Matrix> b) -> <Matrix>
    {
        if this->m > 0 && b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires"
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        return self::quick(array_merge(this->a, b->asArray()));
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentLeft(const <Matrix> b) -> <Matrix>
    {
        if this->m > 0 && b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires"
                . (string) this->m . " rows but Matrix B has "
                . (string) b->m() . ".");
        }

        return self::quick(array_map("array_merge", b->asArray(), this->a));
    }

    /**
     * Attach matrix b to the left of this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentRight(const <Matrix> b) -> <Matrix>
    {
        if this->m > 0 && b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires"
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
     * @throws \InvalidArgumentException
     * @return self
     */
    public function repeat(int m = 1, int n = 1) -> <Matrix>
    {
        if m < 1 || n < 1 {
            throw new InvalidArgumentException("Cannot repeat less than"
                . " 1 row or column.");
        }

        uint j;
        var i, rowA;

        var b = this->a;

        let n -= 1;

        if n > 0 {
            for i, rowA in this->a {
                for j in range(0, n - 1) {
                    let b[i] = array_merge(b[i], rowA);
                }
            }
        }

        array c = [];

        for i in range(0, m - 1) {
            let c = array_merge(c, b);
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise product between this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA * rowB[j];
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the division of two elements, element-wise.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA / rowB[j];
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Add this matrix together with another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA + rowB[j];
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Subtract a matrix from this matrix element-wise.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA - rowB[j];
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Raise this matrix to the power of the elementwise entry in another
     * matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = pow(valueA, rowB[j]);
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Calculate the modulus i.e remainder of division between this matri and
     * another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA % rowB[j];
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and
     * another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA == rowB[j] ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and
     * another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA != rowB[j] ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix
     * and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA > rowB[j] ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            
            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA >= rowB[j] ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix
     * and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA < rowB[j] ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and another matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualMatrix(const <Matrix> b) -> <Matrix>
    {
        if b->shape() !== this->shape() {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , valueA;

        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];

            array rowC = [];

            for j, valueA in rowA {
                let rowC[] = valueA <= rowB[j] ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Multiply this matrix by a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, rowA, valueB;

        array c = [];
    
        for rowA in this->a {
            array rowC = [];
    
            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] * valueB;
            }
    
            let c[] = rowC;
        }
    
        return self::quick(c);
    }

    /**
     * Divide this matrix by a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, rowA, valueB;

        array c = [];
    
        for rowA in this->a {
            array rowC = [];
    
            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] / valueB;
            }
    
            let c[] = rowC;
        }
    
        return self::quick(c);
    }

    /**
     * Add this matrix by a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, rowA, valueB;

        array c = [];
    
        for rowA in this->a {
            array rowC = [];
    
            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] + valueB;
            }
    
            let c[] = rowC;
        }
    
        return self::quick(c);
    }

    /**
     * Subtract a vector from this matrix.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, rowA, valueB;

        array c = [];
    
        for rowA in this->a {
            array rowC = [];
    
            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] - valueB;
            }
    
            let c[] = rowC;
        }
    
        return self::quick(c);
    }

    /**
     * Raise this matrix to the power of a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, rowA, valueB;

        array c = [];
    
        for rowA in this->a {
            array rowC = [];
    
            for j, valueB in iterator(b) {
                let rowC[] = pow(rowA[j], valueB);
            }
    
            let c[] = rowC;
        }
    
        return self::quick(c);
    }

    /**
     * Calculate the modulus of this matrix with a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, rowA, valueB;

        array c = [];
    
        for rowA in this->a {
            array rowC = [];
    
            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] % valueB;
            }
    
            let c[] = rowC;
        }
    
        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a
     * vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function equalVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, rowA, valueB;

        array c = [];

        for rowA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] == valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a
     * vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function notEqualVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, rowA, valueB;

        array c = [];

        for rowA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] != valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix
     * and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function greaterVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, rowA, valueB;

        array c = [];

        for rowA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] > valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function greaterEqualVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, rowA, valueB;

        array c = [];

        for rowA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] >= valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix
     * and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function lessVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, rowA, valueB;

        array c = [];

        for rowA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] < valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function lessEqualVector(const <Vector> b) -> <Matrix>
    {
        if b->n() !== this->n {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, rowA, valueB;

        array c = [];

        for rowA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = rowA[j] <= valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Multiply this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA * valueB;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Divide this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA / valueB;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Add this matrix to a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA + valueB;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Subtract a column vector from this matrix.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA - valueB;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Raise this matrix to the power of a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = pow(valueA, valueB);
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Mod this matrix with a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA % valueB;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA == valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA != valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA > valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA >= valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this matrix and
     * a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA < valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a column vector.
     *
     * @param \Tensor\ColumnVector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualColumnVector(const <ColumnVector> b) -> <Matrix>
    {
        if b->m() !== this->m {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var i, rowA, valueA, valueB;

        array c = [];

        for i, rowA in this->a {
            let valueB = b[i];
            
            array rowC = [];

            for valueA in rowA {
                let rowC[] = valueA <= valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return self::quick(c);
    }

    /**
     * Multiply this matrix by a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA * scalar;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Divide this matrix by a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA / scalar;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Add this matrix by a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA + scalar;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Subtract a scalar from this matrix.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA - scalar;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Raise the matrix to a given scalar power.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = pow(valueA, scalar);
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Calculate the modulus of this matrix with a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA % scalar;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise equality comparison of this matrix and a
     * scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA == scalar ? 1 : 0;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise not equal comparison of this matrix and a
     * scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA != scalar ? 1 : 0;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise greater than comparison of this matrix and a
     * scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA > scalar ? 1 : 0;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this matrix and a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA >= scalar ? 1 : 0;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise less than comparison of this matrix and a
     * scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;

        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA < scalar ? 1 : 0;
            }

            let b[] = rowB;
        }

        return self::quick(b);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this matrix and a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualScalar(const scalar) -> <Matrix>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var rowA, valueA;
        
        array b = [];

        for rowA in this->a {
            array rowB = [];

            for valueA in rowA {
                let rowB[] = valueA <= scalar ? 1 : 0;
            }

            let b[] = rowB;
        }

        return self::quick(b);
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
     * @throws \RuntimeException
     */
    public function offsetSet(index, values) -> void
    {
        throw new RuntimeException("Matrix cannot be mutated directly.");
    }

    /**
     * Does a given column exist in the matrix.
     *
     * @param mixed index
     * @return bool
     */
    public function offsetExists(const index) -> bool
    {
        return isset(this->a[index]);
    }

    /**
     * @param mixed index
     * @throws \RuntimeException
     */
    public function offsetUnset(index) -> void
    {
        throw new RuntimeException("Matrix cannot be mutated directly.");
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param mixed index
     * @throws \InvalidArgumentException
     * @return array
     */
    public function offsetGet(const index) -> array
    {
        var value;

        if fetch value, this->a[index] {
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
        return trim(array_reduce(this->a, ["Tensor\\Matrix", "implodeRow"], ""));
    }

    /**
     * Implode a row of the matrix and return the output.
     *
     * @param string carry
     * @param array row
     * @return string
     */
    protected function implodeRow(string carry, array row) -> string
    {
        return carry . PHP_EOL . "[ " . implode(" ", row) . " ]";
    }
}