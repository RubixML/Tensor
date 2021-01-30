#ifndef TENSOR_ARRAY_MATH_H
#define TENSOR_ARRAY_MATH_H

#include <Zend/zend.h>

void tensor_matmul(zval * return_value, zval * a, zval * b);
void tensor_dot(zval * return_value, zval * a, zval * b);

#endif