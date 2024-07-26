#  cpp-mysql-database_manager

# 学习教务管理系统的记录

最近学习了基础的c++以及mysql的知识，迫不及待寻找紧密相关的项目来巩固所学知识，经过筛选找了一个教务管理系统的项目，总共一千多行代码。

> 很多同学觉得教务系统烂大街了，也觉得简单，但是事实上真正写一个就知道并非想的那么简单！
>
> 虽然内部没有什么难的逻辑和函数，但是想要整个啃下来真是不容易。就那我自己来说，我在写完的时候，看到打印出来的页面别提多开心了，但是一操作就退出，好嘛，出bug了！
>
> 经过2小时的寻找才找到，竟是判断键盘事件的时候，把 == 写成了 =，这么一个小错误可把我气的够呛，后面也遇到了无法注册，无法创建表格等一系列问题。

通过本项目，我学到了c++连接mysql相关知识，windows相关函数设计页面，system执行系统函数，加深了面向对象，函数重载等一系列知识的认识。

# 接下来先看看效果展示图

分别对应登录页面，老师登录界面，学生登录界面



![ 2024-07-26 152616.png](https://s2.loli.net/2024/07/26/qomwF54Nbk7cKar.png)

![image.png](https://s2.loli.net/2024/07/26/8xsaFp4gzXPkBCr.png)

![image.png](https://s2.loli.net/2024/07/26/qnODpIQU4YXlKHM.png)

# **文件的解释**

> table和databaseManager文件用来创建初始的数据库表格，以及数据库的配置
>
> console 文件控制管理系统的内部逻辑
>
> main 为程序的入口



## table

主要是构建需要的表的结构以及基本的函数

构建Base基类包含基础变量number，name，再定义并实现set和get函数

**Person**类继承Base类，具有属性number, name, sex, age, dname, password，分别定义set和get函数

**Course**类继承Base类，具有属性number,name,tname，对tname设置get和set函数，定义stasue表示选课状态

**Department**类继承Base类，具有number，name属性

**Sc**表具有sno，cno，score属性，分别定义set和get函数

定义函数重载各种类的比较函数，一个非降序函数，Department，Person，Course表根据number进行比较，Sc表根据cno排序

## databaseManager

构建databaseManager类

Connect 函数连接数据库

1. mysql_library_init函数判断mysql是否初始合法
2. mysql_init 进行初始化，若返回NULL则表示连接失败
3. mysql_options 函数设置，可以设置charset，执行完毕为0
4. mysql_real_connect() 函数传递数据库指针，host*主机名或IP地址*，user*用户名* ，password，database数据库名，port端口号，unix套接字文件名，客户端标志     连接失败返回null

log函数构建注册表，将content记录记入log.txt

1. 构建systemtime 对象，并通过GetLocalTime函数获取当前的时间
2. 定义一个字符数组并把时间传递道数组中
3. 打开文件选择文件方式是文件末尾追加记录
4. is_open函数判断文件是否打开并输入字符串
5. 关闭文件

ExeSql执行sql语句函数

1. 记录sql语句

2. mysql_query函数传入数据库以及sql的c形式字符串，执行完毕为0，则使用mysql_store_result 把查询结果储存到result

3. 否则就使用mysql_close函数关闭连接返回false

   

键值对返回类型GetTables函数获取数据库的所有表

1. 定义一个该键值对的map m
2. 先插入5张表，初始为false，表示未查找到
3. 使用ExeSql函数执行show tables查询若成功
4. 定义变量记录result的数量，使用mysql_num_fields获取结果中的列数

5. 定义MYSQL_ROW 结构体变量，使用mysql_fetch_row函数读取result结果集
6. 不断遍历每行，把非NULL元素且未遍历过的元素标记为true
7. 返回m结果集

InitializeTbs函数初始化表

1. 先获取数据库所有的表
2. 判断每个是否遍历到，未遍历到就创建表

CreateDepartmentTb函数创建部门表

1. 定义str存储sql语句，创建表的结构，以及插入1 计算机科学与技术 2 土木工程  3 市场营销 4 物流管理 5 人工智能

设置set函数GetDepartmentTB函数获取department表中的所有内容按照compare函数排序

1. 定义一个set对compare排序的函数的集合
2. 跟上述遍历相同方式，字符串数组存储查询记录，把记录插入集合

person

1. 根据传入的mode判断teacher和student，使用sprintf_s函数拼接sql语句赋值到str字符数组中
2. 执行sql语句

GetPersonTb也是相同的方式

course

Sc

创建MYSQL类对象mydata

创建result结果集记录查询结果



## consloe

1. 构建Console类 构造函数

   1. 输出标题 教务管理系统  .data()函数在字符串末尾加上一个空格
   2. 检查路径文件夹是否存在，不存在就使用系统函数创建文件夹
   3. 存在就使用getline函数获取record中存储的账户和数据库的配置信息
   4. 若已经建立连接则预获取部门表并执行Control函数

2. Control函数控制**整体的逻辑**

   1. 先LoadinPage加载初始界面
   2. 再移动箭头到初始位置ArrowsMove
   3. 对获取的键盘事件判断若为Esc就退出循环
   4. 判断Y坐标位置
      1. 5对应输入account 
      2. 6对应输入password
      3. 7对应SignIn登录功能，检查是否注册已注册就WritRecord写入记录进入主页面MainPage，未注册就 重新加载页面  
      4. 8对应教职工的AddTeacherInfo注册 按钮 注册完毕重新载入页面
      5. 9对应配置数据库的信息
      6. 10 对应退出程序 和esc相同

3. **ConnectDatabase函数**  构建数据库连接 

   1. 通过databaseManager实例对象的Connect函数进行连接  并通过Initialize函数进行初始化
   2. 若连接失败  通过Alert函数打印连接失败字样，并询问是否可以打开数据库配置信息  
      1. 键入enter返回true进入config配置函数并再次尝试connextDatabase函数连接数据库  
      2. 键入esc返回false并退出程序

4. **Alert函数**  输出辅助操作说明选项页面，并不断获取键盘事件

   1. 获取到enter 清屏并返回true
   2. 获取到esc  清屏并返回false

5. **config函数**  配置数据库信息

   1. 输出配置页面信息 以及初始的数据库信息
   2. 重新设置光标的初始位置
   3. 循环  ArrowsMove函数打印箭头，并不断获取键盘事件，在函数限定范围内，ws移动光标，若是获取到esc，赋值给operand  
   4. 判断operand为esc就结束配置
   5. 获取Y坐标并Input函数输入相应的信息
   6. 需注意**确定**信息要把数据库配置WriteRecord函数写入记录

6. **SetCursor函数**设置光标位置

   1. 更新COORD结构体变量pos的xy坐标值
   2. SetConsoleCursorPosition() 函数传入控制台标准设备 和 COORD结构体 指定控制台屏幕缓冲区中的光标位置
   3. CONSOLE_CURSOR_INFO结构体变量cci控制光标的大小以及是否可见
   4. 使用SrtConsoleCursorInfo函数传入标准输出设备以及 cci

7. **ArrowsMove函数** 再光标位置输出 -> 

   1. SetCursor函数设置光标位置并输出  ->
   2. 循环检测按键
      1. _kbhit 函数检测是否有按键
      2. _getch函数获取按键的值
         1. enter键则设置光标位置 operand记录当前的按键 结束移动
         2. esc也是同理
         3. ws上下移动更新y坐标 中间需判断不要超过最大最小位置值 重新设置光标位置输出 ->
         4. for循环判断操作是否在自定义传入第五个参数的操作集中

8. **Input函数** 输入数据

   1. 设置光标到输入的位置，visible为ture
   2. 输入一行空可以覆盖原先内容并重新设置光标
   3. 输入内容

9. **LoadinPage函数**   加载初始界面  后通过SetCursor设置光标的位置为初始位置

10. **WriteRecord函数**  记录，文件写入模式把当前登录的以及数据库配置信息记录

11. **SignIn函数** 判断登录是否成功

    1. 拼接sql语句调用databaseManager对象的ExeSql函数查询，teacher和student都不是则查询失败 

    2.  sql执行且查询记录数量为1则表示查询到->账号密码都对应的记录只存在一条

    3. mysql_num_rows() 统计结果行数

       

12. **MainPage函数** 显示登录后的界面

    1. 判断mode是谁登录

    2. 老师登录

       1. 显示登录界面并再初始位置打印-> 
       2. 更新last作为输出-> 的y坐标
       3. 判断获取到的operand
          1. 获取到为esc则询问是否退出 
          2. 获取到enter就判断位置 根据相应位置执行操作
             1. 4则执行ManageCourse函数管理课程
             2. 5则ManagerStudent函数管理学生
             3. 6则DeleteTeacherInfo执行删除当前教职工

    3. 学生登录 **ChoiceCourse函数**

       1. getPerson函数多表查询 no，s.name,sex,age,d.name,password 获取student信息
       2. getCourse函数多表查询 cno,c.name,t.name 获取课程信息
       3. 实例化Person类
       4. 显示登录界面 中间通过it迭代器遍历打印student信息
       5. 接下来是选课操作
          1. 课程数量为0就输出暂无课程
          2. 相同迭代器方式遍历Course，不断取Course存入Course类vector中，并将status置为false表示未选
          3. 在内部相同迭代器遍历Sc表，将课程编号相同的状态置为true表示选课
          4. 打印课程表
          5. 判断status  输出已选或未选以及后续的内容
       6. 设置->到初始位置
       7. 根据operand执行
          1. esc则判断是否退出
          2. enter在分别设计选课以及取消选课

    4. **ManageCourse函数**  管理课程页面

       1. getPerson函数 联查no,t.name,sex,age,d.name,password
       2. 联查getCourse函数cno,c.name,t.name
       3. 打印界面  中间通过it迭代器遍历把每项存入vector容器方便后续查询 并输出课程信息
       4. 设置初始位置的->   此时ArrowsMove函数的第五个参数排上用场，传入自定义的'a''d' 分别表示添加课程和删除
       5. 根据operand的值判断
          1. esc就返回
          2. operand 为 a 执行AddCourseInfo函数增加课程，并更新last位置
          3. 判断是否有课程
             1. 进行enter显示全部学生ShowCourseAllStudent函数
             2. operand为d执行DeleteCourse函数并更新last

    5. **AddCourseInfo函数**   添加课程信息

       1. 定义需要插入课程的cno name tno tname信息

       2. **CourseInfoPage函数** 输出添加课程的页面并设置光标位置

       3. 循环内  

          1. 初始输出->

          2. 判断operand的值

             1. esc退出程序

             2. y坐标为5 输入cno

             3. 为6 输入name

             4. 为7   实例化Person 使用**ChoiceTeacher**选择教师，获取tno，tname  再使用CourseInfoPage函数进行添加

             5. 为8判断这三个值都不为空并做出提醒  拼接sql语句执行插入课程信息，并插入到co课程set内  判断课程号唯一

             6. 最后显示在CourseInforPage页面

                

    6. **ShowCourseAllStudent函数**   查看所有选课的人

       1. 创建自定义操作集
       2. 定义初始y坐标
       3. 执行视图查询语句查询no,s.name,sex,age,dno  根据课程编号和student编号
       4. 执行getPerson函数查询no,s.name,sex,age,d.name
       5. 再执行删除视图
       6. 循环
          1. 创建person的vector
          2. 打印界面
          3. 判断人数 为0输出暂无学生选课
          4. 否则就迭代器遍历person并把信息都加入vector中  打印信息
          5. 设置箭头位置，传入自定义操作集
          6. 判断operand
             1. esc就return
             2. 为操作集中的d就执行**DeleteStudentCourse函数** 删除选课的人 需要注意st的student信息也要执行erase

    7. **DeleteCourse函数**  删除课程

       1. 获取要删除课程的cno
       2. 拼接sql字符串执行，中间进行提醒

    8. **ManageStudent函数**  管理student页面

       1. 自定义操作集
       2. 定义y坐标
       3. getPerson函数联查获取no,s.name,sex,age,d.name
       4. 设计页面 输出信息
       5. 移动-> 并根据operand做出响应
          1. AddStudentInfo，ModifyStudentInfo，SearchStudentInfo，**DeleteStudentInfo**  分别对应添加，修改，查询，删除

    9. **AddStudentInfo函数** 添加student信息

       1. 定义student的信息
       2. InfoPage函数是界面函数
       3. 循环设置->位置  根据获取的键盘事件做出反应
          1. y坐标5678 10分别对应输入 no，name，sex，age，password
          2. y为9用ChoiceDepartment函数获取department实例对象，从而获取dname  再通过InfoPage函数把信息打到屏幕上
          3. 11确认时需要对上方信息提醒
          4. 拼接字符串执行插入信息 同时判断学号不能重复

    10. **SearchStudentInfo函数**  查询学生信息

        1. 定义信息变量
        2. 通过InfoPage函数把查询学生打印到屏幕
        3. 设置->位置，根据不同位置以及键盘事件做出响应
           1. 5678 10 对应输入no,name,sex,age(老师查询学生不应该每个信息都要填，事实上可能no,name就够)   同时拼接sql语句
           2. 思考修改，查找的逻辑不应如此

    11. **ModifyStudentInfo**    修改学生信息

        1. it迭代器遍历到当前人的部门
        2. 定义信息变量以及拼接的sql语句字符换
        3. 循环内获取原信息语句只能执行一遍，再把信息通过InfoPage打印
        4. 移动箭头输入修改的值 并记录拼接sql字符串
        5. 可以判断下是否修改就是有无拼接字符串

    12. **ChoiceDepartment** 选择部门

        1. 定义vector容器v用来存储部门表的查询结果，方便后续直接获取
        2. 打印界面
        3. 打印中间的输出内容通过it迭代器 将遍历的部门存入容器并打印到屏幕上
        4. 设置箭头并判断按键，esc就返回Department空传参的实例对象    enter就返回v中的departmen

    13. COORD结构体变量 pos记录位置

    14. CONSOLE_CURSOR_INFO 结构体变量 cci设置光标的信息

    15. operand记录操作符

    16. account password为账户和密码
    17. mode用于切换
    18. 数据库的配置信息
    19. 实例化数据库
    20. sqlStr字符数组记录sql语句
    21. 以及每种set自动排序集合变量



# 改进的建议

本管理系统初始页面是否应该添加学生的注册按钮，不应该只能在老师界面才能创建学生信息

另外老师查看当前课程所有成员时应当可以设置成绩

> 后续我也会新增这些功能









