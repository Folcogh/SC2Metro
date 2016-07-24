#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QTableWidget>

// Size of the icons in the main toolbar
#define MAIN_TOOLBAR_ICON_WIDTH 64
#define MAIN_TOOLBAR_ICON_HEIGHT 64

// Index of the columns in the timers table
#define COLUMN_SOUND 0
#define COLUMN_PERIOD 1
#define COLUMN_HOTKEY 2

class MainWindow: public QMainWindow
{
        Q_OBJECT

    public:
        ~MainWindow();
        static MainWindow* instance();
        void establishConnections();

    private:
        Q_DISABLE_COPY(MainWindow)

        // MainWindow is a singleton
        static MainWindow* mainWindow;
        MainWindow();

        // These actions are icons in the main toolbar
        QAction* actionNewList;
        QAction* actionOpenList;
        QAction* actionSaveList;
        QAction* actionNewTimer;
        QAction* actionEditTimer;
        QAction* actionRemovTimer;
        QAction* actionMisc;

        // Prevent the toolbar to be hidden with a context menu
        QMenu* createPopupMenu() override;

        // Main widget, displaying the timers
        QTableWidget* timerTable;
};

#endif // MAINWINDOW_HPP
