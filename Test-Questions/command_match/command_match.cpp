/*
��Ŀ����
��6�������������ִ�еĽ���ֱ��ǣ�

��   ��	ִ   ��
reset				reset what
reset board			board fault
board add			where to add
board delet			no board at all
reboot backplane	impossible
backplane abort		install first
he he				unkown command
ע�⣺he he�������

Ϊ�˼����룬�����û����ԡ����Ψһƥ��ԭ��ƥ�䣺
1����ֻ����һ�ִ�����ֻƥ��һ���ؼ��ֵ������С��������룺r�����ݸù���ƥ������reset��ִ�н��Ϊ��reset what�����룺res�����ݸù���ƥ������reset��ִ�н��Ϊ��reset what��
2����ֻ����һ�ִ��������������������ؼ��֣���ƥ��ʧ�ܡ��������룺reb�������ҵ�����reboot backpalne�����Ǹ������������ؼ��ʣ�����ƥ��ʧ�ܣ�ִ�н��Ϊ��unkown command
3�����������ִ�������ƥ���һ�ؼ��֣������ƥ�䵫��Ψһ������ƥ��ڶ��ؼ��֣�����Բ�Ψһ��ƥ��ʧ�ܡ��������룺r b���ҵ�ƥ������reset board �� reboot backplane��ִ�н��Ϊ��unknown command��

4�����������ִ�������ƥ���һ�ؼ��֣������ƥ�䵫��Ψһ������ƥ��ڶ��ؼ��֣����Ψһ��ƥ��ɹ����������룺b a���޷�ȷ��������board add����backplane abort��ƥ��ʧ�ܡ�
5�����������ִ�����һ�ؼ���ƥ��ɹ�����ƥ��ڶ��ؼ��֣�����ƥ�䣬ʧ�ܡ��������룺bo a��ȷ��������board add��ƥ��ɹ���
6����ƥ��ʧ�ܣ���ӡ��unkown command��


��������:
�����ַ�����ÿ���ַ���һ������

�������:
ִ�н����ÿ���������һ��

ʾ��1
����
reset
reset board
board add
board delet
reboot backplane
backplane abort
���
reset what
board fault
where to add
no board at all
impossible
install first

*/

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>

#define RESET   "reset"
#define BOARD   "board"
#define ADD     "add"
#define DELET   "delet"
#define REBOOT  "reboot"
#define BACKPLANE   "backplane"
#define ABORT   "abort"
#define RESET_BOARD "reset board"
#define BOARD_ADD   "board add"
#define BOARD_DELET   "board delet"
#define REBOOT_BACKPLANE    "reboot backplane"
#define BACKPLANE_ABORT "backplane abort"
#define UNKNOWN_COMMAND "unkown command"

std::map<std::string, std::string> g_cmdMap;
std::vector<std::string> g_firstCMDs, g_secondCMDs;

//ȥ����β�ַ�
void Trim(std::string& str)
{
    if(!str.empty())
    {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of('_') + 1);
    }
}

void SplitStr(const std::string& str, const char c, std::vector<std::string>& vec)
{
    size_t start = 0;
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str.at(i) != c)
        {
            continue;
        }
        vec.push_back(str.substr(start, i - start));
        start = i + 1;
    }
    vec.push_back(str.substr(start));
}

std::string ExecuteCMD(const std::string& str)
{
    std::vector<std::string> cmds;
    SplitStr(str, ' ', cmds);
    if (cmds.size() > 2)
    {
        return UNKNOWN_COMMAND; //������������
    }

    std::string cmd1, cmd2;
    //��������
    if (cmds.size() == 1)
    {
        cmd1 = cmds[0];
        if (cmd1.compare(0, cmd1.length(), RESET, 0, cmd1.length()) == 0)
        {
            return g_cmdMap[RESET];
        }
        return UNKNOWN_COMMAND;
    }
    //��������
    cmd1 = cmds[0];
    cmd2 = cmds[1];
    std::vector<std::string> matchs;
    for (size_t i = 0; i < g_firstCMDs.size(); ++i)
    {
        if(g_firstCMDs[i].compare(0, cmd1.length(), cmd1) != 0)
        {
            continue;
        }
        
        //���е�һ��
        for (size_t j = 0; j < g_secondCMDs.size(); ++j)
        {
            if (g_secondCMDs[j].compare(0, cmd2.length(), cmd2) != 0)
            {
                continue;
            }
            matchs.push_back(g_firstCMDs[i] + " " + g_secondCMDs[j]);
        }
    }

    if (matchs.size() == 1)
    {
        return g_cmdMap[matchs[0]];
    }

    return UNKNOWN_COMMAND;
}

int main()
{
    g_cmdMap["reset"] = "reset what";
    g_cmdMap["reset board"] = "board fault";
    g_cmdMap["board add"] = "where to add";
    g_cmdMap["board delet"] = "no board at all";
    g_cmdMap["reboot backplane"] = "impossible";
    g_cmdMap["backplane abort"] = "install first";

    g_firstCMDs.push_back(RESET);
    g_firstCMDs.push_back(BOARD);
    g_firstCMDs.push_back(REBOOT);
    g_firstCMDs.push_back(BACKPLANE);
    g_secondCMDs.push_back(BOARD);
    g_secondCMDs.push_back(ADD);
    g_secondCMDs.push_back(DELET);
    g_secondCMDs.push_back(BACKPLANE);
    g_secondCMDs.push_back(ABORT);
    std::string str;
    while (std::getline(std::cin, str))
    {
        Trim(str);
        std::cout << ExecuteCMD(str) << std::endl;
    }
    return 0;
}
