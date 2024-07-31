//"QMyListWidget.h"
#ifndef QMYLISTWIDGET_H
#define QMYLISTWIDGET_H
#include <QListWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QMouseEvent>
class QMyListWidget : public QListWidget
{
    Q_OBJECT
    friend class ftpManager;
public:
    QMyListWidget(QWidget *parent);
    ~QMyListWidget();
    void setMenu(const QString& name);
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QMenu *contextMenu;
    QAction *dealAction;
    QString selectedItem;

signals:
    void load(QString);
};

#endif // QMYLISTWIDGET_H

