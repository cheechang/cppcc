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
	const QString VIP_SECTION_KEY = "&";//标识v标好友分组
	const QString CONSTANT_SECTION_KEY  = "@";//固定不删除项分组
	const QString ADMIN_SECTION_KEY  = "$";//管理员项分组

	class SortListWidgetItem;
	class SortListWidget : public BaseQListWidget
	{
		Q_OBJECT
	public:
		enum useSectionType{
			Use_ContactList, //好友列表
			Use_GroupList,//群列表
			Use_GroupMemsList,//群成员列表
			Use_PopList, //选择人员列表
			Use_AppList //应用列表
		};
		SortListWidget(QWidget *parent=0,useSectionType=Use_ContactList);
		~SortListWidget();

		//控制checkbox显示
		void setShowCheckBox(bool visible);
		//设置某项是否可以选中
		void setCanChecked(int64 id, bool isCheckable,bool isChecked);
		//获取所有选中项id
		QList<int64>getCheckedItems();
		//生成分组字符
		QString makeSection(QString oriSection,bool isVip=false,bool isAmin=false);
		//插入项
		void addNewItem(SortListWidgetItem*widget);
		//获取widget
		SortListWidgetItem* itemToWidget(QListWidgetItem*item);
		//删除项
		void removeItem(int64 id,bool isAutoSelNextItem);
		//是否显示分组
		void setShowSection(bool vis=true);
		//删除所有项目
		void removeAllItems();
		//更新名称或分组
		void updateItemName(int64 id, QString name,QString sectionKey,int nameWidth =0);
		//更新头像
		void updateAvatar(int64 id,QString avatar);
		//更新在线状态
		void updateOnlineStatus(int64 id,int type);
		//更新Vip
		void updateVip(int64 id,bool isVip);
		//获取widget
		SortListWidgetItem*widgetById(int64 id);
		//设置item信息
		void setItemData(int64 id,QString name,QString avatar,bool flagVis=false,QString flagTips="",int onlineType=-1,QSize AvatarSz=QSize(40,40),QString pix = "");
		//是否删除当前选中项，自动选中下一项
		void setAutoSelectNextAfterRemovingItem(bool isAutoSelNext=false);

		//获取分组Section在列表中的index,item
		QListWidgetItem* indexOfSection(QString sectionKey,int&index);
		//是否存在
		bool isExisted(int64 id);
		//节点数目
		int itemCount();
        //显示和隐藏
		void setHide(int64 id,bool isHide);
		//获取项item
		QListWidgetItem* itemById(int64 id);
		//判断当前分组下是否还有项
		bool hasItemOfSection(QString sectionKey);
		//获取所有项目总高度
		int allItemsHeight();
	protected:
		//初始化分组项
		void initSectionItems(useSectionType useType=Use_ContactList);
		//添加分组项
		void addSectionItem(QString key,QString value);
		//判断是否存在
		SortListWidgetItem* hasItemOfList(int64 id,bool&existed);
		//删除项
		void removeItem(int64 id);
		//删除后，获取下一项合理index
		int nextItemIndex(int64 nowId);
	signals:
		void itemCntChange();
	private:
		//是否显示分组
		bool m_bShowTeam;
		//记录分组字符
		QMap<QString,QString> m_mapKeys;
		//
		bool m_bAutoSelNextItem;
		//使用类型
		useSectionType m_useType;
	};
}


#endif // SORTLISTWIDET_H
