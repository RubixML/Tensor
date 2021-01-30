#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "kernel/memory.h"

void tensor_array_multiply(zval * return_value, zval * a, zval * b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval product;
	zval c;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        mul_function(&product, valueA, valueB);

	    add_next_index_zval(&c, &product);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
    ZEPHIR_MM_RESTORE();
}

void tensor_array_divide(zval * return_value, zval * a, zval * b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval quotient;
	zval c;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        div_function(&quotient, valueA, valueB);

	    add_next_index_zval(&c, &quotient);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
    ZEPHIR_MM_RESTORE();
}

void tensor_array_add(zval * return_value, zval * a, zval * b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval sum;
	zval c;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        fast_add_function(&sum, valueA, valueB);

	    add_next_index_zval(&c, &sum);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
    ZEPHIR_MM_RESTORE();
}

void tensor_array_subtract(zval * return_value, zval * a, zval * b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval difference;
	zval c;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        sub_function(&difference, valueA, valueB);

	    add_next_index_zval(&c, &difference);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
    ZEPHIR_MM_RESTORE();
}

void tensor_array_pow(zval * return_value, zval * a, zval * b)
{
	zval *valueA, *valueB;
	zend_ulong offset;
    zval power;
	zval c;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        pow_function(&power, valueA, valueB);

	    add_next_index_zval(&c, &power);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
    ZEPHIR_MM_RESTORE();
}
