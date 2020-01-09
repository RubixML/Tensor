<?php

namespace Tensor\Benchmarks\Trigonometric;

use Tensor\Matrix;

class CosMatrixBench
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
    public function cosine() : void
    {
        $this->a->cos();
    }
}
