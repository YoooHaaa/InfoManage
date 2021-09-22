#include "CInitFile.h"
#include <ctime>
#include "CCourseNameTree.h"
#include "CStuNameTree.h"
#include "CCourseIDTree.h"
#include "CStuIDTree.h"
#include "CInfoManage.h"

int main(int argc, char* argv[])
{
    srand((unsigned)time(nullptr));

    CInfoManage infoManage;

    infoManage.info_manage();

    system("pause");
    return 0;
}