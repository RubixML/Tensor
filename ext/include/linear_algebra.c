#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "kernel/operators.h"
#include "kernel/memory.h"

void tensor_matmul(zval * return_value, zval * a, zval * bT)
{
    zval * rowA, * columnB;
    zval rowC, c;
    zval sigma;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bTHat = Z_ARR_P(bT);

    int m = zend_array_count(aHat);
    int n = zend_array_count(bTHat);

    array_init_size(&c, m);

    ZEND_HASH_FOREACH_VAL(aHat, rowA) {
        array_init_size(&rowC, n);

        ZEND_HASH_FOREACH_VAL(bTHat, columnB) {
            tensor_dot(&sigma, rowA, columnB);
            
            add_next_index_zval(&rowC, &sigma);
        } ZEND_HASH_FOREACH_END();

        add_next_index_zval(&c, &rowC);
    } ZEND_HASH_FOREACH_END();

    RETVAL_ARR(Z_ARR(c));

    ZEPHIR_MM_RESTORE();
}

void tensor_dot(zval * return_value, zval * a, zval * b)
{
    zval * valueA, * valueB;
	zend_ulong offset;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

    double sigma = 0.0;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);
        
        sigma += zephir_get_numberval(valueA) * zephir_get_numberval(valueB);
    } ZEND_HASH_FOREACH_END();

    RETVAL_DOUBLE(sigma);
}
