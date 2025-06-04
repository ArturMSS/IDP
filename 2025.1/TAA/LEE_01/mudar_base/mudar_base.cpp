#include <iostream>

using namespace std;
string dec_para_bin(long long decimal){
    if (decimal == 0){
        return "0";
    }

    
    string binario = "";

    while(decimal > 0){
        int resto = decimal % 2;
        binario = to_string(resto) + binario;
        decimal /= 2;
    }

    return binario;
}
string dec_para_oct(long long decimal){
    if (decimal == 0){
        return "0";
    }

    
    string octal = "";

    while(decimal > 0){
        int resto = decimal % 8;
        octal = to_string(resto) + octal;
        decimal /= 8;
    }

    return octal;
}

string dec_para_hex(long long decimal){
    if (decimal == 0){
        return "0";
    }

    
    string hex = "";

    while(decimal > 0){
        int resto = decimal % 16;
        switch (resto){
            case 10: hex = 'A' + hex; break;
            case 11: hex = 'B' + hex; break;
            case 12: hex = 'C' + hex; break;
            case 13: hex = 'D' + hex; break;
            case 14: hex = 'E' + hex; break;
            case 15: hex = 'F' + hex; break;
            default: hex = to_string(resto) + hex;
        }

        decimal /= 16;
    }

    return hex;
}

int main(){
    long long decimal;
    int base;
    while(true){
        cin>> decimal>> base;
        if(decimal == -1) break;
        switch(base){
            case 2: cout << dec_para_bin(decimal) << endl; break;
            case 8: cout << dec_para_oct(decimal) << endl; break;
            case 10: cout << decimal << endl; break;
            case 16: cout << dec_para_hex(decimal) << endl; break;
            default: break;
        }
    }

}