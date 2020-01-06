<?php

namespace Tensor\Benchmarks;

use Tensor\Vector;

class RandomVectorBench
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
