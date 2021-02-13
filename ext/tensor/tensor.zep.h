
extern zend_class_entry *tensor_tensor_ce;

ZEPHIR_INIT_CLASS(Tensor_Tensor);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_map, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_reduce, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, initial)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_clip, 0, 0, 2)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, min, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, min)
#endif
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, max, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, max)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_cliplower, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, min, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, min)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_clipupper, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, max, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, max)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_shapestring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_shapestring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor___tostring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor___tostring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_tensor_method_entry) {
	PHP_ABSTRACT_ME(Tensor_Tensor, map, arginfo_tensor_tensor_map)
	PHP_ABSTRACT_ME(Tensor_Tensor, reduce, arginfo_tensor_tensor_reduce)
	PHP_ABSTRACT_ME(Tensor_Tensor, transpose, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, clip, arginfo_tensor_tensor_clip)
	PHP_ABSTRACT_ME(Tensor_Tensor, clipLower, arginfo_tensor_tensor_cliplower)
	PHP_ABSTRACT_ME(Tensor_Tensor, clipUpper, arginfo_tensor_tensor_clipupper)
	PHP_ABSTRACT_ME(Tensor_Tensor, shapeString, arginfo_tensor_tensor_shapestring)
	PHP_ABSTRACT_ME(Tensor_Tensor, __toString, arginfo_tensor_tensor___tostring)
	PHP_FE_END
};
