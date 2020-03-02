#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXARRAYSIZE 128//本系统所采用的数组的最大长度
#define STRINGLENGTH 16//定义本系统所使用的字符数组的大小


char CurrentOperatorClass[STRINGLENGTH];//保存当前操作系统的人的班级
char CurrentOperatorNumber[STRINGLENGTH];//保存当前登录的学号

/*************************************** 学生信息结构体 ********************************************/
struct StudentInfo
{
	char ClassNumber[STRINGLENGTH];//班级号
	char StudentNumber[STRINGLENGTH];//学号
	char StudentName[STRINGLENGTH];//姓名
	char StudentPassword[STRINGLENGTH];//密码
};

//创建一个学生信息结构体
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

/*************************************** 班级信息结构体 ********************************************/
struct ClassInfo
{
	char ClassNumber[STRINGLENGTH];//班号
	char ClassLeader[STRINGLENGTH];//班级学习委员的学号
	int StudentCount;//班级当前人数
	struct StudentInfo StudentsArray[MAXARRAYSIZE];//班级学生数据
};

//增加学生
void addStudent(struct ClassInfo* currentClass, char* classNumber, char* studentNumber, char* studentName, char* studentPassword)
{
	currentClass->StudentsArray[currentClass->StudentCount++] = createStudent(classNumber, studentNumber, studentName, studentPassword);
}

//删除学生
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
			printf("TIPS：已成功将学号：%s的学生从班级：%s中删除！\n", studentNumber, currentClass->ClassNumber);
			return;
		}
	}
	printf("ERROR：班级中不存在学号：%s的学生信息，删除失败！\n", studentNumber);
}

//修改学生登录密码
void alterStudentArr(struct ClassInfo* currentClass, char* studentNumber, char* newPassword)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		if (!strcmp(currentClass->StudentsArray[i].StudentNumber, studentNumber))
		{
			strcpy(currentClass->StudentsArray[i].StudentPassword, newPassword);
			printf("TIPS：已成功将学号：%s的学生的登录密码重置为：%s\n", studentNumber, newPassword);
			return;
		}
	}
	printf("ERROR：班级中不存在学号：%s的学生信息，修改失败！\n", studentNumber);
}

//查询学生信息
void queryStudentArr(struct ClassInfo* currentClass, char* studentNumber)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		if (!strcmp(currentClass->StudentsArray[i].StudentNumber, studentNumber))
		{
			printf("班级编号：%s\n", currentClass->StudentsArray[i].ClassNumber);
			printf("学生学号：%s\n", currentClass->StudentsArray[i].StudentNumber);
			printf("学生姓名：%s\n", currentClass->StudentsArray[i].StudentName);
			printf("登录密码：%s\n", currentClass->StudentsArray[i].StudentPassword);
			return;
		}
	}
	printf("ERROR：班级中不存在学号：%s的学生信息，查询失败！\n", studentNumber);
}

//打印当前学生数组里的全部数据
void printClassInfo(struct ClassInfo* currentClass)
{
	int i = 0;
	for (i = 0; i < currentClass->StudentCount; i++)
	{
		printf("班级编号：%s\n", currentClass->StudentsArray[i].ClassNumber);
		printf("学生学号：%s\n", currentClass->StudentsArray[i].StudentNumber);
		printf("学生姓名：%s\n", currentClass->StudentsArray[i].StudentName);
		printf("登录密码：%s\n", currentClass->StudentsArray[i].StudentPassword);
		printf("\n------------------------------\n\n");
	}
}

//根据学号密码做身份匹配,匹配成功返回true，否则返回false
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

/*************************************** 班级链表结构体 ********************************************/
struct ListNode
{
	struct ClassInfo data;
	struct ListNode* pNext;
};

struct ListNode* createList()
{
	struct ListNode* pHead = (struct ListNode*)malloc(sizeof(struct ListNode));
	strcpy(pHead->data.ClassNumber, "班级编号");
	strcpy(pHead->data.ClassLeader, "学习委员");
	pHead->data.StudentCount = 0;
	pHead->pNext = NULL;
	return pHead;
}

//增加一个班级节点
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

//删除一个班级节点
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
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
		return;
	}
	pDelete = pThis->pNext;
	pThis->pNext = pDelete->pNext;
	free(pDelete);
	printf("TIPS：已成功将班级：%s从系统中删除！\n", classNumber);
}

//修改班级的学习委员学号
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
		printf("TIPS：班级 %s 的学习委员已成功变更为学号：%s的学生！\n", classNumber, leaderNumber);
	}
	else
	{
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
		return;
	}
}

//查询一个班级的全部数据
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
			printf("当前班级编号：%s\t\t", pThis->data.ClassNumber);
			printf("学习委员学号：%s\n", pThis->data.ClassLeader);
			printf("******************** 班级学生信息总览 ********************\n\n");
			printClassInfo(&(pThis->data));
			break;
		}
	}
	if (pThis == NULL)
	{
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
	}
}

//增加学生
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
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
	}
}

//删除学生
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
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
	}
}

//修改学生密码
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
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
	}
}

//查询学生
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
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
	}
}

//判断是否是一个合法的学生账户，如果是一个学生再判断是否的学习委员，学习委员返回1，普通学生返回2，身份不合法返回0
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
			//说明这个班级编号是正确存在的，如果这个班级有这个学生
			if (isStudentArr(&(pThis->data), studentNumber, studentPassword))
			{
				//如果这个学生是学习委员
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
		printf("ERROR：没有这个班级编号的存在，请检查您的输入是否正确！\n");
		return 0;
	}
	return 0;
}

//获取当前链表的长度
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

//文件保存函数
void saveFile(struct ListNode* pHead)
{
	struct ListNode* pThis = pHead->pNext;
	int listLength = getListLength(pHead);
	int i = 0;
	FILE* fp = fopen("班级信息表.txt", "w");
	//首先打印当前有多少个班级
	fprintf(fp, "%d\n", listLength);
	while (pThis)
	{
		//在文件中打印班级的基础信息
		fprintf(fp, "%s  ", pThis->data.ClassNumber);
		fprintf(fp, "%s  ", pThis->data.ClassLeader);
		fprintf(fp, "%d\n", pThis->data.StudentCount);
		//在文件中打印每一个同学的基础信息
		for (i = 0; i < pThis->data.StudentCount; i++)
		{
			fprintf(fp, "%s  ", pThis->data.StudentsArray[i].ClassNumber);
			fprintf(fp, "%s  ", pThis->data.StudentsArray[i].StudentNumber);
			fprintf(fp, "%s  ", pThis->data.StudentsArray[i].StudentName);
			fprintf(fp, "%s\n", pThis->data.StudentsArray[i].StudentPassword);
		}
		//在打印出了一个班级的全部数据之后链表指针后移，打印下一个班级的数据
		pThis = pThis->pNext;
	}
	//在文件写入结束之后，需要关闭文件流
	fclose(fp);
}

//文件读取
void readFile(struct ListNode* pHead)
{
	//文件读取指针
	FILE* fp = fopen("班级信息表.txt", "r");

	//定义一些对应属性的数组，用于接收从文件中读出来的数据
	int studentCount = 0;
	char classNumber[STRINGLENGTH], leaderNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentName[STRINGLENGTH], studentPassword[STRINGLENGTH];

	//定义一个变量首先读取当前有多少个班级
	int listLength = 0;

	int i = 0;
	int j = 0;
	//如果文件打开失败，直接返回
	if (!fp)
	{
		return;
	}
	fscanf(fp, "%d", &listLength);

	for (i = 0; i < listLength; i++)
	{
		//读取班级的基本数据
		fscanf(fp, "%s%s%d", classNumber, leaderNumber, &studentCount);
		//之后创建一个班级。最后一个参数传值0而不是studentCount是因为之后的for循环调用的appendStudent函数
		//会调用ClassInfo类里面的addStudent函数,这个函数是假定数组在没有调用这个函数之前长度是0的
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

/*************************************** 作业信息结构体 ********************************************/
struct JobInfo
{
	char ClassNumber[STRINGLENGTH];//班级编号，用于标识作业的归属
	char JobNumber[STRINGLENGTH];//作业编号
	char CourseName[STRINGLENGTH];//课程名
	int JobTime;//作业次数
	char JobContent[STRINGLENGTH];//作业内容
	char ArrangementTime[STRINGLENGTH];//布置时间
	char JobDeadline[STRINGLENGTH];//截止时间
	char JobNote[STRINGLENGTH];//作业备注 
};

//创建一个新的作业
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

//定义一个作业数组
struct JobInfo JobArrayList[MAXARRAYSIZE];
//作业数组的长度
int JobCount = 0;

//增加一个作业任务
void addJob(char* classNumber, char* jobNumber, char* courseName, int jobTime, char* jobContent, char* arrangementTime, char* jobDeadline, char* jobNote)
{
	JobArrayList[JobCount++] = createJob(classNumber, jobNumber, courseName, jobTime, jobContent, arrangementTime, jobDeadline, jobNote);
}

//按照作业编号删除一个作业
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
			printf("TIPS：已成功将作业编号：%s的作业信息从列表中删除！\n", jobNumber);
			return;
		}
	}
	printf("ERROR：作业列表中不存在作业编号：%s的作业信息，删除失败！\n", jobNumber);
}

//修改作业的截止时间
void alterJob(char* jobNumber, char* newDeadline)
{
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].JobNumber, jobNumber))
		{
			strcpy(JobArrayList[i].JobDeadline, newDeadline);
			printf("TIPS：已成功将作业编号：%s的截止时间修改为：%s\n", jobNumber, newDeadline);
			return;
		}
	}
	printf("ERROR：作业列表中不存在作业编号：%s的作业信息，修改失败！\n", jobNumber);
}

//查询作业的有关信息
void queryJob(char* jobNumber)
{
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].JobNumber, jobNumber))
		{
			printf("作业编号：%s\n", JobArrayList[i].JobNumber);
			printf("课程名称：%s\n", JobArrayList[i].CourseName);
			printf("作业次数：%d\n", JobArrayList[i].JobTime);
			printf("作业内容：%s\n", JobArrayList[i].JobContent);
			printf("发布时间：%s\n", JobArrayList[i].ArrangementTime);
			printf("截止时间：%s\n", JobArrayList[i].JobDeadline);
			printf("作业备注：%s\n", JobArrayList[i].JobNote);
			return;
		}
	}
}

//查询所有作业列表
void travelArrayList(char* classNumber)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].ClassNumber, classNumber))
		{
			atLeastOne = 1;
			printf("作业编号：%s\n", JobArrayList[i].JobNumber);
			printf("课程名称：%s\n", JobArrayList[i].CourseName);
			printf("作业次数：%d\n", JobArrayList[i].JobTime);
			printf("作业内容：%s\n", JobArrayList[i].JobContent);
			printf("发布时间：%s\n", JobArrayList[i].ArrangementTime);
			printf("截止时间：%s\n", JobArrayList[i].JobDeadline);
			printf("作业备注：%s\n", JobArrayList[i].JobNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：作业列表中不存在您班级的作业信息！\n");
	}
}

//按时间范围查询
void queryTime(char* classNumber, char* beginTime, char* endTime)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].ClassNumber, classNumber) && strcmp(JobArrayList[i].ArrangementTime, beginTime) >= 0 && strcmp(JobArrayList[i].ArrangementTime, endTime) <= 0)
		{
			atLeastOne = 1;
			printf("作业编号：%s\n", JobArrayList[i].JobNumber);
			printf("课程名称：%s\n", JobArrayList[i].CourseName);
			printf("作业次数：%d\n", JobArrayList[i].JobTime);
			printf("作业内容：%s\n", JobArrayList[i].JobContent);
			printf("发布时间：%s\n", JobArrayList[i].ArrangementTime);
			printf("截止时间：%s\n", JobArrayList[i].JobDeadline);
			printf("作业备注：%s\n", JobArrayList[i].JobNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：作业列表中不存在您班级的作业信息！\n");
	}
}

//按课程名查询
void queryCourse(char* classNumber, char* courseName)
{
	int atLeastOne = 0;
	int i = 0;
	for (i = 0; i < JobCount; i++)
	{
		if (!strcmp(JobArrayList[i].ClassNumber, classNumber) && !strcmp(JobArrayList[i].CourseName, courseName))
		{
			atLeastOne = 1;
			printf("作业编号：%s\n", JobArrayList[i].JobNumber);
			printf("课程名称：%s\n", JobArrayList[i].CourseName);
			printf("作业次数：%d\n", JobArrayList[i].JobTime);
			printf("作业内容：%s\n", JobArrayList[i].JobContent);
			printf("发布时间：%s\n", JobArrayList[i].ArrangementTime);
			printf("截止时间：%s\n", JobArrayList[i].JobDeadline);
			printf("作业备注：%s\n", JobArrayList[i].JobNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：作业列表中不存在您班级的作业信息！\n");
	}
}

//按时间截止排序升序
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

//保存文件
void saveJobFile()
{
	FILE* fp = fopen("作业信息表.txt", "w");
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

//读取文件
void readJobFile()
{
	FILE* fp = fopen("作业信息表.txt", "r");
	//读取文件条目数
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

/*************************************** 提交情况结构体 ********************************************/
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
			printf("TIPS：已成功将学生：%s的编号：%s的作业从提交情况列表中删除！\n", studentNumber, jobNumber);
			return;
		}
	}
	printf("ERROR：提交情况列表中不存在相关的作业提交信息，删除失败！\n");
}

void alterSubmit(char* studentNumber, char* jobNumber, char* newTime)
{
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].StudentNumber, studentNumber) && !strcmp(SubmitArrayList[i].JobNumber, jobNumber))
		{
			strcpy(SubmitArrayList[i].SubmitTime, newTime);
			printf("TIPS：已成功将学生：%s的编号：%s的作业提交时间修改为：%s！\n", studentNumber, jobNumber, newTime);
			return;
		}
	}
	printf("ERROR：提交情况列表中不存在相关的作业提交信息，修改失败！\n");
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
			printf("班级编号：%s\n", SubmitArrayList[i].ClassNumber);
			printf("学生学号：%s\n", SubmitArrayList[i].StudentNumber);
			printf("作业编号：%s\n", SubmitArrayList[i].JobNumber);
			printf("作业课程：%s\n", SubmitArrayList[i].CourseName);
			printf("提交时间：%s\n", SubmitArrayList[i].SubmitTime);
			printf("提交备注：%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：提交情况列表中不存在您班级的作业信息！\n");
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
			printf("班级编号：%s\n", SubmitArrayList[i].ClassNumber);
			printf("学生学号：%s\n", SubmitArrayList[i].StudentNumber);
			printf("作业编号：%s\n", SubmitArrayList[i].JobNumber);
			printf("作业课程：%s\n", SubmitArrayList[i].CourseName);
			printf("提交时间：%s\n", SubmitArrayList[i].SubmitTime);
			printf("提交备注：%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：提交情况列表中不存在任何相关的作业信息，查询失败！\n");
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
			printf("班级编号：%s\n", SubmitArrayList[i].ClassNumber);
			printf("学生学号：%s\n", SubmitArrayList[i].StudentNumber);
			printf("作业编号：%s\n", SubmitArrayList[i].JobNumber);
			printf("作业课程：%s\n", SubmitArrayList[i].CourseName);
			printf("提交时间：%s\n", SubmitArrayList[i].SubmitTime);
			printf("提交备注：%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：提交情况列表中不存在任何相关的作业信息，查询失败！\n");
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
			printf("班级编号：%s\n", SubmitArrayList[i].ClassNumber);
			printf("学生学号：%s\n", SubmitArrayList[i].StudentNumber);
			printf("作业编号：%s\n", SubmitArrayList[i].JobNumber);
			printf("作业课程：%s\n", SubmitArrayList[i].CourseName);
			printf("提交时间：%s\n", SubmitArrayList[i].SubmitTime);
			printf("提交备注：%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：提交情况列表中不存在任何相关的作业信息，查询失败！\n");
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
	int count = 0;//保存提交作业的数量
	int i = 0;
	for (i = 0; i < SubmitCount; i++)
	{
		if (!strcmp(SubmitArrayList[i].ClassNumber, classNumber) && !strcmp(SubmitArrayList[i].CourseName, courseName))
		{
			count++;
		}
	}
	printf("TIPS：班级：%s提交课程%s已有%d份!\n", classNumber, courseName, count);
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
			printf("班级编号：%s\n", SubmitArrayList[i].ClassNumber);
			printf("学生学号：%s\n", SubmitArrayList[i].StudentNumber);
			printf("作业编号：%s\n", SubmitArrayList[i].JobNumber);
			printf("作业课程：%s\n", SubmitArrayList[i].CourseName);
			printf("提交时间：%s\n", SubmitArrayList[i].SubmitTime);
			printf("提交备注：%s\n", SubmitArrayList[i].SubmitNote);
			printf("\n------------------------------\n\n");
		}
	}
	if (!atLeastOne)
	{
		printf("ERROR：提交情况列表中不存在任何相关的作业信息，查询失败！\n");
	}
}

void saveSubmitFile()
{
	int i = 0;
	FILE* fp = fopen("提交情况表.txt", "w");
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
	FILE* fp = fopen("提交情况表.txt", "r");
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

/*************************************** 主体函数的声明 ********************************************/
void IdentityMenu(struct ListNode* pHead);//身份登录菜单

int AdminLogin();//系统管理员身份登录界面
int LeaderLogin(struct ListNode* pHead);//学习委员登录
int NormalLogin(struct ListNode* pHead);//普通学生登录

void AdminMenu(struct ListNode* pHead);//管理员菜单
void LeaderMenu();//学习委员菜单
void NormalMenu();//普通学生菜单

void AddClass(struct ListNode* pHead);//增加班级基础数据
void DeleteClass(struct ListNode* pHead);//删除班级
void AlterClass(struct ListNode* pHead);//修改班级学习委员
void QueryClass(struct ListNode* pHead);//查询班级基础数据
void AddStudent(struct ListNode* pHead);//增加一个学生的基础信息
void DeleteStudent(struct ListNode* pHead);//删除学生
void AlterStudent(struct ListNode* pHead);//修改学生密码
void QueryStudent(struct ListNode* pHead);//查询学生

void AddJob();//增加作业基础数据
void DeleteJob();//删除作业
void AlterJob();//修改作业截止时间
void QueryJob();//查询班级里面的所有作业
void QueryTime();//按时间范围查询作业
void QueryCourse();//按课程名称查询作业
void SortTime();//按作业截止时间升序
void AddSubmit();//增加作业提交情况
void DeleteSubmit();//删除作业提交情况
void AlterSubmit();//修改作业提交时间
void QuerySubmit();//查询所有作业提交情况
void QuerySubmitTime();//按时间范围查询
void QuerySubmitCourse();//按课程查询
void QuerySubmitStudent();//查询某一个同学的提交情况
void SortSubmit();//按提交时间升序
void StatisticsCourse();//统计课程提交情况
void StatisticsStudent();//统计学生提交情况

void QueryOwnSubmit();//查询本人提交情况
/***************************************************************************************************/

/*************************************** 主体函数的定义 ********************************************/
//身份登录菜单
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
	printf("\t\t\t ******************** 学委作业管理系统 ********************\n\n");
	printf("\t\t\t\t\t 1、系统管理员身份登录\n");
	printf("\t\t\t\t\t 2、班级学委身份登录\n");
	printf("\t\t\t\t\t 3、普通学生身份登录\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t 请输入您的选择：");
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
			printf("ERROR：用户名或密码错误，登录失败！");
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
			printf("ERROR：您还不是班级的学习委员哦，认证失败！");
		}
		else
		{
			printf("ERROR：登录失败！");
		}
		break;
	case 3:
		ret = NormalLogin(pHead);
		if (!ret)
		{
			printf("ERROR：登录失败！");
		}
		else
		{
			NormalMenu();
		}
		break;
	default:
		break;
	}
	printf("按 ENTER 重新登录系统！");
	getchar();
	getchar();
	IdentityMenu(pHead);
}

//系统管理员身份登录界面
int AdminLogin()
{
	char account[STRINGLENGTH], password[STRINGLENGTH];
	system("cls");
	printf("******************** 管理员登录系统 ********************\n\n");
	printf("请输入您的管理员账户：");
	scanf("%s", account);
	printf("请输入您的登录密码：");
	scanf("%s", password);
	if (!strcmp(account, "admin") && !strcmp(password, "666666"))
	{
		return 1;
	}
	return 0;
}

//学习委员登录
int LeaderLogin(struct ListNode* pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentPassword[STRINGLENGTH];
	int ret = 0;
	system("cls");
	printf("******************** 学习委员登录系统 ********************\n\n");
	printf("请输入您的班级编号：");
	scanf("%s", classNumber);
	printf("请输入您的学生编号：");
	scanf("%s", studentNumber);
	printf("请输入您的登录密码：");
	scanf("%s", studentPassword);
	ret = isStudent(pHead, classNumber, studentNumber, studentPassword);
	strcpy(CurrentOperatorClass, classNumber);
	strcpy(CurrentOperatorNumber, studentNumber);
	return ret;
}

//普通学生登录
int NormalLogin(struct ListNode* pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentPassword[STRINGLENGTH];
	int ret = 0;
	system("cls");
	printf("******************** 普通学生登录系统 ********************\n\n");
	printf("请输入您的班级编号：");
	scanf("%s", classNumber);
	printf("请输入您的学生编号：");
	scanf("%s", studentNumber);
	printf("请输入您的登录密码：");
	scanf("%s", studentPassword);
	ret = isStudent(pHead, classNumber, studentNumber, studentPassword);
	strcpy(CurrentOperatorClass, classNumber);
	strcpy(CurrentOperatorNumber, studentNumber);
	return ret;
}

//管理员菜单
void AdminMenu(struct ListNode* pHead)
{
	int switch_on = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 6; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ********************* 管理员操作菜单 *********************\n\n");
	printf("\t\t\t\t\t 1、增加班级基础数据\n");
	printf("\t\t\t\t\t 2、删除班级基础数据\n");
	printf("\t\t\t\t\t 3、修改班级学习委员\n");
	printf("\t\t\t\t\t 4、查询班级基础数据\n");
	printf("\t\t\t\t\t 5、增加学生基本信息\n");
	printf("\t\t\t\t\t 6、删除学生基本信息\n");
	printf("\t\t\t\t\t 7、修改学生登录密码\n");
	printf("\t\t\t\t\t 8、查询学生基本信息\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t 请输入您的选择：");
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
	printf("按 ENTER 返回当前操作菜单！");
	getchar();
	getchar();
	AdminMenu(pHead);
}

//学习委员菜单
void LeaderMenu()
{
	int switch_on = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 4; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ********************* 学习委员操作菜单 *********************\n\n");
	printf("\t\t\t\t\t 1、增加作业基础数据\n");
	printf("\t\t\t\t\t 2、删除作业基础数据\n");
	printf("\t\t\t\t\t 3、修改作业截止时间\n");
	printf("\t\t\t\t\t 4、查询所有作业信息\n");
	printf("\t\t\t\t\t 5、按时间范围查询作业\n");
	printf("\t\t\t\t\t 6、按课程名称查询作业\n");
	printf("\t\t\t\t\t 7、按作业截止时间升序\n");
	printf("\t\t\t\t\t 8、增加作业提交情况\n");
	printf("\t\t\t\t\t 9、删除作业提交情况\n");
	printf("\t\t\t\t\t 10、修改作业提交时间\n");
	printf("\t\t\t\t\t 11、查询本班所有提交情况\n");
	printf("\t\t\t\t\t 12、按时间范围查询列表\n");
	printf("\t\t\t\t\t 13、按课程查询作业列表\n");
	printf("\t\t\t\t\t 14、查询某同学的提交情况\n");
	printf("\t\t\t\t\t 15、按提交时间升序显示\n");
	printf("\t\t\t\t\t 16、统计各课程的提交情况\n");
	printf("\t\t\t\t\t 17、统计各学生的提交情况\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t 请输入您的选择：");
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
	printf("按 ENTER 返回当前操作菜单！");
	getchar();
	getchar();
	LeaderMenu();
}

//普通学生登录菜单
void NormalMenu()
{
	int switch_on = 0;
	int i = 0;
	system("cls");
	for (i = 0; i < 8; i++)
	{
		printf("\n");
	}
	printf("\t\t\t ********************* 普通学生操作菜单 *********************\n\n");
	printf("\t\t\t\t\t 1、查询作业列表\n");
	printf("\t\t\t\t\t 2、查看本人提交情况\n\n");
	printf("\t\t\t **********************************************************\n\n");
	printf("\t\t\t\t\t 请输入您的选择：");
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
	printf("按 ENTER 返回当前操作菜单！");
	getchar();
	getchar();
	NormalMenu();
}

void AddClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 增加班级基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	createClass(pHead, classNumber, "NULL", 0);
}

void DeleteClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 删除班级基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	deleteClass(pHead, classNumber);
}

void AlterClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 修改班级基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入班级学习委员：");
	scanf("%s", studentNumber);
	alterClass(pHead, classNumber, studentNumber);
}

void QueryClass(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 查询班级基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	queryClass(pHead, classNumber);
}

void AddStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentName[STRINGLENGTH], studentPassword[STRINGLENGTH];
	system("cls");
	printf("******************** 增加学生基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	printf("请输入学生姓名：");
	scanf("%s", studentName);
	printf("请输入登录密码：");
	scanf("%s", studentPassword);
	appendStudent(pHead, classNumber, studentNumber, studentName, studentPassword);
}

void DeleteStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 删除学生基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	deleteStudent(pHead, classNumber, studentNumber);
}

void AlterStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], studentPassword[STRINGLENGTH];
	system("cls");
	printf("******************** 修改学生基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	printf("请输入登录密码：");
	scanf("%s", studentPassword);
	alterStudent(pHead, classNumber, studentNumber, studentPassword);
}

void QueryStudent(struct ListNode * pHead)
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 查询学生基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	queryStudent(pHead, classNumber, studentNumber);
}

void AddJob()
{
	int jobTime = 0;
	char classNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], courseName[STRINGLENGTH], jobContent[STRINGLENGTH], arrangementTime[STRINGLENGTH], jobDeadline[STRINGLENGTH], jobNote[STRINGLENGTH];
	system("cls");
	printf("******************** 增加作业基础数据 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入作业编号：");
	scanf("%s", jobNumber);
	printf("请输入课程名称：");
	scanf("%s", courseName);
	printf("请输入作业次数：");
	scanf("%d", &jobTime);
	printf("请输入作业内容：");
	scanf("%s", jobContent);
	printf("请输入布置时间：");
	scanf("%s", arrangementTime);
	printf("请输入截止时间：");
	scanf("%s", jobDeadline);
	printf("请输入任务备注：");
	scanf("%s", jobNote);
	addJob(classNumber, jobNumber, courseName, jobTime, jobContent, arrangementTime, jobDeadline, jobNote);
}

void DeleteJob()
{
	int jobTime = 0;
	char jobNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 删除作业基础数据 ********************\n\n");
	printf("请输入作业编号：");
	scanf("%s", jobNumber);
	deleteJob(jobNumber);
}

void AlterJob()
{
	int jobTime = 0;
	char jobNumber[STRINGLENGTH], newDeadline[STRINGLENGTH];
	system("cls");
	printf("******************** 修改作业基础数据 ********************\n\n");
	printf("请输入作业编号：");
	scanf("%s", jobNumber);
	printf("请输入截止时间：");
	scanf("%s", newDeadline);
	alterJob(jobNumber, newDeadline);
}

void QueryJob()
{
	system("cls");
	printf("******************** 查询作业基础数据 ********************\n\n");
	travelArrayList(CurrentOperatorClass);
}

void QueryTime()
{
	char beginTime[STRINGLENGTH], endTime[STRINGLENGTH];
	system("cls");
	printf("******************** 按时间范围查询作业 ********************\n\n");
	printf("请输入开始时间：");
	scanf("%s", beginTime);
	printf("请输入结束时间：");
	scanf("%s", endTime);
	queryTime(CurrentOperatorClass, beginTime, endTime);
}

void QueryCourse()
{
	char courseName[STRINGLENGTH];
	system("cls");
	printf("******************** 按课程名称查询作业 ********************\n\n");
	printf("请输入课程名称：");
	scanf("%s", courseName);
	queryCourse(CurrentOperatorClass, courseName);
}

void SortTime()
{
	system("cls");
	printf("******************** 按作业截止时间升序 ********************\n\n");
	sortDeadline();
	travelArrayList(CurrentOperatorClass);
}

void AddSubmit()
{
	char classNumber[STRINGLENGTH], studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], courseName[STRINGLENGTH], submitTime[STRINGLENGTH], submitNote[STRINGLENGTH];
	system("cls");
	printf("******************** 增加作业提交情况 ********************\n\n");
	printf("请输入班级编号：");
	scanf("%s", classNumber);
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	printf("请输入作业编号：");
	scanf("%s", jobNumber);
	printf("请输入课程名称：");
	scanf("%s", courseName);
	printf("请输入提交时间：");
	scanf("%s", submitTime);
	printf("请输入提交备注：");
	scanf("%s", submitNote);
	addSubmit(classNumber, studentNumber, jobNumber, courseName, submitTime, submitNote);
}

void DeleteSubmit()
{
	char studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 删除作业提交情况 ********************\n\n");
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	printf("请输入作业编号：");
	scanf("%s", jobNumber);
	deleteSubmit(studentNumber, jobNumber);
}

void AlterSubmit()
{
	char studentNumber[STRINGLENGTH], jobNumber[STRINGLENGTH], newTime[STRINGLENGTH];
	system("cls");
	printf("******************** 修改作业提交时间 ********************\n\n");
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	printf("请输入作业编号：");
	scanf("%s", jobNumber);
	printf("请输入提交时间：");
	scanf("%s", newTime);
	alterSubmit(studentNumber, jobNumber, newTime);
}

void QuerySubmit()
{
	system("cls");
	printf("******************** 查询所有作业提交情况 ********************\n\n");
	travelSubArrayList(CurrentOperatorClass);
}

void QuerySubmitTime()
{
	char beginTime[STRINGLENGTH], endTime[STRINGLENGTH];
	system("cls");
	printf("******************** 按时间范围查询作业 ********************\n\n");
	printf("请输入开始时间：");
	scanf("%s", beginTime);
	printf("请输入结束时间：");
	scanf("%s", endTime);
	querySubmitTime(CurrentOperatorClass, beginTime, endTime);
}

void QuerySubmitCourse()
{
	char courseName[STRINGLENGTH];
	system("cls");
	printf("******************** 按课程名称查询作业 ********************\n\n");
	printf("请输入课程名称：");
	scanf("%s", courseName);
	querySubmitCourse(CurrentOperatorClass, courseName);
}

void QuerySubmitStudent()
{
	char studentNumber[STRINGLENGTH];
	system("cls");
	printf("******************** 查询某一位同学的作业提交情况 ********************\n\n");
	printf("请输入学生学号：");
	scanf("%s", studentNumber);
	queryStudentNumber(studentNumber);
}

void SortSubmit()
{
	system("cls");
	printf("******************** 按作业提交时间升序 ********************\n\n");
	sortSubmitTime();
	travelSubArrayList(CurrentOperatorClass);
}

void StatisticsCourse()
{
	system("cls");
	printf("******************** 统计课程提交情况 ********************\n\n");
	statisticsCourse(CurrentOperatorClass, "语文");
	statisticsCourse(CurrentOperatorClass, "数学");
	statisticsCourse(CurrentOperatorClass, "英语");
}

void StatisticsStudent()
{
	system("cls");
	printf("******************** 统计学生提交情况 ********************\n\n");
	statisticsClass(CurrentOperatorClass);
}

void QueryOwnSubmit()
{
	system("cls");
	printf("******************** 查询本人作业提交情况 ********************\n\n");
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
