namespace Tensor\Decompositions;

use Tensor\Matrix;
use RuntimeException;

/**
 * LU
 *
 * The LU decomposition is a factorization of a Matrix as the product of a
 * lower and upper triangular matrix as well as a permutation matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Lu
{
    const EPSILON = 0.00000001;

    /**
     * The lower triangular matrix.
     *
     * @var \Tensor\Matrix
     */
    protected l;

    /**
     * The upper triangular matrix.
     *
     * @var \Tensor\Matrix
     */
    protected u;

    /**
     * The permutation matrix.
     *
     * @var \Tensor\Matrix
     */
    protected p;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix a
     * @return self
     */
    public static function decompose(const <Matrix> a) -> <Lu>
    {
        if unlikely !a->isSquare() {
            throw new RuntimeException("Cannot decompose a non-square matrix.");
        }

        int i, j, k, row;
        float max, sigma;
        array aHat = [];
        array l = [];
        array u = [];
        array p = [];
        array pa = [];

        var temp, valueA;

        int n = (int) a->n();

        let aHat = (array) a->asArray();

        let l = (array) Matrix::identity(n)->asArray();
        let u = (array) Matrix::zeros(n, n)->asArray();
        let p = (array) Matrix::identity(n)->asArray();

        for i in range(0, n - 1) {
            let max = (float) aHat[i][i];

            let row = i;

            for j in range(i, n - 1) {
                let valueA = aHat[j][i];

                if valueA > max {
                    let max = valueA;
                    let row = j;
                }
            }

            if i !== row {
                let temp = p[i];

                let p[i] = p[row];
                let p[row] = temp;
            }
        }

        let pa = (array) Matrix::quick(p)->matmul(a)->asArray();

        for i in range(0, n - 1) {
            for j in range(0, i) {
               let sigma = 0.0;

                for k in range(0, j - 1) {
                    let sigma += u[k][i] * l[j][k];
                }

                let u[j][i] = pa[j][i] - sigma;
            }

            for j in range(i, n - 1) {
                let sigma = 0.0;

                for k in range(0, i - 1) {
                    let sigma += u[k][i] * l[j][k];
                }

                let l[j][i] = (pa[j][i] - sigma)
                    / (u[i][i] ?: self::EPSILON);
            }
        }

        return new self(
            Matrix::quick(l),
            Matrix::quick(u),
            Matrix::quick(p)
        );
    }

    /**
     * @param \Tensor\Matrix l
     * @param \Tensor\Matrix u
     * @param \Tensor\Matrix p
     */
    public function __construct(const <Matrix> l, const <Matrix> u, const <Matrix> p)
    {
        let this->l = l;
        let this->u = u;
        let this->p = p;
    }

    /**
     * Return the lower triangular matrix.
     *
     * @return \Tensor\Matrix
     */
    public function l() -> <Matrix>
    {
        return this->l;
    }

    /**
     * Return the upper triangular matrix.
     *
     * @return \Tensor\Matrix
     */
    public function u() -> <Matrix>
    {
        return this->u;
    }

    /**
     * Return the permutation matrix.
     *
     * @return \Tensor\Matrix
     */
    public function p() -> <Matrix>
    {
        return this->p;
    }
}
