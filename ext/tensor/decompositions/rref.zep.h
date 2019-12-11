
extern ZEPHIR_API zend_class_entry *tensor_decompositions_rref_ce;

ZEPHIR_INIT_CLASS(Tensor_Decompositions_Rref);

PHP_METHOD(Tensor_Decompositions_Rref, decompose);
PHP_METHOD(Tensor_Decompositions_Rref, __construct);
PHP_METHOD(Tensor_Decompositions_Rref, a);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tensor_decompositions_rref_decompose, 0, 1, Tensor\\Decompositions\\Rref, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_rref_decompose, 0, 1, IS_OBJECT, "Tensor\\Decompositions\\Rref", 0)
#endif
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_decompositions_rref___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_tensor_decompositions_rref_a, 0, 0, Tensor\\Matrix, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_decompositions_rref_a, 0, 0, IS_OBJECT, "Tensor\\Matrix", 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_decompositions_rref_method_entry) {
	PHP_ME(Tensor_Decompositions_Rref, decompose, arginfo_tensor_decompositions_rref_decompose, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tensor_Decompositions_Rref, __construct, arginfo_tensor_decompositions_rref___construct, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Tensor_Decompositions_Rref, a, arginfo_tensor_decompositions_rref_a, ZEND_ACC_PUBLIC)
	PHP_FE_END
};
