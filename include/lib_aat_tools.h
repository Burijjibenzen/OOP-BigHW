#ifndef _ST_TOOLS_ARGS_ANALYSE_H_
#define _ST_TOOLS_ARGS_ANALYSE_H_

#include <string>
using namespace std;

#define INVALID_INT_VALUE_OF_SET	0x7FFFFFFF

/*  args    extargs_num extargs_type  extargs_fun             extargs_defvalue;
	--help  0           NULL          NULL                    NULL
	--limit 1           INT           char * 转 int 返回      min/max/def
	--limit 1           INT           char * 转 int 返回      min/max/无default，返回错
	--limit 1           INT           char * 转 int 返回      12/23/35集合中的一个，返回错
	--user  1           string        char * 转 string 返回   def
	--user  1           string        char * 转 string 返回   "abc"/"def"/"xyz"集合中的一个
	--ip    1           IPADDR        char * 转 ipaddr 返回   NULL
*/

/* 定义各种参数类型 */
enum class ST_EXTARGS_TYPE {
	null = 0,			//仅用于无参初始化
	boolean,				//仅需要返回0/1，表示是否存在，例如：--help
	int_with_default,		//附加参数为整型，介于 min..max之间，有缺省值，若置超过上下限，则置缺省值
	int_with_error,		//附加参数为整型，介于 min..max之间，有缺省值，若置超过上下限，则返回错误
	int_with_set_default,		//附加参数为整型，只能属于一个有若干元素的集合[11/22/33]，有缺省值，若值不在集合中，则置缺省值
	int_with_set_error,		//附加参数为整型，只能属于一个有若干元素的集合[11/22/33]，有缺省值，若值不在集合中，则返回错误
	str,			//附加参数为字符串
	str_with_set_default,	//附加参数为字符串，只能属于一个有若干元素的集合["11"/"22"/"33"]，有缺省值，若值不在集合中，则置缺省值
	str_with_set_error,	//附加参数为字符串，只能属于一个有若干元素的集合["11"/"22"/"33"]，有缺省值，若值不在集合中，则返回错误
	ipaddr_with_default,		//附加参数为IP地址，有缺省值，返回一个u_int32
	ipaddr_with_error,		//附加参数为IP地址，无缺省值，返回错误
	tmax				//最大值，控制超限
};

class st_args_analyse {
protected:
	/* 这些初始化后值就不应该再变 */
	string               args_name;		//参数名称，类似于 "--help形式"
	ST_EXTARGS_TYPE extargs_type;	//本参数的额外参数的类型
	int                  extargs_num;	//额外参数的个数，0-1，其它暂未考虑

	bool extargs_bool_default;		//bool型额外参数的缺省值（default）

	int  extargs_int_default;		//int型额外参数的缺省值（default）
	int  extargs_int_min;			//int型额外参数的最小值（min）
	int  extargs_int_max;			//int型额外参数的最大值（max）
	int* extargs_int_set;			//int型额外参数的集合

	string  extargs_string_default;		//string型额外参数的缺省值(含ipaddr)
	string* extargs_string_set;		//string型额外参数的集合

	unsigned int   extargs_ipaddr_default;		//IP地址缺省值

	/* 下面这些是变量 */
	int    args_existed;			//本参数是否出现过（防止相同参数 -n ** -n ** 重复出现）
	int    extargs_int_value;		//int型额外参数读到的值
	string extargs_string_value;		//string型额外参数读到的值
	unsigned int  extargs_ipaddr_value;		//IP地址额外参数读到的值

	/* 为了方便在自用和给学生的间切换，强制约定class的总大小为200字节 */
	char pad[68];

	const char* get_extargs_type_str() const;
	int print(const int width_args_name, const int width_default, const int width_value) const;
	const string get_parameter() const;

public:
	st_args_analyse();
	st_args_analyse(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const bool def);
	/* 以下四种构造，最后一个参数为true表示支持重复参数，例如 --ip xx --ip xx （作业要求中不需要实现）*/
	st_args_analyse(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max, const bool mutli_args = false);
	st_args_analyse(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set, const bool mutli_args = false);
	st_args_analyse(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const string def, const bool mutli_args = false);
	st_args_analyse(const char* arg_name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set, const bool mutli_args = false);
	~st_args_analyse();

	/* 外取参数 */
	const string get_name() const;			//返回某设置项的名称（返回 "--help"）
	const int    existed() const;			//判断某设置项是否存在
	const int    get_int() const;			//返回某设置项的值（int型）
	const string get_string() const;		//返回某设置项的值（string型）
	const unsigned int get_ipaddr() const;	//返回某设置项的值（IP地址，以"127.0.0.1"为例，返回u_int32型的 0x7f000001）
	const string get_str_ipaddr() const;	//返回某设置项的值（IP地址，以"127.0.0.1"为例，返回字符串形式的"127.0.0.1"）

	friend int args_analyse_process(const int argc, const char* const* const argv, st_args_analyse* const args, const int follow_up_args);
	friend int args_analyse_print(const st_args_analyse* const args);
};

int args_analyse_process(const int argc, const char* const* const argv, st_args_analyse* const args, const int follow_up_args);
int args_analyse_print(const st_args_analyse* const args);

#endif
