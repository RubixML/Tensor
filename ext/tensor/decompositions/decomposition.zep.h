
extern ZEPHIR_API zend_class_entry *tensor_decompositions_decomposition_ce;

ZEPHIR_INIT_CLASS(Tensor_Decompositions_Decomposition);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_decompositions_decomposition_decompose, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, a, Tensor\\Matrix, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_decompositions_decomposition_method_entry) {
	ZEND_FENTRY(decompose, NULL, arginfo_tensor_decompositions_decomposition_decompose, ZEND_ACC_STATIC|ZEND_ACC_ABSTRACT|ZEND_ACC_PUBLIC)
	PHP_FE_END
};
