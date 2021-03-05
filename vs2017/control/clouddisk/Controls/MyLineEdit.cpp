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
		//��õ�ǰ���λ��
		int cursor_pos = cursorPositionAt(event->pos());

		//��ȡ���λ��
		int current_pos = this->cursorPosition();

	
		if (event->button() == Qt::LeftButton && isReadOnly) {
			// do something
			//emit signalClicked();
			event->ignore();
		}
		//�����λ���ڹ��λ��֮ǰ�������ù��ǰ��һ��
		if (cursor_pos < current_pos)
		{
			this->setCursorPosition(current_pos - 1);
		}
		//�����λ���ڹ��λ��֮�������ù�����һ��
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
		//����ȫѡ��������ò�Ҫʹ��Ctrl+A����Ϊ��һ��ȫѡ��������Ϊ��������ʹ��ϵͳ�ıȽϺ�
		if (event->matches(QKeySequence::SelectAll) && isReadOnly)
		{
			return;
		}
		//���θ��ƣ���ȫѡһ����������ò�Ҫʹ��Ctrl+A
		else if (event->matches(QKeySequence::Copy) && isReadOnly)
		{
			return;
		}

		//����ճ��
		else if (event->matches(QKeySequence::Paste) && isReadOnly)
		{
			return;
		}

		//����Home��End��ֱ�ӽ����λ���赽��ǰ����󣬶�����ѡ��
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
	//����ƶ�ʱ��ʲô�����ɣ���Ϊһ������µ�����ƶ��ı����ᱻѡ��

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
	*�ַ���ʡ�ԺŴ����������ܽ�����Ϊfont���ַ���
	* ����Ϊ�����ȴ���maxwidthʱ�����ڲ�����ʾΪ...
	*****************************************/
	void MyLineEdit::setElidedText(QString str)
	{
		QFontMetrics fontWidth(this->font());
		int MaxWidth = this->maxLength();
		int width = fontWidth.width(str);  //�����ַ������
		if (width >= MaxWidth)  //���ַ�����ȴ��������ʱ����ת��
		{
			str = fontWidth.elidedText(str, Qt::ElideRight, MaxWidth);  //�Ҳ���ʾʡ�Ժ�
		}
		this->setText(str);
	}
}