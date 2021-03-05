#ifndef SORTLISTWIDET_H
#define SORTLISTWIDET_H
#include "BaseQListWidget.h"
#include "utils/common.h"
//#include <absinterface/Defines.h>
namespace uicontrols{
	const int TEAMITEMHEIGHT = 30;
	enum{
		ItemRole = Qt::UserRole+1,
	};
	const QString VIP_SECTION_KEY = "&";//��ʶv����ѷ���
	const QString CONSTANT_SECTION_KEY  = "@";//�̶���ɾ�������
	const QString ADMIN_SECTION_KEY  = "$";//����Ա�����

	class SortListWidgetItem;
	class SortListWidget : public BaseQListWidget
	{
		Q_OBJECT
	public:
		enum useSectionType{
			Use_ContactList, //�����б�
			Use_GroupList,//Ⱥ�б�
			Use_GroupMemsList,//Ⱥ��Ա�б�
			Use_PopList, //ѡ����Ա�б�
			Use_AppList //Ӧ���б�
		};
		SortListWidget(QWidget *parent=0,useSectionType=Use_ContactList);
		~SortListWidget();

		//����checkbox��ʾ
		void setShowCheckBox(bool visible);
		//����ĳ���Ƿ����ѡ��
		void setCanChecked(int64 id, bool isCheckable,bool isChecked);
		//��ȡ����ѡ����id
		QList<int64>getCheckedItems();
		//���ɷ����ַ�
		QString makeSection(QString oriSection,bool isVip=false,bool isAmin=false);
		//������
		void addNewItem(SortListWidgetItem*widget);
		//��ȡwidget
		SortListWidgetItem* itemToWidget(QListWidgetItem*item);
		//ɾ����
		void removeItem(int64 id,bool isAutoSelNextItem);
		//�Ƿ���ʾ����
		void setShowSection(bool vis=true);
		//ɾ��������Ŀ
		void removeAllItems();
		//�������ƻ����
		void updateItemName(int64 id, QString name,QString sectionKey,int nameWidth =0);
		//����ͷ��
		void updateAvatar(int64 id,QString avatar);
		//��������״̬
		void updateOnlineStatus(int64 id,int type);
		//����Vip
		void updateVip(int64 id,bool isVip);
		//��ȡwidget
		SortListWidgetItem*widgetById(int64 id);
		//����item��Ϣ
		void setItemData(int64 id,QString name,QString avatar,bool flagVis=false,QString flagTips="",int onlineType=-1,QSize AvatarSz=QSize(40,40),QString pix = "");
		//�Ƿ�ɾ����ǰѡ����Զ�ѡ����һ��
		void setAutoSelectNextAfterRemovingItem(bool isAutoSelNext=false);

		//��ȡ����Section���б��е�index,item
		QListWidgetItem* indexOfSection(QString sectionKey,int&index);
		//�Ƿ����
		bool isExisted(int64 id);
		//�ڵ���Ŀ
		int itemCount();
        //��ʾ������
		void setHide(int64 id,bool isHide);
		//��ȡ��item
		QListWidgetItem* itemById(int64 id);
		//�жϵ�ǰ�������Ƿ�����
		bool hasItemOfSection(QString sectionKey);
		//��ȡ������Ŀ�ܸ߶�
		int allItemsHeight();
	protected:
		//��ʼ��������
		void initSectionItems(useSectionType useType=Use_ContactList);
		//��ӷ�����
		void addSectionItem(QString key,QString value);
		//�ж��Ƿ����
		SortListWidgetItem* hasItemOfList(int64 id,bool&existed);
		//ɾ����
		void removeItem(int64 id);
		//ɾ���󣬻�ȡ��һ�����index
		int nextItemIndex(int64 nowId);
	signals:
		void itemCntChange();
	private:
		//�Ƿ���ʾ����
		bool m_bShowTeam;
		//��¼�����ַ�
		QMap<QString,QString> m_mapKeys;
		//
		bool m_bAutoSelNextItem;
		//ʹ������
		useSectionType m_useType;
	};
}


#endif // SORTLISTWIDET_H
