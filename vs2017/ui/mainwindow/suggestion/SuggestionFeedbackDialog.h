#pragma once

#include <QRadioButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QPushButton>
#include "../contact/createGroup/BaseWindow.h"


namespace ui
{
	class PlaceHolderEdit;
	class SuggestionFeedbackSendDialog;
	class SuggestionFeedbackDialog : public BaseWindow
	{
		Q_OBJECT

	public:
		SuggestionFeedbackDialog(QWidget *parent = CNull);
		~SuggestionFeedbackDialog();
		void showWin();
	signals:
        void ShowSuggestionDialog(QString& filepath);
	public slots:
		void onSaveClicked(void);

	private:
		void initWidget(void);
		void setLayout(void);
		void setAttribute(void);
		void setConnections(void);
		/* 拷贝文件 */
		bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);
		/* 拷贝文件夹 */
		bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
		//文件过滤拷贝
		bool copyDirectoryFilterFiles(const QString &fromDir, const QString &toDir, QStringList& filenamelist, bool coverFileIfExist);
		/* 删除文件 */
		bool DelDir(const QString &path);

		QLabel* m_pLabelThank;
		QLabel* m_pLabelQuastion;
		QRadioButton* m_pRadioCrash;
		QRadioButton* m_pRadioOffline;
		QRadioButton* m_pRadioBlock;
		QRadioButton* m_pRadioOther;
		QRadioButton* m_pRadioSuggestion;
		PlaceHolderEdit* m_pEditSuggestion;
		QCheckBox* m_pCheckEveryOperate;
		QPushButton* m_pButtonSave;
	};
}
