#include "Log.h"

#include <QtCore/QDateTime>
#include <QtCore/QtDebug>
#include <QtCore/QFile>
#include <QtCore/QMutex>

static QFile* file = nullptr;
static char buf[1024];
static QMutex mutex;

void pwinfo(const char* format, ...)
{
	mutex.lock();
	if (!file)
	{
		file = new QFile("log.txt");
		file->open(QIODevice::WriteOnly | QIODevice::Truncate);
	}
	va_list args;
	va_start(args, format);
	sprintf(buf, "info : ");
	vsprintf(buf + strlen(buf), format, args);
	sprintf(buf + strlen(buf), " \"%s(%d)\" %s\n", __FILE__, __LINE__, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString().c_str());
	va_end(args);
	qDebug(buf);
	mutex.unlock();
}

void pwwarning(const char* format, ...)
{
	mutex.lock();
	if (!file)
	{
		file = new QFile("log.txt");
		file->open(QIODevice::WriteOnly | QIODevice::Truncate);
	}
	va_list args;
	va_start(args, format);
	sprintf(buf, "warn : ");
	vsprintf(buf + strlen(buf), format, args);
	sprintf(buf + strlen(buf), " \"%s(%d)\" %s\n", __FILE__, __LINE__, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString().c_str());
	va_end(args);
	qWarning(buf);
	mutex.unlock();
}

void pwerror(const char* format, ...)
{
	mutex.lock();
	if (!file)
	{
		file = new QFile("log.txt");
		file->open(QIODevice::WriteOnly | QIODevice::Truncate);
	}
	va_list args;
	va_start(args, format);
	sprintf(buf, "error: ");
	vsprintf(buf + strlen(buf), format, args);
	sprintf(buf + strlen(buf), " \"%s(%d)\" %s\n", __FILE__, __LINE__, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString().c_str());
	va_end(args);
	qFatal(buf);
	mutex.unlock();
}

void msgHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QTextStream textStream(file);
	textStream << msg;
	file->flush();
}
