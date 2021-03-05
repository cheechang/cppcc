#pragma  once
#include <QColor>
class MsgBubbleConfig{
public:
	MsgBubbleConfig();
	virtual ~MsgBubbleConfig();

	static QColor selfTextColor();
	static void   SetSelfTextColor(QColor&val);

	static QColor otherTextColor();
	static void   SetOtherTextColor(QColor&val);

	static QColor selfBorderColor();
	static void   SetSelfBorderColor(QColor&val);

	static QColor othersBorderColor();
	static void   SetOthersBorderColor(QColor&val);

	static QColor selfBubbleColor();
	static void   SetSelfBubbleColor(QColor&val);

	static QColor otherBubbleColor();
	static void   SetOtherBubbleColor(QColor&val);

	static int	  horizontalMargin();
	static void   SetHorizontalMargin(int&val);

	static int	  VerticalMargin();
	static void   SetVerticalMargin(int&val);

	static int	  MsgVerticalMargin();
	static void   SetMsgVerticalMargin(int&val);

	static int	  ScrollDuration();
	static void   SetScrollDuration(int&val);

	static qreal	  WidthRatio();
	static void   SetWidthRatio(qreal&val);

	static int	  VerticalScrollBarWidth();
	static void   SetVerticalScrollBarWidth(int&val);

	static int	  MaxChatBubbleWidth();
	static void   SetMaxChatBubbleWidth(int&val);

	static int	  MaxSingleLineWidth();
	static void   SetMaxSingleLineWidth(int&val);

	static int	  MinMessageHeight();
	static void   SetMinMessageHeight(int&val);
public:
	static QColor m_selfTextColor;		//���ͷ��ı���ɫ
	static QColor m_othersTextColor;	//���շ��ı���ɫ
	static QColor m_selfBorderColor;	//���ͷ����ݱ߿�����ɫ
	static QColor m_othersBorderColor;	//���շ����ݱ߿�����ɫ
	static QColor m_selfBubbleColor;	//���ͷ�������ɫ
	static QColor m_otherBubbleColor;	//���շ���������ɫ
	static  int   m_HorizontalMargin;
	static  int   m_VerticalMargin;
	static  int   m_GetMsgVerticalMargin;
	static  int	  m_ScrollDuration; // ms
	static  qreal m_WidthRatio;
	static  int   m_VerticalScrollBarWidth;
	static  int   m_MaxChatBubbleWidth;
	static  int   m_MaxSingleLineWidth;
	static  int   m_MinMessageHeight;
};