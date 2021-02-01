# Tensor: Scientific Computing for PHP

[![PHP from Packagist](https://img.shields.io/packagist/php-v/rubix/tensor.svg?style=flat&colorB=8892BF)](https://www.php.net/) [![Latest Stable Version](https://img.shields.io/packagist/v/rubix/tensor.svg?style=flat&colorB=orange)](https://packagist.org/packages/rubix/tensor) [![Build](https://github.com/RubixML/Tensor/workflows/Build/badge.svg)](https://github.com/RubixML/Tensor/actions) [![Downloads from Packagist](https://img.shields.io/packagist/dt/rubix/tensor.svg?style=flat&colorB=red)](https://packagist.org/packages/rubix/tensor) [![GitHub](https://img.shields.io/github/license/RubixML/Tensor)](https://github.com/RubixML/Tensor/blob/master/LICENSE.md)

Tensor is a library and extension that provides objects for scientific computing in [PHP](https://php.net). It is used by libraries such as [Rubix ML](https://rubixml.com) to build and accelerate machine learning algorithms such as neural networks.

## Installation
Install Tensor into your project with [Composer](https://getcomposer.org/):
```sh
$ composer require rubix/tensor
```

## Requirements
- [PHP](https://php.net) 7.2 or above

### Optional To Compile Extension
- A C compiler such as [GCC](https://gcc.gnu.org/), [Clang](https://clang.llvm.org/), or [Visual C++](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)
- The PHP development package (source code and tooling)
- [re2c](https://re2c.org/) 0.13.6 or later
- [GNU make](https://www.gnu.org/software/make/) 3.81 or later
- [autoconf](https://www.gnu.org/software/autoconf/autoconf.html) 2.31 or later
- [automake](https://www.gnu.org/software/automake/) 1.14 or later
- libpcre3
- Ubuntu build-essentials

## Compiling the Extension
Clone the repository locally using [Git](https://git-scm.com/):
```sh
$ git clone https://github.com/RubixML/Tensor
```

Make sure you have all the necessary build tools installed such as a C compiler and make tools. For example, on an Ubuntu linux system you can enter the following on the command line to install the necessary packages.

```sh
$ sudo apt-get install gcc make re2c php-dev libpcre3-dev build-essential
```

Then, change into the `ext` directory from the project root and run the following commands from the terminal. See [this guide](https://www.php.net/manual/en/install.pecl.phpize.php) for more information on compiling PHP extensions with PHPize.

```sh
$ cd ./ext
$ phpize
$ ./configure
$ make
$ make install
```

## Installing the Extension
Add the following line to your `php.ini` configuration to install the extension.
```
extension=tensor.so
```

To confirm that the extension is loaded in PHP, you can run the following command.

```sh
php -m | grep tensor
```

## Funding
Rubix ML is funded by donations from the community. You can become a sponsor by making a contribution to one of our funding sources below.

- [Github Sponsors](https://github.com/sponsors/RubixML)

## Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License
The code is licensed [MIT](LICENSE) and the documentation is licensed [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/).
