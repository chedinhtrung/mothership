#include "ui/tabbar.h"

QString style_tabbar = R"(
    QTabWidget::pane { background-color: #1F1F1F; } 
    QTabBar { font-size: 12pt;  background: white;} 
    QTabBar::tab:selected { color: #CCCCBB; background-color: #1F1F1F; border-top: 3px solid #22A4F1; padding: 5px 10px 5px 20px;}
    QTabBar::tab { color: #CCCCBB; background-color: #181818; padding: 5px 10px 5px 20px;}
)";

TabBar::TabBar(QWidget* parent) : QTabWidget(parent){
    setStyleSheet(style_tabbar);

}

TabBar::~TabBar(){}