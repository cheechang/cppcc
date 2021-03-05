#include "GroupInforSettingTabWidget.h"
#include <QPainter>
#include <QStyleOption>
#include "GroupInforSettingArea.h"
#include "GroupInforMembersArea.h"
#include "GroupNotice.h"
#include "GroupFileList.h"
#include "common/Connect.h"
namespace ui{
	GroupInforSettingTabWidget::GroupInforSettingTabWidget(QWidget *parent)
		: QWidget(parent)
	{
		m_tabWidget = CMakePtr<QTabWidget>(this);
		connect(m_tabWidget.get(),SIGNAL(currentChanged(int)),this,SLOT(onTabCurentChanged(int)));

		m_mainLayout = CMakePtr<QVBoxLayout>(this);
		
		m_tabWidget->setObjectName("groupSettabbar");
		m_mainLayout->addWidget(m_tabWidget.get());
		m_mainLayout->setContentsMargins(0,0,0,0);
		m_tabWidget->setContentsMargins(30,0,30,0);
	
		initGroupSetting();
		intitGroupMems();
		initGroupFiles();
		initGroupNotice();
		setLayout(m_mainLayout.get());

	}

	GroupInforSettingTabWidget::~GroupInforSettingTabWidget()
	{
	}

	void GroupInforSettingTabWidget::initGroupSetting()
	{
		m_areaSetting = CMakePtr<GroupInforSettingArea>();
		m_tabWidget->addTab(m_areaSetting.get(),transfer("群设置"));

	}

	void GroupInforSettingTabWidget::intitGroupMems()
	{
		m_areaMems = CMakePtr<GroupInforMembersArea>();
		m_tabWidget->addTab(m_areaMems.get(),transfer("群成员"));
		connect(m_areaMems.get(),SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),this,SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)));
		connect(m_areaSetting.get(),SIGNAL(signalGroupSet(int , int8 , int8 )),m_areaMems.get(),SLOT(onGroupSet(int , int8 , int8 )));
	}

	void GroupInforSettingTabWidget::initGroupFiles()
	{
		m_areaFiles = CMakePtr<GroupFileList>();
		m_tabWidget->addTab(m_areaFiles.get(), transfer("群文件"));
		connect(m_areaFiles.get(), SIGNAL(signalSerDelUiFile(int64)),this, SIGNAL(signalSerDelUiFile(int64)));
	}

	void GroupInforSettingTabWidget::paintEvent( QPaintEvent *event )
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}

	void GroupInforSettingTabWidget::updateData( int64 gorupId )
	{
		m_areaSetting->updateData(gorupId);
		mGorupId = gorupId;
		m_tabWidget->setCurrentIndex(0);
	}

	void GroupInforSettingTabWidget::onTabCurentChanged( int index )
	{
		if(index == 1){
			m_areaMems->updateData(mGorupId);
		}
		else if (index == 2)
		{
			m_areaFiles->updateData(mGorupId);
		}
		else if(index == 3)
		{
			m_areaNotice->updateData(mGorupId);
		}
	}

	void GroupInforSettingTabWidget::initGroupNotice()
	{
		m_areaNotice = CMakePtr<GroupNotice>();
		m_tabWidget->addTab(m_areaNotice.get(), transfer("公告"));
	}
}