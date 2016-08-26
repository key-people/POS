/*
 * ʹ��C++��Mysql��ģ��POS�����ֹ���
 *
 * ���ܼ��
	1����ģ��
		�����˺ź����룬�������ݿ�����֤�˺ź����룬���˺����͵������������������

	2����ģ������
		1��������ƷID
			2��������ƷIDȥ������������Ʒ�ļ۸񣬺�����
			3����ӡ��Ʒ��Ϣ
		4��������Ʒ����
		5����ӡӦ���ܶ�

	3����ģ��
		1��Ʒ����
			3.1��Ʒ��ѯ			
			3.2�����Ʒ
				1��������ƷID
				2��������Ʒ����
				3��������Ʒ����
			3.3�޸���Ʒ
			3.4ɾ����Ʒ
				������ƷIDɾ����Ʒ

		2�˻�����
			1�˻���ѯ
			2����˻�
			3�޸��˻�
			4ɾ���˻�
 * Lzy	2011-8-19
 */

#include <iostream>
#include <string>
#include "mysqldb.h"
#include "user.h"

using namespace std;

/*
 * ��ͨ�û�ģʽ������
 * ������ƷID
 * ������ƷIDȥ������������Ʒ�ļ۸񣬺���Ʒ����
 * ��ӡ��Ʒ��Ϣ��������Ʒ��������ӡӦ���ܶ�
 */
int user(MysqlDBAccess &mysql)
{
	User p;
	float price; 
	char name[30];
	int count;
	string buf;
	
	while(1)
	{
		cout<<"\nShop ID ";
		cin>>buf;
		price = p.FindByIDPrice(buf,name, mysql);	//������ƷID���õ���Ʒ���ۺ�����
		if(price < 0)
			continue;
		cout<<"Shop Name:  "<<name<<endl;
		cout<<"Shop price: "<<price<<endl;
		cout<<"shop Count: ";
		cin>>count;		
		cout<<"all monery: "<<price*count<<endl<<endl;	
		
		cout<<" Quit(n) S> ";		//������ʾ
		getchar();
		if(getchar() == 'n')
			break;
	}
	return 0;
}

/* 
 * ����Աģʽ������
 * �������Ա���棬�ṩ����Ʒ����ͨ�û����ӸĲ�ȹ���Ȩ��
 */
void management(MysqlDBAccess &mysql)
{
	Management p;
	int choose;
	while(1)
	{
		cout<<"\n 1. Add User"<<endl;
		cout<<" 2. Delete User"<<endl;
		cout<<" 3. Display User"<<endl;
		cout<<" 4. Add Shop"<<endl;
		cout<<" 5. Delete Shop"<<endl;
		cout<<" 6. Display Shop"<<endl;
		cout<<" 0. quit"<<endl<<"\n M> ";
		cin>>choose;
		switch(choose)
		{
		case 1:	
			p.AddUser(mysql);
			break;
		case 2:
			p.DeleteUser(mysql);
			break;
		case 3:
			p.DisplayUser(mysql);
			break;
		case 4:	
			p.AddShop(mysql);
			break;
		case 5:
			p.DeleteShop(mysql);
			break;
		case 6:
			p.DisplayShop(mysql);
			break;
		case 0:
			return ;
		default :
			break;
		}
	}
}

/*
 * ��������Աģʽ������
 * ���볬������Ա���棬�ṩ�Թ���Ա���ӸĲ�ȹ���Ȩ��
 */
void root(MysqlDBAccess &mysql)
{
	Root p;
	int choose;
	while(1)
	{
		cout<<"\n 1. Add Management"<<endl;
		cout<<" 2. Delete Management"<<endl;
		cout<<" 3. Display Management"<<endl;		
		cout<<" 0. quit"<<endl<<"\n R> ";
		cin>>choose;
		switch(choose)
		{
		case 1:	
			p.AddManagement(mysql);
			break;
		case 2:
			p.DeleteManagement(mysql);
			break;
		case 3:
			p.DisplayManagement(mysql);
			break;		
		case 0:
			return ;
		default :
			break;
		}
	}
}


int main(void)
{
	char name[20], pwd[10];
	int staff_type,				//�û����� 0->�����û� 1->����Ա ����Ϊ��ͨ�û�
		staff_ID;				//���

	MysqlDBAccess mysql;					//�������ݿ����
	mysql.mysqldbinit(mysql);				//��ʼ�����ݿ�
	
	while(1)
	{
		cout<<"\nname: ";	cin>>name;
		cout<<"pwd : ";	cin>>pwd;
		staff_type = mysql.ChrRecord(name, pwd, staff_ID);//�û�������������
		if( staff_type <= -1)	//��½ʧ��
		{
			cout<<"faile"<<endl;
			continue;
		}
		else 
			break;
	}
	
	switch(staff_type)
	{
	case 0:
		cout<<"\nRoot: "<<staff_ID<<"->"<<name<<endl;		
		root(mysql);			//���볬������Աģʽ
		break;

	case 1:
		cout<<"\nManagement: "<<staff_ID<<"->"<<name<<endl;		
		management(mysql);		//�������Աģʽ
		break;

	default:
		cout<<"\nUser: "<<staff_ID<<"->"<<name<<endl;
		user(mysql);			//������ͨ�û�ģʽ
		break;
	}
	
	cout<<"Bye\n"<<endl;
	return 0;
}
