#pragma once
#include <iostream>

using namespace std;

/*
*课程ID树：
*结构： 以课程ID为标准进行排序生成的平衡二叉树
*功能： 1 课程的添加
*       2 ID查找课程
*       3 ID查找选课记录
*       4 删除课程
*/

class CCourseIDTree//
{
private:
    //选课学生树，以链表的形式链接在数的每个节点上，记录该课程的选修记录
    struct StuList
    {
        char* pszStuName = nullptr;   //学生名
        char* pszStuID = nullptr;     //学生ID
        char* pszStuScore = nullptr;  //学生成绩
        StuList* pNext = nullptr;     //指向下一个学生
    };

    //以课程ID排序的课程树
    struct Node  
    {
        char* pszID = nullptr;       //课程ID
        char* pszCourse = nullptr;   //课程名
        int nLeftHight = 1;          //左边的层高
        int nRightHight = 1;         //右边的层高
        Node* pParents = nullptr;    //双亲指针
        Node* pLeftChild = nullptr;  //左孩子指针
        Node* pRightChild = nullptr; //右孩子指针
        StuList* pHead = nullptr;    //选择该课程的学生的链表的头节点
    };

public:
    //从根节点开始，释放所有资源
    ~CCourseIDTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //释放课程根节点关联的数据
    void _free_root(Node* pNode);   

    //释放选课学生根节点关联的数据
    void _free_list(StuList* pHead);   

public:
    //以课程名作为标准，创建树
    void create_course_ID_tree();      

    //传入参数课程名字和ID，创建树,szInfo为ID_name格式
    void build_tree(char* szInfo);        

    //将节点pNode插入课程树中
    void _insert_data(Node* pDest, Node* pNode);   

    //检查课程ID是否存在
    bool _check_ID(char* szCourseID);  

    //添加课程信息,写入文件和树中，szInfo为ID_name格式
    void add_course_info(char* szInfo);           

    //创建课程的选课记录，并插在树的节点上
    void create_select_course_list();    

    //传入参数选课信息，找到课程ID，接入链表，szInfo为学生ID_name_score
    void build_stu_list(Node* pNode, StuList* pStuList);             

    //搜索选课记录
    void search_select_course_record(char* szCourseID);              

    //清空树中的资源，将树清空,才能重新读取文件
    void clear_tree();                                   

    //传入参数课程ID，删除课程
    bool del_data(char* szID);     

    //删除指定节点
    void _del_node(Node* pNode);  

    //删除树中的链表
    void _del_list(StuList* pHead);     

    //释放链表
    void _delete_StuList(StuList* pFree);     

    //释放节点
    void _delete_Node(Node* pNode);                      

    //搜索数据，并返回该节点指针
    Node* _search_data(Node* pNode, char* szID);  

    //通过课程ID，查找到课程,并打印
    char* use_ID_search_name(char* szID);             

    //修改课程信息
    bool edit_info(char* szCourseID, char* szCourseName);
public:
    //更新文件信息
    void update_file();                         

    //用先序遍历来将数据写入文件
    void _first_traversal_to_file(Node* pNode, ofstream& writeCourse, ofstream& writeSelectCourse);  

    //将选课信息写入文件
    void write_select_file(Node* pNode, ofstream& writeCourse);    

    //将课程信息写入文件
    void write_course_file(Node* pNode, ofstream& writeCourse);

private:
    //从叶子开始平衡受影响节点的层高
    void _balance_hight(Node* pNode);     

    //顺时针旋转节点
    void _clockwise_rotate(Node* pNode);        

    //逆时针旋转节点
    void _anticlockwise_rotate(Node* pNode);    

    //返回当前节点左右层高的最大值
    int _max_hight(Node* pNode);      

    //修改父母的层高
    void _change_hight(Node* pNode);             

private:
    Node* pRoot = nullptr;//指向树的根节点
};