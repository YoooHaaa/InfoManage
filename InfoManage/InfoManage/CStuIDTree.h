#pragma once
#include <iostream>

using namespace std;

/*
*ѧ��ID����
*�ṹ�� ��ѧ��IDΪ��׼�����������ɵ�ƽ�������
*���ܣ� 1 ѧ�������
*       2 ID����ѧ����
*       3 ID����ѡ�μ�¼
*       4 ɾ��ѧ��
*       5 ɾ��ѡ�μ�¼
*/

class CStuIDTree
{
private:
    //ѡ��ѧ������
    struct CourseList
    {
        char* pszCourseName = nullptr;   //�γ���
        char* pszCourseID = nullptr;     //�γ�ID
        char* pszCourseScore = nullptr;  //�γ̳ɼ�
        CourseList* pNext = nullptr;     //ָ����һ���γ�
    };
    //��ID�����ѧ����
    struct Node  
    {
        char* pszID = nullptr;       //ѧ��ID
        char* pszName = nullptr;     //ѧ����
        int nLeftHight = 1;          //��ߵĲ��
        int nRightHight = 1;         //�ұߵĲ��
        Node* pParents = nullptr;    //˫��ָ��
        Node* pLeftChild = nullptr;  //����ָ��
        Node* pRightChild = nullptr; //�Һ���ָ��
        CourseList* pHead = nullptr; //��ѧ��ѡ��Ŀγ̵������ͷ�ڵ�
    };

public:
    //�Ӹ��ڵ㿪ʼ���ͷ�������Դ
    ~CStuIDTree()
    {
        _free_root(pRoot);
        pRoot = nullptr;
    }

private:
    //�ͷ�ѧ�����ڵ����������
    void _free_root(Node* pNode);   

    //�ͷ�ѡ�����������
    void _free_list(CourseList* pHead);   

    //ɾ��ָ���ڵ�
    void _del_node(Node* pNode);    

    //ɾ�����е�����
    void _del_list(CourseList* pHead);    

    //�ͷ�����
    void _delete_CourseList(CourseList * pFree);    

    //�ͷŽڵ�
    void _delete_Node(Node* pNode);                      

    
 
public:
    //��ѧ��ID��Ϊ��׼��������
    void create_stu_ID_tree();    

    //��������γ����ֺ�ID��������,szInfoΪID_name��ʽ
    void build_tree(char* szInfo);         

    //���ڵ�pNode����γ�����
    void _insert_data(Node* pDest, Node* pNode);   

    //���ID�Ƿ����
    bool _check_ID(char* szStuID); 

    //���ѧ����Ϣ,д���ļ������У�szInfoΪID_name��ʽ
    void add_stu_info(char* szInfo);           

    //����ѧ����ѡ�μ�¼�����������Ľڵ���
    void create_select_course_list();      

    //�������ѡ����Ϣ���ҵ�ѧ��ID����������
    void build_course_list(Node* pNode, CourseList* pCourseList);  

    //����ĳIDѧ����ѡ����Ϣ
    void search_select_course_record(char* szStuID);              

    //����ѧ���Ƿ�ѡ���˸ÿγ�
    bool _check_select_course(char* szStuID, char* szCourseID);   

    //�������,�������¶�ȡ�ļ�
    void clear_tree();                                   

    //ɾ��ѡ�μ�¼
    bool del_select_course_record(char* szStuID, char* szCourseID);  

    //�������ѧ��ID��ɾ��ѧ����Ϣ
    bool del_data(char* szStuID);                           
    
    //�������ݣ������ظýڵ�ָ��
    Node* _search_data(Node* pNode, char* szStuID);    

    //ͨ��ѧ��ID�����ҵ�ѧ����
    char* use_ID_search_name(char* szStuID);             

    //�޸�ѧ������
    bool edit_info(char* szStuID, char* szStuName);

    //�޸�ѡ�μ�¼
    bool edit_elective(char* szStuID, char* szCourseID, char* szScore);
public:
    //�����ļ���Ϣ������ѧ�����ѡ�α�
    void update_file();  

    //�����������������д���ļ�
    void _first_traversal_to_file(Node* pNode, ofstream& writeCourse, ofstream& writeSelectCourse);  

    //��ѡ����Ϣд���ļ�
    void write_select_course_file(Node* pNode, ofstream& writeCourse);  

    //��ѧ����Ϣд���ļ�
    void write_stu_file(Node* pNode, ofstream& writeCourse);

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