#include "ui/mainui.h"

QString mainui_style = R"(
    background-color: #1F1F1F; margin:0px; padding:0px;
)";

MainUI::MainUI(QWidget* parent) : QWidget(parent){
    setStyleSheet(mainui_style);
    setWindowTitle("Mission Control v5.0");
    setWindowFlags(Qt::FramelessWindowHint);

    topbar = new TopBar();
    sidebar = new SideBar();
    tabbar = new TabBar();
    maintab = new MainTab();
    tabbar->addTab(maintab, "Mission Control");

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* row2 = new QHBoxLayout();    
    row2->addWidget(sidebar);
    row2->addWidget(tabbar);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(topbar);
    layout->addLayout(row2);

    setLayout(layout);
}

MainUI::~MainUI() {

}