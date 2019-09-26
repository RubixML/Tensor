
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
#include "kernel/math.h"
#include "kernel/string.h"


/**
 * Vector
 *
 * A one dimensional (rank 1) tensor with integer and/or floating point elements..
 *
 * @category    Machine Learning
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
	zend_declare_property_null(tensor_vector_ce, SL("a"), ZEND_ACC_PROTECTED TSRMLS_CC);

	/**
	 * The number of elements in the vector.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_vector_ce, SL("n"), ZEND_ACC_PROTECTED TSRMLS_CC);

	tensor_vector_ce->create_object = zephir_init_properties_Tensor_Vector;
	/**
	 * A small number used in substitution of 0.
	 */
	zephir_declare_class_constant_double(tensor_vector_ce, SL("EPSILON"), 0.000000001);

	/**
	 * Two multiplied by pi.
	 */
	zephir_declare_class_constant_double(tensor_vector_ce, SL("TWO_PI"), 6.28318530718);

	zephir_declare_class_constant_double(tensor_vector_ce, SL("M_E"), 2.71828);

	zend_class_implements(tensor_vector_ce TSRMLS_CC, 1, tensor_tensor_ce);
	return SUCCESS;

}

/**
 * Factory method to build a new vector from an array.
 *
 * @param array a
 * @return mixed
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
 * @return mixed
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 79 TSRMLS_CC);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 96 TSRMLS_CC);
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
		zephir_gettype(&_3$$3, value TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Value must be an", " integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 115 TSRMLS_CC);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/vector.zep", 120 TSRMLS_CC);
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

	zend_bool _4;
	zval a;
	zend_ulong i = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _7$$4, _8$$4, _9$$4, _11$$4, _12$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, _5, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 137 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	_6 = (n - 1);
	_5 = 0;
	_4 = 0;
	if (_5 <= _6) {
		while (1) {
			if (_4) {
				_5++;
				if (!(_5 <= _6)) {
					break;
				}
			} else {
				_4 = 1;
			}
			i = _5;
			ZEPHIR_INIT_NVAR(&_7$$4);
			ZEPHIR_MM_GET_CONSTANT(&_7$$4, "PHP_INT_MAX");
			ZVAL_LONG(&_8$$4, 0);
			ZEPHIR_CALL_FUNCTION(&_9$$4, "rand", &_10, 6, &_8$$4, &_7$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_11$$4);
			ZEPHIR_MM_GET_CONSTANT(&_11$$4, "PHP_INT_MAX");
			ZEPHIR_INIT_LNVAR(_12$$4);
			div_function(&_12$$4, &_9$$4, &_11$$4 TSRMLS_CC);
			zephir_array_append(&a, &_12$$4, PH_SEPARATE, "tensor/vector.zep", 144);
		}
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
	zend_bool _4;
	zval a;
	zend_ulong i = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_15 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _7$$4, _8$$4, _9$$4, _11$$4, _12$$4, _13$$4, _14$$4, _16$$4, _17$$4, _18$$5, _19$$5, _20$$5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, _5, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 161 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	_6 = (n - 1);
	_5 = 0;
	_4 = 0;
	if (_5 <= _6) {
		while (1) {
			if (_4) {
				_5 += 2;
				if (!(_5 <= _6)) {
					break;
				}
			} else {
				_4 = 1;
			}
			i = _5;
			ZEPHIR_INIT_NVAR(&_7$$4);
			ZEPHIR_MM_GET_CONSTANT(&_7$$4, "PHP_INT_MAX");
			ZVAL_LONG(&_8$$4, 0);
			ZEPHIR_CALL_FUNCTION(&_9$$4, "rand", &_10, 6, &_8$$4, &_7$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_11$$4);
			ZEPHIR_MM_GET_CONSTANT(&_11$$4, "PHP_INT_MAX");
			ZEPHIR_INIT_LNVAR(_12$$4);
			div_function(&_12$$4, &_9$$4, &_11$$4 TSRMLS_CC);
			r1$$4 = zephir_get_numberval(&_12$$4);
			ZEPHIR_INIT_NVAR(&_11$$4);
			ZEPHIR_MM_GET_CONSTANT(&_11$$4, "PHP_INT_MAX");
			ZVAL_LONG(&_8$$4, 0);
			ZEPHIR_CALL_FUNCTION(&_9$$4, "rand", &_10, 6, &_8$$4, &_11$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_13$$4);
			ZEPHIR_MM_GET_CONSTANT(&_13$$4, "PHP_INT_MAX");
			ZEPHIR_INIT_LNVAR(_14$$4);
			div_function(&_14$$4, &_9$$4, &_13$$4 TSRMLS_CC);
			r2$$4 = zephir_get_numberval(&_14$$4);
			ZVAL_DOUBLE(&_8$$4, r1$$4);
			ZEPHIR_CALL_FUNCTION(&_9$$4, "log", &_15, 7, &_8$$4);
			zephir_check_call_status();
			ZVAL_DOUBLE(&_8$$4, (-2.0 * zephir_get_numberval(&_9$$4)));
			r$$4 = sqrt((-2.0 * zephir_get_numberval(&_9$$4)));
			phi$$4 = (r2$$4 * 6.28318530718);
			ZVAL_DOUBLE(&_16$$4, phi$$4);
			ZEPHIR_INIT_NVAR(&_13$$4);
			ZVAL_DOUBLE(&_13$$4, (r$$4 * sin(phi$$4)));
			zephir_array_append(&a, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 175);
			ZVAL_DOUBLE(&_17$$4, phi$$4);
			ZEPHIR_INIT_NVAR(&_13$$4);
			ZVAL_DOUBLE(&_13$$4, (r$$4 * cos(phi$$4)));
			zephir_array_append(&a, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 176);
		}
	}
	if (zephir_fast_count_int(&a TSRMLS_CC) > n) {
		ZVAL_LONG(&_18$$5, 0);
		ZVAL_LONG(&_19$$5, n);
		ZEPHIR_CALL_FUNCTION(&_20$$5, "array_slice", NULL, 8, &a, &_18$$5, &_19$$5);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_20$$5);
	}
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a uniform random vector with mean 0 and unit variance.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, uniform) {

	zend_bool _4;
	zval a;
	zend_ulong i = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _7$$4, _8$$4, _9$$4, _11$$4, _12$$4;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, _5, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 197 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	_6 = (n - 1);
	_5 = 0;
	_4 = 0;
	if (_5 <= _6) {
		while (1) {
			if (_4) {
				_5++;
				if (!(_5 <= _6)) {
					break;
				}
			} else {
				_4 = 1;
			}
			i = _5;
			ZEPHIR_INIT_NVAR(&_7$$4);
			ZEPHIR_MM_GET_CONSTANT(&_7$$4, "PHP_INT_MAX");
			zephir_negate(&_7$$4 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZEPHIR_MM_GET_CONSTANT(&_8$$4, "PHP_INT_MAX");
			ZEPHIR_CALL_FUNCTION(&_9$$4, "rand", &_10, 6, &_7$$4, &_8$$4);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_11$$4);
			ZEPHIR_MM_GET_CONSTANT(&_11$$4, "PHP_INT_MAX");
			ZEPHIR_INIT_LNVAR(_12$$4);
			div_function(&_12$$4, &_9$$4, &_11$$4 TSRMLS_CC);
			zephir_array_append(&a, &_12$$4, PH_SEPARATE, "tensor/vector.zep", 204);
		}
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


	ZEPHIR_CALL_FUNCTION(&_0, "range", NULL, 9, start, end, interval);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 236 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_DOUBLE(&_4, (end - start));
	ZEPHIR_CALL_FUNCTION(&range, "abs", NULL, 10, &_4);
	zephir_check_call_status();
	interval = ((zephir_safe_div_zval_long(&range, ((n - 1)) TSRMLS_CC)) - ((0.000000001 * zephir_get_numberval(&range))));
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 259 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "max");
	ZEPHIR_CALL_FUNCTION(&_11, "array_map", NULL, 11, &_10, &_8, &_9);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 278 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_10);
	ZVAL_STRING(&_10, "min");
	ZEPHIR_CALL_FUNCTION(&_11, "array_map", NULL, 11, &_10, &_8, &_9);
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
		ZEPHIR_CALL_FUNCTION(&_0$$3, "array_values", NULL, 12, &a);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_0$$3);
		zephir_is_iterable(&a, 0, "tensor/vector.zep", 303);
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
				if (_3$$4) {
					ZEPHIR_INIT_NVAR(&_6$$5);
					object_init_ex(&_6$$5, spl_ce_InvalidArgumentException);
					ZEPHIR_INIT_NVAR(&_7$$5);
					zephir_gettype(&_7$$5, &value TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_8$$5);
					ZEPHIR_CONCAT_SSVS(&_8$$5, "Element must be", " an integer or floating point number, ", &_7$$5, " given.");
					ZEPHIR_CALL_METHOD(NULL, &_6$$5, "__construct", &_9, 3, &_8$$5);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_6$$5, "tensor/vector.zep", 300 TSRMLS_CC);
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
					if (_10$$6) {
						ZEPHIR_INIT_NVAR(&_12$$7);
						object_init_ex(&_12$$7, spl_ce_InvalidArgumentException);
						ZEPHIR_INIT_NVAR(&_13$$7);
						zephir_gettype(&_13$$7, &value TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_14$$7);
						ZEPHIR_CONCAT_SSVS(&_14$$7, "Element must be", " an integer or floating point number, ", &_13$$7, " given.");
						ZEPHIR_CALL_METHOD(NULL, &_12$$7, "__construct", &_9, 3, &_14$$7);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_12$$7, "tensor/vector.zep", 300 TSRMLS_CC);
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
	ZVAL_LONG(&_15, zephir_fast_count_int(&a TSRMLS_CC));
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

	zephir_create_array(return_value, 1, 0 TSRMLS_CC);
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
	zephir_create_array(&_1, 1, 0 TSRMLS_CC);
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

	zval value, _0, *_1, _2;
	zval b, _3$$3, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 393);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			ZEPHIR_INIT_NVAR(&_3$$3);
			zephir_create_array(&_3$$3, 1, 0 TSRMLS_CC);
			zephir_array_fast_append(&_3$$3, &value);
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/vector.zep", 390);
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
			ZEPHIR_CALL_METHOD(&value, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_4$$4);
				zephir_create_array(&_4$$4, 1, 0 TSRMLS_CC);
				zephir_array_fast_append(&_4$$4, &value);
				zephir_array_append(&b, &_4$$4, PH_SEPARATE, "tensor/vector.zep", 390);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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

	zend_bool _5, _8$$4;
	zval b, temp$$4;
	zend_ulong i = 0, j = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_13 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0, _1$$3, _2$$3, _3$$3, _4$$3, _11$$5, _12$$5;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, nHat, k, _6, _7, _9$$4, _10$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&temp$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	nHat = (m * n);
	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_LONG_IDENTICAL(&_0, nHat)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_2$$3, nHat);
		ZEPHIR_CALL_FUNCTION(&_3$$3, "strval", NULL, 2, &_2$$3);
		zephir_check_call_status();
		zephir_read_property(&_2$$3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_VSSVS(&_4$$3, &_3$$3, " elements", " are needed but vector only has ", &_2$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 410 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	k = 0;
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	_7 = (m - 1);
	_6 = 0;
	_5 = 0;
	if (_6 <= _7) {
		while (1) {
			if (_5) {
				_6++;
				if (!(_6 <= _7)) {
					break;
				}
			} else {
				_5 = 1;
			}
			i = _6;
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			_10$$4 = (n - 1);
			_9$$4 = 0;
			_8$$4 = 0;
			if (_9$$4 <= _10$$4) {
				while (1) {
					if (_8$$4) {
						_9$$4++;
						if (!(_9$$4 <= _10$$4)) {
							break;
						}
					} else {
						_8$$4 = 1;
					}
					j = _9$$4;
					zephir_read_property(&_11$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch_long(&_12$$5, &_11$$5, k, PH_NOISY | PH_READONLY, "tensor/vector.zep", 421 TSRMLS_CC);
					zephir_array_append(&temp$$4, &_12$$5, PH_SEPARATE, "tensor/vector.zep", 421);
					k += 1;
				}
			}
			zephir_array_append(&b, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 425);
		}
	}
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_13, 0, &b);
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
	ZEPHIR_CALL_FUNCTION(&_1, "min", NULL, 13, &_0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_3, "array_search", NULL, 14, &_1, &_2);
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
	ZEPHIR_CALL_FUNCTION(&_1, "max", NULL, 15, &_0);
	zephir_check_call_status();
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_FUNCTION(&_3, "array_search", NULL, 14, &_1, &_2);
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
	ZEPHIR_CALL_FUNCTION(&_1, "array_map", NULL, 11, callback, &_0);
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
		zephir_gettype(&_3$$3, initial TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Initial value must", " be an integer or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 486 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_reduce", NULL, 16, &_5, callback, initial);
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
	zend_string *_11;
	zend_ulong _10;
	double sigma;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, value, *_8, _9, _2$$3, _3$$3, _5$$3, _12$$4, _13$$4, _14$$4, _15$$5, _16$$5, _17$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 504 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	sigma = 0.0;
	zephir_is_iterable(b, 0, "tensor/vector.zep", 514);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 511 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_14$$4);
			mul_function(&_14$$4, &_13$$4, &value TSRMLS_CC);
			sigma += zephir_get_numberval(&_14$$4);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, b, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&value, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 511 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_17$$5);
				mul_function(&_17$$5, &_16$$5, &value TSRMLS_CC);
				sigma += zephir_get_numberval(&_17$$5);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval _3$$3;
	zend_bool _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long stride, ZEPHIR_LAST_CALL_STATUS, i = 0, _10, _11, k$$6, k$$8;
	zval *b, b_sub, *stride_param = NULL, _0, _1, j, valueB, _8, _2$$3, _4$$4, _5$$4, _6$$4, _7$$4, sigma$$5, *_12$$5, _13$$5, _16$$6, _17$$7, _18$$7, _19$$7, _20$$8, _21$$9, _22$$9, _23$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&sigma$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_23$$9);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 529 TSRMLS_CC);
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
		zephir_throw_exception_debug(&_4$$4, "tensor/vector.zep", 534 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
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
			ZEPHIR_INIT_NVAR(&sigma$$5);
			ZVAL_LONG(&sigma$$5, 0);
			zephir_is_iterable(b, 0, "tensor/vector.zep", 552);
			if (Z_TYPE_P(b) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _14$$5, _15$$5, _12$$5)
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
					zephir_read_property(&_16$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					if (zephir_array_isset_long(&_16$$6, k$$6)) {
						zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						ZEPHIR_OBS_NVAR(&_18$$7);
						zephir_array_fetch_long(&_18$$7, &_17$$7, k$$6, PH_NOISY, "tensor/vector.zep", 548 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_19$$7);
						mul_function(&_19$$7, &_18$$7, &valueB TSRMLS_CC);
						ZEPHIR_ADD_ASSIGN(&sigma$$5, &_19$$7);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$5, b, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, b, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, b, "current", NULL, 0);
					zephir_check_call_status();
						k$$8 = (i - zephir_get_intval(&j));
						zephir_read_property(&_20$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						if (zephir_array_isset_long(&_20$$8, k$$8)) {
							zephir_read_property(&_21$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							ZEPHIR_OBS_NVAR(&_22$$9);
							zephir_array_fetch_long(&_22$$9, &_21$$9, k$$8, PH_NOISY, "tensor/vector.zep", 548 TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_23$$9);
							mul_function(&_23$$9, &_22$$9, &valueB TSRMLS_CC);
							ZEPHIR_ADD_ASSIGN(&sigma$$5, &_23$$9);
						}
					ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &sigma$$5, PH_SEPARATE, "tensor/vector.zep", 552);
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

	zend_string *_6$$3, *_12$$6;
	zend_ulong _5$$3, _11$$6;
	zval c, temp$$3, temp$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_15 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, n, j, valueA, valueB, _0, *_1, _2, *_3$$3, _4$$3, _7$$4, _8$$5, *_9$$6, _10$$6, _13$$7, _14$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$3);
	ZVAL_UNDEF(&temp$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&n, b, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 603);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&valueA);
			ZVAL_COPY(&valueA, _1);
			ZEPHIR_INIT_NVAR(&temp$$3);
			array_init(&temp$$3);
			zephir_is_iterable(b, 0, "tensor/vector.zep", 600);
			if (Z_TYPE_P(b) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _5$$3, _6$$3, _3$$3)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_6$$3 != NULL) { 
						ZVAL_STR_COPY(&j, _6$$3);
					} else {
						ZVAL_LONG(&j, _5$$3);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _3$$3);
					ZEPHIR_INIT_LNVAR(_7$$4);
					mul_function(&_7$$4, &valueA, &valueB TSRMLS_CC);
					zephir_array_append(&temp$$3, &_7$$4, PH_SEPARATE, "tensor/vector.zep", 597);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$3, b, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, b, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, b, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_8$$5);
						mul_function(&_8$$5, &valueA, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$3, &_8$$5, PH_SEPARATE, "tensor/vector.zep", 597);
					ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$3, PH_SEPARATE, "tensor/vector.zep", 600);
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
				ZEPHIR_INIT_NVAR(&temp$$6);
				array_init(&temp$$6);
				zephir_is_iterable(b, 0, "tensor/vector.zep", 600);
				if (Z_TYPE_P(b) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _11$$6, _12$$6, _9$$6)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_12$$6 != NULL) { 
							ZVAL_STR_COPY(&j, _12$$6);
						} else {
							ZVAL_LONG(&j, _11$$6);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _9$$6);
						ZEPHIR_INIT_LNVAR(_13$$7);
						mul_function(&_13$$7, &valueA, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$6, &_13$$7, PH_SEPARATE, "tensor/vector.zep", 597);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_10$$6, b, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_10$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, b, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, b, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_14$$8);
							mul_function(&_14$$8, &valueA, &valueB TSRMLS_CC);
							zephir_array_append(&temp$$6, &_14$$8, PH_SEPARATE, "tensor/vector.zep", 597);
						ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$6, PH_SEPARATE, "tensor/vector.zep", 600);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_15, 0, &c);
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
		zephir_throw_exception_debug(&_3$$3, "tensor/vector.zep", 617 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_5, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 622 TSRMLS_CC);
	zephir_array_fetch_long(&_7, b, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 622 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_8);
	mul_function(&_8, &_6, &_7 TSRMLS_CC);
	zephir_read_property(&_9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_9, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 622 TSRMLS_CC);
	zephir_array_fetch_long(&_7, b, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 622 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_10);
	mul_function(&_10, &_6, &_7 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_11);
	zephir_sub_function(&_11, &_8, &_10);
	zephir_array_append(&c, &_11, PH_SEPARATE, "tensor/vector.zep", 622);
	zephir_read_property(&_12, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_12, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 623 TSRMLS_CC);
	zephir_array_fetch_long(&_7, b, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 623 TSRMLS_CC);
	ZEPHIR_INIT_LNVAR(_8);
	mul_function(&_8, &_6, &_7 TSRMLS_CC);
	zephir_read_property(&_13, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_13, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 623 TSRMLS_CC);
	zephir_array_fetch_long(&_7, b, 2, PH_NOISY | PH_READONLY, "tensor/vector.zep", 623 TSRMLS_CC);
	ZEPHIR_INIT_LNVAR(_10);
	mul_function(&_10, &_6, &_7 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_14);
	zephir_sub_function(&_14, &_8, &_10);
	zephir_array_append(&c, &_14, PH_SEPARATE, "tensor/vector.zep", 623);
	zephir_read_property(&_15, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_15, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 624 TSRMLS_CC);
	zephir_array_fetch_long(&_7, b, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 624 TSRMLS_CC);
	ZEPHIR_INIT_LNVAR(_8);
	mul_function(&_8, &_6, &_7 TSRMLS_CC);
	zephir_read_property(&_16, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch_long(&_6, &_16, 1, PH_NOISY | PH_READONLY, "tensor/vector.zep", 624 TSRMLS_CC);
	zephir_array_fetch_long(&_7, b, 0, PH_NOISY | PH_READONLY, "tensor/vector.zep", 624 TSRMLS_CC);
	ZEPHIR_INIT_LNVAR(_10);
	mul_function(&_10, &_6, &_7 TSRMLS_CC);
	ZEPHIR_INIT_VAR(&_17);
	zephir_sub_function(&_17, &_8, &_10);
	zephir_array_append(&c, &_17, PH_SEPARATE, "tensor/vector.zep", 624);
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
	div_function(&_4, &_0, &_1 TSRMLS_CC);
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
	RETURN_MM_DOUBLE(zephir_sqrt(&_1 TSRMLS_CC));

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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 671 TSRMLS_CC);
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
	ZVAL_DOUBLE(&_6, zephir_safe_div_double_double(1.0, p TSRMLS_CC));
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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot multiply vector", " by a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 709 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividevector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividematrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividescalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot divide vector", " by a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 735 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot add vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 761 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SVS(&_5$$6, "Cannot subtract a ", &_4$$6, " from vector.");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 787 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot raise vector", " to a power of a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 813 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot mod vector", " with a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 839 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot compare vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 865 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot compare vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 891 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatervector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatermatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot compare vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 917 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot compare vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 943 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot compare vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 969 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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

	zend_bool _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _2, _3$$6, _4$$6, _5$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$6);
	ZVAL_UNDEF(&_4$$6);
	ZVAL_UNDEF(&_5$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	do {
		_0 = 1;
		if (_0 == zephir_instance_of_ev(b, tensor_vector_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (_0 == zephir_instance_of_ev(b, tensor_matrix_ce TSRMLS_CC)) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		_1 = Z_TYPE_P(b) == IS_LONG;
		if (!(_1)) {
			ZEPHIR_CALL_FUNCTION(&_2, "is_float", NULL, 4, b);
			zephir_check_call_status();
			_1 = zephir_is_true(&_2);
		}
		if (_0 == _1) {
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalscalar", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		}
		ZEPHIR_INIT_VAR(&_3$$6);
		object_init_ex(&_3$$6, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$6);
		zephir_gettype(&_4$$6, b TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_5$$6);
		ZEPHIR_CONCAT_SSVS(&_5$$6, "Cannot compare vector", " to a ", &_4$$6, ".");
		ZEPHIR_CALL_METHOD(NULL, &_3$$6, "__construct", NULL, 3, &_5$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$6, "tensor/vector.zep", 995 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	} while(0);

	ZEPHIR_MM_RESTORE();

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
	zval *base_param = NULL, value, _0, *_1, _2, _3$$3, _4$$3, _6$$4, _7$$4;
	double base;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
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
		base = 2.71828;
	} else {
		base = zephir_get_doubleval(base_param);
	}


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1065);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			ZVAL_DOUBLE(&_3$$3, base);
			ZEPHIR_CALL_FUNCTION(&_4$$3, "log", &_5, 7, &value, &_3$$3);
			zephir_check_call_status();
			zephir_array_append(&b, &_4$$3, PH_SEPARATE, "tensor/vector.zep", 1062);
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
			ZEPHIR_CALL_METHOD(&value, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZVAL_DOUBLE(&_6$$4, base);
				ZEPHIR_CALL_FUNCTION(&_7$$4, "log", &_5, 7, &value, &_6$$4);
				zephir_check_call_status();
				zephir_array_append(&b, &_7$$4, PH_SEPARATE, "tensor/vector.zep", 1062);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
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
 * Convert angles from radians to degrees.
 *
 * @return self
 */
PHP_METHOD(Tensor_Vector, degrees) {

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
PHP_METHOD(Tensor_Vector, radians) {

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

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
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

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("min", NULL, 13, &_0);
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
	ZEPHIR_RETURN_CALL_FUNCTION("max", NULL, 15, &_0);
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
	if (ZEPHIR_IS_LONG_IDENTICAL(&_0, 0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Mean is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 19, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1168 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	div_function(return_value, &_3, &_4 TSRMLS_CC);
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

	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC);
	if (ZEPHIR_IS_EMPTY(&_0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Median is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 19, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1184 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_4, 2);
	ZEPHIR_CALL_FUNCTION(&mid, "intdiv", NULL, 20, &_3, &_4);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&a, &_4);
	ZEPHIR_MAKE_REF(&a);
	ZEPHIR_CALL_FUNCTION(NULL, "sort", NULL, 21, &a);
	ZEPHIR_UNREF(&a);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (zephir_safe_mod_zval_long(&_4, 2 TSRMLS_CC) == 1) {
		ZEPHIR_OBS_VAR(&median);
		zephir_array_fetch(&median, &a, &mid, PH_NOISY, "tensor/vector.zep", 1196 TSRMLS_CC);
	} else {
		zephir_array_fetch_long(&_5$$5, &a, (zephir_get_numberval(&mid) - 1), PH_NOISY | PH_READONLY, "tensor/vector.zep", 1198 TSRMLS_CC);
		zephir_array_fetch(&_6$$5, &a, &mid, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1198 TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_7$$5);
		zephir_add_function(&_7$$5, &_5$$5, &_6$$5);
		ZEPHIR_INIT_NVAR(&median);
		ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_7$$5, 2.0 TSRMLS_CC));
	}
	RETURN_CCTOR(&median);

}

/**
 * Return the variance of the vector.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Vector, variance) {

	zval _2$$3;
	zval _0, ssd, _3, _4, _5, _6, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&ssd);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_IS_LONG_IDENTICAL(&_0, 0)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Variance is not defined for", " an empty vector.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 19, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 1248 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "mean", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "subtract", NULL, 0, &_4);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, &_3, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&ssd, &_5, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_6, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	div_function(return_value, &ssd, &_6 TSRMLS_CC);
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
	zval *precision_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, value, _4, *_5, _6, _7$$4, _8$$4, _9$$5, _10$$5;
	zend_long precision, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&value);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 1269 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_4, 0, "tensor/vector.zep", 1279);
	if (Z_TYPE_P(&_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4), _5)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _5);
			ZEPHIR_INIT_NVAR(&_7$$4);
			ZVAL_LONG(&_8$$4, precision);
			zephir_round(&_7$$4, &value, &_8$$4, NULL TSRMLS_CC);
			zephir_array_append(&b, &_7$$4, PH_SEPARATE, "tensor/vector.zep", 1276);
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
			ZEPHIR_CALL_METHOD(&value, &_4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				ZVAL_LONG(&_10$$5, precision);
				zephir_round(&_9$$5, &value, &_10$$5, NULL TSRMLS_CC);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 1276);
			ZEPHIR_CALL_METHOD(NULL, &_4, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *min_param = NULL, *max_param = NULL, _0$$3, value, _2, *_3, _4, _5$$5, _6$$6, _7$$8, _8$$9;
	double min, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&value);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/vector.zep", 1315 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/vector.zep", 1337);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _3);
			if (ZEPHIR_GT_DOUBLE(&value, max)) {
				ZEPHIR_INIT_NVAR(&_5$$5);
				ZVAL_DOUBLE(&_5$$5, max);
				zephir_array_append(&b, &_5$$5, PH_SEPARATE, "tensor/vector.zep", 1323);
				continue;
			}
			if (ZEPHIR_LT_DOUBLE(&value, min)) {
				ZEPHIR_INIT_NVAR(&_6$$6);
				ZVAL_DOUBLE(&_6$$6, min);
				zephir_array_append(&b, &_6$$6, PH_SEPARATE, "tensor/vector.zep", 1329);
				continue;
			}
			zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1334);
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
			ZEPHIR_CALL_METHOD(&value, &_2, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_GT_DOUBLE(&value, max)) {
					ZEPHIR_INIT_NVAR(&_7$$8);
					ZVAL_DOUBLE(&_7$$8, max);
					zephir_array_append(&b, &_7$$8, PH_SEPARATE, "tensor/vector.zep", 1323);
					continue;
				}
				if (ZEPHIR_LT_DOUBLE(&value, min)) {
					ZEPHIR_INIT_NVAR(&_8$$9);
					ZVAL_DOUBLE(&_8$$9, min);
					zephir_array_append(&b, &_8$$9, PH_SEPARATE, "tensor/vector.zep", 1329);
					continue;
				}
				zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1334);
			ZEPHIR_CALL_METHOD(NULL, &_2, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *min_param = NULL, value, _0, *_1, _2, _3$$4, _4$$6;
	double min;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
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
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1361);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			if (ZEPHIR_LT_DOUBLE(&value, min)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_DOUBLE(&_3$$4, min);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1353);
				continue;
			}
			zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1358);
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
			ZEPHIR_CALL_METHOD(&value, &_0, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_LT_DOUBLE(&value, min)) {
					ZEPHIR_INIT_NVAR(&_4$$6);
					ZVAL_DOUBLE(&_4$$6, min);
					zephir_array_append(&b, &_4$$6, PH_SEPARATE, "tensor/vector.zep", 1353);
					continue;
				}
				zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1358);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *max_param = NULL, value, _0, *_1, _2, _3$$4, _4$$6;
	double max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
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
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1385);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			if (ZEPHIR_GT_DOUBLE(&value, max)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_DOUBLE(&_3$$4, max);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1377);
				continue;
			}
			zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1382);
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
			ZEPHIR_CALL_METHOD(&value, &_0, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_GT_DOUBLE(&value, max)) {
					ZEPHIR_INIT_NVAR(&_4$$6);
					ZVAL_DOUBLE(&_4$$6, max);
					zephir_array_append(&b, &_4$$6, PH_SEPARATE, "tensor/vector.zep", 1377);
					continue;
				}
				zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1382);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval value, _0, *_1, _2, _3$$4, _4$$5, _5$$6, _6$$8, _7$$9, _8$$10;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
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
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1408);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			if (ZEPHIR_GT_LONG(&value, 0)) {
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZVAL_LONG(&_3$$4, 1);
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/vector.zep", 1400);
			} else if (ZEPHIR_LT_LONG(&value, 0)) {
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZVAL_LONG(&_4$$5, -1);
				zephir_array_append(&b, &_4$$5, PH_SEPARATE, "tensor/vector.zep", 1402);
			} else {
				ZEPHIR_INIT_NVAR(&_5$$6);
				ZVAL_LONG(&_5$$6, 0);
				zephir_array_append(&b, &_5$$6, PH_SEPARATE, "tensor/vector.zep", 1404);
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
			ZEPHIR_CALL_METHOD(&value, &_0, "current", NULL, 0);
			zephir_check_call_status();
				if (ZEPHIR_GT_LONG(&value, 0)) {
					ZEPHIR_INIT_NVAR(&_6$$8);
					ZVAL_LONG(&_6$$8, 1);
					zephir_array_append(&b, &_6$$8, PH_SEPARATE, "tensor/vector.zep", 1400);
				} else if (ZEPHIR_LT_LONG(&value, 0)) {
					ZEPHIR_INIT_NVAR(&_7$$9);
					ZVAL_LONG(&_7$$9, -1);
					zephir_array_append(&b, &_7$$9, PH_SEPARATE, "tensor/vector.zep", 1402);
				} else {
					ZEPHIR_INIT_NVAR(&_8$$10);
					ZVAL_LONG(&_8$$10, 0);
					zephir_array_append(&b, &_8$$10, PH_SEPARATE, "tensor/vector.zep", 1404);
				}
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval value, _0, *_1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/vector.zep", 1425);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _1);
			zephir_negate(&value TSRMLS_CC);
			zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1422);
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
			ZEPHIR_CALL_METHOD(&value, &_0, "current", NULL, 0);
			zephir_check_call_status();
				zephir_negate(&value TSRMLS_CC);
				zephir_array_append(&b, &value, PH_SEPARATE, "tensor/vector.zep", 1422);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1440 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1456);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1453);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					zephir_read_property(&_14$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_15$$5, &_14$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1450 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_16$$5);
					mul_function(&_16$$5, &_15$$5, &value TSRMLS_CC);
					zephir_array_append(&temp$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1450);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						zephir_read_property(&_17$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_18$$6, &_17$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1450 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_19$$6);
						mul_function(&_19$$6, &_18$$6, &value TSRMLS_CC);
						zephir_array_append(&temp$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1450);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1453);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1453);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						zephir_read_property(&_24$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_25$$8, &_24$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1450 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_26$$8);
						mul_function(&_26$$8, &_25$$8, &value TSRMLS_CC);
						zephir_array_append(&temp$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1450);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							zephir_read_property(&_27$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_28$$9, &_27$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1450 TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_29$$9);
							mul_function(&_29$$9, &_28$$9, &value TSRMLS_CC);
							zephir_array_append(&temp$$7, &_29$$9, PH_SEPARATE, "tensor/vector.zep", 1450);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1453);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1471 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1487);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1484);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					zephir_read_property(&_14$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_15$$5, &_14$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1481 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_16$$5);
					div_function(&_16$$5, &_15$$5, &value TSRMLS_CC);
					zephir_array_append(&temp$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1481);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						zephir_read_property(&_17$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_18$$6, &_17$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1481 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_19$$6);
						div_function(&_19$$6, &_18$$6, &value TSRMLS_CC);
						zephir_array_append(&temp$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1481);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1484);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1484);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						zephir_read_property(&_24$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_25$$8, &_24$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1481 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_26$$8);
						div_function(&_26$$8, &_25$$8, &value TSRMLS_CC);
						zephir_array_append(&temp$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1481);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							zephir_read_property(&_27$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_28$$9, &_27$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1481 TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_29$$9);
							div_function(&_29$$9, &_28$$9, &value TSRMLS_CC);
							zephir_array_append(&temp$$7, &_29$$9, PH_SEPARATE, "tensor/vector.zep", 1481);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1484);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1502 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1518);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1515);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					zephir_read_property(&_14$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_15$$5, &_14$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1512 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_16$$5);
					zephir_add_function(&_16$$5, &_15$$5, &value);
					zephir_array_append(&temp$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1512);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						zephir_read_property(&_17$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_18$$6, &_17$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1512 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_19$$6);
						zephir_add_function(&_19$$6, &_18$$6, &value);
						zephir_array_append(&temp$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1512);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1515);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1515);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						zephir_read_property(&_24$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_25$$8, &_24$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1512 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_26$$8);
						zephir_add_function(&_26$$8, &_25$$8, &value);
						zephir_array_append(&temp$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1512);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							zephir_read_property(&_27$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_28$$9, &_27$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1512 TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_29$$9);
							zephir_add_function(&_29$$9, &_28$$9, &value);
							zephir_array_append(&temp$$7, &_29$$9, PH_SEPARATE, "tensor/vector.zep", 1512);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1515);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1533 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1549);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1546);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					zephir_read_property(&_14$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_15$$5, &_14$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1543 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_16$$5);
					zephir_sub_function(&_16$$5, &_15$$5, &value);
					zephir_array_append(&temp$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1543);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						zephir_read_property(&_17$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_18$$6, &_17$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1543 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_19$$6);
						zephir_sub_function(&_19$$6, &_18$$6, &value);
						zephir_array_append(&temp$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1543);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1546);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1546);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						zephir_read_property(&_24$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_25$$8, &_24$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1543 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_26$$8);
						zephir_sub_function(&_26$$8, &_25$$8, &value);
						zephir_array_append(&temp$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1543);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							zephir_read_property(&_27$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_28$$9, &_27$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1543 TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_29$$9);
							zephir_sub_function(&_29$$9, &_28$$9, &value);
							zephir_array_append(&temp$$7, &_29$$9, PH_SEPARATE, "tensor/vector.zep", 1543);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1546);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1564 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1580);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1577);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_NVAR(&_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1574 TSRMLS_CC);
					zephir_pow_function(&_14$$5, &_16$$5, &value);
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1574);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1574 TSRMLS_CC);
						zephir_pow_function(&_17$$6, &_19$$6, &value);
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1574);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1577);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1577);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_NVAR(&_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1574 TSRMLS_CC);
						zephir_pow_function(&_24$$8, &_26$$8, &value);
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1574);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1574 TSRMLS_CC);
							zephir_pow_function(&_27$$9, &_29$$9, &value);
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1574);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1577);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1595 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1611);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1608);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					zephir_read_property(&_14$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_15$$5, &_14$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1605 TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_16$$5);
					mod_function(&_16$$5, &_15$$5, &value TSRMLS_CC);
					zephir_array_append(&temp$$4, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1605);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						zephir_read_property(&_17$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_18$$6, &_17$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1605 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_19$$6);
						mod_function(&_19$$6, &_18$$6, &value TSRMLS_CC);
						zephir_array_append(&temp$$4, &_19$$6, PH_SEPARATE, "tensor/vector.zep", 1605);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1608);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1608);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						zephir_read_property(&_24$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_25$$8, &_24$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1605 TSRMLS_CC);
						ZEPHIR_INIT_LNVAR(_26$$8);
						mod_function(&_26$$8, &_25$$8, &value TSRMLS_CC);
						zephir_array_append(&temp$$7, &_26$$8, PH_SEPARATE, "tensor/vector.zep", 1605);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							zephir_read_property(&_27$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_28$$9, &_27$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1605 TSRMLS_CC);
							ZEPHIR_INIT_LNVAR(_29$$9);
							mod_function(&_29$$9, &_28$$9, &value TSRMLS_CC);
							zephir_array_append(&temp$$7, &_29$$9, PH_SEPARATE, "tensor/vector.zep", 1605);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1608);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1627 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1643);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1640);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_LNVAR(_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1637 TSRMLS_CC);
					if (ZEPHIR_IS_EQUAL(&_16$$5, &value)) {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 0);
					}
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1637);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1637 TSRMLS_CC);
						if (ZEPHIR_IS_EQUAL(&_19$$6, &value)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1637);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1640);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1640);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_LNVAR(_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1637 TSRMLS_CC);
						if (ZEPHIR_IS_EQUAL(&_26$$8, &value)) {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 0);
						}
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1637);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1637 TSRMLS_CC);
							if (ZEPHIR_IS_EQUAL(&_29$$9, &value)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1637);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1640);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1659 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1675);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1672);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_LNVAR(_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1669 TSRMLS_CC);
					if (!ZEPHIR_IS_EQUAL(&_16$$5, &value)) {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 0);
					}
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1669);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1669 TSRMLS_CC);
						if (!ZEPHIR_IS_EQUAL(&_19$$6, &value)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1669);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1672);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1672);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_LNVAR(_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1669 TSRMLS_CC);
						if (!ZEPHIR_IS_EQUAL(&_26$$8, &value)) {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 0);
						}
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1669);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1669 TSRMLS_CC);
							if (!ZEPHIR_IS_EQUAL(&_29$$9, &value)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1669);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1672);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1691 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1707);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1704);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_LNVAR(_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1701 TSRMLS_CC);
					if (ZEPHIR_GT(&_16$$5, &value)) {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 0);
					}
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1701);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1701 TSRMLS_CC);
						if (ZEPHIR_GT(&_19$$6, &value)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1701);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1704);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1704);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_LNVAR(_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1701 TSRMLS_CC);
						if (ZEPHIR_GT(&_26$$8, &value)) {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 0);
						}
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1701);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1701 TSRMLS_CC);
							if (ZEPHIR_GT(&_29$$9, &value)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1701);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1704);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1723 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1739);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1736);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_LNVAR(_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1733 TSRMLS_CC);
					if (ZEPHIR_GE(&_16$$5, &value)) {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 0);
					}
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1733);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1733 TSRMLS_CC);
						if (ZEPHIR_GE(&_19$$6, &value)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1733);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1736);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1736);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_LNVAR(_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1733 TSRMLS_CC);
						if (ZEPHIR_GE(&_26$$8, &value)) {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 0);
						}
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1733);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1733 TSRMLS_CC);
							if (ZEPHIR_GE(&_29$$9, &value)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1733);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1736);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1755 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1771);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1768);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_LNVAR(_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1765 TSRMLS_CC);
					if (ZEPHIR_LT(&_16$$5, &value)) {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 0);
					}
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1765);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1765 TSRMLS_CC);
						if (ZEPHIR_LT(&_19$$6, &value)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1765);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1768);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1768);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_LNVAR(_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1765 TSRMLS_CC);
						if (ZEPHIR_LT(&_26$$8, &value)) {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 0);
						}
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1765);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1765 TSRMLS_CC);
							if (ZEPHIR_LT(&_29$$9, &value)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1765);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1768);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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

	zend_string *_13$$4, *_23$$7;
	zend_ulong _12$$4, _22$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, row, value, *_8, _9, _2$$3, _3$$3, _5$$3, *_10$$4, _11$$4, _14$$5, _15$$5, _16$$5, _17$$6, _18$$6, _19$$6, *_20$$7, _21$$7, _24$$8, _25$$8, _26$$8, _27$$9, _28$$9, _29$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1787 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/vector.zep", 1803);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(b), _8)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/vector.zep", 1800);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _12$$4, _13$$4, _10$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_13$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _13$$4);
					} else {
						ZVAL_LONG(&j, _12$$4);
					}
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _10$$4);
					ZEPHIR_INIT_LNVAR(_14$$5);
					zephir_read_property(&_15$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch(&_16$$5, &_15$$5, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1797 TSRMLS_CC);
					if (ZEPHIR_LE(&_16$$5, &value)) {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_14$$5);
						ZVAL_LONG(&_14$$5, 0);
					}
					zephir_array_append(&temp$$4, &_14$$5, PH_SEPARATE, "tensor/vector.zep", 1797);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_11$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_17$$6);
						zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_19$$6, &_18$$6, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1797 TSRMLS_CC);
						if (ZEPHIR_LE(&_19$$6, &value)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&temp$$4, &_17$$6, PH_SEPARATE, "tensor/vector.zep", 1797);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/vector.zep", 1800);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, b, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_9, b, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/vector.zep", 1800);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&row), _22$$7, _23$$7, _20$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_23$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _23$$7);
						} else {
							ZVAL_LONG(&j, _22$$7);
						}
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _20$$7);
						ZEPHIR_INIT_LNVAR(_24$$8);
						zephir_read_property(&_25$$8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
						zephir_array_fetch(&_26$$8, &_25$$8, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1797 TSRMLS_CC);
						if (ZEPHIR_LE(&_26$$8, &value)) {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_24$$8);
							ZVAL_LONG(&_24$$8, 0);
						}
						zephir_array_append(&temp$$7, &_24$$8, PH_SEPARATE, "tensor/vector.zep", 1797);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_21$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_21$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &row, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_27$$9);
							zephir_read_property(&_28$$9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							zephir_array_fetch(&_29$$9, &_28$$9, &j, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1797 TSRMLS_CC);
							if (ZEPHIR_LE(&_29$$9, &value)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&temp$$7, &_27$$9, PH_SEPARATE, "tensor/vector.zep", 1797);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/vector.zep", 1800);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_30, 0, &c);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1818 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1828);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			zephir_array_fetch(&_13$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1825 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_14$$4);
			mul_function(&_14$$4, &value, &_13$$4 TSRMLS_CC);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/vector.zep", 1825);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_15$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1825 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_16$$5);
				mul_function(&_16$$5, &value, &_15$$5 TSRMLS_CC);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1825);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1843 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1853);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			zephir_array_fetch(&_13$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1850 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_14$$4);
			div_function(&_14$$4, &value, &_13$$4 TSRMLS_CC);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/vector.zep", 1850);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_15$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1850 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_16$$5);
				div_function(&_16$$5, &value, &_15$$5 TSRMLS_CC);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1850);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1868 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1878);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			zephir_array_fetch(&_13$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1875 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_14$$4);
			zephir_add_function(&_14$$4, &value, &_13$$4);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/vector.zep", 1875);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_15$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1875 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_16$$5);
				zephir_add_function(&_16$$5, &value, &_15$$5);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1875);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1893 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1903);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			zephir_array_fetch(&_13$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1900 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_14$$4);
			zephir_sub_function(&_14$$4, &value, &_13$$4);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/vector.zep", 1900);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_15$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1900 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_16$$5);
				zephir_sub_function(&_16$$5, &value, &_15$$5);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1900);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1918 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1928);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1925 TSRMLS_CC);
			zephir_pow_function(&_13$$4, &value, &_14$$4);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 1925);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1925 TSRMLS_CC);
				zephir_pow_function(&_15$$5, &value, &_16$$5);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 1925);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1943 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1953);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			zephir_array_fetch(&_13$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1950 TSRMLS_CC);
			ZEPHIR_INIT_LNVAR(_14$$4);
			mod_function(&_14$$4, &value, &_13$$4 TSRMLS_CC);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/vector.zep", 1950);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_15$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1950 TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_16$$5);
				mod_function(&_16$$5, &value, &_15$$5 TSRMLS_CC);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/vector.zep", 1950);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1969 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 1979);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_LNVAR(_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1976 TSRMLS_CC);
			if (ZEPHIR_IS_EQUAL(&value, &_14$$4)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 1976);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 1976 TSRMLS_CC);
				if (ZEPHIR_IS_EQUAL(&value, &_16$$5)) {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 0);
				}
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 1976);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 1995 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2005);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_LNVAR(_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2002 TSRMLS_CC);
			if (!ZEPHIR_IS_EQUAL(&value, &_14$$4)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2002);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2002 TSRMLS_CC);
				if (!ZEPHIR_IS_EQUAL(&value, &_16$$5)) {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 0);
				}
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 2002);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2021 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2031);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_LNVAR(_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2028 TSRMLS_CC);
			if (ZEPHIR_GT(&value, &_14$$4)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2028);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2028 TSRMLS_CC);
				if (ZEPHIR_GT(&value, &_16$$5)) {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 0);
				}
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 2028);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2047 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2057);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_LNVAR(_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2054 TSRMLS_CC);
			if (ZEPHIR_GE(&value, &_14$$4)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2054);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2054 TSRMLS_CC);
				if (ZEPHIR_GE(&value, &_16$$5)) {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 0);
				}
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 2054);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2073 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2083);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_LNVAR(_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2080 TSRMLS_CC);
			if (ZEPHIR_LT(&value, &_14$$4)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2080);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2080 TSRMLS_CC);
				if (ZEPHIR_LT(&value, &_16$$5)) {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 0);
				}
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 2080);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
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
	zval *b, b_sub, _0, _1, i, value, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, _14$$4, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2099 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/vector.zep", 2109);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _9);
			ZEPHIR_INIT_LNVAR(_13$$4);
			zephir_array_fetch(&_14$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2106 TSRMLS_CC);
			if (ZEPHIR_LE(&value, &_14$$4)) {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_13$$4);
				ZVAL_LONG(&_13$$4, 0);
			}
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/vector.zep", 2106);
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
			ZEPHIR_CALL_METHOD(&value, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_15$$5);
				zephir_array_fetch(&_16$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2106 TSRMLS_CC);
				if (ZEPHIR_LE(&value, &_16$$5)) {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_15$$5);
					ZVAL_LONG(&_15$$5, 0);
				}
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/vector.zep", 2106);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this vector by a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, multiplyScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2124 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2134);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			mul_function(&_8$$4, &value, scalar TSRMLS_CC);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2131);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				mul_function(&_9$$5, &value, scalar TSRMLS_CC);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2131);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this vector by a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, divideScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2149 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2159);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			div_function(&_8$$4, &value, scalar TSRMLS_CC);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2156);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				div_function(&_9$$5, &value, scalar TSRMLS_CC);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2156);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add a scalar to this vector.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, addScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2174 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2184);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			zephir_add_function(&_8$$4, &value, scalar);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2181);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				zephir_add_function(&_9$$5, &value, scalar);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2181);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a scalar from this vector.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, subtractScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2199 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2209);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			zephir_sub_function(&_8$$4, &value, scalar);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2206);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				zephir_sub_function(&_9$$5, &value, scalar);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2206);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise the vector to a the power of a scalar value.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, powScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2224 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2234);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			zephir_pow_function(&_8$$4, &value, scalar);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2231);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_pow_function(&_9$$5, &value, scalar);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2231);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this vector with a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, modScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2249 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2259);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			mod_function(&_8$$4, &value, scalar TSRMLS_CC);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2256);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				mod_function(&_9$$5, &value, scalar TSRMLS_CC);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2256);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this vector and a
 * scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, equalScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2275 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2285);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			if (ZEPHIR_IS_EQUAL(&value, scalar)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2282);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				if (ZEPHIR_IS_EQUAL(&value, scalar)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2282);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this vector and a
 * scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, notEqualScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2301 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2311);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			if (!ZEPHIR_IS_EQUAL(&value, scalar)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2308);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				if (!ZEPHIR_IS_EQUAL(&value, scalar)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2308);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this vector
 * and a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2327 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2337);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			if (ZEPHIR_GT(&value, scalar)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2334);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				if (ZEPHIR_GT(&value, scalar)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2334);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this vector and a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, greaterEqualScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2353 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2363);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			if (ZEPHIR_GE(&value, scalar)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2360);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				if (ZEPHIR_GE(&value, scalar)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2360);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this vector
 * and a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2379 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2389);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			if (ZEPHIR_LT(&value, scalar)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2386);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				if (ZEPHIR_LT(&value, scalar)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2386);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this vector and a scalar.
 *
 * @param mixed scalar
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Vector, lessEqualScalar) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *scalar, scalar_sub, _1, value, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&scalar_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &scalar);



	_0 = !(Z_TYPE_P(scalar) == IS_LONG);
	if (_0) {
		ZEPHIR_CALL_FUNCTION(&_1, "is_float", NULL, 4, scalar);
		zephir_check_call_status();
		_0 = !zephir_is_true(&_1);
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_3$$3);
		zephir_gettype(&_3$$3, scalar TSRMLS_CC);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/vector.zep", 2405 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/vector.zep", 2415);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&value);
			ZVAL_COPY(&value, _6);
			ZEPHIR_INIT_LNVAR(_8$$4);
			if (ZEPHIR_LE(&value, scalar)) {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 1);
			} else {
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_LONG(&_8$$4, 0);
			}
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/vector.zep", 2412);
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
			ZEPHIR_CALL_METHOD(&value, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_LNVAR(_9$$5);
				if (ZEPHIR_LE(&value, scalar)) {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 1);
				} else {
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_9$$5, 0);
				}
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/vector.zep", 2412);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&value);
	ZEPHIR_RETURN_CALL_STATIC("quick", NULL, 0, &b);
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



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Vector cannot be mutated directly.", "tensor/vector.zep", 2435);
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



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Vector cannot be mutated directly.", "tensor/vector.zep", 2455);
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

	zval _2$$3, _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *index, index_sub, _0, _4, _5, _1$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index);



	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	if (!(zephir_array_isset(&_0, index))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		zephir_get_strval(&_2$$3, index);
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Element not found at ", " offset ", &_2$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/vector.zep", 2469 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_array_fetch(&_5, &_4, index, PH_NOISY | PH_READONLY, "tensor/vector.zep", 2472 TSRMLS_CC);
	RETURN_CTOR(&_5);

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
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 22, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convert the tensor into a string representation.
 *
 * @return string
 */
PHP_METHOD(Tensor_Vector, __toString) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_join_str(&_0, SL(" "), &_1 TSRMLS_CC);
	ZEPHIR_CONCAT_SVS(return_value, "[ ", &_0, " ]");
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

