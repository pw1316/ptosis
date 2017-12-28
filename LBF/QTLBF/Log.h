#pragma once
#include <QString>

#include <stdarg.h>

void pwinfo(const char* format, ...);
void pwwarning(const char* format, ...);
void pwerror(const char* format, ...);

void msgHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
