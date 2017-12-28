#include "LoadingStatus.h"

LoadingStatus& LoadingStatus::operator=(LOADING_STATUS status)
{
    _status = status;
    if (_label)
    {
        switch (_status)
        {
        case LOADING_STATUS::LOADING_STOPPED:
            _label->setText(QApplication::translate("QTLBF", "Stopped", Q_NULLPTR));
            break;
        case LOADING_STATUS::LOADING_RUNNING:
            _label->setText(QApplication::translate("QTLBF", "Running", Q_NULLPTR));
            break;
        case LOADING_STATUS::LOADING_DONE:
            _label->setText(QApplication::translate("QTLBF", "Done", Q_NULLPTR));
            break;
        default:
            _label->setText(QApplication::translate("QTLBF", "", Q_NULLPTR));
            break;
        }
    }
    return *this;
}

bool LoadingStatus::operator==(const LOADING_STATUS& status)
{
    return _status == status;
}

bool LoadingStatus::operator!=(const LOADING_STATUS& status)
{
    return _status != status;
}
