#ifndef CELLSCENE_H
#define CELLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QDebug>
#include <QComboBox>

class CellScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CellScene(QObject *parent = nullptr);
    ~CellScene();

    QGraphicsView* getView();
    QComboBox* getValidCellNums();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

private:
    int sceneSize;
    int cellNum;
    int cellSize;
    bool** cellData;
    void initSceneBySize();
    void updateScene();

    int getSurroundingCellNum(int,int);

public slots:
    void changeCellNum(QString);
    void grow();
};

#endif // CELLSCENE_H

