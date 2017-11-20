//
//  mysqlmanager.h
//  program_experiment
//
//  Created by h4akD0g on 13/11/2017.
//  Copyright © 2017 李成禹. All rights reserved.
//

#ifndef MYSQLMANAGER_H_
#define MYSQLMANAGER_H_

#include <mysql.h>

#include <string>
#include <iostream>
#include <vector>

#include <string.h>

using namespace std;

class MySQLManager
{
    public:
    /*
     * 初始化 MySQL
     * @param hosts:主机
     * @param userName: 用户名
     * @param password:密码
     * @param dbName:数据库名
     * @param port:端口
     */
    MySQLManager(std::string hosts, std::string userName, std::string password, std::string dbName, unsigned int port);
    ~MySQLManager();
    void initConnection();
    /*
     * 查询数据库
     * @param mysql:        MySQL Object
     * @param sql:                sql语句
     */
    bool runSQLCommand(std::string sql);
    string getData(std::string car_num);
    /*
     * 更新数据库状态
     * @param park_id:        、 车位
     * @param park_state:                车位状态
     * @car_number:        车号
     * @car_model:          车型
     */
    signed int updateData(std::string park_id,std::string park_state,std::string car_number,std::string car_model);
    /*
     * 执行插入语句
     * @param sql: 执行的SQL语句
     * @return: 受影响的行数
     */
    signed int insert(std::string sql);
    /**
     * 销毁 MySQL object
     * @param mysql                MySQL object
     */
    void destroyConnection();
    void clearResult();
    bool getConnectionStatus();
    vector< vector<string> > getResult();
    protected:
    void setUserName(std::string userName);
    void setHosts(std::string hosts);
    void setPassword(std::string password);
    void setDBName(std::string dbName);
    void setPort(unsigned int port);
    std::string sqlupdate;
    private:
    bool IsConnected;
    vector< vector<string> > resultList;
    MYSQL mySQLClient;
    unsigned int DEFAULTPORT;
    char * HOSTS;
    char * USERNAME;
    char * PASSWORD;
    char * DBNAME;
};

#endif /* MYSQLMANAGER_H_ */
