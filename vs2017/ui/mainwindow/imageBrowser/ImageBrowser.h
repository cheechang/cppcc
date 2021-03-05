#ifndef IMAGEBROWSER_H
#define IMAGEBROWSER_H
#include "../core/BaseDialog.h"
#include "interface/Defines.h"
#include "./ImageHandlerWidget.h"
#include <QTimer>
class QVBoxLayout;
namespace ui{
	class PushButton;
	class ToolButton;
	class ImageBrowser : public BaseDialog
	{
		Q_OBJECT
	private:
		ImageBrowser(QWidget *parent=CNull);
	public:
		~ImageBrowser();
		static void setImgs(QList<QString>imgs,int index=0);
		static ImageBrowser* Instance();
		static void showWin();
	protected:
		virtual void paintEvent(QPaintEvent *event);
		virtual void leaveEvent(QEvent *e);
		virtual void mouseMoveEvent(QMouseEvent *e);

		void initImagePanelWidget();
		void initTitleWidget();
		void initToolWidget();
		
	protected slots:
		void onDownload();
		void onZoomIn();
		void onZoomOut();
		void onRotate();
		void onBtnLeft();
		void onBtnRight();
		void onMin();
		void onClose();
		void onMax();
		void onSetRightBtnTooltip();
		void onSetLeftBtnTooltip();

		void showPags();
	protected:
		PushButton*mBtnZoomIn;
		PushButton*mBtnZoomOut;
		PushButton*mBtnDownload;
		PushButton*mBtnRotate;

		ToolButton*mBtnLeft;
		ToolButton*mBtnRight;

		PushButton* mBtnMin;
		PushButton* mBtnMax;
		PushButton* mBtnClose;

		QVBoxLayout*mMainLayout;
		bool mIsMax;

		static ImageHandlerWidget* mImageHandlerWidget;
		static QList<QString> mImgs;
		static int            mCurrentImgIndex;
		static ImageBrowser*  mPInstance;
		QTimer mTimer;
	};
}
#endif // IMAGEBROWSER_H
