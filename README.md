# Tensor: Scientific Computing for PHP

[![PHP from Packagist](https://img.shields.io/packagist/php-v/rubix/tensor.svg?style=flat-square&colorB=8892BF)](https://www.php.net/) [![Latest Stable Version](https://img.shields.io/packagist/v/rubix/tensor.svg?style=flat-square&colorB=orange)](https://packagist.org/packages/rubix/tensor) [![Travis](https://img.shields.io/travis/RubixML/Tensor.svg?style=flat-square)](https://travis-ci.org/RubixML/Tensor) [![Downloads from Packagist](https://img.shields.io/packagist/dt/rubix/tensor.svg?style=flat-square&colorB=red)](https://packagist.org/packages/rubix/tensor)

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
- [Zephir parser](https://github.com/phalcon/php-zephir-parser) to generate low level extension code

### Additional Requirements for Compiling PHP Extension
See this [guide](https://docs.zephir-lang.com/0.12/en/installation) for additional requirements for compiling and installing the PHP extension from source with [Zephir](https://docs.zephir-lang.com/0.12/en/welcome).

## Compiling the Extension
Clone the repository locally using [Git](https://git-scm.com/):

```sh
$ git clone https://github.com/RubixML/Tensor
```

Install dependencies using [Composer](https://getcomposer.org/):

```sh
$ composer install
```

To compile the PHP extension from source you can run `composer compile`:

```sh
$ composer compile
```

## Installing the Extension
To compile and install the extension in one command you may call `composer install-ext`:

```sh
$ composer install-ext
```

Then, add the following line to your `php.ini` configuration:

```
extension=tensor
```

## License
MIT
