#include <iostream>
#include <map>

#include "widget/Window.h"
#include "widget/ComboBox.h"
#include "widget/Label.h"
#include "utils/XMLLoad.h"
#include "widget/Button.h"
#include "units/MessageBox.h"
#include "units/Dialog.h"
#include "units/MouseCursor.h"

// TODO: lambda capture shared_ptr object by value, lifetime error??
int main()
{
    // GwUI
    // GhostWhite
    // #F8F8FF
//    Craft::System system;
    Craft::XMLLoad l("/Users/fusionbolt/CLionProjects/CraftUI/test.xml");
    l.Analysis();
    auto w = l.GetRoot<Craft::Window>();

    auto label = w->FindChild<Craft::Label>("textLabel");
    auto comboBox = w->FindChild<Craft::ComboBox>("comboBox1");
    std::weak_ptr<Craft::Label> m = label;
    // TODO: 不能捕获shared_ptr会循环饮用以及内存问题 （返回weak？
    if(label != nullptr && comboBox != nullptr)
    {
        comboBox->OnChanged([=](const std::string &nowText)
                            { label->SetText(nowText); });
    }
    w->FindChild<Craft::Button>("buttonMsgBox")->OnClicked([](bool){
        Craft::MessageBox("There is some msg", "MsgBox").Show();
    });
    w->FindChild<Craft::Button>("buttonDialog")->OnClicked([](bool){
        std::vector<Craft::DialogButtonData> v;
        v.emplace_back(0, 0, "rua");
        v.emplace_back(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Return");
        v.emplace_back(SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Escape");
        Craft::Dialog(v, Craft::MessageData("title", "message")).Show();
    });

    std::array cursorID = {SDL_SYSTEM_CURSOR_ARROW,
                    SDL_SYSTEM_CURSOR_IBEAM,
                    SDL_SYSTEM_CURSOR_WAIT,
                    SDL_SYSTEM_CURSOR_CROSSHAIR,
                    SDL_SYSTEM_CURSOR_WAITARROW,
                    SDL_SYSTEM_CURSOR_SIZENWSE,
                    SDL_SYSTEM_CURSOR_SIZENESW,
                    SDL_SYSTEM_CURSOR_SIZEWE,
                    SDL_SYSTEM_CURSOR_SIZENS,
                    SDL_SYSTEM_CURSOR_SIZEALL,
                    SDL_SYSTEM_CURSOR_NO,
                    SDL_SYSTEM_CURSOR_HAND};

    comboBox->ClearItems();
    comboBox->AddItems({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"});

    label->SetParent(w);

    comboBox->OnChanged([&](const std::string &nowText){
        Craft::MouseCursor::SetCursor(cursorID[std::stoi(nowText)]);
    });
    w->ShowAllChild();
    w->Show();
}