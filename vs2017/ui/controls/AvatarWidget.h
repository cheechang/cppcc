#ifndef AVATARWIDGET_H
#define AVATARWIDGET_H
/**
** 新封装控件：圆型头像控件
**/
#include <QWidget>
namespace uicontrols{
	class AvatarWidget : public QWidget
	{
		Q_OBJECT
	public:
		enum DefaultSize{
			DEFAULT_WIDTH = 60,
			DEFAULT__HEIGHT = 60,
		};
		AvatarWidget(QWidget *parent = 0, 
			const QSize& avatarSize = QSize(DEFAULT_WIDTH, DEFAULT__HEIGHT), 
			bool hasHoverBorder = false);

		//设置头像
		void setAvatarPath(const QString& fullPath);
		QString AvatarPath();

		//设置白色边框
		void setHasHoverBorder(const bool hasHoverBorder);
		//头像置灰
		void setShowAsGray(bool isGray);
		//头像大小
		void setAvaterSize(QSize size);

	signals:
		void clicked(QPoint pos);
		void signalEnter();
		void rightClicked();
	protected:
		void enterEvent(QEvent *event);
		void leaveEvent(QEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void paintEvent(QPaintEvent *event);
		QString getImgRealType(QString fileName);
	private:
		bool        m_isMouseOver;
		bool        m_isMousePressed;
		QString     m_imgFullPath;
		QSize       m_avatarSize;
		QImage      m_originalImage;
		QImage      m_maskImg;
		bool		m_hasHoverBorder;
		bool        m_isShowGray;
	};
}
#endif // AVATARWIDGET_H
