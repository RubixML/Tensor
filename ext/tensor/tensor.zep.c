
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

	zend_class_implements(tensor_tensor_ce, 1, zend_ce_arrayaccess);
	zend_class_implements(tensor_tensor_ce, 1, zend_ce_aggregate);
	zend_class_implements(tensor_tensor_ce, 1, spl_ce_Countable);
	return SUCCESS;

}

/**
 * Return a tuple with the dimensionality of the tensor.
 *
 * @return int[]
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, shape);

/**
 * Return the shape of the tensor as a string.
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, shapeString);

/**
 * Return the number of elements in the tensor.
 *
 * @return int
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, size);

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
 * @return int|float
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, reduce);

/**
 * Transpose the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, transpose);

/**
 * A universal function to multiply this tensor with another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, multiply);

/**
 * A universal function to divide this tensor by another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, divide);

/**
 * A universal function to add this tensor with another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, add);

/**
 * A universal function to subtract this tensor from another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, subtract);

/**
 * A universal function to raise this tensor to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, pow);

/**
 * A universal function to compute the integer modulus of this tensor
 * and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, mod);

/**
 * A universal function to compute the equality comparison of a tensor
 * and another tensor element-wise.
 *
 * @param  mixed  b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, equal);

/**
 * A universal function to compute the not equal comparison of
 * this tensor and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, notEqual);

/**
 * A universal function to compute the greater than comparison of a
 * tensor and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, greater);

/**
 * A universal function to compute the greater than or equal to
 * comparison of a tensor and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, greaterEqual);

/**
 * A universal function to compute the less than comparison of a
 * tensor and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, less);

/**
 * A universal function to compute the less than or equal to
 * comparison of a tensor and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, lessEqual);

/**
 * Take the absolute value of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, abs);

/**
 * Square the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, square);

/**
 * Return the square root of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, sqrt);

/**
 * Return the exponential of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, exp);

/**
 * Return the logarithm of the tensor in a specified base.
 *
 * @param float base
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, log);

/**
 * Return the sine of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, sin);

/**
 * Return the cosine of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, cos);

/**
 * Return the tangent of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, tan);

/**
 * Convert angles from radians to degrees.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, degrees);

/**
 * Convert angles from degrees to radians.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, radians);

/**
 * Sum the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, sum);

/**
 * Calculate the product of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, product);

/**
 * Return the minimum of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, min);

/**
 * Return the maximum of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, max);

/**
 * Round the elements in the tensor to a given decimal place.
 *
 * @param int precision
 * @return self
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, round);

/**
 * Round the tensor down to the nearest integer.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, floor);

/**
 * Round the tensor up to the nearest integer.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, ceil);

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
 * Return the element-wise sign indication.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, sign);

/**
 * Negate the tensor i.e take the negative.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, negate);

/**
 * Return the elements of the tensor in an array.
 *
 * @return array
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, asArray);

/**
 * Convert the tensor into a string representation.
 *
 * @return string
 */
ZEPHIR_DOC_METHOD(Tensor_Tensor, __toString);

