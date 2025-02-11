#include <QMenuBar>
#include <QMenu>
#include <QAction>

#ifndef MENUBAR
#define MENUBAR

class ToolsMenu : public QMenu {
    Q_OBJECT

    public:
    ToolsMenu(const QString &title, QWidget* parent=nullptr);
    ~ToolsMenu();
    QAction* network_view;
    QAction* ssh;
    QAction* mission_planer;
};

class MenuBar : public QMenuBar {
    Q_OBJECT

    public:
    MenuBar(QWidget* parent=nullptr);
    ~MenuBar();

    QAction* tools;
    
};

#endif