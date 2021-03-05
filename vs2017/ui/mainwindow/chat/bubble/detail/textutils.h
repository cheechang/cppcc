#ifndef TEXTUTILS_H
#define TEXTUTILS_H

#include <QFontMetrics>

class TextUtils
{
public:
    static QSize textSize(int maxTextWidth, QString& text, const QFontMetrics& fm,bool iscontainsemoji=false,int emojiconut=0);
    static bool singleLine(int maxTextWidth, const QString& text, const QFontMetrics& fm,bool iscontainsemoji=false);
    static QString textColorStyle(const QColor& clr);
	static int    textWidth(int maxTextWidth,QString& text,const QFontMetrics& fm);
};

#endif // TEXTUTILS_H
