<?php

namespace Tensor\Tests;

use Tensor\Tensor;
use Tensor\Vector;
use Tensor\Matrix;
use Tensor\Special;
use Tensor\ArrayLike;
use Tensor\Algebraic;
use Tensor\Arithmetic;
use Tensor\Comparable;
use Tensor\Statistical;
use Tensor\ColumnVector;
use Tensor\Trigonometric;
use Tensor\Reductions\REF;
use Tensor\Reductions\RREF;
use Tensor\Decompositions\LU;
use Tensor\Decompositions\SVD;
use Tensor\Decompositions\Eigen;
use Tensor\Decompositions\Cholesky;
use PHPUnit\Framework\TestCase;
use Generator;

/**
 * @covers \Tensor\Matrix
 */
class MatrixTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    /**
     * @test
     */
    public function build() : void
    {
        $matrix = Matrix::build([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertInstanceOf(Matrix::class, $matrix);
        $this->assertInstanceOf(Tensor::class, $matrix);
        $this->assertInstanceOf(ArrayLike::class, $matrix);
        $this->assertInstanceOf(Arithmetic::class, $matrix);
        $this->assertInstanceOf(Comparable::class, $matrix);
        $this->assertInstanceOf(Algebraic::class, $matrix);
        $this->assertInstanceOf(Trigonometric::class, $matrix);
        $this->assertInstanceOf(Statistical::class, $matrix);
        $this->assertInstanceOf(Special::class, $matrix);
    }

    /**
     * @test
     */
    public function identity() : void
    {
        $matrix = Matrix::identity(4);

        $expected = Matrix::quick([
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function zeros() : void
    {
        $matrix = Matrix::zeros(2, 4);

        $expected = Matrix::quick([
            [0, 0, 0, 0],
            [0, 0, 0, 0],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function ones() : void
    {
        $matrix = Matrix::ones(4, 2);

        $expected = Matrix::quick([
            [1, 1],
            [1, 1],
            [1, 1],
            [1, 1],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function diagonal() : void
    {
        $matrix = Matrix::diagonal([0, 1, 4, 5]);

        $expected = Matrix::quick([
            [0, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 4, 0],
            [0, 0, 0, 5],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function fill() : void
    {
        $matrix = Matrix::fill(5, 4, 4);

        $expected = Matrix::quick([
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
        ]);

        $this->assertEquals($expected, $matrix);
    }

    /**
     * @test
     */
    public function rand() : void
    {
        $matrix = Matrix::rand(4, 4);

        $this->assertCount(16, $matrix);
    }

    /**
     * @test
     */
    public function gaussian() : void
    {
        $matrix = Matrix::gaussian(3, 3);

        $this->assertCount(9, $matrix);
    }

    /**
     * @test
     */
    public function poisson() : void
    {
        $matrix = Matrix::poisson(6, 4, 2.);

        $this->assertCount(24, $matrix);
    }

    /**
     * @test
     */
    public function uniform() : void
    {
        $matrix = Matrix::uniform(3, 3);

        $this->assertCount(9, $matrix);
    }

    /**
     * @test
     */
    public function shape() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals([3, 3], $matrix->shape());
    }

    /**
     * @test
     */
    public function shapeString() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12, 16],
            [4, 11, -2, 18],
        ]);

        $this->assertEquals('2 x 4', $matrix->shapeString());
    }

    /**
     * @test
     * @dataProvider isSquareProvider
     *
     * @param Matrix $matrix
     * @param bool $expected
     */
    public function isSquare(Matrix $matrix, $expected) : void
    {
        $this->assertEquals($expected, $matrix->isSquare());
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function isSquareProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22, -17, 12],
                [4, 11, -2],
                [20, -6, -9],
            ]),
            true,
        ];

        yield [
            Matrix::quick([
                [22, -17, 12, 16],
                [4, 11, -2, 18],
            ]),
            false,
        ];
    }

    /**
     * @test
     */
    public function size() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals(9, $matrix->size());
    }

    /**
     * @test
     */
    public function m() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals(3, $matrix->m());
    }

    /**
     * @test
     */
    public function n() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals(3, $matrix->n());
    }

    /**
     * @test
     */
    public function rowAsVector() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $b = $a->rowAsVector(1);

        $expected = Vector::quick([4, 11, -2]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function columnAsVector() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $b = $a->columnAsVector(1);

        $expected = ColumnVector::quick([-17, 11, -6]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function diagonalAsVector() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $b = $a->diagonalAsVector();

        $expected = Vector::quick([22, 11, -9]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function asArray() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertEquals($expected, $matrix->asArray());
    }

    /**
     * @test
     */
    public function asVectors() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $vectors = $matrix->asVectors();

        $expected = [
            Vector::quick([22, -17, 12]),
            Vector::quick([4, 11, -2]),
            Vector::quick([20, -6, -9]),
        ];

        $this->assertEquals($expected, $vectors);
    }

    /**
     * @test
     */
    public function asColumnVectors() : void
    {
        $matrix = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $vectors = $matrix->asColumnVectors();

        $expected = [
            ColumnVector::quick([22, 4, 20]),
            ColumnVector::quick([-17, 11, -6]),
            ColumnVector::quick([12, -2, -9]),
        ];

        $this->assertEquals($expected, $vectors);
    }

    /**
     * @test
     */
    public function flatten() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $b = $a->flatten();

        $expected = Vector::quick([22, -17, 12, 4, 11, -2, 20, -6, -9]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function transpose() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $b = $a->transpose();

        $expected = Matrix::quick([
            [22, 4, 20],
            [-17, 11, -6],
            [12, -2, -9],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function inverse() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $b = $a->inverse();

        $expected = Matrix::quick([
            [0.02093549603923048, 0.042436816295737464, 0.018483591097698978],
            [0.0007544322897019996, 0.08261033572236892, -0.017351942663145988],
            [0.04602036967182196, 0.03923047906450396, -0.05846850245190495],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function pseudoinverse() : void
    {
        $a = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
        ]);

        $b = $a->pseudoinverse();

        $expected = Matrix::quick([
            [0.03147992432205172, 0.05583000490505223],
            [-0.009144418751313844, 0.07003713825239999],
            [0.01266554551187723, -0.0031357298016957483],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function det() : void
    {
        $a = Matrix::quick([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ]);

        $this->assertEqualsWithDelta(-544.0, $a->det(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function trace() : void
    {
        $a = Matrix::quick([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ]);

        $this->assertEquals(21.0, $a->trace());
    }

    /**
     * @test
     * @dataProvider symmetricProvider
     *
     * @param Matrix $matrix
     * @param bool $expected
     */
    public function symmetric(Matrix $matrix, $expected) : void
    {
        $this->assertEquals($expected, $matrix->symmetric());
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function symmetricProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22, -17, 12],
                [4, 11, -2],
                [20, -6, -9],
            ]),
            false,
        ];

        yield [
            Matrix::quick([
                [1, 5, 2],
                [5, 1, 3],
                [2, 3, 1],
            ]),
            true,
        ];
    }

    /**
     * @test
     */
    public function rank() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $this->assertEquals(3, $a->rank());
    }

    /**
     * @test
     */
    public function fullRank() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $this->assertTrue($a->fullRank());
    }

    /**
     * @test
     */
    public function reciprocal() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->reciprocal();

        $expected = Matrix::quick([
            [0.045454545454545456, -0.058823529411764705, 0.08333333333333333],
            [0.25, 0.09090909090909091, -0.5],
            [0.05, -0.16666666666666666, -0.1111111111111111],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function map() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $sign = function ($value) {
            return $value >= 0.0 ? 1 : -1;
        };

        $b = $a->map($sign);

        $expected = Matrix::quick([
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function ref() : void
    {
        $matrix = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $ref = $matrix->ref();

        $a = Matrix::quick([
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ]);

        $expected = new REF($a, 0);

        $this->assertEqualsWithDelta($expected, $ref, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function rref() : void
    {
        $matrix = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $rref = $matrix->rref();

        $a = Matrix::quick([
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ]);

        $expected = new RREF($a);

        $this->assertEqualsWithDelta($expected, $rref, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function lu() : void
    {
        $matrix = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $lu = $matrix->lu();

        $l = Matrix::quick([
            [1.0, 0, 0],
            [0.18181818181818182, 1.0, 0],
            [0.9090909090909091, 0.6709677419354838, 1.0],
        ]);

        $u = Matrix::quick([
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ]);

        $p = Matrix::quick([
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ]);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function cholesky() : void
    {
        $matrix = Matrix::quick([
            [2, -1, 0],
            [-1, 2, -1],
            [0, -1, 2],
        ]);

        $cholesky = $matrix->cholesky();

        $l = Matrix::quick([
            [1.4142135623730951, 0, 0],
            [-0.7071067811865475, 1.224744871391589, 0],
            [0, -0.8164965809277261, 1.1547005383792515],
        ]);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $cholesky, self::MAX_DELTA);
    }

    /**
     * @test
     * @requires extension tensor
     * @dataProvider eigProvider
     *
     * @param Matrix $matrix
     * @param Eigen $expected
     */
    public function eig(Matrix $matrix, Eigen $expected) : void
    {
        $eig = $matrix->eig(false);

        $this->assertEqualsWithDelta($expected, $eig, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function eigProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            new Eigen(
                [
                    -15.096331148319537, 25.108706520450326, 13.9876246278692,
                ],
                Matrix::quick([
                    [0.25848694820886425, -0.11314537870318066, -0.9593657388523845],
                    [-0.8622719261400653, -0.17721179605718698, -0.47442924101375483],
                    [-0.6684472200177011, -0.6126879076802705, -0.42165369894378907],
                ])
            ),
        ];
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function eigSymmetric() : void
    {
        $matrix = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $eig = $matrix->matmul($matrix)->eig(true);

        $values = [-366.30071669298195, 335.92000012383926, 1084.3807165691428];

        $vectors = Matrix::quick([
            [0.5423765325213931, 0.8162941265260668, -0.19872492538460218],
            [-0.04667292577741032, 0.26544998308386847, 0.9629942598375911],
            [-0.8388380862654284, 0.5130304137961217, -0.1820726765627782],
        ]);

        $expected = new Eigen($values, $vectors);

        $this->assertEqualsWithDelta($expected, $eig, self::MAX_DELTA);
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function svd() : void
    {
        $matrix = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $svd = $matrix->svd();

        $u = Matrix::quick([
            [-0.8436018806559158, 0.4252547343454771, -0.3278631999333884],
            [0.08179499775610413, -0.5016868397437385, -0.8611735557772425],
            [-0.5307027843302525, -0.7533052009276842, 0.38844025146657923],
        ]);

        $singularValues = [
            34.66917512262571, 17.12630582468919, 8.929610580306822,
        ];

        $vT = Matrix::quick([
            [-0.8320393250771425, 0.531457514846513, -0.15894486917903863],
            [-0.4506078135544562, -0.48043370238236727, 0.7524201326246152],
            [-0.3235168618307952, -0.6976649392999047, -0.6392186422366096],
        ]);

        $expected = new SVD($u, $singularValues, $vT);

        $this->assertEqualsWithDelta($expected, $svd, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function matmul() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $c = $a->matmul($b);

        $expected = Matrix::quick([
            [207], [155], [113],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function dotVector() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = Vector::quick([2, 10, -1]);

        $c = $a->dot($b);

        $expected = ColumnVector::quick([-138, 120, -11]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function convolve() : void
    {
        $a = Matrix::quick([
            [3, 27, 66, 29, 42, 5],
            [5, 9, 15, 42, 45, 16],
            [1, 5, 10, 22, 66, 5],
            [0, 1, 4, 9, 10, 22, 2],
            [0, 0, 3, 19, 21, 25],
            [0, 0, 0, 5, 2, 33, 35],
        ]);

        $b = Matrix::quick([
            [0, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
        ]);

        $c = $a->convolve($b, 1);

        $expected = Matrix::quick([
            [3, 32, 75, 44, 84, 50],
            [32, 76, 49, 94, 72, 82],
            [10, 20, 53, 71, 91, 15],
            [5, 11, 26, 78, 34, 43],
            [1, 4, 12, 29, 48, 27],
            [0, 3, 19, 26, 27, 33],
        ]);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @test
     * @dataProvider multiplyProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function multiply(Matrix $a, $b, $expected) : void
    {
        $c = $a->multiply($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function multiplyProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [88, -102, -144],
                [4, 33, -10],
                [-200, 6, -126],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [44, -170, -12],
                [8, 110, 2],
                [40, -60, 9],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [55.0, -42.5, 30.],
                [-4, -11, 2],
                [96.0, -28.799999999999997, -43.199999999999996],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            2.5,
            Matrix::quick([
                [55, -42.5, 30],
                [10.0, 27.5, -5.],
                [50, -15, -22.5],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider divideProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function divide(Matrix $a, $b, $expected) : void
    {
        $c = $a->divide($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function divideProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [5.5, -2.8333333333333335, -1],
                [4, 3.6666666666666665, -0.4],
                [-2, 6, -0.6428571428571429],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [11, -1.7, -12],
                [2, 1.1, 2],
                [10, -0.6, 9],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [8.8, -6.8, 4.8],
                [-4, -11, 2],
                [4.166666666666667, -1.25, -1.875],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            2.0,
            Matrix::quick([
                [11.0, -8.5, 6.],
                [2.0, 5.5, -1.],
                [10.0, -3.0, -4.5],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider addProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function add(Matrix $a, $b, $expected) : void
    {
        $c = $a->add($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function addProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [26, -11, 0],
                [5, 14, 3],
                [10, -7, 5],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [24, -7, 11],
                [6, 21, -3],
                [22, 4, -10],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [24.5, -14.5, 14.5],
                [3, 10, -3],
                [24.8, -1.2000000000000002, -4.2],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            1.0,
            Matrix::quick([
                [23, -16, 13],
                [5, 12, -1],
                [21, -5, -8],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider subtractProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function subtract(Matrix $a, $b, $expected) : void
    {
        $c = $a->subtract($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function subtractProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [18, -23, 24],
                [3, 8, -7],
                [30, -5, -23],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [20, -27, 13],
                [2, 1, -1],
                [18, -16, -8],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [19.5, -19.5, 9.5],
                [5, 12, -1],
                [15.2, -10.8, -13.8],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            10.0,
            Matrix::quick([
                [12, -27, 2],
                [-6, 1, -12],
                [10, -16, -19],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider powProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function pow(Matrix $a, $b, $expected) : void
    {
        $c = $a->pow($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function powProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [234256, 24137569, 1.1215665478461509E-13],
                [4, 1331, -32],
                [9.765625E-14, -0.16666666666666666, 22876792454961],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [484, 2015993900449, 0.08333333333333333],
                [16, 25937424601, -0.5],
                [400, 60466176, -0.1111111111111111],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            3.0,
            Matrix::quick([
                [10648, -4913, 1728],
                [64, 1331, -8],
                [8000, -216, -729],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider modProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function mod(Matrix $a, $b, $expected) : void
    {
        $c = $a->mod($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function modProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [2, -5, 0],
                [0, 2, -2],
                [0, 0, -9],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [0, -7, 0],
                [0, 1, 0],
                [0, -6, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [0,  -1,  0],
                [0, 0, 0],
                [0,  -2,  -1]
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            10.0,
            Matrix::quick([
                [2, -7, 2],
                [4, 1, -2],
                [0, -6, -9],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider equalProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function equal(Matrix $a, $b, $expected) : void
    {
        $c = $a->equal($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function equalProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            4.0,
            Matrix::quick([
                [0, 0, 0],
                [1, 0, 0],
                [0, 0, 0],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider notEqualProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function notEqual(Matrix $a, $b, $expected) : void
    {
        $c = $a->notEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function notEqualProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            4.0,
            Matrix::quick([
                [1, 1, 1],
                [0, 1, 1],
                [1, 1, 1],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider greaterProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function greater(Matrix $a, $b, $expected) : void
    {
        $c = $a->greater($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function greaterProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            4.0,
            Matrix::quick([
                [1, 0, 1],
                [0, 1, 0],
                [1, 0, 0],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider greaterEqualProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function greaterEqual(Matrix $a, $b, $expected) : void
    {
        $c = $a->greaterEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function greaterEqualProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            4.0,
            Matrix::quick([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider lessProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function less(Matrix $a, $b, $expected) : void
    {
        $c = $a->less($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function lessProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            10.0,
            Matrix::quick([
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 1],
            ]),
        ];
    }

    /**
     * @test
     * @dataProvider lessEqualProvider
     *
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    public function lessEqual(Matrix $a, $b, $expected) : void
    {
        $c = $a->lessEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @return \Generator<mixed[]>
     */
    public function lessEqualProvider() : Generator
    {
        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Matrix::quick([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ]),
            Matrix::quick([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            Vector::quick([2, 10, -1]),
            Matrix::quick([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            ColumnVector::quick([2.5, -1, 4.8]),
            Matrix::quick([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ]),
        ];

        yield [
            Matrix::quick([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ]),
            10.0,
            Matrix::quick([
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 1],
            ]),
        ];
    }

    /**
     * @test
     */
    public function abs() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->abs();

        $expected = Matrix::quick([
            [22, 17, 12],
            [4, 11, 2],
            [20, 6, 9],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function square() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->square();

        $expected = Matrix::quick([
            [484, 289, 144],
            [16, 121, 4],
            [400, 36, 81],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function sqrt() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->sqrt();

        $expected = Matrix::quick([
            [3.605551275463989],
            [3.3166247903554],
            [3],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function exp() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->exp();

        $expected = Matrix::quick([
            [442413.3920089205],
            [59874.14171519778],
            [8103.08392757538],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function expm1() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->expm1();

        $expected = Matrix::quick([
            [442412.3920089205],
            [59873.14171519782],
            [8102.083927575384],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function log() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->log();

        $expected = Matrix::quick([
            [2.5649493574615367],
            [2.3978952727983707],
            [2.1972245773362196],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function log1p() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->log1p();

        $expected = Matrix::quick([
            [2.6390573296152584],
            [2.4849066497880004],
            [2.302585092994046],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function sin() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->sin();

        $expected = Matrix::quick([
            [0.4201670368266409],
            [-0.9999902065507035],
            [0.4121184852417566],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function asin() : void
    {
        $a = Matrix::quick([
            [0.32],
            [-0.5],
            [0.01],
        ]);

        $b = $a->asin();

        $expected = Matrix::quick([
            [0.3257294872946302],
            [-0.5235987755982989],
            [0.010000166674167114],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function cos() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->cos();

        $expected = Matrix::quick([
            [0.9074467814501962],
            [0.004425697988050785],
            [-0.9111302618846769],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function acos() : void
    {
        $a = Matrix::quick([
            [0.32],
            [-0.5],
            [0.01],
        ]);

        $b = $a->acos();

        $expected = Matrix::quick([
            [1.2450668395002664],
            [2.0943951023931957],
            [1.5607961601207294],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function tan() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->tan();

        $expected = Matrix::quick([
            [0.4630211329364896],
            [-225.95084645419513],
            [-0.45231565944180985],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function atan() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->atan();

        $expected = Matrix::quick([
            [1.4940244355251187],
            [1.4801364395941514],
            [1.460139105621001],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function rad2deg() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->rad2deg();

        $expected = Matrix::quick([
            [744.8451336700701],
            [630.2535746439056],
            [515.6620156177408],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function deg2rad() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->deg2rad();

        $expected = Matrix::quick([
            [0.22689280275926282],
            [0.19198621771937624],
            [0.15707963267948966],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function sum() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->sum();

        $expected = ColumnVector::quick([17, 13, 5]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function product() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->product();

        $expected = ColumnVector::quick([-4488.0, -88.0, 1080.0]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function min() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->min();

        $expected = ColumnVector::quick([-17, -2, -9]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function max() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->max();

        $expected = ColumnVector::quick([22, 11, 20]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function mean() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->mean();

        $expected = ColumnVector::quick([5.666666666666667, 4.333333333333333, 1.6666666666666667]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function median() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->median();

        $expected = ColumnVector::quick([12, 4, -6]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function quantile() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->quantile(0.4);

        $expected = ColumnVector::quick([6.200000000000001, 2.8000000000000003, -6.6]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function variance() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->variance();

        $expected = ColumnVector::quick([273.55555555555554, 28.222222222222225, 169.55555555555554]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function covariance() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->covariance();

        $expected = Matrix::quick([
            [273.55555555555554, -65.55555555555556, 135.2222222222222],
            [-65.55555555555556, 28.222222222222225, 3.4444444444444406],
            [135.2222222222222, 3.4444444444444406, 169.55555555555554],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function round() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->round(2);

        $expected = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function floor() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->floor();

        $expected = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function ceil() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->ceil();

        $expected = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function l1Norm() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $this->assertEqualsWithDelta(46.0, $a->l1Norm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function l2Norm() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $this->assertEqualsWithDelta(39.68626966596886, $a->l2Norm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function infinityNorm() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $this->assertEqualsWithDelta(51.0, $a->infinityNorm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function maxNorm() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $this->assertEqualsWithDelta(22.0, $a->maxNorm(), self::MAX_DELTA);
    }

    /**
     * @test
     */
    public function clip() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->clip(0.0, INF);

        $expected = Matrix::quick([
            [22, 0.0, 12],
            [4, 11, 0.],
            [20, 0.0, 0.],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function clipLower() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->clipLower(5.);

        $expected = Matrix::quick([
            [22, 5.0, 12],
            [5.0, 11, 5.],
            [20, 5.0, 5.],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function clipUpper() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->clipUpper(16.0);

        $expected = Matrix::quick([
            [16.0, -17.0, 12],
            [4, 11, -2.0],
            [16, -6.0, -9.0],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function sign() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->sign();

        $expected = Matrix::quick([
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function negate() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = $a->negate();

        $expected = Matrix::quick([
            [-22, 17, -12],
            [-4, -11, 2],
            [-20, 6, 9],
        ]);

        $this->assertEquals($expected, $b);
    }

    /**
     * @test
     */
    public function augmentAbove() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = Matrix::quick([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ]);

        $c = $a->augmentAbove($b);

        $expected = Matrix::quick([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function augmentBelow() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = Matrix::quick([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ]);

        $c = $a->augmentBelow($b);

        $expected = Matrix::quick([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function augmentLeft() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $c = $a->augmentLeft($b);

        $expected = Matrix::quick([
            [13, 22, -17, 12],
            [11, 4, 11, -2],
            [9, 20, -6, -9],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function augmentRight() : void
    {
        $a = Matrix::quick([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ]);

        $b = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $c = $a->augmentRight($b);

        $expected = Matrix::quick([
            [22, -17, 12, 13],
            [4, 11, -2, 11],
            [20, -6, -9, 9],
        ]);

        $this->assertEquals($expected, $c);
    }

    /**
     * @test
     */
    public function repeat() : void
    {
        $a = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $b = $a->repeat(1, 3);

        $expected = Matrix::quick([
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
        ]);

        $this->assertEquals($expected, $b);
    }
}
