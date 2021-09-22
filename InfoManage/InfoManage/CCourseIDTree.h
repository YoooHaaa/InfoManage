#pragma once
#include <iostream>

using namespace std;

/*
*�γ�ID����
*�ṹ�� �Կγ�IDΪ��׼�����������ɵ�ƽ�������
*���ܣ� 1 �γ̵����
*       2 ID���ҿγ�
*       3 ID����ѡ�μ�¼
*       4 ɾ���γ�
*/

class CCourseIDTree//
{
private:
    //ѡ��ѧ���������������ʽ����������ÿ���ڵ��ϣ���¼�ÿγ̵�ѡ�޼�¼
    struct StuList
    {
        char* pszStuName = nullptr;   //ѧ����
        char* pszStuID = nullptr;     //ѧ��ID
        char* pszStuScore = nullptr;  //ѧ���ɼ�
        StuList* pNext = nullptr;     //ָ����һ��ѧ��
    };

    //�Կγ�ID����Ŀγ���
    struct Node  
    {
        char* pszID = nullptr;       //�γ�ID
        char* pszCourse = nullptr;   //�γ���
        int nLeftHight = 1;          //��ߵĲ��
        int nRightHight = 1;         //�ұߵĲ��
        Node* pParents = nullptr;    //˫��ָ��
        Node* pLeftChild = nullptr;  //����ָ��
        Node* pRightChild = nullptr; //�Һ���ָ��
        StuList* pHead = nullptr;    //ѡ��ÿγ̵�ѧ���������ͷ�ڵ�
    };

public:
    //�Ӹ��ڵ㿪ʼ���ͷ�������Դ
    ~CCourseIDTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //�ͷſγ̸��ڵ����������
    void _free_root(Node* pNode);   

    //�ͷ�ѡ��ѧ�����ڵ����������
    void _free_list(StuList* pHead);   

public:
    //�Կγ�����Ϊ��׼��������
    void create_course_ID_tree();      

    //��������γ����ֺ�ID��������,szInfoΪID_name��ʽ
    void build_tree(char* szInfo);        

    //���ڵ�pNode����γ�����
    void _insert_data(Node* pDest, Node* pNode);   

    //���γ�ID�Ƿ����
    bool _check_ID(char* szCourseID);  

    //��ӿγ���Ϣ,д���ļ������У�szInfoΪID_name��ʽ
    void add_course_info(char* szInfo);           

    //�����γ̵�ѡ�μ�¼�����������Ľڵ���
    void create_select_course_list();    

    //�������ѡ����Ϣ���ҵ��γ�ID����������szInfoΪѧ��ID_name_score
    void build_stu_list(Node* pNode, StuList* pStuList);             

    //����ѡ�μ�¼
    void search_select_course_record(char* szCourseID);              

    //������е���Դ���������,�������¶�ȡ�ļ�
    void clear_tree();                                   

    //��������γ�ID��ɾ���γ�
    bool del_data(char* szID);     

    //ɾ��ָ���ڵ�
    void _del_node(Node* pNode);  

    //ɾ�����е�����
    void _del_list(StuList* pHead);     

    //�ͷ�����
    void _delete_StuList(StuList* pFree);     

    //�ͷŽڵ�
    void _delete_Node(Node* pNode);                      

    //�������ݣ������ظýڵ�ָ��
    Node* _search_data(Node* pNode, char* szID);  

    //ͨ���γ�ID�����ҵ��γ�,����ӡ
    char* use_ID_search_name(char* szID);             

    //�޸Ŀγ���Ϣ
    bool edit_info(char* szCourseID, char* szCourseName);
public:
    //�����ļ���Ϣ
    void update_file();                         

    //�����������������д���ļ�
    void _first_traversal_to_file(Node* pNode, ofstream& writeCourse, ofstream& writeSelectCourse);  

    //��ѡ����Ϣд���ļ�
    void write_select_file(Node* pNode, ofstream& writeCourse);    

    //���γ���Ϣд���ļ�
    void write_course_file(Node* pNode, ofstream& writeCourse);

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