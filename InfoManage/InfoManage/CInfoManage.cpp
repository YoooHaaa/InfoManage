#include <iostream>
#include <fstream>
#include "CInitFile.h"
#include <ctime>
#include "CCourseNameTree.h"
#include "CStuNameTree.h"
#include "CCourseIDTree.h"
#include "CStuIDTree.h"
#include "CInfoManage.h"

using namespace std;

void CInfoManage::info_manage()//总调用函数
{
    init_file();

    while (true)
    {
        system("cls");

        _menu_total();
        char cInput = 0;
        do 
        {
            cout << "请输入功能编号:" << endl;
            cInput = _choose_func();
        } while (cInput < '1' || cInput > '5');
        
        switch (cInput)
        {
        case '1':
            seek_info();
            break;
        case '2':
            insert_info();
            break;
        case '3':
            del_info();
            break;
        case '4':
            modify_info();
            break;
        case '5':
            return;
        default:break;
        }
    }  
}
void CInfoManage::init_file()//初始化文件，从资源文件获得学生信息与课程信息，并随机产生选课信息,然后读取文件到树中
{
    //初始化文件信息，只需要初始化一次就行了，以后就可以注释掉，用已经生成过的文件来创建树
    initFile.read_name_list();
    initFile.read_course_list();
    initFile.create_select_course();
    system("cls");

    cout << "======================" << endl;
    cout << "正在载入文件请稍后..." << endl;
    cout << "======================" << endl;

    //创建课程名树
    courseNameTree.create_course_name_tree();

    //创建学生名树
    stuNameTree.create_stu_name_tree();

    //创建课程ID树，并将选课信息链接到树上
    courseIDTree.create_course_ID_tree();
    courseIDTree.create_select_course_list();

    //创建学生ID树，并将选课信息链接到树上
    stuIDTree.create_stu_ID_tree();
    stuIDTree.create_select_course_list();

}
char CInfoManage::_choose_func()//选择功能,并检查输入的合法性，然后返回选择码
{
    char szInput[100] = { 0 };

    while (true)
    {
        cin.getline(szInput, 100);

        if (strlen(szInput) == 1)
        {
            return szInput[0];
        }
        else
        {
            cout << "非法输入！ 请重新输入：" << endl;
        }
    }
    return 0;
}
void CInfoManage::_menu_total()  //界面总菜单
{
    cout << "========================" << endl;
    cout << "请选择以下功能：" << endl;
    cout << "1 查找信息：" << endl;
    cout << "2 插入信息：" << endl;
    cout << "3 删除信息：" << endl;
    cout << "4 修改信息：" << endl;
    cout << "5 退出：" << endl;
    cout << "========================" << endl;

}
void CInfoManage::_menu_seek()  //查找菜单
{
    cout << "===========================================" << endl;
    cout << "请选择以下功能：" << endl;
    cout << "1 通过学生ID查询学生姓名：" << endl;
    cout << "2 通过学生姓名查询学生ID：" << endl;
    cout << "3 通过课程ID查询课程名：" << endl;
    cout << "4 通过课程名查询课程ID：" << endl;
    cout << "5 通过课程ID查询选修了该课程的学生以及成绩：" << endl;
    cout << "6 通过学生ID查询该学生选修的课程信息：" << endl;
    cout << "7 退出：" << endl;
    cout << "===========================================" << endl;
}
void CInfoManage::_menu_insert() //插入菜单
{
    cout << "====================================" << endl;
    cout << "请选择以下功能：" << endl;
    cout << "1 新增学生(ID, 名字)：" << endl;
    cout << "2 新增课程(ID,名字)：" << endl;
    cout << "3 新增选课记录(学生ID, 课程ID, 分数)：" << endl;
    cout << "4 退出：" << endl;
    cout << "====================================" << endl;
}
void CInfoManage::_menu_del()   //删除菜单
{
    cout << "====================================" << endl;
    cout << "请选择以下功能：" << endl;
    cout << "1 删除学生(ID, 名字)：" << endl;
    cout << "2 删除课程(ID,名字)：" << endl;
    cout << "3 删除选课记录(学生ID, 课程ID, 分数)：" << endl;
    cout << "4 退出：" << endl;
    cout << "====================================" << endl;
}
void CInfoManage::_menu_edit()  //修改菜单
{
    cout << "====================================" << endl;
    cout << "请选择以下功能：" << endl;
    cout << "1 修改学生(名字)：" << endl;
    cout << "2 修改课程(名字)：" << endl;
    cout << "3 修改选课记录(分数)：" << endl;
    cout << "4 退出：" << endl;
    cout << "====================================" << endl;
}
void CInfoManage::seek_info() //查找功能总调函数
{
    while (true)
    {
        system("cls");

        _menu_seek();
        char cInput = 0;
        do
        {
            cout << "请输入功能编号:" << endl;
            cInput = _choose_func();
        } while (cInput < '1' || cInput > '7');

        switch (cInput)
        {
        case '1':
            system("cls");
            _stu_ID_search_name();
            break;
        case '2':
            system("cls");
            _stu_name_search_ID();
            break;
        case '3':
            system("cls");
            _course_ID_search_name();
            break;
        case '4':
            system("cls");
            _course_name_search_ID();
            break;
        case '5':
            system("cls");
            _course_ID_search_elective();
            break;
        case '6':
            system("cls");
            _stu_ID_search_elective();
            break;
        case '7':
            return;
        default:break;
        }
        system("pause");
    }
}
void CInfoManage::_stu_ID_search_name()
{
    char szStuID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));
    

    char* pName = stuIDTree.use_ID_search_name(szStuID);
    if (pName != nullptr)
    {
        cout << "=========================================" << endl;
        cout << "查询结果  ID: " << szStuID << "   姓名：" << pName << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "==================" << endl;
        cout << "未找到该学生信息！" << endl;
        cout << "==================" << endl;
    }
}
void CInfoManage::_stu_name_search_ID()
{
    char szStuName[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的姓名：" << endl;
        cin.getline(szStuName, 1024);
    } while (!strlen(szStuName));

    stuNameTree.use_stu_search_ID(szStuName);
}
void CInfoManage::_course_ID_search_name()
{
    char szCourseID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入课程的ID号：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    
    char* pName = courseIDTree.use_ID_search_name(szCourseID);
    if (pName != nullptr)
    {
        cout << "=========================================" << endl;
        cout << "查询结果  ID: " << szCourseID << "   课程名：" << pName << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "==================" << endl;
        cout << "未找到该课程信息！" << endl;
        cout << "==================" << endl;
    }
}
void CInfoManage::_course_name_search_ID()
{
    char szCourseName[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入课程名：" << endl;
        cin.getline(szCourseName, 1024);
    } while (!strlen(szCourseName));
    
    char* pID = courseNameTree.use_course_search_ID(szCourseName);
    if (pID != nullptr)
    {
        cout << "=========================================" << endl;
        cout << "查询结果  ID: " << pID << "   课程名：" << szCourseName << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "==================" << endl;
        cout << "未找到该课程信息！" << endl;
        cout << "==================" << endl;
    }
}
void CInfoManage::_course_ID_search_elective()
{
    char szCourseID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入课程的ID号：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    courseIDTree.search_select_course_record(szCourseID);
}
void CInfoManage::_stu_ID_search_elective()
{
    char szStuID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    stuIDTree.search_select_course_record(szStuID);
}
void CInfoManage::insert_info() //插入功能总调函数
{
    while (true)
    {
        system("cls");

        _menu_insert();
        char cInput = 0;
        do
        {
            cout << "请输入功能编号:" << endl;
            cInput = _choose_func();
        } while (cInput < '1' || cInput > '4');

        switch (cInput)
        {
        case '1':
            system("cls");
            _add_stu();
            break;
        case '2':
            system("cls");
            _add_course();
            break;
        case '3':
            system("cls");
            _add_elective();
            break;
        case '4':
            return;
        default:break;
        }
        system("pause");
    } 
}
void CInfoManage::_add_stu()
{
    char szStuID[1024] = { 0 };
    char szStuName[1024] = { 0 };
    char szInfo[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    do //判断是否空输入
    {
        cout << "请输入学生的姓名：" << endl;
        cin.getline(szStuName, 1024);
    } while (!strlen(szStuName));

    strcpy_s(szInfo, 1024, szStuID);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, szStuName);

    //检查该学生是否存在，用ID树检查，因为ID时唯一的，名字不是唯一的
    if (stuIDTree._check_ID(szStuID))
    {
        cout << "=========================" << endl;
        cout << "该学生信息已经存在！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        stuNameTree.add_stu_info(szInfo);//将新增加的学生信息添加到学生名排序树中

        stuIDTree.add_stu_info(szInfo);//将新增加的学生信息添加到学生ID排序树中，并写入文件（写入文件的操作都在主树中进行）

        cout << "=========================" << endl;
        cout << "学生信息添加成功！" << endl;
        cout << "=========================" << endl;
    }
    
}
void CInfoManage::_add_course()
{
    char szCourseID[1024] = { 0 };
    char szCourseName[1024] = { 0 };
    char szInfo[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入课程ID号：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    
    do //判断是否空输入
    {
        cout << "请输入课程名：" << endl;
        cin.getline(szCourseName, 1024);
    } while (!strlen(szCourseName));

    strcpy_s(szInfo, 1024, szCourseID);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, szCourseName);

    //先检查该门课程是否存在
    if (courseIDTree._check_ID(szCourseID))
    {
        cout << "=========================" << endl;
        cout << "课程信息已经存在！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        if (courseNameTree.use_course_search_ID(szCourseName) == nullptr)//没有同名的课程
        {
            courseNameTree.add_course_info(szInfo);

            courseIDTree.add_course_info(szInfo);

            cout << "=========================" << endl;
            cout << "课程信息添加成功！" << endl;
            cout << "=========================" << endl;
        }
        else
        {
            cout << "=========================" << endl;
            cout << "已经存在同名的课程！" << endl;
            cout << "=========================" << endl;

        }
    }
    
}
void CInfoManage::_add_elective()
{
    char szStuID[1024] = { 0 };
    char szCourseID[1024] = { 0 };
    char szScore[1024] = { 0 };
    char szInfo[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    char* pStuName = stuIDTree.use_ID_search_name(szStuID);
    if (pStuName == nullptr)
    {
        cout << "该学生的信息不存在，请先添加学生信息" << endl;
        return;
    }

    do //判断是否空输入
    {
        cout << "请输入课程的ID：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    char* pCourseName = courseIDTree.use_ID_search_name(szCourseID);
    if (pCourseName == nullptr)
    {
        cout << "该课程信息不存在，请先添加课程信息" << endl;
        return;
    }

    do //判断是否空输入
    {
        cout << "请输入课程成绩：" << endl;
        cin.getline(szScore, 1024);
    } while (!strlen(szScore));
 
    /*将选课信息按照设定的格式存进szInfo中*/
    strcpy_s(szInfo, 1024, szStuID);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, pStuName);
    strcat_s(szInfo, 1024, "^");
    strcat_s(szInfo, 1024, szCourseID);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, pCourseName);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, szScore);
    strcat_s(szInfo, 1024, "^");

    //判断该学生是否选修了该门课，如果已经选修了，则报错，并跳过
    if (stuIDTree._check_select_course(szStuID, szCourseID) == false)
    {
        ofstream writeElectiveInfo;
        writeElectiveInfo.open("stu_select_course.bin", ios::out | ios::app); //在文件末尾进行添加
        if (writeElectiveInfo.fail())
        {
            cout << "打开文件stu_select_course.bin失败，请关闭程序，并重试！" << endl;
            system("pause");
            exit(0);
        }
        writeElectiveInfo.write(szInfo, strlen(szInfo) + 1); //写入课表

        writeElectiveInfo.close();

        cout << "================================" << endl;
        cout << "正在将选课信息与文件同步，请稍后" << endl;
        cout << "================================" << endl << endl;

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "选课信息添加成功！" << endl;
        cout << "=========================" << endl;
    }
}

void CInfoManage::del_info()//删除功能总调函数
{
    while (true)
    {
        system("cls");

        _menu_del();
        char cInput = 0;
        do
        {
            cout << "请输入功能编号:" << endl;
            cInput = _choose_func();
        } while (cInput < '1' || cInput > '4');

        switch (cInput)
        {
        case '1':
            system("cls");
            _del_stu();
            break;
        case '2':
            system("cls");
            _del_course();
            break;
        case '3':
            system("cls");
            _del_elective();
            break;
        case '4':
            return;
        default:break;
        }
        system("pause");
    }    
}
void CInfoManage::_del_stu()
{
    char szStuID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入要删除学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    //删除学生信息
    if (stuIDTree.del_data(szStuID))
    {
        cout << "=================================" << endl;
        cout << "正在将删除信息与文件同步，请稍后" << endl;
        cout << "=================================" << endl << endl;

        //更新文件信息
        stuIDTree.update_file();

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "学生信息成功删除！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "======================================" << endl;
        cout << "学生信息删除失败---无法找到该学生信息！" << endl;
        cout << "======================================" << endl;
    }
}
void CInfoManage::_del_course()
{
    char szCourseID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入要删除课程的ID号：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    //删除学生信息
    if (courseIDTree.del_data(szCourseID) == true)
    {
        cout << "================================" << endl;
        cout << "正在将删除信息与文件同步，请稍后" << endl;
        cout << "================================" << endl << endl;

        //更新文件信息
        courseIDTree.update_file();

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "课程信息成功删除！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "==================================" << endl;
        cout << "课程信息删除失败---课程信息不存在！" << endl;
        cout << "==================================" << endl;
    }   
}
void CInfoManage::_del_elective()
{
    char szStuID[1024] = { 0 };
    char szCourseID[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));
    if (stuIDTree._check_ID(szStuID) == false)
    {
        cout << "该学生的信息不存在，请先添加学生信息" << endl;
        return;
    }

    do //判断是否空输入
    {
        cout << "请输入课程的ID号：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    if (courseIDTree._check_ID(szCourseID) == false)
    {
        cout << "该课程的信息不存在，请先添加课程信息" << endl;
        return;
    }

    if (stuIDTree.del_select_course_record(szStuID, szCourseID))//如果选课记录成功删除，则同步到文件
    {
        cout << "=================================" << endl;
        cout << "正在将删除信息与文件同步，请稍后" << endl;
        cout << "=================================" << endl << endl;

        //更新文件信息
        stuIDTree.update_file();

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "选课记录成功删除！" << endl;
        cout << "=========================" << endl;
    }  
}
void CInfoManage::_edit_stu()
{
    char szStuID[1024] = { 0 };
    char szStuName[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入要修改学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    do //判断是否空输入
    {
        cout << "请输入修改后的姓名：" << endl;
        cin.getline(szStuName, 1024);
    } while (!strlen(szStuName));

    //修改学生信息
    if (stuIDTree.edit_info(szStuID, szStuName))
    {
        cout << "=================================" << endl;
        cout << "正在将修改信息与文件同步，请稍后" << endl;
        cout << "=================================" << endl << endl;

        //更新文件信息
        stuIDTree.update_file();

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "学生信息成功修改！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "======================================" << endl;
        cout << "学生信息修改失败---无法找到该学生信息！" << endl;
        cout << "======================================" << endl;
    }
}
void CInfoManage::_edit_course()
{
    char szCourseID[1024] = { 0 };
    char szCourseName[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入要修改课程的ID号：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    do //判断是否空输入
    {
        cout << "请输入修改后的课程名：" << endl;
        cin.getline(szCourseName, 1024);
    } while (!strlen(szCourseName));

    //修改课程信息
    if (courseIDTree.edit_info(szCourseID, szCourseName))
    {
        cout << "=================================" << endl;
        cout << "正在将修改信息与文件同步，请稍后" << endl;
        cout << "=================================" << endl << endl;

        //更新文件信息
        courseIDTree.update_file();

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "课程信息成功修改！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "======================================" << endl;
        cout << "课程信息修改失败---无法找到该课程信息！" << endl;
        cout << "======================================" << endl;
    }
}
void CInfoManage::_edit_elective()
{
    char szStuID[1024] = { 0 };
    char szCourseID[1024] = { 0 };
    char szScore[1024] = { 0 };

    do //判断是否空输入
    {
        cout << "请输入学生的ID号：" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    if (stuIDTree._check_ID(szStuID) == false)
    {
        cout << "该学生的信息不存在，请先添加学生信息" << endl;
        return;
    }

    do //判断是否空输入
    {
        cout << "请输入课程的ID：" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    if (courseIDTree._check_ID(szCourseID) == false)
    {
        cout << "该课程的信息不存在，请先添加课程信息" << endl;
        return;
    }

    do //判断是否空输入
    {
        cout << "请输入课程成绩：" << endl;
        cin.getline(szScore, 1024);
    } while (!strlen(szScore));


    //判断该学生是否选修了该门课
    if (stuIDTree.edit_elective(szStuID, szCourseID, szScore) == true)
    {
        cout << "=======================================" << endl;
        cout << "正在将修改的选课信息与文件同步，请稍后" << endl;
        cout << "=======================================" << endl << endl;

        //更新文件信息
        stuIDTree.update_file();

        //重载树
        overload_tree();

        cout << "=========================" << endl;
        cout << "选课信息添加成功！" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "====================================" << endl;
        cout << "成绩修改失败--该学生并未选修该门课！" << endl;
        cout << "====================================" << endl;
    }
}

void CInfoManage::modify_info()
{
    while (true)
    {
        system("cls");

        _menu_edit();
        char cInput = 0;
        do
        {
            cout << "请输入功能编号:" << endl;
            cInput = _choose_func();
        } while (cInput < '1' || cInput > '4');

        switch (cInput)
        {
        case '1':
            system("cls");
            _edit_stu();
            break;
        case '2':
            system("cls");
            _edit_course();
            break;
        case '3':
            system("cls");
            _edit_elective();
            break;
        case '4':
            return;
        default:break;
        }
        system("pause");
    }
}
void CInfoManage::overload_tree()//重载树，将树清空并重新生成
{
    //清空树
    courseNameTree.clear_tree();
    stuNameTree.clear_tree();
    courseIDTree.clear_tree();
    stuIDTree.clear_tree();

    //创建课程名树
    courseNameTree.create_course_name_tree();

    //创建学生名树
    stuNameTree.create_stu_name_tree();

    //创建课程ID树，并将选课信息链接到树上
    courseIDTree.create_course_ID_tree();
    courseIDTree.create_select_course_list();

    //创建学生ID树，并将选课信息链接到树上
    stuIDTree.create_stu_ID_tree();
    stuIDTree.create_select_course_list();
}
