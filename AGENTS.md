# AGENTS.md

Guidance for AI coding agents contributing to **Tensor** — scientific computing for PHP. The project is a Composer library (`rubix/tensor`) of pure PHP classes in `src/` exposing a single object-oriented API.

## Repository layout

| Path | Purpose |
| --- | --- |
| `src/` | Library classes. `Tensor` interface plus `Vector`, `Matrix`, `ColumnVector`; `Decompositions/` (Cholesky, Eigen, LU, SVD), `Reductions/` (REF, RREF), `Exceptions/`, and `constants.php` (always auto-loaded). |
| `docs/` | Project documentation. |
| `tests/` | PHPUnit test suite. One `*Test.php` per class. |
| `benchmarks/` | phpbench suites, organized per functional area. |

## Environment

- PHP **8.3+** (CI matrix is 8.3 → 8.5).
- Dev tooling is installed as Composer dev dependencies (PHPStan, php-cs-fixer, phpunit, phpbench).

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

## Working verification paths

In some environments, you may need to override the configured extensions to test different paths.

- Library path, ext-free: php -n -d extension=dom -d extension=mbstring -d extension=tokenizer -d extension=xml -d extension=xmlwriter -d extension=xmlreader vendor/bin/phpunit ...

## Notes for agents

- Run `composer fix` rather than trying to normalize formatting by hand — the rule set is broad and idiosyncratic.
- `phpunit.xml` runs a single `Base` test suite from `tests/`; add new files there.
- This is a numerical library: when in doubt about precision, match the existing `MAX_DELTA`-style tolerance approach used in `tests`.
