#!/bin/sh

set -o nounset
set -o errexit

. /etc/os-release

case "${ID:-}" in
  alpine)
    apk update
    case "$VERSION_ID" in
      3.11.* | 3.12.* | 3.13.* | 3.14.* | 3.15.* | 3.16.* | 3.17.*)
        apk update && apk add $PHPIZE_DEPS lapack lapack-dev openblas-dev
        if [ ! -e /usr/lib/liblapacke.so ]; then
          # Fix for Alpine 3.15, 3.16 and 3.17
          ln -s /usr/lib/liblapacke.so.3 /usr/lib/liblapacke.so
        fi
        ;;
      *)
        apk add $PHPIZE_DEPS liblapack lapack-dev openblas-dev
        ;;
    esac
    ;;
  debian)
    apt-get update
    apt-get install -qy gfortran liblapack-dev libopenblas-dev liblapacke-dev
    ;;
  *)
    echo 'Unsupported distribution' >&2
    exit 1
esac

cd /tmp
pecl package /app/package.xml
MAKE="make -j$(nproc)" pecl install tensor-*.tgz
docker-php-ext-enable tensor
php --ri tensor

# Let's check that PHP doesn't output any warning
TENSOR_PHP_OUTPUT="$(php -r ';' 2>&1)"
if [ -n "$TENSOR_PHP_OUTPUT" ]; then
  printf 'PHP displayed these warnings at startup:\n%s\n' "$TENSOR_PHP_OUTPUT" >&2
  exit 1
fi
