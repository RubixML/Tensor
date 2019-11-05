<?php

namespace Tensor;

interface Statistical extends Tensor
{
    /**
     * Return the mean of the tensor.
     *
     * @return mixed
     */
    public function mean();

    /**
     * Return the median of the tensor.
     *
     * @return mixed
     */
    public function median();

    /**
     * Return the pth percentile of the tensor.
     *
     * @param float $p
     * @return mixed
     */
    public function percentile(float $p);
}
