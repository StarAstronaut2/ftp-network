#include "qmylistwidget.h"
#include <QDebug>
#include <QFont>

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

    // 调整整个 QListWidget 的字体大小
    QFont font = this->font();
    font.setPointSize(16);  // 设置字体大小为 12，可以根据需要调整
    this->setFont(font);
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
