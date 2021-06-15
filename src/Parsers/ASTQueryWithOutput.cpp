#include <Parsers/ASTQueryWithOutput.h>

namespace DB
{

void ASTQueryWithOutput::cloneOutputOptions(ASTQueryWithOutput & cloned) const
{
    if (out_file)
    {
        cloned.out_file = out_file->clone();
        cloned.children.push_back(cloned.out_file);
    }
    if (format)
    {
        cloned.format = format->clone();
        cloned.children.push_back(cloned.format);
    }
}

void ASTQueryWithOutput::formatImpl(const FormatSettings & s, FormatState & state, FormatStateStacked frame) const
{
    formatQueryImpl(s, state, frame);

    std::string indent_str = s.one_line ? "" : std::string(4u * frame.indent, ' ');

    if (out_file)
    {
        s.ostr << (s.hilite ? hilite_keyword : "") << s.nl_or_ws << indent_str << "INTO OUTFILE " << (s.hilite ? hilite_none : "");
        out_file->formatImpl(s, state, frame);
    }

    if (format)
    {
        const auto * format_ast = format->as<ASTFormatWithSettings>();
        s.ostr << (s.hilite ? hilite_keyword : "") << s.nl_or_ws << indent_str << "FORMAT " << (s.hilite ? hilite_none : "");
        format_ast->name->formatImpl(s, state, frame);

        if (format_ast->settings)
        {
            s.ostr << (s.hilite ? hilite_keyword : "") << s.nl_or_ws << indent_str << "SETTINGS " << (s.hilite ? hilite_none : "");
            format_ast->settings->formatImpl(s, state, frame);
        }
    }
}

bool ASTQueryWithOutput::resetOutputASTIfExist(IAST & ast)
{
    /// FIXME: try to prettify this cast using `as<>()`
    if (auto * ast_with_output = dynamic_cast<ASTQueryWithOutput *>(&ast))
    {
        ast_with_output->format.reset();
        ast_with_output->out_file.reset();
        return true;
    }

    return false;
}


}
