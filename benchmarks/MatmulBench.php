<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class MatmulBench
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * @var \Tensor\Matrix
     */
    protected $b;

    public function setUpSmall() : void
    {
        $this->a = Matrix::uniform(50, 100);

        $this->b = Matrix::uniform(100, 50);
    }

    public function setUpLarge() : void
    {
        $this->a = Matrix::uniform(500, 1000);

        $this->b = Matrix::uniform(1000, 500);
    }

    /**
     * @Subject
     * @Iterations(10)
     * @BeforeMethods({"setUpSmall"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function matmul_small() : void
    {
        $this->a->matmul($this->b);
    }

    /**
     * @Subject
     * @Iterations(3)
     * @BeforeMethods({"setUpLarge"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function matmul_large() : void
    {
        $this->a->matmul($this->b);
    }
}
