#ifndef PYTHONEDIT
#define PYTHONEDIT

#include <QSyntaxHighlighter>
#include <QVector>

class PythonHighlighter: public QSyntaxHighlighter  {

    // struct to hold regexp pattern and its corresponding highlight style
    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };

    // collection of all supported highlighting rules
    QVector<HighlightingRule> highlightingRules;

    // actual highlighting happens here
    void highlightBlock(const QString &text) override
    {
        // loop over all known highlighling rules
        for (const HighlightingRule &rule: highlightingRules) {
            const QRegExp &expression(rule.pattern);
            int index = expression.indexIn(text);

            // apply highlighting to all occurences of the pattern
            while (index >= 0) {
                int length = expression.matchedLength();
                setFormat(index, length, rule.format);
                index = expression.indexIn(text, index + length);
            }
        }
    }

public:
    // constructor
    PythonHighlighter(QTextDocument *parent = 0) : QSyntaxHighlighter(parent) {
        // define highlighting rules
        HighlightingRule rule;

        // keywords
        QTextCharFormat keywordFormat;
        keywordFormat.setForeground(Qt::darkBlue);
        keywordFormat.setFontWeight(QFont::Bold);
        QStringList keywordPatterns;
        keywordPatterns << "\\band\\b" << "\\bas\\b" << "\\bassert\\b"
                        << "\\bbreak\\b" << "\\bclass\\b" << "\\bcontinue\\b"
                        << "\\bdef\\b" << "\\bdel\\b" << "\\belif\\b"
                        << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                        << "\\belse\\b" << "\\bexcept\\b" << "\\bexec\\b"
                        << "\\bfinally\\b" << "\\bfor\\b" << "\\bfrom\\b"
                        << "\\bglobal\\b" << "\\bif\\b" << "\\bimport\\b"
                        << "\\bin\\b" << "\\bis\\b" << "\\blambda\\b"
                        << "\\bnot\\b" << "\\bor\\b" << "\\bpass\\b"
                        << "\\bprint\\b" << "\\braise\\b" << "\\breturn\\b"
                        << "\\btry\\b" << "\\bwhile\\b" << "\\bwith\\b"
                        << "\\byield\\b";
        for (const QString &pattern: keywordPatterns) {
            rule.pattern = QRegExp(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        // single-quote character strings
        QTextCharFormat singlequoteFormat;
        singlequoteFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("\".*\"");
        rule.format = singlequoteFormat;
        highlightingRules.append(rule);

        // double-quote character strings
        QTextCharFormat doublequoteFormat;
        doublequoteFormat.setForeground(Qt::darkGreen);
        rule.pattern = QRegExp("\'.*\'");
        rule.format = doublequoteFormat;
        highlightingRules.append(rule);

        // # comments
        QTextCharFormat commentFormat;
        commentFormat.setForeground(Qt::gray);
        rule.pattern = QRegExp("#[^\n]*");
        rule.format = commentFormat;
        highlightingRules.append(rule);
    }
};

#endif // PYTHONEDIT
