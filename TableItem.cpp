#include "TableItem.hpp"

TableItem::TableItem(QString text)
    : QTableWidgetItem(text, Qt::DisplayRole)
{
    setTextAlignment(Qt::AlignCenter);
}

TableItem::~TableItem()
{
}
