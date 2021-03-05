#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
namespace uicontrols{
	class Button : public QPushButton
	{
		Q_OBJECT

	public:
		Button(QWidget *parent=0);
		~Button();

	private:

	};
}
#endif // BUTTON_H
