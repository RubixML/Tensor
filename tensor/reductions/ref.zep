namespace Tensor\Reductions;

use Tensor\Matrix;
use InvalidArgumentException;
use RuntimeException;

/**
 * REF
 *
 * The row echelon form (REF) of a matrix.
 *
 * References:
 * [1] M. Rogoyski. (2019). Math PHP: Powerful modern math library for PHP.
 * http://github.com/markrogoyski/math-php.
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
        try {
            return self::gaussianElimination(a);
        } catch RuntimeException {
            return self::rowReductionMethod(a);
        }
    }

    /**
     * Calculate the row echelon form (REF) of the matrix using Gaussian
     * elimination. Return the matrix and the number of swaps in a tuple.
     *
     * @param \Tensor\Matrix a
     * @throws \RuntimeException
     * @return self
     */
    public static function gaussianElimination(const <Matrix> a) -> <Ref>
    {
        int i, j, k, index;
        float diag, scale;
        var temp;
        array b = [];

        int m = (int) a->m();
        int n = (int) a->n();

        let b = (array) a->asArray();

        int swaps = 0;

        for k in range(0, min(m, n) - 1) {
            let index = k;

            for i in range(k, m - 1) {
                if abs(b[i][k]) > abs(b[index][k]) {
                    let index = i;
                }
            }

            if unlikely b[index][k] == 0 {
                throw new RuntimeException("Cannot compute row echelon form"
                    . " of a singular matrix.");
            }

            if k !== index {
                let temp = b[k];

                let b[k] = b[index];
                let b[index] = temp;

                let swaps++;
            }

            let diag = (float) b[k][k];

            for i in range(k + 1, m - 1) {
                let scale = diag !== 0.0 ? (float) b[i][k] / diag : 1.0;

                for j in range(k + 1, n - 1) {
                    let b[i][j] = (float) b[i][j] - scale * (float) b[k][j];
                }

                let b[i][k] = 0;
            }
        }

        return new self(Matrix::quick(b), swaps);
    }

    /**
     * Calculate the row echelon form (REF) of the matrix using the row
     * reduction method. Return the matrix and the number of swaps in a
     * tuple.
     *
     * @param \Tensor\Matrix a
     * @return self
     */
    public static function rowReductionMethod(const <Matrix> a) -> <Ref>
    {
        int i, j;
        float scale, divisor;
        var temp;
        array b = [];
        array t = [];

        int m = (int) a->m();
        int n = (int) a->n();

        int row = 0;
        int col = 0;

        let b = (array) a->asArray();

        int swaps = 0;

        while likely row < m && col < n {
            let t = (array) b[row];

            if t[col] == 0 {
                for i in range(row + 1, m - 1) {
                    if b[i][col] != 0 {
                        let temp = b[i];

                        let b[i] = t;
                        let t = temp;

                        let swaps++;

                        break;
                    }
                }
            }

            if t[col] == 0 {
                let col++;

                continue;
            }

            let divisor = (float) t[col];

            if divisor !== 1.0 {
                for i in range(0, n - 1) {
                    let t[i] = (float) t[i] / divisor;
                }
            }

            for i in range(row + 1, m - 1) {
                let scale = (float) b[i][col];

                if scale !== 0.0 {
                    for j in range(0, n - 1) {
                        let b[i][j] = (float) b[i][j] - scale * (float) t[j];
                    }
                }
            }

            let b[row] = t;

            let row++;
            let col++;
        }

        return new self(Matrix::quick(b), swaps);
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
