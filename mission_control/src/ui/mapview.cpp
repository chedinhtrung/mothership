#include "ui/mapview.h"
#include <QSurfaceFormat>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QWebEngineSettings>
#include <QTimer>

MapView::MapView(QWidget* parent, QString map_api_key) : QWebEngineView(parent){
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, true);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    setZoomFactor(0.7);

    QString html = loadHtml(map_api_key);
    setHtml(html);

    // test function
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MapView::onTestUpdate);
    timer->start(150);
}

void MapView::onTestUpdate(){
    static float lon, lat, head = 0.0;
    lon += 0.001;
    lat += 0.001;
    head += 1;
    updateLocation(lon, lat, head);
}

MapView::~MapView(){

}

void MapView::updateLocation(float lon, float lat, float heading){
    char buf[50];
    sprintf(buf, "update_location(%f, %f, %f)", lon, lat, heading);
    QString JSCall = QString(buf);
    page()->runJavaScript(JSCall);
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