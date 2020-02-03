//
// Created by fusionbolt on 2020-01-28.
//

#ifndef GWUI_IMAGE_H
#define GWUI_IMAGE_H

#include <string>

#include "../utils/Util.hpp"

namespace GWUI
{
    class Image
    {
    public:
        explicit Image(const std::string& path = "");

        void Draw(Renderer renderer);

        void SetRect(Rect rect);

        void SetPath(const std::string& path);
    private:
        std::string _imgPath;

        std::shared_ptr<SDL_Texture> _imgTexture;

        Rect _rect;
    };
}

#endif //GWUI_IMAGE_H
