#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXARRAYSIZE 128//��ϵͳ�����õ��������󳤶�
#define STRINGLENGTH 16//���屾ϵͳ��ʹ�õ��ַ�����Ĵ�С


char CurrentOperatorClass[STRINGLENGTH];//���浱ǰ����ϵͳ���˵İ༶
char CurrentOperatorNumber[STRINGLENGTH];//���浱ǰ��¼��ѧ��

/*************************************** ѧ����Ϣ�ṹ�� ********************************************/
struct StudentInfo
{
	char ClassNumber[STRINGLENGTH];//�༶��
	char StudentNumber[STRINGLENGTH];//ѧ��
	char StudentName[STRINGLENGTH];//����
	char StudentPassword[STRINGLENGTH];//����
};

//����һ��ѧ����Ϣ�ṹ��
struct StudentInfo createStudent(char* classNumber, char* studentNumber, char* studentName, char* studentPassword)
{
	struct StudentInfo newStudent;
	strcpy(newStudent.ClassNumber, classNumber);
	strcpy(newStudent.StudentNumber, studentNumber);
	strcpy(newStudent.StudentName, studentName);
	strcpy(newStudent.StudentPassword, studentPassword);
	return newStudent;
}
/***************************************************************************************************/

/*************************************** �༶��Ϣ�ṹ�� ********************************************/
struct ClassInfo
{
	char ClassNumber[STRINGLENGTH];//���
	char ClassLeader[STRINGLENGTH];//�༶ѧϰίԱ��ѧ��
	int StudentCount;//�༶��ǰ����
	struct StudentInfo StudentsArray[MAXARRAYSIZE];//�༶ѧ������
};

//����ѧ��
void addStudent(struct ClassInfo* currentClass, char* classNumber, char* studentNumber, char* studentName, char* studentPassword)
{
	currentClass->StudentsArray[currentClass->StudentCount++] = createStudent(classNumber, studentNumber, studentName, studentPassword);
}

//ɾ��ѧ��
void deleteStudentArr(struct ClassInfo* currentClass, char* studentNumber)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		if (!strcmp(currentClass->StudentsArray[i].StudentNumber, studentNumber))
		{
			for (j = i; j < currentClass->StudentCount - 1; j++)
			{
				currentClass->StudentsArray[j] = currentClass->StudentsArray[j + 1];
			}
			currentClass->StudentCount--;
			printf("TIPS���ѳɹ���ѧ�ţ�%s��ѧ���Ӱ༶��%s��ɾ����\n", studentNumber, currentClass->ClassNumber);
			return;
		}
	}
	printf("ERROR���༶�в�����ѧ�ţ�%s��ѧ����Ϣ��ɾ��ʧ�ܣ�\n", studentNumber);
}

//�޸�ѧ����¼����
void alterStudentArr(struct ClassInfo* currentClass, char* studentNumber, char* newPassword)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		if (!strcmp(currentClass->StudentsArray[i].StudentNumber, studentNumber))
		{
			strcpy(currentClass->StudentsArray[i].StudentPassword, newPassword);
			printf("TIPS���ѳɹ���ѧ�ţ�%s��ѧ���ĵ�¼��������Ϊ��%s\n", studentNumber, newPassword);
			return;
		}
	}
	printf("ERROR���༶�в�����ѧ�ţ�%s��ѧ����Ϣ���޸�ʧ�ܣ�\n", studentNumber);
}

//��ѯѧ����Ϣ
void queryStudentArr(struct ClassInfo* currentClass, char* studentNumber)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		if (!strcmp(currentClass->StudentsArray[i].StudentNumber, studentNumber))
		{
			printf("�༶��ţ�%s\n", currentClass->StudentsArray[i].ClassNumber);
			printf("ѧ��ѧ�ţ�%s\n", currentClass->StudentsArray[i].StudentNumber);
			printf("ѧ��������%s\n", currentClass->StudentsArray[i].StudentName);
			printf("��¼���룺%s\n", currentClass->StudentsArray[i].StudentPassword);
			return;
		}
	}
	printf("ERROR���༶�в�����ѧ�ţ�%s��ѧ����Ϣ����ѯʧ�ܣ�\n", studentNumber);
}

//��ӡ��ǰѧ���������ȫ������
void printClassInfo(struct ClassInfo* currentClass)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		printf("�༶��ţ�%s\n", currentClass->StudentsArray[i].ClassNumber);
		printf("ѧ��ѧ�ţ�%s\n", currentClass->StudentsArray[i].StudentNumber);
		printf("ѧ��������%s\n", currentClass->StudentsArray[i].StudentName);
		printf("��¼���룺%s\n", currentClass->StudentsArray[i].StudentPassword);
		printf("\n------------------------------\n\n");
	}
}

//����ѧ�����������ƥ��,ƥ��ɹ�����true�����򷵻�false
int isStudentArr(struct ClassInfo* currentClass, char * studentNumber, char * studentPassword)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		if (!strcmp(currentClass->StudentsArray[i].StudentNumber, studentNumber) && !strcmp(currentClass->StudentsArray[i].StudentPassword, studentPassword))
		{
			return 1;
		}
	}
	return 0;
}
/***************************************************************************************************/

/*************************************** �༶����ṹ�� ********************************************/
struct ListNode
{
	struct ClassInfo data;
	struct ListNode* pNext;
};

struct ListNode* createList()
{
	struct ListNode* pHead = (struct ListNode*)malloc(sizeof(struct ListNode));
	strcpy(pHead->data.ClassNumber, "�༶���");
	strcpy(pHead->data.ClassLeader, "ѧϰίԱ");
	pHead->data.StudentCount = 0;
	pHead->pNext = NULL;
	return pHead;
}

//����һ���༶�ڵ�
void createClass(struct ListNode* pHead, char* classNumber, char* leaderNumber, int studentCount)
{
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
	struct ListNode* pThis = NULL;
	strcpy(newNode->data.ClassNumber, classNumber);
	strcpy(newNode->data.ClassLeader, leaderNumber);
	newNode->data.StudentCount = studentCount;
	newNode->pNext = NULL;
	pThis = pHead;
	while (pThis->pNext)
	{
		pThis = pThis->pNext;
	}
	pThis->pNext = newNode;
}

//ɾ��һ���༶�ڵ�
void deleteClass(struct ListNode* pHead, char* classNumber)
{
	struct ListNode* pThis = pHead;
	struct ListNode* pDelete = NULL;
	while (pThis->pNext)
	{
		if (strcmp(pThis->pNext->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			break;
		}
	}
	if (pThis->pNext == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
		return;
	}
	pDelete = pThis->pNext;
	pThis->pNext = pDelete->pNext;
	free(pDelete);
	printf("TIPS���ѳɹ����༶��%s��ϵͳ��ɾ����\n", classNumber);
}

//�޸İ༶��ѧϰίԱѧ��
void alterClass(struct ListNode* pHead, char* classNumber, char* leaderNumber)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			break;
		}
	}
	if (pThis)
	{
		strcpy(pThis->data.ClassLeader, leaderNumber);
		printf("TIPS���༶ %s ��ѧϰίԱ�ѳɹ����Ϊѧ�ţ�%s��ѧ����\n", classNumber, leaderNumber);
	}
	else
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
		return;
	}
}

//��ѯһ���༶��ȫ������
void queryClass(struct ListNode* pHead, char* classNumber)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			printf("��ǰ�༶��ţ�%s\t\t", pThis->data.ClassNumber);
			printf("ѧϰίԱѧ�ţ�%s\n", pThis->data.ClassLeader);
			printf("******************** �༶ѧ����Ϣ���� ********************\n\n");
			printClassInfo(&(pThis->data));
			break;
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
	}
}

//����ѧ��
void appendStudent(struct ListNode* pHead, char* classNumber, char* studentNumber, char* studentName, char* studentPassword)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			addStudent((&pThis->data), classNumber, studentNumber, studentName, studentPassword);
			break;
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
	}
}

//ɾ��ѧ��
void deleteStudent(struct ListNode* pHead, char* classNumber, char* studentNumber)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			deleteStudentArr(&(pThis->data), studentNumber);
			break;
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
	}
}

//�޸�ѧ������
void alterStudent(struct ListNode* pHead, char* classNumber, char* studentNumber, char* newPassword)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			alterStudentArr(&(pThis->data), studentNumber, newPassword);
			break;
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
	}
}

//��ѯѧ��
void queryStudent(struct ListNode* pHead, char* classNumber, char* studentNumber)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			queryStudentArr(&(pThis->data), studentNumber);
			break;
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
	}
}

//�ж��Ƿ���һ���Ϸ���ѧ���˻��������һ��ѧ�����ж��Ƿ��ѧϰίԱ��ѧϰίԱ����1����ͨѧ������2����ݲ��Ϸ�����0
int isStudent(struct ListNode* pHead, char* classNumber, char* studentNumber, char* studentPassword)
{
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		if (strcmp(pThis->data.ClassNumber, classNumber))
		{
			pThis = pThis->pNext;
		}
		else
		{
			//˵������༶�������ȷ���ڵģ��������༶�����ѧ��
			if (isStudentArr(&(pThis->data), studentNumber, studentPassword))
			{
				//������ѧ����ѧϰίԱ
				if (!strcmp(pThis->data.ClassLeader, studentNumber))
				{
					return 1;
				}
				else
				{
					return 2;
				}
			}
			else
			{
				return 0;
			}
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR��û������༶��ŵĴ��ڣ��������������Ƿ���ȷ��\n");
		return 0;
	}
	return 0;
}

//��ȡ��ǰ����ĳ���
int getListLength(struct ListNode* pHead)
{
	int listLength = 0;
	struct ListNode* pThis = pHead->pNext;
	while (pThis)
	{
		listLength++;
		pThis = pThis->pNext;
	}
	return listLength;
}

//�ļ����溯��
void saveFile(struct ListNode* pHead)
{
	struct ListNode* pThis = pHead->pNext;
	int listLength = getListLength(pHead);
	int i = 0;
	FILE* fp = fopen("�༶��Ϣ��.txt", "w");
	//���ȴ�ӡ��ǰ�ж��ٸ��༶
	fprintf(fp, "%d\n", listLength);
	while (pThis)
	{
		//���ļ��д�ӡ�༶�Ļ�����Ϣ
		fprintf(fp, "%s  ", pThis->data.ClassNumber);
		fprintf(fp, "%s  ", pThis->data.ClassLeader);
		fprintf(fp, "%d\n", pThis->data.StudentCount);
		//���ļ��д�ӡÿһ��ͬѧ�Ļ�����Ϣ
		for (i = 0; i < pThis->data.StudentCount; i++)
		{
			fprintf(fp, "%s  ", pThis->data.StudentsArray[i].ClassNumber);
			fprintf(fp, "%s  ", pThis->data.StudentsArray[i].StudentNumber);
			fprintf(fp, "%s  ", pThis->data.StudentsArray[i].StudentName);
			fprintf(fp, "%s\n", pThis->data.StudentsArray[i].StudentPassword);
		}
		//�ڴ�ӡ����һ���༶��ȫ������֮������ָ����ƣ���ӡ��һ���༶������
		pThis = pThis->pNext;
	}
	//���ļ�д�����֮����Ҫ�ر��ļ���
	fclose(fp);
}

//�ļ���ȡ
void readFile(struct ListNode* pHead)
{
	//�ļ���ȡָ��
	FILE* fp = fopen("�༶��Ϣ��.txt", "r");

	//����һЩ��Ӧ���Ե����飬���ڽ��մ��ļ��ж�����������
	int studentCount = 0;
	char classNumber[STRINGLENGTH], leaderNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentName[STRINGLENGTH], studentPassword[STRINGLENGTH];

	//����һ���������ȶ�ȡ��ǰ�ж��ٸ��༶
	int listLength = 0;

	int i = 0;
	int j = 0;
	//����ļ���ʧ�ܣ�ֱ�ӷ���
	if (!fp)
	{
		return;
	}
	fscanf(fp, "%d", &listLength);

	for (i = 0; i < listLength; i++)
	{
		//��ȡ�༶�Ļ�������
		fscanf(fp, "%s%s%d", classNumber, leaderNumber, &studentCount);
		//֮�󴴽�һ���༶�����һ��������ֵ0������studentCount����Ϊ֮���forѭ�����õ�appendStudent����
		//�����ClassInfo�������addStudent����,��������Ǽٶ�������û�е����������֮ǰ������0��
		createClass(pHead, classNumber, leaderNumber, 0);
		for (j = 0; j < studentCount; j++)
		{
			fscanf(fp, "%s%s%s%s", classNumber, studentNumber, studentName, studentPassword);
			appendStudent(pHead, classNumber, studentNumber, studentName, studentPassword);
		}
	}
	fclose(fp);
}
/***************************************************************************************************/

/*************************************** ��ҵ��Ϣ�ṹ�� ********************************************/
struct JobInfo
{
	char ClassNumber[STRINGLENGTH];//�༶��ţ����ڱ�ʶ��ҵ�Ĺ���
	char JobNumber[STRINGLENGTH];//��ҵ���
	char CourseName[STRINGLENGTH];//�γ���
	int JobTime;//��ҵ����
	char JobContent[STRINGLENGTH];//��ҵ����
	char ArrangementTime[STRINGLENGTH];//����ʱ��
	char JobDeadline[STRINGLENGTH];//��ֹʱ��
	char JobNote[STRINGLENGTH];//��ҵ��ע 
};

//����һ���µ���ҵ
struct JobInfo createJob(char* classNumber, char* jobNumber, char* courseName, int jobTime, char* jobContent, char* arrangementTime, char* jobDeadline, char* jobNote)
{
	struct JobInfo newJob;
	strcpy(newJob.ClassNumber, classNumber);
	strcpy(newJob.JobNumber, jobNumber);
	strcpy(newJob.CourseName, courseName);
	newJob.JobTime = jobTime;
	strcpy(newJob.JobContent, jobContent);
	strcpy(newJob.ArrangementTime, arrangementTime);
	strcpy(newJob.JobDeadline, jobDeadline);
	strcpy(newJob.JobNote, jobNote);
	return newJob;
}

//����һ����ҵ����
struct JobInfo JobArrayList[MAXARRAYSIZE];
//��ҵ����ĳ���
int JobCount = 0;

//����һ����ҵ����
void addJob(char* classNumber, char* jobNumber, char* courseName, int jobTime, char* jobContent, char* arrangementTime, char* jobDeadline, char* jobNote)
{
	JobArrayList[JobCount++] = createJob(classNumber, jobNumber, courseName, jobTime, jobContent, arrangementTime, jobDeadline, jobNote);
}

//������ҵ���ɾ��һ����ҵ
void deleteJob(char* jobNumber)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].JobNumber, jobNumber))
		{
			for (j = i; j < JobCount - 1; j++)
			{
				JobArrayList[j] = JobArrayList[j + 1];
			}
			JobCount--;
			printf("TIPS���ѳɹ�����ҵ��ţ�%s����ҵ��Ϣ���б���ɾ����\n", jobNumber);
			return;
		}
	}
	printf("ERROR����ҵ�б��в�������ҵ��ţ�%s����ҵ��Ϣ��ɾ��ʧ�ܣ�\n", jobNumber);
}

//�޸���ҵ�Ľ�ֹʱ��
void alterJob(char* jobNumber, char* newDeadline)
{
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].JobNumber, jobNumber))
		{
			strcpy(JobArrayList[i].JobDeadline, newDeadline);
			printf("TIPS���ѳɹ�����ҵ��ţ�%s�Ľ�ֹʱ���޸�Ϊ��%s\n", jobNumber, newDeadline);
			return;
		}
	}
	printf("ERROR����ҵ�б��в�������ҵ��ţ�%s����ҵ��Ϣ���޸�ʧ�ܣ�\n", jobNumber);
}

//��ѯ��ҵ���й���Ϣ
void queryJob(char* jobNumber)
{
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].JobNumber, jobNumber))
		{
			printf("��ҵ��ţ�%s\n", JobArrayList[i].JobNumber);
			printf("�γ����ƣ�%s\n", JobArrayList[i].CourseName);
			printf("��ҵ������%d\n", JobArrayList[i].JobTime);
			printf("��ҵ���ݣ�%s\n", JobArrayList[i].JobContent);
			printf("����ʱ�䣺%s\n", JobArrayList[i].ArrangementTime);
			printf("��ֹʱ�䣺%s\n", JobArrayList[i].JobDeadline);
			printf("��ҵ��ע��%s\n", JobArrayList[i].JobNote);
			return;
		}
	}
}

//��ѯ������ҵ�б�
void travelArrayList(char* classNumber)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].ClassNumber, classNumber))
		{
			atLeastOne = 1;
			printf("��ҵ��ţ�%s\n", JobArrayList[i].JobNumber);
			printf("�γ����ƣ�%s\n", JobArrayList[i].CourseName);
			printf("��ҵ������%d\n", JobArrayList[i].JobTime);
			printf("��ҵ���ݣ�%s\n", JobArrayList[i].JobContent);
			printf("����ʱ�䣺%s\n", JobArrayList[i].ArrangementTime);
			printf("��ֹʱ�䣺%s\n", JobArrayList[i].JobDeadline);
			printf("��ҵ��ע��%s\n", JobArrayList[i].JobNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR����ҵ�б��в��������༶����ҵ��Ϣ��\n");
	}
}

//��ʱ�䷶Χ��ѯ
void queryTime(char* classNumber, char* beginTime, char* endTime)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].ClassNumber, classNumber) && strcmp(JobArrayList[i].ArrangementTime, beginTime) >= 0 && strcmp(JobArrayList[i].ArrangementTime, endTime) <= 0)
		{
			atLeastOne = 1;
			printf("��ҵ��ţ�%s\n", JobArrayList[i].JobNumber);
			printf("�γ����ƣ�%s\n", JobArrayList[i].CourseName);
			printf("��ҵ������%d\n", JobArrayList[i].JobTime);
			printf("��ҵ���ݣ�%s\n", JobArrayList[i].JobContent);
			printf("����ʱ�䣺%s\n", JobArrayList[i].ArrangementTime);
			printf("��ֹʱ�䣺%s\n", JobArrayList[i].JobDeadline);
			printf("��ҵ��ע��%s\n", JobArrayList[i].JobNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR����ҵ�б��в��������༶����ҵ��Ϣ��\n");
	}
}

//���γ�����ѯ
void queryCourse(char* classNumber, char* courseName)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].ClassNumber, classNumber) && !strcmp(JobArrayList[i].CourseName, courseName))
		{
			atLeastOne = 1;
			printf("��ҵ��ţ�%s\n", JobArrayList[i].JobNumber);
			printf("�γ����ƣ�%s\n", JobArrayList[i].CourseName);
			printf("��ҵ������%d\n", JobArrayList[i].JobTime);
			printf("��ҵ���ݣ�%s\n", JobArrayList[i].JobContent);
			printf("����ʱ�䣺%s\n", JobArrayList[i].ArrangementTime);
			printf("��ֹʱ�䣺%s\n", JobArrayList[i].JobDeadline);
			printf("��ҵ��ע��%s\n", JobArrayList[i].JobNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR����ҵ�б��в��������༶����ҵ��Ϣ��\n");
	}
}

//��ʱ���ֹ��������
void sortDeadline()
{
	int i = 0;
	int j = 0;
	if (JobCount <= 1)
	{
		return;
	}
	for (i = 0; i < JobCount - 1; i++)
	{
		for (j = i + 1; j < JobCount; j++)
		{
			if (strcmp(JobArrayList[i].JobDeadline, JobArrayList[j].JobDeadline) > 0)
			{
				struct JobInfo tmpJob = JobArrayList[i];
				JobArrayList[i] = JobArrayList[j];
				JobArrayList[j] = tmpJob;
			}
		}
	}
}

//�����ļ�
void saveJobFile()
{
	FILE* fp = fopen("��ҵ��Ϣ��.txt", "w");
	int i = 0;
	fprintf(fp, "%d\n", JobCount);
	for (i = 0; i < JobCount; i++)
	{
		fprintf(fp, "%s  ", JobArrayList[i].ClassNumber);
		fprintf(fp, "%s  ", JobArrayList[i].JobNumber);
		fprintf(fp, "%s  ", JobArrayList[i].CourseName);
		fprintf(fp, "%d  ", JobArrayList[i].JobTime);
		fprintf(fp, "%s  ", JobArrayList[i].JobContent);
		fprintf(fp, "%s  ", JobArrayList[i].ArrangementTime);
		fprintf(fp, "%s  ", JobArrayList[i].JobDeadline);
		fprintf(fp, "%s\n", JobArrayList[i].JobNote);
	}
	fclose(fp);
}

//��ȡ�ļ�
void readJobFile()
{
	FILE* fp = fopen("��ҵ��Ϣ��.txt", "r");
	//��ȡ�ļ���Ŀ��
	int arratLength = 0;
	int jobTime = 0;
	char classNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], courseName[STRINGLENGTH], jobContent[STRINGLENGTH], arrangementTime[STRINGLENGTH], jobDeadline[STRINGLENGTH], jobNote[STRINGLENGTH];
	int i = 0;
	if (!fp)
	{
		return;
	}

	fscanf(fp, "%d", &arratLength);
	for (i = 0; i < arratLength; i++)
	{
		fscanf(fp, "%s%s%s%d%s%s%s%s", classNumber, jobNumber, courseName, &jobTime, jobContent, arrangementTime, jobDeadline, jobNote);
		addJob(classNumber, jobNumber, courseName, jobTime, jobContent, arrangementTime, jobDeadline, jobNote);
	}
	fclose(fp);
}
/***************************************************************************************************/

/*************************************** �ύ����ṹ�� ********************************************/
struct SubmitInfo
{
	char ClassNumber[STRINGLENGTH];
	char StudentNumber[STRINGLENGTH];
	char JobNumber[STRINGLENGTH];
	char CourseName[STRINGLENGTH];
	char SubmitTime[STRINGLENGTH];
	char SubmitNote[STRINGLENGTH];
};

struct SubmitInfo SubmitArrayList[MAXARRAYSIZE];
int SubmitCount = 0;

struct SubmitInfo createSubmit(char* classNumber, char* studentNumber, char* jobNumber, char* courseName, char* submitTime, char* submitNote)
{
	struct SubmitInfo newSubmit;
	strcpy(newSubmit.ClassNumber, classNumber);
	strcpy(newSubmit.StudentNumber, studentNumber);
	strcpy(newSubmit.JobNumber, jobNumber);
	strcpy(newSubmit.CourseName, courseName);
	strcpy(newSubmit.SubmitTime, submitTime);
	strcpy(newSubmit.SubmitNote, submitNote);
	return newSubmit;
}

void addSubmit(char* classNumber, char* studentNumber, char* jobNumber, char* courseName, char* submitTime, char* submitNote)
{
	SubmitArrayList[SubmitCount++] = createSubmit(classNumber, studentNumber, jobNumber, courseName, submitTime, submitNote);
}

void deleteSubmit(char* studentNumber, char* jobNumber)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].StudentNumber, studentNumber) && !strcmp(SubmitArrayList[i].JobNumber, jobNumber))
		{
			for (j = i; j < SubmitCount - 1; j++)
			{
				SubmitArrayList[j] = SubmitArrayList[j + 1];
			}
			SubmitCount--;
			printf("TIPS���ѳɹ���ѧ����%s�ı�ţ�%s����ҵ���ύ����б���ɾ����\n", studentNumber, jobNumber);
			return;
		}
	}
	printf("ERROR���ύ����б��в�������ص���ҵ�ύ��Ϣ��ɾ��ʧ�ܣ�\n");
}

void alterSubmit(char* studentNumber, char* jobNumber, char* newTime)
{
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].StudentNumber, studentNumber) && !strcmp(SubmitArrayList[i].JobNumber, jobNumber))
		{
			strcpy(SubmitArrayList[i].SubmitTime, newTime);
			printf("TIPS���ѳɹ���ѧ����%s�ı�ţ�%s����ҵ�ύʱ���޸�Ϊ��%s��\n", studentNumber, jobNumber, newTime);
			return;
		}
	}
	printf("ERROR���ύ����б��в�������ص���ҵ�ύ��Ϣ���޸�ʧ�ܣ�\n");
}

void travelSubArrayList(char* classNumber)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].ClassNumber, classNumber))
		{
			atLeastOne = 1;
			printf("�༶��ţ�%s\n", SubmitArrayList[i].ClassNumber);
			printf("ѧ��ѧ�ţ�%s\n", SubmitArrayList[i].StudentNumber);
			printf("��ҵ��ţ�%s\n", SubmitArrayList[i].JobNumber);
			printf("��ҵ�γ̣�%s\n", SubmitArrayList[i].CourseName);
			printf("�ύʱ�䣺%s\n", SubmitArrayList[i].SubmitTime);
			printf("�ύ��ע��%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR���ύ����б��в��������༶����ҵ��Ϣ��\n");
	}
}

void querySubmitTime(char* classNumber, char* beginTime, char* endTime)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].ClassNumber, classNumber) && strcmp(SubmitArrayList[i].SubmitTime, beginTime) >= 0 && strcmp(SubmitArrayList[i].SubmitTime, endTime) <= 0)
		{
			atLeastOne = 1;
			printf("�༶��ţ�%s\n", SubmitArrayList[i].ClassNumber);
			printf("ѧ��ѧ�ţ�%s\n", SubmitArrayList[i].StudentNumber);
			printf("��ҵ��ţ�%s\n", SubmitArrayList[i].JobNumber);
			printf("��ҵ�γ̣�%s\n", SubmitArrayList[i].CourseName);
			printf("�ύʱ�䣺%s\n", SubmitArrayList[i].SubmitTime);
			printf("�ύ��ע��%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR���ύ����б��в������κ���ص���ҵ��Ϣ����ѯʧ�ܣ�\n");
	}
}

void querySubmitCourse(char* classNumber, char* courseName)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].ClassNumber, classNumber) && !strcmp(SubmitArrayList[i].CourseName, courseName))
		{
			atLeastOne = 1;
			printf("�༶��ţ�%s\n", SubmitArrayList[i].ClassNumber);
			printf("ѧ��ѧ�ţ�%s\n", SubmitArrayList[i].StudentNumber);
			printf("��ҵ��ţ�%s\n", SubmitArrayList[i].JobNumber);
			printf("��ҵ�γ̣�%s\n", SubmitArrayList[i].CourseName);
			printf("�ύʱ�䣺%s\n", SubmitArrayList[i].SubmitTime);
			printf("�ύ��ע��%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR���ύ����б��в������κ���ص���ҵ��Ϣ����ѯʧ�ܣ�\n");
	}
}

void queryStudentNumber(char* studentNumber)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].StudentNumber, studentNumber))
		{
			atLeastOne = 1;
			printf("�༶��ţ�%s\n", SubmitArrayList[i].ClassNumber);
			printf("ѧ��ѧ�ţ�%s\n", SubmitArrayList[i].StudentNumber);
			printf("��ҵ��ţ�%s\n", SubmitArrayList[i].JobNumber);
			printf("��ҵ�γ̣�%s\n", SubmitArrayList[i].CourseName);
			printf("�ύʱ�䣺%s\n", SubmitArrayList[i].SubmitTime);
			printf("�ύ��ע��%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR���ύ����б��в������κ���ص���ҵ��Ϣ����ѯʧ�ܣ�\n");
	}
}

void sortSubmitTime()
{
	int i = 0;
	int j = 0;
	if (SubmitCount <= 1)
	{
		return;
	}
	for (i = 0; i < SubmitCount - 1; i++)
	{
		for (j = i + 1; j < SubmitCount; j++)
		{
			if (strcmp(SubmitArrayList[i].SubmitTime, SubmitArrayList[j].SubmitTime) > 0)
			{
				struct SubmitInfo tmpJob = SubmitArrayList[i];
				SubmitArrayList[i] = SubmitArrayList[j];
				SubmitArrayList[j] = tmpJob;
			}
		}
	}
}

void statisticsCourse(char* classNumber, char* courseName)
{
	int count = 0;//�����ύ��ҵ������
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].ClassNumber, classNumber) && !strcmp(SubmitArrayList[i].CourseName, courseName))
		{
			count++;
		}
	}
	printf("TIPS���༶��%s�ύ�γ�%s����%d��!\n", classNumber, courseName, count);
}

void statisticsClass(char* classNumber)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].ClassNumber, classNumber))
		{
			atLeastOne = 1;
			printf("�༶��ţ�%s\n", SubmitArrayList[i].ClassNumber);
			printf("ѧ��ѧ�ţ�%s\n", SubmitArrayList[i].StudentNumber);
			printf("��ҵ��ţ�%s\n", SubmitArrayList[i].JobNumber);
			printf("��ҵ�γ̣�%s\n", SubmitArrayList[i].CourseName);
			printf("�ύʱ�䣺%s\n", SubmitArrayList[i].SubmitTime);
			printf("�ύ��ע��%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR���ύ����б��в������κ���ص���ҵ��Ϣ����ѯʧ�ܣ�\n");
	}
}

void saveSubmitFile()
{
	int i = 0;
	FILE* fp = fopen("�ύ�����.txt", "w");
	fprintf(fp, "%d\n", SubmitCount);
	for (i = 0; i < SubmitCount; i++)
	{
		fprintf(fp, "%s  %s  %s  %s  %s  %s\n", SubmitArrayList[i].ClassNumber, SubmitArrayList[i].StudentNumber, SubmitArrayList[i].JobNumber,
			SubmitArrayList[i].CourseName, SubmitArrayList[i].SubmitTime, SubmitArrayList[i].SubmitNote);
	}
	fclose(fp);
}

void readSubmitFile()
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], courseName[STRINGLENGTH], submitTime[STRINGLENGTH], submitNote[STRINGLENGTH];
	int arrayLength = 0;
	int i = 0;
	FILE* fp = fopen("�ύ�����.txt", "r");
	if (!fp)
	{
		return;
	}
	fscanf(fp, "%d", &arrayLength);
	for (i = 0; i < arrayLength; i++)
	{
		fscanf(fp, "%s%s%s%s%s%s", classNumber, studentNumber, jobNumber, courseName, submitTime, submitNote);
		addSubmit(classNumber, studentNumber, jobNumber, courseName, submitTime, submitNote);
	}
	fclose(fp);
}
/***************************************************************************************************/

/*************************************** ���庯�������� ********************************************/
void IdentityMenu(struct ListNode* pHead);//��ݵ�¼�˵�

int AdminLogin();//ϵͳ����Ա��ݵ�¼����
int LeaderLogin(struct ListNode* pHead);//ѧϰίԱ��¼
int NormalLogin(struct ListNode* pHead);//��ͨѧ����¼

void AdminMenu(struct ListNode* pHead);//����Ա�˵�
void LeaderMenu();//ѧϰίԱ�˵�
void NormalMenu();//��ͨѧ���˵�

void AddClass(struct ListNode* pHead);//���Ӱ༶��������
void DeleteClass(struct ListNode* pHead);//ɾ���༶
void AlterClass(struct ListNode* pHead);//�޸İ༶ѧϰίԱ
void QueryClass(struct ListNode* pHead);//��ѯ�༶��������
void AddStudent(struct ListNode* pHead);//����һ��ѧ���Ļ�����Ϣ
void DeleteStudent(struct ListNode* pHead);//ɾ��ѧ��
void AlterStudent(struct ListNode* pHead);//�޸�ѧ������
void QueryStudent(struct ListNode* pHead);//��ѯѧ��

void AddJob();//������ҵ��������
void DeleteJob();//ɾ����ҵ
void AlterJob();//�޸���ҵ��ֹʱ��
void QueryJob();//��ѯ�༶�����������ҵ
void QueryTime();//��ʱ�䷶Χ��ѯ��ҵ
void QueryCourse();//���γ����Ʋ�ѯ��ҵ
void SortTime();//����ҵ��ֹʱ������
void AddSubmit();//������ҵ�ύ���
void DeleteSubmit();//ɾ����ҵ�ύ���
void AlterSubmit();//�޸���ҵ�ύʱ��
void QuerySubmit();//��ѯ������ҵ�ύ���
void QuerySubmitTime();//��ʱ�䷶Χ��ѯ
void QuerySubmitCourse();//���γ̲�ѯ
void QuerySubmitStudent();//��ѯĳһ��ͬѧ���ύ���
void SortSubmit();//���ύʱ������
void StatisticsCourse();//ͳ�ƿγ��ύ���
void StatisticsStudent();//ͳ��ѧ���ύ���

void QueryOwnSubmit();//��ѯ�����ύ���
/***************************************************************************************************/

/*************************************** ���庯���Ķ��� ********************************************/
//��ݵ�¼�˵�
void IdentityMenu(struct ListNode* pHead)
{
	int switch_on = 0;
	int ret = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 8; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ******************** ѧί��ҵ����ϵͳ ********************\n\n");
	printf("\t\t\t\t\t 1��ϵͳ����Ա��ݵ�¼\n");
	printf("\t\t\t\t\t 2���༶ѧί��ݵ�¼\n");
	printf("\t\t\t\t\t 3����ͨѧ����ݵ�¼\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t ����������ѡ��");
	scanf("%d", &switch_on);
	switch (switch_on)
	{
	case 1:
		ret = AdminLogin();
		if (ret)
		{
			AdminMenu(pHead);
		}
		else
		{
			printf("ERROR���û�����������󣬵�¼ʧ�ܣ�");
		}
		break;
	case 2:
		ret = LeaderLogin(pHead);
		if (ret == 1)
		{
			LeaderMenu();
		}
		else if (ret == 2)
		{
			printf("ERROR���������ǰ༶��ѧϰίԱŶ����֤ʧ�ܣ�");
		}
		else
		{
			printf("ERROR����¼ʧ�ܣ�");
		}
		break;
	case 3:
		ret = NormalLogin(pHead);
		if (!ret)
		{
			printf("ERROR����¼ʧ�ܣ�");
		}
		else
		{
			NormalMenu();
		}
		break;
	default:
		break;
	}
	printf("�� ENTER ���µ�¼ϵͳ��");
	getchar();
	getchar();
	IdentityMenu(pHead);
}

//ϵͳ����Ա��ݵ�¼����
int AdminLogin()
{
	char account[STRINGLENGTH], password[STRINGLENGTH];
	system("cls");
	printf("******************** ����Ա��¼ϵͳ ********************\n\n");
	printf("���������Ĺ���Ա�˻���");
	scanf("%s", account);
	printf("���������ĵ�¼���룺");
	scanf("%s", password);
	if (!strcmp(account, "admin") && !strcmp(password, "666666"))
	{
		return 1;
	}
	return 0;
}

//ѧϰίԱ��¼
int LeaderLogin(struct ListNode* pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentPassword[STRINGLENGTH];
	int ret = 0;
	system("cls");
	printf("******************** ѧϰίԱ��¼ϵͳ ********************\n\n");
	printf("���������İ༶��ţ�");
	scanf("%s", classNumber);
	printf("����������ѧ����ţ�");
	scanf("%s", studentNumber);
	printf("���������ĵ�¼���룺");
	scanf("%s", studentPassword);
	ret = isStudent(pHead, classNumber, studentNumber, studentPassword);
	strcpy(CurrentOperatorClass, classNumber);
	strcpy(CurrentOperatorNumber, studentNumber);
	return ret;
}

//��ͨѧ����¼
int NormalLogin(struct ListNode* pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentPassword[STRINGLENGTH];
	int ret = 0;
	system("cls");
	printf("******************** ��ͨѧ����¼ϵͳ ********************\n\n");
	printf("���������İ༶��ţ�");
	scanf("%s", classNumber);
	printf("����������ѧ����ţ�");
	scanf("%s", studentNumber);
	printf("���������ĵ�¼���룺");
	scanf("%s", studentPassword);
	ret = isStudent(pHead, classNumber, studentNumber, studentPassword);
	strcpy(CurrentOperatorClass, classNumber);
	strcpy(CurrentOperatorNumber, studentNumber);
	return ret;
}

//����Ա�˵�
void AdminMenu(struct ListNode* pHead)
{
	int switch_on = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 6; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ********************* ����Ա�����˵� *********************\n\n");
	printf("\t\t\t\t\t 1�����Ӱ༶��������\n");
	printf("\t\t\t\t\t 2��ɾ���༶��������\n");
	printf("\t\t\t\t\t 3���޸İ༶ѧϰίԱ\n");
	printf("\t\t\t\t\t 4����ѯ�༶��������\n");
	printf("\t\t\t\t\t 5������ѧ��������Ϣ\n");
	printf("\t\t\t\t\t 6��ɾ��ѧ��������Ϣ\n");
	printf("\t\t\t\t\t 7���޸�ѧ����¼����\n");
	printf("\t\t\t\t\t 8����ѯѧ��������Ϣ\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t ����������ѡ��");
	scanf("%d", &switch_on);
	switch (switch_on)
	{
	case 1:
		AddClass(pHead);
		break;
	case 2:
		DeleteClass(pHead);
		break;
	case 3:
		AlterClass(pHead);
		break;
	case 4:
		QueryClass(pHead);
		break;
	case 5:
		AddStudent(pHead);
		break;
	case 6:
		DeleteStudent(pHead);
		break;
	case 7:
		AlterStudent(pHead);
		break;
	case 8:
		QueryStudent(pHead);
		break;
	default:
		break;
	}
	saveFile(pHead);
	printf("�� ENTER ���ص�ǰ�����˵���");
	getchar();
	getchar();
	AdminMenu(pHead);
}

//ѧϰίԱ�˵�
void LeaderMenu()
{
	int switch_on = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 4; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ********************* ѧϰίԱ�����˵� *********************\n\n");
	printf("\t\t\t\t\t 1��������ҵ��������\n");
	printf("\t\t\t\t\t 2��ɾ����ҵ��������\n");
	printf("\t\t\t\t\t 3���޸���ҵ��ֹʱ��\n");
	printf("\t\t\t\t\t 4����ѯ������ҵ��Ϣ\n");
	printf("\t\t\t\t\t 5����ʱ�䷶Χ��ѯ��ҵ\n");
	printf("\t\t\t\t\t 6�����γ����Ʋ�ѯ��ҵ\n");
	printf("\t\t\t\t\t 7������ҵ��ֹʱ������\n");
	printf("\t\t\t\t\t 8��������ҵ�ύ���\n");
	printf("\t\t\t\t\t 9��ɾ����ҵ�ύ���\n");
	printf("\t\t\t\t\t 10���޸���ҵ�ύʱ��\n");
	printf("\t\t\t\t\t 11����ѯ���������ύ���\n");
	printf("\t\t\t\t\t 12����ʱ�䷶Χ��ѯ�б�\n");
	printf("\t\t\t\t\t 13�����γ̲�ѯ��ҵ�б�\n");
	printf("\t\t\t\t\t 14����ѯĳͬѧ���ύ���\n");
	printf("\t\t\t\t\t 15�����ύʱ��������ʾ\n");
	printf("\t\t\t\t\t 16��ͳ�Ƹ��γ̵��ύ���\n");
	printf("\t\t\t\t\t 17��ͳ�Ƹ�ѧ�����ύ���\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t ����������ѡ��");
	scanf("%d", &switch_on);
	switch (switch_on)
	{
	case 1:
		AddJob();
		break;
	case 2:
		DeleteJob();
		break;
	case 3:
		AlterJob();
		break;
	case 4:
		QueryJob();
		break;
	case 5:
		QueryTime();
		break;
	case 6:
		QueryCourse();
		break;
	case 7:
		SortTime();
		break;
	case 8:
		AddSubmit();
		break;
	case 9:
		DeleteSubmit();
		break;
	case 10:
		AlterSubmit();
		break;
	case 11:
		QuerySubmit();
		break;
	case 12:
		QuerySubmitTime();
		break;
	case 13:
		QuerySubmitCourse();
		break;
	case 14:
		QuerySubmitStudent();
		break;
	case 15:
		SortSubmit();
		break;
	case 16:
		StatisticsCourse();
		break;
	case 17:
		StatisticsStudent();
		break;
	default:
		break;
	}
	saveJobFile();
	saveSubmitFile();
	printf("�� ENTER ���ص�ǰ�����˵���");
	getchar();
	getchar();
	LeaderMenu();
}

//��ͨѧ����¼�˵�
void NormalMenu()
{
	int switch_on = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 8; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ********************* ��ͨѧ�������˵� *********************\n\n");
	printf("\t\t\t\t\t 1����ѯ��ҵ�б�\n");
	printf("\t\t\t\t\t 2���鿴�����ύ���\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t ����������ѡ��");
	scanf("%d", &switch_on);
	switch (switch_on)
	{
	case 1:
		QueryJob();
		break;
	case 2:
		QueryOwnSubmit();
		break;
	default:
		break;
	}
	printf("�� ENTER ���ص�ǰ�����˵���");
	getchar();
	getchar();
	NormalMenu();
}

void AddClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ���Ӱ༶�������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	createClass(pHead, classNumber, "NULL", 0);
}

void DeleteClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ɾ���༶�������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	deleteClass(pHead, classNumber);
}

void AlterClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** �޸İ༶�������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("������༶ѧϰίԱ��");
	scanf("%s", studentNumber);
	alterClass(pHead, classNumber, studentNumber);
}

void QueryClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ��ѯ�༶�������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	queryClass(pHead, classNumber);
}

void AddStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentName[STRINGLENGTH], studentPassword[STRINGLENGTH];
	system("cls");
	printf("******************** ����ѧ���������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	printf("������ѧ��������");
	scanf("%s", studentName);
	printf("�������¼���룺");
	scanf("%s", studentPassword);
	appendStudent(pHead, classNumber, studentNumber, studentName, studentPassword);
}

void DeleteStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ɾ��ѧ���������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	deleteStudent(pHead, classNumber, studentNumber);
}

void AlterStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentPassword[STRINGLENGTH];
	system("cls");
	printf("******************** �޸�ѧ���������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	printf("�������¼���룺");
	scanf("%s", studentPassword);
	alterStudent(pHead, classNumber, studentNumber, studentPassword);
}

void QueryStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ��ѯѧ���������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	queryStudent(pHead, classNumber, studentNumber);
}

void AddJob()
{
	int jobTime = 0;
	char classNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], courseName[STRINGLENGTH], jobContent[STRINGLENGTH], arrangementTime[STRINGLENGTH], jobDeadline[STRINGLENGTH], jobNote[STRINGLENGTH];
	system("cls");
	printf("******************** ������ҵ�������� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("��������ҵ��ţ�");
	scanf("%s", jobNumber);
	printf("������γ����ƣ�");
	scanf("%s", courseName);
	printf("��������ҵ������");
	scanf("%d", &jobTime);
	printf("��������ҵ���ݣ�");
	scanf("%s", jobContent);
	printf("�����벼��ʱ�䣺");
	scanf("%s", arrangementTime);
	printf("�������ֹʱ�䣺");
	scanf("%s", jobDeadline);
	printf("����������ע��");
	scanf("%s", jobNote);
	addJob(classNumber, jobNumber, courseName, jobTime, jobContent, arrangementTime, jobDeadline, jobNote);
}

void DeleteJob()
{
	int jobTime = 0;
	char jobNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ɾ����ҵ�������� ********************\n\n");
	printf("��������ҵ��ţ�");
	scanf("%s", jobNumber);
	deleteJob(jobNumber);
}

void AlterJob()
{
	int jobTime = 0;
	char jobNumber[STRINGLENGTH], newDeadline[STRINGLENGTH];
	system("cls");
	printf("******************** �޸���ҵ�������� ********************\n\n");
	printf("��������ҵ��ţ�");
	scanf("%s", jobNumber);
	printf("�������ֹʱ�䣺");
	scanf("%s", newDeadline);
	alterJob(jobNumber, newDeadline);
}

void QueryJob()
{
	system("cls");
	printf("******************** ��ѯ��ҵ�������� ********************\n\n");
	travelArrayList(CurrentOperatorClass);
}

void QueryTime()
{
	char beginTime[STRINGLENGTH], endTime[STRINGLENGTH];
	system("cls");
	printf("******************** ��ʱ�䷶Χ��ѯ��ҵ ********************\n\n");
	printf("�����뿪ʼʱ�䣺");
	scanf("%s", beginTime);
	printf("���������ʱ�䣺");
	scanf("%s", endTime);
	queryTime(CurrentOperatorClass, beginTime, endTime);
}

void QueryCourse()
{
	char courseName[STRINGLENGTH];
	system("cls");
	printf("******************** ���γ����Ʋ�ѯ��ҵ ********************\n\n");
	printf("������γ����ƣ�");
	scanf("%s", courseName);
	queryCourse(CurrentOperatorClass, courseName);
}

void SortTime()
{
	system("cls");
	printf("******************** ����ҵ��ֹʱ������ ********************\n\n");
	sortDeadline();
	travelArrayList(CurrentOperatorClass);
}

void AddSubmit()
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], courseName[STRINGLENGTH], submitTime[STRINGLENGTH], submitNote[STRINGLENGTH];
	system("cls");
	printf("******************** ������ҵ�ύ��� ********************\n\n");
	printf("������༶��ţ�");
	scanf("%s", classNumber);
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	printf("��������ҵ��ţ�");
	scanf("%s", jobNumber);
	printf("������γ����ƣ�");
	scanf("%s", courseName);
	printf("�������ύʱ�䣺");
	scanf("%s", submitTime);
	printf("�������ύ��ע��");
	scanf("%s", submitNote);
	addSubmit(classNumber, studentNumber, jobNumber, courseName, submitTime, submitNote);
}

void DeleteSubmit()
{
	char studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ɾ����ҵ�ύ��� ********************\n\n");
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	printf("��������ҵ��ţ�");
	scanf("%s", jobNumber);
	deleteSubmit(studentNumber, jobNumber);
}

void AlterSubmit()
{
	char studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], newTime[STRINGLENGTH];
	system("cls");
	printf("******************** �޸���ҵ�ύʱ�� ********************\n\n");
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	printf("��������ҵ��ţ�");
	scanf("%s", jobNumber);
	printf("�������ύʱ�䣺");
	scanf("%s", newTime);
	alterSubmit(studentNumber, jobNumber, newTime);
}

void QuerySubmit()
{
	system("cls");
	printf("******************** ��ѯ������ҵ�ύ��� ********************\n\n");
	travelSubArrayList(CurrentOperatorClass);
}

void QuerySubmitTime()
{
	char beginTime[STRINGLENGTH], endTime[STRINGLENGTH];
	system("cls");
	printf("******************** ��ʱ�䷶Χ��ѯ��ҵ ********************\n\n");
	printf("�����뿪ʼʱ�䣺");
	scanf("%s", beginTime);
	printf("���������ʱ�䣺");
	scanf("%s", endTime);
	querySubmitTime(CurrentOperatorClass, beginTime, endTime);
}

void QuerySubmitCourse()
{
	char courseName[STRINGLENGTH];
	system("cls");
	printf("******************** ���γ����Ʋ�ѯ��ҵ ********************\n\n");
	printf("������γ����ƣ�");
	scanf("%s", courseName);
	querySubmitCourse(CurrentOperatorClass, courseName);
}

void QuerySubmitStudent()
{
	char studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** ��ѯĳһλͬѧ����ҵ�ύ��� ********************\n\n");
	printf("������ѧ��ѧ�ţ�");
	scanf("%s", studentNumber);
	queryStudentNumber(studentNumber);
}

void SortSubmit()
{
	system("cls");
	printf("******************** ����ҵ�ύʱ������ ********************\n\n");
	sortSubmitTime();
	travelSubArrayList(CurrentOperatorClass);
}

void StatisticsCourse()
{
	system("cls");
	printf("******************** ͳ�ƿγ��ύ��� ********************\n\n");
	statisticsCourse(CurrentOperatorClass, "����");
	statisticsCourse(CurrentOperatorClass, "��ѧ");
	statisticsCourse(CurrentOperatorClass, "Ӣ��");
}

void StatisticsStudent()
{
	system("cls");
	printf("******************** ͳ��ѧ���ύ��� ********************\n\n");
	statisticsClass(CurrentOperatorClass);
}

void QueryOwnSubmit()
{
	system("cls");
	printf("******************** ��ѯ������ҵ�ύ��� ********************\n\n");
	queryStudentNumber(CurrentOperatorNumber);
}
/***************************************************************************************************/

int main()
{
	struct ListNode* pHead = createList();

	readFile(pHead);
	readJobFile();
	readSubmitFile();

	IdentityMenu(pHead);
	return 0;
}
