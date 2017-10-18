#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new graphscene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(this->frameGeometry());
    ui->graphicsView->verticalScrollBar()->blockSignals(true);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->horizontalScrollBar()->blockSignals(true);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->addLine(675,0,675,700,QPen());
}

MainWindow::~MainWindow()
{
    delete ui;
}
