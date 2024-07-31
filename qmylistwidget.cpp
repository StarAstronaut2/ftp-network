#include "qmylistwidget.h"
#include <QDebug>

QMyListWidget::QMyListWidget(QWidget *parent)
    : QListWidget(parent)
{
    // 创建一个菜单
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
    // 确保右键点击，然后跳出菜单
    if (event->button() == Qt::RightButton)
    {
        auto item = itemAt(event->pos());
        if (item)
        {
            // 选中右键点击的项目
            clearSelection();
            item->setSelected(true);

            selectedItem = item->text();
            if (selectedItem != "..") // 忽略 ".." 项
            {
                contextMenu->exec(event->globalPos());
            }
        }
    }
    else
    {
        // 保留 QListWidget 原有的点击事件
        QListWidget::mousePressEvent(event);
    }
}
