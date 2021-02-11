<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;

/**
 * @Groups({"LinearAlgebra"})
 * @BeforeMethods({"setUp"})
 */
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

    public function setUp() : void
    {
        $this->a = Matrix::uniform(1000, 1000);

        $this->b = Matrix::uniform(1000, 1000);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("milliseconds", precision=3)
     */
    public function matmul() : void
    {
        $this->a->matmul($this->b);
    }
}
