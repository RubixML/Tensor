<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class RandomMatrixBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function poisson() : void
    {
        Matrix::rand(500, 500);
    }
}
