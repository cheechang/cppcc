#pragma once

#include <QComboBox>
#include <QLineEdit>
#include "interface/Defines.h"


namespace ui {
	class AccountComboBox :
		public QComboBox
	{
		Q_OBJECT
	public:
		AccountComboBox(QWidget* parent = 0);
		~AccountComboBox(void);
		void setPlaceholderText(const QString text);
		void setMaxLength(const unsigned int length);

	private:
		std::shared_ptr<QLineEdit> m_pAccountInput;
	};
}

