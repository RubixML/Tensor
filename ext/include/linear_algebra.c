#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "kernel/operators.h"

void tensor_matmul(zval * return_value, zval * a, zval * bT)
{
    int i, j, k;
    double sigma;
    zval rowC, c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(bT);

    Bucket * ba = aHat->arData;
    Bucket * bb = bHat->arData;

    int m = zend_array_count(aHat);
    int n = zend_array_count(bHat);
    int p = zend_array_count(Z_ARR(ba[0].val));

    double * va = emalloc(m * p * sizeof(double));
    double * vb = emalloc(n * p * sizeof(double));

    for (i = 0; i < m; i++) {
        Bucket * bba = Z_ARR(ba[i].val)->arData;

        for (j = 0; j < p; j++) {
            va[i * p + j] = zephir_get_doubleval(&bba[j].val);
        }
    }

    for (i = 0; i < n; i++) {
        Bucket * bbb = Z_ARR(bb[i].val)->arData;

        for (j = 0; j < p; j++) {
            vb[i * p + j] = zephir_get_doubleval(&bbb[j].val);
        }
    }

    array_init_size(&c, m);

    for (i = 0; i < m; i++) {
        array_init_size(&rowC, n);

        for (j = 0; j < n; j++) {
            sigma = 0.0;

            for (k = 0; k < p; k++) {
                sigma += va[i * p + k] * vb[j * p + k];
            }
                    
            add_next_index_double(&rowC, sigma);
        }

        add_next_index_zval(&c, &rowC);
    }

    efree(va);
    efree(vb);

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
