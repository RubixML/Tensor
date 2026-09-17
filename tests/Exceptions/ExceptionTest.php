<?php

namespace Tensor\Tests\Exceptions;

use Tensor\Exceptions\TensorException;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;
use Tensor\Exceptions\DimensionalityMismatch;
use Tensor\Exceptions\NotImplemented;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Exceptions\NotImplemented
 */
class ExceptionTest extends TestCase
{
    /**
     * @test
     */
    public function tensorExceptionIsAnInterface() : void
    {
        $this->assertTrue(interface_exists(TensorException::class));
    }

    /**
     * @test
     */
    public function invalidArgumentImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(InvalidArgumentException::class), true));
    }

    /**
     * @test
     */
    public function runtimeExceptionImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(RuntimeException::class), true));
    }

    /**
     * @test
     */
    public function dimensionalityMismatchExtendsInvalidArgumentException() : void
    {
        $this->assertTrue(is_subclass_of(DimensionalityMismatch::class, InvalidArgumentException::class));
    }

    /**
     * @test
     */
    public function dimensionalityMismatchImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(DimensionalityMismatch::class), true));
    }

    /**
     * @test
     */
    public function notImplementedExtendsRuntimeException() : void
    {
        $this->assertTrue(is_subclass_of(NotImplemented::class, RuntimeException::class));
    }

    /**
     * @test
     */
    public function notImplementedImplementsTensorException() : void
    {
        $this->assertTrue(in_array(TensorException::class, class_implements(NotImplemented::class), true));
    }

    /**
     * @test
     */
    public function exceptionsPreserveTheirMessage() : void
    {
        $exception = new DimensionalityMismatch('the message');

        $this->assertSame('the message', $exception->getMessage());

        $this->assertInstanceOf(InvalidArgumentException::class, $exception);
        $this->assertInstanceOf(TensorException::class, $exception);
    }
}
