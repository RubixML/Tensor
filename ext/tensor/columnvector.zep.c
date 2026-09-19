
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
#include "kernel/string.h"
#include "kernel/array.h"


/**
 * Column Vector
 *
 * A one dimensional (rank 1) tensor with integer and/or floating point elements.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_ColumnVector)
{
	ZEPHIR_REGISTER_CLASS_EX(Tensor, ColumnVector, tensor, columnvector, tensor_vector_ce, tensor_columnvector_method_entry, 0);

	return SUCCESS;
}

/**
 * Factory method to build a new vector from an array.
 *
 * @param (int|float)[] a
 * @return self
 */
PHP_METHOD(Tensor_ColumnVector, build)
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
	object_init_ex(return_value, tensor_columnvector_ce);
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
PHP_METHOD(Tensor_ColumnVector, quick)
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
	object_init_ex(return_value, tensor_columnvector_ce);
	ZVAL_BOOL(&_0, 0);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 1, &a, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the number of rows in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_ColumnVector, m)
{

	RETURN_MEMBER_TYPED(getThis(), "n", IS_LONG);
}

/**
 * Return the number of columns in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_ColumnVector, n)
{

	RETURN_LONG(1);
}

/**
 * Transpose the vector i.e. rotate it.
 *
 * @return mixed
 */
PHP_METHOD(Tensor_ColumnVector, transpose)
{
	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);
	static zend_string *_zephir_prop_0 = NULL;
	if (UNEXPECTED(!_zephir_prop_0)) {
		_zephir_prop_0 = zend_string_init("a", 1, 1);
	}
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);

	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 3, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", NULL, 0, &_0);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Compute the vector-matrix product of this vector and matrix a.
 *
 * @param \Tensor\Matrix b
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, matmul)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "asColumnMatrix", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "matmul", NULL, 0, b);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Multiply this column vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, multiplyMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 92);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 112);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 101);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 109);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					mul_function(&_18$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 106);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						mul_function(&_21$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 106);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 109);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 101);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 109);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						mul_function(&_28$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 106);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							mul_function(&_31$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 106);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 109);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Divide this column vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, divideMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 127);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 147);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 136);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 144);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					div_function(&_18$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 141);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						div_function(&_21$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 141);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 144);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 136);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 144);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						div_function(&_28$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 141);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							div_function(&_31$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 141);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 144);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Add this column vector to a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, addMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 162);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 182);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 171);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 179);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					zephir_add_function(&_18$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 176);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						zephir_add_function(&_21$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 176);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 179);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 171);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 179);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						zephir_add_function(&_28$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 176);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							zephir_add_function(&_31$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 176);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 179);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Subtract a matrix from this column vector.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, subtractMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 197);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 217);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 206);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 214);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					zephir_sub_function(&_18$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 211);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						zephir_sub_function(&_21$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 211);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 214);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 206);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 214);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						zephir_sub_function(&_28$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 211);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							zephir_sub_function(&_31$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 211);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 214);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Raise this column vector to the power of a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, powMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _24, _21$$4, _31$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_19 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _23, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _20$$4, _18$$5, _22$$6, _25$$7, *_26$$7, _27$$7, *_28$$7, _30$$7, _29$$8, _32$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_27$$7);
	ZVAL_UNDEF(&_30$$7);
	ZVAL_UNDEF(&_29$$8);
	ZVAL_UNDEF(&_32$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 232);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 252);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 241);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 249);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_CALL_FUNCTION(&_18$$5, "pow", &_19, 16, &valueA, &valueB);
					zephir_check_call_status();
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 246);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_21$$4 = 1;
				while (1) {
					if (_21$$4) {
						_21$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_20$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_20$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_CALL_FUNCTION(&_22$$6, "pow", &_19, 16, &valueA, &valueB);
						zephir_check_call_status();
						zephir_array_append(&rowC, &_22$$6, PH_SEPARATE, "tensor/columnvector.zep", 246);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 249);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_24 = 1;
		while (1) {
			if (_24) {
				_24 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_23, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_23)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_25$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_25$$7, &i, PH_NOISY, "tensor/columnvector.zep", 241);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_27$$7);
					zephir_string_to_char_array(&_27$$7, &rowB);
					_26$$7 = &_27$$7;
				} else {
					_26$$7 = &rowB;
				}
				zephir_is_iterable(_26$$7, 0, "tensor/columnvector.zep", 249);
				if (Z_TYPE_P(_26$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_26$$7), _28$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _28$$7);
						ZEPHIR_CALL_FUNCTION(&_29$$8, "pow", &_19, 16, &valueA, &valueB);
						zephir_check_call_status();
						zephir_array_append(&rowC, &_29$$8, PH_SEPARATE, "tensor/columnvector.zep", 246);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _26$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_31$$7 = 1;
					while (1) {
						if (_31$$7) {
							_31$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _26$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_30$$7, _26$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_30$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _26$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_CALL_FUNCTION(&_32$$9, "pow", &_19, 16, &valueA, &valueB);
							zephir_check_call_status();
							zephir_array_append(&rowC, &_32$$9, PH_SEPARATE, "tensor/columnvector.zep", 246);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 249);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Mod this column vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, modMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 267);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 287);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 276);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 284);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					mod_function(&_18$$5, &valueA, &valueB);
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 281);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						mod_function(&_21$$6, &valueA, &valueB);
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 281);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 284);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 276);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 284);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						mod_function(&_28$$8, &valueA, &valueB);
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 281);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							mod_function(&_31$$9, &valueA, &valueB);
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 281);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 284);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise equality comparison of this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, equalMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 302);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 322);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 311);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 319);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 0);
					}
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 316);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 0);
						}
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 316);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 319);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 311);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 319);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 0);
						}
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 316);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 0);
							}
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 316);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 319);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise not equal comparison of this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, notEqualMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 337);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 357);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 346);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 354);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 0);
					}
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 351);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 0);
						}
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 351);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 354);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 346);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 354);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 0);
						}
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 351);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 0);
							}
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 351);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 354);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise greater than comparison of this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, greaterMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 372);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 392);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 381);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 389);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					if (ZEPHIR_GT(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 0);
					}
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 386);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						if (ZEPHIR_GT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 0);
						}
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 386);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 389);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 381);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 389);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						if (ZEPHIR_GT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 0);
						}
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 386);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							if (ZEPHIR_GT(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 0);
							}
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 386);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 389);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise greater than or equal to comparison of this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, greaterEqualMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 407);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 427);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 416);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 424);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					if (ZEPHIR_GE(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 0);
					}
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 421);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						if (ZEPHIR_GE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 0);
						}
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 421);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 424);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 416);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 424);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						if (ZEPHIR_GE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 0);
						}
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 421);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							if (ZEPHIR_GE(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 0);
							}
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 421);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 424);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise less than comparison of this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, lessMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 442);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 462);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 451);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 459);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					if (ZEPHIR_LT(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 0);
					}
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 456);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						if (ZEPHIR_LT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 0);
						}
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 456);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 459);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 451);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 459);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						if (ZEPHIR_LT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 0);
						}
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 456);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							if (ZEPHIR_LT(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 0);
							}
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 456);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 459);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * Return the element-wise less than or equal to comparison of this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \Tensor\Exceptions\DimensionalityMismatch
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, lessEqualMatrix)
{
	zval _4$$3, _6$$3, _7$$3;
	zend_bool _23, _20$$4, _30$$7;
	zend_string *_13;
	zend_ulong _12;
	zval c, rowC;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, *_11, _22, _2$$3, _3$$3, _5$$3, _14$$4, *_15$$4, _16$$4, *_17$$4, _19$$4, _18$$5, _21$$6, _24$$7, *_25$$7, _26$$7, *_27$$7, _29$$7, _28$$8, _31$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_22);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_16$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_18$$5);
	ZVAL_UNDEF(&_21$$6);
	ZVAL_UNDEF(&_24$$7);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_29$$7);
	ZVAL_UNDEF(&_28$$8);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&rowC);
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
		Z_PARAM_OBJECT_OF_CLASS(b, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &b);
	zephir_read_property_cached(&_0, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC | PH_READONLY);
	ZEPHIR_CALL_METHOD(&_1, b, "m", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!ZEPHIR_IS_IDENTICAL(&_0, &_1))) {
		ZEPHIR_INIT_VAR(&_2$$3);
		object_init_ex(&_2$$3, tensor_exceptions_dimensionalitymismatch_ce);
		zephir_memory_observe(&_3$$3);
		zephir_read_property_cached(&_3$$3, this_ptr, _zephir_prop_0, 4, PH_NOISY_CC);
		zephir_cast_to_string(&_4$$3, &_3$$3);
		ZEPHIR_CALL_METHOD(&_5$$3, b, "m", NULL, 0);
		zephir_check_call_status();
		zephir_cast_to_string(&_6$$3, &_5$$3);
		ZEPHIR_INIT_VAR(&_7$$3);
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A expects ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 477);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_INIT_VAR(&rowC);
	array_init(&rowC);
	ZEPHIR_CALL_METHOD(&_8, b, "asArray", NULL, 0);
	zephir_check_call_status();
	if (Z_TYPE_P(&_8) == IS_STRING) {
		ZEPHIR_INIT_VAR(&_10);
		zephir_string_to_char_array(&_10, &_8);
		_9 = &_10;
	} else {
		_9 = &_8;
	}
	zephir_is_iterable(_9, 0, "tensor/columnvector.zep", 497);
	if (Z_TYPE_P(_9) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(_9), _12, _13, _11)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_13 != NULL) { 
				ZVAL_STR_COPY(&i, _13);
			} else {
				ZVAL_LONG(&i, _12);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _11);
			zephir_read_property_cached(&_14$$4, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_14$$4, &i, PH_NOISY, "tensor/columnvector.zep", 486);
			ZEPHIR_INIT_NVAR(&rowC);
			array_init(&rowC);
			if (Z_TYPE_P(&rowB) == IS_STRING) {
				ZEPHIR_INIT_NVAR(&_16$$4);
				zephir_string_to_char_array(&_16$$4, &rowB);
				_15$$4 = &_16$$4;
			} else {
				_15$$4 = &rowB;
			}
			zephir_is_iterable(_15$$4, 0, "tensor/columnvector.zep", 494);
			if (Z_TYPE_P(_15$$4) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_15$$4), _17$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _17$$4);
					ZEPHIR_INIT_NVAR(&_18$$5);
					if (ZEPHIR_LE(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_18$$5);
						ZVAL_LONG(&_18$$5, 0);
					}
					zephir_array_append(&rowC, &_18$$5, PH_SEPARATE, "tensor/columnvector.zep", 491);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, _15$$4, "rewind", NULL, 0);
				zephir_check_call_status();
				_20$$4 = 1;
				while (1) {
					if (_20$$4) {
						_20$$4 = 0;
					} else {
						ZEPHIR_CALL_METHOD(NULL, _15$$4, "next", NULL, 0);
						zephir_check_call_status();
					}
					ZEPHIR_CALL_METHOD(&_19$$4, _15$$4, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_19$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, _15$$4, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_21$$6);
						if (ZEPHIR_LE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$6);
							ZVAL_LONG(&_21$$6, 0);
						}
						zephir_array_append(&rowC, &_21$$6, PH_SEPARATE, "tensor/columnvector.zep", 491);
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 494);
		} ZEND_HASH_FOREACH_END();
	} else {
		ZEPHIR_CALL_METHOD(NULL, _9, "rewind", NULL, 0);
		zephir_check_call_status();
		_23 = 1;
		while (1) {
			if (_23) {
				_23 = 0;
			} else {
				ZEPHIR_CALL_METHOD(NULL, _9, "next", NULL, 0);
				zephir_check_call_status();
			}
			ZEPHIR_CALL_METHOD(&_22, _9, "valid", NULL, 0);
			zephir_check_call_status();
			if (!zend_is_true(&_22)) {
				break;
			}
			ZEPHIR_CALL_METHOD(&i, _9, "key", NULL, 0);
			zephir_check_call_status();
			ZEPHIR_CALL_METHOD(&rowB, _9, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property_cached(&_24$$7, this_ptr, _zephir_prop_1, 3, PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_24$$7, &i, PH_NOISY, "tensor/columnvector.zep", 486);
				ZEPHIR_INIT_NVAR(&rowC);
				array_init(&rowC);
				if (Z_TYPE_P(&rowB) == IS_STRING) {
					ZEPHIR_INIT_NVAR(&_26$$7);
					zephir_string_to_char_array(&_26$$7, &rowB);
					_25$$7 = &_26$$7;
				} else {
					_25$$7 = &rowB;
				}
				zephir_is_iterable(_25$$7, 0, "tensor/columnvector.zep", 494);
				if (Z_TYPE_P(_25$$7) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(_25$$7), _27$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _27$$7);
						ZEPHIR_INIT_NVAR(&_28$$8);
						if (ZEPHIR_LE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_28$$8);
							ZVAL_LONG(&_28$$8, 0);
						}
						zephir_array_append(&rowC, &_28$$8, PH_SEPARATE, "tensor/columnvector.zep", 491);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, _25$$7, "rewind", NULL, 0);
					zephir_check_call_status();
					_30$$7 = 1;
					while (1) {
						if (_30$$7) {
							_30$$7 = 0;
						} else {
							ZEPHIR_CALL_METHOD(NULL, _25$$7, "next", NULL, 0);
							zephir_check_call_status();
						}
						ZEPHIR_CALL_METHOD(&_29$$7, _25$$7, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_29$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, _25$$7, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_31$$9);
							if (ZEPHIR_LE(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_31$$9);
								ZVAL_LONG(&_31$$9, 0);
							}
							zephir_array_append(&rowC, &_31$$9, PH_SEPARATE, "tensor/columnvector.zep", 491);
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC, PH_SEPARATE, "tensor/columnvector.zep", 494);
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", NULL, 0, &c);
	zephir_check_call_status();
	RETURN_MM();
}

