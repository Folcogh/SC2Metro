#ifndef CYCLIC_TIMER_EDIT_HPP
#define CYCLIC_TIMER_EDIT_HPP

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

class CyclicTimerEdit : public QDialog
{
  public:
    explicit CyclicTimerEdit(CyclicTimerSpec* spec);
    ~CyclicTimerEdit();
    static CyclicTimerData* newCyclicTimer(CyclicTimerSpec* spec);
    static bool editCyclicTimer(CyclicTimerSpec* spec, CyclicTimerData* data);

  private:
    Q_DISABLE_COPY(CyclicTimerEdit)
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

#endif // CYCLIC_TIMER_EDIT_HPP
