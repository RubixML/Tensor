#ifndef TENSOR_LINEAR_ALGEBRA_H
#define TENSOR_LINEAR_ALGEBRA_H

#include <Zend/zend.h>

void tensor_matmul(zval * return_value, zval * a, zval * b);
void tensor_dot(zval * return_value, zval * a, zval * b);
void tensor_inverse(zval * return_value, zval * a);

#endif