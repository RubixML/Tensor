<?php

/**
 * @package JAMA
 *
 *  Pythagorean Theorem:
 *
 *  a = 3
 *  b = 4
 *  r = sqrt(square(a) + square(b))
 *  r = 5
 *
 *  r = sqrt(a^2 + b^2) without under/overflow.
 * @param mixed $a
 * @param mixed $b
 */
function hypo($a, $b)
{
    $aHat = abs($a);
    $bHat = abs($b);

    if ($aHat > $bHat) {
        $r = $aHat * sqrt(1 + ($b / $a) ** 2);
    } elseif ($b != 0) {
        $r = $bHat * sqrt(1 + ($a / $b) ** 2);
    } else {
        $r = 0.0;
    }
    return $r;
}
 
/**
  * Mike Bommarito's version.
  * Compute n-dimensional hyotheneuse.
  *
  * function hypot() {
  *  $s = 0;
  *  foreach (func_get_args() as $d) {
  *    if (is_numeric($d))
  *      $s += pow($d, 2);
  *    else
  *      trigger_error(ArgumentTypeException, ERROR);
  *  }
  *  return sqrt($s);
  * }
  */
