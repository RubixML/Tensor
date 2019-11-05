
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Tensor_Arithmetic) {

	ZEPHIR_REGISTER_INTERFACE(Tensor, Arithmetic, tensor, arithmetic, tensor_arithmetic_method_entry);

	zephir_declare_class_constant_double(tensor_arithmetic_ce, SL("M_E"), 2.7182818284590452354);

	return SUCCESS;

}

/**
 * A universal function to multiply this tensor with another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, multiply);

/**
 * A universal function to divide this tensor by another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, divide);

/**
 * A universal function to add this tensor with another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, add);

/**
 * A universal function to subtract this tensor from another tensor
 * element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, subtract);

/**
 * A universal function to raise this tensor to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, pow);

/**
 * A universal function to compute the integer modulus of this tensor
 * and another tensor element-wise.
 *
 * @param mixed b
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, mod);

/**
 * Take the absolute value of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, abs);

/**
 * Square the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, square);

/**
 * Return the square root of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, sqrt);

/**
 * Return the exponential of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, exp);

/**
 * Return the exponential of the tensor minus 1.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, expm1);

/**
 * Return the logarithm of the tensor in a specified base.
 *
 * @param float base
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, log);

/**
 * Return the log of 1 plus the tensor i.e. a transform.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, log1p);

/**
 * Sum the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, sum);

/**
 * Calculate the product of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, product);

/**
 * Return the minimum of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, min);

/**
 * Return the maximum of the tensor.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, max);

/**
 * Round the elements in the tensor to a given decimal place.
 *
 * @param int precision
 * @return self
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, round);

/**
 * Round the tensor down to the nearest integer.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, floor);

/**
 * Round the tensor up to the nearest integer.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, ceil);

/**
 * Return the element-wise sign indication.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, sign);

/**
 * Negate the tensor i.e take the negative.
 *
 * @return mixed
 */
ZEPHIR_DOC_METHOD(Tensor_Arithmetic, negate);

