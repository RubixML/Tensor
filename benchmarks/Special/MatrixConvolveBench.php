<?php

namespace Tensor\Benchmarks\Special;

use Tensor\Matrix;

class MatrixConvolveBench
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * @var \Tensor\Matrix
     */
    protected $kernel;

    public function setUp() : void
    {
        $this->a = Matrix::uniform(500, 500);

        $this->kernel = Matrix::uniform(10, 10);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUp"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolve() : void
    {
        $this->a->convolve($this->kernel);
    }
}
