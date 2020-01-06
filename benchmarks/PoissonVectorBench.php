<?php

namespace Tensor\Benchmarks;

use Tensor\Vector;

class PoissonVectorBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function poisson() : void
    {
        Vector::poisson(250000);
    }
}
