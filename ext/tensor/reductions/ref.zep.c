
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
#include "ext/spl/spl_exceptions.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/array.h"
#include "kernel/exception.h"
#include "kernel/concat.h"


/**
 * REF
 *
 * The row echelon form (REF) of a matrix.
 *
 * References:
 * [1] M. Rogoyski. (2019). Math PHP: Powerful modern math library for PHP.
 * http://github.com/markrogoyski/math-php.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Reductions_Ref) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Reductions, Ref, tensor, reductions_ref, tensor_reductions_ref_method_entry, 0);

	/**
	 * The reduced matrix in row echelon form.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_reductions_ref_ce, SL("a"), ZEND_ACC_PROTECTED);

	/**
	 * The number of swaps made to compute the row echelon form of the matrix.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_reductions_ref_ce, SL("swaps"), ZEND_ACC_PROTECTED);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Reductions_Ref, reduce) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);




	/* try_start_1: */

		ZEPHIR_RETURN_CALL_SELF("gaussianelimination", NULL, 0, a);
		zephir_check_call_status_or_jump(try_end_1);
		RETURN_MM();

	try_end_1:

	if (EG(exception)) {
		ZEPHIR_INIT_VAR(&_0);
		ZVAL_OBJ(&_0, EG(exception));
		Z_ADDREF_P(&_0);
		ZEPHIR_INIT_VAR(&_1);
		if (zephir_instance_of_ev(&_0, spl_ce_RuntimeException)) {
			zend_clear_exception(TSRMLS_C);
			ZEPHIR_CPY_WRT(&_1, &_0);
			ZEPHIR_RETURN_CALL_SELF("rowreductionmethod", NULL, 0, a);
			zephir_check_call_status();
			RETURN_MM();
		}
	}

}

/**
 * Calculate the row echelon form (REF) of the matrix using Gaussian
 * elimination. Return the matrix and the number of swaps in a tuple.
 *
 * @param \Tensor\Matrix a
 * @throws \RuntimeException
 * @return self
 */
PHP_METHOD(Tensor_Reductions_Ref, gaussianElimination) {

	zval _23$$6;
	zend_bool _7, _10$$3, _28$$3, _34$$8;
	zval b, _3;
	double diag = 0, scale = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_16 = NULL, *_24 = NULL, *_44 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, index = 0, m, n, swaps, _8, _9, _11$$3, _12$$3, _29$$3, _30$$3, _35$$8, _36$$8;
	zval *a, a_sub, temp, _0, _1, _2, _4, _5, _6, _43, _20$$3, _21$$3, _26$$3, _27$$3, _13$$4, _14$$4, _15$$4, _17$$4, _18$$4, _19$$4, _22$$6, _25$$7, _31$$8, _32$$8, _33$$8, _42$$8, _37$$9, _38$$9, _39$$9, _40$$9, _41$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_43);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_26$$3);
	ZVAL_UNDEF(&_27$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_18$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_31$$8);
	ZVAL_UNDEF(&_32$$8);
	ZVAL_UNDEF(&_33$$8);
	ZVAL_UNDEF(&_42$$8);
	ZVAL_UNDEF(&_37$$9);
	ZVAL_UNDEF(&_38$$9);
	ZVAL_UNDEF(&_39$$9);
	ZVAL_UNDEF(&_40$$9);
	ZVAL_UNDEF(&_41$$9);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_23$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_CALL_METHOD(&_0, a, "m", NULL, 0);
	zephir_check_call_status();
	m = zephir_get_intval(&_0);
	ZEPHIR_CALL_METHOD(&_1, a, "n", NULL, 0);
	zephir_check_call_status();
	n = zephir_get_intval(&_1);
	ZEPHIR_CALL_METHOD(&_2, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_3, &_2);
	ZEPHIR_CPY_WRT(&b, &_3);
	swaps = 0;
	ZVAL_LONG(&_4, m);
	ZVAL_LONG(&_5, n);
	ZEPHIR_CALL_FUNCTION(&_6, "min", NULL, 18, &_4, &_5);
	zephir_check_call_status();
	_9 = (zephir_get_numberval(&_6) - 1);
	_8 = 0;
	_7 = 0;
	if (_8 <= _9) {
		while (1) {
			if (_7) {
				_8++;
				if (!(_8 <= _9)) {
					break;
				}
			} else {
				_7 = 1;
			}
			k = _8;
			index = k;
			_12$$3 = (m - 1);
			_11$$3 = k;
			_10$$3 = 0;
			if (_11$$3 <= _12$$3) {
				while (1) {
					if (_10$$3) {
						_11$$3++;
						if (!(_11$$3 <= _12$$3)) {
							break;
						}
					} else {
						_10$$3 = 1;
					}
					i = _11$$3;
					zephir_array_fetch_long(&_13$$4, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 77);
					zephir_array_fetch_long(&_14$$4, &_13$$4, k, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 77);
					ZEPHIR_CALL_FUNCTION(&_15$$4, "abs", &_16, 12, &_14$$4);
					zephir_check_call_status();
					zephir_array_fetch_long(&_17$$4, &b, index, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 77);
					zephir_array_fetch_long(&_18$$4, &_17$$4, k, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 77);
					ZEPHIR_CALL_FUNCTION(&_19$$4, "abs", &_16, 12, &_18$$4);
					zephir_check_call_status();
					if (ZEPHIR_GT(&_15$$4, &_19$$4)) {
						index = i;
					}
				}
			}
			zephir_array_fetch_long(&_20$$3, &b, index, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 82);
			zephir_array_fetch_long(&_21$$3, &_20$$3, k, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 82);
			if (UNEXPECTED(ZEPHIR_IS_LONG(&_21$$3, 0))) {
				ZEPHIR_INIT_NVAR(&_22$$6);
				object_init_ex(&_22$$6, spl_ce_RuntimeException);
				ZEPHIR_INIT_NVAR(&_23$$6);
				ZEPHIR_CONCAT_SS(&_23$$6, "Cannot compute row echelon form", " of a singular matrix.");
				ZEPHIR_CALL_METHOD(NULL, &_22$$6, "__construct", &_24, 30, &_23$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_22$$6, "tensor/reductions/ref.zep", 84);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (k != index) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &b, k, PH_NOISY, "tensor/reductions/ref.zep", 88);
				zephir_array_fetch_long(&_25$$7, &b, index, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 90);
				zephir_array_update_long(&b, k, &_25$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&b, index, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				swaps++;
			}
			zephir_array_fetch_long(&_26$$3, &b, k, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 96);
			ZEPHIR_OBS_NVAR(&_27$$3);
			zephir_array_fetch_long(&_27$$3, &_26$$3, k, PH_NOISY, "tensor/reductions/ref.zep", 96);
			diag = zephir_get_doubleval(&_27$$3);
			_30$$3 = (m - 1);
			_29$$3 = (k + 1);
			_28$$3 = 0;
			if (_29$$3 <= _30$$3) {
				while (1) {
					if (_28$$3) {
						_29$$3++;
						if (!(_29$$3 <= _30$$3)) {
							break;
						}
					} else {
						_28$$3 = 1;
					}
					i = _29$$3;
					ZEPHIR_INIT_NVAR(&_31$$8);
					if (diag != 0.0) {
						zephir_array_fetch_long(&_32$$8, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 99);
						ZEPHIR_OBS_NVAR(&_33$$8);
						zephir_array_fetch_long(&_33$$8, &_32$$8, k, PH_NOISY, "tensor/reductions/ref.zep", 99);
						ZEPHIR_INIT_NVAR(&_31$$8);
						ZVAL_DOUBLE(&_31$$8, zephir_safe_div_double_double(zephir_get_doubleval(&_33$$8), diag));
					} else {
						ZEPHIR_INIT_NVAR(&_31$$8);
						ZVAL_DOUBLE(&_31$$8, 1.0);
					}
					scale = zephir_get_numberval(&_31$$8);
					_36$$8 = (n - 1);
					_35$$8 = (k + 1);
					_34$$8 = 0;
					if (_35$$8 <= _36$$8) {
						while (1) {
							if (_34$$8) {
								_35$$8++;
								if (!(_35$$8 <= _36$$8)) {
									break;
								}
							} else {
								_34$$8 = 1;
							}
							j = _35$$8;
							zephir_array_fetch_long(&_37$$9, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 102);
							ZEPHIR_OBS_NVAR(&_38$$9);
							zephir_array_fetch_long(&_38$$9, &_37$$9, j, PH_NOISY, "tensor/reductions/ref.zep", 102);
							zephir_array_fetch_long(&_39$$9, &b, k, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 102);
							ZEPHIR_OBS_NVAR(&_40$$9);
							zephir_array_fetch_long(&_40$$9, &_39$$9, j, PH_NOISY, "tensor/reductions/ref.zep", 102);
							ZEPHIR_INIT_NVAR(&_41$$9);
							ZVAL_DOUBLE(&_41$$9, (zephir_get_doubleval(&_38$$9) - (scale * zephir_get_doubleval(&_40$$9))));
							zephir_array_update_multi(&b, &_41$$9, SL("ll"), 2, i, j);
						}
					}
					ZEPHIR_INIT_NVAR(&_42$$8);
					ZVAL_LONG(&_42$$8, 0);
					zephir_array_update_multi(&b, &_42$$8, SL("ll"), 2, i, k);
				}
			}
		}
	}
	object_init_ex(return_value, tensor_reductions_ref_ce);
	ZEPHIR_CALL_CE_STATIC(&_43, tensor_matrix_ce, "quick", &_44, 0, &b);
	zephir_check_call_status();
	ZVAL_LONG(&_4, swaps);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 32, &_43, &_4);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Calculate the row echelon form (REF) of the matrix using the row
 * reduction method. Return the matrix and the number of swaps in a
 * tuple.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Reductions_Ref, rowReductionMethod) {

	zend_bool _4, _20$$3, _8$$4, _15$$8, _25$$11;
	zval b, t, _3, _6$$3;
	double scale = 0, divisor = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_33 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, m, n, row, col, swaps, _21$$3, _22$$3, _9$$4, _10$$4, _16$$8, _17$$8, _26$$11, _27$$11;
	zval *a, a_sub, temp, _0, _1, _2, _32, _34, _5$$3, _7$$3, _13$$3, _14$$3, _11$$5, _12$$5, _18$$9, _19$$9, _23$$10, _24$$10, _28$$12, _29$$12, _30$$12, _31$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_32);
	ZVAL_UNDEF(&_34);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_23$$10);
	ZVAL_UNDEF(&_24$$10);
	ZVAL_UNDEF(&_28$$12);
	ZVAL_UNDEF(&_29$$12);
	ZVAL_UNDEF(&_30$$12);
	ZVAL_UNDEF(&_31$$12);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_6$$3);

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
	ZEPHIR_CALL_METHOD(&_2, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_3, &_2);
	ZEPHIR_CPY_WRT(&b, &_3);
	swaps = 0;
	while (1) {
		_4 = row < m;
		if (_4) {
			_4 = col < n;
		}
		if (!(EXPECTED(_4))) {
			break;
		}
		ZEPHIR_OBS_NVAR(&_5$$3);
		zephir_array_fetch_long(&_5$$3, &b, row, PH_NOISY, "tensor/reductions/ref.zep", 139);
		zephir_get_arrval(&_6$$3, &_5$$3);
		ZEPHIR_CPY_WRT(&t, &_6$$3);
		zephir_array_fetch_long(&_7$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 141);
		if (ZEPHIR_IS_LONG(&_7$$3, 0)) {
			_10$$4 = (m - 1);
			_9$$4 = (row + 1);
			_8$$4 = 0;
			if (_9$$4 <= _10$$4) {
				while (1) {
					if (_8$$4) {
						_9$$4++;
						if (!(_9$$4 <= _10$$4)) {
							break;
						}
					} else {
						_8$$4 = 1;
					}
					i = _9$$4;
					zephir_array_fetch_long(&_11$$5, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 143);
					zephir_array_fetch_long(&_12$$5, &_11$$5, col, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 143);
					if (!ZEPHIR_IS_LONG(&_12$$5, 0)) {
						ZEPHIR_OBS_NVAR(&temp);
						zephir_array_fetch_long(&temp, &b, i, PH_NOISY, "tensor/reductions/ref.zep", 144);
						zephir_array_update_long(&b, i, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
						ZEPHIR_CPY_WRT(&t, &temp);
						swaps++;
						break;
					}
				}
			}
		}
		zephir_array_fetch_long(&_13$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 156);
		if (ZEPHIR_IS_LONG(&_13$$3, 0)) {
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&_14$$3);
		zephir_array_fetch_long(&_14$$3, &t, col, PH_NOISY, "tensor/reductions/ref.zep", 162);
		divisor = zephir_get_doubleval(&_14$$3);
		if (divisor != 1.0) {
			_17$$8 = (n - 1);
			_16$$8 = 0;
			_15$$8 = 0;
			if (_16$$8 <= _17$$8) {
				while (1) {
					if (_15$$8) {
						_16$$8++;
						if (!(_16$$8 <= _17$$8)) {
							break;
						}
					} else {
						_15$$8 = 1;
					}
					i = _16$$8;
					ZEPHIR_OBS_NVAR(&_18$$9);
					zephir_array_fetch_long(&_18$$9, &t, i, PH_NOISY, "tensor/reductions/ref.zep", 166);
					ZEPHIR_INIT_NVAR(&_19$$9);
					ZVAL_DOUBLE(&_19$$9, zephir_safe_div_double_double(zephir_get_doubleval(&_18$$9), divisor));
					zephir_array_update_long(&t, i, &_19$$9, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_22$$3 = (m - 1);
		_21$$3 = (row + 1);
		_20$$3 = 0;
		if (_21$$3 <= _22$$3) {
			while (1) {
				if (_20$$3) {
					_21$$3++;
					if (!(_21$$3 <= _22$$3)) {
						break;
					}
				} else {
					_20$$3 = 1;
				}
				i = _21$$3;
				zephir_array_fetch_long(&_23$$10, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 171);
				ZEPHIR_OBS_NVAR(&_24$$10);
				zephir_array_fetch_long(&_24$$10, &_23$$10, col, PH_NOISY, "tensor/reductions/ref.zep", 171);
				scale = zephir_get_doubleval(&_24$$10);
				if (scale != 0.0) {
					_27$$11 = (n - 1);
					_26$$11 = 0;
					_25$$11 = 0;
					if (_26$$11 <= _27$$11) {
						while (1) {
							if (_25$$11) {
								_26$$11++;
								if (!(_26$$11 <= _27$$11)) {
									break;
								}
							} else {
								_25$$11 = 1;
							}
							j = _26$$11;
							zephir_array_fetch_long(&_28$$12, &b, i, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 175);
							ZEPHIR_OBS_NVAR(&_29$$12);
							zephir_array_fetch_long(&_29$$12, &_28$$12, j, PH_NOISY, "tensor/reductions/ref.zep", 175);
							ZEPHIR_OBS_NVAR(&_30$$12);
							zephir_array_fetch_long(&_30$$12, &t, j, PH_NOISY, "tensor/reductions/ref.zep", 175);
							ZEPHIR_INIT_NVAR(&_31$$12);
							ZVAL_DOUBLE(&_31$$12, (zephir_get_doubleval(&_29$$12) - (scale * zephir_get_doubleval(&_30$$12))));
							zephir_array_update_multi(&b, &_31$$12, SL("ll"), 2, i, j);
						}
					}
				}
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	object_init_ex(return_value, tensor_reductions_ref_ce);
	ZEPHIR_CALL_CE_STATIC(&_32, tensor_matrix_ce, "quick", &_33, 0, &b);
	zephir_check_call_status();
	ZVAL_LONG(&_34, swaps);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 32, &_32, &_34);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix a
 * @param int swaps
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Reductions_Ref, __construct) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long swaps, ZEPHIR_LAST_CALL_STATUS;
	zval *a, a_sub, *swaps_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0$$3);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&_4);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &swaps_param);

	swaps = zephir_get_intval(swaps_param);


	if (UNEXPECTED(swaps < 0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, swaps);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of swaps must", " be greater than or equal to 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/reductions/ref.zep", 199);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval(this_ptr, SL("a"), a);
	ZEPHIR_INIT_ZVAL_NREF(_4);
	ZVAL_LONG(&_4, swaps);
	zephir_update_property_zval(this_ptr, SL("swaps"), &_4);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the reduced matrix in row echelon form.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Reductions_Ref, a) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

/**
 * Return the number of swaps made to reduce the matrix to ref.
 *
 * @return int
 */
PHP_METHOD(Tensor_Reductions_Ref, swaps) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "swaps");

}

