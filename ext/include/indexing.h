#ifndef TENSOR_INDEXING_H
#define TENSOR_INDEXING_H

#include <Zend/zend.h>

void tensor_argmin(zval * return_value, zval * values);
void tensor_argmax(zval * return_value, zval * values);

#endif
