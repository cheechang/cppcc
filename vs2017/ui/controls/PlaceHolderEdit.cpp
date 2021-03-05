
#include "PlaceHolderEdit.h"

namespace ui
{
	PlaceHolderEdit::PlaceHolderEdit(QWidget*parent) : QTextEdit(parent)
		, m_iMaxLength(0)
	{
		this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		connect(this, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
	}

	PlaceHolderEdit::~PlaceHolderEdit()
	{

	}

	void PlaceHolderEdit::setMaxLength(const unsigned int iMaxLength)
	{
		m_iMaxLength = iMaxLength;
	}

	void PlaceHolderEdit::onTextChanged()
	{
		QString textContent = this->toPlainText();  
		int length = textContent.count();  
		int maxLength = m_iMaxLength; // ×î´ó×Ö·ûÊý  
		if(length > maxLength) {  
			int position = this->textCursor().position();  
			QTextCursor textCursor = this->textCursor();  
			textContent.remove(position-(length-maxLength), length-maxLength);  
			this->setText(textContent);  
			textCursor.setPosition(position-(length-maxLength));  
			this->setTextCursor(textCursor);  
		} 
	}

	void PlaceHolderEdit::setPlaceHolderText(const QString text)
	{
		m_strPlaceHolderText = text;
	}

	void PlaceHolderEdit::showEvent(QShowEvent* e)
	{
		if (this->toPlainText() == "")
		{
			this->setText(m_strPlaceHolderText);
		}
	}

	void PlaceHolderEdit::focusInEvent(QFocusEvent* e)
	{
		if (this->toPlainText() == m_strPlaceHolderText)
		{
			this->setText("");
		}
	}

	void PlaceHolderEdit::focusOutEvent(QFocusEvent* e)
	{
		if (this->toPlainText() == "")
		{
			this->setText(m_strPlaceHolderText);
		}
	}
}