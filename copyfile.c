#include <stdio.h>
#include <stdlib.h>
/* * * * * * * * * * * * * * * * * * *
 * CopyFile: �˺������ڸ���ָ�����ļ���ָ����λ��,
 *        ��������Windows�µ� copy, ��linux�µ� cp.
 * �����ʵ������ fread() �� fwrite(), ������������ʽ��д
 * ����ֵ: �Ǹ���: ���Ƶ��ֽ���.
 *         С��0����: �����ļ����Ƿ���ȷ����, �Ƿ�Ϸ�.
 * * * * * * * * * * * * * * * * * * */
long CopyFile(const char* file_1, const char * file_2)
{
    FILE *pfRead = fopen(file_1, "rb");// pfRead��������Դ.
    FILE *pfWrite = fopen(file_2, "wb");// pfWrite��Ӧ���Ƴ��������ļ�.
    if (NULL == pfRead || NULL == pfWrite)
    {
        fclose(pfRead);
        fclose(pfWrite);
        return -1;
    }
    long bytesCount = 0;//ͳ�Ƹ��Ƶ��ֽ���. long�����Ա�ʾ������2GB���ļ�

    /* ��ΪCû��byte���ͣ�����������char���
     * ò�ƶԴ����������˵��char���� ���ֽ�
     */
    int arrLen = 1024;   //����ǻ��������Ԫ�ش�С
    char bufArr[arrLen]; //����� "����", ������ֽ����� elementSize * arrLen.
    int copiedLen;      //�������������¼fread����ÿһ��������ȡ��Ԫ����
    int elementSize = sizeof(bufArr[0]);
    do
    {
        copiedLen = 0;

        copiedLen = fread(bufArr, elementSize, arrLen, pfRead);
        fwrite(bufArr, elementSize, copiedLen, pfWrite);

        bytesCount += copiedLen * elementSize;

    } while(copiedLen == arrLen);

    //�ر���.
    fclose(pfRead);
    fclose(pfWrite);

    return bytesCount;
}

/* �˳���������в��� ��ȡ�ļ���(·��):
 *      C:\>application_name file1_name file2_name
 * Example��
 *      C:\>cfilecopy.exe e:\abc.txt f:\abc2.txt
 * abc.txt������ڣ�abc2.txt���Բ����ڣ����Զ������ļ�.
 * ���abc2.txt�Ѵ��ڣ��ᱻ���ǵ�.
 *   (������ʾ:ע�Ᵽ����Ҫ���ļ�, ��"��"��!)
 * */
int main(int argc, char *argv[])
{
    if(argc == 3)
    {

        char * f1 = argv[1];
        char * f2 = argv[2];

        printf("Copy File 1: %s\n To File 2: %s\n", f1, f2);
        puts("Copying......");

        long bytesCount = CopyFile(f1, f2);

        if (bytesCount < 0)
        {
            puts("Fail to copy.");
        }
        else
        {
            printf("  %ld bytes wrote into %s.\n", bytesCount, f2);
        }
    }
    else
    {
        puts("parameters error");
    }
    //getchar();
    return 0;
}
