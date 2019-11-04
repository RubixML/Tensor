
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Tensor_ArrayLike) {

	ZEPHIR_REGISTER_INTERFACE(Tensor, ArrayLike, tensor, arraylike, tensor_arraylike_method_entry);

	zend_class_implements(tensor_arraylike_ce, 1, zend_ce_arrayaccess);
	zend_class_implements(tensor_arraylike_ce, 1, zend_ce_aggregate);
	zend_class_implements(tensor_arraylike_ce, 1, spl_ce_Countable);
	return SUCCESS;

}

/**
 * Return a tuple with the dimensionality of the array-like.
 *
 * @return int[]
 */
ZEPHIR_DOC_METHOD(Tensor_ArrayLike, shape);

/**
 * Return the number of elements in the array-like object.
 *
 * @return int
 */
ZEPHIR_DOC_METHOD(Tensor_ArrayLike, size);

/**
 * Return the elements of the array-like as a PHP array.
 *
 * @return array
 */
ZEPHIR_DOC_METHOD(Tensor_ArrayLike, asArray);

