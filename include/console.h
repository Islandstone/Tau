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

	void Write(QString str);

	void AddCommand(ConVar* cv);
	void SendCommand(QString str);

	//QStringList GetArgs() { return m_slArgs; }

private:
	void Execute(QString command, QStringList args);

	QHash<QString, ConVar*> m_vConvars;

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

	QString GetName() { return m_sName; }

	int GetInt() { return m_varValue.toInt(); }
	QString GetString() { return m_varValue.toString(); }
	//int GetBool() { return m_iInt != 0; }
	bool GetBool();

	void SetInt(int i) { m_varValue.setValue(i); }
	void Set(QString s) { m_varValue.setValue(s); }
	void SetBool(bool b) { m_varValue.setValue(b); }

private:
	QString m_sName;
	QVariant m_varValue;
};

#endif
