
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
#include "kernel/object.h"
#include "include/linear_algebra.h"


/**
 * Cholesky
 *
 * An efficient decomposition of a square positive definite matrix into a lower triangular matrix and its conjugate transpose.
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

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a = NULL, a_sub, _0, l, _1, _2;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (!(zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_invalidargumentexception_ce, "Cannot decompose a non-square matrix.", "tensor/decompositions/cholesky.zep", 35);
		return;
	}
	ZEPHIR_INIT_VAR(&l);
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_cholesky(&l, &_1);
	if (Z_TYPE_P(&l) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_runtimeexception_ce, "Failed to decompose matrix.", "tensor/decompositions/cholesky.zep", 41);
		return;
	}
	object_init_ex(return_value, tensor_decompositions_cholesky_ce);
	ZEPHIR_CALL_CE_STATIC(&_2, tensor_matrix_ce, "quick", &_3, 0, &l);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 24, &_2);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix l
 */
PHP_METHOD(Tensor_Decompositions_Cholesky, __construct) {

	zval *l = NULL, l_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&l_sub);

	zephir_fetch_params_without_memory_grow(1, 0, &l);



	zephir_update_property_zval(this_ptr, ZEND_STRL("l"), l);

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

	zephir_read_property(&_0, this_ptr, ZEND_STRL("l"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "transpose", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

