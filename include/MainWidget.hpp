//
// Created by roundedglint585 on 6/11/19.
//

#ifndef KNITTINGPATHFINDER_MAINWIDGET_HPP
#define KNITTINGPATHFINDER_MAINWIDGET_HPP


#include <memory>
#include <iostream>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QMessageBox>
#include "PathFinder.hpp"
#include "RenderArea.hpp"

class MainWidget : public QWidget {
Q_OBJECT
public:
    MainWidget();

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

private slots:

    void calculatePath();

    void resetAll();

    void renderUntilSelectedElement();


private:
    std::unique_ptr<RenderArea> renderArea_;
    std::unique_ptr<QPushButton> calculateButton_;
    std::unique_ptr<QPushButton> resetButton_;
    std::unique_ptr<QListWidget> pathList_;
    std::unique_ptr<QGridLayout> mainLayout_;
};


#endif //KNITTINGPATHFINDER_MAINWIDGET_HPP
