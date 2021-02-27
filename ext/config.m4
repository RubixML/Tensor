PHP_ARG_ENABLE(tensor, whether to enable tensor, [ --enable-tensor   Enable Tensor])

if test "$PHP_TENSOR" = "yes"; then

	

	if ! test "x-lopenblas -llapacke -lgfortran -lpthread" = "x"; then
		PHP_EVAL_LIBLINE(-lopenblas -llapacke -lgfortran -lpthread, TENSOR_SHARED_LIBADD)
	fi

	AC_DEFINE(HAVE_TENSOR, 1, [Whether you have Tensor])
	tensor_sources="tensor.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c tensor/arithmetic.zep.c
	tensor/arraylike.zep.c
	tensor/comparable.zep.c
	tensor/functional.zep.c
	tensor/statistical.zep.c
	tensor/trigonometric.zep.c
	tensor/exceptions/tensorexception.zep.c
	tensor/tensor.zep.c
	tensor/exceptions/invalidargumentexception.zep.c
	tensor/vector.zep.c
	tensor/columnvector.zep.c
	tensor/decompositions/cholesky.zep.c
	tensor/decompositions/eigen.zep.c
	tensor/decompositions/lu.zep.c
	tensor/decompositions/svd.zep.c
	tensor/exceptions/dimensionalitymismatch.zep.c
	tensor/exceptions/runtimeexception.zep.c
	tensor/matrix.zep.c
	tensor/reductions/ref.zep.c
	tensor/reductions/rref.zep.c
	tensor/settings.zep.c include/indexing.c
	include/arithmetic.c
	include/comparison.c
	include/linear_algebra.c
	include/settings.c"
	PHP_NEW_EXTENSION(tensor, $tensor_sources, $ext_shared,, -O3 -ffast-math)
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	PHP_ADD_BUILD_DIR([$ext_builddir/tensor/])
    PHP_ADD_BUILD_DIR([$ext_builddir/tensor/decompositions/])
    PHP_ADD_BUILD_DIR([$ext_builddir/tensor/exceptions/])
    PHP_ADD_BUILD_DIR([$ext_builddir/tensor/reductions/])
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

	PHP_INSTALL_HEADERS([ext/tensor], [php_TENSOR.h])

fi
