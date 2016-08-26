#include "mysqldb.h"
#include <string.h>
#include <stdio.h>




/*
 * �ڱ�Personnel�а�ID����ĳһ�ֶ�
 * ���ѽ��������str��
 */
int MysqlDBAccess::GetRecord(char *str,int ID)
{	
	char selectSQL[150];

	sprintf(selectSQL,"select %s from Personnel where staff_ID=%d;",str,ID);	
	if (ExcuteSQL(selectSQL)==false) 
		return false;

	result = mysql_store_result(mysql);
	row = mysql_fetch_row(result);
	strcpy(str, row[0]);	
	mysql_free_result(result);	

	return true;	
}




/*
 * ִ�в�Ѱ��䣬����ʾ��Ѱ���
 */
int MysqlDBAccess::SDelectRecord(string selectSQL)
{
	int rowNum=-1;
	Table table;
	Fields fields;
	Record record;	

	if (isDBConnected==false) {
		cout<<"Not connect to any database"<<endl;
		return false;
	}
	if (ExcuteSQL(selectSQL)==false) 
		return false;

	result = mysql_store_result(mysql);
	rowNum = mysql_affected_rows(mysql);
	GetFields(fields);

	for (int i=1; i<=rowNum; i++) {
		row = mysql_fetch_row(result);
	
		for (int j = 0; j<fields.size(); j++) {
			if (row[j] == NULL) {
				record[fields[j]] = "";
			}
			else {
				record[fields[j]] = row[j];
			}
		}
		table.push_back(record);
		record.clear();
	}
	mysql_free_result(result);
	DisplayTable(fields, table);
	
	return true;	
}

/*��ʾ��Ѱ������*/
void MysqlDBAccess::DisplayTable(Fields fd,Table dt)
{
	TableIter iter;
	Record rt;
	string valStr;

	for (iter = dt.begin(); iter != dt.end();iter++) {
		rt = *iter;
		for (int i = 0; i < fd.size(); i++) {
			valStr = rt[fd[i]];
			if (valStr != "") {
				cout<<valStr<<"  ";
			}
			else {
				cout<<"---"<<" ";
			}
		}
		cout<<endl;
	}
}

int MysqlDBAccess::GetFields(Fields &fields)
{
	while (field = mysql_fetch_field(result)) {
		fields.push_back(field->name);
	}
	
	return 0;
}

/*ִ��mysql���*/
bool MysqlDBAccess::ExcuteSQL(string sql)
{
	mysql_set_character_set(mysql, "gb2312");
	if (mysql_query(mysql, sql.c_str())) {
		cout<<cout<<"mysql_query: "<<mysql_error(mysql)<<endl;
		return false;
	}		
	return true;
}

//�������ݿ�
bool MysqlDBAccess::ConnectDB(string dbName)
{
	if (mysql_select_db(mysql, dbName.c_str())) {
		cout<<cout<<"mysql_select_db: "<<mysql_error(mysql)<<endl;
		return false;
	}
	isDBConnected = true;
	this->dbName = dbName;

	return true;
}

bool MysqlDBAccess::ConnectSever(string severName, string userName, string pwd, int port)
{
	mysql = mysql_init(NULL);
	if(!mysql_real_connect(mysql, severName.c_str(), userName.c_str(), pwd.c_str(), NULL, port, NULL, 0))
	{
		cout<<"mysql_real_connect: "<<mysql_error(mysql)<<endl;
		return false;
	}else
		isSeverConnected = true;
	return true;
}

/*
 * ��֤�û��������벢�ɲ����б�������
 * ���û���������������ȷ�򷵻��û�����
 *	���򷵻� -1 �û��������д�
 *			 -2 �����д�
 */
int MysqlDBAccess::ChrRecord(char *name, char *pwd, int &ID)
{
	char selectSQL[150];

	sprintf(selectSQL,"select product_pwd,staff_type,staff_ID from Personnel where product_name=\'%s\';",name);
	ExcuteSQL(selectSQL);		

	result = mysql_store_result(mysql);	
	row = mysql_fetch_row(result);
	if(row == NULL)
		return -1;
	mysql_free_result(result);
	if(strcmp(pwd, row[0]) == 0)	
	{
		ID = atoi(row[2]);
		return atoi(row[1]);
	}
	else 
		return -2;	
}


/*
 * ���ݿ��ʼ������
 * ���ӷ�����
 * �������ݿ�ͱ�
 */
void MysqlDBAccess::mysqldbinit(MysqlDBAccess &sql)
{
	sql.ConnectSever("localhost","root");			//���ӷ�����
	sql.ExcuteSQL("create database if not exists LzyPOS"); //�������ݿ�			
	sql.ConnectDB("LzyPOS");						//�������ݿ�
	
	/* ����Ա���� �������򴴽�*/
	sql.ExcuteSQL("create table if not exists Personnel(\
				staff_ID int auto_increment primary key,\
						product_name	varchar(15),	\
		product_pwd		varchar(16) default '123456',	\
						staff_type		int,			\
						remark			varchar(30))");

	/* ϵͳ�Զ����䳬���û����û��� root, ���� 12346*/
	char *selectSQL = "select product_pwd from Personnel where product_name='root'";
	ExcuteSQL(selectSQL);		
	result = mysql_store_result(mysql);		
	row = mysql_fetch_row(result);		//��Ѱ�Ƿ���root�û�
	if(row == NULL)
		ExcuteSQL("insert into Personnel(product_name, staff_type, staff_ID) values('root',0, 0)");
	else
		mysql_free_result(result);
	

	sql.ExcuteSQL("create table if not exists Shop(	\
						bar_code varchar(8),			\
						product_name varchar(30),		\
						sale_price float)");
/*	
	mysql.ExcuteSQL("create table if not exists Cell(	\
						sale_ID	 varchar(12),			\
						trans_ID varchar(4),			\
						staff_ID varchar(6),			\
						sale_date date,					\
						give_sum  float,				\
						real_sum  float,				\
						sale_money float,				\
						change_	  float,				\
						sale_state int);");	

	mysql.ExcuteSQL("create table if not exists Detail(	\
						Detail_ID varchar(18),			\
						sale_ID  varchar(18),			\
						bar_code  varchar(8),			\
						count	  int,					\
						sale_price float,				\
						sale_state int,					\
						staff_ID   varchar(6))");
	*/
	
}

