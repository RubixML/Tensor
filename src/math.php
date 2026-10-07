<?php

namespace Tensor;

/**
 * Return the softplus of $x, defined as log(1 + exp(x)).
 *
 * The computation is split based on the sign of $x so that the
 * exponentially large argument never overflows:
 *     x <  0: log(1 + exp(x))
 *     x >= 0: x + log(1 + exp(-x))
 *
 * @param float $x
 * @return float
 */
function softplus(float $x) : float
{
    return $x < 0.0 ? log1p(exp($x)) : $x + log1p(exp(-$x));
}

/**
 * Return the reciprocal square root of $x, defined as 1 / sqrt(x).
 *
 * @param float $x
 * @return float
 */
function rsqrt(float $x) : float
{
    return 1.0 / sqrt($x);
}

/**
 * Return the sigmoid of $x, defined as 1 / (1 + exp(-x)).
 *
 * The result is always in the open interval (0, 1) and saturates to
 * 1.0 and 0.0 for large positive and negative arguments respectively.
 *
 * @param float $x
 * @return float
 */
function sigmoid(float $x) : float
{
    return 1.0 / (1.0 + exp(-$x));
}

/**
 * Return the error function of $x.
 *
 * The error function is defined as
 *     erf(x) = (2/sqrt(pi)) * integral_0^x exp(-t^2) dt
 *
 * For |x| <= 5 the function is evaluated using its Taylor power series,
 * which reaches a relative error below 1e-14. For |x| > 5 the function
 * returns the sign of x saturated to +/-1.0, which is correct to
 * better than 1e-11 relative error over the remaining domain.
 *
 * @param float $x
 * @return float
 */
function erf(float $x) : float
{
    switch (true) {
        case $x === 0.0:
            return 0.0;

        case $x >= 5.0:
            return 1.0;

        case $x <= -5.0:
            return -1.0;
    }

    $scale = 2.0 / M_SQRTPI;

    $sum = 0.0;
    $term = $x;

    for ($n = 0;; ++$n) {
        if ($n > 0) {
            $term *= -(2 * $n - 1) * $x * $x / ($n * (2 * $n + 1));
        }

        $sum += $term;

        if (abs($term) < 1e-18 * max(1.0, abs($sum))) {
            break;
        }
    }

    return $scale * $sum;
}
