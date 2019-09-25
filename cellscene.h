#ifndef CELLSCENE_H
#define CELLSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>

class CellScene : public QGraphicsScene
{
    Q_OBJECT
public:
    CellScene(QObject *parent = nullptr);
    ~CellScene();

    QGraphicsView* getMainView();
    QVBoxLayout* getCellNum();

public slots:
    void changeCellNum(QString);
    void grow();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

private:
    int sceneSize;
    int cellNum;
    int cellSize;
    bool** cellData;
    void initScene();
    void updateScene();

    int getSurroundingCellNum(int,int);


};

#endif // CELLSCENE_H

