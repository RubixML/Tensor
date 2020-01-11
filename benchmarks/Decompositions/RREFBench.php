<?php

namespace Tensor\Benchmarks\Decompositions;

use Tensor\Matrix;

/**
 * @Groups({"Decompositions"})
 */
class RREFBench
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
    public function rref() : void
    {
        $this->a->rref();
    }
}
