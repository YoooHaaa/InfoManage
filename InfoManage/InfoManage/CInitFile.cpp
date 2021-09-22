#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <ctime>
#include "CInitFile.h"

using namespace std;


void CInitFile::get_score(char* szInfo)//��ÿ��ѧ����������ɼ�
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
    cout << "���ڳ�ʼ��ѧ����Ϣ" << endl;
    cout << "=========================" << endl << endl;

    ifstream readName("name_list.txt");
    if (readName.fail())
    {
        cout << "���ļ�name_list.txtʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeName("stu_ID_Name.bin");
    if (writeName.fail())
    {
        cout << "���ļ�stu_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
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
    cout << "ѧ����Ϣ���ʼ���ɹ���" << endl;
    cout << "=========================" << endl << endl;
}

void CInitFile::read_course_list()
{
    cout << "=========================" << endl;
    cout << "���ڳ�ʼ���γ���Ϣ" << endl;
    cout << "=========================" << endl << endl;

    

    ifstream readName("course_list.txt");
    if (readName.fail())
    {
        cout << "���ļ�course_list.txtʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeName("cour_ID_Name.bin");
    if (writeName.fail())
    {
        cout << "���ļ�cour_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
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
    cout << "�γ���Ϣ��ʼ���ɹ���" << endl;
    cout << "=========================" << endl << endl;
}

void CInitFile::create_select_course()
{
    cout << "=========================" << endl;
    cout << "���ڳ�ʼ��ѡ����Ϣ" << endl;
    cout << "=========================" << endl << endl;

    ifstream readStu("stu_ID_Name.bin");
    if (readStu.fail())
    {
        cout << "���ļ�stu_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    ifstream readCour("cour_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "���ļ�cour_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeStuSelectCourse("stu_select_course.bin");
    if (writeStuSelectCourse.fail())
    {
        cout << "���ļ�stu_select_course.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    char* pCourse[1000] = { nullptr };
    for (int i = 0; i < 1000; i++)
    {
        char szCourse[512] = { 0 };
        readCour.getline(szCourse, 512, 0);//��ȡһ��512λ�ַ���������0����
        
        char* pTemp = new char[strlen(szCourse) + 1];
        if (pTemp == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pTemp, strlen(szCourse) + 1, szCourse);
        pCourse[i] = pTemp;
    }

    for (int i = 1; i <= 100000; i++)
    {
        char szInfo[1024] = { 0 };//���ڴ洢ѧ��ѡ����Ϣ
        readStu.getline(szInfo, 1024, 0); //��ȡһ��1024λ�ַ���������0����

        int nRand[10] = { 0 };//���10�����ظ��������������ȡ��10���γ�
        int j = 0;
        for (j = 0; j < 10; j++)
        {
            char szTemp[1024] = { 0 };
            strcpy_s(szTemp, 1024, szInfo);
            strcat_s(szTemp, 1024, "^");
            while (true)
            {
                int nFlag = 0;//��ǳ��������ͬ�����
                nRand[j] = rand() % 1000;
                if (j != 0)
                {
                    for (int k = 0; k < j; k++)//���ղ������������ǰ���������αȽ�
                    {
                        if (nRand[j] == nRand[k])//������ͬ�����������������������������ٴαȽ�
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
    cout << "ѡ����Ϣ��ʼ���ɹ���" << endl;
    cout << "=========================" << endl << endl;
}