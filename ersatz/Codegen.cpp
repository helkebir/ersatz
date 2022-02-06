//
// Created by Hamza El-Kebir on 1/4/22.
//

#include "Codegen.hpp"

ers::Codegen::Codegen(const std::stringstream &ss)
{
    ss_ << ss.str();
}

uint ers::Codegen::getIndentation() const
{
    return indentation_;
}

ers::Codegen &ers::Codegen::setIndentationString(const std::string &indentString)
{
    indentString_ = indentString;

    return *this;
}

::std::string ers::Codegen::getIndentationString() const
{
    return indentString_;
}

uint ers::Codegen::getIndentationMultiplier() const
{
    return indentationMultiplier_;
}

const ::std::stringstream &ers::Codegen::stream() const
{
    return ss_;
}

bool ers::Codegen::isCPPStyleComment() const
{
    return isCPPStyleComment_;
}

ers::Codegen &ers::Codegen::toggleCPPStyleComment(const bool isDocString)
{
    if (!isCPPStyleComment_ && isCStyleComment_)
        toggleCStyleComment();

    isCPPStyleComment_ = !isCPPStyleComment_;
    isDocString_ = isDocString;

    return *this;
}

bool ers::Codegen::isCStyleComment() const
{
    return isCStyleComment_;
}

ers::Codegen &ers::Codegen::toggleCStyleComment(const bool isDocString)
{
    if (isCStyleComment_) {
        closeCStyleComment_ = true;
        appendLine();
    } else
        openCStyleComment_ = true;

    if (!isCStyleComment_)
        isCPPStyleComment_ = false;

    isCStyleComment_ = !isCStyleComment_;
    isDocString_ = isDocString;

    return *this;
}

ers::Codegen &ers::Codegen::comment(const std::string &s)
{
    toggleCPPStyleComment();
    {
        appendLine(s);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeBox(const std::string &s, const uint padding)
{
    appendLine(fmt::format("┌{0:─^{2}}┐", "", 0, s.size() + padding));
    appendLine(fmt::format("│{1: ^{2}}│", "", s, s.size() + padding));
    appendLine(fmt::format("└{0:─^{2}}┘", "", 0, s.size() + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeBox(const std::vector<::std::string> &sv, const uint padding)
{
    uint width = 0;
    for (const auto &s: sv)
        if (s.size() > width)
            width = s.size();

    appendLine(fmt::format("┌{0:─^{2}}┐", "", 0, width + padding));
    for (const auto &s: sv)
        appendLine(fmt::format("│{1: ^{2}}│", "", s, width + padding));
    appendLine(fmt::format("└{0:─^{2}}┘", "", 0, width + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendMultilineUnicodeBox(const std::string &s, const uint padding, const std::string &delim)
{
    auto sv = split(s, delim);
    return appendUnicodeBox(sv, padding);

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeLabelBox(const std::string &s, const std::string &label, const uint padding)
{
    uint width = s.size() > label.size() ? s.size() : label.size();
    appendLine(fmt::format("┌{0:─^{2}}┐", "", 0, label.size() + padding));
    appendLine(fmt::format("│{1: ^{2}}│", "", label, label.size() + padding));
    if (s.size() > label.size())
        appendLine(fmt::format("├{0:─^{2}}┴{0:─^{3}}┐", "", 0, label.size() + padding,
                               width - label.size() - (int) (padding / 2)));
    else
        appendLine(fmt::format("├{0:─^{2}}┤", "", 0, label.size() + padding));
    appendLine(fmt::format("│{1: ^{2}}│", "", s, width + padding));
    appendLine(fmt::format("└{0:─^{2}}┘", "", 0, width + padding));

    return *this;
}

ers::Codegen &
ers::Codegen::appendUnicodeLabelBox(const std::vector<::std::string> &sv, const std::string &label, const uint padding)
{
    uint contentWidth = 0;
    for (const auto &s: sv)
        if (s.size() > contentWidth)
            contentWidth = s.size();

    uint totalWidth = contentWidth > label.size() ? contentWidth : label.size();
    appendLine(fmt::format("┌{0:─^{2}}┐", "", 0, label.size() + padding));
    appendLine(fmt::format("│{1: ^{2}}│", "", label, label.size() + padding));
    if (contentWidth > label.size())
        appendLine(fmt::format("├{0:─^{2}}┴{0:─^{3}}┐", "", 0, label.size() + padding,
                               totalWidth - label.size() - (int) (padding / 2)));
    else
        appendLine(fmt::format("├{0:─^{2}}┤", "", 0, label.size() + padding));
    for (const auto &s: sv)
        appendLine(fmt::format("│{1: ^{2}}│", "", s, totalWidth + padding));
    appendLine(fmt::format("└{0:─^{2}}┘", "", 0, totalWidth + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendMultilineUnicodeLabelBox(const std::string &s, const std::string &label, const uint padding,
                                                  const std::string &delim)
{
    auto sv = split(s, delim);
    return appendUnicodeLabelBox(sv, label, padding);

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeRoundBox(const std::string &s, const uint padding)
{
    appendLine(fmt::format("╭{0:─^{2}}╮", "", 0, s.size() + padding));
    appendLine(fmt::format("│{1: ^{2}}│", "", s, s.size() + padding));
    appendLine(fmt::format("╰{0:─^{2}}╯", "", 0, s.size() + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeRoundBox(const std::vector<::std::string> &sv, const uint padding)
{
    uint width = 0;
    for (const auto &s: sv)
        if (s.size() > width)
            width = s.size();

    appendLine(fmt::format("╭{0:─^{2}}╮", "", 0, width + padding));
    for (const auto &s: sv)
        appendLine(fmt::format("│{1: ^{2}}│", "", s, width + padding));
    appendLine(fmt::format("╰{0:─^{2}}╯", "", 0, width + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendMultilineUnicodeRoundBox(const std::string &s, const uint padding, const std::string &delim)
{
    auto sv = split(s, delim);
    return appendUnicodeRoundBox(sv, padding);

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeThickBox(const std::string &s, const uint padding)
{
    appendLine(fmt::format("╔{0:═^{2}}╗", "", 0, s.size() + padding));
    appendLine(fmt::format("║{1: ^{2}}║", "", s, s.size() + padding));
    appendLine(fmt::format("╚{0:═^{2}}╝", "", 0, s.size() + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeThickBox(const std::vector<::std::string> &sv, const uint padding)
{
    uint width = 0;
    for (const auto &s: sv)
        if (s.size() > width)
            width = s.size();

    appendLine(fmt::format("╔{0:═^{2}}╗", "", 0, width + padding));
    for (const auto &s: sv)
        appendLine(fmt::format("║{1: ^{2}}║", "", s, width + padding));
    appendLine(fmt::format("╚{0:═^{2}}╝", "", 0, width + padding));

    return *this;
}

ers::Codegen &ers::Codegen::appendMultilineUnicodeThickBox(const std::string &s, const uint padding, const std::string &delim)
{
    auto sv = split(s, delim);
    return appendUnicodeThickBox(sv, padding);

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentBox(const std::string &s, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeBox(s, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentBox(const std::vector<::std::string> &sv, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeBox(sv, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendMultilineUnicodeCommentBox(const std::string &s, const uint padding, const std::string &delim)
{
    toggleCPPStyleComment();
    {
        appendMultilineUnicodeBox(s, padding, delim);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentLabelBox(const std::string &s, const std::string &label, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeLabelBox(s, label, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentLabelBox(const std::vector<::std::string> &sv, const std::string &label,
                                                const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeLabelBox(sv, label, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &
ers::Codegen::appendMultilineUnicodeCommentLabelBox(const std::string &s, const std::string &label, const uint padding,
                                                    const std::string &delim)
{
    toggleCPPStyleComment();
    {
        appendMultilineUnicodeLabelBox(s, label, padding, delim);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentRoundBox(const std::string &s, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeRoundBox(s, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentRoundBox(const std::vector<::std::string> &sv, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeRoundBox(sv, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &
ers::Codegen::appendMultilineUnicodeCommentRoundBox(const std::string &s, const uint padding, const std::string &delim)
{
    toggleCPPStyleComment();
    {
        appendMultilineUnicodeRoundBox(s, padding, delim);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentThickBox(const std::string &s, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeThickBox(s, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &ers::Codegen::appendUnicodeCommentThickBox(const std::vector<::std::string> &sv, const uint padding)
{
    toggleCPPStyleComment();
    {
        appendUnicodeThickBox(sv, padding);
    }
    toggleCPPStyleComment();

    return *this;
}

ers::Codegen &
ers::Codegen::appendMultilineUnicodeCommentThickBox(const std::string &s, const uint padding, const std::string &delim)
{
    toggleCPPStyleComment();
    {
        appendMultilineUnicodeThickBox(s, padding, delim);
    }
    toggleCPPStyleComment();

    return *this;
}

::std::vector<::std::string> ers::Codegen::split(const std::string &s, const std::string &delim)
{
    ::std::vector<::std::string> res;

    size_t last = 0;
    size_t next = 0;
    while ((next = s.find(delim, last)) != ::std::string::npos) {
        res.push_back(s.substr(last, next - last));
        last = next + 1;
    }
    res.push_back(s.substr(last));

    return ::std::move(res);
}

void ers::Codegen::comment_()
{
    if (isCStyleComment_ && !(openCStyleComment_ || closeCStyleComment_)) {
        append(traits_.commentStyle2);
    } else if (isCPPStyleComment_) {
        if (isDocString_)
            append(traits_.docCommentStyle1);
        else
            append(traits_.commentStyle1);
    }

    if (openCStyleComment_) {
        openCStyleComment_ = false;
        if (isDocString_)
            append(traits_.docCommentStyle2Open);
        else
            append(traits_.commentStyle2Open);
    } else if (closeCStyleComment_) {
        closeCStyleComment_ = false;
        append(traits_.commentStyle2Close);
    }
}

ers::Codegen &ers::Codegen::writeToFile(const std::string &filePath)
{
    ::std::ofstream f;
    f.open(filePath);
    f << stream().str();
    f.close();

    return *this;
}

ers::Codegen &ers::Codegen::print()
{
    auto s = stream().str();
    fmt::print("{}", s);

    return *this;
}
