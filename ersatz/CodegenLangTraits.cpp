//
// Created by Hamza El-Kebir on 2/6/22.
//

#include "CodegenLangTraits.hpp"

namespace ers {
    // Cpp
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::commentStyle1 = "// ";
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle1 = "/// ";

    ::std::string CodegenLangTraits<CodegenLang::Cpp>::commentStyle2 = " * ";
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::commentStyle2Open = "/* ";
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::commentStyle2Close = " */";
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle2 = " * ";
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle2Open = "/** ";
    ::std::string CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle2Close = " */";

    // C
    ::std::string CodegenLangTraits<CodegenLang::C>::commentStyle1 = "// ";
    ::std::string CodegenLangTraits<CodegenLang::C>::docCommentStyle1 = "/// ";

    ::std::string CodegenLangTraits<CodegenLang::C>::commentStyle2 = " * ";
    ::std::string CodegenLangTraits<CodegenLang::C>::commentStyle2Open = "/* ";
    ::std::string CodegenLangTraits<CodegenLang::C>::commentStyle2Close = " */";
    ::std::string CodegenLangTraits<CodegenLang::C>::docCommentStyle2 = " * ";
    ::std::string CodegenLangTraits<CodegenLang::C>::docCommentStyle2Open = "/** ";
    ::std::string CodegenLangTraits<CodegenLang::C>::docCommentStyle2Close = " */";

    // Python
    ::std::string CodegenLangTraits<CodegenLang::Python>::commentStyle1 = "# ";
    ::std::string CodegenLangTraits<CodegenLang::Python>::docCommentStyle1 = "# ";

    ::std::string CodegenLangTraits<CodegenLang::Python>::commentStyle2 = "";
    ::std::string CodegenLangTraits<CodegenLang::Python>::commentStyle2Open = R"(""")";
    ::std::string CodegenLangTraits<CodegenLang::Python>::commentStyle2Close = R"(""")";
    ::std::string CodegenLangTraits<CodegenLang::Python>::docCommentStyle2 = "";
    ::std::string CodegenLangTraits<CodegenLang::Python>::docCommentStyle2Open = R"(""")";
    ::std::string CodegenLangTraits<CodegenLang::Python>::docCommentStyle2Close = R"(""")";
}