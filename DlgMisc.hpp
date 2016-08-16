#ifndef DLGMISC_HPP
#define DLGMISC_HPP

#include <QDialog>
#include <QTabWidget>

class DlgMisc : public QDialog
{
    public:
        static void showDlgMisc(QWidget* parent);

    private:
        explicit DlgMisc(QWidget* parent);
        void createPageWithText(QTabWidget* tabWidget, QString filename);
};

#endif // DLGMISC_HPP
