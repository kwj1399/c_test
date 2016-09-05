#include <stdio.h>
#include <stdlib.h>
/* * * * * * * * * * * * * * * * * * *
 * CopyFile: 此函数用于复制指定的文件到指定的位置,
 *        功能算是Windows下的 copy, 或linux下的 cp.
 * 这里的实现用了 fread() 和 fwrite(), 二进制流的形式读写
 * 返回值: 非负数: 复制的字节数.
 *         小于0的数: 请检查文件名是否正确输入, 是否合法.
 * * * * * * * * * * * * * * * * * * */
long CopyFile(const char* file_1, const char * file_2)
{
    FILE *pfRead = fopen(file_1, "rb");// pfRead用作复制源.
    FILE *pfWrite = fopen(file_2, "wb");// pfWrite对应复制出来的新文件.
    if (NULL == pfRead || NULL == pfWrite)
    {
        fclose(pfRead);
        fclose(pfWrite);
        return -1;
    }
    long bytesCount = 0;//统计复制的字节数. long最大可以表示不超过2GB的文件

    /* 因为C没有byte类型，所以这里用char替代
     * 貌似对大多数机器来说，char都是 单字节
     */
    int arrLen = 1024;   //这个是缓存数组的元素大小
    char bufArr[arrLen]; //这个是 "缓存", 缓存的字节数是 elementSize * arrLen.
    int copiedLen;      //这个变量用来记录fread函数每一次真正读取的元素数
    int elementSize = sizeof(bufArr[0]);
    do
    {
        copiedLen = 0;

        copiedLen = fread(bufArr, elementSize, arrLen, pfRead);
        fwrite(bufArr, elementSize, copiedLen, pfWrite);

        bytesCount += copiedLen * elementSize;

    } while(copiedLen == arrLen);

    //关闭流.
    fclose(pfRead);
    fclose(pfWrite);

    return bytesCount;
}

/* 此程序从命令行参数 获取文件名(路径):
 *      C:\>application_name file1_name file2_name
 * Example：
 *      C:\>cfilecopy.exe e:\abc.txt f:\abc2.txt
 * abc.txt必须存在，abc2.txt可以不存在，会自动创建文件.
 * 如果abc2.txt已存在，会被覆盖掉.
 *   (友情提示:注意保存重要的文件, 别被"盖"了!)
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
