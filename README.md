# ersatz

> A lightweight C++11 library for code generation and rapid templating.

## Description

_ersatz_ provides a lightweight templating engine that accomplishes common tasks, including configuration file building
and code generation. Under the hood, _ersatz_ uses the tried-and-tested [{fmt}](https://fmt.dev/latest/index.html) library is used to
allow for string formatting.

## Getting Started

### Dependencies

* CMake
* C++11 compiler
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html) (_optional_)
* [{fmt}](https://fmt.dev/latest/index.html) (C++ formatting library, pre-bundled)

### Installing

Simply clone the [repository](https://github.com/helkebir/ersatz) and build using CMake.
If you just want to grab a static library, run `cmake ..` instead of a debug build.

```bash
git clone https://github.com/helkebir/ersatz
cd ersatz
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

### Executing program

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