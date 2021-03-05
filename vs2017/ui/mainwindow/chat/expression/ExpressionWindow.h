#ifndef EXPRESSIONWINDOW_H
#define EXPRESSIONWINDOW_H
#include <qdialog.h>
#include <QPushButton>
#include <map>
#include <Defines.h>
class QVBoxLayout;
class QWidget;
class QStackedWidget;
namespace ui{
	class ExpressionWidget;
	class TabItemButton:public QPushButton{
		Q_OBJECT
	public:
		TabItemButton(QWidget*parent=CNull,QString icon="");
		~TabItemButton();
	};
	class ExpressionWindow : public QDialog
	{
		Q_OBJECT

	public:
		ExpressionWindow(QWidget *parent=CNull);
		~ExpressionWindow();
		static void initEmoji();
		void showWin();
	signals:
		void signalEmojiClicked(int type,QString path);
	protected:
		void setData();
		void loadFaceEmojiData();
		void loadDyEmojiData();
	protected slots:
		void onClicked(QString fileName);
		void onFaceEmojiClicked();
		void onInstructEmojiClicked();
		void onDyEmojiClicked();
	private:
		QStackedWidget* mStackedWidget;
		QVBoxLayout* mMainLayout;
		ExpressionWidget* mEmojiUserDef;
		ExpressionWidget* mEmojiEmojiFace;
		ExpressionWidget* mEmojiDynamic;

		//��������
		static QMap<QString, QString> m_keyValMap;
		static QStringList m_frontEmoji;
		static QStringList m_frontOther;

		static std::map<std::string, std::string>m_InstructMap;//��������
		static std::map<std::string, std::string>m_engInstructMap;
		static QMap<QString, QString> m_keyDnyValMap;//��̬����
		bool mIsLoad,mIsLoadFaced,mIsLoadDy;
		//������
		TabItemButton*mBtnFaceEmoji;
		TabItemButton*mBtnInstructEmoji;
		TabItemButton*mBtnDyEmoji;
	};
}
#endif // EXPRESSIONWINDOW_H
