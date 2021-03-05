#ifndef SORTLISTWIDGETITEM_H
#define SORTLISTWIDGETITEM_H
#include "TWidget.h"

class QLabel;
class QHBoxLayout;
namespace uicontrols{
	class Label;
	class AvatarWidget;
	class RadioButton;
	class IconButton;
	class SortListWidgetItem : public ui::TWidget
	{
		Q_OBJECT

	public:
		enum OnlineType{
			OnlineOnPC=1,
			OnlineOnPhone=2,
			OnlineOnPad=3,
			Leave,
			Vip
		};
		SortListWidgetItem(int type,QWidget *parent=0);
		~SortListWidgetItem();
		//显示消息内容
		void setMsgContext(std::string text,QString blueText,bool isShow=true);
		//选中状态
		bool isChecked();
		void setChecked(bool isChecked);
		void setCheckBoxVisible(bool vis);
		void setCheckable(bool isCheckable);
		bool isCanCheckable();
		//设置显示删除按钮
		void setDelBtnVisible(bool vis);

		//唯一标识符
		int64 id();
		void setId(int64 id);

		//名称
		QString name();
		void setName(QString name,int width = 0);

		//头像路径
		QString avatarPath();
		void setAvatarPath(QString path);
		//隐藏头像
		void setAvatarVisible(bool isVis);

		//分组字符串
		QString teamKey();
		void setTeamKey(QString key);

		//设置在线状态
		int  onlineStatus();
		void setOnlineStatus(int type=Leave);
		//設置在線狀態圖標位置
		void setOnlineIconPos(QPoint pos,int sz=0);

        //设置我的群标识
		bool flagVisible();
		QString flagVisibleTips();
		void setFlagVisible(bool vis,QString tips="",QString pix = "");
		void setPix(QString pix);
		QString flagPix();
		//设置头像大小
		QSize avatarSize();
		void setAvatarSize(QSize sz);

		QString pinYin();
		void setPinYin(QString pinyin);

		//v标好友
		bool isVip();
		void setVip(bool vip);
		
		//是否能够删除
		bool isCanDel();
		void setCanDel(bool canDel);

		void setTextWidth(int width);
		//仅显示名称
		void setOnlyShowName();
		//设置数据
		void setItemData(int64 id,QString name,QString avatar,bool flagVis=false,QString flagTips="",int onlineType=4,QSize AvatarSz=QSize(40,40),bool isVip=false,QString pix = "");
	signals:
		void signalRemove(int64 id);
		void signalCheckedChanged(int64 id);
		void signalHeadClicked(int64 id);
	protected slots:
		void onDelBtnClicked();
		void onCheckBoxStateChanged();
		void onAvatarClicked(QPoint pt);
	protected:
		virtual void enterEvent(QEvent *event);
		virtual void leaveEvent(QEvent *event);
		virtual void mousePressEvent(QMouseEvent *e);

	private:
		uicontrols::AvatarWidget* m_pAvatar;//头像
		uicontrols::Label*   m_pName;//名称
		QLabel*        m_pOnline;//在线状态图标
		QLabel*        m_pFlag;//我的群图标
		QHBoxLayout*   m_pMainLayout;
		RadioButton* m_checkBox;
		IconButton* m_pBtnDel;

		int64   m_id;
		QString  m_name;
		QString  m_teamKey;
		QString m_pinYin;
		int      m_onlineStatus;
		bool     m_vip;
		bool     m_IsDelBtnShow;
		bool     m_isCanDel;//群列表使用
		QLabel*m_lblMsg;//显示会话信息 
		QString m_pix;
	};

	class SortListWidgetTeamItem: public ui::TWidget{
		Q_OBJECT
	public:
		SortListWidgetTeamItem(int type,QWidget *parent=0,QString key="#",QString value="");
		~SortListWidgetTeamItem();
		int64 id(){return -1;}
		//分组字符
		QString key();
		//列表显示字符
		QString value();
	private:
		QString m_key;
		QString m_value;
	};
}
#endif // SORTLISTWIDGETITEM_H
