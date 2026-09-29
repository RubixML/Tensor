<?php

namespace Tensor\Benchmarks\Reductions;

use Tensor\Matrix;

/**
 * @Groups({"Signal Processing"})
 * @BeforeMethods({"setUp"})
 */
class MatrixConvolveBench
{
    /**
     * @var Matrix
     */
    protected $a;

    /**
     * @var Matrix
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
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolve() : void
    {
        $this->a->convolve($this->kernel);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolveSamePadding() : void
    {
        $this->a->convolve($this->kernel, 1, 5);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolveFullPadding() : void
    {
        $this->a->convolve($this->kernel, 1, 9);
    }
}
