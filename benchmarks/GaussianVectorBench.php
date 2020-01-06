<?php

namespace Tensor\Benchmarks;

use Tensor\Vector;

class GaussianVectorBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function gaussian() : void
    {
        Vector::gaussian(250000);
    }
}
