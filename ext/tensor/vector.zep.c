
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "kernel/array.h"
#include "math.h"
#include "kernel/iterator.h"
#include "kernel/math.h"
#include "kernel/string.h"


/**
 * Vector
 *
 * A one dimensional (rank 1) tensor with integer and/or floating point elements.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Vector) {

	ZEPHIR_REGISTER_CLASS(Tensor, Vector, tensor, vector, tensor_vector_method_entry, 0);

	/**
	 * A 1-d sequential array holding the elements of the vector.
	 *
	 * @var (int|float)[]
	 */
	zend_declare_property_null(tensor_vector_ce, SL("a"), ZEND_ACC_PROTECTED);

	/**
	 * The number of elements in the vector.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_vector_ce, SL("n"), ZEND_ACC_PROTECTED);

	tensor_vector_ce->create_object = zephir_init_properties_Tensor_Vector;

	zend_class_implements(tensor_vector_ce, 1, tensor_tensor_ce);
	return SUCCESS;

}

/**
 * Factory method to build a new vector from an array.
 *
 * @param array a
 * @return self
 */
PHP_METHOD(Tensor_Vector, build) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a_param = NULL, _0;
	zval a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &a_param);

	if (!a_param) {
		ZEPHIR_INIT_VAR(&a);
		array_init(&a);
	} else {
		zephir_get_arrval(&a, a_param);
	}


	object_init_ex(return_value, tensor_vector_ce);
	ZVAL_BOOL(&_0, 1);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 1, &a, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a vector foregoing any validation for quicker instantiation.
 *
 * @param array a
 * @return self
 */
PHP_METHOD(Tensor_Vector, quick) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a_param = NULL, _0;
	zval a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &a_param);

	if (!a_param) {
		ZEPHIR_INIT_VAR(&a);
		array_init(&a);
	} else {
		zephir_get_arrval(&a, a_param);
	}


	object_init_ex(return_value, tensor_vector_ce);
	ZVAL_BOOL(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 1, &a, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a vector of zeros with n elements.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, zeros) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of elements", " must be greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 67);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, 0);
	ZVAL_LONG(&_5, n);
	ZEPHIR_RETURN_CALL_STATIC("fill", NULL, 0, &_4, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a vector of ones with n elements.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, ones) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of elements", " must be greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 84);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_4, 1);
	ZVAL_LONG(&_5, n);
	ZEPHIR_RETURN_CALL_STATIC("fill", NULL, 0, &_4, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Fill a vector with a given value.
 *
 * @param mixed value
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, fill) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *value, value_sub, *n_param = NULL, _1, _9, _10, _11, _2$$3, _3$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &value, &n_param);

	n = zephir_get_intval(n_param);


	_0 = !(Z_TYPE_P(value) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, value);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, value);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Value must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 103);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (n < 1) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", NULL, 2, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "The number of elements", " must be greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/vector.zep", 108);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_9, 0);
	ZVAL_LONG(&_10, n);
	ZEPHIR_CALL_FUNCTION(&_11, "array_fill", NULL, 5, &_9, &_10, value);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_11);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a random uniform vector with values between 0 and 1.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, rand) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4$$4, _5$$4, _6$$4, _8$$4, _9$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of elements", " must be greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 125);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&_4$$4);
		ZEPHIR_GET_CONSTANT(&_4$$4, "PHP_INT_MAX");
		ZVAL_LONG(&_5$$4, 0);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "rand", &_7, 6, &_5$$4, &_4$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZEPHIR_GET_CONSTANT(&_8$$4, "PHP_INT_MAX");
		ZEPHIR_INIT_NVAR(&_9$$4);
		div_function(&_9$$4, &_6$$4, &_8$$4);
		zephir_array_append(&a, &_9$$4, PH_SEPARATE, "tensor/vector.zep", 131);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a standard normally distributed (Gaussian) random vector.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, gaussian) {

	double r1$$4, r2$$4, r$$4, phi$$4;
	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_12 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4$$4, _5$$4, _6$$4, _8$$4, _9$$4, _10$$4, _11$$4, _13$$4, _14$$4, _15$$5, _16$$5, _17$$5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of elements", " must be greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 148);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&_4$$4);
		ZEPHIR_GET_CONSTANT(&_4$$4, "PHP_INT_MAX");
		ZVAL_LONG(&_5$$4, 0);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "rand", &_7, 6, &_5$$4, &_4$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZEPHIR_GET_CONSTANT(&_8$$4, "PHP_INT_MAX");
		ZEPHIR_INIT_NVAR(&_9$$4);
		div_function(&_9$$4, &_6$$4, &_8$$4);
		r1$$4 = zephir_get_numberval(&_9$$4);
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZEPHIR_GET_CONSTANT(&_8$$4, "PHP_INT_MAX");
		ZVAL_LONG(&_5$$4, 0);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "rand", &_7, 6, &_5$$4, &_8$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_10$$4);
		ZEPHIR_GET_CONSTANT(&_10$$4, "PHP_INT_MAX");
		ZEPHIR_INIT_NVAR(&_11$$4);
		div_function(&_11$$4, &_6$$4, &_10$$4);
		r2$$4 = zephir_get_numberval(&_11$$4);
		ZVAL_DOUBLE(&_5$$4, r1$$4);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "log", &_12, 7, &_5$$4);
		zephir_check_call_status();
		ZVAL_DOUBLE(&_5$$4, (-2.0 * zephir_get_numberval(&_6$$4)));
		r$$4 = sqrt((-2.0 * zephir_get_numberval(&_6$$4)));
		phi$$4 = (r2$$4 * 6.28318530718);
		ZVAL_DOUBLE(&_13$$4, phi$$4);
		ZEPHIR_INIT_NVAR(&_10$$4);
		ZVAL_DOUBLE(&_10$$4, (r$$4 * sin(phi$$4)));
		zephir_array_append(&a, &_10$$4, PH_SEPARATE, "tensor/vector.zep", 161);
		ZVAL_DOUBLE(&_14$$4, phi$$4);
		ZEPHIR_INIT_NVAR(&_10$$4);
		ZVAL_DOUBLE(&_10$$4, (r$$4 * cos(phi$$4)));
		zephir_array_append(&a, &_10$$4, PH_SEPARATE, "tensor/vector.zep", 162);
	}
	if (zephir_fast_count_int(&a) > n) {
		ZVAL_LONG(&_15$$5, 0);
		ZVAL_LONG(&_16$$5, n);
		ZEPHIR_CALL_FUNCTION(&_17$$5, "array_slice", NULL, 8, &a, &_15$$5, &_16$$5);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_17$$5);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generate a vector with n elements from a Poisson distribution.
 *
 * @param int n
 * @param float lambda
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, poisson) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	double lambda, p = 0, l;
	zval *n_param = NULL, *lambda_param = NULL, _0, _1, _2$$4, _3$$4, _4$$4, _6$$4, _7$$4, _8$$3;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, k = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &n_param, &lambda_param);

	n = zephir_get_intval(n_param);
	if (!lambda_param) {
		lambda = 1.0;
	} else {
		lambda = zephir_get_doubleval(lambda_param);
	}


	ZVAL_DOUBLE(&_0, -lambda);
	ZEPHIR_CALL_FUNCTION(&_1, "exp", NULL, 9, &_0);
	zephir_check_call_status();
	l = zephir_get_doubleval(&_1);
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		k = 0;
		p = 1.0;
		while (1) {
			if (!(p > l)) {
				break;
			}
			k++;
			ZEPHIR_INIT_NVAR(&_2$$4);
			ZEPHIR_GET_CONSTANT(&_2$$4, "PHP_INT_MAX");
			ZVAL_LONG(&_3$$4, 0);
			ZEPHIR_CALL_FUNCTION(&_4$$4, "rand", &_5, 6, &_3$$4, &_2$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_6$$4);
			ZEPHIR_GET_CONSTANT(&_6$$4, "PHP_INT_MAX");
			ZEPHIR_INIT_NVAR(&_7$$4);
			div_function(&_7$$4, &_4$$4, &_6$$4);
			p *= zephir_get_numberval(&_7$$4);
		}
		ZEPHIR_INIT_NVAR(&_8$$3);
		ZVAL_LONG(&_8$$3, (k - 1));
		zephir_array_append(&a, &_8$$3, PH_SEPARATE, "tensor/vector.zep", 200);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a random uniformly distributed vector with values between -1 and 1.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, uniform) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4$$4, _5$$4, _6$$4, _8$$4, _9$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of elements", " must be greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 217);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&_4$$4);
		ZEPHIR_GET_CONSTANT(&_4$$4, "PHP_INT_MAX");
		zephir_negate(&_4$$4);
		ZEPHIR_INIT_NVAR(&_5$$4);
		ZEPHIR_GET_CONSTANT(&_5$$4, "PHP_INT_MAX");
		ZEPHIR_CALL_FUNCTION(&_6$$4, "rand", &_7, 6, &_4$$4, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZEPHIR_GET_CONSTANT(&_8$$4, "PHP_INT_MAX");
		ZEPHIR_INIT_NVAR(&_9$$4);
		div_function(&_9$$4, &_6$$4, &_8$$4);
		zephir_array_append(&a, &_9$$4, PH_SEPARATE, "tensor/vector.zep", 224);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return evenly spaced values within a given interval.
 *
 * @param mixed start
 * @param mixed end
 * @param mixed interval
 * @return self
 */
PHP_METHOD(Tensor_Vector, range) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *start, start_sub, *end, end_sub, *interval = NULL, interval_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&start_sub);
	ZVAL_UNDEF(&end_sub);
	ZVAL_UNDEF(&interval_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &start, &end, &interval);

	if (!interval) {
		interval = &interval_sub;
		ZEPHIR_INIT_VAR(interval);
		ZVAL_LONG(interval, 1);
	}


	ZEPHIR_CALL_FUNCTION(&_0, "range", NULL, 10, start, end, interval);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return evenly spaced numbers over a specified interval.
 *
 * @param float start
 * @param float end
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, linspace) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *start_param = NULL, *end_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, range, _4, _5, _6;
	double start, end, interval;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&range);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &start_param, &end_param, &n_param);

	start = zephir_get_doubleval(start_param);
	end = zephir_get_doubleval(end_param);
	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of elements", " must be greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 256);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_DOUBLE(&_4, (end - start));
	ZEPHIR_CALL_FUNCTION(&range, "abs", NULL, 11, &_4);
	zephir_check_call_status();
	interval = ((zephir_safe_div_zval_long(&range, ((n - 1)))) - ((0.00000001 * zephir_get_numberval(&range))));
	ZVAL_DOUBLE(&_4, start);
	ZVAL_DOUBLE(&_5, end);
	ZVAL_DOUBLE(&_6, interval);
	ZEPHIR_RETURN_CALL_STATIC("range", NULL, 0, &_4, &_5, &_6);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elementwise maximum of two vectors.
 *
 * @param \Tensor\Vector a
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, maximum) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *b, b_sub, _0, _1, _8, _9, _10, _11, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &b);



	ZEPHIR_CALL_METHOD(&_0, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 279);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "max");
	ZEPHIR_CALL_FUNCTION(&_11, "array_map", NULL, 12, &_10, &_8, &_9);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_11);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elementwise minimum of two vectors.
 *
 * @param \Tensor\Vector a
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, minimum) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *b, b_sub, _0, _1, _8, _9, _10, _11, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &b);



	ZEPHIR_CALL_METHOD(&_0, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 298);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "min");
	ZEPHIR_CALL_FUNCTION(&_11, "array_map", NULL, 12, &_10, &_8, &_9);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_11);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param array a
 * @param bool validate
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Vector, __construct) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool validate, _3$$4, _10$$6;
	zval *a_param = NULL, *validate_param = NULL, value, _15, _0$$3, *_1$$3, _2$$3, _4$$4, _6$$5, _7$$5, _8$$5, _11$$6, _12$$7, _13$$7, _14$$7;
	zval a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &a_param, &validate_param);

	if (!a_param) {
		ZEPHIR_INIT_VAR(&a);
		array_init(&a);
	} else {
		zephir_get_arrval(&a, a_param);
	}
	if (!validate_param) {
		validate = 1;
	} else {
		validate = zephir_get_boolval(validate_param);
	}


	if (validate) {
		ZEPHIR_CALL_FUNCTION(&_0$$3, "array_values", NULL, 13, &a);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_0$$3);
		zephir_is_iterable(&a, 0, "tensor/vector.zep", 323);
		if (Z_TYPE_P(&a) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&a), _1$$3)
			{
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _1$$3);
				_3$$4 = !(Z_TYPE_P(&value) == IS_LONG);
				if (_3$$4) {
					ZEPHIR_CALL_FUNCTION(&_4$$4, "is_float", &_5, 4, &value);
					zephir_check_call_status();
					_3$$4 = !zephir_is_true(&_4$$4);
				}
				if (UNEXPECTED(_3$$4)) {
					ZEPHIR_INIT_NVAR(&_6$$5);
					object_init_ex(&_6$$5, spl_ce_InvalidArgumentException);
					ZEPHIR_INIT_NVAR(&_7$$5);
					zephir_gettype(&_7$$5, &value);
					ZEPHIR_INIT_NVAR(&_8$$5);
					ZEPHIR_CONCAT_SSVS(&_8$$5, "Element must be", " an integer or floating point number, ", &_7$$5, " given.");
					ZEPHIR_CALL_METHOD(NULL, &_6$$5, "__construct", &_9, 3, &_8$$5);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_6$$5, "tensor/vector.zep", 320);
					ZEPHIR_MM_RESTORE();
					return;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &a, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_2$$3, &a, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_2$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&value, &a, "current", NULL, 0);
				zephir_check_call_status();
					_10$$6 = !(Z_TYPE_P(&value) == IS_LONG);
					if (_10$$6) {
						ZEPHIR_CALL_FUNCTION(&_11$$6, "is_float", &_5, 4, &value);
						zephir_check_call_status();
						_10$$6 = !zephir_is_true(&_11$$6);
					}
					if (UNEXPECTED(_10$$6)) {
						ZEPHIR_INIT_NVAR(&_12$$7);
						object_init_ex(&_12$$7, spl_ce_InvalidArgumentException);
						ZEPHIR_INIT_NVAR(&_13$$7);
						zephir_gettype(&_13$$7, &value);
						ZEPHIR_INIT_NVAR(&_14$$7);
						ZEPHIR_CONCAT_SSVS(&_14$$7, "Element must be", " an integer or floating point number, ", &_13$$7, " given.");
						ZEPHIR_CALL_METHOD(NULL, &_12$$7, "__construct", &_9, 3, &_14$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_12$$7, "tensor/vector.zep", 320);
						ZEPHIR_MM_RESTORE();
						return;
					}
				ZEPHIR_CALL_METHOD(NULL, &a, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&value);
	}
	zephir_update_property_zval(this_ptr, SL("a"), &a);
	ZEPHIR_INIT_ZVAL_NREF(_15);
	ZVAL_LONG(&_15, zephir_fast_count_int(&a));
	zephir_update_property_zval(this_ptr, SL("n"), &_15);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return a tuple with the dimensionality of the tensor.
 *
 * @return int[]
 */
PHP_METHOD(Tensor_Vector, shape) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_create_array(return_value, 1, 0);
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();

}

/**
 * Return the shape of the tensor as a string.
 *
 * @return string
 */
PHP_METHOD(Tensor_Vector, shapeString) {

	zval _1;
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC);
	zephir_get_strval(&_1, &_0);
	RETURN_CTOR(&_1);

}

/**
 * Return the number of elements in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, size) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "n");

}

/**
 * Return the number of rows in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, m) {

	zval *this_ptr = getThis();


	RETURN_LONG(1);

}

/**
 * Return the number of columns in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, n) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "n");

}

/**
 * Return the vector as an array.
 *
 * @return array
 */
PHP_METHOD(Tensor_Vector, asArray) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

/**
 * Return this vector as a row matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, asRowMatrix) {

	zval _2;
	zval _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 1, 0);
	ZEPHIR_OBS_VAR(&_2);
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC);
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_0, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return this vector as a column matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, asColumnMatrix) {

	zval b, _3$$3, _4$$4;
	zval valueA, _0, *_1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 414);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			ZEPHIR_INIT_NVAR(&_3$$3);
			zephir_create_array(&_3$$3, 1, 0);
			zephir_array_fast_append(&_3$$3, &valueA);
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/vector.zep", 411);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_4$$4);
				zephir_create_array(&_4$$4, 1, 0);
				zephir_array_fast_append(&_4$$4, &valueA);
				zephir_array_append(&b, &_4$$4, PH_SEPARATE, "tensor/vector.zep", 411);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_5, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a matrix in the shape specified.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, reshape) {

	zval _2$$3;
	zval b, rowB$$5;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zval *m_param = NULL, *n_param = NULL, _3, _1$$3, _4$$4, _5$$4, _6$$4, _7$$4, _8$$6, _9$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, nHat, k;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB$$5);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	_0 = m < 0;
	if (!(_0)) {
		_0 = n < 0;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "The number of rows", " and/or columns cannot be less than 0.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 429);
		ZEPHIR_MM_RESTORE();
		return;
	}
	nHat = (m * n);
	zephir_read_property(&_3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_LONG_IDENTICAL(&_3, nHat)) {
		ZEPHIR_INIT_VAR(&_4$$4);
		object_init_ex(&_4$$4, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_5$$4, nHat);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "strval", NULL, 2, &_5$$4);
		zephir_check_call_status();
		zephir_read_property(&_5$$4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_VSSVS(&_7$$4, &_6$$4, " elements", " are needed but vector only has ", &_5$$4, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 3, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$4, "tensor/vector.zep", 436);
		ZEPHIR_MM_RESTORE();
		return;
	}
	k = 0;
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	while (1) {
		if (!(zephir_fast_count_int(&b) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowB$$5);
		array_init(&rowB$$5);
		while (1) {
			if (!(zephir_fast_count_int(&rowB$$5) < n)) {
				break;
			}
			zephir_read_property(&_8$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_long(&_9$$6, &_8$$6, k, PH_NOISY | PH_READONLY, "tensor/vector.zep", 447);
			zephir_array_append(&rowB$$5, &_9$$6, PH_SEPARATE, "tensor/vector.zep", 447);
			k++;
		}
		zephir_array_append(&b, &rowB$$5, PH_SEPARATE, "tensor/vector.zep", 452);
	}
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_10, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Transpose the vector i.e. rotate it.
 *
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, transpose) {

	zval _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the index of the minimum element in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, argmin) {

	zval _0, _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_1, "min", NULL, 14, &_0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_3, "array_search", NULL, 15, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM_LONG(zephir_get_intval(&_3));

}

/**
 * Return the index of the maximum element in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, argmax) {

	zval _0, _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_1, "max", NULL, 16, &_0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_3, "array_search", NULL, 15, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM_LONG(zephir_get_intval(&_3));

}

/**
 * Map a function over the elements in the vector and return a new
 * vector.
 *
 * @param callable callback
 * @return self
 */
PHP_METHOD(Tensor_Vector, map) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback, callback_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_1, "array_map", NULL, 12, callback, &_0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Reduce the vector down to a scalar.
 *
 * @param callable callback
 * @param mixed initial
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, reduce) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback, callback_sub, *initial = NULL, initial_sub, _1, _5, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&initial_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &callback, &initial);

	if (!initial) {
		initial = &initial_sub;
		ZEPHIR_INIT_VAR(initial);
		ZVAL_LONG(initial, 0);
	}


	_0 = !(Z_TYPE_P(initial) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, initial);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, initial);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Initial value must", " be an integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 513);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_reduce", NULL, 17, &_5, callback, initial);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the dot product of this vector and another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, dot) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	double sigma;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires", &_4$$3, " elements but vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 531);
		ZEPHIR_MM_RESTORE();
		return;
	}
	sigma = 0.0;
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 542);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 539);
			ZEPHIR_INIT_NVAR(&_15$$4);
			mul_function(&_15$$4, &_14$$4, &valueB);
			sigma += zephir_get_numberval(&_15$$4);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_16$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_17$$5, &_16$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 539);
				ZEPHIR_INIT_NVAR(&_18$$5);
				mul_function(&_18$$5, &_17$$5, &valueB);
				sigma += zephir_get_numberval(&_18$$5);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	RETURN_MM_DOUBLE(sigma);

}

/**
 * Convolve this vector with another vector.
 *
 * @param \Tensor\Vector b
 * @param int stride
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, convolve) {

	zend_string *_15$$5;
	zend_ulong _14$$5;
	double sigma$$5;
	zval _3$$3;
	zend_bool _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long stride, ZEPHIR_LAST_CALL_STATUS, i = 0, _10, _11, k$$6, k$$8;
	zval *b, b_sub, *stride_param = NULL, _0, _1, j, valueA, valueB, bHat, _8, _2$$3, _4$$4, _5$$4, _6$$4, _7$$4, *_12$$5, _13$$5, _20$$5, _16$$6, _17$$7, _18$$8, _19$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &b, &stride_param);

	if (!stride_param) {
		stride = 1;
	} else {
		stride = zephir_get_intval(stride_param);
	}


	ZEPHIR_CALL_METHOD(&_0, b, "size", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_GT(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SS(&_3$$3, "Vector B cannot be", " larger than Vector A.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 557);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (stride < 1) {
		ZEPHIR_INIT_VAR(&_4$$4);
		object_init_ex(&_4$$4, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_5$$4, stride);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "strval", NULL, 2, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_SSVS(&_7$$4, "Stride cannot be", " less than 1, ", &_6$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 3, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$4, "tensor/vector.zep", 562);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	_11 = (zephir_get_numberval(&_8) - 1);
	_10 = 0;
	_9 = 0;
	if (_10 <= _11) {
		while (1) {
			if (_9) {
				_10 += stride;
				if (!(_10 <= _11)) {
					break;
				}
			} else {
				_9 = 1;
			}
			i = _10;
			sigma$$5 = (double) (0);
			zephir_is_iterable(&bHat, 0, "tensor/vector.zep", 583);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _14$$5, _15$$5, _12$$5)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$5 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$5);
					} else {
						ZVAL_LONG(&j, _14$$5);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _12$$5);
					k$$6 = (i - zephir_get_intval(&j));
					ZEPHIR_OBS_NVAR(&valueA);
					zephir_read_property(&_16$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					if (zephir_array_isset_long_fetch(&valueA, &_16$$6, k$$6, 0)) {
						ZEPHIR_INIT_NVAR(&_17$$7);
						mul_function(&_17$$7, &valueA, &valueB);
						sigma$$5 += zephir_get_numberval(&_17$$7);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$5, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						k$$8 = (i - zephir_get_intval(&j));
						ZEPHIR_OBS_NVAR(&valueA);
						zephir_read_property(&_18$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						if (zephir_array_isset_long_fetch(&valueA, &_18$$8, k$$8, 0)) {
							ZEPHIR_INIT_NVAR(&_19$$9);
							mul_function(&_19$$9, &valueA, &valueB);
							sigma$$5 += zephir_get_numberval(&_19$$9);
						}
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			ZEPHIR_INIT_NVAR(&_20$$5);
			ZVAL_DOUBLE(&_20$$5, sigma$$5);
			zephir_array_append(&c, &_20$$5, PH_SEPARATE, "tensor/vector.zep", 583);
		}
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the vector-matrix product of this vector and matrix b.
 *
 * @param \Tensor\Matrix b
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, matmul) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, this_ptr, "asrowmatrix", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "matmul", NULL, 0, b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the inner product of two vectors.
 *
 * @param \Tensor\Vector b
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, inner) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dot", NULL, 0, b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the outer product of this and another vector.
 *
 * @param \Tensor\Vector b
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, outer) {

	zend_object_iterator *_3$$3, *_5$$5;
	zval c, rowC$$3, rowC$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, j, valueA, valueB, n, _0, *_1, _2, _4$$4, _6$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$3);
	ZVAL_UNDEF(&rowC$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&n, b, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 635);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			ZEPHIR_INIT_NVAR(&rowC$$3);
			array_init(&rowC$$3);
			_3$$3 = zephir_get_iterator(b);
			_3$$3->funcs->rewind(_3$$3);
			for (;_3$$3->funcs->valid(_3$$3) == SUCCESS && !EG(exception); _3$$3->funcs->move_forward(_3$$3)) {
				ZEPHIR_GET_IMKEY(j, _3$$3);
				{
					ZEPHIR_ITERATOR_COPY(&valueB, _3$$3);
				}
				ZEPHIR_INIT_NVAR(&_4$$4);
				mul_function(&_4$$4, &valueA, &valueB);
				zephir_array_append(&rowC$$3, &_4$$4, PH_SEPARATE, "tensor/vector.zep", 629);
			}
			zend_iterator_dtor(_3$$3);
			zephir_array_append(&c, &rowC$$3, PH_SEPARATE, "tensor/vector.zep", 632);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$5);
				array_init(&rowC$$5);
				_5$$5 = zephir_get_iterator(b);
				_5$$5->funcs->rewind(_5$$5);
				for (;_5$$5->funcs->valid(_5$$5) == SUCCESS && !EG(exception); _5$$5->funcs->move_forward(_5$$5)) {
					ZEPHIR_GET_IMKEY(j, _5$$5);
					{
						ZEPHIR_ITERATOR_COPY(&valueB, _5$$5);
					}
					ZEPHIR_INIT_NVAR(&_6$$6);
					mul_function(&_6$$6, &valueA, &valueB);
					zephir_array_append(&rowC$$5, &_6$$6, PH_SEPARATE, "tensor/vector.zep", 629);
				}
				zend_iterator_dtor(_5$$5);
				zephir_array_append(&c, &rowC$$5, PH_SEPARATE, "tensor/vector.zep", 632);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_7, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the cross product between two 3 dimensional vectors.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, cross) {

	zval _4$$3;
	zval c;
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _3$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	_1 = !ZEPHIR_IS_LONG_IDENTICAL(&_0, 3);
	if (!(_1)) {
		ZEPHIR_CALL_METHOD(&_2, b, "size", NULL, 0);
		zephir_check_call_status();
		_1 = !ZEPHIR_IS_LONG_IDENTICAL(&_2, 3);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_3$$3);
		object_init_ex(&_3$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SS(&_4$$3, "Cross product is", " only defined for vectors of 3 dimensions.");
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$3, "tensor/vector.zep", 649);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_5, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 654);
	zephir_array_fetch_long(&_7, b, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 654);
	ZEPHIR_INIT_VAR(&_8);
	mul_function(&_8, &_6, &_7);
	zephir_read_property(&_9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_9, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 654);
	zephir_array_fetch_long(&_7, b, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 654);
	ZEPHIR_INIT_VAR(&_10);
	mul_function(&_10, &_6, &_7);
	ZEPHIR_INIT_VAR(&_11);
	zephir_sub_function(&_11, &_8, &_10);
	zephir_array_append(&c, &_11, PH_SEPARATE, "tensor/vector.zep", 654);
	zephir_read_property(&_12, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_12, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 655);
	zephir_array_fetch_long(&_7, b, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 655);
	ZEPHIR_INIT_NVAR(&_8);
	mul_function(&_8, &_6, &_7);
	zephir_read_property(&_13, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_13, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 655);
	zephir_array_fetch_long(&_7, b, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 655);
	ZEPHIR_INIT_NVAR(&_10);
	mul_function(&_10, &_6, &_7);
	ZEPHIR_INIT_VAR(&_14);
	zephir_sub_function(&_14, &_8, &_10);
	zephir_array_append(&c, &_14, PH_SEPARATE, "tensor/vector.zep", 655);
	zephir_read_property(&_15, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_15, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 656);
	zephir_array_fetch_long(&_7, b, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 656);
	ZEPHIR_INIT_NVAR(&_8);
	mul_function(&_8, &_6, &_7);
	zephir_read_property(&_16, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_16, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 656);
	zephir_array_fetch_long(&_7, b, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 656);
	ZEPHIR_INIT_NVAR(&_10);
	mul_function(&_10, &_6, &_7);
	ZEPHIR_INIT_VAR(&_17);
	zephir_sub_function(&_17, &_8, &_10);
	zephir_array_append(&c, &_17, PH_SEPARATE, "tensor/vector.zep", 656);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Project this vector on another vector.
 *
 * @param \Tensor\Vector b
 * @return self
 */
PHP_METHOD(Tensor_Vector, project) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _2, _3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, this_ptr, "dot", NULL, 0, b);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CALL_METHOD(&_2, b, "l2norm", NULL, 0);
	zephir_check_call_status();
	ZVAL_LONG(&_3, 2);
	zephir_pow_function(&_1, &_2, &_3);
	ZEPHIR_INIT_VAR(&_4);
	div_function(&_4, &_0, &_1);
	ZEPHIR_RETURN_CALL_METHOD(b, "multiply", NULL, 0, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the L1 or Manhattan norm of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, l1Norm) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "abs", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "sum", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the L2 or Euclidean norm of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, l2Norm) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "sum", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_DOUBLE(zephir_sqrt(&_1));

}

/**
 * Calculate the p-norm of the vector.
 *
 * @param float p
 * @throws \InvalidArgumentException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, pNorm) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *p_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5, _6, _7;
	double p;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &p_param);

	if (!p_param) {
		p = 3.0;
	} else {
		p = zephir_get_doubleval(p_param);
	}


	if (p <= 0.0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_DOUBLE(&_1$$3, p);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "P must be greater", " than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 703);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "abs", NULL, 0);
	zephir_check_call_status();
	ZVAL_DOUBLE(&_6, p);
	ZEPHIR_CALL_METHOD(&_5, &_4, "powscalar", NULL, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, &_5, "sum", NULL, 0);
	zephir_check_call_status();
	ZVAL_DOUBLE(&_6, zephir_safe_div_double_double(1.0, p));
	zephir_pow_function(return_value, &_7, &_6);
	RETURN_MM();

}

/**
 * Calculate the max norm of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, maxNorm) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "abs", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "max", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * A universal function to multiply this vector with another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, multiply) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot multiply vector", " by a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 744);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to divide this vector by another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, divide) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividevector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividematrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividescalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot divide vector", " by a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 772);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to add this vector with another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, add) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot add vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 800);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to subtract this vector from another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, subtract) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SVS(&_5, "Cannot subtract a ", &_4, " from vector.");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 828);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to raise this vector to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, pow) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot raise vector", " to a power of a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 856);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the modulus of this vector and
 * another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, mod) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot mod vector", " with a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 884);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the equality comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, equal) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 912);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the not equal comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, notEqual) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 940);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, greater) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatervector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatermatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 968);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than or equal to
 * comparison of this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, greaterEqual) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 996);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, less) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 1024);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than or equal to
 * comparison of this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, lessEqual) {

	zend_bool _0$$3, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	if (Z_TYPE_P(b) == IS_OBJECT) {
		do {
			_0$$3 = 1;
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
		} while(0);

	}
	_1 = Z_TYPE_P(b) == IS_LONG;
	if (!(_1)) {
		ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_1 = zephir_is_true(&_2);
	}
	if (_1) {
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, spl_ce_InvalidArgumentException);
	ZEPHIR_INIT_VAR(&_4);
	zephir_gettype(&_4, b);
	ZEPHIR_INIT_VAR(&_5);
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare vector", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/vector.zep", 1052);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Return the reciprocal of the vector element-wise.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, reciprocal) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_STATIC(&_0, "ones", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "dividevector", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the absolute value of the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, abs) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "abs");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Square the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, square) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZVAL_LONG(&_0, 2);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powscalar", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Take the square root of the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, sqrt) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "sqrt");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Exponentiate each element in the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, exp) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "exp");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the exponential of the vector minus 1.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, expm1) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "expm1");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Take the log to the given base of each element in the vector.
 *
 * @param float base
 * @return self
 */
PHP_METHOD(Tensor_Vector, log) {

	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *base_param = NULL, valueA, _0, *_1, _2, _3$$3, _4$$3, _6$$4, _7$$4;
	double base;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &base_param);

	if (!base_param) {
		base = 2.7182818284590452354;
	} else {
		base = zephir_get_doubleval(base_param);
	}


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1132);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			ZVAL_DOUBLE(&_3$$3, base);
			ZEPHIR_CALL_FUNCTION(&_4$$3, "log", &_5, 7, &valueA, &_3$$3);
			zephir_check_call_status();
			zephir_array_append(&b, &_4$$3, PH_SEPARATE, "tensor/vector.zep", 1129);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZVAL_DOUBLE(&_6$$4, base);
				ZEPHIR_CALL_FUNCTION(&_7$$4, "log", &_5, 7, &valueA, &_6$$4);
				zephir_check_call_status();
				zephir_array_append(&b, &_7$$4, PH_SEPARATE, "tensor/vector.zep", 1129);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the log of 1 plus the tensor i.e. a transform.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, log1p) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "log1p");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the sine of this vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, sin) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "sin");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the arc sine of the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, asin) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "asin");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the cosine of this vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, cos) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "cos");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the arc cosine of the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, acos) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "acos");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the tangent of this vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, tan) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "tan");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the arc tangent of the vector.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, atan) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "atan");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convert angles from radians to degrees.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, rad2deg) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "rad2deg");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convert angles from degrees to radians.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, deg2rad) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "deg2rad");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * The sum of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, sum) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_sum", NULL, 18, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the product of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, product) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_product", NULL, 19, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the minimum element in the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, min) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("min", NULL, 14, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the maximum element in the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, max) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("max", NULL, 16, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the mean of the vector.
 *
 * @throws \RuntimeException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, mean) {

	zval _2$$3;
	zval _0, _3, _4, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_0, 1)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Mean is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 20, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1275);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	div_function(return_value, &_3, &_4);
	RETURN_MM();

}

/**
 * Return the median of the vector.
 *
 * @throws \RuntimeException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, median) {

	zval _2$$3;
	zval _0, median, mid, _3, _4, a, _1$$3, _5$$5, _6$$5, _7$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&median);
	ZVAL_UNDEF(&mid);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_0, 1)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Median is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 20, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1291);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_4, 2);
	ZEPHIR_CALL_FUNCTION(&mid, "intdiv", NULL, 21, &_3, &_4);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&a, &_4);
	ZEPHIR_MAKE_REF(&a);
	ZEPHIR_CALL_FUNCTION(NULL, "sort", NULL, 22, &a);
	ZEPHIR_UNREF(&a);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (zephir_safe_mod_zval_long(&_4, 2) == 1) {
		ZEPHIR_OBS_VAR(&median);
		zephir_array_fetch(&median, &a, &mid, PH_NOISY, "tensor/vector.zep", 1303);
	} else {
		zephir_array_fetch_long(&_5$$5, &a, (zephir_get_numberval(&mid) - 1), PH_NOISY | PH_READONLY, "tensor/vector.zep", 1305);
		zephir_array_fetch(&_6$$5, &a, &mid, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1305);
		ZEPHIR_INIT_VAR(&_7$$5);
		zephir_add_function(&_7$$5, &_5$$5, &_6$$5);
		ZEPHIR_INIT_NVAR(&median);
		ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_7$$5, 2.0));
	}
	RETURN_CCTOR(&median);

}

/**
 * Return the pth percentile of the vector.
 *
 * @param float p
 * @throws \InvalidArgumentException
 * @throws \RuntimeException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, percentile) {

	zval _7$$4;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, xHat;
	zval *p_param = NULL, _5, a, _8, t, _9, _10, _1$$3, _2$$3, _3$$3, _4$$3, _6$$4;
	double p, x, remainder;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &p_param);

	p = zephir_get_doubleval(p_param);


	_0 = p < 0.0;
	if (!(_0)) {
		_0 = p > 100.0;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZVAL_DOUBLE(&_2$$3, p);
		ZEPHIR_CALL_FUNCTION(&_3$$3, "strval", NULL, 2, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "P must be between", " 0 and 100, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1323);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_5, 1)) {
		ZEPHIR_INIT_VAR(&_6$$4);
		object_init_ex(&_6$$4, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_SS(&_7$$4, "Percentile is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_6$$4, "__construct", NULL, 20, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$4, "tensor/vector.zep", 1328);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&a, &_8);
	ZEPHIR_MAKE_REF(&a);
	ZEPHIR_CALL_FUNCTION(NULL, "sort", NULL, 22, &a);
	ZEPHIR_UNREF(&a);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	x = (((zephir_safe_div_double_long(p, 100)) * (double) (((zephir_get_numberval(&_8) - 1)))) + (double) (1));
	xHat = (int) (x);
	remainder = (x -  (double) xHat);
	ZEPHIR_OBS_VAR(&t);
	zephir_array_fetch_long(&t, &a, (xHat - 1), PH_NOISY, "tensor/vector.zep", 1341);
	zephir_array_fetch_long(&_9, &a, xHat, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1343);
	ZEPHIR_INIT_VAR(&_10);
	zephir_sub_function(&_10, &_9, &t);
	RETURN_MM_DOUBLE((zephir_get_doubleval(&t) + (double) ((remainder * zephir_get_numberval(&_10)))));

}

/**
 * Return the variance of the vector.
 *
 * @param mixed mean
 * @throws \InvalidArgumentException
 * @throws \RuntimeException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, variance) {

	zval _7$$5;
	zend_bool _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *mean = NULL, mean_sub, __$null, _1$$3, _2$$4, _3$$4, _4$$4, _5, ssd, _8, _9, _10, _6$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&mean_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&ssd);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &mean);

	if (!mean) {
		mean = &mean_sub;
		ZEPHIR_CPY_WRT(mean, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(mean);
	}


	if (!(Z_TYPE_P(mean) == IS_NULL)) {
		_0$$3 = !(Z_TYPE_P(mean) == IS_LONG);
		if (_0$$3) {
			ZEPHIR_CALL_FUNCTION(&_1$$3, "is_float", NULL, 4, mean);
			zephir_check_call_status();
			_0$$3 = !zephir_is_true(&_1$$3);
		}
		if (_0$$3) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, spl_ce_InvalidArgumentException);
			ZEPHIR_INIT_VAR(&_3$$4);
			zephir_gettype(&_3$$4, mean);
			ZEPHIR_INIT_VAR(&_4$$4);
			ZEPHIR_CONCAT_SSVS(&_4$$4, "Mean scalar must be", " an integer or floating point number ", &_3$$4, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 3, &_4$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$4, "tensor/vector.zep", 1360);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	zephir_read_property(&_5, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_5, 1)) {
		ZEPHIR_INIT_VAR(&_6$$5);
		object_init_ex(&_6$$5, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_7$$5);
		ZEPHIR_CONCAT_SS(&_7$$5, "Variance is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_6$$5, "__construct", NULL, 20, &_7$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$5, "tensor/vector.zep", 1366);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (Z_TYPE_P(mean) == IS_NULL) {
		ZEPHIR_CALL_METHOD(mean, this_ptr, "mean", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_8, this_ptr, "subtract", NULL, 0, mean);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, &_8, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&ssd, &_9, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_10, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	div_function(return_value, &ssd, &_10);
	RETURN_MM();

}

/**
 * Round the elements in the matrix to a given decimal place.
 *
 * @param int precision
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, round) {

	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *precision_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, valueA, _4, *_5, _6, _7$$4, _8$$4, _9$$5, _10$$5;
	zend_long precision, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &precision_param);

	if (!precision_param) {
		precision = 0;
	} else {
		precision = zephir_get_intval(precision_param);
	}


	if (precision < 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, precision);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Decimal precision cannot", " be less than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 1391);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_4, 0, "tensor/vector.zep", 1402);
	if (Z_TYPE_P(&_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4), _5)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _5);
			ZEPHIR_INIT_NVAR(&_7$$4);
			ZVAL_LONG(&_8$$4, precision);
			zephir_round(&_7$$4, &valueA, &_8$$4, NULL);
			zephir_array_append(&b, &_7$$4, PH_SEPARATE, "tensor/vector.zep", 1399);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_4, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_6, &_4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				ZVAL_LONG(&_10$$5, precision);
				zephir_round(&_9$$5, &valueA, &_10$$5, NULL);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 1399);
			ZEPHIR_CALL_METHOD(NULL, &_4, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Round the elements in the vector down to the nearest integer.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, floor) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "floor");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Round the elements in the vector up to the nearest integer.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, ceil) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	ZVAL_STRING(&_0, "ceil");
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Clip the elements in the vector to be between given minimum and maximum
 * and return a new vector.
 *
 * @param float min
 * @param float max
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, clip) {

	zval b;
	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *min_param = NULL, *max_param = NULL, _0$$3, valueA, _2, *_3, _4, _5$$5, _6$$6, _7$$8, _8$$9;
	double min, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$8);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &min_param, &max_param);

	min = zephir_get_doubleval(min_param);
	max = zephir_get_doubleval(max_param);


	if (min > max) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SS(&_1$$3, "Minimum cannot be", " greater than maximum.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 1438);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/vector.zep", 1461);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _3);
			if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
				ZEPHIR_INIT_NVAR(&_5$$5);
				ZVAL_DOUBLE(&_5$$5, max);
				zephir_array_append(&b, &_5$$5, PH_SEPARATE, "tensor/vector.zep", 1447);
				continue;
			}
			if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
				ZEPHIR_INIT_NVAR(&_6$$6);
				ZVAL_DOUBLE(&_6$$6, min);
				zephir_array_append(&b, &_6$$6, PH_SEPARATE, "tensor/vector.zep", 1453);
				continue;
			}
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1458);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_2, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_4, &_2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_4)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_2, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
					ZEPHIR_INIT_NVAR(&_7$$8);
					ZVAL_DOUBLE(&_7$$8, max);
					zephir_array_append(&b, &_7$$8, PH_SEPARATE, "tensor/vector.zep", 1447);
					continue;
				}
				if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
					ZEPHIR_INIT_NVAR(&_8$$9);
					ZVAL_DOUBLE(&_8$$9, min);
					zephir_array_append(&b, &_8$$9, PH_SEPARATE, "tensor/vector.zep", 1453);
					continue;
				}
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1458);
			ZEPHIR_CALL_METHOD(NULL, &_2, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Clip the tensor to be lower bounded by a given minimum.
 *
 * @param float min
 * @return self
 */
PHP_METHOD(Tensor_Vector, clipLower) {

	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *min_param = NULL, valueA, _0, *_1, _2, _3$$4, _4$$6;
	double min;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &min_param);

	min = zephir_get_doubleval(min_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1486);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_DOUBLE(&_3$$4, min);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1478);
				continue;
			}
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1483);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
					ZEPHIR_INIT_NVAR(&_4$$6);
					ZVAL_DOUBLE(&_4$$6, min);
					zephir_array_append(&b, &_4$$6, PH_SEPARATE, "tensor/vector.zep", 1478);
					continue;
				}
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1483);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Clip the tensor to be upper bounded by a given maximum.
 *
 * @param float max
 * @return self
 */
PHP_METHOD(Tensor_Vector, clipUpper) {

	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *max_param = NULL, valueA, _0, *_1, _2, _3$$4, _4$$6;
	double max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &max_param);

	max = zephir_get_doubleval(max_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1511);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_DOUBLE(&_3$$4, max);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1503);
				continue;
			}
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1508);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
					ZEPHIR_INIT_NVAR(&_4$$6);
					ZVAL_DOUBLE(&_4$$6, max);
					zephir_array_append(&b, &_4$$6, PH_SEPARATE, "tensor/vector.zep", 1503);
					continue;
				}
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1508);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise sign indication.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, sign) {

	zval b;
	zval valueA, _0, *_1, _2, _3$$4, _4$$5, _5$$6, _6$$8, _7$$9, _8$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$8);
	ZVAL_UNDEF(&_7$$9);
	ZVAL_UNDEF(&_8$$10);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1535);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			if (ZEPHIR_GT_LONG(&valueA, 0)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_LONG(&_3$$4, 1);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1527);
			} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZVAL_LONG(&_4$$5, -1);
				zephir_array_append(&b, &_4$$5, PH_SEPARATE, "tensor/vector.zep", 1529);
			} else {
				ZEPHIR_INIT_NVAR(&_5$$6);
				ZVAL_LONG(&_5$$6, 0);
				zephir_array_append(&b, &_5$$6, PH_SEPARATE, "tensor/vector.zep", 1531);
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_GT_LONG(&valueA, 0)) {
					ZEPHIR_INIT_NVAR(&_6$$8);
					ZVAL_LONG(&_6$$8, 1);
					zephir_array_append(&b, &_6$$8, PH_SEPARATE, "tensor/vector.zep", 1527);
				} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
					ZEPHIR_INIT_NVAR(&_7$$9);
					ZVAL_LONG(&_7$$9, -1);
					zephir_array_append(&b, &_7$$9, PH_SEPARATE, "tensor/vector.zep", 1529);
				} else {
					ZEPHIR_INIT_NVAR(&_8$$10);
					ZVAL_LONG(&_8$$10, 0);
					zephir_array_append(&b, &_8$$10, PH_SEPARATE, "tensor/vector.zep", 1531);
				}
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Negate the vector i.e take the negative of each value elementwise.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, negate) {

	zval b;
	zval valueA, _0, *_1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1553);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			zephir_negate(&valueA);
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1550);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_0, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_2, &_0, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_2)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				zephir_negate(&valueA);
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1550);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, multiplyMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1568);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1585);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1582);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1579);
					ZEPHIR_INIT_NVAR(&_17$$5);
					mul_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/vector.zep", 1579);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1579);
						ZEPHIR_INIT_NVAR(&_19$$6);
						mul_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1579);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1582);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1582);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1579);
						ZEPHIR_INIT_NVAR(&_26$$8);
						mul_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1579);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1579);
							ZEPHIR_INIT_NVAR(&_28$$9);
							mul_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/vector.zep", 1579);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1582);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, divideMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1600);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1617);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1614);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1611);
					ZEPHIR_INIT_NVAR(&_17$$5);
					div_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/vector.zep", 1611);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1611);
						ZEPHIR_INIT_NVAR(&_19$$6);
						div_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1611);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1614);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1614);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1611);
						ZEPHIR_INIT_NVAR(&_26$$8);
						div_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1611);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1611);
							ZEPHIR_INIT_NVAR(&_28$$9);
							div_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/vector.zep", 1611);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1614);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this vector to a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, addMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1632);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1649);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1646);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1643);
					ZEPHIR_INIT_NVAR(&_17$$5);
					zephir_add_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/vector.zep", 1643);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1643);
						ZEPHIR_INIT_NVAR(&_19$$6);
						zephir_add_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1643);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1646);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1646);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1643);
						ZEPHIR_INIT_NVAR(&_26$$8);
						zephir_add_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1643);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1643);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_add_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/vector.zep", 1643);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1646);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a matrix from this vector.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, subtractMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1664);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1681);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1678);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1675);
					ZEPHIR_INIT_NVAR(&_17$$5);
					zephir_sub_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/vector.zep", 1675);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1675);
						ZEPHIR_INIT_NVAR(&_19$$6);
						zephir_sub_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1675);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1678);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1678);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1675);
						ZEPHIR_INIT_NVAR(&_26$$8);
						zephir_sub_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1675);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1675);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_sub_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/vector.zep", 1675);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1678);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this vector to the power of a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, powMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1696);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1713);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1710);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1707);
					zephir_pow_function(&_16$$5, &valueA, &_17$$5);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1707);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1707);
						zephir_pow_function(&_18$$6, &valueA, &_19$$6);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1707);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1710);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1710);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1707);
						zephir_pow_function(&_25$$8, &valueA, &_26$$8);
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1707);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1707);
							zephir_pow_function(&_27$$9, &valueA, &_28$$9);
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1707);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1710);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Mod this vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, modMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1728);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1745);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1742);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1739);
					ZEPHIR_INIT_NVAR(&_17$$5);
					mod_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/vector.zep", 1739);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1739);
						ZEPHIR_INIT_NVAR(&_19$$6);
						mod_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1739);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1742);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1742);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1739);
						ZEPHIR_INIT_NVAR(&_26$$8);
						mod_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1739);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1739);
							ZEPHIR_INIT_NVAR(&_28$$9);
							mod_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/vector.zep", 1739);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1742);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a
 * matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, equalMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1761);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1778);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1775);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1772);
					if (ZEPHIR_IS_EQUAL(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1772);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1772);
						if (ZEPHIR_IS_EQUAL(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1772);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1775);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1775);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1772);
						if (ZEPHIR_IS_EQUAL(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1772);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1772);
							if (ZEPHIR_IS_EQUAL(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1772);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1775);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a
 * matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, notEqualMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1794);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1811);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1808);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1805);
					if (!ZEPHIR_IS_EQUAL(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1805);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1805);
						if (!ZEPHIR_IS_EQUAL(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1805);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1808);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1808);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1805);
						if (!ZEPHIR_IS_EQUAL(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1805);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1805);
							if (!ZEPHIR_IS_EQUAL(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1805);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1808);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector
 * and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, greaterMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1827);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1844);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1841);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1838);
					if (ZEPHIR_GT(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1838);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1838);
						if (ZEPHIR_GT(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1838);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1841);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1841);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1838);
						if (ZEPHIR_GT(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1838);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1838);
							if (ZEPHIR_GT(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1838);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1841);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, greaterEqualMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1860);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1877);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1874);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1871);
					if (ZEPHIR_GE(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1871);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1871);
						if (ZEPHIR_GE(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1871);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1874);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1874);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1871);
						if (ZEPHIR_GE(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1871);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1871);
							if (ZEPHIR_GE(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1871);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1874);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector
 * and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, lessMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1893);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1910);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1907);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1904);
					if (ZEPHIR_LT(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1904);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1904);
						if (ZEPHIR_LT(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1904);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1907);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1907);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1904);
						if (ZEPHIR_LT(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1904);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1904);
							if (ZEPHIR_LT(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1904);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1907);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, lessEqualMatrix) {

	zend_string *_15$$4, *_24$$7;
	zend_ulong _14$$4, _23$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_29 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1926);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1943);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_is_iterable(&_11$$4, 0, "tensor/vector.zep", 1940);
			if (Z_TYPE_P(&_11$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_11$$4), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1937);
					if (ZEPHIR_LE(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1937);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &_11$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &_11$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &_11$$4, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &_11$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1937);
						if (ZEPHIR_LE(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/vector.zep", 1937);
					ZEPHIR_CALL_METHOD(NULL, &_11$$4, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/vector.zep", 1940);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_is_iterable(&_20$$7, 0, "tensor/vector.zep", 1940);
				if (Z_TYPE_P(&_20$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_20$$7), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						ZEPHIR_INIT_NVAR(&_25$$8);
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1937);
						if (ZEPHIR_LE(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/vector.zep", 1937);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &_20$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &_20$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &_20$$7, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &_20$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1937);
							if (ZEPHIR_LE(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1937);
						ZEPHIR_CALL_METHOD(NULL, &_20$$7, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/vector.zep", 1940);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_29, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this vector with another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, multiplyVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1958);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1969);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1966);
			ZEPHIR_INIT_NVAR(&_15$$4);
			mul_function(&_15$$4, &_14$$4, &valueB);
			zephir_array_append(&c, &_15$$4, PH_SEPARATE, "tensor/vector.zep", 1966);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_16$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_17$$5, &_16$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1966);
				ZEPHIR_INIT_NVAR(&_18$$5);
				mul_function(&_18$$5, &_17$$5, &valueB);
				zephir_array_append(&c, &_18$$5, PH_SEPARATE, "tensor/vector.zep", 1966);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector by another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, divideVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1984);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1995);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1992);
			ZEPHIR_INIT_NVAR(&_15$$4);
			div_function(&_15$$4, &_14$$4, &valueB);
			zephir_array_append(&c, &_15$$4, PH_SEPARATE, "tensor/vector.zep", 1992);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_16$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_17$$5, &_16$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1992);
				ZEPHIR_INIT_NVAR(&_18$$5);
				div_function(&_18$$5, &_17$$5, &valueB);
				zephir_array_append(&c, &_18$$5, PH_SEPARATE, "tensor/vector.zep", 1992);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this vector to another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, addVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2010);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2021);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2018);
			ZEPHIR_INIT_NVAR(&_15$$4);
			zephir_add_function(&_15$$4, &_14$$4, &valueB);
			zephir_array_append(&c, &_15$$4, PH_SEPARATE, "tensor/vector.zep", 2018);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_16$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_17$$5, &_16$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2018);
				ZEPHIR_INIT_NVAR(&_18$$5);
				zephir_add_function(&_18$$5, &_17$$5, &valueB);
				zephir_array_append(&c, &_18$$5, PH_SEPARATE, "tensor/vector.zep", 2018);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a vector from this vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, subtractVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2036);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2047);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2044);
			ZEPHIR_INIT_NVAR(&_15$$4);
			zephir_sub_function(&_15$$4, &_14$$4, &valueB);
			zephir_array_append(&c, &_15$$4, PH_SEPARATE, "tensor/vector.zep", 2044);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_16$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_17$$5, &_16$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2044);
				ZEPHIR_INIT_NVAR(&_18$$5);
				zephir_sub_function(&_18$$5, &_17$$5, &valueB);
				zephir_array_append(&c, &_18$$5, PH_SEPARATE, "tensor/vector.zep", 2044);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this vector to a power of another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, powVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2062);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2073);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2070);
			zephir_pow_function(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2070);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2070);
				zephir_pow_function(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2070);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this vector with another vector elementwise.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, modVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2088);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2099);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2096);
			ZEPHIR_INIT_NVAR(&_15$$4);
			mod_function(&_15$$4, &_14$$4, &valueB);
			zephir_array_append(&c, &_15$$4, PH_SEPARATE, "tensor/vector.zep", 2096);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_16$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_17$$5, &_16$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2096);
				ZEPHIR_INIT_NVAR(&_18$$5);
				mod_function(&_18$$5, &_17$$5, &valueB);
				zephir_array_append(&c, &_18$$5, PH_SEPARATE, "tensor/vector.zep", 2096);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a
 * another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, equalVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2115);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2126);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2123);
			if (ZEPHIR_IS_EQUAL(&_15$$4, &valueB)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2123);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2123);
				if (ZEPHIR_IS_EQUAL(&_18$$5, &valueB)) {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 0);
				}
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2123);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a
 * another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, notEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2142);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2153);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2150);
			if (!ZEPHIR_IS_EQUAL(&_15$$4, &valueB)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2150);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2150);
				if (!ZEPHIR_IS_EQUAL(&_18$$5, &valueB)) {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 0);
				}
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2150);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector
 * and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2169);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2180);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2177);
			if (ZEPHIR_GT(&_15$$4, &valueB)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2177);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2177);
				if (ZEPHIR_GT(&_18$$5, &valueB)) {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 0);
				}
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2177);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2196);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2207);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2204);
			if (ZEPHIR_GE(&_15$$4, &valueB)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2204);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2204);
				if (ZEPHIR_GE(&_18$$5, &valueB)) {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 0);
				}
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2204);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector
 * and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2223);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2234);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2231);
			if (ZEPHIR_LT(&_15$$4, &valueB)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2231);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2231);
				if (ZEPHIR_LT(&_18$$5, &valueB)) {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 0);
				}
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2231);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$4, _16$$5, _17$$5, _18$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2250);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2261);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2258);
			if (ZEPHIR_LE(&_15$$4, &valueB)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2258);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_8, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_10, &_8, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_10)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_8, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_16$$5);
				zephir_read_property(&_17$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2258);
				if (ZEPHIR_LE(&_18$$5, &valueB)) {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_16$$5);
					ZVAL_LONG(&_16$$5, 0);
				}
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 2258);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this vector by a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, multiplyScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2276);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2287);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			mul_function(&_8$$4, &valueA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2284);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				mul_function(&_9$$5, &valueA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2284);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector by a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, divideScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2302);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2313);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			div_function(&_8$$4, &valueA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2310);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				div_function(&_9$$5, &valueA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2310);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add a scalar to this vector.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, addScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2328);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2339);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			zephir_add_function(&_8$$4, &valueA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2336);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_add_function(&_9$$5, &valueA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2336);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a scalar from this vector.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, subtractScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2354);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2365);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			zephir_sub_function(&_8$$4, &valueA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2362);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_sub_function(&_9$$5, &valueA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2362);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise the vector to a the power of a scalar value.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, powScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2380);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2391);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			zephir_pow_function(&_8$$4, &valueA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2388);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_pow_function(&_9$$5, &valueA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2388);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this vector with a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, modScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2406);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2417);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			mod_function(&_8$$4, &valueA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2414);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				mod_function(&_9$$5, &valueA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2414);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a
 * scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, equalScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2433);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2444);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			if (ZEPHIR_IS_EQUAL(&valueA, b)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2441);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				if (ZEPHIR_IS_EQUAL(&valueA, b)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2441);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a
 * scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, notEqualScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2460);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2471);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			if (!ZEPHIR_IS_EQUAL(&valueA, b)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2468);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				if (!ZEPHIR_IS_EQUAL(&valueA, b)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2468);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector
 * and a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2487);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2498);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			if (ZEPHIR_GT(&valueA, b)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2495);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				if (ZEPHIR_GT(&valueA, b)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2495);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this vector and a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterEqualScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2514);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2525);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			if (ZEPHIR_GE(&valueA, b)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2522);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				if (ZEPHIR_GE(&valueA, b)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2522);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector
 * and a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2541);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2552);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			if (ZEPHIR_LT(&valueA, b)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2549);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				if (ZEPHIR_LT(&valueA, b)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2549);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this vector and a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessEqualScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2568);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2579);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			if (ZEPHIR_LE(&valueA, b)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2576);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_5, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_7, &_5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_7)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				if (ZEPHIR_LE(&valueA, b)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2576);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Count method to implement countable interface.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, count) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "n");

}

/**
 * @param mixed index
 * @param array values
 * @throws \RuntimeException
 */
PHP_METHOD(Tensor_Vector, offsetSet) {

	zval *index, index_sub, *values, values_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&values_sub);

	zephir_fetch_params_without_memory_grow(2, 0, &index, &values);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Vector cannot be mutated directly.", "tensor/vector.zep", 2599);
	return;

}

/**
 * Does a given column exist in the matrix.
 *
 * @param mixed index
 * @return bool
 */
PHP_METHOD(Tensor_Vector, offsetExists) {

	zval *index, index_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);

	zephir_fetch_params_without_memory_grow(1, 0, &index);



	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset(&_0, index));

}

/**
 * @param mixed index
 * @throws \RuntimeException
 */
PHP_METHOD(Tensor_Vector, offsetUnset) {

	zval *index, index_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &index);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Vector cannot be mutated directly.", "tensor/vector.zep", 2619);
	return;

}

/**
 * Return a row from the matrix at the given index.
 *
 * @param mixed index
 * @throws \InvalidArgumentException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, offsetGet) {

	zval _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *index, index_sub, value, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	ZEPHIR_OBS_VAR(&value);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	if (zephir_array_isset_fetch(&value, &_0, index, 0)) {
		RETURN_CCTOR(&value);
	}
	ZEPHIR_INIT_VAR(&_1);
	object_init_ex(&_1, spl_ce_InvalidArgumentException);
	zephir_get_strval(&_2, index);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SSVS(&_3, "Element not found at", " offset ", &_2, ".");
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_1, "tensor/vector.zep", 2638);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Get an iterator for the rows in the matrix.
 *
 * @return \ArrayIterator
 */
PHP_METHOD(Tensor_Vector, getIterator) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	object_init_ex(return_value, zephir_get_internal_ce(SL("arrayiterator")));
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 23, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convert the tensor into a string representation.
 *
 * @return string
 */
PHP_METHOD(Tensor_Vector, __toString) {

	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_join_str(&_0, SL(" "), &_1);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_GET_CONSTANT(&_2, "PHP_EOL");
	ZEPHIR_CONCAT_SVSV(return_value, "[ ", &_0, " ]", &_2);
	RETURN_MM();

}

zend_object *zephir_init_properties_Tensor_Vector(zend_class_entry *class_type TSRMLS_DC) {

		zval _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
		ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);

		ZEPHIR_MM_GROW();
	
	{
		zval local_this_ptr, *this_ptr = &local_this_ptr;
		ZEPHIR_CREATE_OBJECT(this_ptr, class_type);
		zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0) == IS_NULL) {
			ZEPHIR_INIT_VAR(&_1$$3);
			array_init(&_1$$3);
			zephir_update_property_zval(this_ptr, SL("a"), &_1$$3);
		}
		ZEPHIR_MM_RESTORE();
		return Z_OBJ_P(this_ptr);
	}

}

