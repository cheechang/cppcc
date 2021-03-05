#ifndef LOCALSEARCHLISTWIDGET_H
#define LOCALSEARCHLISTWIDGET_H
#include "controls/TWidget.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QKeyEvent>
#include <data/ChatData.h>
#include "interface/Defines.h"
#include "common/Controlptr.h"
class QLabel;
namespace ui{
	class LocalSearchListItemWidget;
	class UserInfoWindow;
	class LocalSearchListWidget : public QWidget
	{
		Q_OBJECT
	public:
		enum{
			TeamItem =-1
		};
		LocalSearchListWidget(QWidget *parent=CNull,bool isShadowEffect=true,bool isDbSendMsg = true);
		~LocalSearchListWidget();
		void searchFromLocal(const QString& text);
		void clearList();
		void setData(std::vector<data::ChatInfo>&list);
	signals:
		void signalSerSearchFromLocal(int, std::vector<data::ChatInfo>&);
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void hideLocalSearchList();
	protected slots:
		void onSerSearchFromLocal(int code, std::vector<data::ChatInfo>&list);
		void onHeadClicked(int64 id);
		void resetTipItem();

		void onItemDoubleClicked(QListWidgetItem *item);
		void onItemClicked(QListWidgetItem*);

		void startChat( QListWidgetItem * item );
		void onInfoStartChat(CSharedPtr<data::ChatInfo>& chatInfo);

	protected:
		virtual void paintEvent(QPaintEvent *event);
		virtual void keyPressEvent(QKeyEvent *event);
		void addItemToList( data::ChatInfo& data );
	private:
		QListWidget* mListWidget; 
		QVBoxLayout* mMainLayout;
		QMap<int64,data::ChatInfo> mMapData;
		IContactMgrControl_Ptr mContactControl;
		UserInfoWindow* m_pUserInfoWidget;
		bool mClickAvatarShowInfo;
	
		QStackedWidget* m_mainStactkedWidget;

		QLabel* m_tipLbl;
		QWidget *m_noninfo;
	};
}

#endif // LOCALSEARCHLISTWIDGET_H
