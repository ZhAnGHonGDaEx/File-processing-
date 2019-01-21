#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
//包含头文件

#define MAX_CHARACTER		0X186A0

#pragma warning(disable:4996)		//取消警告

void HelpForCommand(void);
BOOL TestTwoFile(const char * FirstPath, const char * SecondPath);
BOOL CopyFirstTextToSecondText(const char * FirstPath, const char * SecondPath);

int main(int argc, char * argv[])
{
	//主调函数(由系统调用)
	if (argc < 2)
	{
		//没有命令
		printf("Error:Have no parameter!\n");
		//调用HelpForCommand函数查看命令行
		HelpForCommand();
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (strcmp(argv[argc - 1], "-help") == 0)   //帮助
		{
			HelpForCommand();
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(argv[1], "-n") == 0)	//比较文件
		{
			if (argc < 3)
			{
				printf("Please enter file_1 and file_2!\n");
				exit(EXIT_FAILURE);
			}
			else if (argc < 4)
			{
				printf("Please enter file_2!\n");
				exit(EXIT_FAILURE);
			}

			if (TestTwoFile(argv[argc - 2], argv[argc - 1]) == TRUE)
			{
				printf("两个文件一样!\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("两个文件不一致!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-m") == 0)
		{
			//复制文件
			if (argc < 3)
			{
				printf("Please enter File_1 and path!\n");
				exit(EXIT_FAILURE);
			}
			else if (argc < 4)
			{
				printf("Please enter Path!\n");
				exit(EXIT_FAILURE);
			}

			if (CopyFile(argv[2], argv[3], FALSE) != 0)
			{
				printf("已经将%s的文件复制到%s的位置!\n", argv[2], argv[3]);
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("复制文件失败!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-c") == 0)
		{
			//复制第一个文件的内容到第二个文件
			if (argc < 3)
			{
				printf("Please enter File_1 and File_2!\n");
				exit(EXIT_FAILURE);
			}
			else if (argc < 4)
			{
				printf("Please enter File_2!\n");
				exit(EXIT_FAILURE);
			}

			if (CopyFirstTextToSecondText(argv[2], argv[3]) == TRUE)
			{
				printf("已经将第一个文件的内容复制到第二个文件!\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("复制文件内容失败!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-x") == 0)
		{
			//剪切文件
			if (argc < 3)
			{
				printf("Please enter File_1 and Path!\n");
				exit(EXIT_FAILURE);
			}
			else if (argc < 4)
			{
				printf("Please enter Path!\n");
				exit(EXIT_FAILURE);
			}

			if (MoveFile(argv[2], argv[3]) != 0)
			{
				printf("已经将%s剪切到%s的位置!\n", argv[2], argv[3]);
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("剪切文件失败!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-d") == 0)
		{
			if (argc < 3)
			{
				printf("Please enter Path!\n");
				exit(EXIT_FAILURE);
			}
		
			if (DeleteFile(argv[2]) != 0)
			{
				printf("已经成功删除文件!\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("删除文件失败!\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("Error:Have no parameter!\n");
			HelpForCommand();
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}

void HelpForCommand(void)
{
	printf("[用法]		[作用]			[格式]\n");
	printf("  -n   可以简单比较两个文件     -n File_1 File_2\n");
	printf("  -m   复制文件到某一个地方     -m File_1 Path\n");
	printf("  -c   复制第一个文件的内容     -c File_1 File_2\n");
	printf("       到第二个文件\n");
	printf("  -x   剪切文件到某一个地方     -x File_1 Path\n");
	printf("  -d   强力删除掉某一个文件     -d Path\n");
	//Version:1.0.0最先版本，之后更新拓展
}

BOOL TestTwoFile(const char * FirstPath, const char * SecondPath)
{
	FILE * fp1;
	FILE * fp2;

	//逐字比较
	if ((fp1 = fopen(FirstPath, "r")) == NULL)
	{
		printf("Open first file failure!\n");
		exit(EXIT_FAILURE);
	}
	if ((fp2 = fopen(SecondPath, "r")) == NULL)
	{
		printf("Open second file failure!\n");
		exit(EXIT_FAILURE);
	}

	//如果不报错就打开文件
	char FirstChar[2];		//第一个字符为等待比较的字符，第二为空字符
	char SecondChar[2];		//同上

	char character1;		//第一个数组的字符
	char character2;		//第二个数组的字符

	while (TRUE)
	{
		character1 = getc(fp1);
		character2 = getc(fp2);

		if (character1 != EOF && character2 != EOF)
		{
			FirstChar[0] = character1;
			FirstChar[1] = '\0';
			SecondChar[0] = character2;
			SecondChar[1] = '\0';

			if (strcmp(FirstChar, SecondChar) == 0)
			{
				continue;
			}
			else
			{
				return FALSE;
			}
		}
		else if (character1 == EOF && character2 != EOF)
		{
			return FALSE;
		}
		else if (character1 != EOF && character2 == EOF)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
}

BOOL CopyFirstTextToSecondText(const char * FirstPath, const char * SecondPath)
{
	FILE * fp1;
	FILE * fp2;

	if ((fp1 = fopen(FirstPath, "r")) == NULL)
	{
		printf("Open first file fail!\n");
		exit(EXIT_FAILURE);
	}
	if ((fp2 = fopen(SecondPath, "w")) == NULL)
	{
		printf("Open second file fail!\n");
		exit(EXIT_FAILURE);
	}

	//已经打开两个文件
	char FirstText[MAX_CHARACTER];		//待复制

	char ch1;

	int i = 0;

	while ((ch1 = getc(fp1)) != EOF)
	{
		FirstText[i] = ch1;
		i++;
	}
	FirstText[i] = '\0';

	//写入文件
	int j = 0;
	for (j; FirstText[j] != '\0'; j++)
	{
		putc(FirstText[j], fp2);
	}

	return TRUE;
}