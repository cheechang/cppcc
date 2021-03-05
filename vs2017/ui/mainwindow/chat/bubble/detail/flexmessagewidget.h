#ifndef FLEXMESSAGEWIDGET_H
#define FLEXMESSAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QHBoxLayout>
#include "interface/Defines.h"
#include "data/ChatData.h"
#include <ui/common/ChineseInfos.hpp>
class AbstractMessageWidget;

class ChickFeatherLabel:public QWidget{
	Q_OBJECT
public:
	ChickFeatherLabel(QWidget*parent):QWidget(parent){
		QHBoxLayout*layout = new QHBoxLayout(this);
		mlblText = new QLabel(this);
		mlblIcon = new QLabel(this);
		layout->addWidget(mlblText);
		layout->addWidget(mlblIcon);
		layout->setContentsMargins(0,0,0,0);
		layout->setSpacing(0);
		layout->addStretch();
		this->setLayout(layout);
		mlblText->setObjectName("ChickFeatherFont");
		mlblIcon->setPixmap(QPixmap(":/chat/chickFeather"));
		setVisible(false);
	}
	void setText(QString text,bool isshowIcon=true){
		QString style = "";
		if (text == TEXT_TIP85) {
			style = "QLabel{color:blue; font: 10px;}";
		}
		else if (text == TEXT_TIP150) {
			style = "QLabel{color:red; font: 10px;}";

		}
		else if (text == TEXT_TIP_ALL_READ) {
			style = "QLabel{color:blue; font: 10px;}";
		}
		else if (text == ALL_UNRED_MSG) {
			style = "QLabel{color:red; font: 10px;}";
		}
		else {
			style = "QLabel{color:#FFB400; font: 10px;}";
		}
		mlblText->setStyleSheet(style);
		mlblText->setText(text);
		mlblIcon->setVisible(isshowIcon);
	}
signals:
	void clicked();
protected:
	void mousePressEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton)
		{
			emit clicked();
		}
	}
private:
	QLabel*mlblText;
	QLabel*mlblIcon;
};

class BurnLabel:public QLabel{
	Q_OBJECT
public:
	explicit BurnLabel(QWidget*parent,int64 localId);
	~BurnLabel();
	void start(int time);
signals:
	void timeOut(int64);
protected:
	void paintEvent(QPaintEvent* e);
protected slots:
	void onTimerOut();
private:
	QTimer mTimer;
	int mCount;
	int64 mLocalId;
};
class FlexMessageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlexMessageWidget(bool alignLeft, QWidget *parent = 0);
    ~FlexMessageWidget();
    
    void setName(const QString& name);
    QString name() const;

    void setNameVisible(bool visible);
    bool nameVisible() const;

    void setAvatar(const QPixmap& pixmap);
    QPixmap avatar() const;

	void setMsgStatusLblText(QString text);
	void setMsgStatusWidgetFixedWidth(QString text);

    void setMessageWidget(AbstractMessageWidget* message);
    AbstractMessageWidget* messageWidget() const;

	void addMessageWidget(AbstractMessageWidget* message);

    void suggestWidth(int width);

	void startBurnTimer(int time);
	bool isBurning();

	void setDelayMsgTime();
	void setDelayTime(QString time);
	QString getDelayTime();
	void SetChickFeather();
	void SetChickSendedMsg();
signals:
	void showUserInfoWidget(int64, QString, QString);
	void burnMsg(int64);
	void sizechanged();
public slots:
	void onAvatarClicked();
	void onShowMsgStatus();
private:
    class FlexMessageWidgetPrivate* d_ptr;
	bool m_alignLeft;
};

#endif // FLEXMESSAGEWIDGET_H
