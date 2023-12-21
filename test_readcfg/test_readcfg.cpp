#include <iostream>
#include <Windows.h>
#include <conio.h>
using namespace std;

#include "../include/class_aat.h"
#include "../include/class_crt.h"

enum OPT_ARGS { OPT_ARGS_HELP = 0, OPT_ARGS_CFGFILE };

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
int readconfig_php_linux(const char *const cfgfile_name)
{
	cfgfile_read_tools cfg(cfgfile_name);
	if (cfg.is_open() == 0) {
		cout << "配置文件 [" << cfgfile_name << "] 无法打开." << endl;
		return -1;
	}

	if (1) {
		cout << "测试01.取配置文件中的所有组：" << endl;

		vector <string> group;
		if (cfg.get_all_group(group) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的所有组出错." << endl;
			return -1;
		}
		for (auto& ig : group)
			cout << ig << endl;
		cout << endl;
		wait_for_enter();

		cout << "测试02.取配置文件中的所有组的所有项：" << endl;
		vector <string> item;
		for (auto& ig : group) {
			if (cfg.get_all_item(ig, item) < 0) {
				cout << "取配置文件 [" << cfgfile_name << "] 的" << ig << "组出错." << endl;
				return -1;
			}

			cout << ig << endl;
			for (auto& it : item)
				cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
			cout << endl;
		}
		wait_for_enter();

		cout << "测试03.取配置文件中的所有项（组为NULL，当做简单配置文件理解）：" << endl;
		item.clear();
		if (cfg.get_all_item(NULL, item) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的所有项出错." << endl;
			return -1;
		}

		for (auto& it : item)
			cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;
		wait_for_enter();
	}

	if (1) {
		/* 打印[ODBC]组的所有项目（区分大小写） */
		const char* gname = "[ODBC]";
		cout << "11.取配置文件中的" << gname << "组-区分大小写-正确：" << endl;

		vector <string> item;
		if (cfg.get_all_item(gname, item) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组出错." << endl;
			return -1;
		}
		for (auto& it : item)
			cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 打印[odbc]组的所有项目（区分大小写） */
		gname = "[odbc]";
		cout << "12.取配置文件中的" << gname << "组-区分大小写-出错：" << endl;

		item.clear();
		if (cfg.get_all_item(gname, item) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组出错." << endl;
//			return -1;应该出错，不返回，继续往下执行
		}
		cout << endl;

		/* 打印[odbc]组的所有项目（不分大小写） */
		cout << "13.取配置文件中的" << gname << "组-不分大小写-正确：" << endl;
		if (cfg.get_all_item(gname, item, true) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组出错." << endl;
			return -1;
		}
		for (auto& it : item)
			cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 打印[PostgreSQL]组的所有项目（不分大小写） */
		gname = "[POSTGRESQL]";
		cout << "14.取配置文件中的" << gname << "组-不分大小写-正确：" << endl;
		item.clear();
		if (cfg.get_all_item(gname, item, true) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组出错." << endl;
			return -1;
		}
		for (auto& it : item)
			cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		/* 取几个具体的项（返回该行，包括名称和值）*/
		string str;
		const char* gname = "[ODBC]";
		const char* iname = "odbc.defaultlrl";

		cout << "21.取配置文件的" << gname << "组的[" << iname << "]项-不分大小写-正确：" << endl;
		if (cfg.get_one_item(gname, iname, str) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项出错." << endl;
			return -1;
		}
		cout << '*' << str << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		gname = "[POSTGRESQL]";
		iname = "PGSQL.max_links";
		cout << "22.取配置文件的" << gname << "组的[" << iname << "]项-区分大小写-出错：" << endl;
		if (cfg.get_one_item(gname, iname, str) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项出错." << endl;
			//		return -1;应该出错，不返回，继续往下执行
		}
		cout << endl;

		cout << "23.取配置文件的" << gname << "组的[" << iname << "]项-不分大小写-正确：" << endl;
		if (cfg.get_one_item(gname, iname, str, true) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项出错." << endl;
			return -1;
		}
		cout << '*' << str << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		/* 取几个具体的项（返回int）*/
		const char* gname = "[ODBC]";
		const char* iname = "odbc.defaultlrl";
		int ret_value;

		cout << "31.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是4096：" << endl;
		/* 指定最小值-100，最大值10000，默认值200，因为配置文件中的4096在合理范围内，因此返回4096 */
		if (cfg.item_get_value(gname, iname, -100, 10000, 200, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		cout << "32.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是1：" << endl;
		/* 指定最小值-1，最大值2048，默认值1，因为配置文件中的4096不在合理范围内，因此返回1 */
		if (cfg.item_get_value(gname, iname, -1, 2048, 1, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定最小值0，最大值100，默认值99，因为配置文件中对应项是字符串On，数据类型不匹配，因此返回99 */
		gname = "[ODBC]";
		iname = "odbc.allow_persistent";
		cout << "33.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是99：" << endl;
		if (cfg.item_get_value(gname, iname, 0, 100, 99, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定最小值0，最大值1000，默认值1，因为配置文件中对应项是123.456，按int读，因此返回123 */
		gname = "[Interbase]";
		iname = "ibase.max_persistent";
		cout << "34.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是123：" << endl;
		if (cfg.item_get_value(gname, iname, 0, 1000, 1, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		/* 取几个具体的项（返回double）*/
		const char* gname = "[Interbase]";
		const char* iname = "ibase.max_persistent";
		double ret_value;

		/* 配置文件中是double型数据，且在合理范围内 */
		cout << "41.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是123.456：" << endl;
		if (cfg.item_get_value(gname, iname, 0, 1000, 1, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 配置文件中是double型数据，但不在合理范围内 */
		cout << "42.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是11.22：" << endl;
		if (cfg.item_get_value(gname, iname, 0, 100, 11.22, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		gname = "[ODBC]";
		iname = "odbc.defaultlrl";
		/* 配置文件中是int型数据，当double取也不错 */
		cout << "43.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是4096：" << endl;
		if (cfg.item_get_value(gname, iname, 0, 8000, 1, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		gname = "[POSTGRESQL]";
		iname = "pgsql.allow_persistent";
		/* 配置文件中是On型数据，当double取，置默认值 */
		cout << "44.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是3.2：" << endl;
		if (cfg.item_get_value(gname, iname, 0, 100, 3.2, ret_value) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ret_value << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		const char *gname = "[POSTGRESQL]";
		const char* iname = "pgsql.allow_persistent";
		char s1[80];
		string s2;

		/* 指定以字符数组方式去读，因此返回On */
		cout << "51.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是On：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定以string方式去读，因此返回On */
		cout << "52.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是On：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s2) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s2 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定以字符数组方式去读，指定默认值为Hello，因为 odbc.check_persistent = 后面没有内容，因此返回Hello	*/
		gname = "[ODBC]";
		iname = "odbc.check_persistent";
		cout << "53.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是Hello：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定以字符数组方式去读，且数组最多只能存放5个字符(含尾零)，指定默认值为Hello，因为 odbc.check_persistent = 后面没有内容，因此返回Hell	*/
		cout << "54.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是Hell：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 5) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		gname = "[ODBC]";
		iname = "odbc.defaultlrl";
		/* 指定以字符数组方式去读，即使是int，也能返回字符串型的4096，因此返回4096	*/
		cout << "55.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是4096：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定以字符数组方式去读带加空格的字符串，返回第一个空格前的内容 */
		gname = "[Interbase]";
		iname = "ibase.timeformat";
		cout << "56.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是%Y-%m-%d：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s1, 80) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s1 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定以string去读带空格的字符串，返回含空格的串 */
		gname = "[Interbase]";
		iname = "ibase.timeformat";
		cout << "57.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是%Y-%m-%d %H:%M:%S：" << endl;
		if (cfg.item_get_value(gname, iname, "Hello", s2) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << s2 << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		wait_for_enter();
	}

	if (1) {
		const char* gname = "[Interbase]";
		const char* iname = "ibase.allow_persistent";
		char ch;

		/* 指定以字符去读，因此返回Y */
		cout << "61.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是Y：" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		gname = "[POSTGRESQL]";
		iname = "pgsql.allow_persistent";
		/* 指定以字符去读字符串On，因此返回首字符O */
		cout << "62.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是O：" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		gname = "[ODBC]";
		iname = "odbc.defaultlrl";
		/* 指定以字符去读4096，返回首字符4 */
		cout << "63.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是4：" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		/* 指定以字符去读，因为 odbc.check_persistent = 后面没有内容，因此返回空格	*/
		gname = "[ODBC]";
		iname = "odbc.check_persistent";
		cout << "64.取配置文件的" << gname << "组的[" << iname << "]项的值-应该是 ：" << endl;
		if (cfg.item_get_value(gname, iname, ch) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的" << gname << "组的[" << iname << "]项的值出错." << endl;
			return -1;
		}
		cout << '*' << ch << '*' << int(ch) << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;

		wait_for_enter();
	}

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static int readconfig(const string& cfgfile_name)
{
	cfgfile_read_tools cfg(cfgfile_name);
	if (cfg.is_open() == 0) {
		cout << "配置文件 [" << cfgfile_name << "] 无法打开." << endl;
		return -1;
	}

	if (1) {
		cout << "测试01.取配置文件中的所有组：" << endl;

		vector <string> group;
		if (cfg.get_all_group(group) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的所有组出错." << endl;
			return -1;
		}
		for (auto& ig : group)
			cout << ig << endl;
		cout << endl;
		wait_for_enter();

		cout << "测试02.取配置文件中的所有组的所有项：" << endl;
		vector <string> item;
		for (auto& ig : group) {
			if (cfg.get_all_item(ig, item) < 0) {
				cout << "取配置文件 [" << cfgfile_name << "] 的" << ig << "组出错." << endl;
				return -1;
			}

			cout << ig << endl;
			for (auto& it : item)
				cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
			cout << endl;
		}
		wait_for_enter();

		cout << "测试03.取配置文件中的所有项（组为NULL，当做简单配置文件理解）：" << endl;
		item.clear();
		if (cfg.get_all_item(NULL, item) < 0) {
			cout << "取配置文件 [" << cfgfile_name << "] 的所有项出错." << endl;
			return -1;
		}

		for (auto& it : item)
			cout << '*' << it << '*' << endl; //前后加*便于看清空格等隐含字符
		cout << endl;
		wait_for_enter();
	}

	/* 给出实际需求的测试 */

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
static void usage(const char* full_procname)
{
	/* 在路径字符串（类似“D:\\VS-Debug\\test-readcfg.exe”)中查找最后一个\\，如果不存在，则为全称 */
	const char* procname = strrchr(full_procname, '\\');
	if (procname == NULL)
		procname = full_procname;
	else
		procname++; //指向\\的下一个字符

	cout << "Usage: " << procname << " --cfgfile filename" << endl;
	cout << endl;
	cout << "e.g. : " << endl;
	cout << "       " << procname << " --cfgfile test.conf : 指定配置文件名为test.conf" << endl;
	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：基本测试
  输入参数：
  返 回 值：
  说    明：命令行格式要求：先--开始的可变参数，顺序任意，最后是指定的固定参数
***************************************************************************/
int main(int argc, char **argv)
{
	/* 因为引入了 lib_aat_tools.lib，此处先检查大小是否符合要求 */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools 不是200字节，如果使用 lib_aat_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	args_analyse_tools args[] = {
		args_analyse_tools("--help",      ST_EXTARGS_TYPE::boolean, 0, false),
		args_analyse_tools("--cfgfile",    ST_EXTARGS_TYPE::str,                  1, string("")),		//必须加string()，否则被适配到args_analyse(const char *arg_name, enum ST_EXTARGS_TYPE type, int ext_num, bool def)
		args_analyse_tools()  //最后一个，用于结束
	};

	int need_fixed_args = 0;	//试试改为1
	int cur_argc;

	/* 最后一个参数：1-表示除选项参数外，还需要其它参数
				  0-表示除选项参数外，不需要其它参数 */
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 参数分析完成后的错误处理 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "指定需要固定参数，但未给出" << endl;
			return -1;
		}
	}

	/* 打印当前参数的分析结果 */
	args_analyse_print(args);

	if (args[OPT_ARGS_CFGFILE].existed() == 0) {
		usage(argv[0]);
		cout << "必须给出配置文件名." << endl;
		return -1;
	}

	/* 给出几个参考示例 */
	if (1) {
		cout << "==========================" << endl;
		cout << "php-linux.ini 读取测试" << endl;
		cout << "==========================" << endl;
		readconfig_php_linux("php-linux.ini");
	}

	if (1) {
		cout << "==========================" << endl;
		cout << "php-win.ini 读取测试" << endl;
		cout << "==========================" << endl;
		readconfig_php_linux("php-win.ini");
	}

	if (1) {
		/* 参数指定的配置文件的读取测试（个人按需） */
		string cfgfile_name = args[OPT_ARGS_CFGFILE].get_string();
		cout << "==========================" << endl;
		cout << cfgfile_name << " 读取测试" << endl;
		cout << "==========================" << endl;
		readconfig(cfgfile_name);
	}

	return 0;
}
