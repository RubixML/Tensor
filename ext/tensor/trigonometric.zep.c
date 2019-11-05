
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Tensor_Trigonometric) {

	ZEPHIR_REGISTER_INTERFACE(Tensor, Trigonometric, tensor, trigonometric, tensor_trigonometric_method_entry);

	zend_class_implements(tensor_trigonometric_ce, 1, tensor_tensor_ce);
	return SUCCESS;

}

/**
 * Return the sine of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, sin);

/**
 * Compute the arc sine of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, asin);

/**
 * Return the cosine of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, cos);

/**
 * Compute the arc cosine of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, acos);

/**
 * Return the tangent of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, tan);

/**
 * Compute the arc tangent of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, atan);

/**
 * Convert angles from radians to degrees.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, rad2deg);

/**
 * Convert angles from degrees to radians.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Trigonometric, deg2rad);

