<?php

namespace Tensor\Benchmarks\Structural;

use Tensor\Matrix;

/**
 * @Groups({"Structural"})
 * @BeforeMethods({"setUp"})
 */
class MatrixTransposeBench
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
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function multiply() : void
    {
        $this->a->transpose();
    }
}
