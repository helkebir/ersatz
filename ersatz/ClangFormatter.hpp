//
// Created by Hamza El-Kebir on 1/4/22.
//

#ifndef ERSATZ_CLANGFORMATTER_HPP
#define ERSATZ_CLANGFORMATTER_HPP

#include "Codegen.hpp"
#include <cstdlib>

namespace ers {
    class ClangFormatter {
    public:
        ClangFormatter &dumpFormat(const ::std::string &filePath=".clang-format");

        ClangFormatter &invokeClangFormat(const ::std::string &filePath);

        template<typename... T>
        ClangFormatter &invokeClangFormat(const ::std::string &filePath, const T &...filePaths);

        uint IndentWidth = 4;
        ::std::string BreakBeforeBraces = "Stroustrup";
    };
}


#endif //ERSATZ_CLANGFORMATTER_HPP
