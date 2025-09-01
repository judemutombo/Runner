#include "../includes/Gui.h"
#include "../includes/data.h"


Gui::Gui() : menuStage(MenuStage::MainMenu)
{
    font = LoadFontEx("ressources/font/monogram.ttf", 64, 0, 0);
    menuBackground = LoadTexture("ressources/textures/menu.png");

    joinServerButton = new  Button("Join Server", {SCREEN_WIDTH * 0.05 , SCREEN_HEIGHT * 0.45}, {250, 60}, Data::tilesColors()[2], WHITE);
    joinServerButton->setAction(std::bind(&Gui::joinServer, this));

    settingsButton = new  Button("Settings", {SCREEN_WIDTH * 0.05 , SCREEN_HEIGHT * 0.55}, {250, 60}, Data::tilesColors()[2], WHITE);
    settingsButton->setAction(std::bind(&Gui::settings, this));

    quitButton = new Button("Quit", {SCREEN_WIDTH * 0.05 , SCREEN_HEIGHT * 0.65}, {250, 60}, Data::tilesColors()[2], WHITE);
    quitButton->setAction(std::bind(&Gui::quitGame, this));
}

Gui::~Gui()
{
    UnloadTexture(menuBackground);
    UnloadFont(font);
    delete joinServerButton;
    delete quitButton;
    delete settingsButton;
}

void Gui::draw(){
    if(!onGoing){
        switch (menuStage)
        {
        case MenuStage::MainMenu :
                DrawTexturePro(menuBackground, {0, 0, (float)menuBackground.width, (float)menuBackground.height}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, {0, 0}, 0, WHITE);
                settingsButton->draw();
                joinServerButton->draw();
                quitButton->draw();
            break;
        case MenuStage::JoinMenu : 

            break;
        default:
            break;
        }
    }
}

void Gui::setPause(bool p)
{
    this->pause = p;
}

void Gui::setOngoing(bool og)
{
    this->onGoing = og;
}

void Gui::settings(){

}

void Gui::joinServer(){
    onRequestPartyTriggered.emit(true);
}

void Gui::quitGame(){

}