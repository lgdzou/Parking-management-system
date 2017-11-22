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
#include <ctime>
using namespace std;
class Parting {
public:
    string id;
    bool state;
    double rate = 10;
    double time;
    
    double get_time(time_t t, char date[100]) {
        cout << "录入时间:";
        cout << date << endl;
        time = t;
        return time;
    }
    
    string change_state(bool state) {
        if (state == true) {
            return "1";
        }
        else if (state == false)
            return "0";
        else
            return 0;
        
    }
    
};

class Car: public Parting {
public:
    string id = Parting::id;
    string number;
    string model;
    
    string get_id() {
        cout << "请输入要存入的车位:";
        cin >> id;
        return  id;
    }
    
    string get_number() {
        cout << "请输入车牌号:";
        cin >> number;
        return number;
    }
    
    string get_model() {
        cout << "请输入车型:";
        cin >> model;
        return model;
    }
    
};

time_t change_time(const char* date,char* const format="%Y-%m-%d %H:%M:%S")
{
    struct tm tm;
    strptime((const char*)date,format, &tm) ;
    time_t ft=mktime(&tm);
    return ft;
}

int main()
{
    MySQLManager *mysql = new MySQLManager("123.207.183.132", "root", "rNc6NKKWWL", "parking", (unsigned int)3306);
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
        
        
        if(mysql->runSQLCommand("select username from admin")) {
            vector<vector<std::string> > result = mysql->getResult();
            for(auto & vec : result)
            {
                for(auto &str : vec) {
//                    cout <<str.length()<<endl;
                    cout << "Please input your username: ";
                    for (int i = 0 ; i <= 3; i++) {
                        cin >> username;
                        admin = str.c_str();
                        if(username.compare(admin)==0)
                        {
                            mysql->clearResult();
                            break;
                        }
                        else {
                            if (i < 3) {
                                cout << "Your have " << 3 - i << " chances left" << endl;
                                cout << "Please input the true username: ";
                            }
                            else if (i == 3) {
                                return 0;
                            }
                        }
                    }
            
        }
            if(mysql->runSQLCommand("select password from admin")) {
                vector<vector<std::string> > result = mysql->getResult();
                for(auto & vec : result)
                {
                    for(auto &str : vec) {
                        cout << "Please input your password: ";
                        
                        for (int i = 0 ; i <= 3; i++) {
                            cin >> password;
                            admin_pw = str.c_str();
                            if(password.compare(admin_pw)==0)
                            {
                                for (int k = 0; k < 100; k++) {
                                    mysql->clearResult();
                                    cout << "Please input your choice:\n1.存车\n2.取车\n3.退出系统" << endl;
                                    cin >> method;
                                    if (method == "1") {
                                        mysql->runSQLCommand("select park_id from park where park_state = 0");
                                        cout << "剩余车位 ：\n";
                                        vector<vector<std::string> > result = mysql->getResult();
                                        for(auto & vec : result)
                                        {
                                            for(auto &str : vec) {
                                                cout << str.c_str() << " ";
                                            }
                                            cout << endl;
                                        }
                                        mysql->clearResult();
                                        Car car;
                                        string id = car.get_id();
                                        string number = car.get_number();
                                        string model = car.get_model();
                                        string state = car.change_state(true);
                                        signed int req = mysql->updateData(id, state, number, model);
                                        if(req==1){
                                            cout<<"停车成功!"<<endl;
                                        }
                                        else
                                            cout<<"停车失败请稍后重试。"<<endl;
                                    }
                                    
                                    else if (method == "2") {
                                        time_t entry_time = 1510630398;
                                        Car car;
                                        string number = car.get_number();
                                        string state = car.change_state(false);

                                        string time = mysql->getData(number, "time");
                                        string id = mysql->getData(number, "park_id");
                                        string last_time;
                                        string park_rate;
                                        double total;
                                        
                                        cout << "录入时间: " << time <<endl;
                                        
                                        signed int req = mysql->updateData(id, state, "''", "''");
                                        if(req==1){
                                            mysql->runSQLCommand("select time from park where park_id = " + id);
                                            cout << "出库时间: ";
                                            vector<vector<std::string> > result = mysql->getResult();
                                            for(auto & vec : result)
                                            {
                                                for(auto &str : vec) {
                                                    last_time = str.c_str();
                                                    cout << str.c_str() << endl;
                                                }
                                            }
                                            mysql->clearResult();
                                            
                                            mysql->runSQLCommand("select park_rate from park where park_id = " + id);
                                            vector<vector<std::string> > rate = mysql->getResult();
                                            for(auto & vec : rate)
                                            {
                                                for(auto &str : vec) {
                                                    park_rate = str.c_str();
                                                }
                                            }

                                            const char* entry_time = time.data();
                                            const char* get_time = last_time.data();
                                            
                                            time_t first = change_time(entry_time);
                                            time_t last = change_time(get_time);
                                            time_t time_difference = (last - first)/60 ;
                                            
                                            double total = time_difference * 2;
                                            cout<< "停车时常" << time_difference << " 分" << endl;
                                            cout<< "停车费用" << total << " 元" << endl;
                                            cout<< "结算成功!" <<endl;
                                        }
                                        else
                                            cout<<"结算失败请稍后重试。"<<endl;
                                        
                                    }
                                    else if (method == "3")
                                    {
                                        return 0;
                                    }
                                    else
                                        cout << "Error" << endl;
                                }
                            }
                            else {
                                if (i < 3) {
                                    cout << "Your have " << 3 - i << " chances left" << endl;
                                    cout << "Please input the true password: ";
                                }
                                else if (i == 3) {
                                    return 0;
                                }
                            }
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
