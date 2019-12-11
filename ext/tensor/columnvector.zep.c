
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


/**
 * Column Vector
 *
 * A one dimensional (rank 1) tensor with integer and/or floating point elements.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_ColumnVector) {

	ZEPHIR_REGISTER_CLASS_EX(Tensor, ColumnVector, tensor, columnvector, tensor_vector_ce, tensor_columnvector_method_entry, 0);

	return SUCCESS;

}

/**
 * Factory method to build a new vector from an array.
 *
 * @param array a
 * @return self
 */
PHP_METHOD(Tensor_ColumnVector, build) {

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


	object_init_ex(return_value, tensor_columnvector_ce);
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
PHP_METHOD(Tensor_ColumnVector, quick) {

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
PHP_METHOD(Tensor_ColumnVector, m) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "n");

}

/**
 * Return the number of columns in the vector.
 *
 * @return int
 */
PHP_METHOD(Tensor_ColumnVector, n) {

	zval *this_ptr = getThis();


	RETURN_LONG(1);

}

/**
 * Transpose the vector i.e. rotate it.
 *
 * @return mixed
 */
PHP_METHOD(Tensor_ColumnVector, transpose) {

	zval _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_vector_ce, "quick", &_0, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Compute the vector-matrix product of this vector and matrix a.
 *
 * @param \Tensor\Matrix b
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, matmul) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &b);



	ZEPHIR_CALL_METHOD(&_0, this_ptr, "ascolumnmatrix", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_RETURN_CALL_METHOD(&_0, "matmul", NULL, 0, b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Multiply this column vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, multiplyMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 91);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 110);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 99);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 107);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mul_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 104);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						mul_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 104);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 107);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 99);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 107);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						mul_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 104);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							mul_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 104);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 107);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Divide this column vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, divideMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 125);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 144);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 133);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 141);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					div_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 138);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						div_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 138);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 141);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 133);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 141);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						div_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 138);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							div_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 138);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 141);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Add this column vector to a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, addMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 159);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 178);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 167);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 175);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_add_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 172);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_add_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 172);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 175);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 167);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 175);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_add_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 172);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							zephir_add_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 172);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 175);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Subtract a matrix from this column vector.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, subtractMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 193);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 212);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 201);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 209);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_sub_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 206);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_sub_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 206);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 209);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 201);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 209);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_sub_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 206);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							zephir_sub_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 206);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 209);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Raise this column vector to the power of a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, powMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 227);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 246);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 235);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 243);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					zephir_pow_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 240);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						zephir_pow_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 240);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 243);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 235);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 243);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						zephir_pow_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 240);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							zephir_pow_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 240);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 243);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Mod this column vector with a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, modMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 261);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 280);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 269);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 277);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					mod_function(&_16$$5, &valueA, &valueB);
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 274);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						mod_function(&_17$$6, &valueA, &valueB);
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 274);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 277);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 269);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 277);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						mod_function(&_21$$8, &valueA, &valueB);
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 274);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							mod_function(&_22$$9, &valueA, &valueB);
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 274);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 277);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise equality comparison of this column vector
 * and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, equalMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 296);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 315);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 304);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 312);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 309);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 309);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 312);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 304);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 312);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 309);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 309);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 312);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise not equal comparison of this column vector
 * and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, notEqualMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 331);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 350);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 339);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 347);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 344);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 344);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 347);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 339);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 347);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 344);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (!ZEPHIR_IS_EQUAL(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 344);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 347);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than comparison of this column
 * vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, greaterMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 366);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 385);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 374);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 382);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_GT(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 379);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_GT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 379);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 382);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 374);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 382);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_GT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 379);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_GT(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 379);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 382);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise greater than or equal to comparison of
 * this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, greaterEqualMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 401);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 420);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 409);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 417);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_GE(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 414);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_GE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 414);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 417);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 409);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 417);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_GE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 414);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_GE(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 414);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 417);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than comparison of this column
 * vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, lessMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 436);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 455);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 444);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 452);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_LT(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 449);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_LT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 449);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 452);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 444);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 452);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_LT(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 449);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_LT(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 449);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 452);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the element-wise less than or equal to comparison of
 * this column vector and a matrix.
 *
 * @param \Tensor\Matrix b
 * @throws \InvalidArgumentException
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_ColumnVector, lessEqualMatrix) {

	zval _4$$3, _6$$3, _7$$3;
	zend_string *_12;
	zend_ulong _11;
	zval c, rowC$$4, rowC$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_23 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, rowB, valueB, valueA, _8, *_9, _10, _2$$3, _3$$3, _5$$3, _13$$4, *_14$$4, _15$$4, _16$$5, _17$$6, _18$$7, *_19$$7, _20$$7, _21$$8, _22$$9;
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
		ZEPHIR_CONCAT_SVSVS(&_7$$3, "Vector A requires ", &_4$$3, " rows but Matrix B has ", &_6$$3, ".");
		ZEPHIR_CALL_METHOD(NULL, &_2$$3, "__construct", NULL, 3, &_7$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 471);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	ZEPHIR_CALL_METHOD(&_8, b, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_is_iterable(&_8, 0, "tensor/columnvector.zep", 490);
	if (Z_TYPE_P(&_8) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(&_8), _11, _12, _9)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_12 != NULL) { 
				ZVAL_STR_COPY(&i, _12);
			} else {
				ZVAL_LONG(&i, _11);
			}
			ZEPHIR_INIT_NVAR(&rowB);
			ZVAL_COPY(&rowB, _9);
			zephir_read_property(&_13$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA);
			zephir_array_fetch(&valueA, &_13$$4, &i, PH_NOISY, "tensor/columnvector.zep", 479);
			ZEPHIR_INIT_NVAR(&rowC$$4);
			array_init(&rowC$$4);
			zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 487);
			if (Z_TYPE_P(&rowB) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _14$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _14$$4);
					ZEPHIR_INIT_NVAR(&_16$$5);
					if (ZEPHIR_LE(&valueA, &valueB)) {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_16$$5);
						ZVAL_LONG(&_16$$5, 0);
					}
					zephir_array_append(&rowC$$4, &_16$$5, PH_SEPARATE, "tensor/columnvector.zep", 484);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_15$$4, &rowB, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_15$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_17$$6);
						if (ZEPHIR_LE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_17$$6);
							ZVAL_LONG(&_17$$6, 0);
						}
						zephir_array_append(&rowC$$4, &_17$$6, PH_SEPARATE, "tensor/columnvector.zep", 484);
					ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &rowC$$4, PH_SEPARATE, "tensor/columnvector.zep", 487);
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
			ZEPHIR_CALL_METHOD(&rowB, &_8, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_18$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA);
				zephir_array_fetch(&valueA, &_18$$7, &i, PH_NOISY, "tensor/columnvector.zep", 479);
				ZEPHIR_INIT_NVAR(&rowC$$7);
				array_init(&rowC$$7);
				zephir_is_iterable(&rowB, 0, "tensor/columnvector.zep", 487);
				if (Z_TYPE_P(&rowB) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&rowB), _19$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _19$$7);
						ZEPHIR_INIT_NVAR(&_21$$8);
						if (ZEPHIR_LE(&valueA, &valueB)) {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_21$$8);
							ZVAL_LONG(&_21$$8, 0);
						}
						zephir_array_append(&rowC$$7, &_21$$8, PH_SEPARATE, "tensor/columnvector.zep", 484);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &rowB, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_20$$7, &rowB, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_20$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &rowB, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_22$$9);
							if (ZEPHIR_LE(&valueA, &valueB)) {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_22$$9);
								ZVAL_LONG(&_22$$9, 0);
							}
							zephir_array_append(&rowC$$7, &_22$$9, PH_SEPARATE, "tensor/columnvector.zep", 484);
						ZEPHIR_CALL_METHOD(NULL, &rowB, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &rowC$$7, PH_SEPARATE, "tensor/columnvector.zep", 487);
			ZEPHIR_CALL_METHOD(NULL, &_8, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&rowB);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_23, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

