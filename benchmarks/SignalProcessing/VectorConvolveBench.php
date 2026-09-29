<?php

namespace Tensor\Benchmarks\Reductions;

use Tensor\Vector;

/**
 * @Groups({"Signal Processing"})
 * @BeforeMethods({"setUp"})
 */
class VectorConvolveBench
{
    /**
     * @var Vector
     */
    protected $a;

    /**
     * @var Vector
     */
    protected $kernel;

    public function setUp() : void
    {
        $this->a = Vector::uniform(250000);

        $this->kernel = Vector::uniform(100);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolve() : void
    {
        $this->a->convolve($this->kernel);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolveSamePadding() : void
    {
        $this->a->convolve($this->kernel, 1, 50);
    }

    /**
     * @Subject
     * @Iterations(5)
     * @OutputTimeUnit("seconds", precision=3)
     */
    public function convolveFullPadding() : void
    {
        $this->a->convolve($this->kernel, 1, 99);
    }
}
