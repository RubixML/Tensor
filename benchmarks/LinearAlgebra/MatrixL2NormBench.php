<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;

class MatrixL2NormBench
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
    public function l2_norm() : void
    {
        $this->a->l2Norm();
    }
}
