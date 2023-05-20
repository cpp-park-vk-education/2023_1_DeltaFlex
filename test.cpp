#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <DFvec2.hpp>
class DFBinarySerializer
{
private:
    std::ofstream m_file;

public:
    DFBinarySerializer(const std::string path)
    {
        m_file.open(path, std::ios::binary | std::ios::out);
    }

    template <typename T>
    void Serialize(const T &data)
    {
        m_file.write((char *)&data, sizeof(T));
    }

    template <typename T>
    DFBinarySerializer &operator<<(const T &data)
    {
        Serialize(data);
        return *this;
    }
};

template<>
void DFBinarySerializer::Serialize<std::string>(const std::string &data)
{
    m_file.write(data.c_str(), data.size() * sizeof(char));
    char zero = 0;
    m_file.write(&zero, sizeof(char));
}

int main()
{
    DFBinarySerializer test("./mentis_bellum/test.scene");
    test << 4ul;
    test << "Background" << Vector2<float>(0, 0) << 1ul;
    test << "MainMenuBack"
        << "./resources/images/main-menu.png";

    test << "StartGameButton" << Vector2<float>(1280 / 2, 720  * 1.5 / 3) << 1ul;
    test << "MainMenuPlay"
        << "./resources/images/menu-play.png"
        //     << "./resources/images/start_game_inactive.png"
        << Vector2<float>(226 / 2, 74 / 2);

    test << "OptionsButton" << Vector2<float>(1280 / 2, 720 * 2 / 3) << 1ul;
    test << "MainMenuOptions"
        << "./resources/images/menu-options.png"
        //     << "./resources/images/start_game_inactive.png"
        << Vector2<float>(409 / 2, 76 / 2);

    test << "ExitButton" << Vector2<float>(1280 / 2, 720 * 2.5 / 3) << 1ul;
    test << "MainMenuExit"
        << "./resources/images/menu-exit.png"
        //     << "./resources/images/start_game_inactive.png"
        << Vector2<float>(202 / 2, 69 / 2);

    return 0;
}