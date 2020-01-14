
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

	zend_class_implements(tensor_decompositions_lu_ce, 1, tensor_decompositions_decomposition_ce);
	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Lu, decompose) {

	zend_bool _14, _28, _18$$4, _31$$8, _45$$8, _34$$9, _48$$11;
	zval aHat, l, u, p, pa, _2, _6, _10, _13, _27;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_8 = NULL, *_24 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, row = 0, _15, _16, _29, _30, _19$$4, _20$$4, _32$$8, _33$$8, _46$$8, _47$$8, _35$$9, _36$$9, _49$$11, _50$$11;
	zval *a, a_sub, _0, sigma, max, temp, valueA, n, _1, _3, _5, _7, _9, _11, _12, _23, _25, _26, _63, _64, _65, _17$$4, _21$$5, _22$$7, _42$$9, _43$$9, _44$$9, _37$$10, _38$$10, _39$$10, _40$$10, _41$$10, _56$$11, _57$$11, _58$$11, _59$$11, _60$$11, _62$$11, _51$$12, _52$$12, _53$$12, _54$$12, _55$$12, _61$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&sigma);
	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_9);
	ZVAL_UNDEF(&_11);
	ZVAL_UNDEF(&_12);
	ZVAL_UNDEF(&_23);
	ZVAL_UNDEF(&_25);
	ZVAL_UNDEF(&_26);
	ZVAL_UNDEF(&_63);
	ZVAL_UNDEF(&_64);
	ZVAL_UNDEF(&_65);
	ZVAL_UNDEF(&_17$$4);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$7);
	ZVAL_UNDEF(&_42$$9);
	ZVAL_UNDEF(&_43$$9);
	ZVAL_UNDEF(&_44$$9);
	ZVAL_UNDEF(&_37$$10);
	ZVAL_UNDEF(&_38$$10);
	ZVAL_UNDEF(&_39$$10);
	ZVAL_UNDEF(&_40$$10);
	ZVAL_UNDEF(&_41$$10);
	ZVAL_UNDEF(&_56$$11);
	ZVAL_UNDEF(&_57$$11);
	ZVAL_UNDEF(&_58$$11);
	ZVAL_UNDEF(&_59$$11);
	ZVAL_UNDEF(&_60$$11);
	ZVAL_UNDEF(&_62$$11);
	ZVAL_UNDEF(&_51$$12);
	ZVAL_UNDEF(&_52$$12);
	ZVAL_UNDEF(&_53$$12);
	ZVAL_UNDEF(&_54$$12);
	ZVAL_UNDEF(&_55$$12);
	ZVAL_UNDEF(&_61$$14);
	ZVAL_UNDEF(&aHat);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&pa);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_10);
	ZVAL_UNDEF(&_13);
	ZVAL_UNDEF(&_27);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
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
	ZEPHIR_CALL_METHOD(&n, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_2, &_1);
	ZEPHIR_CPY_WRT(&aHat, &_2);
	ZEPHIR_CALL_CE_STATIC(&_3, tensor_matrix_ce, "identity", &_4, 0, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_6, &_5);
	ZEPHIR_CPY_WRT(&l, &_6);
	ZEPHIR_CALL_CE_STATIC(&_7, tensor_matrix_ce, "zeros", &_8, 0, &n, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_9, &_7, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_10, &_9);
	ZEPHIR_CPY_WRT(&u, &_10);
	ZEPHIR_CALL_CE_STATIC(&_11, tensor_matrix_ce, "identity", &_4, 0, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_12, &_11, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_13, &_12);
	ZEPHIR_CPY_WRT(&p, &_13);
	_16 = (zephir_get_numberval(&n) - 1);
	_15 = 0;
	_14 = 0;
	if (_15 <= _16) {
		while (1) {
			if (_14) {
				_15++;
				if (!(_15 <= _16)) {
					break;
				}
			} else {
				_14 = 1;
			}
			i = _15;
			zephir_array_fetch_long(&_17$$4, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 72);
			ZEPHIR_OBS_NVAR(&max);
			zephir_array_fetch_long(&max, &_17$$4, i, PH_NOISY, "tensor/decompositions/lu.zep", 72);
			row = i;
			_20$$4 = (zephir_get_numberval(&n) - 1);
			_19$$4 = i;
			_18$$4 = 0;
			if (_19$$4 <= _20$$4) {
				while (1) {
					if (_18$$4) {
						_19$$4++;
						if (!(_19$$4 <= _20$$4)) {
							break;
						}
					} else {
						_18$$4 = 1;
					}
					j = _19$$4;
					zephir_array_fetch_long(&_21$$5, &aHat, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 77);
					ZEPHIR_OBS_NVAR(&valueA);
					zephir_array_fetch_long(&valueA, &_21$$5, i, PH_NOISY, "tensor/decompositions/lu.zep", 77);
					if (ZEPHIR_GT(&valueA, &max)) {
						ZEPHIR_CPY_WRT(&max, &valueA);
						row = j;
					}
				}
			}
			if (i != row) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &p, i, PH_NOISY, "tensor/decompositions/lu.zep", 86);
				zephir_array_fetch_long(&_22$$7, &p, row, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 88);
				zephir_array_update_long(&p, i, &_22$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&p, row, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_23, tensor_matrix_ce, "quick", &_24, 0, &p);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_25, &_23, "matmul", NULL, 0, a);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_26, &_25, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_27, &_26);
	ZEPHIR_CPY_WRT(&pa, &_27);
	_30 = (zephir_get_numberval(&n) - 1);
	_29 = 0;
	_28 = 0;
	if (_29 <= _30) {
		while (1) {
			if (_28) {
				_29++;
				if (!(_29 <= _30)) {
					break;
				}
			} else {
				_28 = 1;
			}
			i = _29;
			_33$$8 = i;
			_32$$8 = 0;
			_31$$8 = 0;
			if (_32$$8 <= _33$$8) {
				while (1) {
					if (_31$$8) {
						_32$$8++;
						if (!(_32$$8 <= _33$$8)) {
							break;
						}
					} else {
						_31$$8 = 1;
					}
					j = _32$$8;
					ZEPHIR_INIT_NVAR(&sigma);
					ZVAL_DOUBLE(&sigma, 0.0);
					_36$$9 = (j - 1);
					_35$$9 = 0;
					_34$$9 = 0;
					if (_35$$9 <= _36$$9) {
						while (1) {
							if (_34$$9) {
								_35$$9++;
								if (!(_35$$9 <= _36$$9)) {
									break;
								}
							} else {
								_34$$9 = 1;
							}
							k = _35$$9;
							zephir_array_fetch_long(&_37$$10, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							zephir_array_fetch_long(&_38$$10, &_37$$10, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							zephir_array_fetch_long(&_39$$10, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							zephir_array_fetch_long(&_40$$10, &_39$$10, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 100);
							ZEPHIR_INIT_NVAR(&_41$$10);
							mul_function(&_41$$10, &_38$$10, &_40$$10);
							ZEPHIR_ADD_ASSIGN(&sigma, &_41$$10);
						}
					}
					zephir_array_fetch_long(&_42$$9, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
					zephir_array_fetch_long(&_43$$9, &_42$$9, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
					ZEPHIR_INIT_NVAR(&_44$$9);
					zephir_sub_function(&_44$$9, &_43$$9, &sigma);
					zephir_array_update_multi(&u, &_44$$9, SL("ll"), 2, j, i);
				}
			}
			_47$$8 = (zephir_get_numberval(&n) - 1);
			_46$$8 = i;
			_45$$8 = 0;
			if (_46$$8 <= _47$$8) {
				while (1) {
					if (_45$$8) {
						_46$$8++;
						if (!(_46$$8 <= _47$$8)) {
							break;
						}
					} else {
						_45$$8 = 1;
					}
					j = _46$$8;
					ZEPHIR_INIT_NVAR(&sigma);
					ZVAL_DOUBLE(&sigma, 0.0);
					_50$$11 = (i - 1);
					_49$$11 = 0;
					_48$$11 = 0;
					if (_49$$11 <= _50$$11) {
						while (1) {
							if (_48$$11) {
								_49$$11++;
								if (!(_49$$11 <= _50$$11)) {
									break;
								}
							} else {
								_48$$11 = 1;
							}
							k = _49$$11;
							zephir_array_fetch_long(&_51$$12, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							zephir_array_fetch_long(&_52$$12, &_51$$12, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							zephir_array_fetch_long(&_53$$12, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							zephir_array_fetch_long(&_54$$12, &_53$$12, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
							ZEPHIR_INIT_NVAR(&_55$$12);
							mul_function(&_55$$12, &_52$$12, &_54$$12);
							ZEPHIR_ADD_ASSIGN(&sigma, &_55$$12);
						}
					}
					zephir_array_fetch_long(&_56$$11, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 113);
					zephir_array_fetch_long(&_57$$11, &_56$$11, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 113);
					ZEPHIR_INIT_NVAR(&_58$$11);
					zephir_sub_function(&_58$$11, &_57$$11, &sigma);
					ZEPHIR_INIT_NVAR(&_59$$11);
					zephir_array_fetch_long(&_57$$11, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 114);
					zephir_array_fetch_long(&_60$$11, &_57$$11, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 114);
					if (!(zephir_is_true(&_60$$11))) {
						ZEPHIR_INIT_NVAR(&_59$$11);
						ZVAL_DOUBLE(&_59$$11, 0.00000001);
					} else {
						zephir_array_fetch_long(&_61$$14, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 114);
						ZEPHIR_OBS_NVAR(&_59$$11);
						zephir_array_fetch_long(&_59$$11, &_61$$14, i, PH_NOISY, "tensor/decompositions/lu.zep", 114);
					}
					ZEPHIR_INIT_NVAR(&_62$$11);
					div_function(&_62$$11, &_58$$11, &_59$$11);
					zephir_array_update_multi(&l, &_62$$11, SL("ll"), 2, j, i);
				}
			}
		}
	}
	object_init_ex(return_value, tensor_decompositions_lu_ce);
	ZEPHIR_CALL_CE_STATIC(&_63, tensor_matrix_ce, "quick", &_24, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_64, tensor_matrix_ce, "quick", &_24, 0, &u);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_65, tensor_matrix_ce, "quick", &_24, 0, &p);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 25, &_63, &_64, &_65);
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

