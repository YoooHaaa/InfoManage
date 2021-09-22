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
*�����ࣺ
*�ṹ�� ��4������Ϊ���ݳ�Ա���й���
*���ܣ� ����ɾ���ģ���
*/

class CInfoManage
{
public:
    //�ܵ��ú���
    void info_manage();   

    //ѡ����,���������ĺϷ��ԣ�Ȼ�󷵻�ѡ����
    char _choose_func();    

    //��ʼ���ļ�������Դ�ļ����ѧ����Ϣ��γ���Ϣ�����������ѡ����Ϣ,Ȼ���ȡ�ļ�������
    void init_file();

    //���ҹ����ܵ�����
    void seek_info();   

    //���빦���ܵ�����
    void insert_info();  

    //ɾ�������ܵ�����
    void del_info();    

    //�޸Ĺ����ܵ�����
    void modify_info();

    //��������������ղ���������
    void overload_tree();  

private: //����
    void _stu_ID_search_name();
    void _stu_name_search_ID();
    void _course_ID_search_name();
    void _course_name_search_ID();
    void _course_ID_search_elective();
    void _stu_ID_search_elective();

private: //����
    void _add_stu();
    void _add_course();
    void _add_elective();

private: //ɾ��
    void _del_stu();
    void _del_course();
    void _del_elective();

private: //�޸�
    void _edit_stu();
    void _edit_course();
    void _edit_elective();

private:
    //�����ܲ˵�
    void _menu_total();  

    //���Ҳ˵�
    void _menu_seek();   

    //����˵�
    void _menu_insert(); 

    //ɾ���˵�
    void _menu_del();  

    //�޸Ĳ˵�
    void _menu_edit();
private:
    CCourseIDTree courseIDTree;
    CCourseNameTree courseNameTree;
    CStuIDTree stuIDTree;
    CStuNameTree stuNameTree;
    CInitFile initFile;
};