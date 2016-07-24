#ifndef TABLEITEM_HPP
#define TABLEITEM_HPP

#include <QString>
#include <QTableWidgetItem>

class TableItem: public QTableWidgetItem
{
    public:
        explicit TableItem(QString text);
        ~TableItem();
};

#endif // TABLEITEM_HPP
