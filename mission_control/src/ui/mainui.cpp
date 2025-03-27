#include "ui/mainui.h"
#include <QJsonDocument>
#include <QFile>
#include <QIODevice>

QString mainui_style = R"(
    background-color: #1F1F1F; margin:0px; padding:0px;
)";

MainUI::MainUI(QWidget* parent) : QWidget(parent){
    setStyleSheet(mainui_style);
    setWindowTitle("Mission Control v5.0");
    setWindowFlags(Qt::FramelessWindowHint);

    // load config

    QFile file(":config.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Missing config.json file";
    }
    
    QByteArray data = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    config = doc.object();

    // init UI elements

    topbar = new TopBar();
    sidebar = new SideBar();
    tabbar = new TabBar();
    maintab = new MainTab();
    flightdisp = new FlightDisplay();
    map = new MapView(nullptr, config.value("GOOGLE_MAPS_API_KEY").toString());
    tabbar->addTab(maintab, "Mission Control");

    QVBoxLayout* layout = new QVBoxLayout();

    QHBoxLayout* row2 = new QHBoxLayout(); 
    QVBoxLayout* row2col1 = new QVBoxLayout();  
    row2col1->addWidget(map); 
    row2col1->addWidget(flightdisp);
    row2->addWidget(sidebar);
    row2->addLayout(row2col1);
    row2->addWidget(tabbar);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(topbar);
    layout->addLayout(row2);

    setLayout(layout);
}

MainUI::~MainUI() {

}