<?php

namespace Tensor\Decompositions;

use Tensor\Matrix;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\RuntimeException;

/**
 * Eigen
 *
 * The Eigendecompositon or (Spectral decomposition) is a matrix factorization resulting in a matrix of eigenvectors and a
 * corresponding array of eigenvalues.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
class Eigen
{
    /**
     * The computed eigenvalues.
     *
     * @var (int|float)[]
     */
    protected array $eigenvalues;

    /**
     * The eigenvectors of the eigendecomposition.
     *
     * @var Matrix
     */
    protected Matrix $eigenvectors;

    /**
     * Factory method to decompose a matrix.
     *
     * @param Matrix $a
     * @param bool $symmetric
     * @throws InvalidArgumentException
     * @throws RuntimeException
     * @return self
     */
    public static function decompose(Matrix $a, bool $symmetric = false) : self
    {
        if (!$a->isSquare()) {
            throw new InvalidArgumentException('Matrix must be'
                . " square, {$a->shapeString()} given.");
        }

        $n = $a->n();

        if ($n === 1) {
            return new self($a->rowAsVector(0)->asArray(), Matrix::quick([[1.0]]));
        }

        if ($symmetric) {
            $tri = self::tred2($a->asArray());

            $result = self::tql2($tri['d'], $tri['e'], $tri['v']);
        } else {
            $hess = self::orthes($a->asArray());

            $result = self::hqr2($hess['h'], $hess['v']);
        }

        $d = $result['d'];
        $v = $result['v'];

        $rows = array_fill(0, $n, array_fill(0, $n, 0.0));

        for ($i = 0; $i < $n; ++$i) {
            $norm = 0.0;

            for ($j = 0; $j < $n; ++$j) {
                $norm += $v[$j][$i] ** 2;
            }

            $norm = sqrt($norm);

            for ($j = 0; $j < $n; ++$j) {
                $rows[$i][$j] = $norm > 0.0 ? $v[$j][$i] / $norm : 1.0;
            }
        }

        return new self($d, Matrix::quick($rows));
    }

    /**
     * Reduce a symmetric matrix to tridiagonal form by a sequence of
     * Householder reflections, accumulating the orthogonal transformations.
     *
     * @param list<list<float>> $a
     * @return array{d: list<float>, e: list<float>, v: list<list<float>>}
     */
    protected static function tred2(array $a) : array
    {
        $n = count($a);

        $v = $a;

        $d = [];
        $e = array_fill(0, $n, 0.0);

        for ($j = 0; $j < $n; ++$j) {
            $d[$j] = $v[$n - 1][$j];
        }

        for ($i = $n - 1; $i > 0; --$i) {
            $scale = 0.0;
            $h = 0.0;

            for ($k = 0; $k < $i; ++$k) {
                $scale += abs($d[$k]);
            }

            if ($scale == 0.0) {
                $e[$i] = $d[$i - 1];

                for ($j = 0; $j < $i; ++$j) {
                    $d[$j] = $v[$i - 1][$j];
                    $v[$i][$j] = 0.0;
                    $v[$j][$i] = 0.0;
                }
            } else {
                for ($k = 0; $k < $i; ++$k) {
                    $d[$k] /= $scale;
                    $h += $d[$k] * $d[$k];
                }

                $f = $d[$i - 1];
                $g = sqrt($h);

                if ($f > 0.0) {
                    $g = -$g;
                }

                $e[$i] = $scale * $g;
                $h -= $f * $g;
                $d[$i - 1] = $f - $g;

                for ($j = 0; $j < $i; ++$j) {
                    $e[$j] = 0.0;
                }

                for ($j = 0; $j < $i; ++$j) {
                    $f = $d[$j];
                    $v[$j][$i] = $f;
                    $g = $e[$j] + $v[$j][$j] * $f;

                    for ($k = $j + 1; $k <= $i - 1; ++$k) {
                        $g += $v[$k][$j] * $d[$k];
                        $e[$k] += $v[$k][$j] * $f;
                    }

                    $e[$j] = $g;
                }

                $f = 0.0;

                for ($j = 0; $j < $i; ++$j) {
                    $e[$j] /= $h;
                    $f += $e[$j] * $d[$j];
                }

                $hh = $f / ($h + $h);

                for ($j = 0; $j < $i; ++$j) {
                    $e[$j] -= $hh * $d[$j];
                }

                for ($j = 0; $j < $i; ++$j) {
                    $f = $d[$j];
                    $g = $e[$j];

                    for ($k = $j; $k <= $i - 1; ++$k) {
                        $v[$k][$j] -= ($f * $e[$k] + $g * $d[$k]);
                    }

                    $d[$j] = $v[$i - 1][$j];
                    $v[$i][$j] = 0.0;
                }
            }

            $d[$i] = $h;
        }

        for ($i = 0; $i < $n - 1; ++$i) {
            $v[$n - 1][$i] = $v[$i][$i];
            $v[$i][$i] = 1.0;

            $h = $d[$i + 1];

            if ($h != 0.0) {
                for ($k = 0; $k <= $i; ++$k) {
                    $d[$k] = $v[$k][$i + 1] / $h;
                }

                for ($j = 0; $j <= $i; ++$j) {
                    $g = 0.0;

                    for ($k = 0; $k <= $i; ++$k) {
                        $g += $v[$k][$i + 1] * $v[$k][$j];
                    }

                    for ($k = 0; $k <= $i; ++$k) {
                        $v[$k][$j] -= $g * $d[$k];
                    }
                }
            }

            for ($k = 0; $k <= $i; ++$k) {
                $v[$k][$i + 1] = 0.0;
            }
        }

        for ($j = 0; $j < $n; ++$j) {
            $d[$j] = $v[$n - 1][$j];
            $v[$n - 1][$j] = 0.0;
        }

        $v[$n - 1][$n - 1] = 1.0;
        $e[0] = 0.0;

        return [
            'd' => $d,
            'e' => $e,
            'v' => $v,
        ];
    }

    /**
     * Find the eigenvalues and eigenvectors of a symmetric tridiagonal
     * matrix by the QL algorithm with implicit shifts.
     *
     * @param list<float> $d
     * @param list<float> $e
     * @param list<list<float>> $v
     * @return array{d: list<float>, v: list<list<float>>}
     */
    protected static function tql2(array $d, array $e, array $v) : array
    {
        $n = count($d);

        for ($i = 1; $i < $n; ++$i) {
            $e[$i - 1] = $e[$i];
        }

        $e[$n - 1] = 0.0;

        $f = 0.0;
        $tst1 = 0.0;
        $eps = 2.0 ** -52.0;

        for ($l = 0; $l < $n; ++$l) {
            $tst1 = max($tst1, abs($d[$l]) + abs($e[$l]));

            $m = $l;

            while ($m < $n) {
                if (abs($e[$m]) <= $eps * $tst1) {
                    break;
                }

                ++$m;
            }

            if ($m > $l) {
                $iter = 0;

                do {
                    ++$iter;

                    $g = $d[$l];
                    $p = ($d[$l + 1] - $g) / (2.0 * $e[$l]);
                    $r = hypot($p, 1.0);

                    if ($p < 0.0) {
                        $r = -$r;
                    }

                    $d[$l] = $e[$l] / ($p + $r);
                    $d[$l + 1] = $e[$l] * ($p + $r);

                    $dl1 = $d[$l + 1];
                    $h = $g - $d[$l];

                    for ($i = $l + 2; $i < $n; ++$i) {
                        $d[$i] -= $h;
                    }

                    $f += $h;

                    $p = $d[$m];
                    $c = 1.0;
                    $c2 = $c;
                    $c3 = $c;
                    $el1 = $e[$l + 1];
                    $s = 0.0;
                    $s2 = 0.0;

                    for ($i = $m - 1; $i >= $l; --$i) {
                        $c3 = $c2;
                        $c2 = $c;
                        $s2 = $s;

                        $g = $c * $e[$i];
                        $h = $c * $p;
                        $r = hypot($p, $e[$i]);

                        $e[$i + 1] = $s * $r;
                        $s = $e[$i] / $r;
                        $c = $p / $r;

                        $p = $c * $d[$i] - $s * $g;
                        $d[$i + 1] = $h + $s * ($c * $g + $s * $d[$i]);

                        for ($k = 0; $k < $n; ++$k) {
                            $h = $v[$k][$i + 1];
                            $v[$k][$i + 1] = $s * $v[$k][$i] + $c * $h;
                            $v[$k][$i] = $c * $v[$k][$i] - $s * $h;
                        }
                    }

                    $p = -$s * $s2 * $c3 * $el1 * $e[$l] / $dl1;
                    $e[$l] = $s * $p;
                    $d[$l] = $c * $p;
                } while (abs($e[$l]) > $eps * $tst1);
            }

            $d[$l] += $f;
            $e[$l] = 0.0;
        }

        for ($i = 0; $i < $n - 1; ++$i) {
            $k = $i;
            $p = $d[$i];

            for ($j = $i + 1; $j < $n; ++$j) {
                if ($d[$j] < $p) {
                    $k = $j;
                    $p = $d[$j];
                }
            }

            if ($k != $i) {
                $d[$k] = $d[$i];
                $d[$i] = $p;

                for ($j = 0; $j < $n; ++$j) {
                    $p = $v[$j][$i];
                    $v[$j][$i] = $v[$j][$k];
                    $v[$j][$k] = $p;
                }
            }
        }

        return [
            'd' => $d,
            'v' => $v,
        ];
    }

    /**
     * Reduce a general matrix to upper Hessenberg form by a sequence of
     * Householder reflections, accumulating the orthogonal transformations.
     *
     * @param list<list<float>> $h
     * @return array{h: list<list<float>>, v: list<list<float>>}
     */
    protected static function orthes(array $h) : array
    {
        $n = count($h);

        $low = 0;
        $high = $n - 1;

        $ort = array_fill(0, $n, 0.0);

        for ($m = $low + 1; $m <= $high - 1; ++$m) {
            $scale = 0.0;

            for ($i = $m; $i <= $high; ++$i) {
                $scale += abs($h[$i][$m - 1]);
            }

            if ($scale != 0.0) {
                $hh = 0.0;

                for ($i = $high; $i >= $m; --$i) {
                    $ort[$i] = $h[$i][$m - 1] / $scale;
                    $hh += $ort[$i] * $ort[$i];
                }

                $g = sqrt($hh);

                if ($ort[$m] > 0.0) {
                    $g = -$g;
                }

                $hh -= $ort[$m] * $g;
                $ort[$m] -= $g;

                for ($j = $m; $j < $n; ++$j) {
                    $f = 0.0;

                    for ($i = $high; $i >= $m; --$i) {
                        $f += $ort[$i] * $h[$i][$j];
                    }

                    $f /= $hh;

                    for ($i = $m; $i <= $high; ++$i) {
                        $h[$i][$j] -= $f * $ort[$i];
                    }
                }

                for ($i = 0; $i <= $high; ++$i) {
                    $f = 0.0;

                    for ($j = $high; $j >= $m; --$j) {
                        $f += $ort[$j] * $h[$i][$j];
                    }

                    $f /= $hh;

                    for ($j = $m; $j <= $high; ++$j) {
                        $h[$i][$j] -= $f * $ort[$j];
                    }
                }

                $ort[$m] *= $scale;
                $h[$m][$m - 1] = $scale * $g;
            }
        }

        $v = [];

        for ($i = 0; $i < $n; ++$i) {
            $v[$i] = array_fill(0, $n, 0.0);

            $v[$i][$i] = 1.0;
        }

        for ($m = $high - 1; $m >= $low + 1; --$m) {
            if ($h[$m][$m - 1] != 0.0) {
                for ($i = $m + 1; $i <= $high; ++$i) {
                    $ort[$i] = $h[$i][$m - 1];
                }

                for ($j = $m; $j <= $high; ++$j) {
                    $g = 0.0;

                    for ($i = $m; $i <= $high; ++$i) {
                        $g += $ort[$i] * $v[$i][$j];
                    }

                    $g = ($g / $ort[$m]) / $h[$m][$m - 1];

                    for ($i = $m; $i <= $high; ++$i) {
                        $v[$i][$j] += $g * $ort[$i];
                    }
                }
            }
        }

        return [
            'h' => $h,
            'v' => $v,
        ];
    }

    /**
     * Reduce an upper Hessenberg matrix to quasi-triangular Schur form by
     * the double-shift QR algorithm, accumulating the orthogonal
     * transformations and computing the eigenvectors by back-substitution.
     *
     * @param list<list<float>> $h
     * @param list<list<float>> $v
     * @throws RuntimeException
     * @return array{d: list<float>, e: list<float>, v: list<list<float>>}
     */
    protected static function hqr2(array $h, array $v) : array
    {
        $nn = count($h);

        $n = $nn - 1;

        $low = 0;
        $high = $nn - 1;

        $eps = 2.0 ** -52.0;

        $d = array_fill(0, $nn, 0.0);
        $e = array_fill(0, $nn, 0.0);

        $exshift = 0.0;
        $norm = 0.0;

        for ($i = 0; $i < $nn; ++$i) {
            for ($j = max($i - 1, 0); $j < $nn; ++$j) {
                $norm += abs($h[$i][$j]);
            }
        }

        $iter = 0;

        while ($n >= $low) {
            $l = $n;

            while ($l > $low) {
                $s = abs($h[$l - 1][$l - 1]) + abs($h[$l][$l]);

                if ($s == 0.0) {
                    $s = $norm;
                }

                if (abs($h[$l][$l - 1]) < $eps * $s) {
                    break;
                }

                --$l;
            }

            if ($l == $n) {
                $h[$n][$n] += $exshift;
                $d[$n] = $h[$n][$n];
                $e[$n] = 0.0;

                --$n;
                $iter = 0;
            } elseif ($l == $n - 1) {
                $w = $h[$n][$n - 1] * $h[$n - 1][$n];
                $p = ($h[$n - 1][$n - 1] - $h[$n][$n]) / 2.0;
                $q = $p * $p + $w;
                $z = sqrt(abs($q));

                $h[$n][$n] += $exshift;
                $h[$n - 1][$n - 1] += $exshift;

                $x = $h[$n][$n];

                if ($q >= 0.0) {
                    if ($p >= 0.0) {
                        $z = $p + $z;
                    } else {
                        $z = $p - $z;
                    }

                    $d[$n - 1] = $x + $z;
                    $d[$n] = $d[$n - 1];

                    if ($z != 0.0) {
                        $d[$n] = $x - $w / $z;
                    }

                    $e[$n - 1] = 0.0;
                    $e[$n] = 0.0;

                    $x = $h[$n][$n - 1];
                    $s = abs($x) + abs($z);
                    $p = $x / $s;
                    $q = $z / $s;
                    $r = sqrt($p * $p + $q * $q);
                    $p /= $r;
                    $q /= $r;

                    for ($j = $n - 1; $j < $nn; ++$j) {
                        $z = $h[$n - 1][$j];
                        $h[$n - 1][$j] = $q * $z + $p * $h[$n][$j];
                        $h[$n][$j] = $q * $h[$n][$j] - $p * $z;
                    }

                    for ($i = 0; $i <= $n; ++$i) {
                        $z = $h[$i][$n - 1];
                        $h[$i][$n - 1] = $q * $z + $p * $h[$i][$n];
                        $h[$i][$n] = $q * $h[$i][$n] - $p * $z;
                    }

                    for ($i = $low; $i <= $high; ++$i) {
                        $z = $v[$i][$n - 1];
                        $v[$i][$n - 1] = $q * $z + $p * $v[$i][$n];
                        $v[$i][$n] = $q * $v[$i][$n] - $p * $z;
                    }
                } else {
                    $d[$n - 1] = $x + $p;
                    $d[$n] = $x + $p;
                    $e[$n - 1] = $z;
                    $e[$n] = -$z;
                }

                $n -= 2;
                $iter = 0;
            } else {
                $x = $h[$n][$n];
                $y = 0.0;
                $w = 0.0;

                if ($l < $n) {
                    $y = $h[$n - 1][$n - 1];
                    $w = $h[$n][$n - 1] * $h[$n - 1][$n];
                }

                if ($iter == 10) {
                    $exshift += $x;

                    for ($i = $low; $i <= $n; ++$i) {
                        $h[$i][$i] -= $x;
                    }

                    $s = abs($h[$n][$n - 1]) + abs($h[$n - 1][$n - 2]);
                    $x = $y = 0.75 * $s;
                    $w = -0.4375 * $s * $s;
                }

                if ($iter == 30) {
                    $s = ($y - $x) / 2.0;
                    $s = $s * $s + $w;

                    if ($s > 0.0) {
                        $s = sqrt($s);

                        if ($y < $x) {
                            $s = -$s;
                        }

                        $s = $x - $w / (($y - $x) / 2.0 + $s);

                        for ($i = $low; $i <= $n; ++$i) {
                            $h[$i][$i] -= $s;
                        }

                        $exshift += $s;
                        $x = $y = $w = 0.964;
                    }
                }

                ++$iter;

                if ($iter > 30 * $nn) {
                    throw new RuntimeException('Failed to decompose matrix.');
                }

                $m = $n - 2;

                $p = 0.0;
                $q = 0.0;
                $r = 0.0;
                $p0 = 0.0;
                $q0 = 0.0;
                $r0 = 0.0;

                while ($m >= $l) {
                    $z = $h[$m][$m];
                    $r = $x - $z;
                    $s = $y - $z;
                    $p = ($r * $s - $w) / $h[$m + 1][$m] + $h[$m][$m + 1];
                    $q = $h[$m + 1][$m + 1] - $z - $r - $s;
                    $r = $h[$m + 2][$m + 1];
                    $s = abs($p) + abs($q) + abs($r);
                    $p /= $s;
                    $q /= $s;
                    $r /= $s;

                    if ($m == $l) {
                        break;
                    }

                    if (abs($h[$m][$m - 1]) * (abs($q) + abs($r)) < $eps * (abs($p) * (abs($h[$m - 1][$m - 1]) + abs($z) + abs($h[$m + 1][$m + 1])))) {
                        break;
                    }

                    --$m;
                }

                $p0 = $p;
                $q0 = $q;
                $r0 = $r;

                for ($i = $m + 2; $i <= $n; ++$i) {
                    $h[$i][$i - 2] = 0.0;

                    if ($i > $m + 2) {
                        $h[$i][$i - 3] = 0.0;
                    }
                }

                for ($k = $m; $k <= $n - 1; ++$k) {
                    $notlast = $k != $n - 1;

                    if ($k != $m) {
                        $p = $h[$k][$k - 1];
                        $q = $h[$k + 1][$k - 1];
                        $r = $notlast ? $h[$k + 2][$k - 1] : 0.0;
                        $x = abs($p) + abs($q) + abs($r);

                        if ($x == 0.0) {
                            continue;
                        }

                        $p /= $x;
                        $q /= $x;
                        $r /= $x;
                    } else {
                        $p = $p0;
                        $q = $q0;
                        $r = $r0;
                    }

                    $s = sqrt($p * $p + $q * $q + $r * $r);

                    if ($p < 0.0) {
                        $s = -$s;
                    }

                    if ($s != 0.0) {
                        if ($k != $m) {
                            $h[$k][$k - 1] = -$s * $x;
                        } elseif ($l != $m) {
                            $h[$k][$k - 1] = -$h[$k][$k - 1];
                        }

                        $p += $s;
                        $x = $p / $s;
                        $y = $q / $s;
                        $z = $r / $s;
                        $q /= $p;
                        $r /= $p;

                        for ($j = $k; $j < $nn; ++$j) {
                            $p = $h[$k][$j] + $q * $h[$k + 1][$j];

                            if ($notlast) {
                                $p += $r * $h[$k + 2][$j];
                                $h[$k + 2][$j] -= $p * $z;
                            }

                            $h[$k][$j] -= $p * $x;
                            $h[$k + 1][$j] -= $p * $y;
                        }

                        for ($i = 0; $i <= min($n, $k + 3); ++$i) {
                            $p = $x * $h[$i][$k] + $y * $h[$i][$k + 1];

                            if ($notlast) {
                                $p += $z * $h[$i][$k + 2];
                                $h[$i][$k + 2] -= $p * $r;
                            }

                            $h[$i][$k] -= $p;
                            $h[$i][$k + 1] -= $p * $q;
                        }

                        for ($i = $low; $i <= $high; ++$i) {
                            $p = $x * $v[$i][$k] + $y * $v[$i][$k + 1];

                            if ($notlast) {
                                $p += $z * $v[$i][$k + 2];
                                $v[$i][$k + 2] -= $p * $r;
                            }

                            $v[$i][$k] -= $p;
                            $v[$i][$k + 1] -= $p * $q;
                        }
                    }
                }
            }
        }

        if ($norm == 0.0) {
            return [
                'd' => $d,
                'e' => $e,
                'v' => $v,
            ];
        }

        for ($m = $nn - 1; $m >= 0; --$m) {
            $p = $d[$m];
            $q = $e[$m];

            if ($q == 0.0) {
                $l = $m;

                $h[$m][$m] = 1.0;

                $z = 0.0;
                $s = 0.0;

                for ($i = $m - 1; $i >= 0; --$i) {
                    $w = $h[$i][$i] - $p;
                    $r = 0.0;

                    for ($j = $l; $j <= $m; ++$j) {
                        $r += $h[$i][$j] * $h[$j][$m];
                    }

                    if ($e[$i] < 0.0) {
                        $z = $w;
                        $s = $r;
                    } else {
                        $l = $i;

                        if ($e[$i] == 0.0) {
                            if ($w != 0.0) {
                                $h[$i][$m] = -$r / $w;
                            } else {
                                $h[$i][$m] = -$r / ($eps * $norm);
                            }
                        } else {
                            $x = $h[$i][$i + 1];
                            $y = $h[$i + 1][$i];
                            $q = ($d[$i] - $p) * ($d[$i] - $p) + $e[$i] * $e[$i];
                            $t = ($x * $s - $z * $r) / $q;
                            $h[$i][$m] = $t;

                            if (abs($x) > abs($z)) {
                                $h[$i + 1][$m] = (-$r - $w * $t) / $x;
                            } else {
                                $h[$i + 1][$m] = (-$s - $y * $t) / $z;
                            }
                        }

                        $t = abs($h[$i][$m]);

                        if (($eps * $t) * $t > 1.0) {
                            for ($j = $i; $j <= $m; ++$j) {
                                $h[$j][$m] /= $t;
                            }
                        }
                    }
                }
            } elseif ($q < 0.0) {
                $l = $m - 1;

                $r = 0.0;
                $s = 0.0;
                $z = 0.0;

                if (abs($h[$m][$m - 1]) > abs($h[$m - 1][$m])) {
                    $h[$m - 1][$m - 1] = $q / $h[$m][$m - 1];
                    $h[$m - 1][$m] = -($h[$m][$m] - $p) / $h[$m][$m - 1];
                } else {
                    [$cdivr, $cdivi] = self::cdiv(0.0, -$h[$m - 1][$m], $h[$m - 1][$m - 1] - $p, $q);
                    $h[$m - 1][$m - 1] = $cdivr;
                    $h[$m - 1][$m] = $cdivi;
                }

                $h[$m][$m - 1] = 0.0;
                $h[$m][$m] = 1.0;

                for ($i = $m - 2; $i >= 0; --$i) {
                    $ra = 0.0;
                    $sa = 0.0;

                    for ($j = $l; $j <= $m; ++$j) {
                        $ra += $h[$i][$j] * $h[$j][$m - 1];
                        $sa += $h[$i][$j] * $h[$j][$m];
                    }

                    $w = $h[$i][$i] - $p;

                    if ($e[$i] < 0.0) {
                        $z = $w;
                        $r = $ra;
                        $s = $sa;
                    } else {
                        $l = $i;

                        if ($e[$i] == 0.0) {
                            [$cdivr, $cdivi] = self::cdiv(-$ra, -$sa, $w, $q);
                            $h[$i][$m - 1] = $cdivr;
                            $h[$i][$m] = $cdivi;
                        } else {
                            $x = $h[$i][$i + 1];
                            $y = $h[$i + 1][$i];

                            $vr = ($d[$i] - $p) * ($d[$i] - $p) + $e[$i] * $e[$i] - $q * $q;
                            $vi = ($d[$i] - $p) * 2.0 * $q;

                            if ($vr == 0.0 && $vi == 0.0) {
                                $vr = $eps * $norm * (abs($w) + abs($q) + abs($x) + abs($y) + abs($z));
                            }

                            [$cdivr, $cdivi] = self::cdiv($x * $r - $z * $ra + $q * $sa, $x * $s - $z * $sa - $q * $ra, $vr, $vi);
                            $h[$i][$m - 1] = $cdivr;
                            $h[$i][$m] = $cdivi;

                            if (abs($x) > abs($z) + abs($q)) {
                                $h[$i + 1][$m - 1] = (-$ra - $w * $h[$i][$m - 1] + $q * $h[$i][$m]) / $x;
                                $h[$i + 1][$m] = (-$sa - $w * $h[$i][$m] - $q * $h[$i][$m - 1]) / $x;
                            } else {
                                [$cdivr, $cdivi] = self::cdiv(-$r - $y * $h[$i][$m - 1], -$s - $y * $h[$i][$m], $z, $q);
                                $h[$i + 1][$m - 1] = $cdivr;
                                $h[$i + 1][$m] = $cdivi;
                            }
                        }

                        $t = max(abs($h[$i][$m - 1]), abs($h[$i][$m]));

                        if (($eps * $t) * $t > 1.0) {
                            for ($j = $i; $j <= $m; ++$j) {
                                $h[$j][$m - 1] /= $t;
                                $h[$j][$m] /= $t;
                            }
                        }
                    }
                }
            }
        }

        for ($j = $nn - 1; $j >= $low; --$j) {
            for ($i = $low; $i <= $high; ++$i) {
                $z = 0.0;

                for ($k = $low; $k <= min($j, $high); ++$k) {
                    $z += $v[$i][$k] * $h[$k][$j];
                }

                $v[$i][$j] = $z;
            }
        }

        return [
            'd' => $d,
            'e' => $e,
            'v' => $v,
        ];
    }

    /**
     * Complex division of two complex numbers.
     *
     * @param float $xr
     * @param float $xi
     * @param float $yr
     * @param float $yi
     * @return array{0: float, 1: float}
     */
    protected static function cdiv(float $xr, float $xi, float $yr, float $yi) : array
    {
        if (abs($yr) > abs($yi)) {
            $r = $yi / $yr;
            $d = $yr + $r * $yi;

            return [
                ($xr + $r * $xi) / $d,
                ($xi - $r * $xr) / $d,
            ];
        }

        $r = $yr / $yi;
        $d = $yi + $r * $yr;

        return [
            ($r * $xr + $xi) / $d,
            ($r * $xi - $xr) / $d,
        ];
    }

    /**
     * @param (int|float)[] $eigenvalues
     * @param Matrix $eigenvectors
     */
    public function __construct(array $eigenvalues, Matrix $eigenvectors)
    {
        $this->eigenvalues = $eigenvalues;
        $this->eigenvectors = $eigenvectors;
    }

    /**
     * Return the eigenvalues of the eigendecomposition.
     *
     * @return (int|float)[]
     */
    public function eigenvalues() : array
    {
        return $this->eigenvalues;
    }

    /**
     * Return the eigenvectors of the eigendecomposition.
     *
     * @return Matrix
     */
    public function eigenvectors() : Matrix
    {
        return $this->eigenvectors;
    }
}
