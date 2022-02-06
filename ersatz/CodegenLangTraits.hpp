//
// Created by Hamza El-Kebir on 2/6/22.
//

#ifndef ERSATZ_CODEGENLANGTRAITS_HPP
#define ERSATZ_CODEGENLANGTRAITS_HPP

#include "CodegenLang.hpp"
#include <string>

namespace ers {
    template<CodegenLang TLang>
    class CodegenLangTraits {

    };

    template<>
    class CodegenLangTraits<CodegenLang::Cpp> {
    public:

        static const CodegenLang lang = CodegenLang::Cpp;

        static ::std::string commentStyle1;

        static ::std::string commentStyle2;
        static ::std::string commentStyle2Open;
        static ::std::string commentStyle2Close;

        static ::std::string docCommentStyle1;

        static ::std::string docCommentStyle2;
        static ::std::string docCommentStyle2Open;
        static ::std::string docCommentStyle2Close;
    };

    template<>
    class CodegenLangTraits<CodegenLang::C> {
    public:

        static const CodegenLang lang = CodegenLang::C;

        static ::std::string commentStyle1;

        static ::std::string commentStyle2;
        static ::std::string commentStyle2Open;
        static ::std::string commentStyle2Close;

        static ::std::string docCommentStyle1;

        static ::std::string docCommentStyle2;
        static ::std::string docCommentStyle2Open;
        static ::std::string docCommentStyle2Close;
    };

    template<>
    class CodegenLangTraits<CodegenLang::Python> {
    public:

        static const CodegenLang lang = CodegenLang::Python;

        static ::std::string commentStyle1;

        static ::std::string commentStyle2;
        static ::std::string commentStyle2Open;
        static ::std::string commentStyle2Close;

        static ::std::string docCommentStyle1;

        static ::std::string docCommentStyle2;
        static ::std::string docCommentStyle2Open;
        static ::std::string docCommentStyle2Close;
    };

    struct CodegenLangTraitsDynamic {
        CodegenLangTraitsDynamic() {
            initialize(CodegenLang::Cpp);
        }

        static CodegenLangTraitsDynamic generate(const CodegenLang lang)
        {
            CodegenLangTraitsDynamic traits;
            traits.initialize(lang);

            return traits;
        }

        void initialize(const CodegenLang lang)
        {
            switch (lang) {
                default: {
                    commentStyle1 = CodegenLangTraits<CodegenLang::Cpp>::commentStyle1;
                    commentStyle2 = CodegenLangTraits<CodegenLang::Cpp>::commentStyle2;
                    commentStyle2Open = CodegenLangTraits<CodegenLang::Cpp>::commentStyle2Open;
                    commentStyle2Close = CodegenLangTraits<CodegenLang::Cpp>::commentStyle2Close;

                    docCommentStyle1 = CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle1;
                    docCommentStyle2 = CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle2;
                    docCommentStyle2Open = CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle2Open;
                    docCommentStyle2Close = CodegenLangTraits<CodegenLang::Cpp>::docCommentStyle2Close;
                    break;
                }
                case CodegenLang::C: {
                    commentStyle1 = CodegenLangTraits<CodegenLang::C>::commentStyle1;
                    commentStyle2 = CodegenLangTraits<CodegenLang::C>::commentStyle2;
                    commentStyle2Open = CodegenLangTraits<CodegenLang::C>::commentStyle2Open;
                    commentStyle2Close = CodegenLangTraits<CodegenLang::C>::commentStyle2Close;

                    docCommentStyle1 = CodegenLangTraits<CodegenLang::C>::docCommentStyle1;
                    docCommentStyle2 = CodegenLangTraits<CodegenLang::C>::docCommentStyle2;
                    docCommentStyle2Open = CodegenLangTraits<CodegenLang::C>::docCommentStyle2Open;
                    docCommentStyle2Close = CodegenLangTraits<CodegenLang::C>::docCommentStyle2Close;
                    break;
                }
                case CodegenLang::Python: {
                    commentStyle1 = CodegenLangTraits<CodegenLang::Python>::commentStyle1;
                    commentStyle2 = CodegenLangTraits<CodegenLang::Python>::commentStyle2;
                    commentStyle2Open = CodegenLangTraits<CodegenLang::Python>::commentStyle2Open;
                    commentStyle2Close = CodegenLangTraits<CodegenLang::Python>::commentStyle2Close;

                    docCommentStyle1 = CodegenLangTraits<CodegenLang::Python>::docCommentStyle1;
                    docCommentStyle2 = CodegenLangTraits<CodegenLang::Python>::docCommentStyle2;
                    docCommentStyle2Open = CodegenLangTraits<CodegenLang::Python>::docCommentStyle2Open;
                    docCommentStyle2Close = CodegenLangTraits<CodegenLang::Python>::docCommentStyle2Close;
                    break;
                }
            }
        }

        ::std::string commentStyle1;

        ::std::string commentStyle2;
        ::std::string commentStyle2Open;
        ::std::string commentStyle2Close;

        ::std::string docCommentStyle1;

        ::std::string docCommentStyle2;
        ::std::string docCommentStyle2Open;
        ::std::string docCommentStyle2Close;
    };
}


#endif //ERSATZ_CODEGENLANGTRAITS_HPP
