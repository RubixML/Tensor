
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
#include "include/linear_algebra.h"


/**
 * SVD
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Decompositions_Svd) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Decompositions, Svd, tensor, decompositions_svd, tensor_decompositions_svd_method_entry, 0);

	/**
	 * The U matrix.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_svd_ce, SL("u"), ZEND_ACC_PROTECTED);

	/**
	 * The singular values of the matrix A.
	 *
	 * @var (int|float)[]
	 */
	zend_declare_property_null(tensor_decompositions_svd_ce, SL("singularValues"), ZEND_ACC_PROTECTED);

	/**
	 * The V transposed matrix.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_svd_ce, SL("vT"), ZEND_ACC_PROTECTED);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Svd, decompose) {

	zval usvT, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *a = NULL, a_sub, _0, _1, _3, _5, _6, _7, _8;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_7);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&usvT);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &a);



	ZEPHIR_INIT_VAR(&usvT);
	array_init(&usvT);
	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_svd(&_0, &_1);
	zephir_get_arrval(&_2, &_0);
	ZEPHIR_CPY_WRT(&usvT, &_2);
	object_init_ex(return_value, tensor_decompositions_svd_ce);
	zephir_array_fetch_long(&_5, &usvT, 0, PH_NOISY | PH_READONLY, "tensor/decompositions/svd.zep", 48);
	ZEPHIR_CALL_CE_STATIC(&_3, tensor_matrix_ce, "quick", &_4, 0, &_5);
	zephir_check_call_status();
	zephir_array_fetch_long(&_6, &usvT, 1, PH_NOISY | PH_READONLY, "tensor/decompositions/svd.zep", 49);
	zephir_array_fetch_long(&_8, &usvT, 2, PH_NOISY | PH_READONLY, "tensor/decompositions/svd.zep", 50);
	ZEPHIR_CALL_CE_STATIC(&_7, tensor_matrix_ce, "quick", &_4, 0, &_8);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 27, &_3, &_6, &_7);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param \Tensor\Matrix u
 * @param list<int|float> singularValues
 * @param \Tensor\Matrix vT
 */
PHP_METHOD(Tensor_Decompositions_Svd, __construct) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval singularValues;
	zval *u = NULL, u_sub, *singularValues_param = NULL, *vT = NULL, vT_sub;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&u_sub);
	ZVAL_UNDEF(&vT_sub);
	ZVAL_UNDEF(&singularValues);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 3, 0, &u, &singularValues_param, &vT);

	zephir_get_arrval(&singularValues, singularValues_param);


	zephir_update_property_zval(this_ptr, ZEND_STRL("u"), u);
	zephir_update_property_zval(this_ptr, ZEND_STRL("singularValues"), &singularValues);
	zephir_update_property_zval(this_ptr, ZEND_STRL("vT"), vT);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the U matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Svd, u) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "u");

}

/**
 * Return the singular values of matrix A.
 *
 * @return list<float>
 */
PHP_METHOD(Tensor_Decompositions_Svd, singularValues) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "singularValues");

}

/**
 * Return the singular value matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Svd, s) {

	zval _1;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zephir_fcall_cache_entry *_0 = NULL;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_1, this_ptr, ZEND_STRL("singularValues"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_CE_STATIC(tensor_matrix_ce, "diagonal", &_0, 0, &_1);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the V matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Svd, v) {

	zval _0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&_0);

	ZEPHIR_MM_GROW();

	zephir_read_property(&_0, this_ptr, ZEND_STRL("vT"), PH_NOISY_CC | PH_READONLY);
	ZEPHIR_RETURN_CALL_METHOD(&_0, "transpose", NULL, 0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Return the V transposed matrix.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Svd, vT) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "vT");

}

