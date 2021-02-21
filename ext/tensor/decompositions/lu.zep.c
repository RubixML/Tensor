
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "include/linear_algebra.h"


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

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Lu, decompose) {

	zval lup, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_3 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a = NULL, a_sub, _0, result, _1, l, _4, u, _5, p, _6;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&l);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&u);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&p);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&lup);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_invalidargumentexception_ce, "Cannot decompose a non-square matrix.", "tensor/decompositions/lu.zep", 49);
		return;
	}
	ZEPHIR_INIT_VAR(&result);
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_lu(&result, &_1);
	if (Z_TYPE_P(&result) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_runtimeexception_ce, "Failed to decompose matrix.", "tensor/decompositions/lu.zep", 55);
		return;
	}
	ZEPHIR_INIT_VAR(&lup);
	array_init(&lup);
	zephir_get_arrval(&_2, &result);
	ZEPHIR_CPY_WRT(&lup, &_2);
	zephir_array_fetch_long(&_4, &lup, 0, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 62);
	ZEPHIR_CALL_CE_STATIC(&l, tensor_matrix_ce, "quick", &_3, 0, &_4);
	zephir_check_call_status();
	zephir_array_fetch_long(&_5, &lup, 1, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 63);
	ZEPHIR_CALL_CE_STATIC(&u, tensor_matrix_ce, "quick", &_3, 0, &_5);
	zephir_check_call_status();
	zephir_array_fetch_long(&_6, &lup, 2, PH_NOISY | PH_READONLY, "tensor/decompositions/lu.zep", 64);
	ZEPHIR_CALL_CE_STATIC(&p, tensor_matrix_ce, "quick", &_3, 0, &_6);
	zephir_check_call_status();
	object_init_ex(return_value, tensor_decompositions_lu_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 26, &l, &u, &p);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix l
 * @param \Tensor\Matrix u
 * @param \Tensor\Matrix p
 */
PHP_METHOD(Tensor_Decompositions_Lu, __construct) {

	zval *l = NULL, l_sub, *u = NULL, u_sub, *p = NULL, p_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&l_sub);
	ZVAL_UNDEF(&u_sub);
	ZVAL_UNDEF(&p_sub);

	zephir_fetch_params_without_memory_grow(3, 0, &l, &u, &p);



	zephir_update_property_zval(this_ptr, ZEND_STRL("l"), l);
	zephir_update_property_zval(this_ptr, ZEND_STRL("u"), u);
	zephir_update_property_zval(this_ptr, ZEND_STRL("p"), p);

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

