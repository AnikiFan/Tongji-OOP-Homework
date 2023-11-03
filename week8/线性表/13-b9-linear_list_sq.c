/* 2254298 大数据 范潇 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc函数
#if(__linux__)
#include <unistd.h>		//exit函数
#endif 
#include <math.h>               //fabs函数
#include <string.h>		//strcpy/strcmp等函数
#include "linear_list_sq.h"	//形式定义

/* 初始化线性表 */
Status InitList(sqlist* L)
{
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (L->elem == NULL)
#if(__linux__)
        exit(LOVERFLOW);
#else 
        return LOVERFLOW;
#endif
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    return OK;
}

/* 删除线性表 */
Status DestroyList(sqlist* L)
{
    /* 两种指针类型需要释放二级空间 */
#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    int i;

    /* 首先释放二级空间 */
    for (i = 0; i < L->length; i++)
        free(L->elem[i]);
#endif

    /* 若未执行 InitList，直接执行本函数，则可能出错，因为指针初始值未定 */
    if (L->elem)
        free(L->elem);
    L->length = 0;
    L->listsize = 0;

    return OK;
}

/* 清除线性表（已初始化，不释放空间，只清除内容） */
Status ClearList(sqlist* L)
{
    /* 两种指针类型需要释放二级空间 */
#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    int i;

    /* 首先释放二级空间 */
    for (i = 0; i < L->length; i++)
        free(L->elem[i]);
#endif

    L->length = 0;
    return OK;
}

/* 判断是否为空表 */
Status ListEmpty(sqlist L)
{
    if (L.length == 0)
        return TRUE;
    else
        return FALSE;
}

/* 求表的长度 */
int ListLength(sqlist L)
{
    return L.length;
}

/* 取表中元素 */
Status GetElem(sqlist L, int i, ElemType* e)
{
    if (i<1 || i>L.length)  //不需要多加 || L.length>0
        return ERROR;

    /* 循环比较整个线性表 */
#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    strcpy(*e, L.elem[i - 1]);	//下标从0开始，第i个实际在elem[i-1]中
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    memcpy(e, &(L.elem[i - 1]), sizeof(ElemType)); //下标从0开始，第i个实际在elem[i-1]中
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    memcpy(*e, L.elem[i - 1], sizeof(ET)); //下标从0开始，第i个实际在elem[i-1]中
#else	//int和double直接赋值
    * e = L.elem[i - 1];	//下标从0开始，第i个实际在elem[i-1]中
#endif

    return OK;
}

/* 查找符合指定条件的元素 */
int LocateElem(sqlist L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
    ElemType* p = L.elem;
    int       i = 1;

    while (i <= L.length && (*compare)(*p++, e) == FALSE)
        i++;

    return (i <= L.length) ? i : 0;	//找到返回i，否则返回0
}

/* 查找符合指定条件的元素的前驱元素 */
Status PriorElem(sqlist L, ElemType cur_e, ElemType* pre_e,Status (*compare)(ElemType e1,ElemType e2))
{
    ElemType* p = L.elem;
    int       i = 1;

    /* 循环比较整个线性表 */
    while (i <= L.length &&! compare(*p,cur_e)) {
        i++;
        p++;
    }
    if (i == 1 || i > L.length) //找到第1个元素或未找到
        return ERROR;

#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined(ELEMTYPE_IS_CHAR_P)
    strcpy(*pre_e, *--p);	//取前驱元素的值
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    memcpy(pre_e, --p, sizeof(ElemType));	//取前驱元素的值
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    memcpy(*pre_e, *--p, sizeof(ET));	//取前驱元素的值
#else	//int和double直接赋值
    * pre_e = *--p;	//取前驱元素的值
#endif
    return OK;
    }

/* 查找符合指定条件的元素的后继元素 */
Status NextElem(sqlist L, ElemType cur_e, ElemType * next_e,Status (*compare)(ElemType e1,ElemType e2))
{
    ElemType* p = L.elem;
    int       i = 1;

    /* 循环比较整个线性表(不含尾元素) */
    while (i < L.length && ! compare(*p,cur_e)) {
        i++;
        p++;
    }

    if (i >= L.length)	//未找到（最后一个元素未比较）
        return ERROR;

#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    strcpy(*next_e, *++p);	//取后继元素的值
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    memcpy(next_e, ++p, sizeof(ElemType));	//取后继元素的值
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    memcpy(*next_e, *++p, sizeof(ET));	//取后继元素的值
#else	//int和double直接赋值
    * next_e = *++p;	//取后继元素的值
#endif

    return OK;
    }

/* 在指定位置前插入一个新元素 */
Status ListInsert(sqlist * L, int i, ElemType e)
{
    ElemType* p, * q; //如果是算法，一般可以省略，程序不能

    if (i<1 || i>L->length + 1)   //合理范围是 1..length+1
        return ERROR;

    /* 空间已满则扩大空间 */
    if (L->length >= L->listsize) {
        ElemType* newbase;
        newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return LOVERFLOW;

        L->elem = newbase;
        L->listsize += LISTINCREMENT;
        //L->length暂时不变
    }

    q = &(L->elem[i - 1]);  //第i个元素，即新的插入位置

    /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
    for (p = &(L->elem[L->length - 1]); p >= q; --p)
#if defined (ELEMTYPE_IS_CHAR_ARRAY)
        strcpy(*(p + 1), *p);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        memcpy(p + 1, p, sizeof(ElemType));	//不能用strcpy
#else	//int、double、char指针、struct student指针都是直接赋值
        * (p + 1) = *p;
#endif

    /* 插入新元素，长度+1 */
#if defined (ELEMTYPE_IS_CHAR_ARRAY)
    strcpy(*q, e);
#elif defined (ELEMTYPE_IS_CHAR_P)
    /* 原来L->elem[i-1]的指针已放入[i]中，要重新申请空间，插入新元素，长度+1 */
    L->elem[i - 1] = (ElemType)malloc((strlen(e) + 1) * sizeof(char));
    if (L->elem[i - 1] == NULL)
        return LOVERFLOW;

    strcpy(*q, e);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    memcpy(q, &e, sizeof(ElemType));
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    L->elem[i - 1] = (ElemType)malloc(sizeof(ET));
    if (L->elem[i - 1] == NULL)
        return LOVERFLOW;

    memcpy(*q, e, sizeof(ET));
#else	//int和double直接赋值
    * q = e;
#endif

    L->length++;

    return OK;
}

/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
Status ListDelete(sqlist * L, int i, ElemType * e)
{
    ElemType* p, * q; //如果是算法，一般可以省略，程序不能

    if (i<1 || i>L->length) //合理范围是 1..length
        return ERROR;

    p = &(L->elem[i - 1]); 		//指向第i个元素

#if defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
    strcpy(*e, *p); 				//取第i个元素的值放入e中
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    memcpy(e, p, sizeof(ElemType));	//取第i个元素的值放入e中
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    memcpy(*e, *p, sizeof(ET));		//取第i个元素的值放入e中
#else	//int和double直接赋值
    * e = *p; 				//取第i个元素的值放入e中
#endif

    q = &(L->elem[L->length - 1]);	//指向最后一个元素，也可以 q = L->elem+L->length-1

#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    free(*p);	//释放空间
#endif

    /* 从第i+1到最后，依次前移一格 */
    for (++p; p <= q; ++p) {
#if defined (ELEMTYPE_IS_CHAR_ARRAY)
        strcpy(*(p - 1), *p);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        memcpy((p - 1), p, sizeof(ElemType));
#else	//int、double、char指针、struct student指针都是直接赋值
        * (p - 1) = *p;
#endif
    }

    L->length--;	//长度-1
    return OK;
}

/* 遍历线性表 */
Status ListTraverse(sqlist L, Status(*visit)(ElemType e))
{
    extern int line_count; //在main中定义的打印换行计数器（与算法无关）
    ElemType* p = L.elem;
    int       i = 1;

    line_count = 0;		//计数器恢复初始值（与算法无关）
    while (i <= L.length && (*visit)(*p++) == TRUE)
        i++;

    if (i <= L.length)
        return ERROR;

    printf("\n");//最后打印一个换行，只是为了好看，与算法无关
    return OK;
}

//将线性表置空，如果扩展过空间，则要回复原始空间
Status	ClearList1(sqlist* L)
{
    /* 两种指针类型需要释放二级空间 */
#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    int i;

    /* 首先释放二级空间 */
    for (i = 0; i < L->length; i++)
        free(L->elem[i]);
#endif
    L->length = 0;
    if (L->listsize > LIST_INIT_SIZE) {
        ElemType* newbase = (ElemType*)realloc(L->elem,sizeof(ElemType)*LIST_INIT_SIZE);
        if (!newbase)
#if (__linux__)
            exit(LOVERFLOW);
#else 
            return LOVERFLOW;
#endif
        L->elem = newbase;
        L->listsize = LIST_INIT_SIZE;
    }
    return OK;
}
//如果指定元素有
Status	ListInsert1(sqlist* L, ElemType cur_e, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
    ElemType* p, * q; //如果是算法，一般可以省略，程序不能
    int i = L->length - 1;
    while (i >= 0 && !compare(L->elem[i], cur_e))
        i--;
    if (i < 0)
        return ERROR;
    /* 空间已满则扩大空间 */
    if (L->length >= L->listsize) {
        ElemType* newbase;
        newbase = (ElemType*)realloc(L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
            return LOVERFLOW;

        L->elem = newbase;
        L->listsize += LISTINCREMENT;
        //L->length暂时不变
    }

    q = &(L->elem[i]);  //最后一个相同元素，即新的插入位置

    /* 从最后一个【length放在[length-1]中】开始到第i个元素依次后移一格 */
    for (p = &(L->elem[L->length - 1]); p >= q; --p)
#if defined (ELEMTYPE_IS_CHAR_ARRAY)
        strcpy(*(p + 1), *p);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        memcpy(p + 1, p, sizeof(ElemType));	//不能用strcpy
#else	//int、double、char指针、struct student指针都是直接赋值
        * (p + 1) = *p;
#endif

    /* 插入新元素，长度+1 */
#if defined (ELEMTYPE_IS_CHAR_ARRAY)
    strcpy(*q, e);
#elif defined (ELEMTYPE_IS_CHAR_P)
    /* 原来L->elem[i-1]的指针已放入[i]中，要重新申请空间，插入新元素，长度+1 */
    L->elem[i - 1] = (ElemType)malloc((strlen(e) + 1) * sizeof(char));
    if (L->elem[i - 1] == NULL)
        return LOVERFLOW;

    strcpy(*q, e);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
    memcpy(q, &e, sizeof(ElemType));
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    L->elem[i - 1] = (ElemType)malloc(sizeof(ET));
    if (L->elem[i - 1] == NULL)
        return LOVERFLOW;

    memcpy(*q, e, sizeof(ET));
#else	//int和double直接赋值
    * q = e;
#endif

    L->length++;
    return OK;
}
Status	ListDelete1(sqlist* L, ElemType cur_e, Status(*compare)(ElemType e1, ElemType e2))
{
    ElemType* p, * q; //如果是算法，一般可以省略，程序不能
    int i = 0;
    while (i< L->length && !compare(L->elem[i], cur_e))
        i++;
    if (i >= L->length)
        return ERROR;
    p = &(L->elem[i ]); 		//指向第1个与指定元素相同的位置

    q = &(L->elem[L->length - 1]);	//指向最后一个元素，也可以 q = L->elem+L->length-1

#if defined (ELEMTYPE_IS_CHAR_P) || defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
    free(*p);	//释放空间
#endif

    /* 从第i+1到最后，依次前移一格 */
    for (++p; p <= q; ++p) {
#if defined (ELEMTYPE_IS_CHAR_ARRAY)
        strcpy(*(p - 1), *p);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
        memcpy((p - 1), p, sizeof(ElemType));
#else	//int、double、char指针、struct student指针都是直接赋值
        * (p - 1) = *p;
#endif
    }

    L->length--;	//长度-1
    if (L->listsize> LIST_INIT_SIZE) {
        while (L->listsize > LIST_INIT_SIZE && L->listsize - L->length > 15)
            L->listsize -= LISTINCREMENT;
        ElemType* newbase = (ElemType*)realloc(L->elem,sizeof(ElemType)*(L->listsize));
        if (!newbase)
#if (__linux__)
            exit(LOVERFLOW);
#else 
            return LOVERFLOW;
#endif
        L->elem = newbase;
    }
 
    return OK;
}
Status	ListDelete2(sqlist* L,  ElemType cur_e,Status(*compare)(ElemType e1,ElemType e2))
{
    while (ListDelete1(L, cur_e, compare))
        ;
    return OK;
}
