<?php

namespace Tensor\Benchmarks\Functions;

use Tensor\Matrix;

/**
 * @Groups({"Functions"})
 * @BeforeMethods({"setUp"})
 */
class SigmoidMatrixBench
{
    /**
     * @var Matrix
     */
    protected $a;

    public function setUp() : void
    {
        $this->a = Matrix::uniform(500, 500);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function chained() : void
    {
        $this->a->negate()
            ->exp()
            ->addScalar(1.0)
            ->reciprocal();
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function map() : void
    {
        $this->a->sigmoid();
    }
}
