<?php

namespace Tensor\Benchmarks;

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

    public function setUpSmall() : void
    {
        $this->a = Matrix::uniform(100, 100);

        $this->kernel = Matrix::uniform(5, 5);
    }

    public function setUpLarge() : void
    {
        $this->a = Matrix::uniform(1000, 1000);

        $this->kernel = Matrix::uniform(5, 5);
    }

    /**
     * @Subject
     * @Iterations(10)
     * @BeforeMethods({"setUpSmall"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolve_small() : void
    {
        $this->a->convolve($this->kernel);
    }

    /**
     * @Subject
     * @Iterations(10)
     * @BeforeMethods({"setUpLarge"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolve_large() : void
    {
        $this->a->convolve($this->kernel);
    }
}
