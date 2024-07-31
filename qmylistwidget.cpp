#include "qmylistwidget.h"
#include <QDebug>
QMyListWidget::QMyListWidget(QWidget *parent)
: QListWidget(parent)
{
    //创建一个菜单
    contextMenu = new QMenu(this);
    dealAction = new QAction(this);
    contextMenu->addAction(dealAction);
    connect(dealAction, &QAction::triggered, [=](){
        emit load('/' + selectedItem);
    });
}

QMyListWidget::~QMyListWidget()
{
    delete dealAction;
    delete contextMenu;
}

void QMyListWidget::setMenu(const QString& name)
{
    dealAction->setText(name);
}

void QMyListWidget::mousePressEvent(QMouseEvent *event)
{
    //确保右键点击，然后跳出菜单.
    if (event->button() == Qt::RightButton)
    {
        if(this->selectedItems().size())
        {
            auto item = this->selectedItems()[0];
            selectedItem = item->text();
            if(itemAt(event->QMouseEvent::pos()) == item && selectedItem != "..")
                contextMenu->exec(event->globalPos());
        }
    }
    else
    //要继续保留QListWidget原有的点击事件.
        QListWidget::mousePressEvent(event);
}
