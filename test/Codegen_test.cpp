//
// Created by Hamza El-Kebir on 1/4/22.
//

#include "catchOnce.hpp"
#include "Codegen.hpp"

TEST_CASE("Codegen: comments")
{
    ers::Codegen cg;

    SECTION("C-style") {
        cg.toggleCStyleComment();
        cg.appendText("This is a C-style comment");
        cg.toggleCStyleComment();

        // NOTE: The dangling linebreak for "*/" is by design.
        auto s = cg.stream().str();
        REQUIRE(s == "/* This is a C-style comment */\n");
    }

    SECTION("C++-style") {
        cg.toggleCPPStyleComment();
        cg.appendText("This is a C++-style comment");
        cg.toggleCPPStyleComment();

        auto s = cg.stream().str();
        REQUIRE(s == "// This is a C++-style comment");
    }

    SECTION("C-style multiline") {
        cg.toggleCStyleComment();
        cg.appendLine("This is a C-style comment");
        cg.appendLine("This is a C-style comment");
        cg.toggleCStyleComment();

        // NOTE: The dangling linebreak for "*/" is by design.
        auto s = cg.stream().str();
        REQUIRE(s == "/* This is a C-style comment\n"
                     " * This is a C-style comment\n"
                     " */\n");
    }

    SECTION("C++-style multiline") {
        cg.toggleCPPStyleComment();
        cg.appendLine("This is a C++-style comment");
        cg.appendLine("This is a C++-style comment");
        cg.toggleCPPStyleComment();

        auto s = cg.stream().str();
        REQUIRE(s == "// This is a C++-style comment\n"
                     "// This is a C++-style comment\n");
    }
}

TEST_CASE("Codegen: indentation")
{
    ers::Codegen cg;

    SECTION("Default indentation") {
        cg.appendLine("a");
        cg.indent();
        cg.appendLine("b");
        cg.unindent();
        cg.appendText("c");

        auto s = cg.stream().str();
        REQUIRE(s == "a\n"
                     "    b\n"
                     "c");
    }

    SECTION("Default indentation") {
        cg.appendLine("a");
        cg.indent();
        cg.appendLine("b");
        cg.unindent();
        cg.appendText("c");

        auto s = cg.stream().str();
        REQUIRE(s == "a\n"
                     "    b\n"
                     "c");
    }

    SECTION("Custom indentation length") {
        cg.setIndentationMultiplier(2);
        cg.appendLine("a");
        cg.indent();
        cg.appendLine("b");
        cg.unindent();
        cg.appendLine("c");
        cg.setIndentationMultiplier(6);
        cg.indent();
        cg.appendText("d");

        auto s = cg.stream().str();
        REQUIRE(s == "a\n"
                     "  b\n"
                     "c\n"
                     "      d");
    }

    SECTION("Custom indentation length") {
        cg.setIndentation(1);
        cg.appendLine("a");
        cg.indent();
        cg.appendLine("b");
        cg.setIndentation(0);
        cg.appendText("c");

        auto s = cg.stream().str();
        REQUIRE(s == "    a\n"
                     "        b\n"
                     "c");
    }
}