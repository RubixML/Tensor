namespace Tensor;

interface Tensor extends ArrayLike, Arithmetic, Comparable, Functional, Trigonometric, Statistical
{   
    const EPSILON = 0.00000001;
}
