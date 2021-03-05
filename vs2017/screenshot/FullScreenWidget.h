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
  fullScreenWidget(); //���캯��
  static fullScreenWidget *m_instance;
  void loadLanguage();
  int  getLanguage();
  void updateToolBarText();
public:
  static fullScreenWidget* GetInstance();
  enum shotState{initShot,beginShot,finishShot,endShot,beginMoveShot,finishMoveShot,beginControl,finishControl}; //���н�����״̬
  //�ƶ�ѡ���е�8�����Ƶ㣬����˳ʱ�뷽������Ͽ��Ƶ㵽���п��Ƶ������Ϊ1��8
  enum controlPointEnum{moveControl0,moveControl1,moveControl2,moveControl3,moveControl4,moveControl5,moveControl6,moveControl7,moveControl8};
  QPixmap getFullScreenPixmap(); //��ȡȫ����Pixmap
  void writeToServer(QString message);
  public slots:
  void loadBackgroundPixmap(const QPixmap &bgPixmap);//���ر���Pixmap�ۺ���
  void loadBackgroundPixmap(const QPixmap &bgPixmap, int x, int y, int width, int height); //���ر���pixmap�ۺ���������x,y,width,height
  void exitShotScreen(bool iscancel=false);	//�˳���ͼ
  void savePixmap();	   //��ѡȡ��Ϊ�ķ���
  void finishScreenShot();
  
  signals:
  void finishPixmap(const QPixmap finishPixmap); //�����ͼ���ͼƬ,�����źŸ�������
  void exitPixmap();   //�˳���ͼ�󣬷����źŸ������� add by yjt
  void finishedshot(QString cmd);
  ///////////////////////add by yjt
  void signalChangeCurrentShape(Shape::Code, QPen pen);     //����ͼ�θı��ź�
  void signalDeleteLastDraw();                                //���������ź�
  void signalSelectPenChanged(QPen);				//�߿�Ȼ���ɫ�ı��ź�
  void signalSelectFontChanged(QPen, QFont);
  void signalAddTextToView(QString);
  ///////////////////////////////
  private:
  //ѡ�����8����ѡȡ
  QRect tlRect; //���ϵ�1
  QRect trRect; //���ϵ�1
  QRect blRect; //���µ�1
  QRect brRect; //���µ�1
  QRect tcRect; //���е�1
  QRect bcRect; //���е�1
  QRect lcRect;//���е�1
  QRect rcRect; //���е�1

  QPainter painter;
  QPoint beginPoint,endPoint,moveBeginPoint,moveEndPoint;
  QRect selectedRect; //ѡ������
  QPixmap loadPixmap,shotPixmap;
  shotState currentShotState; //��ǰ�Ľ���״̬
  controlPointEnum controlValue; //��¼�ƶ����Ƶ��ֵ
  QToolBar* m_ptoolBar;//������
  QToolButton* m_pbtnSave;//���水ť
  QToolButton* m_pbtnCancel;//ȡ����ť
  QToolButton* m_pbtnFinish;//��ɰ�ť
  QLabel*	   m_pSpliterOne; //�ָ���1
  QLabel*	   m_pspliterTwo; //�ָ���2
  int screenwidth; //������Ļ�Ŀ��
  int screenheight; //������Ļ�ĸ߶�
  int screenx; //ѡ����X
  int screeny; //ѡ����Y
  int tipWidth,tipHeight,infoWidth,infoHeight; //���س�ʼ��Ŀ�ȣ��߶ȣ���ʾ������Ϣ�Ŀ�ȣ��߶�
  bool m_bIsSend;
  int m_width, m_height;
  QRect getSelectedRect(); //��ȡѡȡ
  QRect getRect(const QPoint &beginPoint, const QPoint &endPoint); //�����������ȡѡȡ����
  void initFullScreenWidget(); //��ʼ��ץȫ������ز���
  bool isInSelectedRect(const QPoint &point); //�жϸõ��Ƿ���ѡ������
  void initToolBar();	 //��ʼ��������
  void updateToolBarPos();//���¹�������λ��
  void drawSelectedPixmap(void); //����Ļ�ϻ�ѡȡ����Ļ
  void updateBeginEndPointValue(const QRect &rect);  //���ƶ�ѡȡ�󣬶�beginPoint,endPoint������������޸�
  void checkMoveEndPoint(); //���ƶ���ѡ�������ж�
  void draw8ControlPoint(const QRect &rect);
  void updateMouseShape(const QPoint &point); //�������ĵ�ǰ״̬
  void updateMoveControlMouseShape(controlPointEnum controlValue);
  controlPointEnum getMoveControlState(const QPoint &point); //��ȡ�ƶ����Ƶ�״̬
  QRect getMoveAllSelectedRect(void); //��ȡ�ƶ�����ѡ�е�ѡ��
  QRect getMoveControlSelectedRect(void);//��ȡ�ƶ����Ƶ��ѡ��
  int   getMinValue(int num1, int num2);//��ȡ�������е���Сֵ
  int   getMaxValue(int num1, int num2);//��ȡ�������е����ֵ
  void updateMouseStytle(); //���������ʽ
  void updateToolBtnStytle(QToolButton* &toolBtn,QString picNormal,QString PicHot,QString PicPressed);
  void cancelSelectedRect(); //ȡ��ѡ������
  void drawXYWHInfo(void);

  //��д���෽��
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
	  void slotSceneTextLeftBtnPressed(QPointF pos, bool bIsPressed);   //�ı��༭ʱ������Scene�Ƿ��������
	  void slotEditTextChanged();
	  void slotBtnCancelClicked();
//signals:


private:
	void delay_MSec(unsigned int msec);
	void updateToolStyleAndColorWidget();
	void ShowDrawWidget();                 //������ͼ�������
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
	int						   m_iEditSetHeigth;      //Ϊ�˽��edit��һ�λ��и߶Ȳ���
	int						   m_iEditSecondLinHeigth;
};

#endif
