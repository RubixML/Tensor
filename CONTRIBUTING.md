# Contributing Guidelines
Thank you for considering a contribution to Rubix ML. We believe that our contributors play the most important role in bringing powerful machine learning tools to the PHP language. Please read over the following guidelines so that we can continue to provide high quality machine learning tools that our users love.

### Pull Request Checklist
Here are a few things to check off before sending in a pull request ...

- Your changes pass [static analysis](#static-analysis)
- All [unit tests](#unit-testing) pass
- Your changes are consistent with our [coding style](#coding-style)
- Do your changes require updates to the documentation?
- Does an entry to the CHANGELOG need to be added?
- Have you read and agreed to our [CLA](#contributor-license-agreement)?

> New to pull requests? Github has a great [howto](https://help.github.com/articles/about-pull-requests/) to get you started.

### Code Review
We use pull requests as an opportunity to communicate with our contributors. Oftentimes, we can improve code readability, find bugs, and make optimizations during the code review process. Every pull request must have the approval from at least one core engineer before merging into the main codebase.

### Contributor License Agreement
To ensure that project maintainers have the legal rights to license and distribute your code contributions, we ask that every contributor sign our [contributor license agreement](https://github.com/RubixML/Signatures/blob/master/CLA.md) (CLA). If you are a first-time contributor, you will automatically receive instructions on how to sign the agreement from our CLA bot with your first pull request.

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

### General Object Testing
Limiting tests to public methods is usually sufficient. It is also important to test for edge cases such as mistakes that the user might make to ensure they are handled properly.

### Bugfix Testing
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

## Extension Development
Every part of Tensor's object oriented API is duplicated in the accompanying PHP extension. This allows users to easily adopt the library and then add the extension later when they need the extra performance. The extension API code is written in [Zephir](https://zephir-lang.com) and the underlying optimizations are written in C. This allows us to take advantage of high-level language features while at the same time delivering high performance. We set up two Composer commands for your development environment that handle compiling both the Zephir and C code for you. For a more detailed setup you can consult the Zephir [documentation](https://docs.zephir-lang.com/0.12/en/installation).

To compile the extension:
```sh
$ composer compile
```

To remove all the files created during compilation:
```sh
$ composer clean
```
