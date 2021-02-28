<?php

namespace Tensor\Tests;

use Tensor\Tensor;
use Tensor\Vector;
use Tensor\Matrix;
use Tensor\ArrayLike;
use Tensor\Arithmetic;
use Tensor\Comparable;
use Tensor\Functional;
use Tensor\Statistical;
use Tensor\ColumnVector;
use Tensor\Trigonometric;
use Tensor\Reductions\REF;
use Tensor\Reductions\RREF;
use Tensor\Decompositions\LU;
use Tensor\Decompositions\Eigen;
use Tensor\Decompositions\Cholesky;
use PHPUnit\Framework\TestCase;

/**
 * @covers \Tensor\Matrix
 */
class MatrixTest extends TestCase
{
    /**
     * @var \Tensor\Matrix
     */
    protected $a;

    /**
     * @var \Tensor\Matrix
     */
    protected $b;

    /**
     * @var \Tensor\Matrix
     */
    protected $c;

    /**
     * @var \Tensor\Vector
     */
    protected $d;

    /**
     * @var \Tensor\ColumnVector
     */
    protected $e;

    /**
     * @before
     */
    public function setUp() : void
    {
        $this->a = Matrix::build([
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ]);

        $this->b = Matrix::quick([
            [13],
            [11],
            [9],
        ]);

        $this->c = Matrix::quick([
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ]);

        $this->d = Vector::quick([2, 10, -1]);

        $this->e = ColumnVector::quick([2.5, -1, 4.8]);
    }

    /**
     * @test
     */
    public function build() : void
    {
        $this->assertInstanceOf(Matrix::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Arithmetic::class, $this->a);
        $this->assertInstanceOf(Comparable::class, $this->a);
        $this->assertInstanceOf(Functional::class, $this->a);
        $this->assertInstanceOf(Trigonometric::class, $this->a);
        $this->assertInstanceOf(Statistical::class, $this->a);
        $this->assertInstanceOf(ArrayLike::class, $this->a);
    }

    /**
     * @test
     */
    public function stackRowVectors() : void
    {
        $z = Matrix::stack([
            $this->d,
            $this->d,
            $this->d,
        ]);

        $expected = [
            [2, 10, -1],
            [2, 10, -1],
            [2, 10, -1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function stackColumnVectors() : void
    {
        $z = Matrix::stack([
            $this->e,
            $this->e,
            $this->e,
        ]);

        $expected = [
            [2.5, 2.5, 2.5],
            [-1, -1, -1],
            [4.8, 4.8, 4.8],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function identity() : void
    {
        $z = Matrix::identity(4);

        $expected = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function zeros() : void
    {
        $z = Matrix::zeros(2, 4);

        $expected = [
            [0, 0, 0, 0],
            [0, 0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function ones() : void
    {
        $z = Matrix::ones(4, 2);

        $expected = [
            [1, 1],
            [1, 1],
            [1, 1],
            [1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function diagonal() : void
    {
        $z = Matrix::diagonal([0, 1, 4, 5]);

        $expected = [
            [0, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 4, 0],
            [0, 0, 0, 5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function fill() : void
    {
        $z = Matrix::fill(5, 4, 4);

        $expected = [
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function rand() : void
    {
        $z = Matrix::rand(4, 4);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(16, $z);
    }

    /**
     * @test
     */
    public function gaussian() : void
    {
        $z = Matrix::gaussian(3, 3);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(9, $z);
    }

    /**
     * @test
     */
    public function poisson() : void
    {
        $z = Matrix::poisson(6, 4, 2.);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(24, $z);
    }

    /**
     * @test
     */
    public function uniform() : void
    {
        $z = Matrix::uniform(3, 3);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(9, $z);
    }

    /**
     * @test
     */
    public function maximum() : void
    {
        $z = Matrix::maximum($this->a, $this->c);

        $expected = [
            [22, 6, 12],
            [4, 11, 5],
            [20, -1, 14],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function minumum() : void
    {
        $z = Matrix::minimum($this->a, $this->c);

        $expected = [
            [4, -17, -12],
            [1, 3, -2],
            [-10, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function shape() : void
    {
        $this->assertEquals([3, 3], $this->a->shape());
        $this->assertEquals([3, 1], $this->b->shape());
        $this->assertEquals([3, 3], $this->c->shape());
    }

    /**
     * @test
     */
    public function shapeString() : void
    {
        $this->assertEquals('3 x 3', $this->a->shapeString());
        $this->assertEquals('3 x 1', $this->b->shapeString());
        $this->assertEquals('3 x 3', $this->c->shapeString());
    }

    /**
     * @test
     */
    public function isSquare() : void
    {
        $this->assertTrue($this->a->isSquare());
        $this->assertFalse($this->b->isSquare());
        $this->assertTrue($this->c->isSquare());
    }

    /**
     * @test
     */
    public function size() : void
    {
        $this->assertEquals(9, $this->a->size());
        $this->assertEquals(3, $this->b->size());
        $this->assertEquals(9, $this->c->size());
    }

    /**
     * @test
     */
    public function m() : void
    {
        $this->assertEquals(3, $this->a->m());
        $this->assertEquals(3, $this->b->m());
        $this->assertEquals(3, $this->c->m());
    }

    /**
     * @test
     */
    public function n() : void
    {
        $this->assertEquals(3, $this->a->n());
        $this->assertEquals(1, $this->b->n());
        $this->assertEquals(3, $this->c->n());
    }

    /**
     * @test
     */
    public function row() : void
    {
        $this->assertEquals([22, -17, 12], $this->a->row(0));
        $this->assertEquals([11], $this->b->row(1));
        $this->assertEquals([-10, -1, 14], $this->c->row(2));
    }

    /**
     * @test
     */
    public function rowAsVector() : void
    {
        $z = $this->a->rowAsVector(1);

        $expected = [4, 11, -2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function column() : void
    {
        $this->assertEquals([-17, 11, -6], $this->a->column(1));
        $this->assertEquals([13, 11, 9], $this->b->column(0));
        $this->assertEquals([-12, 5, 14], $this->c->column(2));
    }

    /**
     * @test
     */
    public function columnAsVector() : void
    {
        $z = $this->a->columnAsVector(1);

        $expected = [-17, 11, -6];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function diagonalAsVector() : void
    {
        $z = $this->a->diagonalAsVector();

        $expected = [22, 11, -9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function asArray() : void
    {
        $z = $this->a->asArray();

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertEquals($expected, $z);
    }

    /**
     * @test
     */
    public function asVectors() : void
    {
        $vectors = $this->a->asVectors();

        $this->assertInstanceOf(Vector::class, $vectors[0]);
        $this->assertInstanceOf(Vector::class, $vectors[1]);
        $this->assertInstanceOf(Vector::class, $vectors[2]);

        $this->assertEquals([22, -17, 12], $vectors[0]->asArray());
        $this->assertEquals([4, 11, -2], $vectors[1]->asArray());
        $this->assertEquals([20, -6, -9], $vectors[2]->asArray());
    }

    /**
     * @test
     */
    public function asColumnVectors() : void
    {
        $vectors = $this->a->asColumnVectors();

        $this->assertInstanceOf(ColumnVector::class, $vectors[0]);
        $this->assertInstanceOf(ColumnVector::class, $vectors[1]);
        $this->assertInstanceOf(ColumnVector::class, $vectors[2]);

        $this->assertEquals([22, 4, 20], $vectors[0]->asArray());
        $this->assertEquals([-17, 11, -6], $vectors[1]->asArray());
        $this->assertEquals([12, -2, -9], $vectors[2]->asArray());
    }

    /**
     * @test
     */
    public function argmin() : void
    {
        $z = $this->a->argmin();

        $expected = [1, 2, 2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function argmax() : void
    {
        $z = $this->a->argmax();

        $expected = [0, 1, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function flatten() : void
    {
        $z = $this->a->flatten();

        $expected = [22, -17, 12, 4, 11, -2, 20, -6, -9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function transpose() : void
    {
        $z = $this->a->transpose();

        $expected = [
            [22, 4, 20],
            [-17, 11, -6],
            [12, -2, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function inverse() : void
    {
        $z = $this->a->inverse();

        $expected = [
            [0.02093549603923048, 0.042436816295737464, 0.018483591097698978],
            [0.0007544322897019996, 0.08261033572236892, -0.017351942663145988],
            [0.04602036967182196, 0.03923047906450396, -0.05846850245190495],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function pseudoinverse() : void
    {
        $a = Matrix::build([
            [22, -17, 12],
            [4, 11, -2],
        ]);

        $z = $a->pseudoinverse();

        $expected = [
            [0.03147992432205172, 0.05583000490505223],
            [-0.009144418751313844, 0.0700371382524],
            [0.012665545511877228, -0.00313572980169575],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function det() : void
    {
        $this->assertEquals(-5301.999999999999, $this->a->det());
        $this->assertEquals(-544.0, $this->c->det());
    }

    /**
     * @test
     */
    public function symmetric() : void
    {
        $a = Matrix::quick([
            [1, 5, 2],
            [5, 1, 3],
            [2, 3, 1],
        ]);

        $this->assertTrue($a->symmetric());

        $this->assertFalse($this->a->symmetric());
    }

    /**
     * @test
     */
    public function positiveDefinite() : void
    {
        $a = Matrix::quick([
            [1, 5, 2],
            [5, 1, 3],
            [2, 3, 1],
        ]);

        $this->assertFalse($a->positiveDefinite());
    }

    /**
     * @test
     */
    public function positiveSemidefinite() : void
    {
        $a = Matrix::quick([
            [1, 5, 2],
            [5, 1, 3],
            [2, 3, 1],
        ]);

        $this->assertFalse($a->positiveSemidefinite());
    }

    /**
     * @test
     */
    public function rank() : void
    {
        $this->assertEquals(3, $this->a->rank());
        $this->assertEquals(3, $this->c->rank());
    }

    /**
     * @test
     */
    public function fullRank() : void
    {
        $this->assertTrue($this->a->fullRank());
        $this->assertTrue($this->c->fullRank());
    }

    /**
     * @test
     */
    public function reciprocal() : void
    {
        $z = $this->a->reciprocal();

        $expected = [
            [0.045454545454545456, -0.058823529411764705, 0.08333333333333333],
            [0.25, 0.09090909090909091, -0.5],
            [0.05, -0.16666666666666666, -0.1111111111111111],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function map() : void
    {
        $z = $this->a->map(function ($value) {
            return $value > 0. ? 1 : -1;
        });

        $expected = [
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function reduce() : void
    {
        $z = $this->a->reduce(function ($value, $carry) {
            return $carry + ($value / 2.0);
        });

        $this->assertEquals(17.5, $z);
    }

    /**
     * @test
     */
    public function ref() : void
    {
        $ref = $this->a->ref();

        $this->assertInstanceOf(REF::class, $ref);

        $expected = [
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ];

        $this->assertInstanceOf(Matrix::class, $ref->a());
        $this->assertEqualsWithDelta($expected, $ref->a()->asArray(), 1e-4);

        $this->assertEquals(0, $ref->swaps());
    }

    /**
     * @test
     */
    public function rref() : void
    {
        $rref = $this->a->rref();

        $this->assertInstanceOf(RREF::class, $rref);

        $expected = [
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $rref->a());
        $this->assertEqualsWithDelta($expected, $rref->a()->asArray(), 1e-4);
    }

    /**
     * @test
     */
    public function lu() : void
    {
        $lu = $this->a->lu();

        $this->assertInstanceOf(LU::class, $lu);

        $lHat = [
            [1.0, 0, 0],
            [0.18181818181818182, 1.0, 0],
            [0.9090909090909091, 0.6709677419354838, 1.0],
        ];

        $uHat = [
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ];

        $this->assertInstanceOf(Matrix::class, $lu->l());
        $this->assertInstanceOf(Matrix::class, $lu->u());

        $this->assertCount(9, $lu->l());
        $this->assertCount(9, $lu->u());

        $this->assertEquals($lHat, $lu->l()->asArray());
        $this->assertEquals($uHat, $lu->u()->asArray());
    }

    /**
     * @test
     */
    public function cholesky() : void
    {
        $a = Matrix::quick([
            [2, -1, 0],
            [-1, 2, -1],
            [0, -1, 2],
        ]);

        $cholesky = $a->cholesky();

        $this->assertInstanceOf(Cholesky::class, $cholesky);

        $expected = [
            [1.4142135623730951, 0, 0],
            [-0.7071067811865475, 1.224744871391589, 0],
            [0, -0.8164965809277261, 1.1547005383792515],
        ];

        $this->assertInstanceOf(Matrix::class, $cholesky->l());
        $this->assertCount(9, $cholesky->l());
        $this->assertEquals($expected, $cholesky->l()->asArray());
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function eig() : void
    {
        $eig = $this->a->eig(false);

        $this->assertInstanceOf(Eigen::class, $eig);

        $values = [-15.096331148319537, 25.108706520450326, 13.9876246278692];

        $vectors = [
            [0.25848694820886425, -0.11314537870318066, -0.9593657388523845],
            [-0.8622719261400653, -0.17721179605718698, -0.47442924101375483],
            [-0.6684472200177011, -0.6126879076802705, -0.42165369894378907],
        ];

        $this->assertInstanceOf(Matrix::class, $eig->eigenvectors());

        $eigenvalues = $eig->eigenvalues();

        $this->assertEqualsWithDelta($values, $eigenvalues, 1e-12);
        $this->assertEquals($vectors, $eig->eigenvectors()->asArray());
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function eigSymmetric() : void
    {
        $eig = $this->a->matmul($this->a)->eig(true);

        $this->assertInstanceOf(Eigen::class, $eig);

        $values = [-366.30071669298195, 335.92000012383926, 1084.3807165691428];

        $vectors = [
            [0.5423765325213931, 0.8162941265260665, -0.19872492538460218],
            [-0.046672925777410314, 0.26544998308386847, 0.9629942598375911],
            [-0.8388380862654284, 0.5130304137961217, -0.1820726765627782],
        ];

        $this->assertInstanceOf(Matrix::class, $eig->eigenvectors());

        $eigenvalues = $eig->eigenvalues();

        $this->assertEqualsWithDelta($values, $eigenvalues, 1e-12);
        $this->assertEquals($vectors, $eig->eigenvectors()->asArray());
    }

    /**
     * @test
     * @requires extension tensor
     */
    public function svd() : void
    {
        $svd = $this->a->svd();

        $uHat = [
            [-0.8436018806559158, 0.4252547343454771, -0.3278631999333884],
            [0.08179499775610413, -0.5016868397437385, -0.8611735557772425],
            [-0.5307027843302525, -0.7533052009276842, 0.38844025146657923],
        ];

        $singularValues = [
            34.66917512262571, 17.12630582468919, 8.929610580306822,
        ];

        $vtHat = [
            [-0.8320393250771425, 0.531457514846513, -0.15894486917903863],
            [-0.4506078135544562, -0.48043370238236727, 0.7524201326246152],
            [-0.3235168618307952, -0.6976649392999047, -0.6392186422366096],
        ];

        $this->assertInstanceOf(Matrix::class, $svd->u());
        $this->assertInstanceOf(Matrix::class, $svd->vT());

        $this->assertEquals($uHat, $svd->u()->asArray());
        $this->assertEquals($singularValues, $svd->singularValues());
        $this->assertEquals($vtHat, $svd->vT()->asArray());
    }

    /**
     * @test
     */
    public function solve() : void
    {
        $z = $this->a->solve($this->d);

        $expected = [
            3.5542559833507, -2.071342351717, -9.2838709677419,
        ];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function matmul() : void
    {
        $z = $this->a->matmul($this->b);

        $expected = [
            [207], [155], [113],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());

        $z = $this->a->matmul($this->c);

        $expected = [
            [-49.0, 69.0, -181.0],
            [47.0, 59.0, -21.0],
            [164.0, 111.0, -396.0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function convolve() : void
    {
        $input = Matrix::quick([
            [3, 27, 66, 29, 42, 5],
            [5, 9, 15, 42, 45, 16],
            [1, 5, 10, 22, 66, 5],
            [0, 1, 4, 9, 10, 22, 2],
            [0, 0, 3, 19, 21, 25],
            [0, 0, 0, 5, 2, 33, 35],
        ]);

        $kernel = Matrix::quick([
            [0, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
        ]);

        $z = $input->convolve($kernel, 1);

        $expected = [
            [3, 32, 75, 44, 84, 50],
            [32, 76, 49, 94, 72, 82],
            [10, 20, 53, 71, 91, 15],
            [5, 11, 26, 78, 34, 43],
            [1, 4, 12, 29, 48, 27],
            [0, 3, 19, 26, 27, 33],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyMatrix() : void
    {
        $z = $this->a->multiply($this->c);

        $expected = [
            [88, -102, -144],
            [4, 33, -10],
            [-200, 6, -126],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideMatrix() : void
    {
        $z = $this->a->divide($this->c);

        $expected = [
            [5.5, -2.8333333333333335, -1],
            [4, 3.6666666666666665, -0.4],
            [-2, 6, -0.6428571428571429],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addMatrix() : void
    {
        $z = $this->a->add($this->c);

        $expected = [
            [26, -11, 0],
            [5, 14, 3],
            [10, -7, 5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractMatrix() : void
    {
        $z = $this->a->subtract($this->c);

        $expected = [
            [18, -23, 24],
            [3, 8, -7],
            [30, -5, -23],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function powMatrix() : void
    {
        $z = $this->a->pow($this->c);

        $expected = [
            [234256, 24137569, 1.1215665478461509E-13],
            [4, 1331, -32],
            [9.765625E-14, -0.16666666666666666, 22876792454961],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function modMatrix() : void
    {
        $z = $this->a->mod($this->c);

        $expected = [
            [2, -5, 0],
            [0, 2, -2],
            [0, 0, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalMatrix() : void
    {
        $z = $this->a->equal($this->c);

        $expected = [
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualMatrix() : void
    {
        $z = $this->a->notEqual($this->c);

        $expected = [
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterMatrix() : void
    {
        $z = $this->a->greater($this->c);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualMatrix() : void
    {
        $z = $this->a->greaterEqual($this->c);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessMatrix() : void
    {
        $z = $this->a->less($this->c);

        $expected = [
            [0, 1, 0],
            [0, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualMatrix() : void
    {
        $z = $this->a->lessEqual($this->c);

        $expected = [
            [0, 1, 0],
            [0, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function dotVector() : void
    {
        $z = $this->a->dot($this->d);

        $expected = [-138, 120, -11];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyVector() : void
    {
        $z = $this->a->multiply($this->d);

        $expected = [
            [44, -170, -12],
            [8, 110, 2],
            [40, -60, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideVector() : void
    {
        $z = $this->a->divide($this->d);

        $expected = [
            [11, -1.7, -12],
            [2, 1.1, 2],
            [10, -0.6, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addVector() : void
    {
        $z = $this->a->add($this->d);

        $expected = [
            [24, -7, 11],
            [6, 21, -3],
            [22, 4, -10],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractVector() : void
    {
        $z = $this->a->subtract($this->d);

        $expected = [
            [20, -27, 13],
            [2, 1, -1],
            [18, -16, -8],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function powVector() : void
    {
        $z = $this->a->pow($this->d);

        $expected = [
            [484, 2015993900449, 0.08333333333333333],
            [16, 25937424601, -0.5],
            [400, 60466176, -0.1111111111111111],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function modVector() : void
    {
        $z = $this->a->mod($this->d);

        $expected = [
            [0, -7, 0],
            [0, 1, 0],
            [0, -6, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalVector() : void
    {
        $z = $this->a->equal($this->d);

        $expected = [
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualVector() : void
    {
        $z = $this->a->notEqual($this->d);

        $expected = [
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterVector() : void
    {
        $z = $this->a->greater($this->d);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualVector() : void
    {
        $z = $this->a->greaterEqual($this->d);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessVector() : void
    {
        $z = $this->a->less($this->d);

        $expected = [
            [0, 1, 0],
            [0, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualVector() : void
    {
        $z = $this->a->less($this->d);

        $expected = [
            [0, 1, 0],
            [0, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyColumnVector() : void
    {
        $z = $this->a->multiply($this->e);

        $expected = [
            [55.0, -42.5, 30.],
            [-4, -11, 2],
            [96.0, -28.799999999999997, -43.199999999999996],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideColumnVector() : void
    {
        $z = $this->a->divide($this->e);

        $expected = [
            [8.8, -6.8, 4.8],
            [-4, -11, 2],
            [4.166666666666667, -1.25, -1.875],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addColumnVector() : void
    {
        $z = $this->a->add($this->e);

        $expected = [
            [24.5, -14.5, 14.5],
            [3, 10, -3],
            [24.8, -1.2000000000000002, -4.2],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractColumnVector() : void
    {
        $z = $this->a->subtract($this->e);

        $expected = [
            [19.5, -19.5, 9.5],
            [5, 12, -1],
            [15.2, -10.8, -13.8],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function modColumnVector() : void
    {
        $z = $this->a->mod($this->e);

        $expected = [
            [0,  -1,  0],
            [0, 0, 0],
            [0,  -2,  -1]
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalColumnVector() : void
    {
        $z = $this->a->equal($this->e);

        $expected = [
            [0, 0, 0],
            [0, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualColumnVector() : void
    {
        $z = $this->a->notEqual($this->e);

        $expected = [
            [1, 1, 1],
            [1, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterColumnVector() : void
    {
        $z = $this->a->greater($this->e);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualColumnVector() : void
    {
        $z = $this->a->greaterEqual($this->e);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessColumnVector() : void
    {
        $z = $this->a->less($this->e);

        $expected = [
            [0, 1, 0],
            [0, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualColumnVector() : void
    {
        $z = $this->a->lessEqual($this->e);

        $expected = [
            [0, 1, 0],
            [0, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function multiplyScalar() : void
    {
        $z = $this->a->multiply(2.5);

        $expected = [
            [55, -42.5, 30],
            [10.0, 27.5, -5.],
            [50, -15, -22.5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function divideScalar() : void
    {
        $z = $this->a->divide(2.);

        $expected = [
            [11.0, -8.5, 6.],
            [2.0, 5.5, -1.],
            [10.0, -3.0, -4.5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function addScalar() : void
    {
        $z = $this->a->add(1);

        $expected = [
            [23, -16, 13],
            [5, 12, -1],
            [21, -5, -8],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subtractScalar() : void
    {
        $z = $this->a->subtract(10);

        $expected = [
            [12, -27, 2],
            [-6, 1, -12],
            [10, -16, -19],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function powScalar() : void
    {
        $z = $this->a->pow(3);

        $expected = [
            [10648, -4913, 1728],
            [64, 1331, -8],
            [8000, -216, -729],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function modScalar() : void
    {
        $z = $this->a->mod(10);

        $expected = [
            [2, -7, 2],
            [4, 1, -2],
            [0, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function equalScalar() : void
    {
        $z = $this->a->equal(4);

        $expected = [
            [0, 0, 0],
            [1, 0, 0],
            [0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function notEqualScalar() : void
    {
        $z = $this->a->notEqual(4);

        $expected = [
            [1, 1, 1],
            [0, 1, 1],
            [1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterScalar() : void
    {
        $z = $this->a->greater(4);

        $expected = [
            [1, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function greaterEqualScalar() : void
    {
        $z = $this->a->greaterEqual(4);

        $expected = [
            [1, 0, 1],
            [1, 1, 0],
            [1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessScalar() : void
    {
        $z = $this->a->less(10);

        $expected = [
            [0, 1, 0],
            [1, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function lessEqualScalar() : void
    {
        $z = $this->a->lessEqual(10);

        $expected = [
            [0, 1, 0],
            [1, 0, 1],
            [0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function abs() : void
    {
        $z = $this->a->abs();

        $expected = [
            [22, 17, 12],
            [4, 11, 2],
            [20, 6, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function square() : void
    {
        $z = $this->a->square();

        $expected = [
            [484, 289, 144],
            [16, 121, 4],
            [400, 36, 81],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sqrt() : void
    {
        $z = $this->b->sqrt();

        $expected = [
            [3.605551275463989],
            [3.3166247903554],
            [3],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function exp() : void
    {
        $z = $this->b->exp();

        $expected = [
            [442413.3920089205],
            [59874.14171519778],
            [8103.08392757538],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function expm1() : void
    {
        $z = $this->b->expm1();

        $expected = [
            [442412.3920089205],
            [59873.14171519782],
            [8102.083927575384],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function log() : void
    {
        $z = $this->b->log();

        $expected = [
            [2.5649493574615367],
            [2.3978952727983707],
            [2.1972245773362196],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function log1p() : void
    {
        $z = $this->b->log1p();

        $expected = [
            [2.6390573296152584],
            [2.4849066497880004],
            [2.302585092994046],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sin() : void
    {
        $z = $this->b->sin();

        $expected = [
            [0.4201670368266409],
            [-0.9999902065507035],
            [0.4121184852417566],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function asin() : void
    {
        $z = Matrix::quick([
            [0.32],
            [-0.5],
            [0.01],
        ])->asin();

        $expected = [
            [0.3257294872946302],
            [-0.5235987755982989],
            [0.010000166674167114],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function cos() : void
    {
        $z = $this->b->cos();

        $expected = [
            [0.9074467814501962],
            [0.004425697988050785],
            [-0.9111302618846769],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function acos() : void
    {
        $z = Matrix::quick([
            [0.32],
            [-0.5],
            [0.01],
        ])->acos();

        $expected = [
            [1.2450668395002664],
            [2.0943951023931957],
            [1.5607961601207294],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function tan() : void
    {
        $z = $this->b->tan();

        $expected = [
            [0.4630211329364896],
            [-225.95084645419513],
            [-0.45231565944180985],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function atan() : void
    {
        $z = $this->b->atan();

        $expected = [
            [1.4940244355251187],
            [1.4801364395941514],
            [1.460139105621001],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function rad2deg() : void
    {
        $z = $this->b->rad2deg();

        $expected = [
            [744.8451336700701],
            [630.2535746439056],
            [515.6620156177408],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function deg2rad() : void
    {
        $z = $this->b->deg2rad();

        $expected = [
            [0.22689280275926282],
            [0.19198621771937624],
            [0.15707963267948966],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sum() : void
    {
        $z = $this->a->sum();

        $expected = [17, 13, 5];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function product() : void
    {
        $z = $this->a->product();

        $expected = [-4488.0, -88.0, 1080.];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function min() : void
    {
        $z = $this->a->min();

        $expected = [-17, -2, -9];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function max() : void
    {
        $z = $this->a->max();

        $expected = [22, 11, 20];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function mean() : void
    {
        $z = $this->a->mean();

        $expected = [5.666666666666667, 4.333333333333333, 1.6666666666666667];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function median() : void
    {
        $z = $this->a->median();

        $expected = [12, 4, -6];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function quantile() : void
    {
        $z = $this->a->quantile(0.4);

        $expected = [6.200000000000003, 2.8000000000000007, -6.6];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function variance() : void
    {
        $z = $this->a->variance();

        $expected = [273.55555555555554, 28.222222222222225, 169.55555555555554];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function covariance() : void
    {
        $z = $this->a->covariance();

        $expected = [
            [273.55555555555554, -65.55555555555556, 135.2222222222222],
            [-65.55555555555556, 28.222222222222225, 3.4444444444444406],
            [135.2222222222222, 3.4444444444444406, 169.55555555555554],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function round() : void
    {
        $z = $this->a->round(2);

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function floor() : void
    {
        $z = $this->a->floor();

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function ceil() : void
    {
        $z = $this->a->ceil();

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function l1Norm() : void
    {
        $this->assertEquals(46.0, $this->a->l1Norm());
        $this->assertEquals(33.0, $this->b->l1Norm());
        $this->assertEquals(31.0, $this->c->l1Norm());
    }

    /**
     * @test
     */
    public function l2Norm() : void
    {
        $this->assertEquals(39.68626966596886, $this->a->l2Norm());
        $this->assertEquals(19.261360284258224, $this->b->l2Norm());
        $this->assertEquals(22.978250586152114, $this->c->l2Norm());
    }

    /**
     * @test
     */
    public function infinityNorm() : void
    {
        $this->assertEquals(51.0, $this->a->infinityNorm());
        $this->assertEquals(13.0, $this->b->infinityNorm());
        $this->assertEquals(25.0, $this->c->infinityNorm());
    }

    /**
     * @test
     */
    public function maxNorm() : void
    {
        $this->assertEquals(22.0, $this->a->maxNorm());
        $this->assertEquals(13.0, $this->b->maxNorm());
        $this->assertEquals(14.0, $this->c->maxNorm());
    }

    /**
     * @test
     */
    public function clip() : void
    {
        $z = $this->a->clip(0.0, INF);

        $expected = [
            [22, 0.0, 12],
            [4, 11, 0.],
            [20, 0.0, 0.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function clipLower() : void
    {
        $z = $this->a->clipLower(5.);

        $expected = [
            [22, 5.0, 12],
            [5.0, 11, 5.],
            [20, 5.0, 5.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function clipUpper() : void
    {
        $z = $this->a->clipUpper(16.);

        $expected = [
            [16.0, -17.0, 12],
            [4, 11, -2.],
            [16, -6.0, -9.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function sign() : void
    {
        $z = $this->a->sign();

        $expected = [
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function negate() : void
    {
        $z = $this->a->negate();

        $expected = [
            [-22, 17, -12],
            [-4, -11, 2],
            [-20, 6, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function insert() : void
    {
        $z = $this->a->insert(Matrix::quick([
            [6, 9],
            [6, 9],
        ]), 1, 0);

        $expected = [
            [22, -17, 12],
            [6, 9, -2],
            [6, 9, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function subMatrix() : void
    {
        $z = $this->a->subMatrix(1, 1, 3, 3);

        $expected = [
            [11, -2],
            [-6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function augmentAbove() : void
    {
        $z = $this->a->augmentAbove($this->c);

        $expected = [
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function augmentBelow() : void
    {
        $z = $this->a->augmentBelow($this->c);

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function augmentLeft() : void
    {
        $z = $this->a->augmentLeft($this->b);

        $expected = [
            [13, 22, -17, 12],
            [11, 4, 11, -2],
            [9, 20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function augmentRight() : void
    {
        $z = $this->a->augmentRight($this->b);

        $expected = [
            [22, -17, 12, 13],
            [4, 11, -2, 11],
            [20, -6, -9, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function repeat() : void
    {
        $z = $this->b->repeat(1, 3);

        $expected = [
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    /**
     * @test
     */
    public function testToString() : void
    {
        $outcome = PHP_EOL
            . '[ 22 -17 12 ]' . PHP_EOL
            . '[ 4 11 -2 ]' . PHP_EOL
            . '[ 20 -6 -9 ]' . PHP_EOL;

        $this->assertEquals($outcome, (string) $this->a);
    }
}
