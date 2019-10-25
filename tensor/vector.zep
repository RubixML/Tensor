namespace Tensor;

use InvalidArgumentException;
use RuntimeException;
use ArrayIterator;

/**
 * Vector
 *
 * A one dimensional (rank 1) tensor with integer and/or floating point elements..
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Vector implements Tensor
{
    const EPSILON = 0.00000001;

    const M_PI = 3.14159265358979323846;

    const TWO_PI = 6.28318530718;

    const M_E = 2.7182818284590452354;

    /**
     * A 1-d sequential array holding the elements of the vector.
     *
     * @var (int|float)[]
     */
    protected a = [
        //
    ];

    /**
     * The number of elements in the vector.
     *
     * @var int
     */
    protected n;

    /**
     * Factory method to build a new vector from an array.
     *
     * @param array a
     * @return self
     */
    public static function build(array a = [])
    {
        return new self(a, true);
    }

    /**
     * Build a vector foregoing any validation for quicker instantiation.
     *
     * @param array a
     * @return self
     */
    public static function quick(array a = [])
    {
        return new self(a, false);
    }

    /**
     * Build a vector of zeros with n elements.
     *
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function zeros(int n) -> <Vector>
    {
        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }

        return static::fill(0, n);
    }

    /**
     * Build a vector of ones with n elements.
     *
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function ones(int n) -> <Vector>
    {
        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }

        return static::fill(1, n);
    }

    /**
     * Fill a vector with a given value.
     *
     * @param mixed value
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function fill(value, int n) -> <Vector>
    {
        if !is_int(value) && !is_float(value) {
            throw new InvalidArgumentException("Value must be an"
                . " integer or floating point number, "
                . gettype(value) . " given.");
        }

        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }

        return static::quick(array_fill(0, n, value));
    }

    /**
     * Return a random uniform vector with values between 0 and 1.
     *
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function rand(int n) -> <Vector>
    {
        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }

        array a = [];

        while count(a) < n {
            let a[] = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
        }

        return static::quick(a);
    }

    /**
     * Return a standard normally distributed (Gaussian) random vector.
     *
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function gaussian(int n) -> <Vector>
    {
        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }

        array a = [];

        while count(a) < n {
            float r1 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            float r2 = rand(0, PHP_INT_MAX) / PHP_INT_MAX;
            
            float r = sqrt(-2.0 * log(r1));

            float phi = r2 * self::TWO_PI;

            let a[] = r * sin(phi);
            let a[] = r * cos(phi);
        }

        if count(a) > n {
            let a = array_slice(a, 0, n);
        }

        return static::quick(a);
    }

    /**
     * Return a random uniformly distributed vector with values between -1 and 1.
     *
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function uniform(int n) -> <Vector>
    {
        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }
        
        array a = [];

        while count(a) < n {
            let a[] = rand(-PHP_INT_MAX, PHP_INT_MAX)
                / PHP_INT_MAX;
        }

        return static::quick(a);
    }

    /**
     * Return evenly spaced values within a given interval.
     *
     * @param mixed start
     * @param mixed end
     * @param mixed interval
     * @return self
     */
    public static function range(start, end, interval = 1) -> <Vector>
    {
        return static::quick(range(start, end, interval));
    }

    /**
     * Return evenly spaced numbers over a specified interval.
     *
     * @param float start
     * @param float end
     * @param int n
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function linspace(float start, float end, int n) -> <Vector>
    {
        if n < 1 {
            throw new InvalidArgumentException("The number of elements"
                . " must be greater than 0, " . strval(n) . " given.");
        }

        var range = abs(end - start);

        float interval = (range / (n - 1)) - (self::EPSILON * range);

        return static::range(start, end, interval);
    }

    /**
     * Return the elementwise maximum of two vectors.
     *
     * @param \Tensor\Vector a
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function maximum(<Vector> a, <Vector> b) -> <Vector>
    {
        if a->n() !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) a->n() . " elements but Vector B has "
                . (string) b->n() . ".");
        }

        return static::quick(array_map("max", a->asArray(), b->asArray()));
    }

    /**
     * Return the elementwise minimum of two vectors.
     *
     * @param \Tensor\Vector a
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public static function minimum(<Vector> a, <Vector> b) -> <Vector>
    {
        if a->n() !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) a->n() . " elements but Vector B has "
                . (string) b->n() . ".");
        }

        return static::quick(array_map("min", a->asArray(), b->asArray()));
    }

    /**
     * @param array a
     * @param bool validate
     * @throws \InvalidArgumentException
     */
    public function __construct(array a = [], bool validate = true)
    {
        var value; 

        if validate {
            let a = array_values(a);

            for value in a {
                if unlikely !is_int(value) && !is_float(value) {
                    throw new InvalidArgumentException("Element must be"
                        . " an integer or floating point number, "
                        . gettype(value) . " given.");
                }
            }
        }

        let this->a = a;
        let this->n = count(a);
    }

    /**
     * Return a tuple with the dimensionality of the tensor.
     *
     * @return int[]
     */
    public function shape() -> array
    {
        return [this->n];
    }

    /**
     * Return the shape of the tensor as a string.
     *
     * @return string
     */
    public function shapeString() -> string
    {
        return (string) this->n;
    }

    /**
     * Return the number of elements in the vector.
     *
     * @return int
     */
    public function size() -> int
    {
        return this->n;
    }

    /**
     * Return the number of rows in the vector.
     *
     * @return int
     */
    public function m() -> int
    {
        return 1;
    }

    /**
     * Return the number of columns in the vector.
     *
     * @return int
     */
    public function n() -> int
    {
        return this->n;
    }

    /**
     * Return the vector as an array.
     *
     * @return array
     */
    public function asArray() -> array
    {
        return this->a;
    }

    /**
     * Return this vector as a row matrix.
     *
     * @return \Tensor\Matrix
     */
    public function asRowMatrix() -> <Matrix>
    {
        return Matrix::quick([this->a]);
    }

    /**
     * Return this vector as a column matrix.
     *
     * @return \Tensor\Matrix
     */
    public function asColumnMatrix() -> <Matrix>
    {
        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = [valueA];
        }

        return Matrix::quick(b);
    }

    /**
     * Return a matrix in the shape specified.
     *
     * @param int m
     * @param int n
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    public function reshape(int m, int n) -> <Matrix>
    {
        if m < 0 || n < 0 {
            throw new InvalidArgumentException("The number of rows"
                . " and/or columns cannot be less than 0.");
        }

        int nHat = m * n;

        if nHat !== this->n {
            throw new InvalidArgumentException(strval(nHat) . " elements"
                . " are needed but vector only has " . this->n . ".");
        }

        int k = 0;

        array b = [];

        while count(b) < m {
            array rowB = [];

            while count(rowB) < n {
                let rowB[] = this->a[k];

                let k++;
            }

            let b[] = rowB;
        }

        return Matrix::quick(b);
    }

    /**
     * Transpose the vector i.e. rotate it.
     *
     * @return mixed
     */
    public function transpose()
    {
        return ColumnVector::quick(this->a);
    }

    /**
     * Return the index of the minimum element in the vector.
     *
     * @return int
     */
    public function argmin() -> int
    {
        return (int) array_search(min(this->a), this->a);
    }

    /**
     * Return the index of the maximum element in the vector.
     *
     * @return int
     */
    public function argmax() -> int
    {
        return (int) array_search(max(this->a), this->a);
    }

    /**
     * Map a function over the elements in the vector and return a new
     * vector.
     *
     * @param callable callback
     * @return self
     */
    public function map(callback) -> <Vector>
    {
        return static::quick(array_map(callback, this->a));
    }

    /**
     * Reduce the vector down to a scalar.
     *
     * @param callable callback
     * @param mixed initial
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function reduce(callback, initial = 0)
    {
        if !is_int(initial) && !is_float(initial) {
            throw new InvalidArgumentException("Initial value must"
                . " be an integer or floating point number, "
                . gettype(initial) . " given.");
        }

        return array_reduce(this->a, callback, initial);
    }

    /**
     * Compute the dot product of this vector and another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function dot(<Vector> b)
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires"
                . (string) this->n . " elements but vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        var sigma = 0.0;

        for i, valueA in this->a {
            let sigma += valueA * b[i];
        }

        return sigma;
    }

    /**
     * Convolve this vector with another vector.
     *
     * @param \Tensor\Vector b
     * @param int stride
     * @throws \InvalidArgumentException
     * @return self
     */
    public function convolve(<Vector> b, int stride = 1) -> <Vector>
    {
        if b->size() > this->n {
            throw new InvalidArgumentException("Vector B cannot be"
                . " larger than Vector A.");
        }

        if stride < 1 {
            throw new InvalidArgumentException("Stride cannot be"
                . " less than 1, " . strval(stride). " given.");
        }

        uint i;
        var j, valueA, valueB;

        array c = [];

        for i in range(0, this->n - 1, stride) {
            float sigma = 0;

            for j, valueB in iterator(b) {
                int k = i - (int) j;

                if likely fetch valueA, this->a[k] {
                    let sigma += valueA * valueB;
                }
            }

            let c[] = sigma;
        }

        return static::quick(c);
    }

    /**
     * Compute the vector-matrix product of this vector and matrix b.
     *
     * @param \Tensor\Matrix b
     * @return \Tensor\Matrix
     */
    public function matmul(<Matrix> b) -> <Matrix>
    {
        return this->asRowMatrix()->matmul(b);
    }

    /**
     * Return the inner product of two vectors.
     *
     * @param \Tensor\Vector b
     * @return int|float
     */
    public function inner(<Vector> b)
    {
        return this->dot(b);
    }

    /**
     * Calculate the outer product of this and another vector.
     *
     * @param \Tensor\Vector b
     * @return \Tensor\Matrix
     */
    public function outer(<Vector> b) -> <Matrix>
    {
        var j, valueA, valueB;

        var n = b->n();

        array c = [];

        for valueA in this->a {
            array rowC = [];

            for j, valueB in iterator(b) {
                let rowC[] = valueA * valueB;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Calculate the cross product between two 3 dimensional vectors.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    public function cross(<Vector> b) -> <Vector>
    {
        if this->n !== 3 || b->size() !== 3 {
            throw new InvalidArgumentException("Cross product is"
                . " only defined for vectors of 3 dimensions.");
        }

        array c = [];

        let c[] = (this->a[1] * b[2]) - (this->a[2] * b[1]);
        let c[] = (this->a[2] * b[0]) - (this->a[0] * b[2]);
        let c[] = (this->a[0] * b[1]) - (this->a[1] * b[0]);

        return static::quick(c);
    }

    /**
     * Project this vector on another vector.
     *
     * @param \Tensor\Vector b
     * @return self
     */
    public function project(<Vector> b) -> <Vector>
    {
        return b->multiply(this->dot(b) / (pow(b->l2Norm(), 2)));
    }

    /**
     * Calculate the L1 or Manhattan norm of the vector.
     *
     * @return int|float
     */
    public function l1Norm()
    {
        return this->abs()->sum();
    }

    /**
     * Calculate the L2 or Euclidean norm of the vector.
     *
     * @return int|float
     */
    public function l2Norm()
    {
        return sqrt(this->square()->sum());
    }

    /**
     * Calculate the p-norm of the vector.
     *
     * @param float p
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function pNorm(float p = 3.0)
    {
        if p <= 0.0 {
            throw new InvalidArgumentException("P must be greater"
                . " than 0, " . strval(p) . " given.");
        }

        return pow(this->abs()->powScalar(p)->sum(), 1.0 / p);
    }

    /**
     * Calculate the max norm of the vector.
     *
     * @return int|float
     */
    public function maxNorm()
    {
        return this->abs()->max();
    }

    /**
     * A universal function to multiply this vector with another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function multiply(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->multiplyVector(b);

                case b instanceof Matrix:
                    return this->multiplyMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->multiplyScalar(b);
        }

        throw new InvalidArgumentException("Cannot multiply vector"
            . " by a " . gettype(b) . ".");
    }

    /**
     * A universal function to divide this vector by another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function divide(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->divideVector(b);

                case b instanceof Matrix:
                    return this->divideMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->divideScalar(b);
        }

        throw new InvalidArgumentException("Cannot divide vector"
            . " by a " . gettype(b) . ".");
    }

    /**
     * A universal function to add this vector with another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function add(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->addVector(b);

                case b instanceof Matrix:
                    return this->addMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->addScalar(b);
        }

        throw new InvalidArgumentException("Cannot add vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to subtract this vector from another tensor
     * element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function subtract(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->subtractVector(b);

                case b instanceof Matrix:
                    return this->subtractMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->subtractScalar(b);
        }

        throw new InvalidArgumentException("Cannot subtract a "
            . gettype(b) . " from vector.");
    }

    /**
     * A universal function to raise this vector to the power of another
     * tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function pow(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->powVector(b);

                case b instanceof Matrix:
                    return this->powMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->powScalar(b);
        }

        throw new InvalidArgumentException("Cannot raise vector"
            . " to a power of a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the modulus of this vector and
     * another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function mod(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->modVector(b);

                case b instanceof Matrix:
                    return this->modMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->modScalar(b);
        }

        throw new InvalidArgumentException("Cannot mod vector"
            . " with a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the equality comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function equal(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->equalVector(b);

                case b instanceof Matrix:
                    return this->equalMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->equalScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the not equal comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function notEqual(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->notEqualVector(b);

                case b instanceof Matrix:
                    return this->notEqualMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->notEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the greater than comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greater(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->greaterVector(b);

                case b instanceof Matrix:
                    return this->greaterMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->greaterScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the greater than or equal to
     * comparison of this vector and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function greaterEqual(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->greaterEqualVector(b);

                case b instanceof Matrix:
                    return this->greaterEqualMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->greaterEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the less than comparison of
     * this vector and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function less(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->lessVector(b);

                case b instanceof Matrix:
                    return this->lessMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->lessScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * A universal function to compute the less than or equal to
     * comparison of this vector and another tensor element-wise.
     *
     * @param mixed b
     * @throws \InvalidArgumentException
     * @return mixed
     */
    public function lessEqual(b)
    {
        if is_object(b) {
            switch (true) {
                case b instanceof Vector:
                    return this->lessEqualVector(b);

                case b instanceof Matrix:
                    return this->lessEqualMatrix(b);
            }
        }
        
        if is_int(b) || is_float(b) {
            return this->lessEqualScalar(b);
        }

        throw new InvalidArgumentException("Cannot compare vector"
            . " to a " . gettype(b) . ".");
    }

    /**
     * Return the reciprocal of the vector element-wise.
     *
     * @return self
     */
    public function reciprocal() -> <Vector>
    {
        return static::ones(this->n)
            ->divideVector(this);
    }

    /**
     * Return the absolute value of the vector.
     *
     * @return self
     */
    public function abs() -> <Vector>
    {
        return this->map("abs");
    }

    /**
     * Square the vector.
     *
     * @return self
     */
    public function square() -> <Vector>
    {
        return this->powScalar(2);
    }

    /**
     * Take the square root of the vector.
     *
     * @return self
     */
    public function sqrt() -> <Vector>
    {
        return this->map("sqrt");
    }

    /**
     * Exponentiate each element in the vector.
     *
     * @return self
     */
    public function exp() -> <Vector>
    {
        return this->map("exp");
    }

    /**
     * Take the log to the given base of each element in the vector.
     *
     * @param float base
     * @return self
     */
    public function log(float base = self::M_E) -> <Vector>
    {
        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = log(valueA, base);
        }

        return static::quick(b);
    }

    /**
     * Return the sine of this vector.
     *
     * @return self
     */
    public function sin() -> <Vector>
    {
        return this->map("sin");
    }

    /**
     * Return the cosine of this vector.
     *
     * @return self
     */
    public function cos() -> <Vector>
    {
        return this->map("cos");
    }

    /**
     * Return the tangent of this vector.
     *
     * @return self
     */
    public function tan() -> <Vector>
    {
        return this->map("tan");
    }

    /**
     * Convert angles from radians to degrees.
     *
     * @return self
     */
    public function rad2deg() -> <Vector>
    {
        return this->map("rad2deg");
    }

    /**
     * Convert angles from degrees to radians.
     *
     * @return self
     */
    public function deg2rad() -> <Vector>
    {
        return this->map("deg2rad");
    }

    /**
     * The sum of the vector.
     *
     * @return int|float
     */
    public function sum()
    {
        return array_sum(this->a);
    }

    /**
     * Return the product of the vector.
     *
     * @return int|float
     */
    public function product()
    {
        return array_product(this->a);
    }

    /**
     * Return the minimum element in the vector.
     *
     * @return int|float
     */
    public function min()
    {
        return min(this->a);
    }

    /**
     * Return the maximum element in the vector.
     *
     * @return int|float
     */
    public function max()
    {
        return max(this->a);
    }

    /**
     * Return the mean of the vector.
     *
     * @throws \RuntimeException
     * @return int|float
     */
    public function mean()
    {
        if empty(this->a) {
            throw new RuntimeException("Mean is not defined for"
                . " an empty vector.");
        }

        return this->sum() / this->n;
    }

    /**
     * Return the median of the vector.
     *
     * @throws \RuntimeException
     * @return int|float
     */
    public function median()
    {
        if empty(this->a) {
            throw new RuntimeException("Median is not defined for"
                . " an empty vector.");
        }

        var median;

        var mid = intdiv(this->n, 2);

        var a = this->a;

        sort(a);

        if this->n % 2 === 1 {
            let median = a[mid];
        } else {
            let median = (a[mid - 1] + a[mid]) / 2.0;
        }

        return median;
    }

    /**
     * Return the pth percentile of the vector.
     *
     * @param float p
     * @throws \InvalidArgumentException
     * @throws \RuntimeException
     * @return int|float
     */
    public function percentile(float p)
    {
        if p < 0.0 || p > 100.0 {
            throw new InvalidArgumentException("P must be between"
                . " 0 and 100, " . strval(p) . " given.");
        }

        if empty(this->a) {
            throw new RuntimeException("Percentile is not defined for"
                . " an empty vector.");
        }

        var a = this->a;

        sort(a);

        float x = (p / 100) * (this->n - 1) + 1;

        int xHat = (int) x;

        float remainder = x - xHat;

        var t = a[xHat - 1];

        return (float) t + remainder * (a[xHat] - t);
    }

    /**
     * Return the variance of the vector.
     *
     * @return int|float
     */
    public function variance()
    {
        if empty(this->a) {
            throw new RuntimeException("Variance is not defined for"
                . " an empty vector.");
        }

        var ssd = this->subtract(this->mean())
            ->square()
            ->sum();

        return ssd / this->n;
    }

    /**
     * Round the elements in the matrix to a given decimal place.
     *
     * @param int precision
     * @throws \InvalidArgumentException
     * @return self
     */
    public function round(int precision = 0) -> <Vector>
    {
        if precision < 0 {
            throw new InvalidArgumentException("Decimal precision cannot"
                . " be less than 0, " . strval(precision)  . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = round(valueA, precision);
        }

        return static::quick(b);
    }

    /**
     * Round the elements in the vector down to the nearest integer.
     *
     * @return self
     */
    public function floor() -> <Vector>
    {
        return this->map("floor");
    }

    /**
     * Round the elements in the vector up to the nearest integer.
     *
     * @return self
     */
    public function ceil() -> <Vector>
    {
        return this->map("ceil");
    }

    /**
     * Clip the elements in the vector to be between given minimum and maximum
     * and return a new vector.
     *
     * @param float min
     * @param float max
     * @throws \InvalidArgumentException
     * @return self
     */
    public function clip(float min, float max) -> <Vector>
    {
        if min > max {
            throw new InvalidArgumentException("Minimum cannot be"
                . " greater than maximum.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            if valueA > max {
                let b[] = max;

                continue;
            }

            if valueA < min {
                let b[] = min;

                continue;
            }

            let b[] = valueA;
        }

        return static::quick(b);
    }

    /**
     * Clip the tensor to be lower bounded by a given minimum.
     *
     * @param float min
     * @return self
     */
    public function clipLower(float min) -> <Vector>
    {
        var valueA;

        array b = [];
        
        for valueA in this->a {
            if valueA < min {
                let b[] = min;

                continue;
            }

            let b[] = valueA;
        }

        return static::quick(b);
    }

    /**
     * Clip the tensor to be upper bounded by a given maximum.
     *
     * @param float max
     * @return self
     */
    public function clipUpper(float max) -> <Vector>
    {
        var valueA;

        array b = [];

        for valueA in this->a {
            if valueA > max {
                let b[] = max;

                continue;
            }

            let b[] = valueA;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise sign indication.
     *
     * @return self
     */
    public function sign() -> <Vector>
    {
        var valueA;

        array b = [];

        for valueA in this->a {
            if valueA > 0 {
                let b[] = 1;
            } elseif valueA < 0 {
                let b[] = -1;
            } else {
                let b[] = 0;
            }
        }

        return static::quick(b);
    }

    /**
     * Negate the vector i.e take the negative of each value elementwise.
     *
     * @return self
     */
    public function negate() -> <Vector>
    {
        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = -valueA;
        }

        return static::quick(b);
    }

    /**
     * Multiply this vector with a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
     protected function multiplyMatrix(<Matrix> b) -> <Matrix>
     {
         if this->n !== b->n() {
             throw new InvalidArgumentException("Vector A requires "
                 . (string) this->n . " columns but Matrix B has "
                 . (string) b->n() . ".");
         }
 
         var j, rowB, valueB;

         array c = [];
 
         for rowB in iterator(b) {
             array rowC = [];
 
             for j, valueB in rowB {
                 let rowC[] = this->a[j] * valueB;
             }
 
             let c[] = rowC;
         }
 
         return Matrix::quick(c);
     }

    /**
     * Divide this vector with a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function divideMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] / valueB;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Add this vector to a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function addMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] + valueB;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Subtract a matrix from this vector.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function subtractMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] - valueB;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Raise this vector to the power of a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function powMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = pow(this->a[j], valueB);
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Mod this vector with a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function modMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;
        
        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] % valueB;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this vector and a
     * matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function equalMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] == valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this vector and a
     * matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function notEqualMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] != valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this vector
     * and a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function greaterMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] > valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this vector and a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function greaterEqualMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] >= valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this vector
     * and a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function lessMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] < valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this vector and a matrix.
     *
     * @param \Tensor\Matrix b
     * @throws \InvalidArgumentException
     * @return \Tensor\Matrix
     */
    protected function lessEqualMatrix(<Matrix> b) -> <Matrix>
    {
        if this->n !== b->n() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " columns but Matrix B has "
                . (string) b->n() . ".");
        }

        var j, rowB, valueB;

        array c = [];

        for rowB in iterator(b) {
            array rowC = [];

            for j, valueB in rowB {
                let rowC[] = this->a[j] <= valueB ? 1 : 0;
            }

            let c[] = rowC;
        }

        return Matrix::quick(c);
    }

    /**
     * Multiply this vector with another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function multiplyVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA * b[i];
        }

        return static::quick(c);
    }

    /**
     * Divide this vector by another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA / b[i];
        }

        return static::quick(c);
    }

    /**
     * Add this vector to another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA + b[i];
        }

        return static::quick(c);
    }

    /**
     * Subtract a vector from this vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA - b[i];
        }

        return static::quick(c);
    }

    /**
     * Raise this vector to a power of another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function powVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = pow(valueA, b[i]);
        }

        return static::quick(c);
    }

    /**
     * Calculate the modulus of this vector with another vector elementwise.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA % b[i];
        }

        return static::quick(c);
    }

    /**
     * Return the element-wise equality comparison of this vector and a
     * another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA == b[i] ? 1 : 0;
        }

        return static::quick(c);
    }

    /**
     * Return the element-wise not equal comparison of this vector and a
     * another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA != b[i] ? 1 : 0;
        }

        return static::quick(c);
    }

    /**
     * Return the element-wise greater than comparison of this vector
     * and a another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA > b[i] ? 1 : 0;
        }

        return static::quick(c);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this vector and a another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA >= b[i] ? 1 : 0;
        }

        return static::quick(c);
    }

    /**
     * Return the element-wise less than comparison of this vector
     * and a another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA < b[i] ? 1 : 0;
        }

        return static::quick(c);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this vector and a another vector.
     *
     * @param \Tensor\Vector b
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualVector(<Vector> b) -> <Vector>
    {
        if this->n !== b->size() {
            throw new InvalidArgumentException("Vector A requires "
                . (string) this->n . " elements but Vector B has "
                . (string) b->size() . ".");
        }

        var i, valueA;

        array c = [];

        for i, valueA in this->a {
            let c[] = valueA <= b[i] ? 1 : 0;
        }

        return static::quick(c);
    }

    /**
     * Multiply this vector by a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
     protected function multiplyScalar(scalar) -> <Vector>
     {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }
 
        var valueA;

        array b = [];
 
        for valueA in this->a {
            let b[] = valueA * scalar;
        }
 
        return static::quick(b);
    }

    /**
     * Divide this vector by a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function divideScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA / scalar;
        }

        return static::quick(b);
    }

    /**
     * Add a scalar to this vector.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function addScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA + scalar;
        }

        return static::quick(b);
    }

    /**
     * Subtract a scalar from this vector.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function subtractScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA - scalar;
        }

        return static::quick(b);
    }

    /**
     * Raise the vector to a the power of a scalar value.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
     protected function powScalar(scalar) -> <Vector>
     {
         if !is_int(scalar) && !is_float(scalar) {
             throw new InvalidArgumentException("Scalar must be an"
                 . " integnr or floating point number, "
                 . gettype(scalar) . " given.");
         }
     
         var valueA;

         array b = [];
 
         for valueA in this->a {
             let b[] = pow(valueA, scalar);
         }
 
         return static::quick(b);
     }

    /**
     * Calculate the modulus of this vector with a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function modScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA % scalar;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise equality comparison of this vector and a
     * scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function equalScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA == scalar ? 1 : 0;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise not equal comparison of this vector and a
     * scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function notEqualScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA != scalar ? 1 : 0;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise greater than comparison of this vector
     * and a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA > scalar ? 1 : 0;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise greater than or equal to comparison of
     * this vector and a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function greaterEqualScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA >= scalar ? 1 : 0;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise less than comparison of this vector
     * and a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;

        array b = [];

        for valueA in this->a {
            let b[] = valueA < scalar ? 1 : 0;
        }

        return static::quick(b);
    }

    /**
     * Return the element-wise less than or equal to comparison of
     * this vector and a scalar.
     *
     * @param mixed scalar
     * @throws \InvalidArgumentException
     * @return self
     */
    protected function lessEqualScalar(scalar) -> <Vector>
    {
        if !is_int(scalar) && !is_float(scalar) {
            throw new InvalidArgumentException("Scalar must be an"
                . " integnr or floating point number, "
                . gettype(scalar) . " given.");
        }

        var valueA;
        
        array b = [];

        for valueA in this->a {
            let b[] = valueA <= scalar ? 1 : 0;
        }

        return static::quick(b);
    }

    /**
     * Count method to implement countable interface.
     *
     * @return int
     */
    public function count() -> int
    {
        return this->n;
    }

    /**
     * @param mixed index
     * @param array values
     * @throws \RuntimeException
     */
    public function offsetSet(index, values) -> void
    {
        throw new RuntimeException("Vector cannot be mutated directly.");
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
        throw new RuntimeException("Vector cannot be mutated directly.");
    }

    /**
     * Return a row from the matrix at the given index.
     *
     * @param mixed index
     * @throws \InvalidArgumentException
     * @return int|float
     */
    public function offsetGet(index)
    {
        if !isset(this->a[index]) {
            throw new InvalidArgumentException("Element not found at "
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
        return "[ " . implode(" ", this->a) . " ]";
    }
}