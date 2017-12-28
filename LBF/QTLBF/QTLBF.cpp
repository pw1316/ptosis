#include "QTLBF.h"

#include <lbf.h>

#include <QtCore/QTextStream>
#include <QTCore/QThread>
#include <QtWidgets/QFileDialog>

#include "Log.h"
#include "Worker.h"
#include "Utils.h"

QTLBF::QTLBF(QWidget *parent) : QMainWindow(parent)
{
    InitUI();
    BindSignalSlot();
    isHaarDone = LoadingStatus(haarStatLabel);
    isAlignDone = LoadingStatus(alignStatLabel);
    isHaarDone = LOADING_STATUS::LOADING_STOPPED;
    isAlignDone = LOADING_STATUS::LOADING_STOPPED;
}

void QTLBF::InitUI()
{
    /* Main Window */
#pragma region MainWindow

    if (this->objectName().isEmpty())
    {
        this->setObjectName(QStringLiteral("QTLBF"));
    }
    this->setWindowTitle(QApplication::translate("QTLBF", "QTLBF", Q_NULLPTR));
    this->resize(1030, 768);
    this->setMinimumSize(QSize(1030, 768));
    this->setMaximumSize(QSize(1030, 768));

#pragma endregion MainWindow

    /* Menu Bar */
#pragma region MenuBar

    menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 1030, 23));

    /* Menu->File */
#pragma region File

    menuFile = new QMenu(menuBar);
    menuFile->setTitle(QApplication::translate("QTLBF", "&File", Q_NULLPTR));
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuBar->addAction(menuFile->menuAction());

    /* Menu->File->Open */
    actionOpen = new QAction(this);
    actionOpen->setObjectName(QStringLiteral("actionOpen"));
    actionOpen->setText(QApplication::translate("QTLBF", "Open", Q_NULLPTR));
    actionOpen->setShortcut(QApplication::translate("QTLBF", "Ctrl+O", Q_NULLPTR));
    menuFile->addAction(actionOpen);

    /* Menu->File->Cheat */
    actionCheat = new QAction(this);
    actionCheat->setObjectName(QStringLiteral("actionCheat"));
    actionCheat->setText(QApplication::translate("QTLBF", "Cheat", Q_NULLPTR));
    actionCheat->setShortcut(QApplication::translate("QTLBF", "Ctrl+D", Q_NULLPTR));
    actionCheat->setEnabled(false);
    menuFile->addAction(actionCheat);

#pragma endregion File

#pragma endregion MenuBar

    /* Central Widget */
#pragma region CentralWidget

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    this->setCentralWidget(centralWidget);

#pragma region MainScreen

    mainScreenWidget = new QWidget(centralWidget);
    mainScreenWidget->setObjectName(QStringLiteral("mainScreenWidget"));
    mainScreenWidget->setGeometry(QRect(20, 20, 800, 495));

    /* Screen */
    screenLabel = new ScreenLabel(mainScreenWidget);
    screenLabel->setObjectName(QStringLiteral("screenLabel"));
    screenLabel->setGeometry(QRect(0, 0, 800, 450));
    screenLabel->setPixmap(QPixmap(QString::fromUtf8(":/QTLBF/Resources/defaultImg.png")));
    screenLabel->setAlignment(Qt::AlignCenter);

    /* Slider */
    horizontalSlider = new QSlider(mainScreenWidget);
    horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
    horizontalSlider->setEnabled(false);
    horizontalSlider->setGeometry(QRect(0, 450, 800, 20));
    horizontalSlider->setMaximum(2000);
    horizontalSlider->setOrientation(Qt::Horizontal);

    /* Screen Buttons */
#pragma region ScreenButton

    screenButtonWidget = new QWidget(mainScreenWidget);
    screenButtonWidget->setObjectName(QStringLiteral("screenButtonWidget"));
    screenButtonWidget->setGeometry(QRect(0, 470, 800, 25));
    horizontalLayout = new QHBoxLayout(screenButtonWidget);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    /* LSpacer */
    btnLSpacer = new QSpacerItem(0, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(btnLSpacer);

    /* Play */
    playButton = new QPushButton(screenButtonWidget);
    playButton->setObjectName(QStringLiteral("playButton"));
    playButton->setEnabled(false);
    QIcon iconPlayButton;
    iconPlayButton.addFile(QStringLiteral(":/QTLBF/Resources/icons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
    playButton->setIcon(iconPlayButton);
    horizontalLayout->addWidget(playButton);

    /* Pause */
    pauseButton = new QPushButton(screenButtonWidget);
    pauseButton->setObjectName(QStringLiteral("pauseButton"));
    pauseButton->setEnabled(false);
    QIcon iconPauseButton;
    iconPauseButton.addFile(QStringLiteral(":/QTLBF/Resources/icons/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
    pauseButton->setIcon(iconPauseButton);
    horizontalLayout->addWidget(pauseButton);

    /* Stop */
    stopButton = new QPushButton(screenButtonWidget);
    stopButton->setObjectName(QStringLiteral("stopButton"));
    stopButton->setEnabled(false);
    QIcon iconStopButton;
    iconStopButton.addFile(QStringLiteral(":/QTLBF/Resources/icons/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
    stopButton->setIcon(iconStopButton);
    horizontalLayout->addWidget(stopButton);

    /* RSpacer */
    btnRSpacer = new QSpacerItem(0, 25, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(btnRSpacer);

#pragma endregion ScreenButton

#pragma endregion MainScreen

#pragma region SideBar

    sideBarWidget = new QWidget(centralWidget);
    sideBarWidget->setObjectName(QStringLiteral("sideBarWidget"));
    sideBarWidget->setGeometry(QRect(830, 20, 180, 495));
    verticalLayout = new QVBoxLayout(sideBarWidget);
    verticalLayout->setSpacing(0);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    loadButton = new QPushButton(sideBarWidget);
    loadButton->setObjectName(QStringLiteral("loadButton"));
    loadButton->setText(QApplication::translate("QTLBF", "Load", Q_NULLPTR));
    verticalLayout->addWidget(loadButton);

    loadFromFileButton = new QPushButton(sideBarWidget);
    loadFromFileButton->setObjectName(QStringLiteral("loadFromFileButton"));
    loadFromFileButton->setText(QApplication::translate("QTLBF", "Load From File", Q_NULLPTR));
    verticalLayout->addWidget(loadFromFileButton);

    unloadButton = new QPushButton(sideBarWidget);
    unloadButton->setObjectName(QStringLiteral("unloadButton"));
    unloadButton->setText(QApplication::translate("QTLBF", "Unload", Q_NULLPTR));
    unloadButton->setEnabled(false);
    verticalLayout->addWidget(unloadButton);

    processButton = new QPushButton(sideBarWidget);
    processButton->setObjectName(QStringLiteral("processButton"));
    processButton->setEnabled(false);
    processButton->setText(QApplication::translate("QTLBF", "Process", Q_NULLPTR));
    verticalLayout->addWidget(processButton);

    progressBar = new QProgressBar(sideBarWidget);
    progressBar->setObjectName(QStringLiteral("progressBar"));
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setValue(0);
    verticalLayout->addWidget(progressBar);

    showPlotCheckBox = new QCheckBox(sideBarWidget);
    showPlotCheckBox->setObjectName(QStringLiteral("showPlotCheckBox"));
    showPlotCheckBox->setText(QApplication::translate("QTLBF", "Show Plot Shapes", Q_NULLPTR));
    verticalLayout->addWidget(showPlotCheckBox);

    saveFaceShapeButton = new QPushButton(sideBarWidget);
    saveFaceShapeButton->setObjectName(QStringLiteral("saveFaceShapeButton"));
    saveFaceShapeButton->setText(QApplication::translate("QTLBF", "Save Face Shapes", Q_NULLPTR));
    verticalLayout->addWidget(saveFaceShapeButton);

    saveEyeShapeButton = new QPushButton(sideBarWidget);
    saveEyeShapeButton->setObjectName(QStringLiteral("saveEyeShapeButton"));
    saveEyeShapeButton->setText(QApplication::translate("QTLBF", "Save Eye Shapes", Q_NULLPTR));
    verticalLayout->addWidget(saveEyeShapeButton);

    haarStatLabel = new QLabel(sideBarWidget);
    haarStatLabel->setObjectName(QStringLiteral("haarStatLabel"));
    verticalLayout->addWidget(haarStatLabel);

    alignStatLabel = new QLabel(sideBarWidget);
    alignStatLabel->setObjectName(QStringLiteral("alignStatLabel"));
    verticalLayout->addWidget(alignStatLabel);

#pragma endregion SideBar

#pragma region PaintPanel

    paintPanel = new PaintPanel(centralWidget);
    paintPanel->setObjectName(QStringLiteral("paintPanel"));
    paintPanel->setGeometry(QRect(20, 520, 990, 200));

#pragma endregion PaintPanel


#pragma endregion CentralWidget

    /* Status Bar */
#pragma region StatusBar

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);

#pragma endregion StatusBar
}

void QTLBF::BindSignalSlot()
{
    connect(actionOpen, &QAction::triggered, screenLabel, &ScreenLabel::OpenFile);
    connect(actionCheat, &QAction::triggered, this, &QTLBF::CheatPreProcess);

    connect(screenLabel, &ScreenLabel::UpdateProcessButton, this, &QTLBF::onUpdateProcessButton);
    connect(screenLabel, &ScreenLabel::UpdateProgressBar, this, &QTLBF::onUpdateProgressBar);

    connect(loadButton, &QPushButton::clicked, this, &QTLBF::LoadCascade);
    connect(loadFromFileButton, &QPushButton::clicked, this, &QTLBF::LoadCascadeFromFile);
    connect(unloadButton, &QPushButton::clicked, this, &QTLBF::UnloadCascade);

    connect(processButton, &QPushButton::clicked, this, &QTLBF::PreProcess);
    connect(saveFaceShapeButton, &QPushButton::clicked, [this] {
        this->screenLabel->SaveFaceShapes();
    });
    connect(saveEyeShapeButton, &QPushButton::clicked, [this] {
        this->paintPanel->SaveEyeShapes();
    });
    connect(showPlotCheckBox, &QCheckBox::stateChanged, screenLabel, &ScreenLabel::onShowPlotShapesChanged);
    connect(paintPanel, &PaintPanel::frameChange, screenLabel, &ScreenLabel::onSelectFrameChanged);
    connect(screenLabel, &ScreenLabel::UpdateEyeData, paintPanel, &PaintPanel::onUpdateEyeData);
    connect(screenLabel, &ScreenLabel::UpdateWorkingDir, paintPanel, &PaintPanel::onUpdateWorkingDir);
    connect(screenLabel, &ScreenLabel::UpdateOpenFile, paintPanel, &PaintPanel::onUpdateOpenFile);
}

void QTLBF::LoadCascade()
{
    pwinfo("Loading by Default");
    bool ret = lbf::loadHaarCascade();
    isHaarDone = ret ? LOADING_STATUS::LOADING_DONE : LOADING_STATUS::LOADING_STOPPED;
    if (!ret)
    {
        pwinfo("Loading Haar ... FAIL");
        statusBar->showMessage("Loading haar failed");
        return;
    }
    pwinfo("Loading Haar ... SUCC");

    if (isAlignDone != LOADING_STATUS::LOADING_RUNNING)
    {
        pwinfo("Start Async Loading Align ...");
        isAlignDone = LOADING_STATUS::LOADING_RUNNING;
        QThread* subThread = new QThread();
        LoadAlignWorker* worker = new LoadAlignWorker();
        worker->moveToThread(subThread);
        connect(subThread, &QThread::started, worker, &LoadAlignWorker::Run);
        connect(worker, &LoadAlignWorker::Done, this, &QTLBF::onLoadAlignThreadDone);
        connect(worker, &LoadAlignWorker::Done, subThread, &QThread::quit);
        connect(worker, &LoadAlignWorker::Done, worker, &LoadAlignWorker::deleteLater);
        connect(subThread, &QThread::finished, subThread, &QThread::deleteLater);
        subThread->start();

        loadButton->setEnabled(false);
        loadFromFileButton->setEnabled(false);
        unloadButton->setEnabled(false);
    }
}

void QTLBF::LoadCascadeFromFile()
{
    pwinfo("Loading from File");
    QString filename;
    /* Haar */
    filename = QFileDialog::getOpenFileName(this, tr("Loading Haar"), QString(), tr("Frontal Face XML File (haarcascade_frontalface_*.xml)"));
    if (filename.isEmpty()) return;

    bool ret = lbf::loadHaarCascade(filename.toStdString());
    isHaarDone = ret ? LOADING_STATUS::LOADING_DONE : LOADING_STATUS::LOADING_STOPPED;
    if (!ret)
    {
        pwinfo("Loading Haar ... FAIL");
        statusBar->showMessage("Loading haar failed");
        return;
    }
    pwinfo("Loading Haar ... SUCC");

    /* Align */
    filename = QFileDialog::getOpenFileName(this, tr("Loading Align"), QString(), tr("LBF Model (model_loose.bin)"));
    if (!filename.isEmpty() && isAlignDone != LOADING_STATUS::LOADING_RUNNING)
    {
        pwinfo("Start Async Loading Align ...");
        isAlignDone = LOADING_STATUS::LOADING_RUNNING;
        QThread* subThread = new QThread();
        LoadAlignWorker* worker = new LoadAlignWorker(filename);
        worker->moveToThread(subThread);
        connect(subThread, &QThread::started, worker, &LoadAlignWorker::Run);
        connect(worker, &LoadAlignWorker::Done, this, &QTLBF::onLoadAlignThreadDone);
        connect(worker, &LoadAlignWorker::Done, subThread, &QThread::quit);
        connect(worker, &LoadAlignWorker::Done, worker, &LoadAlignWorker::deleteLater);
        connect(subThread, &QThread::finished, subThread, &QThread::deleteLater);
        subThread->start();

        loadButton->setEnabled(false);
        loadFromFileButton->setEnabled(false);
        unloadButton->setEnabled(false);
    }
}

void QTLBF::UnloadCascade()
{
    pwinfo("Unloading");
    lbf::unloadHaarCascade();
    lbf::unloadAlignCascade();
    isHaarDone = LOADING_STATUS::LOADING_STOPPED;
    isAlignDone = LOADING_STATUS::LOADING_STOPPED;

    loadButton->setEnabled(true);
    loadFromFileButton->setEnabled(true);
    unloadButton->setEnabled(false);
}

void QTLBF::CheatPreProcess()
{
    onUpdateProcessButton(false);
    screenLabel->CheatProcess();
}

void QTLBF::PreProcess()
{
    /* Cascades must be loaded */
    if (loadButton->isEnabled())
    {
        pwwarning("Can't Process Without Loading Cascades!");
        statusBar->showMessage("Should load Cascades first");
        return;
    }
    onUpdateProcessButton(false);
    screenLabel->Process();
}

void QTLBF::onLoadAlignThreadDone(bool isdone)
{
    if (isdone)
    {
        pwinfo("Loading Align ... SUCC");
        isAlignDone = LOADING_STATUS::LOADING_DONE;

        loadButton->setEnabled(false);
        loadFromFileButton->setEnabled(false);
        unloadButton->setEnabled(true);
    }
    else
    {
        pwinfo("Loading Align ... FAIL");
        isAlignDone = LOADING_STATUS::LOADING_STOPPED;
        statusBar->showMessage("Loading align failed");

        loadButton->setEnabled(true);
        loadFromFileButton->setEnabled(true);
        unloadButton->setEnabled(false);
    }
}

void QTLBF::onUpdateProcessButton(bool canProcess)
{
    processButton->setEnabled(canProcess);
    actionCheat->setEnabled(canProcess);
}

void QTLBF::onUpdateProgressBar(int value)
{
    progressBar->setValue(value);
}
