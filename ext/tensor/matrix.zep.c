
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
#include "kernel/math.h"
#include "math.h"
#include "kernel/iterator.h"
#include "kernel/string.h"


/**
 * Matrix
 *
 * A two dimensional (rank 2) tensor with integer and/or floating point elements.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Matrix) {

	ZEPHIR_REGISTER_CLASS(Tensor, Matrix, tensor, matrix, tensor_matrix_method_entry, 0);

	/**
	 * A 2-dimensional sequential array that holds the values of the matrix.
	 *
	 * @var array[]
	 */
	zend_declare_property_null(tensor_matrix_ce, SL("a"), ZEND_ACC_PROTECTED);

	/**
	 * The number of rows in the matrix.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_matrix_ce, SL("m"), ZEND_ACC_PROTECTED);

	/**
	 * The number of columns in the matrix.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_matrix_ce, SL("n"), ZEND_ACC_PROTECTED);

	zend_class_implements(tensor_matrix_ce, 1, tensor_tensor_ce);
	return SUCCESS;

}

/**
 * Factory method to build a new matrix from an array.
 *
 * @param array[] a
 * @return self
 */
PHP_METHOD(Tensor_Matrix, build) {

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


	object_init_ex(return_value, tensor_matrix_ce);
	ZVAL_BOOL(&_0, 1);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 28, &a, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a new matrix foregoing any validation for quicker instantiation.
 *
 * @param array[] a
 * @return self
 */
PHP_METHOD(Tensor_Matrix, quick) {

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


	object_init_ex(return_value, tensor_matrix_ce);
	ZVAL_BOOL(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 28, &a, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return an identity matrix with dimensionality n x n.
 *
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, identity) {

	zend_bool _2, _5$$4;
	zval a, rowA;
	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0$$3, _8$$5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, _3, _4, _6$$4, _7$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &n_param);

	n = zephir_get_intval(n_param);


	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SS(&_1$$3, "Dimensionality must be", " greater than 0 on all axes.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 76);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	_4 = (n - 1);
	_3 = 0;
	_2 = 0;
	if (_3 <= _4) {
		while (1) {
			if (_2) {
				_3++;
				if (!(_3 <= _4)) {
					break;
				}
			} else {
				_2 = 1;
			}
			i = _3;
			ZEPHIR_INIT_NVAR(&rowA);
			array_init(&rowA);
			_7$$4 = (n - 1);
			_6$$4 = 0;
			_5$$4 = 0;
			if (_6$$4 <= _7$$4) {
				while (1) {
					if (_5$$4) {
						_6$$4++;
						if (!(_6$$4 <= _7$$4)) {
							break;
						}
					} else {
						_5$$4 = 1;
					}
					j = _6$$4;
					ZEPHIR_INIT_NVAR(&_8$$5);
					if (i == j) {
						ZEPHIR_INIT_NVAR(&_8$$5);
						ZVAL_LONG(&_8$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_8$$5);
						ZVAL_LONG(&_8$$5, 0);
					}
					zephir_array_append(&rowA, &_8$$5, PH_SEPARATE, "tensor/matrix.zep", 87);
				}
			}
			zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 90);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a zero matrix with the specified dimensionality.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, zeros) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, _0, _1, _2;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	ZVAL_LONG(&_0, 0);
	ZVAL_LONG(&_1, m);
	ZVAL_LONG(&_2, n);
	ZEPHIR_RETURN_CALL_SELF("fill", NULL, 0, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a one matrix with the given dimensions.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, ones) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, _0, _1, _2;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	ZVAL_LONG(&_0, 1);
	ZVAL_LONG(&_1, m);
	ZVAL_LONG(&_2, n);
	ZEPHIR_RETURN_CALL_SELF("fill", NULL, 0, &_0, &_1, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a matrix with the value of each element along the diagonal
 * and zeros everywhere else.
 *
 * @param (int|float)[] elements
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, diagonal) {

	zval _1$$3;
	zend_bool _15, _4$$4, _10$$6, _18$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, n, i = 0, j = 0, _16, _17, _19$$8, _20$$8;
	zval *elements_param = NULL, element, *_2, _3, _0$$3, _5$$4, _7$$5, _8$$5, _9$$5, _11$$6, _12$$7, _13$$7, _14$$7, _21$$9;
	zval elements, a, rowA;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&elements);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&element);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_1$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &elements_param);

	zephir_get_arrval(&elements, elements_param);


	n = zephir_fast_count_int(&elements);
	if (n < 1) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SS(&_1$$3, "Dimensionality must be", " greater than 0 on all axes.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 136);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_is_iterable(&elements, 0, "tensor/matrix.zep", 149);
	if (Z_TYPE_P(&elements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&elements), _2)
		{
			ZEPHIR_INIT_NVAR(&element);
			ZVAL_COPY(&element, _2);
			_4$$4 = !(Z_TYPE_P(&element) == IS_LONG);
			if (_4$$4) {
				ZEPHIR_CALL_FUNCTION(&_5$$4, "is_float", &_6, 4, &element);
				zephir_check_call_status();
				_4$$4 = !zephir_is_true(&_5$$4);
			}
			if (_4$$4) {
				ZEPHIR_INIT_NVAR(&_7$$5);
				object_init_ex(&_7$$5, spl_ce_InvalidArgumentException);
				ZEPHIR_INIT_NVAR(&_8$$5);
				zephir_gettype(&_8$$5, &element);
				ZEPHIR_INIT_NVAR(&_9$$5);
				ZEPHIR_CONCAT_SSVS(&_9$$5, "Diagonal element", " must be an integer or floating point number, ", &_8$$5, " given.");
				ZEPHIR_CALL_METHOD(NULL, &_7$$5, "__construct", NULL, 3, &_9$$5);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_7$$5, "tensor/matrix.zep", 145);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &elements, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_3, &elements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_3)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&element, &elements, "current", NULL, 0);
			zephir_check_call_status();
				_10$$6 = !(Z_TYPE_P(&element) == IS_LONG);
				if (_10$$6) {
					ZEPHIR_CALL_FUNCTION(&_11$$6, "is_float", &_6, 4, &element);
					zephir_check_call_status();
					_10$$6 = !zephir_is_true(&_11$$6);
				}
				if (_10$$6) {
					ZEPHIR_INIT_NVAR(&_12$$7);
					object_init_ex(&_12$$7, spl_ce_InvalidArgumentException);
					ZEPHIR_INIT_NVAR(&_13$$7);
					zephir_gettype(&_13$$7, &element);
					ZEPHIR_INIT_NVAR(&_14$$7);
					ZEPHIR_CONCAT_SSVS(&_14$$7, "Diagonal element", " must be an integer or floating point number, ", &_13$$7, " given.");
					ZEPHIR_CALL_METHOD(NULL, &_12$$7, "__construct", NULL, 3, &_14$$7);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_12$$7, "tensor/matrix.zep", 145);
					ZEPHIR_MM_RESTORE();
					return;
				}
			ZEPHIR_CALL_METHOD(NULL, &elements, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&element);
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	_17 = (n - 1);
	_16 = 0;
	_15 = 0;
	if (_16 <= _17) {
		while (1) {
			if (_15) {
				_16++;
				if (!(_16 <= _17)) {
					break;
				}
			} else {
				_15 = 1;
			}
			i = _16;
			ZEPHIR_INIT_NVAR(&rowA);
			array_init(&rowA);
			_20$$8 = (n - 1);
			_19$$8 = 0;
			_18$$8 = 0;
			if (_19$$8 <= _20$$8) {
				while (1) {
					if (_18$$8) {
						_19$$8++;
						if (!(_19$$8 <= _20$$8)) {
							break;
						}
					} else {
						_18$$8 = 1;
					}
					j = _19$$8;
					ZEPHIR_INIT_NVAR(&_21$$9);
					if (i == j) {
						ZEPHIR_OBS_NVAR(&_21$$9);
						zephir_array_fetch_long(&_21$$9, &elements, i, PH_NOISY, "tensor/matrix.zep", 157);
					} else {
						ZEPHIR_INIT_NVAR(&_21$$9);
						ZVAL_LONG(&_21$$9, 0);
					}
					zephir_array_append(&rowA, &_21$$9, PH_SEPARATE, "tensor/matrix.zep", 157);
				}
			}
			zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 160);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Fill a matrix with a given value at each element.
 *
 * @param int|float value
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, fill) {

	zval _7$$4;
	zend_bool _0, _5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *value, value_sub, *m_param = NULL, *n_param = NULL, _1, _8, _9, _10, _12, _2$$3, _3$$3, _4$$3, _6$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &value, &m_param, &n_param);

	m = zephir_get_intval(m_param);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 180);
		ZEPHIR_MM_RESTORE();
		return;
	}
	_5 = m < 1;
	if (!(_5)) {
		_5 = n < 1;
	}
	if (_5) {
		ZEPHIR_INIT_VAR(&_6$$4);
		object_init_ex(&_6$$4, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_SS(&_7$$4, "Dimensionality must be", " greater than 0 for all axes.");
		ZEPHIR_CALL_METHOD(NULL, &_6$$4, "__construct", NULL, 3, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$4, "tensor/matrix.zep", 185);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_8, 0);
	ZVAL_LONG(&_9, n);
	ZEPHIR_CALL_FUNCTION(&_10, "array_fill", &_11, 5, &_8, &_9, value);
	zephir_check_call_status();
	ZVAL_LONG(&_8, 0);
	ZVAL_LONG(&_9, m);
	ZEPHIR_CALL_FUNCTION(&_12, "array_fill", &_11, 5, &_8, &_9, &_10);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_12);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a random uniform matrix with values between 0 and 1.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, rand) {

	zval _2$$3;
	zval a, rowA;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, max, _1$$3, _3$$5, _4$$5;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	_0 = m < 1;
	if (!(_0)) {
		_0 = n < 1;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Dimensionality must be", " greater than 0 for all axes.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 203);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_CALL_FUNCTION(&max, "mt_getrandmax", NULL, 6);
	zephir_check_call_status();
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA);
		array_init(&rowA);
		while (1) {
			if (!(zephir_fast_count_int(&rowA) < n)) {
				break;
			}
			ZVAL_LONG(&_3$$5, 0);
			ZEPHIR_INIT_NVAR(&_4$$5);
			ZVAL_DOUBLE(&_4$$5, zephir_safe_div_long_zval(zephir_mt_rand(zephir_get_intval(&_3$$5), zephir_get_intval(&max)), &max));
			zephir_array_append(&rowA, &_4$$5, PH_SEPARATE, "tensor/matrix.zep", 215);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 218);
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a standard normally (Gaussian( distributed random matrix of
 * specified dimensionality.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, gaussian) {

	zval _2$$3;
	zval a, rowA, extras;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL;
	zval *m_param = NULL, *n_param = NULL, r, phi, max, _1$$3, _3$$5, _5$$6, _6$$6, _7$$6, _9$$6, _10$$6, _11$$7;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&r);
	ZVAL_UNDEF(&phi);
	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&extras);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	_0 = m < 1;
	if (!(_0)) {
		_0 = n < 1;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Dimensionality must be", " greater than 0 for all axes.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 237);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_INIT_VAR(&extras);
	array_init(&extras);
	ZEPHIR_CALL_FUNCTION(&max, "mt_getrandmax", NULL, 6);
	zephir_check_call_status();
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA);
		array_init(&rowA);
		if (!(ZEPHIR_IS_EMPTY(&extras))) {
			ZEPHIR_MAKE_REF(&extras);
			ZEPHIR_CALL_FUNCTION(&_3$$5, "array_pop", &_4, 29, &extras);
			ZEPHIR_UNREF(&extras);
			zephir_check_call_status();
			zephir_array_append(&rowA, &_3$$5, PH_SEPARATE, "tensor/matrix.zep", 251);
		}
		while (1) {
			if (!(zephir_fast_count_int(&rowA) < n)) {
				break;
			}
			ZVAL_LONG(&_5$$6, 0);
			ZVAL_DOUBLE(&_6$$6, zephir_safe_div_long_zval(zephir_mt_rand(zephir_get_intval(&_5$$6), zephir_get_intval(&max)), &max));
			ZEPHIR_CALL_FUNCTION(&_7$$6, "log", &_8, 7, &_6$$6);
			zephir_check_call_status();
			ZVAL_DOUBLE(&_6$$6, (-2.0 * zephir_get_numberval(&_7$$6)));
			ZEPHIR_INIT_NVAR(&r);
			ZVAL_DOUBLE(&r, sqrt((-2.0 * zephir_get_numberval(&_7$$6))));
			ZVAL_LONG(&_9$$6, 0);
			ZEPHIR_INIT_NVAR(&phi);
			ZVAL_DOUBLE(&phi, (zephir_safe_div_long_zval(zephir_mt_rand(zephir_get_intval(&_9$$6), zephir_get_intval(&max)), &max) * 6.28318530718));
			ZEPHIR_INIT_NVAR(&_10$$6);
			ZVAL_DOUBLE(&_10$$6, (zephir_get_numberval(&r) * zephir_sin(&phi)));
			zephir_array_append(&rowA, &_10$$6, PH_SEPARATE, "tensor/matrix.zep", 259);
			ZEPHIR_INIT_NVAR(&_10$$6);
			ZVAL_DOUBLE(&_10$$6, (zephir_get_numberval(&r) * zephir_cos(&phi)));
			zephir_array_append(&rowA, &_10$$6, PH_SEPARATE, "tensor/matrix.zep", 260);
		}
		if (zephir_fast_count_int(&rowA) > n) {
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(&_11$$7, "array_pop", &_4, 29, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			zephir_array_append(&extras, &_11$$7, PH_SEPARATE, "tensor/matrix.zep", 264);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 267);
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generate a m x n matrix with elements from a Poisson distribution.
 *
 * @param int m
 * @param int n
 * @param float lambda
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, poisson) {

	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	double lambda, l = 0, p = 0;
	zval *m_param = NULL, *n_param = NULL, *lambda_param = NULL, _0, _1, max, _2$$5, _3$$4;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, k = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &m_param, &n_param, &lambda_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);
	if (!lambda_param) {
		lambda = 1.0;
	} else {
		lambda = zephir_get_doubleval(lambda_param);
	}


	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZVAL_DOUBLE(&_0, -lambda);
	ZEPHIR_CALL_FUNCTION(&_1, "exp", NULL, 9, &_0);
	zephir_check_call_status();
	l = zephir_get_doubleval(&_1);
	ZEPHIR_CALL_FUNCTION(&max, "mt_getrandmax", NULL, 6);
	zephir_check_call_status();
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA);
		array_init(&rowA);
		while (1) {
			if (!(zephir_fast_count_int(&rowA) < n)) {
				break;
			}
			k = 0;
			p = 1.0;
			while (1) {
				if (!(p > l)) {
					break;
				}
				k++;
				ZVAL_LONG(&_2$$5, 0);
				p *= zephir_safe_div_long_zval(zephir_mt_rand(zephir_get_intval(&_2$$5), zephir_get_intval(&max)), &max);
			}
			ZEPHIR_INIT_NVAR(&_3$$4);
			ZVAL_LONG(&_3$$4, (k - 1));
			zephir_array_append(&rowA, &_3$$4, PH_SEPARATE, "tensor/matrix.zep", 306);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 309);
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a random uniformly distributed matrix with values between -1 and 1.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, uniform) {

	zval _2$$3;
	zval a, rowA;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, max, _1$$3, _3$$5;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	_0 = m < 1;
	if (!(_0)) {
		_0 = n < 1;
	}
	if (_0) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Dimensionality must be", " greater than 0 for all axes.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 327);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_CALL_FUNCTION(&max, "mt_getrandmax", NULL, 6);
	zephir_check_call_status();
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA);
		array_init(&rowA);
		while (1) {
			if (!(zephir_fast_count_int(&rowA) < n)) {
				break;
			}
			zephir_negate(&max);
			ZEPHIR_INIT_NVAR(&_3$$5);
			ZVAL_DOUBLE(&_3$$5, zephir_safe_div_long_zval(zephir_mt_rand(zephir_get_intval(&max), zephir_get_intval(&max)), &max));
			zephir_array_append(&rowA, &_3$$5, PH_SEPARATE, "tensor/matrix.zep", 339);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 342);
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elementwise minimum of two matrices.
 *
 * @param \Tensor\Matrix a
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, minimum) {

	zend_object_iterator *_6;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *b, b_sub, _0, _1, i, rowA, _2$$3, _3$$3, _4$$3, _5$$3, _7$$4, _8$$4, _9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &b);



	ZEPHIR_CALL_METHOD(&_0, a, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, b, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_SVSVS(&_5$$3, "Matrix A is ", &_3$$3, " but Matrix B is ", &_4$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 360);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	_6 = zephir_get_iterator(a);
	_6->funcs->rewind(_6);
	for (;_6->funcs->valid(_6) == SUCCESS && !EG(exception); _6->funcs->move_forward(_6)) {
		ZEPHIR_GET_IMKEY(i, _6);
		{
			ZEPHIR_ITERATOR_COPY(&rowA, _6);
		}
		zephir_array_fetch(&_7$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 367);
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "min");
		ZEPHIR_CALL_FUNCTION(&_9$$4, "array_map", &_10, 12, &_8$$4, &rowA, &_7$$4);
		zephir_check_call_status();
		zephir_array_append(&c, &_9$$4, PH_SEPARATE, "tensor/matrix.zep", 367);
	}
	zend_iterator_dtor(_6);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elementwise maximum of two matrices.
 *
 * @param \Tensor\Matrix a
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, maximum) {

	zend_object_iterator *_6;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *b, b_sub, _0, _1, i, rowA, _2$$3, _3$$3, _4$$3, _5$$3, _7$$4, _8$$4, _9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &b);



	ZEPHIR_CALL_METHOD(&_0, a, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, b, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_SVSVS(&_5$$3, "Matrix A is ", &_3$$3, " but Matrix B is ", &_4$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 385);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	_6 = zephir_get_iterator(a);
	_6->funcs->rewind(_6);
	for (;_6->funcs->valid(_6) == SUCCESS && !EG(exception); _6->funcs->move_forward(_6)) {
		ZEPHIR_GET_IMKEY(i, _6);
		{
			ZEPHIR_ITERATOR_COPY(&rowA, _6);
		}
		zephir_array_fetch(&_7$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 392);
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "max");
		ZEPHIR_CALL_FUNCTION(&_9$$4, "array_map", &_10, 12, &_8$$4, &rowA, &_7$$4);
		zephir_check_call_status();
		zephir_array_append(&c, &_9$$4, PH_SEPARATE, "tensor/matrix.zep", 392);
	}
	zend_iterator_dtor(_6);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a matrix by stacking an array of vectors.
 *
 * @param \Tensor\Vector[] vectors
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, stack) {

	zval _12$$7, _23$$11;
	zend_bool columnwise, _6$$4, _17$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *vectors_param = NULL, vector, proto, size, *_0, _1, b, _25, _2$$5, _3$$5, _4$$5, _10$$4, _13$$4, _7$$6, _8$$6, _9$$6, _11$$7, _14$$9, _15$$9, _16$$9, _21$$8, _24$$8, _18$$10, _19$$10, _20$$10, _22$$11;
	zval vectors, a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&vectors);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&vector);
	ZVAL_UNDEF(&proto);
	ZVAL_UNDEF(&size);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_14$$9);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&_20$$10);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_23$$11);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &vectors_param);

	zephir_get_arrval(&vectors, vectors_param);


	if (ZEPHIR_IS_EMPTY(&vectors)) {
		ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_MAKE_REF(&vectors);
	ZEPHIR_CALL_FUNCTION(&proto, "reset", NULL, 30, &vectors);
	ZEPHIR_UNREF(&vectors);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&size, &proto, "size", NULL, 0);
	zephir_check_call_status();
	columnwise = zephir_instance_of_ev(&proto, tensor_columnvector_ce);
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	zephir_is_iterable(&vectors, 0, "tensor/matrix.zep", 440);
	if (Z_TYPE_P(&vectors) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&vectors), _0)
		{
			ZEPHIR_INIT_NVAR(&vector);
			ZVAL_COPY(&vector, _0);
			if (UNEXPECTED(!((zephir_instance_of_ev(&vector, tensor_vector_ce))))) {
				ZEPHIR_INIT_NVAR(&_2$$5);
				object_init_ex(&_2$$5, spl_ce_InvalidArgumentException);
				ZEPHIR_INIT_NVAR(&_3$$5);
				zephir_gettype(&_3$$5, &vector);
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZEPHIR_CONCAT_SSVS(&_4$$5, "Cannot stack a non", " vector, ", &_3$$5, " found.");
				ZEPHIR_CALL_METHOD(NULL, &_2$$5, "__construct", &_5, 3, &_4$$5);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_2$$5, "tensor/matrix.zep", 424);
				ZEPHIR_MM_RESTORE();
				return;
			}
			_6$$4 = columnwise;
			if (_6$$4) {
				_6$$4 = !((zephir_instance_of_ev(&vector, tensor_columnvector_ce)));
			}
			if (UNEXPECTED(_6$$4)) {
				ZEPHIR_INIT_NVAR(&_7$$6);
				object_init_ex(&_7$$6, spl_ce_InvalidArgumentException);
				ZEPHIR_INIT_NVAR(&_8$$6);
				zephir_gettype(&_8$$6, &vector);
				ZEPHIR_INIT_NVAR(&_9$$6);
				ZEPHIR_CONCAT_SSVS(&_9$$6, "Cannot stack a non", " column vector, ", &_8$$6, " found.");
				ZEPHIR_CALL_METHOD(NULL, &_7$$6, "__construct", &_5, 3, &_9$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_7$$6, "tensor/matrix.zep", 429);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_10$$4, &vector, "size", NULL, 0);
			zephir_check_call_status();
			if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_10$$4, &size))) {
				ZEPHIR_INIT_NVAR(&_11$$7);
				object_init_ex(&_11$$7, spl_ce_InvalidArgumentException);
				ZEPHIR_INIT_NVAR(&_12$$7);
				ZEPHIR_CONCAT_SS(&_12$$7, "Vectors must", " all be the same size.");
				ZEPHIR_CALL_METHOD(NULL, &_11$$7, "__construct", &_5, 3, &_12$$7);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_11$$7, "tensor/matrix.zep", 434);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_13$$4, &vector, "asarray", NULL, 0);
			zephir_check_call_status();
			zephir_array_append(&a, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 437);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &vectors, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_1, &vectors, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_1)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&vector, &vectors, "current", NULL, 0);
			zephir_check_call_status();
				if (UNEXPECTED(!((zephir_instance_of_ev(&vector, tensor_vector_ce))))) {
					ZEPHIR_INIT_NVAR(&_14$$9);
					object_init_ex(&_14$$9, spl_ce_InvalidArgumentException);
					ZEPHIR_INIT_NVAR(&_15$$9);
					zephir_gettype(&_15$$9, &vector);
					ZEPHIR_INIT_NVAR(&_16$$9);
					ZEPHIR_CONCAT_SSVS(&_16$$9, "Cannot stack a non", " vector, ", &_15$$9, " found.");
					ZEPHIR_CALL_METHOD(NULL, &_14$$9, "__construct", &_5, 3, &_16$$9);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_14$$9, "tensor/matrix.zep", 424);
					ZEPHIR_MM_RESTORE();
					return;
				}
				_17$$8 = columnwise;
				if (_17$$8) {
					_17$$8 = !((zephir_instance_of_ev(&vector, tensor_columnvector_ce)));
				}
				if (UNEXPECTED(_17$$8)) {
					ZEPHIR_INIT_NVAR(&_18$$10);
					object_init_ex(&_18$$10, spl_ce_InvalidArgumentException);
					ZEPHIR_INIT_NVAR(&_19$$10);
					zephir_gettype(&_19$$10, &vector);
					ZEPHIR_INIT_NVAR(&_20$$10);
					ZEPHIR_CONCAT_SSVS(&_20$$10, "Cannot stack a non", " column vector, ", &_19$$10, " found.");
					ZEPHIR_CALL_METHOD(NULL, &_18$$10, "__construct", &_5, 3, &_20$$10);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_18$$10, "tensor/matrix.zep", 429);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_21$$8, &vector, "size", NULL, 0);
				zephir_check_call_status();
				if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_21$$8, &size))) {
					ZEPHIR_INIT_NVAR(&_22$$11);
					object_init_ex(&_22$$11, spl_ce_InvalidArgumentException);
					ZEPHIR_INIT_NVAR(&_23$$11);
					ZEPHIR_CONCAT_SS(&_23$$11, "Vectors must", " all be the same size.");
					ZEPHIR_CALL_METHOD(NULL, &_22$$11, "__construct", &_5, 3, &_23$$11);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_22$$11, "tensor/matrix.zep", 434);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_24$$8, &vector, "asarray", NULL, 0);
				zephir_check_call_status();
				zephir_array_append(&a, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 437);
			ZEPHIR_CALL_METHOD(NULL, &vectors, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&vector);
	ZEPHIR_CALL_SELF(&b, "quick", NULL, 0, &a);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_25);
	if (columnwise) {
		ZEPHIR_CALL_METHOD(&_25, &b, "transpose", NULL, 0);
		zephir_check_call_status();
	} else {
		ZEPHIR_CPY_WRT(&_25, &b);
	}
	RETURN_CCTOR(&_25);

}

/**
 * @param array[] a
 * @param bool validate
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Matrix, __construct) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL, *_13 = NULL, *_18 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, m, n;
	zend_bool validate, _16$$6, _22$$8, _34$$12, _39$$14;
	zval *a_param = NULL, *validate_param = NULL, row, value, _0, _1, _2, _3, _44, _4$$3, *_5$$3, _6$$3, _7$$5, _8$$5, _9$$5, _11$$5, _12$$5, *_14$$4, _15$$4, _17$$6, _19$$7, _20$$7, _21$$7, _23$$8, _24$$9, _25$$9, _26$$9, _27$$11, _28$$11, _29$$11, _30$$11, _31$$11, *_32$$10, _33$$10, _35$$12, _36$$13, _37$$13, _38$$13, _40$$14, _41$$15, _42$$15, _43$$15;
	zval a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_44);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_27$$11);
	ZVAL_UNDEF(&_28$$11);
	ZVAL_UNDEF(&_29$$11);
	ZVAL_UNDEF(&_30$$11);
	ZVAL_UNDEF(&_31$$11);
	ZVAL_UNDEF(&_33$$10);
	ZVAL_UNDEF(&_35$$12);
	ZVAL_UNDEF(&_36$$13);
	ZVAL_UNDEF(&_37$$13);
	ZVAL_UNDEF(&_38$$13);
	ZVAL_UNDEF(&_40$$14);
	ZVAL_UNDEF(&_41$$15);
	ZVAL_UNDEF(&_42$$15);
	ZVAL_UNDEF(&_43$$15);

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


	m = zephir_fast_count_int(&a);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CALL_FUNCTION(&_1, "current", NULL, 31, &a);
	zephir_check_call_status();
	if (Z_TYPE_P(&_1) == IS_ARRAY) {
		ZEPHIR_CALL_FUNCTION(&_2, "current", NULL, 31, &a);
		zephir_check_call_status();
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_LONG(&_0, zephir_fast_count_int(&_2));
	} else {
		ZEPHIR_INIT_NVAR(&_0);
		ZVAL_LONG(&_0, 1);
	}
	n = zephir_get_numberval(&_0);
	ZEPHIR_INIT_VAR(&_3);
	if (m == 0) {
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_LONG(&_3, 0);
	} else {
		ZEPHIR_INIT_NVAR(&_3);
		ZVAL_LONG(&_3, n);
	}
	n = zephir_get_numberval(&_3);
	if (validate) {
		ZEPHIR_CALL_FUNCTION(&_4$$3, "array_values", NULL, 13, &a);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_4$$3);
		zephir_is_iterable(&a, 0, "tensor/matrix.zep", 477);
		if (Z_TYPE_P(&a) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&a), _5$$3)
			{
				ZEPHIR_INIT_NVAR(&row);
				ZVAL_COPY(&row, _5$$3);
				if (UNEXPECTED(zephir_fast_count_int(&row) != n)) {
					ZEPHIR_INIT_NVAR(&_7$$5);
					object_init_ex(&_7$$5, spl_ce_InvalidArgumentException);
					ZVAL_LONG(&_8$$5, n);
					ZEPHIR_CALL_FUNCTION(&_9$$5, "strval", &_10, 2, &_8$$5);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_11$$5);
					ZVAL_LONG(&_11$$5, zephir_fast_count_int(&row));
					ZEPHIR_INIT_NVAR(&_12$$5);
					ZEPHIR_CONCAT_SSVSVS(&_12$$5, "The number of columns", " must be equal for all rows, ", &_9$$5, " needed but ", &_11$$5, " given.");
					ZEPHIR_CALL_METHOD(NULL, &_7$$5, "__construct", &_13, 3, &_12$$5);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_7$$5, "tensor/matrix.zep", 466);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_is_iterable(&row, 0, "tensor/matrix.zep", 476);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _14$$4)
					{
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _14$$4);
						_16$$6 = !(Z_TYPE_P(&value) == IS_LONG);
						if (_16$$6) {
							ZEPHIR_CALL_FUNCTION(&_17$$6, "is_float", &_18, 4, &value);
							zephir_check_call_status();
							_16$$6 = !zephir_is_true(&_17$$6);
						}
						if (UNEXPECTED(_16$$6)) {
							ZEPHIR_INIT_NVAR(&_19$$7);
							object_init_ex(&_19$$7, spl_ce_InvalidArgumentException);
							ZEPHIR_INIT_NVAR(&_20$$7);
							zephir_gettype(&_20$$7, &value);
							ZEPHIR_INIT_NVAR(&_21$$7);
							ZEPHIR_CONCAT_SSVS(&_21$$7, "Matrix element must", " be an integer or float, ", &_20$$7, " given.");
							ZEPHIR_CALL_METHOD(NULL, &_19$$7, "__construct", &_13, 3, &_21$$7);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_19$$7, "tensor/matrix.zep", 473);
							ZEPHIR_MM_RESTORE();
							return;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_15$$4, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_15$$4)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							_22$$8 = !(Z_TYPE_P(&value) == IS_LONG);
							if (_22$$8) {
								ZEPHIR_CALL_FUNCTION(&_23$$8, "is_float", &_18, 4, &value);
								zephir_check_call_status();
								_22$$8 = !zephir_is_true(&_23$$8);
							}
							if (UNEXPECTED(_22$$8)) {
								ZEPHIR_INIT_NVAR(&_24$$9);
								object_init_ex(&_24$$9, spl_ce_InvalidArgumentException);
								ZEPHIR_INIT_NVAR(&_25$$9);
								zephir_gettype(&_25$$9, &value);
								ZEPHIR_INIT_NVAR(&_26$$9);
								ZEPHIR_CONCAT_SSVS(&_26$$9, "Matrix element must", " be an integer or float, ", &_25$$9, " given.");
								ZEPHIR_CALL_METHOD(NULL, &_24$$9, "__construct", &_13, 3, &_26$$9);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_24$$9, "tensor/matrix.zep", 473);
								ZEPHIR_MM_RESTORE();
								return;
							}
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &a, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_6$$3, &a, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_6$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&row, &a, "current", NULL, 0);
				zephir_check_call_status();
					if (UNEXPECTED(zephir_fast_count_int(&row) != n)) {
						ZEPHIR_INIT_NVAR(&_27$$11);
						object_init_ex(&_27$$11, spl_ce_InvalidArgumentException);
						ZVAL_LONG(&_28$$11, n);
						ZEPHIR_CALL_FUNCTION(&_29$$11, "strval", &_10, 2, &_28$$11);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_30$$11);
						ZVAL_LONG(&_30$$11, zephir_fast_count_int(&row));
						ZEPHIR_INIT_NVAR(&_31$$11);
						ZEPHIR_CONCAT_SSVSVS(&_31$$11, "The number of columns", " must be equal for all rows, ", &_29$$11, " needed but ", &_30$$11, " given.");
						ZEPHIR_CALL_METHOD(NULL, &_27$$11, "__construct", &_13, 3, &_31$$11);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_27$$11, "tensor/matrix.zep", 466);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_is_iterable(&row, 0, "tensor/matrix.zep", 476);
					if (Z_TYPE_P(&row) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _32$$10)
						{
							ZEPHIR_INIT_NVAR(&value);
							ZVAL_COPY(&value, _32$$10);
							_34$$12 = !(Z_TYPE_P(&value) == IS_LONG);
							if (_34$$12) {
								ZEPHIR_CALL_FUNCTION(&_35$$12, "is_float", &_18, 4, &value);
								zephir_check_call_status();
								_34$$12 = !zephir_is_true(&_35$$12);
							}
							if (UNEXPECTED(_34$$12)) {
								ZEPHIR_INIT_NVAR(&_36$$13);
								object_init_ex(&_36$$13, spl_ce_InvalidArgumentException);
								ZEPHIR_INIT_NVAR(&_37$$13);
								zephir_gettype(&_37$$13, &value);
								ZEPHIR_INIT_NVAR(&_38$$13);
								ZEPHIR_CONCAT_SSVS(&_38$$13, "Matrix element must", " be an integer or float, ", &_37$$13, " given.");
								ZEPHIR_CALL_METHOD(NULL, &_36$$13, "__construct", &_13, 3, &_38$$13);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_36$$13, "tensor/matrix.zep", 473);
								ZEPHIR_MM_RESTORE();
								return;
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
						zephir_check_call_status();
						while (1) {
							ZEPHIR_CALL_METHOD(&_33$$10, &row, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_33$$10)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
							zephir_check_call_status();
								_39$$14 = !(Z_TYPE_P(&value) == IS_LONG);
								if (_39$$14) {
									ZEPHIR_CALL_FUNCTION(&_40$$14, "is_float", &_18, 4, &value);
									zephir_check_call_status();
									_39$$14 = !zephir_is_true(&_40$$14);
								}
								if (UNEXPECTED(_39$$14)) {
									ZEPHIR_INIT_NVAR(&_41$$15);
									object_init_ex(&_41$$15, spl_ce_InvalidArgumentException);
									ZEPHIR_INIT_NVAR(&_42$$15);
									zephir_gettype(&_42$$15, &value);
									ZEPHIR_INIT_NVAR(&_43$$15);
									ZEPHIR_CONCAT_SSVS(&_43$$15, "Matrix element must", " be an integer or float, ", &_42$$15, " given.");
									ZEPHIR_CALL_METHOD(NULL, &_41$$15, "__construct", &_13, 3, &_43$$15);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_41$$15, "tensor/matrix.zep", 473);
									ZEPHIR_MM_RESTORE();
									return;
								}
							ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
							zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&value);
				ZEPHIR_CALL_METHOD(NULL, &a, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&row);
	}
	zephir_update_property_zval(this_ptr, SL("a"), &a);
	ZEPHIR_INIT_ZVAL_NREF(_44);
	ZVAL_LONG(&_44, m);
	zephir_update_property_zval(this_ptr, SL("m"), &_44);
	ZEPHIR_INIT_ZVAL_NREF(_44);
	ZVAL_LONG(&_44, n);
	zephir_update_property_zval(this_ptr, SL("n"), &_44);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return a tuple with the dimensionality of the tensor.
 *
 * @return int[]
 */
PHP_METHOD(Tensor_Matrix, shape) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_create_array(return_value, 2, 0);
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();

}

/**
 * Return the shape of the tensor as a string.
 *
 * @return string
 */
PHP_METHOD(Tensor_Matrix, shapeString) {

	zval _1, _3;
	zval _0, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC);
	zephir_get_strval(&_1, &_0);
	ZEPHIR_OBS_VAR(&_2);
	zephir_read_property(&_2, this_ptr, SL("n"), PH_NOISY_CC);
	zephir_get_strval(&_3, &_2);
	ZEPHIR_CONCAT_VSV(return_value, &_1, " x ", &_3);
	RETURN_MM();

}

/**
 * Is this a square matrix?
 *
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, isSquare) {

	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);


	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(ZEPHIR_IS_IDENTICAL(&_0, &_1));

}

/**
 * Return the number of elements in the tensor.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, size) {

	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);


	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	mul_function(return_value, &_0, &_1);
	return;

}

/**
 * Return the number of rows in the matrix.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, m) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "m");

}

/**
 * Return the number of columns in the matrix.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, n) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "n");

}

/**
 * Return a row from the matrix.
 *
 * @param int index
 * @return (int|float)[]
 */
PHP_METHOD(Tensor_Matrix, row) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL, _0;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	index = zephir_get_intval(index_param);


	ZVAL_LONG(&_0, index);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "offsetget", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a row as a vector from the matrix.
 *
 * @param int index
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, rowAsVector) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *index_param = NULL, _1, _2;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	index = zephir_get_intval(index_param);


	ZVAL_LONG(&_2, index);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "row", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", &_0, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a column from the matrix.
 *
 * @param int index
 * @return (int|float)[]
 */
PHP_METHOD(Tensor_Matrix, column) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL, _0, _1;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	index = zephir_get_intval(index_param);


	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, index);
	ZEPHIR_RETURN_CALL_FUNCTION("array_column", NULL, 32, &_0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a column as a vector from the matrix.
 *
 * @param int index
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, columnAsVector) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *index_param = NULL, _1, _2;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &index_param);

	index = zephir_get_intval(index_param);


	ZVAL_LONG(&_2, index);
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "column", NULL, 0, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the diagonal elements of a square matrix as a vector.
 *
 * @throws \RuntimeException
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, diagonalAsVector) {

	zval _2$$3;
	zend_string *_7;
	zend_ulong _6;
	zval b;
	zval _0, i, rowA, _3, *_4, _5, _1$$3, _8$$4, _9$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Cannot trace diagonal of a", " non square matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 20, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 598);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_3, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_3, 0, "tensor/matrix.zep", 608);
	if (Z_TYPE_P(&_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_3), _6, _7, _4)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_7 != NULL) { 
				ZVAL_STR_COPY(&i, _7);
			} else {
				ZVAL_LONG(&i, _6);
			}
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _4);
			zephir_array_fetch(&_8$$4, &rowA, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 605);
			zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 605);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_3, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_5, &_3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_3, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowA, &_3, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_9$$5, &rowA, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 605);
				zephir_array_append(&b, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 605);
			ZEPHIR_CALL_METHOD(NULL, &_3, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", &_10, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elements of the matrix in a 2-d array.
 *
 * @return array[]
 */
PHP_METHOD(Tensor_Matrix, asArray) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

/**
 * Return each row as a vector in an array.
 *
 * @return \Tensor\Vector[]
 */
PHP_METHOD(Tensor_Matrix, asVectors) {

	zval _1, _2;
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Tensor\\Vector");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "quick");
	zephir_array_fast_append(&_0, &_1);
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_map", NULL, 12, &_0, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return each column as a column vector in an array.
 *
 * @return \Tensor\ColumnVector[]
 */
PHP_METHOD(Tensor_Matrix, asColumnVectors) {

	zend_bool _1;
	zval _0, _4$$3, _5$$3;
	zval vectors;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, _2, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&vectors);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&vectors);
	array_init(&vectors);
	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	_3 = (zephir_get_numberval(&_0) - 1);
	_2 = 0;
	_1 = 0;
	if (_2 <= _3) {
		while (1) {
			if (_1) {
				_2++;
				if (!(_2 <= _3)) {
					break;
				}
			} else {
				_1 = 1;
			}
			i = _2;
			ZVAL_LONG(&_5$$3, i);
			ZEPHIR_CALL_METHOD(&_4$$3, this_ptr, "columnasvector", &_6, 0, &_5$$3);
			zephir_check_call_status();
			zephir_array_append(&vectors, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 642);
		}
	}
	RETURN_CTOR(&vectors);

}

/**
 * Flatten i.e unravel the matrix into a vector.
 *
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, flatten) {

	zval _1, _2, _3, _4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	array_init(&_2);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "array_merge");
	ZEPHIR_CALL_FUNCTION(&_4, "array_reduce", NULL, 17, &_1, &_3, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", &_0, 0, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the index of the minimum element in every row of the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, argmin) {

	zval b;
	zval rowA, _0, *_1, _2, _3$$3, _5$$3, _7$$3, _8$$4, _9$$4, _10$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 672);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_CALL_FUNCTION(&_3$$3, "min", &_4, 14, &rowA);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(&_5$$3, "array_search", &_6, 15, &_3$$3, &rowA);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_LONG(&_7$$3, zephir_get_intval(&_5$$3));
			zephir_array_append(&b, &_7$$3, PH_SEPARATE, "tensor/matrix.zep", 669);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_8$$4, "min", &_4, 14, &rowA);
				zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_9$$4, "array_search", &_6, 15, &_8$$4, &rowA);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_10$$4);
				ZVAL_LONG(&_10$$4, zephir_get_intval(&_9$$4));
				zephir_array_append(&b, &_10$$4, PH_SEPARATE, "tensor/matrix.zep", 669);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_11, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the index of the maximum element in every row of the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, argmax) {

	zval b;
	zval rowA, _0, *_1, _2, _3$$3, _5$$3, _7$$3, _8$$4, _9$$4, _10$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_6 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 689);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_CALL_FUNCTION(&_3$$3, "max", &_4, 16, &rowA);
			zephir_check_call_status();
			ZEPHIR_CALL_FUNCTION(&_5$$3, "array_search", &_6, 15, &_3$$3, &rowA);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_7$$3);
			ZVAL_LONG(&_7$$3, zephir_get_intval(&_5$$3));
			zephir_array_append(&b, &_7$$3, PH_SEPARATE, "tensor/matrix.zep", 686);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_8$$4, "max", &_4, 16, &rowA);
				zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_9$$4, "array_search", &_6, 15, &_8$$4, &rowA);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_10$$4);
				ZVAL_LONG(&_10$$4, zephir_get_intval(&_9$$4));
				zephir_array_append(&b, &_10$$4, PH_SEPARATE, "tensor/matrix.zep", 686);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_11, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Run a function over all of the elements in the matrix.
 *
 * @param callable callback
 * @return self
 */
PHP_METHOD(Tensor_Matrix, map) {

	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback, callback_sub, rowA, _0, *_1, _2, _3$$3, _5$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &callback);



	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 707);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_CALL_FUNCTION(&_3$$3, "array_map", &_4, 12, callback, &rowA);
			zephir_check_call_status();
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/matrix.zep", 704);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_5$$4, "array_map", &_4, 12, callback, &rowA);
				zephir_check_call_status();
				zephir_array_append(&b, &_5$$4, PH_SEPARATE, "tensor/matrix.zep", 704);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Reduce the matrix down to a scalar using a callback function.
 *
 * @param callable callback
 * @param int|float initial
 * @throws \InvalidArgumentException
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, reduce) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback, callback_sub, *initial = NULL, initial_sub, _1, rowA, valueA, carry, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&initial_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&carry);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 723);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&carry, initial);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 735);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 733);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_CALL_ZVAL_FUNCTION(&_10$$5, callback, NULL, 0, &valueA, &carry);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&carry, &_10$$5);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_CALL_ZVAL_FUNCTION(&_11$$6, callback, NULL, 0, &valueA, &carry);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&carry, &_11$$6);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 733);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_CALL_ZVAL_FUNCTION(&_14$$8, callback, NULL, 0, &valueA, &carry);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&carry, &_14$$8);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_CALL_ZVAL_FUNCTION(&_15$$9, callback, NULL, 0, &valueA, &carry);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&carry, &_15$$9);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	RETURN_CCTOR(&carry);

}

/**
 * Transpose the matrix i.e row become columns and columns become rows.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, transpose) {

	zend_bool _1;
	zval _0, _4$$3, _5$$3, _6$$3;
	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, _2, _3;
	zephir_fcall_cache_entry *_7 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	_3 = (zephir_get_numberval(&_0) - 1);
	_2 = 0;
	_1 = 0;
	if (_2 <= _3) {
		while (1) {
			if (_1) {
				_2++;
				if (!(_2 <= _3)) {
					break;
				}
			} else {
				_1 = 1;
			}
			i = _2;
			zephir_read_property(&_4$$3, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZVAL_LONG(&_5$$3, i);
			ZEPHIR_CALL_FUNCTION(&_6$$3, "array_column", &_7, 32, &_4$$3, &_5$$3);
			zephir_check_call_status();
			zephir_array_append(&b, &_6$$3, PH_SEPARATE, "tensor/matrix.zep", 749);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the inverse of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, inverse) {

	zend_object_iterator *_3;
	zval rowB, b, _0, _1, _2, _4$$3, _5$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_SELF(&_0, "identity", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &_0, "augmentleft", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&b, &_2, "rref", NULL, 0);
	zephir_check_call_status();
	_3 = zephir_get_iterator(&b);
	_3->funcs->rewind(_3);
	for (;_3->funcs->valid(_3) == SUCCESS && !EG(exception); _3->funcs->move_forward(_3)) {
		{
			ZEPHIR_ITERATOR_COPY(&rowB, _3);
		}
		zephir_read_property(&_4$$3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(&_5$$3, "array_slice", &_6, 8, &rowB, &_4$$3);
		zephir_check_call_status();
		zephir_array_append(&c, &_5$$3, PH_SEPARATE, "tensor/matrix.zep", 770);
	}
	zend_iterator_dtor(_3);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the determinant of the matrix.
 *
 * @throws \RuntimeException
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, det) {

	zval _2$$3;
	zval _0, ref, b, swaps, pi, _3, _4, _5, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&swaps);
	ZVAL_UNDEF(&pi);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Determinant is undefined", " for non square matrices.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 20, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 786);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&ref, this_ptr, "ref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&b);
	zephir_array_fetch_long(&b, &ref, 0, PH_NOISY, "tensor/matrix.zep", 791);
	ZEPHIR_OBS_VAR(&swaps);
	zephir_array_fetch_long(&swaps, &ref, 1, PH_NOISY, "tensor/matrix.zep", 792);
	ZEPHIR_CALL_METHOD(&_3, &b, "diagonalasvector", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&pi, &_3, "product", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_4);
	ZVAL_DOUBLE(&_5, -1.0);
	zephir_pow_function(&_4, &_5, &swaps);
	mul_function(return_value, &pi, &_4);
	RETURN_MM();

}

/**
 * Calculate the rank of the matrix i.e the number of pivots in its reduced row
 * echelon form.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, rank) {

	zend_object_iterator *_0;
	zval row, value, rref, *_1$$3, _2$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, pivots;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&rref);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&rref, this_ptr, "rref", NULL, 0);
	zephir_check_call_status();
	pivots = 0;
	_0 = zephir_get_iterator(&rref);
	_0->funcs->rewind(_0);
	for (;_0->funcs->valid(_0) == SUCCESS && !EG(exception); _0->funcs->move_forward(_0)) {
		{
			ZEPHIR_ITERATOR_COPY(&row, _0);
		}
		zephir_is_iterable(&row, 0, "tensor/matrix.zep", 821);
		if (Z_TYPE_P(&row) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _1$$3)
			{
				ZEPHIR_INIT_NVAR(&value);
				ZVAL_COPY(&value, _1$$3);
				if (!ZEPHIR_IS_LONG(&value, 0)) {
					pivots++;
					continue;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_2$$3, &row, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_2$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
				zephir_check_call_status();
					if (!ZEPHIR_IS_LONG(&value, 0)) {
						pivots++;
						continue;
					}
				ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&value);
	}
	zend_iterator_dtor(_0);
	RETURN_MM_LONG(pivots);

}

/**
 * Is the matrix full rank?
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, fullRank) {

	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "rank", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 14, &_1);
	zephir_check_call_status();
	RETURN_MM_BOOL(ZEPHIR_IS_IDENTICAL(&_0, &_2));

}

/**
 * Is the matrix symmetric i.e. is it equal to its own transpose?
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, symmetric) {

	zend_bool _2, _7$$4;
	zval _0, rowA, _1, _5$$4, _6$$4, _10$$5, _11$$5, _12$$5, _13$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, _3, _4, _8$$4, _9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_4 = (zephir_get_numberval(&_1) - 2);
	_3 = 0;
	_2 = 0;
	if (_3 <= _4) {
		while (1) {
			if (_2) {
				_3++;
				if (!(_3 <= _4)) {
					break;
				}
			} else {
				_2 = 1;
			}
			i = _3;
			zephir_read_property(&_5$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch_long(&rowA, &_5$$4, i, PH_NOISY, "tensor/matrix.zep", 851);
			zephir_read_property(&_6$$4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
			_9$$4 = (zephir_get_numberval(&_6$$4) - 1);
			_8$$4 = (i + 1);
			_7$$4 = 0;
			if (_8$$4 <= _9$$4) {
				while (1) {
					if (_7$$4) {
						_8$$4++;
						if (!(_8$$4 <= _9$$4)) {
							break;
						}
					} else {
						_7$$4 = 1;
					}
					j = _8$$4;
					zephir_array_fetch_long(&_10$$5, &rowA, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 854);
					zephir_read_property(&_11$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch_long(&_12$$5, &_11$$5, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 854);
					zephir_array_fetch_long(&_13$$5, &_12$$5, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 854);
					if (!ZEPHIR_IS_EQUAL(&_10$$5, &_13$$5)) {
						RETURN_MM_BOOL(0);
					}
				}
			}
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Is the matrix positive definite i.e. do all of its principal
 * minor matrices have a determinant greater than 0.
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, positiveDefinite) {

	zend_bool _2;
	zval _0, _1, _4, b$$4, _5$$4, _6$$4, _8$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&b$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "symmetric", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&_4, &_1);
	_3 = 1;
	_2 = 0;
	if (ZEPHIR_GE_LONG(&_4, _3)) {
		while (1) {
			if (_2) {
				_3++;
				if (!(ZEPHIR_GE_LONG(&_4, _3))) {
					break;
				}
			} else {
				_2 = 1;
			}
			i = _3;
			ZVAL_LONG(&_5$$4, 0);
			ZVAL_LONG(&_6$$4, i);
			ZEPHIR_CALL_METHOD(&b$$4, this_ptr, "submatrix", &_7, 0, &_5$$4, &_6$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_8$$4, &b$$4, "det", &_9, 0);
			zephir_check_call_status();
			if (ZEPHIR_LE_LONG(&_8$$4, 0)) {
				RETURN_MM_BOOL(0);
			}
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Is the matrix positive semidefinite i.e. do all of its principal
 * minor matrices have a determinant greater or equal to 0.
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, positiveSemidefinite) {

	zend_bool _2;
	zval _0, _1, _4, b$$4, _5$$4, _6$$4, _8$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL, *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&b$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "symmetric", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CPY_WRT(&_4, &_1);
	_3 = 1;
	_2 = 0;
	if (ZEPHIR_GE_LONG(&_4, _3)) {
		while (1) {
			if (_2) {
				_3++;
				if (!(ZEPHIR_GE_LONG(&_4, _3))) {
					break;
				}
			} else {
				_2 = 1;
			}
			i = _3;
			ZVAL_LONG(&_5$$4, 0);
			ZVAL_LONG(&_6$$4, i);
			ZEPHIR_CALL_METHOD(&b$$4, this_ptr, "submatrix", &_7, 0, &_5$$4, &_6$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_8$$4, &b$$4, "det", &_9, 0);
			zephir_check_call_status();
			if (ZEPHIR_LT_LONG(&_8$$4, 0)) {
				RETURN_MM_BOOL(0);
			}
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Multiply this matrix with another matrix (matrix-matrix product).
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, matmul) {

	zend_string *_19$$5, *_28$$8, *_39$$12, *_48$$15;
	zend_ulong _18$$5, _27$$8, _38$$12, _47$$15;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC, bT, _10;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, k, rowA, valueA, columnB, _8, _9, _11, *_12, _13, _2$$3, _3$$3, _5$$3, *_14$$4, _15$$4, *_16$$5, _17$$5, _24$$5, _20$$6, _21$$6, _22$$7, _23$$7, *_25$$8, _26$$8, _33$$8, _29$$9, _30$$9, _31$$10, _32$$10, *_34$$11, _35$$11, *_36$$12, _37$$12, _44$$12, _40$$13, _41$$13, _42$$14, _43$$14, *_45$$15, _46$$15, _53$$15, _49$$16, _50$$16, _51$$17, _52$$17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&columnB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_24$$5);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_26$$8);
	ZVAL_UNDEF(&_33$$8);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_31$$10);
	ZVAL_UNDEF(&_32$$10);
	ZVAL_UNDEF(&_35$$11);
	ZVAL_UNDEF(&_37$$12);
	ZVAL_UNDEF(&_44$$12);
	ZVAL_UNDEF(&_40$$13);
	ZVAL_UNDEF(&_41$$13);
	ZVAL_UNDEF(&_42$$14);
	ZVAL_UNDEF(&_43$$14);
	ZVAL_UNDEF(&_46$$15);
	ZVAL_UNDEF(&_53$$15);
	ZVAL_UNDEF(&_49$$16);
	ZVAL_UNDEF(&_50$$16);
	ZVAL_UNDEF(&_51$$17);
	ZVAL_UNDEF(&_52$$17);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&bT);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 925);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_INIT_VAR(&bT);
	array_init(&bT);
	ZEPHIR_CALL_METHOD(&_8, b, "transpose", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, &_8, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_10, &_9);
	ZEPHIR_CPY_WRT(&bT, &_10);
	zephir_read_property(&_11, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_11, 0, "tensor/matrix.zep", 952);
	if (Z_TYPE_P(&_11) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_11), _12)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _12);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bT, 0, "tensor/matrix.zep", 949);
			if (Z_TYPE_P(&bT) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&bT), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&columnB);
					ZVAL_COPY(&columnB, _14$$4);
					sigma = 0.0;
					zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 946);
					if (Z_TYPE_P(&rowA) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _18$$5, _19$$5, _16$$5)
						{
							ZEPHIR_INIT_NVAR(&k);
							if (_19$$5 != NULL) { 
								ZVAL_STR_COPY(&k, _19$$5);
							} else {
								ZVAL_LONG(&k, _18$$5);
							}
							ZEPHIR_INIT_NVAR(&valueA);
							ZVAL_COPY(&valueA, _16$$5);
							zephir_array_fetch(&_20$$6, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
							ZEPHIR_INIT_NVAR(&_21$$6);
							mul_function(&_21$$6, &valueA, &_20$$6);
							sigma += zephir_get_numberval(&_21$$6);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
						zephir_check_call_status();
						while (1) {
							ZEPHIR_CALL_METHOD(&_17$$5, &rowA, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_17$$5)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
							zephir_check_call_status();
								zephir_array_fetch(&_22$$7, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
								ZEPHIR_INIT_NVAR(&_23$$7);
								mul_function(&_23$$7, &valueA, &_22$$7);
								sigma += zephir_get_numberval(&_23$$7);
							ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
							zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZEPHIR_INIT_NVAR(&k);
					ZEPHIR_INIT_NVAR(&_24$$5);
					ZVAL_DOUBLE(&_24$$5, sigma);
					zephir_array_append(&rowC, &_24$$5, PH_SEPARATE, "tensor/matrix.zep", 946);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bT, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &bT, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&columnB, &bT, "current", NULL, 0);
					zephir_check_call_status();
						sigma = 0.0;
						zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 946);
						if (Z_TYPE_P(&rowA) == IS_ARRAY) {
							ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _27$$8, _28$$8, _25$$8)
							{
								ZEPHIR_INIT_NVAR(&k);
								if (_28$$8 != NULL) { 
									ZVAL_STR_COPY(&k, _28$$8);
								} else {
									ZVAL_LONG(&k, _27$$8);
								}
								ZEPHIR_INIT_NVAR(&valueA);
								ZVAL_COPY(&valueA, _25$$8);
								zephir_array_fetch(&_29$$9, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
								ZEPHIR_INIT_NVAR(&_30$$9);
								mul_function(&_30$$9, &valueA, &_29$$9);
								sigma += zephir_get_numberval(&_30$$9);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
							zephir_check_call_status();
							while (1) {
								ZEPHIR_CALL_METHOD(&_26$$8, &rowA, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_26$$8)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
								zephir_check_call_status();
									zephir_array_fetch(&_31$$10, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
									ZEPHIR_INIT_NVAR(&_32$$10);
									mul_function(&_32$$10, &valueA, &_31$$10);
									sigma += zephir_get_numberval(&_32$$10);
								ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
								zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZEPHIR_INIT_NVAR(&k);
						ZEPHIR_INIT_NVAR(&_33$$8);
						ZVAL_DOUBLE(&_33$$8, sigma);
						zephir_array_append(&rowC, &_33$$8, PH_SEPARATE, "tensor/matrix.zep", 946);
					ZEPHIR_CALL_METHOD(NULL, &bT, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&columnB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 949);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_11, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_13, &_11, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, &_11, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bT, 0, "tensor/matrix.zep", 949);
				if (Z_TYPE_P(&bT) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&bT), _34$$11)
					{
						ZEPHIR_INIT_NVAR(&columnB);
						ZVAL_COPY(&columnB, _34$$11);
						sigma = 0.0;
						zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 946);
						if (Z_TYPE_P(&rowA) == IS_ARRAY) {
							ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _38$$12, _39$$12, _36$$12)
							{
								ZEPHIR_INIT_NVAR(&k);
								if (_39$$12 != NULL) { 
									ZVAL_STR_COPY(&k, _39$$12);
								} else {
									ZVAL_LONG(&k, _38$$12);
								}
								ZEPHIR_INIT_NVAR(&valueA);
								ZVAL_COPY(&valueA, _36$$12);
								zephir_array_fetch(&_40$$13, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
								ZEPHIR_INIT_NVAR(&_41$$13);
								mul_function(&_41$$13, &valueA, &_40$$13);
								sigma += zephir_get_numberval(&_41$$13);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
							zephir_check_call_status();
							while (1) {
								ZEPHIR_CALL_METHOD(&_37$$12, &rowA, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_37$$12)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
								zephir_check_call_status();
									zephir_array_fetch(&_42$$14, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
									ZEPHIR_INIT_NVAR(&_43$$14);
									mul_function(&_43$$14, &valueA, &_42$$14);
									sigma += zephir_get_numberval(&_43$$14);
								ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
								zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZEPHIR_INIT_NVAR(&k);
						ZEPHIR_INIT_NVAR(&_44$$12);
						ZVAL_DOUBLE(&_44$$12, sigma);
						zephir_array_append(&rowC, &_44$$12, PH_SEPARATE, "tensor/matrix.zep", 946);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bT, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_35$$11, &bT, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_35$$11)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&columnB, &bT, "current", NULL, 0);
						zephir_check_call_status();
							sigma = 0.0;
							zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 946);
							if (Z_TYPE_P(&rowA) == IS_ARRAY) {
								ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _47$$15, _48$$15, _45$$15)
								{
									ZEPHIR_INIT_NVAR(&k);
									if (_48$$15 != NULL) { 
										ZVAL_STR_COPY(&k, _48$$15);
									} else {
										ZVAL_LONG(&k, _47$$15);
									}
									ZEPHIR_INIT_NVAR(&valueA);
									ZVAL_COPY(&valueA, _45$$15);
									zephir_array_fetch(&_49$$16, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
									ZEPHIR_INIT_NVAR(&_50$$16);
									mul_function(&_50$$16, &valueA, &_49$$16);
									sigma += zephir_get_numberval(&_50$$16);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
								zephir_check_call_status();
								while (1) {
									ZEPHIR_CALL_METHOD(&_46$$15, &rowA, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_46$$15)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
									zephir_check_call_status();
										zephir_array_fetch(&_51$$17, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 943);
										ZEPHIR_INIT_NVAR(&_52$$17);
										mul_function(&_52$$17, &valueA, &_51$$17);
										sigma += zephir_get_numberval(&_52$$17);
									ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
									zephir_check_call_status();
								}
							}
							ZEPHIR_INIT_NVAR(&valueA);
							ZEPHIR_INIT_NVAR(&k);
							ZEPHIR_INIT_NVAR(&_53$$15);
							ZVAL_DOUBLE(&_53$$15, sigma);
							zephir_array_append(&rowC, &_53$$15, PH_SEPARATE, "tensor/matrix.zep", 946);
						ZEPHIR_CALL_METHOD(NULL, &bT, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&columnB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 949);
			ZEPHIR_CALL_METHOD(NULL, &_11, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the dot product of this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, dot) {

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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 967);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_9, b, "ascolumnmatrix", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, this_ptr, "matmul", NULL, 0, &_9);
	zephir_check_call_status();
	ZVAL_LONG(&_10, 0);
	ZEPHIR_RETURN_CALL_METHOD(&_8, "columnasvector", NULL, 0, &_10);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Convolve this matrix with another matrix.
 *
 * @param \Tensor\Matrix b
 * @param int stride
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, convolve) {

	zend_string *_24$$6, *_33$$7, *_50$$13;
	zend_ulong _23$$6, _32$$7, _49$$13;
	zval _4$$3;
	zval c, rowC, rowA, bHat, _13, _29$$7, _46$$13;
	double sigma = 0;
	zend_bool _1, _14, _18$$5, _25$$7, _34$$9, _38$$11, _42$$13, _51$$15, _55$$17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long stride, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, x = 0, y = 0, p, q, _15, _16, _19$$5, _20$$5;
	zval *b, b_sub, *stride_param = NULL, m, n, _0, _2, k, l, rowB, valueB, _9, _10, _11, _12, _3$$3, _5$$4, _6$$4, _7$$4, _8$$4, _17$$5, *_21$$6, _22$$6, _59$$6, _26$$7, _27$$7, _28$$7, *_30$$7, _31$$7, _35$$9, _36$$9, _37$$9, _39$$11, _40$$11, _41$$11, _43$$13, _44$$13, _45$$13, *_47$$13, _48$$13, _52$$15, _53$$15, _54$$15, _56$$17, _57$$17, _58$$17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_59$$6);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_27$$7);
	ZVAL_UNDEF(&_28$$7);
	ZVAL_UNDEF(&_31$$7);
	ZVAL_UNDEF(&_35$$9);
	ZVAL_UNDEF(&_36$$9);
	ZVAL_UNDEF(&_37$$9);
	ZVAL_UNDEF(&_39$$11);
	ZVAL_UNDEF(&_40$$11);
	ZVAL_UNDEF(&_41$$11);
	ZVAL_UNDEF(&_43$$13);
	ZVAL_UNDEF(&_44$$13);
	ZVAL_UNDEF(&_45$$13);
	ZVAL_UNDEF(&_48$$13);
	ZVAL_UNDEF(&_52$$15);
	ZVAL_UNDEF(&_53$$15);
	ZVAL_UNDEF(&_54$$15);
	ZVAL_UNDEF(&_56$$17);
	ZVAL_UNDEF(&_57$$17);
	ZVAL_UNDEF(&_58$$17);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_46$$13);
	ZVAL_UNDEF(&_4$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &b, &stride_param);

	if (!stride_param) {
		stride = 1;
	} else {
		stride = zephir_get_intval(stride_param);
	}


	ZEPHIR_CALL_METHOD(&m, b, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&n, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT(&m, &_0);
	if (!(_1)) {
		zephir_read_property(&_2, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		_1 = ZEPHIR_GT(&n, &_2);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_3$$3);
		object_init_ex(&_3$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SS(&_4$$3, "Matrix B cannot be", " larger than Matrix A.");
		ZEPHIR_CALL_METHOD(NULL, &_3$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_3$$3, "tensor/matrix.zep", 988);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (stride < 1) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_6$$4, stride);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", NULL, 2, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "Stride cannot be", " less than 1, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 993);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_INIT_VAR(&bHat);
	array_init(&bHat);
	ZVAL_LONG(&_9, 2);
	ZEPHIR_CALL_FUNCTION(&_10, "intdiv", NULL, 21, &m, &_9);
	zephir_check_call_status();
	p = zephir_get_intval(&_10);
	ZVAL_LONG(&_9, 2);
	ZEPHIR_CALL_FUNCTION(&_11, "intdiv", NULL, 21, &n, &_9);
	zephir_check_call_status();
	q = zephir_get_intval(&_11);
	ZEPHIR_CALL_METHOD(&_12, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_13, &_12);
	ZEPHIR_CPY_WRT(&bHat, &_13);
	zephir_read_property(&_9, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_16 = (zephir_get_numberval(&_9) - 1);
	_15 = 0;
	_14 = 0;
	if (_15 <= _16) {
		while (1) {
			if (_14) {
				_15 += stride;
				if (!(_15 <= _16)) {
					break;
				}
			} else {
				_14 = 1;
			}
			i = _15;
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_read_property(&_17$$5, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
			_20$$5 = (zephir_get_numberval(&_17$$5) - 1);
			_19$$5 = 0;
			_18$$5 = 0;
			if (_19$$5 <= _20$$5) {
				while (1) {
					if (_18$$5) {
						_19$$5 += stride;
						if (!(_19$$5 <= _20$$5)) {
							break;
						}
					} else {
						_18$$5 = 1;
					}
					j = _19$$5;
					sigma = 0.0;
					zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 1035);
					if (Z_TYPE_P(&bHat) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _23$$6, _24$$6, _21$$6)
						{
							ZEPHIR_INIT_NVAR(&k);
							if (_24$$6 != NULL) { 
								ZVAL_STR_COPY(&k, _24$$6);
							} else {
								ZVAL_LONG(&k, _23$$6);
							}
							ZEPHIR_INIT_NVAR(&rowB);
							ZVAL_COPY(&rowB, _21$$6);
							x = ((i + p) - zephir_get_intval(&k));
							_25$$7 = x < 0;
							if (!(_25$$7)) {
								zephir_read_property(&_26$$7, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
								_25$$7 = ZEPHIR_LE_LONG(&_26$$7, x);
							}
							if (_25$$7) {
								continue;
							}
							zephir_read_property(&_27$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							ZEPHIR_OBS_NVAR(&_28$$7);
							zephir_array_fetch_long(&_28$$7, &_27$$7, x, PH_NOISY, "tensor/matrix.zep", 1022);
							zephir_get_arrval(&_29$$7, &_28$$7);
							ZEPHIR_CPY_WRT(&rowA, &_29$$7);
							zephir_is_iterable(&rowB, 0, "tensor/matrix.zep", 1033);
							if (Z_TYPE_P(&rowB) == IS_ARRAY) {
								ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowB), _32$$7, _33$$7, _30$$7)
								{
									ZEPHIR_INIT_NVAR(&l);
									if (_33$$7 != NULL) { 
										ZVAL_STR_COPY(&l, _33$$7);
									} else {
										ZVAL_LONG(&l, _32$$7);
									}
									ZEPHIR_INIT_NVAR(&valueB);
									ZVAL_COPY(&valueB, _30$$7);
									y = ((j + q) - zephir_get_intval(&l));
									_34$$9 = y < 0;
									if (!(_34$$9)) {
										zephir_read_property(&_35$$9, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
										_34$$9 = ZEPHIR_LE_LONG(&_35$$9, y);
									}
									if (_34$$9) {
										continue;
									}
									zephir_array_fetch_long(&_36$$9, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1031);
									ZEPHIR_INIT_NVAR(&_37$$9);
									mul_function(&_37$$9, &_36$$9, &valueB);
									sigma += zephir_get_numberval(&_37$$9);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
								zephir_check_call_status();
								while (1) {
									ZEPHIR_CALL_METHOD(&_31$$7, &rowB, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_31$$7)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&l, &rowB, "key", NULL, 0);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
									zephir_check_call_status();
										y = ((j + q) - zephir_get_intval(&l));
										_38$$11 = y < 0;
										if (!(_38$$11)) {
											zephir_read_property(&_39$$11, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
											_38$$11 = ZEPHIR_LE_LONG(&_39$$11, y);
										}
										if (_38$$11) {
											continue;
										}
										zephir_array_fetch_long(&_40$$11, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1031);
										ZEPHIR_INIT_NVAR(&_41$$11);
										mul_function(&_41$$11, &_40$$11, &valueB);
										sigma += zephir_get_numberval(&_41$$11);
									ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
									zephir_check_call_status();
								}
							}
							ZEPHIR_INIT_NVAR(&valueB);
							ZEPHIR_INIT_NVAR(&l);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
						zephir_check_call_status();
						while (1) {
							ZEPHIR_CALL_METHOD(&_22$$6, &bHat, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_22$$6)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&k, &bHat, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&rowB, &bHat, "current", NULL, 0);
							zephir_check_call_status();
								x = ((i + p) - zephir_get_intval(&k));
								_42$$13 = x < 0;
								if (!(_42$$13)) {
									zephir_read_property(&_43$$13, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
									_42$$13 = ZEPHIR_LE_LONG(&_43$$13, x);
								}
								if (_42$$13) {
									continue;
								}
								zephir_read_property(&_44$$13, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
								ZEPHIR_OBS_NVAR(&_45$$13);
								zephir_array_fetch_long(&_45$$13, &_44$$13, x, PH_NOISY, "tensor/matrix.zep", 1022);
								zephir_get_arrval(&_46$$13, &_45$$13);
								ZEPHIR_CPY_WRT(&rowA, &_46$$13);
								zephir_is_iterable(&rowB, 0, "tensor/matrix.zep", 1033);
								if (Z_TYPE_P(&rowB) == IS_ARRAY) {
									ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowB), _49$$13, _50$$13, _47$$13)
									{
										ZEPHIR_INIT_NVAR(&l);
										if (_50$$13 != NULL) { 
											ZVAL_STR_COPY(&l, _50$$13);
										} else {
											ZVAL_LONG(&l, _49$$13);
										}
										ZEPHIR_INIT_NVAR(&valueB);
										ZVAL_COPY(&valueB, _47$$13);
										y = ((j + q) - zephir_get_intval(&l));
										_51$$15 = y < 0;
										if (!(_51$$15)) {
											zephir_read_property(&_52$$15, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
											_51$$15 = ZEPHIR_LE_LONG(&_52$$15, y);
										}
										if (_51$$15) {
											continue;
										}
										zephir_array_fetch_long(&_53$$15, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1031);
										ZEPHIR_INIT_NVAR(&_54$$15);
										mul_function(&_54$$15, &_53$$15, &valueB);
										sigma += zephir_get_numberval(&_54$$15);
									} ZEND_HASH_FOREACH_END();
								} else {
									ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
									zephir_check_call_status();
									while (1) {
										ZEPHIR_CALL_METHOD(&_48$$13, &rowB, "valid", NULL, 0);
										zephir_check_call_status();
										if (!zend_is_true(&_48$$13)) {
											break;
										}
										ZEPHIR_CALL_METHOD(&l, &rowB, "key", NULL, 0);
										zephir_check_call_status();
										ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
										zephir_check_call_status();
											y = ((j + q) - zephir_get_intval(&l));
											_55$$17 = y < 0;
											if (!(_55$$17)) {
												zephir_read_property(&_56$$17, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
												_55$$17 = ZEPHIR_LE_LONG(&_56$$17, y);
											}
											if (_55$$17) {
												continue;
											}
											zephir_array_fetch_long(&_57$$17, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1031);
											ZEPHIR_INIT_NVAR(&_58$$17);
											mul_function(&_58$$17, &_57$$17, &valueB);
											sigma += zephir_get_numberval(&_58$$17);
										ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
										zephir_check_call_status();
									}
								}
								ZEPHIR_INIT_NVAR(&valueB);
								ZEPHIR_INIT_NVAR(&l);
							ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
							zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&rowB);
					ZEPHIR_INIT_NVAR(&k);
					ZEPHIR_INIT_NVAR(&_59$$6);
					ZVAL_DOUBLE(&_59$$6, sigma);
					zephir_array_append(&rowC, &_59$$6, PH_SEPARATE, "tensor/matrix.zep", 1035);
				}
			}
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 1038);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the row echelon form (REF) of the matrix. Return the reduced
 * matrix and the number of swaps needed to compute the REF.
 *
 * @return array
 */
PHP_METHOD(Tensor_Matrix, ref) {

	zval ref, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&ref, tensor_decompositions_ref_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	zephir_create_array(return_value, 2, 0);
	ZEPHIR_CALL_METHOD(&_1, &ref, "a", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(return_value, &_1);
	ZEPHIR_CALL_METHOD(&_1, &ref, "swaps", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(return_value, &_1);
	RETURN_MM();

}

/**
 * Return the reduced row echelon (RREF) form of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, rref) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&_0, tensor_decompositions_rref_ce, "decompose", &_1, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "a", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the LU decomposition of the matrix in a tuple where l is
 * the lower triangular matrix, u is the upper triangular matrix,
 * and p is the permutation matrix.
 *
 * @throws \RuntimeException
 * @return self[]
 */
PHP_METHOD(Tensor_Matrix, lu) {

	zval lup, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&lup);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&lup, tensor_decompositions_lu_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	zephir_create_array(return_value, 3, 0);
	ZEPHIR_CALL_METHOD(&_1, &lup, "l", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(return_value, &_1);
	ZEPHIR_CALL_METHOD(&_1, &lup, "u", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(return_value, &_1);
	ZEPHIR_CALL_METHOD(&_1, &lup, "p", NULL, 0);
	zephir_check_call_status();
	zephir_array_fast_append(return_value, &_1);
	RETURN_MM();

}

/**
 * Return the lower triangular matrix of the Cholesky decomposition.
 * 
 * @return self
 */
PHP_METHOD(Tensor_Matrix, cholesky) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&_0, tensor_decompositions_cholesky_ce, "decompose", &_1, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "l", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the eigenvalues and eigenvectors of the matrix and return
 * them in a tuple.
 *
 * @param bool normalize
 * @throws \RuntimeException
 * @return array
 */
PHP_METHOD(Tensor_Matrix, eig) {

	zval *normalize_param = NULL;
	zend_bool normalize;
	zval *this_ptr = getThis();


	zephir_fetch_params_without_memory_grow(0, 1, &normalize_param);

	if (!normalize_param) {
		normalize = 1;
	} else {
		normalize = zephir_get_boolval(normalize_param);
	}


	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Not implemented yet.", "tensor/matrix.zep", 1106);
	return;

}

/**
 * Solve a linear system of equations given the matrix and a solution vector b.
 * Returns the column vector x that satisfies the solution.
 *
 * @param \Tensor\Vector b
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, solve) {

	zend_bool _17, _34, _20$$5, _37$$9;
	zval l, u, pb, _2, _5, _9, y, x;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_48 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k, _18, _19, _35, _36, _21$$5, _22$$5, _38$$9, _39$$9;
	zval *b, b_sub, lup, _0, _1, _3, _4, _6, _7, _8, _10, _11, _12, _13, _14, _16, _31, _32, _49, _15$$4, _27$$5, _28$$5, _29$$5, _30$$5, _23$$6, _24$$6, _25$$6, _26$$6, _33$$8, _44$$9, _45$$9, _46$$9, _47$$9, _40$$10, _41$$10, _42$$10, _43$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&lup);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_49);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_27$$5);
	ZVAL_UNDEF(&_28$$5);
	ZVAL_UNDEF(&_29$$5);
	ZVAL_UNDEF(&_30$$5);
	ZVAL_UNDEF(&_23$$6);
	ZVAL_UNDEF(&_24$$6);
	ZVAL_UNDEF(&_25$$6);
	ZVAL_UNDEF(&_26$$6);
	ZVAL_UNDEF(&_33$$8);
	ZVAL_UNDEF(&_44$$9);
	ZVAL_UNDEF(&_45$$9);
	ZVAL_UNDEF(&_46$$9);
	ZVAL_UNDEF(&_47$$9);
	ZVAL_UNDEF(&_40$$10);
	ZVAL_UNDEF(&_41$$10);
	ZVAL_UNDEF(&_42$$10);
	ZVAL_UNDEF(&_43$$10);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&pb);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&y);
	ZVAL_UNDEF(&x);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_INIT_VAR(&l);
	array_init(&l);
	ZEPHIR_INIT_VAR(&u);
	array_init(&u);
	ZEPHIR_INIT_VAR(&pb);
	array_init(&pb);
	ZEPHIR_CALL_METHOD(&lup, this_ptr, "lu", NULL, 0);
	zephir_check_call_status();
	zephir_array_fetch_long(&_0, &lup, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1126);
	ZEPHIR_CALL_METHOD(&_1, &_0, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_2, &_1);
	ZEPHIR_CPY_WRT(&l, &_2);
	zephir_array_fetch_long(&_3, &lup, 1, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1127);
	ZEPHIR_CALL_METHOD(&_4, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_5, &_4);
	ZEPHIR_CPY_WRT(&u, &_5);
	zephir_array_fetch_long(&_6, &lup, 2, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1128);
	ZEPHIR_CALL_METHOD(&_7, &_6, "dot", NULL, 0, b);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, &_7, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_9, &_8);
	ZEPHIR_CPY_WRT(&pb, &_9);
	zephir_read_property(&_10, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	k = ((zephir_get_numberval(&_10) - 1));
	ZEPHIR_INIT_VAR(&y);
	zephir_create_array(&y, 1, 0);
	zephir_array_fetch_long(&_11, &pb, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1132);
	ZEPHIR_INIT_VAR(&_12);
	zephir_array_fetch_long(&_13, &l, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1132);
	zephir_array_fetch_long(&_14, &_13, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1132);
	if (!(zephir_is_true(&_14))) {
		ZEPHIR_INIT_NVAR(&_12);
		ZVAL_DOUBLE(&_12, 0.00000001);
	} else {
		zephir_array_fetch_long(&_15$$4, &l, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1132);
		ZEPHIR_OBS_NVAR(&_12);
		zephir_array_fetch_long(&_12, &_15$$4, 0, PH_NOISY, "tensor/matrix.zep", 1132);
	}
	ZEPHIR_INIT_VAR(&_16);
	div_function(&_16, &_11, &_12);
	zephir_array_update_long(&y, 0, &_16, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	_19 = k;
	_18 = 1;
	_17 = 0;
	if (_18 <= _19) {
		while (1) {
			if (_17) {
				_18++;
				if (!(_18 <= _19)) {
					break;
				}
			} else {
				_17 = 1;
			}
			i = _18;
			sigma = 0.0;
			_22$$5 = (i - 1);
			_21$$5 = 0;
			_20$$5 = 0;
			if (_21$$5 <= _22$$5) {
				while (1) {
					if (_20$$5) {
						_21$$5++;
						if (!(_21$$5 <= _22$$5)) {
							break;
						}
					} else {
						_20$$5 = 1;
					}
					j = _21$$5;
					zephir_array_fetch_long(&_23$$6, &l, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1138);
					zephir_array_fetch_long(&_24$$6, &_23$$6, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1138);
					zephir_array_fetch_long(&_25$$6, &y, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1138);
					ZEPHIR_INIT_NVAR(&_26$$6);
					mul_function(&_26$$6, &_24$$6, &_25$$6);
					sigma += zephir_get_numberval(&_26$$6);
				}
			}
			zephir_array_fetch_long(&_27$$5, &pb, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1141);
			zephir_array_fetch_long(&_28$$5, &l, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1141);
			zephir_array_fetch_long(&_29$$5, &_28$$5, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1141);
			ZEPHIR_INIT_NVAR(&_30$$5);
			ZVAL_DOUBLE(&_30$$5, zephir_safe_div_double_zval(((zephir_get_numberval(&_27$$5) - sigma)), &_29$$5));
			zephir_array_append(&y, &_30$$5, PH_SEPARATE, "tensor/matrix.zep", 1141);
		}
	}
	ZEPHIR_INIT_VAR(&x);
	zephir_create_array(&x, 1, 0);
	zephir_array_fetch_long(&_11, &y, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1144);
	ZEPHIR_INIT_NVAR(&_12);
	zephir_array_fetch_long(&_31, &l, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1144);
	zephir_array_fetch_long(&_32, &_31, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1144);
	if (!(zephir_is_true(&_32))) {
		ZEPHIR_INIT_NVAR(&_12);
		ZVAL_DOUBLE(&_12, 0.00000001);
	} else {
		zephir_array_fetch_long(&_33$$8, &l, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1144);
		ZEPHIR_OBS_NVAR(&_12);
		zephir_array_fetch_long(&_12, &_33$$8, k, PH_NOISY, "tensor/matrix.zep", 1144);
	}
	ZEPHIR_INIT_NVAR(&_16);
	div_function(&_16, &_11, &_12);
	zephir_array_update_long(&x, k, &_16, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	_36 = (k - 1);
	_35 = _36;
	_34 = 0;
	if (_35 >= 0) {
		while (1) {
			if (_34) {
				_35--;
				if (!(_35 >= 0)) {
					break;
				}
			} else {
				_34 = 1;
			}
			i = _35;
			sigma = 0.0;
			_39$$9 = k;
			_38$$9 = (i + 1);
			_37$$9 = 0;
			if (_38$$9 <= _39$$9) {
				while (1) {
					if (_37$$9) {
						_38$$9++;
						if (!(_38$$9 <= _39$$9)) {
							break;
						}
					} else {
						_37$$9 = 1;
					}
					j = _38$$9;
					zephir_array_fetch_long(&_40$$10, &u, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1150);
					zephir_array_fetch_long(&_41$$10, &_40$$10, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1150);
					zephir_array_fetch_long(&_42$$10, &x, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1150);
					ZEPHIR_INIT_NVAR(&_43$$10);
					mul_function(&_43$$10, &_41$$10, &_42$$10);
					sigma += zephir_get_numberval(&_43$$10);
				}
			}
			zephir_array_fetch_long(&_44$$9, &y, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1153);
			zephir_array_fetch_long(&_45$$9, &u, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1153);
			zephir_array_fetch_long(&_46$$9, &_45$$9, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1153);
			ZEPHIR_INIT_NVAR(&_47$$9);
			ZVAL_DOUBLE(&_47$$9, zephir_safe_div_double_zval(((zephir_get_numberval(&_44$$9) - sigma)), &_46$$9));
			zephir_array_update_long(&x, i, &_47$$9, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_49, "array_reverse", NULL, 33, &x);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_48, 0, &_49);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the L1 norm of the matrix.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, l1Norm) {

	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "transpose", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "abs", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &_1, "sum", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_2, "max", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the L2 norm of the matrix.
 *    
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, l2Norm) {

	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "sum", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &_1, "sum", NULL, 0);
	zephir_check_call_status();
	RETURN_MM_DOUBLE(zephir_sqrt(&_2));

}

/**
 * Retrn the infinity norm of the matrix.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, infinityNorm) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "abs", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "sum", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_1, "max", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the max norm of the matrix.
 *
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, maxNorm) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "abs", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "max", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_1, "max", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * A universal function to multiply this matrix with another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, multiply) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplycolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot multiply matrix", " by a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1226);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to divide this matrix by another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, divide) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividematrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividecolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividevector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot divide matrix", " by a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1257);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to add this matrix with another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, add) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot add matrix", " with a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1288);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to subtract this matrix from another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, subtract) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SVS(&_5, "Cannot subtract a ", &_4, " from matrix.");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1319);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to raise this matrix to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, pow) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot raise matrix", " to the power of a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1350);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the integer modulus of this matrix
 * and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, mod) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot mod matrix", " with a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1381);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the equality comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, equal) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare matrix", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1412);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the not equal comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, notEqual) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare matrix", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1443);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, greater) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatermatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatercolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatervector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare matrix", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1474);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than or equal to
 * comparison of this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, greaterEqual) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare matrix", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1505);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, less) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lesscolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare matrix", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1536);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than or equal to
 * comparison of this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, lessEqual) {

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
			if (_0$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalmatrix", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalcolumnvector", NULL, 0, b);
				zephir_check_call_status();
				RETURN_MM();
			}
			if (_0$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) {
				ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SSVS(&_5, "Cannot compare matrix", " to a ", &_4, ".");
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 3, &_5);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1567);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Return the element-wise reciprocal of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, reciprocal) {

	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_SELF(&_0, "ones", NULL, 0, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "dividematrix", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the absolute value of each element in the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, abs) {

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
 * Return the square of the matrix elementwise.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, square) {

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
 * Return the square root of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, sqrt) {

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
 * Return the exponential of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, exp) {

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
 * Return the exponential of the tensor minus 1.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, expm1) {

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
 * Return the logarithm of the matrix in specified base.
 *
 * @param float base
 * @return self
 */
PHP_METHOD(Tensor_Matrix, log) {

	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *base_param = NULL, row, value, _0, *_1, _2, *_3$$3, _4$$3, _5$$4, _6$$4, _8$$5, _9$$5, *_10$$6, _11$$6, _12$$7, _13$$7, _14$$8, _15$$8;
	double base;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &base_param);

	if (!base_param) {
		base = 2.7182818284590452354;
	} else {
		base = zephir_get_doubleval(base_param);
	}


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 1653);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1650);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _3$$3);
					ZVAL_DOUBLE(&_5$$4, base);
					ZEPHIR_CALL_FUNCTION(&_6$$4, "log", &_7, 7, &value, &_5$$4);
					zephir_check_call_status();
					zephir_array_append(&rowB, &_6$$4, PH_SEPARATE, "tensor/matrix.zep", 1647);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$3, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZVAL_DOUBLE(&_8$$5, base);
						ZEPHIR_CALL_FUNCTION(&_9$$5, "log", &_7, 7, &value, &_8$$5);
						zephir_check_call_status();
						zephir_array_append(&rowB, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 1647);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1650);
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
			ZEPHIR_CALL_METHOD(&row, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1650);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _10$$6)
					{
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _10$$6);
						ZVAL_DOUBLE(&_12$$7, base);
						ZEPHIR_CALL_FUNCTION(&_13$$7, "log", &_7, 7, &value, &_12$$7);
						zephir_check_call_status();
						zephir_array_append(&rowB, &_13$$7, PH_SEPARATE, "tensor/matrix.zep", 1647);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_11$$6, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_11$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZVAL_DOUBLE(&_14$$8, base);
							ZEPHIR_CALL_FUNCTION(&_15$$8, "log", &_7, 7, &value, &_14$$8);
							zephir_check_call_status();
							zephir_array_append(&rowB, &_15$$8, PH_SEPARATE, "tensor/matrix.zep", 1647);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1650);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the log of 1 plus the tensor i.e. a transform.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, log1p) {

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
 * Return the sine of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, sin) {

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
 * Compute the arc sine of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, asin) {

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
 * Return the cosine of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, cos) {

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
 * Compute the arc cosine of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, acos) {

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
 * Return the tangent of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, tan) {

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
 * Compute the arc tangent of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, atan) {

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
PHP_METHOD(Tensor_Matrix, rad2deg) {

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
PHP_METHOD(Tensor_Matrix, deg2rad) {

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
 * Sum the rows of the matrix and return a vector.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, sum) {

	zval _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "array_sum");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 12, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the row product of the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, product) {

	zval _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "array_product");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 12, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the minimum of each row in the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, min) {

	zval _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "min");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 12, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the maximum of each row in the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, max) {

	zval _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "max");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 12, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the means of each row and return them in a vector.
 *
 * @throws \InvalidArgumentException
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, mean) {

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
		ZEPHIR_CONCAT_SS(&_2$$3, "Mean is not defined for", " matrices with less than 1 column.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 20, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1796);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_3, this_ptr, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_3, "divide", NULL, 0, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the median vector of this matrix.
 *
 * @throws \RuntimeException
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, median) {

	zval _2$$3;
	zval b;
	zval _0, rowA, median, _3, *_4, _5, _1$$3, mid$$4, _6$$4, _7$$4, _10$$6, _11$$6, _12$$6, mid$$7, _13$$7, _14$$7, _15$$9, _16$$9, _17$$9;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_9 = NULL, *_18 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&median);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&mid$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&mid$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_0, 1)) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Median is not defined for", " with less than 1 column.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 20, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1812);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_3, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_3, 0, "tensor/matrix.zep", 1832);
	if (Z_TYPE_P(&_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_3), _4)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _4);
			zephir_read_property(&_6$$4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
			ZVAL_LONG(&_7$$4, 2);
			ZEPHIR_CALL_FUNCTION(&mid$$4, "intdiv", &_8, 21, &_6$$4, &_7$$4);
			zephir_check_call_status();
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_9, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			zephir_read_property(&_7$$4, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
			if (zephir_safe_mod_zval_long(&_7$$4, 2) == 1) {
				ZEPHIR_OBS_NVAR(&median);
				zephir_array_fetch(&median, &rowA, &mid$$4, PH_NOISY, "tensor/matrix.zep", 1824);
			} else {
				zephir_array_fetch_long(&_10$$6, &rowA, (zephir_get_numberval(&mid$$4) - 1), PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1826);
				zephir_array_fetch(&_11$$6, &rowA, &mid$$4, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1826);
				ZEPHIR_INIT_NVAR(&_12$$6);
				zephir_add_function(&_12$$6, &_10$$6, &_11$$6);
				ZEPHIR_INIT_NVAR(&median);
				ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_12$$6, 2.0));
			}
			zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1829);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_3, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_5, &_3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, &_3, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_13$$7, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
				ZVAL_LONG(&_14$$7, 2);
				ZEPHIR_CALL_FUNCTION(&mid$$7, "intdiv", &_8, 21, &_13$$7, &_14$$7);
				zephir_check_call_status();
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_9, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				zephir_read_property(&_14$$7, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
				if (zephir_safe_mod_zval_long(&_14$$7, 2) == 1) {
					ZEPHIR_OBS_NVAR(&median);
					zephir_array_fetch(&median, &rowA, &mid$$7, PH_NOISY, "tensor/matrix.zep", 1824);
				} else {
					zephir_array_fetch_long(&_15$$9, &rowA, (zephir_get_numberval(&mid$$7) - 1), PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1826);
					zephir_array_fetch(&_16$$9, &rowA, &mid$$7, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1826);
					ZEPHIR_INIT_NVAR(&_17$$9);
					zephir_add_function(&_17$$9, &_15$$9, &_16$$9);
					ZEPHIR_INIT_NVAR(&median);
					ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_17$$9, 2.0));
				}
				zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1829);
			ZEPHIR_CALL_METHOD(NULL, &_3, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_18, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the pth percentile vector of this matrix.
 *
 * @param float p
 * @throws \InvalidArgumentException
 * @throws \RuntimeException
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, percentile) {

	zval _7$$4;
	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_12 = NULL, *_19 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, xHat;
	zval *p_param = NULL, _5, rowA, t, _8, _9, *_10, _11, _1$$3, _2$$3, _3$$3, _4$$3, _6$$4, _13$$5, _14$$5, _15$$5, _16$$6, _17$$6, _18$$6;
	double p, x, remainder;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&b);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1847);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_5, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_5, 1)) {
		ZEPHIR_INIT_VAR(&_6$$4);
		object_init_ex(&_6$$4, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_7$$4);
		ZEPHIR_CONCAT_SS(&_7$$4, "Percentile is not defined for", " with less than 1 column.");
		ZEPHIR_CALL_METHOD(NULL, &_6$$4, "__construct", NULL, 20, &_7$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_6$$4, "tensor/matrix.zep", 1852);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_8, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	x = (((zephir_safe_div_double_long(p, 100)) * (double) (((zephir_get_numberval(&_8) - 1)))) + (double) (1));
	xHat = (int) (x);
	remainder = (x -  (double) xHat);
	zephir_read_property(&_9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_9, 0, "tensor/matrix.zep", 1872);
	if (Z_TYPE_P(&_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_9), _10)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _10);
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_12, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&t);
			zephir_array_fetch_long(&t, &rowA, (xHat - 1), PH_NOISY, "tensor/matrix.zep", 1867);
			zephir_array_fetch_long(&_13$$5, &rowA, xHat, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1869);
			ZEPHIR_INIT_NVAR(&_14$$5);
			zephir_sub_function(&_14$$5, &_13$$5, &t);
			ZEPHIR_INIT_NVAR(&_15$$5);
			ZVAL_DOUBLE(&_15$$5, (zephir_get_doubleval(&t) + (double) ((remainder * zephir_get_numberval(&_14$$5)))));
			zephir_array_append(&b, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 1869);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_9, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_11, &_9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, &_9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_12, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&t);
				zephir_array_fetch_long(&t, &rowA, (xHat - 1), PH_NOISY, "tensor/matrix.zep", 1867);
				zephir_array_fetch_long(&_16$$6, &rowA, xHat, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1869);
				ZEPHIR_INIT_NVAR(&_17$$6);
				zephir_sub_function(&_17$$6, &_16$$6, &t);
				ZEPHIR_INIT_NVAR(&_18$$6);
				ZVAL_DOUBLE(&_18$$6, (zephir_get_doubleval(&t) + (double) ((remainder * zephir_get_numberval(&_17$$6)))));
				zephir_array_append(&b, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 1869);
			ZEPHIR_CALL_METHOD(NULL, &_9, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_19, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the row variance of the matrix.
 *
 * @param mixed mean
 * @throws \InvalidArgumentException
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, variance) {

	zval _7$$5, _9$$5, _10$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *mean = NULL, mean_sub, __$null, _0$$4, _1$$4, _2$$4, _3$$3, _4$$3, _5$$5, _6$$5, _8$$5, _11, _12, _13, _14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&mean_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$4);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &mean);

	if (!mean) {
		mean = &mean_sub;
		ZEPHIR_CPY_WRT(mean, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(mean);
	}


	if (!(Z_TYPE_P(mean) == IS_NULL)) {
		if (!(zephir_instance_of_ev(mean, tensor_columnvector_ce))) {
			ZEPHIR_INIT_VAR(&_0$$4);
			object_init_ex(&_0$$4, spl_ce_InvalidArgumentException);
			ZEPHIR_INIT_VAR(&_1$$4);
			zephir_gettype(&_1$$4, mean);
			ZEPHIR_INIT_VAR(&_2$$4);
			ZEPHIR_CONCAT_SSVS(&_2$$4, "Mean must be a", " column vector ", &_1$$4, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_0$$4, "__construct", NULL, 3, &_2$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_0$$4, "tensor/matrix.zep", 1887);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_3$$3, mean, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_4$$3, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
		if (!ZEPHIR_IS_IDENTICAL(&_3$$3, &_4$$3)) {
			ZEPHIR_INIT_VAR(&_5$$5);
			object_init_ex(&_5$$5, spl_ce_InvalidArgumentException);
			ZEPHIR_OBS_VAR(&_6$$5);
			zephir_read_property(&_6$$5, this_ptr, SL("m"), PH_NOISY_CC);
			zephir_get_strval(&_7$$5, &_6$$5);
			ZEPHIR_CALL_METHOD(&_8$$5, mean, "m", NULL, 0);
			zephir_check_call_status();
			zephir_get_strval(&_9$$5, &_8$$5);
			ZEPHIR_INIT_VAR(&_10$$5);
			ZEPHIR_CONCAT_SSVSVS(&_10$$5, "Mean vector must", " have ", &_7$$5, " rows, ", &_9$$5, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_5$$5, "__construct", NULL, 3, &_10$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_5$$5, "tensor/matrix.zep", 1893);
			ZEPHIR_MM_RESTORE();
			return;
		}
	}
	if (Z_TYPE_P(mean) == IS_NULL) {
		ZEPHIR_CALL_METHOD(mean, this_ptr, "mean", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_11, this_ptr, "subtract", NULL, 0, mean);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_12, &_11, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_13, &_12, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_14, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_13, "divide", NULL, 0, &_14);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the covariance of this matrix and return it in a tuple along with
 * the computed mean.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, covariance) {

	zval b, _0, _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "mean", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&b, this_ptr, "subtract", NULL, 0, &_0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &b, "transpose", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &b, "matmul", NULL, 0, &_2);
	zephir_check_call_status();
	zephir_read_property(&_3, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_1, "divide", NULL, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Round the elements in the matrix to a given decimal place.
 *
 * @param int precision
 * @return self
 */
PHP_METHOD(Tensor_Matrix, round) {

	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *precision_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, row, value, _4, *_5, _6, *_7$$4, _8$$4, _9$$5, _10$$5, _11$$6, _12$$6, *_13$$7, _14$$7, _15$$8, _16$$8, _17$$9, _18$$9;
	zend_long precision, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&value);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 1931);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_4, 0, "tensor/matrix.zep", 1948);
	if (Z_TYPE_P(&_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4), _5)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _5);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1945);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _7$$4)
				{
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _7$$4);
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_10$$5, precision);
					zephir_round(&_9$$5, &value, &_10$$5, NULL);
					zephir_array_append(&rowB, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 1942);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_8$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_8$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						ZVAL_LONG(&_12$$6, precision);
						zephir_round(&_11$$6, &value, &_12$$6, NULL);
						zephir_array_append(&rowB, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 1942);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1945);
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
			ZEPHIR_CALL_METHOD(&row, &_4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1945);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$7)
					{
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _13$$7);
						ZEPHIR_INIT_NVAR(&_15$$8);
						ZVAL_LONG(&_16$$8, precision);
						zephir_round(&_15$$8, &value, &_16$$8, NULL);
						zephir_array_append(&rowB, &_15$$8, PH_SEPARATE, "tensor/matrix.zep", 1942);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_14$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_14$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&value, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_17$$9);
							ZVAL_LONG(&_18$$9, precision);
							zephir_round(&_17$$9, &value, &_18$$9, NULL);
							zephir_array_append(&rowB, &_17$$9, PH_SEPARATE, "tensor/matrix.zep", 1942);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1945);
			ZEPHIR_CALL_METHOD(NULL, &_4, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Round the elements in the matrix down to the nearest integer.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, floor) {

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
 * Round the elements in the matrix up to the nearest integer.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, ceil) {

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
 * Clip the elements in the matrix to be between given minimum and maximum
 * and return a new matrix.
 *
 * @param float min
 * @param float max
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, clip) {

	zval b, rowB;
	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *min_param = NULL, *max_param = NULL, _0$$3, rowA, valueA, _2, *_3, _4, *_5$$4, _6$$4, _7$$6, _8$$7, _9$$9, _10$$10, *_11$$11, _12$$11, _13$$13, _14$$14, _15$$16, _16$$17;
	double min, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_9$$9);
	ZVAL_UNDEF(&_10$$10);
	ZVAL_UNDEF(&_12$$11);
	ZVAL_UNDEF(&_13$$13);
	ZVAL_UNDEF(&_14$$14);
	ZVAL_UNDEF(&_15$$16);
	ZVAL_UNDEF(&_16$$17);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 1984);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/matrix.zep", 2013);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2010);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _5$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _5$$4);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_7$$6);
						ZVAL_DOUBLE(&_7$$6, max);
						zephir_array_append(&rowB, &_7$$6, PH_SEPARATE, "tensor/matrix.zep", 1996);
						continue;
					}
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_8$$7);
						ZVAL_DOUBLE(&_8$$7, min);
						zephir_array_append(&rowB, &_8$$7, PH_SEPARATE, "tensor/matrix.zep", 2002);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2007);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_6$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_6$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_9$$9);
							ZVAL_DOUBLE(&_9$$9, max);
							zephir_array_append(&rowB, &_9$$9, PH_SEPARATE, "tensor/matrix.zep", 1996);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_10$$10);
							ZVAL_DOUBLE(&_10$$10, min);
							zephir_array_append(&rowB, &_10$$10, PH_SEPARATE, "tensor/matrix.zep", 2002);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2007);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2010);
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
			ZEPHIR_CALL_METHOD(&rowA, &_2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2010);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$11)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$11);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_13$$13);
							ZVAL_DOUBLE(&_13$$13, max);
							zephir_array_append(&rowB, &_13$$13, PH_SEPARATE, "tensor/matrix.zep", 1996);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_14$$14);
							ZVAL_DOUBLE(&_14$$14, min);
							zephir_array_append(&rowB, &_14$$14, PH_SEPARATE, "tensor/matrix.zep", 2002);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2007);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_12$$11, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_12$$11)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
								ZEPHIR_INIT_NVAR(&_15$$16);
								ZVAL_DOUBLE(&_15$$16, max);
								zephir_array_append(&rowB, &_15$$16, PH_SEPARATE, "tensor/matrix.zep", 1996);
								continue;
							}
							if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
								ZEPHIR_INIT_NVAR(&_16$$17);
								ZVAL_DOUBLE(&_16$$17, min);
								zephir_array_append(&rowB, &_16$$17, PH_SEPARATE, "tensor/matrix.zep", 2002);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2007);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2010);
			ZEPHIR_CALL_METHOD(NULL, &_2, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Clip the tensor to be lower bounded by a given minimum.
 *
 * @param float min
 * @return self
 */
PHP_METHOD(Tensor_Matrix, clipLower) {

	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *min_param = NULL, rowA, valueA, _0, *_1, _2, *_3$$3, _4$$3, _5$$5, _6$$7, *_7$$8, _8$$8, _9$$10, _10$$12;
	double min;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$10);
	ZVAL_UNDEF(&_10$$12);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &min_param);

	min = zephir_get_doubleval(min_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2044);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2041);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_DOUBLE(&_5$$5, min);
						zephir_array_append(&rowB, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2033);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2038);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$3, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_6$$7);
							ZVAL_DOUBLE(&_6$$7, min);
							zephir_array_append(&rowB, &_6$$7, PH_SEPARATE, "tensor/matrix.zep", 2033);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2038);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2041);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2041);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _7$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _7$$8);
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_DOUBLE(&_9$$10, min);
							zephir_array_append(&rowB, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2033);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2038);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_8$$8, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_8$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
								ZEPHIR_INIT_NVAR(&_10$$12);
								ZVAL_DOUBLE(&_10$$12, min);
								zephir_array_append(&rowB, &_10$$12, PH_SEPARATE, "tensor/matrix.zep", 2033);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2038);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2041);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Clip the tensor to be upper bounded by a given maximum.
 *
 * @param float max
 * @return self
 */
PHP_METHOD(Tensor_Matrix, clipUpper) {

	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *max_param = NULL, rowA, valueA, _0, *_1, _2, *_3$$3, _4$$3, _5$$5, _6$$7, *_7$$8, _8$$8, _9$$10, _10$$12;
	double max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_8$$8);
	ZVAL_UNDEF(&_9$$10);
	ZVAL_UNDEF(&_10$$12);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &max_param);

	max = zephir_get_doubleval(max_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2075);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2072);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_DOUBLE(&_5$$5, max);
						zephir_array_append(&rowB, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2064);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2069);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$3, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_6$$7);
							ZVAL_DOUBLE(&_6$$7, max);
							zephir_array_append(&rowB, &_6$$7, PH_SEPARATE, "tensor/matrix.zep", 2064);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2069);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2072);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2072);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _7$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _7$$8);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_DOUBLE(&_9$$10, max);
							zephir_array_append(&rowB, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2064);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2069);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_8$$8, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_8$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
								ZEPHIR_INIT_NVAR(&_10$$12);
								ZVAL_DOUBLE(&_10$$12, max);
								zephir_array_append(&rowB, &_10$$12, PH_SEPARATE, "tensor/matrix.zep", 2064);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2069);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2072);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise sign indication.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, sign) {

	zval b, rowB;
	zval rowA, valueA, _0, *_1, _2, *_3$$3, _4$$3, _5$$5, _6$$6, _7$$7, _8$$9, _9$$10, _10$$11, *_11$$12, _12$$12, _13$$14, _14$$15, _15$$16, _16$$18, _17$$19, _18$$20;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$9);
	ZVAL_UNDEF(&_9$$10);
	ZVAL_UNDEF(&_10$$11);
	ZVAL_UNDEF(&_12$$12);
	ZVAL_UNDEF(&_13$$14);
	ZVAL_UNDEF(&_14$$15);
	ZVAL_UNDEF(&_15$$16);
	ZVAL_UNDEF(&_16$$18);
	ZVAL_UNDEF(&_17$$19);
	ZVAL_UNDEF(&_18$$20);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2105);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2102);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_GT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_LONG(&_5$$5, 1);
						zephir_array_append(&rowB, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2094);
					} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_6$$6);
						ZVAL_LONG(&_6$$6, -1);
						zephir_array_append(&rowB, &_6$$6, PH_SEPARATE, "tensor/matrix.zep", 2096);
					} else {
						ZEPHIR_INIT_NVAR(&_7$$7);
						ZVAL_LONG(&_7$$7, 0);
						zephir_array_append(&rowB, &_7$$7, PH_SEPARATE, "tensor/matrix.zep", 2098);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$3, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_GT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_8$$9);
							ZVAL_LONG(&_8$$9, 1);
							zephir_array_append(&rowB, &_8$$9, PH_SEPARATE, "tensor/matrix.zep", 2094);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_LONG(&_9$$10, -1);
							zephir_array_append(&rowB, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2096);
						} else {
							ZEPHIR_INIT_NVAR(&_10$$11);
							ZVAL_LONG(&_10$$11, 0);
							zephir_array_append(&rowB, &_10$$11, PH_SEPARATE, "tensor/matrix.zep", 2098);
						}
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2102);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2102);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$12)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$12);
						if (ZEPHIR_GT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_13$$14);
							ZVAL_LONG(&_13$$14, 1);
							zephir_array_append(&rowB, &_13$$14, PH_SEPARATE, "tensor/matrix.zep", 2094);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_14$$15);
							ZVAL_LONG(&_14$$15, -1);
							zephir_array_append(&rowB, &_14$$15, PH_SEPARATE, "tensor/matrix.zep", 2096);
						} else {
							ZEPHIR_INIT_NVAR(&_15$$16);
							ZVAL_LONG(&_15$$16, 0);
							zephir_array_append(&rowB, &_15$$16, PH_SEPARATE, "tensor/matrix.zep", 2098);
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_12$$12, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_12$$12)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_GT_LONG(&valueA, 0)) {
								ZEPHIR_INIT_NVAR(&_16$$18);
								ZVAL_LONG(&_16$$18, 1);
								zephir_array_append(&rowB, &_16$$18, PH_SEPARATE, "tensor/matrix.zep", 2094);
							} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
								ZEPHIR_INIT_NVAR(&_17$$19);
								ZVAL_LONG(&_17$$19, -1);
								zephir_array_append(&rowB, &_17$$19, PH_SEPARATE, "tensor/matrix.zep", 2096);
							} else {
								ZEPHIR_INIT_NVAR(&_18$$20);
								ZVAL_LONG(&_18$$20, 0);
								zephir_array_append(&rowB, &_18$$20, PH_SEPARATE, "tensor/matrix.zep", 2098);
							}
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2102);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Negate the matrix i.e take the negative of each value elementwise.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, negate) {

	zval b, rowB;
	zval rowA, valueA, _0, *_1, _2, *_3$$3, _4$$3, *_5$$6, _6$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2129);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2126);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					zephir_negate(&valueA);
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2123);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_4$$3, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_4$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						zephir_negate(&valueA);
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2123);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2126);
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
			ZEPHIR_CALL_METHOD(&rowA, &_0, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2126);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _5$$6)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _5$$6);
						zephir_negate(&valueA);
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2123);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_6$$6, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_6$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							zephir_negate(&valueA);
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2123);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2126);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the square submatrix starting at an offset on the diagonal
 * and excluding the last n rows and columns.
 * 
 * @param int offset
 * @param int n
 * @throws InvalidArgumentExeption
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subMatrix) {

	zval _13$$5;
	zval b, rowB;
	zend_bool _10, _15, _19$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *offset_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _11, rowA, _14, _12$$5, _18$$6, _22$$7;
	zend_long offset, n, ZEPHIR_LAST_CALL_STATUS, last, i = 0, j = 0, k, _16, _17, _20$$6, _21$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_13$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &offset_param, &n_param);

	if (!offset_param) {
		offset = 0;
	} else {
		offset = zephir_get_intval(offset_param);
	}
	if (!n_param) {
		n = 1;
	} else {
		n = zephir_get_intval(n_param);
	}


	if (offset < 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, offset);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", &_3, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Offset cannot be less", " than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 2145);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (n < 0) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_3, 2, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "N cannot be less than", " 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 2150);
		ZEPHIR_MM_RESTORE();
		return;
	}
	last = (offset + n);
	zephir_read_property(&_9, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_10 = ZEPHIR_LT_LONG(&_9, last);
	if (!(_10)) {
		zephir_read_property(&_11, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		_10 = ZEPHIR_LT_LONG(&_11, last);
	}
	if (_10) {
		ZEPHIR_INIT_VAR(&_12$$5);
		object_init_ex(&_12$$5, spl_ce_InvalidArgumentException);
		ZEPHIR_INIT_VAR(&_13$$5);
		ZEPHIR_CONCAT_SS(&_13$$5, "Sub matrix is out of", " bounds of matrix A.");
		ZEPHIR_CALL_METHOD(NULL, &_12$$5, "__construct", NULL, 3, &_13$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_12$$5, "tensor/matrix.zep", 2157);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_14, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	k = ((zephir_get_numberval(&_14) - n) - 1);
	_17 = k;
	_16 = offset;
	_15 = 0;
	if (_16 <= _17) {
		while (1) {
			if (_15) {
				_16++;
				if (!(_16 <= _17)) {
					break;
				}
			} else {
				_15 = 1;
			}
			i = _16;
			zephir_read_property(&_18$$6, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch_long(&rowA, &_18$$6, i, PH_NOISY, "tensor/matrix.zep", 2168);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			_21$$6 = k;
			_20$$6 = offset;
			_19$$6 = 0;
			if (_20$$6 <= _21$$6) {
				while (1) {
					if (_19$$6) {
						_20$$6++;
						if (!(_20$$6 <= _21$$6)) {
							break;
						}
					} else {
						_19$$6 = 1;
					}
					j = _20$$6;
					zephir_array_fetch_long(&_22$$7, &rowA, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2173);
					zephir_array_append(&rowB, &_22$$7, PH_SEPARATE, "tensor/matrix.zep", 2173);
				}
			}
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2176);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attach matrix b above this matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, augmentAbove) {

	zval _6$$3, _8$$3, _9$$3;
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2, _3, _10, _11, _12, _4$$3, _5$$3, _7$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " columns but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2194);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_CALL_METHOD(&_11, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_12, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_array_merge(&_10, &_11, &_12);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_10);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attach matrix b below this matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, augmentBelow) {

	zval _6$$3, _8$$3, _9$$3;
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2, _3, _10, _11, _12, _4$$3, _5$$3, _7$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, SL("n"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " columns but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2212);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_10);
	zephir_read_property(&_11, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_12, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_fast_array_merge(&_10, &_11, &_12);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_10);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attach matrix b to the left of this matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, augmentLeft) {

	zval _6$$3, _8$$3, _9$$3;
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2, _3, _10, _11, _12, _13, _4$$3, _5$$3, _7$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " rows but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2230);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_11, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "array_merge");
	ZEPHIR_CALL_FUNCTION(&_13, "array_map", NULL, 12, &_12, &_10, &_11);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_13);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attach matrix b to the left of this matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, augmentRight) {

	zval _6$$3, _8$$3, _9$$3;
	zend_bool _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _2, _3, _10, _11, _12, _13, _4$$3, _5$$3, _7$$3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_9$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (_1) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " rows but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2248);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_10, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_11, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "array_merge");
	ZEPHIR_CALL_FUNCTION(&_13, "array_map", NULL, 12, &_12, &_10, &_11);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_13);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Repeat the matrix m times along the vertival axes and n times along the
 * horizontal axes.
 *
 * @param int m
 * @param int n
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, repeat) {

	zend_string *_6$$3;
	zend_ulong _5$$3;
	zend_bool _17, _7$$4, _12$$6;
	zval b, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, i, rowA, _0, c, _2$$3, *_3$$3, _4$$3, _10$$5, _11$$5, _15$$7, _16$$7, _20$$8;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, j = 0, k = 0, _18, _19, _8$$4, _9$$4, _13$$6, _14$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_OBS_VAR(&_0);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC);
	zephir_get_arrval(&_1, &_0);
	ZEPHIR_CPY_WRT(&b, &_1);
	if (n > 0) {
		zephir_read_property(&_2$$3, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_2$$3, 0, "tensor/matrix.zep", 2277);
		if (Z_TYPE_P(&_2$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_2$$3), _5$$3, _6$$3, _3$$3)
			{
				ZEPHIR_INIT_NVAR(&i);
				if (_6$$3 != NULL) { 
					ZVAL_STR_COPY(&i, _6$$3);
				} else {
					ZVAL_LONG(&i, _5$$3);
				}
				ZEPHIR_INIT_NVAR(&rowA);
				ZVAL_COPY(&rowA, _3$$3);
				_9$$4 = (n - 1);
				_8$$4 = 0;
				_7$$4 = 0;
				if (_8$$4 <= _9$$4) {
					while (1) {
						if (_7$$4) {
							_8$$4++;
							if (!(_8$$4 <= _9$$4)) {
								break;
							}
						} else {
							_7$$4 = 1;
						}
						j = _8$$4;
						ZEPHIR_INIT_NVAR(&_10$$5);
						zephir_array_fetch(&_11$$5, &b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2274);
						zephir_fast_array_merge(&_10$$5, &_11$$5, &rowA);
						zephir_array_update_zval(&b, &i, &_10$$5, PH_COPY | PH_SEPARATE);
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &_2$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_4$$3, &_2$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_4$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&i, &_2$$3, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&rowA, &_2$$3, "current", NULL, 0);
				zephir_check_call_status();
					_14$$6 = (n - 1);
					_13$$6 = 0;
					_12$$6 = 0;
					if (_13$$6 <= _14$$6) {
						while (1) {
							if (_12$$6) {
								_13$$6++;
								if (!(_13$$6 <= _14$$6)) {
									break;
								}
							} else {
								_12$$6 = 1;
							}
							j = _13$$6;
							ZEPHIR_INIT_NVAR(&_15$$7);
							zephir_array_fetch(&_16$$7, &b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2274);
							zephir_fast_array_merge(&_15$$7, &_16$$7, &rowA);
							zephir_array_update_zval(&b, &i, &_15$$7, PH_COPY | PH_SEPARATE);
						}
					}
				ZEPHIR_CALL_METHOD(NULL, &_2$$3, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&rowA);
		ZEPHIR_INIT_NVAR(&i);
	}
	ZEPHIR_CPY_WRT(&c, &b);
	_19 = (m - 1);
	_18 = 0;
	_17 = 0;
	if (_18 <= _19) {
		while (1) {
			if (_17) {
				_18++;
				if (!(_18 <= _19)) {
					break;
				}
			} else {
				_17 = 1;
			}
			k = _18;
			ZEPHIR_INIT_NVAR(&_20$$8);
			zephir_fast_array_merge(&_20$$8, &c, &b);
			ZEPHIR_CPY_WRT(&c, &_20$$8);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise product between this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2299);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2318);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2307);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2315);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2312);
					ZEPHIR_INIT_NVAR(&_17$$5);
					mul_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2312);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2312);
						ZEPHIR_INIT_NVAR(&_19$$6);
						mul_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2312);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2315);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2307);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2315);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2312);
						ZEPHIR_INIT_NVAR(&_26$$8);
						mul_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2312);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2312);
							ZEPHIR_INIT_NVAR(&_28$$9);
							mul_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2312);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2315);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the division of two elements, element-wise.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2332);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2351);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2340);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2348);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2345);
					ZEPHIR_INIT_NVAR(&_17$$5);
					div_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2345);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2345);
						ZEPHIR_INIT_NVAR(&_19$$6);
						div_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2345);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2348);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2340);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2348);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2345);
						ZEPHIR_INIT_NVAR(&_26$$8);
						div_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2345);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2345);
							ZEPHIR_INIT_NVAR(&_28$$9);
							div_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2345);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2348);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this matrix together with another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2365);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2384);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2373);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2381);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2378);
					ZEPHIR_INIT_NVAR(&_17$$5);
					zephir_add_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2378);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2378);
						ZEPHIR_INIT_NVAR(&_19$$6);
						zephir_add_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2378);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2381);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2373);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2381);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2378);
						ZEPHIR_INIT_NVAR(&_26$$8);
						zephir_add_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2378);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2378);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_add_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2378);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2381);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a matrix from this matrix element-wise.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2398);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2417);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2406);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2414);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2411);
					ZEPHIR_INIT_NVAR(&_17$$5);
					zephir_sub_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2411);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2411);
						ZEPHIR_INIT_NVAR(&_19$$6);
						zephir_sub_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2411);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2414);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2406);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2414);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2411);
						ZEPHIR_INIT_NVAR(&_26$$8);
						zephir_sub_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2411);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2411);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_sub_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2411);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2414);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this matrix to the power of the elementwise entry in another
 * matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2432);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2451);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2440);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2448);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2445);
					zephir_pow_function(&_16$$5, &valueA, &_17$$5);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2445);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2445);
						zephir_pow_function(&_18$$6, &valueA, &_19$$6);
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2445);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2448);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2440);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2448);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2445);
						zephir_pow_function(&_25$$8, &valueA, &_26$$8);
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2445);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2445);
							zephir_pow_function(&_27$$9, &valueA, &_28$$9);
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2445);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2448);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus i.e remainder of division between this matri and
 * another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2466);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2485);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2474);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2482);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_15$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _15$$4);
					} else {
						ZVAL_LONG(&j, _14$$4);
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _12$$4);
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2479);
					ZEPHIR_INIT_NVAR(&_17$$5);
					mod_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2479);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2479);
						ZEPHIR_INIT_NVAR(&_19$$6);
						mod_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2479);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2482);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2474);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2482);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_24$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _24$$7);
						} else {
							ZVAL_LONG(&j, _23$$7);
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _21$$7);
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2479);
						ZEPHIR_INIT_NVAR(&_26$$8);
						mod_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2479);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2479);
							ZEPHIR_INIT_NVAR(&_28$$9);
							mod_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2479);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2482);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this matrix and
 * another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2500);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2519);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2508);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2516);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2513);
					if (ZEPHIR_IS_EQUAL(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2513);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2513);
						if (ZEPHIR_IS_EQUAL(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2513);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2516);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2508);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2516);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2513);
						if (ZEPHIR_IS_EQUAL(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2513);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2513);
							if (ZEPHIR_IS_EQUAL(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2513);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2516);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this matrix and
 * another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2534);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2553);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2542);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2550);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2547);
					if (!ZEPHIR_IS_EQUAL(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2547);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2547);
						if (!ZEPHIR_IS_EQUAL(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2547);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2550);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2542);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2550);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2547);
						if (!ZEPHIR_IS_EQUAL(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2547);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2547);
							if (!ZEPHIR_IS_EQUAL(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2547);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2550);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this matrix
 * and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2568);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2587);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2576);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2584);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2581);
					if (ZEPHIR_GT(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2581);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2581);
						if (ZEPHIR_GT(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2581);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2584);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2576);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2584);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2581);
						if (ZEPHIR_GT(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2581);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2581);
							if (ZEPHIR_GT(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2581);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2584);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2602);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2621);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2610);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2618);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2615);
					if (ZEPHIR_GE(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2615);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2615);
						if (ZEPHIR_GE(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2615);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2618);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2610);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2618);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2615);
						if (ZEPHIR_GE(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2615);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2615);
							if (ZEPHIR_GE(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2615);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2618);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this matrix
 * and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2636);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2655);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2644);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2652);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2649);
					if (ZEPHIR_LT(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2649);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2649);
						if (ZEPHIR_LT(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2649);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2652);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2644);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2652);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2649);
						if (ZEPHIR_LT(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2649);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2649);
							if (ZEPHIR_LT(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2649);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2652);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualMatrix) {

	zend_string *_10, *_15$$4, *_24$$7;
	zend_ulong _9, _14$$4, _23$$7;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, j, rowA, rowB, valueA, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, *_12$$4, _13$$4, _16$$5, _17$$5, _18$$6, _19$$6, _20$$7, *_21$$7, _22$$7, _25$$8, _26$$8, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
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
	ZVAL_UNDEF(&rowC);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix needed but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2670);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2689);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_6), _9, _10, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_10 != NULL) { 
				ZVAL_STR_COPY(&i, _10);
			} else {
				ZVAL_LONG(&i, _9);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _7);
			zephir_read_property(&_11$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2678);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2686);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _14$$4, _15$$4, _12$$4)
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2683);
					if (ZEPHIR_LE(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2683);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2683);
						if (ZEPHIR_LE(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2683);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2686);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_6, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_8, &_6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_8)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_6, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_6, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_20$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2678);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2686);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _23$$7, _24$$7, _21$$7)
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2683);
						if (ZEPHIR_LE(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2683);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_22$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowA, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$9);
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2683);
							if (ZEPHIR_LE(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2683);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2686);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this matrix by a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2704);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2723);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2720);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2717);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mul_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2717);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2717);
						ZEPHIR_INIT_NVAR(&_18$$6);
						mul_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2717);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2720);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2720);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2717);
						ZEPHIR_INIT_NVAR(&_24$$8);
						mul_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2717);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2717);
							ZEPHIR_INIT_NVAR(&_26$$9);
							mul_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2717);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2720);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this matrix by a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2738);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2757);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2754);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2751);
					ZEPHIR_INIT_NVAR(&_16$$5);
					div_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2751);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2751);
						ZEPHIR_INIT_NVAR(&_18$$6);
						div_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2751);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2754);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2754);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2751);
						ZEPHIR_INIT_NVAR(&_24$$8);
						div_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2751);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2751);
							ZEPHIR_INIT_NVAR(&_26$$9);
							div_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2751);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2754);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this matrix by a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2772);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2791);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2788);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2785);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_add_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2785);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2785);
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_add_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2785);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2788);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2788);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2785);
						ZEPHIR_INIT_NVAR(&_24$$8);
						zephir_add_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2785);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2785);
							ZEPHIR_INIT_NVAR(&_26$$9);
							zephir_add_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2785);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2788);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a vector from this matrix.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2806);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2825);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2822);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2819);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_sub_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2819);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2819);
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_sub_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2819);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2822);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2822);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2819);
						ZEPHIR_INIT_NVAR(&_24$$8);
						zephir_sub_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2819);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2819);
							ZEPHIR_INIT_NVAR(&_26$$9);
							zephir_sub_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2819);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2822);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this matrix to the power of a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2840);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2859);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2856);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2853);
					zephir_pow_function(&_15$$5, &_16$$5, &valueB);
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2853);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2853);
						zephir_pow_function(&_17$$6, &_18$$6, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2853);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2856);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2856);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2853);
						zephir_pow_function(&_23$$8, &_24$$8, &valueB);
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2853);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2853);
							zephir_pow_function(&_25$$9, &_26$$9, &valueB);
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2853);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2856);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this matrix with a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2874);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2893);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2890);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2887);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mod_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2887);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2887);
						ZEPHIR_INIT_NVAR(&_18$$6);
						mod_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2887);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2890);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2890);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2887);
						ZEPHIR_INIT_NVAR(&_24$$8);
						mod_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2887);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2887);
							ZEPHIR_INIT_NVAR(&_26$$9);
							mod_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2887);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2890);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this matrix and a
 * vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2909);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2928);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2925);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2922);
					if (ZEPHIR_IS_EQUAL(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2922);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2922);
						if (ZEPHIR_IS_EQUAL(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2922);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2925);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2925);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2922);
						if (ZEPHIR_IS_EQUAL(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2922);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2922);
							if (ZEPHIR_IS_EQUAL(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2922);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2925);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this matrix and a
 * vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2944);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2963);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2960);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2957);
					if (!ZEPHIR_IS_EQUAL(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2957);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2957);
						if (!ZEPHIR_IS_EQUAL(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2957);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2960);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2960);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2957);
						if (!ZEPHIR_IS_EQUAL(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2957);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2957);
							if (!ZEPHIR_IS_EQUAL(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2957);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2960);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this matrix
 * and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2979);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2998);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2995);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2992);
					if (ZEPHIR_GT(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2992);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2992);
						if (ZEPHIR_GT(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2992);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2995);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2995);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2992);
						if (ZEPHIR_GT(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2992);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2992);
							if (ZEPHIR_GT(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2992);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 2995);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3014);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3033);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3030);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3027);
					if (ZEPHIR_GE(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3027);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3027);
						if (ZEPHIR_GE(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3027);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3030);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3030);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3027);
						if (ZEPHIR_GE(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3027);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3027);
							if (ZEPHIR_GE(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3027);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3030);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this matrix
 * and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3049);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3068);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3065);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3062);
					if (ZEPHIR_LT(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3062);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3062);
						if (ZEPHIR_LT(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3062);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3065);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3065);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3062);
						if (ZEPHIR_LT(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3062);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3062);
							if (ZEPHIR_LT(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3062);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3065);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualVector) {

	zend_string *_14$$4, *_22$$7;
	zend_ulong _13$$4, _21$$7;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, j, rowA, valueB, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, *_11$$4, _12$$4, _15$$5, _16$$5, _17$$6, _18$$6, *_19$$7, _20$$7, _23$$8, _24$$8, _25$$9, _26$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3084);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3103);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3100);
			if (Z_TYPE_P(&bHat) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _13$$4, _14$$4, _11$$4)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_14$$4 != NULL) { 
						ZVAL_STR_COPY(&j, _14$$4);
					} else {
						ZVAL_LONG(&j, _13$$4);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _11$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3097);
					if (ZEPHIR_LE(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3097);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_12$$4, &bHat, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_12$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3097);
						if (ZEPHIR_LE(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3097);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3100);
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
			ZEPHIR_CALL_METHOD(&rowA, &_8, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3100);
				if (Z_TYPE_P(&bHat) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _21$$7, _22$$7, _19$$7)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_22$$7 != NULL) { 
							ZVAL_STR_COPY(&j, _22$$7);
						} else {
							ZVAL_LONG(&j, _21$$7);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_23$$8);
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3097);
						if (ZEPHIR_LE(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3097);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bHat, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &bHat, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &bHat, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &bHat, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_25$$9);
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3097);
							if (ZEPHIR_LE(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3097);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3100);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this matrix with a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3118);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3137);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3126);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3134);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mul_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3131);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						mul_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3131);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3134);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3126);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3134);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						mul_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3131);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							mul_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3131);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3134);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this matrix with a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3152);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3171);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3160);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3168);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					div_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3165);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						div_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3165);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3168);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3160);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3168);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						div_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3165);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							div_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3165);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3168);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this matrix to a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3186);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3205);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3194);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3202);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_add_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3199);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_add_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3199);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3202);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3194);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3202);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_add_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3199);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							zephir_add_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3199);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3202);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a column vector from this matrix.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3220);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3239);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3228);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3236);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_sub_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3233);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_sub_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3233);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3236);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3228);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3236);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_sub_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3233);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							zephir_sub_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3233);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3236);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this matrix to the power of a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3254);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3273);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3262);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3270);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_pow_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3267);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_pow_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3267);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3270);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3262);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3270);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_pow_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3267);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							zephir_pow_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3267);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3270);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Mod this matrix with a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3288);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3307);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3296);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3304);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mod_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3301);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						mod_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3301);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3304);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3296);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3304);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						mod_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3301);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							mod_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3301);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3304);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this matrix and
 * a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3323);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3342);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3331);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3339);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3336);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3336);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3339);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3331);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3339);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3336);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3336);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3339);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this matrix and
 * a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3358);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3377);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3366);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3374);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3371);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3371);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3374);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3366);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3374);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3371);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3371);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3374);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this matrix and
 * a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3393);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3412);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3401);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3409);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_GT(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3406);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_GT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3406);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3409);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3401);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3409);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_GT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3406);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_GT(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3406);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3409);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3428);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3447);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3436);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3444);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_GE(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3441);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_GE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3441);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3444);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3436);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3444);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_GE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3441);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_GE(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3441);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3444);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this matrix and
 * a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3463);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3482);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3471);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3479);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_LT(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3476);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_LT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3476);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3479);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3471);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3479);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_LT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3476);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_LT(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3476);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3479);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualColumnVector) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowA, valueA, valueB, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	if (!ZEPHIR_IS_IDENTICAL(&_0, &_1)) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, spl_ce_InvalidArgumentException);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, SL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3498);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3517);
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
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3506);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3514);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_LE(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3511);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_LE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3511);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3514);
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
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&rowA);
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3506);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3514);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_LE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3511);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_LE(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3511);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3514);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&valueB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this matrix by a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3531);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3548);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3545);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					mul_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3542);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						mul_function(&_11$$6, &valueA, b);
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3542);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3545);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3545);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						mul_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3542);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							mul_function(&_15$$9, &valueA, b);
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3542);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3545);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this matrix by a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3562);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3579);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3576);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					div_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3573);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						div_function(&_11$$6, &valueA, b);
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3573);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3576);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3576);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						div_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3573);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							div_function(&_15$$9, &valueA, b);
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3573);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3576);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this matrix by a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3593);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3610);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3607);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					zephir_add_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3604);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						zephir_add_function(&_11$$6, &valueA, b);
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3604);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3607);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3607);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						zephir_add_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3604);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							zephir_add_function(&_15$$9, &valueA, b);
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3604);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3607);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a scalar from this matrix.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3624);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3641);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3638);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					zephir_sub_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3635);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						zephir_sub_function(&_11$$6, &valueA, b);
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3635);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3638);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3638);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						zephir_sub_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3635);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							zephir_sub_function(&_15$$9, &valueA, b);
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3635);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3638);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise the matrix to a given scalar power.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3656);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3673);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3670);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					zephir_pow_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3667);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						zephir_pow_function(&_11$$6, &valueA, b);
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3667);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3670);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3670);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						zephir_pow_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3667);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							zephir_pow_function(&_15$$9, &valueA, b);
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3667);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3670);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the modulus of this matrix with a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3687);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3704);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3701);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					mod_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3698);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						mod_function(&_11$$6, &valueA, b);
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3698);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3701);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3701);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						mod_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3698);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							mod_function(&_15$$9, &valueA, b);
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3698);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3701);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this matrix and a
 * scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3719);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3736);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3733);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					if (ZEPHIR_IS_EQUAL(&valueA, b)) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3730);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						if (ZEPHIR_IS_EQUAL(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 0);
						}
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3730);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3733);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3733);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						if (ZEPHIR_IS_EQUAL(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 0);
						}
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3730);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							if (ZEPHIR_IS_EQUAL(&valueA, b)) {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 0);
							}
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3730);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3733);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this matrix and a
 * scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3751);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3768);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3765);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					if (!ZEPHIR_IS_EQUAL(&valueA, b)) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3762);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						if (!ZEPHIR_IS_EQUAL(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 0);
						}
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3762);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3765);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3765);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						if (!ZEPHIR_IS_EQUAL(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 0);
						}
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3762);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							if (!ZEPHIR_IS_EQUAL(&valueA, b)) {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 0);
							}
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3762);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3765);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this matrix and a
 * scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3783);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3800);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3797);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					if (ZEPHIR_GT(&valueA, b)) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3794);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						if (ZEPHIR_GT(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 0);
						}
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3794);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3797);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3797);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						if (ZEPHIR_GT(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 0);
						}
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3794);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							if (ZEPHIR_GT(&valueA, b)) {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 0);
							}
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3794);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3797);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this matrix and a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3815);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3832);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3829);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					if (ZEPHIR_GE(&valueA, b)) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3826);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						if (ZEPHIR_GE(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 0);
						}
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3826);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3829);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3829);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						if (ZEPHIR_GE(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 0);
						}
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3826);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							if (ZEPHIR_GE(&valueA, b)) {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 0);
							}
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3826);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3829);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this matrix and a
 * scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3847);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3864);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3861);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					if (ZEPHIR_LT(&valueA, b)) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3858);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						if (ZEPHIR_LT(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 0);
						}
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3858);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3861);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3861);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						if (ZEPHIR_LT(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 0);
						}
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3858);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							if (ZEPHIR_LT(&valueA, b)) {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 0);
							}
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3858);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3861);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this matrix and a scalar.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualScalar) {

	zval c, rowC;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, valueA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, *_8$$4, _9$$4, _10$$5, _11$$6, *_12$$7, _13$$7, _14$$8, _15$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3879);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3896);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3893);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					if (ZEPHIR_LE(&valueA, b)) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowC, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3890);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_11$$6);
						if (ZEPHIR_LE(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_11$$6);
							ZVAL_LONG(&_11$$6, 0);
						}
						zephir_array_append(&rowC, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3890);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3893);
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
			ZEPHIR_CALL_METHOD(&rowA, &_5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3893);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						if (ZEPHIR_LE(&valueA, b)) {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$8);
							ZVAL_LONG(&_14$$8, 0);
						}
						zephir_array_append(&rowC, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3890);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_13$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_13$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_15$$9);
							if (ZEPHIR_LE(&valueA, b)) {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_15$$9);
								ZVAL_LONG(&_15$$9, 0);
							}
							zephir_array_append(&rowC, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3890);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/matrix.zep", 3893);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @return int
 */
PHP_METHOD(Tensor_Matrix, count) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "size", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param mixed index
 * @param array values
 * @throws \RuntimeException
 */
PHP_METHOD(Tensor_Matrix, offsetSet) {

	zval *index, index_sub, *values, values_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&values_sub);

	zephir_fetch_params_without_memory_grow(2, 0, &index, &values);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3914);
	return;

}

/**
 * Does a given column exist in the matrix.
 *
 * @param mixed index
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, offsetExists) {

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
PHP_METHOD(Tensor_Matrix, offsetUnset) {

	zval *index, index_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &index);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3934);
	return;

}

/**
 * Return a row from the matrix at the given index.
 *
 * @param mixed index
 * @throws \InvalidArgumentException
 * @return array
 */
PHP_METHOD(Tensor_Matrix, offsetGet) {

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
	zephir_throw_exception_debug(&_1, "tensor/matrix.zep", 3953);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Get an iterator for the rows in the matrix.
 *
 * @return \ArrayIterator
 */
PHP_METHOD(Tensor_Matrix, getIterator) {

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
PHP_METHOD(Tensor_Matrix, __toString) {

	zval _1;
	zval _0, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "Tensor\\Matrix");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "implodeRow");
	zephir_array_fast_append(&_1, &_2);
	ZEPHIR_INIT_NVAR(&_2);
	ZVAL_STRING(&_2, "");
	ZEPHIR_CALL_FUNCTION(&_3, "array_reduce", NULL, 17, &_0, &_1, &_2);
	zephir_check_call_status();
	ZEPHIR_INIT_NVAR(&_2);
	ZEPHIR_GET_CONSTANT(&_2, "PHP_EOL");
	ZEPHIR_CONCAT_VV(return_value, &_3, &_2);
	RETURN_MM();

}

/**
 * Implode a row of the matrix and return the output.
 *
 * @param string carry
 * @param array row
 * @return string
 */
PHP_METHOD(Tensor_Matrix, implodeRow) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval row;
	zval *carry_param = NULL, *row_param = NULL, _0, _1;
	zval carry;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&carry);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&row);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &carry_param, &row_param);

	zephir_get_strval(&carry, carry_param);
	zephir_get_arrval(&row, row_param);


	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "PHP_EOL");
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_join_str(&_1, SL(" "), &row);
	ZEPHIR_CONCAT_VVSVS(return_value, &carry, &_0, "[ ", &_1, " ]");
	RETURN_MM();

}

