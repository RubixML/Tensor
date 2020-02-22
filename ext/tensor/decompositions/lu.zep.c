
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
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/array.h"
#include "kernel/object.h"


/**
 * LU
 *
 * The LU decomposition is a factorization of a Matrix as the product of a
 * lower and upper triangular matrix as well as a permutation matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Decompositions_Lu) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Decompositions, Lu, tensor, decompositions_lu, tensor_decompositions_lu_method_entry, 0);

	/**
	 * The lower triangular matrix.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_lu_ce, SL("l"), ZEND_ACC_PROTECTED);

	/**
	 * The upper triangular matrix.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_lu_ce, SL("u"), ZEND_ACC_PROTECTED);

	/**
	 * The permutation matrix.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_lu_ce, SL("p"), ZEND_ACC_PROTECTED);

	zephir_declare_class_constant_double(tensor_decompositions_lu_ce, SL("EPSILON"), 0.00000001);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Lu, decompose) {

	zend_bool _17, _32, _22$$4, _35$$8, _49$$8, _38$$9, _52$$11;
	zval aHat, l, u, p, pa, _3, _8, _13, _16, _31;
	double max = 0, sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL, *_10 = NULL, *_28 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, row = 0, n, _18, _19, _33, _34, _23$$4, _24$$4, _36$$8, _37$$8, _50$$8, _51$$8, _39$$9, _40$$9, _53$$11, _54$$11;
	zval *a, a_sub, _0, temp, valueA, _1, _2, _4, _6, _7, _9, _11, _12, _14, _15, _27, _29, _30, _67, _68, _69, _20$$4, _21$$4, _25$$5, _26$$7, _46$$9, _47$$9, _48$$9, _41$$10, _42$$10, _43$$10, _44$$10, _45$$10, _60$$11, _61$$11, _62$$11, _63$$11, _64$$11, _66$$11, _55$$12, _56$$12, _57$$12, _58$$12, _59$$12, _65$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_14);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_30);
	ZVAL_UNDEF(&_67);
	ZVAL_UNDEF(&_68);
	ZVAL_UNDEF(&_69);
	ZVAL_UNDEF(&_20$$4);
	ZVAL_UNDEF(&_21$$4);
	ZVAL_UNDEF(&_25$$5);
	ZVAL_UNDEF(&_26$$7);
	ZVAL_UNDEF(&_46$$9);
	ZVAL_UNDEF(&_47$$9);
	ZVAL_UNDEF(&_48$$9);
	ZVAL_UNDEF(&_41$$10);
	ZVAL_UNDEF(&_42$$10);
	ZVAL_UNDEF(&_43$$10);
	ZVAL_UNDEF(&_44$$10);
	ZVAL_UNDEF(&_45$$10);
	ZVAL_UNDEF(&_60$$11);
	ZVAL_UNDEF(&_61$$11);
	ZVAL_UNDEF(&_62$$11);
	ZVAL_UNDEF(&_63$$11);
	ZVAL_UNDEF(&_64$$11);
	ZVAL_UNDEF(&_66$$11);
	ZVAL_UNDEF(&_55$$12);
	ZVAL_UNDEF(&_56$$12);
	ZVAL_UNDEF(&_57$$12);
	ZVAL_UNDEF(&_58$$12);
	ZVAL_UNDEF(&_59$$12);
	ZVAL_UNDEF(&_65$$14);
	ZVAL_UNDEF(&aHat);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&pa);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_16);
	ZVAL_UNDEF(&_31);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_RuntimeException, "Cannot decompose a non-square matrix.", "tensor/decompositions/lu.zep", 50);
		return;
	}
	ZEPHIR_INIT_VAR(&aHat);
	array_init(&aHat);
	ZEPHIR_INIT_VAR(&l);
	array_init(&l);
	ZEPHIR_INIT_VAR(&u);
	array_init(&u);
	ZEPHIR_INIT_VAR(&p);
	array_init(&p);
	ZEPHIR_INIT_VAR(&pa);
	array_init(&pa);
	ZEPHIR_CALL_METHOD(&_1, a, "n", NULL, 0);
	zephir_check_call_status();
	n = zephir_get_intval(&_1);
	ZEPHIR_CALL_METHOD(&_2, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_3, &_2);
	ZEPHIR_CPY_WRT(&aHat, &_3);
	ZVAL_LONG(&_6, n);
	ZEPHIR_CALL_CE_STATIC(&_4, tensor_matrix_ce, "identity", &_5, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_7, &_4, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_8, &_7);
	ZEPHIR_CPY_WRT(&l, &_8);
	ZVAL_LONG(&_6, n);
	ZVAL_LONG(&_11, n);
	ZEPHIR_CALL_CE_STATIC(&_9, tensor_matrix_ce, "zeros", &_10, 0, &_6, &_11);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_12, &_9, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_13, &_12);
	ZEPHIR_CPY_WRT(&u, &_13);
	ZVAL_LONG(&_6, n);
	ZEPHIR_CALL_CE_STATIC(&_14, tensor_matrix_ce, "identity", &_5, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_15, &_14, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_16, &_15);
	ZEPHIR_CPY_WRT(&p, &_16);
	_19 = (n - 1);
	_18 = 0;
	_17 = 0;
	if (_18 <= _19) {
		while (1) {
			if (_17) {
				_18++;
				if (!(_18 <= _19)) {
					break;
				}
			} else {
				_17 = 1;
			}
			i = _18;
			zephir_array_fetch_long(&_20$$4, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 72);
			ZEPHIR_OBS_NVAR(&_21$$4);
			zephir_array_fetch_long(&_21$$4, &_20$$4, i, PH_NOISY, "tensor/decompositions/lu.zep", 72);
			max = zephir_get_doubleval(&_21$$4);
			row = i;
			_24$$4 = (n - 1);
			_23$$4 = i;
			_22$$4 = 0;
			if (_23$$4 <= _24$$4) {
				while (1) {
					if (_22$$4) {
						_23$$4++;
						if (!(_23$$4 <= _24$$4)) {
							break;
						}
					} else {
						_22$$4 = 1;
					}
					j = _23$$4;
					zephir_array_fetch_long(&_25$$5, &aHat, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 77);
					ZEPHIR_OBS_NVAR(&valueA);
					zephir_array_fetch_long(&valueA, &_25$$5, i, PH_NOISY, "tensor/decompositions/lu.zep", 77);
					if (ZEPHIR_GT_DOUBLE(&valueA, max)) {
						max = zephir_get_numberval(&valueA);
						row = j;
					}
				}
			}
			if (i != row) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &p, i, PH_NOISY, "tensor/decompositions/lu.zep", 86);
				zephir_array_fetch_long(&_26$$7, &p, row, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 88);
				zephir_array_update_long(&p, i, &_26$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&p, row, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_27, tensor_matrix_ce, "quick", &_28, 0, &p);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_29, &_27, "matmul", NULL, 0, a);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_30, &_29, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_31, &_30);
	ZEPHIR_CPY_WRT(&pa, &_31);
	_34 = (n - 1);
	_33 = 0;
	_32 = 0;
	if (_33 <= _34) {
		while (1) {
			if (_32) {
				_33++;
				if (!(_33 <= _34)) {
					break;
				}
			} else {
				_32 = 1;
			}
			i = _33;
			_37$$8 = i;
			_36$$8 = 0;
			_35$$8 = 0;
			if (_36$$8 <= _37$$8) {
				while (1) {
					if (_35$$8) {
						_36$$8++;
						if (!(_36$$8 <= _37$$8)) {
							break;
						}
					} else {
						_35$$8 = 1;
					}
					j = _36$$8;
					sigma = 0.0;
					_40$$9 = (j - 1);
					_39$$9 = 0;
					_38$$9 = 0;
					if (_39$$9 <= _40$$9) {
						while (1) {
							if (_38$$9) {
								_39$$9++;
								if (!(_39$$9 <= _40$$9)) {
									break;
								}
							} else {
								_38$$9 = 1;
							}
							k = _39$$9;
							zephir_array_fetch_long(&_41$$10, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							zephir_array_fetch_long(&_42$$10, &_41$$10, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							zephir_array_fetch_long(&_43$$10, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							zephir_array_fetch_long(&_44$$10, &_43$$10, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							ZEPHIR_INIT_NVAR(&_45$$10);
							mul_function(&_45$$10, &_42$$10, &_44$$10);
							sigma += zephir_get_numberval(&_45$$10);
						}
					}
					zephir_array_fetch_long(&_46$$9, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
					zephir_array_fetch_long(&_47$$9, &_46$$9, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
					ZEPHIR_INIT_NVAR(&_48$$9);
					ZVAL_DOUBLE(&_48$$9, (zephir_get_numberval(&_47$$9) - sigma));
					zephir_array_update_multi(&u, &_48$$9, SL("ll"), 2, j, i);
				}
			}
			_51$$8 = (n - 1);
			_50$$8 = i;
			_49$$8 = 0;
			if (_50$$8 <= _51$$8) {
				while (1) {
					if (_49$$8) {
						_50$$8++;
						if (!(_50$$8 <= _51$$8)) {
							break;
						}
					} else {
						_49$$8 = 1;
					}
					j = _50$$8;
					sigma = 0.0;
					_54$$11 = (i - 1);
					_53$$11 = 0;
					_52$$11 = 0;
					if (_53$$11 <= _54$$11) {
						while (1) {
							if (_52$$11) {
								_53$$11++;
								if (!(_53$$11 <= _54$$11)) {
									break;
								}
							} else {
								_52$$11 = 1;
							}
							k = _53$$11;
							zephir_array_fetch_long(&_55$$12, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							zephir_array_fetch_long(&_56$$12, &_55$$12, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							zephir_array_fetch_long(&_57$$12, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							zephir_array_fetch_long(&_58$$12, &_57$$12, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							ZEPHIR_INIT_NVAR(&_59$$12);
							mul_function(&_59$$12, &_56$$12, &_58$$12);
							sigma += zephir_get_numberval(&_59$$12);
						}
					}
					zephir_array_fetch_long(&_60$$11, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 113);
					zephir_array_fetch_long(&_61$$11, &_60$$11, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 113);
					ZEPHIR_INIT_NVAR(&_62$$11);
					zephir_array_fetch_long(&_63$$11, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 114);
					zephir_array_fetch_long(&_64$$11, &_63$$11, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 114);
					if (!(zephir_is_true(&_64$$11))) {
						ZEPHIR_INIT_NVAR(&_62$$11);
						ZVAL_DOUBLE(&_62$$11, 0.00000001);
					} else {
						zephir_array_fetch_long(&_65$$14, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 114);
						ZEPHIR_OBS_NVAR(&_62$$11);
						zephir_array_fetch_long(&_62$$11, &_65$$14, i, PH_NOISY, "tensor/decompositions/lu.zep", 114);
					}
					ZEPHIR_INIT_NVAR(&_66$$11);
					ZVAL_DOUBLE(&_66$$11, zephir_safe_div_double_zval((zephir_get_numberval(&_61$$11) - sigma), &_62$$11));
					zephir_array_update_multi(&l, &_66$$11, SL("ll"), 2, j, i);
				}
			}
		}
	}
	object_init_ex(return_value, tensor_decompositions_lu_ce);
	ZEPHIR_CALL_CE_STATIC(&_67, tensor_matrix_ce, "quick", &_28, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_68, tensor_matrix_ce, "quick", &_28, 0, &u);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_69, tensor_matrix_ce, "quick", &_28, 0, &p);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 24, &_67, &_68, &_69);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix l
 * @param \Tensor\Matrix u
 * @param \Tensor\Matrix p
 */
PHP_METHOD(Tensor_Decompositions_Lu, __construct) {

	zval *l, l_sub, *u, u_sub, *p, p_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&l_sub);
	ZVAL_UNDEF(&u_sub);
	ZVAL_UNDEF(&p_sub);

	zephir_fetch_params_without_memory_grow(3, 0, &l, &u, &p);



	zephir_update_property_zval(this_ptr, SL("l"), l);
	zephir_update_property_zval(this_ptr, SL("u"), u);
	zephir_update_property_zval(this_ptr, SL("p"), p);

}

/**
 * Return the lower triangular matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Lu, l) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "l");

}

/**
 * Return the upper triangular matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Lu, u) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "u");

}

/**
 * Return the permutation matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Lu, p) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "p");

}

