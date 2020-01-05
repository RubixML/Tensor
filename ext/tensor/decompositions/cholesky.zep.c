
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
#include "kernel/concat.h"
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

	zend_class_implements(tensor_decompositions_cholesky_ce, 1, tensor_decompositions_decomposition_ce);
	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Cholesky, decompose) {

	zval _2$$3;
	zend_bool _5, _8$$4, _11$$5;
	double sigma = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL, *_28 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS, i = 0, j = 0, k = 0, _6, _7, _9$$4, _10$$4, _12$$5, _13$$5;
	zval *a, a_sub, _0, m, aHat, l, _3, _27, _1$$3, _19$$5, _20$$5, _21$$5, _22$$5, _23$$5, _24$$5, _25$$5, _26$$5, _14$$6, _15$$6, _16$$6, _17$$6, _18$$6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&m);
	ZVAL_UNDEF(&aHat);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_27);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_19$$5);
	ZVAL_UNDEF(&_20$$5);
	ZVAL_UNDEF(&_21$$5);
	ZVAL_UNDEF(&_22$$5);
	ZVAL_UNDEF(&_23$$5);
	ZVAL_UNDEF(&_24$$5);
	ZVAL_UNDEF(&_25$$5);
	ZVAL_UNDEF(&_26$$5);
	ZVAL_UNDEF(&_14$$6);
	ZVAL_UNDEF(&_15$$6);
	ZVAL_UNDEF(&_16$$6);
	ZVAL_UNDEF(&_17$$6);
	ZVAL_UNDEF(&_18$$6);
	ZVAL_UNDEF(&_2$$3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, spl_ce_RuntimeException);
		ZEPHIR_INIT_VAR(&_2$$3);
		ZEPHIR_CONCAT_SS(&_2$$3, "Cannot Cholesky decompose a", " non square matrix.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 21, &_2$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/decompositions/cholesky.zep", 35);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_CALL_METHOD(&m, a, "m", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&aHat, a, "asarray", NULL, 0);
	zephir_check_call_status();
	ZEPHIR_CALL_CE_STATIC(&_3, tensor_matrix_ce, "zeros", &_4, 0, &m, &m);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&l, &_3, "asarray", NULL, 0);
	zephir_check_call_status();
	_7 = (zephir_get_numberval(&m) - 1);
	_6 = 0;
	_5 = 0;
	if (_6 <= _7) {
		while (1) {
			if (_5) {
				_6++;
				if (!(_6 <= _7)) {
					break;
				}
			} else {
				_5 = 1;
			}
			i = _6;
			_10$$4 = i;
			_9$$4 = 0;
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
					j = _9$$4;
					sigma = 0.0;
					_13$$5 = (j - 1);
					_12$$5 = 0;
					_11$$5 = 0;
					if (_12$$5 <= _13$$5) {
						while (1) {
							if (_11$$5) {
								_12$$5++;
								if (!(_12$$5 <= _13$$5)) {
									break;
								}
							} else {
								_11$$5 = 1;
							}
							k = _12$$5;
							zephir_array_fetch_long(&_14$$6, &l, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 52);
							zephir_array_fetch_long(&_15$$6, &_14$$6, k, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 52);
							zephir_array_fetch_long(&_16$$6, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 52);
							zephir_array_fetch_long(&_17$$6, &_16$$6, k, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 52);
							ZEPHIR_INIT_NVAR(&_18$$6);
							mul_function(&_18$$6, &_15$$6, &_17$$6);
							sigma += zephir_get_numberval(&_18$$6);
						}
					}
					ZEPHIR_INIT_NVAR(&_19$$5);
					if (i == j) {
						zephir_array_fetch_long(&_20$$5, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 56);
						zephir_array_fetch_long(&_21$$5, &_20$$5, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 56);
						ZVAL_DOUBLE(&_22$$5, (zephir_get_numberval(&_21$$5) - sigma));
						ZEPHIR_INIT_NVAR(&_19$$5);
						ZVAL_DOUBLE(&_19$$5, sqrt((zephir_get_numberval(&_21$$5) - sigma)));
					} else {
						zephir_array_fetch_long(&_23$$5, &l, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 57);
						zephir_array_fetch_long(&_24$$5, &_23$$5, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 57);
						zephir_array_fetch_long(&_25$$5, &aHat, i, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 57);
						zephir_array_fetch_long(&_26$$5, &_25$$5, j, PH_NOISY | PH_READONLY, "tensor/decompositions/cholesky.zep", 57);
						ZEPHIR_INIT_NVAR(&_19$$5);
						ZVAL_DOUBLE(&_19$$5, (zephir_safe_div_long_zval(1, &_24$$5) * (zephir_get_numberval(&_26$$5) - sigma)));
					}
					zephir_array_update_multi(&l, &_19$$5, SL("ll"), 2, i, j);
				}
			}
		}
	}
	ZEPHIR_CALL_CE_STATIC(&_27, tensor_matrix_ce, "quick", &_28, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(&l, &_27);
	object_init_ex(return_value, tensor_decompositions_cholesky_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 25, &l);
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

