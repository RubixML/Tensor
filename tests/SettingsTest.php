<?php

namespace Tensor\Tests;

use PHPUnit\Framework\TestCase;

/**
 * @requires extension tensor
 * @covers \Tensor\Settings
 */
class SettingsTest extends TestCase
{
    /**
     * @test
     */
    public function setAndGetNumThreads() : void
    {
        \Tensor\Settings::setNumThreads(4);

        $this->assertEquals(4, Settings::numThreads());

        \Tensor\Settings::setNumThreads(12);

        $this->assertEquals(12, Settings::numThreads());

        \Tensor\Settings::setNumThreads(1);

        $this->assertEquals(1, Settings::numThreads());
    }
}
