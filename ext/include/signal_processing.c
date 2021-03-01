#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <math.h>
#include "kernel/operators.h"

void tensor_convolve_1d(zval * return_value, zval * a, zval * b, zval * stride)
{
    unsigned int i, j;
    unsigned int jmin, jmax;
    double sigma;
    zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int k = zephir_get_intval(stride);

    unsigned int na = zend_array_count(aa);
    unsigned int nb = zend_array_count(ab);
    unsigned int nc = na + nb - 1;

    double * va = emalloc(na * sizeof(double));
    double * vb = emalloc(nb * sizeof(double));

    for (i = 0; i < na; ++i) {
        va[i] = zephir_get_doubleval(&ba[i].val);
    }

    for (i = 0; i < nb; ++i) {
        vb[i] = zephir_get_doubleval(&bb[i].val);
    }

    unsigned int ncHat = ceil(nc / k);

    array_init_size(&c, ncHat);

    for (i = 0; i < nc; i += k) {
        jmin = i >= nb - 1 ? i - (nb - 1) : 0;
        jmax = i <= na ? i : na - 1;

        sigma = 0.0;

        for (j = jmin; j <= jmax; ++j) {
            sigma += va[j] * vb[i - j];
        }

        add_next_index_double(&c, sigma);
    }

    RETVAL_ARR(Z_ARR(c));

    efree(va);
    efree(vb);
}
