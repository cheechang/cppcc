#pragma once
#include <QWidget>
class QPainter;
class QMovie;
class QLabel;
class QVBoxLayout;
namespace ui{
class DefaultWidget : public QWidget
{
	Q_OBJECT
public:
	explicit DefaultWidget(QWidget *parent = 0);
	explicit DefaultWidget(QString&picname, QWidget *parent = 0);
	~DefaultWidget();
protected:
	void paintEvent(QPaintEvent *event);
private:
	QLabel* m_gifLabel;
	QLabel* m_tipInfo;
	QMovie* m_movie;
	QVBoxLayout* m_pMainLayout;
};
}


