#ifndef TENSOR_TENSOR_ARITHMETIC_H
#define TENSOR_TENSOR_ARITHMETIC_H

#include <Zend/zend.h>

void tensor_multiply(zval * return_value, zval * a, zval * b);

void tensor_divide(zval * return_value, zval * a, zval * b);

void tensor_add(zval * return_value, zval * a, zval * b);

void tensor_subtract(zval * return_value, zval * a, zval * b);

void tensor_pow(zval * return_value, zval * a, zval * b);

void tensor_mod(zval * return_value, zval * a, zval * b);

#endif