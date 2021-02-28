#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include "kernel/operators.h"

void tensor_argmin(zval * return_value, zval * values)
{
	zval * current, min;
	zend_ulong index;

    ZVAL_DOUBLE(&min, INFINITY);
    RETVAL_NULL();

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARR_P(values), index, current) {
        if (ZEPHIR_LT(current, &min)) {
			ZVAL_COPY(&min, current);

            RETVAL_LONG(index);
		}
    } ZEND_HASH_FOREACH_END();
}

void tensor_argmax(zval * return_value, zval * values)
{
	zval * current, max;
	zend_ulong index;

    ZVAL_DOUBLE(&max, -INFINITY);
    RETVAL_NULL();

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARR_P(values), index, current) {
        if (ZEPHIR_GT(current, &max)) {
			ZVAL_COPY(&max, current);

            RETVAL_LONG(index);
		}
    } ZEND_HASH_FOREACH_END();
}
