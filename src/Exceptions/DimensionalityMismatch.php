<?php

namespace Tensor\Exceptions;

class DimensionalityMismatch extends InvalidArgumentException
{
    /**
     * @param string $message
     */
    public function __construct(string $message)
    {
        parent::__construct($message);
    }
}
