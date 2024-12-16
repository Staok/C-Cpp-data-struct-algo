#include "malloc.h"	    

/*���ļ���� ALIENTEKս��STM32������V3 �ڴ���� ��Դ����*/
/*�����ַ��֣�Ӳʯ��YSFxϵ�п�������������ڴ����Դ���������ļ���һģһ�������Ҷ�˵�Լ�������...*/

/*__________���¸���.h�ļ��Ķ�����Ӧ�޸�_________________*/

//�ڴ��(32�ֽڶ���)���������涫���ĵط���
__align(32) u8 mem1base[InrRAM_MAX_SIZE];															//�ڲ�SRAM�ڴ��

__align(32) u8 mem2base[ExRAM1_MAX_SIZE] __attribute__((at(SRAM1_BANK3_ADDR)));					    //�ⲿSRAM�ڴ�أ�ע�ⶨ��û���ַ

__align(32) u8 mem3base[InrCCM_MAX_SIZE] __attribute__((at(0X10000000)));							//�ڲ�CCM�ڴ�أ�ע�ⶨ��û���ַ



//�ڴ�����
u16 mem1mapbase[InrRAM_ALLOC_TABLE_SIZE];														    //�ڲ�SRAM�ڴ��MAP

u16 mem2mapbase[ExRAM1_ALLOC_TABLE_SIZE] __attribute__((at(SRAM1_BANK3_ADDR + ExRAM1_MAX_SIZE)));	//�ⲿSRAM�ڴ��MAP

u16 mem3mapbase[InrCCM_ALLOC_TABLE_SIZE] __attribute__((at(0X10000000 + InrCCM_MAX_SIZE)));		    //�ڲ�CCM�ڴ��MAP



//�ڴ�������	   
const u32 memtblsize[RAM_Num]	= {InrRAM_ALLOC_TABLE_SIZE,	ExRAM1_ALLOC_TABLE_SIZE,	InrCCM_ALLOC_TABLE_SIZE}; 	//�洢�����ڴ����ڴ��Ĵ�С
const u32 memblksize[RAM_Num]	= {InrRAM_BLOCK_SIZE,		ExRAM1_BLOCK_SIZE,			InrCCM_BLOCK_SIZE};			//�洢�����ڴ��Ŀ��С
const u32 memsize[RAM_Num]		= {InrRAM_MAX_SIZE,			ExRAM1_MAX_SIZE,			InrCCM_MAX_SIZE};			//�洢�����ڴ����ֽ����ܴ�С



//�ڴ���������
struct _m_malloc_dev malloc_dev =
{
	my_mem_init,						//�ڴ��ʼ��
	my_mem_perused,						//�ڴ�ʹ����
	mem1base,mem2base,mem3base,			//�ڴ��
	mem1mapbase,mem2mapbase,mem3mapbase,//�ڴ����״̬��
	0,0,0,  		 					//�ڴ����δ����
};


/*__________���»������ö�_________________*/

//�ڴ�����ʼ��  
//memx:�����ڴ��
void my_mem_init(u8 memx)  
{  
    mymemset(malloc_dev.memmap[memx], 	0,	memtblsize[memx]*2	);	//�ڴ�״̬����������  
	mymemset(malloc_dev.membase[memx], 	0,	memsize[memx]		);	//�ڴ��������������  
	malloc_dev.memrdy[memx] = 1;									//�ڴ�����ʼ��OK
}  
//��ȡ�ڴ�ʹ����
//memx:�����ڴ��
//����ֵ:ʹ����(0~100%)
float my_mem_perused(u8 memx)  
{  
    u32 used=0;  
    u32 i;  
    for(i=0;i<memtblsize[memx];i++)  
    {  
        if(malloc_dev.memmap[memx][i])used++; 
    } 
    return ((float)used)/((float)(memtblsize[memx]));  
} 

//�ڴ����(�ڲ�����)
//memx:�����ڴ��
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:0XFFFFFFFF,�������;����,�ڴ�ƫ�Ƶ�ַ 
u32 my_mem_malloc(u8 memx,u32 size)  
{  
    signed long offset=0;  
    u32 nmemb;	//��Ҫ���ڴ����  
	u32 cmemb=0;//�������ڴ����
    u32 i;  
    if(!malloc_dev.memrdy[memx])malloc_dev.init(memx);//δ��ʼ��,��ִ�г�ʼ�� 
    if(size==0)return 0XFFFFFFFF;//����Ҫ����
    nmemb=size/memblksize[memx];  	//��ȡ��Ҫ����������ڴ����
    if(size%memblksize[memx])nmemb++;  
    for(offset=memtblsize[memx]-1;offset>=0;offset--)//���������ڴ������  
    {     
		if(!malloc_dev.memmap[memx][offset])cmemb++;//�������ڴ��������
		else cmemb=0;								//�����ڴ������
		if(cmemb==nmemb)							//�ҵ�������nmemb�����ڴ��
		{
            for(i=0;i<nmemb;i++)  					//��ע�ڴ��ǿ� 
            {  
                malloc_dev.memmap[memx][offset+i]=nmemb;  
            }  
            return (offset*memblksize[memx]);//����ƫ�Ƶ�ַ  
		}
    }  
    return 0XFFFFFFFF;//δ�ҵ����Ϸ����������ڴ��  
}  
//�ͷ��ڴ�(�ڲ�����) 
//memx:�����ڴ��
//offset:�ڴ��ַƫ��
//����ֵ:0,�ͷųɹ�;1,�ͷ�ʧ��;  
u8 my_mem_free(u8 memx,u32 offset)  
{  
    int i;  
    if(!malloc_dev.memrdy[memx])//δ��ʼ��,��ִ�г�ʼ��
	{
		malloc_dev.init(memx);    
        return 1;//δ��ʼ��  
    }  
    if(offset<memsize[memx])//ƫ�����ڴ����. 
    {  
        int index=offset/memblksize[memx];			//ƫ�������ڴ�����  
        int nmemb=malloc_dev.memmap[memx][index];	//�ڴ������
        for(i=0;i<nmemb;i++)  						//�ڴ������
        {  
            malloc_dev.memmap[memx][index+i]=0;  
        }  
        return 0;  
    }else return 2;//ƫ�Ƴ�����.  
}  
//�ͷ��ڴ�(�ⲿ����) 
//memx:�����ڴ��
//ptr:�ڴ��׵�ַ 
void myfree(u8 memx,void *ptr)  
{  
	u32 offset;   
	if(ptr==NULL)return;//��ַΪ0.  
 	offset=(u32)ptr-(u32)malloc_dev.membase[memx];     
    my_mem_free(memx,offset);	//�ͷ��ڴ�      
}  
//�����ڴ�(�ⲿ����)
//memx:�����ڴ��
//size:�ڴ��С(�ֽ�)
//����ֵ:���䵽���ڴ��׵�ַ.
void *mymalloc(u8 memx,u32 size)  
{  
    u32 offset;   
	offset=my_mem_malloc(memx,size);  	   	 	   
    if(offset==0XFFFFFFFF)return NULL;  
    else return (void*)((u32)malloc_dev.membase[memx]+offset);  
}  
//���·����ڴ�(�ⲿ����)
//memx:�����ڴ��
//*ptr:���ڴ��׵�ַ
//size:Ҫ������ڴ��С(�ֽ�)
//����ֵ:�·��䵽���ڴ��׵�ַ.
void *myrealloc(u8 memx,void *ptr,u32 size)  
{  
    u32 offset;    
    offset=my_mem_malloc(memx,size);   	
    if(offset==0XFFFFFFFF)return NULL;     
    else  
    {  									   
	    mymemcpy((void*)((u32)malloc_dev.membase[memx]+offset),ptr,size);	//�������ڴ����ݵ����ڴ�   
        myfree(memx,ptr);  											  		//�ͷž��ڴ�
        return (void*)((u32)malloc_dev.membase[memx]+offset);  				//�������ڴ��׵�ַ
    }  
}











