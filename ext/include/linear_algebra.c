#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "kernel/operators.h"
#include "kernel/memory.h"

void tensor_dot(zval * return_value, zval * a, zval * b)
{
    zval * valueA, * valueB;
	zend_ulong offset;

    zephir_method_globals * ZEPHIR_METHOD_GLOBALS_PTR = NULL;

    ZEPHIR_MM_GROW();

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

    double sigma = 0.0;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(aHat, offset, valueA) {
        valueB = zend_hash_index_find(bHat, offset);
        
        sigma += zephir_get_numberval(valueA) * zephir_get_numberval(valueB);
    } ZEND_HASH_FOREACH_END();

    RETVAL_DOUBLE(sigma);
    ZEPHIR_MM_RESTORE();
}
