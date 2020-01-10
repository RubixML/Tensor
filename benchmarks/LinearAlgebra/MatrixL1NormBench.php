<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;

class MatrixL1NormBench
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
    public function l1_norm() : void
    {
        $this->a->l1Norm();
    }
}
