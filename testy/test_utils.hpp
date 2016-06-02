#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief sqlCmp robocza wersja pomocniczej funkcji naiwnie porównującej zaytania SQL - usuwa białe znaki i porównuje powstałe stringi
 * @param s1
 * @param s2
 * @return
 */
bool sqlCmp(string s1, string s2);

template<typename T> bool rcompare(vector<T> v1, vector<T> v2);

template<typename T> bool rcompare(T t1, T t2){
    return t1==t2;
}

template<typename T> bool rcompare(vector<T> v1, vector<T> v2){
    if(v1.size()!=v2.size()){
        return false;
    }
    for(int i=0; i<v1.size(); i++){
        if(!rcompare(v1[i],v2[i])){
            return false;
        }
    }
    return true;
}


#endif // TEST_UTILS_HPP
