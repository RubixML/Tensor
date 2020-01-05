<?php

namespace Tensor\Benchmarks;

use Tensor\Matrix;

class RandomGaussianMatrixBench
{
    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function gaussian_matrix() : void
    {
        Matrix::gaussian(500, 500);
    }
}
