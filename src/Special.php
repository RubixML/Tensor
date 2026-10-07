<?php

namespace Tensor;

interface Special
{
    /**
     * Return the softmax of the tensor.
     *
     * For a matrix each row is normalized independently, for a vector the
     * entire tensor is treated as a single row.
     *
     * @return mixed
     */
    public function softmax();

    /**
     * Return the element-wise error function of the tensor.
     *
     * @return mixed
     */
    public function erf();
}
