<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Matrix;
use Tensor\ColumnVector;

/**
 * @Groups({"LinearAlgebra"})
 * @BeforeMethods({"setUp"})
 */
class SolveBench
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * @var \Tensor\Vector
     */
    protected $b;

    public function setUp() : void
    {
        $this->a = Matrix::uniform(500, 500);

        $this->b = ColumnVector::uniform(500);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function matmul() : void
    {
        $this->a->solve($this->b);
    }
}
