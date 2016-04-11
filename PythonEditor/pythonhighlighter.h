#ifndef PYTHONEDIT
#define PYTHONEDIT

#include <QSyntaxHighlighter>

class PythonHighlighter: public QSyntaxHighlighter  {

    // inherit constructors
    using QSyntaxHighlighter::QSyntaxHighlighter;

    // based on example from Qt documentation
    void highlightBlock(const QString &text) override
    {
        QTextCharFormat myClassFormat;
        myClassFormat.setFontWeight(QFont::Bold);
        myClassFormat.setForeground(Qt::darkMagenta);
        QString pattern = "\\bfor\\b|\\bin\\b|\\bprint\\b";

        QRegExp expression(pattern);
        int index = text.indexOf(expression);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, myClassFormat);
            index = text.indexOf(expression, index + length);
        }
    }
};

#endif // PYTHONEDIT

