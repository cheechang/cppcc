#pragma  once
#include <QTextEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QFocusEvent>
#include "interface/Defines.h"
#include "common/Common.h"
class QMovie;
class QMimeData;
#define LINK_RegulaString "((http[s]{0,1}|ftp)://[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)|(www.[a-zA-Z0-9\\.\\-]+\\.([a-zA-Z]{2,4})(:\\d+)?(/[a-zA-Z0-9\\.\\-~!@#$%^&*+?:_/=<>]*)?)"

namespace ui{
	class GroupAtSelectListWidget;
	class ChatEdit:public QTextEdit{
		Q_OBJECT
	public:
		typedef struct urldata{
			int firstPos;
			int lastPos;
			QString url;
		}UrlData;

		explicit ChatEdit(QWidget*parent = CNull,bool isreadonly=false);
		virtual ~ChatEdit();
		bool canInsertFromMimeData(const QMimeData* source) const;
		void insertFromMimeData(const QMimeData* source);
		void insertImage(const QString& imagepath);
		void insertFile(const QString& filepath);
		void insertEmoji(const QString& emojipath);
		void setTargetInfo(TargetInfo info);
		void insertText(QString txt);
		void SetEditState(bool isRead, int type=0);
		bool hasWebUrl(QString text);
		void setWebUrlContext(QString text);
		void setContentSrc(bool isRcv);
		void setAtListWidgetVisible(bool isVis);
	public slots:
		void onAnimate(int a);
		void onSendMsg();
		void ontextChanged();
		void onContentsChanged();
		void onSetSendMsgShorcut(int val);
		void onInserAtImg(QString imgPath);
		void onGroupAtDataFinish();
	signals:
		void clicked();
		void keyPress(QEvent *);
		void noticeInputEditFocus();
		void SendMsg(QString,QStringList,QStringList,std::vector<int64>,bool,bool,bool);
	protected:
		bool eventFilter(QObject *obj, QEvent *e);
		virtual void keyReleaseEvent(QKeyEvent *e);
		virtual void focusInEvent(QFocusEvent *e);
		virtual void focusOutEvent(QFocusEvent *e);
		QString GetDefaultPicPath();
		bool ConvertImageToTransparent(QImage& bmp,QString &path);
	protected:
		 void mouseDoubleClickEvent ( QMouseEvent *event );
		 void mouseMoveEvent(QMouseEvent *event);
		 void mousePressEvent(QMouseEvent *event);
		 void dropEvent(QDropEvent *event);
	private:
		void addAnimation(const QUrl& url, const QString& fileName,const QSize&size);
		void addImage(const QUrl& url,QImage& image);
		void dropImage(const QUrl& url, const QImage& image);
		void dropFile(const QUrl& url);
		void cleargif();
		void paraseMsgContent(QTextDocument* textdocu,bool isSendMsg=false);
		void dealWebData(QString& html);
		void showAtWin();
		QString getLinkUrl(QString text);
	private:
		QHash<QString,QMovie*> m_gifmap;
		QMap<QString,QString>m_imagelist;
		QString m_textmsg;
		QStringList m_imagepathlist;
		QStringList m_filepathlist;
		std::vector<int64> m_atmemlist;
		bool m_isburn;
		bool m_isreceipt;
		bool m_isdelay;
		int  m_sendshortcut; //1 enter 发送  2 ctrl+enter 发送
		TargetInfo mTargetInfo;
		GroupAtSelectListWidget* mAtMemsWin;
		QString mOldText;
		int mGroupAtNameLen;
		bool m_isReadOnly;
		QList<UrlData> m_list;
		bool isReceive;
	};
}