#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <QDialog>
class QLabel;
class QTextEdit;
class QWidget;
class QVBoxLayout;
namespace uicontrols{
	class Button;
	class TitleBar;
	class WeMessageBox : public QDialog
	{
		Q_OBJECT

	public:
		enum TypeOfButton{
			Ok     = 0x00000400,//ȷ��
			Cancel = 0x00400000 //ȡ��
		};
		WeMessageBox(QWidget *parent=0,const QString title="",const QString text="",const int maxTextLenth=300);
		~WeMessageBox();

		//����ͼ��
		void setIcon(QString path);
		void setIconSize(QSize size);
		void setMaxTextLenth(int lenth);
		//ѯ�ʿ�
		TypeOfButton question();
		//�����
		TypeOfButton warning();
		//��ʾ��
		TypeOfButton information();
		//�����
		TypeOfButton err();
	    //��icon
		TypeOfButton noIcon();
		//Style ��ʾ��
		TypeOfButton TipInformation(bool isShowIocn=false,bool isShowCancelBtn=false);

		static void setDefaultSkin(const QString skin,const QColor skinColor);
		static TypeOfButton showInformation(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth=300);
		static TypeOfButton showQuestion(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth=300);
		static TypeOfButton showWarning(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth=300);
		static TypeOfButton showCritical(QWidget *parent, const QString &title,const QString &text,const int maxTextLenth=300);

		static TypeOfButton showTipInformation(QWidget *parent, const QString &title,const QString &text,bool showIocn,bool showCancelBtn,const int maxTextLenth=300);
	protected:
		void setWeWindowFlags();
		void paintEvent(QPaintEvent *event);
	protected slots:
		void onBtnCancel();
		void onBtnOk();
	protected:
		TitleBar*				m_titleBar;
		QVBoxLayout*			m_MainLayout;
		Button*					m_pBtnOK;
		Button*					m_pCancel;
		QTextEdit*				m_pText;
		QLabel*					m_pIcon;
		TypeOfButton			m_RetunType;
		QString					m_strIconPath;
		QSize					m_iconSize;
		int						m_titleHeight;
	private:
		static QColor		    m_titleBkColor;
		static QString          m_defaultSkin;
	};
	
}

#endif // MESSAGEBOX_H
