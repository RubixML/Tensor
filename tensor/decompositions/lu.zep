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
class Lu implements Decomposition
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
        if !a->isSquare() {
            throw new RuntimeException("Cannot decompose a non square matrix.");
        }

        int i, j, k, row;
        float sigma;
        var max, temp;

        var n = a->n();

        var l = Matrix::identity(n)->asArray();
        var u = Matrix::zeros(n, n)->asArray();
        var p = Matrix::identity(n)->asArray();

        for i in range(0, n - 1) {
            let max = a[i][i];

            let row = i;

            for j in range(i, n - 1) {
                if a[j][i] > max {
                    let max = a[j][i];

                    let row = j;
                }
            }

            if i !== row {
                let temp = p[i];

                let p[i] = p[row];
                let p[row] = temp;
            }
        }

        let p = Matrix::quick(p);

        var pa = p->matmul(a);

        for i in range(0, n - 1) {
            for j in range(0, i) {
               let sigma = 0.0;

                for k in range(0, j - 1) {
                    let sigma += u[k][i] * l[j][k];
                }

                let u[j][i] = (float) pa[j][i] - sigma;
            }

            for j in range(i, n - 1) {
                let sigma = 0.0;

                for k in range(0, i - 1) {
                    let sigma += u[k][i] * l[j][k];
                }

                let l[j][i] = ((float) pa[j][i] - sigma)
                    / (u[i][i] ?: self::EPSILON);
            }
        }

        let l = Matrix::quick(l);
        let u = Matrix::quick(u);

        return new self(l, u, p);
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
