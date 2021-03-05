#pragma once
#include <QWidget>
class QPainter;
class QVBoxLayout;
class QProgressBar;
class QLabel;
namespace ui{
	class ToolButton;
class LeftWidget : public QWidget
{
	Q_OBJECT
public:
	explicit LeftWidget(QWidget *parent = 0);
	~LeftWidget();
	void SetMySelfBtnSelected();
signals:
	void singalSelfBtnClicked();
	void signalShareBtnClicked();
protected slots:
	void onSelfBtnClicked();
	void onShareBtnClicked();
	void onSpaceInfo(QString&foldername,QString&size,int&proval);
protected:
	void paintEvent(QPaintEvent *event);
private:
	ToolButton* m_myselfbtn;
	ToolButton* m_sharebtn;
	QProgressBar* m_progressbar;
	QLabel*       m_sizeLabel;
	QLabel*       m_sizeTipLabel;
	QVBoxLayout*  m_hlayout;
	QVBoxLayout* m_mainLayout;
};
}


