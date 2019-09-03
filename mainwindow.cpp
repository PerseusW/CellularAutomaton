#include "mainwindow.h"

static const int sceneStart = 0;
static const int sceneSize = 600;
static const int cellSize = 10;
static const int cellNum = sceneSize/cellSize;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initBlankEnvironment();
    initCells();
    updateEnvironment();
    connect(button,SIGNAL(clicked()),this,SLOT(grow()));
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < cellNum; ++i) {
        delete[] cellPlate[i];
    }
    delete[] cellPlate;
}

void MainWindow::initBlankEnvironment()
{
    setWindowTitle("Cellular Automaton");
    mainWidget = new QWidget();
    mainLayout = new QGridLayout(mainWidget);
    settingLayout = new QVBoxLayout();
    button = new QPushButton("Grow");
    cellNumLabel = new QLabel("Cell Number:"+QString::number(cellNum*cellNum));
    settingLayout->addWidget(button);
    settingLayout->addWidget(cellNumLabel);
    mainLayout->addLayout(settingLayout,0,1);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(sceneStart,sceneStart,sceneSize,sceneSize);
    for (int colPos = sceneStart; colPos <= sceneStart + sceneSize - cellSize; colPos += cellSize) {
        for (int rowPos = sceneStart; rowPos <= sceneStart + sceneSize - cellSize; rowPos += cellSize) {
           scene->addRect(colPos,rowPos,cellSize,cellSize);
        }
    }
    view = new QGraphicsView(scene);
    view->setFixedSize(sceneSize + 2 * cellSize, sceneSize + 2 * cellSize);
    mainLayout->addWidget(view,0,0);

    setCentralWidget(mainWidget);
}

void MainWindow::initCells()
{
    cellPlate = new bool*[cellNum]();
    bufferPlate = new bool*[cellNum]();
    for (int i = 0; i < cellNum; ++i) {
        cellPlate[i] = new bool[cellNum]();
        bufferPlate[i] = new bool[cellNum]();
    }
    cellPlate[cellNum/2][cellNum/4-1] = true;
    cellPlate[cellNum/2][cellNum/4+1] = true;
    cellPlate[cellNum/2-1][cellNum/4] = true;
    cellPlate[cellNum/2+1][cellNum/4] = true;
    cellPlate[cellNum/2][cellNum*3/4-1] = true;
    cellPlate[cellNum/2][cellNum*3/4+1] = true;
    cellPlate[cellNum/2-1][cellNum*3/4] = true;
    cellPlate[cellNum/2+1][cellNum*3/4] = true;
}

void MainWindow::updateEnvironment()
{
    QList<QGraphicsItem*> itemList = scene->items(Qt::AscendingOrder);
    int i=0,j=0;
    for (QGraphicsItem* item: itemList) {
        QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
        if (cellPlate[i][j]) {
            rectItem->setBrush(QBrush(Qt::black));
        }
        else {
            rectItem->setBrush(QBrush(Qt::white));
        }
        i++;
        if (i >= cellNum) {
            i = 0;
            j++;
        }
    }
}

void MainWindow::grow()
{
    for (int i = 1; i < cellNum - 1; ++i) {
        for (int j = 1; j < cellNum - 1; ++j) {
            int count = 0;
            if (cellPlate[i-1][j-1]) {
                count++;
            }
            if (cellPlate[i-1][j]) {
                count++;
            }
            if (cellPlate[i-1][j+1]) {
                count++;
            }
            if (cellPlate[i][j-1]) {
                count++;
            }
            if (cellPlate[i][j+1]) {
                count++;
            }
            if (cellPlate[i+1][j-1]) {
                count++;
            }
            if (cellPlate[i+1][j]) {
                count++;
            }
            if (cellPlate[i+1][j+1]) {
                count++;
            }
            if (count == 2 || count == 3) {
                bufferPlate[i][j]=true;
            }
            else {
                bufferPlate[i][j]=false;
            }
        }
    }
    for (int i = 1; i < cellNum - 1; ++i) {
        for (int j = 1; j < cellNum - 1; ++j) {
            cellPlate[i][j] = bufferPlate[i][j];
        }
    }
    updateEnvironment();
}
