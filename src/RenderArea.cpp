//
// Created by roundedglint585 on 6/11/19.
//

#include "../include/RenderArea.hpp"


RenderArea::RenderArea(QWidget *parent, size_t size) :
        QWidget(nullptr), renderData_(std::vector(size, std::vector<uint8_t>(size, 0))), width_(size), height_(size),
        renderPathUntil_(0) {
    this->resize(parent->width() / 2, parent->height() / 2);
    scale_ = std::min(this->width(), this->height()) / height_;
}

void RenderArea::paintEvent(QPaintEvent *) {
    scale_ = std::min(this->width(), this->height()) / height_;
    QPainter painter(this);
    QPen pen;  // creates a default pen
    pen.setStyle(Qt::DotLine);
    painter.setPen(pen);

    for (size_t i = 0; i < height_ + 1; i++) {
        painter.drawLine(0, i * scale_, height_ * scale_, i * scale_);
    }
    for (size_t i = 0; i < width_ + 1; i++) {
        painter.drawLine(i * scale_, 0, i * scale_, width_ * scale_);
    }

    std::visit([this, &painter, &pen](auto &&data) {
        using T = std::decay_t<decltype(data)>;
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if constexpr (std::is_same_v<T, std::vector<std::vector<uint8_t>>>) {
            for (size_t i = 0; i < data.size(); i++) {
                for (size_t j = 0; j < data[i].size(); j++) {
                    if (data[j][i] != 0) {
                        painter.fillRect(i * scale_, j * scale_, scale_ + 1, scale_ + 1, Qt::black);
                    }
                }
            }
        } else if constexpr (std::is_same_v<T, std::vector<std::pair<std::size_t, std::size_t>>>) {
            for (size_t i = 1; i < std::min(data.size(), renderPathUntil_); i++) {
                painter.drawLine(data[i - 1].second * scale_, data[i - 1].first * scale_, data[i].second * scale_,
                                 data[i].first * scale_);
            }
        }

    }, renderData_);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    QPoint point = event->pos();
    updateIndexFromPoint(point);
    update();
}

void RenderArea::updateIndexFromPoint(const QPoint &point) {
    size_t x = point.x() / scale_;
    size_t y = point.y() / scale_;
    if (std::holds_alternative<std::vector<std::vector<uint8_t>>>(renderData_) && (x < width_) && (y < height_)) {
        auto &tiles = std::get<std::vector<std::vector<uint8_t>>>(renderData_);
        tiles[y][x] = (tiles[y][x] + 1) % 2;
    }
}

QSize RenderArea::sizeHint() const {
    return minimumSizeHint();
}

QSize RenderArea::minimumSizeHint() const {
    return {static_cast<int>(scale_) * static_cast<int>(width_) + 1,
            static_cast<int>(scale_) * static_cast<int>(height_) + 1};
}

std::vector<std::vector<uint8_t>> RenderArea::getTiles() const {
    if (std::holds_alternative<std::vector<std::vector<uint8_t>>>(renderData_)) {
        return std::get<std::vector<std::vector<uint8_t>>>(renderData_);
    }
    return {};
}


void RenderArea::setPathToRender(const std::vector<std::pair<size_t, size_t>> &path) {
    renderData_ = path;
    renderPathUntil_ = path.size();
}

void RenderArea::setPathToRender() {
    renderData_ = {};
}

void RenderArea::setTilesToRender(const std::vector<std::pair<std::size_t, std::size_t>> &tiles) {
    renderData_ = tiles;
}

void RenderArea::setTilesToRender() {
    renderData_ = std::vector(height_, std::vector<uint8_t>(width_, 0));
}

void RenderArea::resetTiles() {
    if (std::holds_alternative<std::vector<std::vector<uint8_t>>>(renderData_)) {
        for (auto &i: std::get<std::vector<std::vector<uint8_t>>>(renderData_)) {
            for (auto &j: i) {
                j = 0;
            }
        }
    }
}

void RenderArea::resetPath() {
    setPathToRender();
}

void RenderArea::resetRenderArea() {
    std::visit([this](auto &&data) {
        using T = std::decay_t<decltype(data)>;
        if constexpr (std::is_same_v<T, std::vector<std::vector<uint8_t>>>) {
            resetTiles();
        } else if constexpr (std::is_same_v<T, std::vector<std::pair<std::size_t, std::size_t>>>) {
            setTilesToRender();
        }

    }, renderData_);
}

void RenderArea::renderPathUntil(size_t index) {
    renderPathUntil_ = index;
}