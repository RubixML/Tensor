<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;

/**
 * @Groups({"LinearAlgebra"})
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
        $this->a = Matrix::uniform(500, 500);

        $this->b = Matrix::uniform(500, 500);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUp"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function matmul() : void
    {
        $this->a->matmul($this->b);
    }
}
