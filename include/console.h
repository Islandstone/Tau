#ifndef _CONSOLE_INCLUDE
#define _CONSOLE_INCLUDE

#include <QtGui>

//#define CONSOLE_KEY Qt::Key_Pipe;

class ConsoleInput : public QTextEdit {
public:
	ConsoleInput(QWidget* parent = NULL);
	void keyPressEvent(QKeyEvent *event);
private:
};

class ConsoleText : public QTextEdit {
public:
	ConsoleText(QWidget* parent = NULL);
	void keyPressEvent(QKeyEvent* event);
};

class Console {
public:
	Console(QWidget *parent);

	void Show();
	void Hide();
	void Toggle();
private:
	QWidget* m_pWidget;
	QVBoxLayout* m_pLayout;
	ConsoleText* m_pText;
	ConsoleInput* m_pInput;

	bool m_bVisible;
};

#endif
