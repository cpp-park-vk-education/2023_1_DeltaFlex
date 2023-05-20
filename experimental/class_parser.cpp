#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

struct ParsedClass
{
    std::string classname;
    std::vector<std::string> public_vars;
};

bool startswith(const std::string &src, const std::string substr)
{
    return src.find(substr, 0) == 0;
}

int isComa(int symbol)
{
    return symbol == ',';
}

std::vector<std::string> split(std::string &src, int(*func)(int) = isspace)
{
    std::vector<std::string> to_ret;
    size_t pos = 0;
    to_ret.push_back("");
    while (pos != src.size())
    {
        if (func(src[pos]))
        {
            to_ret.push_back("");
        }
        else
        {
            to_ret.back() += src[pos];
        }
        ++pos;
    }
    return to_ret;
}

std::string replace(std::string &src, std::string from, std::string to)
{
    std::string result;
    size_t from_size = from.size();
    size_t i;
    for (i = 0; i < src.size() - from_size + 1; ++i)
    {
        if (strncmp(src.c_str() + i, from.c_str(), from_size) == 0)
        {
            result += to;
            i += from.size();
        }
        else
        {
            result += src[i];
        }
    }
    return result;
}

std::string strip(std::string &src)
{
    if (src.size() == 0)
    {
        return "";
    }
    size_t i = 0, end = src.size() - 1;
    while (i < src.size() && isspace(src[i]))
    {
        ++i;
    }
    while (end != 0 && isspace(src[end]))
    {
        --end;
    }
    // std::cout << i << " " << end << std::endl;
    if (end <= i)
    {
        return "";
    }
    return src.substr(i, end - i + 1);
}

void CreateLoadingFunc(std::ostream &os, ParsedClass &my_class)
{
    os << "DFComponent *" << my_class.classname << "_loader(DFBinaryDeserializer &bds)" << std::endl;
    os << "{" << std::endl;
    os << "\t" << my_class.classname << " *result = new " << my_class.classname << "();" << std::endl;
    for (auto x : my_class.public_vars)
    {
        os << "\tbds.Deserialize(result->" << x << ");" << std::endl;
    }
    os << "\treturn result;" << std::endl;
    os << "}" << std::endl;
}


class DFComponentClassAnalyzer
{
private:
    std::vector<ParsedClass> m_parsed_classes;
    std::ifstream m_data_file;

public:
    DFComponentClassAnalyzer(std::string path_to_classfile)
    {
        m_data_file.open(path_to_classfile, std::ios::in);
    }

    void Analyze()
    {
        std::vector<std::string> f_lines;
        for (std::string f_string; std::getline(m_data_file, f_string); )
        {
            f_lines.emplace_back(strip(f_string));
        }

        size_t i = 0;

        while (i < f_lines.size())
        {

            if (startswith(f_lines[i], "class"))
            {
                auto splitted = split(f_lines[i]);
                if (splitted.size() <= 2 || splitted.size() > 4)
                {
                    ++i;
                    continue;
                }
                else if (splitted.size() == 3 && !startswith(splitted[2], "DFComponent"))
                {
                    ++i;
                    continue;
                }
                else if (splitted.size() == 4 && !startswith(splitted[3], "DFComponent"))
                {
                    ++i;
                    continue;
                }
                m_parsed_classes.emplace_back();
                ParsedClass &result = m_parsed_classes.back();
                result.classname = replace(splitted[1], ":", "");
                bool public_section = true;
                // std::cout << result.classname << std::endl;
                while (i < f_lines.size() && !startswith(f_lines[i], "};"))
                {
                    if (startswith(f_lines[i], "//"))
                    {
                    }
                    else if (startswith(f_lines[i], "public") || startswith(f_lines[i], "private") || startswith(f_lines[i], "protected"))
                    {
                        public_section = startswith(f_lines[i], "public");
                    }
                    else if (f_lines[i].find("(") != std::string::npos && f_lines[i].find(")") != std::string::npos)
                    {
                    }
                    else if (f_lines[i].find(";") != std::string::npos)
                    {
                        auto tmp = replace(f_lines[i], ";", "");
                        splitted = split(tmp, isComa);
                        auto type_and_first = split(splitted[0]);

                        result.public_vars.push_back(strip(type_and_first[type_and_first.size() - 1]));
                        for (size_t i = 1; i < splitted.size(); ++i)
                            result.public_vars.push_back(strip(splitted[i]));
                        // std::cout << f_lines[i] << std::endl;
                    }
                    ++i;
                }
                // CreateLoadingFunc(result);

            }
            ++i;
        }
    }

    void PrintClassLoaders(std::ostream &os)
    {
        for (auto &class_definition : m_parsed_classes)
        {
            CreateLoadingFunc(os, class_definition);
        }
    }
};

#include <filesystem>


int main(int argc, char **argv)
{
    for (const auto &dirEntry : std::filesystem::recursive_directory_iterator("./"))
    {
        if (dirEntry.is_directory() && std::string(dirEntry.path().c_str()).find(".hpp") == std::string::npos)
        {
            continue;
        }
        // std::cout << dirEntry << std::endl;
        DFComponentClassAnalyzer analyzer(dirEntry.path());
        analyzer.Analyze();
        analyzer.PrintClassLoaders(std::cout);
    }
    // DFComponentClassAnalyzer analyzer(argv[1]);
    // analyzer.Analyze();
    // analyzer.PrintClassLoaders(std::cout);
}
