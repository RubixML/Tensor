#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "kernel/operators.h"

void hashmap_to_c_array(zval *return_value, zval *values)
{
    zval *current;
    zend_ulong index;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL_P(values), index, current) {

    }
}