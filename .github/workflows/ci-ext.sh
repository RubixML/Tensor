#!/bin/sh

set -o nounset
set -o errexit

. /etc/os-release

case "${ID:-}" in
  alpine)
    apk update
    apk add $PHPIZE_DEPS lapack-dev libexecinfo-dev openblas-dev
    ;;
  debian)
    apt-get update
    apt-get install -qy gfortran-8 liblapack-dev libopenblas-dev liblapacke-dev
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
