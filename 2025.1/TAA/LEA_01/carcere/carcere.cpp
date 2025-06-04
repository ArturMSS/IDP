#include <iostream>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    unsigned long long cel, cel_con;
    int con;
    cin >> cel >> con;
    for (int i = 0 ; i< con; i++){
        cin >> cel_con;
        if ((cel >> cel_con) %2==0){
            cout << "apagada" << endl;
        }else{
            cout << "acesa" << endl;
        }
    }
}