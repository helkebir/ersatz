//
// Created by Hamza El-Kebir on 2/7/22.
//

#ifndef ERSATZ_VARIABLEBUILDER_HPP
#define ERSATZ_VARIABLEBUILDER_HPP

#include "Codegen.hpp"
#include <utility>
#include <cassert>

namespace ers {
    class VariableBuilder {
    public:
        class VariableInfo {
        public:
            friend VariableBuilder;

            VariableInfo(::std::string designator) : designator_(std::move(designator)), value_(), type_(),
                                                     isStatic_(false), isConst_(false)
            {}

            VariableInfo &setDesignator(const ::std::string &designator)
            {
                designator_ = designator;

                return *this;
            }

            ::std::string getDesignator() const
            { return designator_; }

            VariableInfo &setValue(const ::std::string &value)
            {
                value_ = value;

                return *this;
            }

            ::std::string getValue() const
            { return value_; }

            VariableInfo &clearValue()
            {
                value_ = "";

                return *this;
            }

            VariableInfo &setType(const ::std::string &type)
            {
                type_ = type;

                return *this;
            }

            ::std::string getType() const
            { return type_; }

            VariableInfo &clearType()
            {
                type_ = "";

                return *this;
            }

            VariableInfo &makeStatic()
            {
                isStatic_ = true;

                return *this;
            }

            VariableInfo &unmakeStatic()
            {
                isStatic_ = false;

                return *this;
            }

            bool isStatic() const
            { return isStatic_; }

            VariableInfo &makeConst()
            {
                isConst_ = true;

                return *this;
            }

            VariableInfo &unmakeConst()
            {
                isConst_ = false;

                return *this;
            }

            bool isConst() const
            { return isConst_; }

        protected:
            ::std::string designator_, value_, type_;
            bool isStatic_, isConst_;
        };

        VariableBuilder &setLang(const CodegenLang lang)
        {
            lang_ = lang;
            traits_.initialize(lang);

            return *this;
        }

        bool hasVariable(const ::std::string &designator) const
        {
            if (variables_.empty())
                return false;

            return ::std::any_of(variables_.begin(), variables_.end(),
                                 [&](const VariableInfo &info) -> bool { return (info.designator_ == designator); });
        }

        VariableInfo &addVariable(const ::std::string &designator)
        {
            variables_.emplace_back(designator);

            assert(hasVariable(designator) && "Multiple declaration of variable.");

            return variables_.back();
        }

        VariableInfo &
        addMatrix(const ::std::string &designator, const int rows, const int cols,
                  const ::std::string &scalarType = "float")
        {
            addVariable(designator);

            switch (lang_) {
                default:
                    break;
                case CodegenLang::Cpp:
                    variables_.back().type_ = fmt::format("Eigen::Matrix<{}, {}, {}>", scalarType, rows, cols);
                    break;
                case CodegenLang::Python:
                    variables_.back().value_ = fmt::format("np.empty([{}, {}], dtype={})", rows, cols, scalarType);
                    break;
            }

            return variables_.back();
        }

        VariableInfo &
        addVector(const ::std::string &designator, const int rows, const ::std::string &scalarType = "float")
        {
            addVariable(designator);

            switch (lang_) {
                default:
                    break;
                case CodegenLang::Cpp:
                    variables_.back().type_ = fmt::format("Eigen::Vector<{}, {}>", scalarType, rows);
                    break;
                case CodegenLang::Python:
                    variables_.back().value_ = fmt::format("np.empty([{}, 1], dtype={})", rows, scalarType);
                    break;
            }

            return variables_.back();
        }

        VariableBuilder &appendVariables(Codegen &cg)
        {
            setLang(cg.getLang());

            for (auto &info: variables_)
                writeVariable(cg, info);

            if (!variables_.empty())
                cg.appendLine();

            return *this;
        }


    protected:
        CodegenLang lang_ = CodegenLang::Cpp;

        ::std::vector<VariableInfo> variables_;

        CodegenLangTraitsDynamic traits_{};

        VariableBuilder &
        writeVariable(Codegen &cg, const VariableInfo &info)
        {
            switch (lang_) {
                case CodegenLang::Cpp:
                case CodegenLang::C:
                    if (info.value_.empty())
                        cg.appendLine(
                                fmt::format("{}{}{} {};", (info.isStatic_ ? "static " : ""),
                                            (info.isConst_ ? "const " : ""), info.type_,
                                            info.designator_));
                    else
                        cg.appendLine(
                                fmt::format("{}{}{} {} = {};", (info.isStatic_ ? "static " : ""),
                                            (info.isConst_ ? "const " : ""),
                                            info.type_, info.designator_, info.value_));
                    break;
                case CodegenLang::Python:
                    if (info.value_.empty())
                        cg.appendLine(fmt::format("{}", info.designator_));
                    else
                        cg.appendLine(fmt::format("{} = {}", info.designator_, info.value_));
                    break;
            }

            return *this;
        }
    };
}


#endif //ERSATZ_VARIABLEBUILDER_HPP
