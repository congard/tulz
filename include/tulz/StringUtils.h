#ifndef TULZ_STRINGUTILS_H
#define TULZ_STRINGUTILS_H

#include <tulz/export.h>

#include <string>
#include <vector>

namespace tulz::StringUtils {
class TULZ_API Matches {
public:
    size_t pos, size;
    std::vector<std::string> matches;

    Matches(size_t pos, size_t size, const std::vector<std::string> &matches);
};

/**
 * Splits input string by delimiter
 * @param input string to split
 * @param delimiter
 * @return
 */
std::vector<std::string> TULZ_API split(const std::string &input, const std::string &delimiter);

/**
 *
 * @param src
 * @param target
 * @return
 */
std::vector<size_t> TULZ_API findAll(const std::string &src, const std::string &target);

/**
 * Replaces first found occurrence
 * @param src
 * @param target
 * @param replacement
 * @return
 */
std::string TULZ_API replace(const std::string &src, const std::string &target, const std::string &replacement);

/**
 * Replaces all found occurrences
 * @param src
 * @param target
 * @param replacement
 * @return
 */
std::string TULZ_API replaceAll(const std::string &src, const std::string &target, const std::string &replacement);

/**
 * Finds regular expression
 * @param src
 * @param regex regular expression
 * @return
 */
[[deprecated("Use https://en.cppreference.com/w/cpp/regex/regex_match instead")]]
std::vector<Matches> TULZ_API findRegex(const std::string &src, const std::string &regex, bool ignoreEmptyMatches = true);

/**
 * Checks if the specified string `str` starts with the prefix `prefix`.
 * @param str The string to check.
 * @param prefix The prefix to compare with.
 * @return `true` if `str` starts with `prefix`, `false` otherwise.
 */
[[deprecated("Use https://en.cppreference.com/w/cpp/string/basic_string/starts_with instead")]]
bool TULZ_API startsWith(std::string_view str, std::string_view prefix);
}

#endif //TULZ_STRINGUTILS_H
