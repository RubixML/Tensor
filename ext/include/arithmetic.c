#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include "kernel/operators.h"

void tensor_multiply(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double product;
	zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        product = zephir_get_doubleval(&ba[i].val) * zephir_get_doubleval(&bb[i].val);

	    add_next_index_double(&c, product);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_divide(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double quotient;
	zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        quotient = zephir_get_doubleval(&ba[i].val) / zephir_get_doubleval(&bb[i].val);

	    add_next_index_double(&c, quotient);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_add(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double sum;
	zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        sum = zephir_get_doubleval(&ba[i].val) + zephir_get_doubleval(&bb[i].val);

	    add_next_index_double(&c, sum);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_subtract(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double difference;
	zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        difference = zephir_get_doubleval(&ba[i].val) - zephir_get_doubleval(&bb[i].val);

	    add_next_index_double(&c, difference);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_pow(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double power;
	zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        power = pow(zephir_get_doubleval(&ba[i].val), zephir_get_doubleval(&bb[i].val));

	    add_next_index_double(&c, power);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_mod(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    zval modulus;
	zval c;

    zend_array * aa = Z_ARR_P(a);
    zend_array * ab = Z_ARR_P(b);

    Bucket * ba = aa->arData;
    Bucket * bb = ab->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        mod_function(&modulus, &ba[i].val, &bb[i].val);

	    add_next_index_zval(&c, &modulus);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_multiply_scalar(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double product;
	zval c;

    zend_array * aa = Z_ARR_P(a);

    Bucket * ba = aa->arData;

    double ab = zephir_get_doubleval(b);

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        product = zephir_get_doubleval(&ba[i].val) * ab;

	    add_next_index_double(&c, product);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_divide_scalar(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double quotient;
	zval c;

    zend_array * aa = Z_ARR_P(a);

    Bucket * ba = aa->arData;

    double ab = zephir_get_doubleval(b);

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        quotient = zephir_get_doubleval(&ba[i].val) / ab;

	    add_next_index_double(&c, quotient);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_add_scalar(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double sum;
	zval c;

    zend_array * aa = Z_ARR_P(a);

    Bucket * ba = aa->arData;

    double ab = zephir_get_doubleval(b);

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        sum = zephir_get_doubleval(&ba[i].val) + ab;

	    add_next_index_double(&c, sum);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_subtract_scalar(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double difference;
	zval c;

    zend_array * aa = Z_ARR_P(a);

    Bucket * ba = aa->arData;

    double ab = zephir_get_doubleval(b);

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        difference = zephir_get_doubleval(&ba[i].val) - ab;

	    add_next_index_double(&c, difference);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_pow_scalar(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    double power;
	zval c;

    zend_array * aa = Z_ARR_P(a);

    Bucket * ba = aa->arData;

    double ab = zephir_get_doubleval(b);

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        power = pow(zephir_get_doubleval(&ba[i].val), ab);

	    add_next_index_double(&c, power);
    }

    RETVAL_ARR(Z_ARR(c));
}

void tensor_mod_scalar(zval * return_value, zval * a, zval * b)
{
    unsigned int i;
    zval modulus;
	zval c;

    zend_array * aa = Z_ARR_P(a);

    Bucket * ba = aa->arData;

    unsigned int n = zend_array_count(aa);

	array_init_size(&c, n);

    for (i = 0; i < n; ++i) {
        mod_function(&modulus, &ba[i].val, b);

	    add_next_index_zval(&c, &modulus);
    }

    RETVAL_ARR(Z_ARR(c));
}
