
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

	zval eig, _3;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_5 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool normalize;
	zval *a = NULL, a_sub, *normalize_param = NULL, _0, eigenvalues, eigenvectors, _1, _2, _4, _6, norm$$4, _7$$4, _8$$4, _9$$4, _10$$4, _11$$4;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&eigenvalues);
	ZVAL_UNDEF(&eigenvectors);
	ZVAL_UNDEF(&_1);
	ZVAL_UNDEF(&_2);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&norm$$4);
	ZVAL_UNDEF(&_7$$4);
	ZVAL_UNDEF(&_8$$4);
	ZVAL_UNDEF(&_9$$4);
	ZVAL_UNDEF(&_10$$4);
	ZVAL_UNDEF(&_11$$4);
	ZVAL_UNDEF(&eig);
	ZVAL_UNDEF(&_3);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &normalize_param);

	normalize = zephir_get_boolval(normalize_param);


	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(spl_ce_RuntimeException, "Cannot decompose a non-square matrix.", "tensor/decompositions/eigen.zep", 44);
		return;
	}
	ZEPHIR_INIT_VAR(&eig);
	array_init(&eig);
	ZEPHIR_INIT_VAR(&_1);
	ZEPHIR_CALL_METHOD(&_2, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_eig(&_1, &_2);
	zephir_get_arrval(&_3, &_1);
	ZEPHIR_CPY_WRT(&eig, &_3);
	ZEPHIR_OBS_VAR(&eigenvalues);
	zephir_array_fetch_long(&eigenvalues, &eig, 0, PH_NOISY, "tensor/decompositions/eigen.zep", 54);
	zephir_array_fetch_long(&_6, &eig, 1, PH_NOISY | PH_READONLY, "tensor/decompositions/eigen.zep", 55);
	ZEPHIR_CALL_CE_STATIC(&_4, tensor_matrix_ce, "quick", &_5, 0, &_6);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&eigenvectors, &_4, "transpose", NULL, 0);
	zephir_check_call_status();
	if (normalize) {
		ZEPHIR_CALL_METHOD(&_7$$4, &eigenvectors, "transpose", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_8$$4, &_7$$4, "square", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_9$$4, &_8$$4, "sum", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_10$$4, &_9$$4, "sqrt", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&norm$$4, &_10$$4, "transpose", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_11$$4, &eigenvectors, "dividevector", NULL, 0, &norm$$4);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&eigenvectors, &_11$$4);
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

