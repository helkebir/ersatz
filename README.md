# ersatz

> A lightweight C++11 library for code generation and rapid templating.

## Description

_ersatz_ provides a lightweight templating engine that accomplishes common tasks, including configuration file building
and code generation. Under the hood, _ersatz_ uses the tried-and-tested [{fmt}](https://fmt.dev/latest/index.html) library
for string formatting.

## Getting Started

### Dependencies

* CMake
* A C++11-compliant compiler
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (_optional_)
* [{fmt}](https://fmt.dev/latest/index.html) (C++ formatting library, _pre-bundled_)

### Building

Simply clone the [repository](https://github.com/helkebir/ersatz) and build using CMake.
If you just want to grab a static library, run `cmake ..` instead of a debug build.

```bash
git clone https://github.com/helkebir/ersatz
cd ersatz
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

You can find the examples in the `example/` folder.

### Getting Started

Here's an example to get you started. In addition to the [Codegen class](ersatz/Codegen.hpp),
we use the [FunctionBuilder class](ersatz/FunctionBuilder.hpp) to construct a template function as follows:

```cpp
#include <ersatz/Codegen.hpp>
#include <ersatz/FunctionBuilder.hpp>

// Declare a Codegen instance to start writing code in
ers::Codegen cg;

// We start by adding a docstring in Doxygen format
cg
.toggleCStyleComment(true).appendLine()
    .appendLine("@brief A function to add two arbitrary types.")
    .appendLine("@tparam T Left type.")
    .appendLine("@tparam U Right type.")
    .appendLine("@param a Left input.")
    .appendLine("@param a Right input.")
    .appendLine("@return Sum.")
.toggleCStyleComment();

// Now it's time to add the template function
ers::FunctionBuilder fb;

fb
.makeStatic() // Make the function static
.makeTemplate() // Make the function templated
.makeTrailingReturn() // Use a trailing return type
.addTemplateParameter("typename", "T") // Add the template parameters
.addTemplateParameter("typename", "U")
.setDesignator("add") // Set function designator
.setReturnType("decltype(a + b)") // We ask the compiler for the return type.
.addParameter("T", "a", "0") // Function parameters as (type, identifier, defaultArgument)
.addParameter("U", "b", "0")
.setFunctionBody("return a + b;") // The actual function body
.appendFunction(cg); // Add the function to the codegen stream

cg.print(); // Print to stdout
cg.writeToFile("myAdd.hpp"); // Write to file
```

Output:

```cpp
/** 
 * @brief A function to add two arbitrary types.
 * @tparam T Left type.
 * @tparam U Right type.
 * @param a Left input.
 * @param a Right input.
 * @return Sum.
 */
template<typename T, typename U>
static auto add(T a = 0, U b = 0) -> decltype(a + b)
{
    return a + b;
}
```

### Examples

A couple of demos have been bundled, with source files in the [`example`](example) folder.

#### [Demo](example/Codegen_demo.cpp)

A code generation demo, showcasing basic features of the [`Codegen` class](ersatz/Codegen.hpp), including box-drawing. Should print this output:
```cpp
/* ┌──────────────┐
 * │ Here's a box │
 * └──────────────┘
 * ╔════════════════════╗
 * ║ Here's a thick box ║
 * ╚════════════════════╝
 * ╭────────────────────╮
 * │ Here's a round box │
 * ╰────────────────────╯
 * ◉ ▣ ◈
 * ◯ □ ◇
 * ● ■ ◆
 * ┌───────────────┐
 * │ I can contain │
 * │     more      │
 * │     than      │
 * │      one      │
 * │     line!     │
 * └───────────────┘
 * ╔══════╗
 * ║  Me  ║
 * ║ too! ║
 * ╚══════╝
 * ┌───────┐
 * │ Label │
 * ├───────┴─┐
 * │ Content │
 * └─────────┘
 * ┌─────────────┐
 * │ with label! │
 * ├─────────────┴─┐
 * │   Here is a   │
 * │ ~~multiline~~ │
 * │     block     │
 * └───────────────┘
 */

template<typename T>
T unaryNegate(const T &a)
{
    /* 
     * This is a C-style comment
     * Have another line!
     */
    // This is a C++-style comment
    return -a;
}
```

#### [Formatting](example/Codegen_formatting.cpp)

A demo showcasing `clang-format` integration.
Shows how a custom `.clang_format` file can be generated using the [ClangFormatter class](ersatz/ClangFormatter.hpp),
and how functions can be built using the [`FunctionBuilder` class](ersatz/FunctionBuilder.hpp).



## Help

Documentation is still work-in-progress; feel free to look around in the header files, and open an issue in the meantime!

## Authors

Hamza El-Kebir<br/>
[@helkebir](http://github.com/helkebir)

## Version History

_Pre-alpha_

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

Beside the [{fmt}](https://fmt.dev/latest/index.html) library, inspiration was drawn from the following projects: 
* [Python formatted string literals (f-strings)](https://www.python.org/dev/peps/pep-0498/)
* [Apache Velocity](https://velocity.apache.org/engine/1.7/user-guide.html)
* [Haxe Templates](https://api.haxe.org/haxe/Template.html)

The name _ersatz_ was drawn from the economic term [_ersatz good_](https://en.wikipedia.org/wiki/Ersatz_good), which
refers to substitute goods. The word Ersatz in German translates to _substitute_ or _replacement_ in English. 