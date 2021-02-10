#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "kernel/operators.h"

void tensor_matmul(zval * return_value, zval * a, zval * bT)
{
    int i, j;
    zval rowC, c;
    zval sigma;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(bT);

    Bucket * va = aHat->arData;
    Bucket * vb = bHat->arData;

    int m = zend_array_count(aHat);
    int n = zend_array_count(bHat);

    array_init_size(&c, m);

    for (i = 0; i < m; i++) {
        array_init_size(&rowC, n);

        for (j = 0; j < n; j++) {
            tensor_dot(&sigma, &va[i].val, &vb[j].val);
            
            add_next_index_zval(&rowC, &sigma);
        }

        add_next_index_zval(&c, &rowC);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_dot(zval * return_value, zval * a, zval * b)
{
    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

    Bucket * va = aHat->arData;
    Bucket * vb = bHat->arData;

    int i;

    int n = zend_array_count(aHat);

    double sigma = 0.0;

    for (i = 0; i < n; i++) {
        sigma += zephir_get_doubleval(&va[i].val) * zephir_get_doubleval(&vb[i].val);
    }

    RETVAL_DOUBLE(sigma);
}
