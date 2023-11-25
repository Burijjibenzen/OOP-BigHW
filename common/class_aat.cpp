/* 2251206 冯羽芯 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;

#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */

static int checkip(const char* ip)
{
	int dot_num = 0;
	int locate[3], j = 0;
	int length = strlen(ip);
	for (int i = 0; i < length; i++) {
		if (ip[i] == '.') // 确定点的数目
			dot_num++;

		if (!(ip[i] == '.' || (ip[i] >= '0' && ip[i] <= '9')))
			return WRONG; //存在非法字符
	}

	if (dot_num != 3) //点的数目不对
		return WRONG;

	if (ip[0] == '.' || ip[length - 1] == '.') // 点出现在首尾
		return WRONG;

	for (int i = 0; i < length - 1; i++)  //前一个和后一个比较，如果有前后两个连续的点，那么也错误
		if (ip[i] == '.' && ip[i + 1] == '.')
			return WRONG;


	//此时三点前后都有内容，并且都是数字

	for (int i = 0; i < length; i++) //为点做标记
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
	 函数名称：
	 功    能：得到最大长度以适应输出
	 输入参数：
	 返 回 值：
	 说    明：const对象只能调用const函数
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	extargs_type = ST_EXTARGS_TYPE::null;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
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
		// 获取数组里的值
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = name;

	extargs_type = type;
	get_type(type);
	extargs_num = ext_num;

	if (type == ST_EXTARGS_TYPE::str_with_set_default) {
		// 获取数组里的值
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (type_name)
		delete[]type_name;
	if (deft)
		delete[]deft;
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

   /***************************************************************************
		函数名称：
		功    能：获取type
		输入参数：
		返 回 值：
		说    明：
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
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

	return out.str(); //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const* const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int i;
	for (i = 1; i < argc; i++) {

		//如果这个参数不是减号开头的，并且这个参数是第二个参数，那么就报错。
		//如果这个参数不是减号开头的，并且这个参数不是第二个参数，并且这个参数的前面一个参数也不是减号开头的，那么就报错
		if ((strlen(argv[i]) <= 2 || !(argv[i][0] == '-' && argv[i][1] == '-'))) {// 不是--开头的有效内容

			if (follow_up_args == 0) {
				if (i == 1) {
					cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
					return ILLEGAL;
				}
				if (i != 1 && (strlen(argv[i - 1]) <= 2 || !(argv[i - 1][0] == '-' && argv[i - 1][1] == '-'))) {
					cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
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
						cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
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
		else { // 是--开头的有效内容 分析是否在args内
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
				cout << "参数[" << argv[i] << "]非法." << endl;
				return ILLEGAL;
			}
			else { //找到了argv[i]
				// 如果重复了
				if (args[mark].args_existed == 1) {
					cout << "参数[" << argv[i] << "]重复." << endl;
					return ILLEGAL;
				}
				// 如果是--bool/--help
				if (args[mark].extargs_type == ST_EXTARGS_TYPE::boolean) {
					args[mark].args_existed = 1;
					args[mark].value = "true";
				}
				else {
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 范围" << args[mark].range << " 缺省:" << args[mark].deft << ")\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, 范围" << args[mark].range << " 缺省:" << args[mark].deft << ")\n";
								return ILLEGAL;
							}
							else {
								// 判断是不是整数
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value与argv比较
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 范围" << args[mark].range << " 缺省:" << args[mark].deft << ")\n";
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
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 范围" << args[mark].range << ")\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, 范围" << args[mark].range << ")\n";
								return ILLEGAL;
							}
							else {
								// 判断是不是整数
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value与argv比较
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 范围" << args[mark].range << ")\n";
										return ILLEGAL;
									}

								args[mark].args_existed = 1;
								if (value > args[mark].extargs_int_max || value < args[mark].extargs_int_min) {
									cout << "参数[" << argv[i] << "]的附加参数值(" << value << ")非法. (类型:int, 范围" << args[mark].range << ")\n";
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
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 可取值[" << args[mark].range << "] 缺省:" << args[mark].deft << ")\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, 可取值[" << args[mark].range << "] 缺省:" << args[mark].deft << ")\n";
								return ILLEGAL;
							}
							else {
								// 判断是不是整数
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value与argv比较
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 可取值[" << args[mark].range << "] 缺省:" << args[mark].deft << ")\n";
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
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 可取值[" << args[mark].range << "]" << ")\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, 可取值[" << args[mark].range << "]" << ")\n";
								return ILLEGAL;
							}
							else {
								// 判断是不是整数
								int value = atoi(argv[i + 1]);
								ostringstream out1, out2;
								out1 << value; //value与argv比较
								if (argv[i + 1][0] == '+' || argv[i + 1][0] == '-')
									out2 << &argv[i + 1][1];
								else
									out2 << argv[i + 1];

								for (unsigned int k = 0; k < out2.str().length(); k++)
									if (out2.str().c_str()[k] > '9' || out2.str().c_str()[k] < '0') {
										cout << "参数[" << argv[i] << "]的附加参数不是整数. (类型:int, 可取值[" << args[mark].range << "]" << ")\n";
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
									cout << "参数[" << argv[i] << "]的附加参数值(" << value << ")非法. (类型:int, 可取值[" << args[mark].range << "])\n";
									return ILLEGAL;
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::str) {
						if (i == argc - 1) { // 后面没有了！
							if (args[mark].deft != "/")
								cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string 缺省:" << args[mark].deft << ")\n";
							else
								cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string)\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								if (args[mark].deft != "/")
									cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string 缺省:" << args[mark].deft << ")\n";
								else
									cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string)\n";
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
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string, 可取值[" << args[mark].range << "] 缺省:" << args[mark].deft << ")\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:string, 可取值[" << args[mark].range << "] 缺省:" << args[mark].deft << ")\n";
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
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string, 可取值[" << args[mark].range << "])\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:string, 可取值[" << args[mark].range << "])\n";
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
									cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:string, 可取值[" << args[mark].range << "])\n";
									return ILLEGAL;
								}
							}
						}
					}
					if (args[mark].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:IP地址)\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:IP地址)\n";
								return ILLEGAL;
							}
							else {
								// 判断是不是IP
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
						if (i == argc - 1) { // 后面没有了！
							cout << "参数[" << argv[i] << "]的附加参数不足. (类型:IP地址)\n";
							return ILLEGAL;
						}
						else { // 后面还有
							if (strlen(argv[i + 1]) >= 2 && argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
								cout << "参数[" << argv[i] << "]缺少附加参数. (类型:IP地址)\n";
								return ILLEGAL;
							}
							else {
								// 判断是不是IP
								args[mark].args_existed = 1;
								if (checkip(argv[i + 1]) == ACCEPT) {
									args[mark].extargs_ipaddr_value = iptoint(argv[i + 1]);
									args[mark].value = argv[i + 1];
								}
								else {
									cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:IP地址)\n";
									return ILLEGAL;
								}
							}
						}
					}
				}
			}
		}
	}
	return argc; //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
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

	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
