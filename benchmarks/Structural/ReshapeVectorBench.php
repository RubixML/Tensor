<?php

namespace Tensor\Benchmarks\Structural;

use Tensor\Vector;

class ReshapeVectorBench
{
    /**
     * @var \Tensor\Vector
     */
    protected $a;

    public function setUp() : void
    {
        $this->a = Vector::uniform(250000);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUp"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function reshape() : void
    {
        $this->a->reshape(500, 500);
    }
}
