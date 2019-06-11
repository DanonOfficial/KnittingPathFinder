//
// Created by roundedglint585 on 6/11/19.
//

#ifndef KNITTINGPATHFINDER_RENDERAREA_HPP
#define KNITTINGPATHFINDER_RENDERAREA_HPP

#include <iostream>
#include <vector>
#include <variant>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

class RenderArea : public QWidget {
Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr, size_t size = 10);

    ~RenderArea() override = default;

    QSize sizeHint() const override;

    QSize minimumSizeHint() const override;

    std::vector<std::vector<uint8_t>> getTiles() const;

    void resetTiles();

    void resetPath();

    void resetRenderArea();

    void setPathToRender(const std::vector<std::pair<size_t, size_t>> &path);

    void setPathToRender();

    void setTilesToRender(const std::vector<std::pair<std::size_t, std::size_t>> &tiles);

    void setTilesToRender();

    void renderPathUntil(size_t index);

protected:
    void paintEvent(QPaintEvent *) override;

    void mousePressEvent(QMouseEvent *event) override;

private:

    void updateIndexFromPoint(const QPoint &point);

    std::variant<std::vector<std::vector<uint8_t>>, std::vector<std::pair<std::size_t, std::size_t>>> renderData_;
    size_t scale_;
    size_t width_, height_;
    size_t renderPathUntil_;
};

#endif //KNITTINGPATHFINDER_RENDERAREA_HPP
