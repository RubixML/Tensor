<?php

namespace Tensor\Benchmarks\Trigonometric;

use Tensor\Matrix;

/**
 * @Groups({"Trigonometric"})
 */
class TanMatrixBench
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
    public function tangent() : void
    {
        $this->a->tan();
    }
}
