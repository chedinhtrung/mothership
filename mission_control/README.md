## Mission Control App

This repo contains the ***Windows*** source code for the Mission Control App. For Linux please see the branch `official-linux-missionctl`.

Dependency: 
- Qt6
- Qt6 WebEngineWidgets
- Qt6 OpenGLWidgets
- OpenGL for Windowss

Application must be built using the MSVC compiler (damn it!) because Qt WebEngineWidget is used to render google maps. WebEngineWidget is only available on MSVC.

Some Windows-only annoying things: 
- The build tool is Nmake, not your usual make or ninja (ships with MSVC)
-

