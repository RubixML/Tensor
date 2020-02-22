
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
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/array.h"
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
ZEPHIR_INIT_CLASS(Tensor_Reductions_Rref) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Reductions, Rref, tensor, reductions_rref, tensor_reductions_rref_method_entry, 0);

	/**
	 * The reduced matrix in reduced row echelon form.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_reductions_rref_ce, SL("a"), ZEND_ACC_PROTECTED);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Reductions_Rref, reduce) {

	zend_bool _6, _17$$3, _12$$5, _21$$8;
	zval b, t, _5, _8$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL, *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, m, n, row, col, _18$$3, _19$$3, _13$$5, _14$$5, _22$$8, _23$$8;
	zval *a, a_sub, scale, divisor, _0, _1, _2, _3, _4, _29, _7$$3, _9$$3, _10$$3, _15$$6, _16$$6, _20$$7, _24$$9, _25$$9, _26$$9, _27$$9, _28$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&divisor);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_20$$7);
	ZVAL_UNDEF(&_24$$9);
	ZVAL_UNDEF(&_25$$9);
	ZVAL_UNDEF(&_26$$9);
	ZVAL_UNDEF(&_27$$9);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_8$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&t);
	array_init(&t);
	ZEPHIR_CALL_METHOD(&_0, a, "m", NULL, 0);
	zephir_check_call_status();
	m = zephir_get_intval(&_0);
	ZEPHIR_CALL_METHOD(&_1, a, "n", NULL, 0);
	zephir_check_call_status();
	n = zephir_get_intval(&_1);
	row = 0;
	col = 0;
	ZEPHIR_CALL_METHOD(&_2, a, "ref", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_3, &_2, "a", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_4, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_5, &_4);
	ZEPHIR_CPY_WRT(&b, &_5);
	while (1) {
		_6 = row < m;
		if (_6) {
			_6 = col < n;
		}
		if (!(EXPECTED(_6))) {
			break;
		}
		ZEPHIR_OBS_NVAR(&_7$$3);
		zephir_array_fetch_long(&_7$$3, &b, row, PH_NOISY, "tensor/reductions/rref.zep", 47);
		zephir_get_arrval(&_8$$3, &_7$$3);
		ZEPHIR_CPY_WRT(&t, &_8$$3);
		zephir_array_fetch_long(&_9$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 49);
		ZEPHIR_CALL_FUNCTION(&_10$$3, "abs", &_11, 12, &_9$$3);
		zephir_check_call_status();
		if (ZEPHIR_IS_LONG(&_10$$3, 0)) {
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&divisor);
		zephir_array_fetch_long(&divisor, &t, col, PH_NOISY, "tensor/reductions/rref.zep", 55);
		if (!ZEPHIR_IS_LONG(&divisor, 1)) {
			_14$$5 = (n - 1);
			_13$$5 = 0;
			_12$$5 = 0;
			if (_13$$5 <= _14$$5) {
				while (1) {
					if (_12$$5) {
						_13$$5++;
						if (!(_13$$5 <= _14$$5)) {
							break;
						}
					} else {
						_12$$5 = 1;
					}
					i = _13$$5;
					zephir_array_fetch_long(&_15$$6, &t, i, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 59);
					ZEPHIR_INIT_NVAR(&_16$$6);
					div_function(&_16$$6, &_15$$6, &divisor);
					zephir_array_update_long(&t, i, &_16$$6, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_19$$3 = (row - 1);
		_18$$3 = _19$$3;
		_17$$3 = 0;
		if (_18$$3 >= 0) {
			while (1) {
				if (_17$$3) {
					_18$$3--;
					if (!(_18$$3 >= 0)) {
						break;
					}
				} else {
					_17$$3 = 1;
				}
				i = _18$$3;
				zephir_array_fetch_long(&_20$$7, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 64);
				ZEPHIR_OBS_NVAR(&scale);
				zephir_array_fetch_long(&scale, &_20$$7, col, PH_NOISY, "tensor/reductions/rref.zep", 64);
				if (!ZEPHIR_IS_LONG(&scale, 0)) {
					_23$$8 = (n - 1);
					_22$$8 = 0;
					_21$$8 = 0;
					if (_22$$8 <= _23$$8) {
						while (1) {
							if (_21$$8) {
								_22$$8++;
								if (!(_22$$8 <= _23$$8)) {
									break;
								}
							} else {
								_21$$8 = 1;
							}
							j = _22$$8;
							zephir_array_fetch_long(&_24$$9, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 68);
							zephir_array_fetch_long(&_25$$9, &_24$$9, j, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 68);
							zephir_array_fetch_long(&_26$$9, &t, j, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 68);
							ZEPHIR_INIT_NVAR(&_27$$9);
							mul_function(&_27$$9, &scale, &_26$$9);
							ZEPHIR_INIT_NVAR(&_28$$9);
							zephir_sub_function(&_28$$9, &_25$$9, &_27$$9);
							zephir_array_update_multi(&b, &_28$$9, SL("ll"), 2, i, j);
						}
					}
				}
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	object_init_ex(return_value, tensor_reductions_rref_ce);
	ZEPHIR_CALL_CE_STATIC(&_29, tensor_matrix_ce, "quick", &_30, 0, &b);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 33, &_29);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix a
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Reductions_Rref, __construct) {

	zval *a, a_sub;
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
PHP_METHOD(Tensor_Reductions_Rref, a) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

