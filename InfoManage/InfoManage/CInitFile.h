#pragma once
#include <iostream>

using namespace std;

/*
* 读取原TXT的信息，选取10W姓名，和1000课程，并存储到新的文件中，再调用新文件，生成100w选课记录
*/

class CInitFile
{
private:
    //用于记录ID和名称
    struct Name
    {
        char szID[50] = { 0 };
        char szName[50] = { 0 };
    };

public:
    //从姓名库读取10w姓名，并生成bin文件
    void read_name_list();

    //从课程库读取1000课程，并生成bin文件
    void read_course_list();

    //从课程表和学生表中读取数据，随机匹配生成100w选课记录
    void create_select_course();

    //产生随机成绩
    void get_score(char* szInfo);
};
