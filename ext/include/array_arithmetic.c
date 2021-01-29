#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "kernel/memory.h"

void tensor_array_multiply(zval *return_value, zval *a, zval *b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval product;
	zval c;

    zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

	array_init(&c);

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(a), offset, valueA) {
        valueB = zend_hash_index_find(Z_ARRVAL_P(b), offset);

        mul_function(&product, valueA, valueB);

	    add_next_index_zval(&c, &product);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARRVAL(c));
}

void tensor_array_divide(zval *return_value, zval *a, zval *b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval quotient;
	zval c;

    zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

	array_init(&c);

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(a), offset, valueA) {
        valueB = zend_hash_index_find(Z_ARRVAL_P(b), offset);

        div_function(&quotient, valueA, valueB);

	    add_next_index_zval(&c, &quotient);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARRVAL(c));
}

void tensor_array_add(zval *return_value, zval *a, zval *b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval sum;
	zval c;

    zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

	array_init(&c);

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(a), offset, valueA) {
        valueB = zend_hash_index_find(Z_ARRVAL_P(b), offset);

        add_function(&sum, valueA, valueB);

	    add_next_index_zval(&c, &sum);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARRVAL(c));
}

void tensor_array_subtract(zval *return_value, zval *a, zval *b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval difference;
	zval c;

    zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

	array_init(&c);

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(a), offset, valueA) {
        valueB = zend_hash_index_find(Z_ARRVAL_P(b), offset);

        sub_function(&difference, valueA, valueB);

	    add_next_index_zval(&c, &difference);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARRVAL(c));
}
