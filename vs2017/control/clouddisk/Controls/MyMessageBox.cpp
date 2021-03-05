#include "MyMessageBox.h"
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QEvent>
#include <QApplication>
#include <QDialogButtonBox>
#include <QAbstractButton>
#include <QLayout>
#include <QPainter>
#include <QWidget>
#include "TitleBar.h"
namespace ui{
	MyMessageBox::MyMessageBox(QWidget *parent, const QString &title, const QString &text,
		QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
		: QDialog(parent)
	{
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->resize(300, 150);

		m_title = new TitleBar(this,false,false,true);
		m_pIconLabel = new QLabel(this);
		m_pLabel = new QLabel(this);

		m_title->setFixedSize(300, 30);
		installEventFilter(m_title);

		setWindowIcon(QIcon(":/img/logo"));
		setWindowTitle(title);
		
		m_pButtonBox = new QDialogButtonBox(this);
		m_pButtonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
		setDefaultButton(defaultButton);

		QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
		if (pYesButton != NULL)
		{
			pYesButton->setObjectName("blueButton");
		}

		QPixmap pixmap(":/img/logo");
		m_pIconLabel->setPixmap(pixmap);
		m_pIconLabel->setFixedSize(35, 35);
		m_pIconLabel->setScaledContents(true);
		m_pLabel->setText(text);

		m_cotentLayout = new QHBoxLayout();
		m_cotentLayout->setContentsMargins(10, 10, 0, 20);
		m_cotentLayout->setAlignment(Qt::AlignCenter);
		m_cotentLayout->setSpacing(20);
		m_cotentLayout->addWidget(m_pIconLabel);
		m_cotentLayout->addWidget(m_pLabel);

		m_pbtnLayout = new QVBoxLayout();
		m_pbtnLayout->setContentsMargins(10, 10, 10, 15);
		m_pbtnLayout->setAlignment(Qt::AlignTop);
		m_pbtnLayout->addLayout(m_cotentLayout);
		m_pbtnLayout->addStretch();
		m_pbtnLayout->addWidget(m_pButtonBox);


		m_pMainLayout = new QVBoxLayout(this);
		m_pMainLayout->setContentsMargins(0, 0, 0, 0);
		m_pMainLayout->setAlignment(Qt::AlignTop);
		m_pMainLayout->setSpacing(0);
		m_pMainLayout->addWidget(m_title);
		m_pMainLayout->addLayout(m_pbtnLayout);
		setLayout(m_pMainLayout);

		translateUI();

		connect(m_pButtonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));
	}

	MyMessageBox::~MyMessageBox()
	{

	}

	void MyMessageBox::changeEvent(QEvent *event)
	{
		switch (event->type())
		{
		case QEvent::LanguageChange:
			translateUI();
			break;
		default:
			QDialog::changeEvent(event);
		}
	}

	void MyMessageBox::translateUI()
	{
		QPushButton *pYesButton = m_pButtonBox->button(QDialogButtonBox::Yes);
		if (pYesButton != NULL)
			pYesButton->setText(tr("是"));

		QPushButton *pNoButton = m_pButtonBox->button(QDialogButtonBox::No);
		if (pNoButton != NULL)
			pNoButton->setText(tr("否"));

		QPushButton *pOkButton = m_pButtonBox->button(QDialogButtonBox::Ok);
		if (pOkButton != NULL)
			pOkButton->setText(tr("确定"));

		QPushButton *pCancelButton = m_pButtonBox->button(QDialogButtonBox::Cancel);
		if (pCancelButton != NULL)
			pCancelButton->setText(tr("取消"));
	}

	QMessageBox::StandardButton MyMessageBox::standardButton(QAbstractButton *button) const
	{
		return (QMessageBox::StandardButton)m_pButtonBox->standardButton(button);
	}

	QAbstractButton *MyMessageBox::clickedButton() const
	{
		return m_pClickedButton;
	}

	int MyMessageBox::execReturnCode(QAbstractButton *button)
	{
		int nResult = m_pButtonBox->standardButton(button);
		return nResult;
	}

	void MyMessageBox::onButtonClicked(QAbstractButton *button)
	{
		m_pClickedButton = button;
		done(execReturnCode(button));
	}

	void MyMessageBox::setDefaultButton(QPushButton *button)
	{
		if (!m_pButtonBox->buttons().contains(button))
			return;
		m_pDefaultButton = button;
		button->setDefault(true);
		button->setFocus();
	}

	void MyMessageBox::setDefaultButton(QMessageBox::StandardButton button)
	{
		setDefaultButton(m_pButtonBox->button(QDialogButtonBox::StandardButton(button)));
	}

	void MyMessageBox::setTitle(const QString &title)
	{
		setWindowTitle(title);
	}

	void MyMessageBox::setText(const QString &text)
	{
		m_pLabel->setText(text);
	}
	void MyMessageBox::setIcon(const QString &icon)
	{
		m_pIconLabel->setPixmap(QPixmap(icon,"png"));
	}
	void MyMessageBox::addWidget(QWidget *pWidget)
	{
		m_pLabel->hide();
		m_pMainLayout->addWidget(pWidget);
	}
	void MyMessageBox::addCancelButton(QDialogButtonBox::StandardButton buttons){
		if (nullptr == m_pButtonBox)return;
		m_pButtonBox->addButton(buttons);
		translateUI();
		setDefaultButton(m_pButtonBox->button(buttons));
	}
	void MyMessageBox::paintEvent(QPaintEvent *event)
	{
		QPainter p(this);
		p.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //边框色
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	}

	QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(":/img/information.png");
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;
		return msgBox.standardButton(msgBox.clickedButton());
	}

	QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(":/img/error.png");
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;
		return msgBox.standardButton(msgBox.clickedButton());
	}

	QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(":/img/success.png");
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;
		return msgBox.standardButton(msgBox.clickedButton());
	}

	QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(QString(":/img/question"));
		msgBox.addCancelButton(QDialogButtonBox::Cancel);
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;
		return msgBox.standardButton(msgBox.clickedButton());
	}

	QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(":/img/warning");
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;
		return msgBox.standardButton(msgBox.clickedButton());
	}

	QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(":/img/warning");
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;
		return msgBox.standardButton(msgBox.clickedButton());
	}

	QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton)
	{
		MyMessageBox msgBox(parent, title, text, buttons, defaultButton);
		msgBox.setIcon(":/img/question");

		QCheckBox *pCheckBox = new QCheckBox(&msgBox);
		pCheckBox->setText(text);
		msgBox.addWidget(pCheckBox);
		if (msgBox.exec() == -1)
			return QMessageBox::Cancel;

		QMessageBox::StandardButton standardButton = msgBox.standardButton(msgBox.clickedButton());
		if (standardButton == QMessageBox::Yes)
		{
			return pCheckBox->isChecked() ? QMessageBox::Yes : QMessageBox::No;
		}
		return QMessageBox::Cancel;
	}

}