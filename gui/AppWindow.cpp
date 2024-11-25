//
// Created by Dekki on 24-11-15.
//

#include <QtWidgets/QFileDialog>

#include "AppWindow.h"

AppWindow::AppWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    core = new Core();
    ui->setupUi(this);
    connect(ui->selectImage, &QPushButton::clicked, this, &AppWindow::selectImageSlot);
    connect(ui->clearSelection, &QPushButton::clicked, this, &AppWindow::clearSelectionSlot);
}

AppWindow::~AppWindow()
{
    delete ui;
    delete core;
}

void AppWindow::selectImageSlot()
{
    QString selectedFile = QFileDialog::getOpenFileName(
        this,
        tr("Select an image..."),
        "C:/",
        "Image(*.png *.jpeg *.jpg *.bmp)");
    if (!selectedFile.isEmpty())
    {
        auto selectedImage = core->readImage(selectedFile.toLocal8Bit().data());
        auto processed = core->process();
        results = processed;
        auto result = core->mat2QImage(processed[0]);
        auto scene = new QGraphicsScene(this);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(result));
        ui->sourceImageDisplay->setScene(scene);
        // ui->sourceImageTitle->setText("selected: " + selectedFile + " width " + QString::number(results[0].cols));
    }
}

void AppWindow::clearSelectionSlot()
{
    // auto currentScene = ui->sourceImageDisplay->scene();
    // if (currentScene != nullptr)
    // {
    //     currentScene->clear();
    // }
    // ui->sourceImageTitle->setText(QString::fromStdString(""));
    // TODO: tiaoshi, jideshan
    if (current == results.size() - 1)
    {
        current = -1;
    }
    current++;
    ui->sourceImageDisplay->scene()->clear();
    ui->sourceImageDisplay->scene()->addPixmap(QPixmap::fromImage(core->mat2QImage(results[current])));
    ui->sourceImageTitle->setText("width " + QString::number(results[current].cols));
}


