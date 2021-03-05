#include "textutils.h"

#include <QColor>
#include <QDebug>
#define EMOJISIZE 24
QSize TextUtils::textSize(int maxTextWidth,QString &text, const QFontMetrics &fm,bool iscontainsemoji,int emojiconut)
{
	int rowHeight = fm.lineSpacing();
    int len = 0;
    int hei = rowHeight;
    QString::const_iterator txtIter = text.begin();
    int rows = 1; // default to 1
    int rowMaxWidth = 0;
    int charWidth = 0;
    int rowWidth = 0;
	int totalWidth = 0;
    bool multiline = false;
	int pos = 0;
    while (txtIter != text.end()) {
		charWidth = txtIter->isSymbol()?EMOJISIZE:fm.width(*txtIter);
		rowHeight = txtIter->isSymbol()?EMOJISIZE:fm.lineSpacing();
		totalWidth+=charWidth;
        len += charWidth;
        rowWidth += charWidth;
        if (len >= maxTextWidth ||*txtIter == '\n') {
            rowMaxWidth = std::max(rowWidth, rowMaxWidth);
            rowWidth = 0;
            multiline = true;
			hei+=rowHeight;
			++rows;
            len = 0;
        }
		++pos;
        ++txtIter;
    }
	 // in case skipped the last longest line
	rowMaxWidth = std::max(rowWidth, rowMaxWidth);
	if (multiline&&(totalWidth%rowMaxWidth))
	{
		hei +=iscontainsemoji?EMOJISIZE:fm.lineSpacing();
	}
    QSize sz(rowMaxWidth,hei); // plus left & right margins
#ifdef QT_DEBUG
    qDebug() << "rows: " << rows;
    qDebug() << "sz : " << sz;
#endif
    return sz;
}

bool TextUtils::singleLine(int maxTextWidth, const QString& text, const QFontMetrics& fm,bool iscontainsemoji)
{
    int len = 0;
    QString::const_iterator txtIter = text.begin();
    int charWidth = 0;
    while (txtIter != text.end()) {
        charWidth = iscontainsemoji?24:fm.width(*txtIter);
        len += charWidth;
        if (len > maxTextWidth || *txtIter == '\n') {
            return false;
        }
        ++txtIter;
    }

    return true;
}

QString TextUtils::textColorStyle(const QColor &clr)
{
    QString style = QString("color: rgb(%1, %2, %3);").arg(clr.red()).arg(clr.green()).arg(clr.blue());
    return style;
}
int  TextUtils::textWidth(int maxTextWidth,QString& text,const QFontMetrics& fm){
	int charWidth = 0;
	int rowMaxWidth = 0;
	int rowWidth = 0;
	int len = 0;
	QString::const_iterator txtIter = text.begin();
	 while (txtIter != text.end()) {
		charWidth = txtIter->isSymbol()?EMOJISIZE:fm.width(*txtIter);
        len += charWidth;
        rowWidth += charWidth;
		if (len >= maxTextWidth ||*txtIter == '\n') {
            rowMaxWidth = std::max(rowWidth, rowMaxWidth);
            rowWidth = 0;
            len = 0;
        }
		++txtIter;
	 }
	 rowMaxWidth = std::max(rowWidth,rowMaxWidth)+10;
	 return rowMaxWidth;
}
