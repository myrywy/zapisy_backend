#include "test_utils.hpp"

bool isWhite(char c){
    if(c==' ' || c=='\n' || c=='\t'){
        return true;
    }
    return false;
}

bool isSpecial(char c){
    if(c=='=' || c=='+' || c=='%' || c=='*' || c=='/' || c=='`'){
        return true;
    }
    return false;
}

bool sqlCmp(string s1, string s2){
    auto i1=s1.begin();
    auto i2=s2.begin();
    while(i1!=s1.end() && i2!=s2.end()){
        while(isWhite(*i1)){
            ++i1;
        }
        while(isWhite(*i2)){
            ++i2;
        }
        if(i1==s1.end()){
            if(i2==s2.end()){
                return true;
            }
            return false;
        }
        if(i2==s2.end()){
            return false;
        }
        if((*i1)!=(*i2)){
            return false;
        }
        ++i1;
        ++i2;
    }
    return true;
}
