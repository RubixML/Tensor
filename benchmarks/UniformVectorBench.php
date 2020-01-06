<?php

namespace Tensor\Benchmarks;

use Tensor\Vector;

class UniformVectorBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function uniform() : void
    {
        Vector::uniform(250000);
    }
}
