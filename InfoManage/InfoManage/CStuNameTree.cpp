#include "CStuNameTree.h"
#include<cstring> 
#include <iostream>
#include <fstream>

using namespace std;

void CStuNameTree::add_stu_info(char* szInfo) //���ѧ����Ϣ��д�����У������ڲ�ѯ
{
    build_tree(szInfo);
}
void CStuNameTree::_insert_data(Node* pDest, Node* pNode)
{
    if (strcmp(pNode->pszName, pDest->pszName) == 0)//ͬ��,�����������
    {
        SameName* pTemp = new SameName;
        if (pTemp == nullptr)
        {
            cout << "�ռ�����ʧ�ܣ���رճ�������..." << endl;
            system("pause");
            exit(0);
        }
        pTemp->pszID = pNode->pszID;
        pTemp->pNext = pDest->pHead;
        pDest->pHead = pTemp;
    }
    else if (strcmp(pNode->pszName, pDest->pszName) > 0)
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

void CStuNameTree::build_tree(char* szInfo)//���γ���Ϣ�����룬�����ڵ㣬��������
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
void CStuNameTree::create_stu_name_tree() //�Կγ�����Ϊ��׼��������
{
    ifstream readCour("stu_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "���ļ�stu_ID_Name.binʧ�ܣ���رճ��򣬲����ԣ�" << endl;
        system("pause");
        exit(0);
    }
    if (pRoot != nullptr)
    {
        clear_tree();
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
int CStuNameTree::_max_hight(Node* pNode)
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
void CStuNameTree::_change_hight(Node* pNode)
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
void CStuNameTree::_balance_hight(Node* pNode)
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
void CStuNameTree::_clockwise_rotate(Node* pNode)    //˳ʱ��
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
void CStuNameTree::_anticlockwise_rotate(Node* pNode)//��ʱ��
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
void CStuNameTree::_delete_Node(Node* pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    if (pNode->pszID)
    {
        delete pNode->pszID;
    }
    if (pNode->pszName)
    {
        delete pNode->pszName;
    }
    delete pNode;
}
void CStuNameTree::_delete_SameName(SameName* pSameName)
{
    if (pSameName == nullptr)
    {
        return;
    }
    if (pSameName->pszID)
    {
        delete pSameName->pszID;
    }
    delete pSameName;
}
void CStuNameTree::_free_list(SameName* pSameName)
{
    if (pSameName == nullptr)
    {
        return;
    }
    SameName* pTemp = pSameName;
    SameName* pFree = pSameName;

    while (pTemp)
    {
        pFree = pTemp;
        pTemp = pTemp->pNext;
        _delete_SameName(pFree);
    }
}
void CStuNameTree::_free_root(Node* pNode)
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
CStuNameTree::Node* CStuNameTree::_search_data(Node* pNode, char* szName)
{
    if (pNode == nullptr)
    {
        return nullptr;
    }
    if (strcmp(szName, pNode->pszName) == 0)
    {
        return pNode;
    }
    else if (strcmp(szName, pNode->pszName) > 0)
    {
        return _search_data(pNode->pRightChild, szName);
    }
    else
    {
        return _search_data(pNode->pLeftChild, szName);
    }
    return nullptr;
}

void CStuNameTree::use_stu_search_ID(char* szName)//ͨ��ѧ���������ҵ��γ�ID��
{
    Node* pTemp = _search_data(pRoot, szName);

    if (pTemp == nullptr)
    {
        cout << "==================" << endl;
        cout << "δ�ҵ���ѧ����Ϣ��" << endl;
        cout << "==================" << endl;
        return ;
    }

    cout << "================================================" << endl;
    cout << "��ѯ���  ID:" << pTemp->pszID << "   ������" << szName << endl;
    SameName* pSame = pTemp->pHead;
    while (pSame)
    {
        cout << "��ѯ���  ID:" << pSame->pszID << "   ������" << szName << endl;
        pSame = pSame->pNext;
    }
    cout << "================================================" << endl;
}
void CStuNameTree::clear_tree()
{
    _free_root(pRoot);
    pRoot = nullptr;
}