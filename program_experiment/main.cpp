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

#include <iostream>
#include <vector>
using namespace std;
int main()
{
    MySQLManager *mysql = new MySQLManager("127.0.0.1", "root", "dog123", "mysql", (unsigned int)3306);
    mysql->initConnection();
    if(mysql->getConnectionStatus())
    {
        if(mysql->runSQLCommand("show databases"))
        {
            vector<vector<std::string> > result = mysql->getResult();
            for(auto & vec : result)
            {
                for(auto &str : vec) {
                    cout << str.c_str() << " ";
                }
                cout << endl;
            }
        }
        else
        cout << "执行失败" << endl;
    }
    else
    cout << "连接未建立" << endl;
    
    return 0;
}
