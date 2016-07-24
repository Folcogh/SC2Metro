#ifndef DLGNEWTIMER_HPP
#define DLGNEWTIMER_HPP

#include <QLabel>
#include <QObject>
#include <QDialog>
#include <QString>
#include <QSpinBox>
#include <QKeyEvent>
#include <QComboBox>
#include <QKeySequenceEdit> // TODO: replace with a custom input widget
#include <QDialogButtonBox>

class DlgNewTimer: public QDialog
{
        Q_OBJECT

    public:
        DlgNewTimer(QWidget* parent = nullptr);
        ~DlgNewTimer();
        QString getSoundName() const;
        int getPeriod() const;
        QKeyEvent getHotKey() const;

    private:
        Q_DISABLE_COPY(DlgNewTimer)

        // Elements of the ui which are used by some slots
        QComboBox* builtinList;
        QSpinBox* period;
        QKeySequenceEdit* editHotkey;
        QDialogButtonBox* buttons;
        QLabel* labelInvalidHotkey;

        // Triggerred when the period is modified
        void periodChanged(int newPeriod);
};

#endif // DLGNEWTIMER_HPP
