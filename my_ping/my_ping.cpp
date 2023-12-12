/* 2251206 ����о �ƿ� */
#include <iostream>
//�ɸ�����Ҫ�ټ���������Ҫ��ͷ�ļ�
#include "../include/class_aat.h"
using namespace std;

enum OPT_ARGS {
	ARGS_HELP = 0,
	ARGS_T,
	ARGS_N,
	ARGS_L
};

/* ���������������������Ҳ���Խ��Զ��庯����������cpp�� */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������һ�룬ΪʲôҪ�� static����Ȼֻ��һ��cpp�������ǹ���ϰ�ߣ�
***************************************************************************/
static void usage(const char* const fullpath_procname)
{
	/* �����п��ö���*/
	const char* procname = strrchr(fullpath_procname, '\\');
	if (procname == NULL)
		procname = fullpath_procname;

	/* ע���ⲿ�ֱ�14-b4��Ҫ��ͣ���Ϊû������������Ӧ */
	cout << endl;
	cout << "Usage: " << procname << " [--help] | [--t] [--n count] [--l size] IPaddress" << endl;
	cout << endl;
	cout << "ѡ��:" << endl;
	cout << "    --help\t\t����������Ϣ" << endl;
	cout << "    --t\t\t\t����Pingָ��������ֱ����Ctrl+Cֹͣ" << endl;
	cout << "    --n count\t\tָ��Ҫ���͵İ�����[1..1024]��Ĭ��4" << endl;
	cout << "    --l size\t\tָ�����ͻ������Ĵ�С[32..64000]��Ĭ��64" << endl;
	cout << endl;
	cout << "ʾ��:" << endl;
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������һ�룬ΪʲôҪ�� static����Ȼֻ��һ��cpp�������ǹ���ϰ�ߣ�
***************************************************************************/
static bool is_ipaddr_valid(const char* const ipstr)
{
	int dot_num = 0;
	int locate[3], j = 0;
	int length = strlen(ipstr);
	for (int i = 0; i < length; i++) {
		if (ipstr[i] == '.') // ȷ�������Ŀ
			dot_num++;

		if (!(ipstr[i] == '.' || (ipstr[i] >= '0' && ipstr[i] <= '9')))
			return false; //���ڷǷ��ַ�
	}

	if (dot_num != 3) //�����Ŀ����
		return false;

	if (ipstr[0] == '.' || ipstr[length - 1] == '.') // ���������β
		return false;

	for (int i = 0; i < length - 1; i++)  //ǰһ���ͺ�һ���Ƚϣ������ǰ�����������ĵ㣬��ôҲ����
		if (ipstr[i] == '.' && ipstr[i + 1] == '.')
			return false;


	//��ʱ����ǰ�������ݣ����Ҷ�������

	for (int i = 0; i < length; i++) //Ϊ�������
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

	return true; //��������Ҫ����ʵ�֣�����ֵ�����޸�
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���������
  ���������
  �� �� ֵ��
  ˵    ���������и�ʽҪ����--��ʼ�Ŀɱ������˳�����⣬�����ָ���Ĺ̶�����
***************************************************************************/
int main(int argc, char* argv[])
{
	/* ��Ϊ������ lib_common_tools.lib���˴��ȼ���С�Ƿ����Ҫ�� */
	if (sizeof(args_analyse_tools) != 200) {
		cout << "class args_analyse_tools ����200�ֽڣ����ʹ�� lib_common_tools.lib �еĺ�������ܳ���" << endl;
		return -1;
	}

	args_analyse_tools args[] = {
		args_analyse_tools("--help", ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--t",    ST_EXTARGS_TYPE::boolean,          0, false), //Ĭ��false
		args_analyse_tools("--n",    ST_EXTARGS_TYPE::int_with_default, 1, 4, 1, 1024), //[1..1024]��Ĭ��4
		args_analyse_tools("--l",    ST_EXTARGS_TYPE::int_with_default, 1, 64, 32, 64000), //[32..64000]��Ĭ��64
		args_analyse_tools()  //���һ�������ڽ���
	};

	/* �����κβ��������⴦����ӡ��ʾ��Ϣ����� */
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}

	int need_fixed_args = 1;	//��Ҫ�̶�����
	int cur_argc;

	/* ���һ��������1 - ��ʾ��ѡ������⣬����Ҫ��������
					  ��1��Windows/Linux�µ�ping���ping IP��ַ��������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  ping 192.168.80.230
						  ping -t -n 10 192.168.80.230
					 ��2��Linux�µ�c++���c++ Դ�����ļ�����������������ʽ�����⻹�кܶ�-/--��ͷ�Ŀ�ѡ����
						  c++ test.cpp
						  c++ -Wall -o test test.cpp
				  0 - ��ʾ��ѡ������⣬����Ҫ��������
		��������ֵ��-1 - ��������д�
					>0 - �ɱ����������ɺ󣬵�ǰͣ��argv[]�ĵڼ����±�λ�ã�������滹��argv[]�����ʾ�̶�����
	*/
	if ((cur_argc = args_analyse_process(argc, argv, args, need_fixed_args)) < 0)
	{
		//������Ϣ�ں������Ѵ�ӡ
		return -1;
	}

	/* ��--help���������⴦����ӡ��ʾ��Ϣ����� */
	if (args[ARGS_HELP].existed()) {
		usage(argv[0]);
		return -1;
	}

	/* �ɱ����������ɺ󣬿��Ƿ��й̶��������Լ��̶������������Ƿ����Ҫ�� */
	if (need_fixed_args) {
		if (cur_argc == argc) {  //˵������û�и���Ҫ�Ĺ̶�����
			cout << "��Ҫָ��IP��ַ����δ����" << endl;
			return -1;
		}
		if (argc - cur_argc > 1) {
			cout << "���ɱ�����⣬��������" << argc - cur_argc << "���̶���������������ֻ��Ҫһ���̶�����" << endl;
			return -1;
		}
	}

	/* ���IP��ַ�Ƿ��ǵ��ʮ���Ƶĺ�������Ҫʵ�� */
	if (is_ipaddr_valid(argv[cur_argc]) == false) {
		cout << "ָ����IP��ַ [" << argv[cur_argc] << "] ����ȷ." << endl;
		return -1;
	}

	/* ��ӡ���������Ľ�� */
	cout << "�ɱ�����б�:" << endl;
	args_analyse_print(args);

	/* ��ӡ������ֵ */
	cout << "�������ͨ��" << endl;
	cout << " --t������" << args[ARGS_T].existed() << endl;
	cout << " --n������" << args[ARGS_N].get_int() << endl;
	cout << " --l������" << args[ARGS_L].get_int() << endl;
	cout << "IP��ַ�ǣ�" << argv[cur_argc] << endl;

	return 0;
}