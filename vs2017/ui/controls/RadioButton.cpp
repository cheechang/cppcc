#include "RadioButton.h"
namespace uicontrols{
	RadioButton::RadioButton(QWidget *parent)
		: QRadioButton(parent)
	{
		this->setObjectName("norItemSelect");
	}

	RadioButton::RadioButton(const QString &text, QWidget *parent/*=0*/):QRadioButton(text,parent)
	{
		this->setObjectName("norItemSelect");
	}

	RadioButton::~RadioButton()
	{

	}

}