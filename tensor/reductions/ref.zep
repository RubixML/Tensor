namespace Tensor\Reductions;

use Tensor\Matrix;
use InvalidArgumentException;

/**
 * REF
 *
 * The row echelon form (REF) of a matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Ref
{
    /**
     * The reduced matrix in row echelon form.
     *
     * @var \Tensor\Matrix
     */
    protected a;
    
    /**
     * The number of swaps made to compute the row echelon form of the matrix.
     *
     * @var int
     */
    protected swaps;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix a
     * @return self
     */
    public static function reduce(const <Matrix> a) -> <Ref>
    {
        array ref = [];

        let ref = (array) tensor_ref(a->asArray());

        return new self(new Matrix(ref[0]), ref[1]);
    }

    /**
     * @param \Tensor\Matrix a
     * @param int swaps
     * @throws \InvalidArgumentException
     */
    public function __construct(const <Matrix> a, const int swaps)
    {
        if unlikely swaps < 0 {
            throw new InvalidArgumentException("The number of swaps must"
                . " be greater than or equal to 0, " . strval(swaps)
                . " given.");
        }

        let this->a = a;
        let this->swaps = swaps;
    }

    /**
     * Return the reduced matrix in row echelon form.
     *
     * @return \Tensor\Matrix
     */
    public function a() -> <Matrix>
    {
        return this->a;
    }

    /**
     * Return the number of swaps made to reduce the matrix to ref.
     *
     * @return int
     */
    public function swaps() -> int
    {
        return this->swaps;
    }
}
