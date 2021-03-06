
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
#include "include/signal_processing.h"
#include "include/arithmetic.h"
#include "include/comparison.h"


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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, identity) {

	zend_bool _4, _7$$4;
	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _10$$5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, _5, _6, _8$$4, _9$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);

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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 79);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
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
			ZEPHIR_INIT_NVAR(&rowA);
			array_init(&rowA);
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
					if (i == j) {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_LONG(&_10$$5, 0);
					}
					zephir_array_append(&rowA, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 91);
				}
			}
			zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 94);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, diagonal) {

	zend_bool _17, _6$$4, _12$$6, _20$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, n, i = 0, j = 0, _18, _19, _21$$8, _22$$8;
	zval *elements_param = NULL, element, *_4, _5, _0$$3, _1$$3, _2$$3, _3$$3, _7$$4, _9$$5, _10$$5, _11$$5, _13$$6, _14$$7, _15$$7, _16$$7, _23$$9;
	zval elements, a, rowA;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&elements);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&element);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_23$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &elements_param);

	zephir_get_arrval(&elements, elements_param);


	n = zephir_fast_count_int(&elements);
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, n);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Number of elements must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 140);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_is_iterable(&elements, 0, "tensor/matrix.zep", 153);
	if (Z_TYPE_P(&elements) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&elements), _4)
		{
			ZEPHIR_INIT_NVAR(&element);
			ZVAL_COPY(&element, _4);
			_6$$4 = !(Z_TYPE_P(&element) == IS_LONG);
			if (_6$$4) {
				ZEPHIR_CALL_FUNCTION(&_7$$4, "is_float", &_8, 2, &element);
				zephir_check_call_status();
				_6$$4 = !zephir_is_true(&_7$$4);
			}
			if (_6$$4) {
				ZEPHIR_INIT_NVAR(&_9$$5);
				object_init_ex(&_9$$5, tensor_exceptions_invalidargumentexception_ce);
				ZEPHIR_INIT_NVAR(&_10$$5);
				zephir_gettype(&_10$$5, &element);
				ZEPHIR_INIT_NVAR(&_11$$5);
				ZEPHIR_CONCAT_SSVS(&_11$$5, "Diagonal element", " must be an integer or floating point number, ", &_10$$5, " given.");
				ZEPHIR_CALL_METHOD(NULL, &_9$$5, "__construct", NULL, 3, &_11$$5);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_9$$5, "tensor/matrix.zep", 149);
				ZEPHIR_MM_RESTORE();
				return;
			}
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &elements, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_5, &elements, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&element, &elements, "current", NULL, 0);
			zephir_check_call_status();
				_12$$6 = !(Z_TYPE_P(&element) == IS_LONG);
				if (_12$$6) {
					ZEPHIR_CALL_FUNCTION(&_13$$6, "is_float", &_8, 2, &element);
					zephir_check_call_status();
					_12$$6 = !zephir_is_true(&_13$$6);
				}
				if (_12$$6) {
					ZEPHIR_INIT_NVAR(&_14$$7);
					object_init_ex(&_14$$7, tensor_exceptions_invalidargumentexception_ce);
					ZEPHIR_INIT_NVAR(&_15$$7);
					zephir_gettype(&_15$$7, &element);
					ZEPHIR_INIT_NVAR(&_16$$7);
					ZEPHIR_CONCAT_SSVS(&_16$$7, "Diagonal element", " must be an integer or floating point number, ", &_15$$7, " given.");
					ZEPHIR_CALL_METHOD(NULL, &_14$$7, "__construct", NULL, 3, &_16$$7);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_14$$7, "tensor/matrix.zep", 149);
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
	_19 = (n - 1);
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
			i = _18;
			ZEPHIR_INIT_NVAR(&rowA);
			array_init(&rowA);
			_22$$8 = (n - 1);
			_21$$8 = 0;
			_20$$8 = 0;
			if (_21$$8 <= _22$$8) {
				while (1) {
					if (_20$$8) {
						_21$$8++;
						if (!(_21$$8 <= _22$$8)) {
							break;
						}
					} else {
						_20$$8 = 1;
					}
					j = _21$$8;
					ZEPHIR_INIT_NVAR(&_23$$9);
					if (i == j) {
						ZEPHIR_OBS_NVAR(&_23$$9);
						zephir_array_fetch_long(&_23$$9, &elements, i, PH_NOISY, "tensor/matrix.zep", 162);
					} else {
						ZEPHIR_INIT_NVAR(&_23$$9);
						ZVAL_LONG(&_23$$9, 0);
					}
					zephir_array_append(&rowA, &_23$$9, PH_SEPARATE, "tensor/matrix.zep", 162);
				}
			}
			zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 165);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, fill) {

	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL, *_17 = NULL;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *value, value_sub, *m_param = NULL, *n_param = NULL, _1, _14, _15, _16, _18, _2$$3, _3$$3, _4$$3, _5$$4, _6$$4, _7$$4, _9$$4, _10$$5, _11$$5, _12$$5, _13$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&value_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &value, &m_param, &n_param);

	m = zephir_get_intval(m_param);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 185);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(m < 1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, m);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_8, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_9$$4);
		ZEPHIR_CONCAT_SSVS(&_9$$4, "M must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_9$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 190);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_10$$5);
		object_init_ex(&_10$$5, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_11$$5, n);
		ZEPHIR_CALL_FUNCTION(&_12$$5, "strval", &_8, 4, &_11$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_13$$5);
		ZEPHIR_CONCAT_SSVS(&_13$$5, "N must be", " greater than 0, ", &_12$$5, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_10$$5, "__construct", NULL, 3, &_13$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_10$$5, "tensor/matrix.zep", 195);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_14, 0);
	ZVAL_LONG(&_15, n);
	ZEPHIR_CALL_FUNCTION(&_16, "array_fill", &_17, 5, &_14, &_15, value);
	zephir_check_call_status();
	ZVAL_LONG(&_14, 0);
	ZVAL_LONG(&_15, m);
	ZEPHIR_CALL_FUNCTION(&_18, "array_fill", &_17, 5, &_14, &_15, &_16);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_18);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a random uniform matrix with values between 0 and 1.
 *
 * @param int m
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, rand) {

	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_11 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10$$6, _12$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;
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
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	if (UNEXPECTED(m < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, m);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", &_3, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "M must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 213);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_3, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "N must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 218);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_CALL_FUNCTION(&_9, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_9);
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
			ZEPHIR_CALL_FUNCTION(&_10$$6, "rand", &_11, 7);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_12$$6);
			ZVAL_DOUBLE(&_12$$6, zephir_safe_div_zval_long(&_10$$6, max));
			zephir_array_append(&rowA, &_12$$6, PH_SEPARATE, "tensor/matrix.zep", 230);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 233);
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return a standard normally (Gaussian( distributed random matrix of specified dimensionality.
 *
 * @param int m
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, gaussian) {

	zval a, rowA, extras;
	double r = 0, phi = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_11 = NULL, *_13 = NULL, *_16 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10$$6, _12$$7, _14$$7, _15$$7, _17$$7, _18$$7, _19$$7, _20$$7, _21$$8;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;
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
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&extras);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	if (UNEXPECTED(m < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, m);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", &_3, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "M must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 251);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_3, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "N must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 256);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_INIT_VAR(&extras);
	array_init(&extras);
	ZEPHIR_CALL_FUNCTION(&_9, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_9);
	while (1) {
		if (!(zephir_fast_count_int(&a) < m)) {
			break;
		}
		ZEPHIR_INIT_NVAR(&rowA);
		array_init(&rowA);
		if (!(ZEPHIR_IS_EMPTY(&extras))) {
			ZEPHIR_MAKE_REF(&extras);
			ZEPHIR_CALL_FUNCTION(&_10$$6, "array_pop", &_11, 9, &extras);
			ZEPHIR_UNREF(&extras);
			zephir_check_call_status();
			zephir_array_append(&rowA, &_10$$6, PH_SEPARATE, "tensor/matrix.zep", 271);
		}
		while (1) {
			if (!(zephir_fast_count_int(&rowA) < n)) {
				break;
			}
			ZEPHIR_CALL_FUNCTION(&_12$$7, "rand", &_13, 7);
			zephir_check_call_status();
			ZVAL_DOUBLE(&_14$$7, zephir_safe_div_zval_long(&_12$$7, max));
			ZEPHIR_CALL_FUNCTION(&_15$$7, "log", &_16, 8, &_14$$7);
			zephir_check_call_status();
			ZVAL_DOUBLE(&_14$$7, (-2.0 * zephir_get_numberval(&_15$$7)));
			r = sqrt((-2.0 * zephir_get_numberval(&_15$$7)));
			ZEPHIR_CALL_FUNCTION(&_17$$7, "rand", &_13, 7);
			zephir_check_call_status();
			phi = (zephir_safe_div_zval_long(&_17$$7, max) * 6.28318530718);
			ZVAL_DOUBLE(&_18$$7, phi);
			ZEPHIR_INIT_NVAR(&_19$$7);
			ZVAL_DOUBLE(&_19$$7, (r * sin(phi)));
			zephir_array_append(&rowA, &_19$$7, PH_SEPARATE, "tensor/matrix.zep", 279);
			ZVAL_DOUBLE(&_20$$7, phi);
			ZEPHIR_INIT_NVAR(&_19$$7);
			ZVAL_DOUBLE(&_19$$7, (r * cos(phi)));
			zephir_array_append(&rowA, &_19$$7, PH_SEPARATE, "tensor/matrix.zep", 280);
		}
		if (zephir_fast_count_int(&rowA) > n) {
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(&_21$$8, "array_pop", &_11, 9, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			zephir_array_append(&extras, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 284);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 287);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, poisson) {

	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_13 = NULL;
	double lambda, l = 0, p = 0;
	zval *m_param = NULL, *n_param = NULL, *lambda_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10, _11, _12$$7, _14$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, k = 0, max;
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
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_14$$6);
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


	if (UNEXPECTED(m < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, m);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", &_3, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "M must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 306);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_3, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "N must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 311);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZVAL_DOUBLE(&_9, -lambda);
	ZEPHIR_CALL_FUNCTION(&_10, "exp", NULL, 10, &_9);
	zephir_check_call_status();
	l = zephir_get_doubleval(&_10);
	ZEPHIR_CALL_FUNCTION(&_11, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_11);
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
				ZEPHIR_CALL_FUNCTION(&_12$$7, "rand", &_13, 7);
				zephir_check_call_status();
				p *= zephir_safe_div_zval_long(&_12$$7, max);
			}
			ZEPHIR_INIT_NVAR(&_14$$6);
			ZVAL_LONG(&_14$$6, (k - 1));
			zephir_array_append(&rowA, &_14$$6, PH_SEPARATE, "tensor/matrix.zep", 337);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 340);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, uniform) {

	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_13 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10$$6, _11$$6, _12$$6, _14$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;
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
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	if (UNEXPECTED(m < 1)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, m);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", &_3, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "M must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 358);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(n < 1)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, n);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_3, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "N must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 363);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZEPHIR_CALL_FUNCTION(&_9, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_9);
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
			ZVAL_LONG(&_10$$6, -max);
			ZVAL_LONG(&_11$$6, max);
			ZEPHIR_CALL_FUNCTION(&_12$$6, "rand", &_13, 7, &_10$$6, &_11$$6);
			zephir_check_call_status();
			ZEPHIR_INIT_NVAR(&_14$$6);
			ZVAL_DOUBLE(&_14$$6, zephir_safe_div_zval_long(&_12$$6, max));
			zephir_array_append(&rowA, &_14$$6, PH_SEPARATE, "tensor/matrix.zep", 375);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 378);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, minimum) {

	zval _4$$3, _6$$3, _7$$3, _12$$4, _14$$4, _15$$4;
	zend_string *_20;
	zend_ulong _19;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *b, b_sub, _0, _1, _8, _9, i, rowA, _16, *_17, _18, _2$$3, _3$$3, _5$$3, _10$$4, _11$$4, _13$$4, _21$$5, _22$$5, _23$$5, _25$$6, _26$$6, _27$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_23$$5);
	ZVAL_UNDEF(&_25$$6);
	ZVAL_UNDEF(&_26$$6);
	ZVAL_UNDEF(&_27$$6);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &b);



	ZEPHIR_CALL_METHOD(&_0, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 397);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_8, &_9))) {
		ZEPHIR_INIT_VAR(&_10$$4);
		object_init_ex(&_10$$4, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_11$$4, a, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_12$$4, &_11$$4);
		ZEPHIR_CALL_METHOD(&_13$$4, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_14$$4, &_13$$4);
		ZEPHIR_INIT_VAR(&_15$$4);
		ZEPHIR_CONCAT_SVSVS(&_15$$4, "Matrix A expects ", &_12$$4, " columns but Matrix B has ", &_14$$4, ".");
		ZEPHIR_CALL_METHOD(NULL, &_10$$4, "__construct", NULL, 3, &_15$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_10$$4, "tensor/matrix.zep", 403);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_16, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_16, 0, "tensor/matrix.zep", 414);
	if (Z_TYPE_P(&_16) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_16), _19, _20, _17)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_20 != NULL) { 
				ZVAL_STR_COPY(&i, _20);
			} else {
				ZVAL_LONG(&i, _19);
			}
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _17);
			zephir_array_fetch(&_21$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 411);
			ZEPHIR_INIT_NVAR(&_22$$5);
			ZVAL_STRING(&_22$$5, "min");
			ZEPHIR_CALL_FUNCTION(&_23$$5, "array_map", &_24, 14, &_22$$5, &rowA, &_21$$5);
			zephir_check_call_status();
			zephir_array_append(&c, &_23$$5, PH_SEPARATE, "tensor/matrix.zep", 411);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_16, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_18, &_16, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_18)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_16, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowA, &_16, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_25$$6, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 411);
				ZEPHIR_INIT_NVAR(&_26$$6);
				ZVAL_STRING(&_26$$6, "min");
				ZEPHIR_CALL_FUNCTION(&_27$$6, "array_map", &_24, 14, &_26$$6, &rowA, &_25$$6);
				zephir_check_call_status();
				zephir_array_append(&c, &_27$$6, PH_SEPARATE, "tensor/matrix.zep", 411);
			ZEPHIR_CALL_METHOD(NULL, &_16, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the elementwise maximum of two matrices.
 *
 * @param \Tensor\Matrix a
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, maximum) {

	zval _4$$3, _6$$3, _7$$3, _12$$4, _14$$4, _15$$4;
	zend_string *_20;
	zend_ulong _19;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *b, b_sub, _0, _1, _8, _9, i, rowA, _16, *_17, _18, _2$$3, _3$$3, _5$$3, _10$$4, _11$$4, _13$$4, _21$$5, _22$$5, _23$$5, _25$$6, _26$$6, _27$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_23$$5);
	ZVAL_UNDEF(&_25$$6);
	ZVAL_UNDEF(&_26$$6);
	ZVAL_UNDEF(&_27$$6);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &b);



	ZEPHIR_CALL_METHOD(&_0, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, a, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 430);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_8, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, b, "n", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_8, &_9))) {
		ZEPHIR_INIT_VAR(&_10$$4);
		object_init_ex(&_10$$4, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_11$$4, a, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_12$$4, &_11$$4);
		ZEPHIR_CALL_METHOD(&_13$$4, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_14$$4, &_13$$4);
		ZEPHIR_INIT_VAR(&_15$$4);
		ZEPHIR_CONCAT_SVSVS(&_15$$4, "Matrix A expects ", &_12$$4, " columns but Matrix B has ", &_14$$4, ".");
		ZEPHIR_CALL_METHOD(NULL, &_10$$4, "__construct", NULL, 3, &_15$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_10$$4, "tensor/matrix.zep", 436);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_16, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_16, 0, "tensor/matrix.zep", 447);
	if (Z_TYPE_P(&_16) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_16), _19, _20, _17)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_20 != NULL) { 
				ZVAL_STR_COPY(&i, _20);
			} else {
				ZVAL_LONG(&i, _19);
			}
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _17);
			zephir_array_fetch(&_21$$5, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 444);
			ZEPHIR_INIT_NVAR(&_22$$5);
			ZVAL_STRING(&_22$$5, "max");
			ZEPHIR_CALL_FUNCTION(&_23$$5, "array_map", &_24, 14, &_22$$5, &rowA, &_21$$5);
			zephir_check_call_status();
			zephir_array_append(&c, &_23$$5, PH_SEPARATE, "tensor/matrix.zep", 444);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_16, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_18, &_16, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_18)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_16, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowA, &_16, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_25$$6, b, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 444);
				ZEPHIR_INIT_NVAR(&_26$$6);
				ZVAL_STRING(&_26$$6, "max");
				ZEPHIR_CALL_FUNCTION(&_27$$6, "array_map", &_24, 14, &_26$$6, &rowA, &_25$$6);
				zephir_check_call_status();
				zephir_array_append(&c, &_27$$6, PH_SEPARATE, "tensor/matrix.zep", 444);
			ZEPHIR_CALL_METHOD(NULL, &_16, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Build a matrix by stacking an array of vectors.
 *
 * @param \Tensor\Vector[] vectors
 * @throws \Tensor\Exceptions\InvalidArgumentException
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


	if (UNEXPECTED(ZEPHIR_IS_EMPTY(&vectors))) {
		ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_MAKE_REF(&vectors);
	ZEPHIR_CALL_FUNCTION(&proto, "reset", NULL, 29, &vectors);
	ZEPHIR_UNREF(&vectors);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&size, &proto, "size", NULL, 0);
	zephir_check_call_status();
	columnwise = zephir_instance_of_ev(&proto, tensor_columnvector_ce);
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	zephir_is_iterable(&vectors, 0, "tensor/matrix.zep", 492);
	if (Z_TYPE_P(&vectors) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&vectors), _0)
		{
			ZEPHIR_INIT_NVAR(&vector);
			ZVAL_COPY(&vector, _0);
			if (UNEXPECTED(!((zephir_instance_of_ev(&vector, tensor_vector_ce))))) {
				ZEPHIR_INIT_NVAR(&_2$$5);
				object_init_ex(&_2$$5, tensor_exceptions_invalidargumentexception_ce);
				ZEPHIR_INIT_NVAR(&_3$$5);
				zephir_gettype(&_3$$5, &vector);
				ZEPHIR_INIT_NVAR(&_4$$5);
				ZEPHIR_CONCAT_SSVS(&_4$$5, "Cannot stack a non", " vector, ", &_3$$5, " found.");
				ZEPHIR_CALL_METHOD(NULL, &_2$$5, "__construct", &_5, 3, &_4$$5);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_2$$5, "tensor/matrix.zep", 476);
				ZEPHIR_MM_RESTORE();
				return;
			}
			_6$$4 = columnwise;
			if (_6$$4) {
				_6$$4 = !((zephir_instance_of_ev(&vector, tensor_columnvector_ce)));
			}
			if (UNEXPECTED(_6$$4)) {
				ZEPHIR_INIT_NVAR(&_7$$6);
				object_init_ex(&_7$$6, tensor_exceptions_invalidargumentexception_ce);
				ZEPHIR_INIT_NVAR(&_8$$6);
				zephir_gettype(&_8$$6, &vector);
				ZEPHIR_INIT_NVAR(&_9$$6);
				ZEPHIR_CONCAT_SSVS(&_9$$6, "Cannot stack a non", " column vector, ", &_8$$6, " found.");
				ZEPHIR_CALL_METHOD(NULL, &_7$$6, "__construct", &_5, 3, &_9$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_7$$6, "tensor/matrix.zep", 481);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_10$$4, &vector, "size", NULL, 0);
			zephir_check_call_status();
			if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_10$$4, &size))) {
				ZEPHIR_INIT_NVAR(&_11$$7);
				object_init_ex(&_11$$7, tensor_exceptions_invalidargumentexception_ce);
				ZEPHIR_INIT_NVAR(&_12$$7);
				ZEPHIR_CONCAT_SS(&_12$$7, "Vectors must", " all be the same size.");
				ZEPHIR_CALL_METHOD(NULL, &_11$$7, "__construct", &_5, 3, &_12$$7);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_11$$7, "tensor/matrix.zep", 486);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_CALL_METHOD(&_13$$4, &vector, "asarray", NULL, 0);
			zephir_check_call_status();
			zephir_array_append(&a, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 489);
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
					object_init_ex(&_14$$9, tensor_exceptions_invalidargumentexception_ce);
					ZEPHIR_INIT_NVAR(&_15$$9);
					zephir_gettype(&_15$$9, &vector);
					ZEPHIR_INIT_NVAR(&_16$$9);
					ZEPHIR_CONCAT_SSVS(&_16$$9, "Cannot stack a non", " vector, ", &_15$$9, " found.");
					ZEPHIR_CALL_METHOD(NULL, &_14$$9, "__construct", &_5, 3, &_16$$9);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_14$$9, "tensor/matrix.zep", 476);
					ZEPHIR_MM_RESTORE();
					return;
				}
				_17$$8 = columnwise;
				if (_17$$8) {
					_17$$8 = !((zephir_instance_of_ev(&vector, tensor_columnvector_ce)));
				}
				if (UNEXPECTED(_17$$8)) {
					ZEPHIR_INIT_NVAR(&_18$$10);
					object_init_ex(&_18$$10, tensor_exceptions_invalidargumentexception_ce);
					ZEPHIR_INIT_NVAR(&_19$$10);
					zephir_gettype(&_19$$10, &vector);
					ZEPHIR_INIT_NVAR(&_20$$10);
					ZEPHIR_CONCAT_SSVS(&_20$$10, "Cannot stack a non", " column vector, ", &_19$$10, " found.");
					ZEPHIR_CALL_METHOD(NULL, &_18$$10, "__construct", &_5, 3, &_20$$10);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_18$$10, "tensor/matrix.zep", 481);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_21$$8, &vector, "size", NULL, 0);
				zephir_check_call_status();
				if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_21$$8, &size))) {
					ZEPHIR_INIT_NVAR(&_22$$11);
					object_init_ex(&_22$$11, tensor_exceptions_invalidargumentexception_ce);
					ZEPHIR_INIT_NVAR(&_23$$11);
					ZEPHIR_CONCAT_SS(&_23$$11, "Vectors must", " all be the same size.");
					ZEPHIR_CALL_METHOD(NULL, &_22$$11, "__construct", &_5, 3, &_23$$11);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_22$$11, "tensor/matrix.zep", 486);
					ZEPHIR_MM_RESTORE();
					return;
				}
				ZEPHIR_CALL_METHOD(&_24$$8, &vector, "asarray", NULL, 0);
				zephir_check_call_status();
				zephir_array_append(&a, &_24$$8, PH_SEPARATE, "tensor/matrix.zep", 489);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 */
PHP_METHOD(Tensor_Matrix, __construct) {

	zend_string *_6$$4;
	zend_ulong _5$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_2 = NULL, *_10 = NULL, *_13 = NULL, *_18 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, m, n;
	zend_bool validate, _16$$7, _22$$9, _35$$13, _40$$15;
	zval *a_param = NULL, *validate_param = NULL, i, rowA, valueA, _0, _46, _1$$4, *_3$$4, _4$$4, _7$$6, _8$$6, _9$$6, _11$$6, _12$$6, *_14$$5, _15$$5, _27$$5, _17$$7, _19$$8, _20$$8, _21$$8, _23$$9, _24$$10, _25$$10, _26$$10, _28$$12, _29$$12, _30$$12, _31$$12, _32$$12, *_33$$11, _34$$11, _45$$11, _36$$13, _37$$14, _38$$14, _39$$14, _41$$15, _42$$16, _43$$16, _44$$16;
	zval a;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_46);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_7$$6);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_27$$5);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$8);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_24$$10);
	ZVAL_UNDEF(&_25$$10);
	ZVAL_UNDEF(&_26$$10);
	ZVAL_UNDEF(&_28$$12);
	ZVAL_UNDEF(&_29$$12);
	ZVAL_UNDEF(&_30$$12);
	ZVAL_UNDEF(&_31$$12);
	ZVAL_UNDEF(&_32$$12);
	ZVAL_UNDEF(&_34$$11);
	ZVAL_UNDEF(&_45$$11);
	ZVAL_UNDEF(&_36$$13);
	ZVAL_UNDEF(&_37$$14);
	ZVAL_UNDEF(&_38$$14);
	ZVAL_UNDEF(&_39$$14);
	ZVAL_UNDEF(&_41$$15);
	ZVAL_UNDEF(&_42$$16);
	ZVAL_UNDEF(&_43$$16);
	ZVAL_UNDEF(&_44$$16);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &a_param, &validate_param);

	zephir_get_arrval(&a, a_param);
	if (!validate_param) {
		validate = 1;
	} else {
		validate = zephir_get_boolval(validate_param);
	}


	if (UNEXPECTED(ZEPHIR_IS_EMPTY(&a))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_invalidargumentexception_ce, "Matrix must contain at least 1 element.", "tensor/matrix.zep", 505);
		return;
	}
	m = zephir_fast_count_int(&a);
	ZEPHIR_CALL_FUNCTION(&_0, "current", NULL, 30, &a);
	zephir_check_call_status();
	n = zephir_fast_count_int(&_0);
	if (validate) {
		ZEPHIR_CALL_FUNCTION(&_1$$4, "array_values", &_2, 15, &a);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_1$$4);
		zephir_is_iterable(&a, 0, "tensor/matrix.zep", 534);
		if (Z_TYPE_P(&a) == IS_ARRAY) {
			ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&a), _5$$4, _6$$4, _3$$4)
			{
				ZEPHIR_INIT_NVAR(&i);
				if (_6$$4 != NULL) { 
					ZVAL_STR_COPY(&i, _6$$4);
				} else {
					ZVAL_LONG(&i, _5$$4);
				}
				ZEPHIR_INIT_NVAR(&rowA);
				ZVAL_COPY(&rowA, _3$$4);
				if (UNEXPECTED(zephir_fast_count_int(&rowA) != n)) {
					ZEPHIR_INIT_NVAR(&_7$$6);
					object_init_ex(&_7$$6, tensor_exceptions_invalidargumentexception_ce);
					ZVAL_LONG(&_8$$6, n);
					ZEPHIR_CALL_FUNCTION(&_9$$6, "strval", &_10, 4, &_8$$6);
					zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&_11$$6);
					ZVAL_LONG(&_11$$6, zephir_fast_count_int(&rowA));
					ZEPHIR_INIT_NVAR(&_12$$6);
					ZEPHIR_CONCAT_SSVSVSSVS(&_12$$6, "The number of columns", " must be equal for all rows, ", &_9$$6, " needed but ", &_11$$6, " given", " at row offset ", &i, ".");
					ZEPHIR_CALL_METHOD(NULL, &_7$$6, "__construct", &_13, 3, &_12$$6);
					zephir_check_call_status();
					zephir_throw_exception_debug(&_7$$6, "tensor/matrix.zep", 521);
					ZEPHIR_MM_RESTORE();
					return;
				}
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 532);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$5)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _14$$5);
						_16$$7 = !(Z_TYPE_P(&valueA) == IS_LONG);
						if (_16$$7) {
							ZEPHIR_CALL_FUNCTION(&_17$$7, "is_float", &_18, 2, &valueA);
							zephir_check_call_status();
							_16$$7 = !zephir_is_true(&_17$$7);
						}
						if (UNEXPECTED(_16$$7)) {
							ZEPHIR_INIT_NVAR(&_19$$8);
							object_init_ex(&_19$$8, tensor_exceptions_invalidargumentexception_ce);
							ZEPHIR_INIT_NVAR(&_20$$8);
							zephir_gettype(&_20$$8, &valueA);
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZEPHIR_CONCAT_SSVS(&_21$$8, "Matrix element must", " be an integer or floating point number, ", &_20$$8, " given.");
							ZEPHIR_CALL_METHOD(NULL, &_19$$8, "__construct", &_13, 3, &_21$$8);
							zephir_check_call_status();
							zephir_throw_exception_debug(&_19$$8, "tensor/matrix.zep", 528);
							ZEPHIR_MM_RESTORE();
							return;
						}
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
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							_22$$9 = !(Z_TYPE_P(&valueA) == IS_LONG);
							if (_22$$9) {
								ZEPHIR_CALL_FUNCTION(&_23$$9, "is_float", &_18, 2, &valueA);
								zephir_check_call_status();
								_22$$9 = !zephir_is_true(&_23$$9);
							}
							if (UNEXPECTED(_22$$9)) {
								ZEPHIR_INIT_NVAR(&_24$$10);
								object_init_ex(&_24$$10, tensor_exceptions_invalidargumentexception_ce);
								ZEPHIR_INIT_NVAR(&_25$$10);
								zephir_gettype(&_25$$10, &valueA);
								ZEPHIR_INIT_NVAR(&_26$$10);
								ZEPHIR_CONCAT_SSVS(&_26$$10, "Matrix element must", " be an integer or floating point number, ", &_25$$10, " given.");
								ZEPHIR_CALL_METHOD(NULL, &_24$$10, "__construct", &_13, 3, &_26$$10);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_24$$10, "tensor/matrix.zep", 528);
								ZEPHIR_MM_RESTORE();
								return;
							}
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				ZEPHIR_CALL_FUNCTION(&_27$$5, "array_values", &_2, 15, &rowA);
				zephir_check_call_status();
				zephir_array_append(&rowA, &_27$$5, PH_SEPARATE, "tensor/matrix.zep", 532);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, &a, "rewind", NULL, 0);
			zephir_check_call_status();
			while (1) {
				ZEPHIR_CALL_METHOD(&_4$$4, &a, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_4$$4)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&i, &a, "key", NULL, 0);
				zephir_check_call_status();
				ZEPHIR_CALL_METHOD(&rowA, &a, "current", NULL, 0);
				zephir_check_call_status();
					if (UNEXPECTED(zephir_fast_count_int(&rowA) != n)) {
						ZEPHIR_INIT_NVAR(&_28$$12);
						object_init_ex(&_28$$12, tensor_exceptions_invalidargumentexception_ce);
						ZVAL_LONG(&_29$$12, n);
						ZEPHIR_CALL_FUNCTION(&_30$$12, "strval", &_10, 4, &_29$$12);
						zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_31$$12);
						ZVAL_LONG(&_31$$12, zephir_fast_count_int(&rowA));
						ZEPHIR_INIT_NVAR(&_32$$12);
						ZEPHIR_CONCAT_SSVSVSSVS(&_32$$12, "The number of columns", " must be equal for all rows, ", &_30$$12, " needed but ", &_31$$12, " given", " at row offset ", &i, ".");
						ZEPHIR_CALL_METHOD(NULL, &_28$$12, "__construct", &_13, 3, &_32$$12);
						zephir_check_call_status();
						zephir_throw_exception_debug(&_28$$12, "tensor/matrix.zep", 521);
						ZEPHIR_MM_RESTORE();
						return;
					}
					zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 532);
					if (Z_TYPE_P(&rowA) == IS_ARRAY) {
						ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _33$$11)
						{
							ZEPHIR_INIT_NVAR(&valueA);
							ZVAL_COPY(&valueA, _33$$11);
							_35$$13 = !(Z_TYPE_P(&valueA) == IS_LONG);
							if (_35$$13) {
								ZEPHIR_CALL_FUNCTION(&_36$$13, "is_float", &_18, 2, &valueA);
								zephir_check_call_status();
								_35$$13 = !zephir_is_true(&_36$$13);
							}
							if (UNEXPECTED(_35$$13)) {
								ZEPHIR_INIT_NVAR(&_37$$14);
								object_init_ex(&_37$$14, tensor_exceptions_invalidargumentexception_ce);
								ZEPHIR_INIT_NVAR(&_38$$14);
								zephir_gettype(&_38$$14, &valueA);
								ZEPHIR_INIT_NVAR(&_39$$14);
								ZEPHIR_CONCAT_SSVS(&_39$$14, "Matrix element must", " be an integer or floating point number, ", &_38$$14, " given.");
								ZEPHIR_CALL_METHOD(NULL, &_37$$14, "__construct", &_13, 3, &_39$$14);
								zephir_check_call_status();
								zephir_throw_exception_debug(&_37$$14, "tensor/matrix.zep", 528);
								ZEPHIR_MM_RESTORE();
								return;
							}
						} ZEND_HASH_FOREACH_END();
					} else {
						ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
						zephir_check_call_status();
						while (1) {
							ZEPHIR_CALL_METHOD(&_34$$11, &rowA, "valid", NULL, 0);
							zephir_check_call_status();
							if (!zend_is_true(&_34$$11)) {
								break;
							}
							ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
							zephir_check_call_status();
								_40$$15 = !(Z_TYPE_P(&valueA) == IS_LONG);
								if (_40$$15) {
									ZEPHIR_CALL_FUNCTION(&_41$$15, "is_float", &_18, 2, &valueA);
									zephir_check_call_status();
									_40$$15 = !zephir_is_true(&_41$$15);
								}
								if (UNEXPECTED(_40$$15)) {
									ZEPHIR_INIT_NVAR(&_42$$16);
									object_init_ex(&_42$$16, tensor_exceptions_invalidargumentexception_ce);
									ZEPHIR_INIT_NVAR(&_43$$16);
									zephir_gettype(&_43$$16, &valueA);
									ZEPHIR_INIT_NVAR(&_44$$16);
									ZEPHIR_CONCAT_SSVS(&_44$$16, "Matrix element must", " be an integer or floating point number, ", &_43$$16, " given.");
									ZEPHIR_CALL_METHOD(NULL, &_42$$16, "__construct", &_13, 3, &_44$$16);
									zephir_check_call_status();
									zephir_throw_exception_debug(&_42$$16, "tensor/matrix.zep", 528);
									ZEPHIR_MM_RESTORE();
									return;
								}
							ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
							zephir_check_call_status();
						}
					}
					ZEPHIR_INIT_NVAR(&valueA);
					ZEPHIR_CALL_FUNCTION(&_45$$11, "array_values", &_2, 15, &rowA);
					zephir_check_call_status();
					zephir_array_append(&rowA, &_45$$11, PH_SEPARATE, "tensor/matrix.zep", 532);
				ZEPHIR_CALL_METHOD(NULL, &a, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&rowA);
		ZEPHIR_INIT_NVAR(&i);
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("a"), &a);
	ZEPHIR_INIT_ZVAL_NREF(_46);
	ZVAL_LONG(&_46, m);
	zephir_update_property_zval(this_ptr, ZEND_STRL("m"), &_46);
	ZEPHIR_INIT_ZVAL_NREF(_46);
	ZVAL_LONG(&_46, n);
	zephir_update_property_zval(this_ptr, ZEND_STRL("n"), &_46);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
	zephir_get_strval(&_1, &_0);
	ZEPHIR_OBS_VAR(&_2);
	zephir_read_property(&_2, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
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


	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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


	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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


	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, index);
	ZEPHIR_RETURN_CALL_FUNCTION("array_column", NULL, 31, &_0, &_1);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, diagonalAsVector) {

	zend_string *_8;
	zend_ulong _7;
	zval b;
	zval _0, i, rowA, _4, *_5, _6, _1$$3, _2$$3, _3$$3, _9$$4, _10$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Matrix must be", " square, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 655);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_4, 0, "tensor/matrix.zep", 666);
	if (Z_TYPE_P(&_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_4), _7, _8, _5)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_8 != NULL) { 
				ZVAL_STR_COPY(&i, _8);
			} else {
				ZVAL_LONG(&i, _7);
			}
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _5);
			zephir_array_fetch(&_9$$4, &rowA, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 663);
			zephir_array_append(&b, &_9$$4, PH_SEPARATE, "tensor/matrix.zep", 663);
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
			ZEPHIR_CALL_METHOD(&i, &_4, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowA, &_4, "current", NULL, 0);
			zephir_check_call_status();
				zephir_array_fetch(&_10$$5, &rowA, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 663);
				zephir_array_append(&b, &_10$$5, PH_SEPARATE, "tensor/matrix.zep", 663);
			ZEPHIR_CALL_METHOD(NULL, &_4, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", &_11, 0, &b);
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
	zephir_read_property(&_2, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_map", NULL, 14, &_0, &_2);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
			zephir_array_append(&vectors, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 701);
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

	zval _1, _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_1);
	zephir_read_property(&_2, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_3);
	ZVAL_STRING(&_3, "array_merge");
	ZEPHIR_CALL_USER_FUNC_ARRAY(&_1, &_3, &_2);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", &_0, 0, &_1);
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
	zval rowA, _0, *_1, _2, _3$$3, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 732);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&_3$$3);
			tensor_argmin(&_3$$3, &rowA);
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/matrix.zep", 729);
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
				ZEPHIR_INIT_NVAR(&_4$$4);
				tensor_argmin(&_4$$4, &rowA);
				zephir_array_append(&b, &_4$$4, PH_SEPARATE, "tensor/matrix.zep", 729);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_5, 0, &b);
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
	zval rowA, _0, *_1, _2, _3$$3, _4$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 750);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&_3$$3);
			tensor_argmax(&_3$$3, &rowA);
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/matrix.zep", 747);
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
				ZEPHIR_INIT_NVAR(&_4$$4);
				tensor_argmax(&_4$$4, &rowA);
				zephir_array_append(&b, &_4$$4, PH_SEPARATE, "tensor/matrix.zep", 747);
			ZEPHIR_CALL_METHOD(NULL, &_0, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_5, 0, &b);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 769);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_CALL_FUNCTION(&_3$$3, "array_map", &_4, 14, callback, &rowA);
			zephir_check_call_status();
			zephir_array_append(&b, &_3$$3, PH_SEPARATE, "tensor/matrix.zep", 766);
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
				ZEPHIR_CALL_FUNCTION(&_5$$4, "array_map", &_4, 14, callback, &rowA);
				zephir_check_call_status();
				zephir_array_append(&b, &_5$$4, PH_SEPARATE, "tensor/matrix.zep", 766);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 785);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CPY_WRT(&carry, initial);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 798);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 796);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 796);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
			zephir_read_property(&_4$$3, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			ZVAL_LONG(&_5$$3, i);
			ZEPHIR_CALL_FUNCTION(&_6$$3, "array_column", &_7, 31, &_4$$3, &_5$$3);
			zephir_check_call_status();
			zephir_array_append(&b, &_6$$3, PH_SEPARATE, "tensor/matrix.zep", 813);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the inverse of the square matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, inverse) {

	zval _0, _4, _5, _1$$3, _2$$3, _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Matrix must be", " square, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 828);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_4);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_inverse(&_4, &_5);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the (Moore-Penrose) pseudoinverse of the general matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, pseudoinverse) {

	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	tensor_pseudoinverse(&_0, &_1);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the determinant of the matrix.
 *
 * @throws \Tensor\Exceptions\RuntimeException
 * @return int|float
 */
PHP_METHOD(Tensor_Matrix, det) {

	zval _0, ref, pi, _4, _5, _6, _7, _8, _1$$3, _2$$3, _3$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&pi);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_CALL_METHOD(&_2$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Matrix must be", " square, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 854);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&ref, this_ptr, "ref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, &ref, "a", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, &_4, "diagonalasvector", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&pi, &_5, "product", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_6);
	ZEPHIR_CALL_METHOD(&_7, &ref, "swaps", NULL, 0);
	zephir_check_call_status();
	ZVAL_DOUBLE(&_8, -1.0);
	zephir_pow_function(&_6, &_8, &_7);
	mul_function(return_value, &pi, &_6);
	RETURN_MM();

}

/**
 * Calculate the rank of the matrix i.e the number of pivots in its reduced row echelon form.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, rank) {

	zval a, _3;
	zval rowA, valueA, _0, _1, _2, *_4, _5, *_6$$3, _7$$3, *_8$$8, _9$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, pivots;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_9$$8);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "rref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "a", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_2, &_1, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_3, &_2);
	ZEPHIR_CPY_WRT(&a, &_3);
	pivots = 0;
	zephir_is_iterable(&a, 0, "tensor/matrix.zep", 889);
	if (Z_TYPE_P(&a) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&a), _4)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _4);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 887);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _6$$3);
					if (!ZEPHIR_IS_LONG(&valueA, 0)) {
						pivots++;
						continue;
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_7$$3, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_7$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						if (!ZEPHIR_IS_LONG(&valueA, 0)) {
							pivots++;
							continue;
						}
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &a, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_5, &a, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_5)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, &a, "current", NULL, 0);
			zephir_check_call_status();
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 887);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _8$$8);
						if (!ZEPHIR_IS_LONG(&valueA, 0)) {
							pivots++;
							continue;
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_9$$8, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_9$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							if (!ZEPHIR_IS_LONG(&valueA, 0)) {
								pivots++;
								continue;
							}
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
			ZEPHIR_CALL_METHOD(NULL, &a, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
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
	ZEPHIR_CALL_FUNCTION(&_2, "min", NULL, 19, &_1);
	zephir_check_call_status();
	RETURN_MM_BOOL(ZEPHIR_IS_IDENTICAL(&_0, &_2));

}

/**
 * Is the matrix symmetric i.e. is it equal to its transpose.
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
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
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
			zephir_read_property(&_5$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch_long(&rowA, &_5$$4, i, PH_NOISY, "tensor/matrix.zep", 918);
			zephir_read_property(&_6$$4, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
					zephir_array_fetch_long(&_10$$5, &rowA, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 921);
					zephir_read_property(&_11$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch_long(&_12$$5, &_11$$5, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 921);
					zephir_array_fetch_long(&_13$$5, &_12$$5, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 921);
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
 * Is the matrix positive definite i.e. do all of its principal minor matrices have a determinant greater than 0.
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, positiveDefinite) {

	zend_bool _2;
	zval _0, _1, _4, b$$4, _5$$4, _6$$4, _7$$4, _8$$4, _10$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&b$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_10$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "symmetric", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
			ZVAL_LONG(&_6$$4, 0);
			ZVAL_LONG(&_7$$4, i);
			ZVAL_LONG(&_8$$4, i);
			ZEPHIR_CALL_METHOD(&b$$4, this_ptr, "submatrix", &_9, 0, &_5$$4, &_6$$4, &_7$$4, &_8$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_10$$4, &b$$4, "det", &_11, 0);
			zephir_check_call_status();
			if (ZEPHIR_LE_LONG(&_10$$4, 0)) {
				RETURN_MM_BOOL(0);
			}
		}
	}
	RETURN_MM_BOOL(1);

}

/**
 * Is the matrix positive semidefinite i.e. do all of its principal minor matrices have a determinant greater or equal to 0.
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, positiveSemidefinite) {

	zend_bool _2;
	zval _0, _1, _4, b$$4, _5$$4, _6$$4, _7$$4, _8$$4, _10$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, _3;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&b$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_10$$4);

	ZEPHIR_MM_GROW();

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "symmetric", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
			ZVAL_LONG(&_6$$4, 0);
			ZVAL_LONG(&_7$$4, i);
			ZVAL_LONG(&_8$$4, i);
			ZEPHIR_CALL_METHOD(&b$$4, this_ptr, "submatrix", &_9, 0, &_5$$4, &_6$$4, &_7$$4, &_8$$4);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&_10$$4, &b$$4, "det", &_11, 0);
			zephir_check_call_status();
			if (ZEPHIR_LT_LONG(&_10$$4, 0)) {
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, matmul) {

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
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 990);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property(&_9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_matmul(&_8, &_9, &_10);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_8);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the dot product of this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 1008);
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
 * Return the 2D convolution of this matrix and a kernel matrix with given stride using the "same" method for zero padding.
 *
 * @param \Tensor\Matrix b
 * @param int stride
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, convolve) {

	zval _6$$3;
	zend_bool _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long stride, ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, *stride_param = NULL, _0, _1, _3, _4, _11, _12, _13, _14, _5$$3, _7$$4, _8$$4, _9$$4, _10$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_6$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &b, &stride_param);

	if (!stride_param) {
		stride = 1;
	} else {
		stride = zephir_get_intval(stride_param);
	}


	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	_2 = ZEPHIR_GT(&_0, &_1);
	if (!(_2)) {
		ZEPHIR_CALL_METHOD(&_3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_4, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
		_2 = ZEPHIR_GT(&_3, &_4);
	}
	if (UNEXPECTED(_2)) {
		ZEPHIR_INIT_VAR(&_5$$3);
		object_init_ex(&_5$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_6$$3);
		ZEPHIR_CONCAT_SS(&_6$$3, "Matrix B cannot be", " larger than Matrix A.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$3, "__construct", NULL, 3, &_6$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$3, "tensor/matrix.zep", 1026);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(stride < 1)) {
		ZEPHIR_INIT_VAR(&_7$$4);
		object_init_ex(&_7$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_8$$4, stride);
		ZEPHIR_CALL_FUNCTION(&_9$$4, "strval", NULL, 4, &_8$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_10$$4);
		ZEPHIR_CONCAT_SSVS(&_10$$4, "Stride cannot be", " less than 1, ", &_9$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_7$$4, "__construct", NULL, 3, &_10$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_7$$4, "tensor/matrix.zep", 1031);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_11);
	zephir_read_property(&_12, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_13, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZVAL_LONG(&_14, stride);
	tensor_convolve_2d(&_11, &_12, &_13, &_14);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_11);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the row echelon form (REF) of the matrix. Return the reduced
 * matrix and the number of swaps needed to compute the REF.
 *
 * @return \Tensor\Reductions\Ref
 */
PHP_METHOD(Tensor_Matrix, ref) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_reductions_ref_ce, "reduce", &_0, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the reduced row echelon (RREF) form of the matrix.
 *
 * @return \Tensor\Reductions\Rref
 */
PHP_METHOD(Tensor_Matrix, rref) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_reductions_rref_ce, "reduce", &_0, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the LU decomposition of the matrix in a tuple where l is
 * the lower triangular matrix, u is the upper triangular matrix,
 * and p is the permutation matrix.
 *
 * @return \Tensor\Decompositions\Lu
 */
PHP_METHOD(Tensor_Matrix, lu) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_lu_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the lower triangular matrix of the Cholesky decomposition.
 * 
 * @return \Tensor\Decompositions\Cholesky;
 */
PHP_METHOD(Tensor_Matrix, cholesky) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_cholesky_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the eigenvalues and eigenvectors of the matrix and return them in a tuple.
 *
 * @param bool symmetric
 * @return \Tensor\Decompositions\Eigen
 */
PHP_METHOD(Tensor_Matrix, eig) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *symmetric_param = NULL, _1;
	zend_bool symmetric;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &symmetric_param);

	if (!symmetric_param) {
		symmetric = 0;
	} else {
		symmetric = zephir_get_boolval(symmetric_param);
	}


	if (symmetric) {
		ZVAL_BOOL(&_1, 1);
	} else {
		ZVAL_BOOL(&_1, 0);
	}
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_eigen_ce, "decompose", &_0, 0, this_ptr, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the singluar value decomposition of this matrix.
 *
 * @return \Tensor\Decompositions\Svd
 */
PHP_METHOD(Tensor_Matrix, svd) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_svd_ce, "decompose", &_0, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();

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
	zval *b, b_sub, lu, _0, _1, _3, _4, _6, _7, _8, _10, _11, _12, _13, _14, _16, _31, _32, _49, _15$$4, _27$$5, _28$$5, _29$$5, _30$$5, _23$$6, _24$$6, _25$$6, _26$$6, _33$$8, _44$$9, _45$$9, _46$$9, _47$$9, _40$$10, _41$$10, _42$$10, _43$$10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&lu);
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
	ZEPHIR_CALL_METHOD(&lu, this_ptr, "lu", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_0, &lu, "l", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, &_0, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_2, &_1);
	ZEPHIR_CPY_WRT(&l, &_2);
	ZEPHIR_CALL_METHOD(&_3, &lu, "u", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_5, &_4);
	ZEPHIR_CPY_WRT(&u, &_5);
	ZEPHIR_CALL_METHOD(&_6, &lu, "p", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, &_6, "dot", NULL, 0, b);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, &_7, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_9, &_8);
	ZEPHIR_CPY_WRT(&pb, &_9);
	zephir_read_property(&_10, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	k = ((zephir_get_numberval(&_10) - 1));
	ZEPHIR_INIT_VAR(&y);
	zephir_create_array(&y, 1, 0);
	zephir_array_fetch_long(&_11, &pb, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1125);
	ZEPHIR_INIT_VAR(&_12);
	zephir_array_fetch_long(&_13, &l, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1125);
	zephir_array_fetch_long(&_14, &_13, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1125);
	if (!(zephir_is_true(&_14))) {
		ZEPHIR_INIT_NVAR(&_12);
		ZVAL_DOUBLE(&_12, 0.00000001);
	} else {
		zephir_array_fetch_long(&_15$$4, &l, 0, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1125);
		ZEPHIR_OBS_NVAR(&_12);
		zephir_array_fetch_long(&_12, &_15$$4, 0, PH_NOISY, "tensor/matrix.zep", 1125);
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
					zephir_array_fetch_long(&_23$$6, &l, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1131);
					zephir_array_fetch_long(&_24$$6, &_23$$6, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1131);
					zephir_array_fetch_long(&_25$$6, &y, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1131);
					ZEPHIR_INIT_NVAR(&_26$$6);
					mul_function(&_26$$6, &_24$$6, &_25$$6);
					sigma += zephir_get_numberval(&_26$$6);
				}
			}
			zephir_array_fetch_long(&_27$$5, &pb, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1134);
			zephir_array_fetch_long(&_28$$5, &l, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1134);
			zephir_array_fetch_long(&_29$$5, &_28$$5, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1134);
			ZEPHIR_INIT_NVAR(&_30$$5);
			ZVAL_DOUBLE(&_30$$5, zephir_safe_div_double_zval(((zephir_get_numberval(&_27$$5) - sigma)), &_29$$5));
			zephir_array_append(&y, &_30$$5, PH_SEPARATE, "tensor/matrix.zep", 1134);
		}
	}
	ZEPHIR_INIT_VAR(&x);
	zephir_create_array(&x, 1, 0);
	zephir_array_fetch_long(&_11, &y, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1137);
	ZEPHIR_INIT_NVAR(&_12);
	zephir_array_fetch_long(&_31, &l, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1137);
	zephir_array_fetch_long(&_32, &_31, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1137);
	if (!(zephir_is_true(&_32))) {
		ZEPHIR_INIT_NVAR(&_12);
		ZVAL_DOUBLE(&_12, 0.00000001);
	} else {
		zephir_array_fetch_long(&_33$$8, &l, k, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1137);
		ZEPHIR_OBS_NVAR(&_12);
		zephir_array_fetch_long(&_12, &_33$$8, k, PH_NOISY, "tensor/matrix.zep", 1137);
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
					zephir_array_fetch_long(&_40$$10, &u, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1143);
					zephir_array_fetch_long(&_41$$10, &_40$$10, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1143);
					zephir_array_fetch_long(&_42$$10, &x, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1143);
					ZEPHIR_INIT_NVAR(&_43$$10);
					mul_function(&_43$$10, &_41$$10, &_42$$10);
					sigma += zephir_get_numberval(&_43$$10);
				}
			}
			zephir_array_fetch_long(&_44$$9, &y, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1146);
			zephir_array_fetch_long(&_45$$9, &u, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1146);
			zephir_array_fetch_long(&_46$$9, &_45$$9, i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1146);
			ZEPHIR_INIT_NVAR(&_47$$9);
			ZVAL_DOUBLE(&_47$$9, zephir_safe_div_double_zval(((zephir_get_numberval(&_44$$9) - sigma)), &_46$$9));
			zephir_array_update_long(&x, i, &_47$$9, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_49, "array_reverse", NULL, 32, &x);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, multiply) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplycolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot multiply", " matrix by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1222);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to divide this matrix by another tensor sdfsdfelement-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, divide) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividecolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot divide", " matrix by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1255);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to add this matrix with another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, add) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot add", " matrix with the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1289);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to subtract this matrix from another tensor
 * element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, subtract) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot multiply", " matrix by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1323);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to raise this matrix to the power of another
 * tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, pow) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot raise", " matrix to the power of the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1357);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the integer modulus of this matrix
 * and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, mod) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot mod", " matrix with the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1391);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the equality comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, equal) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1425);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the not equal comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, notEqual) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1459);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, greater) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatercolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1493);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the greater than or equal to
 * comparison of this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, greaterEqual) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1527);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than comparison of
 * this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, less) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lesscolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1561);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * A universal function to compute the less than or equal to
 * comparison of this matrix and another tensor element-wise.
 *
 * @param mixed b
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return mixed
 */
PHP_METHOD(Tensor_Matrix, lessEqual) {

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
				if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) {
					ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalcolumnvector", NULL, 0, b);
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
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1595);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	zephir_read_property(&_2, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();


	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, this_ptr);
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

	zval rowB, b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_8 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *base_param = NULL, _0$$3, rowA, valueA, _1, *_2, _3, *_4$$4, _5$$4, _6$$5, _7$$5, _9$$6, _10$$6, *_11$$7, _12$$7, _13$$8, _14$$8, _15$$9, _16$$9;
	double base;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$9);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&rowB);
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
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_1, 0, "tensor/matrix.zep", 1686);
	if (Z_TYPE_P(&_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_1), _2)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _2);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 1683);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _4$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _4$$4);
					ZVAL_DOUBLE(&_6$$5, base);
					ZEPHIR_CALL_FUNCTION(&_7$$5, "log", &_8, 8, &valueA, &_6$$5);
					zephir_check_call_status();
					zephir_array_append(&rowB, &_7$$5, PH_SEPARATE, "tensor/matrix.zep", 1680);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_5$$4, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_5$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZVAL_DOUBLE(&_9$$6, base);
						ZEPHIR_CALL_FUNCTION(&_10$$6, "log", &_8, 8, &valueA, &_9$$6);
						zephir_check_call_status();
						zephir_array_append(&rowB, &_10$$6, PH_SEPARATE, "tensor/matrix.zep", 1680);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1683);
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
			ZEPHIR_CALL_METHOD(&rowA, &_1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 1683);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$7);
						ZVAL_DOUBLE(&_13$$8, base);
						ZEPHIR_CALL_FUNCTION(&_14$$8, "log", &_8, 8, &valueA, &_13$$8);
						zephir_check_call_status();
						zephir_array_append(&rowB, &_14$$8, PH_SEPARATE, "tensor/matrix.zep", 1680);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_12$$7, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_12$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZVAL_DOUBLE(&_15$$9, base);
							ZEPHIR_CALL_FUNCTION(&_16$$9, "log", &_8, 8, &valueA, &_15$$9);
							zephir_check_call_status();
							zephir_array_append(&rowB, &_16$$9, PH_SEPARATE, "tensor/matrix.zep", 1680);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1683);
			ZEPHIR_CALL_METHOD(NULL, &_1, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "array_sum");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 14, &_2, &_1);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "array_product");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 14, &_2, &_1);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "min");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 14, &_2, &_1);
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

	zephir_read_property(&_1, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "max");
	ZEPHIR_CALL_FUNCTION(&_3, "array_map", NULL, 14, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_0, 0, &_3);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the means of each row and return them in a vector.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, mean) {

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
	ZEPHIR_RETURN_CALL_METHOD(&_0, "dividescalar", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the median vector of this matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, median) {

	zend_bool odd;
	zval b;
	zval rowA, median, _0, _1, _2, _3, *_4, _5, _7$$5, _8$$5, _9$$5, _10$$8, _11$$8, _12$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_13 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, mid;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&median);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$8);
	ZVAL_UNDEF(&_11$$8);
	ZVAL_UNDEF(&_12$$8);
	ZVAL_UNDEF(&b);

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_0, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 2);
	ZEPHIR_CALL_FUNCTION(&_2, "intdiv", NULL, 21, &_0, &_1);
	zephir_check_call_status();
	mid = zephir_get_intval(&_2);
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	odd = zephir_safe_mod_zval_long(&_1, 2) == 1;
	zephir_read_property(&_3, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_3, 0, "tensor/matrix.zep", 1855);
	if (Z_TYPE_P(&_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_3), _4)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _4);
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_6, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			if (odd) {
				ZEPHIR_OBS_NVAR(&median);
				zephir_array_fetch_long(&median, &rowA, mid, PH_NOISY, "tensor/matrix.zep", 1847);
			} else {
				zephir_array_fetch_long(&_7$$5, &rowA, (mid - 1), PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1849);
				zephir_array_fetch_long(&_8$$5, &rowA, mid, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1849);
				ZEPHIR_INIT_NVAR(&_9$$5);
				zephir_add_function(&_9$$5, &_7$$5, &_8$$5);
				ZEPHIR_INIT_NVAR(&median);
				ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_9$$5, 2.0));
			}
			zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1852);
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
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_6, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				if (odd) {
					ZEPHIR_OBS_NVAR(&median);
					zephir_array_fetch_long(&median, &rowA, mid, PH_NOISY, "tensor/matrix.zep", 1847);
				} else {
					zephir_array_fetch_long(&_10$$8, &rowA, (mid - 1), PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1849);
					zephir_array_fetch_long(&_11$$8, &rowA, mid, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1849);
					ZEPHIR_INIT_NVAR(&_12$$8);
					zephir_add_function(&_12$$8, &_10$$8, &_11$$8);
					ZEPHIR_INIT_NVAR(&median);
					ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_12$$8, 2.0));
				}
				zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1852);
			ZEPHIR_CALL_METHOD(NULL, &_3, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_13, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the q'th quantile of this matrix.
 *
 * @param float q
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, quantile) {

	zval b;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_16 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, xHat;
	zval *q_param = NULL, rowA, _5, _6, *_7, _8, _1$$3, _2$$3, _3$$3, _4$$3, _10$$4, _11$$4, _12$$4, _13$$5, _14$$5, _15$$5;
	double q, t = 0, x, remainder;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&b);

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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Q must be between", " 0 and 1, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1869);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	x = ((q * (double) ((zephir_get_numberval(&_5) - 1))) + (double) (1));
	xHat = (int) (x);
	remainder = (x -  (double) xHat);
	zephir_read_property(&_6, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 1891);
	if (Z_TYPE_P(&_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_6), _7)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _7);
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_9, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(&_10$$4);
			zephir_array_fetch_long(&_10$$4, &rowA, (xHat - 1), PH_NOISY, "tensor/matrix.zep", 1886);
			t = zephir_get_doubleval(&_10$$4);
			zephir_array_fetch_long(&_11$$4, &rowA, xHat, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1888);
			ZEPHIR_INIT_NVAR(&_12$$4);
			ZVAL_DOUBLE(&_12$$4, (t + (remainder * ((zephir_get_numberval(&_11$$4) - t)))));
			zephir_array_append(&b, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 1888);
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
			ZEPHIR_CALL_METHOD(&rowA, &_6, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_9, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_13$$5);
				zephir_array_fetch_long(&_13$$5, &rowA, (xHat - 1), PH_NOISY, "tensor/matrix.zep", 1886);
				t = zephir_get_doubleval(&_13$$5);
				zephir_array_fetch_long(&_14$$5, &rowA, xHat, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 1888);
				ZEPHIR_INIT_NVAR(&_15$$5);
				ZVAL_DOUBLE(&_15$$5, (t + (remainder * ((zephir_get_numberval(&_14$$5) - t)))));
				zephir_array_append(&b, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 1888);
			ZEPHIR_CALL_METHOD(NULL, &_6, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", &_16, 0, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the row variance of the matrix.
 *
 * @param \Tensor\ColumnVector|null mean
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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
		if (UNEXPECTED(!((zephir_instance_of_ev(mean, tensor_columnvector_ce))))) {
			ZEPHIR_INIT_VAR(&_0$$4);
			object_init_ex(&_0$$4, tensor_exceptions_invalidargumentexception_ce);
			ZEPHIR_INIT_VAR(&_1$$4);
			zephir_gettype(&_1$$4, mean);
			ZEPHIR_INIT_VAR(&_2$$4);
			ZEPHIR_CONCAT_SSVS(&_2$$4, "Mean must be a", " column vector ", &_1$$4, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_0$$4, "__construct", NULL, 3, &_2$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_0$$4, "tensor/matrix.zep", 1907);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_3$$3, mean, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_4$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
		if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_3$$3, &_4$$3))) {
			ZEPHIR_INIT_VAR(&_5$$5);
			object_init_ex(&_5$$5, tensor_exceptions_dimensionalitymismatch_ce);
			ZEPHIR_OBS_VAR(&_6$$5);
			zephir_read_property(&_6$$5, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
			zephir_get_strval(&_7$$5, &_6$$5);
			ZEPHIR_CALL_METHOD(&_8$$5, mean, "m", NULL, 0);
			zephir_check_call_status();
			zephir_get_strval(&_9$$5, &_8$$5);
			ZEPHIR_INIT_VAR(&_10$$5);
			ZEPHIR_CONCAT_SSVSVS(&_10$$5, "Mean vector must", " have ", &_7$$5, " rows, ", &_9$$5, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_5$$5, "__construct", NULL, 3, &_10$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_5$$5, "tensor/matrix.zep", 1913);
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(mean, this_ptr, "mean", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&_11, this_ptr, "subtractcolumnvector", NULL, 0, mean);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_12, &_11, "square", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_13, &_12, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_14, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_13, "dividescalar", NULL, 0, &_14);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the covariance of the matrix.
 *
 * @param \Tensor\ColumnVector mean
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, covariance) {

	zval _4$$4, _6$$4, _7$$4;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *mean = NULL, mean_sub, __$null, _0$$3, _1$$3, _2$$4, _3$$4, _5$$4, b, _8, _9, _10;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&mean_sub);
	ZVAL_NULL(&__$null);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &mean);

	if (!mean) {
		mean = &mean_sub;
		ZEPHIR_CPY_WRT(mean, &__$null);
	} else {
		ZEPHIR_SEPARATE_PARAM(mean);
	}


	if (!(Z_TYPE_P(mean) == IS_NULL)) {
		ZEPHIR_CALL_METHOD(&_0$$3, mean, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_1$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
		if (!ZEPHIR_IS_IDENTICAL(&_0$$3, &_1$$3)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, tensor_exceptions_dimensionalitymismatch_ce);
			ZEPHIR_OBS_VAR(&_3$$4);
			zephir_read_property(&_3$$4, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
			zephir_get_strval(&_4$$4, &_3$$4);
			ZEPHIR_CALL_METHOD(&_5$$4, mean, "m", NULL, 0);
			zephir_check_call_status();
			zephir_get_strval(&_6$$4, &_5$$4);
			ZEPHIR_INIT_VAR(&_7$$4);
			ZEPHIR_CONCAT_SSVSVS(&_7$$4, "Mean vector must", " have ", &_4$$4, " rows, ", &_6$$4, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 3, &_7$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$4, "tensor/matrix.zep", 1938);
			ZEPHIR_MM_RESTORE();
			return;
		}
	} else {
		ZEPHIR_CALL_METHOD(mean, this_ptr, "mean", NULL, 0);
		zephir_check_call_status();
	}
	ZEPHIR_CALL_METHOD(&b, this_ptr, "subtractcolumnvector", NULL, 0, mean);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, &b, "transpose", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_8, &b, "matmul", NULL, 0, &_9);
	zephir_check_call_status();
	zephir_read_property(&_10, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_8, "dividescalar", NULL, 0, &_10);
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
	zval *precision_param = NULL, _0$$3, _1$$4, _2$$4, _3$$4, _4$$4, rowA, valueA, _5, *_6, _7, *_8$$5, _9$$5, _10$$6, _11$$6, _12$$7, _13$$7, *_14$$8, _15$$8, _16$$9, _17$$9, _18$$10, _19$$10;
	zend_long precision, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$4);
	ZVAL_UNDEF(&_2$$4);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&_16$$9);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$10);
	ZVAL_UNDEF(&_19$$10);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

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
		zephir_throw_exception_debug(&_1$$4, "tensor/matrix.zep", 1964);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 1982);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 1979);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _8$$5)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$5);
					ZEPHIR_INIT_NVAR(&_10$$6);
					ZVAL_LONG(&_11$$6, precision);
					zephir_round(&_10$$6, &valueA, &_11$$6, NULL);
					zephir_array_append(&rowB, &_10$$6, PH_SEPARATE, "tensor/matrix.zep", 1976);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_9$$5, &rowA, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_9$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_12$$7);
						ZVAL_LONG(&_13$$7, precision);
						zephir_round(&_12$$7, &valueA, &_13$$7, NULL);
						zephir_array_append(&rowB, &_12$$7, PH_SEPARATE, "tensor/matrix.zep", 1976);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1979);
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
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 1979);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _14$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _14$$8);
						ZEPHIR_INIT_NVAR(&_16$$9);
						ZVAL_LONG(&_17$$9, precision);
						zephir_round(&_16$$9, &valueA, &_17$$9, NULL);
						zephir_array_append(&rowB, &_16$$9, PH_SEPARATE, "tensor/matrix.zep", 1976);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowA, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_15$$8, &rowA, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_15$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, &rowA, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_18$$10);
							ZVAL_LONG(&_19$$10, precision);
							zephir_round(&_18$$10, &valueA, &_19$$10, NULL);
							zephir_array_append(&rowB, &_18$$10, PH_SEPARATE, "tensor/matrix.zep", 1976);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1979);
			ZEPHIR_CALL_METHOD(NULL, &_5, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
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


	if (UNEXPECTED(min > max)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_1$$3);
		ZEPHIR_CONCAT_SS(&_1$$3, "Minimum cannot be", " greater than maximum.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_1$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 2018);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property(&_2, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_2, 0, "tensor/matrix.zep", 2048);
	if (Z_TYPE_P(&_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_2), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2045);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _5$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _5$$4);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_7$$6);
						ZVAL_DOUBLE(&_7$$6, max);
						zephir_array_append(&rowB, &_7$$6, PH_SEPARATE, "tensor/matrix.zep", 2031);
						continue;
					}
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_8$$7);
						ZVAL_DOUBLE(&_8$$7, min);
						zephir_array_append(&rowB, &_8$$7, PH_SEPARATE, "tensor/matrix.zep", 2037);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2042);
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
							zephir_array_append(&rowB, &_9$$9, PH_SEPARATE, "tensor/matrix.zep", 2031);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_10$$10);
							ZVAL_DOUBLE(&_10$$10, min);
							zephir_array_append(&rowB, &_10$$10, PH_SEPARATE, "tensor/matrix.zep", 2037);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2042);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2045);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2045);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$11)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$11);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_13$$13);
							ZVAL_DOUBLE(&_13$$13, max);
							zephir_array_append(&rowB, &_13$$13, PH_SEPARATE, "tensor/matrix.zep", 2031);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_14$$14);
							ZVAL_DOUBLE(&_14$$14, min);
							zephir_array_append(&rowB, &_14$$14, PH_SEPARATE, "tensor/matrix.zep", 2037);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2042);
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
								zephir_array_append(&rowB, &_15$$16, PH_SEPARATE, "tensor/matrix.zep", 2031);
								continue;
							}
							if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
								ZEPHIR_INIT_NVAR(&_16$$17);
								ZVAL_DOUBLE(&_16$$17, min);
								zephir_array_append(&rowB, &_16$$17, PH_SEPARATE, "tensor/matrix.zep", 2037);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2042);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2045);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2080);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2077);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_DOUBLE(&_5$$5, min);
						zephir_array_append(&rowB, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2069);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2074);
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
							zephir_array_append(&rowB, &_6$$7, PH_SEPARATE, "tensor/matrix.zep", 2069);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2074);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2077);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2077);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _7$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _7$$8);
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_DOUBLE(&_9$$10, min);
							zephir_array_append(&rowB, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2069);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2074);
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
								zephir_array_append(&rowB, &_10$$12, PH_SEPARATE, "tensor/matrix.zep", 2069);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2074);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2077);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2112);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2109);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_DOUBLE(&_5$$5, max);
						zephir_array_append(&rowB, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2101);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2106);
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
							zephir_array_append(&rowB, &_6$$7, PH_SEPARATE, "tensor/matrix.zep", 2101);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2106);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2109);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2109);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _7$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _7$$8);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_DOUBLE(&_9$$10, max);
							zephir_array_append(&rowB, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2101);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2106);
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
								zephir_array_append(&rowB, &_10$$12, PH_SEPARATE, "tensor/matrix.zep", 2101);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2106);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2109);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2143);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2140);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					if (ZEPHIR_GT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_5$$5);
						ZVAL_LONG(&_5$$5, 1);
						zephir_array_append(&rowB, &_5$$5, PH_SEPARATE, "tensor/matrix.zep", 2132);
					} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_6$$6);
						ZVAL_LONG(&_6$$6, -1);
						zephir_array_append(&rowB, &_6$$6, PH_SEPARATE, "tensor/matrix.zep", 2134);
					} else {
						ZEPHIR_INIT_NVAR(&_7$$7);
						ZVAL_LONG(&_7$$7, 0);
						zephir_array_append(&rowB, &_7$$7, PH_SEPARATE, "tensor/matrix.zep", 2136);
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
							zephir_array_append(&rowB, &_8$$9, PH_SEPARATE, "tensor/matrix.zep", 2132);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_9$$10);
							ZVAL_LONG(&_9$$10, -1);
							zephir_array_append(&rowB, &_9$$10, PH_SEPARATE, "tensor/matrix.zep", 2134);
						} else {
							ZEPHIR_INIT_NVAR(&_10$$11);
							ZVAL_LONG(&_10$$11, 0);
							zephir_array_append(&rowB, &_10$$11, PH_SEPARATE, "tensor/matrix.zep", 2136);
						}
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2140);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2140);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _11$$12)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _11$$12);
						if (ZEPHIR_GT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_13$$14);
							ZVAL_LONG(&_13$$14, 1);
							zephir_array_append(&rowB, &_13$$14, PH_SEPARATE, "tensor/matrix.zep", 2132);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_14$$15);
							ZVAL_LONG(&_14$$15, -1);
							zephir_array_append(&rowB, &_14$$15, PH_SEPARATE, "tensor/matrix.zep", 2134);
						} else {
							ZEPHIR_INIT_NVAR(&_15$$16);
							ZVAL_LONG(&_15$$16, 0);
							zephir_array_append(&rowB, &_15$$16, PH_SEPARATE, "tensor/matrix.zep", 2136);
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
								zephir_array_append(&rowB, &_16$$18, PH_SEPARATE, "tensor/matrix.zep", 2132);
							} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
								ZEPHIR_INIT_NVAR(&_17$$19);
								ZVAL_LONG(&_17$$19, -1);
								zephir_array_append(&rowB, &_17$$19, PH_SEPARATE, "tensor/matrix.zep", 2134);
							} else {
								ZEPHIR_INIT_NVAR(&_18$$20);
								ZVAL_LONG(&_18$$20, 0);
								zephir_array_append(&rowB, &_18$$20, PH_SEPARATE, "tensor/matrix.zep", 2136);
							}
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2140);
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
	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_0, 0, "tensor/matrix.zep", 2168);
	if (Z_TYPE_P(&_0) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0), _1)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _1);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2165);
			if (Z_TYPE_P(&rowA) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _3$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _3$$3);
					zephir_negate(&valueA);
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2162);
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
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2162);
					ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2165);
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
				zephir_is_iterable(&rowA, 0, "tensor/matrix.zep", 2165);
				if (Z_TYPE_P(&rowA) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowA), _5$$6)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _5$$6);
						zephir_negate(&valueA);
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2162);
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
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 2162);
						ZEPHIR_CALL_METHOD(NULL, &rowA, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2165);
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
 * Insert a smaller matrix b into this matrix.
 * 
 * @param \Tensor\Matrix b
 * @param int rowOffset
 * @param int columnOffset
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, insert) {

	zend_string *_19, *_23$$5, *_27$$8;
	zend_ulong _18, _22$$5, _26$$8;
	zval c, _14;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long rowOffset, columnOffset, ZEPHIR_LAST_CALL_STATUS, ii = 0, jj = 0;
	zval *b, b_sub, *rowOffset_param = NULL, *columnOffset_param = NULL, _0, _1, _7, _8, i, j, rowB, valueB, _13, _15, *_16, _17, _2$$3, _3$$3, _4$$3, _6$$3, _9$$4, _10$$4, _11$$4, _12$$4, *_20$$5, _21$$5, *_24$$8, _25$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&j);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_14);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &b, &rowOffset_param, &columnOffset_param);

	rowOffset = zephir_get_intval(rowOffset_param);
	columnOffset = zephir_get_intval(columnOffset_param);


	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_1, (zephir_get_numberval(&_0) + rowOffset))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_3$$3, rowOffset);
		ZEPHIR_CALL_FUNCTION(&_4$$3, "strval", &_5, 4, &_3$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_6$$3);
		ZEPHIR_CONCAT_SSVS(&_6$$3, "Matrix b does not fit", " into matrix a with row offset ", &_4$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_6$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2185);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_7, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	if (ZEPHIR_LT_LONG(&_8, (zephir_get_numberval(&_7) + columnOffset))) {
		ZEPHIR_INIT_VAR(&_9$$4);
		object_init_ex(&_9$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_10$$4, columnOffset);
		ZEPHIR_CALL_FUNCTION(&_11$$4, "strval", &_5, 4, &_10$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$4);
		ZEPHIR_CONCAT_SSVS(&_12$$4, "Matrix b does not fit", " into matrix a with column offset ", &_11$$4, ".");
		ZEPHIR_CALL_METHOD(NULL, &_9$$4, "__construct", NULL, 3, &_12$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_9$$4, "tensor/matrix.zep", 2191);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_OBS_VAR(&_13);
	zephir_read_property(&_13, this_ptr, ZEND_STRL("a"), PH_NOISY_CC);
	zephir_get_arrval(&_14, &_13);
	ZEPHIR_CPY_WRT(&c, &_14);
	ZEPHIR_CALL_METHOD(&_15, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_15, 0, "tensor/matrix.zep", 2211);
	if (Z_TYPE_P(&_15) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_15), _18, _19, _16)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_19 != NULL) { 
				ZVAL_STR_COPY(&i, _19);
			} else {
				ZVAL_LONG(&i, _18);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _16);
			ii = (rowOffset + zephir_get_numberval(&i));
			zephir_is_iterable(&rowB, 0, "tensor/matrix.zep", 2209);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowB), _22$$5, _23$$5, _20$$5)
				{
					ZEPHIR_INIT_NVAR(&j);
					if (_23$$5 != NULL) { 
						ZVAL_STR_COPY(&j, _23$$5);
					} else {
						ZVAL_LONG(&j, _22$$5);
					}
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _20$$5);
					jj = (columnOffset + zephir_get_numberval(&j));
					zephir_array_update_multi(&c, &valueB, SL("ll"), 2, ii, jj);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_21$$5, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_21$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&j, &rowB, "key", NULL, 0);
					zephir_check_call_status();
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						jj = (columnOffset + zephir_get_numberval(&j));
						zephir_array_update_multi(&c, &valueB, SL("ll"), 2, ii, jj);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZEPHIR_INIT_NVAR(&j);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, &_15, "rewind", NULL, 0);
		zephir_check_call_status();
		while (1) {
			ZEPHIR_CALL_METHOD(&_17, &_15, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, &_15, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, &_15, "current", NULL, 0);
			zephir_check_call_status();
				ii = (rowOffset + zephir_get_numberval(&i));
				zephir_is_iterable(&rowB, 0, "tensor/matrix.zep", 2209);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&rowB), _26$$8, _27$$8, _24$$8)
					{
						ZEPHIR_INIT_NVAR(&j);
						if (_27$$8 != NULL) { 
							ZVAL_STR_COPY(&j, _27$$8);
						} else {
							ZVAL_LONG(&j, _26$$8);
						}
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _24$$8);
						jj = (columnOffset + zephir_get_numberval(&j));
						zephir_array_update_multi(&c, &valueB, SL("ll"), 2, ii, jj);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_25$$8, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_25$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&j, &rowB, "key", NULL, 0);
						zephir_check_call_status();
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							jj = (columnOffset + zephir_get_numberval(&j));
							zephir_array_update_multi(&c, &valueB, SL("ll"), 2, ii, jj);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				ZEPHIR_INIT_NVAR(&j);
			ZEPHIR_CALL_METHOD(NULL, &_15, "next", NULL, 0);
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
 * Return the sub matrix starting at row and column offset.
 *
 * @param int startRow
 * @param int startColumn
 * @param int endRow
 * @param int endColumn
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subMatrix) {

	zend_bool _19, _23$$9;
	zval b, rowB;
	zval _10$$5, _12$$6, _15$$7, _18$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zval *startRow_param = NULL, *startColumn_param = NULL, *endRow_param = NULL, *endColumn_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9$$5, _11$$6, _13, _16, rowA, _14$$7, _17$$8, _22$$9, _26$$10;
	zend_long startRow, startColumn, endRow, endColumn, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k, l, _20, _21, _24$$9, _25$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_26$$10);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_18$$8);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 4, 0, &startRow_param, &startColumn_param, &endRow_param, &endColumn_param);

	startRow = zephir_get_intval(startRow_param);
	startColumn = zephir_get_intval(startColumn_param);
	endRow = zephir_get_intval(endRow_param);
	endColumn = zephir_get_intval(endColumn_param);


	if (UNEXPECTED(startRow < 0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_1$$3, startRow);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", &_3, 4, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_4$$3);
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Start row must be", " greater than 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 2232);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(startColumn < 0)) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_LONG(&_6$$4, startColumn);
		ZEPHIR_CALL_FUNCTION(&_7$$4, "strval", &_3, 4, &_6$$4);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_8$$4);
		ZEPHIR_CONCAT_SSVS(&_8$$4, "Start column must be", " greater than 0, ", &_7$$4, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 3, &_8$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 2237);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(endRow < startRow)) {
		ZEPHIR_INIT_VAR(&_9$$5);
		object_init_ex(&_9$$5, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_10$$5);
		ZEPHIR_CONCAT_SS(&_10$$5, "End row must be", " greater than start row.");
		ZEPHIR_CALL_METHOD(NULL, &_9$$5, "__construct", NULL, 3, &_10$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_9$$5, "tensor/matrix.zep", 2242);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(endColumn < startColumn)) {
		ZEPHIR_INIT_VAR(&_11$$6);
		object_init_ex(&_11$$6, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_12$$6);
		ZEPHIR_CONCAT_SS(&_12$$6, "End column must be", " greater than start column.");
		ZEPHIR_CALL_METHOD(NULL, &_11$$6, "__construct", NULL, 3, &_12$$6);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_11$$6, "tensor/matrix.zep", 2247);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_13, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(ZEPHIR_LT_LONG(&_13, endRow))) {
		ZEPHIR_INIT_VAR(&_14$$7);
		object_init_ex(&_14$$7, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_15$$7);
		ZEPHIR_CONCAT_SS(&_15$$7, "End row is out", " of bounds of matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_14$$7, "__construct", NULL, 3, &_15$$7);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_14$$7, "tensor/matrix.zep", 2252);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_16, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(ZEPHIR_LT_LONG(&_16, endColumn))) {
		ZEPHIR_INIT_VAR(&_17$$8);
		object_init_ex(&_17$$8, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_18$$8);
		ZEPHIR_CONCAT_SS(&_18$$8, "End column is out", " of bounds of matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_17$$8, "__construct", NULL, 3, &_18$$8);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_17$$8, "tensor/matrix.zep", 2257);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	k = (endRow - startRow);
	l = (endColumn - startColumn);
	_21 = k;
	_20 = startRow;
	_19 = 0;
	if (_20 <= _21) {
		while (1) {
			if (_19) {
				_20++;
				if (!(_20 <= _21)) {
					break;
				}
			} else {
				_19 = 1;
			}
			i = _20;
			zephir_read_property(&_22$$9, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch_long(&rowA, &_22$$9, i, PH_NOISY, "tensor/matrix.zep", 2269);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			_25$$9 = l;
			_24$$9 = startColumn;
			_23$$9 = 0;
			if (_24$$9 <= _25$$9) {
				while (1) {
					if (_23$$9) {
						_24$$9++;
						if (!(_24$$9 <= _25$$9)) {
							break;
						}
					} else {
						_23$$9 = 1;
					}
					j = _24$$9;
					zephir_array_fetch_long(&_26$$10, &rowA, j, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2274);
					zephir_array_append(&rowB, &_26$$10, PH_SEPARATE, "tensor/matrix.zep", 2274);
				}
			}
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 2277);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " columns but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2295);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_CALL_METHOD(&_11, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_12, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_fast_array_merge(&_10, &_11, &_12);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_10);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attach matrix b below this matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, ZEND_STRL("n"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " columns but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2313);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_10);
	zephir_read_property(&_11, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " rows but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2331);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_11, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "array_merge");
	ZEPHIR_CALL_FUNCTION(&_13, "array_map", NULL, 14, &_12, &_10, &_11);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_13);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Attach matrix b to the left of this matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property(&_3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_5$$3);
		zephir_read_property(&_5$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " rows but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 2349);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property(&_10, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_11, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(&_12);
	ZVAL_STRING(&_12, "array_merge");
	ZEPHIR_CALL_FUNCTION(&_13, "array_map", NULL, 14, &_12, &_10, &_11);
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
 * @return self
 */
PHP_METHOD(Tensor_Matrix, repeat) {

	zval b, temp;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, rowA, _7, _8, _0$$3, *_1$$3, _2$$3, _3$$4, _4$$4, _5$$6, _6$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$4);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$6);
	ZVAL_UNDEF(&_6$$6);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&temp);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);

	m = zephir_get_intval(m_param);
	n = zephir_get_intval(n_param);


	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&temp);
	array_init(&temp);
	if (n > 0) {
		zephir_read_property(&_0$$3, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
		zephir_is_iterable(&_0$$3, 0, "tensor/matrix.zep", 2379);
		if (Z_TYPE_P(&_0$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_0$$3), _1$$3)
			{
				ZEPHIR_INIT_NVAR(&rowA);
				ZVAL_COPY(&rowA, _1$$3);
				ZEPHIR_INIT_NVAR(&temp);
				array_init(&temp);
				while (1) {
					if (!(zephir_fast_count_int(&temp) <= n)) {
						break;
					}
					zephir_array_append(&temp, &rowA, PH_SEPARATE, "tensor/matrix.zep", 2374);
				}
				ZEPHIR_INIT_NVAR(&_3$$4);
				ZEPHIR_INIT_NVAR(&_4$$4);
				ZVAL_STRING(&_4$$4, "array_merge");
				ZEPHIR_CALL_USER_FUNC_ARRAY(&_3$$4, &_4$$4, &temp);
				zephir_check_call_status();
				zephir_array_append(&b, &_3$$4, PH_SEPARATE, "tensor/matrix.zep", 2377);
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
				ZEPHIR_CALL_METHOD(&rowA, &_0$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&temp);
					array_init(&temp);
					while (1) {
						if (!(zephir_fast_count_int(&temp) <= n)) {
							break;
						}
						zephir_array_append(&temp, &rowA, PH_SEPARATE, "tensor/matrix.zep", 2374);
					}
					ZEPHIR_INIT_NVAR(&_5$$6);
					ZEPHIR_INIT_NVAR(&_6$$6);
					ZVAL_STRING(&_6$$6, "array_merge");
					ZEPHIR_CALL_USER_FUNC_ARRAY(&_5$$6, &_6$$6, &temp);
					zephir_check_call_status();
					zephir_array_append(&b, &_5$$6, PH_SEPARATE, "tensor/matrix.zep", 2377);
				ZEPHIR_CALL_METHOD(NULL, &_0$$3, "next", NULL, 0);
				zephir_check_call_status();
			}
		}
		ZEPHIR_INIT_NVAR(&rowA);
	}
	ZEPHIR_INIT_NVAR(&temp);
	array_init(&temp);
	while (1) {
		if (!(zephir_fast_count_int(&temp) <= m)) {
			break;
		}
		zephir_array_append(&temp, &b, PH_SEPARATE, "tensor/matrix.zep", 2384);
	}
	ZEPHIR_INIT_VAR(&_7);
	ZEPHIR_INIT_VAR(&_8);
	ZVAL_STRING(&_8, "array_merge");
	ZEPHIR_CALL_USER_FUNC_ARRAY(&_7, &_8, &temp);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_7);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise product between this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2401);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2412);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2409);
			tensor_multiply(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2409);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2409);
				tensor_multiply(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2409);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2426);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2437);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2434);
			tensor_divide(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2434);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2434);
				tensor_divide(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2434);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2451);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2462);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2459);
			tensor_add(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2459);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2459);
				tensor_add(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2459);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
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
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2487);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2484);
			tensor_subtract(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2484);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2484);
				tensor_subtract(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2484);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2502);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2513);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2510);
			tensor_pow(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2510);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2510);
				tensor_pow(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2510);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2528);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2539);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2536);
			tensor_mod(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2536);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2536);
				tensor_mod(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2536);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2554);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2565);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2562);
			tensor_equal(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2562);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2562);
				tensor_equal(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2562);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2580);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2591);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2588);
			tensor_not_equal(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2588);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2588);
				tensor_not_equal(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2588);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2606);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2617);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2614);
			tensor_greater(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2614);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2614);
				tensor_greater(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2614);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2632);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2643);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2640);
			tensor_greater_equal(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2640);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2640);
				tensor_greater_equal(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2640);
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
 * Return the element-wise less than comparison of this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2657);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2668);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2665);
			tensor_less(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2665);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2665);
				tensor_less(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2665);
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
 * Return the element-wise less than or equal to comparison of this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualMatrix) {

	zend_string *_10;
	zend_ulong _9;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, _2$$3, _3$$3, _4$$3, _5$$3, _11$$4, _12$$4, _13$$4, _14$$5, _15$$5, _16$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&c);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "shape", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, this_ptr, "shape", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_CALL_METHOD(&_3$$3, this_ptr, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_4$$3, b, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_5$$3);
		ZEPHIR_CONCAT_VSVS(&_5$$3, &_3$$3, " matrix expected but ", &_4$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_5$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2682);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_6, 0, "tensor/matrix.zep", 2693);
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
			ZEPHIR_INIT_NVAR(&_11$$4);
			zephir_read_property(&_12$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_13$$4, &_12$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2690);
			tensor_less_equal(&_11$$4, &_13$$4, &rowB);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2690);
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
				ZEPHIR_INIT_NVAR(&_14$$5);
				zephir_read_property(&_15$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_16$$5, &_15$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 2690);
				tensor_less_equal(&_14$$5, &_16$$5, &rowB);
				zephir_array_append(&c, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 2690);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2708);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2721);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_multiply(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2718);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_multiply(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2718);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2736);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2749);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_divide(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2746);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_divide(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2746);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2764);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2777);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_add(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2774);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_add(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2774);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2792);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2805);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_subtract(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2802);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_subtract(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2802);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2820);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2833);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_pow(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2830);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_pow(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2830);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2848);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2861);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_mod(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2858);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_mod(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2858);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2877);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2890);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_equal(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2887);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_equal(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2887);
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
 * Return the element-wise not equal comparison of this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2905);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2918);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_not_equal(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2915);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_not_equal(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2915);
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
 * Return the element-wise greater than comparison of this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2933);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2946);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_greater(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2943);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_greater(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2943);
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
 * Return the element-wise greater than or equal to comparison of this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2961);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 2974);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_greater_equal(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2971);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_greater_equal(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2971);
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
 * Return the element-wise less than comparison of this matrix and a vector.
 *
 * @param \Tensor\Vector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2989);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3002);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_less(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 2999);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_less(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 2999);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualVector) {

	zval _4$$3, _6$$3, _7$$3;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _11$$4, _12$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("n"), PH_NOISY_CC | PH_READONLY);
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3018);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_8, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3031);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_8), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_INIT_NVAR(&_11$$4);
			tensor_less_equal(&_11$$4, &rowA, &bHat);
			zephir_array_append(&c, &_11$$4, PH_SEPARATE, "tensor/matrix.zep", 3028);
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
				ZEPHIR_INIT_NVAR(&_12$$5);
				tensor_less_equal(&_12$$5, &rowA, &bHat);
				zephir_array_append(&c, &_12$$5, PH_SEPARATE, "tensor/matrix.zep", 3028);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3046);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3057);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3054);
			tensor_multiply_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3054);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3054);
				tensor_multiply_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3054);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3072);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3083);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3080);
			tensor_divide_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3080);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3080);
				tensor_divide_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3080);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3098);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3109);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3106);
			tensor_add_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3106);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3106);
				tensor_add_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3106);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3124);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3135);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3132);
			tensor_subtract_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3132);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3132);
				tensor_subtract_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3132);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3150);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3161);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3158);
			tensor_pow_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3158);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3158);
				tensor_pow_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3158);
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
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3176);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3187);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3184);
			tensor_mod_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3184);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3184);
				tensor_mod_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3184);
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
 * Return the element-wise equality comparison of this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3202);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3213);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3210);
			tensor_equal_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3210);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3210);
				tensor_equal_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3210);
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
 * Return the element-wise not equal comparison of this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3228);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
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
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3236);
			tensor_not_equal_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3236);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3236);
				tensor_not_equal_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3236);
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
 * Return the element-wise greater than comparison of this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3254);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3265);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3262);
			tensor_greater_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3262);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3262);
				tensor_greater_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3262);
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
 * Return the element-wise greater than or equal to comparison of this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3280);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3291);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3288);
			tensor_greater_equal_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3288);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3288);
				tensor_greater_equal_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3288);
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
 * Return the element-wise less than comparison of this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3306);
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
			ZEPHIR_INIT_NVAR(&_13$$4);
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3314);
			tensor_less_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3314);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3314);
				tensor_less_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3314);
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
 * Return the element-wise less than or equal to comparison of this matrix and a column vector.
 *
 * @param \Tensor\ColumnVector b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualColumnVector) {

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



	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property(&_1, this_ptr, ZEND_STRL("m"), PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		ZEPHIR_OBS_VAR(&_3$$3);
		zephir_read_property(&_3$$3, this_ptr, ZEND_STRL("m"), PH_NOISY_CC);
		zephir_get_strval(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_get_strval(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3332);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/matrix.zep", 3343);
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
			zephir_read_property(&_14$$4, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
			zephir_array_fetch(&_15$$4, &_14$$4, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3340);
			tensor_less_equal_scalar(&_13$$4, &_15$$4, &valueB);
			zephir_array_append(&c, &_13$$4, PH_SEPARATE, "tensor/matrix.zep", 3340);
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
				zephir_read_property(&_17$$5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch(&_18$$5, &_17$$5, &i, PH_NOISY | PH_READONLY, "tensor/matrix.zep", 3340);
				tensor_less_equal_scalar(&_16$$5, &_18$$5, &valueB);
				zephir_array_append(&c, &_16$$5, PH_SEPARATE, "tensor/matrix.zep", 3340);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3357);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3368);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_multiply_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3365);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_multiply_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3365);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3382);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3393);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_divide_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3390);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_divide_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3390);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3407);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3418);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_add_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3415);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_add_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3415);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3432);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3443);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_subtract_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3440);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_subtract_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3440);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an", " integnr or floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3458);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3469);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_pow_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3466);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_pow_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3466);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3483);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3494);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_mod_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3491);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_mod_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3491);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3509);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3520);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_equal_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3517);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_equal_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3517);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3535);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3546);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_not_equal_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3543);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_not_equal_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3543);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3561);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3572);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_greater_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3569);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_greater_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3569);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3587);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3598);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_greater_equal_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3595);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_greater_equal_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3595);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3613);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3624);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_less_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3621);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_less_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3621);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualScalar) {

	zval c;
	zend_bool _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _1, rowA, _5, *_6, _7, _2$$3, _3$$3, _4$$3, _8$$4, _9$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
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
		ZEPHIR_CONCAT_SSVS(&_4$$3, "Scalar must be an integer or", " floating point number, ", &_3$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_4$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 3639);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property(&_5, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	zephir_is_iterable(&_5, 0, "tensor/matrix.zep", 3650);
	if (Z_TYPE_P(&_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&_5), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_INIT_NVAR(&_8$$4);
			tensor_less_equal_scalar(&_8$$4, &rowA, b);
			zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3647);
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
				ZEPHIR_INIT_NVAR(&_9$$5);
				tensor_less_equal_scalar(&_9$$5, &rowA, b);
				zephir_array_append(&c, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 3647);
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
 * @throws \Tensor\Exceptions\RuntimeException
 */
PHP_METHOD(Tensor_Matrix, offsetSet) {

	zval *index, index_sub, *values, values_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&values_sub);

	zephir_fetch_params_without_memory_grow(2, 0, &index, &values);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(tensor_exceptions_runtimeexception_ce, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3668);
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



	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset(&_0, index));

}

/**
 * @param mixed index
 * @throws \Tensor\Exceptions\RuntimeException
 */
PHP_METHOD(Tensor_Matrix, offsetUnset) {

	zval *index, index_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &index);



	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(tensor_exceptions_runtimeexception_ce, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3688);
	return;

}

/**
 * Return a row from the matrix at the given index.
 *
 * @param mixed index
 * @throws \Tensor\Exceptions\InvalidArgumentException
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
	zephir_throw_exception_debug(&_1, "tensor/matrix.zep", 3707);
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

	zephir_read_property(&_0, this_ptr, ZEND_STRL("a"), PH_NOISY_CC | PH_READONLY);
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
	ZEPHIR_CALL_FUNCTION(&_3, "array_reduce", NULL, 16, &_0, &_1, &_2);
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

