#include "MsgBubbleConfig.h"
QColor MsgBubbleConfig::m_selfTextColor = Qt::white;		//发送方文本颜色
QColor MsgBubbleConfig::m_othersTextColor = Qt::black;		//接收方文本颜色
QColor MsgBubbleConfig::m_selfBorderColor = QColor(19,52,83);	//发送方气泡边框线颜色
QColor MsgBubbleConfig::m_selfBubbleColor = QColor(19,52,83);	//发送方气泡颜色
QColor MsgBubbleConfig::m_othersBorderColor=QColor(228,228,228);//接收方气泡边框线颜色
QColor MsgBubbleConfig::m_otherBubbleColor=QColor(228,228,228);	//接收方方气泡颜色
int	   MsgBubbleConfig::m_HorizontalMargin = 0;
int    MsgBubbleConfig::m_VerticalMargin = 5;
int    MsgBubbleConfig::m_GetMsgVerticalMargin = 30;
int	   MsgBubbleConfig::m_ScrollDuration = 300; // ms
qreal  MsgBubbleConfig::m_WidthRatio =0.9;
int    MsgBubbleConfig::m_VerticalScrollBarWidth = 20;
int    MsgBubbleConfig::m_MaxChatBubbleWidth = 500;
int    MsgBubbleConfig::m_MaxSingleLineWidth = 300;
int    MsgBubbleConfig::m_MinMessageHeight=30;
MsgBubbleConfig::MsgBubbleConfig(){

}
MsgBubbleConfig::~MsgBubbleConfig(){

}
QColor MsgBubbleConfig::selfTextColor(){
	return m_selfTextColor;
}
void  MsgBubbleConfig::SetSelfTextColor(QColor&val){
	m_selfTextColor = val;
}
QColor MsgBubbleConfig::otherTextColor(){
	return m_othersTextColor;
}
void MsgBubbleConfig::SetOtherTextColor(QColor&val){
	m_othersTextColor = val;
}
QColor MsgBubbleConfig::selfBorderColor(){
	return m_selfBorderColor;
}
void MsgBubbleConfig::SetSelfBorderColor(QColor&val){
	m_selfBorderColor = val;
}

QColor MsgBubbleConfig::othersBorderColor(){
	return m_othersBorderColor;
}
void MsgBubbleConfig::SetOthersBorderColor(QColor&val){
	m_othersBorderColor = val;
}
QColor MsgBubbleConfig::selfBubbleColor(){
	return m_selfBubbleColor;
}
void MsgBubbleConfig::SetSelfBubbleColor(QColor&val){
	m_selfBubbleColor = val;
}
QColor MsgBubbleConfig::otherBubbleColor(){
	return m_otherBubbleColor;
}
void MsgBubbleConfig::SetOtherBubbleColor(QColor&val){
	m_otherBubbleColor = val;
}
int	MsgBubbleConfig::horizontalMargin(){
	return m_HorizontalMargin;
}
void MsgBubbleConfig::SetHorizontalMargin(int&val){
	m_HorizontalMargin = val;
}
int	 MsgBubbleConfig::VerticalMargin(){
	return m_VerticalMargin;
}
void MsgBubbleConfig::SetVerticalMargin(int&val){
	m_VerticalMargin = val;
}
int	 MsgBubbleConfig::MsgVerticalMargin(){
	return m_GetMsgVerticalMargin;
}
void MsgBubbleConfig::SetMsgVerticalMargin(int&val){
	m_GetMsgVerticalMargin = val;
}
int	MsgBubbleConfig::ScrollDuration(){
	return m_ScrollDuration;
}
void MsgBubbleConfig::SetScrollDuration(int&val){
	m_ScrollDuration = val;
}
qreal MsgBubbleConfig::WidthRatio(){
	return m_WidthRatio;
}
void MsgBubbleConfig::SetWidthRatio(qreal&val){
	m_WidthRatio = val;
}
int	MsgBubbleConfig::VerticalScrollBarWidth(){
	return m_VerticalScrollBarWidth;
}
void MsgBubbleConfig::SetVerticalScrollBarWidth(int&val){
	m_VerticalScrollBarWidth = val;
}
int	MsgBubbleConfig::MaxChatBubbleWidth(){
	return m_MaxChatBubbleWidth;
}
void MsgBubbleConfig::SetMaxChatBubbleWidth(int&val){
	m_MaxChatBubbleWidth = val;
}
int	MsgBubbleConfig::MaxSingleLineWidth(){
	return m_MaxSingleLineWidth;
}
void MsgBubbleConfig::SetMaxSingleLineWidth(int&val){
	m_MaxSingleLineWidth = val;
}
int	 MsgBubbleConfig::MinMessageHeight(){
	return m_MinMessageHeight;
}
void MsgBubbleConfig::SetMinMessageHeight(int&val){
	m_MinMessageHeight = val;
}