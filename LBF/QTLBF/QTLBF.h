#pragma once
#include <lbf.h>

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include <vector>

#include "ScreenLabel.h"
#include "PaintPanel.h"
#include "LoadingStatus.h"

class QTLBF : public QMainWindow
{
    Q_OBJECT

public:
    QTLBF(QWidget *parent = Q_NULLPTR);
#pragma region UI

    /* MenuBar */
    QMenuBar *menuBar;

    QMenu *menuFile;
    QAction *actionOpen;
    QAction *actionCheat;

    /* Widget */
    QWidget *centralWidget;

    QWidget *mainScreenWidget;
    ScreenLabel *screenLabel;
    QSlider *horizontalSlider;
    QWidget *screenButtonWidget;
    QHBoxLayout *horizontalLayout;

    QSpacerItem *btnLSpacer;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QSpacerItem *btnRSpacer;

    QWidget *sideBarWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *loadButton;
    QPushButton *loadFromFileButton;
    QPushButton *unloadButton;
    QLabel *haarStatLabel;
    QLabel *alignStatLabel;
    QPushButton *processButton;
    QProgressBar *progressBar;
    QCheckBox *showPlotCheckBox;
    QPushButton *saveFaceShapeButton;
    QPushButton *saveEyeShapeButton;

    PaintPanel *paintPanel;

    /* Status */
    QStatusBar *statusBar;

#pragma endregion UI

private:
    void InitUI();
    void BindSignalSlot();
    LoadingStatus isHaarDone;
    LoadingStatus isAlignDone;

#pragma region Slots

    public slots:
#pragma region SideBarButton
    void LoadCascade();
    void LoadCascadeFromFile();
    void UnloadCascade();
    void CheatPreProcess();
    void PreProcess();
#pragma endregion SideBarButton

    void onLoadAlignThreadDone(bool isdone);
    void onUpdateProcessButton(bool canProcess);
    void onUpdateProgressBar(int value);

#pragma endregion Slots

};
