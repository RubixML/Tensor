#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <cblas.h>
#include <lapacke.h>

#include "php_ext.h"
#include "kernel/operators.h"

void tensor_matmul(zval * return_value, zval * a, zval * b)
{
    unsigned int i, j;
    Bucket * row;
    zval rowC, c;

    zend_zephir_globals_def * zephir_globals = ZEPHIR_VGLOBAL;

    openblas_set_num_threads(zephir_globals->num_threads);

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

    for (i = 0; i < m; ++i) {
        row = Z_ARR(ba[i].val)->arData;

        for (j = 0; j < p; ++j) {
            va[i * p + j] = zephir_get_doubleval(&row[j].val);
        }
    }

    for (i = 0; i < p; ++i) {
        row = Z_ARR(bb[i].val)->arData;

        for (j = 0; j < n; ++j) {
            vb[i * n + j] = zephir_get_doubleval(&row[j].val);
        }
    }

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, p, 1.0, va, p, vb, n, 0.0, vc, n);

    array_init_size(&c, m);

    for (i = 0; i < m; ++i) {
        array_init_size(&rowC, n);

        for (j = 0; j < n; ++j) {
            add_next_index_double(&rowC, vc[i * n + j]);
        }

        add_next_index_zval(&c, &rowC);
    }

    RETVAL_ARR(Z_ARR(c));

    efree(va);
    efree(vb);
    efree(vc);
}

void tensor_dot(zval * return_value, zval * a, zval * b)
{
    unsigned int i;

    zend_array * aHat = Z_ARR_P(a);
    zend_array * bHat = Z_ARR_P(b);

    Bucket * ba = aHat->arData;
    Bucket * bb = bHat->arData;

    unsigned int n = zend_array_count(aHat);

    double sigma = 0.0;

    for (i = 0; i < n; ++i) {
        sigma += zephir_get_doubleval(&ba[i].val) * zephir_get_doubleval(&bb[i].val);
    }

    RETVAL_DOUBLE(sigma);
}

void tensor_inverse(zval * return_value, zval * a)
{
    unsigned int i, j;
    Bucket * row;
    zval rowB, b;

    zend_zephir_globals_def * zephir_globals = ZEPHIR_VGLOBAL;

    openblas_set_num_threads(zephir_globals->num_threads);

    zend_array * aHat = Z_ARR_P(a);

    Bucket * ba = aHat->arData;

    unsigned int n = zend_array_count(aHat);

    double * va = emalloc(n * n * sizeof(double));

    for (i = 0; i < n; ++i) {
        row = Z_ARR(ba[i].val)->arData;

        for (j = 0; j < n; ++j) {
            va[i * n + j] = zephir_get_doubleval(&row[j].val);
        }
    }

    lapack_int status;

    int pivots[n];

    status = LAPACKE_dgetrf(LAPACK_ROW_MAJOR, n, n, va, n, pivots);

    if (status != 0) {
        RETURN_NULL();
    }
    
    status = LAPACKE_dgetri(LAPACK_ROW_MAJOR, n, va, n, pivots);

    if (status != 0) {
        RETURN_NULL();
    }

    array_init_size(&b, n);

    for (i = 0; i < n; ++i) {
        array_init_size(&rowB, n);

        for (j = 0; j < n; ++j) {
            add_next_index_double(&rowB, va[i * n + j]);
        }

        add_next_index_zval(&b, &rowB);
    }

    RETVAL_ARR(Z_ARR(b));

    efree(va);
}

void tensor_eig(zval * return_value, zval * a)
{
    unsigned int i, j;
    Bucket * row;
    zval eigenvalues;
    zval rowB, b;
    zval tuple;

    zend_zephir_globals_def * zephir_globals = ZEPHIR_VGLOBAL;

    openblas_set_num_threads(zephir_globals->num_threads);

    zend_array * aHat = Z_ARR_P(a);

    Bucket * ba = aHat->arData;

    unsigned int n = zend_array_count(aHat);

    double * va = emalloc(n * n * sizeof(double));
    double * wr = emalloc(n * sizeof(double));
    double * wi = emalloc(n * sizeof(double));
    double * vr = emalloc(n * n * sizeof(double));

    for (i = 0; i < n; i++) {
        row = Z_ARR(ba[i].val)->arData;

        for (j = 0; j < n; j++) {
            va[i * n + j] = zephir_get_doubleval(&row[j].val);
        }
    }

    lapack_int status = LAPACKE_dgeev(LAPACK_ROW_MAJOR, 'N', 'V', n, va, n, wr, wi, NULL, n, vr, n);

    if (status != 0) {
        RETURN_NULL();
    }

    array_init_size(&eigenvalues, n);
    array_init_size(&b, n);

    for (i = 0; i < n; i++) {
        array_init_size(&rowB, n);

        for (j = 0; j < n; j++) {
            add_next_index_double(&rowB, vr[i * n + j]);
        }

        add_next_index_zval(&b, &rowB);
        
        add_next_index_double(&eigenvalues, wr[i]);
    }

    array_init_size(&tuple, 2);
    
    add_next_index_zval(&tuple, &eigenvalues);
    add_next_index_zval(&tuple, &b);

    RETVAL_ARR(Z_ARR(tuple));

    efree(va);
    efree(wr);
    efree(wi);
    efree(vr);
}
