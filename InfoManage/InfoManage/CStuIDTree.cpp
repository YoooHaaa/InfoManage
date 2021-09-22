#include "CStuIDTree.h"
#include<cstring> 
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void CStuIDTree::add_stu_info(char* szInfo) //���ѧ����Ϣ����д���ļ�β�� ��д����
{
    ofstream writeCourseInfo;
    writeCourseInfo.open("stu_ID_Name.bin", ios::out | ios::app); //���ļ�ĩβ�������
    if (writeCourseInfo.fail())
    {
        cout << "���ļ�stu_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }
    writeCourseInfo.write(szInfo, strlen(szInfo) + 1); //д��α�

    writeCourseInfo.close();

    build_tree(szInfo);   
}
void CStuIDTree::_insert_data(Node* pDest, Node* pNode)
{
    if (strcmp(pNode->pszID, pDest->pszID) == 0)
    {
        _delete_Node(pNode);
    }
    else if (strcmp(pNode->pszID, pDest->pszID) > 0)
    {
        if (pDest->pRightChild == nullptr)
        {
            pDest->pRightChild = pNode;
            pNode->pParents = pDest;
            _balance_hight(pNode);
        }
        else
        {
            _insert_data(pDest->pRightChild, pNode);
        }
    }
    else
    {
        if (pDest->pLeftChild == nullptr)
        {
            pDest->pLeftChild = pNode;
            pNode->pParents = pDest;
            _balance_hight(pNode);
        }
        else
        {
            _insert_data(pDest->pLeftChild, pNode);
        }
    }
}

void CStuIDTree::build_tree(char* szInfo)//��ѧ����Ϣ�����룬�����ڵ㣬��������
{
    Node* pNode = new Node;
    if (pNode == nullptr)
    {
        cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
        system("pause");
        exit(0);
    }

    char pTemp[512] = { 0 };
    int i = 0;

    if (szInfo == nullptr)
    {
        return;
    }
    while (szInfo[i] != '_')
    {
        pTemp[i] = szInfo[i];
        i++;
    }
    pNode->pszID = new char[strlen(pTemp) + 1];
    if (pNode->pszID == nullptr)
    {
        cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
        system("pause");
        exit(0);
    }
    strcpy_s(pNode->pszID, strlen(pTemp) + 1, pTemp);
    pNode->pszName = new char[strlen(&szInfo[i + 1]) + 1];
    if (pNode->pszName == nullptr)
    {
        cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
        system("pause");
        exit(0);
    }
    strcpy_s(pNode->pszName, strlen(&szInfo[i + 1]) + 1, &szInfo[i + 1]);


    if (pRoot == nullptr)
    {
        pRoot = pNode;
    }
    else
    {
        _insert_data(pRoot, pNode);
    }
}
void CStuIDTree::build_course_list(Node* pNode, CourseList* pCourseList)//��ѧ����Ϣ�����룬�����ڵ㣬�������У�pStuListΪ ѧ��ID_ѧ��name_score
{
    if (pNode == nullptr)
    {
        return;
    }
    pCourseList->pNext = pNode->pHead;//��������ͷ�巨
    pNode->pHead = pCourseList;
}
void CStuIDTree::create_select_course_list()
{
    ifstream readSelectCour("stu_select_course.bin");
    if (readSelectCour.fail())
    {
        cout << "���ļ�stu_select_course.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }
    while (!readSelectCour.eof())   //��ȡ�ļ���Ϣ��������
    {
        char szInfo[1024] = { 0 };
        readSelectCour.getline(szInfo, 1024, 0);//��ȡһ��1024λ�ַ���������0����

        if (readSelectCour.eof())
        {
            break;
        }
        //szInfo�ṹ -->> ѧ��ID_ѧ��name^�γ�ID_�γ�name_�γ�score^\0
        char szStuID[36] = { 0 };//�γ̵�ID,���ڶ�λ���γ̽ڵ㣬Ȼ����������
        char szCourseID[36] = { 0 };//szCourseIDΪ�γ�ID
        char szCourseName[128] = { 0 };//szStuNameΪ�γ�name
        char szCourseScore[36] = { 0 };//szStuScoreΪ�γ�score
        char *pTemp = nullptr;
        CourseList* pCourseList = new CourseList;
        if (pCourseList == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }

        int i = 0;
        while (szInfo[i] != '_')//��ȡѧ��ID
        {
            szStuID[i] = szInfo[i];
            i++;
        }
        pTemp = &szInfo[i + 1];

        i = 0;
        while (pTemp[i] != '^')//��ѭ������ѧ����
        {
            i++;
        }
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//��ȡ�γ�ID
        {
            szCourseID[i] = pTemp[i];
            i++;
        }
        pCourseList->pszCourseID = new char[strlen(szCourseID) + 1];
        if (pCourseList->pszCourseID == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pCourseList->pszCourseID, strlen(szCourseID) + 1, szCourseID);
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//��ȡ�γ�name
        {
            szCourseName[i] = pTemp[i];
            i++;
        }
        pCourseList->pszCourseName = new char[strlen(szCourseName) + 1];
        if (pCourseList->pszCourseName == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pCourseList->pszCourseName, strlen(szCourseName) + 1, szCourseName);
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '^')//��ȡ�γ�Score
        {
            szCourseScore[i] = pTemp[i];
            i++;
        }
        pCourseList->pszCourseScore = new char[strlen(szCourseScore) + 1];
        if (pCourseList->pszCourseScore == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pCourseList->pszCourseScore, strlen(szCourseScore) + 1, szCourseScore);

        build_course_list(_search_data(pRoot, szStuID), pCourseList);
    }
    readSelectCour.close();
}
void CStuIDTree::create_stu_ID_tree() //��ѧ��ID��Ϊ��׼��������
{
    ifstream readCour("stu_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "���ļ�stu_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }
    while (!readCour.eof())   //��ȡ�ļ���Ϣ��������
    {
        char szInfo[512] = { 0 };
        readCour.getline(szInfo, 512, 0);//��ȡһ��512λ�ַ���������0����

        if (readCour.eof())
        {
            break;
        }
        build_tree(szInfo);
    }
    readCour.close();
}
int CStuIDTree::_max_hight(Node* pNode)
{
    if (pNode->nLeftHight >= pNode->nRightHight)
    {
        return pNode->nLeftHight;
    }
    else
    {
        return pNode->nRightHight;
    }
}
void CStuIDTree::_change_hight(Node* pNode)
{
    if (pNode->pParents == nullptr)
    {
        return;
    }

    if (pNode == pNode->pParents->pLeftChild)//Ϊ����
    {
        pNode->pParents->nLeftHight = _max_hight(pNode) + 1;
    }
    else//Ϊ�Һ���
    {
        pNode->pParents->nRightHight = _max_hight(pNode) + 1;
    }
}
void CStuIDTree::_balance_hight(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    if (pNode->nLeftHight - pNode->nRightHight >= 2)//������,�ȵ���ƽ�⣬���޸ĸ�ĸ���
    {
        //���ҵ���ת����pNode->pLeftChild
        //�ж����ӵĺ���Ƿ��������ߣ�������Ҳ���ߣ�����ת��
        //��ת
        //����ʱ�滻pNodeλ�õĽڵ���Ϊ���������������ݹ�

        if (pNode->pLeftChild->nLeftHight - pNode->pLeftChild->nRightHight < 0)//�ж���ת�����Ƿ�Ҳ�����
        {
            Node* pTempNode = pNode->pLeftChild;
            Node* pTemp = pTempNode->pRightChild;
            _anticlockwise_rotate(pTempNode);//

            pTempNode->nRightHight = pTemp->nLeftHight;//����λ�ú��޸���Ӧ���ı�Ĳ��
            pTemp->nLeftHight = _max_hight(pTempNode) + 1;
        }

        Node* pTemp = pNode->pLeftChild;
        _clockwise_rotate(pNode);//˳ʱ����ת֮��λ�ûᷢ���ı�

                                 //����λ�ú��޸���Ӧ���ı�Ĳ��       
        pNode->nLeftHight = pTemp->nRightHight;

        pTemp->nRightHight = _max_hight(pNode) + 1;

        _change_hight(pTemp);          //�޸ĸ�ĸ�Ĳ��
        _balance_hight(pTemp->pParents);//���븸ĸ���ݹ��޸�
    }
    else if (pNode->nLeftHight - pNode->nRightHight <= -2)//�Ҳ����
    {
        if (pNode->pRightChild->nLeftHight - pNode->pRightChild->nRightHight > 0)//�ж���ת�����Ƿ�Ҳ�����
        {
            Node* pTempNode = pNode->pRightChild;
            Node* pTemp = pTempNode->pLeftChild;
            _clockwise_rotate(pTempNode);
            pTempNode->nLeftHight = pTemp->nRightHight; //����λ�ú��޸���Ӧ���ı�Ĳ��
            pTemp->nRightHight = _max_hight(pTempNode) + 1;
        }

        Node* pTemp = pNode->pRightChild;
        _anticlockwise_rotate(pNode);//��ʱ����ת֮��λ�ûᷢ���ı�

                                     //����λ�ú��޸���Ӧ���ı�Ĳ��
        pNode->nRightHight = pTemp->nLeftHight;

        pTemp->nLeftHight = _max_hight(pNode) + 1;
        _change_hight(pTemp);          //�޸ĸ�ĸ�Ĳ��
        _balance_hight(pTemp->pParents);//���븸ĸ���ݹ��޸�
    }
    else//ƽ��
    {
        _change_hight(pNode);          //�޸ĸ�ĸ�Ĳ��
        _balance_hight(pNode->pParents);//���븸ĸ���ݹ��޸�
    }
}
void CStuIDTree::_clockwise_rotate(Node* pNode)    //˳ʱ��
{
    Node* pTemp = pNode->pLeftChild;
    Node* pParentsTemp = pNode->pParents;

    pNode->pLeftChild = pTemp->pRightChild;
    if (pTemp->pRightChild != nullptr)
    {
        pTemp->pRightChild->pParents = pNode;
    }

    pNode->pParents = pTemp;
    pTemp->pRightChild = pNode;

    if (pNode == pRoot)
    {
        pRoot = pTemp;
        pTemp->pParents = nullptr;
    }
    else
    {
        if (pParentsTemp->pLeftChild == pNode)
        {
            pParentsTemp->pLeftChild = pTemp;
            pTemp->pParents = pParentsTemp;
        }
        else
        {
            pParentsTemp->pRightChild = pTemp;
            pTemp->pParents = pParentsTemp;
        }
    }
}
void CStuIDTree::_anticlockwise_rotate(Node* pNode)//��ʱ��
{
    Node* pTemp = pNode->pRightChild;
    Node* pParentsTemp = pNode->pParents;

    pNode->pRightChild = pTemp->pLeftChild;
    if (pTemp->pLeftChild != nullptr)
    {
        pTemp->pLeftChild->pParents = pNode;
    }

    pNode->pParents = pTemp;
    pTemp->pLeftChild = pNode;

    if (pNode == pRoot)
    {
        pRoot = pTemp;
        pTemp->pParents = nullptr;
    }
    else
    {
        if (pParentsTemp->pLeftChild == pNode)
        {
            pParentsTemp->pLeftChild = pTemp;
            pTemp->pParents = pParentsTemp;
        }
        else
        {
            pParentsTemp->pRightChild = pTemp;
            pTemp->pParents = pParentsTemp;
        }
    }
}
void CStuIDTree::write_stu_file(Node* pNode, ofstream& writeCourse) //дѧ����
{
    char szInfo[512] = { 0 };

    strcpy_s(szInfo, 512, pNode->pszID);
    strcat_s(szInfo, 512, "_");
    strcat_s(szInfo, 512, pNode->pszName);
    writeCourse.write(szInfo, strlen(szInfo) + 1);
}
void CStuIDTree::write_select_course_file(Node* pNode, ofstream& writeSelectCourse) //дѡ�α�
{
    CourseList* pCourseHead = pNode->pHead;
    if (pCourseHead == nullptr)//���ſγ�����ѡ��
    {
        return;
    }

    while (pCourseHead)
    {
        char szInfo[1024] = { 0 };  //��ѡ����Ϣ����һ���ĸ�ʽ���������
        strcpy_s(szInfo, 1024, pNode->pszID);
        strcat_s(szInfo, 1024, "_");
        strcat_s(szInfo, 1024, pNode->pszName);
        strcat_s(szInfo, 1024, "^");
        strcat_s(szInfo, 1024, pCourseHead->pszCourseID);
        strcat_s(szInfo, 1024, "_");
        strcat_s(szInfo, 1024, pCourseHead->pszCourseName);
        strcat_s(szInfo, 1024, "_");
        strcat_s(szInfo, 1024, pCourseHead->pszCourseScore);
        strcat_s(szInfo, 1024, "^");

        writeSelectCourse.write(szInfo, strlen(szInfo) + 1);//��ѡ����Ϣд���ļ�
        pCourseHead = pCourseHead->pNext;
    }
}
void CStuIDTree::_first_traversal_to_file(Node* pNode, ofstream& writeCourse, ofstream& writeSelectCourse)
{
    if (pNode == nullptr)
    {
        return;
    }
    write_stu_file(pNode, writeCourse);
    write_select_course_file(pNode, writeSelectCourse);
    _first_traversal_to_file(pNode->pLeftChild, writeCourse, writeSelectCourse);
    _first_traversal_to_file(pNode->pRightChild, writeCourse, writeSelectCourse);
}
void CStuIDTree::update_file()
{
    ofstream writeCourse("stu_ID_Name.bin");
    if (writeCourse.fail())
    {
        cout << "���ļ�stu_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    ofstream writeSelectCourse("stu_select_course.bin");
    if (writeSelectCourse.fail())
    {
        cout << "���ļ�stu_select_course.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }

    _first_traversal_to_file(pRoot, writeCourse, writeSelectCourse);//ʹ����������ķ�ʽ��������Ϣд���ļ�

    writeCourse.close();
    writeSelectCourse.close();
}
void CStuIDTree::_delete_Node(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    if (pNode->pszName)
    {
        delete pNode->pszName;
    }
    if (pNode->pszID)
    {
        delete pNode->pszID;
    }
    delete pNode;
}
void CStuIDTree::_delete_CourseList(CourseList * pFree)
{
    if (pFree == nullptr)
    {
        return;
    }
    if (pFree->pszCourseID)
    {
        delete pFree->pszCourseID;
    }
    if (pFree->pszCourseName)
    {
        delete pFree->pszCourseName;
    }
    if (pFree->pszCourseScore)
    {
        delete pFree->pszCourseScore;
    }
    delete pFree;
}
void CStuIDTree::_free_list(CourseList* pHead)
{
    if (pHead == nullptr)
    {
        return;
    }
    CourseList* pTemp = pHead;
    CourseList* pFree = pHead;

    while (pTemp)
    {
        pFree = pTemp;
        pTemp = pTemp->pNext;
        _delete_CourseList(pFree);
    }
}
void CStuIDTree::_free_root(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    _free_root(pNode->pLeftChild);
    _free_root(pNode->pRightChild);

    _free_list(pNode->pHead);
    _delete_Node(pNode);
}
void CStuIDTree::_del_node(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    if (pNode->pLeftChild == nullptr && pNode->pRightChild == nullptr)//Ҷ�ӽڵ�
    {
        if (pNode == pRoot)
        {
            _delete_Node(pNode);
            pRoot = nullptr;
            return;
        }
        if (pNode == pNode->pParents->pLeftChild)//Ϊ����
        {
            pNode->pParents->nLeftHight = 1;
            pNode->pParents->pLeftChild = nullptr;
        }
        else//Ϊ�Һ���
        {
            pNode->pParents->nRightHight = 1;
            pNode->pParents->pRightChild = nullptr;
        }

        _balance_hight(pNode->pParents);
        _delete_Node(pNode);
    }
    else if (pNode->pLeftChild != nullptr && pNode->pRightChild == nullptr)//ֻ������
    {
        if (pNode == pRoot)
        {
            pRoot = pNode->pLeftChild;
            pNode->pLeftChild->pParents = nullptr;
            _delete_Node(pNode);
            return;
        }

        if (pNode == pNode->pParents->pLeftChild)//Ϊ��ĸ������
        {
            pNode->pParents->pLeftChild = pNode->pLeftChild;
            pNode->pLeftChild->pParents = pNode->pParents;
        }
        else//Ϊ��ĸ���Һ���
        {
            pNode->pParents->pRightChild = pNode->pLeftChild;
            pNode->pLeftChild->pParents = pNode->pParents;
        }
        _change_hight(pNode->pLeftChild);
        _balance_hight(pNode->pLeftChild->pParents);
        _delete_Node(pNode);
    }
    else if (pNode->pLeftChild == nullptr && pNode->pRightChild != nullptr)//ֻ���Һ���
    {
        if (pNode == pRoot)
        {
            pRoot = pNode->pRightChild;
            pNode->pRightChild->pParents = nullptr;
            _delete_Node(pNode);
            return;
        }

        if (pNode == pNode->pParents->pLeftChild)//Ϊ��ĸ������
        {
            pNode->pParents->pLeftChild = pNode->pRightChild;
            pNode->pRightChild->pParents = pNode->pParents;
        }
        else//Ϊ��ĸ���Һ���
        {
            pNode->pParents->pRightChild = pNode->pRightChild;
            pNode->pRightChild->pParents = pNode->pParents;
        }
        _change_hight(pNode->pRightChild);
        _balance_hight(pNode->pRightChild->pParents);
        _delete_Node(pNode);
    }
    else//���Һ��Ӷ���
    {
        Node* pTemp = pNode->pLeftChild;    //�˽ڵ�����Ѱ������ڵ�

        while (pTemp->pRightChild)
        {
            pTemp = pTemp->pRightChild;
        }

        Node* pEdit = pTemp->pParents;//�˽ڵ��ߵ�һ�������ı䣬��Ҫƽ����
        if (pEdit != pNode)
        {
            pTemp->pParents->nRightHight = pTemp->nLeftHight;
            pTemp->pParents->pRightChild = pTemp->pLeftChild;
            if (pTemp->pLeftChild != nullptr)
            {
                pTemp->pLeftChild->pParents = pTemp->pParents;
            }

            pTemp->pLeftChild = pNode->pLeftChild;
            pNode->pLeftChild->pParents = pTemp;

            pTemp->pRightChild = pNode->pRightChild;
            pTemp->nRightHight = pNode->nRightHight;
            pNode->pRightChild->pParents = pTemp;

            if (pNode == pRoot)
            {
                pRoot = pTemp;
                pTemp->pParents = nullptr;
            }
            else
            {
                if (pNode = pNode->pParents->pLeftChild)
                {
                    pNode->pParents->pLeftChild = pTemp;
                    pTemp->pParents = pNode->pParents;
                }
                else
                {
                    pNode->pParents->pRightChild = pTemp;
                    pTemp->pParents = pNode->pParents;
                }
            }
            _balance_hight(pEdit);
        }
        else
        {
            pTemp->pRightChild = pNode->pRightChild;
            pNode->pRightChild->pParents = pTemp;
            pTemp->nRightHight = pNode->nRightHight;

            if (pNode == pRoot)
            {
                pRoot = pTemp;
                pTemp->pParents = nullptr;
            }
            else
            {
                if (pNode = pNode->pParents->pLeftChild)
                {
                    pNode->pParents->pLeftChild = pTemp;
                    pTemp->pParents = pNode->pParents;
                }
                else
                {
                    pNode->pParents->pRightChild = pTemp;
                    pTemp->pParents = pNode->pParents;
                }
            }
            _balance_hight(pTemp);
        }
        _delete_Node(pNode);
    }
}
void CStuIDTree::_del_list(CourseList* pHead)
{
    if (pHead == nullptr)
    {
        return;
    }
    CourseList* pTemp = pHead;
    CourseList* pFree = pHead;

    while (pTemp)
    {
        pFree = pTemp;
        pTemp = pTemp->pNext;
        _delete_CourseList(pFree);
    }
}
bool CStuIDTree::del_data(char* szStuID)
{
    Node* pTemp = _search_data(pRoot, szStuID);
    if (pTemp != nullptr)
    {
        _del_list(pTemp->pHead);
        _del_node(pTemp);
    }
    else
    {
        return false;
    }
    return true;
}
CStuIDTree::Node* CStuIDTree::_search_data(Node* pNode, char* szStuID)
{
    if (pNode == nullptr)
    {
        return nullptr;
    }

    if (strcmp(szStuID, pNode->pszID) == 0)
    {
        return pNode;
    }
    else if (strcmp(szStuID, pNode->pszID) > 0)
    {
        return _search_data(pNode->pRightChild, szStuID);
    }
    else
    {
        return _search_data(pNode->pLeftChild, szStuID);
    }
    return nullptr;
}
bool CStuIDTree::edit_info(char* szStuID, char* szStuName)
{
    Node* pTemp = _search_data(pRoot, szStuID);
    if (pTemp == nullptr)
    {
        return false;
    }
    delete pTemp->pszName;

    pTemp->pszName = new char[strlen(szStuName) + 1];
    strcpy_s(pTemp->pszName, strlen(szStuName) + 1, szStuName);

    return true;
}
bool CStuIDTree::edit_elective(char* szStuID, char* szCourseID, char* szScore)
{
    Node* pTemp = _search_data(pRoot, szStuID);
    if (pTemp == nullptr)
    {
        cout << "δ�ҵ���ѧ����Ϣ" << endl;
        return false;
    }
    CourseList* pList = pTemp->pHead;

    while (pList)
    {
        if (strcmp(pList->pszCourseID, szCourseID) == 0)
        {
            delete pList->pszCourseScore;
            pList->pszCourseScore = new char[strlen(szCourseID) + 1];
            strcpy_s(pList->pszCourseScore, strlen(szCourseID) + 1, szScore);
            return true;
        }
        pList = pList->pNext;
    }
    return false;
}
bool CStuIDTree::_check_ID(char* szStuID)//���ID�Ƿ����
{
    if (_search_data(pRoot, szStuID) == nullptr)
    {
        return false;
    }
    return true;
}
char* CStuIDTree::use_ID_search_name(char* szStuID)//ͨ��ѧ��ID�����ҵ�ѧ����
{
    Node* pTemp = _search_data(pRoot, szStuID);

    if (pTemp == nullptr)
    {
        return nullptr;
    }
    return pTemp->pszName;
}
void CStuIDTree::clear_tree()
{
    _free_root(pRoot);
    pRoot = nullptr;
}
void CStuIDTree::search_select_course_record(char* szStuID)
{
    Node* pNode = _search_data(pRoot, szStuID);

    if (pNode == nullptr)
    {
        cout << "δ�ҵ���ѧ��" << endl;
        return;
    }

    cout << "ѧ��ID��" << szStuID << "   ѧ��������" << pNode->pszName << "   ѡ����Ϣ���£�" << endl << endl;//��ӡ���γ���Ϣ

    CourseList* pHead = pNode->pHead;
    if (pHead == nullptr)
    {
        cout << "��ѧ��û��ѡ��" << endl;
        return;
    }

    while (pHead)//��ӡ������ѡ����Ϣ
    {
        cout << "�γ�ID��" << pHead->pszCourseID << "   �γ�����" << setw(35) << left << pHead->pszCourseName << "   �ɼ���" << pHead->pszCourseScore << endl;
        pHead = pHead->pNext;
    }
}
bool CStuIDTree::_check_select_course(char* szStuID, char* szCourseID) //����ѧ���Ƿ�ѡ���˸ÿγ�
{
    Node* pNode = _search_data(pRoot, szStuID);

    if (pNode == nullptr)
    {
        cout << "δ�ҵ���ѧ������Ϣ��" << endl;
        return true;
    }

    CourseList* pHead = pNode->pHead;
    while (pHead)//����ѡ����Ϣ
    {
        if (strcmp(szCourseID, pHead->pszCourseID) == 0)
        {
            cout << "��ѡ�μ�¼�Ѿ����ڣ�" << endl;
            return true;
        }
        pHead = pHead->pNext;
    }
    return false;
}
bool CStuIDTree::del_select_course_record(char* szStuID, char* szCourseID)//ɾ��ѡ�μ�¼
{
    Node* pNode = _search_data(pRoot, szStuID);
    if (pNode == nullptr)
    {
        cout << "û�и�ѧ������Ϣ��¼" << endl;
        return false;
    }

    CourseList* pCourseList = pNode->pHead;
    if (pCourseList == nullptr)
    {
        cout << "��ѧ��û��ѡ����Ϣ" << endl;
        return false;
    }

    CourseList* pTemp = pCourseList;

    while (pCourseList)
    {
        if (strcmp(pCourseList->pszCourseID, szCourseID) == 0)
        {
            if (pCourseList == pNode->pHead)
            {
                pNode->pHead = pCourseList->pNext;
            }
            else
            {
                pTemp->pNext = pCourseList->pNext;//ɾ���ÿγ̽ڵ�
            }
            
            _delete_CourseList(pCourseList);  //�ͷŽڵ�
            return true;
        }
        pTemp = pCourseList;
        pCourseList = pCourseList->pNext;
    }

    cout << "��ѧ��û��ѡ�޸��ſγ�" << endl;
    return false;
}