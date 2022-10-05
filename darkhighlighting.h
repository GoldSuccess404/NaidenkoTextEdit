#ifndef DARKHIGHLIGHTING_H
#define DARKHIGHLIGHTING_H

#include <QSyntaxHighlighter>

class darkHighlighting : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit darkHighlighting(QTextDocument *parent = nullptr);
private:
    QStringList m_lstKeywords;
protected:
    enum{normalState = -1, insideCStyleComment, insideCString};
    virtual void highlightBlock(const QString& str);
    QString getKeyword(int nPos, const QString& str) const;
};

#endif // DARKHIGHLIGHTING_H
