//
// Created by Hamza El-Kebir on 1/4/22.
//

#include "ClangFormatter.hpp"

ers::ClangFormatter &ers::ClangFormatter::dumpFormat(const std::string &filePath)
{
    Codegen cg;

    cg.appendLines(fmt::format(
            "---\n"
            "Language:        Cpp\n"
            "# BasedOnStyle:  LLVM\n"
            "AccessModifierOffset: -2\n"
            "AlignAfterOpenBracket: Align\n"
            "AlignConsecutiveMacros: false\n"
            "AlignConsecutiveAssignments: false\n"
            "AlignConsecutiveDeclarations: false\n"
            "AlignEscapedNewlines: Right\n"
            "AlignOperands:   true\n"
            "AlignTrailingComments: true\n"
            "AllowAllArgumentsOnNextLine: true\n"
            "AllowAllConstructorInitializersOnNextLine: true\n"
            "AllowAllParametersOfDeclarationOnNextLine: true\n"
            "AllowShortBlocksOnASingleLine: Never\n"
            "AllowShortCaseLabelsOnASingleLine: false\n"
            "AllowShortFunctionsOnASingleLine: All\n"
            "AllowShortLambdasOnASingleLine: All\n"
            "AllowShortIfStatementsOnASingleLine: Never\n"
            "AllowShortLoopsOnASingleLine: false\n"
            "AlwaysBreakAfterDefinitionReturnType: None\n"
            "AlwaysBreakAfterReturnType: None\n"
            "AlwaysBreakBeforeMultilineStrings: false\n"
            "AlwaysBreakTemplateDeclarations: MultiLine\n"
            "BinPackArguments: true\n"
            "BinPackParameters: true\n"
            "BraceWrapping:\n"
            "  AfterCaseLabel:  false\n"
            "  AfterClass:      false\n"
            "  AfterControlStatement: false\n"
            "  AfterEnum:       false\n"
            "  AfterFunction:   false\n"
            "  AfterNamespace:  false\n"
            "  AfterObjCDeclaration: false\n"
            "  AfterStruct:     false\n"
            "  AfterUnion:      false\n"
            "  AfterExternBlock: false\n"
            "  BeforeCatch:     false\n"
            "  BeforeElse:      false\n"
            "  IndentBraces:    false\n"
            "  SplitEmptyFunction: true\n"
            "  SplitEmptyRecord: true\n"
            "  SplitEmptyNamespace: true\n"
            "BreakBeforeBinaryOperators: None\n"
            "BreakBeforeBraces: {1}\n"
            "BreakBeforeInheritanceComma: false\n"
            "BreakInheritanceList: BeforeColon\n"
            "BreakBeforeTernaryOperators: true\n"
            "BreakConstructorInitializersBeforeComma: false\n"
            "BreakConstructorInitializers: BeforeColon\n"
            "BreakAfterJavaFieldAnnotations: false\n"
            "BreakStringLiterals: true\n"
            "ColumnLimit:     80\n"
            "CommentPragmas:  '^ IWYU pragma:'\n"
            "CompactNamespaces: false\n"
            "ConstructorInitializerAllOnOneLineOrOnePerLine: false\n"
            "ConstructorInitializerIndentWidth: 4\n"
            "ContinuationIndentWidth: 4\n"
            "Cpp11BracedListStyle: true\n"
            "DeriveLineEnding: true\n"
            "DerivePointerAlignment: false\n"
            "DisableFormat:   false\n"
            "ExperimentalAutoDetectBinPacking: false\n"
            "FixNamespaceComments: true\n"
            "ForEachMacros:\n"
            "  - foreach\n"
            "  - Q_FOREACH\n"
            "  - BOOST_FOREACH\n"
            "IncludeBlocks:   Preserve\n"
            "IncludeCategories:\n"
            "  - Regex:           '^\"(llvm|llvm-c|clang|clang-c)/'\n"
            "    Priority:        2\n"
            "    SortPriority:    0\n"
            "  - Regex:           '^(<|\"(gtest|gmock|isl|json)/)'\n"
            "    Priority:        3\n"
            "    SortPriority:    0\n"
            "  - Regex:           '.*'\n"
            "    Priority:        1\n"
            "    SortPriority:    0\n"
            "IncludeIsMainRegex: '(Test)?$'\n"
            "IncludeIsMainSourceRegex: ''\n"
            "IndentCaseLabels: false\n"
            "IndentGotoLabels: true\n"
            "IndentPPDirectives: None\n"
            "IndentWidth:     {0}\n"
            "IndentWrappedFunctionNames: false\n"
            "JavaScriptQuotes: Leave\n"
            "JavaScriptWrapImports: true\n"
            "KeepEmptyLinesAtTheStartOfBlocks: true\n"
            "MacroBlockBegin: ''\n"
            "MacroBlockEnd:   ''\n"
            "MaxEmptyLinesToKeep: 1\n"
            "NamespaceIndentation: None\n"
            "ObjCBinPackProtocolList: Auto\n"
            "ObjCBlockIndentWidth: 2\n"
            "ObjCSpaceAfterProperty: false\n"
            "ObjCSpaceBeforeProtocolList: true\n"
            "PenaltyBreakAssignment: 2\n"
            "PenaltyBreakBeforeFirstCallParameter: 19\n"
            "PenaltyBreakComment: 300\n"
            "PenaltyBreakFirstLessLess: 120\n"
            "PenaltyBreakString: 1000\n"
            "PenaltyBreakTemplateDeclaration: 10\n"
            "PenaltyExcessCharacter: 1000000\n"
            "PenaltyReturnTypeOnItsOwnLine: 60\n"
            "PointerAlignment: Right\n"
            "ReflowComments:  true\n"
            "SortIncludes:    true\n"
            "SortUsingDeclarations: true\n"
            "SpaceAfterCStyleCast: false\n"
            "SpaceAfterLogicalNot: false\n"
            "SpaceAfterTemplateKeyword: true\n"
            "SpaceBeforeAssignmentOperators: true\n"
            "SpaceBeforeCpp11BracedList: false\n"
            "SpaceBeforeCtorInitializerColon: true\n"
            "SpaceBeforeInheritanceColon: true\n"
            "SpaceBeforeParens: ControlStatements\n"
            "SpaceBeforeRangeBasedForLoopColon: true\n"
            "SpaceInEmptyBlock: false\n"
            "SpaceInEmptyParentheses: false\n"
            "SpacesBeforeTrailingComments: 1\n"
            "SpacesInAngles:  false\n"
            "SpacesInConditionalStatement: false\n"
            "SpacesInContainerLiterals: true\n"
            "SpacesInCStyleCastParentheses: false\n"
            "SpacesInParentheses: false\n"
            "SpacesInSquareBrackets: false\n"
            "SpaceBeforeSquareBrackets: false\n"
            "Standard:        Latest\n"
            "StatementMacros:\n"
            "  - Q_UNUSED\n"
            "  - QT_REQUIRE_VERSION\n"
            "TabWidth:        8\n"
            "UseCRLF:         false\n"
            "UseTab:          Never\n"
            "...",
            IndentWidth,
            BreakBeforeBraces
    ));

    cg.writeToFile(filePath);

    return *this;
}

ers::ClangFormatter &ers::ClangFormatter::invokeClangFormat(const std::string &filePath)
{
    if (system("which clang-format > /dev/null 2>&1")) {

    } else {
        auto s = fmt::format("clang-format -i {}", filePath);
        ::std::system(s.c_str());
    }

    return *this;
}

template<typename... T>
ers::ClangFormatter &ers::ClangFormatter::invokeClangFormat(const std::string &filePath, const T &... filePaths)
{
    if (system("which clang-format > /dev/null 2>&1")) {

    } else {
        invokeClangFormat(filePath);
        invokeClangFormat(filePaths...);
    }

    return *this;
}
