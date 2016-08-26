#include "user.h"

float User::FindByIDPrice(string ID, char *shop, MysqlDBAccess &mysql)
{
	char buf[150];
	/*������ƷID��Ѱ��Ʒ���ۡ�����*/
	sprintf(buf,"select sale_price, product_name from Shop where bar_code=\'%s\';",ID.c_str());
	if(mysql.ExcuteSQL(buf)==false) 
		return -1;

	mysql.result = mysql_store_result(mysql.mysql);
	mysql.row = mysql_fetch_row(mysql.result);
	if(mysql.row == NULL)
	{
		cout<<"NO this Shop"<<endl;
		return -1;
	}
	strcpy(shop, mysql.row[1]);			//�õ���Ʒ����
	mysql_free_result(mysql.result);
	return atof(mysql.row[0]);			//������Ʒ����
}


void Management::DeleteShop(MysqlDBAccess &mysql)
{
	string name;
	cout<<"Input Name:";
	cin>>name;		//����Ҫɾ������Ʒ����

	char buf[150];		
	sprintf(buf,"delete from Shop where product_name = \'%s\'",name.c_str());
	mysql.ExcuteSQL(buf);

	cout<<"\nshop list:"<<endl;		//�Զ���������û���Ϣ
	DisplayShop(mysql);
}

void Management::AddShop(MysqlDBAccess &mysql)
{
	int bar_code;
	cout<<"Input staff_ID: ";	//������Ʒ���
	cin>>bar_code;

	string product_name;
	cout<<"Input Name: ";		//������Ʒ����
	cin>>product_name;

	float sale_price;		
	cout<<"Input price: ";		//������Ʒ�۸�
	cin>>sale_price;

	char buf[150];		
	sprintf(buf,"insert into Shop value(%d,\'%s\', %.4f)",bar_code,product_name.c_str(),sale_price);
	mysql.ExcuteSQL(buf);		//������Ʒ��Ϣ

	cout<<"\nshop list:"<<endl;		//�Զ���������û���Ϣ
	DisplayShop(mysql);
}

void Management::DisplayShop(MysqlDBAccess &mysql)
{
	string sql("select * from Shop");
	mysql.SDelectRecord(sql);
}

void Management::DeleteUser(MysqlDBAccess &mysql)
{
	string name;
	cout<<"Input Name:";
	cin>>name;

	char buf[150];		
	sprintf(buf,"delete from Personnel where  product_name = \'%s\'",name.c_str());
	mysql.ExcuteSQL(buf);

	cout<<"\nproduct_name list:"<<endl;		//�Զ���������û���Ϣ
	DisplayUser(mysql);
}

void Management::DisplayUser(MysqlDBAccess &mysql)
{
	string sql("select * from Personnel where staff_type=2");
	mysql.SDelectRecord(sql);
}

void Management::AddUser(MysqlDBAccess &mysql)
{
	string product_name;	
	cout<<"Input Name: ";
	cin>>product_name;

	char buf[150];	
	sprintf(buf,"insert into Personnel(product_name,staff_type) values(\'%s\', 2);",product_name.c_str());
	if(mysql.ExcuteSQL(buf)==false) 
		cout<<"Faile: "<<endl;
	else
		cout<<"Scuess! "<<endl;

	cout<<"\nproduct_name list:"<<endl;
	DisplayUser(mysql);
}


void Root::AddManagement(MysqlDBAccess &mysql)
{
	string product_name;	
	cout<<"Input Name: ";
	cin>>product_name;

	char buf[150];	
	sprintf(buf,"insert into Personnel(product_name,staff_type) values(\'%s\', 1);",product_name.c_str());
	if(mysql.ExcuteSQL(buf)==false) 
		cout<<"Faile: "<<endl;
	else
		cout<<"Scuess! "<<endl;

	cout<<"\nproduct_name list:"<<endl;
	DisplayManagement(mysql);
}


void Root::DisplayManagement(MysqlDBAccess &mysql)
{
	string sql("select * from Personnel where staff_type=1");
	mysql.SDelectRecord(sql);
}

void Root::DeleteManagement(MysqlDBAccess &mysql)
{
	string name;
	cout<<"Input Name:";
	cin>>name;

	char buf[150];		
	sprintf(buf,"delete from Personnel where  product_name = \'%s\'",name.c_str());
	mysql.ExcuteSQL(buf);

	cout<<"\nproduct_name list:"<<endl;		//�Զ���������û���Ϣ
	DisplayManagement(mysql);
}

