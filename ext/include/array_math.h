#ifndef TENSOR_ARRAY_MATH_H
#define TENSOR_ARRAY_MATH_H

#include <Zend/zend.h>

void tensor_array_multiply(zval *return_value, zval *a, zval *b);
void tensor_array_divide(zval *return_value, zval *a, zval *b);
void tensor_array_add(zval *return_value, zval *a, zval *b);
void tensor_array_subtract(zval *return_value, zval *a, zval *b);

#endif