#ifndef TULZ_LOCALEINFO_H
#define TULZ_LOCALEINFO_H

#include <list>

namespace tulz {
/**
 * Platform independent (Linux/Windows) locale info
 * <br>
 * Using this class you can obtain platform independent
 * ISO 639 alpha-2 code of user's language and country
 * <br>
 * Also you can obtain info such as the country name and
 * the list of languages with the same ISO code you specified
 */
class LocaleInfo {
public:
    struct _info {
        const char *value;
        const char *code;
    };

    using LanguageInfo = _info;
    using CountryInfo = _info;

    struct Info {
        std::list<const char*> languages;
        const char *languageCode;
        const char *country;
        const char *countryCode;
        const char *error {nullptr};
    };

public:
    static Info get(const char *locale);

    static const LanguageInfo languageInfo[];
    static const CountryInfo countryInfo[];

    static const int languagesCount;
    static const int countiesCount;
};
}

#endif //TULZ_LOCALEINFO_H
