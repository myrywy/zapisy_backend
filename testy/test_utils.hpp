#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>

using std::string;

/**
 * @brief sqlCmp robocza wersja pomocniczej funkcji naiwnie porównującej zaytania SQL - usuwa białe znaki i porównuje powstałe stringi
 * @param s1
 * @param s2
 * @return
 */
bool sqlCmp(string s1, string s2);

#endif // TEST_UTILS_HPP
