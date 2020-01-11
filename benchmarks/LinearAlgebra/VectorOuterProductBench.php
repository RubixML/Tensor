<?php

namespace Tensor\Benchmarks\LinearAlgebra;

use Tensor\Vector;

/**
 * @Groups({"LinearAlgebra"})
 */
class VectorOuterProductBench
{
    /**
     * @var \Tensor\Vector
     */
    protected $a;

    /**
     * @var \Tensor\Vector
     */
    protected $b;

    public function setUp() : void
    {
        $this->a = Vector::uniform(500);

        $this->b = Vector::uniform(500);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUp"})
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function outer() : void
    {
        $this->a->outer($this->b);
    }
}
