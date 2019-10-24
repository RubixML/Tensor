
extern ZEPHIR_API zend_class_entry *tensor_tensor_ce;

ZEPHIR_INIT_CLASS(Tensor_Tensor);

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_shape, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_shape, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_shapestring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_shapestring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_size, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_size, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_map, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_reduce, 0, 0, 1)
	ZEND_ARG_INFO(0, callback)
	ZEND_ARG_INFO(0, initial)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_multiply, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_divide, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_add, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_subtract, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_pow, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_mod, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_equal, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_notequal, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_greater, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_greaterequal, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_less, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_lessequal, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_log, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, base, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, base)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_tensor_round, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, precision, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, precision)
#endif
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
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_asarray, 0, 0, IS_ARRAY, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor_asarray, 0, 0, IS_ARRAY, NULL, 0)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor___tostring, 0, 0, IS_STRING, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_tensor___tostring, 0, 0, IS_STRING, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_tensor_method_entry) {
	PHP_ABSTRACT_ME(Tensor_Tensor, shape, arginfo_tensor_tensor_shape)
	PHP_ABSTRACT_ME(Tensor_Tensor, shapeString, arginfo_tensor_tensor_shapestring)
	PHP_ABSTRACT_ME(Tensor_Tensor, size, arginfo_tensor_tensor_size)
	PHP_ABSTRACT_ME(Tensor_Tensor, map, arginfo_tensor_tensor_map)
	PHP_ABSTRACT_ME(Tensor_Tensor, reduce, arginfo_tensor_tensor_reduce)
	PHP_ABSTRACT_ME(Tensor_Tensor, transpose, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, multiply, arginfo_tensor_tensor_multiply)
	PHP_ABSTRACT_ME(Tensor_Tensor, divide, arginfo_tensor_tensor_divide)
	PHP_ABSTRACT_ME(Tensor_Tensor, add, arginfo_tensor_tensor_add)
	PHP_ABSTRACT_ME(Tensor_Tensor, subtract, arginfo_tensor_tensor_subtract)
	PHP_ABSTRACT_ME(Tensor_Tensor, pow, arginfo_tensor_tensor_pow)
	PHP_ABSTRACT_ME(Tensor_Tensor, mod, arginfo_tensor_tensor_mod)
	PHP_ABSTRACT_ME(Tensor_Tensor, equal, arginfo_tensor_tensor_equal)
	PHP_ABSTRACT_ME(Tensor_Tensor, notEqual, arginfo_tensor_tensor_notequal)
	PHP_ABSTRACT_ME(Tensor_Tensor, greater, arginfo_tensor_tensor_greater)
	PHP_ABSTRACT_ME(Tensor_Tensor, greaterEqual, arginfo_tensor_tensor_greaterequal)
	PHP_ABSTRACT_ME(Tensor_Tensor, less, arginfo_tensor_tensor_less)
	PHP_ABSTRACT_ME(Tensor_Tensor, lessEqual, arginfo_tensor_tensor_lessequal)
	PHP_ABSTRACT_ME(Tensor_Tensor, abs, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, square, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, sqrt, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, exp, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, log, arginfo_tensor_tensor_log)
	PHP_ABSTRACT_ME(Tensor_Tensor, sin, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, cos, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, tan, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, degrees, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, radians, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, sum, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, product, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, min, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, max, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, round, arginfo_tensor_tensor_round)
	PHP_ABSTRACT_ME(Tensor_Tensor, floor, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, ceil, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, clip, arginfo_tensor_tensor_clip)
	PHP_ABSTRACT_ME(Tensor_Tensor, clipLower, arginfo_tensor_tensor_cliplower)
	PHP_ABSTRACT_ME(Tensor_Tensor, clipUpper, arginfo_tensor_tensor_clipupper)
	PHP_ABSTRACT_ME(Tensor_Tensor, sign, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, negate, NULL)
	PHP_ABSTRACT_ME(Tensor_Tensor, asArray, arginfo_tensor_tensor_asarray)
	PHP_ABSTRACT_ME(Tensor_Tensor, __toString, arginfo_tensor_tensor___tostring)
	PHP_FE_END
};
