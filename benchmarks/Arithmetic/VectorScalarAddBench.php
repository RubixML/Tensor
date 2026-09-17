<?php

namespace Tensor\Benchmarks\Arithmetic;

use Tensor\Vector;

/**
 * @Groups({"Arithmetic"})
 * @BeforeMethods({"setUp"})
 */
class VectorScalarAddBench
{
    /**
     * @var Vector
     */
    protected $a;

    /**
     * @var float
     */
    protected $b = M_E;

    public function setUp() : void
    {
        $this->a = Vector::uniform(10000);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("milliseconds", precision=3)
     */
    public function add() : void
    {
        $this->a->add($this->b);
    }
}
