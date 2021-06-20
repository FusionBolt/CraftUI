//
// Created by fusionbolt on 2020-01-28.
//

#include "Label.h"

Craft::Label::Label(std::string text) : Widget(), _text(std::move(text))
{

}

Craft::Label::Label(Craft::Image img): _img(std::move(img)), _isImg(true)
{

}

void Craft::Label::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);
    _text.Draw(renderer);
    if (_isImg)
    {
        _img.Draw(renderer, _geometry);
    }
}

void Craft::Label::SetFontSize(uint16_t size)
{
    _text.SetFontSize(size);
}

void Craft::Label::SetPosition(Craft::Point position)
{
    _text.SetPosition(position);
    SetGeometry({position.x, position.y, 0, 0});
}

void Craft::Label::SetFontColor(Craft::Color color)
{
    _text.SetColor(color);
}

void Craft::Label::SetText(const std::string &text)
{
    _text.SetText(text);
}

void Craft::Label::SetPicture(Image img)
{
    _img = std::move(img);
    _isImg = true;
}

void Craft::Label::SetGeometry(Craft::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _text.SetPosition({rect.x, rect.y});
}
