<?php

const CONFIG_M4_PATH = __DIR__ . '/ext/config.m4';

const DOCKER_MATCH = 'PHP_ADD_BUILD_DIR([$ext_builddir/tensor/])';
const DOCKER_PATCH = 'PHP_ADD_BUILD_DIR([$ext_builddir/tensor/])
    PHP_ADD_BUILD_DIR([$ext_builddir/tensor/decompositions/])
    PHP_ADD_BUILD_DIR([$ext_builddir/tensor/exceptions/])
    PHP_ADD_BUILD_DIR([$ext_builddir/tensor/reductions/])';

$contents = file_get_contents(CONFIG_M4_PATH);

$contents = str_replace(DOCKER_MATCH, DOCKER_PATCH, $contents);

file_put_contents(CONFIG_M4_PATH, $contents);
