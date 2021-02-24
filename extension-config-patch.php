<?php

const CONFIG_M4_PATH = __DIR__ . '/ext/config.m4';

const OPENBLAS_MATCH_1 = "PHP_ARG_ENABLE(tensor, whether to enable tensor, [ --enable-tensor   Enable Tensor])";
const OPENBLAS_PATCH_1 = "PHP_ARG_ENABLE(tensor, whether to enable tensor, [ --enable-tensor   Enable Tensor])

PHP_ARG_WITH(openblas, libopenblas directory, [ --with-openblas=DIR   libopenblas directory], no, no)";

const OPENBLAS_MATCH_2 = "if test \"\$PHP_TENSOR\" = \"yes\"; then";
const OPENBLAS_PATCH_2 = "if test \"\$PHP_TENSOR\" = \"yes\"; then

    AC_MSG_CHECKING([Check openblas headers])
    for i in \$PHP_OPENBLAS /usr/local/include /usr/include/openblas /usr/include; do
        if test -r \$i/cblas.h; then
            OPENBLAS_DIR=\$i
            AC_MSG_RESULT([found in \$i])
            break
        fi
    done

    if test -z \"\$OPENBLAS_DIR\"; then
        AC_MSG_ERROR([openblas headers not found])
    else
        PHP_ADD_INCLUDE(\$OPENBLAS_DIR)
    fi";

const DOCKER_MATCH = "PHP_ADD_BUILD_DIR([\$ext_builddir/tensor/])";
const DOCKER_PATCH = "PHP_ADD_BUILD_DIR([\$ext_builddir/tensor/])
    PHP_ADD_BUILD_DIR([\$ext_builddir/tensor/decompositions/])
    PHP_ADD_BUILD_DIR([\$ext_builddir/tensor/reductions/])";

$contents = file_get_contents(CONFIG_M4_PATH);

$contents = str_replace(OPENBLAS_MATCH_1, OPENBLAS_PATCH_1, $contents);
$contents = str_replace(OPENBLAS_MATCH_2, OPENBLAS_PATCH_2, $contents);

$contents = str_replace(DOCKER_MATCH, DOCKER_PATCH, $contents);

file_put_contents(CONFIG_M4_PATH, $contents);
