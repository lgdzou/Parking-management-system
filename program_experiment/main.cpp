//
//  main.cpp
//  program_experiment
//
//  Created by h4akD0g on 13/11/2017.
//  Copyright © 2017 李成禹. All rights reserved.
//

//#include <iostream>
//#include <mysql.h>
//using namespace std;
//
//int main (int argc, const char * argv[])
//{
//    MYSQL *connection, mysql;
//    mysql_init(&mysql);
//    connection = mysql_real_connect(&mysql,"127.0.0.1","root","dog123","mysql",0,0,0);
//    if (connection == NULL)
//    {
//        //unable to connect
//        cout<<"Oh Noes!\n"<<endl;
//    }
//    else
//    {
//        cout<<"Connected.\n"<<endl;
//    }
//        return 0;
//}

#include "mysqlmanager.h"
#include <cstdlib>
#include <iostream>
#include <vector>
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

int main()
{
    MySQLManager *mysql = new MySQLManager("123.207.183.132", "root", "rNc6NKKWWL", "mysql", (unsigned int)3306);
    mysql->initConnection();
    if(mysql->getConnectionStatus())
        
    {

        cout << "数据库连接成功" << endl;
        string admin;
        string temp[1];
        string admin_pw;
        string username;
        string password;
        string method;
        time_t t = time(0);
        struct tm *p;
        p=gmtime(&t);
        char s[100];
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", p);
        printf("%ld: %s\n", (long)t, s);
        
        
        if(mysql->runSQLCommand("select username from parking.admin")) {
            vector<vector<std::string> > result = mysql->getResult();
            for(auto & vec : result)
            {
                for(auto &str : vec) {
//                    cout <<str.length()<<endl;
                    cout << "Please input your username: ";
                    cin >> username;
                    admin = str.c_str();
                    if(username.compare(admin)==0)
                    {
                        mysql->clearResult();
                        break;
                    }
                    else {
                        cout << "Please input the true username";
                        return 0;
                    }
    
            
        }
            if(mysql->runSQLCommand("select password from parking.admin")) {
                vector<vector<std::string> > result = mysql->getResult();
                for(auto & vec : result)
                {
                    for(auto &str : vec) {
                        admin_pw = str.c_str();
//                        cout << admin_pw<<endl;
                        cout << "Please input your password: ";
                        cin >> password;
                        if(password.compare(admin_pw)==0)
                        {
                            for (int k = 0; k < 100; k++) {
                                
                                cout << "Please input your choice:\n1.存车\n2.取车" << endl;
                                cin >> method;
                                if (method == "1") {
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
                                
                                else if (method == "2") {
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
                }
                
            }
            
        }
    }
    else
    {
        cout << "连接未建立！"<<endl;
    }
}
}
