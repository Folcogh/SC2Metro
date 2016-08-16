#ifndef SMDIALOG_HPP
#define SMDIALOG_HPP

#include <QDialog>

class SMDialog : public QDialog
{
    Q_DISABLE_COPY(SMDialog)

  public:
    explicit SMDialog(QWidget* parent);
};

#endif // SMDIALOG_HPP
