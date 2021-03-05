#pragma once
#include <QLabel>
class QTextEdit;
namespace uicontrols{
class Tooltip : public QLabel
{
public:
    Tooltip(QWidget *parent = nullptr);
    ~Tooltip();
	static Tooltip *instance;
    void setText(const QString &context);
    static void popup(QPoint pos, const QString &text);
	static void hideTipWnd();
protected:
	void paintEvent(QPaintEvent*event);
	void hideTip();
private:
	int         m_maxtextLenth;
    QTextEdit*  m_content;
};
}