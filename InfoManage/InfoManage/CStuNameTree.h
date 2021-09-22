#pragma once
#include <iostream>

using namespace std;

/*
*学生名树：
*结构： 以学生名为标准进行排序生成的平衡二叉树
*功能： 1 学生的添加
*       2 学生名查找学生ID
*/

class CStuNameTree
{
private:
    //同名学生链表
    struct SameName
    {
        char* pszID = nullptr;
        SameName* pNext = nullptr;
    };
    //以学生名排序的学生树
    struct Node
    {
        char* pszID = nullptr;       //学生ID
        char* pszName = nullptr;     //学生名
        int nLeftHight = 1;          //左边的层高
        int nRightHight = 1;         //右边的层高
        Node* pParents = nullptr;    //双亲指针
        Node* pLeftChild = nullptr;  //左孩子指针
        Node* pRightChild = nullptr; //右孩子指针
        SameName* pHead = nullptr;   //指向同名学生的头指针
    };

public:
    //从根节点开始，释放所有资源
    ~CStuNameTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //释放同名学生链表的数据
    void _free_list(SameName* pSameName);

    //释放根节点关联的数据
    void _free_root(Node* pNode);   

    //删除指定节点
    void _delete_Node(Node* pNode);

    //删除指定的同名学生链表
    void _delete_SameName(SameName* pSameName);

public:
    //以课程名作为标准，读取文件创建树
    void create_stu_name_tree();       

    //添加学生信息,写入文件和树中
    void add_stu_info(char* szInfo);   

    //传入参数课程名字和ID，创建树
    void build_tree(char* szInfo);        

    //将节点pNode插入树中
    void _insert_data(Node* pDest, Node* pNode);    

    //将树清空,才能重新读取文件
    void clear_tree();  

    //搜索数据，并返回该节点指针
    Node* _search_data(Node* pNode, char* szCourse); 

    //通过课程名，查找到ID号,直接输出
    void use_stu_search_ID(char* szCourse);         

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
    Node* pRoot = nullptr; //指向树的根节点
};