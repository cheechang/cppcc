#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QRadioButton>
namespace uicontrols{
	class RadioButton : public QRadioButton
	{
		Q_OBJECT

	public:
		RadioButton(QWidget *parent);
		RadioButton(const QString &text, QWidget *parent=0);
		~RadioButton();

	private:

	};
}
#endif // RADIOBUTTON_H
