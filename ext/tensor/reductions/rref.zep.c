
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
ZEPHIR_INIT_CLASS(Tensor_Reductions_Rref)
{
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
PHP_METHOD(Tensor_Reductions_Rref, reduce)
{
	zval b, rowB, t, _5, _8$$3, _31$$11;
	zend_bool hasPivot = 0, _6, _27$$3, _12$$4, _17$$7, _22$$9, _35$$12;
	double scale = 0, divisor = 0, epsilon;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_11 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, m, n, row, col, _28$$3, _29$$3, _13$$4, _14$$4, _18$$7, _19$$7, _23$$9, _24$$9, _36$$12, _37$$12;
	zval *a, a_sub, _0, _1, _2, _3, _4, _41, _7$$3, _9$$3, _10$$3, _21$$3, _15$$5, _16$$5, _20$$8, _25$$10, _26$$10, _30$$11, _32$$11, _33$$11, _34$$11, _38$$13, _39$$13, _40$$13;

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_41);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_9$$3);
	ZVAL_UNDEF(&_10$$3);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_15$$5);
	ZVAL_UNDEF(&_16$$5);
	ZVAL_UNDEF(&_20$$8);
	ZVAL_UNDEF(&_25$$10);
	ZVAL_UNDEF(&_26$$10);
	ZVAL_UNDEF(&_30$$11);
	ZVAL_UNDEF(&_32$$11);
	ZVAL_UNDEF(&_33$$11);
	ZVAL_UNDEF(&_34$$11);
	ZVAL_UNDEF(&_38$$13);
	ZVAL_UNDEF(&_39$$13);
	ZVAL_UNDEF(&_40$$13);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&rowB);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_8$$3);
	ZVAL_UNDEF(&_31$$11);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(a, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &a);
	epsilon =  (0.00000001);
	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_INIT_VAR(&rowB);
	array_init(&rowB);
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
		if (!(_6)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&_7$$3);
		zephir_array_fetch_long(&_7$$3, &b, row, PH_NOISY, "tensor/reductions/rref.zep", 52);
		zephir_get_arrval(&_8$$3, &_7$$3);
		ZEPHIR_CPY_WRT(&t, &_8$$3);
		zephir_array_fetch_long(&_9$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 54);
		ZEPHIR_CALL_FUNCTION(&_10$$3, "abs", &_11, 12, &_9$$3);
		zephir_check_call_status();
		if (ZEPHIR_LT_DOUBLE(&_10$$3, epsilon)) {
			hasPivot = 0;
			_14$$4 = (n - 1);
			_13$$4 = col;
			_12$$4 = 0;
			if (_13$$4 <= _14$$4) {
				while (1) {
					if (_12$$4) {
						_13$$4++;
						if (!(_13$$4 <= _14$$4)) {
							break;
						}
					} else {
						_12$$4 = 1;
					}
					i = _13$$4;
					zephir_array_fetch_long(&_15$$5, &t, i, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 58);
					ZEPHIR_CALL_FUNCTION(&_16$$5, "abs", &_11, 12, &_15$$5);
					zephir_check_call_status();
					if (!ZEPHIR_LT_DOUBLE(&_16$$5, epsilon)) {
						hasPivot = 1;
						break;
					}
				}
			}
			if (hasPivot == 0) {
				_19$$7 = (n - 1);
				_18$$7 = col;
				_17$$7 = 0;
				if (_18$$7 <= _19$$7) {
					while (1) {
						if (_17$$7) {
							_18$$7++;
							if (!(_18$$7 <= _19$$7)) {
								break;
							}
						} else {
							_17$$7 = 1;
						}
						i = _18$$7;
						ZEPHIR_INIT_NVAR(&_20$$8);
						ZVAL_DOUBLE(&_20$$8, 0.0);
						zephir_array_update_long(&t, i, &_20$$8, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
					}
				}
				zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				row++;
				continue;
			}
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&_21$$3);
		zephir_array_fetch_long(&_21$$3, &t, col, PH_NOISY, "tensor/reductions/rref.zep", 82);
		divisor =  (zephir_get_doubleval(&_21$$3));
		if (divisor != 1.0) {
			_24$$9 = (n - 1);
			_23$$9 = 0;
			_22$$9 = 0;
			if (_23$$9 <= _24$$9) {
				while (1) {
					if (_22$$9) {
						_23$$9++;
						if (!(_23$$9 <= _24$$9)) {
							break;
						}
					} else {
						_22$$9 = 1;
					}
					i = _23$$9;
					zephir_array_fetch_long(&_25$$10, &t, i, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 86);
					ZEPHIR_INIT_NVAR(&_26$$10);
					ZVAL_DOUBLE(&_26$$10, zephir_safe_div_zval_double(&_25$$10, divisor));
					zephir_array_update_long(&t, i, &_26$$10, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_29$$3 = (row - 1);
		_28$$3 = _29$$3;
		_27$$3 = 0;
		if (_28$$3 >= 0) {
			while (1) {
				if (_27$$3) {
					_28$$3--;
					if (!(_28$$3 >= 0)) {
						break;
					}
				} else {
					_27$$3 = 1;
				}
				i = _28$$3;
				ZEPHIR_OBS_NVAR(&_30$$11);
				zephir_array_fetch_long(&_30$$11, &b, i, PH_NOISY, "tensor/reductions/rref.zep", 91);
				zephir_get_arrval(&_31$$11, &_30$$11);
				ZEPHIR_CPY_WRT(&rowB, &_31$$11);
				ZEPHIR_OBS_NVAR(&_32$$11);
				zephir_array_fetch_long(&_32$$11, &rowB, col, PH_NOISY, "tensor/reductions/rref.zep", 93);
				scale =  (zephir_get_doubleval(&_32$$11));
				ZVAL_DOUBLE(&_33$$11, scale);
				ZEPHIR_CALL_FUNCTION(&_34$$11, "abs", &_11, 12, &_33$$11);
				zephir_check_call_status();
				if (!ZEPHIR_LT_DOUBLE(&_34$$11, epsilon)) {
					_37$$12 = (n - 1);
					_36$$12 = 0;
					_35$$12 = 0;
					if (_36$$12 <= _37$$12) {
						while (1) {
							if (_35$$12) {
								_36$$12++;
								if (!(_36$$12 <= _37$$12)) {
									break;
								}
							} else {
								_35$$12 = 1;
							}
							j = _36$$12;
							zephir_array_fetch_long(&_38$$13, &rowB, j, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 97);
							zephir_array_fetch_long(&_39$$13, &t, j, PH_NOISY | PH_READONLY, "tensor/reductions/rref.zep", 97);
							ZEPHIR_INIT_NVAR(&_40$$13);
							ZVAL_LONG(&_40$$13, (zephir_get_numberval(&_38$$13) - (scale * (zend_long) zephir_get_numberval(&_39$$13))));
							zephir_array_update_long(&rowB, j, &_40$$13, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
						}
					}
				}
				zephir_array_update_long(&b, i, &rowB, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	object_init_ex(return_value, tensor_reductions_rref_ce);
	ZEPHIR_CALL_CE_STATIC(&_41, tensor_matrix_ce, "quick", NULL, 0, &b);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 34, &_41);
	zephir_check_call_status();
	RETURN_MM();
}

/**
 * @param \Tensor\Matrix a
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Reductions_Rref, __construct)
{
	zval *a, a_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(a, zephir_get_internal_ce(SL("tensor\\matrix")))
	ZEND_PARSE_PARAMETERS_END();
	zephir_fetch_params_without_memory_grow(1, 0, &a);
	zephir_update_property_zval(this_ptr, ZEND_STRL("a"), a);
}

/**
 * Return the reduced matrix in reduced row echelon form.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Reductions_Rref, a)
{

	RETURN_MEMBER(getThis(), "a");
}

