
extern ZEPHIR_API zend_class_entry *tensor_decompositions_ref_ce;

ZEPHIR_INIT_CLASS(Tensor_Decompositions_Ref);

PHP_METHOD(Tensor_Decompositions_Ref, decompose);
PHP_METHOD(Tensor_Decompositions_Ref, gaussianElimination);
PHP_METHOD(Tensor_Decompositions_Ref, rowReductionMethod);
PHP_METHOD(Tensor_Decompositions_Ref, __construct);
PHP_METHOD(Tensor_Decompositions_Ref, a);
PHP_METHOD(Tensor_Decompositions_Ref, swaps);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tensor_decompositions_ref_decompose, 0, 1, Tensor\\Decompositions\\Ref, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_ref_decompose, 0, 1, IS_OBJECT, "Tensor\\Decompositions\\Ref", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tensor_decompositions_ref_gaussianelimination, 0, 1, Tensor\\Decompositions\\Ref, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_ref_gaussianelimination, 0, 1, IS_OBJECT, "Tensor\\Decompositions\\Ref", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tensor_decompositions_ref_rowreductionmethod, 0, 1, Tensor\\Decompositions\\Ref, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_ref_rowreductionmethod, 0, 1, IS_OBJECT, "Tensor\\Decompositions\\Ref", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_decompositions_ref___construct, 0, 0, 2)
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, swaps, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, swaps)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tensor_decompositions_ref_a, 0, 0, Tensor\\Matrix, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_ref_a, 0, 0, IS_OBJECT, "Tensor\\Matrix", 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_ref_swaps, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_ref_swaps, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_decompositions_ref_method_entry) {
	PHP_ME(Tensor_Decompositions_Ref, decompose, arginfo_tensor_decompositions_ref_decompose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tensor_Decompositions_Ref, gaussianElimination, arginfo_tensor_decompositions_ref_gaussianelimination, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tensor_Decompositions_Ref, rowReductionMethod, arginfo_tensor_decompositions_ref_rowreductionmethod, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tensor_Decompositions_Ref, __construct, arginfo_tensor_decompositions_ref___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Tensor_Decompositions_Ref, a, arginfo_tensor_decompositions_ref_a, ZEND_ACC_PUBLIC)
	PHP_ME(Tensor_Decompositions_Ref, swaps, arginfo_tensor_decompositions_ref_swaps, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
