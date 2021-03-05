#include "DelayMsgDateWin.h"
#include <QPushButton>
#include <QLabel>
#include <QTimeEdit>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include "../../common/Common.h"
namespace ui{
    DelayMsgDateWin::DelayMsgDateWin(QString text)
    {
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setMinimumSize(260,160);
        initWidget();
		mText = text;
        connect(m_btnOK,SIGNAL(clicked()),this,SLOT(onBtnOKClicked()));
        connect(m_btnCancel,SIGNAL(clicked()),this,SLOT(onBtnCancelClicked()));

    }


    DelayMsgDateWin::~DelayMsgDateWin(void)
    {
    }

    void DelayMsgDateWin::initWidget()
    {
        m_textTitle = new QLabel(this);
        m_btnOK = new QPushButton(this);
        m_btnCancel = new QPushButton(this);
        m_curTime = new QLabel(this);
        m_textTime = new QLabel(this);

        m_mainLayout = new QVBoxLayout();

        m_textTitle->setFixedWidth(250);
        m_textTitle->setText(transfer("设置时间"));
        m_textTitle->setAlignment(Qt::AlignLeft);
        m_textTitle->setStyleSheet("background-color:rgb(31,63,93);color:white;");
		
        m_btnOK->setMinimumSize(60,24);
        m_btnOK->setObjectName("sendbtn");
        m_btnOK->setText(transfer("确定"));

        m_btnCancel->setMinimumSize(60,24);
        m_btnCancel->setObjectName("sendbtn");
        m_btnCancel->setText(transfer("取消"));

		mComboHour = new MyQComboBox(this);
		mComboMin  = new MyQComboBox(this);
		mComboDay = new MyQComboBox(this);
		mComboHour->setFixedWidth(50);
		mComboMin->setFixedWidth(50);
		connect(mComboDay,SIGNAL(currentIndexChanged(int)),this,SLOT(onDayCurrentIndexChanged(int)));
		connect(mComboHour,SIGNAL(currentIndexChanged(int)),this,SLOT(onHourCurrentIndexChanged(int)));
		connect(mComboMin,SIGNAL(currentIndexChanged(int)),this,SLOT(onMinCurrentIndexChanged(int)));
        QHBoxLayout* dateTime = new QHBoxLayout();
        dateTime->addSpacing(5);
        dateTime->addWidget(mComboDay);
        dateTime->addWidget(mComboHour);
		dateTime->addWidget(mComboMin);
        dateTime->addSpacing(5);
        
        m_textTime->setText(transfer("发送时间："));
        QPalette pa;
        pa.setColor(QPalette::WindowText,QColor(25,149,233));
        m_curTime->setPalette(pa);

        QHBoxLayout* textTime = new QHBoxLayout();
        textTime->addSpacing(5);
        textTime->addWidget(m_textTime);
        textTime->addWidget(m_curTime,0,Qt::AlignLeft);
        textTime->addStretch();

        QHBoxLayout* btnLayout = new QHBoxLayout();
        btnLayout->addStretch();
        btnLayout->addWidget(m_btnOK);
        btnLayout->addSpacing(10);
        btnLayout->addWidget(m_btnCancel);
        btnLayout->addSpacing(8);
        m_mainLayout->addWidget(m_textTitle);
        m_mainLayout->addSpacing(10);
        m_mainLayout->addLayout(dateTime);
        m_mainLayout->addLayout(textTime);
        m_mainLayout->addLayout(btnLayout);
        m_mainLayout->addSpacing(5);
        this->setLayout(m_mainLayout);
    }

    void DelayMsgDateWin::onBtnCancelClicked()
    {
       this->close();
    }

    void DelayMsgDateWin::onBtnOKClicked()
    {
		int64 selectTime = 0;
		QTime time(m_currentHour, m_currentMin, 0);

		QDateTime selectDateTime = QDateTime::currentDateTime().addDays(m_currentDate);
		selectDateTime.setTime(time);


		selectTime = selectDateTime.toMSecsSinceEpoch();

		if (QDateTime::currentMSecsSinceEpoch() >= selectTime)
		{
			selectTime= QDateTime::currentMSecsSinceEpoch()+5*60*1000;

		}
        emit signalSendDelayMsg(selectTime,mText);
		this->close();
    }

    void DelayMsgDateWin::setCurentData()
    {
		m_currentDate = 0;
		QDateTime curDateTime = QDateTime::currentDateTime();
		//加五分钟
		curDateTime = curDateTime.addSecs(60*5);

		QDate curDate = curDateTime.date();

		int curMonth = curDate.month();
		int curDay = curDate.day();
		int curHour = 0;
		int curMin = 0;

		QString strFormat("hh:mm");
		QString strTime= curDateTime.toString(strFormat);
		QStringList strList = strTime.split(":");
		curHour = strList.at(0).toInt();
		curMin = strList.at(1).toInt();
		m_currentHour = curHour;
		m_currentMin = curMin;

		//日期
		QString strWeek = "ddd";
		for (int index = 0; index < 31; index++)
		{
			QString tempStr = "";
			curDate = curDateTime.date();
			curMonth = curDate.month();
			curDay = curDate.day();

			tempStr = QString::number(curMonth) + "/" + QString::number(curDay) +
				" " + curDate.toString(strWeek);

			curDateTime = curDateTime.addDays(1);
			m_dateTimeList.push_back(tempStr);
		}
		//小时选择
		for (int index = 0; index < 24; index++)
		{
			QString strHour = QString::number(index);
			strHour = strHour.rightJustified(2, '0');
			m_hourList.push_back(strHour);
		}
		//分钟
		for (int index = 0; index < 60; index++)
		{
			QString strMin = QString::number(index);
			strMin = strMin.rightJustified(2, '0');
			m_minList.push_back(strMin);
		}
		mComboDay->addItems(m_dateTimeList);
		mComboHour->addItems(m_hourList);
		mComboMin->addItems(m_minList);
		m_selectDateTime = m_dateTimeList.at(m_currentDate) + " " + m_hourList.at(m_currentHour) + " : " + m_minList.at(m_currentMin);
		m_curTime->setText(m_selectDateTime);
		mComboMin->setCurrentIndex(m_currentHour);
		mComboHour->setCurrentIndex(m_currentMin);
    }

    void DelayMsgDateWin::ShowDelayWin()
    {
        setCurentData();
		this->exec();
    }

	void DelayMsgDateWin::onDayCurrentIndexChanged( int index )
	{
		m_currentDate = index;
		m_selectDateTime = m_dateTimeList.at(m_currentDate) + " " + m_hourList.at(m_currentHour) + " : " + m_minList.at(m_currentMin);
		m_curTime->setText(m_selectDateTime);
	}

	void DelayMsgDateWin::onHourCurrentIndexChanged( int index )
	{
		m_currentHour = index;
		m_selectDateTime = m_dateTimeList.at(m_currentDate) + " " + m_hourList.at(m_currentHour) + " : " + m_minList.at(m_currentMin);
		m_curTime->setText(m_selectDateTime);
	}

	void DelayMsgDateWin::onMinCurrentIndexChanged( int index )
	{
		m_currentMin = index;
		m_selectDateTime = m_dateTimeList.at(m_currentDate) + " " + m_hourList.at(m_currentHour) + " : " + m_minList.at(m_currentMin);
		m_curTime->setText(m_selectDateTime);
	}

}

