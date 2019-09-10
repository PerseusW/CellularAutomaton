#include "cellscene.h"

CellScene::CellScene(QObject *parent)
    : QGraphicsScene (parent)
{
    sceneSize = 600;
    cellNum = 20;
    cellSize = sceneSize/cellNum;
    initSceneBySize();
}

CellScene::~CellScene()
{
    for (int i = 0; i < cellNum; ++i) {
        delete[] cellData[i];
    }
    delete[] cellData;
}

int CellScene::getSceneSize()
{
    return sceneSize;
}

int CellScene::getCellNum()
{
    return cellNum;
}

QStringList CellScene::getValidCellNums()
{
    QStringList list;
    for (int i = 3; i <= sceneSize/3; ++i) {
        if (sceneSize%i==0) {
            list.append(QString::number(i));
        }
    }
    return list;
}

void CellScene::initSceneBySize()
{
    cellData = new bool*[cellNum]();
    for (int i = 0; i < cellNum; ++i) {
        cellData[i] = new bool[cellNum]();
    }
    this->clear();
    for (int rowPos = 0; rowPos < sceneSize; rowPos += cellSize) {
        for (int colPos = 0; colPos < sceneSize; colPos += cellSize) {
            this->addRect(colPos,rowPos,cellSize,cellSize,QPen(),QBrush(Qt::white));
        }
    }
}

void CellScene::updateScene()
{
    int i=0,j=0;
    for (QGraphicsItem* item: items(Qt::AscendingOrder)) {
        QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
        if (cellData[i][j]) {
            rectItem->setBrush(QBrush(Qt::black));
        }
        else {
            rectItem->setBrush(QBrush(Qt::white));
        }
        ++j;
        if (j >= cellNum) {
            j = 0;
            ++i;
        }
    }
}

void CellScene::changeCellNum(QString string)
{
    cellNum = string.toInt();
    cellSize = sceneSize/cellNum;
    initSceneBySize();
}

void CellScene::grow()
{
    QList<QPoint>* changedCells = new QList<QPoint>();
    for (int i = 1; i < cellNum - 1; ++i) {
        for (int j = 1; j < cellNum - 1; ++j) {
            if (cellData[i-1][j]) {
                changedCells->append(QPoint(i-1,j));
                changedCells->append(QPoint(i,j));
            }
        }
    }
    for (QPoint cellPoint: *changedCells) {
        int row = cellPoint.x();
        int col = cellPoint.y();
        if (cellData[row][col]) {
            cellData[row][col] = false;
        }
        else {
            cellData[row][col] = true;
        }
    }
    updateScene();
}

void CellScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF eventPoint = event->scenePos();
    QGraphicsItem *item = itemAt(eventPoint,QTransform());
    QGraphicsRectItem *rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
    if (rectItem->brush().color() == Qt::white) {
        rectItem->setBrush(QBrush(Qt::black));
    }
    else if (rectItem->brush().color() == Qt::black) {
        rectItem->setBrush(QBrush(Qt::white));
    }
    int row = eventPoint.toPoint().y()/cellSize;
    int col = eventPoint.toPoint().x()/cellSize;
    if (cellData[row][col]) {
        cellData[row][col] = false;
    }
    else {
        cellData[row][col] = true;
    }
}
