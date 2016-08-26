#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include "mysqldb.h"

using namespace std;


/*
 * ��ͨ�û���
 * ���ݳ�Ա��  
 * ������Ա�� ����ģ�� 
					����					������
				������Ʒ��� ������Ʒ����  FindByIDPrice
				���빺������ ����Ӧ�ս��			
				����ʵ���ܶ� ����Ӧ�ҽ��	
			  
 *
 */
class User
{
public:
	float FindByIDPrice(string ID, char *shop, MysqlDBAccess &mysql);
private:
	
};


/*
 * Management��  
 *	������ͨ�û�����Ʒ ������ɾ�Ĳ�
 *
 */

class Management
{
public:
	void AddUser(MysqlDBAccess &mysql);			//������ͨ�û�
	void DisplayUser(MysqlDBAccess &mysql);		//��ʾ�����û�
	void DeleteUser(MysqlDBAccess &mysql);		//ɾ���û�
	void AddShop(MysqlDBAccess &mysql);			//������Ʒ��Ϣ
	void DisplayShop(MysqlDBAccess &mysql);		//��ʾ������Ʒ��Ϣ	
	void DeleteShop(MysqlDBAccess &mysql);		//ɾ����Ʒ��Ϣ
}; 


class Root
{
public:
	void AddManagement(MysqlDBAccess &mysql);			//������ͨ�û�
	void DisplayManagement(MysqlDBAccess &mysql);		//��ʾ�����û�
	void DeleteManagement(MysqlDBAccess &mysql);		//ɾ���û� 
};


#endif
