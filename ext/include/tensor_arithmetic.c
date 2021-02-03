#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "kernel/memory.h"

void tensor_multiply(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
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

void tensor_divide(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
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

void tensor_add(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
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

        add_function(&sum, valueA, valueB);

	    add_next_index_zval(&c, &sum);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));

    ZEPHIR_MM_RESTORE();
}

void tensor_subtract(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
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

void tensor_pow(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
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

void tensor_mod(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval modulus;
	zval c;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        mod_function(&modulus, valueA, valueB);

	    add_next_index_zval(&c, &modulus);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
    
    ZEPHIR_MM_RESTORE();
}
