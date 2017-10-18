#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QObject>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QThread>

class graphscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit graphscene(QObject *parent = nullptr);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void addEdge(std::vector<int> adj[],int sour,int dest);
    void myClone(int sour, std::vector<int> adj[],std::vector<bool> &visited,std::vector<bool> &visited2);

private:
    QPointF node[50];
    QPointF px;
    std::vector<int> adjList[25];

    int nodes=0;
    int firstNodeDone=0,dontPrint=0,clicked=0;
    double mypos=10;

signals:

public slots:
};

class Sleeper : public QThread
{
public:
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

#endif // GRAPHSCENE_H
