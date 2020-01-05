<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;
use Tensor\Vector;

class MatrixVectorMultiplyBench
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * @var \Tensor\Vector
     */
    protected $b;

    public function setUpSmall() : void
    {
        $this->a = Matrix::uniform(100, 100);

        $this->b = Vector::uniform(100);
    }

    public function setUpLarge() : void
    {
        $this->a = Matrix::uniform(1000, 1000);

        $this->b = Vector::uniform(1000);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUpSmall"})
     * @OutputTimeUnit("milliseconds", precision=3)
     */
    public function multiply_small() : void
    {
        $this->a->multiply($this->b);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUpLarge"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function multiply_large() : void
    {
        $this->a->multiply($this->b);
    }
}
