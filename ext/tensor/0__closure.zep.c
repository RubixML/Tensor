
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/concat.h"
#include "kernel/memory.h"
#include "kernel/string.h"
#include "kernel/object.h"


ZEPHIR_INIT_CLASS(tensor_0__closure) {

	ZEPHIR_REGISTER_CLASS(tensor, 0__closure, tensor, 0__closure, tensor_0__closure_method_entry, ZEND_ACC_FINAL_CLASS);

	return SUCCESS;

}

PHP_METHOD(tensor_0__closure, __invoke) {

	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *carry, carry_sub, *row, row_sub, _0, _1;
	zval *this_ptr = getThis();

	ZVAL_UNDEF(&carry_sub);
	ZVAL_UNDEF(&row_sub);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&_1);

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &carry, &row);



	ZEPHIR_INIT_VAR(&_0);
	ZEPHIR_GET_CONSTANT(&_0, "PHP_EOL");
	ZEPHIR_INIT_VAR(&_1);
	zephir_fast_join_str(&_1, SL(" "), row);
	ZEPHIR_CONCAT_VVSVS(return_value, carry, &_0, "[ ", &_1, " ]");
	RETURN_MM();

}

