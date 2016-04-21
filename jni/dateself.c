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
	int id;		//�ڲ�ʹ��,Ψһ������
	int weight;	//Ȩ��
	int number;	//Ȩ�صĸ���
	int x;		//��¼��ǰ��λ��
	int y;
	struct CalculateData1 *next;
};

//����һ��ȫ�ֵ��������������ָ��
struct CalculateData1 *head = NULL;
struct CalculateData1 *last = NULL;

//���ݵĳ���
int dateLength = 0;

#endif

void printAll(void);
struct CalculateData1 *get(int num);

/*
 ===========================
 ���ܣ��������ݵ����ֵ
 ���أ�int
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
			p = p->next;     //�Ƶ���һ���ڵ�
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
 ���ܣ�����һ���µ�
 ���أ�CalculateData1 *
 ===========================
 */
struct CalculateData1 *getNew(void) {
	struct CalculateData1 *jiedian; //�ڵ�ָ��

	jiedian = (struct CalculateData1 *) malloc(LENGTH);   //����һ���½ڵ�
	if (jiedian == NULL)        //�ڵ㿪�ٲ��ɹ�
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
 ���ܣ���ӽڵ�
 ���أ�void
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

	//���ݳ���+1
	dateLength++;

}

/*
 ===========================
 ���ܣ������������
 ���أ�void
 ===========================
 */
void clear(void) {
	head = NULL;
	last = NULL;
}

/*
 ===========================
 ���ܣ������������ݵĳ���
 ���أ�int
 ===========================
 */
int getLength() {
	return dateLength;
}

/*
 ==========================
 ���ܣ�ɾ��ָ���ڵ�
 (��������ɾ��ָ��ѧ�ŵĽڵ�)
 ���أ�void
 ==========================
 */
void delete(int num) {
	struct CalculateData1 *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ
	struct CalculateData1 *p2;     //p2���浱ǰ�����Ľڵ�ĵ�ַ
	if (head == NULL)       //�ǿ��������ͼ3��⣩
			{
		LOGI("%s", "List is null!");
		return;
	}

	//��λҪɾ���Ľڵ�
	p1 = head;
	while (p1->id != num && p1->next != NULL) //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬�ͼ���������
	{
		p2 = p1;            //���浱ǰ�ڵ�ĵ�ַ
		p1 = p1->next;       //����һ���ڵ�
	}

	if (p1->id == num)     //�ҵ��ˡ�
			{
		if (p1 == head)     //���Ҫɾ���Ľڵ��ǵ�һ���ڵ�
				{
			head = p1->next; //ͷָ��ָ���һ���ڵ�ĺ�һ���ڵ㣬Ҳ���ǵڶ����ڵ㡣������һ���ڵ�Ͳ��������У���ɾ��
		} else            //����������ڵ㣬����ԭ��ָ��ǰ�ڵ��ָ�룬ָ��������һ���ڵ㣬���ɾ��
		{
			p2->next = p1->next;
		}

		free(p1);      		//�ͷŵ�ǰ�ڵ�
		p1 = NULL;
		LOGI("delete %d success!", num);
		dateLength -= 1;         //�ڵ�������1��
	} else                		//û���ҵ�
	{
		LOGI("%d not been found!", num);
	}
}

/*
 ==========================
 ���ܣ�����ָ���ڵ������
 ���أ�void
 ==========================
 */
struct CalculateData1 *get(int num) {
	struct CalculateData1 *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ
	int count=0;
	if (head == NULL)       //�ǿ��������ͼ3��⣩
			{
		LOGI("%s", "List is null!");
		return NULL;
	}

	p1 = head;
	count=1;
	while (count < num && p1->next != NULL) //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬�ͼ���������
	{
		count++;
		p1 = p1->next;      //����һ���ڵ�
	}

	if (count == num)     	//�ҵ��ˡ�
	{
		return p1;
	} else                	//û���ҵ�
	{
		return NULL;
	}

}

/*
 ==========================
 ���ܣ�����ָ���ڵ�ĺ���
 (��������ָ��ѧ�ŵĽڵ�)
 ���أ�void
 ==========================
 */
void insert(int num, struct CalculateData1 *node) {
	struct CalculateData1 *p1;     //p1���浱ǰ��Ҫ���Ľڵ�ĵ�ַ
	if (head == NULL)       //ͷ�ڵ�Ϊnullʱ��ֱ�ӱ�������
			{
		head = node;
		node->next = NULL;
		last = node;
		dateLength += 1;
		return;
	}

	p1 = head;
	while (p1->id != num && p1->next != NULL) //p1ָ��Ľڵ㲻����Ҫ���ҵģ��������������һ���ڵ㣬����������
	{
		p1 = p1->next;       //����һ���ڵ�
	}

	if (p1->id == num)        //�ҵ��ˣ����ͼʾ8��⣩
			{
		node->next = p1->next;    //��Ȼnode����һ�ڵ���ԭp1��next
		p1->next = node;     //�����ԭp1����һ�ڵ����Ҫ�����node
		dateLength += 1;         //�ڵ���������1��
		LOGI("\n%d insert success!\n", num);
	} else {
		LOGI("\n%d not been found!\n", num);
	}
}

/*
 ==========================
 ���ܣ�����ڵ�
 (�����ͷ��������β�������β���ͷ)
 ���أ�void
 ==========================
 */
void reverse(void) {
	struct CalculateData1 *p;      //��ʱ�洢
	struct CalculateData1 *p1;     //�洢���ؽ��
	struct CalculateData1 *p2;     //Դ����ڵ�һ��һ��ȡ

	p1 = NULL;          //��ʼ�ߵ�ʱ���ѵߵ��Ĳ���Ϊ��
	p2 = head;          //p2ָ�������ͷ�ڵ�
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
 ���ܣ�ѡ������(��С����)
 ���أ�void
 ==========================
 */
void selectSortSTL() {
	struct CalculateData1 *first;     //���к��������ı�ͷָ��
	struct CalculateData1 *tail;      //���к��������ı�βָ��
	struct CalculateData1 *p_min;     //������ֵ��С�Ľڵ��ǰ���ڵ��ָ��
	struct CalculateData1 *min;       //�洢��С�ڵ�
	struct CalculateData1 *p;         //��ǰ�ȽϵĽڵ�

	first = NULL;
	while (head != NULL)       //���������Ҽ�ֵ��С�Ľڵ�
	{
		//ע�⣺����for����������ѡ������˼��ĵط�
		for (p = head, min = head; p->next != NULL; p = p->next) //ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ�
				{
			if (p->next->weight > min->weight)     //�ҵ�һ���ȵ�ǰminС�Ľڵ�
					{
				p_min = p;        //�����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p
				min = p->next;     //�����ֵ��С�Ľڵ�
			}
		}

		//����for�������󣬾�Ҫ�������£�һ�ǰ����������������У����Ǹ�����Ӧ�������жϣ��������뿪ԭ��������

		//��һ����
		if (first == NULL)     //�����������Ŀǰ����һ��������
				{
			first = min;        //��һ���ҵ���ֵ��С�Ľڵ�
			tail = min;        //ע�⣺βָ������ָ������һ���ڵ�
		} else              //�����������Ѿ��нڵ�
		{
			tail->next = min;    //�Ѹ��ҵ�����С�ڵ�ŵ���󣬼���βָ���nextָ����
			tail = min;           //βָ��ҲҪָ����
		}

		//�ڶ�����
		if (min == head)            //����ҵ�����С�ڵ���ǵ�һ���ڵ�
				{
			head = head->next;      //��Ȼ��headָ��ԭhead->next,���ڶ����ڵ㣬��OK
		} else            //������ǵ�һ���ڵ�
		{
			p_min->next = min->next;  //ǰ����С�ڵ��nextָ��ǰmin��next,��������min�뿪��ԭ����
		}
	}

	if (first != NULL)      //ѭ�������õ���������first
			{
		tail->next = NULL;   //������������һ���ڵ��nextӦ��ָ��NULL
	}
	head = first;
	last = tail;
}

/*
 ===========================
 ���ܣ�����ڵ�
 ���أ� void
 ===========================
 */
void printAll(void) {
	struct CalculateData1 *p;
	p = head;

	LOGI("init success----> %s", "da yin shu ju!");
	if (head != NULL)        //ֻҪ���ǿ�������������������нڵ�
			{
		do {
			/*
			 �����Ӧ��ֵ����ǰ�ڵ��ַ�����ֶ�ֵ����ǰ�ڵ����һ�ڵ��ַ��
			 ����������ڶ������󿴵�һ�����������ڼ�����еĴ洢�ṹ��������
			 ��Ƶ�ͼʾ��һģһ���ġ�
			 */
			LOGI("init success----> x=%d,y=%d,value=%d", p->x, p->y, p->weight); //���ͷָ��ָ��ĵ�ַ
			p = p->next;     //�Ƶ���һ���ڵ�
		} while (p != NULL);
	}
}
