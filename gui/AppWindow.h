//
// Created by Dekki on 24-11-15.
//

#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <gui.h>

#include "core.h"

class AppWindow : public QMainWindow
{
    Q_OBJECT
public:
    AppWindow(QWidget* parent = nullptr);
    ~AppWindow();
private:
    void selectImageSlot();
    void clearSelectionSlot();
    Core* core = nullptr;
    Ui::MainWindow* ui = nullptr;
    int current;
    std::vector<cv::Mat> results;
};

#endif //APPWINDOW_H
