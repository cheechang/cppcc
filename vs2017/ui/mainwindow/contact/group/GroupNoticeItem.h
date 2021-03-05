#pragma once

#include <QLabel>
#include <data/GroupData.h>
#include "controls/TWidget.h"
#include "common/controlptr.h"
#include "interface/Defines.h"
#include <QHBoxLayout>
#include <QTextEdit>

namespace ui{
	class GroupNoticeItem : public TWidget
	{
		Q_OBJECT
	public:
		GroupNoticeItem(QWidget *parent = CNull);
		~GroupNoticeItem();

		void setData(const data::Group& pGroupInfo);
		void setNominition(std::string name);
		QSize GetSizeByContent(int pwidth);
		int getContentHigh();
	private:

		IChatMgrControl_Ptr m_pChatControl;

		QTextEdit* m_pLabelNoticeContent;
		//QLabel* m_pLabelNoticeContent;
		QLabel* m_pNomination;
		QVBoxLayout* m_MainLayout;
	};
}
