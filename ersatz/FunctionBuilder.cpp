//
// Created by Hamza El-Kebir on 1/4/22.
//

#include "FunctionBuilder.hpp"

ers::FunctionBuilder &ers::FunctionBuilder::makeStatic()
{
    isStatic_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeStatic()
{
    isStatic_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::makeConst()
{
    isConst_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeConst()
{
    isConst_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::makeOverridden()
{
    isOverridden_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeOverridden()
{
    isOverridden_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::makeFinal()
{
    isFinal_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeFinal()
{
    isFinal_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::makeTrailingReturn()
{
    hasTrailingReturn_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeTrailingReturn()
{
    hasTrailingReturn_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::makeMember()
{
    isMember_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeMember()
{
    isMember_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::makeTemplate()
{
    isTemplate_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::unmakeTemplate()
{
    isTemplate_ = false;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::setDesignator(const std::string &designator)
{
    designator_ = designator;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::setReturnType(const std::string &returnType)
{
    returnType_ = returnType;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::setFunctionBody(const std::string &functionBody)
{
    functionBody_ = functionBody;
    hasFunctionBody_ = true;

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::addParameter(const std::string &type, const std::string &identifier,
                                                         const std::string &defaultArg)
{
    parameterList_.emplace_back(type, identifier, defaultArg, lang_);

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::addTemplateParameter(const std::string &type, const std::string &identifier,
                                                                 const std::string &defaultArg)
{
    templateParameterList_.emplace_back(type, identifier, defaultArg, lang_);

    return *this;
}

ers::FunctionBuilder &ers::FunctionBuilder::appendFunction(ers::Codegen &cg)
{
    setLang(cg.lang_);

    ::std::string temp, declaration, body;

    if (lang_ == CodegenLang::Cpp)
        temp = fmt::format("{}",
                           (isTemplate_ ? fmt::format("template<{}>", makeTemplateParameterList()) : ""));

    if (!temp.empty())
        cg.appendLine(temp, false);

    if (lang_ == CodegenLang::Python && isStatic_)
        cg.appendLine("@staticmethod");

    ::std::string declarationTemplate;
    switch (lang_) {
        case CodegenLang::Cpp:
        case CodegenLang::C:
            declarationTemplate = "{}({}){}{}{}";
        case CodegenLang::Python:
            declarationTemplate = "def {}({}):{}{}{}";
    }

    declaration = fmt::format(declarationTemplate,
                              makeDeclarationSpecifierSeq(),
                              makeParameterList(),
                              makeConstVolatileQualification(),
                              makeVirtualSpecifierSeq(),
                              makeTrailing());

    body = fmt::format("{}",
                       (hasFunctionBody_ ? makeFunctionBody() : ""));

    if (body.empty()) {
        switch (lang_) {
            default:
            case CodegenLang::C:
                cg.appendLine(fmt::format("{};", declaration), false);
                break;
            case CodegenLang::Python:
                cg.appendLine(fmt::format("pass", declaration), false);
                break;
        }
    } else {
        switch (lang_) {
            default:
            case CodegenLang::C:
                cg
                        .appendLine(declaration, false)
                        .appendLine("{", false)
                        .indent()
                        .appendLines(functionBody_, false)
                        .unindent()
                        .appendLine("}", false);
                break;
            case CodegenLang::Python:
                cg
                        .appendLine(declaration, false)
                        .indent()
                        .appendLines(functionBody_, false)
                        .unindent();
                break;
        }
    }

    return *this;
}

::std::string ers::FunctionBuilder::makeTemplateParameterList() const
{
    if (templateParameterList_.empty())
        return "";
    else
        return join_(templateParameterList_);
}

::std::string ers::FunctionBuilder::makeDeclarationSpecifierSeq() const
{
    switch (lang_) {
        case CodegenLang::Cpp:
            return fmt::format("{}{}{}",
                               (isStatic_ ? "static " : ""),
                               (hasTrailingReturn_ ? "auto " : fmt::format("{} ", returnType_)),
                               designator_
            );
        case CodegenLang::C:
            return fmt::format("{}{}{}",
                               (isStatic_ ? "static " : ""),
                               fmt::format("{} ", returnType_),
                               designator_
            );
        case CodegenLang::Python:
            return designator_;
    }

    return designator_;
}

::std::string ers::FunctionBuilder::makeParameterList() const
{
    if (parameterList_.empty())
        return "";
    else
        return join_(parameterList_);
}

::std::string ers::FunctionBuilder::makeConstVolatileQualification() const
{
    switch (lang_) {
        case CodegenLang::Cpp:
        case CodegenLang::C:
            return fmt::format("{}{}",
                               (!isStatic_ && isConst_ ? " const" : ""),
                               (!isStatic_ && isVolatile_ ? " volatile" : "")
            );
        default:
            return "";
    }
}

::std::string ers::FunctionBuilder::makeVirtualSpecifierSeq() const
{
    switch (lang_) {
        case CodegenLang::Cpp:
            return fmt::format("{}{}",
                               (!isStatic_ && isOverridden_ ? " override" : ""),
                               (!isStatic_ && isFinal_ ? " final" : "")
            );
        default:
            return "";
    }
}

::std::string ers::FunctionBuilder::makeTrailing() const
{
    switch (lang_) {
        case CodegenLang::Cpp:
            return fmt::format("{}",
                               (hasTrailingReturn_ ? fmt::format(" -> {}", returnType_) : ""));
        default:
            return "";
    }
}

::std::string ers::FunctionBuilder::makeFunctionBody() const
{
    return functionBody_;
}

::std::string ers::FunctionBuilder::join_(const std::vector<Parameter> &params, const ::std::string sep)
{
    ::std::stringstream ss;

    if (!params.empty())
        ss << fmt::format("{}", fmt::join(params, sep));

    return ss.str();
}
