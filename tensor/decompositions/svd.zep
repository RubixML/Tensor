namespace Tensor\Decompositions;

use Tensor\Matrix;

/**
 * SVD
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Svd
{
    /**
     * The u matrix.
     *
     * @var \Tensor\Matrix
     */
     protected u;

    /**
     * The singular values of the matrix.
     *
     * @var (int|float)[]
     */
    protected s;

    /**
     * The vt unitary matrix.
     *
     * @var \Tensor\Matrix
     */
    protected vt;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix a
     * @return self
     */
    public static function decompose(const <Matrix> a) -> <Svd>
    {
        array usvt = [];

        let usvt = (array) tensor_svd(a->asArray());

        return new self(
            Matrix::quick(usvt[0]),
            usvt[1],
            Matrix::quick(usvt[2])
        );
    }

    /**
     * @param \Tensor\Matrix u
     * @param list<int|float> s
     * @param \Tensor\Matrix vt
     */
     public function __construct(const <Matrix> u, const array s, const <Matrix> vt)
     {
         let this->u = u;
         let this->s = s;
         let this->vt = vt;
     }
 
    /**
     * Return the U matrix.
     *
     * @return \Tensor\Matrix
     */
    public function u() -> <Matrix>
    {
        return this->u;
    }
 
    /**
     * Return the singular values of matrix A in descending order.
     *
     * @return list<int|float>
     */
    public function s() -> array
    {
        return this->s;
    }
 
    /**
     * Return the vt unitary matrix.
     *
     * @return \Tensor\Matrix
     */
    public function vt() -> <Matrix>
    {
       return this->vt;
    }
}
