namespace Tensor\Decompositions;

use Tensor\Matrix;
use RuntimeException;

/**
 * Cholesky
 *
 * An efficient decomposition of a square positive definite matrix into a
 * lower triangular matrix and its conjugate transpose.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Cholesky implements Decomposition
{
    /**
     * The lower triangular matrix.
     * 
     * @var \Tensor\Matrix
     */
    protected l;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix a
     * @return self
     */
    public static function decompose(const <Matrix> a) -> <Cholesky>
    {
        if !a->isSquare() {
            throw new RuntimeException("Cannot Cholesky decompose a"
                . " non square matrix.");
        }

        int i, j, k;
        float sigma;

        var m = a->m();

        var aHat = a->asArray();

        var l = Matrix::zeros(m, m)->asArray();

        for i in range(0, m - 1) {
            for j in range(0, i) {
                let sigma = 0.0;

                for k in range(0, j - 1) {
                    let sigma += l[i][k] * l[j][k];
                }

                let l[i][j] = i === j
                    ? sqrt(aHat[i][i] - sigma)
                    : 1 / l[j][j] * (aHat[i][j] - sigma);
            }
        }

        let l = Matrix::quick(l);

        return new self(l);
    }

    /**
     * @param \Tensor\Matrix l
     */
    public function __construct(const <Matrix> l)
    {
        let this->l = l;
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
     * Return the conjugate transpose of the lower triangular matrix.
     *
     * @return \Tensor\Matrix
     */
    public function lT() -> <Matrix>
    {
        return this->l->transpose();
    }
}