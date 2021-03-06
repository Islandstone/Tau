#include "console.h"

ConsoleInput::ConsoleInput(QWidget* parent) : QTextEdit(parent) {

}

void ConsoleInput::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		Console()->SendCommand(toPlainText().trimmed());
		setText("");
		event->ignore();
	}
	else if (event->key() == Qt::Key_PageUp) {
		event->ignore();
	}
	else if (event->key() == Qt::Key_Up) {
		qDebug() << "Key up";
	}
	else if (event->key() == Qt::Key_Down) {
		qDebug() << "Key down";
	}
	else if (event->key() == Qt::Key_Tab) {
		return;
	}
	else {
		QTextEdit::keyPressEvent(event);
	}
}

ConsoleText::ConsoleText(QWidget* parent) : QTextEdit(parent) {
	setReadOnly(true);
}

void ConsoleText::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
		event->ignore();
	}
	else if (event->key() == Qt::Key_PageUp) {
		event->ignore();
	}
	else {
		QTextEdit::keyPressEvent(event);
	}
}

ConsoleWidget::ConsoleWidget() {
	
}

void ConsoleWidget::InitWidgets(QWidget* parent) {
	m_pWidget = new QWidget();
	m_pWidget->setParent(parent);

	m_pText = new ConsoleText();
	m_pInput = new ConsoleInput();
	m_pInput->setFixedHeight(25); // HACKHACK

	m_pLayout = new QVBoxLayout(m_pWidget);
	m_pLayout->addWidget(m_pText);
	m_pLayout->addWidget(m_pInput);

	// Set scrollbar policy
	m_pText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_pInput->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	m_pWidget->hide();
	/*
	m_pWidget->show();
	m_pText->show();
	m_pInput->show();
	*/

	int width = 0.7f * parent->width();
	int height = 0.7f * parent->height();

	m_pWidget->resize(width, height);
	m_pText->resize(100, 100);
	m_pInput->resize(100, 10);
	m_pInput->move(0, 100);

	m_pWidget->move((0.5f * parent->width()) - (0.5f * width), (0.5f * parent->height()) - (0.5f * height) );

	m_bVisible = false;
}

void ConsoleWidget::Toggle() {
	if (m_bVisible) {
		Hide();
	} else {
		Show();
	}
}

void ConsoleWidget::Show() {
	m_pWidget->show();
	m_pInput->setFocus();
	m_bVisible = true;
}

void ConsoleWidget::Hide() {
	m_pWidget->hide();
	m_bVisible = false;
}

void ConsoleWidget::Write(QString str) {
	m_pText->append(str);
}

//#define DEBUG_COMMAND_SPLIT
void ConsoleWidget::SendCommand(QString str) {
	Write("] " + str);

	QRegExp rx("([^ ]+|\"[^\"]+\")");
	QString tmp;
	QString command;
	QStringList args;

	int pos = 0;
	while ((pos = rx.indexIn(str, pos)) != -1) {
		tmp = rx.cap(1);

		if (tmp.startsWith('\"') && tmp.endsWith('\"')) {
			tmp = tmp.mid(1, tmp.size()-2);
		}

		if (pos == 0) {
			command = tmp;
		} else {
			args << tmp;
		}
		
		pos += rx.matchedLength();
	}

#ifndef DEBUG_COMMAND_SPLIT
	Execute(command, args);
#else
	Write("String split into the following parts:");

	Write("] " << command);
	for (int i = 0; i < args.size(); i++) {
		Write(args[i]);
	}
	Write("------------------------------END------------------------------");
#endif
}

void ConsoleWidget::Execute(QString command, QStringList args) {
	//m_slArgs = args;

	if (!m_vConvars.contains(command)) {
		Write("No such command: " + command );
		return;
	}

	ConVar* var = m_vConvars.value(command);

	if (args.isEmpty()) {
		Write(command + " " + var->GetString());
		return;
	} else {
		var->Set(args[0]);
	}
}

void ConsoleWidget::AddCommand(ConVar* cv) {
	m_vConvars.insert(cv->GetName(), cv);
}

ConVar::ConVar(QString name, bool def) {
	m_sName = name;
	m_varValue.setValue(def);
	Console()->AddCommand(this);
}

bool ConVar::GetBool() {
	return m_varValue.toBool();
}
