#include "darkhighlighting.h"

darkHighlighting::darkHighlighting(QTextDocument *parent)
    : QSyntaxHighlighter{parent}
{
    m_lstKeywords << "int" << "float" << "char" << "string" << "double"
             << "class" << "for" << "if" << "while" << "do" << "break"
             << "virtual" << "this" << "else" << "delete" << "case"
             << "switch" << "new" << "protected" << "private" << "public"
             << "bool" << "true" << "false" << "return" << "using"
             << "namespace" << "throw" << "void" << "struct" << "const"
             << "mutable";
}

void darkHighlighting::highlightBlock(const QString& str){
    int nState = previousBlockState();
    int nStart = 0;
    for(int i = 0; i < str.size(); i++){
        setFormat(i, 1, "#ffffff");
        if(nState == insideCStyleComment){
            if(str.mid(i, 2) == "*/"){
                nState = normalState;
                setFormat(nStart, i - nStart + 2, "#777777");
                i++;
            }
        }
        else if(nState == insideCString){
            if(str.mid(i, 1) == "\"" || str.mid(i, 1) == "\'"){
                if(str.mid(i - 1, 2) != "\\\"" || str.mid(i - 1, 2) != "\\\'"){
                    nState = normalState;
                    setFormat(nStart, i - nStart + 1, "#e7db74");
                }
            }
        }
        else{
            if(str.mid(i, 2) == "//"){
                setFormat(i, str.size() - i, "#777777");
                break;
            }else if(str.mid(i, 1) == "#"){
                setFormat(i, str.size() - i, "#f92472");
                break;
            }else if(str.at(i).isNumber()){
                setFormat(i, 1, "#ac80ff");
            }else if(str.mid(i, 2) == "/*"){
                nState = insideCStyleComment;
                nStart = i;
            }else if(str.mid(i, 1) == "\"" || str.mid(i, 1) == "\'"){
                nState = insideCString;
                nStart = i;
            }
            else{
                QString strKeyWord = getKeyword(i, str);
                if(i != 0){
                    if(!strKeyWord.isEmpty() && !str.at(i - 1).isLetterOrNumber()){
                        setFormat(i, strKeyWord.length(), "#67d8ef");
                        i+=strKeyWord.length() - 1;
                    }
                }else if(!strKeyWord.isEmpty()){
                    setFormat(i, strKeyWord.length(), "#67d8ef");
                    i+=strKeyWord.length() - 1;
                }
            }
        }
    }
    if(nState == insideCString){
        setFormat(nStart, str.length() - nStart, "#e7db74");
    }
    if(nState == insideCStyleComment){
        setFormat(nStart, str.length() - nStart, "#777777");
    }
    setCurrentBlockState(nState);
}

QString darkHighlighting::getKeyword(int nPos, const QString& str) const{
    QString strTemp("");
    foreach(QString keyWord, m_lstKeywords){
        if(str.mid(nPos, keyWord.length()) == keyWord){
            strTemp = keyWord;
            return strTemp;
        }
    }

    return strTemp;
}
