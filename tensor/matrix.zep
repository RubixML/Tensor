namespace Tensor;

use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;

/**
 * Matrix
 *
 * A two dimensional (rank 2) tensor with integer and/or floating point elements.
 *
 * @category    Machine Learning
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Matrix implements Tensor
{
    /**
     * A small number used in substitution of 0.
     */
    const EPSILON = 0.000000001;

    /**
     * Two multiplied by pi.
     */
    const TWO_PI = 6.28318530718;

    const M_E = 2.71828;

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
    public static function identity(int n) -> <Matrix>
    {
        if (n < 1) {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 on all axes.");
        }
 
        uint i, j;
        array a, temp = [];
 
        for i in range(0, n - 1) {
            let temp = [];
 
            for j in range(0, n - 1) {
                let temp[] = i === j ? 1 : 0;
            }
 
            let a[] = temp;
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
    public static function zeros(int m, int n) -> <Matrix>
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
    public static function ones(int m, int n) -> <Matrix>
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
    public static function diagonal(array elements) -> <Matrix>
    {
        int i, j;
        int n = count(elements);
        var element;
 
        if (n < 1) {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 on all axes.");
        }
 
        for element in elements {
            if (!is_int(element) && !is_float(element)) {
                throw new InvalidArgumentException("Diagonal element"
                    . " must be an integer or floating point number, "
                    . gettype(element) . " given.");
            }
        }
 
        array a = [];
 
        for i in range(0, n - 1) {
             array temp = [];
 
            for j in range(0, n - 1) {
                let temp[] = i === j ? elements[i] : 0;
            }
 
            let a[] = temp;
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
    public static function fill(value, int m, int n) -> <Matrix>
    {
        if (!is_int(value) && !is_float(value)) {
            throw new InvalidArgumentException("Value must be an"
                . " integer or floating point number, "
                . gettype(value) . " given.");
        }
 
        if (m < 1 || n < 1) {
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
    public static function rand(int m, int n) -> <Matrix>
    {
        if (m < 1 || n < 1) {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }
 
        uint i, j;
        array a = [];
 
        for i in range(0, m - 1) {
            array temp = [];
 
            for j in range(0, m - 1) {
                let temp[] = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            }
 
            let a[] = temp;
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
    public static function gaussian(int m, int n) -> <Matrix>
    {
        if (m < 1 || n < 1) {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }
 
        uint i, j;
        array a = [], extras = [];
 
        for i in range(0, m - 1) {
            array temp = [];
             
            if (!empty(extras)) {
                let temp[] = array_pop(extras);
            }
 
            for j in range(0, n - 1, 2) {
                float r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
                float r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
 
                float r = sqrt(-2.0 * log(r1));
 
                float phi = r2 * self::TWO_PI;
 
                let temp[] = r * sin(phi);
                let temp[] = r * cos(phi);
             }
 
             if (count(temp) > n) {
                let extras[] = array_pop(temp);
             }
 
             let a[] = temp;
         }
 
         return self::quick(a);
     }

    /**
     * Return a random uniformly distributed matrix with mean 0 and unit
     * variance.
     *
     * @param int m
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function uniform(int m, int n) -> <Matrix>
    {
        if (m < 1 || n < 1) {
            throw new InvalidArgumentException("Dimensionality must be"
                . " greater than 0 for all axes.");
        }

        uint i, j;
        array a, temp;
    
        let a = [];
    
        for i in range(0, m - 1) {
            let temp = [];
    
            for j in range(0, n - 1) {
                let temp[] = rand(-PHP_INT_MAX, PHP_INT_MAX) / PHP_INT_MAX;
            }
    
            let a[] = temp;
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
    public static function minimum(<Matrix> a, <Matrix> b) -> <Matrix>
    {
        if (a->shape() !== b->shape()) {
            throw new InvalidArgumentException("Matrix A is " . a->shapeString()
                . " but Matrix B is " . b->shapeString() . ".");
        }

        var i, row;
        array c = [];

        for i, row in a {
            let c[] = array_map("min", row, b[i]);
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
    public static function maximum(<Matrix> a, <Matrix> b) -> <Matrix>
    {
        if (a->shape() !== b->shape()) {
            throw new InvalidArgumentException("Matrix A is " . a->shapeString()
                . " but Matrix B is " . b->shapeString() . ".");
        }

        var i, row;
        array c = [];

        for i, row in a {
            let c[] = array_map("max", row, b[i]);
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
    public static function stack(array vectors) -> <Matrix>
    {
        var vector;
        array a = [];

        for vector in vectors {
            if (!(vector instanceof Vector)) {
                throw new InvalidArgumentException("Cannot stack a non"
                    . " vector, " . gettype(vector) . " found.");
            }

            let a[] = vector->asArray();
        }

        return self::quick(a);
    }

    /**
     * @param array a
     * @param bool validate
     * @throws \InvalidArgumentException
     */
    public function __construct(array a = [], bool validate = true)
    {
        uint m, n;
        var row, value;

        let m = count(a);
 
        let n = is_array(current(a)) ? count(current(a)) : 1;
        let n = m === 0 ? 0 : n;
 
        if (validate) {
            let a = array_values(a);
 
            for row in a {
                if (count(row) !== n) {
                    throw new InvalidArgumentException("The number of columns"
                        . " must be equal for all rows, " . strval(n)  . " needed but "
                        . count(row) . " given.");
                }
 
                for value in row {
                    if (!is_int(value) && !is_float(value)) {
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
    public function row(int index) -> array
    {
        return this->offsetGet(index);
    }

    /**
     * Return a row as a vector from the matrix.
     *
     * @param int index
     * @return \Tensor\Vector
     */
    public function rowAsVector(int index) -> <Vector>
    {
        return Vector::quick(this->offsetGet(index));
    }

    /**
     * Return a column from the matrix.
     *
     * @param int index
     * @return (int|float)[]
     */
    public function column(int index) -> array
    {
        return array_column(this->a, index);
    }

    /**
     * Return a column as a vector from the matrix.
     *
     * @param int index
     * @return \Tensor\ColumnVector
     */
    public function columnAsVector(int index) -> <ColumnVector>
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
        if (!this->isSquare()) {
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
        var row;
        array b = [];

        for row in this->a {
            let b[] = (int) array_search(min(row), row);
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
        var row;
        array b = [];

        for row in this->a {
            let b[] = (int) array_search(max(row), row);
        }

        return ColumnVector::quick(b);
    }

    /**
     * Run a function over all of the elements in the matrix.
     *
     * @param callable callback
     * @return self
     */
    public function map(callback) -> <Matrix>
    {
        var row;
        array b = [];
 
        for row in this->a {
            let b[] = array_map(callback, row);
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
    public function reduce(callback, initial = 0)
    {
        if (!is_int(initial) && !is_float(initial)) {
            throw new InvalidArgumentException("Initial value must"
                . " be an integer or floating point number, "
                . gettype(initial) . " given.");
        }
 
        var row, value;
        var carry = initial;
 
        for row in this->a {
            for value in row {
                let carry = {callback}(value, carry);
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
     * Multiply this matrix with another matrix (matrix-matrix product).
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function matmul(<Matrix> b) -> <Matrix>
    {
        uint i;
        float sigma;
        var j, row, value;

        if (this->n !== b->m()) {
            throw new InvalidArgumentException("Matrix A requires "
                . this->n . " rows but Matrix B has " . b->m() . ".");
        }
 
        var bHat = b->asArray();
        var p = b->n();
         
        array c = [];
 
        for row in this->a {
            array temp = [];
 
            for i in range(0, p - 1) {
                var column = array_column(bHat, i);
                 
                let sigma = 0;
 
                for j, value in row {
                    let sigma += value * column[j];
                }
 
                let temp[] = sigma;
             }
 
             let c[] = temp;
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
    public function dot(<Vector> b) -> <ColumnVector>
    {
        if (this->n !== b->size()) {
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
    public function convolve(<Matrix> b, int stride = 1) -> <Matrix>
    {
        int i, j;
        var k, l, rowB, valueB;

        var m = b->m();
        var n = b->n();

        if (m > this->m || n > this->n) {
            throw new InvalidArgumentException("Matrix B cannot be"
                . " larger than Matrix A.");
        }

        if (stride < 1) {
            throw new InvalidArgumentException("Stride cannot be"
                . " less than 1, " . strval(stride) . " given.");
        }

        var p = intdiv(m, 2);
        var q = intdiv(n, 2);

        array c = [];

        for i in range(0, this->m - 1, stride) {
            array temp = [];

            for j in range(0, this->n - 1, stride) {
                var sigma = 0;

                for k, rowB in b {
                    for l, valueB in rowB {
                        int x = i + p - (int) k;
                        int y = j + q - (int) l;

                        if (x < 0 || x >= this->n || y < 0 || y >= this->m) {
                            continue;
                        }

                        let sigma += this->a[x][y] * valueB;
                    }
                }

                let temp[] = sigma;
            }

            let c[] = temp;
        }

        return self::quick(c);
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
    public function multiply(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->multiplyMatrix(b);

            case b instanceof ColumnVector:
                return this->multiplyColumnVector(b);
            
            case b instanceof Vector:
                return this->multiplyVector(b);

            case is_int(b) || is_float(b):
                return this->multiplyScalar(b);

            default:
                throw new InvalidArgumentException("Cannot multiply matrix"
                    . " by a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to divide this matrix by another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->divideMatrix(b);

            case b instanceof ColumnVector:
                return this->divideColumnVector(b);
            
            case b instanceof Vector:
                return this->divideVector(b);

            case is_int(b) || is_float(b):
                return this->divideScalar(b);

            default:
                throw new InvalidArgumentException("Cannot divide matrix"
                    . " by a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to add this matrix with another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->addMatrix(b);

            case b instanceof ColumnVector:
                return this->addColumnVector(b);
            
            case b instanceof Vector:
                return this->addVector(b);

            case is_int(b) || is_float(b):
                return this->addScalar(b);

            default:
                throw new InvalidArgumentException("Cannot add matrix"
                    . " with a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to subtract this matrix from another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->subtractMatrix(b);

            case b instanceof ColumnVector:
                return this->subtractColumnVector(b);
                
            case b instanceof Vector:
                return this->subtractVector(b);

            case is_int(b) || is_float(b):
                return this->subtractScalar(b);

            default:
                throw new InvalidArgumentException("Cannot subtract a "
                    . gettype(b) . " from matrix.");
        }
    }

    /**
     * A universal function to raise this matrix to the power of another
     * tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->powMatrix(b);

            case b instanceof ColumnVector:
                return this->powColumnVector(b);
            
            case b instanceof Vector:
                return this->powVector(b);

            case is_int(b) || is_float(b):
                return this->powScalar(b);

            default:
                throw new InvalidArgumentException("Cannot raise matrix"
                    . " to the power of a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the integer modulus of this matrix
     * and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->modMatrix(b);
            
            case b instanceof ColumnVector:
                return this->modColumnVector(b);
            
            case b instanceof Vector:
                return this->modVector(b);

            case is_int(b) || is_float(b):
                return this->modScalar(b);

            default:
                throw new InvalidArgumentException("Cannot mod matrix"
                    . " with a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the equality comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function equal(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->equalMatrix(b);

            case b instanceof ColumnVector:
                return this->equalColumnVector(b);

            case b instanceof Vector:
                return this->equalVector(b);

            case is_int(b) || is_float(b):
                return this->equalScalar(b);

            default:
                throw new InvalidArgumentException("Cannot compare matrix"
                    . " to a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the not equal comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function notEqual(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->notEqualMatrix(b);

            case b instanceof ColumnVector:
                return this->notEqualColumnVector(b);

            case b instanceof Vector:
                return this->notEqualVector(b);

            case is_int(b) || is_float(b):
                return this->notEqualScalar(b);

            default:
                throw new InvalidArgumentException("Cannot compare matrix"
                    . " to a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the greater than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greater(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->greaterMatrix(b);

            case b instanceof ColumnVector:
                return this->greaterColumnVector(b);

            case b instanceof Vector:
                return this->greaterVector(b);

            case is_int(b) || is_float(b):
                return this->greaterScalar(b);

            default:
                throw new InvalidArgumentException("Cannot compare matrix"
                    . " to a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the greater than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greaterEqual(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->greaterEqualMatrix(b);

            case b instanceof ColumnVector:
                return this->greaterEqualColumnVector(b);

            case b instanceof Vector:
                return this->greaterEqualVector(b);

            case is_int(b) || is_float(b):
                return this->greaterEqualScalar(b);

            default:
                throw new InvalidArgumentException("Cannot compare matrix"
                    . " to a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the less than comparison of
     * this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function less(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->lessMatrix(b);
            
            case b instanceof ColumnVector:
                return this->lessColumnVector(b);

            case b instanceof Vector:
                return this->lessVector(b);

            case is_int(b) || is_float(b):
                return this->lessScalar(b);

            default:
                throw new InvalidArgumentException("Cannot compare matrix"
                    . " to a " . gettype(b) . ".");
        }
    }

    /**
     * A universal function to compute the less than or equal to
     * comparison of this matrix and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function lessEqual(b)
    {
        switch (true) {
            case b instanceof Matrix:
                return this->lessEqualMatrix(b);

            case b instanceof ColumnVector:
                return this->lessEqualColumnVector(b);
            
            case b instanceof Vector:
                return this->lessEqualVector(b);

            case is_int(b) || is_float(b):
                return this->lessEqualScalar(b);

            default:
                throw new InvalidArgumentException("Cannot compare matrix"
                    . " to a " . gettype(b) . ".");
        }
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
    public function log(float base = self::M_E) -> <Matrix>
    {
        var row, value;
        array b = [];
 
        for row in this->a {
            array temp = [];
 
            for value in row {
                let temp[] = log(value, base);
            }
 
            let b[] = temp;
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
    public function degrees() -> <Matrix>
    {
        return this->map("rad2deg");
    }
 
    /**
     * Convert angles from degrees to radians.
     *
     * @return self
     */
    public function radians() -> <Matrix>
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
        if (this->n < 1) {
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
        if (this->n < 1) {
            throw new RuntimeException("Median is not defined for"
                . " with less than 1 column.");
        }

        var row, median;
        array b = [];

        for row in this->a {
            var mid = intdiv(this->n, 2);

            sort(row);

            if (this->n % 2 === 1) {
                let median = row[mid];
            } else {
                let median = (row[mid - 1] + row[mid]) / 2.0;
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
    public function percentile(float p) -> <ColumnVector>
    {
        if (p < 0.0 || p > 100.0) {
            throw new InvalidArgumentException("P must be between"
                . " 0 and 100, " . strval(p) . " given.");
        }

        if (this->n < 1) {
            throw new RuntimeException("Percentile is not defined for"
                . " with less than 1 column.");
        }

        var row;
        array b = [];

        for row in this->a {
            sort(row);

            float x = (p / 100) * (this->n - 1) + 1;

            int xHat = (int) x;
    
            float remainder = x - xHat;
    
            var t = row[xHat - 1];
    
            let b[] = t + remainder * (row[xHat] - t);
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
     * @throws \InvalidArgumentException
     * @return self
     */
    public function round(int precision = 0) -> <Matrix>
    {
        if (precision < 0) {
            throw new InvalidArgumentException("Decimal precision cannot"
                . " be less than 0, " . strval(precision) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = round(value, precision);
            }

            let b[] = temp;
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
    public function clip(float min, float max) -> <Matrix>
    {
        if (min > max) {
            throw new InvalidArgumentException("Minimum cannot be"
                . " greater than maximum.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                if (value > max) {
                    let temp[] = max;

                    continue;
                }

                if (value < min) {
                    let temp[] = min;

                    continue;
                }

                let temp[] = value;
            }

            let b[] = temp;
        }

        return self::quick(b);
    }

    /**
     * Clip the tensor to be lower bounded by a given minimum.
     *
     * @param float min
     * @return self
     */
    public function clipLower(float min) -> <Matrix>
    {
        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                if (value < min) {
                    let temp[] = min;

                    continue;
                }

                let temp[] = value;
            }

            let b[] = temp;
        }

        return self::quick(b);
    }

    /**
     * Clip the tensor to be upper bounded by a given maximum.
     *
     * @param float max
     * @return self
     */
    public function clipUpper(float max) -> <Matrix>
    {
        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                if (value > max) {
                    let temp[] = max;

                    continue;
                }

                let temp[] = value;
            }

            let b[] = temp;
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
        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                if (value > 0) {
                    let temp[] = 1;
                } elseif (value < 0) {
                    let temp[] = -1;
                } else {
                    let temp[] = 0;
                }
            }

            let b[] = temp;
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
        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = -value;
            }

            let b[] = temp;
        }

        return self::quick(b);
    }

    /**
     * Exclude a row from the matrix.
     *
     * @param int index
     * @return self
     */
    public function rowExclude(int index) -> <Matrix>
    {
        var b = this->a;

        unset(b[index]);

        return self::quick(array_values(b));
    }

    /**
     * Attach matrix b above this matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function augmentAbove(<Matrix> b) -> <Matrix>
    {
        if (this->m > 0 && b->n() !== this->n) {
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
    public function augmentBelow(<Matrix> b) -> <Matrix>
    {
        if (this->m > 0 && b->n() !== this->n) {
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
    public function augmentLeft(<Matrix> b) -> <Matrix>
    {
        if (this->m > 0 && b->m() !== this->m) {
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
    public function augmentRight(<Matrix> b) -> <Matrix>
    {
        if (this->m > 0 && b->m() !== this->m) {
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
        if (m < 1 || n < 1) {
            throw new InvalidArgumentException("Cannot repeat less than"
                . " 1 row or column.");
        }

        var i, row;
        uint j;

        var b = this->a;

        let n -= 1;

        if (n > 0) {
            for i, row in this->a {
                for j in range(0, n - 1) {
                    let b[i] = array_merge(b[i], row);
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
    protected function multiplyMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value * rowB[j];
            }

            let c[] = temp;
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
    protected function divideMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value / rowB[j];
            }

            let c[] = temp;
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
    protected function addMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value + rowB[j];
            }

            let c[] = temp;
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
    protected function subtractMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value - rowB[j];
            }

            let c[] = temp;
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
    protected function powMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = pow(value, rowB[j]);
            }

            let c[] = temp;
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
    protected function modMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value % rowB[j];
            }

            let c[] = temp;
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
    protected function equalMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value == rowB[j] ? 1 : 0;
            }

            let c[] = temp;
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
    protected function notEqualMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value != rowB[j] ? 1 : 0;
            }

            let c[] = temp;
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
    protected function greaterMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value > rowB[j] ? 1 : 0;
            }

            let c[] = temp;
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
    protected function greaterEqualMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value >= rowB[j] ? 1 : 0;
            }

            let c[] = temp;
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
    protected function lessMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value < rowB[j] ? 1 : 0;
            }

            let c[] = temp;
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
    protected function lessEqualMatrix(<Matrix> b) -> <Matrix>
    {
        if (b->shape() !== this->shape()) {
            throw new InvalidArgumentException(this->shapeString()
                . " matrix needed but " . b->shapeString() . " given.");
        }

        var i, j, rowA , value;
        array c = [];

        for i, rowA in this->a {
            var rowB = b[i];
            array temp = [];

            for j, value in rowA {
                let temp[] = value <= rowB[j] ? 1 : 0;
            }

            let c[] = temp;
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
    protected function multiplyVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, row, valueB;
        array c = [];
    
        for row in this->a {
            array temp = [];
    
            for j, valueB in b {
                let temp[] = row[j] * valueB;
            }
    
            let c[] = temp;
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
    protected function divideVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, row, valueB;
        array c = [];
    
        for row in this->a {
            array temp = [];
    
            for j, valueB in b {
                let temp[] = row[j] / valueB;
            }
    
            let c[] = temp;
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
    protected function addVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, row, valueB;
        array c = [];
    
        for row in this->a {
            array temp = [];
    
            for j, valueB in b {
                let temp[] = row[j] + valueB;
            }
    
            let c[] = temp;
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
    protected function subtractVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, row, valueB;
        array c = [];
    
        for row in this->a {
            array temp = [];
    
            for j, valueB in b {
                let temp[] = row[j] - valueB;
            }
    
            let c[] = temp;
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
    protected function powVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, row, valueB;
        array c = [];
    
        for row in this->a {
            array temp = [];
    
            for j, valueB in b {
                let temp[] = pow(row[j], valueB);
            }
    
            let c[] = temp;
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
    protected function modVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }
    
        var j, row, valueB;
        array c = [];
    
        for row in this->a {
            array temp = [];
    
            for j, valueB in b {
                let temp[] = row[j] % valueB;
            }
    
            let c[] = temp;
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
    public function equalVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] == valueB ? 1 : 0;
            }

            let c[] = temp;
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
    public function notEqualVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] != valueB ? 1 : 0;
            }

            let c[] = temp;
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
    public function greaterVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] > valueB ? 1 : 0;
            }

            let c[] = temp;
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
    public function greaterEqualVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] >= valueB ? 1 : 0;
            }

            let c[] = temp;
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
    public function lessVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] < valueB ? 1 : 0;
            }

            let c[] = temp;
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
    public function lessEqualVector(<Vector> b) -> <Matrix>
    {
        if (b->n() !== this->n) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->n . " columns but Vector B has "
                . (string) b->n() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] <= valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function multiplyColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] * valueB;
            }

            let c[] = temp;
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
    protected function divideColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] / valueB;
            }

            let c[] = temp;
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
    protected function addColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] + valueB;
            }

            let c[] = temp;
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
    protected function subtractColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] - valueB;
            }

            let c[] = temp;
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
    protected function powColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = pow(row[j], valueB);
            }

            let c[] = temp;
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
    protected function modColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] % valueB;
            }

            let c[] = temp;
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
    protected function equalColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] == valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function notEqualColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] != valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function greaterColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] > valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function greaterEqualColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] >= valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function lessColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] < valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function lessEqualColumnVector(<ColumnVector> b) -> <Matrix>
    {
        if (b->m() !== this->m) {
            throw new InvalidArgumentException("Matrix A requires "
                . (string) this->m . " rows but Vector B has "
                . (string) b->m() . ".");
        }

        var j, row, valueB;
        array c = [];

        for row in this->a {
            array temp = [];

            for j, valueB in b {
                let temp[] = row[j] <= valueB ? 1 : 0;
            }

            let c[] = temp;
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
    protected function multiplyScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value * scalar;
            }

            let b[] = temp;
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
    protected function divideScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value / scalar;
            }

            let b[] = temp;
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
    protected function addScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value + scalar;
            }

            let b[] = temp;
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
    protected function subtractScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value - scalar;
            }

            let b[] = temp;
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
    protected function powScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = pow(value, scalar);
            }

            let b[] = temp;
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
    protected function modScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value % scalar;
            }

            let b[] = temp;
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
    protected function equalScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value == scalar ? 1 : 0;
            }

            let b[] = temp;
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
    protected function notEqualScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value != scalar ? 1 : 0;
            }

            let b[] = temp;
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
    protected function greaterScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value > scalar ? 1 : 0;
            }

            let b[] = temp;
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
    protected function greaterEqualScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value >= scalar ? 1 : 0;
            }

            let b[] = temp;
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
    protected function lessScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value < scalar ? 1 : 0;
            }

            let b[] = temp;
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
    protected function lessEqualScalar(scalar) -> <Matrix>
    {
        if (!is_int(scalar) && !is_float(scalar)) {
            throw new InvalidArgumentException("Scalar must be an integer or"
                . " floating point number, " . gettype(scalar) . " given.");
        }

        var row, value;
        array b = [];

        for row in this->a {
            array temp = [];

            for value in row {
                let temp[] = value <= scalar ? 1 : 0;
            }

            let b[] = temp;
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
    public function offsetExists(index) -> bool
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
    public function offsetGet(index) -> array
    {
        if (empty(this->a[index])) {
            throw new InvalidArgumentException("Element not found at"
                . " offset " . (string) index . ".");
        }

        return this->a[index];
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
        return trim(array_reduce(this->a, function (carry, row) {
            return carry . PHP_EOL . "[ " . implode(" ", row) . " ]";
        }, ""));
    }
}