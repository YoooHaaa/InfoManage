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

void CInfoManage::info_manage()//�ܵ��ú���
{
    init_file();

    while (true)
    {
        system("cls");

        _menu_total();
        char cInput = 0;
        do 
        {
            cout << "�����빦�ܱ��:" << endl;
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
void CInfoManage::init_file()//��ʼ���ļ�������Դ�ļ����ѧ����Ϣ��γ���Ϣ�����������ѡ����Ϣ,Ȼ���ȡ�ļ�������
{
    //��ʼ���ļ���Ϣ��ֻ��Ҫ��ʼ��һ�ξ����ˣ��Ժ�Ϳ���ע�͵������Ѿ����ɹ����ļ���������
    initFile.read_name_list();
    initFile.read_course_list();
    initFile.create_select_course();
    system("cls");

    cout << "======================" << endl;
    cout << "���������ļ����Ժ�..." << endl;
    cout << "======================" << endl;

    //�����γ�����
    courseNameTree.create_course_name_tree();

    //����ѧ������
    stuNameTree.create_stu_name_tree();

    //�����γ�ID��������ѡ����Ϣ���ӵ�����
    courseIDTree.create_course_ID_tree();
    courseIDTree.create_select_course_list();

    //����ѧ��ID��������ѡ����Ϣ���ӵ�����
    stuIDTree.create_stu_ID_tree();
    stuIDTree.create_select_course_list();

}
char CInfoManage::_choose_func()//ѡ����,���������ĺϷ��ԣ�Ȼ�󷵻�ѡ����
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
            cout << "�Ƿ����룡 ���������룺" << endl;
        }
    }
    return 0;
}
void CInfoManage::_menu_total()  //�����ܲ˵�
{
    cout << "========================" << endl;
    cout << "��ѡ�����¹��ܣ�" << endl;
    cout << "1 ������Ϣ��" << endl;
    cout << "2 ������Ϣ��" << endl;
    cout << "3 ɾ����Ϣ��" << endl;
    cout << "4 �޸���Ϣ��" << endl;
    cout << "5 �˳���" << endl;
    cout << "========================" << endl;

}
void CInfoManage::_menu_seek()  //���Ҳ˵�
{
    cout << "===========================================" << endl;
    cout << "��ѡ�����¹��ܣ�" << endl;
    cout << "1 ͨ��ѧ��ID��ѯѧ��������" << endl;
    cout << "2 ͨ��ѧ��������ѯѧ��ID��" << endl;
    cout << "3 ͨ���γ�ID��ѯ�γ�����" << endl;
    cout << "4 ͨ���γ�����ѯ�γ�ID��" << endl;
    cout << "5 ͨ���γ�ID��ѯѡ���˸ÿγ̵�ѧ���Լ��ɼ���" << endl;
    cout << "6 ͨ��ѧ��ID��ѯ��ѧ��ѡ�޵Ŀγ���Ϣ��" << endl;
    cout << "7 �˳���" << endl;
    cout << "===========================================" << endl;
}
void CInfoManage::_menu_insert() //����˵�
{
    cout << "====================================" << endl;
    cout << "��ѡ�����¹��ܣ�" << endl;
    cout << "1 ����ѧ��(ID, ����)��" << endl;
    cout << "2 �����γ�(ID,����)��" << endl;
    cout << "3 ����ѡ�μ�¼(ѧ��ID, �γ�ID, ����)��" << endl;
    cout << "4 �˳���" << endl;
    cout << "====================================" << endl;
}
void CInfoManage::_menu_del()   //ɾ���˵�
{
    cout << "====================================" << endl;
    cout << "��ѡ�����¹��ܣ�" << endl;
    cout << "1 ɾ��ѧ��(ID, ����)��" << endl;
    cout << "2 ɾ���γ�(ID,����)��" << endl;
    cout << "3 ɾ��ѡ�μ�¼(ѧ��ID, �γ�ID, ����)��" << endl;
    cout << "4 �˳���" << endl;
    cout << "====================================" << endl;
}
void CInfoManage::_menu_edit()  //�޸Ĳ˵�
{
    cout << "====================================" << endl;
    cout << "��ѡ�����¹��ܣ�" << endl;
    cout << "1 �޸�ѧ��(����)��" << endl;
    cout << "2 �޸Ŀγ�(����)��" << endl;
    cout << "3 �޸�ѡ�μ�¼(����)��" << endl;
    cout << "4 �˳���" << endl;
    cout << "====================================" << endl;
}
void CInfoManage::seek_info() //���ҹ����ܵ�����
{
    while (true)
    {
        system("cls");

        _menu_seek();
        char cInput = 0;
        do
        {
            cout << "�����빦�ܱ��:" << endl;
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

    do //�ж��Ƿ������
    {
        cout << "������ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));
    

    char* pName = stuIDTree.use_ID_search_name(szStuID);
    if (pName != nullptr)
    {
        cout << "=========================================" << endl;
        cout << "��ѯ���  ID: " << szStuID << "   ������" << pName << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "==================" << endl;
        cout << "δ�ҵ���ѧ����Ϣ��" << endl;
        cout << "==================" << endl;
    }
}
void CInfoManage::_stu_name_search_ID()
{
    char szStuName[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������ѧ����������" << endl;
        cin.getline(szStuName, 1024);
    } while (!strlen(szStuName));

    stuNameTree.use_stu_search_ID(szStuName);
}
void CInfoManage::_course_ID_search_name()
{
    char szCourseID[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������γ̵�ID�ţ�" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    
    char* pName = courseIDTree.use_ID_search_name(szCourseID);
    if (pName != nullptr)
    {
        cout << "=========================================" << endl;
        cout << "��ѯ���  ID: " << szCourseID << "   �γ�����" << pName << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "==================" << endl;
        cout << "δ�ҵ��ÿγ���Ϣ��" << endl;
        cout << "==================" << endl;
    }
}
void CInfoManage::_course_name_search_ID()
{
    char szCourseName[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������γ�����" << endl;
        cin.getline(szCourseName, 1024);
    } while (!strlen(szCourseName));
    
    char* pID = courseNameTree.use_course_search_ID(szCourseName);
    if (pID != nullptr)
    {
        cout << "=========================================" << endl;
        cout << "��ѯ���  ID: " << pID << "   �γ�����" << szCourseName << endl;
        cout << "=========================================" << endl;
    }
    else
    {
        cout << "==================" << endl;
        cout << "δ�ҵ��ÿγ���Ϣ��" << endl;
        cout << "==================" << endl;
    }
}
void CInfoManage::_course_ID_search_elective()
{
    char szCourseID[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������γ̵�ID�ţ�" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    courseIDTree.search_select_course_record(szCourseID);
}
void CInfoManage::_stu_ID_search_elective()
{
    char szStuID[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    stuIDTree.search_select_course_record(szStuID);
}
void CInfoManage::insert_info() //���빦���ܵ�����
{
    while (true)
    {
        system("cls");

        _menu_insert();
        char cInput = 0;
        do
        {
            cout << "�����빦�ܱ��:" << endl;
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

    do //�ж��Ƿ������
    {
        cout << "������ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    do //�ж��Ƿ������
    {
        cout << "������ѧ����������" << endl;
        cin.getline(szStuName, 1024);
    } while (!strlen(szStuName));

    strcpy_s(szInfo, 1024, szStuID);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, szStuName);

    //����ѧ���Ƿ���ڣ���ID����飬��ΪIDʱΨһ�ģ����ֲ���Ψһ��
    if (stuIDTree._check_ID(szStuID))
    {
        cout << "=========================" << endl;
        cout << "��ѧ����Ϣ�Ѿ����ڣ�" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        stuNameTree.add_stu_info(szInfo);//�������ӵ�ѧ����Ϣ��ӵ�ѧ������������

        stuIDTree.add_stu_info(szInfo);//�������ӵ�ѧ����Ϣ��ӵ�ѧ��ID�������У���д���ļ���д���ļ��Ĳ������������н��У�

        cout << "=========================" << endl;
        cout << "ѧ����Ϣ��ӳɹ���" << endl;
        cout << "=========================" << endl;
    }
    
}
void CInfoManage::_add_course()
{
    char szCourseID[1024] = { 0 };
    char szCourseName[1024] = { 0 };
    char szInfo[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������γ�ID�ţ�" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    
    do //�ж��Ƿ������
    {
        cout << "������γ�����" << endl;
        cin.getline(szCourseName, 1024);
    } while (!strlen(szCourseName));

    strcpy_s(szInfo, 1024, szCourseID);
    strcat_s(szInfo, 1024, "_");
    strcat_s(szInfo, 1024, szCourseName);

    //�ȼ����ſγ��Ƿ����
    if (courseIDTree._check_ID(szCourseID))
    {
        cout << "=========================" << endl;
        cout << "�γ���Ϣ�Ѿ����ڣ�" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        if (courseNameTree.use_course_search_ID(szCourseName) == nullptr)//û��ͬ���Ŀγ�
        {
            courseNameTree.add_course_info(szInfo);

            courseIDTree.add_course_info(szInfo);

            cout << "=========================" << endl;
            cout << "�γ���Ϣ��ӳɹ���" << endl;
            cout << "=========================" << endl;
        }
        else
        {
            cout << "=========================" << endl;
            cout << "�Ѿ�����ͬ���Ŀγ̣�" << endl;
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

    do //�ж��Ƿ������
    {
        cout << "������ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    char* pStuName = stuIDTree.use_ID_search_name(szStuID);
    if (pStuName == nullptr)
    {
        cout << "��ѧ������Ϣ�����ڣ��������ѧ����Ϣ" << endl;
        return;
    }

    do //�ж��Ƿ������
    {
        cout << "������γ̵�ID��" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    char* pCourseName = courseIDTree.use_ID_search_name(szCourseID);
    if (pCourseName == nullptr)
    {
        cout << "�ÿγ���Ϣ�����ڣ�������ӿγ���Ϣ" << endl;
        return;
    }

    do //�ж��Ƿ������
    {
        cout << "������γ̳ɼ���" << endl;
        cin.getline(szScore, 1024);
    } while (!strlen(szScore));
 
    /*��ѡ����Ϣ�����趨�ĸ�ʽ���szInfo��*/
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

    //�жϸ�ѧ���Ƿ�ѡ���˸��ſΣ�����Ѿ�ѡ���ˣ��򱨴�������
    if (stuIDTree._check_select_course(szStuID, szCourseID) == false)
    {
        ofstream writeElectiveInfo;
        writeElectiveInfo.open("stu_select_course.bin", ios::out | ios::app); //���ļ�ĩβ�������
        if (writeElectiveInfo.fail())
        {
            cout << "���ļ�stu_select_course.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
            system("pause");
            exit(0);
        }
        writeElectiveInfo.write(szInfo, strlen(szInfo) + 1); //д��α�

        writeElectiveInfo.close();

        cout << "================================" << endl;
        cout << "���ڽ�ѡ����Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "================================" << endl << endl;

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "ѡ����Ϣ��ӳɹ���" << endl;
        cout << "=========================" << endl;
    }
}

void CInfoManage::del_info()//ɾ�������ܵ�����
{
    while (true)
    {
        system("cls");

        _menu_del();
        char cInput = 0;
        do
        {
            cout << "�����빦�ܱ��:" << endl;
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

    do //�ж��Ƿ������
    {
        cout << "������Ҫɾ��ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    //ɾ��ѧ����Ϣ
    if (stuIDTree.del_data(szStuID))
    {
        cout << "=================================" << endl;
        cout << "���ڽ�ɾ����Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "=================================" << endl << endl;

        //�����ļ���Ϣ
        stuIDTree.update_file();

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "ѧ����Ϣ�ɹ�ɾ����" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "======================================" << endl;
        cout << "ѧ����Ϣɾ��ʧ��---�޷��ҵ���ѧ����Ϣ��" << endl;
        cout << "======================================" << endl;
    }
}
void CInfoManage::_del_course()
{
    char szCourseID[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������Ҫɾ���γ̵�ID�ţ�" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    //ɾ��ѧ����Ϣ
    if (courseIDTree.del_data(szCourseID) == true)
    {
        cout << "================================" << endl;
        cout << "���ڽ�ɾ����Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "================================" << endl << endl;

        //�����ļ���Ϣ
        courseIDTree.update_file();

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "�γ���Ϣ�ɹ�ɾ����" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "==================================" << endl;
        cout << "�γ���Ϣɾ��ʧ��---�γ���Ϣ�����ڣ�" << endl;
        cout << "==================================" << endl;
    }   
}
void CInfoManage::_del_elective()
{
    char szStuID[1024] = { 0 };
    char szCourseID[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));
    if (stuIDTree._check_ID(szStuID) == false)
    {
        cout << "��ѧ������Ϣ�����ڣ��������ѧ����Ϣ" << endl;
        return;
    }

    do //�ж��Ƿ������
    {
        cout << "������γ̵�ID�ţ�" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    if (courseIDTree._check_ID(szCourseID) == false)
    {
        cout << "�ÿγ̵���Ϣ�����ڣ�������ӿγ���Ϣ" << endl;
        return;
    }

    if (stuIDTree.del_select_course_record(szStuID, szCourseID))//���ѡ�μ�¼�ɹ�ɾ������ͬ�����ļ�
    {
        cout << "=================================" << endl;
        cout << "���ڽ�ɾ����Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "=================================" << endl << endl;

        //�����ļ���Ϣ
        stuIDTree.update_file();

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "ѡ�μ�¼�ɹ�ɾ����" << endl;
        cout << "=========================" << endl;
    }  
}
void CInfoManage::_edit_stu()
{
    char szStuID[1024] = { 0 };
    char szStuName[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������Ҫ�޸�ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    do //�ж��Ƿ������
    {
        cout << "�������޸ĺ��������" << endl;
        cin.getline(szStuName, 1024);
    } while (!strlen(szStuName));

    //�޸�ѧ����Ϣ
    if (stuIDTree.edit_info(szStuID, szStuName))
    {
        cout << "=================================" << endl;
        cout << "���ڽ��޸���Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "=================================" << endl << endl;

        //�����ļ���Ϣ
        stuIDTree.update_file();

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "ѧ����Ϣ�ɹ��޸ģ�" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "======================================" << endl;
        cout << "ѧ����Ϣ�޸�ʧ��---�޷��ҵ���ѧ����Ϣ��" << endl;
        cout << "======================================" << endl;
    }
}
void CInfoManage::_edit_course()
{
    char szCourseID[1024] = { 0 };
    char szCourseName[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������Ҫ�޸Ŀγ̵�ID�ţ�" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));

    do //�ж��Ƿ������
    {
        cout << "�������޸ĺ�Ŀγ�����" << endl;
        cin.getline(szCourseName, 1024);
    } while (!strlen(szCourseName));

    //�޸Ŀγ���Ϣ
    if (courseIDTree.edit_info(szCourseID, szCourseName))
    {
        cout << "=================================" << endl;
        cout << "���ڽ��޸���Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "=================================" << endl << endl;

        //�����ļ���Ϣ
        courseIDTree.update_file();

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "�γ���Ϣ�ɹ��޸ģ�" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "======================================" << endl;
        cout << "�γ���Ϣ�޸�ʧ��---�޷��ҵ��ÿγ���Ϣ��" << endl;
        cout << "======================================" << endl;
    }
}
void CInfoManage::_edit_elective()
{
    char szStuID[1024] = { 0 };
    char szCourseID[1024] = { 0 };
    char szScore[1024] = { 0 };

    do //�ж��Ƿ������
    {
        cout << "������ѧ����ID�ţ�" << endl;
        cin.getline(szStuID, 1024);
    } while (!strlen(szStuID));

    if (stuIDTree._check_ID(szStuID) == false)
    {
        cout << "��ѧ������Ϣ�����ڣ��������ѧ����Ϣ" << endl;
        return;
    }

    do //�ж��Ƿ������
    {
        cout << "������γ̵�ID��" << endl;
        cin.getline(szCourseID, 1024);
    } while (!strlen(szCourseID));
    if (courseIDTree._check_ID(szCourseID) == false)
    {
        cout << "�ÿγ̵���Ϣ�����ڣ�������ӿγ���Ϣ" << endl;
        return;
    }

    do //�ж��Ƿ������
    {
        cout << "������γ̳ɼ���" << endl;
        cin.getline(szScore, 1024);
    } while (!strlen(szScore));


    //�жϸ�ѧ���Ƿ�ѡ���˸��ſ�
    if (stuIDTree.edit_elective(szStuID, szCourseID, szScore) == true)
    {
        cout << "=======================================" << endl;
        cout << "���ڽ��޸ĵ�ѡ����Ϣ���ļ�ͬ�������Ժ�" << endl;
        cout << "=======================================" << endl << endl;

        //�����ļ���Ϣ
        stuIDTree.update_file();

        //������
        overload_tree();

        cout << "=========================" << endl;
        cout << "ѡ����Ϣ��ӳɹ���" << endl;
        cout << "=========================" << endl;
    }
    else
    {
        cout << "====================================" << endl;
        cout << "�ɼ��޸�ʧ��--��ѧ����δѡ�޸��ſΣ�" << endl;
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
            cout << "�����빦�ܱ��:" << endl;
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
void CInfoManage::overload_tree()//��������������ղ���������
{
    //�����
    courseNameTree.clear_tree();
    stuNameTree.clear_tree();
    courseIDTree.clear_tree();
    stuIDTree.clear_tree();

    //�����γ�����
    courseNameTree.create_course_name_tree();

    //����ѧ������
    stuNameTree.create_stu_name_tree();

    //�����γ�ID��������ѡ����Ϣ���ӵ�����
    courseIDTree.create_course_ID_tree();
    courseIDTree.create_select_course_list();

    //����ѧ��ID��������ѡ����Ϣ���ӵ�����
    stuIDTree.create_stu_ID_tree();
    stuIDTree.create_select_course_list();
}
