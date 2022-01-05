//
// Created by Hamza El-Kebir on 1/4/22.
//

#include "Codegen.hpp"
#include "FunctionBuilder.hpp"
#include "ClangFormatter.hpp"

int main()
{
    ers::Codegen cg;

    cg
    .toggleCStyleComment(true).appendLine()
        .appendLine("@brief My epic template function.")
        .appendLine("@tparam T Type.")
        .appendLine("@param a Input.")
        .appendLine("@return Negated input.")
    .toggleCStyleComment()
    .appendLine("template<typename T>")
    .appendLine("T unaryNegate(const T &a)")
    .appendLine("{")
    .indent()
        .comment("This is a C++-style comment")
        .appendLine("return -a;")
    .unindent()
    .appendLine("}");

    cg.appendLine();

//    cg.toggleCPPStyleComment();
    {
        ers::FunctionBuilder fb;
        fb
        .makeStatic()
        .makeTemplate()
        .makeTrailingReturn()
        .addTemplateParameter("typename", "T")
        .addTemplateParameter("typename", "U")
        .setDesignator("add")
        .setReturnType("decltype(a + b)")
        .addParameter("T", "a", "0")
        .addParameter("U", "b", "0")
        .setFunctionBody("auto c = a + b; return c;")
        .appendFunction(cg);
    }
//    cg.toggleCPPStyleComment();


    cg.print();
    cg.writeToFile("unaryNegate.hpp");

    ers::ClangFormatter cf;
    cf.IndentWidth = 2;
    cf.dumpFormat();
    cf.invokeClangFormat("unaryNegate.hpp");

    return 0;
}