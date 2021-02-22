
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
#include "kernel/concat.h"
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
 * @throws \Tensor\Exceptions\InvalidArgumentException
 * @throws \Tensor\Exceptions\RuntimeException
 * @return self
 */
PHP_METHOD(Tensor_Decompositions_Eigen, decompose) {

	zval eig, _5;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zephir_fcall_cache_entry *_7 = NULL;
	zend_long ZEPHIR_LAST_CALL_STATUS;
	zend_bool normalize;
	zval *a = NULL, a_sub, *normalize_param = NULL, _0, eigenvalues, eigenvectors, result, _4, _6, _8, _1$$3, _2$$3, _3$$3, norm$$5, _9$$5, _10$$5, _11$$5, _12$$5, _13$$5;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&a_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&eigenvalues);
	ZVAL_UNDEF(&eigenvectors);
	ZVAL_UNDEF(&result);
	ZVAL_UNDEF(&_4);
	ZVAL_UNDEF(&_6);
	ZVAL_UNDEF(&_8);
	ZVAL_UNDEF(&_1$$3);
	ZVAL_UNDEF(&_2$$3);
	ZVAL_UNDEF(&_3$$3);
	ZVAL_UNDEF(&norm$$5);
	ZVAL_UNDEF(&_9$$5);
	ZVAL_UNDEF(&_10$$5);
	ZVAL_UNDEF(&_11$$5);
	ZVAL_UNDEF(&_12$$5);
	ZVAL_UNDEF(&_13$$5);
	ZVAL_UNDEF(&eig);
	ZVAL_UNDEF(&_5);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &a, &normalize_param);

	normalize = zephir_get_boolval(normalize_param);


	ZEPHIR_CALL_METHOD(&_0, a, "issquare", NULL, 0);
	zephir_check_call_status();
	if (UNEXPECTED(!zephir_is_true(&_0))) {
		ZEPHIR_INIT_VAR(&_1$$3);
		object_init_ex(&_1$$3, tensor_exceptions_invalidargumentexception_ce);
		ZEPHIR_CALL_METHOD(&_2$$3, a, "shapestring", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_INIT_VAR(&_3$$3);
		ZEPHIR_CONCAT_SSVS(&_3$$3, "Matrix must be", " square, ", &_2$$3, " given.");
		ZEPHIR_CALL_METHOD(NULL, &_1$$3, "__construct", NULL, 3, &_3$$3);
		zephir_check_call_status();
		zephir_throw_exception_debug(&_1$$3, "tensor/decompositions/eigen.zep", 48);
		ZEPHIR_MM_RESTORE();
		return;
	}
	ZEPHIR_INIT_VAR(&result);
	ZEPHIR_CALL_METHOD(&_4, a, "asarray", NULL, 0);
	zephir_check_call_status();
	tensor_eig(&result, &_4);
	if (Z_TYPE_P(&result) == IS_NULL) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(tensor_exceptions_runtimeexception_ce, "Failed to decompose matrix.", "tensor/decompositions/eigen.zep", 57);
		return;
	}
	ZEPHIR_INIT_VAR(&eig);
	array_init(&eig);
	zephir_get_arrval(&_5, &result);
	ZEPHIR_CPY_WRT(&eig, &_5);
	ZEPHIR_OBS_VAR(&eigenvalues);
	zephir_array_fetch_long(&eigenvalues, &eig, 0, PH_NOISY, "tensor/decompositions/eigen.zep", 64);
	zephir_array_fetch_long(&_8, &eig, 1, PH_NOISY | PH_READONLY, "tensor/decompositions/eigen.zep", 65);
	ZEPHIR_CALL_CE_STATIC(&_6, tensor_matrix_ce, "quick", &_7, 0, &_8);
	zephir_check_call_status();
	ZEPHIR_CALL_METHOD(&eigenvectors, &_6, "transpose", NULL, 0);
	zephir_check_call_status();
	if (normalize) {
		ZEPHIR_CALL_METHOD(&_9$$5, &eigenvectors, "transpose", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_10$$5, &_9$$5, "square", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_11$$5, &_10$$5, "sum", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_12$$5, &_11$$5, "sqrt", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&norm$$5, &_12$$5, "transpose", NULL, 0);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_13$$5, &eigenvectors, "dividevector", NULL, 0, &norm$$5);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(&eigenvectors, &_13$$5);
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

