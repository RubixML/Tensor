
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
#include "kernel/object.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "kernel/array.h"


ZEPHIR_INIT_CLASS(Tensor_ColumnVector) {

	ZEPHIR_REGISTER_CLASS_EX(Tensor, ColumnVector, tensor, columnvector, tensor_vector_ce, tensor_columnvector_method_entry, 0);

	return SUCCESS;

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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 60 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 78);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 67 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 75);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					mul_function(&_15$$5, &valueA$$4, &valueB TSRMLS_CC);
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 72);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						mul_function(&_16$$6, &valueA$$4, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 72);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 75);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 67 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 75);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						mul_function(&_20$$8, &valueA$$7, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 72);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							mul_function(&_21$$9, &valueA$$7, &valueB TSRMLS_CC);
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 72);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 75);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 93 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 111);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 100 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 108);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					div_function(&_15$$5, &valueA$$4, &valueB TSRMLS_CC);
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 105);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						div_function(&_16$$6, &valueA$$4, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 105);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 108);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 100 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 108);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						div_function(&_20$$8, &valueA$$7, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 105);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							div_function(&_21$$9, &valueA$$7, &valueB TSRMLS_CC);
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 105);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 108);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 126 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 144);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 133 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 141);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					zephir_add_function(&_15$$5, &valueA$$4, &valueB);
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 138);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						zephir_add_function(&_16$$6, &valueA$$4, &valueB);
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 138);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 141);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 133 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 141);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						zephir_add_function(&_20$$8, &valueA$$7, &valueB);
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 138);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							zephir_add_function(&_21$$9, &valueA$$7, &valueB);
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 138);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 141);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 159 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 177);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 166 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 174);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					zephir_sub_function(&_15$$5, &valueA$$4, &valueB);
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 171);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						zephir_sub_function(&_16$$6, &valueA$$4, &valueB);
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 171);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 174);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 166 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 174);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						zephir_sub_function(&_20$$8, &valueA$$7, &valueB);
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 171);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							zephir_sub_function(&_21$$9, &valueA$$7, &valueB);
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 171);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 174);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 192 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 210);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 199 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 207);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_NVAR(&_15$$5);
					zephir_pow_function(&_15$$5, &valueA$$4, &valueB);
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 204);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_NVAR(&_16$$6);
						zephir_pow_function(&_16$$6, &valueA$$4, &valueB);
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 204);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 207);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 199 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 207);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_NVAR(&_20$$8);
						zephir_pow_function(&_20$$8, &valueA$$7, &valueB);
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 204);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_NVAR(&_21$$9);
							zephir_pow_function(&_21$$9, &valueA$$7, &valueB);
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 204);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 207);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 225 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 243);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 232 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 240);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					mod_function(&_15$$5, &valueA$$4, &valueB TSRMLS_CC);
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 237);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						mod_function(&_16$$6, &valueA$$4, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 237);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 240);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 232 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 240);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						mod_function(&_20$$8, &valueA$$7, &valueB TSRMLS_CC);
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 237);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							mod_function(&_21$$9, &valueA$$7, &valueB TSRMLS_CC);
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 237);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 240);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 259 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 277);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 266 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 274);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					if (ZEPHIR_IS_EQUAL(&valueA$$4, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 271);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						if (ZEPHIR_IS_EQUAL(&valueA$$4, &valueB)) {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 0);
						}
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 271);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 274);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 266 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 274);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						if (ZEPHIR_IS_EQUAL(&valueA$$7, &valueB)) {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 0);
						}
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 271);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							if (ZEPHIR_IS_EQUAL(&valueA$$7, &valueB)) {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 0);
							}
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 271);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 274);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 293 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 311);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 300 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 308);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					if (!ZEPHIR_IS_EQUAL(&valueA$$4, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 305);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						if (!ZEPHIR_IS_EQUAL(&valueA$$4, &valueB)) {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 0);
						}
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 305);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 308);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 300 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 308);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						if (!ZEPHIR_IS_EQUAL(&valueA$$7, &valueB)) {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 0);
						}
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 305);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							if (!ZEPHIR_IS_EQUAL(&valueA$$7, &valueB)) {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 0);
							}
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 305);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 308);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 327 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 345);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 334 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 342);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					if (ZEPHIR_GT(&valueA$$4, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 339);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						if (ZEPHIR_GT(&valueA$$4, &valueB)) {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 0);
						}
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 339);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 342);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 334 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 342);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						if (ZEPHIR_GT(&valueA$$7, &valueB)) {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 0);
						}
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 339);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							if (ZEPHIR_GT(&valueA$$7, &valueB)) {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 0);
							}
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 339);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 342);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 361 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 379);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 368 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 376);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					if (ZEPHIR_GE(&valueA$$4, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 373);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						if (ZEPHIR_GE(&valueA$$4, &valueB)) {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 0);
						}
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 373);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 376);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 368 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 376);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						if (ZEPHIR_GE(&valueA$$7, &valueB)) {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 0);
						}
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 373);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							if (ZEPHIR_GE(&valueA$$7, &valueB)) {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 0);
							}
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 373);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 376);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 395 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 413);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 402 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 410);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					if (ZEPHIR_LT(&valueA$$4, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 407);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						if (ZEPHIR_LT(&valueA$$4, &valueB)) {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 0);
						}
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 407);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 410);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 402 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 410);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						if (ZEPHIR_LT(&valueA$$7, &valueB)) {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 0);
						}
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 407);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							if (ZEPHIR_LT(&valueA$$7, &valueB)) {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 0);
							}
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 407);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 410);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
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
	zend_string *_11;
	zend_ulong _10;
	zval c, temp$$4, temp$$7;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *b, b_sub, _0, _1, i, row, valueB, *_8, _9, _2$$3, _3$$3, _5$$3, valueA$$4, _12$$4, *_13$$4, _14$$4, _15$$5, _16$$6, valueA$$7, _17$$7, *_18$$7, _19$$7, _20$$8, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&b_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&i);
	ZVAL_UNDEF(&row);
	ZVAL_UNDEF(&valueB);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&valueA$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&valueA$$7);
	ZVAL_UNDEF(&_17$$7);
	ZVAL_UNDEF(&_19$$7);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&c);
	ZVAL_UNDEF(&temp$$4);
	ZVAL_UNDEF(&temp$$7);
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
		zephir_throw_exception_debug(&_2$$3, "tensor/columnvector.zep", 429 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&c);
	array_init(&c);
	zephir_is_iterable(b, 0, "tensor/columnvector.zep", 447);
	if (Z_TYPE_P(b) == IS_ARRAY) {
		ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(b), _10, _11, _8)
		{
			ZEPHIR_INIT_NVAR(&i);
			if (_11 != NULL) { 
				ZVAL_STR_COPY(&i, _11);
			} else {
				ZVAL_LONG(&i, _10);
			}
			ZEPHIR_INIT_NVAR(&row);
			ZVAL_COPY(&row, _8);
			zephir_read_property(&_12$$4, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
			ZEPHIR_OBS_NVAR(&valueA$$4);
			zephir_array_fetch(&valueA$$4, &_12$$4, &i, PH_NOISY, "tensor/columnvector.zep", 436 TSRMLS_CC);
			ZEPHIR_INIT_NVAR(&temp$$4);
			array_init(&temp$$4);
			zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 444);
			if (Z_TYPE_P(&row) == IS_ARRAY) {
				ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _13$$4)
				{
					ZEPHIR_INIT_NVAR(&valueB);
					ZVAL_COPY(&valueB, _13$$4);
					ZEPHIR_INIT_LNVAR(_15$$5);
					if (ZEPHIR_LE(&valueA$$4, &valueB)) {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 1);
					} else {
						ZEPHIR_INIT_NVAR(&_15$$5);
						ZVAL_LONG(&_15$$5, 0);
					}
					zephir_array_append(&temp$$4, &_15$$5, PH_SEPARATE, "tensor/columnvector.zep", 441);
				} ZEND_HASH_FOREACH_END();
			} else {
				ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
				zephir_check_call_status();
				while (1) {
					ZEPHIR_CALL_METHOD(&_14$$4, &row, "valid", NULL, 0);
					zephir_check_call_status();
					if (!zend_is_true(&_14$$4)) {
						break;
					}
					ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
					zephir_check_call_status();
						ZEPHIR_INIT_LNVAR(_16$$6);
						if (ZEPHIR_LE(&valueA$$4, &valueB)) {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_16$$6);
							ZVAL_LONG(&_16$$6, 0);
						}
						zephir_array_append(&temp$$4, &_16$$6, PH_SEPARATE, "tensor/columnvector.zep", 441);
					ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
					zephir_check_call_status();
				}
			}
			ZEPHIR_INIT_NVAR(&valueB);
			zephir_array_append(&c, &temp$$4, PH_SEPARATE, "tensor/columnvector.zep", 444);
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
			ZEPHIR_CALL_METHOD(&row, b, "current", NULL, 0);
			zephir_check_call_status();
				zephir_read_property(&_17$$7, this_ptr, SL("a"), PH_NOISY_CC | PH_READONLY);
				ZEPHIR_OBS_NVAR(&valueA$$7);
				zephir_array_fetch(&valueA$$7, &_17$$7, &i, PH_NOISY, "tensor/columnvector.zep", 436 TSRMLS_CC);
				ZEPHIR_INIT_NVAR(&temp$$7);
				array_init(&temp$$7);
				zephir_is_iterable(&row, 0, "tensor/columnvector.zep", 444);
				if (Z_TYPE_P(&row) == IS_ARRAY) {
					ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(&row), _18$$7)
					{
						ZEPHIR_INIT_NVAR(&valueB);
						ZVAL_COPY(&valueB, _18$$7);
						ZEPHIR_INIT_LNVAR(_20$$8);
						if (ZEPHIR_LE(&valueA$$7, &valueB)) {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 1);
						} else {
							ZEPHIR_INIT_NVAR(&_20$$8);
							ZVAL_LONG(&_20$$8, 0);
						}
						zephir_array_append(&temp$$7, &_20$$8, PH_SEPARATE, "tensor/columnvector.zep", 441);
					} ZEND_HASH_FOREACH_END();
				} else {
					ZEPHIR_CALL_METHOD(NULL, &row, "rewind", NULL, 0);
					zephir_check_call_status();
					while (1) {
						ZEPHIR_CALL_METHOD(&_19$$7, &row, "valid", NULL, 0);
						zephir_check_call_status();
						if (!zend_is_true(&_19$$7)) {
							break;
						}
						ZEPHIR_CALL_METHOD(&valueB, &row, "current", NULL, 0);
						zephir_check_call_status();
							ZEPHIR_INIT_LNVAR(_21$$9);
							if (ZEPHIR_LE(&valueA$$7, &valueB)) {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 1);
							} else {
								ZEPHIR_INIT_NVAR(&_21$$9);
								ZVAL_LONG(&_21$$9, 0);
							}
							zephir_array_append(&temp$$7, &_21$$9, PH_SEPARATE, "tensor/columnvector.zep", 441);
						ZEPHIR_CALL_METHOD(NULL, &row, "next", NULL, 0);
						zephir_check_call_status();
					}
				}
				ZEPHIR_INIT_NVAR(&valueB);
				zephir_array_append(&c, &temp$$7, PH_SEPARATE, "tensor/columnvector.zep", 444);
			ZEPHIR_CALL_METHOD(NULL, b, "next", NULL, 0);
			zephir_check_call_status();
		}
	}
	ZEPHIR_INIT_NVAR(&row);
	ZEPHIR_INIT_NVAR(&i);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "quick", &_22, 0, &c);
	zephir_check_call_status();
	RETURN_MM();

}

