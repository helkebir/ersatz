//
// Created by Hamza El-Kebir on 2/6/22.
//

#include "Codegen.hpp"
#include "FunctionBuilder.hpp"
#include "ClangFormatter.hpp"

int main()
{
    ers::Codegen cg;
    cg.setLang(ers::CodegenLang::Python);

//    cg.toggleCPPStyleComment();
    {
        ers::FunctionBuilder fb;
        fb
                .setLang(ers::CodegenLang::Python)
                .makeStatic()
                .makeTemplate()
                .makeTrailingReturn()
                .addTemplateParameter("typename", "T")
                .addTemplateParameter("typename", "U")
                .setDesignator("add")
                .setReturnType("decltype(a + b)")
                .addParameter("T", "a", "0")
                .addParameter("U", "b", "0")
                .setFunctionBody("c = a + b\nreturn c")
                .appendFunction(cg);
    }
//    cg.toggleCPPStyleComment();


    cg.print();
    cg.writeToFile("unaryNegate.py");
//
//    ers::ClangFormatter cf;
//    cf.IndentWidth = 2;
//    cf.dumpFormat();
//    cf.invokeClangFormat("unaryNegate.hpp");

    return 0;
}