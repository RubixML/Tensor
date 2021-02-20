namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Vector;
use Tensor\ColumnVector;
use RuntimeException;

/**
 * Eigen
 *
 * The Eigendecompositon or (Spectral decomposition) is a matrix factorization resulting in a
 * matrix of eigenvectors and a corresponding array of eigenvalues.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Eigen
{
    /**
     * The computed eigenvalues.
     *
     * @var (int|float)[]
     */
    protected eigenvalues;

    /**
     * The eigenvectors of the eigendecomposition.
     *
     * @var \Tensor\Matrix
     */
    protected eigenvectors;

    /**
     * Factory method to decompose a matrix.
     *
     * @param \Tensor\Matrix a
     * @param bool normalize
     * @return self
     */
    public static function decompose(const <Matrix> a, const bool normalize) -> <Eigen>
    {
        if unlikely !a->isSquare() {
            throw new RuntimeException("Cannot decompose a non-square matrix.");
        }

        var eigenvalues;
        var eigenvectors;

        array eig = [];

        let eig = (array) tensor_eig(a->asArray());

        let eigenvalues = eig[0];
        let eigenvectors = Matrix::quick(eig[1])->transpose();

        if (normalize) {
            var norm;
            
            let norm = eigenvectors->transpose()
                ->square()
                ->sum()
                ->sqrt()
                ->transpose();

            let eigenvectors = eigenvectors->divideVector(norm);
        }

        return new self(eigenvalues, eigenvectors);
    }

    /**
     * @param list<int|float> eigenvalues
     * @param \Tensor\Matrix eigenvectors
     */
    public function __construct(const array eigenvalues, const <Matrix> eigenvectors)
    {
        let this->eigenvalues = eigenvalues;
        let this->eigenvectors = eigenvectors;
    }

    /**
     * Return the eigenvalues.
     *
     * @return list<int|float>
     */
    public function eigenvalues() -> <Matrix>
    {
        return this->eigenvalues;
    }

    /**
     * Return the eigenvectors.
     *
     * @return \Tensor\Matrix
     */
    public function eigenvectors() -> <Matrix>
    {
        return this->eigenvectors;
    }
}
