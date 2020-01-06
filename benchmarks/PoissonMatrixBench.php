<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class PoissonMatrixBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function poisson() : void
    {
        Matrix::poisson(500, 500);
    }
}
