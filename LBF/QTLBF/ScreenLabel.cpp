#include "ScreenLabel.h"

#include <lbf.h>

#include <QtCore/QThread>
#include <QtGui/QPainter>
#include <QtWidgets/QFileDialog>

#include <fstream>
#include <string>
#include <vector>

#include "Log.h"
#include "Worker.h"
#include "Utils.h"

void ScreenLabel::paintEvent(QPaintEvent* event)
{
	QLabel::paintEvent(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(QColor(255, 0, 0), 2));

	if (!isAligned || !showPlotShapes)
	{
		return;
	}

	int2 offset;
	offset.x = (width() - image.cols) / 2;
	offset.y = (height() - image.rows) / 2;
	assert(isImage || isVideo);
	int idx = isImage ? 0 : frameId;
	assert(shapes.size() > idx);
	for (size_t i = 0; i < shapes[idx].size(); i++)
	{
		painter.drawEllipse(QPointF(shapes[idx][i].x + offset.x, shapes[idx][i].y + offset.y), 1, 1);
	}
}

void ScreenLabel::Cleanup()
{
	pwinfo("Cleaning Up ...");
	cvReleaseCapture(&capture);
	frameId = 0;
	image.release();
	shapes.clear();
	InnerUpdateWorkingDir("");
	scale = 1;
	isImage = false;
	isVideo = false;
	isAligned = false;
	showPlotShapes = false;
}

void ScreenLabel::InnerUpdateWorkingDir(const QString & dir)
{
	workingDir = dir;
	emit UpdateWorkingDir(dir);
}

void ScreenLabel::OpenFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), QString(), tr("PNG, MPEG4 (*.png *.mp4 *.mov)"));
	pwinfo("Opened file: [%s]", filename.toStdString().c_str());

	if (!filename.isEmpty())
	{
		Cleanup();
		InnerUpdateWorkingDir(filename.left(filename.lastIndexOf('/') + 1));
		/* Images */
		if (filename.endsWith(".png"))
		{
			image = cv::imread(filename.toStdString());
			if (image.rows == 0)
			{
				pwinfo("Open Image ... FAIL");
				return;
			}
			QRect rect = geometry();

			/* Scale Image */
			double xScale = 1.0 * rect.width() / image.cols;
			double yScale = 1.0 * rect.height() / image.rows;
			scale = cv::min(xScale, yScale);
			if (scale < 1) {
				cv::resize(image, image, cv::Size(), scale, scale, CV_INTER_AREA);
			}
			else {
				cv::resize(image, image, cv::Size(), scale, scale, CV_INTER_LINEAR);
			}
			scale = 1;
			/* Scale Image */
			QImage qimage = cvMat2QImage(image);
			setPixmap(QPixmap::fromImage(qimage));
			isImage = true;
			isVideo = false;

			emit UpdateProgressBar(0);
			emit UpdateProcessButton(true);
			emit UpdateOpenFile();
			update();
			pwinfo("Open Image ... SUCC");
		}
		/* Videos */
		else
		{
			capture = cvCreateFileCapture(filename.toStdString().c_str());
			IplImage* iplImg = cvQueryFrame(capture);
			cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, 0);
			frameId = 0;
			image = cv::cvarrToMat(iplImg);
			if (image.empty())
			{
				pwinfo("Open Video ... FAIL");
				Cleanup();
				return;
			}
			if (iplImg->origin != IPL_ORIGIN_TL)
				flip(image, image, 0);

			QRect rect = geometry();
			double xScale = 1.0 * rect.width() / image.cols;
			double yScale = 1.0 * rect.height() / image.rows;
			scale = cv::min(xScale, yScale);

			if (scale < 1) {
				cv::resize(image, image, cv::Size(), scale, scale, CV_INTER_AREA);
			}
			else {
				cv::resize(image, image, cv::Size(), scale, scale, CV_INTER_LINEAR);
			}
			QImage qimage = cvMat2QImage(image);
			setPixmap(QPixmap::fromImage(qimage));
			isImage = false;
			isVideo = true;

			emit UpdateProgressBar(0);
			emit UpdateProcessButton(true);
			emit UpdateOpenFile();
			update();
		}
		pwinfo("Open Video ... SUCC");
	}
}

void ScreenLabel::SaveFaceShapes()
{
	if (!workingDir.isEmpty())
	{
		pwinfo("Saving Face ...");
		FILE* fp;
		fopen_s(&fp, (workingDir + "FaceShape.csv").toStdString().c_str(), "w");
		for (size_t i = 0; i < shapes.size(); i++)
		{
			fprintf(fp, "F\n");
			for (size_t j = 0; j < shapes[i].size(); j++)
			{
				fprintf(fp, "%f, %f\n", shapes[i][j].x, shapes[i][j].y);
			}
		}
		fclose(fp);
	}
}

void ScreenLabel::Process()
{
	if (isImage)
	{
		pwinfo("Processing Image ...");
		shapes.clear();
		shapes.push_back(std::vector<double2>());
		int ret = lbf::alignImage(image, shapes[0]);
		isAligned = (ret == 0) ? true : false;
		emit UpdateProcessButton(!isAligned);
		update();
	}
	else if (isVideo)
	{
		pwinfo("Processing Async Video ...");
		QThread* subThread = new QThread();
		AlignWorker* worker = new AlignWorker(capture, &shapes, &scale);
		worker->moveToThread(subThread);
		connect(subThread, &QThread::started, worker, &AlignWorker::Run);
		connect(worker, &AlignWorker::UpdateProgress, this, &ScreenLabel::onProgressUpdate);
		connect(worker, &AlignWorker::Done, this, &ScreenLabel::onAlignDone);
		connect(worker, &AlignWorker::Done, subThread, &QThread::quit);
		connect(worker, &AlignWorker::Done, worker, &AlignWorker::deleteLater);
		connect(subThread, &QThread::finished, subThread, &QThread::deleteLater);
		subThread->start();
	}
}

void ScreenLabel::CheatProcess()
{
	if (isImage)
	{
		pwwarning("Image Cannot Cheat");
	}
	else if (isVideo)
	{
		pwinfo("Cheating Video ...");
		shapes.clear();
		if (!workingDir.isEmpty())
		{
			std::ifstream iFile((workingDir + "FaceShape.csv").toStdString());
			if (!iFile.is_open())
			{
				onAlignDone(false);
				return;
			}
			std::string line;
			while (std::getline(iFile, line))
			{
				if (line == "F")
				{
					shapes.push_back(std::vector<double2>());
				}
				else
				{
					double x, y;
					sscanf(line.c_str(), "%lf, %lf", &x, &y);
					shapes[shapes.size() - 1].push_back(double2(x, y));
				}
			}
			iFile.close();
			onAlignDone(true);
			return;
		}
		onAlignDone(false);
	}
}

void ScreenLabel::onProgressUpdate(int value)
{
	emit UpdateProgressBar(value);
}

void ScreenLabel::onAlignDone(bool isSucc)
{
	isAligned = isSucc;
	emit UpdateProcessButton(!isSucc);
	update();
	emit UpdateEyeData(&shapes);
}

void ScreenLabel::onSelectFrameChanged(size_t idx)
{
	frameId = static_cast<int>(idx);
	cvSetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES, frameId);
	IplImage* iplImg = cvQueryFrame(capture);
	image = cv::cvarrToMat(iplImg);
	/* No such frame */
	if (image.empty())
		return;
	if (iplImg->origin != IPL_ORIGIN_TL)
		flip(image, image, 0);
	if (scale < 1) {
		cv::resize(image, image, cv::Size(), scale, scale, CV_INTER_AREA);
	}
	else {
		cv::resize(image, image, cv::Size(), scale, scale, CV_INTER_LINEAR);
	}
	QImage qimage = cvMat2QImage(image);
	setPixmap(QPixmap::fromImage(qimage));
	update();
}

void ScreenLabel::onShowPlotShapesChanged(int state)
{
	showPlotShapes = state;
	update();
}
