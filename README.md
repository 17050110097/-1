# -1
学委作业管理系统
学委作业管理系统
问题描述：
为了方便学委发布作业信息和记录收作业的情况，设计一个学委作业管理系统。要求可以记录作业的基本信息（作业编号，课程名称，作业次数，作业内容，布置时间，提交截止时间，备注……），记录每个同学的作业提交情况（班级，学号，作业编号，提交时间，备注……）。管理员可以管理班级、角色（学委和学生），学委可以管理作业和作业提交情况，学生可以查看作业和自己的作业提交情况。
基本功能要求：
系统中的作业列表、作业提交情况列表、学生列表等都必须采用所学过的一种数据结构（链表、栈、队列、树等）存储，不能全部只使用数组。所有功能的操作是对数据结构（数组或链表等）中的数据进行操作。
每一个功能模块需要划分多个子模块，使用各自不同的结构体来储存不同的信息，实现信息的添加、删除、查询、修改、排序等操作。其他信息根据功能需求可以自行设计。
（1）管理员对班级和班级学生的增删改查功能，管理员设置角色（学委/学生），每个班只有一个学委。
（2）学委和学生的登录功能，需要输入正确的密码登录。
（3）学委对作业的增删改，查询所有作业列表，按时间范围查询作业，按课程查询作业，按时间的升序或降序排列显示。
（4）学委对作业提交情况的增删改，查询学生的所有作业提交列表，按时间范围查询作业提交列表，按课程查询作业提交情况，查询某同学的作业提交情况，按时间、提交次数等的升序或降序排列显示。
（5）学生查看作业，学生查看本人的作业提交情况。
扩展功能要求：
（1）统计各课程的作业提交情况，统计各学生的作业提交情况。
（2）运行文件对各种信息进行合理的保存和读取。
