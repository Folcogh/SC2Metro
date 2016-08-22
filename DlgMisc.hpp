#ifndef DLGMISC_HPP
#define DLGMISC_HPP

#include <QDialog>

namespace Ui
{
    class DlgMisc;
}

class DlgMisc : public QDialog
{
    Q_OBJECT

  public:
    ~DlgMisc();
    static void showDlgMisc(QWidget* parent);

  private:
    explicit DlgMisc(QWidget* parent);
    Ui::DlgMisc* ui;
};

#endif // DLGMISC_HPP
