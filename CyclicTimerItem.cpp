#include "CyclicTimerItem.hpp"
#include <QObject>

CyclicTimerItem::CyclicTimerItem(QString text)
    : QTableWidgetItem(text)
{
    setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
}

void CyclicTimerItem::adjustText()
{
    if (flags() & Qt::ItemIsUserCheckable) {
        if (checkState() == Qt::Unchecked) {
            setText(QObject::tr("no"));
        }
        else {
            setText(QObject::tr("yes"));
        }
    }
}
