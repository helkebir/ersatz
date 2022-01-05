//
// Created by Hamza El-Kebir on 1/4/22.
//

#ifndef ERSATZ_CODEGEN_HPP
#define ERSATZ_CODEGEN_HPP

#define FMT_HEADER_ONLY

#include <fmt/core.h>

#include <utility>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

namespace ers {
    class Codegen {
    public:
        Codegen() = default;

        Codegen(const ::std::stringstream &ss);

        inline Codegen &append(const ::std::string &s)
        {
            ss_ << s;

            return *this;
        }

        inline Codegen &newLine()
        {
            ss_ << "\n";

            return *this;
        }

        inline Codegen &appendText(const ::std::string &s = "", bool indentFirst = true)
        {
            if (indentFirst) {
                append(indent_);
                comment_();
            } else {
                comment_();
                append(indent_);
            }

            append(s);

            return *this;
        }

        inline Codegen &appendLine(const ::std::string &s = "", bool indentFirst = true)
        {
            appendText(s, indentFirst);
            newLine();

            return *this;
        }

        inline Codegen &appendLines(const ::std::string &s = "", bool indentFirst = true)
        {
            auto lines = split(s);
            for (const auto &line: lines)
                appendLine(line, indentFirst);

            return *this;
        }

        inline Codegen &setIndentation(uint indentation)
        {
            indentation_ = indentation;
            indent_ = fmt::format("{0: <{1}}", "", (indentation_ * indentationMultiplier_));

            return *this;
        }

        uint getIndentation() const;

        Codegen &setIndentationString(const ::std::string &indentString);

        ::std::string getIndentationString() const;

        inline Codegen &setIndentationMultiplier(uint indentationMultiplier)
        {
            indentationMultiplier_ = indentationMultiplier;
            setIndentation(indentation_);

            return *this;
        }

        uint getIndentationMultiplier() const;

        inline Codegen &indent()
        {
            setIndentation(indentation_ + 1);

            return *this;
        }

        inline Codegen &unindent()
        {
            setIndentation(indentation_ - 1 < 0 ? 0 : indentation_ - 1);

            return *this;
        }

        const ::std::stringstream &stream() const;

        bool isCPPStyleComment() const;

        Codegen &toggleCPPStyleComment(bool isDocString = false);

        bool isCStyleComment() const;

        Codegen &toggleCStyleComment(bool isDocString = false);

        Codegen &comment(const ::std::string &s);

        Codegen &appendUnicodeBox(const ::std::string &s, uint padding = 2);

        Codegen &appendUnicodeBox(const ::std::vector<::std::string> &sv, uint padding = 2);

        Codegen &
        appendMultilineUnicodeBox(const ::std::string &s, uint padding = 2, const ::std::string &delim = "\n");

        Codegen &appendUnicodeLabelBox(const ::std::string &s, const ::std::string &label, uint padding = 2);

        Codegen &
        appendUnicodeLabelBox(const ::std::vector<::std::string> &sv, const ::std::string &label, uint padding = 2);

        Codegen &appendMultilineUnicodeLabelBox(const ::std::string &s, const ::std::string &label, uint padding = 2,
                                                const ::std::string &delim = "\n");

        Codegen &appendUnicodeRoundBox(const ::std::string &s, uint padding = 2);

        Codegen &appendUnicodeRoundBox(const ::std::vector<::std::string> &sv, uint padding = 2);

        Codegen &
        appendMultilineUnicodeRoundBox(const ::std::string &s, uint padding = 2, const ::std::string &delim = "\n");

        Codegen &appendUnicodeThickBox(const ::std::string &s, uint padding = 2);

        Codegen &appendUnicodeThickBox(const ::std::vector<::std::string> &sv, uint padding = 2);

        Codegen &
        appendMultilineUnicodeThickBox(const ::std::string &s, uint padding = 2, const ::std::string &delim = "\n");

        Codegen &appendUnicodeCommentBox(const ::std::string &s, uint padding = 2);

        Codegen &appendUnicodeCommentBox(const ::std::vector<::std::string> &sv, uint padding = 2);

        Codegen &
        appendMultilineUnicodeCommentBox(const ::std::string &s, uint padding = 2, const ::std::string &delim = "\n");

        Codegen &appendUnicodeCommentLabelBox(const ::std::string &s, const ::std::string &label, uint padding = 2);

        Codegen &appendUnicodeCommentLabelBox(const ::std::vector<::std::string> &sv, const ::std::string &label,
                                              uint padding = 2);

        Codegen &
        appendMultilineUnicodeCommentLabelBox(const ::std::string &s, const ::std::string &label, uint padding = 2,
                                              const ::std::string &delim = "\n");

        Codegen &appendUnicodeCommentRoundBox(const ::std::string &s, uint padding = 2);

        Codegen &appendUnicodeCommentRoundBox(const ::std::vector<::std::string> &sv, uint padding = 2);

        Codegen &appendMultilineUnicodeCommentRoundBox(const ::std::string &s, uint padding = 2,
                                                       const ::std::string &delim = "\n");

        Codegen &appendUnicodeCommentThickBox(const ::std::string &s, uint padding = 2);

        Codegen &appendUnicodeCommentThickBox(const ::std::vector<::std::string> &sv, uint padding = 2);

        Codegen &appendMultilineUnicodeCommentThickBox(const ::std::string &s, uint padding = 2,
                                                       const ::std::string &delim = "\n");

        Codegen &writeToFile(const ::std::string &filePath);

        Codegen &print();

        static ::std::vector<::std::string> split(const ::std::string &s, const ::std::string &delim = "\n");

    protected:
        void comment_();

        ::std::stringstream ss_;

        ::std::string indent_;
        ::std::string indentString_ = " ";
        uint indentation_ = 0;
        uint indentationMultiplier_ = 4;

        bool isCStyleComment_ = false; /**/
        bool openCStyleComment_ = false;
        bool closeCStyleComment_ = false;

        bool isCPPStyleComment_ = false; //

        bool isDocString_ = false;
    };
}


#endif //ERSATZ_CODEGEN_HPP
