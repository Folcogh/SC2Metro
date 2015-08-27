#ifndef UI_EDIT_CYCLIC_TIMER_HPP
#define UI_EDIT_CYCLIC_TIMER_HPP

#include <QString>
#include <QDialog>
#include <QSlider>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QKeySequence>
#include <QKeySequenceEdit>

/* Period
 * Start at
 * Terminate at
 * Sound
 * Volume
 * Hotkey
 */
class UiEditCyclicTimer : public QDialog
{
  public:
    UiEditCyclicTimer();
    ~UiEditCyclicTimer();
    static bool newCyclicTimer();

  private:
    void buttonMoreClicked();

    bool Collapsed;
    QPushButton* ButtonMore;
    QGroupBox* AdvancedBox;
    QSlider* SliderStart;
    QSlider* SliderTerminate;
    QSlider* SliderPeriod;
    QSlider* SliderVolume;
    QComboBox* ComboSound;
    QKeySequenceEdit* EditKeySequence;
};

#define BUTTON_MORE_TEXT "More..."

#endif // UI_EDIT_CYCLIC_TIMER_HPP
