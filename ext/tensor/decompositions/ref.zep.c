
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
ZEPHIR_INIT_CLASS(Tensor_Decompositions_Ref) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Decompositions, Ref, tensor, decompositions_ref, tensor_decompositions_ref_method_entry, 0);

	/**
	 * The reduced matrix in row echelon form.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_ref_ce, SL("a"), ZEND_ACC_PROTECTED);

	/**
	 * The number of swaps made to compute the row echelon form of the matrix.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_decompositions_ref_ce, SL("swaps"), ZEND_ACC_PROTECTED);

	zend_class_implements(tensor_decompositions_ref_ce, 1, tensor_decompositions_decomposition_ce);
	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Ref, decompose) {

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
PHP_METHOD(Tensor_Decompositions_Ref, gaussianElimination) {

	zval _23$$6;
	zend_bool _7, _10$$3, _27$$3, _32$$8;
	zval b, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_16 = NULL, *_24 = NULL, *_43 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, index = 0, m, n, swaps, _8, _9, _11$$3, _12$$3, _28$$3, _29$$3, _33$$8, _34$$8;
	zval *a, a_sub, temp, diag, scale, _0, _1, _2, _4, _5, _6, _42, _20$$3, _21$$3, _26$$3, _13$$4, _14$$4, _15$$4, _17$$4, _18$$4, _19$$4, _22$$6, _25$$7, _30$$8, _31$$8, _41$$8, _35$$9, _36$$9, _37$$9, _38$$9, _39$$9, _40$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&diag);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_42);
	ZVAL_UNDEF(&_20$$3);
	ZVAL_UNDEF(&_21$$3);
	ZVAL_UNDEF(&_26$$3);
	ZVAL_UNDEF(&_13$$4);
	ZVAL_UNDEF(&_14$$4);
	ZVAL_UNDEF(&_15$$4);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_18$$4);
	ZVAL_UNDEF(&_19$$4);
	ZVAL_UNDEF(&_22$$6);
	ZVAL_UNDEF(&_25$$7);
	ZVAL_UNDEF(&_30$$8);
	ZVAL_UNDEF(&_31$$8);
	ZVAL_UNDEF(&_41$$8);
	ZVAL_UNDEF(&_35$$9);
	ZVAL_UNDEF(&_36$$9);
	ZVAL_UNDEF(&_37$$9);
	ZVAL_UNDEF(&_38$$9);
	ZVAL_UNDEF(&_39$$9);
	ZVAL_UNDEF(&_40$$9);
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
	ZEPHIR_CALL_FUNCTION(&_6, "min", NULL, 15, &_4, &_5);
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
					zephir_array_fetch_long(&_13$$4, &b, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 76);
					zephir_array_fetch_long(&_14$$4, &_13$$4, k, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 76);
					ZEPHIR_CALL_FUNCTION(&_15$$4, "abs", &_16, 12, &_14$$4);
					zephir_check_call_status();
					zephir_array_fetch_long(&_17$$4, &b, index, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 76);
					zephir_array_fetch_long(&_18$$4, &_17$$4, k, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 76);
					ZEPHIR_CALL_FUNCTION(&_19$$4, "abs", &_16, 12, &_18$$4);
					zephir_check_call_status();
					if (ZEPHIR_GT(&_15$$4, &_19$$4)) {
						index = i;
					}
				}
			}
			zephir_array_fetch_long(&_20$$3, &b, index, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 81);
			zephir_array_fetch_long(&_21$$3, &_20$$3, k, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 81);
			if (UNEXPECTED(ZEPHIR_IS_LONG(&_21$$3, 0))) {
				ZEPHIR_INIT_NVAR(&_22$$6);
				object_init_ex(&_22$$6, spl_ce_RuntimeException);
				ZEPHIR_INIT_NVAR(&_23$$6);
				ZEPHIR_CONCAT_SS(&_23$$6, "Cannot compute row echelon form", " of a singular matrix.");
				ZEPHIR_CALL_METHOD(NULL, &_22$$6, "__construct", &_24, 26, &_23$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_22$$6, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 83);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (k != index) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &b, k, PH_NOISY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 87);
				zephir_array_fetch_long(&_25$$7, &b, index, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 89);
				zephir_array_update_long(&b, k, &_25$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&b, index, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				swaps++;
			}
			zephir_array_fetch_long(&_26$$3, &b, k, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 95);
			ZEPHIR_OBS_NVAR(&diag);
			zephir_array_fetch_long(&diag, &_26$$3, k, PH_NOISY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 95);
			_29$$3 = (m - 1);
			_28$$3 = (k + 1);
			_27$$3 = 0;
			if (_28$$3 <= _29$$3) {
				while (1) {
					if (_27$$3) {
						_28$$3++;
						if (!(_28$$3 <= _29$$3)) {
							break;
						}
					} else {
						_27$$3 = 1;
					}
					i = _28$$3;
					if (!ZEPHIR_IS_LONG(&diag, 0)) {
						zephir_array_fetch_long(&_30$$8, &b, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 98);
						zephir_array_fetch_long(&_31$$8, &_30$$8, k, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 98);
						ZEPHIR_INIT_NVAR(&scale);
						div_function(&scale, &_31$$8, &diag);
					} else {
						ZEPHIR_INIT_NVAR(&scale);
						ZVAL_LONG(&scale, 1);
					}
					_34$$8 = (n - 1);
					_33$$8 = (k + 1);
					_32$$8 = 0;
					if (_33$$8 <= _34$$8) {
						while (1) {
							if (_32$$8) {
								_33$$8++;
								if (!(_33$$8 <= _34$$8)) {
									break;
								}
							} else {
								_32$$8 = 1;
							}
							j = _33$$8;
							zephir_array_fetch_long(&_35$$9, &b, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 101);
							zephir_array_fetch_long(&_36$$9, &_35$$9, j, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 101);
							zephir_array_fetch_long(&_37$$9, &b, k, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 101);
							zephir_array_fetch_long(&_38$$9, &_37$$9, j, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 101);
							ZEPHIR_INIT_NVAR(&_39$$9);
							mul_function(&_39$$9, &scale, &_38$$9);
							ZEPHIR_INIT_NVAR(&_40$$9);
							zephir_sub_function(&_40$$9, &_36$$9, &_39$$9);
							zephir_array_update_multi(&b, &_40$$9, SL("ll"), 2, i, j);
						}
					}
					ZEPHIR_INIT_NVAR(&_41$$8);
					ZVAL_LONG(&_41$$8, 0);
					zephir_array_update_multi(&b, &_41$$8, SL("ll"), 2, i, k);
				}
			}
		}
	}
	object_init_ex(return_value, tensor_decompositions_ref_ce);
	ZEPHIR_CALL_CE_STATIC(&_42, tensor_matrix_ce, "quick", &_43, 0, &b);
	zephir_check_call_status();
	ZVAL_LONG(&_4, swaps);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 27, &_42, &_4);
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
PHP_METHOD(Tensor_Decompositions_Ref, rowReductionMethod) {

	zend_bool _4, _19$$3, _8$$4, _14$$8, _23$$11;
	zval b, t, _3, _6$$3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_32 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, m, n, row, col, swaps, _20$$3, _21$$3, _9$$4, _10$$4, _15$$8, _16$$8, _24$$11, _25$$11;
	zval *a, a_sub, scale, divisor, temp, _0, _1, _2, _31, _33, _5$$3, _7$$3, _13$$3, _11$$5, _12$$5, _17$$9, _18$$9, _22$$10, _26$$12, _27$$12, _28$$12, _29$$12, _30$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&divisor);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_31);
	ZVAL_UNDEF(&_33);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_17$$9);
	ZVAL_UNDEF(&_18$$9);
	ZVAL_UNDEF(&_22$$10);
	ZVAL_UNDEF(&_26$$12);
	ZVAL_UNDEF(&_27$$12);
	ZVAL_UNDEF(&_28$$12);
	ZVAL_UNDEF(&_29$$12);
	ZVAL_UNDEF(&_30$$12);
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
		if (!(_4)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&_5$$3);
		zephir_array_fetch_long(&_5$$3, &b, row, PH_NOISY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 137);
		zephir_get_arrval(&_6$$3, &_5$$3);
		ZEPHIR_CPY_WRT(&t, &_6$$3);
		zephir_array_fetch_long(&_7$$3, &t, col, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 139);
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
					zephir_array_fetch_long(&_11$$5, &b, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 141);
					zephir_array_fetch_long(&_12$$5, &_11$$5, col, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 141);
					if (!ZEPHIR_IS_LONG(&_12$$5, 0)) {
						ZEPHIR_OBS_NVAR(&temp);
						zephir_array_fetch_long(&temp, &b, i, PH_NOISY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 142);
						zephir_array_update_long(&b, i, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
						ZEPHIR_CPY_WRT(&t, &temp);
						swaps++;
						break;
					}
				}
			}
		}
		zephir_array_fetch_long(&_13$$3, &t, col, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 154);
		if (ZEPHIR_IS_LONG(&_13$$3, 0)) {
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&divisor);
		zephir_array_fetch_long(&divisor, &t, col, PH_NOISY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 160);
		if (!ZEPHIR_IS_LONG(&divisor, 1)) {
			_16$$8 = (n - 1);
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
					i = _15$$8;
					zephir_array_fetch_long(&_17$$9, &t, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 164);
					ZEPHIR_INIT_NVAR(&_18$$9);
					div_function(&_18$$9, &_17$$9, &divisor);
					zephir_array_update_long(&t, i, &_18$$9, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_21$$3 = (m - 1);
		_20$$3 = (row + 1);
		_19$$3 = 0;
		if (_20$$3 <= _21$$3) {
			while (1) {
				if (_19$$3) {
					_20$$3++;
					if (!(_20$$3 <= _21$$3)) {
						break;
					}
				} else {
					_19$$3 = 1;
				}
				i = _20$$3;
				zephir_array_fetch_long(&_22$$10, &b, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 169);
				ZEPHIR_OBS_NVAR(&scale);
				zephir_array_fetch_long(&scale, &_22$$10, col, PH_NOISY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 169);
				if (!ZEPHIR_IS_LONG(&scale, 0)) {
					_25$$11 = (n - 1);
					_24$$11 = 0;
					_23$$11 = 0;
					if (_24$$11 <= _25$$11) {
						while (1) {
							if (_23$$11) {
								_24$$11++;
								if (!(_24$$11 <= _25$$11)) {
									break;
								}
							} else {
								_23$$11 = 1;
							}
							j = _24$$11;
							zephir_array_fetch_long(&_26$$12, &b, i, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 173);
							zephir_array_fetch_long(&_27$$12, &_26$$12, j, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 173);
							zephir_array_fetch_long(&_28$$12, &t, j, PH_NOISY | PH_READONLY, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 173);
							ZEPHIR_INIT_NVAR(&_29$$12);
							mul_function(&_29$$12, &scale, &_28$$12);
							ZEPHIR_INIT_NVAR(&_30$$12);
							zephir_sub_function(&_30$$12, &_27$$12, &_29$$12);
							zephir_array_update_multi(&b, &_30$$12, SL("ll"), 2, i, j);
						}
					}
				}
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	object_init_ex(return_value, tensor_decompositions_ref_ce);
	ZEPHIR_CALL_CE_STATIC(&_31, tensor_matrix_ce, "quick", &_32, 0, &b);
	zephir_check_call_status();
	ZVAL_LONG(&_33, swaps);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 27, &_31, &_33);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix a
 * @param int swaps
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Decompositions_Ref, __construct) {

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


	if (swaps < 0) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, swaps);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of swaps must", " be greater than or equal to 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "/mnt/c/Users/Andrew/Workspace/Tensor/tensor/decompositions/ref.zep", 197);
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
PHP_METHOD(Tensor_Decompositions_Ref, a) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

/**
 * Return the number of swaps made to reduce the matrix to ref.
 *
 * @return int
 */
PHP_METHOD(Tensor_Decompositions_Ref, swaps) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "swaps");

}

