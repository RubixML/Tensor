
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

	zend_bool _6, _17, _10$$4, _20$$8, _34$$8, _23$$9, _37$$11;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL, *_16 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, row = 0, _7, _8, _18, _19, _11$$4, _12$$4, _21$$8, _22$$8, _35$$8, _36$$8, _24$$9, _25$$9, _38$$11, _39$$11;
	zval *a, a_sub, _0, max, temp, valueA, n, aHat, l, _1, u, _3, p, _5, _15, pa, _52, _9$$4, _13$$5, _14$$7, _31$$9, _32$$9, _33$$9, _26$$10, _27$$10, _28$$10, _29$$10, _30$$10, _45$$11, _46$$11, _47$$11, _48$$11, _49$$11, _51$$11, _40$$12, _41$$12, _42$$12, _43$$12, _44$$12, _50$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&valueA);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&aHat);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_15);
	ZVAL_UNDEF(&pa);
	ZVAL_UNDEF(&_52);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$7);
	ZVAL_UNDEF(&_31$$9);
	ZVAL_UNDEF(&_32$$9);
	ZVAL_UNDEF(&_33$$9);
	ZVAL_UNDEF(&_26$$10);
	ZVAL_UNDEF(&_27$$10);
	ZVAL_UNDEF(&_28$$10);
	ZVAL_UNDEF(&_29$$10);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_45$$11);
	ZVAL_UNDEF(&_46$$11);
	ZVAL_UNDEF(&_47$$11);
	ZVAL_UNDEF(&_48$$11);
	ZVAL_UNDEF(&_49$$11);
	ZVAL_UNDEF(&_51$$11);
	ZVAL_UNDEF(&_40$$12);
	ZVAL_UNDEF(&_41$$12);
	ZVAL_UNDEF(&_42$$12);
	ZVAL_UNDEF(&_43$$12);
	ZVAL_UNDEF(&_44$$12);
	ZVAL_UNDEF(&_50$$14);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_RuntimeException, "Cannot decompose a non square matrix.", "tensor/decompositions/lu.zep", 50);
		return;
	}
	ZEPHIR_CALL_METHOD(&n, a, "n", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&aHat, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_1, tensor_matrix_ce, "identity", &_2, 0, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&l, &_1, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_3, tensor_matrix_ce, "zeros", &_4, 0, &n, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&u, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_5, tensor_matrix_ce, "identity", &_2, 0, &n);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&p, &_5, "asarray", NULL, 0);
	zephir_check_call_status();
	_8 = (zephir_get_numberval(&n) - 1);
	_7 = 0;
	_6 = 0;
	if (_7 <= _8) {
		while (1) {
			if (_6) {
				_7++;
				if (!(_7 <= _8)) {
					break;
				}
			} else {
				_6 = 1;
			}
			i = _7;
			zephir_array_fetch_long(&_9$$4, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 66);
			ZEPHIR_OBS_NVAR(&max);
			zephir_array_fetch_long(&max, &_9$$4, i, PH_NOISY, "tensor/decompositions/lu.zep", 66);
			row = i;
			_12$$4 = (zephir_get_numberval(&n) - 1);
			_11$$4 = i;
			_10$$4 = 0;
			if (_11$$4 <= _12$$4) {
				while (1) {
					if (_10$$4) {
						_11$$4++;
						if (!(_11$$4 <= _12$$4)) {
							break;
						}
					} else {
						_10$$4 = 1;
					}
					j = _11$$4;
					zephir_array_fetch_long(&_13$$5, &aHat, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 71);
					ZEPHIR_OBS_NVAR(&valueA);
					zephir_array_fetch_long(&valueA, &_13$$5, i, PH_NOISY, "tensor/decompositions/lu.zep", 71);
					if (ZEPHIR_GT(&valueA, &max)) {
						ZEPHIR_CPY_WRT(&max, &valueA);
						row = j;
					}
				}
			}
			if (i != row) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &p, i, PH_NOISY, "tensor/decompositions/lu.zep", 80);
				zephir_array_fetch_long(&_14$$7, &p, row, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 82);
				zephir_array_update_long(&p, i, &_14$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&p, row, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_15, tensor_matrix_ce, "quick", &_16, 0, &p);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&p, &_15);
	ZEPHIR_CALL_METHOD(&_15, &p, "matmul", NULL, 0, a);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&pa, &_15, "asarray", NULL, 0);
	zephir_check_call_status();
	_19 = (zephir_get_numberval(&n) - 1);
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
			_22$$8 = i;
			_21$$8 = 0;
			_20$$8 = 0;
			if (_21$$8 <= _22$$8) {
				while (1) {
					if (_20$$8) {
						_21$$8++;
						if (!(_21$$8 <= _22$$8)) {
							break;
						}
					} else {
						_20$$8 = 1;
					}
					j = _21$$8;
					sigma = 0.0;
					_25$$9 = (j - 1);
					_24$$9 = 0;
					_23$$9 = 0;
					if (_24$$9 <= _25$$9) {
						while (1) {
							if (_23$$9) {
								_24$$9++;
								if (!(_24$$9 <= _25$$9)) {
									break;
								}
							} else {
								_23$$9 = 1;
							}
							k = _24$$9;
							zephir_array_fetch_long(&_26$$10, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 96);
							zephir_array_fetch_long(&_27$$10, &_26$$10, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 96);
							zephir_array_fetch_long(&_28$$10, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 96);
							zephir_array_fetch_long(&_29$$10, &_28$$10, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 96);
							ZEPHIR_INIT_NVAR(&_30$$10);
							mul_function(&_30$$10, &_27$$10, &_29$$10);
							sigma += zephir_get_numberval(&_30$$10);
						}
					}
					zephir_array_fetch_long(&_31$$9, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 99);
					ZEPHIR_OBS_NVAR(&_32$$9);
					zephir_array_fetch_long(&_32$$9, &_31$$9, i, PH_NOISY, "tensor/decompositions/lu.zep", 99);
					ZEPHIR_INIT_NVAR(&_33$$9);
					ZVAL_DOUBLE(&_33$$9, (double) (zephir_get_doubleval(&_32$$9) - sigma));
					zephir_array_update_multi(&u, &_33$$9, SL("ll"), 2, j, i);
				}
			}
			_36$$8 = (zephir_get_numberval(&n) - 1);
			_35$$8 = i;
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
					sigma = 0.0;
					_39$$11 = (i - 1);
					_38$$11 = 0;
					_37$$11 = 0;
					if (_38$$11 <= _39$$11) {
						while (1) {
							if (_37$$11) {
								_38$$11++;
								if (!(_38$$11 <= _39$$11)) {
									break;
								}
							} else {
								_37$$11 = 1;
							}
							k = _38$$11;
							zephir_array_fetch_long(&_40$$12, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 106);
							zephir_array_fetch_long(&_41$$12, &_40$$12, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 106);
							zephir_array_fetch_long(&_42$$12, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 106);
							zephir_array_fetch_long(&_43$$12, &_42$$12, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 106);
							ZEPHIR_INIT_NVAR(&_44$$12);
							mul_function(&_44$$12, &_41$$12, &_43$$12);
							sigma += zephir_get_numberval(&_44$$12);
						}
					}
					zephir_array_fetch_long(&_45$$11, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 109);
					ZEPHIR_OBS_NVAR(&_46$$11);
					zephir_array_fetch_long(&_46$$11, &_45$$11, i, PH_NOISY, "tensor/decompositions/lu.zep", 109);
					ZEPHIR_INIT_NVAR(&_47$$11);
					zephir_array_fetch_long(&_48$$11, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
					zephir_array_fetch_long(&_49$$11, &_48$$11, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
					if (!(zephir_is_true(&_49$$11))) {
						ZEPHIR_INIT_NVAR(&_47$$11);
						ZVAL_DOUBLE(&_47$$11, 0.00000001);
					} else {
						zephir_array_fetch_long(&_50$$14, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 110);
						ZEPHIR_OBS_NVAR(&_47$$11);
						zephir_array_fetch_long(&_47$$11, &_50$$14, i, PH_NOISY, "tensor/decompositions/lu.zep", 110);
					}
					ZEPHIR_INIT_NVAR(&_51$$11);
					ZVAL_DOUBLE(&_51$$11, zephir_safe_div_double_zval((double) (zephir_get_doubleval(&_46$$11) - sigma), &_47$$11));
					zephir_array_update_multi(&l, &_51$$11, SL("ll"), 2, j, i);
				}
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_52, tensor_matrix_ce, "quick", &_16, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&l, &_52);
	ZEPHIR_CALL_CE_STATIC(&_52, tensor_matrix_ce, "quick", &_16, 0, &u);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&u, &_52);
	object_init_ex(return_value, tensor_decompositions_lu_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 25, &l, &u, &p);
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

