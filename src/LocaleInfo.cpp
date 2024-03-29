#include <tulz/LocaleInfo.h>

#include <cstring>
#include <cstdio>

// Data from https://datahub.io/core/language-codes and https://datahub.io/core/country-list

namespace tulz {
const LocaleInfo::LanguageInfo LocaleInfo::languageInfo[] = {
        {"Afar", "aa"},
        {"Abkhazian", "ab"},
        {"Avestan", "ae"},
        {"Afrikaans", "af"},
        {"Akan", "ak"},
        {"Amharic", "am"},
        {"Aragonese", "an"},
        {"Arabic", "ar"},
        {"Assamese", "as"},
        {"Avaric", "av"},
        {"Aymara", "ay"},
        {"Azerbaijani", "az"},
        {"Bashkir", "ba"},
        {"Belarusian", "be"},
        {"Bulgarian", "bg"},
        {"Bihari languages", "bh"},
        {"Bislama", "bi"},
        {"Bambara", "bm"},
        {"Bengali", "bn"},
        {"Tibetan", "bo"},
        {"Breton", "br"},
        {"Bosnian", "bs"},
        {"Catalan", "ca"},
        {"Valencian", "ca"},
        {"Chechen", "ce"},
        {"Chamorro", "ch"},
        {"Corsican", "co"},
        {"Cree", "cr"},
        {"Czech", "cs"},
        {"Church Slavic", "cu"},
        {"Old Slavonic", "cu"},
        {"Church Slavonic", "cu"},
        {"Old Bulgarian", "cu"},
        {"Old Church Slavonic", "cu"},
        {"Chuvash", "cv"},
        {"Welsh", "cy"},
        {"Danish", "da"},
        {"German", "de"},
        {"Divehi", "dv"},
        {"Dhivehi", "dv"},
        {"Maldivian", "dv"},
        {"Dzongkha", "dz"},
        {"Ewe", "ee"},
        {"Greek", "el"},
        {"English", "en"},
        {"Esperanto", "eo"},
        {"Spanish", "es"},
        {"Castilian", "es"},
        {"Estonian", "et"},
        {"Basque", "eu"},
        {"Persian", "fa"},
        {"Fulah", "ff"},
        {"Finnish", "fi"},
        {"Fijian", "fj"},
        {"Faroese", "fo"},
        {"French", "fr"},
        {"Western Frisian", "fy"},
        {"Irish", "ga"},
        {"Gaelic", "gd"},
        {"Scottish Gaelic", "gd"},
        {"Galician", "gl"},
        {"Guarani", "gn"},
        {"Gujarati", "gu"},
        {"Manx", "gv"},
        {"Hausa", "ha"},
        {"Hebrew", "he"},
        {"Hindi", "hi"},
        {"Hiri Motu", "ho"},
        {"Croatian", "hr"},
        {"Haitian", "ht"},
        {"Haitian Creole", "ht"},
        {"Hungarian", "hu"},
        {"Armenian", "hy"},
        {"Herero", "hz"},
        {"Interlingua", "ia"},
        {"Indonesian", "id"},
        {"Interlingue", "ie"},
        {"Occidental", "ie"},
        {"Igbo", "ig"},
        {"Sichuan Yi", "ii"},
        {"Nuosu", "ii"},
        {"Inupiaq", "ik"},
        {"Ido", "io"},
        {"Icelandic", "is"},
        {"Italian", "it"},
        {"Inuktitut", "iu"},
        {"Japanese", "ja"},
        {"Javanese", "jv"},
        {"Georgian", "ka"},
        {"Kongo", "kg"},
        {"Kikuyu", "ki"},
        {"Gikuyu", "ki"},
        {"Kuanyama", "kj"},
        {"Kwanyama", "kj"},
        {"Kazakh", "kk"},
        {"Kalaallisut", "kl"},
        {"Greenlandic", "kl"},
        {"Central Khmer", "km"},
        {"Kannada", "kn"},
        {"Korean", "ko"},
        {"Kanuri", "kr"},
        {"Kashmiri", "ks"},
        {"Kurdish", "ku"},
        {"Komi", "kv"},
        {"Cornish", "kw"},
        {"Kirghiz", "ky"},
        {"Kyrgyz", "ky"},
        {"Latin", "la"},
        {"Luxembourgish", "lb"},
        {"Letzeburgesch", "lb"},
        {"Ganda", "lg"},
        {"Limburgan", "li"},
        {"Limburger", "li"},
        {"Limburgish", "li"},
        {"Lingala", "ln"},
        {"Lao", "lo"},
        {"Lithuanian", "lt"},
        {"Luba-Katanga", "lu"},
        {"Latvian", "lv"},
        {"Malagasy", "mg"},
        {"Marshallese", "mh"},
        {"Maori", "mi"},
        {"Macedonian", "mk"},
        {"Malayalam", "ml"},
        {"Mongolian", "mn"},
        {"Marathi", "mr"},
        {"Malay", "ms"},
        {"Maltese", "mt"},
        {"Burmese", "my"},
        {"Nauru", "na"},
        {"Bokmål", "nb"},
        {"Norwegian", "nb"},
        {"Norwegian Bokmål", "nb"},
        {"Ndebele", "nd"},
        {"North", "nd"},
        {"North Ndebele", "nd"},
        {"Nepali", "ne"},
        {"Ndonga", "ng"},
        {"Dutch", "nl"},
        {"Flemish", "nl"},
        {"Norwegian Nynorsk", "nn"},
        {"Nynorsk", "nn"},
        {"Norwegian", "nn"},
        {"Norwegian", "no"},
        {"Ndebele", "nr"},
        {"South", "nr"},
        {"South Ndebele", "nr"},
        {"Navajo", "nv"},
        {"Navaho", "nv"},
        {"Chichewa", "ny"},
        {"Chewa", "ny"},
        {"Nyanja", "ny"},
        {"Occitan", "oc"},
        {"Ojibwa", "oj"},
        {"Oromo", "om"},
        {"Oriya", "or"},
        {"Ossetian", "os"},
        {"Ossetic", "os"},
        {"Panjabi", "pa"},
        {"Punjabi", "pa"},
        {"Pali", "pi"},
        {"Polish", "pl"},
        {"Pushto", "ps"},
        {"Pashto", "ps"},
        {"Portuguese", "pt"},
        {"Quechua", "qu"},
        {"Romansh", "rm"},
        {"Rundi", "rn"},
        {"Romanian", "ro"},
        {"Moldavian", "ro"},
        {"Moldovan", "ro"},
        {"Russian", "ru"},
        {"Kinyarwanda", "rw"},
        {"Sanskrit", "sa"},
        {"Sardinian", "sc"},
        {"Sindhi", "sd"},
        {"Northern Sami", "se"},
        {"Sango", "sg"},
        {"Sinhala", "si"},
        {"Sinhalese", "si"},
        {"Slovak", "sk"},
        {"Slovenian", "sl"},
        {"Samoan", "sm"},
        {"Shona", "sn"},
        {"Somali", "so"},
        {"Albanian", "sq"},
        {"Serbian", "sr"},
        {"Swati", "ss"},
        {"Sotho", "st"},
        {"Southern", "st"},
        {"Sundanese", "su"},
        {"Swedish", "sv"},
        {"Swahili", "sw"},
        {"Tamil", "ta"},
        {"Telugu", "te"},
        {"Tajik", "tg"},
        {"Thai", "th"},
        {"Tigrinya", "ti"},
        {"Turkmen", "tk"},
        {"Tagalog", "tl"},
        {"Tswana", "tn"},
        {"Tonga (Tonga Islands)", "to"},
        {"Turkish", "tr"},
        {"Tsonga", "ts"},
        {"Tatar", "tt"},
        {"Twi", "tw"},
        {"Tahitian", "ty"},
        {"Uighur", "ug"},
        {"Uyghur", "ug"},
        {"Ukrainian", "uk"},
        {"Urdu", "ur"},
        {"Uzbek", "uz"},
        {"Venda", "ve"},
        {"Vietnamese", "vi"},
        {"Volapük", "vo"},
        {"Walloon", "wa"},
        {"Wolof", "wo"},
        {"Xhosa", "xh"},
        {"Yiddish", "yi"},
        {"Yoruba", "yo"},
        {"Zhuang", "za"},
        {"Chuang", "za"},
        {"Chinese", "zh"},
        {"Zulu", "zu"}
};

const LocaleInfo::CountryInfo LocaleInfo::countryInfo[] = {
        {"Afghanistan", "AF"},
        {"Åland Islands", "AX"},
        {"Albania", "AL"},
        {"Algeria", "DZ"},
        {"American Samoa", "AS"},
        {"Andorra", "AD"},
        {"Angola", "AO"},
        {"Anguilla", "AI"},
        {"Antarctica", "AQ"},
        {"Antigua and Barbuda", "AG"},
        {"Argentina", "AR"},
        {"Armenia", "AM"},
        {"Aruba", "AW"},
        {"Australia", "AU"},
        {"Austria", "AT"},
        {"Azerbaijan", "AZ"},
        {"Bahamas", "BS"},
        {"Bahrain", "BH"},
        {"Bangladesh", "BD"},
        {"Barbados", "BB"},
        {"Belarus", "BY"},
        {"Belgium", "BE"},
        {"Belize", "BZ"},
        {"Benin", "BJ"},
        {"Bermuda", "BM"},
        {"Bhutan", "BT"},
        {"Bolivia, Plurinational State of", "BO"},
        {"Bonaire, Sint Eustatius and Saba", "BQ"},
        {"Bosnia and Herzegovina", "BA"},
        {"Botswana", "BW"},
        {"Bouvet Island", "BV"},
        {"Brazil", "BR"},
        {"British Indian Ocean Territory", "IO"},
        {"Brunei Darussalam", "BN"},
        {"Bulgaria", "BG"},
        {"Burkina Faso", "BF"},
        {"Burundi", "BI"},
        {"Cambodia", "KH"},
        {"Cameroon", "CM"},
        {"Canada", "CA"},
        {"Cape Verde", "CV"},
        {"Cayman Islands", "KY"},
        {"Central African Republic", "CF"},
        {"Chad", "TD"},
        {"Chile", "CL"},
        {"China", "CN"},
        {"Christmas Island", "CX"},
        {"Cocos (Keeling) Islands", "CC"},
        {"Colombia", "CO"},
        {"Comoros", "KM"},
        {"Congo", "CG"},
        {"Congo, the Democratic Republic of the", "CD"},
        {"Cook Islands", "CK"},
        {"Costa Rica", "CR"},
        {"Côte d'Ivoire", "CI"},
        {"Croatia", "HR"},
        {"Cuba", "CU"},
        {"Curaçao", "CW"},
        {"Cyprus", "CY"},
        {"Czech Republic", "CZ"},
        {"Denmark", "DK"},
        {"Djibouti", "DJ"},
        {"Dominica", "DM"},
        {"Dominican Republic", "DO"},
        {"Ecuador", "EC"},
        {"Egypt", "EG"},
        {"El Salvador", "SV"},
        {"Equatorial Guinea", "GQ"},
        {"Eritrea", "ER"},
        {"Estonia", "EE"},
        {"Ethiopia", "ET"},
        {"Falkland Islands (Malvinas)", "FK"},
        {"Faroe Islands", "FO"},
        {"Fiji", "FJ"},
        {"Finland", "FI"},
        {"France", "FR"},
        {"French Guiana", "GF"},
        {"French Polynesia", "PF"},
        {"French Southern Territories", "TF"},
        {"Gabon", "GA"},
        {"Gambia", "GM"},
        {"Georgia", "GE"},
        {"Germany", "DE"},
        {"Ghana", "GH"},
        {"Gibraltar", "GI"},
        {"Greece", "GR"},
        {"Greenland", "GL"},
        {"Grenada", "GD"},
        {"Guadeloupe", "GP"},
        {"Guam", "GU"},
        {"Guatemala", "GT"},
        {"Guernsey", "GG"},
        {"Guinea", "GN"},
        {"Guinea-Bissau", "GW"},
        {"Guyana", "GY"},
        {"Haiti", "HT"},
        {"Heard Island and McDonald Islands", "HM"},
        {"Holy See (Vatican City State)", "VA"},
        {"Honduras", "HN"},
        {"Hong Kong", "HK"},
        {"Hungary", "HU"},
        {"Iceland", "IS"},
        {"India", "IN"},
        {"Indonesia", "ID"},
        {"Iran, Islamic Republic of", "IR"},
        {"Iraq", "IQ"},
        {"Ireland", "IE"},
        {"Isle of Man", "IM"},
        {"Israel", "IL"},
        {"Italy", "IT"},
        {"Jamaica", "JM"},
        {"Japan", "JP"},
        {"Jersey", "JE"},
        {"Jordan", "JO"},
        {"Kazakhstan", "KZ"},
        {"Kenya", "KE"},
        {"Kiribati", "KI"},
        {"Korea, Democratic People's Republic of", "KP"},
        {"Korea, Republic of", "KR"},
        {"Kuwait", "KW"},
        {"Kyrgyzstan", "KG"},
        {"Lao People's Democratic Republic", "LA"},
        {"Latvia", "LV"},
        {"Lebanon", "LB"},
        {"Lesotho", "LS"},
        {"Liberia", "LR"},
        {"Libya", "LY"},
        {"Liechtenstein", "LI"},
        {"Lithuania", "LT"},
        {"Luxembourg", "LU"},
        {"Macao", "MO"},
        {"Macedonia, the Former Yugoslav Republic of", "MK"},
        {"Madagascar", "MG"},
        {"Malawi", "MW"},
        {"Malaysia", "MY"},
        {"Maldives", "MV"},
        {"Mali", "ML"},
        {"Malta", "MT"},
        {"Marshall Islands", "MH"},
        {"Martinique", "MQ"},
        {"Mauritania", "MR"},
        {"Mauritius", "MU"},
        {"Mayotte", "YT"},
        {"Mexico", "MX"},
        {"Micronesia, Federated States of", "FM"},
        {"Moldova, Republic of", "MD"},
        {"Monaco", "MC"},
        {"Mongolia", "MN"},
        {"Montenegro", "ME"},
        {"Montserrat", "MS"},
        {"Morocco", "MA"},
        {"Mozambique", "MZ"},
        {"Myanmar", "MM"},
        {"Namibia", "NA"},
        {"Nauru", "NR"},
        {"Nepal", "NP"},
        {"Netherlands", "NL"},
        {"New Caledonia", "NC"},
        {"New Zealand", "NZ"},
        {"Nicaragua", "NI"},
        {"Niger", "NE"},
        {"Nigeria", "NG"},
        {"Niue", "NU"},
        {"Norfolk Island", "NF"},
        {"Northern Mariana Islands", "MP"},
        {"Norway", "NO"},
        {"Oman", "OM"},
        {"Pakistan", "PK"},
        {"Palau", "PW"},
        {"Palestine, State of", "PS"},
        {"Panama", "PA"},
        {"Papua New Guinea", "PG"},
        {"Paraguay", "PY"},
        {"Peru", "PE"},
        {"Philippines", "PH"},
        {"Pitcairn", "PN"},
        {"Poland", "PL"},
        {"Portugal", "PT"},
        {"Puerto Rico", "PR"},
        {"Qatar", "QA"},
        {"Réunion", "RE"},
        {"Romania", "RO"},
        {"Russian Federation", "RU"},
        {"Rwanda", "RW"},
        {"Saint Barthélemy", "BL"},
        {"Saint Helena, Ascension and Tristan da Cunha", "SH"},
        {"Saint Kitts and Nevis", "KN"},
        {"Saint Lucia", "LC"},
        {"Saint Martin (French part)", "MF"},
        {"Saint Pierre and Miquelon", "PM"},
        {"Saint Vincent and the Grenadines", "VC"},
        {"Samoa", "WS"},
        {"San Marino", "SM"},
        {"Sao Tome and Principe", "ST"},
        {"Saudi Arabia", "SA"},
        {"Senegal", "SN"},
        {"Serbia", "RS"},
        {"Seychelles", "SC"},
        {"Sierra Leone", "SL"},
        {"Singapore", "SG"},
        {"Sint Maarten (Dutch part)", "SX"},
        {"Slovakia", "SK"},
        {"Slovenia", "SI"},
        {"Solomon Islands", "SB"},
        {"Somalia", "SO"},
        {"South Africa", "ZA"},
        {"South Georgia and the South Sandwich Islands", "GS"},
        {"South Sudan", "SS"},
        {"Spain", "ES"},
        {"Sri Lanka", "LK"},
        {"Sudan", "SD"},
        {"Suriname", "SR"},
        {"Svalbard and Jan Mayen", "SJ"},
        {"Swaziland", "SZ"},
        {"Sweden", "SE"},
        {"Switzerland", "CH"},
        {"Syrian Arab Republic", "SY"},
        {"Taiwan, Province of China", "TW"},
        {"Tajikistan", "TJ"},
        {"Tanzania, United Republic of", "TZ"},
        {"Thailand", "TH"},
        {"Timor-Leste", "TL"},
        {"Togo", "TG"},
        {"Tokelau", "TK"},
        {"Tonga", "TO"},
        {"Trinidad and Tobago", "TT"},
        {"Tunisia", "TN"},
        {"Turkey", "TR"},
        {"Turkmenistan", "TM"},
        {"Turks and Caicos Islands", "TC"},
        {"Tuvalu", "TV"},
        {"Uganda", "UG"},
        {"Ukraine", "UA"},
        {"United Arab Emirates", "AE"},
        {"United Kingdom", "GB"},
        {"United States", "US"},
        {"United States Minor Outlying Islands", "UM"},
        {"Uruguay", "UY"},
        {"Uzbekistan", "UZ"},
        {"Vanuatu", "VU"},
        {"Venezuela, Bolivarian Republic of", "VE"},
        {"Viet Nam", "VN"},
        {"Virgin Islands, British", "VG"},
        {"Virgin Islands, U.S.", "VI"},
        {"Wallis and Futuna", "WF"},
        {"Western Sahara", "EH"},
        {"Yemen", "YE"},
        {"Zambia", "ZM"},
        {"Zimbabwe", "ZW"}
};

const int LocaleInfo::languagesCount = sizeof(LocaleInfo::languageInfo) / sizeof(LocaleInfo::LanguageInfo);
const int LocaleInfo::countiesCount = sizeof(LocaleInfo::countryInfo) / sizeof(LocaleInfo::CountryInfo);

LocaleInfo::Info LocaleInfo::get(const char *locale) {
    // Supported formats are:
    // en_GB.UTF-8
    // English_United States.1252
    // hu_HU

    LocaleInfo::Info result;

    char buffer[64] {0};

    auto dotDelim = strstr(locale, ".");
    auto delim = strstr(locale, "_");

    if (!dotDelim) {
        dotDelim = locale + strlen(locale);
    }

    if (delim) {
        memcpy(buffer, locale, delim - locale); // gets language info

        for (const auto &inf : languageInfo) {
            if (strcmp(inf.code, buffer) == 0) {
                result.languageCode = inf.code;
                result.languages.emplace_back(inf.value);
            } else if (strcmp(inf.value, buffer) == 0) {
                // language name is unique, so there is no need to continue the search
                result.languageCode = inf.code;
                result.languages.emplace_back(inf.value);
                break;
            }
        }

        memset(buffer, 0, sizeof(buffer) / sizeof(buffer[0]));
        memcpy(buffer, delim + 1, dotDelim - delim - 1); // gets country/region info

        for (const auto &inf : countryInfo) {
            if (strcmp(inf.code, buffer) == 0 || strcmp(inf.value, buffer) == 0) {
                result.countryCode = inf.code;
                result.country = inf.value;
                return result;
            }
        }
    }

    fprintf(stderr, "Couldn't find locale %s\nFalling back to English, United Kingdom\n", locale);

    result = {};
    result.languageCode = "en";
    result.languages.emplace_back("English");
    result.countryCode = "GB";
    result.country = "United Kingdom";
    result.error = "Locale cannot be found";

    return result;
}
}
