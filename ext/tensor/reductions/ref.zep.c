
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
#include "kernel/array.h"
#include "kernel/object.h"
#include "kernel/exception.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/concat.h"
#include "include/linear_algebra.h"


/**
 * REF
 *
 * The row echelon form (REF) of a matrix.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Reductions_Ref) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Reductions, Ref, tensor, reductions_ref, tensor_reductions_ref_method_entry, 0);

	/**
	 * The reduced matrix in row echelon form.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_reductions_ref_ce, SL("a"), ZEND_ACC_PROTECTED);

	/**
	 * The number of swaps made to compute the row echelon form of the matrix.
	 *
	 * @var int
	 */
	zend_declare_property_null(tensor_reductions_ref_ce, SL("swaps"), ZEND_ACC_PROTECTED);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Reductions_Ref, reduce) {

	zval ref, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a = NULL, a_sub, _0, _1, _3, _4, _5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&ref);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_INIT_VAR(&ref);
	array_init(&ref);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_ref(&_0, &_1);
	zephir_get_arrval(&_2, &_0);
	ZEPHIR_CPY_WRT(&ref, &_2);
	object_init_ex(return_value, tensor_reductions_ref_ce);
	ZEPHIR_INIT_VAR(&_3);
	object_init_ex(&_3, tensor_matrix_ce);
	zephir_array_fetch_long(&_4, &ref, 0, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 43);
	ZEPHIR_CALL_METHOD(NULL, &_3, "__construct", NULL, 27, &_4);
	zephir_check_call_status();
	zephir_array_fetch_long(&_5, &ref, 1, PH_NOISY | PH_READONLY, "tensor/reductions/ref.zep", 43);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 33, &_3, &_5);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix a
 * @param int swaps
 * @throws \InvalidArgumentException
 */
PHP_METHOD(Tensor_Reductions_Ref, __construct) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long swaps, ZEPHIR_LAST_CALL_STATUS;
	zval *a = NULL, a_sub, *swaps_param = NULL, _0$$3, _1$$3, _2$$3, _3$$3, _4;
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


	if (UNEXPECTED(swaps < 0)) {
		ZEPHIR_INIT_VAR(&_0$$3);
		object_init_ex(&_0$$3, spl_ce_InvalidArgumentException);
		ZVAL_LONG(&_1$$3, swaps);
		ZEPHIR_CALL_FUNCTION(&_2$$3, "strval", NULL, 2, &_1$$3);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "The number of swaps must", " be greater than or equal to 0, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_0$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_0$$3, "tensor/reductions/ref.zep", 56);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_zval(this_ptr, ZEND_STRL("a"), a);
	ZEPHIR_INIT_ZVAL_NREF(_4);
	ZVAL_LONG(&_4, swaps);
	zephir_update_property_zval(this_ptr, ZEND_STRL("swaps"), &_4);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the reduced matrix in row echelon form.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Reductions_Ref, a) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "a");

}

/**
 * Return the number of swaps made to reduce the matrix to ref.
 *
 * @return int
 */
PHP_METHOD(Tensor_Reductions_Ref, swaps) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "swaps");

}

