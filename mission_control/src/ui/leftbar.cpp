#include "ui/leftbar.h"
#include <QScreen>
#include <QApplication>

QString style_sidebar = R"(
    background-color: #181818;
    padding:0;
)";

QString style_sidebar_button = R"(
    QPushButton {padding: 4px;}
    QPushButton:hover {background-color:#595958;}
)";

SideBar::SideBar(QWidget* parent) : QWidget(parent){
    QScreen *screen = QApplication::primaryScreen();
    int screenHeight = screen->geometry().height();
    int screenWidth = screen->geometry().width();
    int width = static_cast<int>(screenWidth/25);
    int icon_width = static_cast<int>(width/2);

    setFixedWidth(width);
    setStyleSheet(style_sidebar);
    layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    account = new QPushButton();
    account->setFixedHeight(width);
    account->setIcon(QIcon(":/login.png"));
    account->setIconSize(QSize(icon_width, icon_width));
    account->setStyleSheet(style_sidebar_button);

    nav = new QPushButton();
    nav->setFixedHeight(width);
    nav->setIcon(QIcon(":/map.png"));
    nav->setIconSize(QSize(icon_width, icon_width));
    nav->setStyleSheet(style_sidebar_button);

    log = new QPushButton();
    log->setFixedHeight(width);
    log->setIcon(QIcon(":/log.png"));
    log->setIconSize(QSize(icon_width, icon_width));
    log->setStyleSheet(style_sidebar_button);

    power = new QPushButton();
    power->setFixedHeight(width);
    power->setIcon(QIcon(":/power.png"));
    power->setIconSize(QSize(icon_width, icon_width));
    power->setStyleSheet(style_sidebar_button);

    sos = new QPushButton();
    sos->setFixedHeight(width);
    sos->setIcon(QIcon(":/sos.png"));
    sos->setIconSize(QSize(icon_width, icon_width));
    sos->setStyleSheet(style_sidebar_button);

    layout->addWidget(account);
    layout->addWidget(nav);
    layout->addWidget(log);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout->addWidget(spacer);
    layout->addWidget(sos);
    layout->addWidget(power);
    this->setLayout(layout);
}

SideBar::~SideBar(){

}