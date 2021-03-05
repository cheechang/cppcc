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
		//��ʾ��Ϣ����
		void setMsgContext(std::string text,QString blueText,bool isShow=true);
		//ѡ��״̬
		bool isChecked();
		void setChecked(bool isChecked);
		void setCheckBoxVisible(bool vis);
		void setCheckable(bool isCheckable);
		bool isCanCheckable();
		//������ʾɾ����ť
		void setDelBtnVisible(bool vis);

		//Ψһ��ʶ��
		int64 id();
		void setId(int64 id);

		//����
		QString name();
		void setName(QString name,int width = 0);

		//ͷ��·��
		QString avatarPath();
		void setAvatarPath(QString path);
		//����ͷ��
		void setAvatarVisible(bool isVis);

		//�����ַ���
		QString teamKey();
		void setTeamKey(QString key);

		//��������״̬
		int  onlineStatus();
		void setOnlineStatus(int type=Leave);
		//�O���ھ���B�D��λ��
		void setOnlineIconPos(QPoint pos,int sz=0);

        //�����ҵ�Ⱥ��ʶ
		bool flagVisible();
		QString flagVisibleTips();
		void setFlagVisible(bool vis,QString tips="",QString pix = "");
		void setPix(QString pix);
		QString flagPix();
		//����ͷ���С
		QSize avatarSize();
		void setAvatarSize(QSize sz);

		QString pinYin();
		void setPinYin(QString pinyin);

		//v�����
		bool isVip();
		void setVip(bool vip);
		
		//�Ƿ��ܹ�ɾ��
		bool isCanDel();
		void setCanDel(bool canDel);

		void setTextWidth(int width);
		//����ʾ����
		void setOnlyShowName();
		//��������
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
		uicontrols::AvatarWidget* m_pAvatar;//ͷ��
		uicontrols::Label*   m_pName;//����
		QLabel*        m_pOnline;//����״̬ͼ��
		QLabel*        m_pFlag;//�ҵ�Ⱥͼ��
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
		bool     m_isCanDel;//Ⱥ�б�ʹ��
		QLabel*m_lblMsg;//��ʾ�Ự��Ϣ 
		QString m_pix;
	};

	class SortListWidgetTeamItem: public ui::TWidget{
		Q_OBJECT
	public:
		SortListWidgetTeamItem(int type,QWidget *parent=0,QString key="#",QString value="");
		~SortListWidgetTeamItem();
		int64 id(){return -1;}
		//�����ַ�
		QString key();
		//�б���ʾ�ַ�
		QString value();
	private:
		QString m_key;
		QString m_value;
	};
}
#endif // SORTLISTWIDGETITEM_H
