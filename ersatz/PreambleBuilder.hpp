//
// Created by Hamza El-Kebir on 2/7/22.
//

#ifndef ERSATZ_PREAMBLEBUILDER_HPP
#define ERSATZ_PREAMBLEBUILDER_HPP

#include <utility>
#include "Codegen.hpp"

namespace ers {
    class PreambleBuilder {
    public:
        class ImportInfo {
        public:
            friend PreambleBuilder;

            ImportInfo(::std::string name) : name_(std::move(name)), alias_(), subimport_(), angleBrackets_(false)
            {}

            ImportInfo &setName(const ::std::string &name)
            {
                name_ = name;

                return *this;
            }

            ::std::string getName() const
            { return name_; }

            ImportInfo &setAlias(const ::std::string &alias)
            {
                alias_ = alias;

                return *this;
            }

            ::std::string getAlias() const
            { return alias_; }

            ImportInfo &setSubImport(const ::std::string &subimport)
            {
                subimport_ = subimport;

                return *this;
            }

            ::std::string getSubImport() const
            { return subimport_; }

            ImportInfo &setAngleBrackets()
            {
                angleBrackets_ = true;

                return *this;
            }

            ImportInfo &unsetAngleBrackets()
            {
                angleBrackets_ = false;

                return *this;
            }

            bool hasAngleBrackets() const
            { return angleBrackets_; }

        protected:
            ::std::string name_;
            ::std::string alias_;
            ::std::string subimport_;

            bool angleBrackets_ = false;
        };

        ImportInfo &addImport(::std::string name)
        {
            imports_.emplace_back(name);

            return imports_.back();
        }

        bool hasImport(const ::std::string &name) const
        {
            if (imports_.empty())
                return false;

            return ::std::any_of(imports_.begin(), imports_.end(),
                                 [&](const ImportInfo &info) -> bool { return (info.name_ == name); });
        }

        PreambleBuilder &setLang(const CodegenLang lang)
        {
            lang_ = lang;
            traits_.initialize(lang);

            return *this;
        }

        PreambleBuilder &addPreamble(Codegen &cg)
        {
            setLang(cg.getLang());

            for (auto &info: imports_)
                writeInclude(cg, info);

            if (!imports_.empty())
                cg.appendLine();

            return *this;
        }

    protected:
        CodegenLang lang_ = CodegenLang::Cpp;

        ::std::vector<ImportInfo> imports_;

        CodegenLangTraitsDynamic traits_{};

        void writeInclude(Codegen &cg, const ImportInfo &info)
        {
            switch (lang_) {
                case CodegenLang::Cpp:
                case CodegenLang::C:
                    cg.appendLine(fmt::format("#include {}{}{}", (info.angleBrackets_ ? "<" : "\""), info.name_,
                                              (info.angleBrackets_ ? ">" : "\"")));
                    break;
                case CodegenLang::Python:
                    cg.appendLine(fmt::format("{}import {}{}",
                                              (info.subimport_.empty() ? "" : fmt::format("from {} ", info.name_)),
                                              (info.subimport_.empty() ? info.name_ : info.subimport_),
                                              (info.alias_.empty() ? "" : fmt::format(" as {}", info.alias_))));
                    break;
            }
        }
    };
}


#endif //ERSATZ_PREAMBLEBUILDER_HPP
