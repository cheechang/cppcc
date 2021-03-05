#include "ExpressionWindow.h"
#include "ExpressionWidget.h"
#include <QWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QScrollBar>
#include <QDir>

#include <common/ChineseInfos.hpp>
#include <common/Common.h>
namespace ui{
	std::map<std::string, std::string>ExpressionWindow::m_InstructMap;
	std::map<std::string, std::string>ExpressionWindow::m_engInstructMap;
	QMap<QString, QString> ExpressionWindow::    m_keyDnyValMap;
	QMap<QString, QString> ExpressionWindow::    m_keyValMap;
	QStringList ExpressionWindow::    m_frontEmoji;
	QStringList ExpressionWindow::    m_frontOther;

	ExpressionWindow::ExpressionWindow(QWidget *parent)
		: QDialog(parent)
	{
		setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint|Qt::Popup);
		setAttribute(Qt::WA_TranslucentBackground);
		mMainLayout = new QVBoxLayout(this);
		setLayout(mMainLayout);
		mMainLayout->setSpacing(0);
		mMainLayout->setContentsMargins(0,0,0,0);
		setMinimumSize(410*gDdpi,240*gDdpi);
		mIsLoadDy = mIsLoadFaced = mIsLoad =false;
		mEmojiEmojiFace = new ExpressionWidget(this);
		mEmojiEmojiFace->setRowAndColumn(10, 13);
		mEmojiEmojiFace->setEmotionSize(QSize(32*gDdpi, 32*gDdpi));
		mEmojiEmojiFace->setEmotionMovieSize(QSize(24*gDdpi, 24*gDdpi));
		mEmojiEmojiFace->setMaxRow(8);
		mEmojiEmojiFace->initTableWidget();
		connect(mEmojiEmojiFace,SIGNAL(clicked(QString)),this,SLOT(onClicked(QString)));

		mEmojiUserDef = new ExpressionWidget(this);
		mEmojiUserDef->setRowAndColumn(10, 13);
		mEmojiUserDef->setEmotionSize(QSize(32*gDdpi, 32*gDdpi));
		mEmojiUserDef->setEmotionMovieSize(QSize(24*gDdpi, 24*gDdpi));
		mEmojiUserDef->setMaxRow(8);
		mEmojiUserDef->initTableWidget();
		mEmojiUserDef->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		connect(mEmojiUserDef,SIGNAL(clicked(QString)),this,SLOT(onClicked(QString)));
		
		mEmojiDynamic = new ExpressionWidget(this);
		mEmojiDynamic->setRowAndColumn(4, 7);
		mEmojiDynamic->setEmotionSize(QSize(62*gDdpi, 64*gDdpi));
		mEmojiDynamic->setEmotionMovieSize(QSize(62*gDdpi, 64*gDdpi));
		mEmojiDynamic->setMaxRow(8);
		mEmojiDynamic->initTableWidget();
		connect(mEmojiDynamic,SIGNAL(clicked(QString)),this,SLOT(onClicked(QString)));
		
		mStackedWidget = new QStackedWidget(this);
		mStackedWidget->addWidget(mEmojiUserDef);
		mStackedWidget->addWidget(mEmojiEmojiFace);
		mStackedWidget->addWidget(mEmojiDynamic);
	
		mBtnFaceEmoji = new TabItemButton(this,":/img/smilies/emoji_face/e298ba.png");
		mBtnInstructEmoji = new TabItemButton(this,":/img/smilies/instruct/weixiao.png");
		mBtnDyEmoji = new TabItemButton(this,":/chat/dny");
		mBtnInstructEmoji->setChecked(true);
		mBtnDyEmoji->setVisible(true);
		connect(mBtnFaceEmoji,SIGNAL(clicked(bool)),this,SLOT(onFaceEmojiClicked()));
		connect(mBtnInstructEmoji,SIGNAL(clicked(bool)),this,SLOT(onInstructEmojiClicked()));
		connect(mBtnDyEmoji,SIGNAL(clicked(bool)),this,SLOT(onDyEmojiClicked()));

		QHBoxLayout*layout = new QHBoxLayout(this);
		layout->setContentsMargins(0,0,0,0);
		layout->setSpacing(0);
		layout->addWidget(mBtnInstructEmoji);
		layout->addWidget(mBtnFaceEmoji);
		layout->addWidget(mBtnDyEmoji);
		layout->addStretch();
		QWidget*widget = new QWidget(this);
		widget->setLayout(layout);
		widget->setObjectName("ExpressWidget");
		widget->setMinimumHeight(40*gDdpi);

		QVBoxLayout*layoutWidget = new QVBoxLayout(this);
		layoutWidget->setContentsMargins(1*gDdpi,1*gDdpi,1*gDdpi,1*gDdpi);
		layoutWidget->setSpacing(0);;
		layoutWidget->addWidget(mStackedWidget);
		layoutWidget->addWidget(widget);

		QWidget*widgetMain = new QWidget(this);
		widgetMain->setObjectName("parentW");
		widgetMain->setObjectName("ExpresswidgetMain");
		widgetMain->setLayout(layoutWidget);
		mMainLayout->addWidget(widgetMain);
	}

	ExpressionWindow::~ExpressionWindow()
	{

	}

	void ExpressionWindow::initEmoji()
	{
		if (!m_keyValMap.isEmpty())
		{
			return;
		}
		//基本表情
	    m_keyValMap["23e283a3"] = FACE_23e283a3;
	    m_keyValMap["30e283a3"] = FACE_30e283a3;
	    m_keyValMap["31e283a3"] = FACE_31e283a3;
	    m_keyValMap["32e283a3"] = FACE_32e283a3;
	    m_keyValMap["33e283a3"] = FACE_33e283a3;
	    m_keyValMap["34e283a3"] = FACE_34e283a3;
	    m_keyValMap["35e283a3"] = FACE_35e283a3;
	    m_keyValMap["36e283a3"] = FACE_36e283a3;
	    m_keyValMap["37e283a3"] = FACE_37e283a3;
	    m_keyValMap["38e283a3"] = FACE_38e283a3;
	    m_keyValMap["39e283a3"] = FACE_39e283a3;
	    m_keyValMap["c2a9a9"] = FACE_c2a9a9;
	    m_keyValMap["c2aeae"] = FACE_c2aeae;
	    m_keyValMap["e284a2"] = FACE_e284a2;
	    m_keyValMap["e28696"] = FACE_e28696;
	    m_keyValMap["e28697"] = FACE_e28697;
	    m_keyValMap["e28698"] = FACE_e28698;
	    m_keyValMap["e28699"] = FACE_e28699;
	    m_keyValMap["e28fa9"] = FACE_e28fa9;
	    m_keyValMap["e28faa"] = FACE_e28faa;
	    m_keyValMap["e296b6"] = FACE_e296b6;
	    m_keyValMap["e29780"] = FACE_e29780;
	    m_keyValMap["e29880"] = FACE_e29880;
	    m_keyValMap["e29881"] = FACE_e29881;
	    m_keyValMap["e2988e"] = FACE_e2988e;
	    m_keyValMap["e29894"] = FACE_e29894;
	    m_keyValMap["e29895"] = FACE_e29895;
	    m_keyValMap["e2989d"] = FACE_e2989d;
	    m_keyValMap["e298ba"] = FACE_e298ba;
	    m_keyValMap["e29988"] = FACE_e29988;
	    m_keyValMap["e29989"] = FACE_e29989;
	    m_keyValMap["e2998a"] = FACE_e2998a;
	    m_keyValMap["e2998b"] = FACE_e2998b;
	    m_keyValMap["e2998c"] = FACE_e2998c;
	    m_keyValMap["e2998d"] = FACE_e2998d;
	    m_keyValMap["e2998e"] = FACE_e2998e;
	    m_keyValMap["e2998f"] = FACE_e2998f;
	    m_keyValMap["e29990"] = FACE_e29990;
	    m_keyValMap["e29991"] = FACE_e29991;
	    m_keyValMap["e29992"] = FACE_e29992;
	    m_keyValMap["e29993"] = FACE_e29993;
	    m_keyValMap["e299a0"] = FACE_e299a0;
	    m_keyValMap["e299a3"] = FACE_e299a3;
	    m_keyValMap["e299a5"] = FACE_e299a5;
	    m_keyValMap["e299a6"] = FACE_e299a6;
	    m_keyValMap["e299a8"] = FACE_e299a8;
	    m_keyValMap["e299bf"] = FACE_e299bf;
	    m_keyValMap["e29aa0"] = FACE_e29aa0;
	    m_keyValMap["e29aa1"] = FACE_e29aa1;
	    m_keyValMap["e29abd"] = FACE_e29abd;
	    m_keyValMap["e29abe"] = FACE_e29abe;
	    m_keyValMap["e29b84"] = FACE_e29b84;
	    m_keyValMap["e29baa"] = FACE_e29baa;
	    m_keyValMap["e29bb2"] = FACE_e29bb2;
	    m_keyValMap["e29bb3"] = FACE_e29bb3;
	    m_keyValMap["e29bb5"] = FACE_e29bb5;
	    m_keyValMap["e29bba"] = FACE_e29bba;
	    m_keyValMap["e29bbd"] = FACE_e29bbd;
	    m_keyValMap["e29c82"] = FACE_e29c82;
	    m_keyValMap["e29c88"] = FACE_e29c88;
	    m_keyValMap["e29c8a"] = FACE_e29c8a;
	    m_keyValMap["e29c8b"] = FACE_e29c8b;
	    m_keyValMap["e29c8c"] = FACE_e29c8c;
	    m_keyValMap["e29ca8"] = FACE_e29ca8;
	    m_keyValMap["e29cb3"] = FACE_e29cb3;
	    m_keyValMap["e29cb4"] = FACE_e29cb4;
	    m_keyValMap["e29d8c"] = FACE_e29d8c;
	    m_keyValMap["e29d94"] = FACE_e29d94;
	    m_keyValMap["e29d95"] = FACE_e29d95;
	    m_keyValMap["e29da4"] = FACE_e29da4;
	    m_keyValMap["e29ea1"] = FACE_e29ea1;
	    m_keyValMap["e29ebf"] = FACE_e29ebf;
	    m_keyValMap["e2ac85"] = FACE_e2ac85;
	    m_keyValMap["e2ac86"] = FACE_e2ac86;
	    m_keyValMap["e2ac87"] = FACE_e2ac87;
	    m_keyValMap["e2ad95"] = FACE_e2ad95;
	    m_keyValMap["e380bd"] = FACE_e380bd;
	    m_keyValMap["e38a97"] = FACE_e38a97;
	    m_keyValMap["e3ba99"] = FACE_e3ba99;
	    m_keyValMap["f09f8084"] = FACE_f09f8084;
	    m_keyValMap["f09f85b0"] = FACE_f09f85b0;
	    m_keyValMap["f09f85b1"] = FACE_f09f85b1;
	    m_keyValMap["f09f85be"] = FACE_f09f85be;
	    m_keyValMap["f09f85bf"] = FACE_f09f85bf;
	    m_keyValMap["f09f868e"] = FACE_f09f868e;
	    m_keyValMap["f09f8692"] = FACE_f09f8692;
	    m_keyValMap["f09f8694"] = FACE_f09f8694;
	    m_keyValMap["f09f8695"] = FACE_f09f8695;
	    m_keyValMap["f09f8697"] = FACE_f09f8697;
	    m_keyValMap["f09f8699"] = FACE_f09f8699;
	    m_keyValMap["f09f869a"] = FACE_f09f869a;
	    m_keyValMap["f09f87a8f09f8FACE_7b3"] = FACE_f09f87a8f09f8FACE_7b3;
	    m_keyValMap["f09f87a9f09f8FACE_7aa"] = FACE_f09f87a9f09f8FACE_7aa;
	    m_keyValMap["f09f87aaf09f8FACE_7b8"] = FACE_f09f87aaf09f8FACE_7b8;
	    m_keyValMap["f09f87abf09f8FACE_7b7"] = FACE_f09f87abf09f8FACE_7b7;
	    m_keyValMap["f09f87acf09f8FACE_7a7"] = FACE_f09f87acf09f8FACE_7a7;
	    m_keyValMap["f09f87aef09f8FACE_7b9"] = FACE_f09f87aef09f8FACE_7b9;
	    m_keyValMap["f09f87aff09f8FACE_7b5"] = FACE_f09f87aff09f8FACE_7b5;
	    m_keyValMap["f09f87b0f09f8FACE_7b7"] = FACE_f09f87b0f09f8FACE_7b7;
	    m_keyValMap["f09f87b7f09f8FACE_7ba"] = FACE_f09f87b7f09f8FACE_7ba;
	    m_keyValMap["f09f87baf09f8FACE_7b8"] = FACE_f09f87baf09f8FACE_7b8;
	    m_keyValMap["f09f8881"] = FACE_f09f8881;
	    m_keyValMap["f09f8882"] = FACE_f09f8882;
	    m_keyValMap["f09f889a"] = FACE_f09f889a;
	    m_keyValMap["f09f88af"] = FACE_f09f88af;
	    m_keyValMap["f09f88b3"] = FACE_f09f88b3;
	    m_keyValMap["f09f88b5"] = FACE_f09f88b5;
	    m_keyValMap["f09f88b6"] = FACE_f09f88b6;
	    m_keyValMap["f09f88b7"] = FACE_f09f88b7;
	    m_keyValMap["f09f88b8"] = FACE_f09f88b8;
	    m_keyValMap["f09f88b9"] = FACE_f09f88b9;
	    m_keyValMap["f09f88ba"] = FACE_f09f88ba;
	    m_keyValMap["f09f8990"] = FACE_f09f8990;
	    m_keyValMap["f09f8c80"] = FACE_f09f8c80;
	    m_keyValMap["f09f8c82"] = FACE_f09f8c82;
	    m_keyValMap["f09f8c83"] = FACE_f09f8c83;
	    m_keyValMap["f09f8c84"] = FACE_f09f8c84;
	    m_keyValMap["f09f8c85"] = FACE_f09f8c85;
	    m_keyValMap["f09f8c86"] = FACE_f09f8c86;
	    m_keyValMap["f09f8c87"] = FACE_f09f8c87;
	    m_keyValMap["f09f8c88"] = FACE_f09f8c88;
	    m_keyValMap["f09f8c8a"] = FACE_f09f8c8a;
	    m_keyValMap["f09f8c99"] = FACE_f09f8c99;
	    m_keyValMap["f09f8c9f"] = FACE_f09f8c9f;
	    m_keyValMap["f09f8cb4"] = FACE_f09f8cb4;
	    m_keyValMap["f09f8cb5"] = FACE_f09f8cb5;
	    m_keyValMap["f09f8cb7"] = FACE_f09f8cb7;
	    m_keyValMap["f09f8cb9"] = FACE_f09f8cb9;
	    m_keyValMap["f09f8cba"] = FACE_f09f8cba;
	    m_keyValMap["f09f8cbb"] = FACE_f09f8cbb;
	    m_keyValMap["f09f8cbe"] = FACE_f09f8cbe;
	    m_keyValMap["f09f8d80"] = FACE_f09f8d80;
	    m_keyValMap["f09f8d81"] = FACE_f09f8d81;
	    m_keyValMap["f09f8d82"] = FACE_f09f8d82;
	    m_keyValMap["f09f8d83"] = FACE_f09f8d83;
	    m_keyValMap["f09f8d85"] = FACE_f09f8d85;
	    m_keyValMap["f09f8d86"] = FACE_f09f8d86;
	    m_keyValMap["f09f8d89"] = FACE_f09f8d89;
	    m_keyValMap["f09f8d8a"] = FACE_f09f8d8a;
	    m_keyValMap["f09f8d8e"] = FACE_f09f8d8e;
	    m_keyValMap["f09f8d93"] = FACE_f09f8d93;
	    m_keyValMap["f09f8d94"] = FACE_f09f8d94;
	    m_keyValMap["f09f8d98"] = FACE_f09f8d98;
	    m_keyValMap["f09f8d99"] = FACE_f09f8d99;
	    m_keyValMap["f09f8d9a"] = FACE_f09f8d9a;
	    m_keyValMap["f09f8d9b"] = FACE_f09f8d9b;
	    m_keyValMap["f09f8d9c"] = FACE_f09f8d9c;
	    m_keyValMap["f09f8d9d"] = FACE_f09f8d9d;
	    m_keyValMap["f09f8d9e"] = FACE_f09f8d9e;
	    m_keyValMap["f09f8d9f"] = FACE_f09f8d9f;
	    m_keyValMap["f09f8da1"] = FACE_f09f8da1;
	    m_keyValMap["f09f8da2"] = FACE_f09f8da2;
	    m_keyValMap["f09f8da3"] = FACE_f09f8da3;
	    m_keyValMap["f09f8da6"] = FACE_f09f8da6;
	    m_keyValMap["f09f8da7"] = FACE_f09f8da7;
	    m_keyValMap["f09f8db0"] = FACE_f09f8db0;
	    m_keyValMap["f09f8db1"] = FACE_f09f8db1;
	    m_keyValMap["f09f8db2"] = FACE_f09f8db2;
	    m_keyValMap["f09f8db3"] = FACE_f09f8db3;
	    m_keyValMap["f09f8db4"] = FACE_f09f8db4;
	    m_keyValMap["f09f8db5"] = FACE_f09f8db5;
	    m_keyValMap["f09f8db6"] = FACE_f09f8db6;
	    m_keyValMap["f09f8db8"] = FACE_f09f8db8;
	    m_keyValMap["f09f8dba"] = FACE_f09f8dba;
	    m_keyValMap["f09f8dbb"] = FACE_f09f8dbb;
	    m_keyValMap["f09f8e80"] = FACE_f09f8e80;
	    m_keyValMap["f09f8e81"] = FACE_f09f8e81;
	    m_keyValMap["f09f8e82"] = FACE_f09f8e82;
	    m_keyValMap["f09f8e83"] = FACE_f09f8e83;
	    m_keyValMap["f09f8e84"] = FACE_f09f8e84;
	    m_keyValMap["f09f8e85"] = FACE_f09f8e85;
	    m_keyValMap["f09f8e86"] = FACE_f09f8e86;
	    m_keyValMap["f09f8e87"] = FACE_f09f8e87;
	    m_keyValMap["f09f8e88"] = FACE_f09f8e88;
	    m_keyValMap["f09f8e89"] = FACE_f09f8e89;
	    m_keyValMap["f09f8e8c"] = FACE_f09f8e8c;
	    m_keyValMap["f09f8e8d"] = FACE_f09f8e8d;
	    m_keyValMap["f09f8e8e"] = FACE_f09f8e8e;
	    m_keyValMap["f09f8e8f"] = FACE_f09f8e8f;
	    m_keyValMap["f09f8e90"] = FACE_f09f8e90;
	    m_keyValMap["f09f8e91"] = FACE_f09f8e91;
	    m_keyValMap["f09f8e92"] = FACE_f09f8e92;
	    m_keyValMap["f09f8ea1"] = FACE_f09f8ea1;
	    m_keyValMap["f09f8ea2"] = FACE_f09f8ea2;
	    m_keyValMap["f09f8ea4"] = FACE_f09f8ea4;
	    m_keyValMap["f09f8ea5"] = FACE_f09f8ea5;
	    m_keyValMap["f09f8ea6"] = FACE_f09f8ea6;
	    m_keyValMap["f09f8ea7"] = FACE_f09f8ea7;
	    m_keyValMap["f09f8ea8"] = FACE_f09f8ea8;
	    m_keyValMap["f09f8ea9"] = FACE_f09f8ea9;
	    m_keyValMap["f09f8eab"] = FACE_f09f8eab;
	    m_keyValMap["f09f8eac"] = FACE_f09f8eac;
	    m_keyValMap["f09f8eaf"] = FACE_f09f8eaf;
	    m_keyValMap["f09f8eb0"] = FACE_f09f8eb0;
	    m_keyValMap["f09f8eb1"] = FACE_f09f8eb1;
	    m_keyValMap["f09f8eb5"] = FACE_f09f8eb5;
	    m_keyValMap["f09f8eb7"] = FACE_f09f8eb7;
	    m_keyValMap["f09f8eb8"] = FACE_f09f8eb8;
	    m_keyValMap["f09f8eb9"] = FACE_f09f8eb9;
	    m_keyValMap["f09f8eba"] = FACE_f09f8eba;
	    m_keyValMap["f09f8ebe"] = FACE_f09f8ebe;
	    m_keyValMap["f09f8ebf"] = FACE_f09f8ebf;
	    m_keyValMap["f09f8f80"] = FACE_f09f8f80;
	    m_keyValMap["f09f8f81"] = FACE_f09f8f81;
	    m_keyValMap["f09f8f83"] = FACE_f09f8f83;
	    m_keyValMap["f09f8f84"] = FACE_f09f8f84;
	    m_keyValMap["f09f8f86"] = FACE_f09f8f86;
	    m_keyValMap["f09f8f88"] = FACE_f09f8f88;
	    m_keyValMap["f09f8f8a"] = FACE_f09f8f8a;
	    m_keyValMap["f09f8fa0"] = FACE_f09f8fa0;
	    m_keyValMap["f09f8fa2"] = FACE_f09f8fa2;
	    m_keyValMap["f09f8fa3"] = FACE_f09f8fa3;
	    m_keyValMap["f09f8fa5"] = FACE_f09f8fa5;
	    m_keyValMap["f09f8fa6"] = FACE_f09f8fa6;
	    m_keyValMap["f09f8fa7"] = FACE_f09f8fa7;
	    m_keyValMap["f09f8fa8"] = FACE_f09f8fa8;
	    m_keyValMap["f09f8fa9"] = FACE_f09f8fa9;
	    m_keyValMap["f09f8faa"] = FACE_f09f8faa;
	    m_keyValMap["f09f8fab"] = FACE_f09f8fab;
	    m_keyValMap["f09f8fac"] = FACE_f09f8fac;
	    m_keyValMap["f09f8fad"] = FACE_f09f8fad;
	    m_keyValMap["f09f8faf"] = FACE_f09f8faf;
	    m_keyValMap["f09f8fb0"] = FACE_f09f8fb0;
	    m_keyValMap["f09f908d"] = FACE_f09f908d;
	    m_keyValMap["f09f908e"] = FACE_f09f908e;
	    m_keyValMap["f09f9091"] = FACE_f09f9091;
	    m_keyValMap["f09f9092"] = FACE_f09f9092;
	    m_keyValMap["f09f9094"] = FACE_f09f9094;
	    m_keyValMap["f09f9097"] = FACE_f09f9097;
	    m_keyValMap["f09f9098"] = FACE_f09f9098;
	    m_keyValMap["f09f9099"] = FACE_f09f9099;
	    m_keyValMap["f09f909a"] = FACE_f09f909a;
	    m_keyValMap["f09f909b"] = FACE_f09f909b;
	    m_keyValMap["f09f909f"] = FACE_f09f909f;
	    m_keyValMap["f09f90a0"] = FACE_f09f90a0;
	    m_keyValMap["f09f90a4"] = FACE_f09f90a4;
	    m_keyValMap["f09f90a6"] = FACE_f09f90a6;
	    m_keyValMap["f09f90a7"] = FACE_f09f90a7;
	    m_keyValMap["f09f90a8"] = FACE_f09f90a8;
	    m_keyValMap["f09f90ab"] = FACE_f09f90ab;
	    m_keyValMap["f09f90ac"] = FACE_f09f90ac;
	    m_keyValMap["f09f90ad"] = FACE_f09f90ad;
	    m_keyValMap["f09f90ae"] = FACE_f09f90ae;
	    m_keyValMap["f09f90af"] = FACE_f09f90af;
	    m_keyValMap["f09f90b0"] = FACE_f09f90b0;
	    m_keyValMap["f09f90b1"] = FACE_f09f90b1;
	    m_keyValMap["f09f90b3"] = FACE_f09f90b3;
	    m_keyValMap["f09f90b4"] = FACE_f09f90b4;
	    m_keyValMap["f09f90b5"] = FACE_f09f90b5;
	    m_keyValMap["f09f90b6"] = FACE_f09f90b6;
	    m_keyValMap["f09f90b7"] = FACE_f09f90b7;
	    m_keyValMap["f09f90b8"] = FACE_f09f90b8;
	    m_keyValMap["f09f90b9"] = FACE_f09f90b9;
	    m_keyValMap["f09f90ba"] = FACE_f09f90ba;
	    m_keyValMap["f09f90bb"] = FACE_f09f90bb;
	    m_keyValMap["f09f9180"] = FACE_f09f9180;
	    m_keyValMap["f09f9182"] = FACE_f09f9182;
	    m_keyValMap["f09f9183"] = FACE_f09f9183;
	    m_keyValMap["f09f9184"] = FACE_f09f9184;
	    m_keyValMap["f09f9186"] = FACE_f09f9186;
	    m_keyValMap["f09f9187"] = FACE_f09f9187;
	    m_keyValMap["f09f9188"] = FACE_f09f9188;
	    m_keyValMap["f09f9189"] = FACE_f09f9189;
	    m_keyValMap["f09f918a"] = FACE_f09f918a;
	    m_keyValMap["f09f918b"] = FACE_f09f918b;
	    m_keyValMap["f09f918c"] = FACE_f09f918c;
	    m_keyValMap["f09f918d"] = FACE_f09f918d;
	    m_keyValMap["f09f918e"] = FACE_f09f918e;
	    m_keyValMap["f09f918f"] = FACE_f09f918f;
	    m_keyValMap["f09f9190"] = FACE_f09f9190;
	    m_keyValMap["f09f9191"] = FACE_f09f9191;
	    m_keyValMap["f09f9192"] = FACE_f09f9192;
	    m_keyValMap["f09f9194"] = FACE_f09f9194;
	    m_keyValMap["f09f9195"] = FACE_f09f9195;
	    m_keyValMap["f09f9197"] = FACE_f09f9197;
	    m_keyValMap["f09f9198"] = FACE_f09f9198;
	    m_keyValMap["f09f9199"] = FACE_f09f9199;
	    m_keyValMap["f09f919c"] = FACE_f09f919c;
	    m_keyValMap["f09f919f"] = FACE_f09f919f;
	    m_keyValMap["f09f91a0"] = FACE_f09f91a0;
	    m_keyValMap["f09f91a1"] = FACE_f09f91a1;
	    m_keyValMap["f09f91a2"] = FACE_f09f91a2;
	    m_keyValMap["f09f91a3"] = FACE_f09f91a3;
	    m_keyValMap["f09f91a6"] = FACE_f09f91a6;
	    m_keyValMap["f09f91a7"] = FACE_f09f91a7;
	    m_keyValMap["f09f91a8"] = FACE_f09f91a8;
	    m_keyValMap["f09f91a9"] = FACE_f09f91a9;
	    m_keyValMap["f09f91ab"] = FACE_f09f91ab;
	    m_keyValMap["f09f91ae"] = FACE_f09f91ae;
	    m_keyValMap["f09f91af"] = FACE_f09f91af;
	    m_keyValMap["f09f91b1"] = FACE_f09f91b1;
	    m_keyValMap["f09f91b2"] = FACE_f09f91b2;
	    m_keyValMap["f09f91b3"] = FACE_f09f91b3;
	    m_keyValMap["f09f91b4"] = FACE_f09f91b4;
	    m_keyValMap["f09f91b5"] = FACE_f09f91b5;
	    m_keyValMap["f09f91b6"] = FACE_f09f91b6;
	    m_keyValMap["f09f91b7"] = FACE_f09f91b7;
	    m_keyValMap["f09f91b8"] = FACE_f09f91b8;
	    m_keyValMap["f09f91bb"] = FACE_f09f91bb;
	    m_keyValMap["f09f91bc"] = FACE_f09f91bc;
	    m_keyValMap["f09f91bd"] = FACE_f09f91bd;
	    m_keyValMap["f09f91be"] = FACE_f09f91be;
	    m_keyValMap["f09f91bf"] = FACE_f09f91bf;
	    m_keyValMap["f09f9280"] = FACE_f09f9280;
	    m_keyValMap["f09f9281"] = FACE_f09f9281;
	    m_keyValMap["f09f9282"] = FACE_f09f9282;
	    m_keyValMap["f09f9283"] = FACE_f09f9283;
	    m_keyValMap["f09f9284"] = FACE_f09f9284;
	    m_keyValMap["f09f9285"] = FACE_f09f9285;
	    m_keyValMap["f09f9286"] = FACE_f09f9286;
	    m_keyValMap["f09f9287"] = FACE_f09f9287;
	    m_keyValMap["f09f9288"] = FACE_f09f9288;
	    m_keyValMap["f09f9289"] = FACE_f09f9289;
	    m_keyValMap["f09f928a"] = FACE_f09f928a;
	    m_keyValMap["f09f928b"] = FACE_f09f928b;
	    m_keyValMap["f09f928d"] = FACE_f09f928d;
	    m_keyValMap["f09f928e"] = FACE_f09f928e;
	    m_keyValMap["f09f928f"] = FACE_f09f928f;
	    m_keyValMap["f09f9290"] = FACE_f09f9290;
	    m_keyValMap["f09f9291"] = FACE_f09f9291;
	    m_keyValMap["f09f9292"] = FACE_f09f9292;
	    m_keyValMap["f09f9293"] = FACE_f09f9293;
	    m_keyValMap["f09f9294"] = FACE_f09f9294;
	    m_keyValMap["f09f9297"] = FACE_f09f9297;
	    m_keyValMap["f09f9298"] = FACE_f09f9298;
	    m_keyValMap["f09f9299"] = FACE_f09f9299;
	    m_keyValMap["f09f929a"] = FACE_f09f929a;
	    m_keyValMap["f09f929b"] = FACE_f09f929b;
	    m_keyValMap["f09f929c"] = FACE_f09f929c;
	    m_keyValMap["f09f929d"] = FACE_f09f929d;
	    m_keyValMap["f09f929f"] = FACE_f09f929f;
	    m_keyValMap["f09f92a1"] = FACE_f09f92a1;
	    m_keyValMap["f09f92a2"] = FACE_f09f92a2;
	    m_keyValMap["f09f92a3"] = FACE_f09f92a3;
	    m_keyValMap["f09f92a4"] = FACE_f09f92a4;
	    m_keyValMap["f09f92a6"] = FACE_f09f92a6;
	    m_keyValMap["f09f92a8"] = FACE_f09f92a8;
	    m_keyValMap["f09f92a9"] = FACE_f09f92a9;
	    m_keyValMap["f09f92aa"] = FACE_f09f92aa;
	    m_keyValMap["f09f92b0"] = FACE_f09f92b0;
	    m_keyValMap["f09f92b1"] = FACE_f09f92b1;
	    m_keyValMap["f09f92b9"] = FACE_f09f92b9;
	    m_keyValMap["f09f92ba"] = FACE_f09f92ba;
	    m_keyValMap["f09f92bb"] = FACE_f09f92bb;
	    m_keyValMap["f09f92bc"] = FACE_f09f92bc;
	    m_keyValMap["f09f92bd"] = FACE_f09f92bd;
	    m_keyValMap["f09f92bf"] = FACE_f09f92bf;
	    m_keyValMap["f09f9380"] = FACE_f09f9380;
	    m_keyValMap["f09f9396"] = FACE_f09f9396;
	    m_keyValMap["f09f939d"] = FACE_f09f939d;
	    m_keyValMap["f09f93a0"] = FACE_f09f93a0;
	    m_keyValMap["f09f93a1"] = FACE_f09f93a1;
	    m_keyValMap["f09f93a2"] = FACE_f09f93a2;
	    m_keyValMap["f09f93a3"] = FACE_f09f93a3;
	    m_keyValMap["f09f93a9"] = FACE_f09f93a9;
	    m_keyValMap["f09f93ab"] = FACE_f09f93ab;
	    m_keyValMap["f09f93ae"] = FACE_f09f93ae;
	    m_keyValMap["f09f93b1"] = FACE_f09f93b1;
	    m_keyValMap["f09f93b2"] = FACE_f09f93b2;
	    m_keyValMap["f09f93b3"] = FACE_f09f93b3;
	    m_keyValMap["f09f93b4"] = FACE_f09f93b4;
	    m_keyValMap["f09f93b6"] = FACE_f09f93b6;
	    m_keyValMap["f09f93b7"] = FACE_f09f93b7;
	    m_keyValMap["f09f93ba"] = FACE_f09f93ba;
	    m_keyValMap["f09f93bb"] = FACE_f09f93bb;
	    m_keyValMap["f09f93bc"] = FACE_f09f93bc;
	    m_keyValMap["f09f948a"] = FACE_f09f948a;
	    m_keyValMap["f09f948d"] = FACE_f09f948d;
	    m_keyValMap["f09f9491"] = FACE_f09f9491;
	    m_keyValMap["f09f9492"] = FACE_f09f9492;
	    m_keyValMap["f09f9493"] = FACE_f09f9493;
	    m_keyValMap["f09f9494"] = FACE_f09f9494;
	    m_keyValMap["f09f949d"] = FACE_f09f949d;
	    m_keyValMap["f09f949e"] = FACE_f09f949e;
	    m_keyValMap["f09f94a5"] = FACE_f09f94a5;
	    m_keyValMap["f09f94a8"] = FACE_f09f94a8;
	    m_keyValMap["f09f94ab"] = FACE_f09f94ab;
	    m_keyValMap["f09f94af"] = FACE_f09f94af;
	    m_keyValMap["f09f94b0"] = FACE_f09f94b0;
	    m_keyValMap["f09f94b1"] = FACE_f09f94b1;
	    m_keyValMap["f09f94b4"] = FACE_f09f94b4;
	    m_keyValMap["f09f9590"] = FACE_f09f9590;
	    m_keyValMap["f09f9591"] = FACE_f09f9591;
	    m_keyValMap["f09f9592"] = FACE_f09f9592;
	    m_keyValMap["f09f9593"] = FACE_f09f9593;
	    m_keyValMap["f09f9594"] = FACE_f09f9594;
	    m_keyValMap["f09f9595"] = FACE_f09f9595;
	    m_keyValMap["f09f9596"] = FACE_f09f9596;
	    m_keyValMap["f09f9597"] = FACE_f09f9597;
	    m_keyValMap["f09f9598"] = FACE_f09f9598;
	    m_keyValMap["f09f9599"] = FACE_f09f9599;
	    m_keyValMap["f09f959a"] = FACE_f09f959a;
	    m_keyValMap["f09f959b"] = FACE_f09f959b;
	    m_keyValMap["f09f97bb"] = FACE_f09f97bb;
	    m_keyValMap["f09f97bc"] = FACE_f09f97bc;
	    m_keyValMap["f09f97bd"] = FACE_f09f97bd;
	    m_keyValMap["f09f9881"] = FACE_f09f9881;
	    m_keyValMap["f09f9882"] = FACE_f09f9882;
	    m_keyValMap["f09f9883"] = FACE_f09f9883;
	    m_keyValMap["f09f9884"] = FACE_f09f9884;
	    m_keyValMap["f09f9889"] = FACE_f09f9889;
	    m_keyValMap["f09f988a"] = FACE_f09f988a;
	    m_keyValMap["f09f988c"] = FACE_f09f988c;
	    m_keyValMap["f09f988d"] = FACE_f09f988d;
	    m_keyValMap["f09f988f"] = FACE_f09f988f;
	    m_keyValMap["f09f9892"] = FACE_f09f9892;
	    m_keyValMap["f09f9893"] = FACE_f09f9893;
	    m_keyValMap["f09f9894"] = FACE_f09f9894;
	    m_keyValMap["f09f9896"] = FACE_f09f9896;
	    m_keyValMap["f09f9898"] = FACE_f09f9898;
	    m_keyValMap["f09f989a"] = FACE_f09f989a;
	    m_keyValMap["f09f989c"] = FACE_f09f989c;
	    m_keyValMap["f09f989d"] = FACE_f09f989d;
	    m_keyValMap["f09f989e"] = FACE_f09f989e;
	    m_keyValMap["f09f98a0"] = FACE_f09f98a0;
	    m_keyValMap["f09f98a1"] = FACE_f09f98a1;
	    m_keyValMap["f09f98a2"] = FACE_f09f98a2;
	    m_keyValMap["f09f98a3"] = FACE_f09f98a3;
	    m_keyValMap["f09f98a5"] = FACE_f09f98a5;
	    m_keyValMap["f09f98a8"] = FACE_f09f98a8;
	    m_keyValMap["f09f98aa"] = FACE_f09f98aa;
	    m_keyValMap["f09f98ad"] = FACE_f09f98ad;
	    m_keyValMap["f09f98b0"] = FACE_f09f98b0;
	    m_keyValMap["f09f98b1"] = FACE_f09f98b1;
	    m_keyValMap["f09f98b2"] = FACE_f09f98b2;
	    m_keyValMap["f09f98b3"] = FACE_f09f98b3;
	    m_keyValMap["f09f98b7"] = FACE_f09f98b7;
	    m_keyValMap["f09f9985"] = FACE_f09f9985;
	    m_keyValMap["f09f9986"] = FACE_f09f9986;
	    m_keyValMap["f09f9987"] = FACE_f09f9987;
	    m_keyValMap["f09f998c"] = FACE_f09f998c;
	    m_keyValMap["f09f998f"] = FACE_f09f998f;
	    m_keyValMap["f09f9a80"] = FACE_f09f9a80;
	    m_keyValMap["f09f9a83"] = FACE_f09f9a83;
	    m_keyValMap["f09f9a84"] = FACE_f09f9a84;
	    m_keyValMap["f09f9a85"] = FACE_f09f9a85;
	    m_keyValMap["f09f9a87"] = FACE_f09f9a87;
	    m_keyValMap["f09f9a89"] = FACE_f09f9a89;
	    m_keyValMap["f09f9a8c"] = FACE_f09f9a8c;
	    m_keyValMap["f09f9a8f"] = FACE_f09f9a8f;
	    m_keyValMap["f09f9a91"] = FACE_f09f9a91;
	    m_keyValMap["f09f9a92"] = FACE_f09f9a92;
	    m_keyValMap["f09f9a93"] = FACE_f09f9a93;
	    m_keyValMap["f09f9a95"] = FACE_f09f9a95;
	    m_keyValMap["f09f9a97"] = FACE_f09f9a97;
	    m_keyValMap["f09f9a99"] = FACE_f09f9a99;
	    m_keyValMap["f09f9a9a"] = FACE_f09f9a9a;
	    m_keyValMap["f09f9aa2"] = FACE_f09f9aa2;
	    m_keyValMap["f09f9aa4"] = FACE_f09f9aa4;
	    m_keyValMap["f09f9aa5"] = FACE_f09f9aa5;
	    m_keyValMap["f09f9aa7"] = FACE_f09f9aa7;
	    m_keyValMap["f09f9aac"] = FACE_f09f9aac;
	    m_keyValMap["f09f9aad"] = FACE_f09f9aad;
	    m_keyValMap["f09f9ab2"] = FACE_f09f9ab2;
	    m_keyValMap["f09f9ab6"] = FACE_f09f9ab6;
	    m_keyValMap["f09f9ab9"] = FACE_f09f9ab9;
	    m_keyValMap["f09f9aba"] = FACE_f09f9aba;
	    m_keyValMap["f09f9abb"] = FACE_f09f9abb;
	    m_keyValMap["f09f9abc"] = FACE_f09f9abc;
	    m_keyValMap["f09f9abd"] = FACE_f09f9abd;
	    m_keyValMap["f09f9abe"] = FACE_f09f9abe;
	    m_keyValMap["f09f9b80"] = FACE_f09f9b80;
	    m_keyValMap["f09f9cb8"] = FACE_f09f9cb8;


		////////字符表情需要优先显示到前面的表情列表
	    m_frontEmoji.push_back("e298ba");
	    m_frontEmoji.push_back("ee908a");
	    m_frontEmoji.push_back("ee908b");
	    m_frontEmoji.push_back("ee908c");
	    m_frontEmoji.push_back("ee908d");
	    m_frontEmoji.push_back("ee908e");
	    m_frontEmoji.push_back("ee908f");
	    m_frontEmoji.push_back("ee8196");
	    m_frontEmoji.push_back("ee8197");
	    m_frontEmoji.push_back("ee8198");
	    m_frontEmoji.push_back("ee8199");
	    m_frontEmoji.push_back("ee8485");
	    m_frontEmoji.push_back("ee8486");
	    m_frontEmoji.push_back("ee8487");
	    m_frontEmoji.push_back("ee8488");

	    m_frontEmoji.push_back("ee9081");
	    m_frontEmoji.push_back("ee9082");
	    m_frontEmoji.push_back("ee9083");
	    m_frontEmoji.push_back("ee9084");
	    m_frontEmoji.push_back("ee9085");
	    m_frontEmoji.push_back("ee9086");
	    m_frontEmoji.push_back("ee9087");
	    m_frontEmoji.push_back("ee9088");
	    m_frontEmoji.push_back("ee9089");
	    m_frontEmoji.push_back("ee9090");
	    m_frontEmoji.push_back("ee9091");
	    m_frontEmoji.push_back("ee9092");
	    m_frontEmoji.push_back("ee9093");
	    m_frontEmoji.push_back("ee9094");
	    m_frontEmoji.push_back("ee9095");
	    m_frontEmoji.push_back("ee9096");
	    m_frontEmoji.push_back("ee9097");
	    m_frontEmoji.push_back("ee9098");
	    m_frontEmoji.push_back("f09f98a0");
	    m_frontEmoji.push_back("f09f98a1");
	    m_frontEmoji.push_back("f09f98a2");
	    m_frontEmoji.push_back("f09f98a3");
	    m_frontEmoji.push_back("f09f98a5");
	    m_frontEmoji.push_back("f09f98a8");
	    m_frontEmoji.push_back("f09f98aa");
	    m_frontEmoji.push_back("f09f98ad");
	    m_frontEmoji.push_back("f09f98b0");
	    m_frontEmoji.push_back("f09f98b1");
	    m_frontEmoji.push_back("f09f98b2");
	    m_frontEmoji.push_back("f09f98b3");
	    m_frontEmoji.push_back("f09f98b7");
	    m_frontEmoji.push_back("f09f988a");
	    m_frontEmoji.push_back("f09f988c");
	    m_frontEmoji.push_back("f09f988d");
	    m_frontEmoji.push_back("f09f988f");
	    m_frontEmoji.push_back("f09f989a");
	    m_frontEmoji.push_back("f09f989c");
	    m_frontEmoji.push_back("f09f989d");
	    m_frontEmoji.push_back("f09f989e");
	    m_frontEmoji.push_back("f09f9881");
	    m_frontEmoji.push_back("f09f9882");
	    m_frontEmoji.push_back("f09f9883");
	    m_frontEmoji.push_back("f09f9884");
	    m_frontEmoji.push_back("f09f9889");
	    m_frontEmoji.push_back("f09f9892");
	    m_frontEmoji.push_back("f09f9893");
	    m_frontEmoji.push_back("f09f9894");
	    m_frontEmoji.push_back("f09f9896");
	    m_frontEmoji.push_back("f09f9898");

	    m_frontOther.push_back("e29c8a");
	    m_frontOther.push_back("e29c8b");
	    m_frontOther.push_back("e29c8c");
	    m_frontOther.push_back("e2989d");
	    m_frontOther.push_back("e2989defb88f");
	    m_frontOther.push_back("ee88af");
	    m_frontOther.push_back("ee88b0");
	    m_frontOther.push_back("ee88b1");
	    m_frontOther.push_back("ee88ae");
	    m_frontOther.push_back("ee90a0");
	    m_frontOther.push_back("ee90a1");
	    m_frontOther.push_back("ee90a2");
	    m_frontOther.push_back("ee90a7");
	    m_frontOther.push_back("ee808d");
	    m_frontOther.push_back("ee808f");
	    m_frontOther.push_back("ee909d");
	    m_frontOther.push_back("ee909e");
	    m_frontOther.push_back("ee909f");
	    m_frontOther.push_back("ee8090");
	    m_frontOther.push_back("ee8091");
	    m_frontOther.push_back("ee8092");
	    m_frontOther.push_back("ee8c97");
	    m_frontOther.push_back("ee8ca5");
	    m_frontOther.push_back("e2988e");
	    m_frontOther.push_back("ee8cb6");
	    m_frontOther.push_back("ee8cb7");
	    m_frontOther.push_back("f09f998c");
	    m_frontOther.push_back("f09f998f");
	    m_frontOther.push_back("f09f9186");
	    m_frontOther.push_back("f09f9187");
	    m_frontOther.push_back("f09f9188");
	    m_frontOther.push_back("f09f9189");
	    m_frontOther.push_back("f09f9190");
	    m_frontOther.push_back("f09f918f");
	    m_frontOther.push_back("f09f918e");
	    m_frontOther.push_back("f09f918d");
	    m_frontOther.push_back("f09f918c");
	    m_frontOther.push_back("f09f918b");
	    m_frontOther.push_back("f09f918a");
	    m_frontOther.push_back("f09f92aa");

		//自定义表情
		m_InstructMap.insert(std::pair<std::string, std::string>("[微笑]", "weixiao"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[色]", "se"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[得意]", "deyi"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[流泪]", "liulei"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[害羞]", "haixiu"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[闭嘴]", "bizui"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[睡]", "shui"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[尴尬]", "ganga"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[发怒]", "fanu"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[调皮]", "tiaopi"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[呲牙]", "ciya"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[惊讶]", "jingya"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[抓狂]", "zhuakuang"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[偷笑]", "touxiao"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[白眼]", "baiyan"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[傲慢]", "aoman"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[流汗]", "liuhan"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[疑问]", "yiwen"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[嘘]", "xu"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[晕]", "yun"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[疯了]", "fengle"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[敲打]", "qiaoda"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[衰]", "shuai"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[再见]", "zaijian"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[抠鼻]", "koubi"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[鼓掌]", "guzhang"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[坏笑]", "huaixiao"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[鄙视]", "bishi"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[委屈]", "weiqu"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[阴险]", "yinxian"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[亲亲]", "qinqin"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[可怜]", "kelian"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[左哼哼]", "zuohengheng"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[右哼哼]", "youhengheng"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[不高兴]", "bugaoxing"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[挨打]", "aida"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[不屑]", "buxie"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[大笑]", "daxiao"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[哼]", "heng"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[花痴]", "huachi"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[哭]", "ku"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[困]", "kun"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[冷汗]", "lenghan"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[难过]", "nanguo"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[怒]", "nu"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[窃笑]", "qiexiao"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[吓]", "xia"));
		m_InstructMap.insert(std::pair<std::string, std::string>("[折磨]", "zhemo"));


		m_engInstructMap.insert(std::pair<std::string, std::string>("[Smile]", "weixiao"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Drool]", "se"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Smug]", "deyi"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Tears]", "liulei"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Shy]", "haixiu"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Slience]", "bizui"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Sleep]", "shui"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Awkward]", "ganga"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Angry]", "fanu"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Naughty]", "tiaopi"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Grin]", "ciya"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Surprise]", "jingya"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Scream]", "zhuakuang"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Titter]", "touxiao"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Slight]", "baiyan"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Arrogant]", "aoman"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Speechless]", "liuhan"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Question]", "yiwen"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Hush]", "xu"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Dizzy]", "yun"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Crazy]", "fengle"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Hammer]", "qiaoda"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Unlucky]", "shuai"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Bye]", "zaijian"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[NosePick]", "koubi"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Applaud]", "guzhang"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Grin]", "huaixiao"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Disdain]", "bishi"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Grievance]", "weiqu"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Sly]", "yinxian"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Kiss]", "qinqin"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Pitiful]", "kelian"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[BahLeft]", "zuohengheng"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[BahRight]", "youhengheng"));
		m_engInstructMap.insert(std::pair<std::string, std::string>("[Unhappy]", "bugaoxing"));
		
		//动态表情
		m_keyDnyValMap["Dynamic_Expression_01"] = BAOBAO_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_02"] = CENGCENG_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_03"] = CHIFAN_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_04"] = DAKU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_05"] = HENG_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_06"] = JIAYOU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_07"] = KOUBI_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_08"] = LIEPI_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_09"] = QINQIN_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_10"] = SHUQIAN_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_11"] = SHUIJIAO_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_12"] = WULIAO_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_13"] = XIEXIE_DYNAMIC;
	    m_keyDnyValMap["Dynamic_Expression_14"] = ZAIJI_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_15"] = ZHUAKUANG_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_16"] = CHOUMEI_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_17"] = DAXIAO_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_18"] = DIANTOU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_19"] = FEIJIALOU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_20"] = GANBEI_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_21"] = JICHENGGOU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_22"] = JIABANLOU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_23"] = KAIHUILA_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_24"] = LAOTIANBAOYOU_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_25"] = QIANDAO_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_26"] = XINGHUI_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_27"] = YALISHANDA_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_28"] = ZAN_DYNAMIC;
		m_keyDnyValMap["Dynamic_Expression_29"] = GUZHANG_DYNAMIC;
	}

	void ExpressionWindow::setData()
	{
		if (mIsLoad)
		{
			return;
		}
		//豆豆表情
		std::map<std::string, std::string>::iterator iter= m_InstructMap.begin();
		for (;iter!= m_InstructMap.end();++iter)
		{
			std::string emoji = iter->second;
			QString path = ":/img/smilies/instruct/";
			path.append(emoji.c_str());
			path.append(".png");
			QString tips = QString::fromLocal8Bit(iter->first.c_str());
			tips = tips.remove("[").remove("]");
			mEmojiUserDef->addEmotionItem(path, tips);
			QCoreApplication::processEvents();
		}
		std::map<std::string, std::string>::iterator iter1= m_engInstructMap.begin();
		for (;iter1!= m_engInstructMap.end();++iter1)
		{
			std::string emoji = iter1->second;
			QString path = ":/img/smilies/instruct/";
			path.append(emoji.c_str());
			path.append(".png");
			mEmojiUserDef->addEmotionItem(path,iter1->first.c_str());
			QCoreApplication::processEvents();

		}
		mIsLoad = true;
	}

	void ExpressionWindow::showWin()
	{
		ExpressionWindow::initEmoji();
		setData();
		this->show();
	}

	void ExpressionWindow::onClicked( QString fileName )
	{
		//
		if (fileName.contains(":/img/smilies/dynamic_expression/"))
		{
			fileName = fileName.remove(":/img/smilies/dynamic_expression/");
			emit signalEmojiClicked(0,fileName);
			hide();
		}else if(fileName.contains(":/img/smilies/instruct/")||fileName.contains(":/img/smilies/emoji_face/")){
			emit signalEmojiClicked(1,fileName);
			hide();
		}
	}

	void ExpressionWindow::onFaceEmojiClicked()
	{
		mBtnFaceEmoji->setChecked(true);
		mBtnInstructEmoji->setChecked(false);
		mBtnDyEmoji->setChecked(false);
		mStackedWidget->setCurrentWidget(mEmojiEmojiFace);
		if (!mIsLoadFaced)
		{
			loadFaceEmojiData();
		}
	}

	void ExpressionWindow::onInstructEmojiClicked()
	{
		mBtnDyEmoji->setChecked(false);
		mBtnFaceEmoji->setChecked(false);
		mBtnInstructEmoji->setChecked(true);
		mStackedWidget->setCurrentWidget(mEmojiUserDef);
	}

	void ExpressionWindow::loadFaceEmojiData()
	{
		if(mIsLoadFaced==false){
			//基本表情
			QDir faceDir;
			faceDir.setPath(":/img/smilies/emoji_face/"); 
			QFileInfoList faceFileInfoList = faceDir.entryInfoList(QDir::Files, QDir::Name);
			QString faceName="";
			QString facePath="";

            QMap<QString,QString> map1;
			QMap<QString,QString> map2;
			QMap<QString,QString> map3;
			for (int i = 0; i < faceFileInfoList.size(); i++)
			{
				facePath = faceFileInfoList.at(i).absoluteFilePath();
				faceName = faceFileInfoList.at(i).baseName();

				if (m_keyValMap.contains(faceName))
				{
					if (m_frontEmoji.contains(faceName))
					{
						map1[facePath] = m_keyValMap[faceName];
					}
					else if (m_frontOther.contains(faceName))
					{
						map2[facePath] = m_keyValMap[faceName];
					}
					else
					{
						map3[facePath] = m_keyValMap[faceName];
					}
				}
			}
			 QMap<QString,QString>::iterator iter = map1.begin();
			 while(iter != map1.end()){
				 mEmojiEmojiFace->addEmotionItem(iter.key(),iter.value());
				 iter++;
				 QCoreApplication::processEvents();
			 }
			 iter = map2.begin();
			 while(iter != map2.end()){
				 mEmojiEmojiFace->addEmotionItem(iter.key(),iter.value());
				 iter++;
				 QCoreApplication::processEvents();
			 }
			 iter = map3.begin();
			 while(iter != map3.end()){
				 mEmojiEmojiFace->addEmotionItem(iter.key(),iter.value());
				 iter++;
				 QCoreApplication::processEvents();
			 }
			mIsLoadFaced = true;
		}
	}

	void ExpressionWindow::onDyEmojiClicked()
	{
		mBtnFaceEmoji->setChecked(false);
		mBtnInstructEmoji->setChecked(false);
		mBtnDyEmoji->setChecked(true);
		mStackedWidget->setCurrentWidget(mEmojiDynamic);
		if (!mIsLoadDy)
		{
			loadDyEmojiData();
		}
	}

	void ExpressionWindow::loadDyEmojiData()
	{
		if (!mIsLoadDy)
		{
			//动态表情
		
			QList<QString> keys = m_keyDnyValMap.keys();
			for (int i=0;i<keys.size();++i)
			{
				QString key = keys.at(i);
				QString path = ":/img/smilies/dynamic_expression/";
				path.append(key);
				path.append(".gif");
				mEmojiDynamic->addEmotionItem(path,m_keyDnyValMap.value(key));
			}
			mIsLoadDy = true;
		}
	}

	TabItemButton::TabItemButton( QWidget*parent/*=CNull*/ ,QString icon):QPushButton(parent)
	{
		setFixedSize(60*gDdpi,40*gDdpi);
		this->setObjectName("ExpressButton");
		setCheckable(true);
		if (!icon.isEmpty())
		{
			QVBoxLayout* layout = new QVBoxLayout(this);
			QLabel*lbl = new QLabel(this);
			lbl->setPixmap(QPixmap(icon));
			lbl->setFixedSize(24*gDdpi,24*gDdpi);
			layout->addWidget(lbl,0,Qt::AlignCenter);
			lbl->setObjectName("transparentlbl");
			setLayout(layout);
		}
	}

	TabItemButton::~TabItemButton()
	{

	}

}