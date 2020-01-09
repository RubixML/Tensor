<?php

namespace Tensor\Benchmarks\Arithmetic;

use Tensor\Matrix;

class MatrixScalarMultiplyBench
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * @var float
     */
    protected $b = M_E;

    public function setUp() : void
    {
        $this->a = Matrix::uniform(1000, 1000);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUp"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function multiply() : void
    {
        $this->a->multiply($this->b);
    }
}
