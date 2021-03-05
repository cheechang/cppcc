#include "Button.h"
namespace uicontrols{
	Button::Button(QWidget *parent)
		: QPushButton(parent)
	{
		this->setObjectName("sendbtn");
	}

	Button::~Button()
	{

	}
}
