//
//  view.cpp
//  program_experiment
//
//  Created by sky_origin on 2017/11/15.
//  Copyright © 2017年 李成禹. All rights reserved.
//

#include "view.h"
#include <iostream>
using namespace std;

class Parting {
public:
    int id;
    bool state;
    double rate = 10;
    double time;
    
    double get_time(time_t t, char date[100]) {
        cout << "录入时间:";
        cout << date << endl;
        time = t;
        return time;
    }
    
    void change_state() {
        state = !state;
        if (state == true) {
            cout << "录入成功\n";
        }
        else if (state == false) {
            cout << "结算成功\n";
        }
    }
    
};

class Car: public Parting {
public:
    int id = Parting::id;
    string number;
    string model;
    
    void get_id() {
        cout << "请输入要存入的车位:";
        cin >> id;
    }
    
    void get_number() {
        cout << "请输入车牌号:";
        cin >> number;
    }
    
    void get_model() {
        cout << "请输入车型:";
        cin >> model;
    }
    
};

int main() {
    double password;
    string method;
    time_t t = time(0);
    struct tm *p;
    p=gmtime(&t);
    char s[100];
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
    printf("%ld: %s\n", (long)t, s);
    
    cout << "Please input your password: ";
    cin >> password;
    if (password == 666666) {
        for (int k = 0; k < 100; k++) {
            
            cout << "Please input entry or claer" << endl;
            cin >> method;
            if (method == "entry") {
                double left[10] = {1,2,3,4,5,6,7,8,9,10};
                cout << "剩余车位 ：";
                for (int i = 0; i < 10; i++) {
                    if (i == 9) {
                        cout << left[i] << endl;
                    }
                    else
                        cout << left[i] << ",";
                }
                
                Car car;
                car.get_id();
                car.get_time(t, s);
                car.get_number();
                car.get_model();
                car.change_state();
                
            }
            
            else if (method == "clear") {
                time_t entry_time = 1510630398;
                
                Parting space;
                double last_time = space.get_time(t, s);
                double time_difference = last_time - entry_time;
                double total = (time_difference/60) * space.rate;
                
                space.state = true;
                space.change_state();
                cout << "Total:" << total << endl;
            }
            
            else
                cout << "Error" << endl;
        }
    }
    else {
        cout << "Please input the true password";
    }
}

