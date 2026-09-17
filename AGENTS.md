# AGENTS.md

Guidance for AI coding agents contributing to **Tensor** — scientific computing for PHP. The project ships two things with a single, identical object-oriented API:

- **A Composer library** (`rubix/tensor`) — pure PHP classes in `src/`.
- **A PECL extension** — the same API re-implemented in Zephir + C, backed by OpenBLAS / LAPACKE, built from `ext/` and `package.xml`.

> If both the library and the extension are installed and loaded, the **extension takes precedence**. The public surface of the two is meant to stay in lockstep.

## Repository layout

| Path | Purpose |
| --- | --- |
| `src/` | Library classes. `Tensor` interface plus `Vector`, `Matrix`, `ColumnVector`; `Decompositions/` (Cholesky, Eigen, LU, SVD), `Reductions/` (REF, RREF), `Exceptions/`, and `constants.php` (always auto-loaded). |
| `tests/` | PHPUnit test suite. One `*Test.php` per class. |
| `benchmarks/` | phpbench suites, organized per functional area. |
| `optimizers/` | Zephir function-call optimizers, one `Tensor*Optimizer.php` per operation. |
| `ext/` | Generated Zephir C code + hand-written C under `ext/include/*.c`. Do not hand-edit generated files. |
| `config.json` | Zephir build config (namespace, version, `extra-libs`, optimization & warning flags). |
| `package.xml` | PECL package descriptor (name, version, source list). |
| `build-ext` | PHP script that patches `ext/config.m4` before compile (Alpine/musl + backtrace_symbols `execinfo` handling). |

## Environment

- PHP **8.0+** (CI matrix is 8.0 → 8.3). `composer.json` still declares `>=7.4`.
- Dev tooling is installed as Composer dev dependencies (PHPStan, php-cs-fixer, phpunit, phpbench, Zephir).
- Compiling the extension additionally needs a C compiler, GFortran, `phpize`, OpenBLAS dev headers, LAPACKE, and re2c (see README for per-OS install commands).

## Commands

All are Composer scripts (see `composer.json`):

| Task | Command |
| --- | --- |
| Install deps | `composer install` |
| Validate manifest | `composer validate` |
| Static analysis | `composer analyze` (PHPStan level 8 over `src`, `tests`, `benchmarks`) |
| Run tests | `composer test` (PHPUnit, test suite `Base`) |
| Check style | `composer check` (php-cs-fixer, dry-run; sets `PHP_CS_FIXER_IGNORE_ENV=1`) |
| Fix style | `composer fix` |
| Full build | `composer build` = validate → install → analyze → test → check |
| Benchmarks | `composer benchmark` |
| Compile extension | `composer compile` = zephir generate → `php build-ext` → zephir compile → zephir install |
| Clean generated extension | `composer clean` (zephir fullclean) |

**Recommended loop before submitting a change:**

```sh
composer install
composer analyze
composer test
composer fix
```

(`composer build` runs all of the above in one shot, plus `composer validate`.)

## Conventions to follow

- **No anonymous classes or anonymous functions (closures).** The library relies on `serialize()`/`unserialize()` for persistence, and PHP cannot un-nameable anonymous code. Always introduce a named class or named function instead.
- **Coding style** is governed by `.php-cs-fixer.dist.php` (extends `@PSR2`). Highlights: single quotes, short array syntax, compact nullable type hints, pre-increment, ordered class elements, trimmed/multi-line phpdoc, `echo` over `print`. Rather than memorize the rule set, run `composer fix`.
- **Static analysis is required.** New code must pass PHPStan level 8 (`composer analyze`). Keep types accurate; the codebase uses docblock generics like `list<float>` and `int<0,max>`.
- **Testing guidance** (from `CONTRIBUTING.md`):
  - New functionality ships with a matching unit test in `tests/`.
  - Bug fixes ship with a passing test that would have reproduced the bug beforehand.
  - Tests target public methods and cover edge cases / invalid input.
- **Documentation & changelog:** update docs if behavior changes, and add a `CHANGELOG.md` entry for user-facing changes.
- **PHPDoc:** classes use `@category` / `@package` / `@author` blocks; methods carry param and return annotations. Use `@var list<float>` for element arrays.
- **Exceptions** are typed under `Tensor\Exceptions` (e.g. `InvalidArgumentException`, `DimensionalityMismatch`, `RuntimeException`). Use the existing ones rather than `Exception`.
- **Math is float-only.** Values stored/computed as `float`; don't introduce integer-only branches. When adding a new operation, mirror it across the `Tensor` sub-interfaces (`Arithmetic`, `Comparable`, `Algebraic`, `Trigonometric`, `Statistical`, `Special`).
- Optimizations should be accompanied by a before and after benchmark to measure and prove the performance gain.

## Keeping library and extension in sync

Every public method a new `src/` class adds typically has a counterpart in the Zephir extension. When you add or change an operation at the API level:

1. Update the PHP class in `src/`.
2. Add/adjust the matching `optimizers/Tensor<Op>Optimizer.php` if it is a callable that the extension should route into C.
3. Ensure the underlying C implementation exists under `ext/include/*.c` and is linked (already wired in `config.json` `extra-sources`).
4. Bump the version in both `config.json` and `package.xml` if this is a released change, and record it in `CHANGELOG.md`.

Do **not** hand-edit the generated C in `ext/` (files like `*.dep`, `*.lo`, `*.o`, `Makefile*`, `config.h`). They are produced by `composer compile`. Hand-written logic belongs in `ext/include/*.c`.

## Working verification paths

- Library path, ext-free: php -n -d extension=dom -d extension=mbstring -d extension=tokenizer -d extension=xml -d extension=xmlwriter -d extension=xmlreader vendor/bin/phpunit ...
- Extension path, local build: php -n -d extension=$PWD/ext/modules/tensor.so vendor/bin/phpunit ...

## Notes for agents

- Run `composer fix` rather than trying to normalize formatting by hand — the rule set is broad and idiosyncratic.
- `phpunit.xml` runs a single `Base` test suite from `tests/`; add new files there.
- The `build-ext` script is part of `composer compile` and patches `ext/config.m4` idempotently; it is safe to re-run.
- This is a numerical library: when in doubt about precision, match the existing `MAX_DELTA`-style tolerance approach used in `tests`.
- The `optimizers/` namespace is `Zephir\Optimizers\FunctionCall` (PSR-4 in `composer.json`), not `Tensor`.
