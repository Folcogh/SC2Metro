#ifndef STARTPAGE_HPP
#define STARTPAGE_HPP

#include <QWidget>

namespace Ui {
    class StartPage;
}

class StartPage : public QWidget
{
        Q_OBJECT

    public:
         StartPage();
        ~StartPage();

    private:
        Q_DISABLE_COPY(StartPage)
        Ui::StartPage *ui;
};

#endif // STARTPAGE_HPP
