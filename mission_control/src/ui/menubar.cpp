#include "ui/menubar.h"

QString style_menubar = R"(
    QMenuBar {
        background-color: #181818;
        color: #CCCCBB;
        padding-left: 20px;
        padding-top: 5px;
    }
    QMenuBar::item:selected {
        background-color: #37373D;
        color: #CCCCBB;
    }
    QMenuBar::item:pressed {
        background-color: #37373D;
        color: #CCCCBB;
    }
)";
    
QString style_menu = R"(
 QMenu {
    background-color: #1F1F1F;
    color: #CCCCBB;
    }
    QMenu::item {
        background-color: 1F1F1F;
    }
    QMenu::item:selected {
        background-color: #37373D;
    }
)";

ToolsMenu::ToolsMenu(const QString& title, QWidget* parent) : QMenu(title, parent)
{
    setTitle(title);
    setStyleSheet(style_menu);
    network_view = new QAction("Network Monitor", this);
    ssh = new QAction("SSH", this);
    mission_planer = new QAction("Mission Planer", this);

    addAction(network_view);
    addAction(ssh);
    addAction(mission_planer);
    
}

ToolsMenu::~ToolsMenu(){}

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    setStyleSheet(style_menubar);
    ToolsMenu* toolsmenu = new ToolsMenu("Tools", this);
    tools = addMenu(toolsmenu);
}

MenuBar::~MenuBar(){}