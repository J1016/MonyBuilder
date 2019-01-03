#include "MonySyntaxHighlighter.h"

//
//构造函数 : 构造一个 CMonySyntaxHighlighter
//
CMonySyntaxHighlighter::CMonySyntaxHighlighter(QTextDocument * pParent)
    : QSyntaxHighlighter(pParent)
{
    HighlighterRule rule;
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";

    foreach (const QString & pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        m_highlighterRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    m_highlighterRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    m_highlighterRules.append(rule);

    m_multiLineCommentFormat.setForeground(Qt::red);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    m_highlighterRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    QStringList functionPatterns;
    functionPatterns << "\\bmony_trace\\b" << "\\mony_clear_http_param_map\\b"
                     << "\\mony_date_milli\\b" << "\\mony_invoke\\b"
                     << "\\mony_sericode\\b" << "\\mony_array_get\\b"
                     << "\\mony_array_length\\b" << "\\mony_input_vercode\\b"
                     << "\\mony_fixed_gain_mouse_pwd\\b" << "\\mony_load_durable_param\\b"
                     << "\\mony_save_durable_param\\b" << "\\mony_get_global_param\\b"
                     << "\\mony_set_global_param\\b" << "\\mony_set_http_param\\b"
                     << "\\mony_get_http_response\\b" << "\\mony_get_http_response_merge\\b"
                     << "\\mony_get_http_response_total\\b" << "\\mony_http_get_file\\b"
                     << "\\mony_http_post_file\\b" << "\\mony_http_get\\b"
                     << "\\mony_http_options\\b" << "\\mony_http_post\\b"
                     << "\\mony_http_post_ext\\b" << "\\mony_math_random_double\\b"
                     << "\\mony_math_random_double_value\\b" << "\\mony_math_random_int\\b"
                     << "\\mony_math_random_int_value\\b" << "\\mony_math_random_string\\b"
                     << "\\mony_string_equals\\b" << "\\mony_string_cut\\b"
                     << "\\mony_string_find_line\\b" << "\\mony_string_replace\\b"
                     << "\\mony_string_url_encp1\\b" << "\\mony_string_url_encp2\\b"
                     << "\\mony_string_url_encp3\\b" << "\\mony_string_gain_file_name\\b"
                     << "\\mony_rect_limit\\b" << "\\mony_homepage_callback\\b"
                     << "\\mony_run_js\\b" << "\\mony_match_template\\b"
                     << "\\mony_sleep\\b";

    foreach (const QString & pattern, functionPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = functionFormat;
        m_highlighterRules.append(rule);
    }

    m_commentStartExpression = QRegExp("/\\*");
    m_commentEndExpression = QRegExp("\\*/");
}

//
//析构函数 : 释放一个 CMonySyntaxHighlighter
//
CMonySyntaxHighlighter::~CMonySyntaxHighlighter()
{
}

void CMonySyntaxHighlighter::highlightBlock(const QString & text)
{
    foreach (const HighlighterRule & rule, m_highlighterRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        startIndex = m_commentStartExpression.indexIn(text);
    }

    while (startIndex >= 0)
    {
        int endIndex = m_commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex
                    + m_commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, m_multiLineCommentFormat);
        startIndex = m_commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
