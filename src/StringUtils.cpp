#include <tulz/StringUtils.h>
#include <regex>

namespace tulz {
namespace StringUtils {
Matches::Matches(size_t pos, size_t size, const std::vector<std::string> &matches) {
    this->pos = pos;
    this->size = size;
    this->matches = matches;
}

std::vector<std::string> split(const std::string &_input, const std::string &delimiter) {
    std::string input = _input;
    std::vector<std::string> result;

    size_t pos = 0;
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    result.push_back(input);

    return result;
}

std::vector<size_t> findAll(const std::string &_src, const std::string &target) {
    std::string src = _src;
    std::vector<size_t> result;
    size_t pos, absolutePos = 0;

    while ((pos = src.find(target)) != std::string::npos) {
        absolutePos += pos;
        result.push_back(absolutePos);
        src.erase(0, pos + target.length());
        absolutePos += target.length();
    }

    return result;
}

std::string replace(const std::string &src, const std::string &target, const std::string &replacement) {
    std::string _src = src;
    std::size_t pos = _src.find(target);
    if (pos == std::string::npos)
        return _src;
    return _src.replace(pos, target.length(), replacement);
}

std::string replaceAll(const std::string &src, const std::string &target, const std::string &replacement) {
    std::vector<size_t> indices = findAll(src, target);
    std::string result = src;

    for (long i = static_cast<long>(indices.size()) - 1; i >= 0; --i) // long because i can be less than zero
        result.replace(indices[i], target.length(), replacement);

    return result;
}

std::vector<Matches> findRegex(const std::string &src, const std::string &_regex, const bool ignoreEmptyMatches) {
    std::vector<Matches> matches;
    std::regex regex(_regex);

    for (auto i = std::sregex_iterator(src.begin(), src.end(), regex); i != std::sregex_iterator(); ++i) {
        std::vector<std::string> strings;
        for (size_t j = 0; j < i->size(); j++) {
            if (ignoreEmptyMatches && i->operator[](j).str().empty())
                continue; // ignore empty matches
            strings.emplace_back(i->operator[](j).str());
        }

        matches.emplace_back(i->position(), i->str().size(), strings);
    }

    return matches;
}

}
}