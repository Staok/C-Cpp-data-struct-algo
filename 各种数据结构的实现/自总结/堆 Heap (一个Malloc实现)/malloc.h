#ifndef __MALLOC_H
#define __MALLOC_H


/*���ļ���� ALIENTEKս��STM32������V3 �ڴ���� ��Դ����*/
/*�����ַ��֣�Ӳʯ��YSFxϵ�п�������������ڴ����Դ���������ļ���һģһ�������Ҷ�˵�Լ�������...*/

/*______________________�û�����___________________________*/
#define RAM_Num 		3		//����֧�ֵ�SRAM����
/*��������˵��Ŀ��ڴ棬������Ҫ�պ�«��ư������Ӧ������Ϣ*/

/*______________________�û�����___________________________*/
//�����ڴ�ر�־
#define InrRAM	 		0		//�ڲ��ڴ��

#define ExRAM1   	    1		//�ⲿ�ڴ��1

#define InrCCM  		2		//CCM�ڴ��(�˲���SRAM����CPU���Է���!!!)
//#define ExRAM2   		3		//�ⲿ�ڴ��2���������ʱû�õ���

/*______________________�û����ã�InrRAM ___________________________*/
//InrRAM�ڴ�����趨��InrRAM��ȫ����MCU�ڲ�SRAM����
#define InrRAM_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽڣ�һ�㲻�ö�������Ĭ�Ͼͺã�

#define InrRAM_MAX_SIZE             70*1024  						    //�������ڴ� 70K���������

#define InrRAM_ALLOC_TABLE_SIZE	(InrRAM_MAX_SIZE/InrRAM_BLOCK_SIZE) 	//�ڴ���С�������ĪҪ�Ҷ�����

/*______________________�û����ã�ExRAM1 ___________________________*/
//ExRAM1�ڴ�����趨��ExRAM1���ڴ�ش����ⲿSRAM����
#define ExRAM1_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽڣ�һ�㲻�ö�������Ĭ�Ͼͺã�
#define ExRAM1_MAX_SIZE             960*1024  						    //�������ڴ�960K������1MB�ռ���ⲿSRAM�����ﱣ��Ĭ�Ͼͺã�
#define ExRAM1_ALLOC_TABLE_SIZE	(ExRAM1_MAX_SIZE/ExRAM1_BLOCK_SIZE) 	//�ڴ���С����ExRAM1_MAX_SIZEΪ960K����£����ռ30K
/*��������˵������ڴ棬Ҫȥ.c�ļ��޸�Ҫ�޸ĵĲ���*/

/*______________________�û����ã�InrCCM ___________________________*/
//InrCCM�ڴ�����趨�����ڹ���CCM(�ر�ע��,�ⲿ��SRAM,��CPU���Է���!!)
#define InrCCM_BLOCK_SIZE			32  	  							//�ڴ���СΪ32�ֽ�
#define InrCCM_MAX_SIZE             60*1024                             //�������ڴ�60K��Ĭ�ϲ��ö���
#define InrCCM_ALLOC_TABLE_SIZE	(InrCCM_MAX_SIZE/InrCCM_BLOCK_SIZE)		//�ڴ���С


/*________________________����Ĭ�ϵĲ��ö�________________________*/
//�ڴ���������
struct _m_malloc_dev
{
	void (*init)(u8);					//��ʼ��
	float (*perused)(u8);		  	    	//�ڴ�ʹ����
	u8 	*membase[RAM_Num];				//�ڴ�� ����SRAMBANK��������ڴ�
	u16 *memmap[RAM_Num]; 				//�ڴ����״̬��
	u8  memrdy[RAM_Num]; 				//�ڴ�����Ƿ����
};
extern struct _m_malloc_dev malloc_dev;	 //��malloc.c���涨��
    
void my_mem_init(u8 memx);				//�ڴ�����ʼ������(��/�ڲ�����)
u32 my_mem_malloc(u8 memx,u32 size);	//�ڴ����(�ڲ�����)
u8 my_mem_free(u8 memx,u32 offset);		//�ڴ��ͷ�(�ڲ�����)
float my_mem_perused(u8 memx);				//����ڴ�ʹ����(��/�ڲ�����) 
////////////////////////////////////////////////////////////////////////////////
/*________�����û����õĺ�����ʹ�÷����� stdlib.h �����malloc()������________*/
void myfree(u8 memx,void *ptr);  			//�ڴ��ͷ�(�ⲿ����)
void *mymalloc(u8 memx,u32 size);			//�ڴ����(�ⲿ����)
void *myrealloc(u8 memx,void *ptr,u32 size);//���·����ڴ�(�ⲿ����)

#endif













