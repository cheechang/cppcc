#pragma once
#include "core/BaseDialog.h"
#include <interface/Defines.h>
#include <QGridLayout>
#include "controls/MyQComboBox.h"

class QGridLayout;
class QTimeEdit;
class QDateEdit;
class QLabel;
class QPushButton;
namespace ui{
    class DelayMsgDateWin :     public BaseDialog
    {
        Q_OBJECT
    public:
        DelayMsgDateWin(QString text);
        ~DelayMsgDateWin(void);
        void ShowDelayWin();
    signals:
        void signalSendDelayMsg(int64 time,QString text);
    public slots:
            void onBtnCancelClicked();
            void onBtnOKClicked();
            void onDayCurrentIndexChanged(int index);
			void onHourCurrentIndexChanged(int index);
			void onMinCurrentIndexChanged(int index);
    protected:
        void initWidget(); 
        void setCurentData();
    private:
        QLabel*       m_textTitle;
        QLabel*       m_curTime;
        QLabel*       m_textTime;
        QPushButton*  m_btnOK;
        QPushButton*  m_btnCancel;

		MyQComboBox* mComboDay;
		MyQComboBox* mComboHour;
		MyQComboBox* mComboMin;
		QStringList m_dateTimeList;   //日期
		int m_currentDate;
		QStringList m_hourList;   //小时
		int m_currentHour;
		QStringList m_minList;  //分钟
		int m_currentMin;
		QString m_selectDateTime;

        QVBoxLayout*  m_mainLayout;
		QString mText;
    };
}


