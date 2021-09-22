#pragma once
#include <iostream>
#include "CInitFile.h"
#include <ctime>
#include "CCourseNameTree.h"
#include "CStuNameTree.h"
#include "CCourseIDTree.h"
#include "CStuIDTree.h"

using namespace std;

/*
*管理类：
*结构： 将4棵树作为数据成员进行管理
*功能： 增，删，改，查
*/

class CInfoManage
{
public:
    //总调用函数
    void info_manage();   

    //选择功能,并检查输入的合法性，然后返回选择码
    char _choose_func();    

    //初始化文件，从资源文件获得学生信息与课程信息，并随机产生选课信息,然后读取文件到树中
    void init_file();

    //查找功能总调函数
    void seek_info();   

    //插入功能总调函数
    void insert_info();  

    //删除功能总调函数
    void del_info();    

    //修改功能总调函数
    void modify_info();

    //重载树，将树清空并重新生成
    void overload_tree();  

private: //查找
    void _stu_ID_search_name();
    void _stu_name_search_ID();
    void _course_ID_search_name();
    void _course_name_search_ID();
    void _course_ID_search_elective();
    void _stu_ID_search_elective();

private: //增加
    void _add_stu();
    void _add_course();
    void _add_elective();

private: //删除
    void _del_stu();
    void _del_course();
    void _del_elective();

private: //修改
    void _edit_stu();
    void _edit_course();
    void _edit_elective();

private:
    //界面总菜单
    void _menu_total();  

    //查找菜单
    void _menu_seek();   

    //插入菜单
    void _menu_insert(); 

    //删除菜单
    void _menu_del();  

    //修改菜单
    void _menu_edit();
private:
    CCourseIDTree courseIDTree;
    CCourseNameTree courseNameTree;
    CStuIDTree stuIDTree;
    CStuNameTree stuNameTree;
    CInitFile initFile;
};