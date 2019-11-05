
extern ZEPHIR_API zend_class_entry *tensor_arithmetic_ce;

ZEPHIR_INIT_CLASS(Tensor_Arithmetic);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_multiply, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_divide, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_add, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_subtract, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_pow, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_mod, 0, 0, 1)
	ZEND_ARG_INFO(0, b)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_log, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, base, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, base)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_arithmetic_round, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, precision, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, precision)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_arithmetic_method_entry) {
	PHP_ABSTRACT_ME(Tensor_Arithmetic, multiply, arginfo_tensor_arithmetic_multiply)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, divide, arginfo_tensor_arithmetic_divide)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, add, arginfo_tensor_arithmetic_add)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, subtract, arginfo_tensor_arithmetic_subtract)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, pow, arginfo_tensor_arithmetic_pow)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, mod, arginfo_tensor_arithmetic_mod)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, abs, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, square, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, sqrt, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, exp, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, expm1, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, log, arginfo_tensor_arithmetic_log)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, log1p, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, sum, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, product, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, min, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, max, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, round, arginfo_tensor_arithmetic_round)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, floor, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, ceil, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, sign, NULL)
	PHP_ABSTRACT_ME(Tensor_Arithmetic, negate, NULL)
	PHP_FE_END
};
