
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

	zend_bool _6, _19, _10$$4, _22$$8, _36$$8, _25$$9, _39$$11;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_2 = NULL, *_4 = NULL, *_18 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, row = 0, _7, _8, _20, _21, _11$$4, _12$$4, _23$$8, _24$$8, _37$$8, _38$$8, _26$$9, _27$$9, _40$$11, _41$$11;
	zval *a, a_sub, _0, max, temp, n, l, _1, u, _3, p, _5, _17, pa, _9$$4, _13$$5, _14$$5, _15$$6, _16$$7, _33$$9, _34$$9, _35$$9, _28$$10, _29$$10, _30$$10, _31$$10, _32$$10, _47$$11, _48$$11, _49$$11, _50$$11, _51$$11, _53$$11, _42$$12, _43$$12, _44$$12, _45$$12, _46$$12, _52$$14;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&max);
	ZVAL_UNDEF(&temp);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_17);
	ZVAL_UNDEF(&pa);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&_14$$5);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$7);
	ZVAL_UNDEF(&_33$$9);
	ZVAL_UNDEF(&_34$$9);
	ZVAL_UNDEF(&_35$$9);
	ZVAL_UNDEF(&_28$$10);
	ZVAL_UNDEF(&_29$$10);
	ZVAL_UNDEF(&_30$$10);
	ZVAL_UNDEF(&_31$$10);
	ZVAL_UNDEF(&_32$$10);
	ZVAL_UNDEF(&_47$$11);
	ZVAL_UNDEF(&_48$$11);
	ZVAL_UNDEF(&_49$$11);
	ZVAL_UNDEF(&_50$$11);
	ZVAL_UNDEF(&_51$$11);
	ZVAL_UNDEF(&_53$$11);
	ZVAL_UNDEF(&_42$$12);
	ZVAL_UNDEF(&_43$$12);
	ZVAL_UNDEF(&_44$$12);
	ZVAL_UNDEF(&_45$$12);
	ZVAL_UNDEF(&_46$$12);
	ZVAL_UNDEF(&_52$$14);

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
			zephir_array_fetch_long(&_9$$4, a, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 64);
			ZEPHIR_OBS_NVAR(&max);
			zephir_array_fetch_long(&max, &_9$$4, i, PH_NOISY, "tensor/decompositions/lu.zep", 64);
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
					zephir_array_fetch_long(&_13$$5, a, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 69);
					zephir_array_fetch_long(&_14$$5, &_13$$5, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 69);
					if (ZEPHIR_GT(&_14$$5, &max)) {
						zephir_array_fetch_long(&_15$$6, a, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 70);
						ZEPHIR_OBS_NVAR(&max);
						zephir_array_fetch_long(&max, &_15$$6, i, PH_NOISY, "tensor/decompositions/lu.zep", 70);
						row = j;
					}
				}
			}
			if (i != row) {
				ZEPHIR_OBS_NVAR(&temp);
				zephir_array_fetch_long(&temp, &p, i, PH_NOISY, "tensor/decompositions/lu.zep", 77);
				zephir_array_fetch_long(&_16$$7, &p, row, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 79);
				zephir_array_update_long(&p, i, &_16$$7, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				zephir_array_update_long(&p, row, &temp, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_17, tensor_matrix_ce, "quick", &_18, 0, &p);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&p, &_17);
	ZEPHIR_CALL_METHOD(&pa, &p, "matmul", NULL, 0, a);
	zephir_check_call_status();
	_21 = (zephir_get_numberval(&n) - 1);
	_20 = 0;
	_19 = 0;
	if (_20 <= _21) {
		while (1) {
			if (_19) {
				_20++;
				if (!(_20 <= _21)) {
					break;
				}
			} else {
				_19 = 1;
			}
			i = _20;
			_24$$8 = i;
			_23$$8 = 0;
			_22$$8 = 0;
			if (_23$$8 <= _24$$8) {
				while (1) {
					if (_22$$8) {
						_23$$8++;
						if (!(_23$$8 <= _24$$8)) {
							break;
						}
					} else {
						_22$$8 = 1;
					}
					j = _23$$8;
					sigma = 0.0;
					_27$$9 = (j - 1);
					_26$$9 = 0;
					_25$$9 = 0;
					if (_26$$9 <= _27$$9) {
						while (1) {
							if (_25$$9) {
								_26$$9++;
								if (!(_26$$9 <= _27$$9)) {
									break;
								}
							} else {
								_25$$9 = 1;
							}
							k = _26$$9;
							zephir_array_fetch_long(&_28$$10, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 93);
							zephir_array_fetch_long(&_29$$10, &_28$$10, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 93);
							zephir_array_fetch_long(&_30$$10, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 93);
							zephir_array_fetch_long(&_31$$10, &_30$$10, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 93);
							ZEPHIR_INIT_NVAR(&_32$$10);
							mul_function(&_32$$10, &_29$$10, &_31$$10);
							sigma += zephir_get_numberval(&_32$$10);
						}
					}
					zephir_array_fetch_long(&_33$$9, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 96);
					ZEPHIR_OBS_NVAR(&_34$$9);
					zephir_array_fetch_long(&_34$$9, &_33$$9, i, PH_NOISY, "tensor/decompositions/lu.zep", 96);
					ZEPHIR_INIT_NVAR(&_35$$9);
					ZVAL_DOUBLE(&_35$$9, (double) (zephir_get_doubleval(&_34$$9) - sigma));
					zephir_array_update_multi(&u, &_35$$9, SL("ll"), 2, j, i);
				}
			}
			_38$$8 = (zephir_get_numberval(&n) - 1);
			_37$$8 = i;
			_36$$8 = 0;
			if (_37$$8 <= _38$$8) {
				while (1) {
					if (_36$$8) {
						_37$$8++;
						if (!(_37$$8 <= _38$$8)) {
							break;
						}
					} else {
						_36$$8 = 1;
					}
					j = _37$$8;
					sigma = 0.0;
					_41$$11 = (i - 1);
					_40$$11 = 0;
					_39$$11 = 0;
					if (_40$$11 <= _41$$11) {
						while (1) {
							if (_39$$11) {
								_40$$11++;
								if (!(_40$$11 <= _41$$11)) {
									break;
								}
							} else {
								_39$$11 = 1;
							}
							k = _40$$11;
							zephir_array_fetch_long(&_42$$12, &u, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
							zephir_array_fetch_long(&_43$$12, &_42$$12, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
							zephir_array_fetch_long(&_44$$12, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
							zephir_array_fetch_long(&_45$$12, &_44$$12, k, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 103);
							ZEPHIR_INIT_NVAR(&_46$$12);
							mul_function(&_46$$12, &_43$$12, &_45$$12);
							sigma += zephir_get_numberval(&_46$$12);
						}
					}
					zephir_array_fetch_long(&_47$$11, &pa, j, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 106);
					ZEPHIR_OBS_NVAR(&_48$$11);
					zephir_array_fetch_long(&_48$$11, &_47$$11, i, PH_NOISY, "tensor/decompositions/lu.zep", 106);
					ZEPHIR_INIT_NVAR(&_49$$11);
					zephir_array_fetch_long(&_50$$11, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 107);
					zephir_array_fetch_long(&_51$$11, &_50$$11, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 107);
					if (!(zephir_is_true(&_51$$11))) {
						ZEPHIR_INIT_NVAR(&_49$$11);
						ZVAL_DOUBLE(&_49$$11, 0.00000001);
					} else {
						zephir_array_fetch_long(&_52$$14, &u, i, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 107);
						ZEPHIR_OBS_NVAR(&_49$$11);
						zephir_array_fetch_long(&_49$$11, &_52$$14, i, PH_NOISY, "tensor/decompositions/lu.zep", 107);
					}
					ZEPHIR_INIT_NVAR(&_53$$11);
					ZVAL_DOUBLE(&_53$$11, zephir_safe_div_double_zval((double) (zephir_get_doubleval(&_48$$11) - sigma), &_49$$11));
					zephir_array_update_multi(&l, &_53$$11, SL("ll"), 2, j, i);
				}
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_17, tensor_matrix_ce, "quick", &_18, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&l, &_17);
	ZEPHIR_CALL_CE_STATIC(&_17, tensor_matrix_ce, "quick", &_18, 0, &u);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&u, &_17);
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

