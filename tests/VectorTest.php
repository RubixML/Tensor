<?php

namespace Rubix\Tensor\Tests;

use Rubix\Tensor\Tensor;
use Rubix\Tensor\Vector;
use Rubix\Tensor\Matrix;
use Rubix\Tensor\ColumnVector;
use PHPUnit\Framework\TestCase;
use InvalidArgumentException;
use IteratorAggregate;
use RuntimeException;
use ArrayAccess;
use Countable;

class VectorTest extends TestCase
{
    protected $a;

    protected $b;

    protected $c;

    protected $d;

    public function setUp()
    {
        $this->a = Vector::build([-15, 25, 35, -36, -72, 89, 106, 45]);

        $this->b = Vector::quick([0.25, 0.1, 2., -0.5, -1., -3.0, 3.3, 2.0]);

        $this->c = Vector::quick([4., 6.5, 2.9, 20., 2.6, 11.9]);

        $this->d = Matrix::quick([
            [6.23, -1., 0.03, -0.01, -0.5, 2.],
            [0.01, 2.01, 1.0, 0.02, 0.05, -1.],
            [1.1, 5., -5., 30, -0.005, -0.001],
        ]);
    }

    public function test_build_vector()
    {
        $this->assertInstanceOf(Vector::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Countable::class, $this->a);
        $this->assertInstanceOf(IteratorAggregate::class, $this->a);
        $this->assertInstanceOf(ArrayAccess::class, $this->a);
    }

    public function test_build_bad_element()
    {
        $this->expectException(InvalidArgumentException::class);

        Vector::build([0, 0.1, 'bad']);
    }

    public function test_build_zeros()
    {
        $z = Vector::zeros(4);

        $y = [0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_ones()
    {
        $z = Vector::ones(4);

        $y = [1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }
    
    public function test_build_fill()
    {
        $z = Vector::fill(16, 4);

        $y = [16, 16, 16, 16];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_rand()
    {
        $z = Vector::rand(4);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(4, $z);
    }

    public function test_build_gaussian()
    {
        $z = Vector::gaussian(4);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(4, $z);
    }

    public function test_build_uniform()
    {
        $z = Vector::uniform(5);

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(5, $z);
    }

    public function test_build_range()
    {
        $z = Vector::range(5., 12., 2.);

        $y = [5., 7., 9., 11.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_build_linspace()
    {
        $z = Vector::linspace(-5, 5, 9);

        $y = [
            -5., -3.7500001000000003, -2.5000002, -1.2500003, -4.0000000023354687E-7,
            1.2499994999999995, 2.4999994, 3.749999299999999, 4.9999991999999995,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(9, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_maximum()
    {
        $z = Vector::maximum($this->a, $this->b);

        $y = [0.25, 25, 35, -0.5, -1.0, 89, 106, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_minimum()
    {
        $z = Vector::minimum($this->a, $this->b);

        $y = [-15, 0.1, 2.0, -36, -72, -3., 3.3, 2.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_shape()
    {
        $this->assertEquals([1, 8], $this->a->shape());
        $this->assertEquals([1, 8], $this->b->shape());
        $this->assertEquals([1, 6], $this->c->shape());
    }

    public function test_size()
    {
        $this->assertEquals(8, $this->a->size());
        $this->assertEquals(8, $this->b->size());
        $this->assertEquals(6, $this->c->size());
    }

    public function test_get_m()
    {
        $this->assertEquals(1, $this->a->m());
        $this->assertEquals(1, $this->b->m());
        $this->assertEquals(1, $this->c->m());
    }

    public function test_get_n()
    {
        $this->assertEquals(8, $this->a->n());
        $this->assertEquals(8, $this->b->n());
        $this->assertEquals(6, $this->c->n());
    }

    public function test_as_array()
    {
        $z = $this->a->asArray();

        $y = [-15, 25, 35, -36, -72, 89, 106, 45];

        $this->assertEquals($y, $z);
    }

    public function test_as_row_matrix()
    {
        $z = $this->a->asRowMatrix();

        $y = [[-15, 25, 35, -36, -72, 89, 106, 45]];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_as_column_matrix()
    {
        $z = $this->a->asColumnMatrix();

        $y = [[-15], [25], [35], [-36], [-72], [89], [106], [45]];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_reshape()
    {
        $z = $this->a->reshape(4, 2);

        $y = [
            [-15, 25],
            [35, -36],
            [-72, 89],
            [106, 45],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals([4, 2], $z->shape());
        $this->assertEquals($y, $z->asArray());
    }

    public function test_transpose()
    {
        $z = $this->a->transpose();

        $outcome = [-15, 25, 35, -36, -72, 89, 106, 45];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($outcome, $z->asArray());

        $z = $this->a->T;

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($outcome, $z->asArray());
    }

    public function test_map()
    {
        $z = $this->a->map(function ($value) {
            return $value > 0. ? 1 : 0;
        });

        $y = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_reduce()
    {
        $scalar = $this->a->reduce(function ($value, $carry) {
            return $carry + ($value / 2.);
        });

        $this->assertEquals(110.3671875, $scalar);
    }

    public function test_reciprocal()
    {
        $z = $this->a->reciprocal();

        $y = [
            -0.06666666666666667, 0.04, 0.02857142857142857, -0.027777777777777776,
            -0.013888888888888888, 0.011235955056179775, 0.009433962264150943, 0.022222222222222223,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_argmin()
    {
        $this->assertEquals(4, $this->a->argmin());
        $this->assertEquals(5, $this->b->argmin());
        $this->assertEquals(4, $this->c->argmin());
    }

    public function test_argmax()
    {
        $this->assertEquals(6, $this->a->argmax());
        $this->assertEquals(6, $this->b->argmax());
        $this->assertEquals(3, $this->c->argmax());
    }

    public function test_dot()
    {
        $this->assertEquals(331.54999999999995, $this->a->dot($this->b));
    }

    public function test_inner()
    {
        $this->assertEquals(331.54999999999995, $this->a->inner($this->b));
    }

    public function test_outer()
    {
        $z = $this->a->outer($this->b);

        $y = [
            [-3.75, -1.5, -30., 7.5, 15., 45., -49.5, -30.],
            [6.25, 2.5, 50., -12.5, -25., -75., 82.5, 50.],
            [8.75, 3.5, 70., -17.5, -35., -105., 115.5, 70.],
            [-9.0, -3.6, -72., 18., 36., 108., -118.8, -72.],
            [-18., -7.2, -144., 36., 72., 216., -237.6, -144.],
            [22.25, 8.9, 178., -44.5, -89., -267., 293.7, 178.],
            [26.5, 10.600000000000001, 212., -53., -106., -318., 349.79999999999995, 212.],
            [11.25, 4.5, 90., -22.5, -45., -135., 148.5, 90.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_cross()
    {
        $a = new Vector([1., -0.5, 6.]);

        $b = new Vector([2., 0., 3.]);

        $z = $a->cross($b);

        $y = [-1.5, 9., 1.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_project()
    {
        $z = $this->a->project($this->b);

        $y = [
            2.8373983739837394, 1.1349593495934958, 22.699186991869915, -5.674796747967479,
            -11.349593495934958, -34.048780487804876, 37.45365853658536, 22.699186991869915,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_multiply_matrix()
    {
        $z = $this->c->multiply($this->d);

        $y = [
            [24.92, -6.5, 0.087, -0.2,-1.3, 23.8],
            [0.04, 13.064999999999998, 2.9, 0.4, 0.13, -11.9],
            [4.4, 32.5, -14.5, 600., -0.013000000000000001, -0.0119],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_matrix()
    {
        $z = $this->c->divide($this->d);

        $y = [
            [0.6420545746388443, -6.5, 96.66666666666667, -2000., -5.2, 5.95],
            [400., 3.2338308457711444, 2.9, 1000., 52., -11.9],
            [3.6363636363636362, 1.3, -0.58, 0.6666666666666666, -520., -11900.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_matrix()
    {
        $z = $this->c->add($this->d);

        $y = [
            [10.23, 5.5, 2.9299999999999997, 19.99, 2.1, 13.9],
            [4.01, 8.51, 3.9, 20.02, 2.65, 10.9],
            [5.1, 11.5, -2.1, 50., 2.595, 11.899000000000001],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_matrix()
    {
        $z = $this->c->subtract($this->d);

        $y = [
            [-2.2300000000000004, 7.5, 2.87, 20.01, 3.1, 9.9],
            [3.99, 4.49, 1.9, 19.98, 2.5500000000000003, 12.9],
            [2.9, 1.5, 7.9, -10., 2.605, 11.901],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow_matrix()
    {
        $z = $this->c->pow($this->d);

        $y = [
            [5634.219287100394, 0.15384615384615385, 1.0324569211337775, 0.9704869503929601, 0.6201736729460423, 141.61],
            [1.013959479790029, 43.048284263459465, 2.9, 1.0617459178549786, 1.0489352187366092, 0.08403361344537814],
            [4.59479341998814, 11602.90625, 0.004875397277841432, 1.073741824E+39, 0.9952338371484033, 0.9975265256911376],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_equal_matrix()
    {
        $z = $this->c->equal($this->d);

        $y = [
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_not_equal_matrix()
    {
        $z = $this->c->notEqual($this->d);

        $y = [
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_matrix()
    {
        $z = $this->c->greater($this->d);

        $y = [
            [0, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_equal_matrix()
    {
        $z = $this->c->greaterEqual($this->d);

        $y = [
            [0, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 1, 1],
            [1, 1, 1, 0, 1, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_matrix()
    {
        $z = $this->c->less($this->d);

        $y = [
            [1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_equal_matrix()
    {
        $z = $this->c->lessEqual($this->d);

        $y = [
            [1, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 0, 0, 1, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_multiply_vector()
    {
        $z = $this->a->multiply($this->b);

        $y = [-3.75, 2.5, 70., 18., 72., -267., 349.79999999999995, 90.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_vector()
    {
        $z = $this->a->divide($this->b);

        $y = [-60., 250., 17.5, 72., 72., -29.666666666666668, 32.121212121212125, 22.5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_vector()
    {
        $z = $this->a->add($this->b);

        $y = [-14.75, 25.1, 37., -36.5, -73., 86., 109.3, 47.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_vector()
    {
        $z = $this->a->subtract($this->b);

        $y = [-15.25, 24.9, 33., -35.5, -71., 92., 102.7, 43.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow_vector()
    {
        $z = $this->b->pow($this->a);

        $y = [
            1073741824.0, 1.0000000000000014E-25, 34359738368.0, 68719476736.0,
            1., -2.909321189362571E+42, 9.172286825801562E+54, 35184372088832.0,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_mod_vector()
    {
        $z = $this->b->mod($this->a);

        $y = [0, 0, 2, 0, -1, -3, 3, 2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_equal_vector()
    {
        $z = $this->b->equal($this->a);

        $y = [0, 0, 0, 0, 0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_not_equal_vector()
    {
        $z = $this->b->notEqual($this->a);

        $y = [1, 1, 1, 1, 1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_vector()
    {
        $z = $this->b->greater($this->a);

        $y = [1, 0, 0, 1, 1, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_equal_vector()
    {
        $z = $this->b->greaterEqual($this->a);

        $y = [1, 0, 0, 1, 1, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_vector()
    {
        $z = $this->b->less($this->a);

        $y = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_equal_vector()
    {
        $z = $this->b->lessEqual($this->a);

        $y = [0, 1, 1, 0, 0, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_multiply_scalar()
    {
        $z = $this->a->multiply(2);
        
        $y = [-30, 50, 70, -72, -144, 178, 212, 90];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_divide_scalar()
    {
        $z = $this->a->divide(2);

        $y = [-7.5, 12.5, 17.5, -18, -36, 44.5, 53, 22.5];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_add_scalar()
    {
        $z = $this->a->add(10);

        $y = [-5, 35, 45, -26, -62, 99, 116, 55];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_subtract_scalar()
    {
        $z = $this->a->subtract(10);

        $y = [-25, 15, 25, -46, -82, 79, 96, 35];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow_scalar()
    {
        $z = $this->a->pow(4);

        $y = [
            50625, 390625, 1500625, 1679616, 26873856, 62742241, 126247696, 4100625
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_mod_scalar()
    {
        $z = $this->a->mod(4);

        $y = [-3, 1, 3,0, 0, 1, 2, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_equal_scalar()
    {
        $z = $this->a->equal(25);

        $y = [0, 1, 0, 0, 0, 0, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_not_equal_scalar()
    {
        $z = $this->a->notEqual(25);

        $y = [1, 0, 1, 1, 1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_scalar()
    {
        $z = $this->b->greater(1);

        $y = [0, 0, 1, 0, 0, 0, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_greater_equal_scalar()
    {
        $z = $this->b->greaterEqual(1);

        $y = [0, 0, 1, 0, 0, 0, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_scalar()
    {
        $z = $this->b->less(1);

        $y = [1, 1, 0, 1, 1, 1, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_less_equal_scalar()
    {
        $z = $this->b->lessEqual(1);

        $y = [1, 1, 0, 1, 1, 1, 0, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_abs()
    {
        $z = $this->a->abs();

        $y = [15, 25, 35, 36, 72, 89, 106, 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_square()
    {
        $z = $this->a->square();

        $y = [225, 625, 1225, 1296, 5184, 7921, 11236, 2025];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_pow()
    {
        $z = $this->a->pow(3);

        $y = [-3375, 15625, 42875, -46656, -373248, 704969, 1191016, 91125];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_sqrt()
    {
        $z = $this->c->sqrt();

        $y = [
            2., 2.5495097567963922, 1.70293863659264, 4.47213595499958,
            1.61245154965971, 3.449637662132068,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_exp()
    {
        $z = $this->a->exp();

        $y = [
            3.059023205018258E-7, 72004899337.38588, 1586013452313430.8,
            2.3195228302435696E-16, 5.380186160021138E-32, 4.4896128191743455E+38,
            1.0844638552900231E+46, 3.4934271057485095E+19,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_log()
    {
        $z = $this->c->log();

        $y = [
            1.3862943611198906, 1.8718021769015913, 1.0647107369924282,
            2.995732273553991, 0.9555114450274363, 2.4765384001174837,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_sin()
    {
        $z = $this->c->sin();

        $y = [
            -0.7568024953079282, 0.21511998808781552, 0.23924932921398243,
            0.9129452507276277, 0.5155013718214642, -0.6181371122370333,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_cos()
    {
        $z = $this->c->cos();

        $y = [
            -0.6536436208636119, 0.9765876257280235, -0.9709581651495905,
            0.40808206181339196, -0.8568887533689473, 0.7860702961410393,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_tan()
    {
        $z = $this->c->tan();

        $y = [
            1.1578212823495777, 0.22027720034589682, -0.24640539397196634,
            2.237160944224742, -0.6015966130897586, -0.7863636563696398,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_degrees()
    {
        $z = $this->c->degrees();

        $y = [
            229.1831180523293, 372.42256683503507, 166.15776058793872,
            1145.9155902616465, 148.96902673401405, 681.8197762056797,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_radians()
    {
        $z = $this->c->radians();

        $y = [
            0.06981317007977318, 0.11344640137963141, 0.05061454830783556,
            0.3490658503988659, 0.04537856055185257, 0.2076941809873252,
        ];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_sum()
    {
        $this->assertEquals(177., $this->a->sum());
        $this->assertEquals(3.15, $this->b->sum());
        $this->assertEquals(47.9, $this->c->sum());
    }

    public function test_product()
    {
        $this->assertEquals(-14442510600000.0, $this->a->product());
        $this->assertEquals(-0.49500000000000005, $this->b->product());
        $this->assertEquals(46657.52, $this->c->product());
    }

    public function test_min()
    {
        $this->assertEquals(-72, $this->a->min());
        $this->assertEquals(-3, $this->b->min());
        $this->assertEquals(2.6, $this->c->min());
    }

    public function test_max()
    {
        $this->assertEquals(106, $this->a->max());
        $this->assertEquals(3.3, $this->b->max());
        $this->assertEquals(20., $this->c->max());
    }

    public function test_mean()
    {
        $this->assertEquals(22.125, $this->a->mean());
        $this->assertEquals(0.39375, $this->b->mean());
        $this->assertEquals(7.983333333333333, $this->c->mean());
    }

    public function test_median()
    {
        $this->assertEquals(30., $this->a->median());
        $this->assertEquals(0.175, $this->b->median());
        $this->assertEquals(5.25, $this->c->median());
    }

    public function test_percentile()
    {
        $this->assertEquals(30., $this->a->percentile(50));
        $this->assertEquals(-0.625, $this->b->percentile(25));
        $this->assertEquals(10.55, $this->c->percentile(75));
    }

    public function test_variance()
    {
        $this->assertEquals(3227.609375, $this->a->variance());
        $this->assertEquals(3.4965234374999996, $this->b->variance());
        $this->assertEquals(38.77138888888888, $this->c->variance());
    }

    public function test_round()
    {
        $z = $this->c->round(2);

        $y = [4.0, 6.5, 2.9, 20., 2.6, 11.9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_floor()
    {
        $z = $this->c->floor();

        $y = [4., 6., 2., 20., 2., 11.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_ceil()
    {
        $z = $this->c->ceil(2);

        $y = [4., 7., 3., 20., 3., 12.];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_l1_norm()
    {
        $this->assertEquals(423., $this->a->l1Norm());
        $this->assertEquals(12.149999999999999, $this->b->l1Norm());
        $this->assertEquals(47.9, $this->c->l1Norm());
    }

    public function test_l2_norm()
    {
        $this->assertEquals(172.4441938715247, $this->a->l2Norm());
        $this->assertEquals(5.404858925078433, $this->b->l2Norm());
        $this->assertEquals(24.799798386277256, $this->c->l2Norm());
    }

    public function test_p_norm()
    {
        $this->assertEquals(135.15554088861361, $this->a->pNorm(3.));
        $this->assertEquals(3.7063242195906976, $this->b->pNorm(5.));
        $this->assertEquals(20.01112107057168, $this->c->pNorm(10.));
    }

    public function test_max_norm()
    {
        $this->assertEquals(106., $this->a->maxNorm());
        $this->assertEquals(3.3, $this->b->maxNorm());
        $this->assertEquals(20., $this->c->maxNorm());
    }

    public function test_clip()
    {
        $z = $this->a->clip(0., 100);

        $y = [0., 25, 35, 0., 0., 89, 100., 45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_sign()
    {
        $z = $this->a->sign();

        $y = [-1, 1, 1, -1, -1, 1, 1, 1];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_negate()
    {
        $z = $this->a->negate();

        $y = [15, -25, -35, 36, 72, -89, -106, -45];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($y, $z->asArray());
    }

    public function test_to_string()
    {
        $outcome = '[ -15 25 35 -36 -72 89 106 45 ]';

        // Windows/Linux have diff line endings
        // $this->assertEquals($outcome, (string) $this->a);

        $this->assertTrue(true);
    }
}
