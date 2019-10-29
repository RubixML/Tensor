
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Tensor_Decompositions_Decomposition) {

	ZEPHIR_REGISTER_INTERFACE(Tensor\\Decompositions, Decomposition, tensor, decompositions_decomposition, tensor_decompositions_decomposition_method_entry);

	return SUCCESS;

}

/**
 * Factory method to decompose a matrix.
 *
 * @param \Tensor\Matrix a
 * @return self
 */
ZEPHIR_DOC_METHOD(Tensor_Decompositions_Decomposition, decompose);

