
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

	tensor_matrix_ce->create_object = zephir_init_properties_Tensor_Matrix;

	zend_class_implements(tensor_matrix_ce, 1, tensor_tensor_ce);
	return SUCCESS;

}

/**
 * Factory method to build a new matrix from an array.
 *
 * @param array a
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
 * @param array a
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
	zval a, rowA$$4;
	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0$$3, _8$$5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, _3, _4, _6$$4, _7$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA$$4);

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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 78);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
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
			ZEPHIR_INIT_NVAR(&rowA$$4);
			array_init(&rowA$$4);
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
					zephir_array_append(&rowA$$4, &_8$$5, PH_SEPARATE, "tensor/matrix.zep", 89);
				}
			}
			zephir_array_append(&a, &rowA$$4, PH_SEPARATE, "tensor/matrix.zep", 92);
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
 * @param array elements
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
	zval elements, a, rowA$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&elements);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA$$8);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 138);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_is_iterable(&elements, 0, "tensor/matrix.zep", 151);
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
				zephir_throw_exception_debug(&_7$$5, "tensor/matrix.zep", 147);
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
					zephir_throw_exception_debug(&_12$$7, "tensor/matrix.zep", 147);
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
			ZEPHIR_INIT_NVAR(&rowA$$8);
			array_init(&rowA$$8);
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
						zephir_array_fetch_long(&_21$$9, &elements, i, PH_NOISY, "tensor/matrix.zep", 159);
					} else {
						ZEPHIR_INIT_NVAR(&_21$$9);
						ZVAL_LONG(&_21$$9, 0);
					}
					zephir_array_append(&rowA$$8, &_21$$9, PH_SEPARATE, "tensor/matrix.zep", 159);
				}
			}
			zephir_array_append(&a, &rowA$$8, PH_SEPARATE, "tensor/matrix.zep", 162);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Fill a matrix with a given value at each element.
 *
 * @param mixed value
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 182);
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
		zephir_throw_exception_debug(&_6$$4, "tensor/matrix.zep", 187);
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
	zval a, rowA$$4;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zval *m_param = NULL, *n_param = NULL, _1$$3, _3$$5, _4$$5, _5$$5, _7$$5, _8$$5;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA$$4);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 205);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA$$4);
		array_init(&rowA$$4);
		while (1) {
			if (!(zephir_fast_count_int(&rowA$$4) < n)) {
				break;
			}
			ZEPHIR_INIT_NVAR(&_3$$5);
			ZEPHIR_GET_CONSTANT(&_3$$5, "PHP_INT_MAX");
			ZVAL_LONG(&_4$$5, 0);
			ZEPHIR_CALL_FUNCTION(&_5$$5, "rand", &_6, 6, &_4$$5, &_3$$5);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_7$$5);
			ZEPHIR_GET_CONSTANT(&_7$$5, "PHP_INT_MAX");
			ZEPHIR_INIT_NVAR(&_8$$5);
			div_function(&_8$$5, &_5$$5, &_7$$5);
			zephir_array_append(&rowA$$4, &_8$$5, PH_SEPARATE, "tensor/matrix.zep", 215);
		}
		zephir_array_append(&a, &rowA$$4, PH_SEPARATE, "tensor/matrix.zep", 218);
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

	double r1$$6, r2$$6, r$$6, phi$$6;
	zval _2$$3;
	zval a, extras, rowA$$4;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL, *_13 = NULL;
	zval *m_param = NULL, *n_param = NULL, _1$$3, _3$$5, _5$$6, _6$$6, _7$$6, _9$$6, _10$$6, _11$$6, _12$$6, _14$$6, _15$$6, _16$$7;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&extras);
	ZVAL_UNDEF(&rowA$$4);
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
	ZEPHIR_INIT_VAR(&extras);
	array_init(&extras);
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA$$4);
		array_init(&rowA$$4);
		if (!(ZEPHIR_IS_EMPTY(&extras))) {
			ZEPHIR_MAKE_REF(&extras);
			ZEPHIR_CALL_FUNCTION(&_3$$5, "array_pop", &_4, 29, &extras);
			ZEPHIR_UNREF(&extras);
			zephir_check_call_status();
			zephir_array_append(&rowA$$4, &_3$$5, PH_SEPARATE, "tensor/matrix.zep", 248);
		}
		while (1) {
			if (!(zephir_fast_count_int(&rowA$$4) < n)) {
				break;
			}
			ZEPHIR_INIT_NVAR(&_5$$6);
			ZEPHIR_GET_CONSTANT(&_5$$6, "PHP_INT_MAX");
			ZVAL_LONG(&_6$$6, 0);
			ZEPHIR_CALL_FUNCTION(&_7$$6, "rand", &_8, 6, &_6$$6, &_5$$6);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_9$$6);
			ZEPHIR_GET_CONSTANT(&_9$$6, "PHP_INT_MAX");
			ZEPHIR_INIT_NVAR(&_10$$6);
			div_function(&_10$$6, &_7$$6, &_9$$6);
			r1$$6 = zephir_get_numberval(&_10$$6);
			ZEPHIR_INIT_NVAR(&_9$$6);
			ZEPHIR_GET_CONSTANT(&_9$$6, "PHP_INT_MAX");
			ZVAL_LONG(&_6$$6, 0);
			ZEPHIR_CALL_FUNCTION(&_7$$6, "rand", &_8, 6, &_6$$6, &_9$$6);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_11$$6);
			ZEPHIR_GET_CONSTANT(&_11$$6, "PHP_INT_MAX");
			ZEPHIR_INIT_NVAR(&_12$$6);
			div_function(&_12$$6, &_7$$6, &_11$$6);
			r2$$6 = zephir_get_numberval(&_12$$6);
			ZVAL_DOUBLE(&_6$$6, r1$$6);
			ZEPHIR_CALL_FUNCTION(&_7$$6, "log", &_13, 7, &_6$$6);
			zephir_check_call_status();
			ZVAL_DOUBLE(&_6$$6, (-2.0 * zephir_get_numberval(&_7$$6)));
			r$$6 = sqrt((-2.0 * zephir_get_numberval(&_7$$6)));
			phi$$6 = (r2$$6 * 6.28318530718);
			ZVAL_DOUBLE(&_14$$6, phi$$6);
			ZEPHIR_INIT_NVAR(&_11$$6);
			ZVAL_DOUBLE(&_11$$6, (r$$6 * sin(phi$$6)));
			zephir_array_append(&rowA$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 259);
			ZVAL_DOUBLE(&_15$$6, phi$$6);
			ZEPHIR_INIT_NVAR(&_11$$6);
			ZVAL_DOUBLE(&_11$$6, (r$$6 * cos(phi$$6)));
			zephir_array_append(&rowA$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 260);
		}
		if (zephir_fast_count_int(&rowA$$4) > n) {
			ZEPHIR_MAKE_REF(&rowA$$4);
			ZEPHIR_CALL_FUNCTION(&_16$$7, "array_pop", &_4, 29, &rowA$$4);
			ZEPHIR_UNREF(&rowA$$4);
			zephir_check_call_status();
			zephir_array_append(&extras, &_16$$7, PH_SEPARATE, "tensor/matrix.zep", 264);
		}
		zephir_array_append(&a, &rowA$$4, PH_SEPARATE, "tensor/matrix.zep", 267);
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

	zval a, rowA$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	double lambda, p = 0, l;
	zval *m_param = NULL, *n_param = NULL, *lambda_param = NULL, _0, _1, _2$$5, _3$$5, _4$$5, _6$$5, _7$$5, _8$$4;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, k = 0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &m_param, &n_param, &lambda_param);

	m = zephir_get_intval(m_param);
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
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA$$3);
		array_init(&rowA$$3);
		while (1) {
			if (!(zephir_fast_count_int(&rowA$$3) < n)) {
				break;
			}
			k = 0;
			p = 1.0;
			while (1) {
				if (!(p > l)) {
					break;
				}
				k++;
				ZEPHIR_INIT_NVAR(&_2$$5);
				ZEPHIR_GET_CONSTANT(&_2$$5, "PHP_INT_MAX");
				ZVAL_LONG(&_3$$5, 0);
				ZEPHIR_CALL_FUNCTION(&_4$$5, "rand", &_5, 6, &_3$$5, &_2$$5);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_6$$5);
				ZEPHIR_GET_CONSTANT(&_6$$5, "PHP_INT_MAX");
				ZEPHIR_INIT_NVAR(&_7$$5);
				div_function(&_7$$5, &_4$$5, &_6$$5);
				p *= zephir_get_numberval(&_7$$5);
			}
			ZEPHIR_INIT_NVAR(&_8$$4);
			ZVAL_LONG(&_8$$4, (k - 1));
			zephir_array_append(&rowA$$3, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 305);
		}
		zephir_array_append(&a, &rowA$$3, PH_SEPARATE, "tensor/matrix.zep", 308);
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
	zval a, rowA$$4;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zval *m_param = NULL, *n_param = NULL, _1$$3, _3$$5, _4$$5, _5$$5, _7$$5, _8$$5;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_3$$5);
	ZVAL_UNDEF(&_4$$5);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA$$4);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 326);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA$$4);
		array_init(&rowA$$4);
		while (1) {
			if (!(zephir_fast_count_int(&rowA$$4) < n)) {
				break;
			}
			ZEPHIR_INIT_NVAR(&_3$$5);
			ZEPHIR_GET_CONSTANT(&_3$$5, "PHP_INT_MAX");
			zephir_negate(&_3$$5);
			ZEPHIR_INIT_NVAR(&_4$$5);
			ZEPHIR_GET_CONSTANT(&_4$$5, "PHP_INT_MAX");
			ZEPHIR_CALL_FUNCTION(&_5$$5, "rand", &_6, 6, &_3$$5, &_4$$5);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_7$$5);
			ZEPHIR_GET_CONSTANT(&_7$$5, "PHP_INT_MAX");
			ZEPHIR_INIT_NVAR(&_8$$5);
			div_function(&_8$$5, &_5$$5, &_7$$5);
			zephir_array_append(&rowA$$4, &_8$$5, PH_SEPARATE, "tensor/matrix.zep", 336);
		}
		zephir_array_append(&a, &rowA$$4, PH_SEPARATE, "tensor/matrix.zep", 339);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 357);
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
		zephir_array_fetch(&_7$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 365);
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "min");
		ZEPHIR_CALL_FUNCTION(&_9$$4, "array_map", &_10, 12, &_8$$4, &rowA, &_7$$4);
		zephir_check_call_status();
		zephir_array_append(&c, &_9$$4, PH_SEPARATE, "tensor/matrix.zep", 365);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 383);
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
		zephir_array_fetch(&_7$$4, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 391);
		ZEPHIR_INIT_NVAR(&_8$$4);
		ZVAL_STRING(&_8$$4, "max");
		ZEPHIR_CALL_FUNCTION(&_9$$4, "array_map", &_10, 12, &_8$$4, &rowA, &_7$$4);
		zephir_check_call_status();
		zephir_array_append(&c, &_9$$4, PH_SEPARATE, "tensor/matrix.zep", 391);
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
	zephir_is_iterable(&vectors, 0, "tensor/matrix.zep", 439);
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
				zephir_throw_exception_debug(&_2$$5, "tensor/matrix.zep", 423);
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
				zephir_throw_exception_debug(&_7$$6, "tensor/matrix.zep", 428);
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
				zephir_throw_exception_debug(&_11$$7, "tensor/matrix.zep", 433);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_13$$4, &vector, "asarray", NULL, 0);
			zephir_check_call_status();
			zephir_array_append(&a, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 436);
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
					zephir_throw_exception_debug(&_14$$9, "tensor/matrix.zep", 423);
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
					zephir_throw_exception_debug(&_18$$10, "tensor/matrix.zep", 428);
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
					zephir_throw_exception_debug(&_22$$11, "tensor/matrix.zep", 433);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_24$$8, &vector, "asarray", NULL, 0);
				zephir_check_call_status();
				zephir_array_append(&a, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 436);
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
 * @param array a
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
		zephir_is_iterable(&a, 0, "tensor/matrix.zep", 476);
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
					zephir_throw_exception_debug(&_7$$5, "tensor/matrix.zep", 465);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_is_iterable(&row, 0, "tensor/matrix.zep", 475);
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
							zephir_throw_exception_debug(&_19$$7, "tensor/matrix.zep", 472);
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
								zephir_throw_exception_debug(&_24$$9, "tensor/matrix.zep", 472);
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
						zephir_throw_exception_debug(&_27$$11, "tensor/matrix.zep", 465);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_is_iterable(&row, 0, "tensor/matrix.zep", 475);
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
								zephir_throw_exception_debug(&_36$$13, "tensor/matrix.zep", 472);
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
									zephir_throw_exception_debug(&_41$$15, "tensor/matrix.zep", 472);
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
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "offsetget", NULL, 0, &_2);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 597);
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
			zephir_array_append(&vectors, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 643);
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
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 674);
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
			zephir_array_append(&b, &_7$$3, PH_SEPARATE, "tensor/matrix.zep", 671);
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
				zephir_array_append(&b, &_10$$4, PH_SEPARATE, "tensor/matrix.zep", 671);
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
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 692);
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
			zephir_array_append(&b, &_7$$3, PH_SEPARATE, "tensor/matrix.zep", 689);
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
				zephir_array_append(&b, &_10$$4, PH_SEPARATE, "tensor/matrix.zep", 689);
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
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 711);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_CALL_FUNCTION(&_3$$3, "array_map", &_4, 12, callback, &rowA);
			zephir_check_call_status();
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/matrix.zep", 708);
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
				zephir_array_append(&b, &_5$$4, PH_SEPARATE, "tensor/matrix.zep", 708);
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
 * @param mixed initial
 * @throws \InvalidArgumentException
 * @return mixed
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 727);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&carry, initial);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 740);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 738);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 738);
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
			zephir_array_append(&b, &_6$$3, PH_SEPARATE, "tensor/matrix.zep", 755);
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
	zval c;
	zval rowB, b, _0, _1, _2, _4$$3, _5$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_SELF(&_0, "identity", NULL, 0, &_1);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &_0, "augmentleft", NULL, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&b, &_2, "rref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	_3 = zephir_get_iterator(&b);
	_3->funcs->rewind(_3);
	for (;_3->funcs->valid(_3) == SUCCESS && !EG(exception); _3->funcs->move_forward(_3)) {
		{
			ZEPHIR_ITERATOR_COPY(&rowB, _3);
		}
		zephir_read_property(&_4$$3, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
		ZEPHIR_CALL_FUNCTION(&_5$$3, "array_slice", &_6, 8, &rowB, &_4$$3);
		zephir_check_call_status();
		zephir_array_append(&c, &_5$$3, PH_SEPARATE, "tensor/matrix.zep", 777);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 793);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&ref, this_ptr, "ref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&b);
	zephir_array_fetch_long(&b, &ref, 0, PH_NOISY, "tensor/matrix.zep", 798);
	ZEPHIR_OBS_VAR(&swaps);
	zephir_array_fetch_long(&swaps, &ref, 1, PH_NOISY, "tensor/matrix.zep", 799);
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
		zephir_is_iterable(&row, 0, "tensor/matrix.zep", 828);
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
			zephir_array_fetch_long(&rowA, &_5$$4, i, PH_NOISY, "tensor/matrix.zep", 858);
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
					zephir_array_fetch_long(&_10$$5, &rowA, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 861);
					zephir_read_property(&_11$$5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch_long(&_12$$5, &_11$$5, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 861);
					zephir_array_fetch_long(&_13$$5, &_12$$5, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 861);
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

	zend_string *_17$$5, *_26$$8, *_37$$12, *_46$$15;
	zend_ulong _16$$5, _25$$8, _36$$12, _45$$15;
	zval _4$$3, _6$$3, _7$$3;
	zval c, rowC$$4, rowC$$11;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, k, rowA, valueA, columnB, p, bT, _8, _9, *_10, _11, _2$$3, _3$$3, _5$$3, *_12$$4, _13$$4, *_14$$5, _15$$5, _22$$5, _18$$6, _19$$6, _20$$7, _21$$7, *_23$$8, _24$$8, _31$$8, _27$$9, _28$$9, _29$$10, _30$$10, *_32$$11, _33$$11, *_34$$12, _35$$12, _42$$12, _38$$13, _39$$13, _40$$14, _41$$14, *_43$$15, _44$$15, _51$$15, _47$$16, _48$$16, _49$$17, _50$$17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&columnB);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&bT);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_31$$8);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$10);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_33$$11);
	ZVAL_UNDEF(&_35$$12);
	ZVAL_UNDEF(&_42$$12);
	ZVAL_UNDEF(&_38$$13);
	ZVAL_UNDEF(&_39$$13);
	ZVAL_UNDEF(&_40$$14);
	ZVAL_UNDEF(&_41$$14);
	ZVAL_UNDEF(&_44$$15);
	ZVAL_UNDEF(&_51$$15);
	ZVAL_UNDEF(&_47$$16);
	ZVAL_UNDEF(&_48$$16);
	ZVAL_UNDEF(&_49$$17);
	ZVAL_UNDEF(&_50$$17);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$11);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 932);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&p, b, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, b, "transpose", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&bT, &_8, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_9, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_9, 0, "tensor/matrix.zep", 960);
	if (Z_TYPE_P(&_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_9), _10)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _10);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bT, 0, "tensor/matrix.zep", 957);
			if (Z_TYPE_P(&bT) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&bT), _12$$4)
				{
					ZEPHIR_INIT_NVAR(&columnB);
					ZVAL_COPY(&columnB, _12$$4);
					sigma = 0.0;
					zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 954);
					if (Z_TYPE_P(&rowA) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _16$$5, _17$$5, _14$$5)
						{
							ZEPHIR_INIT_NVAR(&k);
							if (_17$$5 != NULL) { 
								ZVAL_STR_COPY(&k, _17$$5);
							} else {
								ZVAL_LONG(&k, _16$$5);
							}
							ZEPHIR_INIT_NVAR(&valueA);
							ZVAL_COPY(&valueA, _14$$5);
							zephir_array_fetch(&_18$$6, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
							ZEPHIR_INIT_NVAR(&_19$$6);
							mul_function(&_19$$6, &valueA, &_18$$6);
							sigma += zephir_get_numberval(&_19$$6);
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
						zephir_check_call_status();
						while (1) {
							ZEPHIR_CALL_METHOD(&_15$$5, &rowA, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_15$$5)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
							zephir_check_call_status();
								zephir_array_fetch(&_20$$7, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
								ZEPHIR_INIT_NVAR(&_21$$7);
								mul_function(&_21$$7, &valueA, &_20$$7);
								sigma += zephir_get_numberval(&_21$$7);
							ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
							zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZEPHIR_INIT_NVAR(&k);
					ZEPHIR_INIT_NVAR(&_22$$5);
					ZVAL_DOUBLE(&_22$$5, sigma);
					zephir_array_append(&rowC$$4, &_22$$5, PH_SEPARATE, "tensor/matrix.zep", 954);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &bT, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_13$$4, &bT, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_13$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&columnB, &bT, "current", NULL, 0);
					zephir_check_call_status();
						sigma = 0.0;
						zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 954);
						if (Z_TYPE_P(&rowA) == IS_ARRAY) {
							ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _25$$8, _26$$8, _23$$8)
							{
								ZEPHIR_INIT_NVAR(&k);
								if (_26$$8 != NULL) { 
									ZVAL_STR_COPY(&k, _26$$8);
								} else {
									ZVAL_LONG(&k, _25$$8);
								}
								ZEPHIR_INIT_NVAR(&valueA);
								ZVAL_COPY(&valueA, _23$$8);
								zephir_array_fetch(&_27$$9, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
								ZEPHIR_INIT_NVAR(&_28$$9);
								mul_function(&_28$$9, &valueA, &_27$$9);
								sigma += zephir_get_numberval(&_28$$9);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
							zephir_check_call_status();
							while (1) {
								ZEPHIR_CALL_METHOD(&_24$$8, &rowA, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_24$$8)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
								zephir_check_call_status();
									zephir_array_fetch(&_29$$10, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
									ZEPHIR_INIT_NVAR(&_30$$10);
									mul_function(&_30$$10, &valueA, &_29$$10);
									sigma += zephir_get_numberval(&_30$$10);
								ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
								zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZEPHIR_INIT_NVAR(&k);
						ZEPHIR_INIT_NVAR(&_31$$8);
						ZVAL_DOUBLE(&_31$$8, sigma);
						zephir_array_append(&rowC$$4, &_31$$8, PH_SEPARATE, "tensor/matrix.zep", 954);
					ZEPHIR_CALL_METHOD(NULL, &bT, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&columnB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 957);
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
				ZEPHIR_INIT_NVAR(&rowC$$11);
				array_init(&rowC$$11);
				zephir_is_iterable(&bT, 0, "tensor/matrix.zep", 957);
				if (Z_TYPE_P(&bT) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&bT), _32$$11)
					{
						ZEPHIR_INIT_NVAR(&columnB);
						ZVAL_COPY(&columnB, _32$$11);
						sigma = 0.0;
						zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 954);
						if (Z_TYPE_P(&rowA) == IS_ARRAY) {
							ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _36$$12, _37$$12, _34$$12)
							{
								ZEPHIR_INIT_NVAR(&k);
								if (_37$$12 != NULL) { 
									ZVAL_STR_COPY(&k, _37$$12);
								} else {
									ZVAL_LONG(&k, _36$$12);
								}
								ZEPHIR_INIT_NVAR(&valueA);
								ZVAL_COPY(&valueA, _34$$12);
								zephir_array_fetch(&_38$$13, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
								ZEPHIR_INIT_NVAR(&_39$$13);
								mul_function(&_39$$13, &valueA, &_38$$13);
								sigma += zephir_get_numberval(&_39$$13);
							} ZEND_HASH_FOREACH_END();
						} else {
							ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
							zephir_check_call_status();
							while (1) {
								ZEPHIR_CALL_METHOD(&_35$$12, &rowA, "valid", NULL, 0);
								zephir_check_call_status();
								if (!zend_is_true(&_35$$12)) {
									break;
								}
								ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
								zephir_check_call_status();
								ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
								zephir_check_call_status();
									zephir_array_fetch(&_40$$14, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
									ZEPHIR_INIT_NVAR(&_41$$14);
									mul_function(&_41$$14, &valueA, &_40$$14);
									sigma += zephir_get_numberval(&_41$$14);
								ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
								zephir_check_call_status();
							}
						}
						ZEPHIR_INIT_NVAR(&valueA);
						ZEPHIR_INIT_NVAR(&k);
						ZEPHIR_INIT_NVAR(&_42$$12);
						ZVAL_DOUBLE(&_42$$12, sigma);
						zephir_array_append(&rowC$$11, &_42$$12, PH_SEPARATE, "tensor/matrix.zep", 954);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &bT, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_33$$11, &bT, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_33$$11)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&columnB, &bT, "current", NULL, 0);
						zephir_check_call_status();
							sigma = 0.0;
							zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 954);
							if (Z_TYPE_P(&rowA) == IS_ARRAY) {
								ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowA), _45$$15, _46$$15, _43$$15)
								{
									ZEPHIR_INIT_NVAR(&k);
									if (_46$$15 != NULL) { 
										ZVAL_STR_COPY(&k, _46$$15);
									} else {
										ZVAL_LONG(&k, _45$$15);
									}
									ZEPHIR_INIT_NVAR(&valueA);
									ZVAL_COPY(&valueA, _43$$15);
									zephir_array_fetch(&_47$$16, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
									ZEPHIR_INIT_NVAR(&_48$$16);
									mul_function(&_48$$16, &valueA, &_47$$16);
									sigma += zephir_get_numberval(&_48$$16);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
								zephir_check_call_status();
								while (1) {
									ZEPHIR_CALL_METHOD(&_44$$15, &rowA, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_44$$15)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&k, &rowA, "key", NULL, 0);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
									zephir_check_call_status();
										zephir_array_fetch(&_49$$17, &columnB, &k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 951);
										ZEPHIR_INIT_NVAR(&_50$$17);
										mul_function(&_50$$17, &valueA, &_49$$17);
										sigma += zephir_get_numberval(&_50$$17);
									ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
									zephir_check_call_status();
								}
							}
							ZEPHIR_INIT_NVAR(&valueA);
							ZEPHIR_INIT_NVAR(&k);
							ZEPHIR_INIT_NVAR(&_51$$15);
							ZVAL_DOUBLE(&_51$$15, sigma);
							zephir_array_append(&rowC$$11, &_51$$15, PH_SEPARATE, "tensor/matrix.zep", 954);
						ZEPHIR_CALL_METHOD(NULL, &bT, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&columnB);
				zephir_array_append(&c, &rowC$$11, PH_SEPARATE, "tensor/matrix.zep", 957);
			ZEPHIR_CALL_METHOD(NULL, &_9, "next", NULL, 0);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 975);
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

	zend_string *_20$$6, *_27$$7, *_42$$13;
	zend_ulong _19$$6, _26$$7, _41$$13;
	zval _4$$3;
	zval c, rowC$$5;
	zend_bool _1, _10, _14$$5, _21$$7, _28$$9, _32$$11, _36$$13, _43$$15, _47$$17;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long stride, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, x = 0, y = 0, _11, _12, _15$$5, _16$$5;
	zval *b, b_sub, *stride_param = NULL, m, n, _0, _2, k, l, rowA, rowB, valueB, bHat, p, _9, q, _3$$3, _5$$4, _6$$4, _7$$4, _8$$4, _13$$5, sigma$$6, *_17$$6, _18$$6, _22$$7, _23$$7, *_24$$7, _25$$7, _29$$9, _30$$9, _31$$9, _33$$11, _34$$11, _35$$11, _37$$13, _38$$13, *_39$$13, _40$$13, _44$$15, _45$$15, _46$$15, _48$$17, _49$$17, _50$$17;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&k);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&q);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&sigma$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&_33$$11);
	ZVAL_UNDEF(&_34$$11);
	ZVAL_UNDEF(&_35$$11);
	ZVAL_UNDEF(&_37$$13);
	ZVAL_UNDEF(&_38$$13);
	ZVAL_UNDEF(&_40$$13);
	ZVAL_UNDEF(&_44$$15);
	ZVAL_UNDEF(&_45$$15);
	ZVAL_UNDEF(&_46$$15);
	ZVAL_UNDEF(&_48$$17);
	ZVAL_UNDEF(&_49$$17);
	ZVAL_UNDEF(&_50$$17);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC$$5);
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
		zephir_throw_exception_debug(&_3$$3, "tensor/matrix.zep", 996);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 1001);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZVAL_LONG(&_9, 2);
	ZEPHIR_CALL_FUNCTION(&p, "intdiv", NULL, 21, &m, &_9);
	zephir_check_call_status();
	ZVAL_LONG(&_9, 2);
	ZEPHIR_CALL_FUNCTION(&q, "intdiv", NULL, 21, &n, &_9);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_9, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_12 = (zephir_get_numberval(&_9) - 1);
	_11 = 0;
	_10 = 0;
	if (_11 <= _12) {
		while (1) {
			if (_10) {
				_11 += stride;
				if (!(_11 <= _12)) {
					break;
				}
			} else {
				_10 = 1;
			}
			i = _11;
			ZEPHIR_INIT_NVAR(&rowC$$5);
			array_init(&rowC$$5);
			zephir_read_property(&_13$$5, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
			_16$$5 = (zephir_get_numberval(&_13$$5) - 1);
			_15$$5 = 0;
			_14$$5 = 0;
			if (_15$$5 <= _16$$5) {
				while (1) {
					if (_14$$5) {
						_15$$5 += stride;
						if (!(_15$$5 <= _16$$5)) {
							break;
						}
					} else {
						_14$$5 = 1;
					}
					j = _15$$5;
					ZEPHIR_INIT_NVAR(&sigma$$6);
					ZVAL_LONG(&sigma$$6, 0);
					zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 1040);
					if (Z_TYPE_P(&bHat) == IS_ARRAY) {
						ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&bHat), _19$$6, _20$$6, _17$$6)
						{
							ZEPHIR_INIT_NVAR(&k);
							if (_20$$6 != NULL) { 
								ZVAL_STR_COPY(&k, _20$$6);
							} else {
								ZVAL_LONG(&k, _19$$6);
							}
							ZEPHIR_INIT_NVAR(&rowB);
							ZVAL_COPY(&rowB, _17$$6);
							x = ((i + zephir_get_numberval(&p)) - zephir_get_intval(&k));
							_21$$7 = x < 0;
							if (!(_21$$7)) {
								zephir_read_property(&_22$$7, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
								_21$$7 = ZEPHIR_LE_LONG(&_22$$7, x);
							}
							if (_21$$7) {
								continue;
							}
							zephir_read_property(&_23$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
							ZEPHIR_OBS_NVAR(&rowA);
							zephir_array_fetch_long(&rowA, &_23$$7, x, PH_NOISY, "tensor/matrix.zep", 1027);
							zephir_is_iterable(&rowB, 0, "tensor/matrix.zep", 1038);
							if (Z_TYPE_P(&rowB) == IS_ARRAY) {
								ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowB), _26$$7, _27$$7, _24$$7)
								{
									ZEPHIR_INIT_NVAR(&l);
									if (_27$$7 != NULL) { 
										ZVAL_STR_COPY(&l, _27$$7);
									} else {
										ZVAL_LONG(&l, _26$$7);
									}
									ZEPHIR_INIT_NVAR(&valueB);
									ZVAL_COPY(&valueB, _24$$7);
									y = ((j + zephir_get_numberval(&q)) - zephir_get_intval(&l));
									_28$$9 = y < 0;
									if (!(_28$$9)) {
										zephir_read_property(&_29$$9, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
										_28$$9 = ZEPHIR_LE_LONG(&_29$$9, y);
									}
									if (_28$$9) {
										continue;
									}
									zephir_array_fetch_long(&_30$$9, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1036);
									ZEPHIR_INIT_NVAR(&_31$$9);
									mul_function(&_31$$9, &_30$$9, &valueB);
									ZEPHIR_ADD_ASSIGN(&sigma$$6, &_31$$9);
								} ZEND_HASH_FOREACH_END();
							} else {
								ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
								zephir_check_call_status();
								while (1) {
									ZEPHIR_CALL_METHOD(&_25$$7, &rowB, "valid", NULL, 0);
									zephir_check_call_status();
									if (!zend_is_true(&_25$$7)) {
										break;
									}
									ZEPHIR_CALL_METHOD(&l, &rowB, "key", NULL, 0);
									zephir_check_call_status();
									ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
									zephir_check_call_status();
										y = ((j + zephir_get_numberval(&q)) - zephir_get_intval(&l));
										_32$$11 = y < 0;
										if (!(_32$$11)) {
											zephir_read_property(&_33$$11, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
											_32$$11 = ZEPHIR_LE_LONG(&_33$$11, y);
										}
										if (_32$$11) {
											continue;
										}
										zephir_array_fetch_long(&_34$$11, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1036);
										ZEPHIR_INIT_NVAR(&_35$$11);
										mul_function(&_35$$11, &_34$$11, &valueB);
										ZEPHIR_ADD_ASSIGN(&sigma$$6, &_35$$11);
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
							ZEPHIR_CALL_METHOD(&_18$$6, &bHat, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_18$$6)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&k, &bHat, "key", NULL, 0);
							zephir_check_call_status();
							ZEPHIR_CALL_METHOD(&rowB, &bHat, "current", NULL, 0);
							zephir_check_call_status();
								x = ((i + zephir_get_numberval(&p)) - zephir_get_intval(&k));
								_36$$13 = x < 0;
								if (!(_36$$13)) {
									zephir_read_property(&_37$$13, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
									_36$$13 = ZEPHIR_LE_LONG(&_37$$13, x);
								}
								if (_36$$13) {
									continue;
								}
								zephir_read_property(&_38$$13, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
								ZEPHIR_OBS_NVAR(&rowA);
								zephir_array_fetch_long(&rowA, &_38$$13, x, PH_NOISY, "tensor/matrix.zep", 1027);
								zephir_is_iterable(&rowB, 0, "tensor/matrix.zep", 1038);
								if (Z_TYPE_P(&rowB) == IS_ARRAY) {
									ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowB), _41$$13, _42$$13, _39$$13)
									{
										ZEPHIR_INIT_NVAR(&l);
										if (_42$$13 != NULL) { 
											ZVAL_STR_COPY(&l, _42$$13);
										} else {
											ZVAL_LONG(&l, _41$$13);
										}
										ZEPHIR_INIT_NVAR(&valueB);
										ZVAL_COPY(&valueB, _39$$13);
										y = ((j + zephir_get_numberval(&q)) - zephir_get_intval(&l));
										_43$$15 = y < 0;
										if (!(_43$$15)) {
											zephir_read_property(&_44$$15, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
											_43$$15 = ZEPHIR_LE_LONG(&_44$$15, y);
										}
										if (_43$$15) {
											continue;
										}
										zephir_array_fetch_long(&_45$$15, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1036);
										ZEPHIR_INIT_NVAR(&_46$$15);
										mul_function(&_46$$15, &_45$$15, &valueB);
										ZEPHIR_ADD_ASSIGN(&sigma$$6, &_46$$15);
									} ZEND_HASH_FOREACH_END();
								} else {
									ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
									zephir_check_call_status();
									while (1) {
										ZEPHIR_CALL_METHOD(&_40$$13, &rowB, "valid", NULL, 0);
										zephir_check_call_status();
										if (!zend_is_true(&_40$$13)) {
											break;
										}
										ZEPHIR_CALL_METHOD(&l, &rowB, "key", NULL, 0);
										zephir_check_call_status();
										ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
										zephir_check_call_status();
											y = ((j + zephir_get_numberval(&q)) - zephir_get_intval(&l));
											_47$$17 = y < 0;
											if (!(_47$$17)) {
												zephir_read_property(&_48$$17, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
												_47$$17 = ZEPHIR_LE_LONG(&_48$$17, y);
											}
											if (_47$$17) {
												continue;
											}
											zephir_array_fetch_long(&_49$$17, &rowA, y, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1036);
											ZEPHIR_INIT_NVAR(&_50$$17);
											mul_function(&_50$$17, &_49$$17, &valueB);
											ZEPHIR_ADD_ASSIGN(&sigma$$6, &_50$$17);
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
					zephir_array_append(&rowC$$5, &sigma$$6, PH_SEPARATE, "tensor/matrix.zep", 1040);
				}
			}
			zephir_array_append(&c, &rowC$$5, PH_SEPARATE, "tensor/matrix.zep", 1043);
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

	zval ref, a, swaps;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&swaps);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&ref, tensor_decompositions_ref_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&a, &ref, "a", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&swaps, &ref, "swaps", NULL, 0);
	zephir_check_call_status();
	zephir_create_array(return_value, 2, 0);
	zephir_array_fast_append(return_value, &a);
	zephir_array_fast_append(return_value, &swaps);
	RETURN_MM();

}

/**
 * Return the reduced row echelon (RREF) form of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, rref) {

	zval a, _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_1 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&_0, tensor_decompositions_rref_ce, "decompose", &_1, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&a, &_0, "a", NULL, 0);
	zephir_check_call_status();
	RETURN_CCTOR(&a);

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

	zval lup, l, u, p;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&lup);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&p);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_CE_STATIC(&lup, tensor_decompositions_lu_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&l, &lup, "l", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&u, &lup, "u", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&p, &lup, "p", NULL, 0);
	zephir_check_call_status();
	zephir_create_array(return_value, 3, 0);
	zephir_array_fast_append(return_value, &l);
	zephir_array_fast_append(return_value, &u);
	zephir_array_fast_append(return_value, &p);
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


	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Not implemented yet.", "tensor/matrix.zep", 1116);
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

	zend_bool _8, _26, _11$$5, _30$$9;
	zval y, x;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_41 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, _9, _10, _27, _28, _12$$5, _13$$5, _31$$9, _32$$9;
	zval *b, b_sub, _0, lup, l, u, p, pb, _1, _2, _3, _4, _6, _7, _22, _23, _25, _42, _5$$4, sigma$$5, _18$$5, _19$$5, _20$$5, _21$$5, _14$$6, _15$$6, _16$$6, _17$$6, _24$$8, sigma$$9, _29$$9, _37$$9, _38$$9, _39$$9, _40$$9, _33$$10, _34$$10, _35$$10, _36$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&lup);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&pb);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_42);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&sigma$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&sigma$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_37$$9);
	ZVAL_UNDEF(&_38$$9);
	ZVAL_UNDEF(&_39$$9);
	ZVAL_UNDEF(&_40$$9);
	ZVAL_UNDEF(&_33$$10);
	ZVAL_UNDEF(&_34$$10);
	ZVAL_UNDEF(&_35$$10);
	ZVAL_UNDEF(&_36$$10);
	ZVAL_UNDEF(&y);
	ZVAL_UNDEF(&x);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	zephir_read_property(&_0, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	k = (zephir_get_numberval(&_0) - 1);
	ZEPHIR_CALL_METHOD(&lup, this_ptr, "lu", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&l);
	zephir_array_fetch_long(&l, &lup, 0, PH_NOISY, "tensor/matrix.zep", 1134);
	ZEPHIR_OBS_VAR(&u);
	zephir_array_fetch_long(&u, &lup, 1, PH_NOISY, "tensor/matrix.zep", 1135);
	ZEPHIR_OBS_VAR(&p);
	zephir_array_fetch_long(&p, &lup, 2, PH_NOISY, "tensor/matrix.zep", 1136);
	ZEPHIR_CALL_METHOD(&pb, &p, "dot", NULL, 0, b);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&y);
	zephir_create_array(&y, 1, 0);
	zephir_array_fetch_long(&_1, &pb, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1140);
	ZEPHIR_INIT_VAR(&_2);
	zephir_array_fetch_long(&_3, &l, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1140);
	zephir_array_fetch_long(&_4, &_3, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1140);
	if (!(zephir_is_true(&_4))) {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_DOUBLE(&_2, 0.00000001);
	} else {
		zephir_array_fetch_long(&_5$$4, &l, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1140);
		ZEPHIR_OBS_NVAR(&_2);
		zephir_array_fetch_long(&_2, &_5$$4, 0, PH_NOISY, "tensor/matrix.zep", 1140);
	}
	ZEPHIR_INIT_VAR(&_6);
	div_function(&_6, &_1, &_2);
	zephir_array_update_long(&y, 0, &_6, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_read_property(&_7, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_10 = (zephir_get_numberval(&_7) - 1);
	_9 = 1;
	_8 = 0;
	if (_9 <= _10) {
		while (1) {
			if (_8) {
				_9++;
				if (!(_9 <= _10)) {
					break;
				}
			} else {
				_8 = 1;
			}
			i = _9;
			ZEPHIR_INIT_NVAR(&sigma$$5);
			ZVAL_DOUBLE(&sigma$$5, 0.0);
			_13$$5 = (i - 1);
			_12$$5 = 0;
			_11$$5 = 0;
			if (_12$$5 <= _13$$5) {
				while (1) {
					if (_11$$5) {
						_12$$5++;
						if (!(_12$$5 <= _13$$5)) {
							break;
						}
					} else {
						_11$$5 = 1;
					}
					j = _12$$5;
					zephir_array_fetch_long(&_14$$6, &l, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1146);
					zephir_array_fetch_long(&_15$$6, &_14$$6, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1146);
					zephir_array_fetch_long(&_16$$6, &y, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1146);
					ZEPHIR_INIT_NVAR(&_17$$6);
					mul_function(&_17$$6, &_15$$6, &_16$$6);
					ZEPHIR_ADD_ASSIGN(&sigma$$5, &_17$$6);
				}
			}
			zephir_array_fetch_long(&_18$$5, &pb, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1149);
			ZEPHIR_INIT_NVAR(&_19$$5);
			zephir_sub_function(&_19$$5, &_18$$5, &sigma$$5);
			zephir_array_fetch_long(&_18$$5, &l, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1149);
			zephir_array_fetch_long(&_20$$5, &_18$$5, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1149);
			ZEPHIR_INIT_NVAR(&_21$$5);
			div_function(&_21$$5, &_19$$5, &_20$$5);
			zephir_array_append(&y, &_21$$5, PH_SEPARATE, "tensor/matrix.zep", 1149);
		}
	}
	ZEPHIR_INIT_VAR(&x);
	zephir_create_array(&x, 1, 0);
	zephir_array_fetch_long(&_1, &y, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1152);
	ZEPHIR_INIT_NVAR(&_2);
	zephir_array_fetch_long(&_22, &l, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1152);
	zephir_array_fetch_long(&_23, &_22, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1152);
	if (!(zephir_is_true(&_23))) {
		ZEPHIR_INIT_NVAR(&_2);
		ZVAL_DOUBLE(&_2, 0.00000001);
	} else {
		zephir_array_fetch_long(&_24$$8, &l, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1152);
		ZEPHIR_OBS_NVAR(&_2);
		zephir_array_fetch_long(&_2, &_24$$8, k, PH_NOISY, "tensor/matrix.zep", 1152);
	}
	ZEPHIR_INIT_NVAR(&_6);
	div_function(&_6, &_1, &_2);
	zephir_array_update_long(&x, k, &_6, PH_COPY ZEPHIR_DEBUG_PARAMS_DUMMY);
	zephir_read_property(&_25, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
	_28 = (zephir_get_numberval(&_25) - 2);
	_27 = _28;
	_26 = 0;
	if (_27 >= 0) {
		while (1) {
			if (_26) {
				_27--;
				if (!(_27 >= 0)) {
					break;
				}
			} else {
				_26 = 1;
			}
			i = _27;
			ZEPHIR_INIT_NVAR(&sigma$$9);
			ZVAL_DOUBLE(&sigma$$9, 0.0);
			zephir_read_property(&_29$$9, this_ptr, SL("m"), PH_NOISY_CC | PH_READONLY);
			_32$$9 = (zephir_get_numberval(&_29$$9) - 1);
			_31$$9 = (i + 1);
			_30$$9 = 0;
			if (_31$$9 <= _32$$9) {
				while (1) {
					if (_30$$9) {
						_31$$9++;
						if (!(_31$$9 <= _32$$9)) {
							break;
						}
					} else {
						_30$$9 = 1;
					}
					j = _31$$9;
					zephir_array_fetch_long(&_33$$10, &u, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1158);
					zephir_array_fetch_long(&_34$$10, &_33$$10, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1158);
					zephir_array_fetch_long(&_35$$10, &x, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1158);
					ZEPHIR_INIT_NVAR(&_36$$10);
					mul_function(&_36$$10, &_34$$10, &_35$$10);
					ZEPHIR_ADD_ASSIGN(&sigma$$9, &_36$$10);
				}
			}
			zephir_array_fetch_long(&_37$$9, &y, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1161);
			ZEPHIR_INIT_NVAR(&_38$$9);
			zephir_sub_function(&_38$$9, &_37$$9, &sigma$$9);
			zephir_array_fetch_long(&_37$$9, &u, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1161);
			zephir_array_fetch_long(&_39$$9, &_37$$9, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1161);
			ZEPHIR_INIT_NVAR(&_40$$9);
			div_function(&_40$$9, &_38$$9, &_39$$9);
			zephir_array_update_long(&x, i, &_40$$9, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_42, "array_reverse", NULL, 33, &x);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_41, 0, &_42);
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
 * A universal function to multiply this matrix with another tensor
 * element-wise.
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1235);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1266);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1297);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1328);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to raise this matrix to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @throws \InvalidArgumentException
 * @return mixed
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1359);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1390);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1421);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1452);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1483);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1514);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1545);
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
	zephir_throw_exception_debug(&_3, "tensor/matrix.zep", 1576);
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

	zval b, rowB$$3, rowB$$6;
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
	ZVAL_UNDEF(&rowB$$3);
	ZVAL_UNDEF(&rowB$$6);

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
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 1662);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _1);
			ZEPHIR_INIT_NVAR(&rowB$$3);
			array_init(&rowB$$3);
			zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1659);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _3$$3);
					ZVAL_DOUBLE(&_5$$4, base);
					ZEPHIR_CALL_FUNCTION(&_6$$4, "log", &_7, 7, &value, &_5$$4);
					zephir_check_call_status();
					zephir_array_append(&rowB$$3, &_6$$4, PH_SEPARATE, "tensor/matrix.zep", 1656);
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
						zephir_array_append(&rowB$$3, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 1656);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			zephir_array_append(&b, &rowB$$3, PH_SEPARATE, "tensor/matrix.zep", 1659);
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
				ZEPHIR_INIT_NVAR(&rowB$$6);
				array_init(&rowB$$6);
				zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1659);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _10$$6)
					{
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _10$$6);
						ZVAL_DOUBLE(&_12$$7, base);
						ZEPHIR_CALL_FUNCTION(&_13$$7, "log", &_7, 7, &value, &_12$$7);
						zephir_check_call_status();
						zephir_array_append(&rowB$$6, &_13$$7, PH_SEPARATE, "tensor/matrix.zep", 1656);
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
							zephir_array_append(&rowB$$6, &_15$$8, PH_SEPARATE, "tensor/matrix.zep", 1656);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				zephir_array_append(&b, &rowB$$6, PH_SEPARATE, "tensor/matrix.zep", 1659);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1805);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1821);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_3, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_3, 0, "tensor/matrix.zep", 1842);
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
				zephir_array_fetch(&median, &rowA, &mid$$4, PH_NOISY, "tensor/matrix.zep", 1834);
			} else {
				zephir_array_fetch_long(&_10$$6, &rowA, (zephir_get_numberval(&mid$$4) - 1), PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1836);
				zephir_array_fetch(&_11$$6, &rowA, &mid$$4, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1836);
				ZEPHIR_INIT_NVAR(&_12$$6);
				zephir_add_function(&_12$$6, &_10$$6, &_11$$6);
				ZEPHIR_INIT_NVAR(&median);
				ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_12$$6, 2.0));
			}
			zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1839);
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
					zephir_array_fetch(&median, &rowA, &mid$$7, PH_NOISY, "tensor/matrix.zep", 1834);
				} else {
					zephir_array_fetch_long(&_15$$9, &rowA, (zephir_get_numberval(&mid$$7) - 1), PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1836);
					zephir_array_fetch(&_16$$9, &rowA, &mid$$7, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1836);
					ZEPHIR_INIT_NVAR(&_17$$9);
					zephir_add_function(&_17$$9, &_15$$9, &_16$$9);
					ZEPHIR_INIT_NVAR(&median);
					ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_17$$9, 2.0));
				}
				zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1839);
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
	zephir_fcall_cache_entry *_11 = NULL, *_20 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, xHat$$5, xHat$$6;
	zval *p_param = NULL, _5, rowA, _8, *_9, _10, _1$$3, _2$$3, _3$$3, _4$$3, _6$$4, _12$$5, t$$5, _13$$5, _14$$5, _15$$5, _16$$6, t$$6, _17$$6, _18$$6, _19$$6;
	double p, x$$5, remainder$$5, x$$6, remainder$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&t$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&t$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1857);
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
		zephir_throw_exception_debug(&_6$$4, "tensor/matrix.zep", 1862);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 1883);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_11, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			zephir_read_property(&_12$$5, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
			x$$5 = (((zephir_safe_div_double_long(p, 100)) * (double) (((zephir_get_numberval(&_12$$5) - 1)))) + (double) (1));
			xHat$$5 = (int) (x$$5);
			remainder$$5 = (x$$5 -  (double) xHat$$5);
			ZEPHIR_OBS_NVAR(&t$$5);
			zephir_array_fetch_long(&t$$5, &rowA, (xHat$$5 - 1), PH_NOISY, "tensor/matrix.zep", 1878);
			zephir_array_fetch_long(&_13$$5, &rowA, xHat$$5, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1880);
			ZEPHIR_INIT_NVAR(&_14$$5);
			zephir_sub_function(&_14$$5, &_13$$5, &t$$5);
			ZEPHIR_INIT_NVAR(&_15$$5);
			ZVAL_DOUBLE(&_15$$5, (zephir_get_doubleval(&t$$5) + (double) ((remainder$$5 * zephir_get_numberval(&_14$$5)))));
			zephir_array_append(&b, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 1880);
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
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_11, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				zephir_read_property(&_16$$6, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
				x$$6 = (((zephir_safe_div_double_long(p, 100)) * (double) (((zephir_get_numberval(&_16$$6) - 1)))) + (double) (1));
				xHat$$6 = (int) (x$$6);
				remainder$$6 = (x$$6 -  (double) xHat$$6);
				ZEPHIR_OBS_NVAR(&t$$6);
				zephir_array_fetch_long(&t$$6, &rowA, (xHat$$6 - 1), PH_NOISY, "tensor/matrix.zep", 1878);
				zephir_array_fetch_long(&_17$$6, &rowA, xHat$$6, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1880);
				ZEPHIR_INIT_NVAR(&_18$$6);
				zephir_sub_function(&_18$$6, &_17$$6, &t$$6);
				ZEPHIR_INIT_NVAR(&_19$$6);
				ZVAL_DOUBLE(&_19$$6, (zephir_get_doubleval(&t$$6) + (double) ((remainder$$6 * zephir_get_numberval(&_18$$6)))));
				zephir_array_append(&b, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 1880);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_20, 0, &b);
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
			zephir_throw_exception_debug(&_0$$4, "tensor/matrix.zep", 1898);
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
			zephir_throw_exception_debug(&_5$$5, "tensor/matrix.zep", 1904);
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

	zval b, rowB$$4, rowB$$7;
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
	ZVAL_UNDEF(&rowB$$4);
	ZVAL_UNDEF(&rowB$$7);

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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 1942);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_4, 0, "tensor/matrix.zep", 1959);
	if (Z_TYPE_P(&_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_4), _5)
		{
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _5);
			ZEPHIR_INIT_NVAR(&rowB$$4);
			array_init(&rowB$$4);
			zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1956);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _7$$4)
				{
					ZEPHIR_INIT_NVAR(&value);
					ZVAL_COPY(&value, _7$$4);
					ZEPHIR_INIT_NVAR(&_9$$5);
					ZVAL_LONG(&_10$$5, precision);
					zephir_round(&_9$$5, &value, &_10$$5, NULL);
					zephir_array_append(&rowB$$4, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 1953);
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
						zephir_array_append(&rowB$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 1953);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&value);
			zephir_array_append(&b, &rowB$$4, PH_SEPARATE, "tensor/matrix.zep", 1956);
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
				ZEPHIR_INIT_NVAR(&rowB$$7);
				array_init(&rowB$$7);
				zephir_is_iterable(&row, 0, "tensor/matrix.zep", 1956);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$7)
					{
						ZEPHIR_INIT_NVAR(&value);
						ZVAL_COPY(&value, _13$$7);
						ZEPHIR_INIT_NVAR(&_15$$8);
						ZVAL_LONG(&_16$$8, precision);
						zephir_round(&_15$$8, &value, &_16$$8, NULL);
						zephir_array_append(&rowB$$7, &_15$$8, PH_SEPARATE, "tensor/matrix.zep", 1953);
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
							zephir_array_append(&rowB$$7, &_17$$9, PH_SEPARATE, "tensor/matrix.zep", 1953);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&value);
				zephir_array_append(&b, &rowB$$7, PH_SEPARATE, "tensor/matrix.zep", 1956);
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

	zval b, rowB$$4, rowB$$11;
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
	ZVAL_UNDEF(&rowB$$4);
	ZVAL_UNDEF(&rowB$$11);

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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 1995);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_2, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/matrix.zep", 2024);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB$$4);
			array_init(&rowB$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2021);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _5$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _5$$4);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_7$$6);
						ZVAL_DOUBLE(&_7$$6, max);
						zephir_array_append(&rowB$$4, &_7$$6, PH_SEPARATE, "tensor/matrix.zep", 2007);
						continue;
					}
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_8$$7);
						ZVAL_DOUBLE(&_8$$7, min);
						zephir_array_append(&rowB$$4, &_8$$7, PH_SEPARATE, "tensor/matrix.zep", 2013);
						continue;
					}
					zephir_array_append(&rowB$$4, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2018);
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
							zephir_array_append(&rowB$$4, &_9$$9, PH_SEPARATE, "tensor/matrix.zep", 2007);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_10$$10);
							ZVAL_DOUBLE(&_10$$10, min);
							zephir_array_append(&rowB$$4, &_10$$10, PH_SEPARATE, "tensor/matrix.zep", 2013);
							continue;
						}
						zephir_array_append(&rowB$$4, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2018);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB$$4, PH_SEPARATE, "tensor/matrix.zep", 2021);
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
				ZEPHIR_INIT_NVAR(&rowB$$11);
				array_init(&rowB$$11);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2021);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$11)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$11);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_13$$13);
							ZVAL_DOUBLE(&_13$$13, max);
							zephir_array_append(&rowB$$11, &_13$$13, PH_SEPARATE, "tensor/matrix.zep", 2007);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_14$$14);
							ZVAL_DOUBLE(&_14$$14, min);
							zephir_array_append(&rowB$$11, &_14$$14, PH_SEPARATE, "tensor/matrix.zep", 2013);
							continue;
						}
						zephir_array_append(&rowB$$11, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2018);
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
								zephir_array_append(&rowB$$11, &_15$$16, PH_SEPARATE, "tensor/matrix.zep", 2007);
								continue;
							}
							if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
								ZEPHIR_INIT_NVAR(&_16$$17);
								ZVAL_DOUBLE(&_16$$17, min);
								zephir_array_append(&rowB$$11, &_16$$17, PH_SEPARATE, "tensor/matrix.zep", 2013);
								continue;
							}
							zephir_array_append(&rowB$$11, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2018);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB$$11, PH_SEPARATE, "tensor/matrix.zep", 2021);
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

	zval b, rowB$$3, rowB$$8;
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
	ZVAL_UNDEF(&rowB$$3);
	ZVAL_UNDEF(&rowB$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &min_param);

	min = zephir_get_doubleval(min_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2055);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB$$3);
			array_init(&rowB$$3);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2052);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_DOUBLE(&_5$$5, min);
						zephir_array_append(&rowB$$3, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2044);
						continue;
					}
					zephir_array_append(&rowB$$3, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2049);
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
							zephir_array_append(&rowB$$3, &_6$$7, PH_SEPARATE, "tensor/matrix.zep", 2044);
							continue;
						}
						zephir_array_append(&rowB$$3, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2049);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB$$3, PH_SEPARATE, "tensor/matrix.zep", 2052);
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
				ZEPHIR_INIT_NVAR(&rowB$$8);
				array_init(&rowB$$8);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2052);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _7$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _7$$8);
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_DOUBLE(&_9$$10, min);
							zephir_array_append(&rowB$$8, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2044);
							continue;
						}
						zephir_array_append(&rowB$$8, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2049);
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
								zephir_array_append(&rowB$$8, &_10$$12, PH_SEPARATE, "tensor/matrix.zep", 2044);
								continue;
							}
							zephir_array_append(&rowB$$8, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2049);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB$$8, PH_SEPARATE, "tensor/matrix.zep", 2052);
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

	zval b, rowB$$3, rowB$$8;
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
	ZVAL_UNDEF(&rowB$$3);
	ZVAL_UNDEF(&rowB$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &max_param);

	max = zephir_get_doubleval(max_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2086);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB$$3);
			array_init(&rowB$$3);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2083);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_DOUBLE(&_5$$5, max);
						zephir_array_append(&rowB$$3, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2075);
						continue;
					}
					zephir_array_append(&rowB$$3, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2080);
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
							zephir_array_append(&rowB$$3, &_6$$7, PH_SEPARATE, "tensor/matrix.zep", 2075);
							continue;
						}
						zephir_array_append(&rowB$$3, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2080);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB$$3, PH_SEPARATE, "tensor/matrix.zep", 2083);
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
				ZEPHIR_INIT_NVAR(&rowB$$8);
				array_init(&rowB$$8);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2083);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _7$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _7$$8);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_DOUBLE(&_9$$10, max);
							zephir_array_append(&rowB$$8, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2075);
							continue;
						}
						zephir_array_append(&rowB$$8, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2080);
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
								zephir_array_append(&rowB$$8, &_10$$12, PH_SEPARATE, "tensor/matrix.zep", 2075);
								continue;
							}
							zephir_array_append(&rowB$$8, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2080);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB$$8, PH_SEPARATE, "tensor/matrix.zep", 2083);
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

	zval b, rowB$$3, rowB$$12;
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
	ZVAL_UNDEF(&rowB$$3);
	ZVAL_UNDEF(&rowB$$12);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2116);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB$$3);
			array_init(&rowB$$3);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2113);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_GT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_LONG(&_5$$5, 1);
						zephir_array_append(&rowB$$3, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2105);
					} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_6$$6);
						ZVAL_LONG(&_6$$6, -1);
						zephir_array_append(&rowB$$3, &_6$$6, PH_SEPARATE, "tensor/matrix.zep", 2107);
					} else {
						ZEPHIR_INIT_NVAR(&_7$$7);
						ZVAL_LONG(&_7$$7, 0);
						zephir_array_append(&rowB$$3, &_7$$7, PH_SEPARATE, "tensor/matrix.zep", 2109);
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
							zephir_array_append(&rowB$$3, &_8$$9, PH_SEPARATE, "tensor/matrix.zep", 2105);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_LONG(&_9$$10, -1);
							zephir_array_append(&rowB$$3, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2107);
						} else {
							ZEPHIR_INIT_NVAR(&_10$$11);
							ZVAL_LONG(&_10$$11, 0);
							zephir_array_append(&rowB$$3, &_10$$11, PH_SEPARATE, "tensor/matrix.zep", 2109);
						}
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB$$3, PH_SEPARATE, "tensor/matrix.zep", 2113);
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
				ZEPHIR_INIT_NVAR(&rowB$$12);
				array_init(&rowB$$12);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2113);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$12)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$12);
						if (ZEPHIR_GT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_13$$14);
							ZVAL_LONG(&_13$$14, 1);
							zephir_array_append(&rowB$$12, &_13$$14, PH_SEPARATE, "tensor/matrix.zep", 2105);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_14$$15);
							ZVAL_LONG(&_14$$15, -1);
							zephir_array_append(&rowB$$12, &_14$$15, PH_SEPARATE, "tensor/matrix.zep", 2107);
						} else {
							ZEPHIR_INIT_NVAR(&_15$$16);
							ZVAL_LONG(&_15$$16, 0);
							zephir_array_append(&rowB$$12, &_15$$16, PH_SEPARATE, "tensor/matrix.zep", 2109);
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
								zephir_array_append(&rowB$$12, &_16$$18, PH_SEPARATE, "tensor/matrix.zep", 2105);
							} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
								ZEPHIR_INIT_NVAR(&_17$$19);
								ZVAL_LONG(&_17$$19, -1);
								zephir_array_append(&rowB$$12, &_17$$19, PH_SEPARATE, "tensor/matrix.zep", 2107);
							} else {
								ZEPHIR_INIT_NVAR(&_18$$20);
								ZVAL_LONG(&_18$$20, 0);
								zephir_array_append(&rowB$$12, &_18$$20, PH_SEPARATE, "tensor/matrix.zep", 2109);
							}
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB$$12, PH_SEPARATE, "tensor/matrix.zep", 2113);
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

	zval b, rowB$$3, rowB$$6;
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
	ZVAL_UNDEF(&rowB$$3);
	ZVAL_UNDEF(&rowB$$6);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2140);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB$$3);
			array_init(&rowB$$3);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2137);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					zephir_negate(&valueA);
					zephir_array_append(&rowB$$3, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2134);
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
						zephir_array_append(&rowB$$3, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2134);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB$$3, PH_SEPARATE, "tensor/matrix.zep", 2137);
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
				ZEPHIR_INIT_NVAR(&rowB$$6);
				array_init(&rowB$$6);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2137);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _5$$6)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _5$$6);
						zephir_negate(&valueA);
						zephir_array_append(&rowB$$6, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2134);
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
							zephir_array_append(&rowB$$6, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2134);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB$$6, PH_SEPARATE, "tensor/matrix.zep", 2137);
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
	zval b, rowB$$6;
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
	ZVAL_UNDEF(&rowB$$6);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 2156);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 2161);
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
		zephir_throw_exception_debug(&_12$$5, "tensor/matrix.zep", 2168);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_14, this_ptr, SL("n"), PH_NOISY_CC | PH_READONLY);
	k = ((zephir_get_numberval(&_14) - n) - 1);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
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
			zephir_array_fetch_long(&rowA, &_18$$6, i, PH_NOISY, "tensor/matrix.zep", 2179);
			ZEPHIR_INIT_NVAR(&rowB$$6);
			array_init(&rowB$$6);
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
					zephir_array_fetch_long(&_22$$7, &rowA, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2184);
					zephir_array_append(&rowB$$6, &_22$$7, PH_SEPARATE, "tensor/matrix.zep", 2184);
				}
			}
			zephir_array_append(&b, &rowB$$6, PH_SEPARATE, "tensor/matrix.zep", 2187);
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
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2205);
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
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2223);
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
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2241);
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
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2259);
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

	zend_string *_4$$3;
	zend_ulong _3$$3;
	zend_bool _15, _5$$4, _10$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, i, rowA, b, c, _0$$3, *_1$$3, _2$$3, _8$$5, _9$$5, _13$$7, _14$$7, _18$$8;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, j = 0, k = 0, _16, _17, _6$$4, _7$$4, _11$$6, _12$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_18$$8);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	ZEPHIR_OBS_VAR(&b);
	zephir_read_property(&b, this_ptr, SL("a"), PH_NOISY_CC);
	if (n > 0) {
		zephir_read_property(&_0$$3, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_0$$3, 0, "tensor/matrix.zep", 2287);
		if (Z_TYPE_P(&_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_0$$3), _3$$3, _4$$3, _1$$3)
			{
				ZEPHIR_INIT_NVAR(&i);
				if (_4$$3 != NULL) { 
					ZVAL_STR_COPY(&i, _4$$3);
				} else {
					ZVAL_LONG(&i, _3$$3);
				}
				ZEPHIR_INIT_NVAR(&rowA);
				ZVAL_COPY(&rowA, _1$$3);
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
						zephir_array_fetch(&_9$$5, &b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2284);
						zephir_fast_array_merge(&_8$$5, &_9$$5, &rowA);
						zephir_array_update_zval(&b, &i, &_8$$5, PH_COPY | PH_SEPARATE);
					}
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &_0$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_2$$3, &_0$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_2$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&i, &_0$$3, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&rowA, &_0$$3, "current", NULL, 0);
				zephir_check_call_status();
					_12$$6 = (n - 1);
					_11$$6 = 0;
					_10$$6 = 0;
					if (_11$$6 <= _12$$6) {
						while (1) {
							if (_10$$6) {
								_11$$6++;
								if (!(_11$$6 <= _12$$6)) {
									break;
								}
							} else {
								_10$$6 = 1;
							}
							j = _11$$6;
							ZEPHIR_INIT_NVAR(&_13$$7);
							zephir_array_fetch(&_14$$7, &b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2284);
							zephir_fast_array_merge(&_13$$7, &_14$$7, &rowA);
							zephir_array_update_zval(&b, &i, &_13$$7, PH_COPY | PH_SEPARATE);
						}
					}
				ZEPHIR_CALL_METHOD(NULL, &_0$$3, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&rowA);
		ZEPHIR_INIT_NVAR(&i);
	}
	ZEPHIR_CPY_WRT(&c, &b);
	_17 = (m - 1);
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
			k = _16;
			ZEPHIR_INIT_NVAR(&_18$$8);
			zephir_fast_array_merge(&_18$$8, &c, &b);
			ZEPHIR_CPY_WRT(&c, &_18$$8);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2309);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2328);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2317);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2325);
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
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2322);
					ZEPHIR_INIT_NVAR(&_17$$5);
					mul_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2322);
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
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2322);
						ZEPHIR_INIT_NVAR(&_19$$6);
						mul_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2322);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2325);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2317);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2325);
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
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2322);
						ZEPHIR_INIT_NVAR(&_26$$8);
						mul_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2322);
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
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2322);
							ZEPHIR_INIT_NVAR(&_28$$9);
							mul_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2322);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2325);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2342);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2361);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2350);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2358);
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
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2355);
					ZEPHIR_INIT_NVAR(&_17$$5);
					div_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2355);
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
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2355);
						ZEPHIR_INIT_NVAR(&_19$$6);
						div_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2355);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2358);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2350);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2358);
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
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2355);
						ZEPHIR_INIT_NVAR(&_26$$8);
						div_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2355);
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
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2355);
							ZEPHIR_INIT_NVAR(&_28$$9);
							div_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2355);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2358);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2375);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2394);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2383);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2391);
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
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2388);
					ZEPHIR_INIT_NVAR(&_17$$5);
					zephir_add_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2388);
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
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2388);
						ZEPHIR_INIT_NVAR(&_19$$6);
						zephir_add_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2388);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2391);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2383);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2391);
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
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2388);
						ZEPHIR_INIT_NVAR(&_26$$8);
						zephir_add_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2388);
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
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2388);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_add_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2388);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2391);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2408);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2427);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2416);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2424);
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
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2421);
					ZEPHIR_INIT_NVAR(&_17$$5);
					zephir_sub_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2421);
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
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2421);
						ZEPHIR_INIT_NVAR(&_19$$6);
						zephir_sub_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2421);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2424);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2416);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2424);
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
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2421);
						ZEPHIR_INIT_NVAR(&_26$$8);
						zephir_sub_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2421);
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
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2421);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_sub_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2421);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2424);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2442);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2461);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2450);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2458);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2455);
					zephir_pow_function(&_16$$5, &valueA, &_17$$5);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2455);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2455);
						zephir_pow_function(&_18$$6, &valueA, &_19$$6);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2455);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2458);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2450);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2458);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2455);
						zephir_pow_function(&_25$$8, &valueA, &_26$$8);
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2455);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2455);
							zephir_pow_function(&_27$$9, &valueA, &_28$$9);
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2455);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2458);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2476);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2495);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2484);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2492);
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
					zephir_array_fetch(&_16$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2489);
					ZEPHIR_INIT_NVAR(&_17$$5);
					mod_function(&_17$$5, &valueA, &_16$$5);
					zephir_array_append(&rowC$$4, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2489);
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
						zephir_array_fetch(&_18$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2489);
						ZEPHIR_INIT_NVAR(&_19$$6);
						mod_function(&_19$$6, &valueA, &_18$$6);
						zephir_array_append(&rowC$$4, &_19$$6, PH_SEPARATE, "tensor/matrix.zep", 2489);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2492);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2484);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2492);
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
						zephir_array_fetch(&_25$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2489);
						ZEPHIR_INIT_NVAR(&_26$$8);
						mod_function(&_26$$8, &valueA, &_25$$8);
						zephir_array_append(&rowC$$7, &_26$$8, PH_SEPARATE, "tensor/matrix.zep", 2489);
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
							zephir_array_fetch(&_27$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2489);
							ZEPHIR_INIT_NVAR(&_28$$9);
							mod_function(&_28$$9, &valueA, &_27$$9);
							zephir_array_append(&rowC$$7, &_28$$9, PH_SEPARATE, "tensor/matrix.zep", 2489);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2492);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2510);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2529);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2518);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2526);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2523);
					if (ZEPHIR_IS_EQUAL(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2523);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2523);
						if (ZEPHIR_IS_EQUAL(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2523);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2526);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2518);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2526);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2523);
						if (ZEPHIR_IS_EQUAL(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2523);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2523);
							if (ZEPHIR_IS_EQUAL(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2523);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2526);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2544);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2563);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2552);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2560);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2557);
					if (!ZEPHIR_IS_EQUAL(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2557);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2557);
						if (!ZEPHIR_IS_EQUAL(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2557);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2560);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2552);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2560);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2557);
						if (!ZEPHIR_IS_EQUAL(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2557);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2557);
							if (!ZEPHIR_IS_EQUAL(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2557);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2560);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2578);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2597);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2586);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2594);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2591);
					if (ZEPHIR_GT(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2591);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2591);
						if (ZEPHIR_GT(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2591);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2594);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2586);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2594);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2591);
						if (ZEPHIR_GT(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2591);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2591);
							if (ZEPHIR_GT(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2591);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2594);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2612);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2631);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2620);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2628);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2625);
					if (ZEPHIR_GE(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2625);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2625);
						if (ZEPHIR_GE(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2625);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2628);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2620);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2628);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2625);
						if (ZEPHIR_GE(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2625);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2625);
							if (ZEPHIR_GE(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2625);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2628);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2646);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2665);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2654);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2662);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2659);
					if (ZEPHIR_LT(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2659);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2659);
						if (ZEPHIR_LT(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2659);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2662);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2654);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2662);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2659);
						if (ZEPHIR_LT(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2659);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2659);
							if (ZEPHIR_LT(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2659);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2662);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2680);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2699);
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
			zephir_array_fetch(&rowA, &_11$$4, &i, PH_NOISY, "tensor/matrix.zep", 2688);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2696);
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
					zephir_array_fetch(&_17$$5, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2693);
					if (ZEPHIR_LE(&valueA, &_17$$5)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2693);
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
						zephir_array_fetch(&_19$$6, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2693);
						if (ZEPHIR_LE(&valueA, &_19$$6)) {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_18$$6);
							ZVAL_LONG(&_18$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2693);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2696);
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
				zephir_array_fetch(&rowA, &_20$$7, &i, PH_NOISY, "tensor/matrix.zep", 2688);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2696);
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
						zephir_array_fetch(&_26$$8, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2693);
						if (ZEPHIR_LE(&valueA, &_26$$8)) {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_25$$8);
							ZVAL_LONG(&_25$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_25$$8, PH_SEPARATE, "tensor/matrix.zep", 2693);
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
							zephir_array_fetch(&_28$$9, &rowB, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2693);
							if (ZEPHIR_LE(&valueA, &_28$$9)) {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$9);
								ZVAL_LONG(&_27$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_27$$9, PH_SEPARATE, "tensor/matrix.zep", 2693);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2696);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2714);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2733);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2730);
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
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2727);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mul_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2727);
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
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2727);
						ZEPHIR_INIT_NVAR(&_18$$6);
						mul_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2727);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2730);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2730);
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
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2727);
						ZEPHIR_INIT_NVAR(&_24$$8);
						mul_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC$$7, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2727);
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
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2727);
							ZEPHIR_INIT_NVAR(&_26$$9);
							mul_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC$$7, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2727);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2730);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2748);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2767);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2764);
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
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2761);
					ZEPHIR_INIT_NVAR(&_16$$5);
					div_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2761);
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
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2761);
						ZEPHIR_INIT_NVAR(&_18$$6);
						div_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2761);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2764);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2764);
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
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2761);
						ZEPHIR_INIT_NVAR(&_24$$8);
						div_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC$$7, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2761);
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
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2761);
							ZEPHIR_INIT_NVAR(&_26$$9);
							div_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC$$7, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2761);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2764);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2782);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2801);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2798);
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
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2795);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_add_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2795);
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
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2795);
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_add_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2795);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2798);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2798);
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
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2795);
						ZEPHIR_INIT_NVAR(&_24$$8);
						zephir_add_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC$$7, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2795);
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
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2795);
							ZEPHIR_INIT_NVAR(&_26$$9);
							zephir_add_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC$$7, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2795);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2798);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2816);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2835);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2832);
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
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2829);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_sub_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2829);
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
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2829);
						ZEPHIR_INIT_NVAR(&_18$$6);
						zephir_sub_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2829);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2832);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2832);
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
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2829);
						ZEPHIR_INIT_NVAR(&_24$$8);
						zephir_sub_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC$$7, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2829);
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
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2829);
							ZEPHIR_INIT_NVAR(&_26$$9);
							zephir_sub_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC$$7, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2829);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2832);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2850);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2869);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2866);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2863);
					zephir_pow_function(&_15$$5, &_16$$5, &valueB);
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2863);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2863);
						zephir_pow_function(&_17$$6, &_18$$6, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2863);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2866);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2866);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2863);
						zephir_pow_function(&_23$$8, &_24$$8, &valueB);
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2863);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2863);
							zephir_pow_function(&_25$$9, &_26$$9, &valueB);
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2863);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2866);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2884);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2903);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2900);
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
					zephir_array_fetch(&_15$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2897);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mod_function(&_16$$5, &_15$$5, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 2897);
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
						zephir_array_fetch(&_17$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2897);
						ZEPHIR_INIT_NVAR(&_18$$6);
						mod_function(&_18$$6, &_17$$6, &valueB);
						zephir_array_append(&rowC$$4, &_18$$6, PH_SEPARATE, "tensor/matrix.zep", 2897);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2900);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2900);
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
						zephir_array_fetch(&_23$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2897);
						ZEPHIR_INIT_NVAR(&_24$$8);
						mod_function(&_24$$8, &_23$$8, &valueB);
						zephir_array_append(&rowC$$7, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 2897);
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
							zephir_array_fetch(&_25$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2897);
							ZEPHIR_INIT_NVAR(&_26$$9);
							mod_function(&_26$$9, &_25$$9, &valueB);
							zephir_array_append(&rowC$$7, &_26$$9, PH_SEPARATE, "tensor/matrix.zep", 2897);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2900);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2919);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2938);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2935);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2932);
					if (ZEPHIR_IS_EQUAL(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2932);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2932);
						if (ZEPHIR_IS_EQUAL(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2932);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2935);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2935);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2932);
						if (ZEPHIR_IS_EQUAL(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2932);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2932);
							if (ZEPHIR_IS_EQUAL(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2932);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2935);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2954);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2973);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2970);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2967);
					if (!ZEPHIR_IS_EQUAL(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2967);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2967);
						if (!ZEPHIR_IS_EQUAL(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 2967);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 2970);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 2970);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2967);
						if (!ZEPHIR_IS_EQUAL(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 2967);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2967);
							if (!ZEPHIR_IS_EQUAL(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 2967);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 2970);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2989);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3008);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3005);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3002);
					if (ZEPHIR_GT(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3002);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3002);
						if (ZEPHIR_GT(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3002);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3005);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3005);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3002);
						if (ZEPHIR_GT(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3002);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3002);
							if (ZEPHIR_GT(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3002);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3005);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3024);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3043);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3040);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3037);
					if (ZEPHIR_GE(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3037);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3037);
						if (ZEPHIR_GE(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3037);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3040);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3040);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3037);
						if (ZEPHIR_GE(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3037);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3037);
							if (ZEPHIR_GE(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3037);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3040);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3059);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3078);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3075);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3072);
					if (ZEPHIR_LT(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3072);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3072);
						if (ZEPHIR_LT(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3072);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3075);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3075);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3072);
						if (ZEPHIR_LT(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3072);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3072);
							if (ZEPHIR_LT(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3072);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3075);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3094);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_8, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3113);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3110);
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
					zephir_array_fetch(&_16$$5, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3107);
					if (ZEPHIR_LE(&_16$$5, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 3107);
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
						zephir_array_fetch(&_18$$6, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3107);
						if (ZEPHIR_LE(&_18$$6, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3107);
					ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3110);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&bHat, 0, "tensor/matrix.zep", 3110);
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
						zephir_array_fetch(&_24$$8, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3107);
						if (ZEPHIR_LE(&_24$$8, &valueB)) {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_23$$8);
							ZVAL_LONG(&_23$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_23$$8, PH_SEPARATE, "tensor/matrix.zep", 3107);
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
							zephir_array_fetch(&_26$$9, &rowA, &j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3107);
							if (ZEPHIR_LE(&_26$$9, &valueB)) {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_25$$9);
								ZVAL_LONG(&_25$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 3107);
						ZEPHIR_CALL_METHOD(NULL, &bHat, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3110);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3128);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3147);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3136);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3144);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mul_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3141);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3141);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3144);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3136);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3144);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						mul_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3141);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3141);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3144);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3162);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3181);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3170);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3178);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					div_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3175);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3175);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3178);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3170);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3178);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						div_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3175);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3175);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3178);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3196);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3215);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3204);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3212);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_add_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3209);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3209);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3212);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3204);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3212);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_add_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3209);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3209);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3212);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3230);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3249);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3238);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3246);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_sub_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3243);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3243);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3246);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3238);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3246);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_sub_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3243);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3243);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3246);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3264);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3283);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3272);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3280);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_pow_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3277);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3277);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3280);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3272);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3280);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_pow_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3277);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3277);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3280);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3298);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3317);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3306);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3314);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mod_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3311);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3311);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3314);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3306);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3314);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						mod_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3311);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3311);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3314);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3333);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3352);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3341);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3349);
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
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3346);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3346);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3349);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3341);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3349);
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
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3346);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3346);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3349);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3368);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3387);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3376);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3384);
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
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3381);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3381);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3384);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3376);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3384);
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
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3381);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3381);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3384);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3403);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3422);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3411);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3419);
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
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3416);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3416);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3419);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3411);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3419);
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
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3416);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3416);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3419);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3438);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3457);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3446);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3454);
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
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3451);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3451);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3454);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3446);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3454);
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
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3451);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3451);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3454);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3473);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3492);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3481);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3489);
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
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3486);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3486);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3489);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3481);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3489);
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
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3486);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3486);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3489);
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
	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3508);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3527);
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
			zephir_array_fetch(&rowA, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 3516);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3524);
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
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3521);
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
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/matrix.zep", 3521);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3524);
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
				zephir_array_fetch(&rowA, &_18$$7, &i, PH_NOISY, "tensor/matrix.zep", 3516);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3524);
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
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 3521);
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
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/matrix.zep", 3521);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3524);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3541);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3558);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3555);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					mul_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3552);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3552);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3555);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3555);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						mul_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3552);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3552);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3555);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3572);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3589);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3586);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					div_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3583);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3583);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3586);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3586);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						div_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3583);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3583);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3586);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3603);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3620);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3617);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					zephir_add_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3614);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3614);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3617);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3617);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						zephir_add_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3614);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3614);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3617);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3634);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3651);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3648);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					zephir_sub_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3645);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3645);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3648);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3648);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						zephir_sub_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3645);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3645);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3648);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3666);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3683);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3680);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					zephir_pow_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3677);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3677);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3680);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3680);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						zephir_pow_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3677);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3677);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3680);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3697);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3714);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3711);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					ZEPHIR_INIT_NVAR(&_10$$5);
					mod_function(&_10$$5, &valueA, b);
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3708);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3708);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3711);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3711);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _12$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _12$$7);
						ZEPHIR_INIT_NVAR(&_14$$8);
						mod_function(&_14$$8, &valueA, b);
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3708);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3708);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3711);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3729);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3746);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3743);
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
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3740);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3740);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3743);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3743);
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
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3740);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3740);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3743);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3761);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3778);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3775);
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
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3772);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3772);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3775);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3775);
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
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3772);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3772);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3775);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3793);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3810);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3807);
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
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3804);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3804);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3807);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3807);
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
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3804);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3804);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3807);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3825);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3842);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3839);
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
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3836);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3836);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3839);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3839);
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
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3836);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3836);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3839);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3857);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3874);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3871);
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
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3868);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3868);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3871);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3871);
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
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3868);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3868);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3871);
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

	zval c, rowC$$4, rowC$$7;
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
	ZVAL_UNDEF(&rowC$$4);
	ZVAL_UNDEF(&rowC$$7);

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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3889);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3906);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3903);
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
					zephir_array_append(&rowC$$4, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 3900);
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
						zephir_array_append(&rowC$$4, &_11$$6, PH_SEPARATE, "tensor/matrix.zep", 3900);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/matrix.zep", 3903);
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
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 3903);
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
						zephir_array_append(&rowC$$7, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 3900);
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
							zephir_array_append(&rowC$$7, &_15$$9, PH_SEPARATE, "tensor/matrix.zep", 3900);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/matrix.zep", 3903);
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



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3924);
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



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_RuntimeException, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3944);
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
	zephir_throw_exception_debug(&_1, "tensor/matrix.zep", 3963);
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

zend_object *zephir_init_properties_Tensor_Matrix(zend_class_entry *class_type TSRMLS_DC) {

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

