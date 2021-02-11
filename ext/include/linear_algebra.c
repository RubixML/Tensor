#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <cblas.h>

#include "kernel/operators.h"

void tensor_matmul(zval * return_value, zval * a, zval * b)
{
    unsigned int i, j;
    Bucket * row;
    zval rowC, c;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

    Bucket * ba = aHat->arData;
    Bucket * bb = bHat->arData;

    unsigned int m = zend_array_count(aHat);
    unsigned int p = zend_array_count(bHat);
    unsigned int n = zend_array_count(Z_ARR(bb[0].val));

    double * va = emalloc(m * p * sizeof(double));
    double * vb = emalloc(n * p * sizeof(double));
    double * vc = emalloc(m * n * sizeof(double));

    for (i = 0; i < m; i++) {
        row = Z_ARR(ba[i].val)->arData;

        for (j = 0; j < p; j++) {
            va[i * p + j] = zephir_get_doubleval(&row[j].val);
        }
    }

    for (i = 0; i < p; i++) {
        row = Z_ARR(bb[i].val)->arData;

        for (j = 0; j < n; j++) {
            vb[i * n + j] = zephir_get_doubleval(&row[j].val);
        }
    }

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, p, 1, va, p, vb, n, 1, vc, n);

    array_init_size(&c, m);

    for (i = 0; i < m; i++) {
        array_init_size(&rowC, n);

        for (j = 0; j < n; j++) {
            add_next_index_double(&rowC, vc[i * n + j]);
        }

        add_next_index_zval(&c, &rowC);
    }

    efree(va);
    efree(vb);
    efree(vc);

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
