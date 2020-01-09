<?php

namespace Tensor\Benchmarks\Statistical;

use Tensor\Matrix;

class MatrixPercentileBench
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
    public function percentile() : void
    {
        $this->a->percentile(50.0);
    }
}
