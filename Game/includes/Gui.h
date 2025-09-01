#include "Button.h"
#include "config.h"
#include "Signal/Signal.h"

enum MenuStage{
    MainMenu,
    PauseMenu,
    SettingsMenu,
    JoinMenu,
    GameMenu
};

class Gui
{
private:
    Button *joinServerButton;
    Button *settingsButton;
    Button *quitButton;

    Texture2D menuBackground;
    Font font;

    void joinServer();
    void settings();
    void quitGame();

    bool onGoing;
    bool pause;

    MenuStage menuStage;

public:
    Gui(/* args */);
    ~Gui();
    void draw();

    void setPause(bool p);
    void setOngoing(bool og);

    Signal<bool> onRequestPartyTriggered;
};


