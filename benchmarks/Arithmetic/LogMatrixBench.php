<?php

namespace Tensor\Benchmarks\Arithmetic;

use Tensor\Matrix;

class LogMatrixBench
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
    public function log() : void
    {
        $this->a->log();
    }
}
