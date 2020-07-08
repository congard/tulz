#ifndef TULZ_STRINGUTILS_H
#define TULZ_STRINGUTILS_H

#include <string>
#include <vector>

namespace tulz {
namespace StringUtils {
class Matches {
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
std::vector<std::string> split(const std::string &input, const std::string &delimiter);

/**
 *
 * @param src
 * @param target
 * @return
 */
std::vector<size_t> findAll(const std::string &src, const std::string &target);

/**
 * Replaces first found occurrence
 * @param src
 * @param target
 * @param replacement
 * @return
 */
std::string replace(const std::string &src, const std::string &target, const std::string &replacement);

/**
 * Replaces all found occurrences
 * @param src
 * @param target
 * @param replacement
 * @return
 */
std::string replaceAll(const std::string &src, const std::string &target, const std::string &replacement);

/**
 * Finds regular expression
 * @param src
 * @param regex regular expression
 * @return
 */
std::vector<Matches> findRegex(const std::string &src, const std::string &regex, bool ignoreEmptyMatches = true);
}
}


#endif //TULZ_STRINGUTILS_H
