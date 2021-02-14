
extern zend_class_entry *tensor_settings_ce;

ZEPHIR_INIT_CLASS(Tensor_Settings);

PHP_METHOD(Tensor_Settings, setNumThreads);
PHP_METHOD(Tensor_Settings, numThreads);

#if PHP_VERSION_ID >= 70100
#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_settings_setnumthreads, 0, 1, IS_VOID, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_settings_setnumthreads, 0, 1, IS_VOID, NULL, 0)
#endif
#else
ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_settings_setnumthreads, 0, 0, 1)
#define arginfo_tensor_settings_setnumthreads NULL
#endif

#if PHP_VERSION_ID >= 70200
	ZEND_ARG_TYPE_INFO(0, threads, IS_LONG, 0)
#else
	ZEND_ARG_INFO(0, threads)
#endif
ZEND_END_ARG_INFO()

#if PHP_VERSION_ID >= 70200
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_settings_numthreads, 0, 0, IS_LONG, 0)
#else
ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_tensor_settings_numthreads, 0, 0, IS_LONG, NULL, 0)
#endif
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_settings_method_entry) {
	PHP_ME(Tensor_Settings, setNumThreads, arginfo_tensor_settings_setnumthreads, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Tensor_Settings, numThreads, arginfo_tensor_settings_numthreads, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
