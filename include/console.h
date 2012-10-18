#ifndef _CONSOLE_INCLUDE
#define _CONSOLE_INCLUDE

#include <QtGui>

//#define CONSOLE_KEY Qt::Key_Pipe;

class ConVar;

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

class ConsoleWidget {
	ConsoleWidget();
public:

	static ConsoleWidget* GetInstance() {
		static ConsoleWidget console;
		return &console;
	}

	void InitWidgets(QWidget *parent);

	void Show();
	void Hide();
	void Toggle();

	void SendCommand(QString str);
private:
	QSet<ConVar> m_vConvars;

	QWidget* m_pWidget;
	QVBoxLayout* m_pLayout;
	ConsoleText* m_pText;
	ConsoleInput* m_pInput;

	bool m_bVisible;
};

inline extern ConsoleWidget* Console() {
	return ConsoleWidget::GetInstance();
}

class ConVar {
public:
	ConVar(QString name, int def);
	ConVar(QString name, QString def);
	ConVar(QString name, bool def);

	int GetInt() { return m_iInt; }
	QString GetString() { return m_sString; }
	int GetBool() { return m_iInt != 0; }

	void SetInt(int i);
	void SetString(QString s);
	void SetBool(bool b);

private:
	int m_iInt;
	QString m_sString;
	
};

#endif
