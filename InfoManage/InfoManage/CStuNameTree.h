#pragma once
#include <iostream>

using namespace std;

/*
*ѧ��������
*�ṹ�� ��ѧ����Ϊ��׼�����������ɵ�ƽ�������
*���ܣ� 1 ѧ�������
*       2 ѧ��������ѧ��ID
*/

class CStuNameTree
{
private:
    //ͬ��ѧ������
    struct SameName
    {
        char* pszID = nullptr;
        SameName* pNext = nullptr;
    };
    //��ѧ���������ѧ����
    struct Node
    {
        char* pszID = nullptr;       //ѧ��ID
        char* pszName = nullptr;     //ѧ����
        int nLeftHight = 1;          //��ߵĲ��
        int nRightHight = 1;         //�ұߵĲ��
        Node* pParents = nullptr;    //˫��ָ��
        Node* pLeftChild = nullptr;  //����ָ��
        Node* pRightChild = nullptr; //�Һ���ָ��
        SameName* pHead = nullptr;   //ָ��ͬ��ѧ����ͷָ��
    };

public:
    //�Ӹ��ڵ㿪ʼ���ͷ�������Դ
    ~CStuNameTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //�ͷ�ͬ��ѧ�����������
    void _free_list(SameName* pSameName);

    //�ͷŸ��ڵ����������
    void _free_root(Node* pNode);   

    //ɾ��ָ���ڵ�
    void _delete_Node(Node* pNode);

    //ɾ��ָ����ͬ��ѧ������
    void _delete_SameName(SameName* pSameName);

public:
    //�Կγ�����Ϊ��׼����ȡ�ļ�������
    void create_stu_name_tree();       

    //���ѧ����Ϣ,д���ļ�������
    void add_stu_info(char* szInfo);   

    //��������γ����ֺ�ID��������
    void build_tree(char* szInfo);        

    //���ڵ�pNode��������
    void _insert_data(Node* pDest, Node* pNode);    

    //�������,�������¶�ȡ�ļ�
    void clear_tree();  

    //�������ݣ������ظýڵ�ָ��
    Node* _search_data(Node* pNode, char* szCourse); 

    //ͨ���γ��������ҵ�ID��,ֱ�����
    void use_stu_search_ID(char* szCourse);         

private:
    //��Ҷ�ӿ�ʼƽ����Ӱ��ڵ�Ĳ��
    void _balance_hight(Node* pNode);      

    //˳ʱ����ת�ڵ�
    void _clockwise_rotate(Node* pNode);  

    //��ʱ����ת�ڵ�
    void _anticlockwise_rotate(Node* pNode);  

    //���ص�ǰ�ڵ����Ҳ�ߵ����ֵ
    int _max_hight(Node* pNode);         

    //�޸ĸ�ĸ�Ĳ��
    void _change_hight(Node* pNode);             

private:
    Node* pRoot = nullptr; //ָ�����ĸ��ڵ�
};