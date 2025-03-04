#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include "binarysearchtree.h"
#include <QColor>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(BinarySearchTree<int> *bst, QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void zoomIn();
    void zoomOut();
    bool eventFilter(QObject *, QEvent *event);
    void autoSize();
    void callRepaint();

signals:

public slots:

protected:

    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:

    BinarySearchTree<int> *bst;
    double scale;
    QPen pen;
    QBrush brush;
    QColor backgroundColor;
    QColor nodeColor = QColor(135, 121, 242);
    QColor textColor;

};

#endif // RENDERAREA_H
