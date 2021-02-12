
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Tensor_Tensor) {

	ZEPHIR_REGISTER_INTERFACE(Tensor, Tensor, tensor, tensor, tensor_tensor_method_entry);

	zephir_declare_class_constant_double(tensor_tensor_ce, SL("EPSILON"), 0.00000001);

	zend_class_implements(tensor_tensor_ce, 1, tensor_arraylike_ce);
	zend_class_implements(tensor_tensor_ce, 1, tensor_arithmetic_ce);
	zend_class_implements(tensor_tensor_ce, 1, tensor_comparable_ce);
	zend_class_implements(tensor_tensor_ce, 1, tensor_functional_ce);
	zend_class_implements(tensor_tensor_ce, 1, tensor_trigonometric_ce);
	zend_class_implements(tensor_tensor_ce, 1, tensor_statistical_ce);
	return SUCCESS;

}

/**
 * Map a function over all of the elements in the tensor.
 *
 * @param callable callback
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, map);

/**
 * Reduce the tensor down to a scalar.
 *
 * @param callable callback
 * @param mixed initial
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, reduce);

/**
 * Transpose the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, transpose);

/**
 * Clip the tensor to be between the given minimum and maximum.
 *
 * @param float min
 * @param float max
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, clip);

/**
 * Clip the tensor to be lower bounded by a given minimum.
 *
 * @param float min
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, clipLower);

/**
 * Clip the tensor to be upper bounded by a given maximum.
 *
 * @param float max
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, clipUpper);

/**
 * Return the shape of the tensor as a string.
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, shapeString);

/**
 * Convert the tensor into a string representation.
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, __toString);

