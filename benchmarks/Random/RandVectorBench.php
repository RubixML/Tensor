<?php

namespace Tensor\Benchmarks\Random;

use Tensor\Vector;

class RandVectorBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function rand() : void
    {
        Vector::rand(250000);
    }
}
