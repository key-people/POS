#ifndef MYSQLDBACCESS_H
#define MYSQLDBACCESS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <mysql.h>

using namespace std;

typedef map<string, string>	Record;
typedef map<string, string>::iterator RecordIter;

typedef vector<Record>	Table;
typedef vector<Record>::iterator TableIter;

typedef vector<string>	Fields;
typedef vector<string>::iterator FieldsIter;

class User;

class MysqlDBAccess
{
public:
	MysqlDBAccess(){isSeverConnected = isDBConnected = false;}
	~MysqlDBAccess(){if(isSeverConnected) DisconnentSever();}
	bool ConnectSever(string severName, string userName, string pwd="", int port=3306);	//���ӷ�����
	void DisconnentSever(void){mysql_close(mysql);}		
	bool ConnectDB(string dbName);						//�������ݿ�
	bool ExcuteSQL(string sql);						//ִ�����
	int SDelectRecord(string selectSQL);				//ִ�в�Ѱʫ�䲢��ʾ��Ѱ����

	int ChrRecord(char *name,char *pwd,int &ID);	//�û���������֤	
	void mysqldbinit(MysqlDBAccess &sql);			//���ݿ��ʼ��
	int GetRecord(char *str,int ID);
	
	friend	class User;

protected:
	int GetFields(Fields & fields);
	void DisplayTable(Fields fd,Table dt);

private:
	MYSQL *mysql;
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	bool isSeverConnected;
	bool isDBConnected;
	string dbName;
};



#endif
