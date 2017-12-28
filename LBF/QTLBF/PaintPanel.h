#pragma once
#include <lbf.h>

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QLabel>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include <vector>

class PaintPanel : public QOpenGLWidget
{
    Q_OBJECT

public:
    PaintPanel(QWidget* parent);
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    /* Text Label(Coordinates) */
    QLabel* coordLabel = Q_NULLPTR;
    /* Floating toolbar */
    QWidget* toolWidget = Q_NULLPTR;
    QPushButton* showLButton = Q_NULLPTR;
    QPushButton* showRButton = Q_NULLPTR;
    QPushButton* showALLButton = Q_NULLPTR;
	QPushButton* dragButton = Q_NULLPTR;
	QPushButton* markButton = Q_NULLPTR;
private:
	QString workingDir = "";

    void findShapeIdx(const QPoint& p);
    int delta = 10;
    int skip = 1;

	bool isDrag = true;

    /* Drag */
    int maxDragOffset = 20;
    int dragOffset = 0;
    int minDragOffset = -20;
    /* Drag */

	/* Mark */
	std::vector<std::pair<int, int>> lMarkTable;
	std::vector<std::pair<int, int>> rMarkTable;
	/* Mark */

    bool chosen = false;
    int selectEye = 0;//0-L 1-R
    int selectIdx = 0;
    std::vector<double> lEye;
    std::vector<double> rEye;
    bool showLeftEye = true;
    bool showRightEye = true;

    /* Mouse true-down false-up */
    bool mouseLeft = false;
    bool mouseRight = false;
    QPoint leftCursor;
    QPoint rightCursor;

signals:
    void frameChange(size_t idx);

    public slots:
    void onUpdateEyeData(void* shapes);
	void onUpdateWorkingDir(const QString& dir);
	void onUpdateOpenFile();
    void SaveEyeShapes();
    void onChangeShowEye(bool l, bool r);
	void onChangeStatus(bool isDrag);
};
