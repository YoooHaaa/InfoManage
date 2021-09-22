#include "CStuNameTree.h"
#include<cstring> 
#include <iostream>
#include <fstream>

using namespace std;

void CStuNameTree::add_stu_info(char* szInfo) //添加学生信息，写进树中，仅用于查询
{
    build_tree(szInfo);
}
void CStuNameTree::_insert_data(Node* pDest, Node* pNode)
{
    if (strcmp(pNode->pszName, pDest->pszName) == 0)//同名,则插入链表中
    {
        SameName* pTemp = new SameName;
        if (pTemp == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
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

void CStuNameTree::build_tree(char* szInfo)//将课程信息包传入，构建节点，插入树中
{
    Node* pNode = new Node;
    if (pNode == nullptr)
    {
        cout << "空间申请失败！请关闭程序并重试..." << endl;
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
        cout << "空间申请失败！请关闭程序并重试..." << endl;
        system("pause");
        exit(0);
    }
    strcpy_s(pNode->pszID, strlen(pTemp) + 1, pTemp);
    pNode->pszName = new char[strlen(&szInfo[i + 1]) + 1];
    if (pNode->pszName == nullptr)
    {
        cout << "空间申请失败！请关闭程序并重试..." << endl;
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
void CStuNameTree::create_stu_name_tree() //以课程名作为标准，创建树
{
    ifstream readCour("stu_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "打开文件stu_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }
    if (pRoot != nullptr)
    {
        clear_tree();
    }
    while (!readCour.eof())   //读取文件信息，创建树
    {
        char szInfo[512] = { 0 };
        readCour.getline(szInfo, 512, 0);//读取一个512位字符串，遇到0结束

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

    if (pNode == pNode->pParents->pLeftChild)//为左孩子
    {
        pNode->pParents->nLeftHight = _max_hight(pNode) + 1;
    }
    else//为右孩子
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
    if (pNode->nLeftHight - pNode->nRightHight >= 2)//左层过高,先调整平衡，再修改父母层高
    {
        //先找到旋转因子pNode->pLeftChild
        //判断左孩子的后继是否都是左层过高，如果是右层过高，就先转化
        //旋转
        //将此时替换pNode位置的节点作为参数传进来继续递归

        if (pNode->pLeftChild->nLeftHight - pNode->pLeftChild->nRightHight < 0)//判断旋转因子是否也是左高
        {
            Node* pTempNode = pNode->pLeftChild;
            Node* pTemp = pTempNode->pRightChild;
            _anticlockwise_rotate(pTempNode);//

            pTempNode->nRightHight = pTemp->nLeftHight;//调整位置后，修改相应被改变的层高
            pTemp->nLeftHight = _max_hight(pTempNode) + 1;
        }

        Node* pTemp = pNode->pLeftChild;
        _clockwise_rotate(pNode);//顺时针旋转之后，位置会发生改变

                                 //调整位置后，修改相应被改变的层高       
        pNode->nLeftHight = pTemp->nRightHight;

        pTemp->nRightHight = _max_hight(pNode) + 1;

        _change_hight(pTemp);          //修改父母的层高
        _balance_hight(pTemp->pParents);//传入父母，递归修改
    }
    else if (pNode->nLeftHight - pNode->nRightHight <= -2)//右层过高
    {
        if (pNode->pRightChild->nLeftHight - pNode->pRightChild->nRightHight > 0)//判断旋转因子是否也是左高
        {
            Node* pTempNode = pNode->pRightChild;
            Node* pTemp = pTempNode->pLeftChild;
            _clockwise_rotate(pTempNode);
            pTempNode->nLeftHight = pTemp->nRightHight; //调整位置后，修改相应被改变的层高
            pTemp->nRightHight = _max_hight(pTempNode) + 1;
        }

        Node* pTemp = pNode->pRightChild;
        _anticlockwise_rotate(pNode);//逆时针旋转之后，位置会发生改变

                                     //调整位置后，修改相应被改变的层高
        pNode->nRightHight = pTemp->nLeftHight;

        pTemp->nLeftHight = _max_hight(pNode) + 1;
        _change_hight(pTemp);          //修改父母的层高
        _balance_hight(pTemp->pParents);//传入父母，递归修改
    }
    else//平衡
    {
        _change_hight(pNode);          //修改父母的层高
        _balance_hight(pNode->pParents);//传入父母，递归修改
    }
}
void CStuNameTree::_clockwise_rotate(Node* pNode)    //顺时针
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
void CStuNameTree::_anticlockwise_rotate(Node* pNode)//逆时针
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

void CStuNameTree::use_stu_search_ID(char* szName)//通过学生名，查找到课程ID号
{
    Node* pTemp = _search_data(pRoot, szName);

    if (pTemp == nullptr)
    {
        cout << "==================" << endl;
        cout << "未找到该学生信息！" << endl;
        cout << "==================" << endl;
        return ;
    }

    cout << "================================================" << endl;
    cout << "查询结果  ID:" << pTemp->pszID << "   姓名：" << szName << endl;
    SameName* pSame = pTemp->pHead;
    while (pSame)
    {
        cout << "查询结果  ID:" << pSame->pszID << "   姓名：" << szName << endl;
        pSame = pSame->pNext;
    }
    cout << "================================================" << endl;
}
void CStuNameTree::clear_tree()
{
    _free_root(pRoot);
    pRoot = nullptr;
}