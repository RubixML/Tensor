<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class RandomUniformMatrixBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function uniform_matrix() : void
    {
        Matrix::uniform(500, 500);
    }
}
