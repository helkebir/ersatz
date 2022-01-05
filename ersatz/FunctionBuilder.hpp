//
// Created by Hamza El-Kebir on 1/4/22.
//

#ifndef ERSATZ_FUNCTIONBUILDER_HPP
#define ERSATZ_FUNCTIONBUILDER_HPP

#include <utility>

#include "Codegen.hpp"

namespace ers {
    class FunctionBuilder {
    public:
        struct Parameter {
            Parameter(::std::string type_ = "void", ::std::string identifier_ = "", ::std::string default_ = "") :
                    type(std::move(type_)),
                    identifier(std::move(identifier_)),
                    defaultArg(std::move(default_))
            {}

            ::std::string type = "void";
            ::std::string identifier;
            ::std::string defaultArg;
        };

        FunctionBuilder &makeStatic();

        FunctionBuilder &unmakeStatic();

        FunctionBuilder &makeConst();

        FunctionBuilder &unmakeConst();

        FunctionBuilder &makeOverridden();

        FunctionBuilder &unmakeOverridden();

        FunctionBuilder &makeFinal();

        FunctionBuilder &unmakeFinal();

        FunctionBuilder &makeTrailingReturn();

        FunctionBuilder &unmakeTrailingReturn();

        FunctionBuilder &makeMember();

        FunctionBuilder &unmakeMember();

        FunctionBuilder &makeTemplate();

        FunctionBuilder &unmakeTemplate();

        FunctionBuilder &setDesignator(const ::std::string &designator);

        FunctionBuilder &setReturnType(const ::std::string &returnType);

        FunctionBuilder &setFunctionBody(const ::std::string &functionBody);

        FunctionBuilder &addParameter(const ::std::string &type, const ::std::string &identifier = "",
                                      const ::std::string &defaultArg = "");

        FunctionBuilder &addTemplateParameter(const ::std::string &type, const ::std::string &identifier = "",
                                              const ::std::string &defaultArg = "");

        FunctionBuilder &appendFunction(Codegen &cg);

        // template parameter-list
        ::std::string makeTemplateParameterList() const;

        // decl-specifier-seq
        ::std::string makeDeclarationSpecifierSeq() const;

        // parameter-list
        ::std::string makeParameterList() const;

        // cv
        ::std::string makeConstVolatileQualification() const;

        // virt-specifier-seq
        ::std::string makeVirtualSpecifierSeq() const;

        // -> trailing
        ::std::string makeTrailing() const;

        // function-body
        ::std::string makeFunctionBody() const;


    protected:
        bool isMember_ = false;
        bool isTemplate_ = false;
        bool isStatic_ = false;
        bool isConst_ = false;
        bool isVolatile_ = false;
        bool isOverridden_ = false;
        bool isFinal_ = false;
        bool hasTrailingReturn_ = false;
        bool hasFunctionBody_ = false;

        ::std::string designator_; /// Function designator (identifier by which the function is called).
        ::std::string returnType_ = "auto";
        ::std::string functionBody_;
        ::std::vector<Parameter> parameterList_;
        ::std::vector<Parameter> templateParameterList_;

        static ::std::string join_(const ::std::vector<Parameter> &params, const ::std::string sep = ", ");
    };
}

template<>
struct fmt::formatter<ers::FunctionBuilder::Parameter> {
    // Presentation format: 'f' - fixed, 'e' - exponential.
    char presentation = 'f';

    // Parses format specifications of the form ['f' | 'e'].
    auto parse(format_parse_context &ctx) -> ::std::remove_const<decltype(ctx.begin())>::type
    {
        // [ctx.begin(), ctx.end()) is a character range that contains a part of
        // the format string starting from the format specifications to be parsed,
        // e.g. in
        //
        //   fmt::format("{:f} - point of interest", point{1, 2});
        //
        // the range will contain "f} - point of interest". The formatter should
        // parse specifiers until '}' or the end of the range. In this example
        // the formatter should parse the 'f' specifier and return an iterator
        // pointing to '}'.

        // Parse the presentation format and store it in the formatter:
        auto it = ctx.begin();
        auto end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'e')) presentation = *it++;

        // Check if reached the end of the range:
        if (it != end && *it != '}') throw format_error("invalid format");

        // Return an iterator past the end of the parsed range:
        return it;
    }

    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    template<typename FormatContext>
    auto format(const ers::FunctionBuilder::Parameter &param, FormatContext &ctx) -> decltype(ctx.out())
    {
        // ctx.out() is an output iterator to write to.
        return format_to(ctx.out(),
                         "{} {}{}",
                         param.type,
                         param.identifier,
                         (param.defaultArg == "" ? "" : fmt::format(" = {}", param.defaultArg))
        );
    }
};

#endif //ERSATZ_FUNCTIONBUILDER_HPP
