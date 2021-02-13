
extern zend_class_entry *tensor_trigonometric_ce;

ZEPHIR_INIT_CLASS(Tensor_Trigonometric);

ZEPHIR_INIT_FUNCS(tensor_trigonometric_method_entry) {
	PHP_ABSTRACT_ME(Tensor_Trigonometric, sin, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, asin, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, cos, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, acos, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, tan, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, atan, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, rad2deg, NULL)
	PHP_ABSTRACT_ME(Tensor_Trigonometric, deg2rad, NULL)
	PHP_FE_END
};
