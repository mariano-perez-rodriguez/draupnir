# Draupnir Contribution Guidelines

This document briefly describes the contribution guidelines to be observed when contributing to Draupnir.

## Index

- [Coding Style](#coding-style)
- [Filename Conventions](#filename-conventions)
- [Coding Conventions](#coding-conventions)
- [Testing](#testing)
- [Licensing](#licensing)

* * *

## Coding Style

Draupnir follows an indentation style reminiscent of the [1TBS](https://en.wikipedia.org/wiki/Indent_style#Variant:_1TBS) (ie. "one True Brace Style"). If you're using Eclipse CDT, you can find a style definition XML in [extras/DraupnirStyle.xml](./extras/DraupnirStyle.xml).

To summarize it, consider:

- Braces for statements follow the statements they brace (ie. a `for` loop has its corresponding brace on the same line), as do functions ans classes, and their bodies are indented within. The only formal exception to this rule are plain blocks, whose opening and closing braces should start at the current indentation level and whose body should be indented within. Of course, there can be _reasonable_ exceptions to this rule.
- No braces can be omitted from bodies (again, this rule allows for _reasonable_ exceptions).
- No spaces are required nor desired before function calls, but required before the parenthesized conditions in `for`, `do`, `while`, `if`, `switch`, and `catch`.
- Spaces are required, though, for every binary operator, with the exceptions of `operator[]`, `operator()`, and `operator,`, this last one requires a space after, but not before.

This is merely a summary, when in doubt, the style file provided is authoritative.

## Filename Conventions

All `C++` files should be placed in the `src` directory, possibly within subdirectories therein.

All files having a `.cpp` extension ___will be compiled into object files and linked with the main executable.___ Although exceptions can be accommodated for, they will be virtually nonexistent until we see a truly compelling reason behind them (the `Makefile` is a treacherous beast).

No directory names `doc`, `tex`, `man`, `release`, `debug`, `noopt`, or `extras` are allowed to be clobbered. The build system uses `release`, `debug` and `noopt` for release, debug and non-optimized builds respectively; the `extras` directory contains loosely unrelated files; the `doc` directory contains documentation resources; and the `man` and `tex` directories are reserved for future use.

## Coding Conventions

Avoid polluting the `std` namespace unless a currently established best practice compels you to (eg. defining a specialization of `std::swap`). Furthermore, avoid the lazy `using namespace std;` declaration: its awfully broad; _specially_ in header files.

Arguments or variables which are not used, yet must be declared should be flagged with `__attribute__((unused))`; furthermore, the preferred attribute syntax is `__attribute__`, not `__attribute`, and underscores in attribute declarations proper should be dispensed with whenever possible.

Every non-`static`, non anonymous (ie. defined in an empty namespace) function _must_ be provided with prototypes in a header file. Similar requirements apply to classes, structures, unions, and enums.

Every header file _must_ use include guards, and such include guards must follow the form:

````c++
#ifndef NAME_OF_INCLUDE_FILE_H__
#define NAME_OF_INCLUDE_FILE_H__

...

#endif /* NAME_OF_INCLUDE_FILE_H__ */
````

Ie. the name of the guard constant must be the un-camelCased name of the header file, followed by `_H__`; a comment stating the name of the header guard must follow the `#endif` directive. ___No code whatsoever is allowed before the include guard___, including comments, preprocessor directives or blank lines. Exceptions can be made, but they will be extremely rare.

Each template class must be defined in a file with `.hpp` extension. This file must include the header guards of a "normal" header file, but with an `_HPP__` suffix (all previous observations about header files apply in these cases as well). Furthermore, the corresponding header file _must_ include the implementation file as the last statement before the header guard closing, eg:

````c++
#ifndef NAME_OF_INCLUDE_FILE_H__
#define NAME_OF_INCLUDE_FILE_H__

...

#include "NameOfIncludeFile.hpp"

#endif /* NAME_OF_INCLUDE_FILE_H__*/
````

Where the `.hpp` file would be:

````c++
#ifndef NAME_OF_INCLUDE_FILE_HPP__
#define NAME_OF_INCLUDE_FILE_HPP__

#include "NameOfIncludeFile.h"

...

#endif /* NAME_OF_INCLUDE_FILE_HPP__*/
````

This is so that problems with template instantiation can be solved in a straightforward (albeit inelegant) way. Note that the `.hpp` file includes the `.h` file back: this is in order to allow for refactoring templates into plain classes to be simpler and less error-prone.

Template functions should observe the same rules.

If, because of circular dependencies, forward declarations must be provided for, the forward declarations of elements defined in a header file named `Filename.h` must be named `Filename.fwd.h`. Of course, circular dependencies are best avoided, but if unavoidable, they should follow this scheme.

___Code for GCC___, no support for other platforms or compilers is currently planned, so there's no point in providing it at the expense of functionality or clarity.

All functions, classes, structures, etc. must be clearly and thoroughly documented, if you cannot be bothered to write the proper documentation, at the very least make your code speak for you (and submit an issue for documentation writing).

And last, but not least, `goto` is not evil, it's merely dangerous if used irresponsibly, so if `goto` would make the source clearer or more performant, by all means, use it, but exercise caution and be responsible.

## Testing

No testing framework is prescribed. Currently, Draupnir has no tests whatsoever generated for it.

The quality of the numbers generated, though, _must_ be tested. This is easily accomplished with `dieharder`.

Furthermore, the generator's throughput should not suffer particularly, so be sure to test for it with something along the lines of:

````sh
pv -pterabSs $((1024 * 1024 * 1024)) > /dev/null
````

using the `pv` utility (found in the standard repos).

## Licensing

Finally, this should go without saying, your contributions will form part of a GNU project released under the AGPLv3 (see the file [LICENSE.md](./LICENSE.md) for details), be sure you understand and accept the terms therein before contributing.
