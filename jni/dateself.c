#include <jni.h>
#include <android/log.h>

#include <stdlib.h>
#include <stdio.h>

#ifndef _DATESELF_H_
#define _DATESELF_H_

#define LENGTH sizeof(struct CalculateData1)
#define LOG_TAG    "com.csh.wuziqi from C"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

struct CalculateData1 {
	int id;		//内部使用,唯一的数据
	int weight;	//权重
	int number;	//权重的个数
	int x;		//记录当前的位置
	int y;
	struct CalculateData1 *next;
};

//创建一个全局的引导进入链表的指针
struct CalculateData1 *head = NULL;
struct CalculateData1 *last = NULL;

//数据的长度
int dateLength = 0;

#endif

void printAll(void);
struct CalculateData1 *get(int num);

/*
 ===========================
 功能：返回数据的最大值
 返回：int
 ===========================
 */
int getMaxValue(void) {
	struct CalculateData1 *p;

	int value = 0;
	int first=0;
	int second=0;
	int count=0;

	if (head != NULL) {
		first=head->weight;
		second=first;

		p = head;

		while (p != NULL&&second==first) {
			count++;
			second=p->weight;
			p = p->next;     //移到下一个节点
		}
		count--;
		LOGI("%d", count);
		count=(int)(rand() % count);
		count++;
		LOGI("%d", count);
		p=get(count);
		if(p==NULL){
			return -1;
		}else{
			return p->x * 100 + p->y;
		}

	} else {
		return -1;
	}
}

/*
 ===========================
 功能：创建一个新的
 返回：CalculateData1 *
 ===========================
 */
struct CalculateData1 *getNew(void) {
	struct CalculateData1 *jiedian; //节点指针

	jiedian = (struct CalculateData1 *) malloc(LENGTH);   //开辟一个新节点
	if (jiedian == NULL)        //节点开辟不成功
			{
		LOGI("%s", "Cann't create it, try it again in a moment!");
	} else {
		if (head == NULL) {
			jiedian->id = 1;
		} else {
			jiedian->id = last->id + 1;
		}
		LOGI("%s", "create it success!");
	}
	return jiedian;
}

/*
 ===========================
 功能：添加节点
 返回：void
 ===========================
 */
void add(struct CalculateData1 *node) {

	node->next = NULL;
	if (head == NULL) {
		head = node;
	} else {
		last->next = node;
	}
	last = node;

	//数据长度+1
	dateLength++;

}

/*
 ===========================
 功能：清空所有数据
 返回：void
 ===========================
 */
void clear(void) {
	head = NULL;
	last = NULL;
}

/*
 ===========================
 功能：返回所有数据的长度
 返回：int
 ===========================
 */
int getLength() {
	return dateLength;
}

/*
 ==========================
 功能：删除指定节点
 (此例中是删除指定学号的节点)
 返回：void
 ==========================
 */
void delete(int num) {
	struct CalculateData1 *p1;     //p1保存当前需要检查的节点的地址
	struct CalculateData1 *p2;     //p2保存当前检查过的节点的地址
	if (head == NULL)       //是空链表（结合图3理解）
			{
		LOGI("%s", "List is null!");
		return;
	}

	//定位要删除的节点
	p1 = head;
	while (p1->id != num && p1->next != NULL) //p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
	{
		p2 = p1;            //保存当前节点的地址
		p1 = p1->next;       //后移一个节点
	}

	if (p1->id == num)     //找到了。
			{
		if (p1 == head)     //如果要删除的节点是第一个节点
				{
			head = p1->next; //头指针指向第一个节点的后一个节点，也就是第二个节点。这样第一个节点就不在链表中，即删除
		} else            //如果是其它节点，则让原来指向当前节点的指针，指向它的下一个节点，完成删除
		{
			p2->next = p1->next;
		}

		free(p1);      		//释放当前节点
		p1 = NULL;
		LOGI("delete %d success!", num);
		dateLength -= 1;         //节点总数减1个
	} else                		//没有找到
	{
		LOGI("%d not been found!", num);
	}
}

/*
 ==========================
 功能：返回指定节点的数据
 返回：void
 ==========================
 */
struct CalculateData1 *get(int num) {
	struct CalculateData1 *p1;     //p1保存当前需要检查的节点的地址
	int count=0;
	if (head == NULL)       //是空链表（结合图3理解）
			{
		LOGI("%s", "List is null!");
		return NULL;
	}

	p1 = head;
	count=1;
	while (count < num && p1->next != NULL) //p1指向的节点不是所要查找的，并且它不是最后一个节点，就继续往下找
	{
		count++;
		p1 = p1->next;      //后移一个节点
	}

	if (count == num)     	//找到了。
	{
		return p1;
	} else                	//没有找到
	{
		return NULL;
	}

}

/*
 ==========================
 功能：插入指定节点的后面
 (此例中是指定学号的节点)
 返回：void
 ==========================
 */
void insert(int num, struct CalculateData1 *node) {
	struct CalculateData1 *p1;     //p1保存当前需要检查的节点的地址
	if (head == NULL)       //头节点为null时，直接保存数据
			{
		head = node;
		node->next = NULL;
		last = node;
		dateLength += 1;
		return;
	}

	p1 = head;
	while (p1->id != num && p1->next != NULL) //p1指向的节点不是所要查找的，并且它不是最后一个节点，继续往下找
	{
		p1 = p1->next;       //后移一个节点
	}

	if (p1->id == num)        //找到了（结合图示8理解）
			{
		node->next = p1->next;    //显然node的下一节点是原p1的next
		p1->next = node;     //插入后，原p1的下一节点就是要插入的node
		dateLength += 1;         //节点总数增加1个
		LOGI("\n%d insert success!\n", num);
	} else {
		LOGI("\n%d not been found!\n", num);
	}
}

/*
 ==========================
 功能：反序节点
 (链表的头变成链表的尾，链表的尾变成头)
 返回：void
 ==========================
 */
void reverse(void) {
	struct CalculateData1 *p;      //临时存储
	struct CalculateData1 *p1;     //存储返回结果
	struct CalculateData1 *p2;     //源结果节点一个一个取

	p1 = NULL;          //开始颠倒时，已颠倒的部分为空
	p2 = head;          //p2指向链表的头节点
	last = head;
	while (p2 != NULL) {
		p = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = p;
	}
	head = p1;
	last->next = NULL;
}

/*
 ==========================
 功能：选择排序(由小到大)
 返回：void
 ==========================
 */
void selectSortSTL() {
	struct CalculateData1 *first;     //排列后有序链的表头指针
	struct CalculateData1 *tail;      //排列后有序链的表尾指针
	struct CalculateData1 *p_min;     //保留键值更小的节点的前驱节点的指针
	struct CalculateData1 *min;       //存储最小节点
	struct CalculateData1 *p;         //当前比较的节点

	first = NULL;
	while (head != NULL)       //在链表中找键值最小的节点
	{
		//注意：这里for语句就是体现选择排序思想的地方
		for (p = head, min = head; p->next != NULL; p = p->next) //循环遍历链表中的节点，找出此时最小的节点
				{
			if (p->next->weight > min->weight)     //找到一个比当前min小的节点
					{
				p_min = p;        //保存找到节点的前驱节点：显然p->next的前驱节点是p
				min = p->next;     //保存键值更小的节点
			}
		}

		//上面for语句结束后，就要做两件事；一是把它放入有序链表中；二是根据相应的条件判断，安排它离开原来的链表

		//第一件事
		if (first == NULL)     //如果有序链表目前还是一个空链表
				{
			first = min;        //第一次找到键值最小的节点
			tail = min;        //注意：尾指针让它指向最后的一个节点
		} else              //有序链表中已经有节点
		{
			tail->next = min;    //把刚找到的最小节点放到最后，即让尾指针的next指向它
			tail = min;           //尾指针也要指向它
		}

		//第二件事
		if (min == head)            //如果找到的最小节点就是第一个节点
				{
			head = head->next;      //显然让head指向原head->next,即第二个节点，就OK
		} else            //如果不是第一个节点
		{
			p_min->next = min->next;  //前次最小节点的next指向当前min的next,这样就让min离开了原链表
		}
	}

	if (first != NULL)      //循环结束得到有序链表first
			{
		tail->next = NULL;   //单向链表的最后一个节点的next应该指向NULL
	}
	head = first;
	last = tail;
}

/*
 ===========================
 功能：输出节点
 返回： void
 ===========================
 */
void printAll(void) {
	struct CalculateData1 *p;
	p = head;

	LOGI("init success----> %s", "da yin shu ju!");
	if (head != NULL)        //只要不是空链表，就输出链表中所有节点
			{
		do {
			/*
			 输出相应的值：当前节点地址、各字段值、当前节点的下一节点地址。
			 这样输出便于读者形象看到一个单向链表在计算机中的存储结构，和我们
			 设计的图示是一模一样的。
			 */
			LOGI("init success----> x=%d,y=%d,value=%d", p->x, p->y, p->weight); //输出头指针指向的地址
			p = p->next;     //移到下一个节点
		} while (p != NULL);
	}
}
