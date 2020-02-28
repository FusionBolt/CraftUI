//
// Created by fusionbolt on 2020-01-25.
//

#include "ComboBox.h"

#include <utility>

GWUI::ComboBox::ComboBox():
    Widget(),
    _height(20), _width(60)
{
}

void GWUI::ComboBox::AddItems(const std::vector<std::string>& items)
{
    for(const auto& item : items)
    {
        AddItem(item);
    }
}

void GWUI::ComboBox::AddItem(const std::string &item)
{
    auto text = Text(item);
    text.SetWrapLength(_geometry.w);
    text.SetPosition({_geometry.x, static_cast<int>(_geometry.y + _height*(_items.size() + 1))});
    _items.push_back(text);
}

void GWUI::ComboBox::Draw(Renderer &renderer)
{
    Widget::Draw(renderer);

    renderer.RenderFillRectangle(_geometry, GWUI::White);
    renderer.RenderRectangle(_geometry, GWUI::Black);

    renderer.RenderFillRectangle(
            {_geometry.x + _geometry.w - _height, _geometry.y, _height, _height},
            GWUI::White);
    renderer.RenderRectangle(
            {_geometry.x + _geometry.w - _height, _geometry.y, _height, _height},
            GWUI::Black);

    _currentText.Draw(renderer);
    if (_showList)
    {
        renderer.RenderLine({_geometry.x, _geometry.y + _height},
                            {_geometry.x + _geometry.w, _geometry.y + _height});
        for(auto& item : _items)
        {
            auto t = item.GetText();
            item.Draw(renderer);
        }
    }
}

void GWUI::ComboBox::OnChanged(std::function<void(const std::string &)> f)
{
    _onChanged = std::move(f);
}

void GWUI::ComboBox::MousePressEvent(const MouseEvent &mouseEvent)
{
    Widget::MousePressEvent(mouseEvent);
    auto mousePosition = mouseEvent.GetPosition();
    if (_clickOnButtonArea(mousePosition))
    {
        if (_showList = !_showList; _showList)
        {
            _geometry.h *= static_cast<int>(_items.size() + 1);
        }
        else
        {
            _geometry.h /= static_cast<int>(_items.size() + 1);
        }
    }
    else if (_clickOnItems(mousePosition))
    {
        if (_showList)
        {
            auto index = _GetItemIndexFromPosition(mousePosition);
            auto currentText = _items[index].GetText();
            _currentText.SetText(currentText);
            std::invoke(_onChanged, currentText);
            _showList = false;
            _geometry.h /= static_cast<int>(_items.size() + 1);
        }
    }
}

GWUI::Rect GWUI::ComboBox::_GetListRectangle()
{
    auto rect = GetGeometry();
    rect.y += _height;
    rect.h = _height * static_cast<int>(_items.size());
    return rect;
}

void GWUI::ComboBox::SetGeometry(GWUI::Rect rect) noexcept
{
    Widget::SetGeometry(rect);
    _currentText.SetPosition({rect.x, rect.y});
    int index = 1;
    for(auto& item : _items)
    {
        item.SetPosition({rect.x, rect.y + index * _height});
        item.SetWrapLength(rect.w);
        index++;
    }
}

bool GWUI::ComboBox::_clickOnButtonArea(Point position)
{
    return JudgeCoincide(position, {_geometry.x + _geometry.w - _height, _geometry.y, _height, _height});
}

bool GWUI::ComboBox::_clickOnItems(GWUI::Point position)
{
    return JudgeCoincide(position, {_geometry.x, _geometry.y + _height, _geometry.w, _geometry.h - _height});
}

size_t GWUI::ComboBox::_GetItemIndexFromPosition(GWUI::Point position)
{
    return (position.y - (_geometry.y + _height)) / _height;
}
