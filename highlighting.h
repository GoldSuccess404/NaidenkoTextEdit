#ifndef HIGHLIGHTING_H
#define HIGHLIGHTING_H

#include <QSyntaxHighlighter>
class highlighting : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit highlighting(QTextDocument *parent = nullptr);
private:
    QStringList m_lstKeywords;
protected:
    enum{normalState = -1, insideCStyleComment, insideCString};
    virtual void highlightBlock(const QString& str);
    QString getKeyword(int nPos, const QString& str) const;
};

#endif // HIGHLIGHTING_H
