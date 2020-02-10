//
// Created by fusionbolt on 2020-01-28.
//

#include "Label.h"

GWUI::Label::Label(const std::string &text) : Widget(), _text(text)
{

}

void GWUI::Label::Draw(GWUI::Renderer renderer)
{
    Widget::Draw(renderer);
    _text.Draw(renderer);
    if(_isImg)
    {
        _img.Draw(renderer);
    }
}

void GWUI::Label::SetFontSize(uint16_t size)
{
    _text.SetFontSize(size);
}

void GWUI::Label::SetPosition(GWUI::Point position)
{
    _text.SetPosition(position);
    SetGeometry({position.x, position.y, 0, 0});
}

void GWUI::Label::SetFontColor(GWUI::Color color)
{
    _text.SetColor(color);
}

void GWUI::Label::SetText(const std::string &text)
{
    _text.SetText(text);
}

void GWUI::Label::SetPicture(const std::string &path, Rect rect)
{
    _img.SetPath(path);
    _img.SetRect(rect);
    _isImg = true;
}
