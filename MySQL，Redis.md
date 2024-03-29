> **[数据库简要笔记](res/DB.md)**

***

## MySQL

***

### 什么是非关系型数据库？

非关系型数据库也叫NoSQL，采用键值对的形式进行存储。

它的读写性能很高，易于扩展，可分为内存性数据库以及文档型数据库，比如 Redis，Mongodb，HBase等等。

适合使用非关系型数据库的场景：

* 日志系统
* 地理位置存储
* 数据量巨大
* 高可用

### 关系型和非关系型数据库的区别你了解多少？

* 关系型数据库的优点
  - 容易理解。因为它采用了关系模型来组织数据。
  - 可以保持数据的一致性。
  - 数据更新的开销比较小。
  - 支持复杂查询（带where子句的查询）
* 非关系型数据库的优点
  - 不需要经过SQL层的解析，读写效率高。
  - 基于键值对，数据的扩展性很好。
  - 可以支持多种类型数据的存储，如图片，文档等等。

### 数据库三大范式精讲

**第一范式**

在任何一个关系数据库中，第一范式（1NF）是对关系模式的基本要求，不满足第一范式（1NF）的数据库就不是关系数据库。 所谓第一范式（1NF）是指数据库表的每一列都是不可分割的基本数据项，同一列中不能有多个值，即实体中的某个属性不能有多个值或者不能有重复的属性。

如果出现重复的属性，就可能需要定义一个新的实体，新的实体由重复的属性构成，新实体与原实体之间为一对多关系。在第一范式（1NF）中表的每一行只包含一个实例的信息。

简而言之，**第一范式就是无重复的列**。

**第二范式**

第二范式（2NF）是在第一范式（1NF）的基础上建立起来的，即满足第二范式（2NF）必须先满足第一范式（1NF）。第二范式（2NF）要求数据库表中的每个实例或行必须可以被惟一地区分。

为实现区分通常需要为表加上一个列，以存储各个实例的惟一标识。这个惟一属性列被称为主关键字或主键、主码。 第二范式（2NF）要求实体的属性完全依赖于主关键字。

所谓完全依赖是指不能存在仅依赖主关键字一部分的属性，如果存在，那么这个属性和主关键字的这一部分应该分离出来形成一个新的实体，新实体与原实体之间是一对多的关系。为实现区分通常需要为表加上一个列，以存储各个实例的惟一标识。

简而言之，**第二范式就是非主属性非部分依赖于主关键字**。

**第三范式**

满足第三范式（3NF）必须先满足第二范式（2NF）。简而言之，第三范式（3NF）要求一个数据库表中不包含已在其它表中已包含的非主关键字信息。

例如，**存在一个部门信息表，其中每个部门有部门编号（dept_id）、部门名称、部门简介等信息。那么在员工信息表中列出部门编号后就不能再将部门名称、部门简介等与部门有关的信息再加入员工信息表中。如果不存在部门信息表，则根据第三范式（3NF）也应该构建它，否则就会有大量的数据冗余。**

简而言之，第三范式就是属性不依赖于其它非主属性。

**简单归纳**：

- 第一范式（1NF）：字段不可分；
- 第二范式（2NF）：有主键，非主键字段依赖主键；
- 第三范式（3NF）：非主键字段不能相互依赖。

**解释**：

- 1NF：原子性。 字段不可再分,否则就不是关系数据库;
- 2NF：唯一性 。一个表只说明一个事物；
- 3NF：每列都与主键有直接关系，不存在传递依赖。

### 数据库中的主键、超键、候选键、外键是什么？

- **超键**：在关系中能唯一标识**元组的属性集**称为关系模式的超键

- **候选键**：不含有**多余属性的超键**称为候选键。也就是在候选键中，若再删除属性，就不是键了！

- **主键**：**用户选作元组标识的一个候选键程序主键**

- **外键**：如果关系模式**R中属性K是其它模式的主键**，那么**k在模式R中称为外键**。

**举例**：

| 学号     | 姓名   | 性别 | 年龄 | 系别   | 专业     |
| -------- | ------ | ---- | ---- | ------ | -------- |
| 20020612 | 李辉   | 男   | 20   | 计算机 | 软件开发 |
| 20060613 | 张明   | 男   | 18   | 计算机 | 软件开发 |
| 20060614 | 王小玉 | 女   | 19   | 物理   | 力学     |
| 20060615 | 李淑华 | 女   | 17   | 生物   | 动物学   |
| 20060616 | 赵静   | 男   | 21   | 化学   | 食品化学 |
| 20060617 | 赵静   | 女   | 20   | 生物   | 植物学   |

1. 超键：于是我们从例子中可以发现 学号是标识学生实体的唯一标识。那么该元组的超键就为学号。除此之外我们还可以把它跟其他属性组合起来，比如：(`学号`，`性别`)，(`学号`，`年龄`)
2. 候选键：根据例子可知，学号是一个可以唯一标识元组的唯一标识，因此学号是一个候选键，实际上，候选键是超键的子集，比如 （学号，年龄）是超键，但是它不是候选键。因为它还有了额外的属性。
3. 主键：简单的说，例子中的元组的候选键为学号，但是我们选定他作为该元组的唯一标识，那么学号就为主键。
4. 外键是相对于主键的，比如在学生记录里，主键为学号，在成绩单表中也有学号字段，因此学号为成绩单表的外键，为学生表的主键。

**主键为候选键的子集，候选键为超键的子集，而外键的确定是相对于主键的。**

### 关系型数据库的四大特性在得不到保障的情况下会怎样？

ACID，原子性(Atomicity)、一致性(Consistency)、隔离性(Isolation)、持久性(Durability)

我们以从A账户转账50元到B账户为例进行说明一下ACID这四大特性。

**原子性**

原子性是指一个事务是一个不可分割的工作单位，**其中的操作要么都做，要么都不做**。即要么转账成功，要么转账失败，是不存在中间的状态！

**如果无法保证原子性会怎么样？**

OK，就会出现数据不一致的情形，A账户减去50元，而B账户增加50元操作失败。系统将无故丢失50元~

**一致性**

一致性是指事务执行前后，数据处于一种合法的状态，这种状态是语义上的而不是语法上的。 那什么是合法的数据状态呢？这个状态是满足预定的约束就叫做合法的状态，再通俗一点，这状态是由你自己来定义的。**满足这个状态，数据就是一致的，不满足这个状态，数据就是不一致的！**

**如果无法保证一致性会怎么样？**

- 例一:A账户有200元，转账300元出去，此时A账户余额为-100元。你自然就发现了此时数据是不一致的，为什么呢？因为你定义了一个状态，余额这列必须大于0。
- 例二:A账户200元，转账50元给B账户，A账户的钱扣了，但是B账户因为各种意外，余额并没有增加。你也知道此时数据是不一致的，为什么呢？因为你定义了一个状态，要求A+B的余额必须不变。

**隔离性**

隔离性是指**多个事务并发执行的时候，事务内部的操作与其他事务是隔离的**，并发执行的各个事务之间不能互相干扰。

**如果无法保证隔离性会怎么样**？

假设A账户有200元，B账户0元。A账户往B账户转账两次，金额为50元，分别在两个事务中执行。如果无法保证隔离性，A可能就会出现扣款两次的情形，而B只加款一次，凭空消失了50元，依然出现了数据不一致的情形！

**持久性**

根据定义，**持久性是指事务一旦提交，它对数据库的改变就应该是永久性的**。接下来的其他操作或故障不应该对其有任何影响。

如果无法保证持久性会怎么样？

在MySQL中，为了解决CPU和磁盘速度不一致问题，MySQL是将磁盘上的数据加载到内存，对内存进行操作，然后再回写磁盘。好，假设此时宕机了，在内存中修改的数据全部丢失了，持久性就无法保证。

设想一下，系统提示你转账成功。但是你发现金额没有发生任何改变，此时数据出现了不合法的数据状态，我们将这种状态认为是**数据不一致**的情形。

### 数据库如何保证一致性？

分为两个层面来说。 

- **从数据库层面**，数据库通过原子性、隔离性、持久性来保证一致性。也就是说ACID四大特性之中，C(一致性)是目的，A(原子性)、I(隔离性)、D(持久性)是手段，是为了保证一致性，数据库提供的手段。**数据库必须要实现AID三大特性，才有可能实现一致性**。例如，原子性无法保证，显然一致性也无法保证。
- **从应用层面**，通过代码判断数据库数据是否有效，然后决定回滚还是提交数据！

### 数据库如何保证原子性？

主要是利用 Innodb 的**undo log**。 **undo log**名为回滚日志，是实现原子性的关键，当事务回滚时能够撤销所有已经成功执行的 SQL语句，他需要记录你要回滚的相应日志信息。 例如

- 当你delete一条数据的时候，就需要记录这条数据的信息，回滚的时候，insert这条旧数据
- 当你update一条数据的时候，就需要记录之前的旧值，回滚的时候，根据旧值执行update操作
- 当年insert一条数据的时候，就需要这条记录的主键，回滚的时候，根据主键执行delete操作

**undo log**记录了这些回滚需要的信息，当事务执行失败或调用了**rollback**，导致事务需要回滚，便可以利用**undo log**中的信息将数据回滚到修改之前的样子。

### 数据库如何保证持久性？

主要是利用Innodb的**redo log**。重写日志， 正如之前说的，MySQL是先把磁盘上的数据加载到内存中，在内存中对数据进行修改，再写回到磁盘上。如果此时突然宕机，内存中的数据就会丢失。 怎么解决这个问题？ 简单啊，事务提交前直接把数据写入磁盘就行啊。 这么做有什么问题？

- 只修改一个页面里的一个字节，就要将整个页面刷入磁盘，太浪费资源了。毕竟一个页面16kb大小，你只改其中一点点东西，就要将16kb的内容刷入磁盘，听着也不合理。
- 毕竟一个事务里的SQL可能牵涉到多个数据页的修改，而这些数据页可能不是相邻的，也就是属于随机IO。显然操作随机IO，速度会比较慢。

于是，决定采用**redo log**解决上面的问题。当做数据修改的时候，不仅在内存中操作，还会在**redo log**中记录这次操作。当事务提交的时候，会将**redo log**日志进行刷盘(**redo log**一部分在内存中，一部分在磁盘上)。当数据库宕机重启的时候，会将redo log中的内容恢复到数据库中，再根据**undo log**和**binlog**内容决定回滚数据还是提交数据。

**采用redo log的好处？**

其实好处就是将**redo log**进行刷盘比对数据页刷盘效率高，具体表现如下：

- **redo log**体积小，毕竟只记录了哪一页修改了啥，因此体积小，刷盘快。
- **redo log**是一直往末尾进行追加，属于顺序IO。效率显然比随机IO来的快。

### 你了解MySQL的内部构造吗？一般可以分为哪两个部分？

可以分为服务层和存储引擎层两部分，其中：

**服务层包括连接器、查询缓存、分析器、优化器、执行器等**，涵盖MySQL的大多数核心服务功能，以及所有的内置函数（如日期、时间、数学和加密函数等），所有跨存储引擎的功能都在这一层实现，比如存储过程、触发器、视图等。

**存储引擎层负责数据的存储和提取**。其架构模式是插件式的，支持InnoDB、MyISAM、Memory等多个存储引擎。现在最常用的存储引擎是InnoDB，它从MySQL 5.5.5版本开始成为了默认的存储引擎。

### 说一下MySQL是如何执行一条SQL的？具体步骤有哪些？

![image-20211005102655929](https://gitee.com/duycc/picgo/raw/master/20211005102657.png)

**Server层按顺序执行sql的步骤为**：

1. 客户端请求->
2. 连接器（验证用户身份，给予权限） ->
3. 查询缓存（存在缓存则直接返回，不存在则执行后续操作）->
4. 分析器（对SQL进行词法分析和语法分析操作） -> 
5. 优化器（主要对执行的sql优化选择最优的执行方案方法） -> 
6. 执行器（执行时会先看用户是否有执行权限，有才去使用这个引擎提供的接口）->
7. 去引擎层获取数据返回（如果开启查询缓存则会缓存查询结果）

**简单概括**：

- **连接器**：管理连接、权限验证；
- **查询缓存**：命中缓存则直接返回结果；
- **分析器**：对SQL进行词法分析、语法分析；（判断查询的SQL字段是否存在也是在这步）
- **优化器**：执行计划生成、选择索引；
- **执行器**：操作引擎、返回结果；
- **存储引擎**：存储数据、提供读写接口。

### 数据库并发事务会带来哪些问题？

[数据库事务的四大特性以及事务的隔离级别](https://www.cnblogs.com/fjdingsd/p/5273008.html)

### 事务四大特性（ACID）原子性、一致性、隔离性、持久性？

**原子性**：一个事务（transaction）中的所有操作，要么全部完成，要么全部不完成，不会结束在中间某个环节。
。事务在执行过程中发生错误，会被恢复（Rollback）到事务开始前的状态，就像这个事务从来没有执行过一样。
**一致性**：在事务开始之前和事务结束以后，数据库的完整性没有被破坏。这表示写入的资料必须完全符合所有的预设规则，这包含资料的精确度、串联性以及后续数据库可以自发性地完成预定的工作。
**隔离性**：数据库允许多个并发事务同时对其数据进行读写和修改的能力，隔离性可以防止多个事务并发执行时由于交叉执行而导致数据的不一致。事务隔离分为不同级别，包括读未提交（Read uncommitted）、读提交（read committed）、可重复读（repeatable read）和串行化（Serializable）。
**持久性**：事务处理结束后，对数据的修改就是永久的，即便系统故障也不会丢失。

### 不可重复读和幻读区别是什么？

**不可重复读的重点是修改，幻读的重点在于新增或者删除。**

- 例1（同样的条件, 你读取过的数据, 再次读取出来发现值不一样了 ）：事务1中的A先生读取自己的工资为 1000的操作还没完成，事务2中的B先生就修改了A的工资为2000，导致A再读自己的工资时工资变为 2000；这就是不可重复读。

- 例2（同样的条件, 第1次和第2次读出来的记录数不一样 ）：假某工资单表中工资大于3000的有4人，事务1读取了所有工资大于3000的人，共查到4条记录，这时事务2 又插入了一条工资大于3000的记录，事务1再次读取时查到的记 录就变为了5条，这样就导致了幻读。

### 数据库隔离级别

- **未提交读**，事务中发生了修改，即使没有提交，其他事务也是可见的，比如对于一个数A原来50修改为100，但是我还没有提交修改，另一个事务看到这个修改，而这个时候原事务发生了回滚，这时候A还是50，但是另一个事务看到的A是100。**可能会导致脏读、幻读或不可重复读**
- **提交读**，对于一个事务从开始直到提交之前，所做的任何修改是其他事务不可见的，举例就是对于一个数A原来是50，然后提交修改成100，这个时候另一个事务在A提交修改之前，读取的A是50，刚读取完，A就被修改成100，这个时候另一个事务再进行读取发现A就突然变成100了；**可以阻止脏读，但是幻读或不可重复读仍有可能发生**
- **重复读**，就是对一个记录读取多次的记录是相同的，比如对于一个数A读取的话一直是A，前后两次读取的A是一致的；**可以阻止脏读和不可重复读，但幻读仍有可能发生**
- **可串行化读**，在并发情况下，和串行化的读取的结果是一致的，没有什么不同，比如不会发生脏读和幻读；**该级别可以防止脏读、不可重复读以及幻读**

| 隔离级别                  | 脏读 | 不可重复读 | 幻影读 |
| ------------------------- | ---- | ---------- | ------ |
| READ-UNCOMMITTED 未提交读 | √    | √          | √      |
| READ-COMMITTED 提交读     | ×    | √          | √      |
| REPEATABLE-READ 重复读    | ×    | ×          | √      |
| SERIALIZABLE 可串行化读   | ×    | ×          | ×      |

MySQL InnoDB 存储引擎的默认支持的隔离级别是 **REPEATABLE-READ**（可重读）

**这里需要注意的是**：与 SQL 标准不同的地方在于InnoDB 存储引擎在 REPEATABLE-READ（可重读）事务隔离级别 下使用的是**Next-Key Lock 锁**算法，因此可以避免幻读的产生，这与其他数据库系统(如 SQL Server)是不同的。所以 说InnoDB 存储引擎的默认支持的隔离级别是 REPEATABLE-READ（可重读） 已经可以完全保证事务的隔离性要 求，即达到了 SQL标准的SERIALIZABLE(可串行化)隔离级别。

因为隔离级别越低，事务请求的锁越少，所以大部分数据库系统的隔离级别都是READ-COMMITTED(读取提交内 容):，但是你要知道的是InnoDB 存储引擎默认使用 **REPEATABLE-READ（可重读）并不会有任何性能损失**。

InnoDB 存储引擎在分布式事务 的情况下一般会用到SERIALIZABLE(可串行化)隔离级别。

### MySQL中为什么要有事务回滚机制？

而在 MySQL 中，恢复机制是通过回滚日志（undo log）实现的，所有事务进行的修改都会先记录到这个回滚日志中，然后在对数据库中的对应行进行写入。 当事务已经被提交之后，就无法再次回滚了。

**回滚日志作用**：

- 能够在发生错误或者用户执行 ROLLBACK 时提供回滚相关的信息
- 在整个系统发生崩溃、数据库进程直接被杀死后，当用户再次启动数据库进程时，还能够立刻通过查询回滚日志将之前未完成的事务进行回滚，这也就需要回滚日志必须先于数据持久化到磁盘上，是我们需要先写日志后写数据库的主要原因。

### 数据库悲观锁和乐观锁的原理和应用场景分别有什么？

悲观锁，先获取锁，再进行业务操作，一般就是利用类似 SELECT … FOR UPDATE 这样的语句，对数据加锁，避免其他事务意外修改数据。
当数据库执行SELECT … FOR UPDATE时会获取被select中的数据行的行锁，select for update获取的行锁会在当前事务结束时自动释放，因此必须在事务中使用。

乐观锁，先进行业务操作，只在最后实际更新数据时进行检查数据是否被更新过。Java 并发包中的 AtomicFieldUpdater 类似，也是利用 CAS 机制，并不会对数据加锁，而是通过对比数据的时间戳或者版本号，来实现乐观锁需要的版本判断。

### 说一说Drop、Delete与Truncate的共同点和区别

**第一种回答**

Drop、Delete、Truncate都表示删除，但是三者有一些差别：
**Delete**用来删除表的全部或者一部分数据行，执行delete之后，用户需要提交(commmit)或者回滚(rollback)来执行删除或者撤销删除，会触发这个表上所有的delete触发器。
**Truncate**删除表中的所有数据，这个操作不能回滚，也不会触发这个表上的触发器，TRUNCATE比delete更快，占用的空间更小。
**Drop**命令从数据库中删除表，所有的数据行，索引和权限也会被删除，所有的DML触发器也不会被触发，这个命令也不能回滚。

因此，在不再需要一张表的时候，用Drop；在想删除部分数据行时候，用Delete；在保留表而删除所有数据的时候用Truncate。

**具体解析**

1. DELETE语句执行删除的过程是每次从表中删除一行，并且同时将该行的删除操作作为事务记录在日志中保存以便进行进行回滚操作。TRUNCATE TABLE 则一次性地从表中删除所有的数据并不把单独的删除操作记录记入日志保存，删除行是不能恢复的。并且在删除的过程中不会激活与表有关的删除触发器。执行速度快。
2. 表和索引所占空间。当表被TRUNCATE 后，这个表和索引所占用的空间会恢复到初始大小，而DELETE操作不会减少表或索引所占用的空间。drop语句将表所占用的空间全释放掉。
3. 一般而言，drop > truncate > delete
4. 应用范围。TRUNCATE 只能对TABLE；DELETE可以是table和view
5. TRUNCATE 和DELETE只删除数据，而DROP则删除整个表（结构和数据）。
6. truncate与不带where的delete ：只删除数据，而不删除表的结构（定义）drop语句将删除表的结构被依赖的约束（constrain),触发器（trigger)索引（index)；依赖于该表的存储过程/函数将被保留，但其状态会变为：invalid。
7. delete语句为DML（Data Manipulation Language),这个操作会被放到 rollback segment中,事务提交后才生效。如果有相应的 tigger，执行的时候将被触发。
8. truncate、drop是DDL（Data Define Language)，操作立即生效，原数据不放到 rollback segment中，不能回滚
9. 在没有备份情况下，谨慎使用 drop 与 truncate。要删除部分数据行采用delete且注意结合where来约束影响范围。回滚段要足够大。要删除表用drop；若想保留表而将表中数据删除，如果与事务无关，用truncate即可实现。如果和事务有关，或老是想触发trigger，还是用delete。
10. Truncate table 表名 速度快，而且效率高，因为: truncate table 在功能上与不带 WHERE 子句的 DELETE 语句相同：二者均删除表中的全部行。但 TRUNCATE TABLE 比 DELETE 速度快，且使用的系统和事务日志资源少。DELETE 语句每次删除一行，并在事务日志中为所删除的每行记录一项。TRUNCATE TABLE 通过释放存储表数据所用的数据页来删除数据，并且只在事务日志中记录页的释放。
11. TRUNCATE TABLE 删除表中的所有行，但表结构及其列、约束、索引等保持不变。新行标识所用的计数值重置为该列的种子。如果想保留标识计数值，请改用 DELETE。如果要删除表定义及其数据，请使用 DROP TABLE 语句。
12. 对于由 FOREIGN KEY 约束引用的表，不能使用 TRUNCATE TABLE，而应使用不带 WHERE 子句的 DELETE 语句。由于 TRUNCATE TABLE 不记录在日志中，所以它不能激活触发器。

### 为什么使用索引？

- 通过创建唯一性索引，可以保证数据库表中每一行数据的唯一性。
- 可以大大加快数据的检索速度，这也是创建索引的最主要的原因。
- 帮助服务器避免排序和临时表
- 将随机IO变为顺序IO。
- 可以加速表和表之间的连接，特别是在实现数据的参考完整性方面特别有意义。

### 什么时候需要建立数据库索引呢？

在最频繁使用的、用以缩小查询范围的字段，需要排序的字段上建立索引。

**不宜**：
1）对于查询中很少涉及的列或者重复值比较多的列
2）对于一些特殊的数据类型，不宜建立索引，比如文本字段（text）等。

### 覆盖索引是什么？

如果一个索引包含（或者说覆盖）所有需要查询的字段的值，我们就称 之为“覆盖索引”。

我们知道在InnoDB存储引擎中，如果不是主键索引，叶子节点存储的是主键+列值。最终还是要“回表”，也就是要通过主键再查找一次,这样就 会比较慢。覆盖索引就是把要查询出的列和索引是对应的，不做回表操作！

### MySQL中有四种索引类型，可以简单说说吗？

- **FULLTEXT** ：即为全文索引，目前只有MyISAM引擎支持。其可以在CREATE TABLE ，ALTER TABLE ，CREATE INDEX 使用，不过目前只有 CHAR、VARCHAR ，TEXT 列上可以创建全文索引。
- **HASH** ：由于HASH的唯一（几乎100%的唯一）及类似键值对的形式，很适合作为索引。 HASH索引可以一次定位，不需要像树形索引那样逐层查找,因此具有极高的效率。但是，这种高效是有条件的，即只在“=”和“in”条件下高效，对于范围查询、排序及组合索引仍然效率不高。
- **BTREE** ：BTREE索引就是一种将索引值按一定的算法，存入一个树形的数据结构中（二叉树），每次查询都是从树的入口root开始，依次遍历node，获取leaf。这是MySQL里默认和最常用的索引类型。
- **RTREE** ：RTREE在MySQL很少使用，仅支持geometry数据类型，支持该类型的存储引擎只有MyISAM、BDb、InnoDb、NDb、Archive几种。 相对于BTREE，RTREE的优势在于范围查找。

### 文件索引和数据库索引为什么使用B+树？

文件与数据库都是需要较大的存储，也就是说，它们都不可能全部存储在内存中，故需要存储到磁盘上。而所谓索引，则为了数据的快速定位与查找，那么索引的结构组织要尽量减少查找过程中磁盘I/O的存取次数，因此B+树相比B树更为合适。数据库系统巧妙利用了局部性原理与磁盘预读原理，将一个节点的大小设为等于一个页，这样每个节点只需要一次I/O就可以完全载入，而红黑树这种结构，高度明显要深的多，并且由于逻辑上很近的节点(父子)物理上可能很远，无法利用局部性。

最重要的是，B+树还有一个最大的好处：方便扫库。

B树必须用中序遍历的方法按序扫库，而B+树直接从叶子结点挨个扫一遍就完了，B+树支持range-query非常方便，而B树不支持，这是数据库选用B+树的最主要原因。

B+树查找效率更加稳定，B树有可能在中间节点找到数据，稳定性不够。

### Innodb为什么要用自增id作为主键？

如果表使用自增主键，那么每次插入新的记录，记录就会顺序添加到当前索引节点的后续位置，当一页写满，就会自动开辟一个新的页。如果使用非自增主键（如果身份证号或学号等），由于每次插入主键的值近似于随机，因此每次新纪录都要被插到现有索引页得中间某个位置， 频繁的移动、分页操作造成了大量的碎片，得到了不够紧凑的索引结构，后续不得不通过OPTIMIZE TABLE（optimize table）来重建表并优化填充页面。

### 聚集索引与非聚集索引的区别是什么?

非聚集索引和聚集索引的区别在于， 通过聚集索引可以查到需要查找的数据， 而通过非聚集索引可以查到记录对应的主键值 ， 再使用主键的值通过聚集索引查找到需要的数据。

聚集索引和非聚集索引的根本区别是表记录的排列顺序和与索引的排列顺序是否一致。

 聚集索引（Innodb）的叶节点就是数据节点，而非聚集索引(MyisAM)的叶节点仍然是索引节点，只不过其包含一个指向对应数据块的指针。

### MyISAM和InnoDB实现B树索引方式的区别是什么？

- MyISAM，B+Tree叶节点的data域存放的是数据记录的地址，在索引检索的时候，首先按照B+Tree搜索算法搜索索引，如果指定的key存在，则取出其data域的值，然后以data域的值为地址读取相应的数据记录，这被称为“非聚簇索引”

- InnoDB，其数据文件本身就是索引文件，相比MyISAM，索引文件和数据文件是分离的，其表数据文件本身就是按B+Tree组织的一个索引结构，树的节点data域保存了完整的数据记录，这个索引的key是数据表的主键，因此InnoDB表数据文件本身就是主索引，这被称为“聚簇索引”或者聚集索引，而其余的索引都作为辅助索引，辅助索引的data域存储相应记录主键的值而不是地址，这也是和MyISAM不同的地方。

  在根据主索引搜索时，直接找到key所在的节点即可取出数据；在根据辅助索引查找时，则需要先取出主键的值，再走一遍主索引。因此，在设计表的时候，不建议使用过长的字段为主键，也不建议使用非单调的字段作为主键，这样会造成主索引频繁分裂，过长的主索引会导致辅助索引变得非常大。

### 数据库引擎InnoDB与MyISAM的区别

**InnoDB**

- 是 MySQL 默认的事务型存储引擎，只有在需要它不支持的特性时，才考虑使用其它存储引擎。
- 实现了四个标准的隔离级别，默认级别是可重复读(REPEATABLE READ)。在可重复读隔离级别下，通过多版本并发控制(MVCC)+ 间隙锁(Next-Key Locking)防止幻影读。
- 主索引是聚簇索引，在索引中保存了数据，从而避免直接读取磁盘，因此对查询性能有很大的提升。
- 内部做了很多优化，包括从磁盘读取数据时采用的可预测性读、能够加快读操作并且自动创建的自适应哈希索引、能够加速插入操作的插入缓冲区等。
- 支持真正的在线热备份。其它存储引擎不支持在线热备份，要获取一致性视图需要停止对所有表的写入，而在读写混合场景中，停止写入可能也意味着停止读取。

**MyISAM**

- 设计简单，数据以紧密格式存储。对于只读数据，或者表比较小、可以容忍修复操作，则依然可以使用它。
- 提供了大量的特性，包括压缩表、空间数据索引等。
- 不支持事务。
- 不支持行级锁，只能对整张表加锁，读取时会对需要读到的所有表加共享锁，写入时则对表加排它锁。但在表有读取操作的同时，也可以往表中插入新的记录，这被称为并发插入(CONCURRENT INSERT)。

**总结**

- 事务: InnoDB 是事务型的，可以使用 `Commit` 和 `Rollback` 语句。
- 并发: MyISAM 只支持表级锁，而 InnoDB 还支持行级锁。
- 外键: InnoDB 支持外键。
- 备份: InnoDB 支持在线热备份。
- 崩溃恢复: MyISAM 崩溃后发生损坏的概率比 InnoDB 高很多，而且恢复的速度也更慢。
- 其它特性: MyISAM 支持压缩表和空间数据索引。

**适用场景**：
MyISAM适合： 插入不频繁，查询非常频繁，如果执行大量的SELECT，MyISAM是更好的选择， 没有事务。
InnoDB适合： 可靠性要求比较高，或者要求事务； 表更新和查询都相当的频繁， 大量的INSERT或UPDATE

### 听说过视图吗？那游标呢？

视图是虚拟的表，与包含数据的表不一样，视图只包含使用时动态检索数据的查询；不包含任何列或数据。

使用视图可以简化复杂的 sql 操作，隐藏具体的细节，保护数据；视图创建后，可以使用与表相同的方式利用它们。

视图不能被索引，也不能有关联的触发器或默认值，如果视图本身内有order by 则对视图再次order by将被覆盖。

创建视图：`create view xxx as xxxx`

对于某些视图比如未使用联结子查询分组聚集函数Distinct Union等，是可以对其更新的，对视图的更新将对基表进行更新；但是视图主要用于简化检索，保护数据，并不用于更新，而且大部分视图都不可以更新。

游标是对查询出来的结果集作为一个单元来有效的处理。一般不使用游标，但是需要逐条处理数据的时候，游标显得十分重要。

### 创建索引时需要注意什么？

非空字段：应该指定列为NOT NULL，除非你想存储NULL。在 MySQL 中，含有空值的列很难进行查询优化，因为它们使得索引、索引的统计信息以及比较运算更加复杂。你应该用0、一个特殊的值或者一个空串代替空值；

取值离散大的字段：（变量各个取值之间的差异程度）的列放到联合索引的前面，可以通过count()函数查看字段的差异值，返回值越大说明字段的唯一值越多字段的离散程度高；

索引字段越小越好：数据库的数据存储以页为单位一页存储的数据越多一次IO操作获取的数据越大效率越高。

**唯一、不为空、经常被查询的字段 的字段适合建索引**

### MySQL中CHAR和VARCHAR的区别有哪些？

- char的长度是不可变的，用空格填充到指定长度大小，而varchar的长度是可变的。
- char的存取速度还是要比varchar要快得多
- char的存储方式是：对英文字符（ASCII）占用1个字节，对一个汉字占用两个字节。varchar的存储方式是：对每个英文字符占用2个字节，汉字也占用2个字节。

### MySQL 索引使用的注意事项

MySQL 索引通常是被用于提高 WHERE 条件的数据行匹配时的搜索速度，在索引的使用过程中，存在一些使用细节和注意事项。

函数，运算，否定操作符，连接条件，多个单列索引，最左前缀原则，范围查询，不会包含有NULL值的列，like 语句不要在列上使用函数和进行运算

**1）不要在列上使用函数，这将导致索引失效而进行全表扫描。**

```
select * from news where year(publish_time) < 2017
```

为了使用索引，防止执行全表扫描，可以进行改造。

```
select * from news where publish_time < '2017-01-01'
```

还有一个建议，不要在列上进行运算，这也将导致索引失效而进行全表扫描。

```
select * from news where id / 100 = 1
```

为了使用索引，防止执行全表扫描，可以进行改造。

```
select * from news where id = 1 * 100
```

**2）尽量避免使用 != 或 not in或 <> 等否定操作符**
应该尽量避免在 where 子句中使用 != 或 not in 或 <> 操作符，因为这几个操作符都会导致索引失效而进行全表扫描。
应该尽量避免在 where 子句中使用 or 来连接条件，因为这会导致索引失效而进行全表扫描。

```
select * from news where id = 1 or id = 2
```

**3）多个单列索引并不是最佳选择**
MySQL 只能使用一个索引，会从多个索引中选择一个限制最为严格的索引，因此，为多个列创建单列索引，并不能提高 MySQL 的查询性能。
假设，有两个单列索引，分别为 news_year_idx(news_year) 和 news_month_idx(news_month)。现在，有一个场景需要针对资讯的年份和月份进行查询，那么，SQL 语句可以写成：

```
select * from news where news_year = 2017 and news_month = 1
```

事实上，MySQL 只能使用一个单列索引。为了提高性能，可以使用复合索引 news_year_month_idx(news_year, news_month) 保证 news_year 和 news_month 两个列都被索引覆盖。

**4）复合索引的最左前缀原则**
复合索引遵守“最左前缀”原则，即在查询条件中使用了复合索引的第一个字段，索引才会被使用。因此，在复合索引中索引列的顺序至关重要。如果不是按照索引的最左列开始查找，则无法使用索引。
假设，有一个场景只需要针对资讯的月份进行查询，那么，SQL 语句可以写成：

```
select * from news where news_month = 1
```

此时，无法使用 news_year_month_idx(news_year, news_month) 索引，因为遵守“最左前缀”原则，在查询条件中没有使用复合索引的第一个字段，索引是不会被使用的。

**5）覆盖索引的好处**
如果一个索引包含所有需要的查询的字段的值，直接根据索引的查询结果返回数据，而无需读表，能够极大的提高性能。因此，可以定义一个让索引包含的额外的列，即使这个列对于索引而言是无用的。

**6）范围查询对多列查询的影响**
查询中的某个列有范围查询，则其右边所有列都无法使用索引优化查找。
举个例子，假设有一个场景需要查询本周发布的资讯文章，其中的条件是必须是启用状态，且发布时间在这周内。那么，SQL 语句可以写成：

```
select * from news where publish_time >= '2017-01-02' and publish_time <= '2017-01-08' and enable = 1
```

这种情况下，因为范围查询对多列查询的影响，将导致 news_publish_idx(publish_time, enable) 索引中 publish_time 右边所有列都无法使用索引优化查找。换句话说，news_publish_idx(publish_time, enable) 索引等价于 news_publish_idx(publish_time) 。
对于这种情况，我的建议：对于范围查询，务必要注意它带来的副作用，并且尽量少用范围查询，可以通过曲线救国的方式满足业务场景。
例如，上面案例的需求是查询本周发布的资讯文章，因此可以创建一个news_weekth 字段用来存储资讯文章的周信息，使得范围查询变成普通的查询，SQL 可以改写成：

```
select * from news where news_weekth = 1 and enable = 1
```

然而，并不是所有的范围查询都可以进行改造，对于必须使用范围查询但无法改造的情况，我的建议：不必试图用 SQL 来解决所有问题，可以使用其他数据存储技术控制时间轴，例如 Redis 的 SortedSet 有序集合保存时间，或者通过缓存方式缓存查询结果从而提高性能。

**7）索引不会包含有NULL值的列**
只要列中包含有 NULL 值都将不会被包含在索引中，复合索引中只要有一列含有 NULL值，那么这一列对于此复合索引就是无效的。
因此，在数据库设计时，除非有一个很特别的原因使用 NULL 值，不然尽量不要让字段的默认值为 NULL。

**8）隐式转换的影响**
当查询条件左右两侧类型不匹配的时候会发生隐式转换，隐式转换带来的影响就是可能导致索引失效而进行全表扫描。下面的案例中，date_str 是字符串，然而匹配的是整数类型，从而发生隐式转换。

```
select * from news where date_str = 201701
```

因此，要谨记隐式转换的危害，时刻注意通过同类型进行比较。
**9）like 语句的索引失效问题**
like 的方式进行查询，在 like “value%” 可以使用索引，但是对于 like “%value%” 这样的方式，执行全表查询，这在数据量小的表，不存在性能问题，但是对于海量数据，全表扫描是非常可怕的事情。所以，根据业务需求，考虑使用 ElasticSearch 或 Solr 是个不错的方案。

### MySQL中有哪些索引？有什么特点？

- **普通索引**：仅加速查询
- **唯一索引**：加速查询 + 列值唯一（可以有null）
- **主键索引**：加速查询 + 列值唯一（不可以有null）+ 表中只有一个
- **组合索引**：多列值组成一个索引，专门用于组合搜索，其效率大于索引合并
- **全文索引**：对文本的内容进行分词，进行搜索
- **索引合并**：使用多个单列索引组合搜索
- **覆盖索引**：select的数据列只用从索引中就能够取得，不必读取数据行，换句话说查询列要被所建的索引覆盖
- **聚簇索引**：表数据是和主键一起存储的，主键索引的叶结点存储行数据(包含了主键值)，二级索引的叶结点存储行的主键值。使用的是B+树作为索引的存储结构，非叶子节点都是索引关键字，但非叶子节点中的关键字中不存储对应记录的具体内容或内容地址。叶子节点上的数据是主键与具体记录(数据内容)

### 既然索引有那么多优点，为什么不对表总的每一列创建一个索引呢？

- 当对表中的数据进行增加、删除和修改的时候，**索引也要动态的维护**，这样就降低了数据的维护速度。
- **索引需要占物理空间**，除了数据表占数据空间之外，每一个索引还要占一定的物理空间，如果要建立簇索引，那么需要的空间就会更大。
- **创建索引和维护索引要耗费时间**，这种时间随着数据量的增加而增加

### 增加B+树的路数可以降低树的高度，那么无限增加树的路数是不是可以有最优的查找效率？

不可以。因为这样会形成一个有序数组，文件系统和数据库的索引都是存在硬盘上的，并且如果数据量大的话，不一定能一次性加载到内存中。有序数组没法一次性加载进内存，这时候B+树的多路存储威力就出来了，可以每次加载B+树的一个结点，然后一步步往下找。


### 为什么MySQL索引适用用B+树而不用hash表和B树？

- 利用Hash需要把数据全部**加载到内存中**，如果数据量大，是一件很**消耗内存**的事，而采用B+树，是基于**按照节点分段加载，由此减少内存消耗**。
- 和业务场景有段，**对于唯一查找**（查找一个值），Hash确实更快，**但数据库中经常查询多条数据**，这时候由于B+数据的有序性，与叶子节点又有链表相连，他的查询效率会比Hash快的多。
- b+树的**非叶子节点不保存数据**，**只保存子树的临界值**（最大或者最小），所以同样大小的节点，**b+树相对于b树能够有更多的分支，使得这棵树更加矮胖，查询时做的IO操作次数也更少**。

### 说一下数据库表锁和行锁吧

**表锁**

不会出现死锁，发生锁冲突几率高，并发低。

MyISAM在执行查询语句（select）前，会自动给涉及的所有表加读锁，在执行增删改操作前，会自动给涉及的表加写锁。

MySQL的表级锁有两种模式：表共享读锁和表独占写锁。

读锁会阻塞写，写锁会阻塞读和写

- 对MyISAM表的读操作，不会阻塞其它进程对同一表的读请求，但会阻塞对同一表的写请求。只有当读锁释放后，才会执行其它进程的写操作。
- 对MyISAM表的写操作，会阻塞其它进程对同一表的读和写操作，只有当写锁释放后，才会执行其它进程的读写操作。

MyISAM不适合做写为主表的引擎，因为写锁后，其它线程不能做任何操作，大量的更新会使查询很难得到锁，从而造成永远阻塞。

**行锁**

会出现死锁，发生锁冲突几率低，并发高。

在MySQL的InnoDB引擎支持行锁，与Oracle不同，MySQL的行锁是通过索引加载的，也就是说，行锁是加在索引响应的行上的，要是对应的SQL语句没有走索引，则会全表扫描，行锁则无法实现，取而代之的是表锁，此时其它事务无法对当前表进行更新或插入操作。

**行锁的实现需要注意：**

- 行锁必须有索引才能实现，否则会自动锁全表，那么就不是行锁了。
- 两个事务不能锁同一个索引。
- insert，delete，update在事务中都会自动默认加上排它锁。

**行锁的适用场景：**

A用户消费，service层先查询该用户的账户余额，若余额足够，则进行后续的扣款操作；这种情况查询的时候应该对该记录进行加锁。

否则，B用户在A用户查询后消费前先一步将A用户账号上的钱转走，而此时A用户已经进行了用户余额是否足够的判断，则可能会出现余额已经不足但却扣款成功的情况。

为了避免此情况，需要在A用户操作该记录的时候进行for update加锁

### SQL语法中内连接、自连接、外连接（左、右、全）、交叉连接的区别分别是什么？

内连接：只有两个元素表相匹配的才能在结果集中显示。

左外连接: 左边为驱动表，驱动表的数据全部显示，匹配表的不匹配的不会显示。

右外连接: 右边为驱动表，驱动表的数据全部显示，匹配表的不匹配的不会显示。

全外连接：连接的表中不匹配的数据全部会显示出来。

交叉连接： 笛卡尔效应，显示的结果是链接表数的乘积。

### 你知道哪些数据库结构优化的手段？

- **范式优化**： 比如消除冗余（节省空间。。）
- **反范式优化**：比如适当加冗余等（减少join）
- **限定数据的范围**： 务必禁止不带任何限制数据范围条件的查询语句。比如：我们当用户在查询订单历史的时候，我们可以控制在一个月的范围内。
- **读/写分离**： 经典的数据库拆分方案，主库负责写，从库负责读；
- **拆分表**：分区将数据在物理上分隔开，不同分区的数据可以制定保存在处于不同磁盘上的数据文件里。这样，当对这个表进行查询时，只需要在表分区中进行扫描，而不必进行全表扫描，明显缩短了查询时间，另外处于不同磁盘的分区也将对这个表的数据传输分散在不同的磁盘I/O，一个精心设置的分区可以将数据传输对磁盘I/O竞争均匀地分散开。对数据量大的时时表可采取此方法。可按月自动建表分区。

### 数据库为什么要进行分库和分表呢？都放在一个库或者一张表中不可以吗？

分库与分表的目的在于，减小数据库的单库单表负担，提高查询性能，缩短查询时间。

**通过分表**，可以减少数据库的单表负担，将压力分散到不同的表上，同时因为不同的表上的数据量少了，起到提高查询性能，缩短查询时间的作用，此外，可以很大的缓解表锁的问题。

**分表策略可以归纳为垂直拆分和水平拆分**：

**水平分表**：取模分表就属于随机分表，而时间维度分表则属于连续分表。

如何设计好垂直拆分，我的建议：将不常用的字段单独拆分到另外一张扩展表. 将大文本的字段单独拆分到另外一张扩展表, 将不经常修改的字段放在同一张表中，将经常改变的字段放在另一张表中。
对于海量用户场景，可以考虑取模分表，数据相对比较均匀，不容易出现热点和并发访问的瓶颈。

**库内分表**，仅仅是解决了单表数据过大的问题，但并没有把单表的数据分散到不同的物理机上，因此并不能减轻 MySQL 服务器的压力，仍然存在同一个物理机上的资源竞争和瓶颈，包括 CPU、内存、磁盘 IO、网络带宽等。

**分库与分表带来的分布式困境与应对之策**

数据迁移与扩容问题----一般做法是通过程序先读出数据，然后按照指定的分表策略再将数据写入到各个分表中。

分页与排序问题----需要在不同的分表中将数据进行排序并返回，并将不同分表返回的结果集进行汇总和再次排序，最后再返回给用户。

### MySQL优化了解吗？说一下从哪些方面可以做到性能优化？

- 为搜索字段创建索引
- 避免使用 Select *，列出需要查询的字段
- 垂直分割分表
- 选择正确的存储引擎

### 一道场景题：假如你所在的公司选择MySQL数据库作数据存储，一天五万条以上的增量，预计运维三年，你有哪些优化手段？

- 设计良好的数据库结构，允许部分数据冗余，尽量避免join查询，提高效率。
- 选择合适的表字段数据类型和存储引擎，适当的添加索引。
- MySQL库主从读写分离。
- 找规律分表，减少单表中的数据量提高查询速度。
- 添加缓存机制，比如Memcached，Apc等。
- 不经常改动的页面，生成静态页面。
- 书写高效率的SQL。比如 SELECT * FROM TABEL 改为 SELECT field_1, field_2, field_3 FROM TABLE。

### 数据库优化中有一个比较常用的手段就是把数据表进行拆分，关于拆分数据表你了解哪些？

拆分其实又分**垂直拆分**和**水平拆分**

案例： 简单购物系统暂设涉及如下表：

1.产品表（数据量10w，稳定）

2.订单表（数据量200w，且有增长趋势）

3.用户表 （数据量100w，且有增长趋势）

以 MySQL 为例讲述下水平拆分和垂直拆分，MySQL能容忍的数量级在百万静态数据可以到千万

**垂直拆分**

解决问题：表与表之间的io竞争

不解决问题：单表中数据量增长出现的压力

方案： 把产品表和用户表放到一个server上 订单表单独放到一个server上

**水平拆分**

解决问题：单表中数据量增长出现的压力

不解决问题：表与表之间的io争夺

方案：**用户表** 通过性别拆分为男用户表和女用户表，**订单表** 通过已完成和完成中拆分为已完成订单和未完成订单，**产品表** 未完成订单放一个server上，已完成订单表盒男用户表放一个server上，女用户表放一个server上(女的爱购物 哈哈)。

### 数据库高并发是我们经常会遇到的，你有什么好的解决方案吗？

- 在web服务框架中加入缓存。在服务器与数据库层之间加入缓存层，将高频访问的数据存入缓存中，减少数据库的读取负担。
- 增加数据库索引，进而提高查询速度。（不过索引太多会导致速度变慢，并且数据库的写入会导致索引的更新，也会导致速度变慢）
- 主从读写分离，让主服务器负责写，从服务器负责读。
- 将数据库进行拆分，使得数据库的表尽可能小，提高查询的速度。
- 使用分布式架构，分散计算压力。

***

## Redis

***


### 听说过Redis吗？它是什么？

Redis是一个**数据库**，不过与传统数据库不同的是Redis的数据库是存在**内存**中，所以**读写速度非常快**，因此 Redis被广泛应用于**缓存**方向。

除此之外，Redis也经常用来做分布式锁，Redis提供了多种数据类型来支持不同的业务场景。除此之外，Redis 支持事务持久化、LUA脚本、LRU驱动事件、多种集群方案。


### Redis的五种数据结构整理

#### 简单动态字符串(Simple Dynamic String，SDS)

Redis没有直接使用C语言传统的字符串，而是自己构建了一种名为简单动态字符串（Simple dynamic string，SDS）的抽象类型，并将SDS用作Redis的默认字符串表示。

其实SDS等同于C语言中的char * ，但它可以存储任意二进制数据，不能像C语言字符串那样以字符’\0’来标识字符串的结 束，因此它必然有个长度字段。

**定义**

```c
struct sdshdr {
  // 记录buf数组中已使用字节的数量
  // 等于sds所保存字符串的长度
  int len;

  // 记录buf数组中未使用字节的数量
  int free;

  // 字节数组，用于保存字符串
  char buf[];
}
```

**优点**

- 获取字符串长度的复杂度为O(1)。
- 杜绝缓冲区溢出。
- 减少修改字符串长度时所需要的内存重分配次数。
- 二进制安全。
- 兼容部分C字符串函数。

它具有很常规的 set/get 操作，value 可以是String也可以是数字，一般做一些复杂的计数功能的缓存。

#### 链表

当有一个列表键包含了数量比较多的元素，又或者列表中包含的元素都是比较长的额字符串时，Redis就会使用链表作为列表建的底层实现。

**节点底层结构**

```c
typedef struct listNode {
  // 前置节点
  struct listNode *prev;
  // 后置节点
  struct listNode *next;
  // 节点的值
  void *value;
} listNode;
```

**list底层结构**

```c
typedef struct list {
  // 表头节点
  listNode *head;
  // 表尾节点
  listNode *tail;
  // 链表所包含的节点数量
  unsigned long len;
  // 节点值复制函数
  void *(*dup)(void *ptr);
  // 节点值释放函数
  void (*free)(void *ptr);
  // 节点值对比函数
  int（ *match）(void *ptr, void *key);
} list;
```

**特性**

- 链表被广泛用于实现Redis的各种功能，比如列表建、发布与订阅、慢查询、监视器等。
- 每个链表节点由一个listNode结构来表示，每个节点都有一个指向前置节点和后置节点的指针，所以Redis的链表实现是双端链表。
- 每个链表使用一个list结构表示，这个结构带有表头节点指针、表尾节点指针，以及链表长度等信息。
- 因为链表表头的前置节点和表尾节点的后置节点都指向NULL，所以Redis的链表实现是无环链表。
- 通过为链表设置不同的类型特定函数，Redis的链表可以用于保存各种不同类型的值。

#### 字典

字典的底层是哈希表，类似 C++中的 map ，也就是键值对。

**哈希表**

```c
typedef struct dictht {
  // 哈希表数组
  dictEntry **table;
  // 哈希表大小
  unsigned long size;
  // 哈希表大小掩码，用于计算索引值
  // 总是等于size-1
  unsigned long sizemark;
  // 该哈希表已有节点的数量
  unsigned long used;
} dichht;
```

**哈希算法**

当字典被用作数据库的底层实现，或者哈希键的底层实现时，Redis使用MurmurHash算法。这种算法的优点在于即使输入的键是规律的，算法仍能给出一个个很好的随机分布性，并且算法的计算速度非常快。

**哈希冲突的解决方式**

Redis的哈希表使用链地址法来解决键冲突，每个哈希表节点都有一个next指针，多个哈希表节点可以用这个单向链表连接起来，这就解决了键冲突的问题。

**特性**

1. 字典被广泛用于实现Redis的各种功能，其中包括数据库和哈希键。
2. Redis中的字典使用哈希表作为底层结构实现，每个字典带有两个哈希表，一个平时使用，另一个仅在进行rehash时使用。
3. Redis使用MurmurHash2算法来计算键的哈希值。
4. 哈希表使用链地址法来解决键冲突。

#### 跳跃表

先看这样一张图：

![image-20211007094555887](https://gitee.com/duycc/picgo/raw/master/20211007094557.png)

如上图，我们要查找一个元素，就需要从头节点开始遍历，直到找到对应的节点或者是第一个大于要查找的元素的节点（没找到）。时间复杂度为O(N)。

这个查找效率是比较低的，但如果我们把列表的某些节点拔高一层，如下图，例如把每两个节点中有一个节点变成两层。那么第二层的节点只有第一层的一半，查找效率也就会提高。

![image-20211007094637713](https://gitee.com/duycc/picgo/raw/master/20211007094638.png)

查找的步骤是从头节点的顶层开始，查到第一个大于指定元素的节点时，退回上一节点，在下一层继续查找。

比如我们要查找16：

1. 从头节点的最顶层开始，先到节点7。
2. 7的下一个节点是39，大于16，因此我们退回到7
3. 从7开始，在下一层继续查找，就可以找到16。

这个例子中遍历的节点不比一维列表少，但是当节点更多，查找的数字更大时，这种做法的优势就体现出来了。还是上面的例子，如果我们要**查找的是39**，那么只需要访问两个节点（7、39）就可以找到了。这比一维列表要减少一半的数量。

为了避免插入操作的时间复杂度是O(N)，skiplist每层的数量不会严格按照2:1的比例，而是对每个要插入的元素随机一个层数。

随机层数的计算过程如下：

1. 每个节点都有第一层
2. 那么它有第二层的概率是p，有第三层的概率是p*p
3. 不能超过最大层数

**zskiplistNode**

```c
typedef struct zskiplistNode {
  // 后退指针
  struct zskiplistNode *backward;
  // 分值 权重
  double score;
  // 成员对象
  robj *obj;
  // 层
  struct zskiplistLevel {
    // 前进指针
    struct zskiplistNode *forward;
    // 跨度
    unsigned int span;
  } leval[];
} zskiplistNode;
```

一般来说，层的数量越多，访问其他节点的速度越快。

**zskipList**

```c
typedef struct zskiplist {
  // 表头节点和表尾节点
  struct zskiplistNode *header, *tail;
  // 表中节点的数量
  unsigned long length;
  // 表中层数最大的节点的层数
  int leval;
} zskiplist;
```

特性

- 跳跃表是有序集合的底层实现之一
- Redis的跳跃表实现由zskiplist和zskiplistNode两个结构组成，其中zskiplist用于保存跳跃表信息（比如表头节点、表尾节点、长度），而zskiplistNode则用于表示跳跃表节点
- 每个跳跃表节点的层高都是1至32之间的随机数
- 在同一个跳跃表中，多个节点可以包含相同的分值，但每个节点的成员对象必须是唯一的。
- 跳跃表中的节点按照分值大小进行排序，当分值相同时，节点按照成员对象的大小进行排序。
- 跳表是一种实现起来很简单，单层多指针的链表，它查找效率很高，堪比优化过的二叉平衡树，且比平衡树的实现。

#### 压缩列表

压缩列表(ziplist)是列表键和哈希键的底层实现之一。当一个列表键只包含少量列表项，并且每个列表项要么就是小整数值，要么就是长度比较短的字符串，那么Redis就会使用压缩列表来做列表键的底层实现。

**特性**

看他的名字就能看出来，是为了节省内存造的列表结构。


### Redis常见数据结构以及使用场景分别是什么？

**String**

String数据结构是简单的key-value类型，value其实不仅可以是String，也可以是数字。 常规key-value缓存应用； 常规计数：微博数，粉丝数等。

**Hash**

Hash 是一个 string 类型的 ﬁeld 和 value 的映射表，hash 特别适合用于存储对象，后续操作的时候，你可以直接仅修改这个对象中的某个字段的值。 比如我们可以Hash数据结构来存储用户信息，商品信息等。

**List**

list 就是链表，Redis list 的应用场景非常多，也是Redis最重要的数据结构之一，比如微博的关注列表，粉丝列表， 消息列表等功能都可以用Redis的 list 结构来实现。

Redis list 的实现为一个双向链表，即可以支持反向查找和遍历，更方便操作，不过带来了部分额外的内存开销。

另外可以通过 lrange 命令，就是从某个元素开始读取多少个元素，可以基于 list 实现分页查询，这个很棒的一个功 能，基于 Redis 实现简单的高性能分页，可以做类似微博那种下拉不断分页的东西（一页一页的往下走），性能高。

**Set**

set 对外提供的功能与list类似是一个列表的功能，特殊之处在于 set 是可以自动排重的。

当你需要存储一个列表数据，又不希望出现重复数据时，set是一个很好的选择，并且set提供了判断某个成员是否在 一个set集合内的重要接口，这个也是list所不能提供的。可以基于 set 轻易实现交集、并集、差集的操作。

比如：在微博应用中，可以将一个用户所有的关注人存在一个集合中，将其所有粉丝存在一个集合。Redis可以非常 方便的实现如共同关注、共同粉丝、共同喜好等功能。这个过程也就是求交集的过程，具体命令如下：`sinterstore key1 key2 key3`将交集存在key1内。

**Sorted Set**

和set相比，sorted set增加了一个权重参数score，使得集合中的元素能够按score进行有序排列。

举例： 在直播系统中，实时排行信息包含直播间在线用户列表，各种礼物排行榜，弹幕消息（可以理解为按消息维 度的消息排行榜）等信息，适合使用 Redis 中的 SortedSet 结构进行存储。


### 有MySQL不就够用了吗？为什么要用Redis这种新的数据库？

主要是因为 Redis 具备高性能和高并发两种特性。

- **高性能**：假如用户第一次访问数据库中的某些数据。这个过程会比较慢，因为是从硬盘上读取的。将该用户访问的数据存在缓存中，这样下一次再访问这些数据的时候就可以直接从缓存中获取了。操作缓存就是直接操作内存，所以速度相当快。如果数据库中的对应数据改变的之后，同步改变缓存中相应的数据即可！
- **高并发**：直接操作缓存能够承受的请求是远远大于直接访问数据库的，所以我们可以考虑把数据库中的部分数据转移到缓存中去，这样用户的一部分请求会直接到缓存这里而不用经过数据库。


### C++中的Map也是一种缓存型数据结构，为什么不用Map，而选择Redis做缓存？

严格意义上来说缓存分为**本地缓存**和**分布式缓存**。

那以 C++ 语言为例，我们可以使用 STL 下自带的容器 map 来实现缓存，但只能实现本地缓存，它最主要的特点是轻量以及快速，但是其生命周期随着程序的销毁而结束，并且在多实例的情况下，每个实例都需要各自保存一份缓存，缓存不具有一致性。

使用 Redis 或 Memcached 之类的称为分布式缓存，在多实例的情况下，各实例共享一份缓存数据，缓存具有一致性。这是Redis或者Memcached的优点所在，但它也有缺点，那就是需要保持 Redis 或 Memcached服务的高可用，整个程序架构上较为复杂。


### 使用Redis的好处有哪些？

- 访问速度快，因为数据存在内存中，类似于Java中的HashMap或者C++中的哈希表（如unordered_map/unordered_set），这两者的优势就是查找和操作的时间复杂度都是O(1)

- 数据类型丰富，支持String，list，set，sorted set，hash这五种数据结构

- 支持事务，Redis中的操作都是原子性，换句话说就是对数据的更改要么全部执行，要么全部不执行，这就是原子性的定义

- 特性丰富：Redis可用于缓存，消息，按key设置过期时间，过期后将会自动删除。


### Memcached与Redis的区别都有哪些？

**存储方式**：

- Memecache把数据全部存在内存之中，断电后会挂掉，没有持久化功能，数据不能超过内存大小。
- Redis有部份存在硬盘上，这样能保证数据的持久性。

**数据支持类型**：

- Memcache对数据类型支持相对简单,只有String这一种类型
- Redis有复杂的数据类型。Redis不仅仅支持简单的k/v类型的数据，同时还提供 list，set，zset，hash等数据结构的存储。

**使用底层模型不同**：

- 它们底层实现方式以及与客户端之间通信的应用协议不一样。
- Redis直接自己构建了VM 机制 ，因为一般的系统调用系统函数的话，会浪费一定的时间去移动和请求。

**集群模式**：Memcached没有原生的集群模式，需要依靠客户端来实现往集群中分片写入数据；但是 Redis 目前是原生支持 cluster 模式的.

* Memcached是多线程，非阻塞IO复用的网络模型；Redis使用单线程的多路 IO 复用模型。
* Value 值大小不同：Redis 最大可以达到 512MB；Memcached 只有 1MB。


### 缓存中常说的热点数据和冷数据是什么？

其实就是名字上的意思，热数据就是访问次数较多的数据，冷数据就是访问很少或者从不访问的数据。

需要注意的是只有热点数据，缓存才有价值，对于冷数据而言，大部分数据可能还没有再次访问到就已经被挤出内存，不仅占用内存，而且价值不大。

**数据更新前至少读取两次**，缓存才有意义。这个是最基本的策略，如果缓存还没有起作用就失效了，那就没有太大价值了。

### Redis 为什么是单线程的而不采用多线程方案？

这主要是基于一种客观原因来考虑的。因为Redis是基于内存的操作，CPU不是Redis的瓶颈，Redis的瓶颈最有可能是机器内存的大小或者网络带宽。既然单线程容易实现，而且CPU不会成为瓶颈，那就顺理成章地采用单线程的方案了（毕竟采用多线程会有很多麻烦！）


### 单线程的Redis为什么这么快？

- Redis的全部操作都是纯内存的操作；
- Redis采用单线程，有效避免了频繁的上下文切换；
- 采用了非阻塞I/O多路复用机制。

### 了解Redis的线程模型吗？可以大致说说吗？

如果你打开看过 Redis 的源码就会发现Redis 内部使用文件事件处理器 file event handler，这个文件事件处理器是单线程的，所以 Redis 才叫做单线程的模型。它采用 IO 多路复用机制同时监听多个 socket，根据 socket 上的事件来选择对应的事件处理器进行处理。

![image-20211007101108341](https://gitee.com/duycc/picgo/raw/master/20211007101109.png)

文件事件处理器的结构包含 4 个部分：

- 多个 socket
- IO多路复用程序
- 文件事件分派器
- 事件处理器（连接应答处理器、命令请求处理器、命令回复处理器）

使用 I/O 多路复用程序来同时监听多个套接字， 并根据套接字目前执行的任务来为套接字关联不同的事件处理器。当被监听的套接字准备好执行连接应答（accept）、读取（read）、写入（write）、关闭（close）等操作时， 与操作相对应的文件事件就会产生， 这时文件事件处理器就会调用套接字之前关联好的事件处理器来处理这些事件。

多个 socket 可能会并发产生不同的操作，每个操作对应不同的文件事件，但是 IO 多路复用程序会监听多个 socket，会将 socket 产生的事件放入队列中排队，事件分派器每次从队列中取出一个事件，把该事件交给对应的事件处理器进行处理。

一句话总结就是：“I/O 多路复用程序负责监听多个套接字， 并向文件事件分派器传送那些产生了事件的套接字。”


### 定期和惰性一定能保证删除数据吗？如果不能，Redis会有什么应对措施？

Redis中有个设置时间过期的功能，即对存储在 Redis 数据库中的值可以设置一个过期时间。

作为一个缓存数据库， 这是非常实用的，比如一些 token 或者登录信息，尤其是短信验证码都是有时间限制的，按照传统的数据库处理方式，一般都是自己判断过期，这样无疑会严重影响项目性能。

我们 set key 的时候，都可以给一个 expire time，就是过期时间，通过过期时间我们可以指定这个 key 可以存活的时间，主要可采用**定期删除和惰性删除**两种方案。

并不能保证一定删除，Redsi有一个Redis 内存淘汰机制来确保数据一定会被删除。

**首先介绍一下定期删除和惰性删除的工作流程**：

定期删除，Redis默认每个100ms检查，是否有过期的key,有过期key则删除。需要说明的是，Redis不是每个100ms将所有的key检查一次，而是随机抽取进行检查(如果每隔100ms,全部key进行检查，Redis岂不是卡死)。因此，如果只采用定期删除策略，会导致很多key到时间没有删除。于是，惰性删除派上用场。也就是说在你获取某个key的时候，Redis会检查一下，这个key如果设置了过期时间那么是否过期了？如果过期了此时就会删除。

采用定期删除+惰性删除就没其他问题了么?不是的，如果定期删除没删除key。然后你也没即时去请求key，也就是说惰性删除也没生效。这样，Redis内存会越来越高。那么就应该采用内存淘汰机制。

在Redis.conf中有一行配置:maxmemory-policy volatile-lru

该配置就是配内存淘汰策略的，主要有以下六种方案：

**volatile-lru**：从已设置过期时间的数据集（server.db[i].expires）中挑选最近最少使用的数据淘汰
**volatile-ttl**：从已设置过期时间的数据集（server.db[i].expires）中挑选将要过期的数据淘汰
**volatile-random**：从已设置过期时间的数据集（server.db[i].expires）中任意选择数据淘汰
**allkeys-lru**：从数据集（server.db[i].dict）中挑选最近最少使用的数据淘汰
**allkeys-random**：从数据集（server.db[i].dict）中任意选择数据淘汰
**no-enviction**（驱逐）：禁止驱逐数据，新写入操作会报错
ps：如果没有设置 expire 的key, 不满足先决条件(prerequisites); 那么 volatile-lru, volatile-random 和 volatile-ttl 策略的行为, 和 noeviction(不删除) 基本上一致。

### 缓存雪崩、缓存穿透、缓存预热、缓存更新、缓存击穿、缓存降级

#### 缓存雪崩

缓存雪崩指的是缓存同一时间大面积的失效，所以，后面的请求都会落到数据库上，造成数据库短时间内承受大量请求而崩掉。

我们可以简单的理解为：由于原有缓存失效，新缓存未到期间(例如：我们设置缓存时采用了相同的过期时间，在同一时刻出现大面积的缓存过期)，所有原本应该访问缓存的请求都去查询数据库了，而对数据库CPU和内存造成巨大压力，严重的会造成数据库宕机，从而形成一系列连锁反应，造成整个系统崩溃。

**解决办法**

- 事前：尽量保证整个 Redis 集群的高可用性，发现机器宕机尽快补上，选择合适的内存淘汰策略。
- 事中：本地ehcache缓存 + hystrix限流&降级，避免MySQL崩掉， 通过加锁或者队列来控制读数据库写缓存的线程数量。比如对某个key只允许一个线程查询数据和写缓存，其他线程等待。 
- 事后：利用 Redis 持久化机制保存的数据尽快恢复缓存

#### 缓存穿透

一般是黑客故意去请求缓存中不存在的数据，导致所有的请求都落到数据库上，造成数据库短时间内承受大量 请求而崩掉。

缓存穿透是指查询一个一定不存在的数据，由于缓存不命中，接着查询数据库也无法查询出结果，因此也不会写入到缓存中，这将会导致每个查询都会去请求数据库，造成缓存穿透。

**解决办法**

1、**布隆过滤器**

这是最常见的一种解决方法了，它是将所有可能存在的数据哈希到一个足够大的**bitmap**中，一个一定不存在的数据会被这个bitmap拦截掉，从而避免了对底层存储系统的查询压力。

 对所有可能查询的参数以hash形式存储，在控制层先进行校验，不符合则丢弃，从而避免了对底层存储系统的查询压力； 

这里稍微科普一下布隆过滤器。

> 布隆过滤器是引入了k(k>1)k(k>1)个相互独立的哈希函数，保证在给定的空间、误判率下，完成元素判重的过程。
> 它的优点是空间效率和查询时间都远远超过一般的算法，缺点是有一定的误识别率和删除困难。
>
> 该算法的**核心思想**就是利用多个不同的Hash函数来解决“冲突”。Hash存在一个冲突（碰撞）的问题，用同一个Hash得到的两个URL的值有可能相同。为了减少冲突，我们可以多引入几个Hash，如果通过其中的一个Hash值我们得出某元素不在集合中，那么该元素肯定不在集合中。只有在所有的Hash函数告诉我们该元素在集合中时，才能确定该元素存在于集合中。这便是布隆过滤器的基本思想，一般用于在大数据量的集合中判定某元素是否存在。

2、**缓存空对象**

当存储层不命中后，即使返回的空对象也将其缓存起来，同时会设置一个过期时间，之后再访问这个数据将会从缓存中获取，保护了后端数据源；如果一个**查询返回的数据为空**（不管是数据不存在，还是系统故障），我们仍然把这个空结果进行缓存，但它的**过期时间会很短**，最长不超过五分钟。

但是这种方法会存在两个问题：

1、如果空值能够被缓存起来，这就意味着缓存需要更多的空间存储更多的键，因为这当中可能会有很多的空值的键；

2、即使对空值设置了过期时间，还是会存在缓存层和存储层的数据会有一段时间窗口的不一致，这对于需要保持一致性的业务会有影响。

我们可以从适用场景和维护成本两方面对这两汇总方法进行一个**简单比较**：

**适用场景**：缓存空对象适用于，数据命中不高，数据频繁变化且实时性较高 ；而布隆过滤器适用数据命中不高，数据相对固定即实时性较低

**维护成本**：缓存空对象的方法适合1、代码维护简单 2、需要较多的缓存空间 3、数据会出现不一致的现象；布隆过滤器适合 1、代码维护较复杂 2、缓存空间要少一些

#### 缓存预热

缓存预热是指系统上线后，将相关的缓存数据直接加载到缓存系统。这样就可以避免在用户请求的时候，先查询数据库，然后再将数据缓存的问题。用户会直接查询事先被预热的缓存数据！

**解决思路**

- 直接写个缓存刷新页面，上线时手工操作下；
- 数据量不大，可以在项目启动的时候自动进行加载；
- 定时刷新缓存；

#### 缓存击穿

缓存击穿，是指一个key非常热点，在不停的扛着大并发，大并发集中对这一个点进行访问，当这个key在失效的瞬间，持续的大并发就穿破缓存，直接请求数据库，就像在一个屏障上凿开了一个洞。

比如常见的电商项目中，某些货物成为“爆款”了，可以对一些主打商品的缓存直接设置为永不过期。即便某些商品自己发酵成了爆款，也是直接设为永不过期就好了。mutex key互斥锁基本上是用不上的，有个词叫做大道至简。

#### 缓存降级

当访问量剧增、服务出现问题（如响应时间慢或不响应）或非核心服务影响到核心流程的性能时，仍然需要保证服务还是可用的，即使是有损服务。系统可以根据一些关键数据进行自动降级，也可以配置开关实现人工降级。
降级的最终目的是保证核心服务可用，即使是有损的。而且有些服务是无法降级的（如加入购物车、结算）。

以参考日志级别设置预案：

（1）一般：比如有些服务偶尔因为网络抖动或者服务正在上线而超时，可以自动降级；
（2）警告：有些服务在一段时间内成功率有波动（如在95~100%之间），可以自动降级或人工降级，并发送告警；
（3）错误：比如可用率低于90%，或者数据库连接池被打爆了，或者访问量突然猛增到系统能承受的最大阀值，此时可以根据情况自动降级或者人工降级；
（4）严重错误：比如因为特殊原因数据错误了，此时需要紧急人工降级。

服务降级的目的，是为了防止Redis服务故障，导致数据库跟着一起发生雪崩问题。因此，对于不重要的缓存数据，可以采取服务降级策略，例如一个比较常见的做法就是，Redis出现问题，不去数据库查询，而是直接返回默认值给用户。


### 假如MySQL有1000万数据，采用Redis作为中间缓存，取其中的10万，如何保证Redis中的数据都是热点数据？

可以使用Redis的**数据淘汰策略**，Redis 内存数据集大小上升到一定大小的时候，就会施行这种策略。具体说来，主要有 6种内存淘汰策略：

- voltile-lru：从已设置过期时间的数据集（server.db[i].expires）中挑选最近最少使用的数据淘汰

- volatile-ttl：从已设置过期时间的数据集（server.db[i].expires）中挑选将要过期的数据淘汰

- volatile-random：从已设置过期时间的数据集（server.db[i].expires）中任意选择数据淘汰

- allkeys-lru：从数据集（server.db[i].dict）中挑选最近最少使用的数据淘汰

- allkeys-random：从数据集（server.db[i].dict）中任意选择数据淘汰

- no-enviction（驱逐）：禁止驱逐数据


### Redis持久化机制可以说一说吗？

Redis是一个支持持久化的内存数据库，通过持久化机制把内存中的数据同步到硬盘文件来保证数据持久化。当Redis重启后通过把硬盘文件重新加载到内存，就能达到恢复数据的目的。

很多时候我们需要持久化数据也就是将内存中的数据写入到硬盘里面，大部分原因是为了之后**重用数据**（比如重启机 器、机器故障之后回复数据），或者是为了防止系统故障而将**数据备份**到一个远程位置。

实现：单独创建fork()一个子进程，将当前父进程的数据库数据复制到子进程的内存中，然后由子进程写入到临时文件中，持久化的过程结束了，再用这个临时文件替换上次的快照文件，然后子进程退出，内存释放。

**以下有两种持久化机制**

**快照（snapshotting）持久化（RDB持久化）**

Redis可以通过创建快照来获得存储在内存里面的数据在某个时间点上的副本。Redis创建快照之后，可以对快照进行备份，可以将快照复制到其他服务器从而创建具有相同数据的服务器副本（Redis主从结构，主要用来提高Redis性能），还可以将快照留在原地以便重启服务器的时候使用。

快照持久化是Redis默认采用的持久化方式，在Redis.conf配置文件中默认有此下配置：

```shell
save 900 1 # 在900秒(15分钟)之后，如果至少有1个key发生变化，Redis就会自动触发BGSAVE命令
创建快照。

save 300 10 # 在300秒(5分钟)之后，如果至少有10个key发生变化，Redis就会自动触发BGSAVE命令创建快照。

save 60 10000 # 在60秒(1分钟)之后，如果至少有10000个key发生变化，Redis就会自动触发BGSAVE命令创建快照。
```

**AOF（append-only file）持久化**

与快照持久化相比，AOF**持久化的实时性更好**，因此已成为主流的持久化方案。默认情况下Redis没有开启 AOF（append only ﬁle）方式的持久化，可以通过appendonly参数开启：`appendonly yes`

开启AOF持久化后每执行一条会更改Redis中的数据的命令，Redis就会将该命令写入硬盘中的AOF文件。AOF文件的 保存位置和RDB文件的位置相同，都是通过dir参数设置的，默认的文件名是appendonly.aof。

在Redis的配置文件中存在三种不同的 AOF 持久化方式，它们分别是：

```shell
appendfsync always # 每次有数据修改发生时都会写入AOF文件,这样会严重降低Redis的速度
appendfsync everysec  # 每秒钟同步一次，显示地将多个写命令同步到硬盘
appendfsync no  # 让操作系统决定何时进行同步
```

为了兼顾数据和写入性能，用户可以考虑 appendfsync everysec选项 ，让Redis每秒同步一次AOF文件，Redis性能 几乎没受到任何影响。而且这样即使出现系统崩溃，用户最多只会丢失一秒之内产生的数据。当硬盘忙于执行写入操作的时候，Redis还会优雅的放慢自己的速度以便适应硬盘的最大写入速度。

**Redis 4.0 对于持久化机制的优化**

Redis 4.0 开始支持 RDB 和 AOF 的混合持久化（默认关闭，可以通过配置项 aof-use-rdb-preamble 开启）。

如果把混合持久化打开，AOF 重写的时候就直接把 RDB 的内容写到 AOF 文件开头。这样做的好处是可以结合 RDB 和 AOF 的优点, 快速加载同时避免丢失过多的数据。当然缺点也是有的， AOF 里面的 RDB 部分是压缩格式不再是 AOF 格式，可读性较差。


### AOF重写了解吗？可以简单说说吗？

AOF重写可以产生一个新的AOF文件，这个新的AOF文件和原有的AOF文件所保存的数据库状态一样，**但体积更小**。

在执行 BGREWRITEAOF 命令时，Redis 服务器会维护一个 AOF **重写缓冲区**，该缓冲区会在子进程创建新AOF文件期间，记录服务器执行的所有写命令。**当子进程完成创建新AOF文件的工作之后，服务器会将重写缓冲区中的所有内容 追加到新AOF文件的末尾，使得新旧两个AOF文件所保存的数据库状态一致**。最后，服务器用新的AOF文件替换旧的 AOF文件，以此来完成AOF文件重写操作。


### 是否使用Redis集群，集群的原理是什么

Redis Sentinel（哨兵）着眼于高可用，在master宕机时会自动将slave提升为master，继续提供服务。

Sentinel（哨兵）可以监听集群中的服务器，并在主服务器进入下线状态时，自动从服务器中选举出新的主服务器。

Redis Cluster（集群）着眼于扩展性，在单个Redis内存不足时，使用Cluster进行分片存储。


### 如何解决Redis的并发竞争Key问题

所谓 Redis 的并发竞争 Key 的问题也就是多个系统同时对一个 key 进行操作，但是最后执行的顺序和我们期望的顺序不同，这样也就导致了结果的不同！

推荐一种方案：分布式锁（zookeeper 和 Redis 都可以实现分布式锁）。（如果不存在 Redis 的并发竞争 Key 问 题，不要使用分布式锁，这样会影响性能）

基于zookeeper临时有序节点可以实现的分布式锁。大致思想为：每个客户端对某个方法加锁时，在zookeeper上的 与该方法对应的指定节点的目录下，生成一个唯一的瞬时有序节点。 判断是否获取锁的方式很简单，只需要判断有 序节点中序号最小的一个。 当释放锁的时候，只需将这个瞬时节点删除即可。同时，其可以避免服务宕机导致的锁 无法释放，而产生的死锁问题。完成业务流程后，删除对应的子节点释放锁。

在实践中，当然是从以可靠性为主。所以首推Zookeeper。

### 如何保证缓存与数据库双写时的数据一致性

首先说一句，你只要用缓存，就可能会涉及到缓存与数据库双存储双写，你只要是双写，就一定会有数据一致性的问题，那么你如 何解决一致性问题？

一般来说，就是如果你的系统不是严格要求缓存+数据库必须一致性的话，缓存可以稍微的跟数据库偶尔有不一致的 情况，最好不要做这个方案，最好将**读请求和写请求串行化**，串到一个内存队列里去，这样就可以保证一定不会出现不一致的情况。

串行化之后，就会导致系统的吞吐量会大幅度的降低，用比正常情况下多几倍的机器去支撑线上的一个请求。

最经典的缓存+数据库读写的模式，就是 **预留缓存模式**Cache Aside Pattern。

- 读的时候，先读缓存，缓存没有的话，就读数据库，然后取出数据后放入缓存，同时返回响应。
- 更新的时候，**先删除缓存，然后再更新数据库，这样读的时候就会发现缓存中没有数据而直接去数据库中拿数据了**。

### 数据为什么会出现不一致的情况？

这样的问题主要是在并发读写访问的时候，缓存和数据相互交叉执行。

**一、单库情况下**

同一时刻发生了并发读写请求，**例如为A(写) B (读)2个请求**

![image-20211007112110133](https://gitee.com/duycc/picgo/raw/master/20211007112111.png)

1. A请求发送一个写操作到服务端，第一步会淘汰cache，然后因为各种原因卡主了，不在执行后面业务(例：大量的业务操作、调用其他服务处理消耗了1s）。

2. B请求发送一个读操作，读cache，因为cache淘汰，所以为空

3. B请求继续读DB，读出一个脏数据，并写入cache

4. A请求终于执行完全，在写入数据到DB

总结：因最后才把写操作数据入DB，并没同步。cache里面一直保持脏数据

脏数据是指源系统中的数据不在给定的范围内或对于实际业务毫无意义，或是数据格式非法，以及在源系统中存在不规范的编码和含糊的业务逻辑。

**二、主从同步，读写分离的情况下，读从库而产生脏数据**

![image-20211007112225430](https://gitee.com/duycc/picgo/raw/master/20211007112226.png)



1. A请求发送一个写操作到服务端，第一步会淘汰cache

2. A请求写主数据库，写了最新的数据。

3. B请求发送一个读操作，读cache，因为cache淘汰，所以为空

4. B请求继续读DB，读的是从库，此时主从同步还没同步成功。读出脏数据，然后脏数据入cache

5. 最后数据库主从同步完成

总结：这种情况下请求A和请求B操作时序没问题，是主从同步的时延问题(假设1s)，导致读请求读取从库读到脏数据导致的数据不一致

**根本原因:**

单库下，逻辑处理中消耗1s，可能读到旧数据入缓存

主从+读写分离，在1s的主从同步时延中，到从库的旧数据入缓存

### 常见的数据优化方案你了解吗？

![image-20211007112512144](https://gitee.com/duycc/picgo/raw/master/20211007112513.png)

**一、缓存双淘汰法**

1. 先淘汰缓存
2. 再写数据库
3. 往消息总线esb发送一个淘汰消息，发送立即返回。写请求的处理时间几乎没有增加，这个方法淘汰了缓存两次。因此被称为“缓存双淘汰法“，而在消息总线下游，有一个异步淘汰缓存的消费者，在拿到淘汰消息在1s后淘汰缓存，这样，即使在一秒内有脏数据入缓存，也能够被淘汰掉。

**二、异步淘汰缓存**

上述的步骤，都是在业务线里面执行，新增一个线下的读取binlog异步淘汰缓存模块，读取binlog总的数据，然后进行异步淘汰。

![image-20211007112531276](https://gitee.com/duycc/picgo/raw/master/20211007112532.png)

这里简单提供一个思路

1.思路：

MySQL binlog增量发布订阅消费+消息队列+增量数据更新到Redis

1）读请求走Redis：热数据基本都在Redis

2）写请求走MySQL: 增删改都操作MySQL

3）更新Redis数据：MySQ的数据操作binlog，来更新到Redis

2.Redis更新

1）数据操作主要分为两块：

- 一个是全量(将全部数据一次写入到Redis)
- 一个是增量（实时更新）

这里说的是增量,指的是mysql的update、insert、delate变更数据。这样一旦MySQL中产生了新的写入、更新、删除等操作，就可以把binlog相关的消息推送至Redis，Redis再根据binlog中的记录，对Redis进行更新，就无需在从业务线去操作缓存内容。

