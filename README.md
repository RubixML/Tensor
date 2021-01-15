# Tensor: Scientific Computing for PHP

[![PHP from Packagist](https://img.shields.io/packagist/php-v/rubix/tensor.svg?style=flat&colorB=8892BF)](https://www.php.net/) [![Latest Stable Version](https://img.shields.io/packagist/v/rubix/tensor.svg?style=flat&colorB=orange)](https://packagist.org/packages/rubix/tensor) [![Build](https://github.com/RubixML/Tensor/workflows/Build/badge.svg)](https://github.com/RubixML/Tensor/actions) [![Downloads from Packagist](https://img.shields.io/packagist/dt/rubix/tensor.svg?style=flat&colorB=red)](https://packagist.org/packages/rubix/tensor) [![GitHub](https://img.shields.io/github/license/RubixML/Tensor)](https://github.com/RubixML/Tensor/blob/master/LICENSE.md)

Tensor is a library and extension that provides objects for scientific computing in [PHP](https://php.net).

## Installation
Install Tensor into your project with [Composer](https://getcomposer.org/):
```sh
$ composer require rubix/tensor
```

## Requirements
- [PHP](https://php.net) 7.2 or above

### Optional
- A C compiler such as [GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), or [Visual C++](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads) to compile the extension

## Compiling the Extension
Clone the repository locally using [Git](https://git-scm.com/):
```sh
$ git clone https://github.com/RubixML/Tensor
```

Make sure you have the PHP development package installed, change into the `ext` directory, and run the following commands from the terminal. See [this guide](https://www.php.net/manual/en/install.pecl.phpize.php) for more information on compiling PHP extensions with PHPize.

```sh
$ cd ./ext
$ phpize
$ ./configure
$ make
$ make install
```

## Installing the Extension
Then, you can add the following line to your `php.ini` configuration to install the extension.
```
extension=tensor.so
```

To confirm that the extension is loaded in PHP, run the following command.

```sh
php -m | grep tensor
```

## License
The code is licensed [MIT](LICENSE.md) and the documentation is licensed [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/).
