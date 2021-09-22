#pragma once
#include <iostream>

using namespace std;

/*
*课程名树：
*结构： 以课程名为标准进行排序生成的平衡二叉树
*功能： 1 课程的添加
*       2 课程名查找ID
*/

class CCourseNameTree
{
private:
    //以课程名排序的课程树
    struct Node
    {
        char* pszID = nullptr;       //课程ID
        char* pszCourse = nullptr;   //课程名
        int nLeftHight = 1;          //左边的层高
        int nRightHight = 1;         //右边的层高
        Node* pParents = nullptr;    //双亲指针
        Node* pLeftChild = nullptr;  //左孩子指针
        Node* pRightChild = nullptr; //右孩子指针
    };

public:
    //从根节点开始，释放所有资源
    ~CCourseNameTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //释放根节点关联的数据
    void _free_root(Node* pNode);                

public:
    //以课程名作为标准，创建树
    void create_course_name_tree();   

    //添加课程信息,写入文件和树中
    void add_course_info(char* szInfo);  

    //传入参数课程名字和ID，创建树
    void build_tree(char* szInfo);          

    //将节点pNode插入树中
    void _insert_data(Node* pDest, Node* pNode);      

    //将树清空,才能重新读取文件
    void clear_tree();                               

    //释放节点
    void _delete_Node(Node* pNode);

    //搜索数据，并返回该节点指针
    Node* _search_data(Node* pNode, char* szCourse); 

    //通过课程名，查找到ID号,并返回
    char* use_course_search_ID(char* szCourse);      

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