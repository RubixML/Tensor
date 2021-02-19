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

        array lup = [];

        let lup = (array) tensor_lu(a->asArray());

        return new self(
            Matrix::quick(lup[0]),
            Matrix::quick(lup[1]),
            Matrix::quick(lup[2])
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
