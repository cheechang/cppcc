#pragma once
#include <QMenu>
#include <qsharedpointer.h>
namespace ui{
	enum MenuItem
	{
		MENU_DEL,
		MENU_RENAME,
		MENU_REFRESH,
		MENU_SORTBYTIME
	};
	class CloudDiskMenu :public QMenu{
		Q_OBJECT
	public:
		CloudDiskMenu(QWidget *parent = nullptr);
		virtual ~CloudDiskMenu();
		void setMenuState(MenuItem item, bool isShow);
		void setMenuEnable(MenuItem item, bool enable);
		void show(QPoint pt = QCursor().pos());
		void setIsOwner(bool isowned);
		void setIsRootNode(bool isrootnode);
	signals:
		void signalDelMenu();
		void signalRenameMenu();
		void signalRefresh();
		void signalSortByTime();
	private:
		bool			m_isowner;
		bool            m_isrootnode;
		std::shared_ptr<QAction> m_pDelItem;			//ɾ��
		std::shared_ptr<QAction> m_pRenameItem;		//������
		std::shared_ptr<QAction> m_pRefresh;			//ˢ��
		std::shared_ptr<QAction> m_pSortByTime;		//ʱ������
	};
}