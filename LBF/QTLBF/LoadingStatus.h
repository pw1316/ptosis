#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

using LOADING_STATUS = enum
{
    LOADING_STOPPED = 0,
    LOADING_RUNNING = 1,
    LOADING_DONE = 2,
};
class LoadingStatus
{
public:
    LoadingStatus(QLabel* label = nullptr) :_label(label), _status(LOADING_STATUS::LOADING_STOPPED) {}
    LoadingStatus& operator=(LOADING_STATUS status);
    bool operator==(const LOADING_STATUS& status);
    bool operator!=(const LOADING_STATUS& status);
    
private:
    LOADING_STATUS _status;
    QLabel* _label;
};
