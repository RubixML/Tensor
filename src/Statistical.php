<?php

namespace Tensor;

interface Statistical
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

    /**
     * Compute the variance of the tensor.
     *
     * @param mixed $mean
     * @return mixed
     */
    public function variance($mean = null);
}
