#include "CCourseIDTree.h"
#include<cstring> 
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void CCourseIDTree::add_course_info(char* szInfo) //��ӿγ���Ϣ��1д���ļ�β 2д����
{
    ofstream writeCourseInfo;
    writeCourseInfo.open("cour_ID_Name.bin", ios::out | ios::app); //���ļ�ĩβ�������
    if (writeCourseInfo.fail())
    {
        cout << "���ļ�cour_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }
    writeCourseInfo.write(szInfo, strlen(szInfo) + 1); //д��α�

    writeCourseInfo.close();

    build_tree(szInfo);
}
void CCourseIDTree::_insert_data(Node* pDest, Node* pNode)
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

void CCourseIDTree::build_tree(char* szInfo)//���γ���Ϣ�����룬�����ڵ㣬��������
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
    pNode->pszCourse = new char[strlen(&szInfo[i + 1]) + 1];
    if (pNode->pszCourse == nullptr)
    {
        cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
        system("pause");
        exit(0);
    }
    strcpy_s(pNode->pszCourse, strlen(&szInfo[i + 1]) + 1, &szInfo[i + 1]);

    if (pRoot == nullptr)
    {
        pRoot = pNode;
    }
    else
    {
        _insert_data(pRoot, pNode);
    }
}
void CCourseIDTree::build_stu_list(Node* pNode, StuList* pStuList)//��ѧ����Ϣ�����룬�����ڵ㣬�������У�pStuListΪ ѧ��ID_ѧ��name_score
{
    if (pNode == nullptr)
    {
        return;
    }
    pStuList->pNext = pNode->pHead;//��������ͷ�巨
    pNode->pHead = pStuList;
}
void CCourseIDTree::create_select_course_list()
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
        char szInfo[512] = { 0 };
        readSelectCour.getline(szInfo, 512, 0);//��ȡһ��512λ�ַ���������0����

        if (readSelectCour.eof())
        {
            break;
        }
        //szInfo�ṹ -->> ѧ��ID_ѧ��name^�γ�ID_�γ�name_�γ�score^\0
        char szCourseID[36] = { 0 };//�γ̵�ID,���ڶ�λ���γ̽ڵ㣬Ȼ����������
        char szStuID[36] = { 0 };//szStuIDΪѧ��ID
        char szStuName[128] = { 0 };//szStuNameΪѧ��name
        char szStuScore[36] = { 0 };//szStuScoreΪѧ��score
        char *pTemp = nullptr;
        StuList* pStuList = new StuList;
        if (pStuList == nullptr)
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
        pStuList->pszStuID = new char[strlen(szStuID) + 1];
        if (pStuList->pszStuID == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pStuList->pszStuID, strlen(szStuID) + 1, szStuID);
        pTemp = &szInfo[i + 1];

        i = 0;
        while (pTemp[i] != '^')//��ȡѧ��name
        {
            szStuName[i] = pTemp[i];
            i++;
        }
        pStuList->pszStuName = new char[strlen(szStuName) + 1];
        if (pStuList->pszStuName == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pStuList->pszStuName, strlen(szStuName) + 1, szStuName);
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//��ѭ����ȡ�γ�ID
        {
            szCourseID[i] = pTemp[i];
            i++;
        }
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//��ѭ�������γ�name
        {
            i++;
        }
        pTemp = &pTemp[i + 1];//pTempָ��score��

        i = 0;
        while (pTemp[i] != '^')//��ѭ����ȡ�γ�Score
        {
            szStuScore[i] = pTemp[i];
            i++;
        }
        pStuList->pszStuScore = new char[strlen(szStuScore) + 1];
        if (pStuList->pszStuScore == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pStuList->pszStuScore, strlen(szStuScore) + 1, szStuScore);
      
        build_stu_list(_search_data(pRoot, szCourseID), pStuList);
    }
    readSelectCour.close();
}
void CCourseIDTree::create_course_ID_tree() //�Կγ�ID��Ϊ��׼��������
{
    ifstream readCour("cour_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "���ļ�cour_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
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
int CCourseIDTree::_max_hight(Node* pNode)
{
    if (pNode == nullptr)
    {
        return 0;
    }
    if (pNode->nLeftHight >= pNode->nRightHight)
    {
        return pNode->nLeftHight;
    }
    else
    {
        return pNode->nRightHight;
    }
}
void CCourseIDTree::_change_hight(Node* pNode)
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
void CCourseIDTree::_balance_hight(Node* pNode)
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
void CCourseIDTree::_clockwise_rotate(Node* pNode)    //˳ʱ��
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
void CCourseIDTree::_anticlockwise_rotate(Node* pNode)//��ʱ��
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
void CCourseIDTree::write_course_file(Node* pNode, ofstream& writeCourse) //д�γ̱�
{
    char szInfo[512] = { 0 };

    strcpy_s(szInfo, 512, pNode->pszID);
    strcat_s(szInfo, 512, "_");
    strcat_s(szInfo, 512, pNode->pszCourse);
    writeCourse.write(szInfo, strlen(szInfo) + 1);
}
void CCourseIDTree::write_select_file(Node* pNode, ofstream& writeSelectCourse) //дѡ�α�
{
    StuList* pStuHead = pNode->pHead;
    if (pStuHead == nullptr)//���ſγ�����ѡ��
    {
        return; 
    }

    while (pStuHead)
    {
        char szInfo[1024] = { 0 };  //��ѡ����Ϣ����һ���ĸ�ʽ���������
        strcpy_s(szInfo, 1024, pStuHead->pszStuID);
        strcat_s(szInfo, 1024, "_");
        strcat_s(szInfo, 1024, pStuHead->pszStuName);
        strcat_s(szInfo, 1024, "^");
        strcat_s(szInfo, 1024, pNode->pszID);
        strcat_s(szInfo, 1024, "_");
        strcat_s(szInfo, 1024, pNode->pszCourse);
        strcat_s(szInfo, 1024, "_");
        strcat_s(szInfo, 1024, pStuHead->pszStuScore);
        strcat_s(szInfo, 1024, "^");

        writeSelectCourse.write(szInfo, strlen(szInfo) + 1);//��ѡ����Ϣд���ļ�
        pStuHead = pStuHead->pNext;
    }
}
void CCourseIDTree::_first_traversal_to_file(Node* pNode, ofstream& writeCourse, ofstream& writeSelectCourse)
{
    if (pNode == nullptr)
    {
        return;
    }
    write_course_file(pNode, writeCourse);
    write_select_file(pNode, writeSelectCourse);
    _first_traversal_to_file(pNode->pLeftChild, writeCourse, writeSelectCourse);
    _first_traversal_to_file(pNode->pRightChild, writeCourse, writeSelectCourse);
}
void CCourseIDTree::update_file()
{
    ofstream writeCourse("cour_ID_Name.bin");
    if (writeCourse.fail())
    {
        cout << "���ļ�cour_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
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

    _first_traversal_to_file(pRoot, writeCourse, writeSelectCourse);
    writeCourse.close();
    writeSelectCourse.close();
}
void CCourseIDTree::_delete_Node(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    if (pNode->pszCourse)
    {
        delete pNode->pszCourse;
    }
    if (pNode->pszID)
    {
        delete pNode->pszID;
    }
    delete pNode;
}
void CCourseIDTree::_delete_StuList(StuList* pFree)
{
    if (pFree == nullptr)
    {
        return;
    }
 
    if (pFree->pszStuID)
    {
        delete pFree->pszStuID;
    }

    if (pFree->pszStuName)
    {
        delete pFree->pszStuName;
    }
 
    if (pFree->pszStuScore)
    {
        delete pFree->pszStuScore;
    }
    delete pFree;
}
void CCourseIDTree::_free_list(StuList* pHead)
{
    if (pHead == nullptr)
    {
        return;
    }
    StuList* pTemp = pHead;
    StuList* pFree = pHead;

    while (pTemp)
    {
        pFree = pTemp;
        pTemp = pTemp->pNext;
        _delete_StuList(pFree);
    }
}
void CCourseIDTree::_free_root(Node* pNode)
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

void CCourseIDTree::_del_node(Node* pNode)
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
void CCourseIDTree::_del_list(StuList* pHead)
{
    if (pHead == nullptr)
    {
        return;
    }
    StuList* pTemp = pHead;
    StuList* pFree = pHead;
    
    while (pTemp)
    {
        pFree = pTemp;
        pTemp = pTemp->pNext;
        _delete_StuList(pFree);
    }
}
bool CCourseIDTree::del_data(char* szID)
{
    Node* pTemp = _search_data(pRoot, szID);
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
CCourseIDTree::Node* CCourseIDTree::_search_data(Node* pNode, char* szID)
{
    if (pNode == nullptr)
    {
        return nullptr;
    }

    if (strcmp(szID, pNode->pszID) == 0)
    {
        return pNode;
    }
    else if (strcmp(szID, pNode->pszID) > 0)
    {
        return _search_data(pNode->pRightChild, szID);
    }
    else
    {
        return _search_data(pNode->pLeftChild, szID);
    }
    return nullptr;
}
bool CCourseIDTree::edit_info(char* szCourseID, char* szCourseName)
{
    Node* pTemp = _search_data(pRoot, szCourseID);
    if (pTemp == nullptr)
    {
        return false;
    }
    delete pTemp->pszCourse;

    pTemp->pszCourse = new char[strlen(szCourseName) + 1];
    strcpy_s(pTemp->pszCourse, strlen(szCourseName) + 1, szCourseName);

    return true;
}
bool CCourseIDTree::_check_ID(char* szCourseID)//���γ�ID�Ƿ����
{
    if (_search_data(pRoot, szCourseID) == nullptr)
    {
        return false;
    }
    return true;
}
char* CCourseIDTree::use_ID_search_name(char* szID)//ͨ���γ�ID�����ҵ��γ���
{
    Node* pTemp = _search_data(pRoot, szID);

    if (pTemp == nullptr)
    {
        return nullptr;
    }

    return pTemp->pszCourse;
}
void CCourseIDTree::clear_tree()
{
    _free_root(pRoot);
    pRoot = nullptr;
}
void CCourseIDTree::search_select_course_record(char* szCourseID)
{
    Node* pNode = _search_data(pRoot, szCourseID);

    
    if (pNode == nullptr)
    {
        cout << "δ�ҵ��ÿγ�" << endl;
        return;
    }

    cout << "�γ�ID��" << szCourseID << "   �γ�����" << pNode->pszCourse << "   ѡ�޸��ſγ̵�ѧ���У�" << endl << endl;//��ӡ���γ���Ϣ

    StuList* pHead = pNode->pHead;
    if (pHead == nullptr)
    {
        cout << "�ÿγ�û����ѡ" << endl;
        return;
    }

    while (pHead)//��ӡ������ѡ����Ϣ
    {
        cout << "ѧ��ID:" << pHead->pszStuID << "   ѧ����:" << setw(10) << left << pHead->pszStuName << "   �ɼ�" << pHead->pszStuScore << endl;
        pHead = pHead->pNext;
    }
}