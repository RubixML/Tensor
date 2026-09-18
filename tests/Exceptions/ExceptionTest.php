<?php

namespace Tensor\Tests\Exceptions;

use Tensor\Exceptions\TensorException;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;
use Tensor\Exceptions\DimensionalityMismatch;
use Tensor\Exceptions\NotImplemented;
use PHPUnit\Framework\TestCase;

#[\PHPUnit\Framework\Attributes\CoversClass(NotImplemented::class)]
class ExceptionTest extends TestCase
{
    #[\PHPUnit\Framework\Attributes\Test]
    public function tensorExceptionIsAnInterface() : void
    {
        $this->assertTrue(interface_exists(TensorException::class));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function invalidArgumentImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(InvalidArgumentException::class), true));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function runtimeExceptionImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(RuntimeException::class), true));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function dimensionalityMismatchExtendsInvalidArgumentException() : void
    {
        $this->assertTrue(in_array(InvalidArgumentException::class, class_parents(DimensionalityMismatch::class), true));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function dimensionalityMismatchImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(DimensionalityMismatch::class), true));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function notImplementedExtendsRuntimeException() : void
    {
        $this->assertTrue(in_array(RuntimeException::class, class_parents(NotImplemented::class), true));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function notImplementedImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(NotImplemented::class), true));
    }

    #[\PHPUnit\Framework\Attributes\Test]
    public function exceptionsPreserveTheirMessage() : void
    {
        $exception = new DimensionalityMismatch('the message');

        $this->assertSame('the message', $exception->getMessage());

        $this->assertTrue(in_array(InvalidArgumentException::class, class_parents($exception), true));
        $this->assertTrue(in_array(TensorException::class, class_implements($exception), true));
    }
}
