<?php

namespace Tensor\Benchmarks;

use Tensor\Vector;

class VectorDotBench
{
    /**
     * @var \Tensor\Vector
     */
    protected $a;

    /**
     * @var \Tensor\Vector
     */
    protected $b;

    public function setUpSmall() : void
    {
        $this->a = Vector::uniform(1000);

        $this->b = Vector::uniform(1000);
    }

    public function setUpLarge() : void
    {
        $this->a = Vector::uniform(10000);

        $this->b = Vector::uniform(10000);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUpSmall"})
     * @OutputTimeUnit("milliseconds", precision=3)
     */
    public function dot_small() : void
    {
        $this->a->dot($this->b);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @BeforeMethods({"setUpLarge"})
     * @OutputTimeUnit("milliseconds", precision=3)
     */
    public function dot_large() : void
    {
        $this->a->dot($this->b);
    }
}
