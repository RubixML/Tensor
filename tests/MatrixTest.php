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
use Tensor\Exceptions\RuntimeException;
use Tensor\Exceptions\InvalidArgumentException;
use Tensor\Exceptions\DimensionalityMismatch;
use Tensor\Decompositions\Eigen;
use Tensor\Decompositions\Cholesky;
use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\CoversClass;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\Test;
use Generator;

#[CoversClass(Matrix::class)]
class MatrixTest extends TestCase
{
    /**
     * The maximum error tolerated due to varying numerical precision.
     *
     * @var float
     */
    protected const MAX_DELTA = 1e-8;

    /**
     * @return Generator<mixed[]>
     */
    public static function isSquareProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22, -17, 12],
                [4, 11, -2],
                [20, -6, -9],
            ], false),
            true,
        ];

        yield [
            Matrix::fromArray([
                [22, -17, 12, 16],
                [4, 11, -2, 18],
            ], false),
            false,
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function symmetricProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22, -17, 12],
                [4, 11, -2],
                [20, -6, -9],
            ], false),
            false,
        ];

        yield [
            Matrix::fromArray([
                [1, 5, 2],
                [5, 1, 3],
                [2, 3, 1],
            ], false),
            true,
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function multiplyProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [88, -102, -144],
                [4, 33, -10],
                [-200, 6, -126],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [44, -170, -12],
                [8, 110, 2],
                [40, -60, 9],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [55.0, -42.5, 30.],
                [-4, -11, 2],
                [96.0, -28.799999999999997, -43.199999999999996],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            2.5,
            Matrix::fromArray([
                [55, -42.5, 30],
                [10.0, 27.5, -5.],
                [50, -15, -22.5],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function divideProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [5.5, -2.8333333333333335, -1],
                [4, 3.6666666666666665, -0.4],
                [-2, 6, -0.6428571428571429],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [11, -1.7, -12],
                [2, 1.1, 2],
                [10, -0.6, 9],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [8.8, -6.8, 4.8],
                [-4, -11, 2],
                [4.166666666666667, -1.25, -1.875],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            2.0,
            Matrix::fromArray([
                [11.0, -8.5, 6.],
                [2.0, 5.5, -1.],
                [10.0, -3.0, -4.5],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function addProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [26, -11, 0],
                [5, 14, 3],
                [10, -7, 5],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [24, -7, 11],
                [6, 21, -3],
                [22, 4, -10],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [24.5, -14.5, 14.5],
                [3, 10, -3],
                [24.8, -1.2000000000000002, -4.2],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            1.0,
            Matrix::fromArray([
                [23, -16, 13],
                [5, 12, -1],
                [21, -5, -8],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function subtractProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [18, -23, 24],
                [3, 8, -7],
                [30, -5, -23],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [20, -27, 13],
                [2, 1, -1],
                [18, -16, -8],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [19.5, -19.5, 9.5],
                [5, 12, -1],
                [15.2, -10.8, -13.8],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            10.0,
            Matrix::fromArray([
                [12, -27, 2],
                [-6, 1, -12],
                [10, -16, -19],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function powProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [234256, 24137569, 1.1215665478461509E-13],
                [4, 1331, -32],
                [9.765625E-14, -0.16666666666666666, 22876792454961],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [484, 2015993900449, 0.08333333333333333],
                [16, 25937424601, -0.5],
                [400, 60466176, -0.1111111111111111],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            3.0,
            Matrix::fromArray([
                [10648, -4913, 1728],
                [64, 1331, -8],
                [8000, -216, -729],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function modProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [2, -5, 0],
                [0, 2, -2],
                [0, 0, -9],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [0, -7, 0],
                [0, 1, 0],
                [0, -6, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [2.0, -2.0, 2.0],
                [0.0, 0.0, 0.0],
                [0.8, -1.2, -4.2],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            10.0,
            Matrix::fromArray([
                [2, -7, 2],
                [4, 1, -2],
                [0, -6, -9],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function equalProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [0, 0, 0],
                [0, 0, 0],
                [0, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            4.0,
            Matrix::fromArray([
                [0, 0, 0],
                [1, 0, 0],
                [0, 0, 0],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function notEqualProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [1, 1, 1],
                [1, 1, 1],
                [1, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            4.0,
            Matrix::fromArray([
                [1, 1, 1],
                [0, 1, 1],
                [1, 1, 1],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function greaterProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            4.0,
            Matrix::fromArray([
                [1, 0, 1],
                [0, 1, 0],
                [1, 0, 0],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function greaterEqualProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            4.0,
            Matrix::fromArray([
                [1, 0, 1],
                [1, 1, 0],
                [1, 0, 0],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function lessProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            10.0,
            Matrix::fromArray([
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 1],
            ], false),
        ];
    }

    /**
     * @return Generator<mixed[]>
     */
    public static function lessEqualProvider() : Generator
    {
        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Matrix::fromArray([
                [4, 6, -12],
                [1, 3, 5],
                [-10, -1, 14],
            ], false),
            Matrix::fromArray([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            Vector::fromArray([2, 10, -1], false),
            Matrix::fromArray([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            ColumnVector::fromArray([2.5, -1, 4.8], false),
            Matrix::fromArray([
                [0, 1, 0],
                [0, 0, 1],
                [0, 1, 1],
            ], false),
        ];

        yield [
            Matrix::fromArray([
                [22.0, -17.0, 12.0],
                [4.0, 11.0, -2.0],
                [20.0, -6.0, -9.0],
            ], false),
            10.0,
            Matrix::fromArray([
                [0, 1, 0],
                [1, 0, 1],
                [0, 1, 1],
            ], false),
        ];
    }

    #[Test]
    public function fromArray() : void
    {
        $matrix = Matrix::fromArray([
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

    #[Test]
    public function fromArrayCastsIntegersToFloatsAndPreservesShape() : void
    {
        $matrix = Matrix::fromArray([
            [1, 2, 3],
            [4, 5, 6],
        ]);

        $this->assertSame([2, 3], $matrix->shape());
        $this->assertSame(6, $matrix->size());

        $result = $matrix->asArray();

        $this->assertCount(2, $result);

        foreach ($result as $row) {
            $this->assertCount(3, $row);

            foreach ($row as $value) {
                $this->assertTrue(is_float($value));
            }
        }

        $this->assertEqualsWithDelta([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], $result, self::MAX_DELTA);
    }

    #[Test]
    public function identity() : void
    {
        $matrix = Matrix::identity(4);

        $expected = Matrix::fromArray([
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1],
        ], false);

        $this->assertEquals($expected, $matrix);
    }

    #[Test]
    public function zeros() : void
    {
        $matrix = Matrix::zeros(2, 4);

        $expected = Matrix::fromArray([
            [0, 0, 0, 0],
            [0, 0, 0, 0],
        ], false);

        $this->assertEquals($expected, $matrix);
    }

    #[Test]
    public function ones() : void
    {
        $matrix = Matrix::ones(4, 2);

        $expected = Matrix::fromArray([
            [1, 1],
            [1, 1],
            [1, 1],
            [1, 1],
        ], false);

        $this->assertEquals($expected, $matrix);
    }

    #[Test]
    public function diagonal() : void
    {
        $matrix = Matrix::diagonal([0, 1, 4, 5]);

        $expected = Matrix::fromArray([
            [0, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 4, 0],
            [0, 0, 0, 5],
        ], false);

        $this->assertEquals($expected, $matrix);
    }

    #[Test]
    public function fill() : void
    {
        $matrix = Matrix::fill(5, 4, 4);

        $expected = Matrix::fromArray([
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
        ], false);

        $this->assertEquals($expected, $matrix);
    }

    #[Test]
    public function rand() : void
    {
        $matrix = Matrix::rand(4, 4);

        $this->assertCount(16, $matrix);
    }

    #[Test]
    public function gaussian() : void
    {
        $matrix = Matrix::gaussian(3, 3);

        $this->assertCount(9, $matrix);
    }

    #[Test]
    public function poisson() : void
    {
        $matrix = Matrix::poisson(6, 4, 2.);

        $this->assertCount(24, $matrix);
    }

    #[Test]
    public function poissonZeroLambdaIsZero() : void
    {
        $matrix = Matrix::poisson(3, 3, 0.0);

        $expected = Matrix::fill(0.0, 3, 3);

        $this->assertEquals($expected, $matrix);
    }

    #[Test]
    public function poissonNegativeLambdaThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::poisson(1, 1, -1.0);
    }

    #[Test]
    public function uniform() : void
    {
        $matrix = Matrix::uniform(3, 3);

        $this->assertCount(9, $matrix);
    }

    #[Test]
    public function shape() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals([3, 3], $matrix->shape());
    }

    #[Test]
    public function shapeString() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12, 16],
            [4, 11, -2, 18],
        ], false);

        $this->assertEquals('2 x 4', $matrix->shapeString());
    }

    /**
     * @param Matrix $matrix
     * @param bool $expected
     */
    #[Test]
    #[DataProvider('isSquareProvider')]
    public function isSquare(Matrix $matrix, $expected) : void
    {
        $this->assertEquals($expected, $matrix->isSquare());
    }

    #[Test]
    public function testSize() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals(9, $matrix->size());
    }

    #[Test]
    public function m() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals(3, $matrix->m());
    }

    #[Test]
    public function n() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals(3, $matrix->n());
    }

    #[Test]
    public function rowAsVector() : void
    {
        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $b = $a->rowAsVector(1);

        $expected = Vector::fromArray([4, 11, -2], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function columnAsVector() : void
    {
        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $b = $a->columnAsVector(1);

        $expected = ColumnVector::fromArray([-17, 11, -6], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function diagonalAsVector() : void
    {
        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $b = $a->diagonalAsVector();

        $expected = Vector::fromArray([22, 11, -9], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function asArray() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertEquals($expected, $matrix->asArray());
    }

    #[Test]
    public function asVectors() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $vectors = $matrix->asVectors();

        $expected = [
            Vector::fromArray([22, -17, 12], false),
            Vector::fromArray([4, 11, -2], false),
            Vector::fromArray([20, -6, -9], false),
        ];

        $this->assertEquals($expected, $vectors);
    }

    #[Test]
    public function asColumnVectors() : void
    {
        $matrix = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $vectors = $matrix->asColumnVectors();

        $expected = [
            ColumnVector::fromArray([22, 4, 20], false),
            ColumnVector::fromArray([-17, 11, -6], false),
            ColumnVector::fromArray([12, -2, -9], false),
        ];

        $this->assertEquals($expected, $vectors);
    }

    #[Test]
    public function flatten() : void
    {
        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $b = $a->flatten();

        $expected = Vector::fromArray([22, -17, 12, 4, 11, -2, 20, -6, -9], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function transpose() : void
    {
        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $b = $a->transpose();

        $expected = Matrix::fromArray([
            [22, 4, 20],
            [-17, 11, -6],
            [12, -2, -9],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function inverse() : void
    {
        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $b = $a->inverse();

        $expected = Matrix::fromArray([
            [0.02093549603923048, 0.042436816295737464, 0.018483591097698978],
            [0.0007544322897019996, 0.08261033572236892, -0.017351942663145988],
            [0.04602036967182196, 0.03923047906450396, -0.05846850245190495],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function inverseNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
            [5.0, 6.0],
        ], false)->inverse();
    }

    #[Test]
    public function inverseSingularThrows() : void
    {
        // Exactly singular (column 3 = column 0 - column 1 + column 2); the
        // inverse must be rejected rather than return a magnitude ~1e15 matrix
        // that does not satisfy A * A^-1 = I.
        $a = Matrix::fromArray([
            [2.0, 1.0, 0.0, 1.0],
            [1.0, 2.0, 1.0, 0.0],
            [0.0, 1.0, 2.0, 1.0],
            [1.0, 0.0, 1.0, 2.0],
        ], false);

        $this->expectException(RuntimeException::class);

        $a->inverse();
    }

    #[Test]
    public function det() : void
    {
        $a = Matrix::fromArray([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ], false);

        $this->assertEqualsWithDelta(-544.0, $a->det(), self::MAX_DELTA);
    }

    #[Test]
    public function detSingularIsZero() : void
    {
        // Exactly singular (column 3 = column 0 - column 1 + column 2); the
        // determinant must be ~0 rather than a spurious ~1e-15 value.
        $a = Matrix::fromArray([
            [2.0, 1.0, 0.0, 1.0],
            [1.0, 2.0, 1.0, 0.0],
            [0.0, 1.0, 2.0, 1.0],
            [1.0, 0.0, 1.0, 2.0],
        ], false);

        $this->assertEqualsWithDelta(0.0, $a->det(), self::MAX_DELTA);
    }

    #[Test]
    public function trace() : void
    {
        $a = Matrix::fromArray([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ], false);

        $this->assertEquals(21.0, $a->trace());
    }

    /**
     * @param Matrix $matrix
     * @param bool $expected
     */
    #[Test]
    #[DataProvider('symmetricProvider')]
    public function symmetric(Matrix $matrix, $expected) : void
    {
        $this->assertEquals($expected, $matrix->symmetric());
    }

    #[Test]
    public function rank() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $this->assertEquals(3, $a->rank());

        $b = Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false);

        $this->assertEquals(2, $b->rank());

        // Exactly singular (column 3 = column 0 - column 1 + column 2); the
        // rank must be 3, not 4, even though floating point leaves a ~1e-16
        // residual on the diagonal.
        $c = Matrix::fromArray([
            [2.0, 1.0, 0.0, 1.0],
            [1.0, 2.0, 1.0, 0.0],
            [0.0, 1.0, 2.0, 1.0],
            [1.0, 0.0, 1.0, 2.0],
        ], false);

        $this->assertEquals(3, $c->rank());
    }

    #[Test]
    public function fullRank() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $this->assertTrue($a->fullRank());

        $b = Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false);

        $this->assertTrue($b->fullRank());

        // Exactly singular 4x4 (see rank() above); fullRank() must be false.
        $c = Matrix::fromArray([
            [2.0, 1.0, 0.0, 1.0],
            [1.0, 2.0, 1.0, 0.0],
            [0.0, 1.0, 2.0, 1.0],
            [1.0, 0.0, 1.0, 2.0],
        ], false);

        $this->assertFalse($c->fullRank());
    }

    #[Test]
    public function reciprocal() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->reciprocal();

        $expected = Matrix::fromArray([
            [0.045454545454545456, -0.058823529411764705, 0.08333333333333333],
            [0.25, 0.09090909090909091, -0.5],
            [0.05, -0.16666666666666666, -0.1111111111111111],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function map() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $sign = function ($value) {
            return $value >= 0.0 ? 1 : -1;
        };

        $b = $a->map($sign);

        $expected = Matrix::fromArray([
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function reduce() : void
    {
        $a = Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false);

        $sum = function ($carry, $value) {
            return $carry + $value;
        };

        $this->assertEqualsWithDelta(10.0, $a->reduce($sum), self::MAX_DELTA);

        // Asymmetric callback: pins the (carry, value) argument order.
        $subtract = function ($carry, $value) {
            return $carry - $value;
        };

        $this->assertEqualsWithDelta(-10.0, $a->reduce($subtract), self::MAX_DELTA);
        $this->assertEqualsWithDelta(-8.0, $a->reduce($subtract, 2.0), self::MAX_DELTA);

        // Must match Vector::reduce() for the same data and callback.
        $v = Vector::fromArray([1.0, 2.0, 3.0, 4.0], false);

        $this->assertEqualsWithDelta($v->reduce($subtract), $a->reduce($subtract), self::MAX_DELTA);
    }

    #[Test]
    public function ref() : void
    {
        $matrix = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $ref = $matrix->ref();

        $a = Matrix::fromArray([
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ], false);

        $expected = new REF($a, 0);

        $this->assertEqualsWithDelta($expected, $ref, self::MAX_DELTA);
    }

    #[Test]
    public function rref() : void
    {
        $matrix = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $rref = $matrix->rref();

        $a = Matrix::fromArray([
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ], false);

        $expected = new RREF($a);

        $this->assertEqualsWithDelta($expected, $rref, self::MAX_DELTA);
    }

    #[Test]
    public function lu() : void
    {
        $matrix = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $lu = $matrix->lu();

        $l = Matrix::fromArray([
            [1.0, 0, 0],
            [0.18181818181818182, 1.0, 0],
            [0.9090909090909091, 0.6709677419354838, 1.0],
        ], false);

        $u = Matrix::fromArray([
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ], false);

        $p = Matrix::fromArray([
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ], false);

        $expected = new LU($l, $u, $p);

        $this->assertEqualsWithDelta($expected, $lu, self::MAX_DELTA);
    }

    #[Test]
    public function luMultiPivot() : void
    {
        $matrix = Matrix::fromArray([
            [0.0,  1.0,  0.0,  0.0],
            [-1.0,  0.0,  0.0,  0.0],
            [0.0,  0.0,  0.0,  2.0],
            [0.0,  0.0,  3.0,  1.0],
        ], false);

        $lu = $matrix->lu();

        $pa = $lu->p()->matmul($matrix);
        $luProd = $lu->l()->matmul($lu->u());

        $this->assertEqualsWithDelta($pa, $luProd, self::MAX_DELTA);
    }

    #[Test]
    public function luNegativePivot() : void
    {
        $matrix = Matrix::fromArray([
            [1.0,  2.0,  3.0,  4.0],
            [-9.0,  1.0,  0.0,  0.0],
            [0.5,  0.5,  1.0,  1.0],
            [0.1,  0.2,  0.3,  0.4],
        ], false);

        $lu = $matrix->lu();

        $pa = $lu->p()->matmul($matrix);
        $luProd = $lu->l()->matmul($lu->u());

        $this->assertEqualsWithDelta($pa, $luProd, self::MAX_DELTA);
    }

    #[Test]
    public function luSingular() : void
    {
        $this->expectException(RuntimeException::class);

        $matrix = Matrix::fromArray([
            [1.0, 2.0,  0.0,  0.0],
            [0.0, 1.0,  1.0,  0.0],
            [2.0, 4.0,  0.0,  1.0],
            [0.0, 1.0,  1.0,  0.0],
        ], false);

        $matrix->lu();
    }

    #[Test]
    public function cholesky() : void
    {
        $matrix = Matrix::fromArray([
            [2, -1, 0],
            [-1, 2, -1],
            [0, -1, 2],
        ], false);

        $cholesky = $matrix->cholesky();

        $l = Matrix::fromArray([
            [1.4142135623730951, 0, 0],
            [-0.7071067811865475, 1.224744871391589, 0],
            [0, -0.8164965809277261, 1.1547005383792515],
        ], false);

        $expected = new Cholesky($l);

        $this->assertEqualsWithDelta($expected, $cholesky, self::MAX_DELTA);
    }

    #[Test]
    public function matmul() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $c = $a->matmul($b);

        $expected = Matrix::fromArray([
            [207], [155], [113],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function dotVector() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = Vector::fromArray([2, 10, -1], false);

        $c = $a->dot($b);

        $expected = ColumnVector::fromArray([-138, 120, -11], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    #[Test]
    public function convolve() : void
    {
        $a = Matrix::fromArray([
            [3, 27, 66, 29, 42, 5],
            [5, 9, 15, 42, 45, 16],
            [1, 5, 10, 22, 66, 5],
            [0, 1, 4, 9, 10, 22, 2],
            [0, 0, 3, 19, 21, 25],
            [0, 0, 0, 5, 2, 33, 35],
        ], false);

        $b = Matrix::fromArray([
            [0, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
        ], false);

        $c = $a->convolve($b, 1);

        $expected = Matrix::fromArray([
            [3, 32, 75, 44, 84, 50],
            [32, 76, 49, 94, 72, 82],
            [10, 20, 53, 71, 91, 15],
            [5, 11, 26, 78, 34, 43],
            [1, 4, 12, 29, 48, 27],
            [0, 3, 19, 26, 27, 33],
        ], false);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('multiplyProvider')]
    public function multiply(Matrix $a, $b, $expected) : void
    {
        $c = $a->multiply($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('divideProvider')]
    public function divide(Matrix $a, $b, $expected) : void
    {
        $c = $a->divide($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('addProvider')]
    public function add(Matrix $a, $b, $expected) : void
    {
        $c = $a->add($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('subtractProvider')]
    public function subtract(Matrix $a, $b, $expected) : void
    {
        $c = $a->subtract($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('powProvider')]
    public function pow(Matrix $a, $b, $expected) : void
    {
        $c = $a->pow($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('modProvider')]
    public function mod(Matrix $a, $b, $expected) : void
    {
        $c = $a->mod($b);

        $this->assertEqualsWithDelta($expected, $c, self::MAX_DELTA);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('equalProvider')]
    public function equal(Matrix $a, $b, $expected) : void
    {
        $c = $a->equal($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('notEqualProvider')]
    public function notEqual(Matrix $a, $b, $expected) : void
    {
        $c = $a->notEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('greaterProvider')]
    public function greater(Matrix $a, $b, $expected) : void
    {
        $c = $a->greater($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('greaterEqualProvider')]
    public function greaterEqual(Matrix $a, $b, $expected) : void
    {
        $c = $a->greaterEqual($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('lessProvider')]
    public function less(Matrix $a, $b, $expected) : void
    {
        $c = $a->less($b);

        $this->assertEquals($expected, $c);
    }

    /**
     * @param Matrix $a
     * @param Tensor|float $b
     * @param Tensor|float $expected
     */
    #[Test]
    #[DataProvider('lessEqualProvider')]
    public function lessEqual(Matrix $a, $b, $expected) : void
    {
        $c = $a->lessEqual($b);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function abs() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->abs();

        $expected = Matrix::fromArray([
            [22, 17, 12],
            [4, 11, 2],
            [20, 6, 9],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function square() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->square();

        $expected = Matrix::fromArray([
            [484, 289, 144],
            [16, 121, 4],
            [400, 36, 81],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function sqrt() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->sqrt();

        $expected = Matrix::fromArray([
            [3.605551275463989],
            [3.3166247903554],
            [3],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function exp() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->exp();

        $expected = Matrix::fromArray([
            [442413.3920089205],
            [59874.14171519778],
            [8103.08392757538],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function expm1() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->expm1();

        $expected = Matrix::fromArray([
            [442412.3920089205],
            [59873.14171519782],
            [8102.083927575384],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function log() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->log();

        $expected = Matrix::fromArray([
            [2.5649493574615367],
            [2.3978952727983707],
            [2.1972245773362196],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function log1p() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->log1p();

        $expected = Matrix::fromArray([
            [2.6390573296152584],
            [2.4849066497880004],
            [2.302585092994046],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function sin() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->sin();

        $expected = Matrix::fromArray([
            [0.4201670368266409],
            [-0.9999902065507035],
            [0.4121184852417566],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function asin() : void
    {
        $a = Matrix::fromArray([
            [0.32],
            [-0.5],
            [0.01],
        ], false);

        $b = $a->asin();

        $expected = Matrix::fromArray([
            [0.3257294872946302],
            [-0.5235987755982989],
            [0.010000166674167114],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function cos() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->cos();

        $expected = Matrix::fromArray([
            [0.9074467814501962],
            [0.004425697988050785],
            [-0.9111302618846769],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function acos() : void
    {
        $a = Matrix::fromArray([
            [0.32],
            [-0.5],
            [0.01],
        ], false);

        $b = $a->acos();

        $expected = Matrix::fromArray([
            [1.2450668395002664],
            [2.0943951023931957],
            [1.5607961601207294],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function tan() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->tan();

        $expected = Matrix::fromArray([
            [0.4630211329364896],
            [-225.95084645419513],
            [-0.45231565944180985],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function atan() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->atan();

        $expected = Matrix::fromArray([
            [1.4940244355251187],
            [1.4801364395941514],
            [1.460139105621001],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function rad2deg() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->rad2deg();

        $expected = Matrix::fromArray([
            [744.8451336700701],
            [630.2535746439056],
            [515.6620156177408],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function deg2rad() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->deg2rad();

        $expected = Matrix::fromArray([
            [0.22689280275926282],
            [0.19198621771937624],
            [0.15707963267948966],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function sum() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->sum();

        $expected = ColumnVector::fromArray([17, 13, 5], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function product() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->product();

        $expected = ColumnVector::fromArray([-4488.0, -88.0, 1080.0], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function min() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->min();

        $expected = ColumnVector::fromArray([-17, -2, -9], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function max() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->max();

        $expected = ColumnVector::fromArray([22, 11, 20], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function mean() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->mean();

        $expected = ColumnVector::fromArray([5.666666666666667, 4.333333333333333, 1.6666666666666667], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function median() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->median();

        $expected = ColumnVector::fromArray([12, 4, -6], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function quantile() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->quantile(0.4);

        $expected = ColumnVector::fromArray([6.200000000000001, 2.8000000000000003, -6.6], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);

        $max = $a->quantile(1.0);

        $maxExpected = ColumnVector::fromArray([22.0, 11.0, 20.0], false);

        $this->assertEqualsWithDelta($maxExpected, $max, self::MAX_DELTA);

        $single = Matrix::fromArray([
            [5.0],
            [3.0],
            [8.0],
        ], false);

        $singleExpected = ColumnVector::fromArray([5.0, 3.0, 8.0], false);

        $this->assertEqualsWithDelta(
            $singleExpected,
            $single->quantile(0.5),
            self::MAX_DELTA
        );
    }

    #[Test]
    public function variance() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->variance();

        $expected = ColumnVector::fromArray([273.55555555555554, 28.222222222222225, 169.55555555555554], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function varianceRowNonSquare() : void
    {
        $a = Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [10.0, 20.0, 30.0],
        ], false);

        $b = $a->variance();

        $expected = ColumnVector::fromArray([0.6666666666666666, 66.66666666666667], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function covariance() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->covariance();

        $expected = Matrix::fromArray([
            [273.55555555555554, -65.55555555555556, 135.2222222222222],
            [-65.55555555555556, 28.222222222222225, 3.4444444444444406],
            [135.2222222222222, 3.4444444444444406, 169.55555555555554],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);

        $c = Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false);

        $d = $c->covariance();

        $expectedC = Matrix::fromArray([
            [2.0 / 3.0, 2.0 / 3.0],
            [2.0 / 3.0, 2.0 / 3.0],
        ], false);

        $this->assertEqualsWithDelta($expectedC, $d, self::MAX_DELTA);
    }

    #[Test]
    public function round() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->round(2);

        $expected = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function floor() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->floor();

        $expected = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function ceil() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->ceil();

        $expected = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function l1Norm() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $this->assertEqualsWithDelta(46.0, $a->l1Norm(), self::MAX_DELTA);
    }

    #[Test]
    public function l2Norm() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $this->assertEqualsWithDelta(39.68626966596886, $a->l2Norm(), self::MAX_DELTA);
    }

    #[Test]
    public function infinityNorm() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $this->assertEqualsWithDelta(51.0, $a->infinityNorm(), self::MAX_DELTA);
    }

    #[Test]
    public function maxNorm() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $this->assertEqualsWithDelta(22.0, $a->maxNorm(), self::MAX_DELTA);
    }

    #[Test]
    public function clip() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->clip(0.0, INF);

        $expected = Matrix::fromArray([
            [22, 0.0, 12],
            [4, 11, 0.],
            [20, 0.0, 0.],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function clipLower() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->clipLower(5.);

        $expected = Matrix::fromArray([
            [22, 5.0, 12],
            [5.0, 11, 5.],
            [20, 5.0, 5.],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function clipUpper() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->clipUpper(16.0);

        $expected = Matrix::fromArray([
            [16.0, -17.0, 12],
            [4, 11, -2.0],
            [16, -6.0, -9.0],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function sign() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->sign();

        $expected = Matrix::fromArray([
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function negate() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = $a->negate();

        $expected = Matrix::fromArray([
            [-22, 17, -12],
            [-4, -11, 2],
            [-20, 6, 9],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function augmentAbove() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = Matrix::fromArray([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ], false);

        $c = $a->augmentAbove($b);

        $expected = Matrix::fromArray([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function augmentBelow() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = Matrix::fromArray([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ], false);

        $c = $a->augmentBelow($b);

        $expected = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function augmentLeft() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $c = $a->augmentLeft($b);

        $expected = Matrix::fromArray([
            [13, 22, -17, 12],
            [11, 4, 11, -2],
            [9, 20, -6, -9],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function augmentRight() : void
    {
        $a = Matrix::fromArray([
            [22.0, -17.0, 12.0],
            [4.0, 11.0, -2.0],
            [20.0, -6.0, -9.0],
        ], false);

        $b = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $c = $a->augmentRight($b);

        $expected = Matrix::fromArray([
            [22, -17, 12, 13],
            [4, 11, -2, 11],
            [20, -6, -9, 9],
        ], false);

        $this->assertEquals($expected, $c);
    }

    #[Test]
    public function repeat() : void
    {
        $a = Matrix::fromArray([
            [13],
            [11],
            [9],
        ], false);

        $b = $a->repeat(1, 3);

        $expected = Matrix::fromArray([
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
        ], false);

        $this->assertEquals($expected, $b);
    }

    #[Test]
    public function fillNegativeMThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fill(1.0, 0, 2);
    }

    #[Test]
    public function fillNegativeNThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fill(1.0, 2, 0);
    }

    #[Test]
    public function identityNegativeNThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::identity(0);
    }

    #[Test]
    public function detNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false)->det();
    }

    #[Test]
    public function matmulDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false)->matmul(Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
            [5.0, 6.0],
        ], false));
    }

    #[Test]
    public function dotDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false)->dot(Vector::fromArray([1.0, 2.0], false));
    }

    #[Test]
    public function augmentAboveDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        Matrix::fromArray([
            [1.0, 2.0],
        ], false)->augmentAbove(Matrix::fromArray([
            [1.0, 2.0, 3.0],
        ], false));
    }

    #[Test]
    public function augmentBelowDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        Matrix::fromArray([
            [1.0, 2.0],
        ], false)->augmentBelow(Matrix::fromArray([
            [1.0, 2.0, 3.0],
        ], false));
    }

    #[Test]
    public function augmentLeftDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        Matrix::fromArray([
            [1.0, 2.0],
        ], false)->augmentLeft(Matrix::fromArray([
            [1.0],
            [2.0],
            [3.0],
        ], false));
    }

    #[Test]
    public function augmentRightDimensionMismatchThrows() : void
    {
        $this->expectException(DimensionalityMismatch::class);

        Matrix::fromArray([
            [1.0, 2.0],
        ], false)->augmentRight(Matrix::fromArray([
            [1.0],
            [2.0],
            [3.0],
        ], false));
    }

    #[Test]
    public function offsetSetThrows() : void
    {
        $this->expectException(RuntimeException::class);

        $a = Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false);

        $a[0] = 10.0;
    }

    #[Test]
    public function offsetUnsetThrows() : void
    {
        $this->expectException(RuntimeException::class);

        $a = Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false);

        unset($a[0][0]);
    }

    #[Test]
    public function offsetGetOutOfBoundsThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        $a = Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false);

        $this->assertInstanceOf(Vector::class, $a[10]);
    }

    #[Test]
    public function luNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false)->lu();
    }

    #[Test]
    public function choleskyNonSquareThrows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fromArray([
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ], false)->cholesky();
    }

    #[Test]
    public function eigReturnsEigen() : void
    {
        $a = Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false);

        $eig = $a->eig(false);

        $this->assertInstanceOf(Eigen::class, $eig);

        $eigenvalues = $eig->eigenvalues();

        $eigenvectors = $eig->eigenvectors()->asArray();

        $aa = $a->asArray();

        for ($j = 0; $j < 2; ++$j) {
            for ($i = 0; $i < 2; ++$i) {
                $sum = $aa[$i][0] * $eigenvectors[$j][0] + $aa[$i][1] * $eigenvectors[$j][1];

                $this->assertEqualsWithDelta($eigenvalues[$j] * $eigenvectors[$j][$i], $sum, 1e-8);
            }
        }
    }

    #[Test]
    public function eigSymmetricReturnsEigen() : void
    {
        $a = Matrix::fromArray([
            [9.0, 3.0],
            [3.0, 5.0],
        ], false);

        $eig = $a->eig(true);

        $this->assertInstanceOf(Eigen::class, $eig);

        $this->assertEqualsWithDelta([3.3944487241610, 10.605551275464], $eig->eigenvalues(), 1e-8);
    }

    #[Test]
    public function svdPurePHP() : void
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Extension tensor is loaded.');
        }

        $matrix = Matrix::fromArray([
            [1.0, 2.0],
            [3.0, 4.0],
        ], false);

        $svd = $matrix->svd();

        $reconstructed = $svd->u()
            ->matmul($svd->s())
            ->matmul($svd->vT());

        $this->assertEqualsWithDelta($matrix, $reconstructed, self::MAX_DELTA);
    }

    #[Test]
    public function pseudoinversePurePHP() : void
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Extension tensor is loaded.');
        }

        $a = Matrix::fromArray([
            [22, -17, 12],
            [4, 11, -2],
        ], false);

        $b = $a->pseudoinverse();

        $expected = Matrix::fromArray([
            [0.03147992432205172, 0.05583000490505223],
            [-0.009144418751313844, 0.07003713825239999],
            [0.01266554551187723, -0.0031357298016957483],
        ], false);

        $this->assertEqualsWithDelta($expected, $b, self::MAX_DELTA);
    }

    #[Test]
    public function pseudoinversePreservesTinySingularValues() : void
    {
        $a = Matrix::fromArray([
            [1.0, 0.0],
            [0.0, 1e-9],
        ], false);

        $expected = Matrix::fromArray([
            [1.0, 0.0],
            [0.0, 1.0 / 1e-9],
        ], false);

        $this->assertEqualsWithDelta($expected, $a->pseudoinverse(), self::MAX_DELTA);
    }

    #[Test]
    public function fromArrayThrowsOnMismatchedRows() : void
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::fromArray([[1.0, 2.0], [3.0]]);
    }

    #[Test]
    public function serializeRoundTrip() : void
    {
        $matrix = Matrix::fromArray([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]);

        $unserialised = unserialize(serialize($matrix));

        $this->assertInstanceOf(Matrix::class, $unserialised);
        $this->assertEquals($matrix->asArray(), $unserialised->asArray());
        $this->assertEquals($matrix->shape(), $unserialised->shape());
    }

    #[Test]
    public function serialisedShapeIsCompatibleWithTensorExt() : void
    {
        $matrix = Matrix::fromArray([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]);

        // Byte-compatible with the Tensor-Ext native serialisation: the rows
        // are emitted under a named "data" key (with "m"/"n") rather than a
        // nested "a" property.
        $this->assertSame(
            'O:13:"Tensor\\Matrix":3:{s:1:"a";a:2:{i:0;a:3:{i:0;d:1;i:1;d:2;i:2;d:3;}i:1;a:3:{i:0;d:4;i:1;d:5;i:2;d:6;}}s:1:"m";i:2;s:1:"n";i:3;}',
            serialize($matrix)
        );
    }

    #[Test]
    public function unserializeFromExtPayload() : void
    {
        // A payload produced identically by the Tensor-Ext polyfill.
        $payload = 'O:13:"Tensor\\Matrix":3:{s:1:"a";a:2:{i:0;a:3:{i:0;d:1;i:1;d:2;i:2;d:3;}i:1;a:3:{i:0;d:4;i:1;d:5;i:2;d:6;}}s:1:"m";i:2;s:1:"n";i:3;}';

        $matrix = unserialize($payload);

        $this->assertEquals([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]], $matrix->asArray());
        $this->assertEquals([2, 3], $matrix->shape());
    }
}
