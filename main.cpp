#include <iostream>
#include <map>

#include "widget/Window.h"
#include "core/System.hpp"
#include "pugixml.hpp"
#include "widget/ComboBox.h"
#include "widget/Label.h"
#include "utils/XMLLoad.h"
#include "widget/Button.h"
#include "units/MessageBox.h"
#include "units/Dialog.h"

int main()
{
    // GhostWhite
    // #F8F8FF
    GWUI::System system;
    GWUI::XMLLoad l("/Users/fusionbolt/CLionProjects/GWUI/test.xml");
    l.Analysis();
    auto w = l.GetRoot<GWUI::Window>();

    auto label = w->FindChild<GWUI::Label>("textLabel");
    auto comboBox = w->FindChild<GWUI::ComboBox>("comboBox1");

    if(label != nullptr && comboBox != nullptr)
    {
        comboBox->OnChanged([=](const std::string &nowText)
                            { label->SetText(nowText); });
    }
    w->FindChild<GWUI::Button>("buttonMsgBox")->OnClicked([](bool){
        GWUI::MessageBox("There is some msg", "MsgBox").Show();
    });
    w->FindChild<GWUI::Button>("buttonDialog")->OnClicked([](bool){
        GWUI::Dialog().Show();
    });

    //TODO: 多级控件事件分发
    // w->ShowAllChild();
    w->Show();
}