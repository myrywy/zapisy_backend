#include "test_utils.hpp"

bool sqlCmp(string s1, string s2){
    string tmp_s1;
    string tmp_s2;
    for(char l : s1){
        if(l!=' ' && l!='\n' && l!='\t'){
            tmp_s1+=l;
        }
    }
    for(char l : s2){
        if(l!=' ' && l!='\n' && l!='\t'){
            tmp_s2+=l;
        }
    }
    if(tmp_s1==tmp_s2){
        return true;
    }else{
        return false;
    }
}
