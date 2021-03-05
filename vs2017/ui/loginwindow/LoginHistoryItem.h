#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "interface/Defines.h"


namespace ui{
	class HeadImage;
	class PushButton;
	class LoginHistoryItem :
		public QWidget
	{
		Q_OBJECT
	public:
		explicit LoginHistoryItem(QWidget *parent = 0/*, QString avatar = "",
			QString account = "", QString name = ""*/);
		~LoginHistoryItem(void);
		void setAvatar(const QString avatar);
		void setAccount(const QString account);
		void setName(const QString name);
	
	private:
		std::shared_ptr<QGridLayout>m_pLayout;
		std::shared_ptr<HeadImage>	m_pAvatar;
		std::shared_ptr<QLabel>		m_pAccount;
		std::shared_ptr<QLabel>		m_pName;
		std::shared_ptr<PushButton>	m_pCloseButton;
	};
}

