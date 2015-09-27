#ifndef CYCLIC_TIMER_ITEM_HPP
#define CYCLIC_TIMER_ITEM_HPP

#include <QTableWidgetItem>

class CyclicTimerItem : public QTableWidgetItem
{
  public:
      CyclicTimerItem(QString text);
      void adjustText();
};

#endif // CYCLIC_TIMER_ITEM_HPP
