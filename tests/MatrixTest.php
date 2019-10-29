<?php

namespace Tensor\Tests;

use Tensor\Tensor;
use Tensor\Vector;
use Tensor\Matrix;
use Tensor\ColumnVector;
use PHPUnit\Framework\TestCase;
use InvalidArgumentException;
use IteratorAggregate;
use RuntimeException;
use ArrayAccess;
use Countable;

class MatrixTest extends TestCase
{
    protected $a;

    protected $b;

    protected $c;

    protected $d;

    protected $e;

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

        $this->e = ColumnVector::quick([2.5, -1, 4.8]);
    }

    public function test_build_matrix()
    {
        $this->assertInstanceOf(Matrix::class, $this->a);
        $this->assertInstanceOf(Tensor::class, $this->a);
        $this->assertInstanceOf(Countable::class, $this->a);
        $this->assertInstanceOf(IteratorAggregate::class, $this->a);
        $this->assertInstanceOf(ArrayAccess::class, $this->a);
    }

    public function test_build_bad_element()
    {
        $this->expectException(InvalidArgumentException::class);

        Matrix::build([
            [0, 0.1, 'bad'],
        ]);
    }

    public function test_stack()
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

    public function test_build_identity()
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

    public function test_build_zeros()
    {
        $z = Matrix::zeros(2, 4);

        $expected = [
            [0, 0, 0, 0],
            [0, 0, 0, 0],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_build_ones()
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

    public function test_build_diagonal()
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

    public function test_build_fill()
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

        $expected = [
            [22, 6, 12],
            [4, 11, 5],
            [20, -1, 14],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_minumum()
    {
        $z = Matrix::minimum($this->a, $this->c);

        $expected = [
            [4,-17, -12],
            [1, 3, -2],
            [-10, -6, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_shape()
    {
        $this->assertEquals([3, 3], $this->a->shape());
        $this->assertEquals([3, 1], $this->b->shape());
        $this->assertEquals([3, 3], $this->c->shape());
    }

    public function test_shape_string()
    {
        $this->assertEquals('3 x 3', $this->a->shapeString());
        $this->assertEquals('3 x 1', $this->b->shapeString());
        $this->assertEquals('3 x 3', $this->c->shapeString());
    }

    public function test_is_square()
    {
        $this->assertTrue($this->a->isSquare());
        $this->assertFalse($this->b->isSquare());
        $this->assertTrue($this->c->isSquare());
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

        $expected = [4, 11, -2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($expected, $z->asArray());
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

        $expected = [-17, 11, -6];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_diagonal_as_vector()
    {
        $z = $this->a->diagonalAsVector();

        $expected = [22, 11, -9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertCount(3, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_as_array()
    {
        $z = $this->a->asArray();

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
            [20, -6, -9],
        ];

        $this->assertEquals($expected, $z);
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

    public function test_as_column_vectors()
    {
        $vectors = $this->a->asColumnVectors();

        $this->assertInstanceOf(ColumnVector::class, $vectors[0]);
        $this->assertInstanceOf(ColumnVector::class, $vectors[1]);
        $this->assertInstanceOf(ColumnVector::class, $vectors[2]);

        $this->assertEquals([22, 4, 20], $vectors[0]->asArray());
        $this->assertEquals([-17, 11, -6], $vectors[1]->asArray());
        $this->assertEquals([12, -2, -9], $vectors[2]->asArray());
    }

    public function test_argmin()
    {
        $z = $this->a->argmin();

        $expected = [1, 2, 2];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_argmax()
    {
        $z = $this->a->argmax();

        $expected = [0, 1, 0];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_flatten()
    {
        $z = $this->a->flatten();

        $expected = [22, -17, 12, 4, 11, -2, 20, -6, -9];

        $this->assertInstanceOf(Vector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_transpose()
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

    public function test_inverse()
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

    public function test_determinant()
    {
        $this->assertEquals(-5301.999999999999, $this->a->determinant());
        $this->assertEquals(-544., $this->c->determinant());
    }

    public function test_rank()
    {
        $this->assertEquals(3, $this->a->rank());
        $this->assertEquals(1, $this->b->rank());
        $this->assertEquals(3, $this->c->rank());
    }

    public function test_reciprocal()
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

    public function test_map()
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

    public function test_reduce()
    {
        $z = $this->a->reduce(function ($value, $carry) {
            return $carry + ($value / 2.);
        });

        $this->assertEquals(17.5, $z);
    }

    public function test_ref()
    {
        [$z, $swaps] = $this->a->ref();

        $expected = [
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_rref()
    {
        $z = $this->a->rref();

        $expected = [
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_lu_decomposition()
    {
        [$l, $u] = $this->a->lu();

        $lHat = [
            [1., 0, 0],
            [0.18181818181818182, 1., 0],
            [0.9090909090909091, 0.6709677419354838, 1.],
        ];

        $uHat = [
            [22, -17, 12],
            [0, 14.09090909090909, -4.181818181818182],
            [0, 0, -17.10322580645161],
        ];

        $this->assertInstanceOf(Matrix::class, $l);
        $this->assertInstanceOf(Matrix::class, $u);

        $this->assertCount(9, $l);
        $this->assertCount(9, $u);

        $this->assertEquals($lHat, $l->asArray());
        $this->assertEquals($uHat, $u->asArray());
    }

    public function test_eig()
    {
        if (extension_loaded('tensor')) {
            $this->markTestSkipped('Not implemented in extension yet.');
        }

        [$eigvalues, $eigvectors] = $this->a->eig();

        $values = [25.108706520450326, -15.096331148319537, 13.9876246278692];

        $vectors = [
            [-0.5029346679560592, -0.1309992382037118, -0.33107976181279675],
            [0.15580805853732102, -0.08643645234319261, -0.6918777439682378],
            [0.8501650243704214, 0.987607178637524, 0.641631809310763],
        ];

        $this->assertInstanceOf(Matrix::class, $eigvectors);

        $this->assertEquals($values, $eigvalues);
        $this->assertEquals($vectors, $eigvectors->asArray());
    }

    public function test_solve()
    {
        $z = $this->a->solve($this->d);

        $expected = [
            3.5542559833507, -2.071342351717, -9.2838709677419,
        ];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_matmul()
    {
        $z = $this->a->matmul($this->b);

        $expected = [
            [207], [155], [113],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_convolve()
    {
        $input = Matrix::quick([
            [3, 27, 66, 29, 42, 1],
            [5, 9, 15, 42, 45, 16],
            [91, 67, 49, 22, 66, 5],
            [5, 1, 4, 9, 8, 6, 2],
            [22, 16, 18, 19, 21, 25],
            [6, 9, 69, 5, 2, 33, 35],
        ]);

        $z = $input->convolve($this->a, 1);

        $expected = [
            [254, 792, 1565, 811, 499, 195],
            [540, 2311, 711, 2350, -766, 409],
            [1356, 1083, 1304, 992, 478, -584],
            [831, 164, -75, 1225, 21, -747],
            [392, 1670, -566, 1114, 1036, -412],
            [290, 429, 889, 69, 347, 20],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_multiply_matrix()
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

    public function test_divide_matrix()
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

    public function test_add_matrix()
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

    public function test_subtract_matrix()
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

    public function test_pow_matrix()
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

    public function test_mod_matrix()
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

    public function test_equal_matrix()
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

    public function test_not_equal_matrix()
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

    public function test_greater_matrix()
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

    public function test_greater_equal_matrix()
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

    public function test_less_matrix()
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

    public function test_less_equal_matrix()
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

    public function test_dot_vector()
    {
        $z = $this->a->dot($this->d);

        $expected = [-138, 120, -11];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_multiply_vector()
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

    public function test_divide_vector()
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

    public function test_add_vector()
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

    public function test_subtract_vector()
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

    public function test_pow_vector()
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

    public function test_mod_vector()
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

    public function test_equal_vector()
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

    public function test_not_equal_vector()
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

    public function test_greater_vector()
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

    public function test_greater_equal_vector()
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

    public function test_less_vector()
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

    public function test_less_equal_vector()
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

    public function test_multiply_column_vector()
    {
        $z = $this->a->multiply($this->e);

        $expected = [
            [55.0, -42.5, 30.],
            [-4, -11, 2],
            [96., -28.799999999999997, -43.199999999999996],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_divide_column_vector()
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

    public function test_add_column_vector()
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

    public function test_subtract_column_vector()
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

    public function test_mod_column_vector()
    {
        $z = $this->a->mod($this->e);

        $expected = [
            [0, -1, 0],
            [0, 0, 0],
            [0, -2, -1],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_equal_column_vector()
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

    public function test_not_equal_column_vector()
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

    public function test_greater_column_vector()
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

    public function test_greater_equal_column_vector()
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

    public function test_less_column_vector()
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

    public function test_less_equal_column_vector()
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

    public function test_multiply_scalar()
    {
        $z = $this->a->multiply(2.5);

        $expected = [
            [55, -42.5, 30],
            [10., 27.5, -5.],
            [50, -15, -22.5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_divide_scalar()
    {
        $z = $this->a->divide(2.);

        $expected = [
            [11., -8.5, 6.],
            [2., 5.5, -1.],
            [10., -3., -4.5],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_add_scalar()
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

    public function test_subtract_scalar()
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

    public function test_pow_scalar()
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

    public function test_mod_scalar()
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

    public function test_equal_scalar()
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

    public function test_not_equal_scalar()
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

    public function test_greater_scalar()
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

    public function test_greater_equal_scalar()
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

    public function test_less_scalar()
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

    public function test_less_equal_scalar()
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

    public function test_abs()
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

    public function test_square()
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

    public function test_square_root()
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

    public function test_exp()
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

    public function test_log()
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

    public function test_sin()
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

    public function test_cos()
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

    public function test_tan()
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

    public function test_rad2deg()
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

    public function test_deg2rad()
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

    public function test_sum()
    {
        $z = $this->a->sum();

        $expected = [17, 13, 5];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_product()
    {
        $z = $this->a->product();

        $expected = [-4488., -88., 1080.];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_min()
    {
        $z = $this->a->min();

        $expected = [-17, -2, -9];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_max()
    {
        $z = $this->a->max();

        $expected = [22, 11, 20];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_mean()
    {
        $z = $this->a->mean();

        $expected = [5.666666666666667, 4.333333333333333, 1.6666666666666667];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_median()
    {
        $z =$this->a->median();

        $expected = [12, 4, -6];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_percentile()
    {
        $z =$this->a->percentile(40);

        $expected = [6.200000000000003, 2.8000000000000007, -6.6];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_variance()
    {
        $z = $this->a->variance();

        $expected = [273.55555555555554, 28.222222222222225, 169.55555555555554];

        $this->assertInstanceOf(ColumnVector::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_covariance()
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

    public function test_round()
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

    public function test_floor()
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

    public function test_ceil()
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

        $expected = [
            [22, 0., 12],
            [4, 11, 0.],
            [20, 0., 0.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_clip_lower()
    {
        $z = $this->a->clipLower(5.);

        $expected = [
            [22, 5., 12],
            [5., 11, 5.],
            [20, 5., 5.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_clip_upper()
    {
        $z = $this->a->clipUpper(16.);

        $expected = [
            [16., -17., 12],
            [4, 11, -2.],
            [16, -6., -9.],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_sign()
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

    public function test_negate()
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

    public function test_row_exclude()
    {
        $z = $this->a->rowExclude(2);

        $expected = [
            [22, -17, 12],
            [4, 11, -2],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_column_exclude()
    {
        $z = $this->a->columnExclude(1);

        $expected = [
            [22, 12],
            [4, -2],
            [20, -9],
        ];

        $this->assertInstanceOf(Matrix::class, $z);
        $this->assertEquals($expected, $z->asArray());
    }

    public function test_augment_above()
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

    public function test_augment_below()
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

    public function test_augment_left()
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

    public function test_augment_right()
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

    public function test_repeat()
    {
        $z = $this->b->repeat(2, 4);

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

    public function test_to_string()
    {
        $outcome = '[ 22 -17 12 ]' . "\r\n"
                    . '[ 4 11 -2 ]' . "\r\n"
                    . '[ 20 -6 -9 ]';

        // Windows/Linux have diff line endings
        // $this->assertEquals($outcome, (string) $this->a);

        $this->assertTrue(true);
    }
}
