
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
 * Eigen
 *
 * The Eigendecompositon or (Spectral decomposition) is a matrix factorization resulting in a
 * matrix of eigenvectors and a corresponding array of eigenvalues.
 *
 * @category    Scientific Computing
 * @package     Rubix/Tensor
 * @author      Andrew DalPino
 */
ZEPHIR_INIT_CLASS(Tensor_Decompositions_Eigen) {

	ZEPHIR_REGISTER_CLASS(Tensor\\Decompositions, Eigen, tensor, decompositions_eigen, tensor_decompositions_eigen_method_entry, 0);

	/**
	 * The computed eigenvalues.
	 *
	 * @var (int|float)[]
	 */
	zend_declare_property_null(tensor_decompositions_eigen_ce, SL("eigenvalues"), ZEND_ACC_PROTECTED);

	/**
	 * The eigenvectors of the eigendecomposition.
	 *
	 * @var \Tensor\Matrix
	 */
	zend_declare_property_null(tensor_decompositions_eigen_ce, SL("eigenvectors"), ZEND_ACC_PROTECTED);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @param bool normalize
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Eigen, decompose) {

	zval eig, _2;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_4 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool normalize;
	zval *a = NULL, a_sub, *normalize_param = NULL, _0, eigenvalues, eigenvectors, result, _1, _3, _5, norm$$5, _6$$5, _7$$5, _8$$5, _9$$5, _10$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&eigenvalues);
	ZVAL_UNDEF(&eigenvectors);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_3);
	ZVAL_UNDEF(&_5);
	ZVAL_UNDEF(&norm$$5);
	ZVAL_UNDEF(&_6$$5);
	ZVAL_UNDEF(&_7$$5);
	ZVAL_UNDEF(&_8$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&eig);
	ZVAL_UNDEF(&_2);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &normalize_param);

	normalize = zephir_get_boolval(normalize_param);


	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_invalidargumentexception_ce, "Cannot decompose a non-square matrix.", "tensor/decompositions/eigen.zep", 45);
		return;
	}
	ZEPHIR_INIT_VAR(&result);
	ZEPHIR_CALL_METHOD(&_1, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_eig(&result, &_1);
	if (Z_TYPE_P(&result) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_runtimeexception_ce, "Failed to decompose matrix.", "tensor/decompositions/eigen.zep", 54);
		return;
	}
	ZEPHIR_INIT_VAR(&eig);
	array_init(&eig);
	zephir_get_arrval(&_2, &result);
	ZEPHIR_CPY_WRT(&eig, &_2);
	ZEPHIR_OBS_VAR(&eigenvalues);
	zephir_array_fetch_long(&eigenvalues, &eig, 0, PH_NOISY, "tensor/decompositions/eigen.zep", 61);
	zephir_array_fetch_long(&_5, &eig, 1, PH_NOISY | PH_READONLY, "tensor/decompositions/eigen.zep", 62);
	ZEPHIR_CALL_CE_STATIC(&_3, tensor_matrix_ce, "quick", &_4, 0, &_5);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&eigenvectors, &_3, "transpose", NULL, 0);
	zephir_check_call_status();
	if (normalize) {
		ZEPHIR_CALL_METHOD(&_6$$5, &eigenvectors, "transpose", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_7$$5, &_6$$5, "square", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_8$$5, &_7$$5, "sum", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_9$$5, &_8$$5, "sqrt", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&norm$$5, &_9$$5, "transpose", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_10$$5, &eigenvectors, "dividevector", NULL, 0, &norm$$5);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&eigenvectors, &_10$$5);
	}
	object_init_ex(return_value, tensor_decompositions_eigen_ce);
	ZEPHIR_CALL_METHOD(NULL, return_value, "__construct", NULL, 25, &eigenvalues, &eigenvectors);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * @param list<int|float> eigenvalues
 * @param \Tensor\Matrix eigenvectors
 */
PHP_METHOD(Tensor_Decompositions_Eigen, __construct) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *eigenvalues_param = NULL, *eigenvectors = NULL, eigenvectors_sub;
	zval eigenvalues;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&eigenvalues);
	ZVAL_UNDEF(&eigenvectors_sub);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &eigenvalues_param, &eigenvectors);

	zephir_get_arrval(&eigenvalues, eigenvalues_param);


	zephir_update_property_zval(this_ptr, ZEND_STRL("eigenvalues"), &eigenvalues);
	zephir_update_property_zval(this_ptr, ZEND_STRL("eigenvectors"), eigenvectors);
	ZEPHIR_MM_RESTORE();

}

/**
 * Return the eigenvalues.
 *
 * @return list<int|float>
 */
PHP_METHOD(Tensor_Decompositions_Eigen, eigenvalues) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "eigenvalues");

}

/**
 * Return the eigenvectors.
 *
 * @return \Tensor\Matrix
 */
PHP_METHOD(Tensor_Decompositions_Eigen, eigenvectors) {

	zval *this_ptr = getThis();


	RETURN_MEMBER(getThis(), "eigenvectors");

}

