#ifndef UI_EDIT_CYCLIC_TIMER_HPP
#define UI_EDIT_CYCLIC_TIMER_HPP

#include <QLabel>
#include <QString>
#include <QDialog>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QKeySequence>
#include <QKeySequenceEdit>
#include "CyclicTimerSpec.hpp"
#include "CyclicTimerData.hpp"

class UiEditCyclicTimer : public QDialog
{
  public:
    explicit UiEditCyclicTimer(CyclicTimerSpec* spec);
    ~UiEditCyclicTimer();
    static CyclicTimerData* newCyclicTimer(CyclicTimerSpec* spec);
    static CyclicTimerData* editCyclictimer(CyclicTimerSpec* spec);

  private:
    void checkStart();
    void checkTerminate();
    void buttonMoreClicked();
    void adjustPeriodLabel(int seconds);
    void adjustStartLabel(int seconds);
    void adjustTerminateLabel(int seconds);
    void adjustVolumeLabel(int percent);

    bool Collapsed;
    QKeySequenceEdit* EditKeySequence;
    QPushButton* ButtonClear;
    QPushButton* ButtonMore;
    QGroupBox* AdvancedBox;
    QComboBox* ComboSound;
    QSlider* SliderTerminate;
    QSlider* SliderPeriod;
    QSlider* SliderVolume;
    QSlider* SliderStart;
    QLabel* LabelTerminate;
    QLabel* LabelPeriod;
    QLabel* LabelVolume;
    QLabel* LabelStart;
};

#define BUTTON_MORE_TEXT "More..."

#endif // UI_EDIT_CYCLIC_TIMER_HPP
