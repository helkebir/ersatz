//
// Created by Hamza El-Kebir on 1/4/22.
//

#include "Codegen.hpp"

int main()
{
    ers::Codegen cg;

    cg
    .toggleCStyleComment()
    .appendUnicodeBox("Here's a box")
    .appendUnicodeThickBox("Here's a thick box")
    .appendUnicodeRoundBox("Here's a round box")
    .appendLine("◉ ▣ ◈")
    .appendLine("◯ □ ◇")
    .appendLine("● ■ ◆")
    .appendMultilineUnicodeBox("I can contain\nmore\nthan\none\nline!")
    .appendMultilineUnicodeThickBox("Me\ntoo!")
    .appendUnicodeLabelBox("Content", "Label")
    .appendMultilineUnicodeLabelBox("Here is a\n~~multiline~~\nblock", "with label!")
    .toggleCStyleComment()
    .appendLine();

    cg
    .appendLine("template<typename T>")
    .appendLine("T unaryNegate(const T &a)")
    .appendLine("{")
    .indent()
        .toggleCStyleComment()
            .appendLine()
            .appendLine("This is a C-style comment")
            .appendLine("Have another line!")
        .toggleCStyleComment()
        .comment("This is a C++-style comment")
        .appendLine("return -a;")
    .unindent()
    .appendLine("}");

    cg.print();

    return 0;
}