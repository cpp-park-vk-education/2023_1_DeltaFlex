#pragma once

#include <fstream>
#include <string>

class DFBinaryDeserializer
{
private:
    std::ifstream m_file;

public:
    DFBinaryDeserializer(const std::string path)
    {
        m_file.open(path, std::ios::binary | std::ios::in);
    }

    template <typename T>
    void Deserialize(T &data)
    {
        m_file.read((char *)&data, sizeof(T));
    }

    template <typename T>
    DFBinaryDeserializer &operator>>(T &data)
    {
        Deserialize(data);
        return *this;
    }
};

template<>
void DFBinaryDeserializer::Deserialize(std::string &data)
{
    char cur_char;
    m_file.read(&cur_char, sizeof(char));
    while (cur_char != '\0')
    {
        data += cur_char;
        m_file.read(&cur_char, sizeof(char));
    }
}