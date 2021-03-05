#ifndef FULLSCREENWIDGET_H
#define FULLSCREENWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPoint>
#include <QtGui>
#include <QPainter>
#include <QBrush>
#include <QEvent>
#include <QMouseEvent>
#include <QToolBar>
#include "DrawShapeWidget.h"
class Shape;
class fullScreenWidget : public QWidget{

  Q_OBJECT
  
  private:
  fullScreenWidget(); //构造函数
  static fullScreenWidget *m_instance;
  void loadLanguage();
  int  getLanguage();
  void updateToolBarText();
public:
  static fullScreenWidget* GetInstance();
  enum shotState{initShot,beginShot,finishShot,endShot,beginMoveShot,finishMoveShot,beginControl,finishControl}; //进行截屏的状态
  //移动选区中的8个控制点，按照顺时针方向从左上控制点到左中控制点分配编号为1～8
  enum controlPointEnum{moveControl0,moveControl1,moveControl2,moveControl3,moveControl4,moveControl5,moveControl6,moveControl7,moveControl8};
  QPixmap getFullScreenPixmap(); //获取全屏的Pixmap
  void writeToServer(QString message);
  public slots:
  void loadBackgroundPixmap(const QPixmap &bgPixmap);//加载背景Pixmap槽函数
  void loadBackgroundPixmap(const QPixmap &bgPixmap, int x, int y, int width, int height); //加载背景pixmap槽函数，设置x,y,width,height
  void exitShotScreen(bool iscancel=false);	//退出截图
  void savePixmap();	   //保选取行为的方法
  void finishScreenShot();
  
  signals:
  void finishPixmap(const QPixmap finishPixmap); //完成切图后的图片,发送信号给连接者
  void exitPixmap();   //退出截图后，发送信号给连接者 add by yjt
  void finishedshot(QString cmd);
  ///////////////////////add by yjt
  void signalChangeCurrentShape(Shape::Code, QPen pen);     //绘制图形改变信号
  void signalDeleteLastDraw();                                //撤销绘制信号
  void signalSelectPenChanged(QPen);				//线宽度或颜色改变信号
  void signalSelectFontChanged(QPen, QFont);
  void signalAddTextToView(QString);
  ///////////////////////////////
  private:
  //选区框的8个点选取
  QRect tlRect; //左上点1
  QRect trRect; //右上点1
  QRect blRect; //左下点1
  QRect brRect; //右下点1
  QRect tcRect; //上中点1
  QRect bcRect; //下中点1
  QRect lcRect;//左中点1
  QRect rcRect; //右中点1

  QPainter painter;
  QPoint beginPoint,endPoint,moveBeginPoint,moveEndPoint;
  QRect selectedRect; //选择区域
  QPixmap loadPixmap,shotPixmap;
  shotState currentShotState; //当前的截屏状态
  controlPointEnum controlValue; //记录移动控制点的值
  QToolBar* m_ptoolBar;//工具栏
  QToolButton* m_pbtnSave;//保存按钮
  QToolButton* m_pbtnCancel;//取消按钮
  QToolButton* m_pbtnFinish;//完成按钮
  QLabel*	   m_pSpliterOne; //分割线1
  QLabel*	   m_pspliterTwo; //分割线2
  int screenwidth; //整个屏幕的宽度
  int screenheight; //整个屏幕的高度
  int screenx; //选区的X
  int screeny; //选区的Y
  int tipWidth,tipHeight,infoWidth,infoHeight; //加载初始框的宽度，高度；显示坐标信息的宽度，高度
  bool m_bIsSend;
  int m_width, m_height;
  QRect getSelectedRect(); //获取选取
  QRect getRect(const QPoint &beginPoint, const QPoint &endPoint); //根据两个点获取选取坐标
  void initFullScreenWidget(); //初始化抓全屏的相关参数
  bool isInSelectedRect(const QPoint &point); //判断该点是否在选中区域
  void initToolBar();	 //初始化工具栏
  void updateToolBarPos();//更新工具栏的位置
  void drawSelectedPixmap(void); //在屏幕上画选取的屏幕
  void updateBeginEndPointValue(const QRect &rect);  //当移动选取后，对beginPoint,endPoint坐标进行重新修改
  void checkMoveEndPoint(); //对移动的选区进行判断
  void draw8ControlPoint(const QRect &rect);
  void updateMouseShape(const QPoint &point); //更新鼠标的当前状态
  void updateMoveControlMouseShape(controlPointEnum controlValue);
  controlPointEnum getMoveControlState(const QPoint &point); //获取移动控制点状态
  QRect getMoveAllSelectedRect(void); //获取移动整个选中的选区
  QRect getMoveControlSelectedRect(void);//获取移动控制点的选区
  int   getMinValue(int num1, int num2);//获取两个数中的最小值
  int   getMaxValue(int num1, int num2);//获取两个数中的最大值
  void updateMouseStytle(); //更新鼠标样式
  void updateToolBtnStytle(QToolButton* &toolBtn,QString picNormal,QString PicHot,QString PicPressed);
  void cancelSelectedRect(); //取消选择区域
  void drawXYWHInfo(void);

  //重写基类方法
  void keyPressEvent(QKeyEvent *event);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);  
  void mouseMoveEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent *event);
  void contextMenuEvent(QContextMenuEvent *event);
  //////////////////////////add by yjt//////////////////////
  public slots:
	  void slotDrawRectClicked();
	  void slotDrawEllipseClicked();
	  void slotDrawArrowClicked();
	  void slotDrawTextClicked();
	  void slotDrawPathClicked();
	  void slotRevokeClicked();
	  void slotSelectPenChanged(QPen pen);
	  void slotSelectFontChanged(QPen pen, QFont font);
	  void slotSceneTextLeftBtnPressed(QPointF pos, bool bIsPressed);   //文本编辑时，接收Scene是否左键按下
	  void slotEditTextChanged();
	  void slotBtnCancelClicked();
//signals:


private:
	void delay_MSec(unsigned int msec);
	void updateToolStyleAndColorWidget();
	void ShowDrawWidget();                 //创建绘图的相关类
private:
	QToolButton* m_pBtnDrawRect;
	QToolButton* m_pBtnDrawEllipse;
	QToolButton* m_pBtnDrawArrow;
	QToolButton* m_pBtnDrawPath;
	QToolButton* m_pBtnDrawText;
	QToolButton* m_pBtnRevoke;
	SelectColorWidget* m_pSelectRectColorWidget;
	SelectColorWidget* m_pSelectEllipseColorWidget;
	SelectColorWidget* m_pSelectArrowColorWidget;
	SelectColorWidget* m_pSelectPathColorWidget;
	SelectColorWidget* m_pSelectTextWidget;
	QStackedWidget*	   m_pStackedWidget;
	PaintWidgetScene* m_drawWidget;
	//QGraphicsView*     m_pGraphicsView;
	GraphicsViewWidget* m_pGraphicsView;
	QLabel*                  m_pFinshShowLabel;  
	QTextEdit*			   m_pTextEdit;
private:
	QString m_imagePath;
	bool                       m_bIsShapeBtnClicked;
	Shape::Code			  m_curShapeCode;
	QPen					  m_curPen;
	QFont					  m_curFont;
	int						   m_iEditSetHeigth;      //为了解决edit第一次换行高度不变
	int						   m_iEditSecondLinHeigth;
};

#endif
