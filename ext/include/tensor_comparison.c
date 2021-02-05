#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "kernel/operators.h"

void tensor_equal(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval comparison;
	zval c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        if (ZEPHIR_IS_EQUAL(valueA, valueB)) {
            ZVAL_LONG(&comparison, 1);
        } else {
            ZVAL_LONG(&comparison, 0);
        }

	    add_next_index_zval(&c, &comparison);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
}

void tensor_not_equal(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval comparison;
	zval c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        if (ZEPHIR_IS_EQUAL(valueA, valueB)) {
            ZVAL_LONG(&comparison, 0);
        } else {
            ZVAL_LONG(&comparison, 1);
        }

	    add_next_index_zval(&c, &comparison);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
}

void tensor_greater(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval comparison;
	zval c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        if (ZEPHIR_GT(valueA, valueB)) {
            ZVAL_LONG(&comparison, 1);
        } else {
            ZVAL_LONG(&comparison, 0);
        }

	    add_next_index_zval(&c, &comparison);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
}

void tensor_greater_equal(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval comparison;
	zval c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        if (ZEPHIR_GE(valueA, valueB)) {
            ZVAL_LONG(&comparison, 1);
        } else {
            ZVAL_LONG(&comparison, 0);
        }

	    add_next_index_zval(&c, &comparison);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
}

void tensor_less(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval comparison;
	zval c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);

        if (ZEPHIR_LT(valueA, valueB)) {
            ZVAL_LONG(&comparison, 1);
        } else {
            ZVAL_LONG(&comparison, 0);
        }

	    add_next_index_zval(&c, &comparison);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
}

void tensor_less_equal(zval * return_value, zval * a, zval * b)
{
	zval * valueA, * valueB;
	zend_ulong offset;
    zval comparison;
	zval c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

	array_init_size(&c, zend_array_count(aHat));

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);
        
        if (ZEPHIR_LE(valueA, valueB)) {
            ZVAL_LONG(&comparison, 1);
        } else {
            ZVAL_LONG(&comparison, 0);
        }

	    add_next_index_zval(&c, &comparison);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));
}
