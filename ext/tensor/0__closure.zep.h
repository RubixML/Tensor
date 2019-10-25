
extern ZEPHIR_API zend_class_entry *tensor_0__closure_ce;

ZEPHIR_INIT_CLASS(tensor_0__closure);

PHP_METHOD(tensor_0__closure, __invoke);

ZEND_BEGIN_ARG_INFO_EX(arginfo_tensor_0__closure___invoke, 0, 0, 2)
	ZEND_ARG_INFO(0, carry)
	ZEND_ARG_INFO(0, row)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(tensor_0__closure_method_entry) {
	PHP_ME(tensor_0__closure, __invoke, arginfo_tensor_0__closure___invoke, ZEND_ACC_PUBLIC|ZEND_ACC_FINAL)
	PHP_FE_END
};
