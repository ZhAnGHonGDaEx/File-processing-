#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
//����ͷ�ļ�

#define MAX_CHARACTER		0X186A0

#pragma warning(disable:4996)		//ȡ������

void HelpForCommand(void);
BOOL TestTwoFile(const char * FirstPath, const char * SecondPath);
BOOL CopyFirstTextToSecondText(const char * FirstPath, const char * SecondPath);

int main(int argc, char * argv[])
{
	//��������(��ϵͳ����)
	if (argc < 2)
	{
		//û������
		printf("Error:Have no parameter!\n");
		//����HelpForCommand�����鿴������
		HelpForCommand();
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (strcmp(argv[argc - 1], "-help") == 0)   //����
		{
			HelpForCommand();
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(argv[1], "-n") == 0)	//�Ƚ��ļ�
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
				printf("�����ļ�һ��!\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("�����ļ���һ��!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-m") == 0)
		{
			//�����ļ�
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
				printf("�Ѿ���%s���ļ����Ƶ�%s��λ��!\n", argv[2], argv[3]);
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("�����ļ�ʧ��!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-c") == 0)
		{
			//���Ƶ�һ���ļ������ݵ��ڶ����ļ�
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
				printf("�Ѿ�����һ���ļ������ݸ��Ƶ��ڶ����ļ�!\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("�����ļ�����ʧ��!\n");
				exit(EXIT_FAILURE);
			}
		}
		else if (strcmp(argv[1], "-x") == 0)
		{
			//�����ļ�
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
				printf("�Ѿ���%s���е�%s��λ��!\n", argv[2], argv[3]);
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("�����ļ�ʧ��!\n");
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
				printf("�Ѿ��ɹ�ɾ���ļ�!\n");
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("ɾ���ļ�ʧ��!\n");
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
	printf("[�÷�]		[����]			[��ʽ]\n");
	printf("  -n   ���Լ򵥱Ƚ������ļ�     -n File_1 File_2\n");
	printf("  -m   �����ļ���ĳһ���ط�     -m File_1 Path\n");
	printf("  -c   ���Ƶ�һ���ļ�������     -c File_1 File_2\n");
	printf("       ���ڶ����ļ�\n");
	printf("  -x   �����ļ���ĳһ���ط�     -x File_1 Path\n");
	printf("  -d   ǿ��ɾ����ĳһ���ļ�     -d Path\n");
	//Version:1.0.0���Ȱ汾��֮�������չ
}

BOOL TestTwoFile(const char * FirstPath, const char * SecondPath)
{
	FILE * fp1;
	FILE * fp2;

	//���ֱȽ�
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

	//���������ʹ��ļ�
	char FirstChar[2];		//��һ���ַ�Ϊ�ȴ��Ƚϵ��ַ����ڶ�Ϊ���ַ�
	char SecondChar[2];		//ͬ��

	char character1;		//��һ��������ַ�
	char character2;		//�ڶ���������ַ�

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

	//�Ѿ��������ļ�
	char FirstText[MAX_CHARACTER];		//������

	char ch1;

	int i = 0;

	while ((ch1 = getc(fp1)) != EOF)
	{
		FirstText[i] = ch1;
		i++;
	}
	FirstText[i] = '\0';

	//д���ļ�
	int j = 0;
	for (j; FirstText[j] != '\0'; j++)
	{
		putc(FirstText[j], fp2);
	}

	return TRUE;
}