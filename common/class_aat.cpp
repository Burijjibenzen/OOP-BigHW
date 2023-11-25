/* 2251206 ����о �ƿ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//���б�Ҫ�����Լ�������ͷ�ļ�
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //��ʹ��lib����Ч

/* ---------------------------------------------------------------
	 �������������Ҫstatic�������ڲ������ã�
   ---------------------------------------------------------------- */

static int checkip(const char* ip)
{
	int dot_num = 0;
	int locate[3], j = 0;
	int length = strlen(ip);
	for (int i = 0; i < length; i++) {
		if (ip[i] == '.') // ȷ�������Ŀ
			dot_num++;

		if (!(ip[i] == '.' || (ip[i] >= '0' && ip[i] <= '9')))
			return WRONG; //���ڷǷ��ַ�
	}

	if (dot_num != 3) //�����Ŀ����
		return WRONG;

	if (ip[0] == '.' || ip[length - 1] == '.') // ���������β
		return WRONG;

	for (int i = 0; i < length - 1; i++)  //ǰһ���ͺ�һ���Ƚϣ������ǰ�����������ĵ㣬��ôҲ����
		if (ip[i] == '.' && ip[i + 1] == '.')
			return WRONG;


	//��ʱ����ǰ�������ݣ����Ҷ�������

	for (int i = 0; i < length; i++) //Ϊ�������
		if (ip[i] == '.') {
			locate[j] = i;
			j++;
		}

	int num[4];
	num[0] = atoi(ip);
	num[1] = atoi(&ip[locate[0] + 1]);
	num[2] = atoi(&ip[locate[1] + 1]);
	num[3] = atoi(&ip[locate[2] + 1]);

	//cout << num[0] << ' ' << num[1] << ' ' << num[2] << ' ' << num[3] << ' ' << endl;
	for (int i = 0; i <= 3; i++)
		if (num[i] > 255 || num[i] < 0)
			return WRONG;

	return ACCEPT;
}

static unsigned int iptoint(string ipaddr)
{
	int num[4];

	istringstream in(ipaddr);
	in >> num[0];
	in.clear();
	in.ignore(1);
	in >> num[1];
	in.clear();
	in.ignore(1);
	in >> num[2];
	in.clear();
	in.ignore(1);
	in >> num[3];
	in.clear();

	int ipnum;
	ipnum = (num[0] << 24) + (num[1] << 16) + (num[2] << 8) + num[3];

	return ipnum;
}

/***************************************************************************
	 �������ƣ�
	 ��    �ܣ��õ���󳤶�����Ӧ���
	 ���������
	 �� �� ֵ��
	 ˵    ����const����ֻ�ܵ���const����
	***************************************************************************/
void args_analyse_tools::get_max(MAXLEN& max, const args_analyse_tools* const args) const
{
	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) {
		if (args[i].args_name.length() > max.name)
			max.name = args[i].args_name.length();

		if (strlen(args[i].type_name) > max.type)
			max.type = strlen(args[i].type_name);

		if (strlen(args[i].deft) > max.def)
			max.def = strlen(args[i].deft);

		if (args[i].value.length() > max.value)
			max.value = args[i].value.length();

		if (args[i].range.length() > max.range)
			max.range = args[i].range.length();
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	extargs_type = ST_EXTARGS_TYPE::null;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;

	extargs_type = type;
	get_type(type);
	extargs_num = ext_num;

	extargs_bool_default = def;
	deft = new (nothrow) char[10];
	if (deft == NULL) {
		cout << "No Memory" << endl;
		return;
	}
	if (def == false)
		strcpy(deft, "false");
	else
		strcpy(deft, "true");

	args_existed = 0;

	value = "/";

	range = "/";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_default��int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_name = name;

	extargs_type = type;
	get_type(type);
	extargs_num = ext_num;

	deft = new (nothrow) char[15];
	if (deft == NULL) {
		cout << "No Memory" << endl;
		return;
	}
	if (type == ST_EXTARGS_TYPE::int_with_default) {
		ostringstream out;
		out << def;
		strcpy(deft, out.str().c_str());
		extargs_int_default = def;
		extargs_int_value = def;
	}
	else
		strcpy(deft, "/");

	args_existed = 0;

	value = "/";

	extargs_int_min = _min;
	extargs_int_max = _max;

	ostringstream ran;
	ran << "[" << _min << ".." << _max << "]";
	range = ran.str();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����int_with_set_default��int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_name = name;

	extargs_type = type;
	get_type(type);
	extargs_num = ext_num;

	deft = new (nothrow) char[15];
	if (deft == NULL) {
		cout << "No Memory" << endl;
		return;
	}

	if (type == ST_EXTARGS_TYPE::int_with_set_default) {
		// ��ȡ�������ֵ
		int i;
		for (i = 0; set[i] != INVALID_INT_VALUE_OF_SET; i++)
			;
		if (def_of_set_pos >= 0 && def_of_set_pos < i)
			extargs_int_default = extargs_int_value = set[def_of_set_pos];
		else
			extargs_int_default = extargs_int_value = set[0];

		ostringstream out;
		out << extargs_int_default;
		strcpy(deft, out.str().c_str());
	}
	else
		strcpy(deft, "/");

	args_existed = 0;

	value = "/";

	extargs_int_set = (int*)set;

	ostringstream ran;
	ran << set[0];
	for (int i = 1; set[i] != INVALID_INT_VALUE_OF_SET; i++)
		ran << "/" << set[i];
	range = ran.str();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str��ipaddr_with_default��ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_name = name;

	extargs_type = type;
	get_type(type);
	extargs_num = ext_num;

	deft = new (nothrow) char[def.length() + 5];
	if (deft == NULL) {
		cout << "No Memory" << endl;
		return;
	}
	if (def != "") {
		ostringstream out;
		out << def;
		strcpy(deft, out.str().c_str());
	}
	else
		strcpy(deft, "/");

	extargs_string_default = def;
	extargs_string_value = def;

	args_existed = 0;

	value = "/";

	range = "/";

	if (type == ST_EXTARGS_TYPE::ipaddr_with_default)
		extargs_ipaddr_default = iptoint(deft);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����str_with_set_default��str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = name;

	extargs_type = type;
	get_type(type);
	extargs_num = ext_num;

	if (type == ST_EXTARGS_TYPE::str_with_set_default) {
		// ��ȡ�������ֵ
		int i;
		for (i = 0; set[i] != ""; i++)
			;
		if (def_of_set_pos >= 0 && def_of_set_pos < i)
			extargs_string_default = extargs_string_value = set[def_of_set_pos];
		else
			extargs_string_default = extargs_string_value = set[0];

		deft = new (nothrow) char[extargs_string_default.length() + 5];
		if (deft == NULL) {
			cout << "No Memory" << endl;
			return;
		}

		ostringstream out;
		out << extargs_string_default;
		strcpy(deft, out.str().c_str());
	}
	else {
		deft = new (nothrow) char[5];
		if (deft == NULL) {
			cout << "No Memory" << endl;
			return;
		}
		strcpy(deft, "/");
	}

	args_existed = 0;

	value = "/";

	extargs_string_set = (string*)set;

	ostringstream ran;
	ran << set[0];
	for (int i = 1; set[i] != ""; i++)
		ran << "/" << set[i];
	range = ran.str();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (type_name)
		delete[]type_name;
	if (deft)
		delete[]deft;
}

/* ---------------------------------------------------------------
	 ����AAT���Զ����Ա������ʵ�֣�private��
   ---------------------------------------------------------------- */

   /***************************************************************************
		�������ƣ�
		��    �ܣ���ȡtype
		���������
		�� �� ֵ��
		˵    ����
	   ***************************************************************************/
int args_analyse_tools::get_type(const ST_EXTARGS_TYPE type)
{
	type_name = new (nothrow) char[MAX_TYPE_NAME_LEN];
	if (type_name == NULL) {
		cout << "No Memory" << endl;
		return OVERFLOW;
	}

	switch (type) {
		case ST_EXTARGS_TYPE::boolean:
			strcpy(type_name, "Bool");
			break;
		case ST_EXTARGS_TYPE::int_with_default:
			strcpy(type_name, "IntWithDefault");
			break;
		case ST_EXTARGS_TYPE::int_with_error:
			strcpy(type_name, "IntWithError");
			break;
		case ST_EXTARGS_TYPE::int_with_set_default:
			strcpy(type_name, "IntSETWithDefault");
			break;
		case ST_EXTARGS_TYPE::int_with_set_error:
			strcpy(type_name, "IntSETWithError");
			break;
		case ST_EXTARGS_TYPE::str:
			strcpy(type_name, "String");
			break;
		case ST_EXTARGS_TYPE::str_with_set_default:
			strcpy(type_name, "StringSETWithDefault");
			break;
		case ST_EXTARGS_TYPE::str_with_set_error:
			strcpy(type_name, "StringSETWithError");
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_default:
			strcpy(type_name, "IPAddrWithDefault");
			break;
		case ST_EXTARGS_TYPE::ipaddr_with_error:
			strcpy(type_name, "IPAddrWithError");
			break;
		case ST_EXTARGS_TYPE::null:
		default:
			break;
	}
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������!!��ֻ����0/1
			��ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ʵ�֣���Ҫ��
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ extargs_ipaddr_value ��ֵ�� 0x7f000001 תΪ "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	ostringstream out;
	int num[4];
	num[0] = (extargs_ipaddr_value >> 24) & 0x00000011;
	num[1] = (extargs_ipaddr_value >> 16) & 0x00000011;
	num[2] = (extargs_ipaddr_value >> 8) & 0x00000011;
	num[3] = extargs_ipaddr_value & 0x00000011;

	out << num[0] << '.' << num[1] << '.' << num[2] << '.' << num[3];

	return out.str(); //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������follow_up_args���Ƿ��к�������
			0  ���޺�������
			1  ���к�������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int i;
	for (i = 1; i < argc; i++) {

		//�������������Ǽ��ſ�ͷ�ģ�������������ǵڶ�����������ô�ͱ���
		//�������������Ǽ��ſ�ͷ�ģ���������������ǵڶ����������������������ǰ��һ������Ҳ���Ǽ��ſ�ͷ�ģ���ô�ͱ���
		if ((strlen(argv[i]) <= 2 || !(argv[i][0] == '-' && argv[i][1] == '-'))) {// ����--��ͷ����Ч����

			if (follow_up_args == 0) {
				if (i == 1) {
					cout << "����[" << argv[i] << "]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
					return ILLEGAL;
				}
				if (i != 1 && (strlen(argv[i - 1]) <= 2 || !(argv[i - 1][0] == '-' && argv[i - 1][1] == '-'))) {
					cout << "����[" << argv[i] << "]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
					return ILLEGAL;
				}
				if (i != 1) {
					int mark;
					bool is_included = false;
					for (int j = 0; args[j].extargs_type != ST_EXTARGS_TYPE::null; j++) {
						ostringstream name;
						name << argv[i - 1];
						if (name.str() == args[j].args_name) {
							is_included = true;
							mark = j;
							break;
						}
					}
					if (is_included == true && args[mark].extargs_type == ST_EXTARGS_TYPE::boolean) {
						cout << "����[" << argv[i] << "]��ʽ�Ƿ�(����--��ͷ����Ч����)." << endl;
						return ILLEGAL;
					}
				}
			}
			else {
				if (i == 1)
					return i;
				if (i != 1 && (strlen(argv[i - 1]) <= 2 || !(argv[i - 1][0] == '-' && argv[i - 1][1] == '-')))
					return i;
				if (i != 1) {
					int mark;
					bool is_included = false;
					for (int j = 0; args[j].extargs_type != ST_EXTARGS_TYPE::null; j++) {
						ostringstream name;
						name << argv[i - 1];
						if (name.str() == args[j].args_name) {
							is_included = true;
							mark = j;
							break;
						}
					}
					if (is_included == true && args[mark].extargs_type == ST_EXTARGS_TYPE::boolean)
						return i;
				}
			}
		}
		else { // ��--��ͷ����Ч���� �����Ƿ���args��
			bool is_included = false;
			int mark;
			for (int j = 0; args[j].extargs_type != ST_EXTARGS_TYPE::null; j++) {
				ostringstream name;
				name << argv[i];
				if (name.str() == args[j].args_name) {
					is_included = true;
					mark = j;
					break;
				}
			}

			if (is_included == false) {
				cout << "����[" << argv[i] << "]�Ƿ�." << endl;
				return ILLEGAL;
			}
			else { //�ҵ���argv[i]
				// ����ظ���
				if (args[mark].args_existed == 1) {
					cout << "����[" << argv[i] << "]�ظ�." << endl;
					return ILLEGAL;
				}
				// �����--bool/--help
				if (args[mark].extargs_type == ST_EXTARGS_TYPE::boolean) {
					args[mark].args_existed = 1;
					args[mark].value = "true";
				}
				else {
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:int, ��Χ" << args[mark].range << " ȱʡ:" << args[mark].deft << ")\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:int, ��Χ" << args[mark].range << " ȱʡ:" << args[mark].deft << ")\n";
								return ILLEGAL;
							}
							else {
								// �ж��ǲ�������
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value��argv�Ƚ�
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��Χ" << args[mark].range << " ȱʡ:" << args[mark].deft << ")\n";
										return ILLEGAL;
									}

								args[mark].args_existed = 1;
								if (value > args[mark].extargs_int_max || value < args[mark].extargs_int_min) {
									args[mark].value = args[mark].deft;
									args[mark].extargs_int_value = args[mark].extargs_int_default;
								}
								else {
									args[mark].value = out1.str();
									args[mark].extargs_int_value = value;
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:int, ��Χ" << args[mark].range << ")\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:int, ��Χ" << args[mark].range << ")\n";
								return ILLEGAL;
							}
							else {
								// �ж��ǲ�������
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value��argv�Ƚ�
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��Χ" << args[mark].range << ")\n";
										return ILLEGAL;
									}

								args[mark].args_existed = 1;
								if (value > args[mark].extargs_int_max || value < args[mark].extargs_int_min) {
									cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:int, ��Χ" << args[mark].range << ")\n";
									return ILLEGAL;
								}
								else {
									args[mark].extargs_int_value = value;
									args[mark].value = out1.str();
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:int, ��ȡֵ[" << args[mark].range << "] ȱʡ:" << args[mark].deft << ")\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:int, ��ȡֵ[" << args[mark].range << "] ȱʡ:" << args[mark].deft << ")\n";
								return ILLEGAL;
							}
							else {
								// �ж��ǲ�������
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value��argv�Ƚ�
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��ȡֵ[" << args[mark].range << "] ȱʡ:" << args[mark].deft << ")\n";
										return ILLEGAL;
									}

								args[mark].args_existed = 1;
								bool is_found = false;
								for (int k = 0; args[mark].extargs_int_set[k] != INVALID_INT_VALUE_OF_SET; k++)
									if (value == args[mark].extargs_int_set[k]) {
										ostringstream out;
										out << args[mark].extargs_int_set[k];
										args[mark].value = out.str();
										args[mark].extargs_int_value = value;
										is_found = true;
									}

								if (is_found == false)
									args[mark].value = args[mark].deft;
							}
						}

					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:int, ��ȡֵ[" << args[mark].range << "]" << ")\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:int, ��ȡֵ[" << args[mark].range << "]" << ")\n";
								return ILLEGAL;
							}
							else {
								// �ж��ǲ�������
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value��argv�Ƚ�
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "����[" << argv[i] << "]�ĸ��Ӳ�����������. (����:int, ��ȡֵ[" << args[mark].range << "]" << ")\n";
										return ILLEGAL;
									}

								args[mark].args_existed = 1;
								bool is_found = false;
								for (int k = 0; args[mark].extargs_int_set[k] != INVALID_INT_VALUE_OF_SET; k++)
									if (value == args[mark].extargs_int_set[k]) {
										ostringstream out;
										out << args[mark].extargs_int_set[k];
										args[mark].value = out.str();
										args[mark].extargs_int_value = value;
										is_found = true;
									}

								if (is_found == false) {
									cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << value << ")�Ƿ�. (����:int, ��ȡֵ[" << args[mark].range << "])\n";
									return ILLEGAL;
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::str) {
						if (i == argc - 1) { // ����û���ˣ�
							if (args[mark].deft != "/")
								cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:string ȱʡ:" << args[mark].deft << ")\n";
							else
								cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:string)\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								if (args[mark].deft != "/")
									cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:string ȱʡ:" << args[mark].deft << ")\n";
								else
									cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:string)\n";
								return ILLEGAL;
							}
							else {
								args[mark].args_existed = 1;
								args[mark].extargs_string_value = argv[i + 1];
								args[mark].value = argv[i + 1];
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:string, ��ȡֵ[" << args[mark].range << "] ȱʡ:" << args[mark].deft << ")\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:string, ��ȡֵ[" << args[mark].range << "] ȱʡ:" << args[mark].deft << ")\n";
								return ILLEGAL;
							}
							else {
								args[mark].args_existed = 1;
								bool is_found = false;
								for (int k = 0; args[mark].extargs_string_set[k] != ""; k++)
									if (argv[i + 1] == args[mark].extargs_string_set[k]) {
										ostringstream out;
										out << args[mark].extargs_string_set[k];
										args[mark].value = out.str();
										args[mark].extargs_string_value = argv[i + 1];
										is_found = true;
									}

								if (is_found == false)
									args[mark].value = args[mark].deft;
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:string, ��ȡֵ[" << args[mark].range << "])\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:string, ��ȡֵ[" << args[mark].range << "])\n";
								return ILLEGAL;
							}
							else {
								args[mark].args_existed = 1;
								bool is_found = false;
								for (int k = 0; args[mark].extargs_string_set[k] != ""; k++)
									if (argv[i + 1] == args[mark].extargs_string_set[k]) {
										ostringstream out;
										out << args[mark].extargs_string_set[k];
										args[mark].value = out.str();
										args[mark].extargs_string_value = argv[i + 1];
										is_found = true;
									}

								if (is_found == false) {
									cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:string, ��ȡֵ[" << args[mark].range << "])\n";
									return ILLEGAL;
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:IP��ַ)\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:IP��ַ)\n";
								return ILLEGAL;
							}
							else {
								// �ж��ǲ���IP
								args[mark].args_existed = 1;
								if (checkip(argv[i + 1]) == ACCEPT) {
									args[mark].extargs_ipaddr_value = iptoint(argv[i + 1]);
									args[mark].value = argv[i + 1];
								}
								else {
									args[mark].value = args[mark].deft;
									args[mark].extargs_ipaddr_value = args[mark].extargs_ipaddr_default;
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
						if (i == argc - 1) { // ����û���ˣ�
							cout << "����[" << argv[i] << "]�ĸ��Ӳ�������. (����:IP��ַ)\n";
							return ILLEGAL;
						}
						else { // ���滹��
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "����[" << argv[i] << "]ȱ�ٸ��Ӳ���. (����:IP��ַ)\n";
								return ILLEGAL;
							}
							else {
								// �ж��ǲ���IP
								args[mark].args_existed = 1;
								if (checkip(argv[i + 1]) == ACCEPT) {
									args[mark].extargs_ipaddr_value = iptoint(argv[i + 1]);
									args[mark].value = argv[i + 1];
								}
								else {
									cout << "����[" << argv[i] << "]�ĸ��Ӳ���ֵ(" << argv[i + 1] << ")�Ƿ�. (����:IP��ַ)\n";
									return ILLEGAL;
								}
							}
						}
					}
				}
			}
		}
	}
	return argc; //�˾������Ҫ�޸�
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������Ԫ����
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	MAXLEN max;

	args->get_max(max, args);
	cout << setiosflags(ios::left);
	cout << "=";
	for (unsigned int i = 1; i <= max.name + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.type + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.def + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= 7; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.value + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.range + 1; i++)
		cout << "=";
	cout << endl;

	cout << ' ';
	cout << setw(max.name + 1) << "name";
	cout << setw(max.type + 1) << "type";
	cout << setw(max.def + 1) << "default";
	cout << "exists ";
	cout << setw(max.value + 1) << "value";
	cout << setw(max.range + 1) << "range/set";
	cout << endl;
	//cout << max.type << endl;
	cout << "=";
	for (unsigned int i = 1; i <= max.name + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.type + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.def + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= 7; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.value + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.range + 1; i++)
		cout << "=";
	cout << endl;

	for (int i = 0; args[i].extargs_type != ST_EXTARGS_TYPE::null; i++) {
		cout << ' ';
		cout << setw(max.name + 1) << args[i].args_name;
		cout << setw(max.type + 1) << args[i].type_name;
		cout << setw(max.def + 1) << args[i].deft;
		cout << setw(7) << args[i].args_existed;
		cout << setw(max.value + 1) << args[i].value;
		cout << setw(max.range + 1) << args[i].range;
		cout << endl;
	}

	cout << "=";
	for (unsigned int i = 1; i <= max.name + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.type + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.def + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= 7; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.value + 1; i++)
		cout << "=";
	for (unsigned int i = 1; i <= max.range + 1; i++)
		cout << "=";
	cout << endl;

	return 0; //�˾������Ҫ�޸�
}

#endif // !ENABLE_LIB_COMMON_TOOLS
