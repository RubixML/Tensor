
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
#include "kernel/string.h"
#include "kernel/math.h"
#include "ext/spl/spl_array.h"
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
ZEPHIR_INIT_CLASS(Tensor_Matrix)
{
	ZEPHIR_REGISTER_CLASS(Tensor, Matrix, tensor, matrix, tensor_matrix_method_entry, 0);

	/**
	 * A 2-dimensional sequential array that holds the values of the matrix.
	 *
	 * @var list<list<float>>
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
PHP_METHOD(Tensor_Matrix, build)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a_param = NULL, _0;
	zval a;

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(a, a_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
PHP_METHOD(Tensor_Matrix, quick)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a_param = NULL, _0;
	zval a;

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		ZEPHIR_Z_PARAM_ARRAY(a, a_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
PHP_METHOD(Tensor_Matrix, identity)
{
	zend_bool _4, _7$$4;
	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *n_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _10$$5;
	zend_long n, ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, _5, _6, _8$$4, _9$$4;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &n_param);
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
						ZVAL_DOUBLE(&_10$$5, 1.0);
					} else {
						ZEPHIR_INIT_NVAR(&_10$$5);
						ZVAL_DOUBLE(&_10$$5, 0.0);
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
PHP_METHOD(Tensor_Matrix, zeros)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, _0, _1, _2;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);
	ZVAL_DOUBLE(&_0, 0.0);
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
PHP_METHOD(Tensor_Matrix, ones)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, _0, _1, _2;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);
	ZVAL_DOUBLE(&_0, 1.0);
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
 * @param float[] elements
 * @return self
 */
PHP_METHOD(Tensor_Matrix, diagonal)
{
	zend_bool _1, _4$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, n, i = 0, j = 0, _2, _3, _5$$3, _6$$3;
	zval *elements_param = NULL, _0, _7$$4;
	zval elements, a, rowA;

	ZVAL_UNDEF(&elements);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_7$$4);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		ZEPHIR_Z_PARAM_ARRAY(elements, elements_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &elements_param);
	zephir_get_arrval(&elements, elements_param);
	n = zephir_fast_count_int(&elements);
	ZEPHIR_CALL_FUNCTION(&_0, "array_values", NULL, 29, &elements);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&elements, &_0);
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	_3 = (n - 1);
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
			ZEPHIR_INIT_NVAR(&rowA);
			array_init(&rowA);
			_6$$3 = (n - 1);
			_5$$3 = 0;
			_4$$3 = 0;
			if (_5$$3 <= _6$$3) {
				while (1) {
					if (_4$$3) {
						_5$$3++;
						if (!(_5$$3 <= _6$$3)) {
							break;
						}
					} else {
						_4$$3 = 1;
					}
					j = _5$$3;
					ZEPHIR_INIT_NVAR(&_7$$4);
					if (i == j) {
						ZEPHIR_OBS_NVAR(&_7$$4);
						zephir_array_fetch_long(&_7$$4, &elements, i, PH_NOISY, "tensor/matrix.zep", 148);
					} else {
						ZEPHIR_INIT_NVAR(&_7$$4);
						ZVAL_DOUBLE(&_7$$4, 0.0);
					}
					zephir_array_append(&rowA, &_7$$4, PH_SEPARATE, "tensor/matrix.zep", 148);
				}
			}
			zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 151);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Fill a matrix with a given value at each element.
 *
 * @param float value
 * @param int m
 * @param int n
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, fill)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_13 = NULL;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *value_param = NULL, *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10, _11, _12, _14;
	double value;

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
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_ZVAL(value_param)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 3, 0, &value_param, &m_param, &n_param);
	value = zephir_get_doubleval(value_param);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 170);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 175);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZVAL_LONG(&_9, 0);
	ZVAL_LONG(&_10, n);
	ZVAL_DOUBLE(&_11, value);
	ZEPHIR_CALL_FUNCTION(&_12, "array_fill", &_13, 5, &_9, &_10, &_11);
	zephir_check_call_status();
	ZVAL_LONG(&_9, 0);
	ZVAL_LONG(&_10, m);
	ZEPHIR_CALL_FUNCTION(&_14, "array_fill", &_13, 5, &_9, &_10, &_12);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_14);
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
PHP_METHOD(Tensor_Matrix, rand)
{
	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_11 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10$$6, _12$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;

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
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 193);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 198);
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
			zephir_array_append(&rowA, &_12$$6, PH_SEPARATE, "tensor/matrix.zep", 210);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 213);
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
PHP_METHOD(Tensor_Matrix, gaussian)
{
	zval a, rowA, extras;
	double r = 0, phi = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_11 = NULL, *_13 = NULL, *_16 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10$$6, _12$$7, _14$$7, _15$$7, _17$$7, _18$$7, _19$$7, _20$$7, _21$$8;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;

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
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 231);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 236);
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
			zephir_array_append(&rowA, &_10$$6, PH_SEPARATE, "tensor/matrix.zep", 251);
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
			r =  (sqrt((-2.0 * zephir_get_numberval(&_15$$7))));
			ZEPHIR_CALL_FUNCTION(&_17$$7, "rand", &_13, 7);
			zephir_check_call_status();
			phi =  ((zephir_safe_div_zval_long(&_17$$7, max) * 6.28318530718));
			ZVAL_DOUBLE(&_18$$7, phi);
			ZEPHIR_INIT_NVAR(&_19$$7);
			ZVAL_DOUBLE(&_19$$7, (r * sin(phi)));
			zephir_array_append(&rowA, &_19$$7, PH_SEPARATE, "tensor/matrix.zep", 259);
			ZVAL_DOUBLE(&_20$$7, phi);
			ZEPHIR_INIT_NVAR(&_19$$7);
			ZVAL_DOUBLE(&_19$$7, (r * cos(phi)));
			zephir_array_append(&rowA, &_19$$7, PH_SEPARATE, "tensor/matrix.zep", 260);
		}
		if (zephir_fast_count_int(&rowA) > n) {
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(&_21$$8, "array_pop", &_11, 9, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			zephir_array_append(&extras, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 264);
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, poisson)
{
	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_20 = NULL;
	double lambda, l = 0, p = 0, k = 0;
	zval *m_param = NULL, *n_param = NULL, *lambda_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9$$5, _10$$5, _11$$5, _12$$5, _13$$6, _14$$6, _15$$6, _16, _17, _18, _19$$9, _21$$8;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&rowA);
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(lambda_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 1, &m_param, &n_param, &lambda_param);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 286);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 291);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(lambda < 0.0)) {
		ZEPHIR_INIT_VAR(&_9$$5);
		object_init_ex(&_9$$5, tensor_exceptions_invalidargumentexception_ce);
		ZVAL_DOUBLE(&_10$$5, lambda);
		ZEPHIR_CALL_FUNCTION(&_11$$5, "strval", &_3, 4, &_10$$5);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_12$$5);
		ZEPHIR_CONCAT_SSVS(&_12$$5, "Lambda must be", " greater than or equal to 0, ", &_11$$5, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_9$$5, "__construct", NULL, 3, &_12$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_9$$5, "tensor/matrix.zep", 296);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if (UNEXPECTED(lambda == 0.0)) {
		ZVAL_DOUBLE(&_13$$6, 0.0);
		ZVAL_LONG(&_14$$6, m);
		ZVAL_LONG(&_15$$6, n);
		ZEPHIR_RETURN_CALL_SELF("fill", NULL, 0, &_13$$6, &_14$$6, &_15$$6);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&a);
	array_init(&a);
	ZEPHIR_INIT_VAR(&rowA);
	array_init(&rowA);
	ZVAL_DOUBLE(&_16, -lambda);
	ZEPHIR_CALL_FUNCTION(&_17, "exp", NULL, 10, &_16);
	zephir_check_call_status();
	l =  (zephir_get_doubleval(&_17));
	ZEPHIR_CALL_FUNCTION(&_18, "getrandmax", NULL, 6);
	zephir_check_call_status();
	max = zephir_get_intval(&_18);
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
			k =  (0.0);
			p =  (1.0);
			while (1) {
				if (!(p > l)) {
					break;
				}
				k++;
				ZEPHIR_CALL_FUNCTION(&_19$$9, "rand", &_20, 7);
				zephir_check_call_status();
				p *=  (zephir_safe_div_zval_long(&_19$$9, max));
			}
			ZEPHIR_INIT_NVAR(&_21$$8);
			ZVAL_DOUBLE(&_21$$8, (k - 1.0));
			zephir_array_append(&rowA, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 325);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 328);
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
PHP_METHOD(Tensor_Matrix, uniform)
{
	zval a, rowA;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL, *_13 = NULL;
	zval *m_param = NULL, *n_param = NULL, _0$$3, _1$$3, _2$$3, _4$$3, _5$$4, _6$$4, _7$$4, _8$$4, _9, _10$$6, _11$$6, _12$$6, _14$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS, max;

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
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 346);
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
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 351);
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
			zephir_array_append(&rowA, &_14$$6, PH_SEPARATE, "tensor/matrix.zep", 363);
		}
		zephir_array_append(&a, &rowA, PH_SEPARATE, "tensor/matrix.zep", 366);
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &a);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param array[] a
 * @param bool validate
 * @throws \Tensor\Exceptions\InvalidArgumentException
 */
PHP_METHOD(Tensor_Matrix, __construct)
{
	zend_string *_5$$5;
	zend_ulong _4$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_12 = NULL, *_18 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, m, n;
	zend_bool validate, _20$$6;
	zval *a_param = NULL, *validate_param = NULL, i, rowA, valueA, _0, _1, _23, _2$$5, *_3$$5, _6$$7, _7$$7, _8$$7, _10$$7, _11$$7, *_13$$6, _14$$6, *_15$$6, _19$$6, _16$$8, _17$$8, _21$$9, _22$$9;
	zval a, b$$5, rowB$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&b$$5);
	ZVAL_UNDEF(&rowB$$5);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_2$$5);
	ZVAL_UNDEF(&_6$$7);
	ZVAL_UNDEF(&_7$$7);
	ZVAL_UNDEF(&_8$$7);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_11$$7);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_16$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("n", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		ZEPHIR_Z_PARAM_ARRAY(a, a_param)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(validate)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &a_param, &validate_param);
	zephir_get_arrval(&a, a_param);
	if (!validate_param) {
		validate = 1;
	} else {
		}
	m = zephir_fast_count_int(&a);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CALL_FUNCTION(&_1, "current", NULL, 30, &a);
	zephir_check_call_status();
	if (!(zephir_is_true(&_1))) {
		ZEPHIR_INIT_NVAR(&_0);
		array_init(&_0);
	} else {
		ZEPHIR_CALL_FUNCTION(&_0, "current", NULL, 30, &a);
		zephir_check_call_status();
	}
	n = zephir_fast_count_int(&_0);
	if (validate) {
		ZEPHIR_INIT_VAR(&b$$5);
		array_init(&b$$5);
		ZEPHIR_INIT_VAR(&rowB$$5);
		array_init(&rowB$$5);
		ZEPHIR_CALL_FUNCTION(&_2$$5, "array_values", NULL, 29, &a);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&a, &_2$$5);
		zephir_is_iterable(&a, 0, "tensor/matrix.zep", 407);
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&a), _4$$5, _5$$5, _3$$5)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_5$$5 != NULL) { 
				ZVAL_STR_COPY(&i, _5$$5);
			} else {
				ZVAL_LONG(&i, _4$$5);
			}
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3$$5);
			if (UNEXPECTED(zephir_fast_count_int(&rowA) != n)) {
				ZEPHIR_INIT_NVAR(&_6$$7);
				object_init_ex(&_6$$7, tensor_exceptions_invalidargumentexception_ce);
				ZVAL_LONG(&_7$$7, n);
				ZEPHIR_CALL_FUNCTION(&_8$$7, "strval", &_9, 4, &_7$$7);
				zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_10$$7);
				ZVAL_LONG(&_10$$7, zephir_fast_count_int(&rowA));
				ZEPHIR_INIT_NVAR(&_11$$7);
				ZEPHIR_CONCAT_SSVSVSSVS(&_11$$7, "The number of columns", " must be equal for all rows, ", &_8$$7, " needed but ", &_10$$7, " given", " at row offset ", &i, ".");
				ZEPHIR_CALL_METHOD(NULL, &_6$$7, "__construct", &_12, 3, &_11$$7);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_6$$7, "tensor/matrix.zep", 395);
				ZEPHIR_MM_RESTORE();
				return;
			}
			ZEPHIR_INIT_NVAR(&rowB$$5);
			array_init(&rowB$$5);
			ZEPHIR_CPY_WRT(&rowB$$5, &rowB$$5);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_14$$6);
				zephir_string_to_char_array(&_14$$6, &rowA);
				_13$$6 = &_14$$6;
			} else {
				_13$$6 = &rowA;
			}
			zephir_is_iterable(_13$$6, 0, "tensor/matrix.zep", 404);
			if (Z_TYPE_P(_13$$6) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13$$6), _15$$6)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _15$$6);
					ZEPHIR_INIT_NVAR(&_16$$8);
					ZEPHIR_CALL_FUNCTION(&_17$$8, "is_float", &_18, 2, &valueA);
					zephir_check_call_status();
					if (zephir_is_true(&_17$$8)) {
						ZEPHIR_CPY_WRT(&_16$$8, &valueA);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$8);
						ZVAL_DOUBLE(&_16$$8, zephir_get_doubleval(&valueA));
					}
					zephir_array_append(&rowB$$5, &_16$$8, PH_SEPARATE, "tensor/matrix.zep", 401);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _13$$6, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$6 = 1;
				while (1) {
					if (_20$$6) {
						_20$$6 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _13$$6, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$6, _13$$6, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$6)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _13$$6, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$9);
						ZEPHIR_CALL_FUNCTION(&_22$$9, "is_float", &_18, 2, &valueA);
						zephir_check_call_status();
						if (zephir_is_true(&_22$$9)) {
							ZEPHIR_CPY_WRT(&_21$$9, &valueA);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$9);
							ZVAL_DOUBLE(&_21$$9, zephir_get_doubleval(&valueA));
						}
						zephir_array_append(&rowB$$5, &_21$$9, PH_SEPARATE, "tensor/matrix.zep", 401);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b$$5, &rowB$$5, PH_SEPARATE, "tensor/matrix.zep", 404);
		} ZEND_HASH_FOREACH_END();
		ZEPHIR_INIT_NVAR(&rowA);
		ZEPHIR_INIT_NVAR(&i);
		ZEPHIR_CPY_WRT(&a, &b$$5);
	}
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_0, 14, &a);
	ZVAL_UNDEF(&_23);
	ZVAL_LONG(&_23, m);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_1, 15, &_23);
	ZVAL_UNDEF(&_23);
	ZVAL_LONG(&_23, n);
	zephir_update_property_zval_cached(this_ptr, _zephir_prop_2, 16, &_23);
	ZEPHIR_MM_RESTORE();
}

/**
 * Return a tuple with the dimensionality of the tensor.
 *
 * @return int[]
 */
PHP_METHOD(Tensor_Matrix, shape)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_create_array(return_value, 2, 0);
	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
	zephir_array_fast_append(return_value, &_0);
	ZEPHIR_OBS_NVAR(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC);
	zephir_array_fast_append(return_value, &_0);
	RETURN_MM();
}

/**
 * Return the shape of the tensor as a string.
 *
 * @return string
 */
PHP_METHOD(Tensor_Matrix, shapeString)
{
	zval _1, _3;
	zval _0, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_memory_observe(&_0);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
	zephir_cast_to_string(&_1, &_0);
	zephir_memory_observe(&_2);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC);
	zephir_cast_to_string(&_3, &_2);
	ZEPHIR_CONCAT_VSV(return_value, &_1, " x ", &_3);
	RETURN_MM();
}

/**
 * Is this a square matrix?
 *
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, isSquare)
{
	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(ZEPHIR_IS_IDENTICAL(&_0, &_1));
}

/**
 * Return the number of elements in the tensor.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, size)
{
	zval _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
	mul_function(return_value, &_0, &_1);
	return;
}

/**
 * Return the number of rows in the matrix.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, m)
{

	RETURN_MEMBER_TYPED(getThis(), "m", IS_LONG);
}

/**
 * Return the number of columns in the matrix.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, n)
{

	RETURN_MEMBER_TYPED(getThis(), "n", IS_LONG);
}

/**
 * Return a row as a vector from the matrix.
 *
 * @param int index
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, rowAsVector)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL, _0;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	ZVAL_LONG(&_0, index);
	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "offsetget", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return a column as a vector from the matrix.
 *
 * @param int index
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, columnAsVector)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *index_param = NULL, _0, _1, _2;
	zend_long index, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index_param);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, index);
	ZEPHIR_CALL_FUNCTION(&_2, "array_column", NULL, 31, &_0, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the diagonal elements of a square matrix as a vector.
 *
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, diagonalAsVector)
{
	zend_bool _12;
	zend_string *_9;
	zend_ulong _8;
	zval b;
	zval _0, i, rowA, _4, *_5, _6, *_7, _11, _1$$3, _2$$3, _3$$3, _10$$4, _13$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&b);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 507);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property_cached(&_4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_4) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_6);
		zephir_string_to_char_array(&_6, &_4);
		_5 = &_6;
	} else {
		_5 = &_4;
	}
	zephir_is_iterable(_5, 0, "tensor/matrix.zep", 518);
	if (Z_TYPE_P(_5) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_5), _8, _9, _7)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_9 != NULL) { 
				ZVAL_STR_COPY(&i, _9);
			} else {
				ZVAL_LONG(&i, _8);
			}
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _7);
			ZEPHIR_OBS_NVAR(&_10$$4);
			zephir_array_fetch(&_10$$4, &rowA, &i, PH_NOISY, "tensor/matrix.zep", 515);
			zephir_array_append(&b, &_10$$4, PH_SEPARATE, "tensor/matrix.zep", 515);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _5, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _5, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _5, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _5, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowA, _5, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_OBS_NVAR(&_13$$5);
				zephir_array_fetch(&_13$$5, &rowA, &i, PH_NOISY, "tensor/matrix.zep", 515);
				zephir_array_append(&b, &_13$$5, PH_SEPARATE, "tensor/matrix.zep", 515);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the elements of the matrix in a 2-d array.
 *
 * @return list<list<float>>
 */
PHP_METHOD(Tensor_Matrix, asArray)
{

	RETURN_MEMBER_TYPED(getThis(), "a", IS_ARRAY);
}

/**
 * Return each row as a vector in an array.
 *
 * @return \Tensor\Vector[]
 */
PHP_METHOD(Tensor_Matrix, asVectors)
{
	zval _1, _2;
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	zephir_create_array(&_0, 2, 0);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "Tensor\\Vector");
	zephir_array_fast_append(&_0, &_1);
	ZEPHIR_INIT_NVAR(&_1);
	ZVAL_STRING(&_1, "quick");
	zephir_array_fast_append(&_0, &_1);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_FUNCTION("array_map", NULL, 14, &_0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return each column as a column vector in an array.
 *
 * @return \Tensor\ColumnVector[]
 */
PHP_METHOD(Tensor_Matrix, asColumnVectors)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&vectors);
	array_init(&vectors);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
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
			zephir_array_append(&vectors, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 553);
		}
	}
	RETURN_CTOR(&vectors);
}

/**
 * Flatten i.e unravel the matrix into a vector.
 *
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, flatten)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&_0);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_2);
	ZVAL_STRING(&_2, "array_merge");
	ZEPHIR_CALL_USER_FUNC_ARRAY(&_0, &_2, &_1);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Run a function over all of the elements in the matrix.
 *
 * @internal
 *
 * @param callable callback
 * @return self
 */
PHP_METHOD(Tensor_Matrix, map)
{
	zend_bool _7;
	zval b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *callback, callback_sub, rowA, _0, *_1, _2, *_3, _6, _4$$3, _8$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&b);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(callback)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &callback);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 587);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_CALL_FUNCTION(&_4$$3, "array_map", &_5, 14, callback, &rowA);
			zephir_check_call_status();
			zephir_array_append(&b, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 584);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_CALL_FUNCTION(&_8$$4, "array_map", &_5, 14, callback, &rowA);
				zephir_check_call_status();
				zephir_array_append(&b, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 584);
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
 * @internal
 *
 * @param callable callback function (float carry, float value): float
 * @param float initial
 * @return float
 */
PHP_METHOD(Tensor_Matrix, reduce)
{
	zend_bool _12, _9$$3, _18$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	double initial;
	zval *callback, callback_sub, *initial_param = NULL, rowA, valueA, carry, _0, *_1, _2, *_3, _11, *_4$$3, _5$$3, *_6$$3, _8$$3, _7$$4, _10$$5, *_13$$6, _14$$6, *_15$$6, _17$$6, _16$$7, _19$$8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&callback_sub);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&carry);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_19$$8);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_ZVAL(callback)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(initial_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &callback, &initial_param);
	if (!initial_param) {
		initial = 0.0;
	} else {
		initial = zephir_get_doubleval(initial_param);
	}
	ZEPHIR_INIT_VAR(&carry);
	ZVAL_DOUBLE(&carry, initial);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 611);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &rowA);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &rowA;
			}
			zephir_is_iterable(_4$$3, 0, "tensor/matrix.zep", 609);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _6$$3);
					ZEPHIR_CALL_ZVAL_FUNCTION(&_7$$4, callback, NULL, 0, &carry, &valueA);
					zephir_check_call_status();
					ZEPHIR_CPY_WRT(&carry, &_7$$4);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_9$$3 = 1;
				while (1) {
					if (_9$$3) {
						_9$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_8$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_8$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_CALL_ZVAL_FUNCTION(&_10$$5, callback, NULL, 0, &carry, &valueA);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&carry, &_10$$5);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_14$$6);
					zephir_string_to_char_array(&_14$$6, &rowA);
					_13$$6 = &_14$$6;
				} else {
					_13$$6 = &rowA;
				}
				zephir_is_iterable(_13$$6, 0, "tensor/matrix.zep", 609);
				if (Z_TYPE_P(_13$$6) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13$$6), _15$$6)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _15$$6);
						ZEPHIR_CALL_ZVAL_FUNCTION(&_16$$7, callback, NULL, 0, &carry, &valueA);
						zephir_check_call_status();
						ZEPHIR_CPY_WRT(&carry, &_16$$7);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _13$$6, "rewind", NULL, 0);
					zephir_check_call_status();
					_18$$6 = 1;
					while (1) {
						if (_18$$6) {
							_18$$6 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _13$$6, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_17$$6, _13$$6, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_17$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _13$$6, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_CALL_ZVAL_FUNCTION(&_19$$8, callback, NULL, 0, &carry, &valueA);
							zephir_check_call_status();
							ZEPHIR_CPY_WRT(&carry, &_19$$8);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
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
PHP_METHOD(Tensor_Matrix, transpose)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
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
			zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZVAL_LONG(&_5$$3, i);
			ZEPHIR_CALL_FUNCTION(&_6$$3, "array_column", &_7, 31, &_4$$3, &_5$$3);
			zephir_check_call_status();
			zephir_array_append(&b, &_6$$3, PH_SEPARATE, "tensor/matrix.zep", 626);
		}
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &b);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compute the inverse of the square matrix.
 *
 * @throws \Tensor\Exceptions\RuntimeException
 * @return self
 */
PHP_METHOD(Tensor_Matrix, inverse)
{
	zval _6$$4, _9$$5;
	zval _0, _4, result, _7, _1$$3, _2$$3, _3$$3, _5$$4, _8$$5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_9$$5);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 642);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_4, this_ptr, "fullrank", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_4))) {
		ZEPHIR_INIT_VAR(&_5$$4);
		object_init_ex(&_5$$4, tensor_exceptions_runtimeexception_ce);
		ZEPHIR_INIT_VAR(&_6$$4);
		ZEPHIR_CONCAT_SS(&_6$$4, "Failed to compute the inverse", " of a singular matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$4, "__construct", NULL, 32, &_6$$4);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$4, "tensor/matrix.zep", 647);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&result);
	zephir_read_property_cached(&_7, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	tensor_inverse(&result, &_7);
	if (Z_TYPE_P(&result) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_8$$5);
		object_init_ex(&_8$$5, tensor_exceptions_runtimeexception_ce);
		ZEPHIR_INIT_VAR(&_9$$5);
		ZEPHIR_CONCAT_SS(&_9$$5, "Failed to compute the inverse", " of a singular matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_8$$5, "__construct", NULL, 32, &_9$$5);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_8$$5, "tensor/matrix.zep", 654);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &result);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compute the Moore-Penrose pseudoinverse of a general matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, pseudoinverse)
{
	zval _2$$3;
	zval result, _0, _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&result);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	tensor_pseudoinverse(&result, &_0);
	if (Z_TYPE_P(&result) == IS_NULL) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_runtimeexception_ce);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Failed to compute the pseudoinverse", " of the matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 32, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 671);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &result);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Calculate the determinant of the matrix.
 *
 * @throws \Tensor\Exceptions\RuntimeException
 * @return float
 */
PHP_METHOD(Tensor_Matrix, det)
{
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
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 687);
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
	ZEPHIR_CALL_METHOD(&_6, &ref, "swaps", NULL, 0);
	zephir_check_call_status();
	ZVAL_DOUBLE(&_7, -1.0);
	ZEPHIR_CALL_FUNCTION(&_8, "pow", NULL, 16, &_7, &_6);
	zephir_check_call_status();
	mul_function(return_value, &pi, &_8);
	RETURN_MM();
}

/**
 * Return the trace of the matrix i.e the sum of all diagonal elements of a square matrix.
 *
 * @return float
 */
PHP_METHOD(Tensor_Matrix, trace)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "diagonalasvector", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "sum", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Calculate the rank of the matrix i.e the number of pivots in its reduced row echelon form.
 *
 * @return int
 */
PHP_METHOD(Tensor_Matrix, rank)
{
	double epsilon;
	zend_bool stop = 0, _11$$3;
	zval a, _3;
	zval rowA, valueA, _0, _1, _2, *_4, *_5$$3, _6$$3, *_7$$3, _10$$3, _8$$4, _12$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, pivots;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_12$$7);
	ZVAL_UNDEF(&a);
	ZVAL_UNDEF(&_3);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
	epsilon =  (0.00000001);
	zephir_is_iterable(&a, 0, "tensor/matrix.zep", 742);
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&a), _4)
	{
		ZEPHIR_INIT_NVAR(&rowA);
		ZVAL_COPY(&rowA, _4);
		stop = 0;
		if (Z_TYPE_P(&rowA) == IS_STRING) {
			ZEPHIR_INIT_NVAR(&_6$$3);
			zephir_string_to_char_array(&_6$$3, &rowA);
			_5$$3 = &_6$$3;
		} else {
			_5$$3 = &rowA;
		}
		zephir_is_iterable(_5$$3, 0, "tensor/matrix.zep", 740);
		if (Z_TYPE_P(_5$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5$$3), _7$$3)
			{
				ZEPHIR_INIT_NVAR(&valueA);
				ZVAL_COPY(&valueA, _7$$3);
				if (stop) {
					continue;
				}
				ZEPHIR_CALL_FUNCTION(&_8$$4, "abs", &_9, 12, &valueA);
				zephir_check_call_status();
				if (!ZEPHIR_LT_DOUBLE(&_8$$4, epsilon)) {
					pivots++;
					stop = 1;
				}
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _5$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_11$$3 = 1;
			while (1) {
				if (_11$$3) {
					_11$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _5$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_10$$3, _5$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_10$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&valueA, _5$$3, "current", NULL, 0);
				zephir_check_call_status();
					if (stop) {
						continue;
					}
					ZEPHIR_CALL_FUNCTION(&_12$$7, "abs", &_9, 12, &valueA);
					zephir_check_call_status();
					if (!ZEPHIR_LT_DOUBLE(&_12$$7, epsilon)) {
						pivots++;
						stop = 1;
					}
			}
		}
		ZEPHIR_INIT_NVAR(&valueA);
	} ZEND_HASH_FOREACH_END();
	ZEPHIR_INIT_NVAR(&rowA);
	RETURN_MM_LONG(pivots);
}

/**
 * Is the matrix full rank?
 * 
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, fullRank)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, symmetric)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("n", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		RETURN_MM_BOOL(0);
	}
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
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
			zephir_read_property_cached(&_5$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&rowA);
			zephir_array_fetch_long(&rowA, &_5$$4, i, PH_NOISY, "tensor/matrix.zep", 771);
			zephir_read_property_cached(&_6$$4, this_ptr, _zephir_prop_2, 16, PH_NOISY_CC | PH_READONLY);
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
					ZEPHIR_OBS_NVAR(&_10$$5);
					zephir_array_fetch_long(&_10$$5, &rowA, j, PH_NOISY, "tensor/matrix.zep", 774);
					zephir_read_property_cached(&_11$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
					ZEPHIR_OBS_NVAR(&_12$$5);
					zephir_array_fetch_long(&_12$$5, &_11$$5, j, PH_NOISY, "tensor/matrix.zep", 774);
					ZEPHIR_OBS_NVAR(&_13$$5);
					zephir_array_fetch_long(&_13$$5, &_12$$5, i, PH_NOISY, "tensor/matrix.zep", 774);
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
 * Multiply this matrix with another matrix (matrix-matrix product).
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, matmul)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 795);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_8);
	zephir_read_property_cached(&_9, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, dot)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "size", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "size", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A requires ", &_4$$3, " elements but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 813);
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
PHP_METHOD(Tensor_Matrix, convolve)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(stride)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 1, &b, &stride_param);
	if (!stride_param) {
		stride = 1;
	} else {
		}
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	_2 = ZEPHIR_GT(&_0, &_1);
	if (!(_2)) {
		ZEPHIR_CALL_METHOD(&_3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_4, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
		_2 = ZEPHIR_GT(&_3, &_4);
	}
	if (UNEXPECTED(_2)) {
		ZEPHIR_INIT_VAR(&_5$$3);
		object_init_ex(&_5$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_INIT_VAR(&_6$$3);
		ZEPHIR_CONCAT_SS(&_6$$3, "Matrix B cannot be", " larger than Matrix A.");
		ZEPHIR_CALL_METHOD(NULL, &_5$$3, "__construct", NULL, 3, &_6$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_5$$3, "tensor/matrix.zep", 831);
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
		zephir_throw_exception_debug(&_7$$4, "tensor/matrix.zep", 836);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_11);
	zephir_read_property_cached(&_12, this_ptr, _zephir_prop_2, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_13, b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZVAL_LONG(&_14, stride);
	tensor_convolve_2d(&_11, &_12, &_13, &_14);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_11);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Calculate the row echelon form (REF) of the matrix.
 *
 * @return \Tensor\Reductions\Ref
 */
PHP_METHOD(Tensor_Matrix, ref)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_reductions_ref_ce, "reduce", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the reduced row echelon (RREF) form of the matrix.
 *
 * @return \Tensor\Reductions\Rref
 */
PHP_METHOD(Tensor_Matrix, rref)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_reductions_rref_ce, "reduce", NULL, 0, this_ptr);
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
PHP_METHOD(Tensor_Matrix, lu)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_lu_ce, "decompose", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the lower triangular matrix of the Cholesky decomposition.
 * 
 * @return \Tensor\Decompositions\Cholesky;
 */
PHP_METHOD(Tensor_Matrix, cholesky)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_cholesky_ce, "decompose", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compute the eigenvalues and eigenvectors of the matrix and return them in a tuple.
 *
 * @param bool symmetric
 * @return \Tensor\Decompositions\Eigen
 */
PHP_METHOD(Tensor_Matrix, eig)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *symmetric_param = NULL, _0;
	zend_bool symmetric;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(symmetric)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &symmetric_param);
	if (!symmetric_param) {
		symmetric = 0;
	} else {
		}
	if (symmetric) {
		ZVAL_BOOL(&_0, 1);
	} else {
		ZVAL_BOOL(&_0, 0);
	}
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_eigen_ce, "decompose", NULL, 0, this_ptr, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compute the singluar value decomposition of this matrix.
 *
 * @return \Tensor\Decompositions\Svd
 */
PHP_METHOD(Tensor_Matrix, svd)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_decompositions_svd_ce, "decompose", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the L1 norm of the matrix.
 *
 * @return float
 */
PHP_METHOD(Tensor_Matrix, l1Norm)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
 * @return float
 */
PHP_METHOD(Tensor_Matrix, l2Norm)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
 * @return float
 */
PHP_METHOD(Tensor_Matrix, infinityNorm)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
 * @return float
 */
PHP_METHOD(Tensor_Matrix, maxNorm)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, multiply)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplycolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplyscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot multiply", " matrix by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 975);
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
PHP_METHOD(Tensor_Matrix, divide)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividematrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividecolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividevector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "dividescalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot divide", " matrix by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1008);
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
PHP_METHOD(Tensor_Matrix, add)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "addscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot add", " matrix with the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1042);
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
PHP_METHOD(Tensor_Matrix, subtract)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "subtractscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot multiply", " matrix by the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1076);
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
PHP_METHOD(Tensor_Matrix, pow)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "powscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot raise", " matrix to the power of the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1110);
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
PHP_METHOD(Tensor_Matrix, mod)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "modscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot mod", " matrix with the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1144);
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
PHP_METHOD(Tensor_Matrix, equal)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "equalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1178);
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
PHP_METHOD(Tensor_Matrix, notEqual)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "notequalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1212);
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
PHP_METHOD(Tensor_Matrix, greater)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatermatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatercolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greatervector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1246);
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
PHP_METHOD(Tensor_Matrix, greaterEqual)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "greaterequalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1280);
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
PHP_METHOD(Tensor_Matrix, less)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lesscolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1314);
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
PHP_METHOD(Tensor_Matrix, lessEqual)
{
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
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_INIT_VAR(&_0);
	zephir_gettype(&_0, b);
	if (ZEPHIR_IS_STRING(&_0, "object")) { goto zephir_switch_0_clause_0; }
	if (ZEPHIR_IS_STRING(&_0, "double")) { goto zephir_switch_0_clause_1; }
	if (ZEPHIR_IS_STRING(&_0, "integer")) { goto zephir_switch_0_clause_2; }
	goto zephir_switch_0_end;
	zephir_switch_0_clause_0: ;
		_1$$3 = 1;
		if (_1$$3 == zephir_instance_of_ev(b, tensor_matrix_ce)) { goto zephir_switch_1_clause_0; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_columnvector_ce)) { goto zephir_switch_1_clause_1; }
		if (_1$$3 == zephir_instance_of_ev(b, tensor_vector_ce)) { goto zephir_switch_1_clause_2; }
		goto zephir_switch_1_end;
		zephir_switch_1_clause_0: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalmatrix", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_1: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalcolumnvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_clause_2: ;
			ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalvector", NULL, 0, b);
			zephir_check_call_status();
			RETURN_MM();
		zephir_switch_1_end: ;

		goto zephir_switch_0_end;
	zephir_switch_0_clause_1: ;
	zephir_switch_0_clause_2: ;
		ZEPHIR_RETURN_CALL_METHOD(this_ptr, "lessequalscalar", NULL, 0, b);
		zephir_check_call_status();
		RETURN_MM();
	zephir_switch_0_end: ;

	ZEPHIR_INIT_VAR(&_2);
	object_init_ex(&_2, tensor_exceptions_invalidargumentexception_ce);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SS(&_3, "Cannot compare", " matrix to the given input.");
	ZEPHIR_CALL_METHOD(NULL, &_2, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_2, "tensor/matrix.zep", 1348);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Return the element-wise reciprocal of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, reciprocal)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, abs)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, square)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "multiplymatrix", NULL, 0, this_ptr);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the square root of the matrix.
 *
 * @return self
 */
PHP_METHOD(Tensor_Matrix, sqrt)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, exp)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, expm1)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, log)
{
	zend_bool _16, _12$$4, _23$$7;
	zval rowB, b;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *base_param = NULL, _0$$3, rowA, valueA, _1, *_2, _3, *_4, _15, *_5$$4, _6$$4, *_7$$4, _11$$4, _8$$5, _9$$5, _13$$6, _14$$6, *_17$$7, _18$$7, *_19$$7, _22$$7, _20$$8, _21$$8, _24$$9, _25$$9;
	double base;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&b);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL(base_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_1) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_3);
		zephir_string_to_char_array(&_3, &_1);
		_2 = &_3;
	} else {
		_2 = &_1;
	}
	zephir_is_iterable(_2, 0, "tensor/matrix.zep", 1439);
	if (Z_TYPE_P(_2) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_2), _4)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _4);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_6$$4);
				zephir_string_to_char_array(&_6$$4, &rowA);
				_5$$4 = &_6$$4;
			} else {
				_5$$4 = &rowA;
			}
			zephir_is_iterable(_5$$4, 0, "tensor/matrix.zep", 1436);
			if (Z_TYPE_P(_5$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_5$$4), _7$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _7$$4);
					ZVAL_DOUBLE(&_8$$5, base);
					ZEPHIR_CALL_FUNCTION(&_9$$5, "log", &_10, 8, &valueA, &_8$$5);
					zephir_check_call_status();
					zephir_array_append(&rowB, &_9$$5, PH_SEPARATE, "tensor/matrix.zep", 1433);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _5$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_12$$4 = 1;
				while (1) {
					if (_12$$4) {
						_12$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _5$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_11$$4, _5$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _5$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZVAL_DOUBLE(&_13$$6, base);
						ZEPHIR_CALL_FUNCTION(&_14$$6, "log", &_10, 8, &valueA, &_13$$6);
						zephir_check_call_status();
						zephir_array_append(&rowB, &_14$$6, PH_SEPARATE, "tensor/matrix.zep", 1433);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1436);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _2, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _2, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _2, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _2, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_18$$7);
					zephir_string_to_char_array(&_18$$7, &rowA);
					_17$$7 = &_18$$7;
				} else {
					_17$$7 = &rowA;
				}
				zephir_is_iterable(_17$$7, 0, "tensor/matrix.zep", 1436);
				if (Z_TYPE_P(_17$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_17$$7), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$7);
						ZVAL_DOUBLE(&_20$$8, base);
						ZEPHIR_CALL_FUNCTION(&_21$$8, "log", &_10, 8, &valueA, &_20$$8);
						zephir_check_call_status();
						zephir_array_append(&rowB, &_21$$8, PH_SEPARATE, "tensor/matrix.zep", 1433);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _17$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_23$$7 = 1;
					while (1) {
						if (_23$$7) {
							_23$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _17$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_22$$7, _17$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _17$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZVAL_DOUBLE(&_24$$9, base);
							ZEPHIR_CALL_FUNCTION(&_25$$9, "log", &_10, 8, &valueA, &_24$$9);
							zephir_check_call_status();
							zephir_array_append(&rowB, &_25$$9, PH_SEPARATE, "tensor/matrix.zep", 1433);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1436);
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
PHP_METHOD(Tensor_Matrix, log1p)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, sin)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, asin)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, cos)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, acos)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, tan)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, atan)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, rad2deg)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, deg2rad)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, sum)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "array_sum");
	ZEPHIR_CALL_FUNCTION(&_2, "array_map", NULL, 14, &_1, &_0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Calculate the row product of the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, product)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "array_product");
	ZEPHIR_CALL_FUNCTION(&_2, "array_map", NULL, 14, &_1, &_0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the minimum of each row in the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, min)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "min");
	ZEPHIR_CALL_FUNCTION(&_2, "array_map", NULL, 14, &_1, &_0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the maximum of each row in the matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, max)
{
	zval _0, _1, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_INIT_VAR(&_1);
	ZVAL_STRING(&_1, "max");
	ZEPHIR_CALL_FUNCTION(&_2, "array_map", NULL, 14, &_1, &_0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &_2);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compute the means of each row and return them in a vector.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, mean)
{
	zval _0, _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_CALL_METHOD(&_0, this_ptr, "sum", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "dividescalar", NULL, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the median vector of this matrix.
 *
 * @return \Tensor\ColumnVector
 */
PHP_METHOD(Tensor_Matrix, median)
{
	zend_bool odd, _12;
	zval b;
	zval rowA, median, _0, _1, _2, _3, *_4, _5, *_6, _11, _8$$5, _9$$5, _10$$5, _13$$8, _14$$8, _15$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, mid;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&median);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_13$$8);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_15$$8);
	ZVAL_UNDEF(&b);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	ZVAL_LONG(&_1, 2);
	ZEPHIR_CALL_FUNCTION(&_2, "intdiv", NULL, 21, &_0, &_1);
	zephir_check_call_status();
	mid = zephir_get_intval(&_2);
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	odd = zephir_safe_mod_zval_long(&_1, 2) == 1;
	zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_3) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_5);
		zephir_string_to_char_array(&_5, &_3);
		_4 = &_5;
	} else {
		_4 = &_3;
	}
	zephir_is_iterable(_4, 0, "tensor/matrix.zep", 1608);
	if (Z_TYPE_P(_4) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4), _6)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _6);
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_7, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			if (odd) {
				ZEPHIR_OBS_NVAR(&median);
				zephir_array_fetch_long(&median, &rowA, mid, PH_NOISY, "tensor/matrix.zep", 1600);
			} else {
				ZEPHIR_OBS_NVAR(&_8$$5);
				zephir_array_fetch_long(&_8$$5, &rowA, (mid - 1), PH_NOISY, "tensor/matrix.zep", 1602);
				ZEPHIR_OBS_NVAR(&_9$$5);
				zephir_array_fetch_long(&_9$$5, &rowA, mid, PH_NOISY, "tensor/matrix.zep", 1602);
				ZEPHIR_INIT_NVAR(&_10$$5);
				zephir_add_function(&_10$$5, &_8$$5, &_9$$5);
				ZEPHIR_INIT_NVAR(&median);
				ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_10$$5, 2.0));
			}
			zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1605);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _4, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _4, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _4, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_7, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				if (odd) {
					ZEPHIR_OBS_NVAR(&median);
					zephir_array_fetch_long(&median, &rowA, mid, PH_NOISY, "tensor/matrix.zep", 1600);
				} else {
					ZEPHIR_OBS_NVAR(&_13$$8);
					zephir_array_fetch_long(&_13$$8, &rowA, (mid - 1), PH_NOISY, "tensor/matrix.zep", 1602);
					ZEPHIR_OBS_NVAR(&_14$$8);
					zephir_array_fetch_long(&_14$$8, &rowA, mid, PH_NOISY, "tensor/matrix.zep", 1602);
					ZEPHIR_INIT_NVAR(&_15$$8);
					zephir_add_function(&_15$$8, &_13$$8, &_14$$8);
					ZEPHIR_INIT_NVAR(&median);
					ZVAL_DOUBLE(&median, zephir_safe_div_zval_double(&_15$$8, 2.0));
				}
				zephir_array_append(&b, &median, PH_SEPARATE, "tensor/matrix.zep", 1605);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &b);
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
PHP_METHOD(Tensor_Matrix, quantile)
{
	zval b;
	zend_bool _0, _19;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_10 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, xHat;
	zval *q_param = NULL, rowA, _5, _6, *_7, _8, *_9, _18, _1$$3, _2$$3, _3$$3, _4$$3, _11$$4, _15$$4, _16$$4, _17$$4, _12$$5, _13$$5, _14$$5, _20$$6, _24$$6, _25$$6, _26$$6, _21$$7, _22$$7, _23$$7;
	double q, t = 0, x, remainder;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&_24$$6);
	ZVAL_UNDEF(&_25$$6);
	ZVAL_UNDEF(&_26$$6);
	ZVAL_UNDEF(&_21$$7);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_23$$7);
	ZVAL_UNDEF(&b);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(q_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_1$$3, "tensor/matrix.zep", 1622);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	x =  (((q * (double) ((zephir_get_numberval(&_5) - 1))) + (double) (1)));
	xHat = (int) x;
	remainder =  ((x -  (double) xHat));
	zephir_read_property_cached(&_6, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 1650);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_7), _9)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _9);
			ZEPHIR_MAKE_REF(&rowA);
			ZEPHIR_CALL_FUNCTION(NULL, "sort", &_10, 22, &rowA);
			ZEPHIR_UNREF(&rowA);
			zephir_check_call_status();
			zephir_read_property_cached(&_11$$4, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
			if (ZEPHIR_LE_LONG(&_11$$4, xHat)) {
				ZEPHIR_OBS_NVAR(&_12$$5);
				zephir_read_property_cached(&_13$$5, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
				zephir_array_fetch_long(&_12$$5, &rowA, (zephir_get_numberval(&_13$$5) - 1), PH_NOISY, "tensor/matrix.zep", 1640);
				ZEPHIR_INIT_NVAR(&_14$$5);
				ZVAL_DOUBLE(&_14$$5, zephir_get_doubleval(&_12$$5));
				zephir_array_append(&b, &_14$$5, PH_SEPARATE, "tensor/matrix.zep", 1640);
				continue;
			}
			ZEPHIR_OBS_NVAR(&_15$$4);
			zephir_array_fetch_long(&_15$$4, &rowA, (xHat - 1), PH_NOISY, "tensor/matrix.zep", 1645);
			t =  (zephir_get_doubleval(&_15$$4));
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch_long(&_16$$4, &rowA, xHat, PH_NOISY, "tensor/matrix.zep", 1647);
			ZEPHIR_INIT_NVAR(&_17$$4);
			ZVAL_DOUBLE(&_17$$4, (t + (remainder * (zephir_get_numberval(&_16$$4) - t))));
			zephir_array_append(&b, &_17$$4, PH_SEPARATE, "tensor/matrix.zep", 1647);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_19 = 1;
		while (1) {
			if (_19) {
				_19 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_18, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_18)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_MAKE_REF(&rowA);
				ZEPHIR_CALL_FUNCTION(NULL, "sort", &_10, 22, &rowA);
				ZEPHIR_UNREF(&rowA);
				zephir_check_call_status();
				zephir_read_property_cached(&_20$$6, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
				if (ZEPHIR_LE_LONG(&_20$$6, xHat)) {
					ZEPHIR_OBS_NVAR(&_21$$7);
					zephir_read_property_cached(&_22$$7, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
					zephir_array_fetch_long(&_21$$7, &rowA, (zephir_get_numberval(&_22$$7) - 1), PH_NOISY, "tensor/matrix.zep", 1640);
					ZEPHIR_INIT_NVAR(&_23$$7);
					ZVAL_DOUBLE(&_23$$7, zephir_get_doubleval(&_21$$7));
					zephir_array_append(&b, &_23$$7, PH_SEPARATE, "tensor/matrix.zep", 1640);
					continue;
				}
				ZEPHIR_OBS_NVAR(&_24$$6);
				zephir_array_fetch_long(&_24$$6, &rowA, (xHat - 1), PH_NOISY, "tensor/matrix.zep", 1645);
				t =  (zephir_get_doubleval(&_24$$6));
				ZEPHIR_OBS_NVAR(&_25$$6);
				zephir_array_fetch_long(&_25$$6, &rowA, xHat, PH_NOISY, "tensor/matrix.zep", 1647);
				ZEPHIR_INIT_NVAR(&_26$$6);
				ZVAL_DOUBLE(&_26$$6, (t + (remainder * (zephir_get_numberval(&_25$$6) - t))));
				zephir_array_append(&b, &_26$$6, PH_SEPARATE, "tensor/matrix.zep", 1647);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_columnvector_ce, "quick", NULL, 0, &b);
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
PHP_METHOD(Tensor_Matrix, variance)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ZVAL_OR_NULL(mean)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
			zephir_throw_exception_debug(&_0$$4, "tensor/matrix.zep", 1666);
			ZEPHIR_MM_RESTORE();
			return;
		}
		ZEPHIR_CALL_METHOD(&_3$$3, mean, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_4$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
		if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_3$$3, &_4$$3))) {
			ZEPHIR_INIT_VAR(&_5$$5);
			object_init_ex(&_5$$5, tensor_exceptions_dimensionalitymismatch_ce);
			zephir_memory_observe(&_6$$5);
			zephir_read_property_cached(&_6$$5, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
			zephir_cast_to_string(&_7$$5, &_6$$5);
			ZEPHIR_CALL_METHOD(&_8$$5, mean, "m", NULL, 0);
			zephir_check_call_status();
			zephir_cast_to_string(&_9$$5, &_8$$5);
			ZEPHIR_INIT_VAR(&_10$$5);
			ZEPHIR_CONCAT_SSVSVS(&_10$$5, "Mean vector must", " have ", &_7$$5, " rows, ", &_9$$5, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_5$$5, "__construct", NULL, 3, &_10$$5);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_5$$5, "tensor/matrix.zep", 1672);
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
	zephir_read_property_cached(&_14, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, covariance)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}

	bool is_null_true = 1;
	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_OBJECT_OF_CLASS_OR_NULL(mean, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_read_property_cached(&_1$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
		if (!ZEPHIR_IS_IDENTICAL(&_0$$3, &_1$$3)) {
			ZEPHIR_INIT_VAR(&_2$$4);
			object_init_ex(&_2$$4, tensor_exceptions_dimensionalitymismatch_ce);
			zephir_memory_observe(&_3$$4);
			zephir_read_property_cached(&_3$$4, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
			zephir_cast_to_string(&_4$$4, &_3$$4);
			ZEPHIR_CALL_METHOD(&_5$$4, mean, "m", NULL, 0);
			zephir_check_call_status();
			zephir_cast_to_string(&_6$$4, &_5$$4);
			ZEPHIR_INIT_VAR(&_7$$4);
			ZEPHIR_CONCAT_SSVSVS(&_7$$4, "Mean vector must", " have ", &_4$$4, " rows, ", &_6$$4, " given.");
			ZEPHIR_CALL_METHOD(NULL, &_2$$4, "__construct", NULL, 3, &_7$$4);
			zephir_check_call_status();
			zephir_throw_exception_debug(&_2$$4, "tensor/matrix.zep", 1697);
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
	zephir_read_property_cached(&_10, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, round)
{
	zend_bool _19, _15$$5, _26$$8;
	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *precision_param = NULL, _0$$3, _1$$4, _2$$4, _3$$4, _4$$4, rowA, valueA, _5, *_6, _7, *_8, _18, *_9$$5, _10$$5, *_11$$5, _14$$5, _12$$6, _13$$6, _16$$7, _17$$7, *_20$$8, _21$$8, *_22$$8, _25$$8, _23$$9, _24$$9, _27$$10, _28$$10;
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
	ZVAL_UNDEF(&_18);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_13$$6);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_21$$8);
	ZVAL_UNDEF(&_25$$8);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_27$$10);
	ZVAL_UNDEF(&_28$$10);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(precision)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 0, 1, &precision_param);
	if (!precision_param) {
		precision = 0;
	} else {
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
		zephir_throw_exception_debug(&_1$$4, "tensor/matrix.zep", 1723);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property_cached(&_5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_5) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_7);
		zephir_string_to_char_array(&_7, &_5);
		_6 = &_7;
	} else {
		_6 = &_5;
	}
	zephir_is_iterable(_6, 0, "tensor/matrix.zep", 1741);
	if (Z_TYPE_P(_6) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_6), _8)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _8);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_10$$5);
				zephir_string_to_char_array(&_10$$5, &rowA);
				_9$$5 = &_10$$5;
			} else {
				_9$$5 = &rowA;
			}
			zephir_is_iterable(_9$$5, 0, "tensor/matrix.zep", 1738);
			if (Z_TYPE_P(_9$$5) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9$$5), _11$$5)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _11$$5);
					ZEPHIR_INIT_NVAR(&_12$$6);
					ZVAL_LONG(&_13$$6, precision);
					zephir_round(&_12$$6, &valueA, &_13$$6, NULL);
					zephir_array_append(&rowB, &_12$$6, PH_SEPARATE, "tensor/matrix.zep", 1735);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9$$5, "rewind", NULL, 0);
				zephir_check_call_status();
				_15$$5 = 1;
				while (1) {
					if (_15$$5) {
						_15$$5 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _9$$5, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_14$$5, _9$$5, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$5)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _9$$5, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_16$$7);
						ZVAL_LONG(&_17$$7, precision);
						zephir_round(&_16$$7, &valueA, &_17$$7, NULL);
						zephir_array_append(&rowB, &_16$$7, PH_SEPARATE, "tensor/matrix.zep", 1735);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1738);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _6, "rewind", NULL, 0);
		zephir_check_call_status();
		_19 = 1;
		while (1) {
			if (_19) {
				_19 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _6, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_18, _6, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_18)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _6, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_21$$8);
					zephir_string_to_char_array(&_21$$8, &rowA);
					_20$$8 = &_21$$8;
				} else {
					_20$$8 = &rowA;
				}
				zephir_is_iterable(_20$$8, 0, "tensor/matrix.zep", 1738);
				if (Z_TYPE_P(_20$$8) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_20$$8), _22$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _22$$8);
						ZEPHIR_INIT_NVAR(&_23$$9);
						ZVAL_LONG(&_24$$9, precision);
						zephir_round(&_23$$9, &valueA, &_24$$9, NULL);
						zephir_array_append(&rowB, &_23$$9, PH_SEPARATE, "tensor/matrix.zep", 1735);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _20$$8, "rewind", NULL, 0);
					zephir_check_call_status();
					_26$$8 = 1;
					while (1) {
						if (_26$$8) {
							_26$$8 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _20$$8, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_25$$8, _20$$8, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_25$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _20$$8, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_27$$10);
							ZVAL_LONG(&_28$$10, precision);
							zephir_round(&_27$$10, &valueA, &_28$$10, NULL);
							zephir_array_append(&rowB, &_27$$10, PH_SEPARATE, "tensor/matrix.zep", 1735);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1738);
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
PHP_METHOD(Tensor_Matrix, floor)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, ceil)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

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
PHP_METHOD(Tensor_Matrix, clip)
{
	zend_bool _16, _12$$4, _23$$11;
	zval b, rowB;
	zval _1$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *min_param = NULL, *max_param = NULL, _0$$3, rowA, valueA, _2, *_3, _4, *_5, _15, *_6$$4, _7$$4, *_8$$4, _11$$4, _9$$6, _10$$7, _13$$9, _14$$10, *_17$$11, _18$$11, *_19$$11, _22$$11, _20$$13, _21$$14, _24$$16, _25$$17;
	double min, max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_13$$9);
	ZVAL_UNDEF(&_14$$10);
	ZVAL_UNDEF(&_18$$11);
	ZVAL_UNDEF(&_22$$11);
	ZVAL_UNDEF(&_20$$13);
	ZVAL_UNDEF(&_21$$14);
	ZVAL_UNDEF(&_24$$16);
	ZVAL_UNDEF(&_25$$17);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(min_param)
		Z_PARAM_ZVAL(max_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/matrix.zep", 1777);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property_cached(&_2, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_2) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_4);
		zephir_string_to_char_array(&_4, &_2);
		_3 = &_4;
	} else {
		_3 = &_2;
	}
	zephir_is_iterable(_3, 0, "tensor/matrix.zep", 1807);
	if (Z_TYPE_P(_3) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_3), _5)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _5);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_7$$4);
				zephir_string_to_char_array(&_7$$4, &rowA);
				_6$$4 = &_7$$4;
			} else {
				_6$$4 = &rowA;
			}
			zephir_is_iterable(_6$$4, 0, "tensor/matrix.zep", 1804);
			if (Z_TYPE_P(_6$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_6$$4), _8$$4)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _8$$4);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_9$$6);
						ZVAL_DOUBLE(&_9$$6, max);
						zephir_array_append(&rowB, &_9$$6, PH_SEPARATE, "tensor/matrix.zep", 1790);
						continue;
					}
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_10$$7);
						ZVAL_DOUBLE(&_10$$7, min);
						zephir_array_append(&rowB, &_10$$7, PH_SEPARATE, "tensor/matrix.zep", 1796);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1801);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _6$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_12$$4 = 1;
				while (1) {
					if (_12$$4) {
						_12$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _6$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_11$$4, _6$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_11$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _6$$4, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_13$$9);
							ZVAL_DOUBLE(&_13$$9, max);
							zephir_array_append(&rowB, &_13$$9, PH_SEPARATE, "tensor/matrix.zep", 1790);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_14$$10);
							ZVAL_DOUBLE(&_14$$10, min);
							zephir_array_append(&rowB, &_14$$10, PH_SEPARATE, "tensor/matrix.zep", 1796);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1801);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1804);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _3, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _3, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _3, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _3, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_18$$11);
					zephir_string_to_char_array(&_18$$11, &rowA);
					_17$$11 = &_18$$11;
				} else {
					_17$$11 = &rowA;
				}
				zephir_is_iterable(_17$$11, 0, "tensor/matrix.zep", 1804);
				if (Z_TYPE_P(_17$$11) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_17$$11), _19$$11)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$11);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_20$$13);
							ZVAL_DOUBLE(&_20$$13, max);
							zephir_array_append(&rowB, &_20$$13, PH_SEPARATE, "tensor/matrix.zep", 1790);
							continue;
						}
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_21$$14);
							ZVAL_DOUBLE(&_21$$14, min);
							zephir_array_append(&rowB, &_21$$14, PH_SEPARATE, "tensor/matrix.zep", 1796);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1801);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _17$$11, "rewind", NULL, 0);
					zephir_check_call_status();
					_23$$11 = 1;
					while (1) {
						if (_23$$11) {
							_23$$11 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _17$$11, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_22$$11, _17$$11, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_22$$11)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _17$$11, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
								ZEPHIR_INIT_NVAR(&_24$$16);
								ZVAL_DOUBLE(&_24$$16, max);
								zephir_array_append(&rowB, &_24$$16, PH_SEPARATE, "tensor/matrix.zep", 1790);
								continue;
							}
							if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
								ZEPHIR_INIT_NVAR(&_25$$17);
								ZVAL_DOUBLE(&_25$$17, min);
								zephir_array_append(&rowB, &_25$$17, PH_SEPARATE, "tensor/matrix.zep", 1796);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1801);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1804);
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
PHP_METHOD(Tensor_Matrix, clipLower)
{
	zend_bool _12, _9$$3, _18$$8;
	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *min_param = NULL, rowA, valueA, _0, *_1, _2, *_3, _11, *_4$$3, _5$$3, *_6$$3, _8$$3, _7$$5, _10$$7, *_13$$8, _14$$8, *_15$$8, _17$$8, _16$$10, _19$$12;
	double min;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(min_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &min_param);
	min = zephir_get_doubleval(min_param);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 1839);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &rowA);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &rowA;
			}
			zephir_is_iterable(_4$$3, 0, "tensor/matrix.zep", 1836);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _6$$3);
					if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
						ZEPHIR_INIT_NVAR(&_7$$5);
						ZVAL_DOUBLE(&_7$$5, min);
						zephir_array_append(&rowB, &_7$$5, PH_SEPARATE, "tensor/matrix.zep", 1828);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1833);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_9$$3 = 1;
				while (1) {
					if (_9$$3) {
						_9$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_8$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_8$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_10$$7);
							ZVAL_DOUBLE(&_10$$7, min);
							zephir_array_append(&rowB, &_10$$7, PH_SEPARATE, "tensor/matrix.zep", 1828);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1833);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1836);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_14$$8);
					zephir_string_to_char_array(&_14$$8, &rowA);
					_13$$8 = &_14$$8;
				} else {
					_13$$8 = &rowA;
				}
				zephir_is_iterable(_13$$8, 0, "tensor/matrix.zep", 1836);
				if (Z_TYPE_P(_13$$8) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13$$8), _15$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _15$$8);
						if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
							ZEPHIR_INIT_NVAR(&_16$$10);
							ZVAL_DOUBLE(&_16$$10, min);
							zephir_array_append(&rowB, &_16$$10, PH_SEPARATE, "tensor/matrix.zep", 1828);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1833);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _13$$8, "rewind", NULL, 0);
					zephir_check_call_status();
					_18$$8 = 1;
					while (1) {
						if (_18$$8) {
							_18$$8 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _13$$8, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_17$$8, _13$$8, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_17$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _13$$8, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_LT_DOUBLE(&valueA, min)) {
								ZEPHIR_INIT_NVAR(&_19$$12);
								ZVAL_DOUBLE(&_19$$12, min);
								zephir_array_append(&rowB, &_19$$12, PH_SEPARATE, "tensor/matrix.zep", 1828);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1833);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1836);
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
PHP_METHOD(Tensor_Matrix, clipUpper)
{
	zend_bool _12, _9$$3, _18$$8;
	zval b, rowB;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *max_param = NULL, rowA, valueA, _0, *_1, _2, *_3, _11, *_4$$3, _5$$3, *_6$$3, _8$$3, _7$$5, _10$$7, *_13$$8, _14$$8, *_15$$8, _17$$8, _16$$10, _19$$12;
	double max;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_10$$7);
	ZVAL_UNDEF(&_14$$8);
	ZVAL_UNDEF(&_17$$8);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_19$$12);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(max_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &max_param);
	max = zephir_get_doubleval(max_param);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 1871);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &rowA);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &rowA;
			}
			zephir_is_iterable(_4$$3, 0, "tensor/matrix.zep", 1868);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _6$$3);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						ZEPHIR_INIT_NVAR(&_7$$5);
						ZVAL_DOUBLE(&_7$$5, max);
						zephir_array_append(&rowB, &_7$$5, PH_SEPARATE, "tensor/matrix.zep", 1860);
						continue;
					}
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1865);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_9$$3 = 1;
				while (1) {
					if (_9$$3) {
						_9$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_8$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_8$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_10$$7);
							ZVAL_DOUBLE(&_10$$7, max);
							zephir_array_append(&rowB, &_10$$7, PH_SEPARATE, "tensor/matrix.zep", 1860);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1865);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1868);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_12 = 1;
		while (1) {
			if (_12) {
				_12 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_11, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_11)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_14$$8);
					zephir_string_to_char_array(&_14$$8, &rowA);
					_13$$8 = &_14$$8;
				} else {
					_13$$8 = &rowA;
				}
				zephir_is_iterable(_13$$8, 0, "tensor/matrix.zep", 1868);
				if (Z_TYPE_P(_13$$8) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_13$$8), _15$$8)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _15$$8);
						if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
							ZEPHIR_INIT_NVAR(&_16$$10);
							ZVAL_DOUBLE(&_16$$10, max);
							zephir_array_append(&rowB, &_16$$10, PH_SEPARATE, "tensor/matrix.zep", 1860);
							continue;
						}
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1865);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _13$$8, "rewind", NULL, 0);
					zephir_check_call_status();
					_18$$8 = 1;
					while (1) {
						if (_18$$8) {
							_18$$8 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _13$$8, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_17$$8, _13$$8, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_17$$8)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _13$$8, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
								ZEPHIR_INIT_NVAR(&_19$$12);
								ZVAL_DOUBLE(&_19$$12, max);
								zephir_array_append(&rowB, &_19$$12, PH_SEPARATE, "tensor/matrix.zep", 1860);
								continue;
							}
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1865);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1868);
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
PHP_METHOD(Tensor_Matrix, sign)
{
	zend_bool _16, _11$$3, _24$$12;
	zval b, rowB;
	zval rowA, valueA, _0, *_1, _2, *_3, _15, *_4$$3, _5$$3, *_6$$3, _10$$3, _7$$5, _8$$6, _9$$7, _12$$9, _13$$10, _14$$11, *_17$$12, _18$$12, *_19$$12, _23$$12, _20$$14, _21$$15, _22$$16, _25$$18, _26$$19, _27$$20;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$7);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_13$$10);
	ZVAL_UNDEF(&_14$$11);
	ZVAL_UNDEF(&_18$$12);
	ZVAL_UNDEF(&_23$$12);
	ZVAL_UNDEF(&_20$$14);
	ZVAL_UNDEF(&_21$$15);
	ZVAL_UNDEF(&_22$$16);
	ZVAL_UNDEF(&_25$$18);
	ZVAL_UNDEF(&_26$$19);
	ZVAL_UNDEF(&_27$$20);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 1902);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &rowA);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &rowA;
			}
			zephir_is_iterable(_4$$3, 0, "tensor/matrix.zep", 1899);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _6$$3);
					if (ZEPHIR_GT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_7$$5);
						ZVAL_DOUBLE(&_7$$5, 1.0);
						zephir_array_append(&rowB, &_7$$5, PH_SEPARATE, "tensor/matrix.zep", 1891);
					} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
						ZEPHIR_INIT_NVAR(&_8$$6);
						ZVAL_DOUBLE(&_8$$6, -1.0);
						zephir_array_append(&rowB, &_8$$6, PH_SEPARATE, "tensor/matrix.zep", 1893);
					} else {
						ZEPHIR_INIT_NVAR(&_9$$7);
						ZVAL_DOUBLE(&_9$$7, 0.0);
						zephir_array_append(&rowB, &_9$$7, PH_SEPARATE, "tensor/matrix.zep", 1895);
					}
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_11$$3 = 1;
				while (1) {
					if (_11$$3) {
						_11$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_10$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_10$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						if (ZEPHIR_GT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_12$$9);
							ZVAL_DOUBLE(&_12$$9, 1.0);
							zephir_array_append(&rowB, &_12$$9, PH_SEPARATE, "tensor/matrix.zep", 1891);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_13$$10);
							ZVAL_DOUBLE(&_13$$10, -1.0);
							zephir_array_append(&rowB, &_13$$10, PH_SEPARATE, "tensor/matrix.zep", 1893);
						} else {
							ZEPHIR_INIT_NVAR(&_14$$11);
							ZVAL_DOUBLE(&_14$$11, 0.0);
							zephir_array_append(&rowB, &_14$$11, PH_SEPARATE, "tensor/matrix.zep", 1895);
						}
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1899);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_18$$12);
					zephir_string_to_char_array(&_18$$12, &rowA);
					_17$$12 = &_18$$12;
				} else {
					_17$$12 = &rowA;
				}
				zephir_is_iterable(_17$$12, 0, "tensor/matrix.zep", 1899);
				if (Z_TYPE_P(_17$$12) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_17$$12), _19$$12)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _19$$12);
						if (ZEPHIR_GT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_20$$14);
							ZVAL_DOUBLE(&_20$$14, 1.0);
							zephir_array_append(&rowB, &_20$$14, PH_SEPARATE, "tensor/matrix.zep", 1891);
						} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
							ZEPHIR_INIT_NVAR(&_21$$15);
							ZVAL_DOUBLE(&_21$$15, -1.0);
							zephir_array_append(&rowB, &_21$$15, PH_SEPARATE, "tensor/matrix.zep", 1893);
						} else {
							ZEPHIR_INIT_NVAR(&_22$$16);
							ZVAL_DOUBLE(&_22$$16, 0.0);
							zephir_array_append(&rowB, &_22$$16, PH_SEPARATE, "tensor/matrix.zep", 1895);
						}
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _17$$12, "rewind", NULL, 0);
					zephir_check_call_status();
					_24$$12 = 1;
					while (1) {
						if (_24$$12) {
							_24$$12 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _17$$12, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_23$$12, _17$$12, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_23$$12)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _17$$12, "current", NULL, 0);
						zephir_check_call_status();
							if (ZEPHIR_GT_LONG(&valueA, 0)) {
								ZEPHIR_INIT_NVAR(&_25$$18);
								ZVAL_DOUBLE(&_25$$18, 1.0);
								zephir_array_append(&rowB, &_25$$18, PH_SEPARATE, "tensor/matrix.zep", 1891);
							} else if (ZEPHIR_LT_LONG(&valueA, 0)) {
								ZEPHIR_INIT_NVAR(&_26$$19);
								ZVAL_DOUBLE(&_26$$19, -1.0);
								zephir_array_append(&rowB, &_26$$19, PH_SEPARATE, "tensor/matrix.zep", 1893);
							} else {
								ZEPHIR_INIT_NVAR(&_27$$20);
								ZVAL_DOUBLE(&_27$$20, 0.0);
								zephir_array_append(&rowB, &_27$$20, PH_SEPARATE, "tensor/matrix.zep", 1895);
							}
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1899);
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
PHP_METHOD(Tensor_Matrix, negate)
{
	zend_bool _10, _8$$3, _15$$6;
	zval b, rowB;
	zval rowA, valueA, _0, *_1, _2, *_3, _9, *_4$$3, _5$$3, *_6$$3, _7$$3, *_11$$6, _12$$6, *_13$$6, _14$$6;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_12$$6);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 1927);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&rowB);
			array_init(&rowB);
			if (Z_TYPE_P(&rowA) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_5$$3);
				zephir_string_to_char_array(&_5$$3, &rowA);
				_4$$3 = &_5$$3;
			} else {
				_4$$3 = &rowA;
			}
			zephir_is_iterable(_4$$3, 0, "tensor/matrix.zep", 1924);
			if (Z_TYPE_P(_4$$3) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_4$$3), _6$$3)
				{
					ZEPHIR_INIT_NVAR(&valueA);
					ZVAL_COPY(&valueA, _6$$3);
					zephir_negate(&valueA);
					zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1921);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _4$$3, "rewind", NULL, 0);
				zephir_check_call_status();
				_8$$3 = 1;
				while (1) {
					if (_8$$3) {
						_8$$3 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _4$$3, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_7$$3, _4$$3, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_7$$3)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueA, _4$$3, "current", NULL, 0);
					zephir_check_call_status();
						zephir_negate(&valueA);
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1921);
				}
			}
			ZEPHIR_INIT_NVAR(&valueA);
			zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1924);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_10 = 1;
		while (1) {
			if (_10) {
				_10 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_9, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_9)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&rowB);
				array_init(&rowB);
				if (Z_TYPE_P(&rowA) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_12$$6);
					zephir_string_to_char_array(&_12$$6, &rowA);
					_11$$6 = &_12$$6;
				} else {
					_11$$6 = &rowA;
				}
				zephir_is_iterable(_11$$6, 0, "tensor/matrix.zep", 1924);
				if (Z_TYPE_P(_11$$6) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_11$$6), _13$$6)
					{
						ZEPHIR_INIT_NVAR(&valueA);
						ZVAL_COPY(&valueA, _13$$6);
						zephir_negate(&valueA);
						zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1921);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _11$$6, "rewind", NULL, 0);
					zephir_check_call_status();
					_15$$6 = 1;
					while (1) {
						if (_15$$6) {
							_15$$6 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _11$$6, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_14$$6, _11$$6, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_14$$6)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueA, _11$$6, "current", NULL, 0);
						zephir_check_call_status();
							zephir_negate(&valueA);
							zephir_array_append(&rowB, &valueA, PH_SEPARATE, "tensor/matrix.zep", 1921);
					}
				}
				ZEPHIR_INIT_NVAR(&valueA);
				zephir_array_append(&b, &rowB, PH_SEPARATE, "tensor/matrix.zep", 1924);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
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
PHP_METHOD(Tensor_Matrix, augmentAbove)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_5$$3);
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " columns but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 1942);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_CALL_METHOD(&_11, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_12, this_ptr, _zephir_prop_2, 14, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, augmentBelow)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	static zend_string *_zephir_prop_2 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_2)) {
		_zephir_prop_2 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_3, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_5$$3);
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_1, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " columns but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 1960);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&_10);
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_2, 14, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, augmentLeft)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_5$$3);
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " rows but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 1978);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&_10, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_11, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, augmentRight)
{
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
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	_1 = ZEPHIR_GT_LONG(&_0, 0);
	if (_1) {
		ZEPHIR_CALL_METHOD(&_2, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_read_property_cached(&_3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
		_1 = !ZEPHIR_IS_IDENTICAL(&_2, &_3);
	}
	if (UNEXPECTED(_1)) {
		ZEPHIR_INIT_VAR(&_4$$3);
		object_init_ex(&_4$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_5$$3);
		zephir_read_property_cached(&_5$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_CALL_METHOD(&_7$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_8$$3, &_7$$3);
		ZEPHIR_INIT_VAR(&_9$$3);
		ZEPHIR_CONCAT_SVSVS(&_9$$3, "Matrix A requires", &_6$$3, " rows but Matrix B has ", &_8$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_4$$3, "__construct", NULL, 3, &_9$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_4$$3, "tensor/matrix.zep", 1996);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_read_property_cached(&_10, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
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
PHP_METHOD(Tensor_Matrix, repeat)
{
	zend_bool _7$$3;
	zval b, temp;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *m_param = NULL, *n_param = NULL, rowA, _10, _11, _0$$3, *_1$$3, _2$$3, *_3$$3, _6$$3, _4$$4, _5$$4, _8$$6, _9$$6;
	zend_long m, n, ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_4$$4);
	ZVAL_UNDEF(&_5$$4);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&temp);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(m)
		Z_PARAM_LONG(n)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &m_param, &n_param);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&temp);
	array_init(&temp);
	if (n > 0) {
		zephir_read_property_cached(&_0$$3, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
		if (Z_TYPE_P(&_0$$3) == IS_STRING) {
			ZEPHIR_INIT_VAR(&_2$$3);
			zephir_string_to_char_array(&_2$$3, &_0$$3);
			_1$$3 = &_2$$3;
		} else {
			_1$$3 = &_0$$3;
		}
		zephir_is_iterable(_1$$3, 0, "tensor/matrix.zep", 2026);
		if (Z_TYPE_P(_1$$3) == IS_ARRAY) {
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1$$3), _3$$3)
			{
				ZEPHIR_INIT_NVAR(&rowA);
				ZVAL_COPY(&rowA, _3$$3);
				ZEPHIR_INIT_NVAR(&temp);
				array_init(&temp);
				while (1) {
					if (!(zephir_fast_count_int(&temp) <= n)) {
						break;
					}
					zephir_array_append(&temp, &rowA, PH_SEPARATE, "tensor/matrix.zep", 2021);
				}
				ZEPHIR_INIT_NVAR(&_4$$4);
				ZEPHIR_INIT_NVAR(&_5$$4);
				ZVAL_STRING(&_5$$4, "array_merge");
				ZEPHIR_CALL_USER_FUNC_ARRAY(&_4$$4, &_5$$4, &temp);
				zephir_check_call_status();
				zephir_array_append(&b, &_4$$4, PH_SEPARATE, "tensor/matrix.zep", 2024);
			} ZEND_HASH_FOREACH_END();
		} else {
			ZEPHIR_CALL_METHOD(NULL, _1$$3, "rewind", NULL, 0);
			zephir_check_call_status();
			_7$$3 = 1;
			while (1) {
				if (_7$$3) {
					_7$$3 = 0;
				} else {
					ZEPHIR_CALL_METHOD(NULL, _1$$3, "next", NULL, 0);
					zephir_check_call_status();
				}
				ZEPHIR_CALL_METHOD(&_6$$3, _1$$3, "valid", NULL, 0);
				zephir_check_call_status();
				if (!zend_is_true(&_6$$3)) {
					break;
				}
				ZEPHIR_CALL_METHOD(&rowA, _1$$3, "current", NULL, 0);
				zephir_check_call_status();
					ZEPHIR_INIT_NVAR(&temp);
					array_init(&temp);
					while (1) {
						if (!(zephir_fast_count_int(&temp) <= n)) {
							break;
						}
						zephir_array_append(&temp, &rowA, PH_SEPARATE, "tensor/matrix.zep", 2021);
					}
					ZEPHIR_INIT_NVAR(&_8$$6);
					ZEPHIR_INIT_NVAR(&_9$$6);
					ZVAL_STRING(&_9$$6, "array_merge");
					ZEPHIR_CALL_USER_FUNC_ARRAY(&_8$$6, &_9$$6, &temp);
					zephir_check_call_status();
					zephir_array_append(&b, &_8$$6, PH_SEPARATE, "tensor/matrix.zep", 2024);
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
		zephir_array_append(&temp, &b, PH_SEPARATE, "tensor/matrix.zep", 2031);
	}
	ZEPHIR_INIT_VAR(&_10);
	ZEPHIR_INIT_VAR(&_11);
	ZVAL_STRING(&_11, "array_merge");
	ZEPHIR_CALL_USER_FUNC_ARRAY(&_10, &_11, &temp);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &_10);
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
PHP_METHOD(Tensor_Matrix, multiplyMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2048);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2059);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2056);
			tensor_multiply(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2056);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2056);
				tensor_multiply(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2056);
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
PHP_METHOD(Tensor_Matrix, divideMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2073);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2084);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2081);
			tensor_divide(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2081);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2081);
				tensor_divide(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2081);
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
PHP_METHOD(Tensor_Matrix, addMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2098);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2109);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2106);
			tensor_add(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2106);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2106);
				tensor_add(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2106);
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
PHP_METHOD(Tensor_Matrix, subtractMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2123);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2134);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2131);
			tensor_subtract(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2131);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2131);
				tensor_subtract(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2131);
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
PHP_METHOD(Tensor_Matrix, powMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2149);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2160);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2157);
			tensor_pow(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2157);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2157);
				tensor_pow(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2157);
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
PHP_METHOD(Tensor_Matrix, modMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2175);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2186);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2183);
			tensor_mod(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2183);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2183);
				tensor_mod(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2183);
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
PHP_METHOD(Tensor_Matrix, equalMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2201);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2212);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2209);
			tensor_equal(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2209);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2209);
				tensor_equal(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2209);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise not equal comparison of this matrix and another matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2226);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2237);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2234);
			tensor_not_equal(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2234);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2234);
				tensor_not_equal(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2234);
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
PHP_METHOD(Tensor_Matrix, greaterMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2252);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2263);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2260);
			tensor_greater(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2260);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2260);
				tensor_greater(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2260);
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
PHP_METHOD(Tensor_Matrix, greaterEqualMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2278);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2289);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2286);
			tensor_greater_equal(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2286);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2286);
				tensor_greater_equal(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2286);
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
PHP_METHOD(Tensor_Matrix, lessMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2303);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2314);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2311);
			tensor_less(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2311);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2311);
				tensor_less(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2311);
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
PHP_METHOD(Tensor_Matrix, lessEqualMatrix)
{
	zend_bool _16;
	zend_string *_11;
	zend_ulong _10;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, _6, *_7, _8, *_9, _15, _2$$3, _3$$3, _4$$3, _5$$3, _12$$4, _13$$4, _14$$4, _17$$5, _18$$5, _19$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_17$$5);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_matrix_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2328);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_6, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_6) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_8);
		zephir_string_to_char_array(&_8, &_6);
		_7 = &_8;
	} else {
		_7 = &_6;
	}
	zephir_is_iterable(_7, 0, "tensor/matrix.zep", 2339);
	if (Z_TYPE_P(_7) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_7), _10, _11, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			ZEPHIR_INIT_NVAR(&_12$$4);
			zephir_read_property_cached(&_13$$4, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_14$$4);
			zephir_array_fetch(&_14$$4, &_13$$4, &i, PH_NOISY, "tensor/matrix.zep", 2336);
			tensor_less_equal(&_12$$4, &_14$$4, &rowB);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2336);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _7, "rewind", NULL, 0);
		zephir_check_call_status();
		_16 = 1;
		while (1) {
			if (_16) {
				_16 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _7, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_15, _7, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_15)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _7, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _7, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_17$$5);
				zephir_read_property_cached(&_18$$5, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_19$$5);
				zephir_array_fetch(&_19$$5, &_18$$5, &i, PH_NOISY, "tensor/matrix.zep", 2336);
				tensor_less_equal(&_17$$5, &_19$$5, &rowB);
				zephir_array_append(&c, &_17$$5, PH_SEPARATE, "tensor/matrix.zep", 2336);
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
PHP_METHOD(Tensor_Matrix, multiplyVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2354);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2367);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_multiply(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2364);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_multiply(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2364);
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
PHP_METHOD(Tensor_Matrix, divideVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2382);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2395);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_divide(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2392);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_divide(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2392);
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
PHP_METHOD(Tensor_Matrix, addVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2410);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2423);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_add(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2420);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_add(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2420);
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
PHP_METHOD(Tensor_Matrix, subtractVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2438);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2451);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_subtract(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2448);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_subtract(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2448);
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
PHP_METHOD(Tensor_Matrix, powVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2466);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2479);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_pow(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2476);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_pow(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2476);
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
PHP_METHOD(Tensor_Matrix, modVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2494);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2507);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_mod(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2504);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_mod(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2504);
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
PHP_METHOD(Tensor_Matrix, equalVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2523);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2536);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_equal(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2533);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_equal(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2533);
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
PHP_METHOD(Tensor_Matrix, notEqualVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2551);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2564);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_not_equal(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2561);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_not_equal(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2561);
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
PHP_METHOD(Tensor_Matrix, greaterVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2579);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2592);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_greater(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2589);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_greater(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2589);
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
PHP_METHOD(Tensor_Matrix, greaterEqualVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2607);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2620);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_greater_equal(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2617);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_greater_equal(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2617);
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
PHP_METHOD(Tensor_Matrix, lessVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2635);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2648);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_less(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2645);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_less(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2645);
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
PHP_METHOD(Tensor_Matrix, lessEqualVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _14;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, rowA, bHat, _8, *_9, _10, *_11, _13, _2$$3, _3$$3, _5$$3, _12$$4, _15$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&bHat);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("n", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_vector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "n", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 16, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "n", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " columns but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2664);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&bHat, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_8, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2677);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_9), _11)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _11);
			ZEPHIR_INIT_NVAR(&_12$$4);
			tensor_less_equal(&_12$$4, &rowA, &bHat);
			zephir_array_append(&c, &_12$$4, PH_SEPARATE, "tensor/matrix.zep", 2674);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_14 = 1;
		while (1) {
			if (_14) {
				_14 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_13, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_13)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_15$$5);
				tensor_less_equal(&_15$$5, &rowA, &bHat);
				zephir_array_append(&c, &_15$$5, PH_SEPARATE, "tensor/matrix.zep", 2674);
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
PHP_METHOD(Tensor_Matrix, multiplyColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2692);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2703);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2700);
			tensor_multiply_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2700);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2700);
				tensor_multiply_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2700);
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
PHP_METHOD(Tensor_Matrix, divideColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2718);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2729);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2726);
			tensor_divide_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2726);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2726);
				tensor_divide_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2726);
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
PHP_METHOD(Tensor_Matrix, addColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2744);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2755);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2752);
			tensor_add_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2752);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2752);
				tensor_add_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2752);
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
PHP_METHOD(Tensor_Matrix, subtractColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2770);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2781);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2778);
			tensor_subtract_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2778);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2778);
				tensor_subtract_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2778);
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
PHP_METHOD(Tensor_Matrix, powColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2796);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2807);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2804);
			tensor_pow_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2804);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2804);
				tensor_pow_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2804);
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
PHP_METHOD(Tensor_Matrix, modColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2822);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2833);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2830);
			tensor_mod_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2830);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2830);
				tensor_mod_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2830);
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
PHP_METHOD(Tensor_Matrix, equalColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2848);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2859);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2856);
			tensor_equal_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2856);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2856);
				tensor_equal_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2856);
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
PHP_METHOD(Tensor_Matrix, notEqualColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2874);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2885);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2882);
			tensor_not_equal_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2882);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2882);
				tensor_not_equal_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2882);
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
PHP_METHOD(Tensor_Matrix, greaterColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2900);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2911);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2908);
			tensor_greater_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2908);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2908);
				tensor_greater_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2908);
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
PHP_METHOD(Tensor_Matrix, greaterEqualColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2926);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2937);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2934);
			tensor_greater_equal_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2934);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2934);
				tensor_greater_equal_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2934);
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
PHP_METHOD(Tensor_Matrix, lessColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2952);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2963);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2960);
			tensor_less_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2960);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2960);
				tensor_less_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2960);
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
PHP_METHOD(Tensor_Matrix, lessEqualColumnVector)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _18;
	zend_string *_13;
	zend_ulong _12;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, valueB, _8, *_9, _10, *_11, _17, _2$$3, _3$$3, _5$$3, _14$$4, _15$$4, _16$$4, _19$$5, _20$$5, _21$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_6$$3);
	ZVAL_UNDEF(&_7$$3);
	static zend_string *_zephir_prop_0 = NULL;
	static zend_string *_zephir_prop_1 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("m", 1, 1);
	}
	if (UNEXPECTED(!_zephir_prop_1)) {
		_zephir_prop_1 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, tensor_columnvector_ce)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, b, "m", NULL, 0);
	zephir_check_call_status();
	zephir_read_property_cached(&_1, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC | PH_READONLY);
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 15, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Matrix A expects ", &_4$$3, " rows but Vector B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/matrix.zep", 2978);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/matrix.zep", 2989);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&valueB);
			ZVAL_COPY(&valueB, _11);
			ZEPHIR_INIT_NVAR(&_14$$4);
			zephir_read_property_cached(&_15$$4, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&_16$$4);
			zephir_array_fetch(&_16$$4, &_15$$4, &i, PH_NOISY, "tensor/matrix.zep", 2986);
			tensor_less_equal_scalar(&_14$$4, &_16$$4, &valueB);
			zephir_array_append(&c, &_14$$4, PH_SEPARATE, "tensor/matrix.zep", 2986);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_18 = 1;
		while (1) {
			if (_18) {
				_18 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_17, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_17)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&valueB, _9, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_19$$5);
				zephir_read_property_cached(&_20$$5, this_ptr, _zephir_prop_1, 14, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&_21$$5);
				zephir_array_fetch(&_21$$5, &_20$$5, &i, PH_NOISY, "tensor/matrix.zep", 2986);
				tensor_less_equal_scalar(&_19$$5, &_21$$5, &valueB);
				zephir_array_append(&c, &_19$$5, PH_SEPARATE, "tensor/matrix.zep", 2986);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, multiplyScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3008);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_multiply_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3005);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_multiply_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3005);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, divideScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3027);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_divide_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3024);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_divide_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3024);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, addScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3046);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_add_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3043);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_add_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3043);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, subtractScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3065);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_subtract_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3062);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_subtract_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3062);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, powScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3084);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_pow_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3081);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_pow_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3081);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, modScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3103);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_mod_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3100);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_mod_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3100);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise equality comparison of this matrix and a scalar.
 *
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, equalScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3122);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_equal_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3119);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_equal_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3119);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise not equal comparison of this matrix and a scalar.
 *
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, notEqualScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3141);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_not_equal_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3138);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_not_equal_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3138);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise greater than comparison of this matrix and a scalar.
 *
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3160);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_greater_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3157);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_greater_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3157);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, greaterEqualScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3180);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_greater_equal_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3177);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_greater_equal_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3177);
		}
	}
	ZEPHIR_INIT_NVAR(&rowA);
	ZEPHIR_RETURN_CALL_SELF("quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise less than comparison of this matrix and a scalar.
 *
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3199);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_less_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3196);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_less_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3196);
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
 * @param float b
 * @return self
 */
PHP_METHOD(Tensor_Matrix, lessEqualScalar)
{
	zend_bool _7;
	zval c;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b_param = NULL, rowA, _0, *_1, _2, *_3, _6, _4$$3, _5$$3, _8$$4, _9$$4;
	double b;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&rowA);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&c);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(b_param)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b_param);
	b = zephir_get_doubleval(b_param);
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (Z_TYPE_P(&_0) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_2);
		zephir_string_to_char_array(&_2, &_0);
		_1 = &_2;
	} else {
		_1 = &_0;
	}
	zephir_is_iterable(_1, 0, "tensor/matrix.zep", 3219);
	if (Z_TYPE_P(_1) == IS_ARRAY) {
		ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_1), _3)
		{
			ZEPHIR_INIT_NVAR(&rowA);
			ZVAL_COPY(&rowA, _3);
			ZEPHIR_INIT_NVAR(&_4$$3);
			ZVAL_DOUBLE(&_5$$3, b);
			tensor_less_equal_scalar(&_4$$3, &rowA, &_5$$3);
			zephir_array_append(&c, &_4$$3, PH_SEPARATE, "tensor/matrix.zep", 3216);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _1, "rewind", NULL, 0);
		zephir_check_call_status();
		_7 = 1;
		while (1) {
			if (_7) {
				_7 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _1, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_6, _1, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_6)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&rowA, _1, "current", NULL, 0);
			zephir_check_call_status();
				ZEPHIR_INIT_NVAR(&_8$$4);
				ZVAL_DOUBLE(&_9$$4, b);
				tensor_less_equal_scalar(&_8$$4, &rowA, &_9$$4);
				zephir_array_append(&c, &_8$$4, PH_SEPARATE, "tensor/matrix.zep", 3216);
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
PHP_METHOD(Tensor_Matrix, count)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "size", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param mixed index
 * @param array values
 * @throws \Tensor\Exceptions\RuntimeException
 */
PHP_METHOD(Tensor_Matrix, offsetSet)
{
	zval *index, index_sub, *values, values_sub;

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&values_sub);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ZVAL(index)
		Z_PARAM_ZVAL(values)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(2, 0, &index, &values);
	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(tensor_exceptions_runtimeexception_ce, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3237);
	return;
}

/**
 * Does a given column exist in the matrix.
 *
 * @param mixed index
 * @return bool
 */
PHP_METHOD(Tensor_Matrix, offsetExists)
{
	zval *index, index_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &index);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	RETURN_BOOL(zephir_array_isset_value(&_0, index));
}

/**
 * @param mixed index
 * @throws \Tensor\Exceptions\RuntimeException
 */
PHP_METHOD(Tensor_Matrix, offsetUnset)
{
	zval *index, index_sub;

	ZVAL_UNDEF(&index_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(index)
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &index);
	ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(tensor_exceptions_runtimeexception_ce, "Matrix cannot be mutated directly.", "tensor/matrix.zep", 3257);
	return;
}

/**
 * Return a row from the matrix at the given index.
 *
 * @param mixed index
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @return \Tensor\Vector
 */
PHP_METHOD(Tensor_Matrix, offsetGet)
{
	zval _2, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *index, index_sub, row, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&index_sub);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_ZVAL(index)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &index);
	zephir_memory_observe(&row);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 14, PH_NOISY_CC | PH_READONLY);
	if (EXPECTED(zephir_array_isset_fetch(&row, &_0, index, 0))) {
		ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", NULL, 0, &row);
		zephir_check_call_status();
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(&_1);
	object_init_ex(&_1, tensor_exceptions_invalidargumentexception_ce);
	zephir_cast_to_string(&_2, index);
	ZEPHIR_INIT_VAR(&_3);
	ZEPHIR_CONCAT_SSVS(&_3, "Element not found at", " offset ", &_2, ".");
	ZEPHIR_CALL_METHOD(NULL, &_1, "__construct", NULL, 3, &_3);
	zephir_check_call_status();
	zephir_throw_exception_debug(&_1, "tensor/matrix.zep", 3276);
	ZEPHIR_MM_RESTORE();
	return;
}

/**
 * Get an iterator for the rows in the matrix.
 *
 * @return \ArrayIterator
 */
PHP_METHOD(Tensor_Matrix, getIterator)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	object_init_ex(return_value, spl_ce_ArrayIterator);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "asvectors", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 23, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

