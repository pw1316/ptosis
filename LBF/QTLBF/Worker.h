#pragma once
#include <lbf.h>

#include <QtCore/QObject>
#include <QtCore/QString>

class LoadAlignWorker : public QObject
{
    Q_OBJECT

public:
    LoadAlignWorker(const QString& _filename = "") :QObject(), filename(_filename) {}

private:
    QString filename;

signals:
    void Done(bool _isdone);

    public slots:
    void Run();
};

class AlignWorker : public QObject
{
    Q_OBJECT

public:
    AlignWorker(CvCapture* capture, std::vector<std::vector<double2>>* phapes, double* pscale);

private:
    int progressValue;
    CvCapture* capture;
    std::vector<std::vector<double2>>* pshapes;
    double* pscale;

signals:
    void Done(bool isSucc);
    void UpdateProgress(int value);

    public slots:
    void Run();
};