#define _CRT_SECURE_NO_WARNINGS
#define OK 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2
#define MAX_OPT_SIZE 10

#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef int Status;
typedef struct {
	int suit;
	int point;
}card, ElemType;
typedef struct Card {
	Card* prior;//从bottom指向bottom
	Card* next;//从top指向bottom
	ElemType card;
}Card, * Deck;
Deck deck;
//-------------------------------------------
//   prior  <-  bottom   Head top -> next
//-------------------------------------------
const char* suits[] = { "Spade","Heart","Club","Diamond","ERROR" };
const char* points[] = { "ERROR","A","2","3","4","5","6","7","8","9","10","J","Q","K" };

//创建链表，带头节点
Status InitDeck(Deck& L) {
	L = (Deck)malloc(sizeof(Deck));
	if (!L) {
		printf("OVERFLOW\n");
		return OVERFLOW;
	}
	L->prior = L->next = L;
	card data = { 4,0 };
	L->card = data;
	return OK;
}
//显示输出
Status PrintDeck(Deck& L) {
	//	printf("Start Print:\n");
	if (L->next == L)
		return ERROR;
	Card* p = L->next;
	while (p != L) {
		printf("%s %s\n", suits[p->card.suit], points[p->card.point]);
		p = p->next;
	}
	return OK;
}
//bottom侧插入
Status AppendCard(Deck& L, card in) {
	Card* p = (Card*)malloc(sizeof(Card));
	if (!p) {
		printf("OVERFLOW\n");
		return OVERFLOW;

	}
	p->card = in;
	p->next = L;
	p->prior = L->prior;
	L->prior->next = p;
	L->prior = p;
	return OK;
}
//top侧删除
Status PopCard(Deck& L) {
	if (L->next == L) {
		printf("NULL\n");
		return ERROR;
	}
	Card* p = L->next;
	L->next = L->next->next;
	L->next->prior = L;
	printf("%s %s\n", suits[p->card.suit], points[p->card.point]);
	free(p);
	return OK;
}
//反转
Status RevertDeck(Deck& L) {
	//PrintDeck(deck);
	Card* p = L, * temp;
	//	printf("Revert:from %s %s; %s %s; %s %s\n",suits[p->prior->card.suit],
	//				points[p->prior->card.point],suits[p->card.suit],
	//				points[p->card.point],suits[p->next->card.suit],
	//				points[p->next->card.point]);
	temp = p->next;
	p->next = p->prior;
	p->prior = temp;
	//printf("Revert:to %s %s; %s %s; %s %s\n",suits[p->prior->card.suit],
	//				points[p->prior->card.point],suits[p->card.suit],
	//				points[p->card.point],suits[p->next->card.suit],
	//				points[p->next->card.point]);
	p = p->prior;
	while (p != L) {
		temp = p->next;
		p->next = p->prior;
		p->prior = temp;
		p = p->prior;
	}
	//PrintDeck(deck);
	return OK;
}
Status Extract(Deck& L, int suit) {
	if (L->next == L)
		return ERROR;
	Deck sub;
	InitDeck(sub);//用于存储指定花色，从bottom侧插入，从小到大
	//		printf("search for suit %s\n",suits[suit]);
//	printf("search in :");
//	PrintDeck(L);
	for (int i = 1; i <= 13; i++) {
		//		printf("search in :");
			//	PrintDeck(L);
		//		printf("search for suit %s,point %s\n",suits[suit],points[i]);
		if (L->next == L)
			return OK;
		Card* p = L->next;
		while (p != L) {
			//printf("searching...\n");
			if (p->card.suit == suit && p->card.point == i) {
				//		printf("find one:\n");
			//		printf("%s %s\n",suits[p->card.suit],points[p->card.point]);
				p->prior->next = p->next;
				p->next->prior = p->prior;
				AppendCard(sub, p->card);
				Card* temp = p;
				p = p->next;
				free(temp);
				//			printf("to append:");
			//		PrintDeck(sub);

			}
			else
				p = p->next;
		}
	}
	if (sub->next != sub) {
		//		printf("search end,to append:\n");
		//			PrintDeck(sub);
		//			printf("\n");
		L->next->prior = sub->prior;
		sub->prior->next = L->next;
		L->next = sub->next;
		sub->next->prior = L;
	}
	free(sub);

	return OK;
}
int main()
{
	int n;
	char opt[MAX_OPT_SIZE];
	scanf("%d", &n);
	InitDeck(deck);
	for (int i = 0; i < n; i++) {
		scanf("%s", opt);
		//	printf("\nOPT:%s\n",opt);
		if (!strcmp(opt, "Pop"))
			PopCard(deck);
		else if (!strcmp(opt, "Append")) {
			int suit;
			int point;
			scanf("%s", opt);
			if (!strcmp(opt, "Spade"))
				suit = 0;
			else if (!strcmp(opt, "Heart"))
				suit = 1;
			else if (!strcmp(opt, "Club"))
				suit = 2;
			else if (!strcmp(opt, "Diamond"))
				suit = 3;
			scanf("%s", opt);
			if (!strcmp(opt, "A"))
				point = 1;
			else if (!strcmp(opt, "2"))
				point = 2;
			else if (!strcmp(opt, "3"))
				point = 3;
			else if (!strcmp(opt, "4"))
				point = 4;
			else if (!strcmp(opt, "5"))
				point = 5;
			else if (!strcmp(opt, "6"))
				point = 6;
			else if (!strcmp(opt, "7"))
				point = 7;
			else if (!strcmp(opt, "8"))
				point = 8;
			else if (!strcmp(opt, "9"))
				point = 9;
			else if (!strcmp(opt, "10"))
				point = 10;
			else if (!strcmp(opt, "J"))
				point = 11;
			else if (!strcmp(opt, "Q"))
				point = 12;
			else if (!strcmp(opt, "K"))
				point = 13;
			card in{ suit,point };
			AppendCard(deck, in);
		}
		else if (!strcmp(opt, "Revert"))
			RevertDeck(deck);
		else if (!strcmp(opt, "Extract")) {
			int suit;
			scanf("%s", opt);
			if (!strcmp(opt, "Spade"))
				suit = 0;
			else if (!strcmp(opt, "Heart"))
				suit = 1;
			else if (!strcmp(opt, "Club"))
				suit = 2;
			else if (!strcmp(opt, "Diamond"))
				suit = 3;
			Extract(deck, suit);
		}
	}
	PrintDeck(deck);
	return 0;
}

