namespace Tensor\Decompositions;

use Tensor\Matrix;

interface Decomposition
{
    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix a
     * @return self
     */
    public static function decompose(<Matrix> a);
}
