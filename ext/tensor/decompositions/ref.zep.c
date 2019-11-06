
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

	zval _16$$6;
	zend_bool _0, _3$$3, _20$$3, _25$$8;
	zend_ulong swaps;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_9 = NULL, *_17 = NULL, *_36 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, index = 0, _1, _2, _4$$3, _5$$3, _21$$3, _22$$3, _26$$8, _27$$8;
	zval *a, a_sub, temp, diag, scale, m, n, minDim, b, _35, _37, _13$$3, _14$$3, _19$$3, _6$$4, _7$$4, _8$$4, _10$$4, _11$$4, _12$$4, _15$$6, _18$$7, _23$$8, _24$$8, _34$$8, _28$$9, _29$$9, _30$$9, _31$$9, _32$$9, _33$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&diag);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&minDim);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_35);
	ZVAL_UNDEF(&_37);
	ZVAL_UNDEF(&_13$$3);
	ZVAL_UNDEF(&_14$$3);
	ZVAL_UNDEF(&_19$$3);
	ZVAL_UNDEF(&_6$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&_12$$4);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_18$$7);
	ZVAL_UNDEF(&_23$$8);
	ZVAL_UNDEF(&_24$$8);
	ZVAL_UNDEF(&_34$$8);
	ZVAL_UNDEF(&_28$$9);
	ZVAL_UNDEF(&_29$$9);
	ZVAL_UNDEF(&_30$$9);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&_32$$9);
	ZVAL_UNDEF(&_33$$9);
	ZVAL_UNDEF(&_16$$6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&m, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&n, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_FUNCTION(&minDim, "min", NULL, 14, &m, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&b, a, "asarray", NULL, 0);
	zephir_check_call_status();
	swaps = 0;
	_2 = (zephir_get_numberval(&minDim) - 1);
	_1 = 0;
	_0 = 0;
	if (_1 <= _2) {
		while (1) {
			if (_0) {
				_1++;
				if (!(_1 <= _2)) {
					break;
				}
			} else {
				_0 = 1;
			}
			k = _1;
			index = k;
			_5$$3 = (zephir_get_numberval(&m) - 1);
			_4$$3 = k;
			_3$$3 = 0;
			if (_4$$3 <= _5$$3) {
				while (1) {
					if (_3$$3) {
						_4$$3++;
						if (!(_4$$3 <= _5$$3)) {
							break;
						}
					} else {
						_3$$3 = 1;
					}
					i = _4$$3;
					zephir_array_fetch_long(&_6$$4, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 77);
					zephir_array_fetch_long(&_7$$4, &_6$$4, k, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 77);
					ZEPHIR_CALL_FUNCTION(&_8$$4, "abs", &_9, 11, &_7$$4);
					zephir_check_call_status();
					zephir_array_fetch_long(&_10$$4, &b, index, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 77);
					zephir_array_fetch_long(&_11$$4, &_10$$4, k, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 77);
					ZEPHIR_CALL_FUNCTION(&_12$$4, "abs", &_9, 11, &_11$$4);
					zephir_check_call_status();
					if (ZEPHIR_GT(&_8$$4, &_12$$4)) {
						index = i;
					}
				}
			}
			zephir_array_fetch_long(&_13$$3, &b, index, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 82);
			zephir_array_fetch_long(&_14$$3, &_13$$3, k, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 82);
			if (UNEXPECTED(ZEPHIR_IS_LONG(&_14$$3, 0))) {
				ZEPHIR_INIT_NVAR(&_15$$6);
				object_init_ex(&_15$$6, spl_ce_RuntimeException);
				ZEPHIR_INIT_NVAR(&_16$$6);
				ZEPHIR_CONCAT_SS(&_16$$6, "Cannot compute row echelon form", " of a singular matrix.");
				ZEPHIR_CALL_METHOD(NULL, &_15$$6, "__construct", &_17, 20, &_16$$6);
				zephir_check_call_status();
				zephir_throw_exception_debug(&_15$$6, "tensor/decompositions/ref.zep", 84);
				ZEPHIR_MM_RESTORE();
				return;
			}
			if (k != index) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &b, k, PH_NOISY, "tensor/decompositions/ref.zep", 88);
				zephir_array_fetch_long(&_18$$7, &b, index, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 90);
				zephir_array_update_long(&b, k, &_18$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&b, index, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				swaps++;
			}
			zephir_array_fetch_long(&_19$$3, &b, k, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 96);
			ZEPHIR_OBS_NVAR(&diag);
			zephir_array_fetch_long(&diag, &_19$$3, k, PH_NOISY, "tensor/decompositions/ref.zep", 96);
			_22$$3 = (zephir_get_numberval(&m) - 1);
			_21$$3 = (k + 1);
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
					if (!ZEPHIR_IS_LONG(&diag, 0)) {
						zephir_array_fetch_long(&_23$$8, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 99);
						zephir_array_fetch_long(&_24$$8, &_23$$8, k, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 99);
						ZEPHIR_INIT_NVAR(&scale);
						div_function(&scale, &_24$$8, &diag);
					} else {
						ZEPHIR_INIT_NVAR(&scale);
						ZVAL_LONG(&scale, 1);
					}
					_27$$8 = (zephir_get_numberval(&n) - 1);
					_26$$8 = (k + 1);
					_25$$8 = 0;
					if (_26$$8 <= _27$$8) {
						while (1) {
							if (_25$$8) {
								_26$$8++;
								if (!(_26$$8 <= _27$$8)) {
									break;
								}
							} else {
								_25$$8 = 1;
							}
							j = _26$$8;
							zephir_array_fetch_long(&_28$$9, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 102);
							zephir_array_fetch_long(&_29$$9, &_28$$9, j, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 102);
							zephir_array_fetch_long(&_30$$9, &b, k, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 102);
							zephir_array_fetch_long(&_31$$9, &_30$$9, j, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 102);
							ZEPHIR_INIT_NVAR(&_32$$9);
							mul_function(&_32$$9, &scale, &_31$$9);
							ZEPHIR_INIT_NVAR(&_33$$9);
							zephir_sub_function(&_33$$9, &_29$$9, &_32$$9);
							zephir_array_update_multi(&b, &_33$$9, SL("ll"), 2, i, j);
						}
					}
					ZEPHIR_INIT_NVAR(&_34$$8);
					ZVAL_LONG(&_34$$8, 0);
					zephir_array_update_multi(&b, &_34$$8, SL("ll"), 2, i, k);
				}
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_35, tensor_matrix_ce, "quick", &_36, 0, &b);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&b, &_35);
	object_init_ex(return_value, tensor_decompositions_ref_ce);
	ZVAL_LONG(&_37, swaps);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 26, &b, &_37);
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

	zend_bool _0, _13$$3, _2$$4, _8$$8, _17$$11;
	zend_ulong swaps;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_26 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, row, col, _14$$3, _15$$3, _3$$4, _4$$4, _9$$8, _10$$8, _18$$11, _19$$11;
	zval *a, a_sub, t, scale, divisor, temp, m, n, b, _25, _27, _1$$3, _7$$3, _5$$5, _6$$5, _11$$9, _12$$9, _16$$10, _20$$12, _21$$12, _22$$12, _23$$12, _24$$12;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&divisor);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_7$$3);
	ZVAL_UNDEF(&_5$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_11$$9);
	ZVAL_UNDEF(&_12$$9);
	ZVAL_UNDEF(&_16$$10);
	ZVAL_UNDEF(&_20$$12);
	ZVAL_UNDEF(&_21$$12);
	ZVAL_UNDEF(&_22$$12);
	ZVAL_UNDEF(&_23$$12);
	ZVAL_UNDEF(&_24$$12);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&m, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&n, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&b, a, "asarray", NULL, 0);
	zephir_check_call_status();
	row = 0;
	col = 0;
	swaps = 0;
	while (1) {
		_0 = ZEPHIR_GT_LONG(&m, row);
		if (_0) {
			_0 = ZEPHIR_GT_LONG(&n, col);
		}
		if (!(_0)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&t);
		zephir_array_fetch_long(&t, &b, row, PH_NOISY, "tensor/decompositions/ref.zep", 138);
		zephir_array_fetch_long(&_1$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 140);
		if (ZEPHIR_IS_LONG(&_1$$3, 0)) {
			_4$$4 = (zephir_get_numberval(&m) - 1);
			_3$$4 = (row + 1);
			_2$$4 = 0;
			if (_3$$4 <= _4$$4) {
				while (1) {
					if (_2$$4) {
						_3$$4++;
						if (!(_3$$4 <= _4$$4)) {
							break;
						}
					} else {
						_2$$4 = 1;
					}
					i = _3$$4;
					zephir_array_fetch_long(&_5$$5, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 142);
					zephir_array_fetch_long(&_6$$5, &_5$$5, col, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 142);
					if (!ZEPHIR_IS_LONG(&_6$$5, 0)) {
						ZEPHIR_OBS_NVAR(&temp);
						zephir_array_fetch_long(&temp, &b, i, PH_NOISY, "tensor/decompositions/ref.zep", 143);
						zephir_array_update_long(&b, i, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
						ZEPHIR_CPY_WRT(&t, &temp);
						swaps++;
						break;
					}
				}
			}
		}
		zephir_array_fetch_long(&_7$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 155);
		if (ZEPHIR_IS_LONG(&_7$$3, 0)) {
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&divisor);
		zephir_array_fetch_long(&divisor, &t, col, PH_NOISY, "tensor/decompositions/ref.zep", 161);
		if (!ZEPHIR_IS_LONG(&divisor, 1)) {
			_10$$8 = (zephir_get_numberval(&n) - 1);
			_9$$8 = 0;
			_8$$8 = 0;
			if (_9$$8 <= _10$$8) {
				while (1) {
					if (_8$$8) {
						_9$$8++;
						if (!(_9$$8 <= _10$$8)) {
							break;
						}
					} else {
						_8$$8 = 1;
					}
					i = _9$$8;
					zephir_array_fetch_long(&_11$$9, &t, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 165);
					ZEPHIR_INIT_NVAR(&_12$$9);
					div_function(&_12$$9, &_11$$9, &divisor);
					zephir_array_update_long(&t, i, &_12$$9, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_15$$3 = (zephir_get_numberval(&m) - 1);
		_14$$3 = (row + 1);
		_13$$3 = 0;
		if (_14$$3 <= _15$$3) {
			while (1) {
				if (_13$$3) {
					_14$$3++;
					if (!(_14$$3 <= _15$$3)) {
						break;
					}
				} else {
					_13$$3 = 1;
				}
				i = _14$$3;
				zephir_array_fetch_long(&_16$$10, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 170);
				ZEPHIR_OBS_NVAR(&scale);
				zephir_array_fetch_long(&scale, &_16$$10, col, PH_NOISY, "tensor/decompositions/ref.zep", 170);
				if (!ZEPHIR_IS_LONG(&scale, 0)) {
					_19$$11 = (zephir_get_numberval(&n) - 1);
					_18$$11 = 0;
					_17$$11 = 0;
					if (_18$$11 <= _19$$11) {
						while (1) {
							if (_17$$11) {
								_18$$11++;
								if (!(_18$$11 <= _19$$11)) {
									break;
								}
							} else {
								_17$$11 = 1;
							}
							j = _18$$11;
							zephir_array_fetch_long(&_20$$12, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 174);
							zephir_array_fetch_long(&_21$$12, &_20$$12, j, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 174);
							zephir_array_fetch_long(&_22$$12, &t, j, PH_NOISY | PH_READONLY, "tensor/decompositions/ref.zep", 174);
							ZEPHIR_INIT_NVAR(&_23$$12);
							mul_function(&_23$$12, &scale, &_22$$12);
							ZEPHIR_INIT_NVAR(&_24$$12);
							zephir_sub_function(&_24$$12, &_21$$12, &_23$$12);
							zephir_array_update_multi(&b, &_24$$12, SL("ll"), 2, i, j);
						}
					}
				}
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	ZEPHIR_CALL_CE_STATIC(&_25, tensor_matrix_ce, "quick", &_26, 0, &b);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&b, &_25);
	object_init_ex(return_value, tensor_decompositions_ref_ce);
	ZVAL_LONG(&_27, swaps);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 26, &b, &_27);
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
		zephir_throw_exception_debug(&_0$$3, "tensor/decompositions/ref.zep", 200);
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

