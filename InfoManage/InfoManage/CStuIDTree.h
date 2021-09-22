#pragma once
#include <iostream>

using namespace std;

/*
*学生ID树：
*结构： 以学生ID为标准进行排序生成的平衡二叉树
*功能： 1 学生的添加
*       2 ID查找学生名
*       3 ID查找选课记录
*       4 删除学生
*       5 删除选课记录
*/

class CStuIDTree
{
private:
    //选课学生链表
    struct CourseList
    {
        char* pszCourseName = nullptr;   //课程名
        char* pszCourseID = nullptr;     //课程ID
        char* pszCourseScore = nullptr;  //课程成绩
        CourseList* pNext = nullptr;     //指向下一个课程
    };
    //以ID排序的学生树
    struct Node  
    {
        char* pszID = nullptr;       //学生ID
        char* pszName = nullptr;     //学生名
        int nLeftHight = 1;          //左边的层高
        int nRightHight = 1;         //右边的层高
        Node* pParents = nullptr;    //双亲指针
        Node* pLeftChild = nullptr;  //左孩子指针
        Node* pRightChild = nullptr; //右孩子指针
        CourseList* pHead = nullptr; //该学生选择的课程的链表的头节点
    };

public:
    //从根节点开始，释放所有资源
    ~CStuIDTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //释放学生根节点关联的数据
    void _free_root(Node* pNode);   

    //释放选课链表的数据
    void _free_list(CourseList* pHead);   

    //删除指定节点
    void _del_node(Node* pNode);    

    //删除树中的链表
    void _del_list(CourseList* pHead);    

    //释放链表
    void _delete_CourseList(CourseList * pFree);    

    //释放节点
    void _delete_Node(Node* pNode);                      

    
 
public:
    //以学生ID作为标准，创建树
    void create_stu_ID_tree();    

    //传入参数课程名字和ID，创建树,szInfo为ID_name格式
    void build_tree(char* szInfo);         

    //将节点pNode插入课程树中
    void _insert_data(Node* pDest, Node* pNode);   

    //检查ID是否存在
    bool _check_ID(char* szStuID); 

    //添加学生信息,写入文件和树中，szInfo为ID_name格式
    void add_stu_info(char* szInfo);           

    //创建学生的选课记录，并插在树的节点上
    void create_select_course_list();      

    //传入参数选课信息，找到学生ID，接入链表
    void build_course_list(Node* pNode, CourseList* pCourseList);  

    //搜索某ID学生的选课信息
    void search_select_course_record(char* szStuID);              

    //检查该学生是否选修了该课程
    bool _check_select_course(char* szStuID, char* szCourseID);   

    //将树清空,才能重新读取文件
    void clear_tree();                                   

    //删除选课记录
    bool del_select_course_record(char* szStuID, char* szCourseID);  

    //传入参数学生ID，删除学生信息
    bool del_data(char* szStuID);                           
    
    //搜索数据，并返回该节点指针
    Node* _search_data(Node* pNode, char* szStuID);    

    //通过学生ID，查找到学生名
    char* use_ID_search_name(char* szStuID);             

    //修改学生姓名
    bool edit_info(char* szStuID, char* szStuName);

    //修改选课记录
    bool edit_elective(char* szStuID, char* szCourseID, char* szScore);
public:
    //更新文件信息，更新学生表和选课表
    void update_file();  

    //用先序遍历来将数据写入文件
    void _first_traversal_to_file(Node* pNode, ofstream& writeCourse, ofstream& writeSelectCourse);  

    //将选课信息写入文件
    void write_select_course_file(Node* pNode, ofstream& writeCourse);  

    //将学生信息写入文件
    void write_stu_file(Node* pNode, ofstream& writeCourse);

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