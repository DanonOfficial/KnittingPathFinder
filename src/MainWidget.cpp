//
// Created by roundedglint585 on 6/11/19.
//

#include "../include/MainWidget.hpp"

MainWidget::MainWidget() : renderArea_(new RenderArea(this, 12)), calculateButton_(new QPushButton),
                           resetButton_(new QPushButton), pathList_(new QListWidget),
                           mainLayout_(new QGridLayout) {

    connect(resetButton_.get(), SIGNAL(pressed()), this, SLOT(resetAll()));
    connect(calculateButton_.get(), SIGNAL(pressed()), this, SLOT(calculatePath()));
    connect(pathList_.get(), SIGNAL(itemSelectionChanged()), this, SLOT(renderUntilSelectedElement()));
    calculateButton_->setText(tr("Calculate Path"));
    resetButton_->setText(tr("Reset Image"));
    mainLayout_->setColumnStretch(0, 1);
    mainLayout_->setColumnStretch(1, 1);
    mainLayout_->addWidget(renderArea_.get(), 0, 0, 2, 1);
    mainLayout_->addWidget(resetButton_.get(), 2, 0, 1, 1);
    mainLayout_->addWidget(calculateButton_.get(), 0, 1, 1, 1);
    mainLayout_->addWidget(pathList_.get(), 1, 1, 2, 1);
    setLayout(mainLayout_.get());
    setWindowTitle(tr("Knitting!"));
}

QSize MainWidget::sizeHint() const {
    return {this->width(), this->height()};
}

QSize MainWidget::minimumSizeHint() const {
    return {this->width(), this->height()};
}

void MainWidget::resetAll() {
    renderArea_->resetRenderArea();
    renderArea_->update();
    pathList_->clear();
}

void MainWidget::calculatePath() {
    PathFinder pathFinder;
    auto result = pathFinder(renderArea_->getTiles());
    if (result) {
        renderArea_->resetTiles();
        renderArea_->setPathToRender(result.value());
        renderArea_->update();
        pathList_->clear();
        for (auto &i: result.value()) {
            pathList_->addItem(static_cast<QString>(std::string(
                    "(" + std::to_string(i.first) + "," + std::to_string(i.second) + ")").c_str()));
        }
    } else {
        QMessageBox::warning(this, "Warning", "There are no way to build path");
    }
}

void MainWidget::renderUntilSelectedElement() {
    renderArea_->renderPathUntil(pathList_->currentIndex().row() + 1);
    renderArea_->update();
}
