
extern zend_class_entry *tensor_functional_ce;

ZEPHIR_INIT_CLASS(Tensor_Functional);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_functional_log, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, base, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, base)
#endif
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_functional_round, 0, 0, 0)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, precision, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, precision)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_functional_method_entry) {
	PHP_ABSTRACT_ME(Tensor_Functional, abs, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, square, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, sqrt, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, exp, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, expm1, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, log, arginfo_tensor_functional_log)
	PHP_ABSTRACT_ME(Tensor_Functional, log1p, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, sum, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, product, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, min, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, max, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, round, arginfo_tensor_functional_round)
	PHP_ABSTRACT_ME(Tensor_Functional, floor, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, ceil, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, sign, NULL)
	PHP_ABSTRACT_ME(Tensor_Functional, negate, NULL)
	PHP_FE_END
};
