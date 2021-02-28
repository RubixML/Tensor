
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
#include "kernel/concat.h"
#include "kernel/array.h"
#include "math.h"
#include "kernel/math.h"
#include "kernel/string.h"
#include "include/indexing.h"
#include "include/linear_algebra.h"
#include "include/arithmetic.h"
#include "include/comparison.h"


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

	zend_class_implements(tensor_vector_ce, 1, tensor_tensor_ce);
	return SUCCESS;

}

/**
 * Factory method to build a new vector from an array.
 *
 * @param (int|float)[] a
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
 * @param (int|float)[] a
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, zeros) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0, _1;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	ZVAL_LONG(&_0, 0);
	ZVAL_LONG(&_1, n);
	ZEPHIR_RETURN_CALL_STATIC("fill", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a vector of ones with n elements.
 *
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, ones) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0, _1;
	zend_long n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	ZVAL_LONG(&_0, 1);
	ZVAL_LONG(&_1, n);
	ZEPHIR_RETURN_CALL_STATIC("fill", NULL, 0, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Fill a vector with a given value.
 *
 * @param int|float value
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
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
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, value);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, value);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Value must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 92);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", NULL, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "N must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/vector.zep", 97);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, rand) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5$$4, _7$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "N must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 114);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_CALL_FUNCTION(&_4, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_4);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		ZEPHIR_CALL_FUNCTION(&_5$$4, "rand", &_6, 7);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_7$$4);
		ZVAL_DOUBLE(&_7$$4, zephir_safe_div_zval_long(&_5$$4, max));
		zephir_array_append(&a, &_7$$4, PH_SEPARATE, "tensor/vector.zep", 122);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a standard normally distributed (Gaussian) random vector with mean 0
 * and unit variance.
 *
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, gaussian) {

	zval a;
	double r = 0, phi = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_9 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5$$4, _7$$4, _8$$4, _10$$4, _11$$4, _12$$4, _13$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "N must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 140);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_CALL_FUNCTION(&_4, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_4);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		ZEPHIR_CALL_FUNCTION(&_5$$4, "rand", &_6, 7);
		zephir_check_call_status();
		ZVAL_DOUBLE(&_7$$4, zephir_safe_div_zval_long(&_5$$4, max));
		ZEPHIR_CALL_FUNCTION(&_8$$4, "log", &_9, 8, &_7$$4);
		zephir_check_call_status();
		ZVAL_DOUBLE(&_7$$4, (-2.0 * zephir_get_numberval(&_8$$4)));
		r = sqrt((-2.0 * zephir_get_numberval(&_8$$4)));
		ZEPHIR_CALL_FUNCTION(&_10$$4, "rand", &_6, 7);
		zephir_check_call_status();
		phi = (zephir_safe_div_zval_long(&_10$$4, max) * 6.28318530718);
		ZVAL_DOUBLE(&_11$$4, phi);
		ZEPHIR_INIT_NVAR(&_12$$4);
		ZVAL_DOUBLE(&_12$$4, (r * sin(phi)));
		zephir_array_append(&a, &_12$$4, PH_SEPARATE, "tensor/vector.zep", 154);
		ZVAL_DOUBLE(&_13$$4, phi);
		ZEPHIR_INIT_NVAR(&_12$$4);
		ZVAL_DOUBLE(&_12$$4, (r * cos(phi)));
		zephir_array_append(&a, &_12$$4, PH_SEPARATE, "tensor/vector.zep", 155);
	}
	if (zephir_fast_count_int(&a) > n) {
		ZEPHIR_MAKE_REF(&a);
		ZEPHIR_CALL_FUNCTION(NULL, "array_pop", NULL, 9, &a);
		ZEPHIR_UNREF(&a);
		zephir_check_call_status();
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, poisson) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	double lambda, p = 0, l;
	zval *n_param = NULL, *lambda_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5, _6, _7$$5, _9$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, k = 0, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &n_param, &lambda_param);

	n = zephir_get_intval(n_param);
	if (!lambda_param) {
		lambda = 1.0;
	} else {
		lambda = zephir_get_doubleval(lambda_param);
	}


	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "N must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 177);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZVAL_DOUBLE(&_4, -lambda);
	ZEPHIR_CALL_FUNCTION(&_5, "exp", NULL, 10, &_4);
	zephir_check_call_status();
	l = zephir_get_doubleval(&_5);
	ZEPHIR_CALL_FUNCTION(&_6, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_6);
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
			ZEPHIR_CALL_FUNCTION(&_7$$5, "rand", &_8, 7);
			zephir_check_call_status();
			p *= zephir_safe_div_zval_long(&_7$$5, max);
		}
		ZEPHIR_INIT_NVAR(&_9$$4);
		ZVAL_LONG(&_9$$4, (k - 1));
		zephir_array_append(&a, &_9$$4, PH_SEPARATE, "tensor/vector.zep", 199);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a random uniformly distributed vector with values between -1 and 1.
 *
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, uniform) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4, _5$$4, _6$$4, _7$$4, _9$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "N must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 216);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_CALL_FUNCTION(&_4, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_4);
	while (1) {
		if (!(zephir_fast_count_int(&a) < n)) {
			break;
		}
		ZVAL_LONG(&_5$$4, -max);
		ZVAL_LONG(&_6$$4, max);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "rand", &_8, 7, &_5$$4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_9$$4);
		ZVAL_DOUBLE(&_9$$4, zephir_safe_div_zval_long(&_7$$4, max));
		zephir_array_append(&a, &_9$$4, PH_SEPARATE, "tensor/vector.zep", 224);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return evenly spaced values within a given interval.
 *
 * @param int|float start
 * @param int|float end
 * @param int|float interval
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


	ZEPHIR_CALL_FUNCTION(&_0, "range", NULL, 11, start, end, interval);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a vector of n evenly spaced numbers between minimum and maximum.
 *
 * @param float min
 * @param float max
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, linspace) {

	zval a;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, k;
	zval *min_param = NULL, *max_param = NULL, *n_param = NULL, _0$$4, _1$$4, _2$$4, _3$$4, _4, _5, _6, _7$$5, _9$$5;
	double min, max, interval;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&a);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &min_param, &max_param, &n_param);

	min = zephir_get_doubleval(min_param);
	max = zephir_get_doubleval(max_param);
	n = zephir_get_intval(n_param);


	if (UNEXPECTED(min > max)) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_invalidargumentexception_ce, "Minimum must be less than maximum.", "tensor/vector.zep", 255);
		return;
	}
	if (UNEXPECTED(n < 2)) {
		ZEPHIR_INIT_VAR(&_0$$4);
		object_init_ex(&_0$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$4, n);
		ZEPHIR_CALL_FUNCTION(&_2$$4, "strval", NULL, 4, &_1$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$4);
		ZEPHIR_CONCAT_SSVS(&_3$$4, "Number of elements", " must be greater than 1, ", &_2$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$4, "__construct", NULL, 3, &_3$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$4, "tensor/vector.zep", 260);
		ZEPHIR_MM_RESTORE();
		return;
	}
	k = (n - 1);
	ZVAL_DOUBLE(&_4, (max - min));
	ZEPHIR_CALL_FUNCTION(&_5, "abs", NULL, 12, &_4);
	zephir_check_call_status();
	interval = zephir_safe_div_zval_long(&_5, k);
	ZEPHIR_INIT_VAR(&a);
	zephir_create_array(&a, 1, 0);
	ZEPHIR_INIT_VAR(&_6);
	ZVAL_DOUBLE(&_6, min);
	zephir_array_fast_append(&a, &_6);
	while (1) {
		if (!(zephir_fast_count_int(&a) < k)) {
			break;
		}
		ZEPHIR_MAKE_REF(&a);
		ZEPHIR_CALL_FUNCTION(&_7$$5, "end", &_8, 13, &a);
		ZEPHIR_UNREF(&a);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_9$$5);
		ZVAL_DOUBLE(&_9$$5, (zephir_get_numberval(&_7$$5) + interval));
		zephir_array_append(&a, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 270);
	}
	ZEPHIR_INIT_NVAR(&_6);
	ZVAL_DOUBLE(&_6, max);
	zephir_array_append(&a, &_6, PH_SEPARATE, "tensor/vector.zep", 273);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elementwise maximum of two vectors.
 *
 * @param \Tensor\Vector a
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 291);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "max");
	ZEPHIR_CALL_FUNCTION(&_11, "array_map", NULL, 14, &_10, &_8, &_9);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 310);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "min");
	ZEPHIR_CALL_FUNCTION(&_11, "array_map", NULL, 14, &_10, &_8, &_9);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_11);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param (int|float)[] a
 * @param bool validate
 * @throws \Tensor\Exceptions\InvalidArgumentException
 */
PHP_METHOD(Tensor_Vector, __construct) {

	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool validate;
	zval *a_param = NULL, *validate_param = NULL, _0$$3, _2$$4, _3;
	zval a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &a_param, &validate_param);

	zephir_get_arrval(&a, a_param);
	if (!validate_param) {
		validate = 1;
	} else {
		validate = zephir_get_boolval(validate_param);
	}


	if (UNEXPECTED(ZEPHIR_IS_EMPTY(&a))) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SS(&_1$$3, "Vector must contain", " at least one element.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 325);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (validate) {
		ZEPHIR_CALL_FUNCTION(&_2$$4, "array_values", NULL, 15, &a);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_2$$4);
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("a"), &a);
	ZEPHIR_INIT_ZVAL_NREF(_3);
	ZVAL_LONG(&_3, zephir_fast_count_int(&a));
	zephir_update_property_zval(this_ptr, ZEND_STRL("n"), &_3);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
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
 * @return (int|float)[]
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
	zephir_read_property(&_2, this_ptr, ZEND_STRL("a"), PH_NOISY_CC);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 421);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			ZEPHIR_INIT_NVAR(&_3$$3);
			zephir_create_array(&_3$$3, 1, 0);
			zephir_array_fast_append(&_3$$3, &valueA);
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/vector.zep", 418);
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
				zephir_array_append(&b, &_4$$4, PH_SEPARATE, "tensor/vector.zep", 418);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, reshape) {

	zval _2$$3;
	zval b, rowB;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zval *m_param = NULL, *n_param = NULL, _3, _1$$3, _4$$4, _5$$4, _6$$4, _7$$4, _8$$6, _9$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, nHat, i;
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
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	_0 = m < 0;
	if (!(_0)) {
		_0 = n < 0;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "The number of rows", " and/or columns cannot be less than 0.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 436);
		ZEPHIR_MM_RESTORE();
		return;
	}
	nHat = (m * n);
	zephir_read_property(&_3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_LONG_IDENTICAL(&_3, nHat))) {
		ZEPHIR_INIT_VAR(&_4$$4);
		object_init_ex(&_4$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_5$$4, nHat);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "strval", NULL, 4, &_5$$4);
		zephir_check_call_status();
		zephir_read_property(&_5$$4, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_VSSVS(&_7$$4, &_6$$4, " elements", " are needed but vector only has ", &_5$$4, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 3, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$4, "tensor/vector.zep", 443);
		ZEPHIR_MM_RESTORE();
		return;
	}
	i = 0;
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	while (1) {
		if (!(zephir_fast_count_int(&b) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowB);
		array_init(&rowB);
		while (1) {
			if (!(zephir_fast_count_int(&rowB) < n)) {
				break;
			}
			zephir_read_property(&_8$$6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch_long(&_9$$6, &_8$$6, i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 455);
			zephir_array_append(&rowB, &_9$$6, PH_SEPARATE, "tensor/vector.zep", 455);
			i++;
		}
		zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/vector.zep", 460);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
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

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_argmin(return_value, &_0);
	return;

}

/**
 * Return the index of the maximum element in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_Vector, argmax) {

	zval _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);


	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_argmax(return_value, &_0);
	return;

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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_1, "array_map", NULL, 14, callback, &_0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Reduce the vector down to a scalar.
 *
 * @param callable callback
 * @param int|float initial
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return int|float
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
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, initial);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, initial);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Initial value must", " be an integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 521);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_reduce", NULL, 16, &_5, callback, initial);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the dot product of this vector and another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return float
 */
PHP_METHOD(Tensor_Vector, dot) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " elements but vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 539);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_dot(return_value, &_8, &_9);
	RETURN_MM();

}

/**
 * Convolve this vector with another vector.
 *
 * @param \Tensor\Vector b
 * @param int stride
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, convolve) {

	zend_string *_17$$5;
	zend_ulong _16$$5;
	zval _3$$3;
	zend_bool _11;
	zval bHat, c, _9;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long stride, ZEPHIR_LAST_CALL_STATUS, i = 0, _12, _13, k$$6, k$$8;
	zval *b, b_sub, *stride_param = NULL, _0, _1, j, valueA, valueB, _8, _10, _2$$3, _4$$4, _5$$4, _6$$4, _7$$4, *_14$$5, _15$$5, _22$$5, _18$$6, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_9);
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
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(ZEPHIR_GT(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SS(&_3$$3, "Vector B cannot be", " larger than Vector A.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 557);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(stride < 1)) {
		ZEPHIR_INIT_VAR(&_4$$4);
		object_init_ex(&_4$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_5$$4, stride);
		ZEPHIR_CALL_FUNCTION(&_6$$4, "strval", NULL, 4, &_5$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_SSVS(&_7$$4, "Stride cannot be", " less than 1, ", &_6$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_4$$4, "__construct", NULL, 3, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$4, "tensor/vector.zep", 562);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&bHat);
	array_init(&bHat);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_9, &_8);
	ZEPHIR_CPY_WRT(&bHat, &_9);
	zephir_read_property(&_10, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	_13 = (zephir_get_numberval(&_10) - 1);
	_12 = 0;
	_11 = 0;
	if (_12 <= _13) {
		while (1) {
			if (_11) {
				_12 += stride;
				if (!(_12 <= _13)) {
					break;
				}
			} else {
				_11 = 1;
			}
			i = _12;
			sigma = 0.0;
			zephir_is_iterable(&bHat, 0, "tensor/vector.zep", 585);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _16$$5, _17$$5, _14$$5)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_17$$5 != NULL) { 
						ZVAL_STR_COPY(&j, _17$$5);
					} else {
						ZVAL_LONG(&j, _16$$5);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$5);
					k$$6 = (i - zephir_get_intval(&j));
					ZEPHIR_OBS_NVAR(&valueA);
					zephir_read_property(&_18$$6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
					if (zephir_array_isset_long_fetch(&valueA, &_18$$6, k$$6, 0)) {
						ZEPHIR_INIT_NVAR(&_19$$7);
						mul_function(&_19$$7, &valueA, &valueB);
						sigma += zephir_get_numberval(&_19$$7);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$5, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						k$$8 = (i - zephir_get_intval(&j));
						ZEPHIR_OBS_NVAR(&valueA);
						zephir_read_property(&_20$$8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
						if (zephir_array_isset_long_fetch(&valueA, &_20$$8, k$$8, 0)) {
							ZEPHIR_INIT_NVAR(&_21$$9);
							mul_function(&_21$$9, &valueA, &valueB);
							sigma += zephir_get_numberval(&_21$$9);
						}
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			ZEPHIR_INIT_NVAR(&_22$$5);
			ZVAL_DOUBLE(&_22$$5, sigma);
			zephir_array_append(&c, &_22$$5, PH_SEPARATE, "tensor/vector.zep", 585);
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

	zend_string *_8$$3, *_14$$6;
	zend_ulong _7$$3, _13$$6;
	zval bHat, c, rowC, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_17 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, j, valueA, valueB, _0, _2, *_3, _4, *_5$$3, _6$$3, _9$$4, _10$$5, *_11$$6, _12$$6, _15$$7, _16$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&bHat);
	array_init(&bHat);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_0, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_1, &_0);
	ZEPHIR_CPY_WRT(&bHat, &_1);
	zephir_read_property(&_2, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/vector.zep", 639);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _3);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/vector.zep", 636);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _7$$3, _8$$3, _5$$3)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_8$$3 != NULL) { 
						ZVAL_STR_COPY(&j, _8$$3);
					} else {
						ZVAL_LONG(&j, _7$$3);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _5$$3);
					ZEPHIR_INIT_NVAR(&_9$$4);
					mul_function(&_9$$4, &valueA, &valueB);
					zephir_array_append(&rowC, &_9$$4, PH_SEPARATE, "tensor/vector.zep", 633);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_6$$3, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_6$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_10$$5);
						mul_function(&_10$$5, &valueA, &valueB);
						zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/vector.zep", 633);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/vector.zep", 636);
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
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/vector.zep", 636);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$6, _14$$6, _11$$6)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_14$$6 != NULL) { 
							ZVAL_STR_COPY(&j, _14$$6);
						} else {
							ZVAL_LONG(&j, _13$$6);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _11$$6);
						ZEPHIR_INIT_NVAR(&_15$$7);
						mul_function(&_15$$7, &valueA, &valueB);
						zephir_array_append(&rowC, &_15$$7, PH_SEPARATE, "tensor/vector.zep", 633);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_12$$6, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_12$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_16$$8);
							mul_function(&_16$$8, &valueA, &valueB);
							zephir_array_append(&rowC, &_16$$8, PH_SEPARATE, "tensor/vector.zep", 633);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/vector.zep", 636);
			ZEPHIR_CALL_METHOD(NULL, &_2, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_17, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the cross product between two 3 dimensional vectors.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\InvalidArgumentException
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	_1 = !ZEPHIR_IS_LONG_IDENTICAL(&_0, 3);
	if (!(_1)) {
		ZEPHIR_CALL_METHOD(&_2, b, "size", NULL, 0);
		zephir_check_call_status();
		_1 = !ZEPHIR_IS_LONG_IDENTICAL(&_2, 3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_3$$3);
		object_init_ex(&_3$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SS(&_4$$3, "Cross product is", " only defined for vectors of 3 dimensions.");
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$3, "tensor/vector.zep", 653);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_5, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 658);
	zephir_array_fetch_long(&_7, b, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 658);
	ZEPHIR_INIT_VAR(&_8);
	mul_function(&_8, &_6, &_7);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_9, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 658);
	zephir_array_fetch_long(&_7, b, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 658);
	ZEPHIR_INIT_VAR(&_10);
	mul_function(&_10, &_6, &_7);
	ZEPHIR_INIT_VAR(&_11);
	zephir_sub_function(&_11, &_8, &_10);
	zephir_array_append(&c, &_11, PH_SEPARATE, "tensor/vector.zep", 658);
	zephir_read_property(&_12, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_12, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 659);
	zephir_array_fetch_long(&_7, b, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 659);
	ZEPHIR_INIT_NVAR(&_8);
	mul_function(&_8, &_6, &_7);
	zephir_read_property(&_13, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_13, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 659);
	zephir_array_fetch_long(&_7, b, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 659);
	ZEPHIR_INIT_NVAR(&_10);
	mul_function(&_10, &_6, &_7);
	ZEPHIR_INIT_VAR(&_14);
	zephir_sub_function(&_14, &_8, &_10);
	zephir_array_append(&c, &_14, PH_SEPARATE, "tensor/vector.zep", 659);
	zephir_read_property(&_15, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_15, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 660);
	zephir_array_fetch_long(&_7, b, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 660);
	ZEPHIR_INIT_NVAR(&_8);
	mul_function(&_8, &_6, &_7);
	zephir_read_property(&_16, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_16, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 660);
	zephir_array_fetch_long(&_7, b, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 660);
	ZEPHIR_INIT_NVAR(&_10);
	mul_function(&_10, &_6, &_7);
	ZEPHIR_INIT_VAR(&_17);
	zephir_sub_function(&_17, &_8, &_10);
	zephir_array_append(&c, &_17, PH_SEPARATE, "tensor/vector.zep", 660);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
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


	if (UNEXPECTED(p <= 0.0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_DOUBLE(&_1$$3, p);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "P must be greater", " than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 707);
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
 * A universal function to multiply this vector with another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, multiply) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot multiply", " vector by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 750);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to divide this vector by another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, divide) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividematrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividevector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividescalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot divide", " vector by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 780);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to add this vector with another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, add) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot add", " vector by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 811);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to subtract this vector from another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, subtract) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot subtract", " vector from the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 842);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to raise this vector to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, pow) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot raise", " vector to the power of the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 873);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the modulus of this vector and
 * another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, mod) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot mod", " vector with the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 904);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the equality comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, equal) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " vector to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 935);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the not equal comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, notEqual) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " vector to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 966);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, greater) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatermatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatervector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " vector to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 997);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than or equal to
 * comparison of this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, greaterEqual) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " vector to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 1028);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than comparison of
 * this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, less) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " vector to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 1059);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than or equal to
 * comparison of this vector and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Vector, lessEqual) {

	zend_bool _1$$3;
	zval _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	do {
		if (ZEPHIR_IS_STRING(&_0, "object")) {
			do {
				_1$$3 = 1;
				if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalmatrix", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
				if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalvector", NULL, 0, b);
					zephir_check_call_status();
					RETURN_MM();
				}
			} while(0);

			break;
		}
		if (ZEPHIR_IS_STRING(&_0, "double") || ZEPHIR_IS_STRING(&_0, "integer")) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
	} while(0);

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " vector to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/vector.zep", 1090);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyvector", NULL, 0, this_ptr);
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
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *base_param = NULL, _0$$3, valueA, _1, *_2, _3, _4$$4, _5$$4, _7$$5, _8$$5;
	double base;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &base_param);

	if (!base_param) {
		base = 2.7182818284590452354;
	} else {
		base = zephir_get_doubleval(base_param);
	}


	if (base == 2.7182818284590452354) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "log");
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_1, 0, "tensor/vector.zep", 1174);
	if (Z_TYPE_P(&_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _2);
			ZVAL_DOUBLE(&_4$$4, base);
			ZEPHIR_CALL_FUNCTION(&_5$$4, "log", &_6, 8, &valueA, &_4$$4);
			zephir_check_call_status();
			zephir_array_append(&b, &_5$$4, PH_SEPARATE, "tensor/vector.zep", 1171);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_1, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_3, &_1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&valueA, &_1, "current", NULL, 0);
			zephir_check_call_status();
				ZVAL_DOUBLE(&_7$$5, base);
				ZEPHIR_CALL_FUNCTION(&_8$$5, "log", &_6, 8, &valueA, &_7$$5);
				zephir_check_call_status();
				zephir_array_append(&b, &_8$$5, PH_SEPARATE, "tensor/vector.zep", 1171);
			ZEPHIR_CALL_METHOD(NULL, &_1, "next", NULL, 0);
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

	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_sum", NULL, 17, &_0);
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

	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_product", NULL, 18, &_0);
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

	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("min", NULL, 19, &_0);
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

	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("max", NULL, 20, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the mean of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, mean) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	div_function(return_value, &_0, &_1);
	RETURN_MM();

}

/**
 * Return the median of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, median) {

	zval median, _0, _1, _2, a, _3$$4, _4$$4, _5$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, mid;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&median);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 2);
	ZEPHIR_CALL_FUNCTION(&_2, "intdiv", NULL, 21, &_0, &_1);
	zephir_check_call_status();
	mid = zephir_get_intval(&_2);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&a, &_1);
	ZEPHIR_MAKE_REF(&a);
	ZEPHIR_CALL_FUNCTION(NULL, "sort", NULL, 22, &a);
	ZEPHIR_UNREF(&a);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	if (zephir_safe_mod_zval_long(&_1, 2) == 1) {
		ZEPHIR_OBS_VAR(&median);
		zephir_array_fetch_long(&median, &a, mid, PH_NOISY, "tensor/vector.zep", 1333);
	} else {
		zephir_array_fetch_long(&_3$$4, &a, (mid - 1), PH_NOISY | PH_READONLY, "tensor/vector.zep", 1335);
		zephir_array_fetch_long(&_4$$4, &a, mid, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1335);
		ZEPHIR_INIT_VAR(&_5$$4);
		zephir_add_function(&_5$$4, &_3$$4, &_4$$4);
		ZEPHIR_INIT_NVAR(&median);
		ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_5$$4, 2.0));
	}
	RETURN_CCTOR(&median);

}

/**
 * Return the q'th quantile of the vector.
 *
 * @param float q
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, quantile) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, xHat;
	zval *q_param = NULL, a, _5, _6, _7, _1$$3, _2$$3, _3$$3, _4$$3;
	double q, x, remainder, t;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &q_param);

	q = zephir_get_doubleval(q_param);


	_0 = q < 0.0;
	if (!(_0)) {
		_0 = q > 1.0;
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_DOUBLE(&_2$$3, q);
		ZEPHIR_CALL_FUNCTION(&_3$$3, "strval", NULL, 4, &_2$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Q must be", " between 0 and 1, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1352);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&a, &_5);
	ZEPHIR_MAKE_REF(&a);
	ZEPHIR_CALL_FUNCTION(NULL, "sort", NULL, 22, &a);
	ZEPHIR_UNREF(&a);
	zephir_check_call_status();
	zephir_read_property(&_5, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	x = ((q * (double) ((zephir_get_numberval(&_5) - 1))) + (double) (1));
	xHat = (int) (x);
	remainder = (x -  (double) xHat);
	ZEPHIR_OBS_VAR(&_6);
	zephir_array_fetch_long(&_6, &a, (xHat - 1), PH_NOISY, "tensor/vector.zep", 1365);
	t = zephir_get_doubleval(&_6);
	zephir_array_fetch_long(&_7, &a, xHat, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1367);
	RETURN_MM_DOUBLE((t + (remainder * ((zephir_get_numberval(&_7) - t)))));

}

/**
 * Return the variance of the vector.
 *
 * @param mixed mean
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, variance) {

	zend_bool _0$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *mean = NULL, mean_sub, __$null, _1$$3, _2$$4, _3$$4, _4$$4, ssd, _5, _6, _7;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&mean_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&ssd);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);

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
			ZEPHIR_CALL_FUNCTION(&_1$$3, "is_float", NULL, 2, mean);
			zephir_check_call_status();
			_0$$3 = !zephir_is_true(&_1$$3);
		}
		if (UNEXPECTED(_0$$3)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, tensor_exceptions_invalidargumentexception_ce);
			ZEPHIR_INIT_VAR(&_3$$4);
			zephir_gettype(&_3$$4, mean);
			ZEPHIR_INIT_VAR(&_4$$4);
			ZEPHIR_CONCAT_SSVS(&_4$$4, "Mean scalar must be", " an integer or floating point number ", &_3$$4, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 3, &_4$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$4, "tensor/vector.zep", 1383);
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(mean, this_ptr, "mean", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_5, this_ptr, "subtractscalar", NULL, 0, mean);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_6, &_5, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&ssd, &_6, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_7, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	div_function(return_value, &ssd, &_7);
	RETURN_MM();

}

/**
 * Round the elements in the matrix to a given decimal place.
 *
 * @param int precision
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, round) {

	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *precision_param = NULL, _0$$3, _1$$4, _2$$4, _3$$4, _4$$4, valueA, _5, *_6, _7, _8$$5, _9$$5, _10$$6, _11$$6;
	zend_long precision, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &precision_param);

	if (!precision_param) {
		precision = 0;
	} else {
		precision = zephir_get_intval(precision_param);
	}


	if (precision == 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		ZVAL_STRING(&_0$$3, "round");
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "map", NULL, 0, &_0$$3);
		zephir_check_call_status();
		RETURN_MM();
	}
	if (UNEXPECTED(precision < 0)) {
		ZEPHIR_INIT_VAR(&_1$$4);
		object_init_ex(&_1$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_2$$4, precision);
		ZEPHIR_CALL_FUNCTION(&_3$$4, "strval", NULL, 4, &_2$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$4);
		ZEPHIR_CONCAT_SSVS(&_4$$4, "Decimal precision cannot", " be less than 0, ", &_3$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$4, "__construct", NULL, 3, &_4$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$4, "tensor/vector.zep", 1411);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 1422);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _6);
			ZEPHIR_INIT_NVAR(&_8$$5);
			ZVAL_LONG(&_9$$5, precision);
			zephir_round(&_8$$5, &valueA, &_9$$5, NULL);
			zephir_array_append(&b, &_8$$5, PH_SEPARATE, "tensor/vector.zep", 1419);
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
				ZEPHIR_INIT_NVAR(&_10$$6);
				ZVAL_LONG(&_11$$6, precision);
				zephir_round(&_10$$6, &valueA, &_11$$6, NULL);
				zephir_array_append(&b, &_10$$6, PH_SEPARATE, "tensor/vector.zep", 1419);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
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


	if (UNEXPECTED(min > max)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SS(&_1$$3, "Minimum cannot be", " greater than maximum.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 1458);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_2, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/vector.zep", 1481);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _3);
			if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
				ZEPHIR_INIT_NVAR(&_5$$5);
				ZVAL_DOUBLE(&_5$$5, max);
				zephir_array_append(&b, &_5$$5, PH_SEPARATE, "tensor/vector.zep", 1467);
				continue;
			}
			if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
				ZEPHIR_INIT_NVAR(&_6$$6);
				ZVAL_DOUBLE(&_6$$6, min);
				zephir_array_append(&b, &_6$$6, PH_SEPARATE, "tensor/vector.zep", 1473);
				continue;
			}
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1478);
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
					zephir_array_append(&b, &_7$$8, PH_SEPARATE, "tensor/vector.zep", 1467);
					continue;
				}
				if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
					ZEPHIR_INIT_NVAR(&_8$$9);
					ZVAL_DOUBLE(&_8$$9, min);
					zephir_array_append(&b, &_8$$9, PH_SEPARATE, "tensor/vector.zep", 1473);
					continue;
				}
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1478);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1506);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_DOUBLE(&_3$$4, min);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1498);
				continue;
			}
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1503);
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
					zephir_array_append(&b, &_4$$6, PH_SEPARATE, "tensor/vector.zep", 1498);
					continue;
				}
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1503);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1531);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_DOUBLE(&_3$$4, max);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1523);
				continue;
			}
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1528);
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
					zephir_array_append(&b, &_4$$6, PH_SEPARATE, "tensor/vector.zep", 1523);
					continue;
				}
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1528);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1555);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			if (ZEPHIR_GT_LONG(&valueA, 0)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_LONG(&_3$$4, 1);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1547);
			} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZVAL_LONG(&_4$$5, -1);
				zephir_array_append(&b, &_4$$5, PH_SEPARATE, "tensor/vector.zep", 1549);
			} else {
				ZEPHIR_INIT_NVAR(&_5$$6);
				ZVAL_LONG(&_5$$6, 0);
				zephir_array_append(&b, &_5$$6, PH_SEPARATE, "tensor/vector.zep", 1551);
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
					zephir_array_append(&b, &_6$$8, PH_SEPARATE, "tensor/vector.zep", 1547);
				} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
					ZEPHIR_INIT_NVAR(&_7$$9);
					ZVAL_LONG(&_7$$9, -1);
					zephir_array_append(&b, &_7$$9, PH_SEPARATE, "tensor/vector.zep", 1549);
				} else {
					ZEPHIR_INIT_NVAR(&_8$$10);
					ZVAL_LONG(&_8$$10, 0);
					zephir_array_append(&b, &_8$$10, PH_SEPARATE, "tensor/vector.zep", 1551);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1573);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			zephir_negate(&valueA);
			zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1570);
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
				zephir_array_append(&b, &valueA, PH_SEPARATE, "tensor/vector.zep", 1570);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, multiplyMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1588);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1598);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_multiply(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1595);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_multiply(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1595);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, divideMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1613);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1623);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_divide(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1620);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_divide(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1620);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this vector to a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, addMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1638);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1648);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_add(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1645);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_add(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1645);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a matrix from this vector.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, subtractMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1663);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1673);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_subtract(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1670);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_subtract(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1670);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this vector to the power of a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, powMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1688);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1698);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_pow(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1695);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_pow(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1695);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Mod this vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, modMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1713);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1723);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_mod(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1720);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_mod(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1720);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, equalMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1738);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1748);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_equal(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1745);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_equal(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1745);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, notEqualMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1763);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1773);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_not_equal(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1770);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_not_equal(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1770);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, greaterMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1788);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1798);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_greater(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1795);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_greater(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1795);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, greaterEqualMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1813);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1823);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_greater_equal(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1820);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_greater_equal(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1820);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, lessMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1838);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1848);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_less(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1845);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_less(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1845);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of this vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Vector, lessEqualMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$4, _13$$5, _14$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " columns but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1863);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1873);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			tensor_less_equal(&_11$$4, &_12$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/vector.zep", 1870);
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
				ZEPHIR_INIT_NVAR(&_13$$5);
				zephir_read_property(&_14$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				tensor_less_equal(&_13$$5, &_14$$5, &rowB);
				zephir_array_append(&c, &_13$$5, PH_SEPARATE, "tensor/vector.zep", 1870);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this vector with another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, multiplyVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1888);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_multiply(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector by another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, divideVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1906);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_divide(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this vector to another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, addVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1924);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_add(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a vector from this vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, subtractVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1942);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_subtract(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this vector to a power of another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, powVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1960);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_pow(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this vector with another vector elementwise.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, modVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1978);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_mod(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a
 * another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, equalVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1997);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_equal(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, notEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2015);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_not_equal(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2033);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_greater(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2051);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_greater_equal(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2069);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_less(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of this vector and a another vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, _8, _9, _10, _2$$3, _3$$3, _5$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2087);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_less_equal(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this vector by a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, multiplyScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2105);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_multiply_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector by a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, divideScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2123);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_divide_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add a scalar to this vector.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, addScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2141);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_add_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a scalar from this vector.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, subtractScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2159);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_subtract_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise the vector to a the power of a scalar value.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, powScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2177);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_pow_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this vector with a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, modScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2195);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_mod_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a
 * scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, equalScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2214);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_equal_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a
 * scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, notEqualScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2233);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_not_equal_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector
 * and a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2252);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_greater_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this vector and a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterEqualScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2271);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_greater_equal_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector
 * and a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2290);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_less_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this vector and a scalar.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessEqualScalar) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, _5, _6, _2$$3, _3$$3, _4$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	_0 = !(Z_TYPE_P(b) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 2, b);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (UNEXPECTED(_0)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, b);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2309);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_5);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_less_equal_scalar(&_5, &_6, b);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &_5);
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
 * @throws \Tensor\Exceptions\RuntimeException
 */
PHP_METHOD(Tensor_Vector, offsetSet) {

	zval *index, index_sub, *values, values_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&values_sub);

	zephir_fetch_params_without_memory_grow(2, 0, &index, &values);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(tensor_exceptions_runtimeexception_ce, "Vector cannot be mutated directly.", "tensor/vector.zep", 2332);
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset(&_0, index));

}

/**
 * @param mixed index
 * @throws \Tensor\Exceptions\RuntimeException
 */
PHP_METHOD(Tensor_Vector, offsetUnset) {

	zval *index, index_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &index);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(tensor_exceptions_runtimeexception_ce, "Vector cannot be mutated directly.", "tensor/vector.zep", 2352);
	return;

}

/**
 * Return a row from the matrix at the given index.
 *
 * @param mixed index
 * @throws \Tensor\Exceptions\InvalidArgumentException
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	if (EXPECTED(zephir_array_isset_fetch(&value, &_0, index, 0))) {
		RETURN_CCTOR(&value);
	}
	ZEPHIR_INIT_VAR(&_1);
	object_init_ex(&_1, tensor_exceptions_invalidargumentexception_ce);
	zephir_get_strval(&_2, index);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SSVS(&_3, "Element not found at", " offset ", &_2, ".");
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_1, "tensor/vector.zep", 2371);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
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
	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_join_str(&_0, SL(" "), &_1);
	ZEPHIR_INIT_VAR(&_2);
	ZEPHIR_GET_CONSTANT(&_2, "PHP_EOL");
	ZEPHIR_CONCAT_SVSV(return_value, "[ ", &_0, " ]", &_2);
	RETURN_MM();

}

