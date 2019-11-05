
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"
#include "kernel/array.h"
#include "kernel/operators.h"
#include "kernel/object.h"


/**
 * RREF
 *
 * The reduced row echelon form (RREF) of a matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Decompositions_Rref) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Decompositions, Rref, tensor, decompositions_rref, tensor_decompositions_rref_method_entry, 0);

	/**
	 * The reduced matrix in reduced row echelon form.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_rref_ce, SL("a"), ZEND_ACC_PROTECTED);

	zend_class_implements(tensor_decompositions_rref_ce, 1, tensor_decompositions_decomposition_ce);
	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Rref, decompose) {

	zend_bool _1, _10$$3, _5$$5, _14$$8;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_22 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, row, col, _11$$3, _12$$3, _6$$5, _7$$5, _15$$8, _16$$8;
	zval *a = NULL, a_sub, t, scale, divisor, m, n, ref, b, swaps, _0, _2$$3, _3$$3, _8$$6, _9$$6, _13$$7, _17$$9, _18$$9, _19$$9, _20$$9, _21$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&divisor);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&swaps);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_8$$6);
	ZVAL_UNDEF(&_9$$6);
	ZVAL_UNDEF(&_13$$7);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&m, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&n, a, "n", NULL, 0);
	zephir_check_call_status();
	row = 0;
	col = 0;
	ZEPHIR_CALL_METHOD(&ref, a, "ref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_OBS_VAR(&b);
	zephir_array_fetch_long(&b, &ref, 0, PH_NOISY, "tensor/decompositions/rref.zep", 44);
	ZEPHIR_OBS_VAR(&swaps);
	zephir_array_fetch_long(&swaps, &ref, 1, PH_NOISY, "tensor/decompositions/rref.zep", 45);
	ZEPHIR_CALL_METHOD(&_0, &b, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&b, &_0);
	while (1) {
		_1 = ZEPHIR_GT_LONG(&m, row);
		if (_1) {
			_1 = ZEPHIR_GT_LONG(&n, col);
		}
		if (!(_1)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&t);
		zephir_array_fetch_long(&t, &b, row, PH_NOISY, "tensor/decompositions/rref.zep", 50);
		zephir_array_fetch_long(&_2$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 52);
		ZEPHIR_CALL_FUNCTION(&_3$$3, "abs", &_4, 10, &_2$$3);
		zephir_check_call_status();
		if (ZEPHIR_IS_LONG(&_3$$3, 0)) {
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&divisor);
		zephir_array_fetch_long(&divisor, &t, col, PH_NOISY, "tensor/decompositions/rref.zep", 58);
		if (!ZEPHIR_IS_LONG(&divisor, 1)) {
			_7$$5 = (zephir_get_numberval(&n) - 1);
			_6$$5 = 0;
			_5$$5 = 0;
			if (_6$$5 <= _7$$5) {
				while (1) {
					if (_5$$5) {
						_6$$5++;
						if (!(_6$$5 <= _7$$5)) {
							break;
						}
					} else {
						_5$$5 = 1;
					}
					i = _6$$5;
					zephir_array_fetch_long(&_8$$6, &t, i, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 62);
					ZEPHIR_INIT_NVAR(&_9$$6);
					div_function(&_9$$6, &_8$$6, &divisor);
					zephir_array_update_long(&t, i, &_9$$6, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_12$$3 = (row - 1);
		_11$$3 = _12$$3;
		_10$$3 = 0;
		if (_11$$3 >= 0) {
			while (1) {
				if (_10$$3) {
					_11$$3--;
					if (!(_11$$3 >= 0)) {
						break;
					}
				} else {
					_10$$3 = 1;
				}
				i = _11$$3;
				zephir_array_fetch_long(&_13$$7, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 67);
				ZEPHIR_OBS_NVAR(&scale);
				zephir_array_fetch_long(&scale, &_13$$7, col, PH_NOISY, "tensor/decompositions/rref.zep", 67);
				if (!ZEPHIR_IS_LONG(&scale, 0)) {
					_16$$8 = (zephir_get_numberval(&n) - 1);
					_15$$8 = 0;
					_14$$8 = 0;
					if (_15$$8 <= _16$$8) {
						while (1) {
							if (_14$$8) {
								_15$$8++;
								if (!(_15$$8 <= _16$$8)) {
									break;
								}
							} else {
								_14$$8 = 1;
							}
							j = _15$$8;
							zephir_array_fetch_long(&_17$$9, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 71);
							zephir_array_fetch_long(&_18$$9, &_17$$9, j, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 71);
							zephir_array_fetch_long(&_19$$9, &t, j, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 71);
							ZEPHIR_INIT_NVAR(&_20$$9);
							mul_function(&_20$$9, &scale, &_19$$9);
							ZEPHIR_INIT_NVAR(&_21$$9);
							zephir_sub_function(&_21$$9, &_18$$9, &_20$$9);
							zephir_array_update_multi(&b, &_21$$9, SL("ll"), 2, i, j);
						}
					}
				}
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	ZEPHIR_CALL_CE_STATIC(&_0, tensor_matrix_ce, "quick", &_22, 0, &b);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&b, &_0);
	object_init_ex(return_value, tensor_decompositions_rref_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 25, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix a
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Decompositions_Rref, __construct) {

	zval *a = NULL, a_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &a);



	zephir_update_property_zval(this_ptr, SL("a"), a);

}

/**
 * Return the reduced matrix in reduced row echelon form.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Rref, a) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

