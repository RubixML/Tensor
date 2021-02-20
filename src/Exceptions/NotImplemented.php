<?php

namespace Tensor\Exceptions;

class NotImplemented extends RuntimeException
{
    /**
     * @param string $message
     */
    public function __construct(string $message)
    {
        parent::__construct($message);
    }
}
