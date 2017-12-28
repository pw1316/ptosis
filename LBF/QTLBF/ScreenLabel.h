#pragma once
#include <lbf.h>

#include <QtWidgets/QLabel>

class ScreenLabel : public QLabel
{
    Q_OBJECT

public:
    ScreenLabel(QWidget* parent) :QLabel(parent) {}
    void paintEvent(QPaintEvent* event) override;

private:
    void Cleanup();
	void InnerUpdateWorkingDir(const QString& dir);

    CvCapture* capture = nullptr;
    int frameId = 0;
    cv::Mat image;
    std::vector<std::vector<double2>> shapes;
    QString workingDir = "";
    double scale = 1;
    bool isImage = false;
    bool isVideo = false;
    bool isAligned = false;
    bool showPlotShapes = false;

signals:
    void UpdateProcessButton(bool canProcess);
    void UpdateProgressBar(int value);
    void UpdateEyeData(void* shapes);
	void UpdateWorkingDir(const QString& dir);
	void UpdateOpenFile();

    public slots:
    void OpenFile();
    void SaveFaceShapes();
    void Process();
    void CheatProcess();
    void onProgressUpdate(int);
    void onAlignDone(bool isSucc);
    void onSelectFrameChanged(size_t idx);
    void onShowPlotShapesChanged(int state);
};
