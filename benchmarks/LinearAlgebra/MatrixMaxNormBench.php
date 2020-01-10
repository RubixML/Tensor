<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;

class MatrixMaxNormBench
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
    public function max_norm() : void
    {
        $this->a->maxNorm();
    }
}
