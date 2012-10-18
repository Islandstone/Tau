#ifndef _CONSOLE_INCLUDE
#define _CONSOLE_INCLUDE

#include <QtGui>

class Console {
public:
	Console(QWidget *parent);

	void Show();
	void Hide();
	void Toggle();
private:
	QWidget* m_pWidget;
	QVBoxLayout* m_pLayout;
	QTextEdit* m_pText;
	QTextEdit* m_pInput;

	bool m_bVisible;
};

#endif
