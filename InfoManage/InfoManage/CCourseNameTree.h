#pragma once
#include <iostream>

using namespace std;

/*
*�γ�������
*�ṹ�� �Կγ���Ϊ��׼�����������ɵ�ƽ�������
*���ܣ� 1 �γ̵����
*       2 �γ�������ID
*/

class CCourseNameTree
{
private:
    //�Կγ�������Ŀγ���
    struct Node
    {
        char* pszID = nullptr;       //�γ�ID
        char* pszCourse = nullptr;   //�γ���
        int nLeftHight = 1;          //��ߵĲ��
        int nRightHight = 1;         //�ұߵĲ��
        Node* pParents = nullptr;    //˫��ָ��
        Node* pLeftChild = nullptr;  //����ָ��
        Node* pRightChild = nullptr; //�Һ���ָ��
    };

public:
    //�Ӹ��ڵ㿪ʼ���ͷ�������Դ
    ~CCourseNameTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //�ͷŸ��ڵ����������
    void _free_root(Node* pNode);                

public:
    //�Կγ�����Ϊ��׼��������
    void create_course_name_tree();   

    //��ӿγ���Ϣ,д���ļ�������
    void add_course_info(char* szInfo);  

    //��������γ����ֺ�ID��������
    void build_tree(char* szInfo);          

    //���ڵ�pNode��������
    void _insert_data(Node* pDest, Node* pNode);      

    //�������,�������¶�ȡ�ļ�
    void clear_tree();                               

    //�ͷŽڵ�
    void _delete_Node(Node* pNode);

    //�������ݣ������ظýڵ�ָ��
    Node* _search_data(Node* pNode, char* szCourse); 

    //ͨ���γ��������ҵ�ID��,������
    char* use_course_search_ID(char* szCourse);      

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
    Node* pRoot = nullptr;//ָ�����ĸ��ڵ�
};