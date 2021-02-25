<?php

namespace Tensor\Tests;

use Tensor\Settings;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Settings
 * @requires extension tensor
 */
class SettingsTest extends TestCase
{
    /**
     * @test
     */
    public function setAndGetNumThreads() : void
    {
        Settings::setNumThreads(4);

        $this->assertEquals(4, Settings::numThreads());

        Settings::setNumThreads(12);

        $this->assertEquals(12, Settings::numThreads());

        Settings::setNumThreads(1);

        $this->assertEquals(1, Settings::numThreads());
    }
}
