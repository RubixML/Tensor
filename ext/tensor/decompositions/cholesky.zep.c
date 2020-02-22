
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
#include "math.h"
#include "kernel/object.h"


/**
 * Cholesky
 *
 * An efficient decomposition of a square positive definite matrix into a
 * lower triangular matrix and its conjugate transpose.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Decompositions_Cholesky) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Decompositions, Cholesky, tensor, decompositions_cholesky, tensor_decompositions_cholesky_method_entry, 0);

	/**
	 * The lower triangular matrix.
	 * 
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_cholesky_ce, SL("l"), ZEND_ACC_PROTECTED);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @throws \InvalidArgumentExeption
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Cholesky, decompose) {

	zend_bool _7, _10$$4, _13$$5;
	zval aHat, l, _2, _6;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_30 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, _8, _9, _11$$4, _12$$4, _14$$5, _15$$5;
	zval *a, a_sub, _0, m, _1, _3, _5, _29, _21$$5, _22$$5, _23$$5, _24$$5, _25$$5, _26$$5, _27$$5, _28$$5, _16$$6, _17$$6, _18$$6, _19$$6, _20$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_29);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_23$$5);
	ZVAL_UNDEF(&_24$$5);
	ZVAL_UNDEF(&_25$$5);
	ZVAL_UNDEF(&_26$$5);
	ZVAL_UNDEF(&_27$$5);
	ZVAL_UNDEF(&_28$$5);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_19$$6);
	ZVAL_UNDEF(&_20$$6);
	ZVAL_UNDEF(&aHat);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_6);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_InvalidArgumentException, "Cannot decompose a non-square matrix.", "tensor/decompositions/cholesky.zep", 35);
		return;
	}
	ZEPHIR_INIT_VAR(&aHat);
	array_init(&aHat);
	ZEPHIR_INIT_VAR(&l);
	array_init(&l);
	ZEPHIR_CALL_METHOD(&m, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_2, &_1);
	ZEPHIR_CPY_WRT(&aHat, &_2);
	ZEPHIR_CALL_CE_STATIC(&_3, tensor_matrix_ce, "zeros", &_4, 0, &m, &m);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&_5, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	zephir_get_arrval(&_6, &_5);
	ZEPHIR_CPY_WRT(&l, &_6);
	_9 = (zephir_get_numberval(&m) - 1);
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
			i = _8;
			_12$$4 = i;
			_11$$4 = 0;
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
					sigma = 0.0;
					_15$$5 = (j - 1);
					_14$$5 = 0;
					_13$$5 = 0;
					if (_14$$5 <= _15$$5) {
						while (1) {
							if (_13$$5) {
								_14$$5++;
								if (!(_14$$5 <= _15$$5)) {
									break;
								}
							} else {
								_13$$5 = 1;
							}
							k = _14$$5;
							zephir_array_fetch_long(&_16$$6, &l, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 54);
							zephir_array_fetch_long(&_17$$6, &_16$$6, k, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 54);
							zephir_array_fetch_long(&_18$$6, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 54);
							zephir_array_fetch_long(&_19$$6, &_18$$6, k, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 54);
							ZEPHIR_INIT_NVAR(&_20$$6);
							mul_function(&_20$$6, &_17$$6, &_19$$6);
							sigma += zephir_get_numberval(&_20$$6);
						}
					}
					ZEPHIR_INIT_NVAR(&_21$$5);
					if (i == j) {
						zephir_array_fetch_long(&_22$$5, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 58);
						zephir_array_fetch_long(&_23$$5, &_22$$5, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 58);
						ZVAL_DOUBLE(&_24$$5, (zephir_get_numberval(&_23$$5) - sigma));
						ZEPHIR_INIT_NVAR(&_21$$5);
						ZVAL_DOUBLE(&_21$$5, sqrt((zephir_get_numberval(&_23$$5) - sigma)));
					} else {
						zephir_array_fetch_long(&_25$$5, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 59);
						zephir_array_fetch_long(&_26$$5, &_25$$5, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 59);
						zephir_array_fetch_long(&_27$$5, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 59);
						zephir_array_fetch_long(&_28$$5, &_27$$5, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 59);
						ZEPHIR_INIT_NVAR(&_21$$5);
						ZVAL_DOUBLE(&_21$$5, (zephir_safe_div_long_zval(1, &_26$$5) * (zephir_get_numberval(&_28$$5) - sigma)));
					}
					zephir_array_update_multi(&l, &_21$$5, SL("ll"), 2, i, j);
				}
			}
		}
	}
	object_init_ex(return_value, tensor_decompositions_cholesky_ce);
	ZEPHIR_CALL_CE_STATIC(&_29, tensor_matrix_ce, "quick", &_30, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 23, &_29);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix l
 */
PHP_METHOD(Tensor_Decompositions_Cholesky, __construct) {

	zval *l, l_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&l_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &l);



	zephir_update_property_zval(this_ptr, SL("l"), l);

}

/**
 * Return the lower triangular matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Cholesky, l) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "l");

}

/**
 * Return the conjugate transpose of the lower triangular matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Cholesky, lT) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, SL("l"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "transpose", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

