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
        auto result = core->mat2QImage(processed);
        auto scene = new QGraphicsScene(this);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(result));
        ui->sourceImageDisplay->setScene(scene);
        ui->sourceImageTitle->setText("selected: " + selectedFile);
    }
}

void AppWindow::clearSelectionSlot()
{
    auto currentScene = ui->sourceImageDisplay->scene();
    if (currentScene != nullptr)
    {
        currentScene->clear();
    }
    ui->sourceImageTitle->setText(QString::fromStdString(""));
}


