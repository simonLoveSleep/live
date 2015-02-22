#ifndef TESTFFMPEG_H
#define TESTFFMPEG_H

#include <QtGui/QMainWindow>
#include "ui_testffmpeg.h"
class testffmpeg : public QMainWindow
{
	Q_OBJECT

public:
	testffmpeg(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testffmpeg();

private:
	Ui::testffmpegClass ui;
};

#endif // TESTFFMPEG_H
