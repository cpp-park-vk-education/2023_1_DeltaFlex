#pragma once

#include <fstream>
#include <string>
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
    void Serialize(T &data)
    {
        m_file.write((char *)&data, sizeof(T));
    }

    template <typename T>
    DFBinarySerializer &operator<<(T &data)
    {
        Serialize(data);
        return *this;
    }
};

template<>
void DFBinarySerializer::Serialize<std::string>(std::string &data)
{
    m_file.write(data.c_str(), data.size() * sizeof(char));
    char zero = 0;
    m_file.write(&zero, sizeof(char));
}