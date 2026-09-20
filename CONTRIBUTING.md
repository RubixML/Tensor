# Contributing Guidelines

Thank you for considering a contribution to Rubix ML. We believe that our contributors play the most important role in bringing powerful machine learning tools to the PHP language. Please read over the following guidelines so that we can continue to provide high quality machine learning tools that our users love.

## Pull Request Checklist

Here are a few things to check off before sending in a pull request ...

- Your changes pass [static analysis](#static-analysis)
- All [unit tests](#unit-testing) pass
- Your changes are consistent with our [coding style](#coding-style)
- Do your changes require updates to the documentation?
- Does an entry to the CHANGELOG need to be added?

> New to pull requests? Github has a great [howto](https://help.github.com/articles/about-pull-requests/) to get you started.

## Code Review

We use pull requests as an opportunity to communicate with our contributors. Oftentimes, we can improve code readability, find bugs, and make optimizations during the code review process. Every pull request must have the approval from at least one core engineer before merging into the main codebase.

## Static Analysis

Static code analysis is an integral part of our overall testing and quality assurance strategy. Static analysis allows us to catch bugs before they make it into the codebase. Therefore, it is important that your updates pass static analysis at the level set by the project lead.

To run static analysis:

```sh
$ composer analyze
```
  
## Unit Testing

New code will usually require an accompanying unit test. What to test depends on the type of change you are making. See the individual unit testing guidelines below.

To run the unit tests:

```sh
$ composer test
```

## General Object Testing

Limiting tests to public methods is usually sufficient. It is also important to test for edge cases such as mistakes that the user might make to ensure they are handled properly.

## Bugfix Testing

Bugs usually indicate an area of the code that has not been properly tested yet. When submitting a bug fix, please include a passing test that would have reproduced the bug prior to your changes.

## Coding Style

Rubix ML follows the PSR-2 coding style with additional rules to keep the codebase clean and reduce cognitive load for our developers. A consistent codebase allows for quicker debugging and generally a more pleasant developer experience (DX).

To run the style checker:

```sh
$ composer check
```

To run the automatic style fixer:

```sh
$ composer fix
```

### Anonymous Classes and Functions

Due to a limitation in PHP that requires objects and functions to be named in order to be unserialized and since the library relies on serialization for persistence, we do not use anonymous classes or functions in our codebase. Instead, create a named class or function.

## Benchmarks

Performance can be critical for some machine learning projects. To ensure that our users have the best experience, we benchmark every learner and use the information as a baseline to make optimizations. When contributing a new learner or transformer please include a benchmark.

To run the benchmarking suite:

```sh
$ composer benchmark
```

## Compiling the Docs

We use [Mkdocs](https://www.mkdocs.org) and [Mike](https://github.com/jimporter/mike) to compile the markdown documents in the `docs` folder to a versioned static document site.

Make sure to have the following Python dependencies installed.

```sh
$ pip install mike mkdocs mkdocs-material mkdocs-git-revision-date-localized-plugin
```

To serve the documentation site locally for development you can run the following commands from the terminal. Then, you'll be able to view the docs by navigating to `http://127.0.0.1:8000` in your browser.

```sh
$ mike deploy 'VERSION'

$ mike serve
```