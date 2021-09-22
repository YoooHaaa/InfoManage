#include "CStuIDTree.h"
#include<cstring> 
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void CStuIDTree::add_stu_info(char* szInfo) //添加学生信息，先写进文件尾， 再写进树
{
    ofstream writeCourseInfo;
    writeCourseInfo.open("stu_ID_Name.bin", ios::out | ios::app); //在文件末尾进行添加
    if (writeCourseInfo.fail())
    {
        cout << "打开文件stu_ID_Name.bin失败，请关闭程序，并重试！" << endl;
        system("pause");
        exit(0);
    }
    writeCourseInfo.write(szInfo, strlen(szInfo) + 1); //写入课表

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

void CStuIDTree::build_tree(char* szInfo)//将学生信息包传入，构建节点，插入树中
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
void CStuIDTree::build_course_list(Node* pNode, CourseList* pCourseList)//将学生信息包传入，构建节点，插入树中，pStuList为 学生ID_学生name_score
{
    if (pNode == nullptr)
    {
        return;
    }
    pCourseList->pNext = pNode->pHead;//接入链表，头插法
    pNode->pHead = pCourseList;
}
void CStuIDTree::create_select_course_list()
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
        char szInfo[1024] = { 0 };
        readSelectCour.getline(szInfo, 1024, 0);//读取一个1024位字符串，遇到0结束

        if (readSelectCour.eof())
        {
            break;
        }
        //szInfo结构 -->> 学生ID_学生name^课程ID_课程name_课程score^\0
        char szStuID[36] = { 0 };//课程的ID,用于定位到课程节点，然后连接链表
        char szCourseID[36] = { 0 };//szCourseID为课程ID
        char szCourseName[128] = { 0 };//szStuName为课程name
        char szCourseScore[36] = { 0 };//szStuScore为课程score
        char *pTemp = nullptr;
        CourseList* pCourseList = new CourseList;
        if (pCourseList == nullptr)
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
        pTemp = &szInfo[i + 1];

        i = 0;
        while (pTemp[i] != '^')//用循环跳过学生名
        {
            i++;
        }
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//提取课程ID
        {
            szCourseID[i] = pTemp[i];
            i++;
        }
        pCourseList->pszCourseID = new char[strlen(szCourseID) + 1];
        if (pCourseList->pszCourseID == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pCourseList->pszCourseID, strlen(szCourseID) + 1, szCourseID);
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '_')//提取课程name
        {
            szCourseName[i] = pTemp[i];
            i++;
        }
        pCourseList->pszCourseName = new char[strlen(szCourseName) + 1];
        if (pCourseList->pszCourseName == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pCourseList->pszCourseName, strlen(szCourseName) + 1, szCourseName);
        pTemp = &pTemp[i + 1];

        i = 0;
        while (pTemp[i] != '^')//提取课程Score
        {
            szCourseScore[i] = pTemp[i];
            i++;
        }
        pCourseList->pszCourseScore = new char[strlen(szCourseScore) + 1];
        if (pCourseList->pszCourseScore == nullptr)
        {
            cout << "空间申请失败！请关闭程序并重试..." << endl;
            system("pause");
            exit(0);
        }
        strcpy_s(pCourseList->pszCourseScore, strlen(szCourseScore) + 1, szCourseScore);

        build_course_list(_search_data(pRoot, szStuID), pCourseList);
    }
    readSelectCour.close();
}
void CStuIDTree::create_stu_ID_tree() //以学生ID作为标准，创建树
{
    ifstream readCour("stu_ID_Name.bin");
    if (readCour.fail())
    {
        cout << "打开文件stu_ID_Name.bin失败，请关闭程序，并重试！" << endl;
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

    if (pNode == pNode->pParents->pLeftChild)//为左孩子
    {
        pNode->pParents->nLeftHight = _max_hight(pNode) + 1;
    }
    else//为右孩子
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
void CStuIDTree::_clockwise_rotate(Node* pNode)    //顺时针
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
void CStuIDTree::_anticlockwise_rotate(Node* pNode)//逆时针
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
void CStuIDTree::write_stu_file(Node* pNode, ofstream& writeCourse) //写学生表
{
    char szInfo[512] = { 0 };

    strcpy_s(szInfo, 512, pNode->pszID);
    strcat_s(szInfo, 512, "_");
    strcat_s(szInfo, 512, pNode->pszName);
    writeCourse.write(szInfo, strlen(szInfo) + 1);
}
void CStuIDTree::write_select_course_file(Node* pNode, ofstream& writeSelectCourse) //写选课表
{
    CourseList* pCourseHead = pNode->pHead;
    if (pCourseHead == nullptr)//该门课程无人选修
    {
        return;
    }

    while (pCourseHead)
    {
        char szInfo[1024] = { 0 };  //将选课信息按照一定的格式载入此数组
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

        writeSelectCourse.write(szInfo, strlen(szInfo) + 1);//将选课信息写入文件
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
        cout << "打开文件stu_ID_Name.bin失败，请关闭程序，并重试！" << endl;
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

    _first_traversal_to_file(pRoot, writeCourse, writeSelectCourse);//使用先序遍历的方式将树的信息写入文件

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
        cout << "未找到该学生信息" << endl;
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
bool CStuIDTree::_check_ID(char* szStuID)//检查ID是否存在
{
    if (_search_data(pRoot, szStuID) == nullptr)
    {
        return false;
    }
    return true;
}
char* CStuIDTree::use_ID_search_name(char* szStuID)//通过学生ID，查找到学生名
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
        cout << "未找到该学生" << endl;
        return;
    }

    cout << "学生ID：" << szStuID << "   学生姓名：" << pNode->pszName << "   选课信息如下：" << endl << endl;//打印出课程信息

    CourseList* pHead = pNode->pHead;
    if (pHead == nullptr)
    {
        cout << "该学生没有选课" << endl;
        return;
    }

    while (pHead)//打印出所有选课信息
    {
        cout << "课程ID：" << pHead->pszCourseID << "   课程名：" << setw(35) << left << pHead->pszCourseName << "   成绩：" << pHead->pszCourseScore << endl;
        pHead = pHead->pNext;
    }
}
bool CStuIDTree::_check_select_course(char* szStuID, char* szCourseID) //检查该学生是否选修了该课程
{
    Node* pNode = _search_data(pRoot, szStuID);

    if (pNode == nullptr)
    {
        cout << "未找到该学生的信息！" << endl;
        return true;
    }

    CourseList* pHead = pNode->pHead;
    while (pHead)//遍历选课信息
    {
        if (strcmp(szCourseID, pHead->pszCourseID) == 0)
        {
            cout << "该选课记录已经存在！" << endl;
            return true;
        }
        pHead = pHead->pNext;
    }
    return false;
}
bool CStuIDTree::del_select_course_record(char* szStuID, char* szCourseID)//删除选课记录
{
    Node* pNode = _search_data(pRoot, szStuID);
    if (pNode == nullptr)
    {
        cout << "没有该学生的信息记录" << endl;
        return false;
    }

    CourseList* pCourseList = pNode->pHead;
    if (pCourseList == nullptr)
    {
        cout << "该学生没有选课信息" << endl;
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
                pTemp->pNext = pCourseList->pNext;//删除该课程节点
            }
            
            _delete_CourseList(pCourseList);  //释放节点
            return true;
        }
        pTemp = pCourseList;
        pCourseList = pCourseList->pNext;
    }

    cout << "该学生没有选修该门课程" << endl;
    return false;
}