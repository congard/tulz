#include <tulz/StringUtils.h>
#include <regex>

using namespace std;

namespace tulz {
namespace StringUtils {
Matches::Matches(size_t pos, size_t size, const vector<string> &matches) {
    this->pos = pos;
    this->size = size;
    this->matches = matches;
}

vector<string> split(const string &_input, const string &delimiter) {
    string input = _input;
    vector<string> result;

    size_t pos;
    string token;

    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);

        result.push_back(token);

        input.erase(0, pos + delimiter.length());
    }

    result.push_back(input);

    return result;
}

vector<size_t> findAll(const string &_src, const string &target) {
    string src = _src;
    vector<size_t> result;
    size_t pos, absolutePos = 0;

    while ((pos = src.find(target)) != string::npos) {
        absolutePos += pos;

        result.push_back(absolutePos);

        src.erase(0, pos + target.length());

        absolutePos += target.length();
    }

    return result;
}

string replace(const string &src, const string &target, const string &replacement) {
    string _src = src;
    size_t pos = _src.find(target);

    if (pos == string::npos) {
        return _src;
    }

    return _src.replace(pos, target.length(), replacement);
}

string replaceAll(const string &src, const string &target, const string &replacement) {
    vector<size_t> indices = findAll(src, target);
    string result = src;

    for (long i = static_cast<long>(indices.size()) - 1; i >= 0; --i) {// long because i can be less than zero
        result.replace(indices[i], target.length(), replacement);
    }

    return result;
}

vector<Matches> findRegex(const string &src, const string &_regex, bool ignoreEmptyMatches) {
    vector<Matches> matches;
    regex regex(_regex);

    for (auto i = sregex_iterator(src.begin(), src.end(), regex); i != sregex_iterator(); ++i) {
        vector<string> strings;

        for (size_t j = 0; j < i->size(); j++) {
            if (ignoreEmptyMatches && i->operator[](j).str().empty()) {
                continue; // ignore empty matches
            }

            strings.emplace_back(i->operator[](j).str());
        }

        matches.emplace_back(i->position(), i->str().size(), strings);
    }

    return matches;
}
}
}