
extern zend_class_entry *tensor_arraylike_ce;

ZEPHIR_INIT_CLASS(Tensor_ArrayLike);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_arraylike_shape, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_arraylike_shape, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_arraylike_size, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_arraylike_size, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_arraylike_asarray, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_arraylike_asarray, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_arraylike_method_entry) {
	PHP_ABSTRACT_ME(Tensor_ArrayLike, shape, arginfo_tensor_arraylike_shape)
	PHP_ABSTRACT_ME(Tensor_ArrayLike, size, arginfo_tensor_arraylike_size)
	PHP_ABSTRACT_ME(Tensor_ArrayLike, asArray, arginfo_tensor_arraylike_asarray)
	PHP_FE_END
};
