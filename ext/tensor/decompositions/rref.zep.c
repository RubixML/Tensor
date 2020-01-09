
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

	zend_bool _3, _12$$3, _7$$5, _16$$8;
	zval b, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_6 = NULL, *_25 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, row, col, _13$$3, _14$$3, _8$$5, _9$$5, _17$$8, _18$$8;
	zval *a, a_sub, t, scale, divisor, m, n, ref, _0, _1, _24, _4$$3, _5$$3, _10$$6, _11$$6, _15$$7, _19$$9, _20$$9, _21$$9, _22$$9, _23$$9;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&t);
	ZVAL_UNDEF(&scale);
	ZVAL_UNDEF(&divisor);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&n);
	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_24);
	ZVAL_UNDEF(&_4$$3);
	ZVAL_UNDEF(&_5$$3);
	ZVAL_UNDEF(&_10$$6);
	ZVAL_UNDEF(&_11$$6);
	ZVAL_UNDEF(&_15$$7);
	ZVAL_UNDEF(&_19$$9);
	ZVAL_UNDEF(&_20$$9);
	ZVAL_UNDEF(&_21$$9);
	ZVAL_UNDEF(&_22$$9);
	ZVAL_UNDEF(&_23$$9);
	ZVAL_UNDEF(&b);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_INIT_VAR(&b);
	array_init(&b);
	ZEPHIR_CALL_METHOD(&m, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&n, a, "n", NULL, 0);
	zephir_check_call_status();
	row = 0;
	col = 0;
	ZEPHIR_CALL_METHOD(&ref, a, "ref", NULL, 0);
	zephir_check_call_status();
	zephir_array_fetch_long(&_0, &ref, 0, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 46);
	ZEPHIR_CALL_METHOD(&_1, &_0, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_2, &_1);
	ZEPHIR_CPY_WRT(&b, &_2);
	while (1) {
		_3 = ZEPHIR_GT_LONG(&m, row);
		if (_3) {
			_3 = ZEPHIR_GT_LONG(&n, col);
		}
		if (!(_3)) {
			break;
		}
		ZEPHIR_OBS_NVAR(&t);
		zephir_array_fetch_long(&t, &b, row, PH_NOISY, "tensor/decompositions/rref.zep", 49);
		zephir_array_fetch_long(&_4$$3, &t, col, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 51);
		ZEPHIR_CALL_FUNCTION(&_5$$3, "abs", &_6, 12, &_4$$3);
		zephir_check_call_status();
		if (ZEPHIR_IS_LONG(&_5$$3, 0)) {
			col++;
			continue;
		}
		ZEPHIR_OBS_NVAR(&divisor);
		zephir_array_fetch_long(&divisor, &t, col, PH_NOISY, "tensor/decompositions/rref.zep", 57);
		if (!ZEPHIR_IS_LONG(&divisor, 1)) {
			_9$$5 = (zephir_get_numberval(&n) - 1);
			_8$$5 = 0;
			_7$$5 = 0;
			if (_8$$5 <= _9$$5) {
				while (1) {
					if (_7$$5) {
						_8$$5++;
						if (!(_8$$5 <= _9$$5)) {
							break;
						}
					} else {
						_7$$5 = 1;
					}
					i = _8$$5;
					zephir_array_fetch_long(&_10$$6, &t, i, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 61);
					ZEPHIR_INIT_NVAR(&_11$$6);
					div_function(&_11$$6, &_10$$6, &divisor);
					zephir_array_update_long(&t, i, &_11$$6, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
				}
			}
		}
		_14$$3 = (row - 1);
		_13$$3 = _14$$3;
		_12$$3 = 0;
		if (_13$$3 >= 0) {
			while (1) {
				if (_12$$3) {
					_13$$3--;
					if (!(_13$$3 >= 0)) {
						break;
					}
				} else {
					_12$$3 = 1;
				}
				i = _13$$3;
				zephir_array_fetch_long(&_15$$7, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 66);
				ZEPHIR_OBS_NVAR(&scale);
				zephir_array_fetch_long(&scale, &_15$$7, col, PH_NOISY, "tensor/decompositions/rref.zep", 66);
				if (!ZEPHIR_IS_LONG(&scale, 0)) {
					_18$$8 = (zephir_get_numberval(&n) - 1);
					_17$$8 = 0;
					_16$$8 = 0;
					if (_17$$8 <= _18$$8) {
						while (1) {
							if (_16$$8) {
								_17$$8++;
								if (!(_17$$8 <= _18$$8)) {
									break;
								}
							} else {
								_16$$8 = 1;
							}
							j = _17$$8;
							zephir_array_fetch_long(&_19$$9, &b, i, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 70);
							zephir_array_fetch_long(&_20$$9, &_19$$9, j, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 70);
							zephir_array_fetch_long(&_21$$9, &t, j, PH_NOISY | PH_READONLY, "tensor/decompositions/rref.zep", 70);
							ZEPHIR_INIT_NVAR(&_22$$9);
							mul_function(&_22$$9, &scale, &_21$$9);
							ZEPHIR_INIT_NVAR(&_23$$9);
							zephir_sub_function(&_23$$9, &_20$$9, &_22$$9);
							zephir_array_update_multi(&b, &_23$$9, SL("ll"), 2, i, j);
						}
					}
				}
			}
		}
		zephir_array_update_long(&b, row, &t, PH_COPY | PH_SEPARATE ZEPHIR_DEBUG_PARAMS_DUMMY);
		row++;
		col++;
	}
	ZEPHIR_CALL_CE_STATIC(&_24, tensor_matrix_ce, "quick", &_25, 0, &b);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&b, &_24);
	object_init_ex(return_value, tensor_decompositions_rref_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 28, &b);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix a
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Decompositions_Rref, __construct) {

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
PHP_METHOD(Tensor_Decompositions_Rref, a) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

