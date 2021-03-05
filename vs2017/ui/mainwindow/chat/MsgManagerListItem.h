#pragma once
#include "controls/TWidget.h"
#include <QLabel>
#include <QHBoxLayout>

namespace ui{
	class HeadImage;
	class MsgManagerListItem : public TWidget
	{
		Q_OBJECT
	public:
		MsgManagerListItem(QWidget* parent = CNull,int64 targetid=0);
		~MsgManagerListItem();

		void Init();
		void SetData(QString head,QString name,int count);
		int64 GetTargetid();
		int GetCountMsg();
	private:
		CSharedPtr<QHBoxLayout> m_Mainlayout;
		CSharedPtr<QLabel> m_lblName;
		CSharedPtr<HeadImage> m_imgHead;

		int64 mTargetId;
		int m_count;
	};
}