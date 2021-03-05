#include "MyLineEdit.h"
#include <QMouseEvent>
namespace ui{
	MyLineEdit::MyLineEdit(QWidget *parent) :QLineEdit(parent){
		this->setReadOnly(true);
		this->setMouseTracking(true);
		this->setMaxLength(220);
		this->setFixedHeight(25);
		this->setObjectName("namelineedit");
		this->setContextMenuPolicy(Qt::NoContextMenu);
		this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
	}
	MyLineEdit::~MyLineEdit(){

	}
	void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *e){
		if (this->isReadOnly()){
			e->ignore();
		}
		else{
			QLineEdit::mouseMoveEvent(e);
		}
	}
	void MyLineEdit::mousePressEvent(QMouseEvent *event)
	{
		bool isReadOnly = this->isReadOnly();
		//获得当前鼠标位置
		int cursor_pos = cursorPositionAt(event->pos());

		//获取光标位置
		int current_pos = this->cursorPosition();

	
		if (event->button() == Qt::LeftButton && isReadOnly) {
			// do something
			//emit signalClicked();
			event->ignore();
		}
		//鼠标点击位置在光标位置之前，则设置光标前移一格
		if (cursor_pos < current_pos)
		{
			this->setCursorPosition(current_pos - 1);
		}
		//鼠标点击位置在光标位置之后，则设置光标后移一格
		else if (cursor_pos > current_pos)
		{
			this->setCursorPosition(current_pos + 1);
		}
		else if (cursor_pos == current_pos)
		{
			this->setCursorPosition(current_pos);
		}
		else {
			event->ignore();
		}
	}
	void MyLineEdit::focusOutEvent(QFocusEvent *e){
		emit signalFocusOut();
		e->ignore();
	}
	void MyLineEdit::keyPressEvent(QKeyEvent *event)
	{
		bool isReadOnly = this->isReadOnly();
		//屏蔽全选，这里最好不要使用Ctrl+A，因为不一点全选都被设置为它，所以使用系统的比较好
		if (event->matches(QKeySequence::SelectAll) && isReadOnly)
		{
			return;
		}
		//屏蔽复制，和全选一样，这里最好不要使用Ctrl+A
		else if (event->matches(QKeySequence::Copy) && isReadOnly)
		{
			return;
		}

		//屏蔽粘贴
		else if (event->matches(QKeySequence::Paste) && isReadOnly)
		{
			return;
		}

		//设置Home、End键直接将光标位置设到最前、最后，而不被选中
		else if (event->key() == Qt::Key_Home && isReadOnly)
		{
			this->setCursorPosition(0);
		}
		else if (event->key() == Qt::Key_End && isReadOnly)
		{
			this->setCursorPosition(this->text().length());
		}
		else
		{
			QLineEdit::keyPressEvent(event);
		}
	}
	//鼠标移动时，什么都不干，因为一般情况下当鼠标移动文本都会被选中

	void MyLineEdit::mouseMoveEvent(QMouseEvent *event)
	{
		if (this->isReadOnly()){
			event->accept();
		}
		else{
			QLineEdit::mouseMoveEvent(event);
		}
	}
	void MyLineEdit::mouseReleaseEvent(QMouseEvent *e){
		e->ignore();
	}
	/*****************************************
	*字符串省略号处理函数，功能将字体为font的字符串
	* 处理为当长度大于maxwidth时，大于部分显示为...
	*****************************************/
	void MyLineEdit::setElidedText(QString str)
	{
		QFontMetrics fontWidth(this->font());
		int MaxWidth = this->maxLength();
		int width = fontWidth.width(str);  //计算字符串宽度
		if (width >= MaxWidth)  //当字符串宽度大于最大宽度时进行转换
		{
			str = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);  //右部显示省略号
		}
		this->setText(str);
	}
}