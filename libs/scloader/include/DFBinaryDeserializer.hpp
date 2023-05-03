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
    T Deserialize()
    {
        T data;
        m_file.read((char *)&data, sizeof(T));
        return data;
    }
};

template<>
std::string DFBinaryDeserializer::Deserialize()
{
    std::string to_ret;
    char cur_char;
    m_file.read(&cur_char, sizeof(char));
    while (cur_char != '\0')
    {
        to_ret += cur_char;
        m_file.read(&cur_char, sizeof(char));
    }
    return to_ret;
}