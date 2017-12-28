#include "PaintPanel.h"

#include <lbf.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>

#include <vector>

#include <gl/GL.h>
#include <gl/GLU.h>

#include "Log.h"
#include "Utils.h"

PaintPanel::PaintPanel(QWidget* parent) : QOpenGLWidget(parent)
{
	setMouseTracking(true);

	coordLabel = new QLabel(this);
	coordLabel->setObjectName(QStringLiteral("coordLabel"));
	coordLabel->setGeometry(0, 0, 200, 20);

	toolWidget = new QWidget(this);
	toolWidget->setObjectName(QStringLiteral("toolWidget"));
	toolWidget->setGeometry(395, 0, 200, 20);
	toolWidget->hide();

	showLButton = new QPushButton(toolWidget);
	showLButton->setObjectName(QStringLiteral("showLButton"));
	showLButton->setGeometry(0, 0, 20, 20);
	showLButton->setText(QApplication::translate("QTLBF", "L", Q_NULLPTR));
	connect(showLButton, &QPushButton::clicked, [this] {
		this->onChangeShowEye(true, false);
	});

	showRButton = new QPushButton(toolWidget);
	showRButton->setObjectName(QStringLiteral("showRButton"));
	showRButton->setGeometry(20, 0, 20, 20);
	showRButton->setText(QApplication::translate("QTLBF", "R", Q_NULLPTR));
	connect(showRButton, &QPushButton::clicked, [this] {
		this->onChangeShowEye(false, true);
	});

	showALLButton = new QPushButton(toolWidget);
	showALLButton->setObjectName(QStringLiteral("showALLButton"));
	showALLButton->setGeometry(40, 0, 20, 20);
	showALLButton->setText(QApplication::translate("QTLBF", "A", Q_NULLPTR));
	showALLButton->setEnabled(false);
	connect(showALLButton, &QPushButton::clicked, [this] {
		this->onChangeShowEye(true, true);
	});

	dragButton = new QPushButton(toolWidget);
	dragButton->setObjectName(QStringLiteral("dragButton"));
	dragButton->setGeometry(80, 0, 40, 20);
	dragButton->setText(QApplication::translate("QTLBF", "Drag", Q_NULLPTR));
	dragButton->setEnabled(!isDrag);
	connect(dragButton, &QPushButton::clicked, [this] {
		this->dragButton->setEnabled(false);
		this->markButton->setEnabled(true);
		this->onChangeStatus(true);
	});

	markButton = new QPushButton(toolWidget);
	markButton->setObjectName(QStringLiteral("markButton"));
	markButton->setGeometry(120, 0, 40, 20);
	markButton->setText(QApplication::translate("QTLBF", "Mark", Q_NULLPTR));
	markButton->setEnabled(isDrag);
	connect(markButton, &QPushButton::clicked, [this] {
		this->dragButton->setEnabled(true);
		this->markButton->setEnabled(false);
		this->onChangeStatus(false);
	});
}

void PaintPanel::initializeGL()
{
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
}

void PaintPanel::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, -1, 5);
}

void PaintPanel::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Grid */
	glLineWidth(1);
	glColor3f(0.85f, 0.85f, 0.85f);
	glBegin(GL_LINES);
	int startX = delta - (20 * delta - dragOffset) % delta;
	while (startX < geometry().width())
	{
		glVertex3f(startX, -1, 0);
		glVertex3f(startX, 5, 0);
		startX += delta;
	}
	float startY = -0.5;
	while (startY < 5)
	{
		glVertex3f(0, startY, 0);
		glVertex3f(geometry().width(), startY, 0);
		startY += 0.5;
	}
	glEnd();

	if (lEye.size() <= 1)
	{
		return;
	}

	/* Graph */
	glLineWidth(1.5);
	if (showLeftEye) {
		glColor3f(0, 0.5, 0);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < lEye.size(); i++)
		{
			glVertex3f(1.0f * i * delta / skip + dragOffset, lEye[i], 0.1f);
		}
		glEnd();

		glPointSize(4);
		glBegin(GL_POINTS);
		for (int i = 0; i < lEye.size(); i++)
		{
			glVertex3f(1.0f * i * delta / skip + dragOffset, lEye[i], 0.1f);
		}
		glEnd();
	}
	if (showRightEye) {
		glColor3f(0, 0, 0.5);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < rEye.size(); i++)
		{
			glVertex3f(1.0f * i * delta / skip + dragOffset, rEye[i], 0.1f);
		}
		glEnd();

		glPointSize(4);
		glBegin(GL_POINTS);
		for (int i = 0; i < rEye.size(); i++)
		{
			glVertex3f(1.0f * i * delta / skip + dragOffset, rEye[i], 0.1f);
		}
		glEnd();
	}

	/* Aux */
	std::vector<double>* auxEye = selectEye ? &rEye : &lEye;
	if (!chosen)
	{
		glLineWidth(1);
		glColor3f(0.6f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, (*auxEye)[selectIdx], 0.2f);
		glVertex3f(this->geometry().width(), (*auxEye)[selectIdx], 0.2f);

		glVertex3f(1.0 * selectIdx * delta / skip + dragOffset, -1.0f, 0.2f);
		glVertex3f(1.0 * selectIdx * delta / skip + dragOffset, 5.0f, 0.2f);
		glEnd();
	}
	else
	{
		glPointSize(4);
		glColor3f(0.6f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(1.0 * selectIdx * delta / skip + dragOffset, (*auxEye)[selectIdx], 0.2f);
		glEnd();
	}

	/* Mark */
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
	glLineWidth(1.5);
	if (showLeftEye) {
		for (size_t rangeId = 0; rangeId < lMarkTable.size(); rangeId++)
		{
			glColor4f(1, 0, 0, 0.5);
			glBegin(GL_LINE_STRIP);
			for (int i = lMarkTable[rangeId].first; i < lMarkTable[rangeId].second; i++)
			{
				glVertex3f(1.0f * i * delta / skip + dragOffset, lEye[i], 0.2f);
			}
			glEnd();
			glPointSize(4);
			glBegin(GL_POINTS);
			for (int i = lMarkTable[rangeId].first; i < lMarkTable[rangeId].second; i++)
			{
				glVertex3f(1.0f * i * delta / skip + dragOffset, lEye[i], 0.2f);
			}
			glEnd();
		}
	}
	if (showRightEye) {
		for (size_t rangeId = 0; rangeId < rMarkTable.size(); rangeId++)
		{
			glColor4f(1, 0, 0, 0.5);
			glBegin(GL_LINE_STRIP);
			for (int i = rMarkTable[rangeId].first; i < rMarkTable[rangeId].second; i++)
			{
				glVertex3f(1.0f * i * delta / skip + dragOffset, rEye[i], 0.2f);
			}
			glEnd();
			glPointSize(4);
			glBegin(GL_POINTS);
			for (int i = rMarkTable[rangeId].first; i < rMarkTable[rangeId].second; i++)
			{
				glVertex3f(1.0f * i * delta / skip + dragOffset, rEye[i], 0.2f);
			}
			glEnd();
		}
	}
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}

void PaintPanel::wheelEvent(QWheelEvent * event)
{
	delta += (event->angleDelta().y() > 0) ? 1 : -1;
	if (delta > 0 && delta < 10)
	{
		if (skip == 0x40000000)
		{
			delta = 10;
		}
		else
		{
			skip *= 2;
			delta = delta * 2 + 1;
		}
	}
	else if (delta >= 20 && (delta % 2 == 0) && skip > 1)
	{
		skip /= 2;
		delta = delta / 2;
	}
	else if (delta < 0)
	{
		delta = 0x40000000;
	}
	update();
}

void PaintPanel::mouseMoveEvent(QMouseEvent * event)
{
	static QPoint lastPos = QPoint(0, 0);
	/* Raw Move */
	if (!mouseLeft && !mouseRight)
	{
		QRect bb = toolWidget->geometry();
		bool isInside = true;
		isInside = isInside && event->pos().x() >= bb.x();
		isInside = isInside && event->pos().x() <= bb.x() + bb.width();
		isInside = isInside && event->pos().y() >= bb.y();
		isInside = isInside && event->pos().y() <= bb.y() + bb.height();
		if (isInside)
		{
			toolWidget->show();
		}
		else
		{
			toolWidget->hide();
		}
		update();
		if (!chosen)
		{
			findShapeIdx(event->pos());
			if (selectIdx < lEye.size())
			{
				char buf[128];
				sprintf(buf, "%c(%d, %f)", selectEye ? 'R' : 'L', selectIdx, selectEye ? rEye[selectIdx] : lEye[selectIdx]);
				coordLabel->setText(buf);
			}
			update();
		}
	}
	/* Right Drag */
	else if (!mouseLeft && mouseRight)
	{
	}
	/* Left Drag */
	else if (mouseLeft && !mouseRight)
	{
		/* Drag Mode */
		if (isDrag)
		{
			dragOffset += (event->pos().x() - lastPos.x());
			if (dragOffset > maxDragOffset)
			{
				dragOffset = maxDragOffset;
			}
			else if (dragOffset < minDragOffset)
			{
				dragOffset = minDragOffset;
			}
			update();
		}
		/* Mark Mode */
		else
		{
			//TODO
		}
	}
	/* Both Drag */
	else
	{
	}
	lastPos = event->pos();
}

void PaintPanel::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouseLeft = true;
		leftCursor = event->pos();
	}
	else if (event->button() == Qt::RightButton)
	{
		mouseRight = true;
		rightCursor = event->pos();
	}
	else
	{
		mouseLeft = false;
		mouseRight = false;
	}
}

void PaintPanel::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		/* Left Click */
		if (mouseLeft && event->pos() == leftCursor)
		{
			findShapeIdx(event->pos());
			if (selectIdx < lEye.size())
			{
				char buf[128];
				sprintf(buf, "%c(%d, %f)", selectEye ? 'R' : 'L', selectIdx, selectEye ? rEye[selectIdx] : lEye[selectIdx]);
				coordLabel->setText(buf);
			}
			chosen = true;
			emit frameChange(selectIdx);
			update();
		}
		mouseLeft = false;
	}
	else if (event->button() == Qt::RightButton)
	{
		/* Right Click */
		if (mouseRight && event->pos() == rightCursor)
		{
			findShapeIdx(event->pos());
			chosen = false;
			if (selectIdx < lEye.size())
			{
				char buf[128];
				sprintf(buf, "%c(%d, %f)", selectEye ? 'R' : 'L', selectIdx, selectEye ? rEye[selectIdx] : lEye[selectIdx]);
				coordLabel->setText(buf);
			}
			update();
		}
		mouseRight = false;
	}
}

void PaintPanel::findShapeIdx(const QPoint & p)
{
	if (lEye.size() < 1)
	{
		selectIdx = 0;
		selectEye = 0;
		return;
	}

	int x = p.x() - dragOffset;
	selectIdx = x / (1.0f * delta / skip);
	if (selectIdx < 0)
	{
		selectIdx = 0;
	}
	else if (selectIdx >= lEye.size() - 1)
	{
		selectIdx = static_cast<int>(lEye.size() - 1);
	}
	else if (1.0 * x / delta * skip - selectIdx > selectIdx + 1 - 1.0 * x / delta * skip)
	{
		++selectIdx;
	}

	if (showLeftEye && !showRightEye)
	{
		selectEye = 0;
	}
	else if (!showLeftEye && showRightEye)
	{
		selectEye = 1;
	}
	else
	{
		int h = geometry().height();
		float y = 1.0 * (h - p.y()) / h * 6 - 1;
		float deltaL = cv::abs(lEye[selectIdx] - y);
		float deltaR = cv::abs(rEye[selectIdx] - y);
		selectEye = (deltaL < deltaR) ? 0 : 1;
	}
}

void PaintPanel::onUpdateWorkingDir(const QString& dir)
{
	workingDir = dir;
}

void PaintPanel::onUpdateOpenFile()
{
	delta = 10;
	skip = 1;
	isDrag = true;
	dragButton->setEnabled(!isDrag);
	markButton->setEnabled(isDrag);

	/* Drag */
	maxDragOffset = 20;
	dragOffset = 0;
	minDragOffset = -20;
	/* Drag */

	/* Mark */
	lMarkTable.clear();
	rMarkTable.clear();
	/* Mark */

	chosen = false;
	selectEye = 0;//0-L 1-R
	selectIdx = 0;
	lEye.clear();
	rEye.clear();
	showLeftEye = true;
	showRightEye = true;

	/* Mouse true-down false-up */
	mouseLeft = false;
	mouseRight = false;
	QPoint leftCursor;
	QPoint rightCursor;
}

void PaintPanel::SaveEyeShapes()
{
	if (!workingDir.isEmpty())
	{
		pwinfo("Saving Eye ...");
		FILE* fp;
		fopen_s(&fp, (workingDir + "EyeShape.csv").toStdString().c_str(), "w");
		for (size_t i = 0; i < lEye.size(); i++)
		{
			fprintf(fp, "%llu, %f, %f\n", i, lEye[i], rEye[i]);
		}
		fclose(fp);
	}
}

void PaintPanel::onChangeShowEye(bool l, bool r)
{
	showLeftEye = l;
	showRightEye = r;
	showLButton->setEnabled(!l || r);
	showRButton->setEnabled(l || !r);
	showALLButton->setEnabled(!l || !r);
	update();
}

void PaintPanel::onChangeStatus(bool isDrag)
{
	this->isDrag = isDrag;
	/* Save File */
	if (isDrag)
	{
		if (!workingDir.isEmpty())
		{
			FILE* fp;
			fopen_s(&fp, (workingDir + "BlinkPeriods.txt").toStdString().c_str(), "w");
			if (fp) {
				for (size_t i = 0; i < lMarkTable.size(); i++)
				{
					fprintf(fp, "%d %d %c\n", lMarkTable[i].first, lMarkTable[i].second, 'L');
				}
				for (size_t i = 0; i < lMarkTable.size(); i++)
				{
					fprintf(fp, "%d %d %c\n", rMarkTable[i].first, rMarkTable[i].second, 'R');
				}
				fclose(fp);
			}
		}
	}
	/* Load File */
	else
	{
		if (!workingDir.isEmpty())
		{
			FILE* fp;
			fopen_s(&fp, (workingDir + "BlinkPeriods.txt").toStdString().c_str(), "r");
			int a, b;
			char LR;
			if (fp) {
				lMarkTable.clear();
				rMarkTable.clear();
				while (fscanf(fp, "%d %d %c", &a, &b, &LR) > 0)
				{
					if (LR == 'L')
					{
						lMarkTable.emplace_back(a, b);
					}
					else
					{
						rMarkTable.emplace_back(a, b);
					}
				}
				fclose(fp);
			}
		}
	}
}

void PaintPanel::onUpdateEyeData(void* shapes)
{
	std::vector<std::vector<double2>>* shps = reinterpret_cast<std::vector<std::vector<double2>>*>(shapes);
	lbf::getEyeDataFromShapes(*shps, lEye, rEye);
	int right = (lEye.size() <= 1) ? geometry().width() : delta * static_cast<int>(lEye.size() - 1);
	if (right > geometry().width())
	{
		minDragOffset = geometry().width() - right - 20;
	}
	else
	{
		minDragOffset = -20;
	}
	if (lEye.size() > 1)
	{
		float fakeDelta = 1.0 * geometry().width() / (lEye.size() - 1);
		skip = 1;
		while (fakeDelta < 10)
		{
			fakeDelta *= 2;
			skip *= 2;
		}
		delta = fakeDelta;
	}
	findShapeIdx(QPoint(0, 0));
	update();
}
