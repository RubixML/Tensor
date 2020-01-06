<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class UniformMatrixBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function uniform() : void
    {
        Matrix::uniform(500, 500);
    }
}
