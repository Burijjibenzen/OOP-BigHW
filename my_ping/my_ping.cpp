/* 2251206 冯羽芯 计科 */
#include <iostream>
//可根据需要再加入其它需要的头文件
#include "../include/class_aat.h"
using namespace std;

enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_T,
	ARGS_N,
	ARGS_L
};

/* 允许自行添加其它函数，也可以将自定义函数放在其它cpp中 */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：想一想，为什么要加 static（虽然只有一个cpp，但这是工程习惯）
***************************************************************************/
static void usage(const char* const fullpath_procname)
{
	/* 这三行看得懂吗？*/
	const char* procname = strrchr(fullpath_procname, '\\');
	if (procname == NULL)
		procname = fullpath_procname;

	/* 注：这部分比14-b4的要求低，因为没有做到按需适应 */
	cout << endl;
	cout << "Usage: " << procname << " [--help] | [--t] [--n count] [--l size] IPaddress" << endl;
	cout << endl;
	cout << "选项:" << endl;
	cout << "    --help\t\t给出帮助信息" << endl;
	cout << "    --t\t\t\t持续Ping指定主机，直到按Ctrl+C停止" << endl;
	cout << "    --n count\t\t指定要发送的包数量[1..1024]，默认4" << endl;
	cout << "    --l size\t\t指定发送缓冲区的大小[32..64000]，默认64" << endl;
	cout << endl;
	cout << "示例:" << endl;
	cout << "    " << procname << " --help" << endl;
	cout << "    " << procname << " 192.168.80.230" << endl;
	cout << "    " << procname << " --t 192.168.80.230" << endl;
	cout << "    " << procname << " --l 2000 192.168.80.230" << endl;
	cout << "    " << procname << " --n 200 --l 1000 192.168.80.230" << endl;
	cout << "    " << procname << " --l 1000 --n 200 192.168.80.230" << endl;
	cout << "    " << procname << " --l 1000 --t 192.168.80.230" << endl;
	cout << "    " << procname << " --t --l 1000 --n 20 192.168.80.230" << endl;
	cout << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：想一想，为什么要加 static（虽然只有一个cpp，但这是工程习惯）
***************************************************************************/
static bool is_ipaddr_valid(const char* const ipstr)
{
	int dot_num = 0;
	int locate[3], j = 0;
	int length = strlen(ipstr);
	for (int i = 0; i < length; i++) {
		if (ipstr[i] == '.') // 确定点的数目
			dot_num++;

		if (!(ipstr[i] == '.' || (ipstr[i] >= '0' && ipstr[i] <= '9')))
			return false; //存在非法字符
	}

	if (dot_num != 3) //点的数目不对
		return false;

	if (ipstr[0] == '.' || ipstr[length - 1] == '.') // 点出现在首尾
		return false;

	for (int i = 0; i < length - 1; i++)  //前一个和后一个比较，如果有前后两个连续的点，那么也错误
		if (ipstr[i] == '.' && ipstr[i + 1] == '.')
			return false;


	//此时三点前后都有内容，并且都是数字

	for (int i = 0; i < length; i++) //为点做标记
		if (ipstr[i] == '.') {
			locate[j] = i;
			j++;
		}

	int num[4];
	num[0] = atoi(ipstr);
	num[1] = atoi(&ipstr[locate[0] + 1]);
	num[2] = atoi(&ipstr[locate[1] + 1]);
	num[3] = atoi(&ipstr[locate[2] + 1]);

	//cout << num[0] << ' ' << num[1] << ' ' << num[2] << ' ' << num[3] << ' ' << endl;
	for (int i = 0; i <= 3; i++)
		if (num[i] > 255 || num[i] < 0)
			return false;

	return true; //本函数需要自行实现，返回值按需修改
}

/***************************************************************************
  函数名称：
  功    能：基本测试
  输入参数：
  返 回 值：
  说    明：命令行格式要求：先--开始的可变参数，顺序任意，最后是指定的固定参数
***************************************************************************/
int main(int argc, char* argv[])
{
	/* 因为引入了 lib_common_tools.lib，此处先检查大小是否符合要求 */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools 不是200字节，如果使用 lib_common_tools.lib 中的函数则可能出错" << endl;
		return -1;
	}

	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean,          0, false), //默认false
		args_analyse_tools("--t",    ST_EXTARGS_TYPE::boolean,          0, false), //默认false
		args_analyse_tools("--n",    ST_EXTARGS_TYPE::int_with_default, 1, 4, 1, 1024), //[1..1024]，默认4
		args_analyse_tools("--l",    ST_EXTARGS_TYPE::int_with_default, 1, 64, 32, 64000), //[32..64000]，默认64
		args_analyse_tools()  //最后一个，用于结束
	};

	/* 不带任何参数做特殊处理，打印提示信息后结束 */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 1;	//需要固定参数
	int cur_argc;

	/* 最后一个参数：1 - 表示除选项参数外，还需要其它参数
					  例1：Windows/Linux下的ping命令，ping IP地址是最基本的命令格式，另外还有很多-/--开头的可选参数
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 例2：Linux下的c++命令，c++ 源程序文件名是最基本的命令格式，另外还有很多-/--开头的可选参数
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - 表示除选项参数外，不需要其它参数
		函数返回值：-1 - 处理过程有错
					>0 - 可变参数处理完成后，当前停在argv[]的第几个下标位置，如果后面还有argv[]，则表示固定参数
	*/
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//错误信息在函数中已打印
		return -1;
	}

	/* 带--help参数做特殊处理，打印提示信息后结束 */
	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return -1;
	}

	/* 可变参数分析完成后，看是否还有固定参数，以及固定参数的数量是否符合要求 */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //说明后面没有跟需要的固定参数
			cout << "需要指定IP地址，但未给出" << endl;
			return -1;
		}
		if (argc - cur_argc > 1) {
			cout << "除可变参数外，还给出了" << argc - cur_argc << "个固定参数，但本程序只需要一个固定参数" << endl;
			return -1;
		}
	}

	/* 检查IP地址是否是点分十进制的函数，需要实现 */
	if (is_ipaddr_valid(argv[cur_argc]) == false) {
		cout << "指定的IP地址 [" << argv[cur_argc] << "] 不正确." << endl;
		return -1;
	}

	/* 打印参数分析的结果 */
	cout << "可变参数列表:" << endl;
	args_analyse_print(args);

	/* 打印参数的值 */
	cout << "参数检查通过" << endl;
	cout << " --t参数：" << args[ARGS_T].existed() << endl;
	cout << " --n参数：" << args[ARGS_N].get_int() << endl;
	cout << " --l参数：" << args[ARGS_L].get_int() << endl;
	cout << "IP地址是：" << argv[cur_argc] << endl;

	return 0;
}