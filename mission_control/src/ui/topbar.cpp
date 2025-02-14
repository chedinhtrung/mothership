#include "ui/topbar.h"
#include "ui/style.h"
#include <QSpacerItem>
#include <QApplication>
#include <QFile>
#include <QScreen>

QString style_close_button = R"(
    QPushButton {background-color:darkred; padding:10px} 
    QPushButton:hover {background-color: red;}
)";

QString style_minimize_button = R"(
    QPushButton {font-weight:bold; color: #CCCCBB;}
    QPushButton:hover {background-color:#595958;}
)";

QString style_topbar = R"(
    border-bottom: 2px solid #262626;
    background-color: #181818;
)";

TopBar::TopBar(QWidget* parent, QWidget* rootui) : QWidget(parent){
    QScreen *screen = QApplication::primaryScreen();
    int screenHeight = screen->geometry().height();
    int screenWidth = screen->geometry().width();
    int height = static_cast<int>(screenHeight*0.04);

    setObjectName("TopBar");
    layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setStyleSheet(style_topbar);
    setAutoFillBackground(true);
    setFixedHeight(height);
    
    menubar = new MenuBar();
    menubar->setFixedHeight(height);

    minimize_button = new QPushButton("__");
    minimize_button->setStyleSheet(style_minimize_button);
    minimize_button->setFixedHeight(height-2);
    minimize_button->setFixedWidth(static_cast<int>(screenWidth/20));

    close_button = new QPushButton();
    close_button->setStyleSheet(style_close_button);
    close_button->setIcon(QIcon(":/close.png"));
    close_button->setFixedHeight(height-2);
    close_button->setFixedWidth(static_cast<int>(screenWidth/20));

    if (rootui != nullptr){
        connect(close_button, &QPushButton::clicked, rootui, &QWidget::close);
    } else {
        connect(close_button, &QPushButton::clicked, &QApplication::quit);
    }
    
    layout->addWidget(menubar);
    
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout->addWidget(spacer);
    layout->addWidget(minimize_button);
    layout->addWidget(close_button);

    setLayout(layout);
}

TopBar::~TopBar(){

}