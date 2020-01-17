/*
题目描述
有6条配置命令，它们执行的结果分别是：

命   令	执   行
reset				reset what
reset board			board fault
board add			where to add
board delet			no board at all
reboot backplane	impossible
backplane abort		install first
he he				unkown command
注意：he he不是命令。

为了简化输入，方便用户，以“最短唯一匹配原则”匹配：
1、若只输入一字串，则只匹配一个关键字的命令行。例如输入：r，根据该规则，匹配命令reset，执行结果为：reset what；输入：res，根据该规则，匹配命令reset，执行结果为：reset what；
2、若只输入一字串，但本条命令有两个关键字，则匹配失败。例如输入：reb，可以找到命令reboot backpalne，但是该命令有两个关键词，所有匹配失败，执行结果为：unkown command
3、若输入两字串，则先匹配第一关键字，如果有匹配但不唯一，继续匹配第二关键字，如果仍不唯一，匹配失败。例如输入：r b，找到匹配命令reset board 和 reboot backplane，执行结果为：unknown command。

4、若输入两字串，则先匹配第一关键字，如果有匹配但不唯一，继续匹配第二关键字，如果唯一，匹配成功。例如输入：b a，无法确定是命令board add还是backplane abort，匹配失败。
5、若输入两字串，第一关键字匹配成功，则匹配第二关键字，若无匹配，失败。例如输入：bo a，确定是命令board add，匹配成功。
6、若匹配失败，打印“unkown command”


输入描述:
多行字符串，每行字符串一条命令

输出描述:
执行结果，每条命令输出一行

示例1
输入
reset
reset board
board add
board delet
reboot backplane
backplane abort
输出
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

//去掉首尾字符
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
        return UNKNOWN_COMMAND; //超过两条命令
    }

    std::string cmd1, cmd2;
    //单条命令
    if (cmds.size() == 1)
    {
        cmd1 = cmds[0];
        if (cmd1.compare(0, cmd1.length(), RESET, 0, cmd1.length()) == 0)
        {
            return g_cmdMap[RESET];
        }
        return UNKNOWN_COMMAND;
    }
    //两条命令
    cmd1 = cmds[0];
    cmd2 = cmds[1];
    std::vector<std::string> matchs;
    for (size_t i = 0; i < g_firstCMDs.size(); ++i)
    {
        if(g_firstCMDs[i].compare(0, cmd1.length(), cmd1) != 0)
        {
            continue;
        }
        
        //命中第一个
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
