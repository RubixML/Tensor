# Getting Started

Tensor provides objects for scientific computing in PHP. It ships two ways — a pure-PHP Composer library and a PECL extension backed by OpenBLAS / LAPACKE for native speed. Both expose the same object-oriented API.

> **Note:** If both the library and the extension are installed, the extension takes precedence.

## Installation

### Requirements

- PHP 8.0 or above
- [Composer](https://getcomposer.org/) (to install the library)

### Tensor PHP (Library)

Install the library into your project with Composer:

```sh
$ composer require rubix/tensor
```

### Tensor Extension

Install the compiled extension via [PECL](https://pecl.php.net/package/Tensor):

```sh
$ pecl install tensor
```

After installing, add the following line to your `php.ini`:

```
extension=tensor.so
```

Confirm the extension is loaded:

```sh
$ php -m | grep tensor
```

See the [README](https://github.com/RubixML/Tensor#manually-compiling-the-extension) for instructions on compiling the extension from source (requires a C compiler, GFortran, OpenBLAS, LAPACKE, and PHP development tooling).

## Your First Script

Create a simple example that constructs a matrix, performs a matrix multiplication, computes some statistics, and reduces it to row echelon form.

```php
<?php

require __DIR__ . '/vendor/autoload.php';

use Tensor\Matrix;
use Tensor\Vector;

// Build a 2 x 3 matrix.
$a = Matrix::build([
    [1.0, 2.0, 3.0],
    [4.0, 5.0, 6.0],
]);

// Build a 3 x 2 matrix.
$b = Matrix::build([
    [7.0, 8.0],
    [9.0, 10.0],
    [11.0, 12.0],
]);

// Matrix-matrix product -> 2 x 2 matrix.
$c = $a->matmul($b);

var_export($c->asArray());
// [[58.0, 64.0], [139.0, 154.0]]

// Element-wise operations work against scalars, vectors, and matrices.
$d = $a->multiplyScalar(2.0)->add(1.0);

var_export($d->asArray());
// [[3.0, 5.0, 7.0], [9.0, 11.0, 13.0]]

// Methods are chainable, immutable, and reuse underlying arrays when possible.
var_export($a->sqrt()->round(2)->asArray());
// [[1.0, 1.41, 1.73], [2.0, 2.24, 2.45]]

// Compute the mean of each row (a ColumnVector).
$means = $a->mean();

var_export($means->asArray());
// [2.0, 5.0]

// Compute the reduced row echelon form (RREF).
$rref = $a->rref()->a();

var_export($rref->asArray());
// [[1, 0, -1], [0.0, 1.0, 2.0]]

// Vectors are 1-dimensional tensors.
$v = Vector::range(1.0, 4.0);

echo $v->dot(Vector::ones(4)) . PHP_EOL;
// 10

var_export($v->l2Norm());
// 5.477225575051661
```

## Next Steps

- Browse the [API reference](README.md) to learn about every class and interface.