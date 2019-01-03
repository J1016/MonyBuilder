#ifndef MONYSYNTAXHIGHLIGHTER_H
#define MONYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

struct HighlighterRule
{
    QRegExp pattern;
    QTextCharFormat format;
};

class CMonySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CMonySyntaxHighlighter(QTextDocument * pParent = 0);
    virtual ~CMonySyntaxHighlighter();

protected:
    void highlightBlock(const QString & text) Q_DECL_OVERRIDE;

private:
    QVector<HighlighterRule> m_highlighterRules;

    QRegExp m_commentStartExpression;
    QRegExp m_commentEndExpression;

    QTextCharFormat singleLineKey;
    QTextCharFormat singleLineValue;

    QTextCharFormat m_multiLineCommentFormat;



};
#endif // MONYSYNTAXHIGHLIGHTER_H
