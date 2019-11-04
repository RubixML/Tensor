PHP_ARG_ENABLE(tensor, whether to enable tensor, [ --enable-tensor   Enable Tensor])

if test "$PHP_TENSOR" = "yes"; then

	

	if ! test "x" = "x"; then
		PHP_EVAL_LIBLINE(, TENSOR_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_TENSOR, 1, [Whether you have Tensor])
	tensor_sources="tensor.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c tensor/arraylike.zep.c
	tensor/decompositions/decomposition.zep.c
	tensor/tensor.zep.c
	tensor/vector.zep.c
	tensor/columnvector.zep.c
	tensor/decompositions/lu.zep.c
	tensor/decompositions/ref.zep.c
	tensor/decompositions/rref.zep.c
	tensor/matrix.zep.c "
	PHP_NEW_EXTENSION(tensor, $tensor_sources, $ext_shared,, )
	PHP_SUBST(TENSOR_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([tensor], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([tensor], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/tensor], [tensor/arraylike.zep.h tensor/decompositions/decomposition.zep.h tensor/tensor.zep.h tensor/vector.zep.h tensor/columnvector.zep.h tensor/decompositions/lu.zep.h tensor/decompositions/ref.zep.h tensor/decompositions/rref.zep.h tensor/matrix.zep.h])

fi
