#ifndef TENSOR_ARRAY_COMPARISON_H
#define TENSOR_ARRAY_COMPARISON_H

#include <Zend/zend.h>

void tensor_equal(zval * return_value, zval * a, zval * b);

void tensor_not_equal(zval * return_value, zval * a, zval * b);

void tensor_greater(zval * return_value, zval * a, zval * b);

void tensor_equal_equal(zval * return_value, zval * a, zval * b);

void tensor_less(zval * return_value, zval * a, zval * b);

void tensor_less_equal(zval * return_value, zval * a, zval * b);

#endif