
extern zend_class_entry *tensor_statistical_ce;

ZEPHIR_INIT_CLASS(Tensor_Statistical);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_statistical_variance, 0, 0, 0)
	ZEND_ARG_INFO(0, mean)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_statistical_quantile, 0, 0, 1)
#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, q, IS_DOUBLE, 0)
#else
	ZEND_ARG_INFO(0, q)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_statistical_method_entry) {
	PHP_ABSTRACT_ME(Tensor_Statistical, mean, NULL)
	PHP_ABSTRACT_ME(Tensor_Statistical, variance, arginfo_tensor_statistical_variance)
	PHP_ABSTRACT_ME(Tensor_Statistical, median, NULL)
	PHP_ABSTRACT_ME(Tensor_Statistical, quantile, arginfo_tensor_statistical_quantile)
	PHP_FE_END
};
