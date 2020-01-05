<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class RandomPoissonMatrixBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function poisson_matrix() : void
    {
        Matrix::poisson(500, 500);
    }
}
