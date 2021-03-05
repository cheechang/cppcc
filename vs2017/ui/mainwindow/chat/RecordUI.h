#pragma once

#include <common/Controlptr.h>
#include <QProgressBar>

class QHBoxLayout;
class QLabel;
class Record;

namespace ui
{
	class PushButton;
    const int RECORD_BUTTON_WIDTH = 18;
    const int RECORD_HEIGTH = RECORD_BUTTON_WIDTH + 12;
    const QString FILE_POSTFIX = ".raw";
	const QString FILE_AMRPSTFIX = ".amr";
	class RecordUI : public QProgressBar
	{
		Q_OBJECT
	public:
		explicit RecordUI(QWidget *parent = 0);
		void StartRecord();
		void StopRecord();
		QString RawConvertWav(QString srcPath, bool& isConverted);

	signals:
		void signalRecordResult(QString path,int time);
		void signalStopRecord();

	public slots:
		void onTimerOut();
		void onStopClicked();
		void onOKClicked();

	protected:
		void initWidgets();
		QString initLocalSetting();

	private:
		Record*        m_record;
		QString        m_audioPath;
		QLabel*        m_audioText;
		QLabel*		   m_audioErrText;

		PushButton* m_audioPoint;
		PushButton* m_recordOk;
		PushButton* m_recordCancel;

		QTimer*         m_recordTime;
		int             m_time;

		int64           m_startTime;
		IChatMgrControl_Ptr m_chatPtr;
		QHBoxLayout*    m_mainLayout;
	};
}