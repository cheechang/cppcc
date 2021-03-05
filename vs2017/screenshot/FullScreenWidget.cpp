#include "FullScreenWidget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QScreen>
#include <QDateTime>
#include <QMouseEvent>
#include <../ui/common/ChineseInfos.hpp>
/*********************************************************
函数名：MonitorEnumProc（）
输入参数：HMONITOR hMonitor ---显示器句柄
HDC hdcMonitor  ----显示器DC句柄
LPRECT lprcMonitor-----
LPARAM dwData-----EnumDisplayMonitors传来的数据
返回：bool
功能：若返回为真，EnumDisplayMonitors继续枚举，
若返回为假，EnumDisplayMonitors停止枚举，从而获得显示器信息
将显示器个数保存在numScreen，分辨率信息保存在rect
**********************************************************/
// BOOL CALLBACK MonitorEnumProc(
// 								HMONITOR hMonitor,
// 								HDC		 hdcMonitor, 
// 								LPRECT   lprcMonitor, 
// 								LPARAM   dwData
// 								)
// {
//    static BOOL first		= TRUE;   //标志
//    static int  numScreen	= 0;
//    RECT	  rect [10]				;
// 
//    //保存显示器信息
//    MONITORINFO monitorinfo;         
//    monitorinfo.cbSize = sizeof(MONITORINFO);
// 
//    //获得显示器信息，将信息保存到monitorinfo中
//    GetMonitorInfo(hMonitor, &monitorinfo);
// 
//    //若检测到主屏
//    if(monitorinfo.dwFlags == MONITORINFOF_PRIMARY)
//    {
// 		if(first)  //第一次检测到主屏
// 		{
// 			 first = FALSE;
// 			 numScreen = 1;
// 			 //将显示器的分辨率信息保存到rect
// 			 rect[0] = monitorinfo.rcMonitor;
// 			 return TRUE;  
// 		}
// 		else //第二次检测到主屏,说明所有的监视器都已经检测了一遍，故可以停止检测了
// 		{
// 		 first = TRUE;    //标志复位
// 		 return FALSE;    //结束检测
// 		}
//    }
// 
//    rect[numScreen] = monitorinfo.rcMonitor;
//    numScreen++;
//    return TRUE;
// }

fullScreenWidget::fullScreenWidget() :
m_pbtnSave(NULL),//保存按钮
m_pbtnCancel(NULL),//取消按钮
m_pbtnFinish(NULL),//完成按钮
m_pSpliterOne(NULL),
m_pspliterTwo(NULL)
{
	m_imagePath = ":/image/screenShot/";
//#ifndef _DEBUG
//	m_imagePath = ":/image/screenShot/";
//#else
//	m_imagePath = "ui/image/screenShot/";
//#endif

	m_bIsShapeBtnClicked = false;
	m_iEditSetHeigth = 0;
	m_drawWidget = NULL;
	m_pGraphicsView = NULL;
	tipWidth = 300; //温馨提示框的宽度
	tipHeight = 100; //温馨提示框的高度
	infoWidth = 335; //坐标信息框的宽度
	infoHeight = 27; //坐标信息框的高度
	// EnumDisplayMonitors(NULL,NULL,MonitorEnumProc,0);
	//初始化工具栏
	initToolBar();
	initFullScreenWidget();
	m_bIsSend = false;
}
fullScreenWidget* fullScreenWidget::m_instance = NULL;
fullScreenWidget * fullScreenWidget::GetInstance()
{
	if (m_instance == NULL)  //判断是否第一次调用  
		m_instance = new fullScreenWidget();
	return m_instance;
}
void fullScreenWidget::initToolBar()
{
	m_pbtnSave = new QToolButton(this);//保存按钮
	m_pbtnCancel = new QToolButton(this);//取消按钮
	m_pbtnFinish = new QToolButton(this);//完成按钮
	m_pSpliterOne = new QLabel(this);
	m_pspliterTwo = new QLabel(this);
	m_pbtnSave->setToolTip(SAVE_TIP);
	m_pbtnCancel->setToolTip(CANCEL_TIP);
	m_pbtnFinish->setToolTip(SCREEN_FINISHED_TIP);
	m_pbtnFinish->setText(FINISHED_TIP);
	m_pBtnDrawRect = new QToolButton(this);
	m_pBtnDrawRect->setFixedSize(24, 21);
	m_pBtnDrawRect->setToolTip(SCREEN_RECT_TIP);

	m_pBtnDrawEllipse = new QToolButton(this);
	m_pBtnDrawEllipse->setFixedSize(24, 21);
	m_pBtnDrawEllipse->setToolTip(SCREEN_ELLIPSE_TIP);

	m_pBtnDrawArrow = new QToolButton(this);
	m_pBtnDrawArrow->setFixedSize(24, 21);
	m_pBtnDrawArrow->setToolTip(SCREEN_ARROE_TIP);

	m_pBtnDrawPath = new QToolButton(this);
	m_pBtnDrawPath->setFixedSize(24, 21);
	m_pBtnDrawPath->setToolTip(SCREEN_PATH_TIP);

	m_pBtnDrawText = new QToolButton(this);
	m_pBtnDrawText->setFixedSize(24, 21);
	m_pBtnDrawText->setToolTip(SCREEN_TEXT_TIP);

	m_pBtnRevoke = new QToolButton(this);
	m_pBtnRevoke->setFixedSize(24, 21);
	m_pBtnRevoke->setToolTip(SCREEN_REVOKE_TIP);

	m_pbtnSave->setFixedSize(24, 21);
	m_pbtnCancel->setFixedSize(24, 21);
	m_pbtnFinish->setFixedSize(70, 22);
	m_pSpliterOne->setFixedSize(2, 22);
	m_pspliterTwo->setFixedSize(2, 22);
	m_pSpliterOne->setScaledContents(true);
	m_pspliterTwo->setScaledContents(true);
	m_pSpliterOne->setPixmap(m_imagePath + "septal_line.png");
	m_pspliterTwo->setPixmap(m_imagePath + "septal_line.png");

	updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");
	updateToolBtnStytle(m_pBtnRevoke, "cacel.png", "cacel_enter.png", "cacel_down.png");

	updateToolBtnStytle(m_pbtnSave, "save.png", "save_enter.png", "save_down.png");
	updateToolBtnStytle(m_pbtnCancel, "exit.png", "exit_enter.png", "exit_down.png");
	updateToolBtnStytle(m_pbtnFinish, "finish.png", "finish_enter.png", "finish_down.png");

	//连接信号槽函数
	connect(m_pbtnSave, SIGNAL(clicked()), this, SLOT(savePixmap()), Qt::QueuedConnection);
	connect(m_pbtnCancel, SIGNAL(clicked()), this, SLOT(slotBtnCancelClicked()), Qt::DirectConnection);
	connect(m_pbtnFinish, SIGNAL(clicked()), this, SLOT(finishScreenShot()), Qt::DirectConnection);

	connect(m_pBtnDrawRect, SIGNAL(clicked()), this, SLOT(slotDrawRectClicked()), Qt::QueuedConnection);
	connect(m_pBtnDrawEllipse, SIGNAL(clicked()), this, SLOT(slotDrawEllipseClicked()), Qt::QueuedConnection);
	connect(m_pBtnDrawArrow, SIGNAL(clicked()), this, SLOT(slotDrawArrowClicked()), Qt::QueuedConnection);
	connect(m_pBtnDrawPath, SIGNAL(clicked()), this, SLOT(slotDrawPathClicked()), Qt::QueuedConnection);
	connect(m_pBtnDrawText, SIGNAL(clicked()), this, SLOT(slotDrawTextClicked()), Qt::QueuedConnection);
	connect(m_pBtnRevoke, SIGNAL(clicked()), this, SLOT(slotRevokeClicked()), Qt::QueuedConnection);

	m_ptoolBar = new QToolBar(this);
	QWidget *pNewWidget = new QWidget(this);
	pNewWidget->setFixedSize(3, 22);
	m_ptoolBar->addWidget(pNewWidget);
	m_ptoolBar->addWidget(m_pBtnDrawRect);
	m_ptoolBar->addWidget(m_pBtnDrawEllipse);
	m_ptoolBar->addWidget(m_pBtnDrawArrow);
	m_ptoolBar->addWidget(m_pBtnDrawPath);
	m_ptoolBar->addWidget(m_pBtnDrawText);
	m_ptoolBar->addWidget(m_pSpliterOne);          //分隔线
	m_ptoolBar->addWidget(m_pBtnRevoke);
	m_ptoolBar->addWidget(m_pbtnSave);
	m_ptoolBar->addWidget(m_pspliterTwo);          //分隔线
	m_ptoolBar->addWidget(m_pbtnCancel);
	m_ptoolBar->addWidget(m_pbtnFinish);
	m_ptoolBar->setFixedSize(infoWidth, infoHeight);

	QString strToolBarStyle = "QToolBar{border-image:url(" + m_imagePath + "screenshotbg.png); spacing:6px;}";
	m_ptoolBar->setStyleSheet(strToolBarStyle);
	m_ptoolBar->setMouseTracking(true);
	m_ptoolBar->setVisible(false);

	//add by yjt

	m_pSelectRectColorWidget = new SelectColorWidget(this);
	m_pSelectRectColorWidget->setFixedSize(232, 32);

	m_pSelectEllipseColorWidget = new SelectColorWidget(this);
	m_pSelectEllipseColorWidget->setFixedSize(232, 32);

	m_pSelectArrowColorWidget = new SelectColorWidget(this);
	m_pSelectArrowColorWidget->setFixedSize(232, 32);

	m_pSelectPathColorWidget = new SelectColorWidget(this);
	m_pSelectPathColorWidget->setFixedSize(232, 32);

	m_pSelectTextWidget = new SelectColorWidget(this, 1);
	//todo
	//m_pSelectTextWidget->LoadQssFile(QString::fromStdString((QSS_FILE_DIR_PATH+"fullScreen.qss" ).c_str()));
	m_pSelectTextWidget->setFixedSize(232, 32);

	m_pStackedWidget = new QStackedWidget(this);
	m_pStackedWidget->setFixedSize(232, 32);
	m_pStackedWidget->addWidget(m_pSelectRectColorWidget);
	m_pStackedWidget->addWidget(m_pSelectEllipseColorWidget);
	m_pStackedWidget->addWidget(m_pSelectArrowColorWidget);
	m_pStackedWidget->addWidget(m_pSelectPathColorWidget);
	m_pStackedWidget->addWidget(m_pSelectTextWidget);
	m_pStackedWidget->setHidden(true);

	//add by yjt
	m_drawWidget = new PaintWidgetScene(this);
	m_drawWidget->setItemIndexMethod(QGraphicsScene::NoIndex);

	m_pGraphicsView = new GraphicsViewWidget(m_drawWidget, this);
	m_pGraphicsView->setObjectName("GraphicsView");
	m_pGraphicsView->setStyleSheet("QGraphicsView#GraphicsView{background:transparent; border:0px;}");
	m_pGraphicsView->setHidden(true);
	m_pGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pGraphicsView->setRenderHint(QPainter::Antialiasing);//使用抗锯齿的方式渲染
	m_pGraphicsView->setCacheMode(QGraphicsView::CacheBackground);//设置缓存背景，这样可以加快渲染速度

	//文本编辑框
	m_pTextEdit = new QTextEdit(m_pGraphicsView);
	m_pTextEdit->setMinimumSize(60, 30);
	m_pTextEdit->resize(60, 30);
	m_pTextEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	m_pTextEdit->setStyleSheet("QTextEdit{background:transparent; border-image:url(" + m_imagePath + "textEditboder.png);border:2px;}");
	m_pTextEdit->setContentsMargins(0, 0, 0, 0);
	m_pTextEdit->setLineWrapMode(QTextEdit::WidgetWidth);

	m_pTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pTextEdit->setHidden(true);

	connect(m_pTextEdit, SIGNAL(textChanged()), this, SLOT(slotEditTextChanged()), Qt::QueuedConnection);

	qRegisterMetaType<Shape::Code>("Shape::Code");
	connect(this, SIGNAL(signalChangeCurrentShape(Shape::Code, QPen)), m_drawWidget, SLOT(slotSetCurrentShape(Shape::Code, QPen)), Qt::QueuedConnection);
	connect(this, SIGNAL(signalDeleteLastDraw()), m_drawWidget, SLOT(slotDelLastDraw()), Qt::QueuedConnection);
	connect(this, SIGNAL(signalSelectPenChanged(QPen)), m_drawWidget, SLOT(slotSetCurPen(QPen)), Qt::QueuedConnection);
	connect(this, SIGNAL(signalSelectFontChanged(QPen, QFont)), m_drawWidget, SLOT(slotSetCurFont(QPen, QFont)), Qt::QueuedConnection);
	connect(m_drawWidget, SIGNAL(signalLeftBtnPressed(QPointF, bool)), this, SLOT(slotSceneTextLeftBtnPressed(QPointF, bool)), Qt::QueuedConnection);
	connect(this, SIGNAL(signalAddTextToView(QString)), m_drawWidget, SLOT(slotAddText(QString)), Qt::DirectConnection);
	//Qpen改变信号槽函数
	connect(m_pSelectRectColorWidget, SIGNAL(signalSelectChange(QPen)), this, SLOT(slotSelectPenChanged(QPen)), Qt::QueuedConnection);
	connect(m_pSelectEllipseColorWidget, SIGNAL(signalSelectChange(QPen)), this, SLOT(slotSelectPenChanged(QPen)), Qt::QueuedConnection);
	connect(m_pSelectArrowColorWidget, SIGNAL(signalSelectChange(QPen)), this, SLOT(slotSelectPenChanged(QPen)), Qt::QueuedConnection);
	connect(m_pSelectPathColorWidget, SIGNAL(signalSelectChange(QPen)), this, SLOT(slotSelectPenChanged(QPen)), Qt::QueuedConnection);
	connect(m_pSelectTextWidget, SIGNAL(signalSelectFontChange(QPen, QFont)), this, SLOT(slotSelectFontChanged(QPen, QFont)), Qt::QueuedConnection);
}
void fullScreenWidget::updateToolBarText(){
	m_pbtnSave->setToolTip(SAVE_TIP);
	m_pbtnCancel->setToolTip(CANCEL_TIP);
	m_pbtnFinish->setToolTip(SCREEN_FINISHED_TIP);
	m_pbtnFinish->setText(FINISHED_TIP);
	m_pBtnDrawRect->setToolTip(SCREEN_RECT_TIP);
	m_pBtnDrawEllipse->setToolTip(SCREEN_ELLIPSE_TIP);
	m_pBtnDrawArrow->setToolTip(SCREEN_ARROE_TIP);
	m_pBtnDrawPath->setToolTip(SCREEN_PATH_TIP);
	m_pBtnDrawText->setToolTip(SCREEN_TEXT_TIP);
	m_pBtnRevoke->setToolTip(SCREEN_REVOKE_TIP);
}
void fullScreenWidget::updateToolBarPos()//更新工具栏的位置
{
	QDesktopWidget* desktopWidget = QApplication::desktop();
	//得到客户区矩形
	//QRect clientRect = desktopWidget->availableGeometry();
	//得到应用程序矩形
	QRect applicationRect = desktopWidget->screenGeometry();
	int x = selectedRect.right() - infoWidth;
	//int y = (applicationRect.bottom()-selectedRect.bottom())>infoHeight ? selectedRect.bottom()+8:(selectedRect.y() > infoHeight ? selectedRect.y()-infoHeight-8:selectedRect.y()-8);
	int y = (applicationRect.bottom() - selectedRect.bottom()) > infoHeight ? selectedRect.bottom() + 4 : (selectedRect.y() > infoHeight ? selectedRect.y() - infoHeight - 4 : selectedRect.y() - 4);
	m_ptoolBar->move(x, y);
	m_pStackedWidget->move(x, y + 28);
	m_ptoolBar->setVisible(true);
}
void fullScreenWidget::savePixmap()
{
	QPixmap pixmap;
	if (m_pGraphicsView->isVisible())
	{
		pixmap = QPixmap::grabWidget(m_pGraphicsView);
	}
	else
	{
		pixmap = shotPixmap;
	}

	QString fileName;
#ifndef _WIN32
	QString strTimeName = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
	QFileDialog dialog(this, "", QDir::homePath() + "/" + strTimeName + ".png");
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	//dialog.setFileMode(QFileDialog::Directory);
	dialog.setNameFilter(IMAGE_MSG_TIP + " (*.jpg *.png *.bmp)");
	dialog.setViewMode(QFileDialog::Detail);
	dialog.setWindowFlags(dialog.windowFlags() ^ Qt::WindowContextHelpButtonHint);
	dialog.setOption(QFileDialog::DontUseNativeDialog);
	dialog.setOption(QFileDialog::DontResolveSymlinks);
	dialog.setLabelText(QFileDialog::Reject, CANCEL);
	dialog.setWindowTitle(SAVE_TIP + IMAGE_MSG_TIP);
	//dialog.setDirectory(QDir::homePath());
	QStringList fileNames;
	if (dialog.exec())
		fileNames = dialog.selectedFiles();
	fileName = fileNames.isEmpty() ? "" : fileNames[0];
#else
	QString desktopPath =QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + QString::fromLocal8Bit("/screen.jpg");
	qDebug() << "++++++++++++++++++++" + desktopPath;
	fileName = QFileDialog::getSaveFileName(this, SAVE_TIP + IMAGE_MSG_TIP, desktopPath, tr("Images (*.jpg *.png *.bmp)"));
#endif
	qDebug() << "=============== "<<fileName;
	if (fileName.isNull())
		return;
	qDebug() << "QPixmap isNull  = " << pixmap.isNull();
	bool bret = pixmap.save(fileName);
	qDebug() << "bret = " << bret;
	if ( !bret)
	{
		qDebug() << "=====SAVE======= " << fileName<<" Failed!";
	}
	//退出截屏
	exitShotScreen(true);
}

void fullScreenWidget::loadBackgroundPixmap(const QPixmap &bgPixmap)
{
	loadBackgroundPixmap(bgPixmap, 0, 0, m_width, m_height);
}

void fullScreenWidget::loadBackgroundPixmap(const QPixmap &bgPixmap, int x, int y, int width, int height)
{
	loadPixmap = bgPixmap;
	screenx = x;
	screeny = y;
	screenwidth = width;
	screenheight = height;
	initFullScreenWidget();
}

QPixmap fullScreenWidget::getFullScreenPixmap()
{
	loadLanguage();
	updateToolBarText();
	initFullScreenWidget();
	QPixmap result = QPixmap();
	//int width, height;
	//width = QApplication::desktop()->width();
	//height = QApplication::desktop()->height();
	//QScreen* screen = QApplication::primaryScreen();
	//result = screen->grabWindow(0, 0, 0, width, height); //抓取当前屏幕的图片
	QList<QScreen*> list = QApplication::screens();
	if ( list.size())
	{
		QScreen* screen = list.at(0);
		m_width  = list.at(0)->geometry().width();
		m_height = list.at(0)->geometry().height();
		result = list.at(0)->grabWindow(0, 0, 0, m_width, m_height);
	}
	return result;
}

void fullScreenWidget::paintEvent(QPaintEvent *event)
{
	if (moveBeginPoint.isNull() && moveBeginPoint.isNull() && finishControl == currentShotState)
		return;
	QColor shadowColor;
	shadowColor = QColor(0, 0, 0, 153); //阴影颜色设置
	painter.begin(this); //进行重绘
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(QColor(19, 139, 237), 2, Qt::SolidLine, Qt::FlatCap));//设置画笔
	painter.drawPixmap(screenx, screeny, loadPixmap); //将背景图片画到窗体上
	painter.fillRect(screenx, screeny, screenwidth, screenheight, shadowColor); //画影罩效果

	switch (currentShotState){
	case initShot:
	{
					 break;
	}
	case beginShot:
	case finishShot:
	{
					   selectedRect = getRect(beginPoint, endPoint); //获取选区
					   drawSelectedPixmap();
					   break;
	}
	case beginMoveShot:
	case finishMoveShot:
	{
						   selectedRect = getMoveAllSelectedRect(); //获取选区
						   drawSelectedPixmap();
						   break;
	}
	case beginControl:
	case finishControl:
	{
						  selectedRect = getMoveControlSelectedRect();
						  drawSelectedPixmap();
						  break;
	}
	default:
	{
			   break;
	}
	}
	//qDebug()<<"Enter fullScreenWidget::paintEvent,currentShotState:"<<currentShotState;
	drawXYWHInfo(); //打印坐标信息
	painter.end();  //重绘结束
	if (finishMoveShot == currentShotState || finishControl == currentShotState){
		updateBeginEndPointValue(selectedRect); //当移动完选区后，更新beginPoint,endPoint;为下一次移动做准备工作
	}
}

void fullScreenWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
	case Qt::Key_Escape:
		{
			exitShotScreen(true);
		    break;
		}
	default:
		QWidget::keyPressEvent(event);
	}
}

void fullScreenWidget::mousePressEvent(QMouseEvent *event)
{
	//当开始进行拖动进行选择区域时,确定开始选取的beginPoint坐标
	if (event->button() == Qt::LeftButton && currentShotState == initShot && !m_bIsShapeBtnClicked){
		currentShotState = beginShot; //设置当前状态为beginShot状态
		beginPoint = event->pos();
	}

	//移动选区改变选区的所在位置
	if (event->button() == Qt::LeftButton && isInSelectedRect(event->pos()) &&
		getMoveControlState(event->pos()) == moveControl0 && !m_bIsShapeBtnClicked){
		currentShotState = beginMoveShot; //启用开始移动选取选项,beginMoveShot状态
		moveBeginPoint = event->pos();
	}
	//移动控制点改变选区大小
	if (event->button() == Qt::LeftButton && getMoveControlState(event->pos()) != moveControl0 && !m_bIsShapeBtnClicked){
		currentShotState = beginControl; //开始移动控制点
		controlValue = getMoveControlState(event->pos());
		moveBeginPoint = event->pos();
	}

	// qDebug()<<"mousePressEvent:beginPoint"<<beginPoint;
	// qDebug()<<"mousePressEvent:moveBeginPoint"<<moveBeginPoint;
}

void fullScreenWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && currentShotState == beginShot && !m_bIsShapeBtnClicked){
		currentShotState = finishShot;
		endPoint = event->pos();
		update();
		updateToolBarPos();
	}

	if (event->button() == Qt::LeftButton && currentShotState == beginMoveShot&& !m_bIsShapeBtnClicked){
		currentShotState = finishMoveShot;
		moveEndPoint = event->pos();
		update();
		updateToolBarPos();
	}

	//当前状态为beginControl状态时，设置状态为finishControl
	if (event->button() == Qt::LeftButton && currentShotState == beginControl&& !m_bIsShapeBtnClicked){
		currentShotState = finishControl;
		moveEndPoint = event->pos();
		update();
		updateToolBarPos();
	}
	m_ptoolBar->setFocus();
	//qDebug()<<"mouseReleaseEvent:endPoint"<<endPoint;
	// qDebug()<<"mouseReleaseEvent:moveEndPoint"<<moveEndPoint;
}

void fullScreenWidget::mouseMoveEvent(QMouseEvent *event)
{
	//当拖动时，动态的更新所选择的区域
	if (currentShotState == beginShot && !m_bIsShapeBtnClicked){
		endPoint = event->pos();
		update();
		updateToolBarPos();
	}

	//当确定选区后，对选区进行移动操作
	if (currentShotState == beginMoveShot && !m_bIsShapeBtnClicked){
		moveEndPoint = event->pos();
		update();
		updateToolBarPos();
	}

	if (currentShotState == beginControl && !m_bIsShapeBtnClicked){
		moveEndPoint = event->pos();
		update();
		m_ptoolBar->setVisible(false);
		m_pStackedWidget->setHidden(true);
		m_pGraphicsView->setHidden(true);
	}

	if (currentShotState == finishControl && !m_bIsShapeBtnClicked){
		currentShotState = finishMoveShot;
		update();
		updateToolBarPos();
	}
	if (!m_bIsShapeBtnClicked)
	{
		updateMouseShape(event->pos()); //修改鼠标的形状
	}

	setMouseTracking(true);
	m_ptoolBar->setFocus();
	// qDebug()<<"mouseMoveEvent:endPoint"<<endPoint;
	// qDebug()<<"mouseMoveEvent:moveEndPoint"<<moveEndPoint;
}

void fullScreenWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	finishScreenShot();
}
void fullScreenWidget::contextMenuEvent(QContextMenuEvent *event)
{
	if (selectedRect.isEmpty())
	{
		exitShotScreen(true);
	}
	else
	{
		cancelSelectedRect();
	}
}

QRect fullScreenWidget::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
	int x, y, width, height;
	width = qAbs(beginPoint.x() - endPoint.x());
	height = qAbs(beginPoint.y() - endPoint.y());
	x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
	y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

	return QRect(x, y, width, height);
}

void fullScreenWidget::initFullScreenWidget()
{
	QPixmapCache::setCacheLimit(1);
	currentShotState = initShot;
	controlValue = moveControl0;
	beginPoint = QPoint(0, 0);
	endPoint = QPoint(0, 0);
	moveBeginPoint = QPoint(0, 0);
	moveEndPoint = QPoint(0, 0);
	selectedRect = QRect(0, 0, 0, 0);

	tlRect = QRect(0, 0, 0, 0); //左上点
	trRect = QRect(0, 0, 0, 0); //上右点
	blRect = QRect(0, 0, 0, 0); //左下点
	brRect = QRect(0, 0, 0, 0); //右下点
	tcRect = QRect(0, 0, 0, 0); //上中点
	bcRect = QRect(0, 0, 0, 0); //下中点
	lcRect = QRect(0, 0, 0, 0); //左中点
	rcRect = QRect(0, 0, 0, 0); //右中点
	/*setCursor(Qt::CrossCursor);*/
	updateMouseStytle();
}

bool fullScreenWidget::isInSelectedRect(const QPoint &point)
{
	int x, y;
	QRect selectedRect;
	if (currentShotState == initShot || currentShotState == beginShot)
		return false;

	selectedRect = getSelectedRect();
	x = point.x();
	y = point.y();

	return selectedRect.contains(x, y);
}

void fullScreenWidget::cancelSelectedRect()
{
	initFullScreenWidget();
	m_ptoolBar->setVisible(false);
	m_pStackedWidget->setHidden(true);
	m_pGraphicsView->setHidden(true);
	m_pTextEdit->setHidden(true);
	m_drawWidget->clear();
	m_bIsShapeBtnClicked = false;
	m_iEditSetHeigth = 0;
	updateToolStyleAndColorWidget();  //将绘画按钮选中状态清空
	update(); //进行重绘，将选取区域去掉
}
//退出截图
void fullScreenWidget::exitShotScreen(bool iscancel)
{
	initFullScreenWidget();
	hide();
	m_ptoolBar->setVisible(false);
	m_pStackedWidget->setHidden(true);
	m_pGraphicsView->setHidden(true);
	m_pTextEdit->setHidden(true);
	m_drawWidget->clear();
	m_bIsShapeBtnClicked = false;
	m_iEditSetHeigth = 0;
	updateToolStyleAndColorWidget();  //将绘画按钮选中状态清空

	m_bIsShapeBtnClicked = false;

	setCursor(Qt::ArrowCursor);
	loadPixmap = QPixmap();
	if (!iscancel)
	{
#if defined(__linux__) || defined(_WIN32)
		emit exitPixmap();
		writeToServer(QString::number(0));
#else
		emit exitPixmap();          //发送退出屏幕截图信号 add by yjt
#endif
	}
	else{
#if defined(__linux__) || defined(_WIN32)
		emit exitPixmap(); 
		writeToServer(QString::number(1));
#else
		exit(1);
#endif
	}
}
//client端发送数据
void fullScreenWidget::writeToServer(QString message)
{
	emit finishedshot(message);
}
QRect fullScreenWidget::getSelectedRect()
{
	if (currentShotState == beginMoveShot){
		return getMoveAllSelectedRect();
	}
	else if (currentShotState == beginControl){
		return getMoveControlSelectedRect();
	}
	else{
		return getRect(beginPoint, endPoint);
	}
}

void fullScreenWidget::updateBeginEndPointValue(const QRect &rect)
{

	beginPoint = rect.topLeft();
	endPoint = rect.bottomRight();

	moveBeginPoint = QPoint(0, 0);
	moveEndPoint = QPoint(0, 0);
	qDebug() <<"updateBeginEndPointValue  "<< "beginPoint:" << beginPoint << "endpoint:" << endPoint;
	qDebug() << "updateBeginEndPointValue  " << "moveBeginPoint:" << moveBeginPoint << "moveEndPoint:" << moveEndPoint;
}

void fullScreenWidget::checkMoveEndPoint()
{
	int x, y;
	QRect selectedRect = getRect(beginPoint, endPoint);
	QPoint bottomRightPoint = selectedRect.bottomRight();
	x = moveEndPoint.x() - moveBeginPoint.x();
	y = moveEndPoint.y() - moveBeginPoint.y();

	if (x + selectedRect.x() < 0){ //当移动后X坐标小于零时，则出现选区丢失，则计算出moveEndPoint的X最大坐标值，进行赋值
		moveEndPoint.setX(qAbs(selectedRect.x() - moveBeginPoint.x()));
	}

	if (y + selectedRect.y() < 0){ //当移动后Y坐标小于零时，则出现选区丢失，则计算出moveEndPoint的Y最大坐标值，进行赋值
		moveEndPoint.setY(qAbs(selectedRect.y() - moveBeginPoint.y()));
	}

	if (x + bottomRightPoint.x() > screenwidth){ //当移动选区后，出现超出整个屏幕的右面时，设置moveEndPoint的X的最大坐标
		moveEndPoint.setX(screenwidth - bottomRightPoint.x() + moveBeginPoint.x());
	}

	if (y + bottomRightPoint.y() > screenheight){ //当移动选区后，出现超出整个屏幕的下面时，设置moveEndPoint的Y的最大坐标值
		moveEndPoint.setY(screenheight - bottomRightPoint.y() + moveBeginPoint.y());
	}
}

void fullScreenWidget::draw8ControlPoint(const QRect &rect)
{
	int x, y;
	QColor color = QColor(19, 139, 237); //画点的颜色设置
	QPoint tlPoint = rect.topLeft(); //左上点
	QPoint trPoint = rect.topRight(); //右上点
	QPoint blPoint = rect.bottomLeft(); //左下点
	QPoint brPoint = rect.bottomRight(); //右下点

	x = (tlPoint.x() + trPoint.x()) / 2;
	y = tlPoint.y();
	QPoint tcPoint = QPoint(x, y);

	x = (blPoint.x() + brPoint.x()) / 2;
	y = blPoint.y();
	QPoint bcPoint = QPoint(x, y);

	x = tlPoint.x();
	y = (tlPoint.y() + blPoint.y()) / 2;
	QPoint lcPoint = QPoint(x, y);

	x = trPoint.x();
	y = (trPoint.y() + brPoint.y()) / 2;
	QPoint rcPoint = QPoint(x, y);

	tlRect = QRect(tlPoint.x() - 2, tlPoint.y() - 2, 6, 6); //左上点
	trRect = QRect(trPoint.x() - 2, trPoint.y() - 2, 6, 6); //右上点
	blRect = QRect(blPoint.x() - 2, blPoint.y() - 2, 6, 6); //左下点
	brRect = QRect(brPoint.x() - 2, brPoint.y() - 2, 6, 6); //右下点
	tcRect = QRect(tcPoint.x() - 2, tcPoint.y() - 2, 6, 6); //上中点
	bcRect = QRect(bcPoint.x() - 2, bcPoint.y() - 2, 6, 6); //下中点
	lcRect = QRect(lcPoint.x() - 2, lcPoint.y() - 2, 6, 6);//左中点
	rcRect = QRect(rcPoint.x() - 2, rcPoint.y() - 2, 6, 6); //右中点

	painter.fillRect(tlRect, color);
	painter.fillRect(trRect, color);
	painter.fillRect(blRect, color);
	painter.fillRect(brRect, color);
	painter.fillRect(tcRect, color);
	painter.fillRect(bcRect, color);
	painter.fillRect(lcRect, color);
	painter.fillRect(rcRect, color);
}

void fullScreenWidget::updateMouseShape(const QPoint &point)
{
	switch (currentShotState){
	case initShot:
	case beginShot:
	{
					  updateMouseStytle();
					  break;
	}
	case beginMoveShot:
	{
						  setCursor(Qt::OpenHandCursor);
						  break;
	}
	case finishShot:
	case finishMoveShot:
	case finishControl:
	{
						  if (getSelectedRect().contains(point))
						  {
							  setCursor(Qt::OpenHandCursor);
						  }
						  else
						  {
							  updateMoveControlMouseShape(getMoveControlState(point));
						  }
						  break;
	}
	case beginControl:
	{
						 updateMoveControlMouseShape(controlValue); //调用函数对移动8个控制点进行鼠标状态的改变
						 break;
	}
	default:
	{
			   updateMouseStytle();
			   break;
	}
	}
}

void fullScreenWidget::updateMoveControlMouseShape(controlPointEnum controlValue){
	switch (controlValue){
	case moveControl1:
	case moveControl5:
		setCursor(Qt::SizeFDiagCursor);
		break;
	case moveControl2:
	case moveControl6:
		setCursor(Qt::SizeVerCursor);
		break;
	case moveControl3:
	case moveControl7:
		setCursor(Qt::SizeBDiagCursor);
		break;
	case moveControl4:
	case moveControl8:
		setCursor(Qt::SizeHorCursor);
		break;
	default:
		updateMouseStytle();
		break;
	}
}

fullScreenWidget::controlPointEnum fullScreenWidget::getMoveControlState(const QPoint &point)
{
	fullScreenWidget::controlPointEnum result = moveControl0;
	if (currentShotState == initShot || currentShotState == beginShot)  {
		result = moveControl0;
	}
	else if (tlRect.contains(point)){
		result = moveControl1;
	}
	else if (tcRect.contains(point)){
		result = moveControl2;
	}
	else if (trRect.contains(point)){
		result = moveControl3;
	}
	else if (rcRect.contains(point)){
		result = moveControl4;
	}
	else if (brRect.contains(point)){
		result = moveControl5;
	}
	else if (bcRect.contains(point)){
		result = moveControl6;
	}
	else if (blRect.contains(point)){
		result = moveControl7;
	}
	else if (lcRect.contains(point)){
		result = moveControl8;
	}
	else
	{
		result = moveControl0;
	}

	return result;
}

QRect fullScreenWidget::getMoveAllSelectedRect(void)
{
	QRect result;
	QPoint tmpBeginPoint, tmpEndPoint;
	int moveX, moveY;
	checkMoveEndPoint(); //对移动选区进行判断，当移动的选区超出边界，则停止移动
	moveX = moveEndPoint.x() - moveBeginPoint.x();
	moveY = moveEndPoint.y() - moveBeginPoint.y();
	tmpBeginPoint.setX(beginPoint.x() + moveX);
	tmpBeginPoint.setY(beginPoint.y() + moveY);
	tmpEndPoint.setX(endPoint.x() + moveX);
	tmpEndPoint.setY(endPoint.y() + moveY);

	result = getRect(tmpBeginPoint, tmpEndPoint);
	return result;
}

QRect fullScreenWidget::getMoveControlSelectedRect(void)
{
	int x, y, w, h;
	QRect rect = getRect(beginPoint, endPoint);
	QRect result;
	switch (controlValue){
	case moveControl1:
		result = getRect(rect.bottomRight(), moveEndPoint);
		qDebug() << "moveControl1";
		break;
	case moveControl2:
		x = rect.x();
		y = getMinValue(moveEndPoint.y(), rect.bottomRight().y());
		w = rect.width();
		h = qAbs(moveEndPoint.y() - rect.bottomRight().y());
		result = QRect(x, y, w, h); //获取选区
		qDebug() << "moveControl2";
		break;
	case moveControl3:
		result = getRect(rect.bottomLeft(), moveEndPoint);
		qDebug() << "moveControl3";
		break;
	case moveControl4:
		x = getMinValue(rect.x(), moveEndPoint.x());
		y = rect.y();
		w = qAbs(rect.bottomLeft().x() - moveEndPoint.x());
		h = rect.height();
		result = QRect(x, y, w, h); //获取选区
		qDebug() << "moveControl4";
		break;
	case moveControl5:
		result = getRect(rect.topLeft(), moveEndPoint);
		qDebug() << "moveControl5";
		break;
	case moveControl6:
		x = rect.x();
		y = getMinValue(rect.y(), moveEndPoint.y());
		w = rect.width();
		h = qAbs(moveEndPoint.y() - rect.topLeft().y());
		result = QRect(x, y, w, h); //获取选区
		qDebug() << "moveControl6";
		break;
	case moveControl7:
		result = getRect(moveEndPoint, rect.topRight());
		qDebug() << "moveControl7";
		break;
	case moveControl8:
		x = getMinValue(moveEndPoint.x(), rect.bottomRight().x());
		y = rect.y();
		w = qAbs(rect.bottomRight().x() - moveEndPoint.x());
		h = rect.height();
		result = QRect(x, y, w, h); //获取选区
		qDebug() << "moveControl8";
		break;
	default:
		result = getRect(beginPoint, endPoint);
		qDebug() << "default";
		break;
	}
	qDebug() << "getMoveControlSelectedRect" << result << "moveEndPoint" << moveEndPoint;
	return result;
}

int fullScreenWidget::getMinValue(int num1, int num2)
{
	return num1<num2 ? num1 : num2;
}

int fullScreenWidget::getMaxValue(int num1, int num2)
{
	return num1>num2 ? num1 : num2;
}

void fullScreenWidget::drawSelectedPixmap(void)
{
	painter.drawRect(selectedRect); //画选中的矩形框
	shotPixmap = loadPixmap.copy(selectedRect);  //更新选区的Pixmap
	if (selectedRect.width() && selectedRect.height()){
		painter.drawPixmap(selectedRect.topLeft(), shotPixmap); //画选中区域的图片
	}
	draw8ControlPoint(selectedRect); //画出选区的8个控制点
}
void fullScreenWidget::updateMouseStytle() //更新鼠标样式
{
	setCursor(Qt::ArrowCursor);
	return;
	static QCursor cursor;
	static int i = 0;
	if (i == 0)
	{
		i = 1;
		QString strPicPath;
		QPixmap pixmap;
		strPicPath = QString::fromStdString("mouse.png");
		pixmap.load(strPicPath);
		cursor = QCursor(pixmap);
	}
	if (i == 1)
	{
		setCursor(cursor);
	}
}
void fullScreenWidget::drawXYWHInfo(void)
{
	int x, y;
	int disInfoHeight = 20, disInfoWidth = 70;
	QColor color = QColor(40, 40, 40, 153);
	QRect rect;
	QString strTipsText;
	switch (currentShotState){
	case beginShot:
	case finishShot:
	case beginMoveShot:
	case finishMoveShot:
	case beginControl:
	case finishControl:
		x = selectedRect.x();
		y = selectedRect.y() > disInfoHeight ? selectedRect.y() - disInfoHeight : selectedRect.y();
		rect = QRect(x, y, disInfoWidth, disInfoHeight);
		strTipsText = QString(tr("%1x%2")).arg(selectedRect.width(), 4).arg(selectedRect.height(), 4);
		painter.fillRect(rect, color);
		painter.setPen(QPen(Qt::white));//设置画笔的颜色为黑色
		painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, strTipsText);
		break;
	default:
		break;
	}
}

//更新按钮的样式
void fullScreenWidget::updateToolBtnStytle(QToolButton* &toolBtn, QString picNormal, QString PicHot, QString PicPressed)
{
	QString strStytleSheet = "QToolButton{border-image:url(" + m_imagePath;
	strStytleSheet += picNormal;
	strStytleSheet += ");}QToolButton:hover{border-image:url(" + m_imagePath;
	strStytleSheet += PicHot;
	strStytleSheet += ");}QToolButton:hover{border-image:url(" + m_imagePath;
	strStytleSheet += PicPressed;
	strStytleSheet += ");}";
	toolBtn->setStyleSheet(strStytleSheet);
}
void fullScreenWidget::finishScreenShot()
{
	if (currentShotState == finishShot || currentShotState == finishMoveShot || currentShotState == finishControl){
		QPixmap pixmap;
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
		if (m_pGraphicsView->isVisible())
		{
			pixmap = QPixmap::grabWidget(m_pGraphicsView);
			qDebug() << "=====pixmap============";
		}
		else
		{
			pixmap = shotPixmap;
			qDebug() << "=====shotPixmap============";
		}
		//////////linux下以文件形式传递，win下用剪切板传递数据
 #ifdef _WIN32
 		//将截图黏贴至剪切板
 		QClipboard *tmpClipboard = QApplication::clipboard();
 		tmpClipboard->setPixmap(pixmap);
#endif
 //#else
	   QString appPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#if defined(__APPLE__)
		appPath.replace("Application Support","Containers/com.vrv.linkood/Data/");
#endif
		appPath.replace("screenshot", "CPPCC");
		qDebug() << "====Srcreenshot Path:========" << appPath;
		QString strSavePath = appPath + "/temp_screenshot.png";
		pixmap.save(strSavePath);
//#endif 
		//当完成时发送finishPixmap信号
		//emit finishPixmap(pixmap);
		qDebug() << "send Shot Picture,currentShotState:" << currentShotState;
		exitShotScreen();
	}
}
void fullScreenWidget::updateToolStyleAndColorWidget()
{
	updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");
}
void fullScreenWidget::slotDrawRectClicked()
{
	if (m_pSelectRectColorWidget->isVisible())
	{
		m_pStackedWidget->setHidden(true);
		updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
		return;
	}
	if (m_pTextEdit->isVisible())
	{
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
	}
	if ((NULL != m_pGraphicsView) && !m_pGraphicsView->isVisible())
	{
		ShowDrawWidget();
	}
	m_pStackedWidget->setVisible(true);
	m_pStackedWidget->setCurrentIndex(0);
	m_bIsShapeBtnClicked = true;
	updateToolBtnStytle(m_pBtnDrawRect, "box_down.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");

	m_curPen = m_pSelectRectColorWidget->GetCurPen();
	emit signalChangeCurrentShape(Shape::Rect, m_curPen);
}
void fullScreenWidget::slotDrawEllipseClicked()
{
	if (m_pSelectEllipseColorWidget->isVisible())
	{
		m_pStackedWidget->setHidden(true);
		updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
		return;
	}
	if (m_pTextEdit->isVisible())
	{
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
	}
	if ((NULL != m_pGraphicsView) && !m_pGraphicsView->isVisible())
	{
		ShowDrawWidget();
	}

	m_bIsShapeBtnClicked = true;

	updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring_down.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");
	m_pStackedWidget->setVisible(true);
	m_pStackedWidget->setCurrentIndex(1);
	m_curPen = m_pSelectEllipseColorWidget->GetCurPen();

	emit signalChangeCurrentShape(Shape::Ellipse, m_curPen);
}
void fullScreenWidget::slotDrawArrowClicked()
{
	if (m_pSelectArrowColorWidget->isVisible())
	{
		m_pStackedWidget->setHidden(true);
		updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
		return;
	}
	if (m_pTextEdit->isVisible())
	{
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
	}
	if ((NULL != m_pGraphicsView) && !m_pGraphicsView->isVisible())
	{
		ShowDrawWidget();
	}
	m_bIsShapeBtnClicked = true;

	updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow_down.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");
	m_pStackedWidget->setVisible(true);
	m_pStackedWidget->setCurrentIndex(2);

	m_curPen = m_pSelectArrowColorWidget->GetCurPen();
	emit signalChangeCurrentShape(Shape::Arrow, m_curPen);
}

void fullScreenWidget::slotDrawPathClicked()
{
	if (m_pSelectPathColorWidget->isVisible())
	{
		m_pStackedWidget->setHidden(true);
		updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
		return;
	}
	if (m_pTextEdit->isVisible())
	{
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
	}
	if ((NULL != m_pGraphicsView) && !m_pGraphicsView->isVisible())
	{
		ShowDrawWidget();
	}
	m_bIsShapeBtnClicked = true;

	updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path_down.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");
	m_pStackedWidget->setVisible(true);
	m_pStackedWidget->setCurrentIndex(3);

	m_curPen = m_pSelectPathColorWidget->GetCurPen();
	emit signalChangeCurrentShape(Shape::PathBrush, m_curPen);
}
void fullScreenWidget::slotDrawTextClicked()
{
	if (m_pTextEdit->isVisible())
	{
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
	}
	if (m_pSelectTextWidget->isVisible())
	{
		m_pStackedWidget->setHidden(true);
		updateToolBtnStytle(m_pBtnDrawText, "text.png", "text_enter.png", "text_down.png");
		return;
	}
	if ((NULL != m_pGraphicsView) && !m_pGraphicsView->isVisible())
	{
		ShowDrawWidget();
	}
	m_bIsShapeBtnClicked = true;

	updateToolBtnStytle(m_pBtnDrawRect, "box.png", "box_enter.png", "box_down.png");
	updateToolBtnStytle(m_pBtnDrawEllipse, "ring.png", "ring_enter.png", "ring_down.png");
	updateToolBtnStytle(m_pBtnDrawArrow, "paintedArrow.png", "paintedArrow_enter.png", "paintedArrow_down.png");
	updateToolBtnStytle(m_pBtnDrawPath, "path.png", "path_enter.png", "path_down.png");
	updateToolBtnStytle(m_pBtnDrawText, "text_down.png", "text_enter.png", "text_down.png");
	m_pStackedWidget->setVisible(true);
	m_pStackedWidget->setCurrentIndex(4);
	m_curPen = m_pSelectTextWidget->GetCurPen();
	m_curFont = m_pSelectTextWidget->GetCurFont();

	m_pTextEdit->setTextColor(m_curPen.color());
	m_pTextEdit->setFont(m_curFont);

	emit signalChangeCurrentShape(Shape::Text, m_curPen);
}

void fullScreenWidget::slotRevokeClicked()
{
	if (m_pGraphicsView->isVisible())
	{
		if (m_pTextEdit->isVisible())
		{
			m_pTextEdit->setHidden(true);
			m_iEditSetHeigth = 0;
			m_pTextEdit->resize(50, 30);
			m_pTextEdit->clear();
			return;
		}
		emit signalDeleteLastDraw();
	}
}
void fullScreenWidget::slotSelectPenChanged(QPen pen)
{
	m_curPen = pen;
	emit signalSelectPenChanged(m_curPen);
}
void fullScreenWidget::slotSelectFontChanged(QPen pen, QFont font)
{
	m_curPen = pen;
	m_curFont = font;
	m_pTextEdit->setFont(m_curFont);
	m_pTextEdit->setTextColor(m_curPen.color());
	QString text = m_pTextEdit->toPlainText();
	m_pTextEdit->clear();
	m_pTextEdit->append(text);
	emit signalSelectFontChanged(m_curPen, m_curFont);
}
void fullScreenWidget::slotSceneTextLeftBtnPressed(QPointF pos, bool bIsPressed)
{
	if (bIsPressed)
	{
		m_iEditSetHeigth = 0;
		m_pTextEdit->setTextColor(m_curPen.color());
		m_pTextEdit->setFont(m_curFont);
		m_pTextEdit->move(pos.x(), pos.y());
		int widthLine = m_pGraphicsView->width() - pos.x();
		m_pTextEdit->setLineWrapColumnOrWidth(widthLine);
		m_pTextEdit->setMaximumSize(m_pGraphicsView->width() - pos.x(), m_pGraphicsView->height() - pos.y() - 10);
		m_pTextEdit->setVisible(true);
		m_pTextEdit->setFocus();
	}
	else
	{
		//输入的文本还有处理，添加到View上
		if (m_pTextEdit->isVisible())
		{
			QString content = m_pTextEdit->toPlainText();
			emit signalAddTextToView(content);
		}
		m_pTextEdit->setHidden(true);
		m_iEditSetHeigth = 0;
		m_pTextEdit->resize(50, 30);
		m_pTextEdit->clear();
	}


}

void fullScreenWidget::slotEditTextChanged()
{

	QString text = m_pTextEdit->toPlainText();
	QFontMetrics fontme(m_pTextEdit->font());
	int curWidth = fontme.width(text);

	int curHeight = m_pTextEdit->height() + 20;
	int maxWidth = m_pTextEdit->maximumWidth() - 18;      //减去与边框的间距
	int minWidth = m_pTextEdit->minimumWidth();
	if (curWidth < maxWidth)
	{
		m_pTextEdit->resize(curWidth + 50, m_pTextEdit->height());
	}
	else
	{
		m_iEditSetHeigth++;
		if (m_iEditSetHeigth < 2)
		{
			m_pTextEdit->resize(m_pTextEdit->width(), 25 * 2);
			m_iEditSecondLinHeigth = m_pTextEdit->height();
		}
		else
		{
			int tempWidth = curWidth / (maxWidth);
			m_pTextEdit->resize(m_pTextEdit->width(), 20 * tempWidth + m_iEditSecondLinHeigth);
		}

	}

}
void fullScreenWidget::ShowDrawWidget()
{
	QRectF rect = getRect(beginPoint, endPoint);
	qDebug() << "ShowDrawWidget: = " << rect.x() << rect.y() << rect.width() << rect.height();

	int width = shotPixmap.width();
	int heit = shotPixmap.height();

	m_drawWidget->clear();
	//这一句不能用
	// m_drawWidget->setSceneRect(rect);
	m_drawWidget->update(rect);
	m_drawWidget->SetVisibleRect(QRectF(0, 0, rect.width(), rect.height()));
	m_drawWidget->addPixmap(shotPixmap);


	m_pGraphicsView->move(rect.x(), rect.y());
	m_pGraphicsView->setFixedSize(width, heit);

	m_pGraphicsView->setScene(m_drawWidget);
	//m_pGraphicsView->setGeometry(rect.x(), rect.y(), shotPixmap.width(), shotPixmap.height());
	//m_pGraphicsView->setFixedSize(width, heit);
	//m_pGraphicsView->setSceneRect(rect);
	m_pGraphicsView->show();
}
void fullScreenWidget::slotBtnCancelClicked(){
	exitShotScreen(true);
}
//获取系统设置语言
int fullScreenWidget::getLanguage(){
	int ret = 0;//默认主题色值
	QString inifilepath(QApplication::applicationDirPath());
	QSharedPointer<QSettings> configptr;
	inifilepath.append("/config.ini");
	qDebug() << "inifilepath" << inifilepath;
	configptr.reset(new QSettings(inifilepath, QSettings::IniFormat));
	if (!configptr.isNull())
	{
		bool bret = configptr->contains(QString::fromLocal8Bit("/system/language"));
		if (bret)
		{
			ret = configptr->value(QString::fromLocal8Bit("/system/language")).toInt();
			qDebug() << "language" << ret;
		}
	}
	return ret;
}
void fullScreenWidget::loadLanguage(){
	bool isChinise = (0 == getLanguage()) ? true : false;
	qDebug() << "isChinise" << isChinise;
	utils::Error::InitErrInfo(isChinise);
}
void fullScreenWidget::delay_MSec(unsigned int msec)
{
	QTime _Timer = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < _Timer)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}