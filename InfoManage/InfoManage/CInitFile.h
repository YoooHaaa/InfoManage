#pragma once
#include <iostream>

using namespace std;

/*
* ��ȡԭTXT����Ϣ��ѡȡ10W��������1000�γ̣����洢���µ��ļ��У��ٵ������ļ�������100wѡ�μ�¼
*/

class CInitFile
{
private:
    //���ڼ�¼ID������
    struct Name
    {
        char szID[50] = { 0 };
        char szName[50] = { 0 };
    };

public:
    //���������ȡ10w������������bin�ļ�
    void read_name_list();

    //�ӿγ̿��ȡ1000�γ̣�������bin�ļ�
    void read_course_list();

    //�ӿγ̱��ѧ�����ж�ȡ���ݣ����ƥ������100wѡ�μ�¼
    void create_select_course();

    //��������ɼ�
    void get_score(char* szInfo);
};
