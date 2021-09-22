#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <ctime>
#include "CInitFile.h"

using namespace std;


void CInitFile::get_score(char* szInfo)//给每个学生产生随机成绩
{
    char szScore[10] = { 0 };

    switch (rand() % 10 + 1)
    {
    case 1:
        strcpy_s(szScore, 10, "1");
        break;
    case 2:
        strcpy_s(szScore, 10, "2");
        break;
    case 3:
        strcpy_s(szScore, 10, "3");
        break;
    case 4:
        strcpy_s(szScore, 10, "4");
        break;
    case 5:
        strcpy_s(szScore, 10, "5");
        break;
    case 6:
        strcpy_s(szScore, 10, "6");
        break;
    case 7:
        strcpy_s(szScore, 10, "7");
        break;
    case 8:
        strcpy_s(szScore, 10, "8");
        break;
    case 9:
        strcpy_s(szScore, 10, "9");
        break;
    case 10:
        strcpy_s(szScore, 10, "100");
        strcat_s(szInfo, 512, "_");
        strcat_s(szInfo, 512, szScore);
        return;
    default:break;
    }

    switch (rand() % 10)
    {
    case 1:
        strcat_s(szScore, 10, "1");
        break;
    case 2:
        strcat_s(szScore, 10, "2");
        break;
    case 3:
        strcat_s(szScore, 10, "3");
        break;
    case 4:
        strcat_s(szScore, 10, "4");
        break;
    case 5:
        strcat_s(szScore, 10, "5");
        break;
    case 6:
        strcat_s(szScore, 10, "6");
        break;
    case 7:
        strcat_s(szScore, 10, "7");
        break;
    case 8:
        strcat_s(szScore, 10, "8");
        break;
    case 9:
        strcat_s(szScore, 10, "9");
        break;
    case 0:
        strcat_s(szScore, 10, "0");
        break;
    default:break;
    }
    strcat_s(szInfo, 512, "_");
    strcat_s(szInfo, 512, szScore);
}
void CInitFile::read_name_list()
{
    cout << "=========================" << endl;
    cout << "正在初始化学生信息" << endl;
    cout << "=========================" << endl << endl;

    ifstream readName("name_list.txt");
    if (readName.fail())
    {
        cout << "打开文件name_list.txt失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeName("stu_ID_Name.bin");
    if (writeName.fail())
    {
        cout << "打开文件stu_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    for (int i = 10000001; i <= 10100000; i++)
    {
        char szInfo[100] = { 0 };
        char szName[100] = { 0 };

        sprintf_s(szInfo, "%d", i);
        strcat_s(szInfo, 100, "_");
        readName >> szName;
        strcat_s(szInfo, 100, szName);
        writeName.write(szInfo, strlen(szInfo) + 1);
    }

    readName.close();
    writeName.close();

    cout << "=========================" << endl;
    cout << "学生信息表初始化成功！" << endl;
    cout << "=========================" << endl << endl;
}

void CInitFile::read_course_list()
{
    cout << "=========================" << endl;
    cout << "正在初始化课程信息" << endl;
    cout << "=========================" << endl << endl;

    

    ifstream readName("course_list.txt");
    if (readName.fail())
    {
        cout << "打开文件course_list.txt失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeName("cour_ID_Name.bin");
    if (writeName.fail())
    {
        cout << "打开文件cour_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    for (int i = 100001; i <= 101000; i++)
    {
        char szInfo[100] = { 0 };
        char szName[100] = { 0 };

        sprintf_s(szInfo, "%d", i);
        strcat_s(szInfo, 100, "_");
        readName.getline(szName, 100);
        strcat_s(szInfo, 100, szName);
        writeName.write(szInfo, strlen(szInfo) + 1);
    }

    readName.close();
    writeName.close();

    cout << "=========================" << endl;
    cout << "课程信息初始化成功！" << endl;
    cout << "=========================" << endl << endl;
}

void CInitFile::create_select_course()
{
    cout << "=========================" << endl;
    cout << "正在初始化选课信息" << endl;
    cout << "=========================" << endl << endl;

    ifstream readStu("stu_ID_Name.bin");
    if (readStu.fail())
    {
        cout << "打开文件stu_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    ifstream readCour("cour_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "打开文件cour_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeStuSelectCourse("stu_select_course.bin");
    if (writeStuSelectCourse.fail())
    {
        cout << "打开文件stu_select_course.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }

    char* pCourse[1000] = { nullptr };
    for (int i = 0; i < 1000; i++)
    {
        char szCourse[512] = { 0 };
        readCour.getline(szCourse, 512, 0);//读取一个512位字符串，遇到0结束
        
        char* pTemp = new char[strlen(szCourse) + 1];
        if (pTemp == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pTemp, strlen(szCourse) + 1, szCourse);
        pCourse[i] = pTemp;
    }

    for (int i = 1; i <= 100000; i++)
    {
        char szInfo[1024] = { 0 };//用于存储学生选课信息
        readStu.getline(szInfo, 1024, 0); //读取一个1024位字符串，遇到0结束

        int nRand[10] = { 0 };//存放10个不重复的随机数，用于取出10个课程
        int j = 0;
        for (j = 0; j < 10; j++)
        {
            char szTemp[1024] = { 0 };
            strcpy_s(szTemp, 1024, szInfo);
            strcat_s(szTemp, 1024, "^");
            while (true)
            {
                int nFlag = 0;//标记出否出现相同随机数
                nRand[j] = rand() % 1000;
                if (j != 0)
                {
                    for (int k = 0; k < j; k++)//将刚产生的随机数与前几个数依次比较
                    {
                        if (nRand[j] == nRand[k])//产生相同随机数，跳出，继续产生随机数，再次比较
                        {
                            nFlag = 1;
                            break;
                        }
                    }
                }
                if (nFlag == 0)
                {
                    break;
                }
            }

            strcat_s(szTemp, 1024, pCourse[nRand[j]]);
            get_score(szTemp);
            strcat_s(szTemp, 1024, "^");
            
            writeStuSelectCourse.write(szTemp, strlen(szTemp) + 1);
        }       
    }

    readStu.close();
    readCour.close();
    writeStuSelectCourse.close();

    for (int i = 0; i < 1000; i++)
    {
        delete pCourse[i];
    }

    cout << "=========================" << endl;
    cout << "选课信息初始化成功！" << endl;
    cout << "=========================" << endl << endl;
}