//
// Created by fusionbolt on 2020-01-25.
//

#include "ComboBox.h"

#include <utility>

GWUI::ComboBox::ComboBox():
    Widget(),
    _height(20),
    _mainRectangle(Rect{100, 250, 60, _height}),
    _buttonRectangle(Rect{140, 250, 20, _height}),
    _listRectangle(Rect{100, 270, 60, _height}),
    _currentStringIndex(0),
    _currentText("M", 20, {0, 0, 0, 0}),
    _showList(false)
{
    _currentText.SetPosition({100, 250});
    _items.push_back(_currentText);
    _items[0].SetPosition({100, 270});

    // TODO:bug
    SetGeometry(_mainRectangle.GetRect());
}

void GWUI::ComboBox::AddItems(const std::vector<std::string>& items)
{
    for(const auto& item : items)
    {
        auto text = Text(item, 20,{0,0,0,0}, 40);
        text.SetPosition({100, static_cast<int>(250 + _height*(_items.size() + 1))});
        _items.push_back(text);
    }
    _listRectangle.SetRect({100, 270, 60, static_cast<int>(_items.size() * _height)});
}

void GWUI::ComboBox::AddItem(const std::string &item)
{
    AddItems({item});
}

void GWUI::ComboBox::AddItem(std::string &&item)
{
    _items.emplace_back(item);
    _listRectangle.SetRect({100, 270, 60, static_cast<int>(_items.size() * _height)});
}

void GWUI::ComboBox::Draw(Renderer renderer)
{
    // main 和 button 分开还是合在一起
    _mainRectangle.Draw(renderer);
    _buttonRectangle.Draw(renderer);
    _currentText.Draw(renderer);
    if(_showList)
    {
        _listRectangle.Draw(renderer);
        for(auto& text : _items)
        {
            text.Draw(renderer);
        }
    }
    Widget::Draw(renderer);
}


void GWUI::ComboBox::OnChanged(std::function<void(const std::string &)> f)
{
    _onChanged = std::move(f);
}

void GWUI::ComboBox::MousePressEvent(const MouseEvent &mouseEvent)
{
    auto mousePosition = mouseEvent.GetPosition();
    if(JudgeCoincide(mousePosition, _buttonRectangle.GetRect()))
    {
        _showList = !_showList;

        if(_showList)
        {
            auto rect = GetGeometry();
            rect.h = _height * _listRectangle.GetRect().h;
            SetGeometry(rect);
        }
        else
        {
            auto rect = GetGeometry();
            rect.h = _height;
            SetGeometry(rect);
        }
    }
    if(_showList)
    {
        if (JudgeCoincide(mousePosition, _listRectangle.GetRect()))
        {
            auto index = (mousePosition.y - _listRectangle.GetRect().y) / _height;
            auto currentText = _items.at(index).GetText();
            _currentText.SetText(currentText);
            try
            {
                std::invoke(_onChanged, currentText);
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
            _showList = false;
        }
    }
    Widget::MousePressEvent(mouseEvent);
}
