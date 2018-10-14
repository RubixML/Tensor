<?php

namespace Rubix\Tensor\Tests;

use Rubix\Tensor\Tensor;
use Rubix\Tensor\Vector;
use Rubix\Tensor\Matrix;
use PHPUnit\Framework\TestCase;
use InvalidArgumentException;
use IteratorAggregate;
use ArrayAccess;
use Countable;

class MatrixTest extends TestCase
{
    protected $a;

    protected $b;

    protected $c;

    protected $d;

    public function setUp()
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
    }

    public function test_build_matrix()
    {
        $this->assertInstanceOf(Matrix::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Countable::class, $this->a);
        $this->assertInstanceOf(IteratorAggregate::class, $this->a);
        $this->assertInstanceOf(ArrayAccess::class, $this->a);
    }

    public function test_from_vectors()
    {
        $z = Matrix::fromVectors([
            $this->d,
            $this->d,
            $this->d,
        ]);

        $outcome = [
            [2, 10, -1],
            [2, 10, -1],
            [2, 10, -1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($outcome, $z->asArray());
    }

    public function test_build_identity()
    {
        $z = Matrix::identity(4);

        $y = [
            [1, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 1, 0],
            [0, 0, 0, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_zeros()
    {
        $z = Matrix::zeros(2, 4);

        $y = [
            [0, 0, 0, 0],
            [0, 0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_ones()
    {
        $z = Matrix::ones(4, 2);

        $y = [
            [1, 1],
            [1, 1],
            [1, 1],
            [1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_diagonal()
    {
        $z = Matrix::diagonal([0, 1, 4, 5]);

        $y = [
            [0, 0, 0, 0],
            [0, 1, 0, 0],
            [0, 0, 4, 0],
            [0, 0, 0, 5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_fill()
    {
        $z = Matrix::fill(5, 4, 4);

        $y = [
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
            [5, 5, 5, 5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_rand()
    {
        $z = Matrix::rand(4, 4);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(16, $z);
    }

    public function test_build_gaussian()
    {
        $z = Matrix::gaussian(3, 3);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(9, $z);
    }

    public function test_build_uniform()
    {
        $z = Matrix::uniform(3, 3);

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertCount(9, $z);
    }

    public function test_maximum()
    {
        $z = Matrix::maximum($this->a, $this->c);

        $y = [
            [22, 6, 12],
            [4, 11, 5],
            [20, -1, 14],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_minumum()
    {
        $z = Matrix::minimum($this->a, $this->c);

        $y = [
            [4,-17, -12],
            [1, 3, -2],
            [-10, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_shape()
    {
        $this->assertEquals([3, 3], $this->a->shape());
        $this->assertEquals([3, 1], $this->b->shape());
        $this->assertEquals([3, 3], $this->c->shape());
    }

    public function test_size()
    {
        $this->assertEquals(9, $this->a->size());
        $this->assertEquals(3, $this->b->size());
        $this->assertEquals(9, $this->c->size());
    }

    public function test_get_m()
    {
        $this->assertEquals(3, $this->a->m());
        $this->assertEquals(3, $this->b->m());
        $this->assertEquals(3, $this->c->m());
    }

    public function test_get_n()
    {
        $this->assertEquals(3, $this->a->n());
        $this->assertEquals(1, $this->b->n());
        $this->assertEquals(3, $this->c->n());
    }

    public function test_get_row()
    {
        $this->assertEquals([22, -17, 12], $this->a->row(0));
        $this->assertEquals([11], $this->b->row(1));
        $this->assertEquals([-10, -1, 14], $this->c->row(2));
    }

    public function test_row_as_vector()
    {
        $z = $this->a->rowAsVector(1);

        $y = [4, 11, -2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_get_column()
    {
        $this->assertEquals([-17, 11, -6], $this->a->column(1));
        $this->assertEquals([13, 11, 9], $this->b->column(0));
        $this->assertEquals([-12, 5, 14], $this->c->column(2));
    }

    public function test_column_as_vector()
    {
        $z = $this->a->columnAsVector(1);

        $y = [-17, 11, -6];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_as_array()
    {
        $z = $this->a->asArray();

        $y = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertEquals($y, $z);
    }

    public function test_as_vectors()
    {
        $vectors = $this->a->asVectors();

        $this->assertInstanceOf(Vector::class, $vectors[0]);
        $this->assertInstanceOf(Vector::class, $vectors[1]);
        $this->assertInstanceOf(Vector::class, $vectors[2]);

        $this->assertEquals([22, -17, 12], $vectors[0]->asArray());
        $this->assertEquals([4, 11, -2], $vectors[1]->asArray());
        $this->assertEquals([20, -6, -9], $vectors[2]->asArray());
    }

    public function test_argmin()
    {
        $z = $this->a->argmin();

        $y = [1, 2, 2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_argmax()
    {
        $z = $this->a->argmax();

        $y = [0, 1, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_flatten()
    {
        $z = $this->a->flatten();

        $y = [22, -17, 12, 4, 11, -2, 20, -6, -9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_transpose()
    {
        $z = $this->a->transpose();

        $y = [
            [22, 4, 20],
            [-17, 11, -6],
            [12, -2, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_inverse()
    {
        $z = $this->a->inverse();

        $y = [
            [0.02093549603923048, 0.042436816295737464, 0.018483591097698978],
            [0.0007544322897019996, 0.08261033572236892, -0.017351942663145988],
            [0.04602036967182196, 0.03923047906450396, -0.05846850245190495],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_reciprocal()
    {
        $z = $this->a->reciprocal();

        $y = [
            [0.045454545454545456, -0.058823529411764705, 0.08333333333333333],
            [0.25, 0.09090909090909091, -0.5],
            [0.05, -0.16666666666666666, -0.1111111111111111],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_map()
    {
        $z = $this->a->map(function ($value) {
            return $value > 0. ? 1 : -1;
        });

        $y = [
            [1, -1, 1],
            [1, 1, -1],
            [1, -1, -1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_reduce()
    {
        $z = $this->a->reduce(function ($value, $carry) {
            return $carry + ($value / 2.);
        });

        $this->assertEquals(17.5, $z);
    }

    public function test_ref()
    {
        $z =  $this->a->ref();

        $y = [
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_rref()
    {
        $z = $this->a->rref();

        $y = [
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_matmul()
    {
        $z = $this->a->matmul($this->b);

        $y = [
            [207], [155], [113],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_multiply_matrix()
    {
        $z = $this->a->multiply($this->c);

        $y = [
            [88, -102, -144],
            [4, 33, -10],
            [-200, 6, -126],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_matrix()
    {
        $z = $this->a->divide($this->c);

        $y = [
            [5.5, -2.8333333333333335, -1],
            [4, 3.6666666666666665, -0.4],
            [-2, 6, -0.6428571428571429],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_matrix()
    {
        $z = $this->a->add($this->c);

        $y = [
            [26, -11, 0],
            [5, 14, 3],
            [10, -7, 5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_matrix()
    {
        $z = $this->a->subtract($this->c);

        $y = [
            [18, -23, 24],
            [3, 8, -7],
            [30, -5, -23],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow_matrix()
    {
        $z = $this->a->pow($this->c);

        $y = [
            [234256, 24137569, 1.1215665478461509E-13],
            [4, 1331, -32],
            [9.765625E-14, -0.16666666666666666, 22876792454961],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_mod_matrix()
    {
        $z = $this->a->mod($this->c);

        $y = [
            [2, -5, 0],
            [0, 2, -2],
            [0, 0, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_dot_vector()
    {
        $z = $this->a->dot($this->d);

        $y = [
            [-138],
            [120],
            [-11],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_multiply_vector()
    {
        $z = $this->a->multiply($this->d);

        $y = [
            [44, -170, -12],
            [8, 110, 2],
            [40, -60, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_vector()
    {
        $z = $this->a->divide($this->d);

        $y = [
            [11, -1.7, -12],
            [2, 1.1, 2],
            [10, -0.6, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_vector()
    {
        $z = $this->a->add($this->d);

        $y = [
            [24, -7, 11],
            [6, 21, -3],
            [22, 4, -10],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_vector()
    {
        $z = $this->a->subtract($this->d);

        $y = [
            [20, -27, 13],
            [2, 1, -1],
            [18, -16, -8],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow_vector()
    {
        $z = $this->a->pow($this->d);

        $y = [
            [484, 2015993900449, 0.08333333333333333],
            [16, 25937424601, -0.5],
            [400, 60466176, -0.1111111111111111],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_mod_vector()
    {
        $z = $this->a->mod($this->d);

        $y = [
            [0, -7, 0],
            [0, 1, 0],
            [0, -6, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_multiply_scalar()
    {
        $z = $this->a->multiply(2.5);

        $y = [
            [55, -42.5, 30],
            [10., 27.5, -5.],
            [50, -15, -22.5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_scalar()
    {
        $z = $this->a->divide(2.);

        $y = [
            [11., -8.5, 6.],
            [2., 5.5, -1.],
            [10., -3., -4.5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_scalar()
    {
        $z = $this->a->add(1);

        $y = [
            [23, -16, 13],
            [5, 12, -1],
            [21, -5, -8],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_scalar()
    {
        $z = $this->a->subtract(10);

        $y = [
            [12, -27, 2],
            [-6, 1, -12],
            [10, -16, -19],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow_scalar()
    {
        $z = $this->a->pow(3);

        $y = [
            [10648, -4913, 1728],
            [64, 1331, -8],
            [8000, -216, -729],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_mod_scalar()
    {
        $z = $this->a->mod(10);

        $y = [
            [2, -7, 2],
            [4, 1, -2],
            [0, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_abs()
    {
        $z = $this->a->abs();

        $y = [
            [22, 17, 12],
            [4, 11, 2],
            [20, 6, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_square()
    {
        $z = $this->a->square();

        $y = [
            [484, 289, 144],
            [16, 121, 4],
            [400, 36, 81],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_square_root()
    {
        $z = $this->b->sqrt();

        $y = [
            [3.605551275463989],
            [3.3166247903554],
            [3],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_exp()
    {
        $z = $this->b->exp();

        $y = [
            [442413.3920089205],
            [59874.14171519778],
            [8103.08392757538],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_log()
    {
        $z = $this->b->log();

        $y = [
            [2.5649493574615367],
            [2.3978952727983707],
            [2.1972245773362196],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_sin()
    {
        $z = $this->b->sin();
        
        $y = [
            [0.4201670368266409],
            [-0.9999902065507035],
            [0.4121184852417566],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_cos()
    {
        $z = $this->b->cos();

        $y = [
            [0.9074467814501962],
            [0.004425697988050785],
            [-0.9111302618846769],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_tan()
    {
        $z = $this->b->tan();

        $y = [
            [0.4630211329364896],
            [-225.95084645419513],
            [-0.45231565944180985],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_degrees()
    {
        $z = $this->b->degrees();

        $y = [
            [744.8451336700701],
            [630.2535746439056],
            [515.6620156177408],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_radians()
    {
        $z = $this->b->radians();

        $y = [
            [0.22689280275926282],
            [0.19198621771937624],
            [0.15707963267948966],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_sum()
    {
        $z = $this->a->sum();

        $y = [17, 13, 5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_product()
    {
        $z = $this->a->product();

        $y = [-4488., -88., 1080.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_min()
    {
        $z = $this->a->min();

        $y = [-17, -2, -9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_max()
    {
        $z = $this->a->max();

        $y = [22, 11, 20];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_mean()
    {
        $z = $this->a->mean();

        $y = [5.666666666666667, 4.333333333333333, 1.6666666666666667];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_median()
    {
        $z =$this->a->median();

        $y = [12, 4, -6];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_variance()
    {
        $z = $this->a->variance();

        $y = [828.6666666666666, 60.66666666666667, 425.99999999999994];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_covariance()
    {
        $z = $this->a->covariance();

        $y = [
            [116.51851851851852, -99.25925925925925, -17.259259259259263],
            [-99.25925925925925, 119.62962962962963, -20.370370370370367],
            [-17.259259259259263, -20.370370370370367, 37.62962962962963],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_round()
    {
        $z = $this->a->round(2);

        $y = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_floor()
    {
        $z = $this->a->floor();

        $y = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_ceil()
    {
        $z = $this->a->ceil();

        $y = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_l1_norm()
    {
        $this->assertEquals(46., $this->a->l1Norm());
        $this->assertEquals(33., $this->b->l1Norm());
        $this->assertEquals(31., $this->c->l1Norm());
    }

    public function test_l2_norm()
    {
        $this->assertEquals(39.68626966596886, $this->a->l2Norm());
        $this->assertEquals(19.261360284258224, $this->b->l2Norm());
        $this->assertEquals(22.978250586152114, $this->c->l2Norm());
    }

    public function test_infinity_norm()
    {
        $this->assertEquals(51.0, $this->a->infinityNorm());
        $this->assertEquals(13.0, $this->b->infinityNorm());
        $this->assertEquals(25.0, $this->c->infinityNorm());
    }

    public function test_max_norm()
    {
        $this->assertEquals(22.0, $this->a->maxNorm());
        $this->assertEquals(13.0, $this->b->maxNorm());
        $this->assertEquals(14.0, $this->c->maxNorm());
    }

    public function test_clip()
    {
        $z = $this->a->clip(0., INF);

        $y = [
            [22, 0., 12],
            [4, 11, 0.],
            [20, 0., 0.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_negate()
    {
        $z = $this->a->negate();

        $y = [
            [-22, 17, -12],
            [-4, -11, 2],
            [-20, 6, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_row_exclude()
    {
        $z = $this->a->rowExclude(2);

        $y = [
            [22, -17, 12],
            [4, 11, -2],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_column_exclude()
    {
        $z = $this->a->columnExclude(1);

        $y = [
            [22, 12],
            [4, -2],
            [20, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_augment_above()
    {
        $z = $this->a->augmentAbove($this->c);

        $y = [
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_augment_below()
    {
        $z = $this->a->augmentBelow($this->c);

        $y = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
            [4, 6, -12],
            [1, 3, 5],
            [-10, -1, 14],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_augment_left()
    {
        $z = $this->a->augmentLeft($this->b);

        $y = [
            [13, 22, -17, 12],
            [11, 4, 11, -2],
            [9, 20, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_augment_right()
    {
        $z = $this->a->augmentRight($this->b);

        $y = [
            [22, -17, 12, 13],
            [4, 11, -2, 11],
            [20, -6, -9, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_repeat()
    {
        $z = $this->b->repeat(2, 4);

        $y = [
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
            [13, 13, 13, 13],
            [11, 11, 11, 11],
            [9, 9, 9, 9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }
}
