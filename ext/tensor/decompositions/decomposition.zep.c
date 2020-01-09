
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Tensor_Decompositions_Decomposition) {

	ZEPHIR_REGISTER_INTERFACE(Tensor\\Decompositions, Decomposition, tensor, decompositions_decomposition, NULL);

	return SUCCESS;

}

