#include "CCourseIDTree.h"
#include<cstring> 
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void CCourseIDTree::add_course_info(char* szInfo) //添加课程信息，1写进文件尾 2写进树
{
    ofstream writeCourseInfo;
    writeCourseInfo.open("cour_ID_Name.bin", ios::out | ios::app); //在文件末尾进行添加
    if (writeCourseInfo.fail())
    {
        cout << "打开文件cour_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }
    writeCourseInfo.write(szInfo, strlen(szInfo) + 1); //写入课表

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

void CCourseIDTree::build_tree(char* szInfo)//将课程信息包传入，构建节点，插入树中
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
    pNode->pszCourse = new char[strlen(&szInfo[i + 1]) + 1];
    if (pNode->pszCourse == nullptr)
    {
        cout << "空间申请失败！请关闭程序并重试..." << endl;
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
void CCourseIDTree::build_stu_list(Node* pNode, StuList* pStuList)//将学生信息包传入，构建节点，插入树中，pStuList为 学生ID_学生name_score
{
    if (pNode == nullptr)
    {
        return;
    }
    pStuList->pNext = pNode->pHead;//接入链表，头插法
    pNode->pHead = pStuList;
}
void CCourseIDTree::create_select_course_list()
{
    ifstream readSelectCour("stu_select_course.bin");
    if (readSelectCour.fail())
    {
        cout << "打开文件stu_select_course.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }
    while (!readSelectCour.eof())   //读取文件信息，创建树
    {
        char szInfo[512] = { 0 };
        readSelectCour.getline(szInfo, 512, 0);//读取一个512位字符串，遇到0结束

        if (readSelectCour.eof())
        {
            break;
        }
        //szInfo结构 -->> 学生ID_学生name^课程ID_课程name_课程score^\0
        char szCourseID[36] = { 0 };//课程的ID,用于定位到课程节点，然后连接链表
        char szStuID[36] = { 0 };//szStuID为学生ID
        char szStuName[128] = { 0 };//szStuName为学生name
        char szStuScore[36] = { 0 };//szStuScore为学生score
        char *pTemp = nullptr;
        StuList* pStuList = new StuList;
        if (pStuList == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }

        int i = 0;
        while (szInfo[i] != '_')//提取学生ID
        {
            szStuID[i] = szInfo[i];
            i++;
        }
        pStuList->pszStuID = new char[strlen(szStuID) + 1];
        if (pStuList->pszStuID == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pStuList->pszStuID, strlen(szStuID) + 1, szStuID);
        pTemp = &szInfo[i + 1];

        i = 0;
        while (pTemp[i] != '^')//提取学生name
        {
            szStuName[i] = pTemp[i];
            i++;
        }
        pStuList->pszStuName = new char[strlen(szStuName) + 1];
        if (pStuList->pszStuName == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pStuList->pszStuName, strlen(szStuName) + 1, szStuName);
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//用循环获取课程ID
        {
            szCourseID[i] = pTemp[i];
            i++;
        }
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//用循环跳过课程name
        {
            i++;
        }
        pTemp = &pTemp[i + 1];//pTemp指向score了

        i = 0;
        while (pTemp[i] != '^')//用循环获取课程Score
        {
            szStuScore[i] = pTemp[i];
            i++;
        }
        pStuList->pszStuScore = new char[strlen(szStuScore) + 1];
        if (pStuList->pszStuScore == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pStuList->pszStuScore, strlen(szStuScore) + 1, szStuScore);
      
        build_stu_list(_search_data(pRoot, szCourseID), pStuList);
    }
    readSelectCour.close();
}
void CCourseIDTree::create_course_ID_tree() //以课程ID作为标准，创建树
{
    ifstream readCour("cour_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "打开文件cour_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
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

    if (pNode == pNode->pParents->pLeftChild)//为左孩子
    {
        pNode->pParents->nLeftHight = _max_hight(pNode) + 1;
    }
    else//为右孩子
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
void CCourseIDTree::_clockwise_rotate(Node* pNode)    //顺时针
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
void CCourseIDTree::_anticlockwise_rotate(Node* pNode)//逆时针
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
void CCourseIDTree::write_course_file(Node* pNode, ofstream& writeCourse) //写课程表
{
    char szInfo[512] = { 0 };

    strcpy_s(szInfo, 512, pNode->pszID);
    strcat_s(szInfo, 512, "_");
    strcat_s(szInfo, 512, pNode->pszCourse);
    writeCourse.write(szInfo, strlen(szInfo) + 1);
}
void CCourseIDTree::write_select_file(Node* pNode, ofstream& writeSelectCourse) //写选课表
{
    StuList* pStuHead = pNode->pHead;
    if (pStuHead == nullptr)//该门课程无人选修
    {
        return; 
    }

    while (pStuHead)
    {
        char szInfo[1024] = { 0 };  //将选课信息按照一定的格式载入此数组
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

        writeSelectCourse.write(szInfo, strlen(szInfo) + 1);//将选课信息写入文件
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
        cout << "打开文件cour_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }
    ofstream writeSelectCourse("stu_select_course.bin");
    if (writeSelectCourse.fail())
    {
        cout << "打开文件stu_select_course.bin失败，请关闭程序，并重试！" << endl;
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
    if (pNode->pLeftChild == nullptr && pNode->pRightChild == nullptr)//叶子节点
    {
        if (pNode == pRoot)
        {
            _delete_Node(pNode);
            pRoot = nullptr;
            return;
        }
        if (pNode == pNode->pParents->pLeftChild)//为左孩子
        {
            pNode->pParents->nLeftHight = 1;
            pNode->pParents->pLeftChild = nullptr;
        }
        else//为右孩子
        {
            pNode->pParents->nRightHight = 1;
            pNode->pParents->pRightChild = nullptr;
        }

        _balance_hight(pNode->pParents);
        _delete_Node(pNode);
    }
    else if (pNode->pLeftChild != nullptr && pNode->pRightChild == nullptr)//只有左孩子
    {
        if (pNode == pRoot)
        {
            pRoot = pNode->pLeftChild;
            pNode->pLeftChild->pParents = nullptr;
            _delete_Node(pNode);
            return;
        }

        if (pNode == pNode->pParents->pLeftChild)//为父母的左孩子
        {
            pNode->pParents->pLeftChild = pNode->pLeftChild;
            pNode->pLeftChild->pParents = pNode->pParents;
        }
        else//为父母的右孩子
        {
            pNode->pParents->pRightChild = pNode->pLeftChild;
            pNode->pLeftChild->pParents = pNode->pParents;
        }
        _change_hight(pNode->pLeftChild);
        _balance_hight(pNode->pLeftChild->pParents);
        _delete_Node(pNode);
    }
    else if (pNode->pLeftChild == nullptr && pNode->pRightChild != nullptr)//只有右孩子
    {
        if (pNode == pRoot)
        {
            pRoot = pNode->pRightChild;
            pNode->pRightChild->pParents = nullptr;
            _delete_Node(pNode);
            return;
        }

        if (pNode == pNode->pParents->pLeftChild)//为父母的左孩子
        {
            pNode->pParents->pLeftChild = pNode->pRightChild;
            pNode->pRightChild->pParents = pNode->pParents;
        }
        else//为父母的右孩子
        {
            pNode->pParents->pRightChild = pNode->pRightChild;
            pNode->pRightChild->pParents = pNode->pParents;
        }
        _change_hight(pNode->pRightChild);
        _balance_hight(pNode->pRightChild->pParents);
        _delete_Node(pNode);
    }
    else//左右孩子都有
    {
        Node* pTemp = pNode->pLeftChild;    //此节点用来寻找替代节点

        while (pTemp->pRightChild)
        {
            pTemp = pTemp->pRightChild;
        }

        Node* pEdit = pTemp->pParents;//此节点层高第一个发生改变，需要平衡层高
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
bool CCourseIDTree::_check_ID(char* szCourseID)//检查课程ID是否存在
{
    if (_search_data(pRoot, szCourseID) == nullptr)
    {
        return false;
    }
    return true;
}
char* CCourseIDTree::use_ID_search_name(char* szID)//通过课程ID，查找到课程名
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
        cout << "未找到该课程" << endl;
        return;
    }

    cout << "课程ID：" << szCourseID << "   课程名：" << pNode->pszCourse << "   选修该门课程的学生有：" << endl << endl;//打印出课程信息

    StuList* pHead = pNode->pHead;
    if (pHead == nullptr)
    {
        cout << "该课程没有人选" << endl;
        return;
    }

    while (pHead)//打印出所有选课信息
    {
        cout << "学生ID:" << pHead->pszStuID << "   学生名:" << setw(10) << left << pHead->pszStuName << "   成绩" << pHead->pszStuScore << endl;
        pHead = pHead->pNext;
    }
}