//
// Created by fusionbolt on 2020-01-28.
//

#include "Label.h"

GWUI::Label::Label(std::string text) : Widget(), _text(std::move(text))
{

}

GWUI::Label::Label(GWUI::Image img):_img(std::move(img)), _isImg(true)
{

}

void GWUI::Label::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    _text.Draw(renderer);
    if(_isImg)
    {
        _img.Draw(renderer, _geometry);
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

void GWUI::Label::SetPicture(Image img)
{
    _img = std::move(img);
    _isImg = true;
}

void GWUI::Label::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _text.SetPosition({rect.x, rect.y});
}
