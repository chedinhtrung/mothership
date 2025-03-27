#include "ui/mapview.h"
#include <QSurfaceFormat>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QWebEngineSettings>

MapView::MapView(QWidget* parent, QString map_api_key) : QWebEngineView(parent){
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    setZoomFactor(0.5);

    QString html = loadHtml(map_api_key);
    QUrl base_url = QUrl::fromLocalFile("C:/Users/steve/OneDrive/Desktop/mothership/mission_control/resources/googlemaps.html");
    setHtml(html);
    //load(QUrl::fromLocalFile("C:/Users/steve/OneDrive/Desktop/mothership/mission_control/resources/googlemaps.html"));
}

MapView::~MapView(){

}

QString MapView::loadHtml(QString map_api_key) {
    QFile file(":googlemaps.html");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open googlemaps.html";
        return "";
    }

    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();
    return htmlContent.replace("{{API_KEY}}", map_api_key);
}