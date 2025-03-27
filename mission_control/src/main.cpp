#include <QApplication>
#include "ui/mainui.h"
#include <QSurfaceFormat>


int main(int argc, char *argv[]) {
    // qputenv to force rendering with OpenGL. Fixes "top-level window is not using OpenGL for composition"
    // https://forum.freecad.org/viewtopic.php?t=81395
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
   
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--enable-gpu-rasterization --ignore-gpu-blocklist --enable-zero-copy --use-gl=desktop --disable-es3-gl-context");
    qputenv("QT3D_RENDERER", "opengl");
    qputenv("QSG_RHI_BACKEND", "opengl");
    

    QApplication app(argc, argv);
    MainUI window;
    window.showFullScreen();
    return app.exec();
}