#include "graphscene.h"
#include "mainwindow.h"

graphscene::graphscene(QObject *parent) : QGraphicsScene(parent){
}

void graphscene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   QPointF pt = mouseEvent->scenePos();
   px=pt;
   //clicked=1;
}

void graphscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF pt = mouseEvent->scenePos();

    if(px==pt&&pt.x()<675)
    {
        double rad=30;
        for(int i=0;i<nodes;i++)
        {
            if((pt.x()>(node[i].x()-50))&&(pt.x()<(node[i].x()+50))&&(pt.y()>(node[i].y()-50))&&(pt.y()<(node[i].y()+50)))
            {
                dontPrint=1;
                break;
            }
            else
            {
                dontPrint=0;
            }
        }

        if(firstNodeDone==1)
        {
            if(dontPrint==0)
            {
                this->addEllipse(pt.x()-rad,pt.y()-rad,rad*2.0,rad*2.0,QPen(),QBrush(Qt::gray));
                QPen rectPen;
                rectPen.setStyle(Qt::DashLine);
                rectPen.setColor(Qt::gray);
                this->addLine(pt.x()-50,pt.y()-50,pt.x()-50,pt.y()+50,rectPen);
                this->addLine(pt.x()-50,pt.y()-50,pt.x()+50,pt.y()-50,rectPen);
                this->addLine(pt.x()+50,pt.y()+50,pt.x()+50,pt.y()-50,rectPen);
                this->addLine(pt.x()+50,pt.y()+50,pt.x()-50,pt.y()+50,rectPen);
                node[nodes]=pt;

                nodes++;
                QGraphicsTextItem *text = this->addText(QString::number(nodes));
                text->adjustSize();
                text->setPos(pt.x()-10,pt.y()-10);
            }
        }
        else
        {
            this->addEllipse(pt.x()-rad,pt.y()-rad,rad*2.0,rad*2.0,QPen(),QBrush(Qt::gray));
            QPen rectPen;
            rectPen.setStyle(Qt::DashLine);
            rectPen.setColor(Qt::gray);
            this->addLine(pt.x()-50,pt.y()-50,pt.x()-50,pt.y()+50,rectPen);
            this->addLine(pt.x()-50,pt.y()-50,pt.x()+50,pt.y()-50,rectPen);
            this->addLine(pt.x()+50,pt.y()+50,pt.x()+50,pt.y()-50,rectPen);
            this->addLine(pt.x()+50,pt.y()+50,pt.x()-50,pt.y()+50,rectPen);
            node[nodes]=pt;

            nodes++;
            QGraphicsTextItem *text = this->addText(QString::number(nodes));
            text->adjustSize();
            text->setPos(pt.x()-10,pt.y()-10);
            firstNodeDone=1;
        }
    }
    else
    {
        int s=-1,d=-1;
        for(int i=0;i<nodes;i++)
        {
            if((px.x()>(node[i].x()-50))&&(px.x()<(node[i].x()+50))&&(px.y()>(node[i].y()-50))&&(px.y()<(node[i].y()+50)))
            {
                s=i;
                break;
            }
            else
                continue;
        }

        for(int i=0;i<nodes;i++)
        {
            if((pt.x()>(node[i].x()-50))&&(pt.x()<(node[i].x()+50))&&(pt.y()>(node[i].y()-50))&&(pt.y()<(node[i].y()+50)))
            {
                d=i;
                break;
            }
            else
                continue;
        }

        if((s!=-1&&d!=-1)&&s!=d)
        {
            addEdge(adjList,s,d);
            QPen linePen;
            linePen.setWidth(2);
            this->addLine(px.x(),px.y(),pt.x(),pt.y(),linePen);
            double rad=3;
            this->addRect(px.x()-4,px.y()-4,6,6,QPen(),QBrush(Qt::red));
            this->addEllipse(pt.x()-rad,pt.y()-rad,rad*2.0,rad*2.0,QPen(),QBrush(Qt::green));
            //this->addEllipse(px.x()-rad,px.y()-rad,rad*2.0,rad*2.0,QPen(),QBrush(Qt::red));
        }
        else
        {

        }
    }
}

void graphscene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    std::vector<bool> done(25, false);
    std::vector<bool> done2(25, false);
    QPointF pt = mouseEvent->scenePos();
    int temp=-1;
    for(int i=0;i<nodes;i++)
    {
        if((pt.x()>(node[i].x()-50))&&(pt.x()<(node[i].x()+50))&&(pt.y()>(node[i].y()-50))&&(pt.y()<(node[i].y()+50)))
        {
            temp=i;
            break;
        }
        else
            continue;
    }

    if(temp!=-1)
    {
        myClone(temp,adjList,done,done2);
        double rad=30;
        QPen sourPen;
        sourPen.setWidth(2);
        sourPen.setColor(Qt::red);
        this->addEllipse(node[temp].x()-rad+675,node[temp].y()-rad,rad*2.0,rad*2.0,sourPen);
    }
}

void graphscene::addEdge(std::vector<int> myList[], int sour, int dest)
{
    myList[sour].push_back(dest);
}

void graphscene::myClone(int sour,std::vector<int> myList[],std::vector<bool> &done,std::vector<bool> &done2)
{
    if (done[sour]==true)
    {
        done2[sour]=true;
    }
    done[sour] = true;

    QPen linePen;
    linePen.setWidth(2);
    double rad=30;

    if(done2[sour]==false)
    {
        this->addEllipse(node[sour].x()-rad+675,node[sour].y()-rad,rad*2.0,rad*2.0,QPen());
        QGraphicsTextItem *text = this->addText(QString::number(sour+1)+" ");
        text->setPos(node[sour].x()+675-10,node[sour].y()-10);
    }

    if(done[sour]==false&&done2[sour]==false)
    {
        for(int i=0;i<myList[sour].size();i++)
        {
            if (done[myList[sour][i]]==false||done2[myList[sour][i]]==false)
            {
                this->addLine(node[sour].x()+675-10,node[sour].y()-10,node[myList[sour][i]].x()+675+10,node[myList[sour][i]].y()+10,linePen);
                double rad=3;
                this->addRect(node[sour].x()-4+675-10,node[sour].y()-4-10,6,6,QPen(),QBrush(Qt::red));
                this->addEllipse(node[myList[sour][i]].x()-rad+675+10,node[myList[sour][i]].y()-rad+10,rad*2.0,rad*2.0,QPen(),QBrush(Qt::green));
                myClone(myList[sour][i],myList,done,done2);
            }
        }
    }
    else if(done[sour]==true&&done2[sour]==false)
    {
        for(int i=(myList[sour].size())-1;i>=0;i--)
        {
            if (done[myList[sour][i]]==false||done2[myList[sour][i]]==false)
            {
                this->addLine(node[sour].x()+675-10,node[sour].y()-10,node[myList[sour][i]].x()+675+10,node[myList[sour][i]].y()+10,linePen);
                double rad=3;
                this->addRect(node[sour].x()-4+675-10,node[sour].y()-4-10,6,6,QPen(),QBrush(Qt::red));
                this->addEllipse(node[myList[sour][i]].x()-rad+675+10,node[myList[sour][i]].y()-rad+10,rad*2.0,rad*2.0,QPen(),QBrush(Qt::green));
                myClone(myList[sour][i],myList,done,done2);
            }
        }
    }
}
