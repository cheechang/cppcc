#pragma once
#include <QDialog>
#include <QMessageBox>
#include <QDialogButtonBox>
#include <qstring.h>
class QVBoxLayout;
class QAbstractButton;
class QLabel;
class QHBoxLayout;
class QWidget;
namespace ui{
	class TitleBar;
	class MyMessageBox : public QDialog
	{
		Q_OBJECT
	public:
		explicit MyMessageBox(QWidget *parent = 0, const QString &title = tr("Tip"), const QString &text = "",
			QMessageBox::StandardButtons buttons = QMessageBox::Ok, QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
		~MyMessageBox();
		QAbstractButton *clickedButton() const;
		QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
		// 设置默认按钮
		void setDefaultButton(QPushButton *button);
		void setDefaultButton(QMessageBox::StandardButton button);
		// 设置窗体标题
		void setTitle(const QString &title);
		// 设置提示信息
		void setText(const QString &text);
		// 设置窗体图标
		void setIcon(const QString &icon);
		// 添加控件-替换提示信息所在的QLabel
		void addWidget(QWidget *pWidget);
		void addCancelButton(QDialogButtonBox::StandardButton buttons);

	protected:
		// 多语言翻译
		void changeEvent(QEvent *event);
		void paintEvent(QPaintEvent *event);
	private slots:
		void onButtonClicked(QAbstractButton *button);
	private:
		void translateUI();
		int execReturnCode(QAbstractButton *button);

	private:
		TitleBar* m_title;
		QLabel *m_pIconLabel;
		QLabel *m_pLabel;
		QHBoxLayout* m_cotentLayout;
		QVBoxLayout *m_pbtnLayout;
		QVBoxLayout *m_pMainLayout;
		QDialogButtonBox *m_pButtonBox;
		QAbstractButton *m_pClickedButton;
		QAbstractButton *m_pDefaultButton;
	};
	QMessageBox::StandardButton showInformation(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton);

	QMessageBox::StandardButton showError(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton);

	QMessageBox::StandardButton showSuccess(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton);
	QMessageBox::StandardButton showQuestion(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
		QMessageBox::StandardButton defaultButton = QMessageBox::Cancel);
	QMessageBox::StandardButton showWarning(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
		QMessageBox::StandardButton defaultButton = QMessageBox::Ok);
	QMessageBox::StandardButton showCritical(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton);
	QMessageBox::StandardButton showCheckBoxQuestion(QWidget *parent, const QString &title,
		const QString &text, QMessageBox::StandardButtons buttons,
		QMessageBox::StandardButton defaultButton);
}