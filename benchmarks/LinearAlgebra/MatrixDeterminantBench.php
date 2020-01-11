<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;

/**
 * @Groups({"LinearAlgebra"})
 */
class MatrixDeterminantBench
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    public function setUp() : void
    {
        $this->a = Matrix::uniform(500, 500);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUp"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function det() : void
    {
        $this->a->det();
    }
}
