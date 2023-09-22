# Tensor: Scientific Computing for PHP

[![PHP from Packagist](https://img.shields.io/packagist/php-v/rubix/tensor.svg?style=flat&colorB=8892BF)](https://www.php.net/) [![Latest Stable Version](https://img.shields.io/packagist/v/rubix/tensor.svg?style=flat&colorB=orange)](https://packagist.org/packages/rubix/tensor) [![Code Checks](https://github.com/RubixML/Tensor/actions/workflows/ci.yml/badge.svg)](https://github.com/RubixML/Tensor/actions/workflows/ci.yml) [![Extension Build](https://github.com/RubixML/Tensor/actions/workflows/ci-ext.yml/badge.svg)](https://github.com/RubixML/Tensor/actions/workflows/ci-ext.yml) [![Downloads from Packagist](https://img.shields.io/packagist/dt/rubix/tensor.svg?style=flat&colorB=red)](https://packagist.org/packages/rubix/tensor) [![GitHub](https://img.shields.io/github/license/RubixML/Tensor)](https://github.com/RubixML/Tensor/blob/master/LICENSE.md)

A library and extension that provides objects for scientific computing in [PHP](https://php.net).
## Installation
Follow the instructions below to install either Tensor PHP or the Tensor extension.

### Tensor PHP
Install Tensor PHP into your project with [Composer](https://getcomposer.org/):
```sh
$ composer require rubix/tensor
```

### Tensor Extension
Install the Tensor extension via [PECL](https://pecl.php.net/package/Tensor):
```sh
$ pecl install tensor
```

> **Note:** If both the library and extension are installed, the extension will take precedence.

## Requirements
- [PHP](https://php.net) 7.4 or above

### Optional To Compile Extension
- A C compiler such as [GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), or [Visual C++](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)
- A Fortran compiler such as [GFortran](https://gcc.gnu.org/wiki/GFortran)
- The PHP development package (source code and tooling)
- [OpenBLAS](https://www.openblas.net/) development package
- [LAPACKE](https://www.netlib.org/lapack/lapacke.html) C interface to [LAPACK](http://www.netlib.org/lapack/)
- [re2c](https://re2c.org/) 0.13.6 or later
- [GNU make](https://www.gnu.org/software/make/) 3.81 or later
- [autoconf](https://www.gnu.org/software/autoconf/autoconf.html) 2.31 or later
- [automake](https://www.gnu.org/software/automake/) 1.14 or later
- Ubuntu build-essentials

## Manually Compiling the Extension
Clone the repository locally using [Git](https://git-scm.com/):
```sh
$ git clone https://github.com/RubixML/Tensor
```

Make sure you have all the necessary build tools installed such as a C compiler and make tools. For example, on an Ubuntu linux system you can enter the following on the command line to install the necessary dependencies.

```sh
$ sudo apt-get install make gcc gfortran php-dev libopenblas-dev liblapacke-dev re2c build-essential
```

Then, change into the `ext` directory from the project root and run the following commands from the terminal. See [this guide](https://www.php.net/manual/en/install.pecl.phpize.php) for more information on compiling PHP extensions with PHPize.

```sh
$ cd ./ext
$ phpize
$ ./configure
$ make
$ sudo make install
```

Finally, add the following line to your `php.ini` configuration to install the extension.
```
extension=tensor.so
```

To confirm that the extension is loaded in PHP, you can run the following command.

```sh
php -m | grep tensor
```

## Performance Comparison

![Tensor Performance MNIST](https://raw.githubusercontent.com/RubixML/Tensor/master/docs/images/tensor-performance-mnist.png)

![Tensor Performance Benchmarks](https://raw.githubusercontent.com/RubixML/Tensor/master/docs/images/tensor-performance-benchmarks.png)

## Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License
The code is licensed [MIT](LICENSE) and the documentation is licensed [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/).
