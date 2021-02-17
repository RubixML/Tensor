namespace Tensor\Decompositions;

use Tensor\Matrix;
use InvalidArgumentException;

/**
 * Cholesky
 *
 * An efficient decomposition of a square positive definite matrix into a lower triangular matrix and its conjugate transpose.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Cholesky
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
     * @throws \InvalidArgumentExeption
     * @return self
     */
    public static function decompose(const <Matrix> a) -> <Cholesky>
    {
        if !a->isSquare() {
            throw new InvalidArgumentException("Cannot decompose a non-square matrix.");
        }

        array l = [];

        let l = (array) tensor_cholesky(a->asArray());

        return new self(Matrix::quick(l));
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