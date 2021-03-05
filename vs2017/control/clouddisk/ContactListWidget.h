#pragma once
#include "Controls/TWidget.h"
#include "Common/ServiceDefine.h"
#include <qlistwidget.h>
class QCheckBox;
class QLabel;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QStackedWidget;
namespace ui{
	class HeadImage;
	class ElidedLabel;
	class DefaultWidget;
	class ContactListItem :public QWidget{
		Q_OBJECT
	public:
		explicit ContactListItem(QString&head, QString&name, bool ischeckable=true,QWidget*parent = nullptr);
		virtual  ~ContactListItem();
		void			setItemData(model::Contact&contact);
		model::Contact  getItemData() const;
		void			setUserData(model::EntpriseUserInfo&user);
		model::EntpriseUserInfo getUserData()const;
		bool            isCheckable();
		void            setItemType(int type);
	signals:
		void            signalChecked(qint32, qint64, bool);
	protected slots:
		void		    slotClicked(int checked);
	private:
		bool m_ischeckable;
		model::EntpriseUserInfo m_userdata;
		model::Contact  m_contact;
		QCheckBox*   m_check;
		HeadImage*	 m_head;
		ElidedLabel* m_name;
		QHBoxLayout* m_mainLayout;
		int		     m_type; //1联系人 2企业组织
	};
	class ContactList :public QListWidget{
		Q_OBJECT
	public:
		explicit ContactList(QListWidget *parent = nullptr);
		virtual  ~ContactList();
		void	 getSelectedMember(QVector<model::Contact>&members);
		void	 addItem(model::Contact&contact, bool ischeckable=true);
		void     setMemberState(qint64 id, bool ischecked);
	signals:
		void     signalChecked(qint32, qint64, bool);
	public slots:
		void	 onItemPressed(QListWidgetItem* item);
	};
	class ContactListWidget :public TWidget{
		Q_OBJECT
	public:
		explicit ContactListWidget(QVector<qint64>&memberlist, QWidget*parent = nullptr);
		virtual  ~ContactListWidget();
		void	 getSelectedMember(QVector<model::Contact>&members);
		void     updateItemState(qint64 id, bool ischecked);
	signals:
		void        signalChecked(qint32, qint64, bool);
	public slots:
		void		loadData();
	private:
		ContactList*        m_contactList;
		DefaultWidget*      m_loadingWidget;
		QStackedWidget*     m_stackWidget;
		QVBoxLayout*		m_mainLayout;
	private:
		IContactService_Ptr m_contact;
		QVector<qint64> m_filterMemList;
	};
}