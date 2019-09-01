#include "mainwindow.h"

static const int sceneStart = 0;
static const int sceneSize = 600;
static const int cellSize = 20;
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

}


void MainWindow::initBlankEnvironment()
{
    setWindowTitle("Cellular Automaton");
    setFixedSize(800,800);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(sceneStart,sceneStart,sceneSize,sceneSize);
    for (int colPos = sceneStart; colPos <= sceneStart + sceneSize - cellSize; colPos += cellSize) {
        for (int rowPos = sceneStart; rowPos <= sceneStart + sceneSize - cellSize; rowPos += cellSize) {
           scene->addRect(colPos,rowPos,cellSize,cellSize,QPen(),QBrush());
        }
    }
    view = new QGraphicsView(scene);
    view->setFixedSize(sceneSize + 2 * cellSize, sceneSize + 2 * cellSize);
    widget = new QWidget();
    mainLayout = new QGridLayout(widget);
    mainLayout->addWidget(view,0,0);
    settingLayout = new QVBoxLayout();
    button = new QPushButton("Grow");
    settingLayout->addWidget(button);
    mainLayout->addLayout(settingLayout,0,1);
    setCentralWidget(widget);
}

void MainWindow::initCells()
{
    cellPlate = new bool*[cellNum]();
    for (int i = 0; i < cellNum; ++i) {
        cellPlate[i] = new bool[cellNum]();
    }
    cellPlate[cellNum/2][cellNum/2] = true;
    cellPlate[cellNum/2+1][cellNum/2+1] = true;
    cellPlate[cellNum/2-1][cellNum/2+1] = true;
}

void MainWindow::updateEnvironment()
{
    QList<QGraphicsItem*> itemList = scene->items(Qt::AscendingOrder);
    int i=0,j=0;
    for (QGraphicsItem* item: itemList) {
        QGraphicsRectItem* rectItem = (QGraphicsRectItem*) item;
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
    bool** nextPlate = new bool*[cellNum]();
    for (int i = 0; i < cellNum; ++i) {
        nextPlate[i] = new bool[cellNum]();
    }
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
                nextPlate[i][j]=true;
            }
            else {
                nextPlate[i][j]=false;
            }
        }
    }
    for (int i = 1; i < cellNum - 1; ++i) {
        for (int j = 1; j < cellNum - 1; ++j) {
            cellPlate[i][j] = nextPlate[i][j];
        }
    }
    updateEnvironment();
}
