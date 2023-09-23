/* 2254298 ������ ���� */


/* ----------------------------------------------------------------------------------

	 ���ļ����ܣ�
	1����ű� hanoi_main.cpp �и��ݲ˵�����ֵ���õĸ��˵����Ӧ��ִ�к���

	 ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------------------------------------------------- */
#include"90-01-b1-hanoi.h"
static int Top[3], Stack[3][10], speed, totalstep = 0;//Top�洢���Ǵ������λ��


/***************************************************************************
  �������ƣ�reload
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �������س�������,��������Ϊһ������
***************************************************************************/
extern void reload(void)
{
	char input;
	cout << endl;
	cout << "���س�������";
	while (1) {
		input = _getch();
		if (input == 13)
			break;
	}
	cct_cls();
	speed = 0;
	totalstep = 0;
	return;
}

/***************************************************************************
  �������ƣ�initializevariable
  ��    �ܣ�
  ���������
  �� �� ֵ��dst
  ˵    ��������inputnumber����������Щ������ֵ���ҳ�ʼ��Top��Stack,����Ӧ����ѭֻ�����������ʹ���ʱ����ջ�������ԭ��
***************************************************************************/
void initializevariable(char input, char* src, char* dst, char* tmp, int* level)
{
	int  i, j;
	//TODO:������
	//for (i = 0; i < 3; i++)
	//	cout << "������&" << Top[i];
	//������
	for (i = 0; i < 3; i++)
		Top[i] = 0;//����Top����
	for (i = 0; i < 3; i++)
		for (j = 0; j < 10; j++)
			Stack[i][j] = 0;//����Stack����
	cout << "�����뺺ŵ���Ĳ���(1-10)" << endl;
	while (1) {
		cin >> *level;
		if (*level > 0 && *level <= 10 && !cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
			break;
		}
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
		}
		cout << "�����뺺ŵ���Ĳ���(1-10)" << endl;
	}
	//TODO:������
	//for (i = 0; i < 3; i++)
	//	cout << "������#" << Top[i];
	//������
	cout << "��������ʼ��(A-C)" << endl;
	while (1) {
		cin >> *src;
		if ((*src == 'A' || *src == 'B' || *src == 'C' || *src == 'a' || *src == 'b' || *src == 'c') && !cin.rdstate()) {
			switch (*src) {
				case 'a':
					*src = 'A';
					break;
				case 'b':
					*src = 'B';
					break;
				case 'c':
					*src = 'C';
					break;
				default:
					break;
			}
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
			break;
		}
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
		}
		cout << "��������ʼ��(A-C)" << endl;
	}
	cout << "������Ŀ����(A-C)" << endl;
	while (1) {
		cin >> *dst;
		if ((*dst == 'A' || *dst == 'B' || *dst == 'C' || *dst == 'a' || *dst == 'b' || *dst == 'c') && !cin.rdstate()
			&& dst != src && dst != (src + 32)) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
			break;
		}
		else if (cin.rdstate()) {
			cin.clear();
			cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
		}
		if (*dst == *src || *dst == (*src + 32))
			cout << "Ŀ����(" << src << ")��������ʼ��(" << src << ")��ͬ" << endl;
		cout << "������Ŀ����(A-C)" << endl;
	}
	switch (*dst) {
		case 'a':
			*dst = 'A';
			break;
		case 'b':
			*dst = 'B';
			break;
		case 'c':
			*dst = 'C';
			break;
	}
	*tmp = 'A' + 'B' + 'C' - *src - *dst;
	//TODO:������
	//for (i = 0; i < 3; i++)
	//	cout << "������*" << Top[i];
	//������
	Top[*src - 'A'] = *level;
	for (i = 0; i < *level; i++)
		Stack[*src - 'A'][i] = *level - i;
	//TODO:������
	//for (i = 0; i < 3; i++)
	//	cout << "������" << Top[i];
	//������
	if (input == '4' || input == '8') {
		cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)" << endl;
		while (1) {
			cin >> speed;
			if (speed >= 0 && speed <= 5 && !cin.rdstate()) {
				cin.clear();
				cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
				break;
			}
			else if (cin.rdstate()) {
				cin.clear();
				cin.ignore(10000000, '\n');//ɾ������Ժ����ѭ��
			}
			cout << "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)";
		}
	}
	return;
}


/***************************************************************************
  �������ƣ�speedcontrol
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����������ʱ�ĺ���
***************************************************************************/
void speedcontrol()
{
	switch (speed) {
		case 0:
			while (_getch() != 13)
				;
			break;
		case 1:
			Sleep(speed1);
			break;
		case 2:
			Sleep(speed2);
			break;
		case 3:
			Sleep(speed3);
			break;
		case 4:
			Sleep(speed4);
			break;
		case 5:
			Sleep(speed5);
			break;
		case 6:
			Sleep(speed6);
			break;
	}
	return;
}

/***************************************************************************
�������ƣ�horizontal
��    �ܣ�
��������������ʼλ��,�����Ҫ���"��ʼ"��bool initialize==True
�� �� ֵ��
˵    �����������
***************************************************************************/
void horizontal(int xcoordinate, int ycoordinate, int level, char src, char dst, bool initialized)
{
	int i, tenflag = 0;

	cct_gotoxy(xcoordinate, ycoordinate);
	if (initialized)
		cout << "��ʼ:  ";
	else
		cout << "��" << setw(4) << totalstep << " ��( " << setw(2) << level << "#: " << src << "-->" << dst << ") ";
	cout << "A:";
	for (i = 0; i < Top[0]; i++) {
		if (Stack[0][i] == 10)
			tenflag = 1;
		cout << setw(2) << Stack[0][i];
	}
	cout << setw(2 * (10 - Top[0]) + 3);
	tenflag = 0;

	cout << "B:";
	for (i = 0; i < Top[1]; i++) {
		if (Stack[1][i] == 10)
			tenflag = 1;
		cout << setw(2) << Stack[1][i];
	}
	cout << setw(2 * (10 - Top[1]) + 3);

	cout << "C:";
	for (i = 0; i < Top[2]; i++) {
		if (Stack[2][i] == 10)
			tenflag = 1;
		cout << setw(2) << Stack[2][i];
	}
	cout << setw(2 * (10 - Top[2]) + 3) << " ";
	cout << endl;
}

/***************************************************************************
�������ƣ�vertical
��    �ܣ�
������������B��λ��,��Ҫ��ʾ��ʼ״̬ʱbool initialize=tru
�� �� ֵ��
˵    ������ֱ���
***************************************************************************/
void vertical(char src, char dst, int level, int xcoordinate, int ycoordinate, bool initialize)
{
	int i;
	if (initialize) {
		cct_gotoxy(xcoordinate - xcoodif - 2, ycoordinate - 1);
		cout << setfill('=') << setw(6 + 2 * xcoodif) << " ";
		cout << setfill(' ');
		cct_gotoxy(xcoordinate, ycoordinate);
		cout << "B";
		cct_gotoxy(xcoordinate - xcoodif, ycoordinate);
		cout << "A";
		cct_gotoxy(xcoordinate + xcoodif, ycoordinate);
		cout << "C";
		for (i = 1; i < level + 1; i++) {
			cct_gotoxy(xcoordinate - ('B' - src) * xcoodif - 1, ycoordinate - 1 - i);
			cout << setw(2) << level + 1 - i;

		}
		return;
	}
	cct_gotoxy(xcoordinate - ('B' - src) * xcoodif - 1, ycoordinate - Top[src - 'A'] - 2);
	cout << setw(2) << " ";
	cct_gotoxy(xcoordinate - ('B' - dst) * xcoodif - 1, ycoordinate - 1 - Top[dst - 'A']);
	//������
	//cout << "$";
	//������
	cout << setw(2) << Stack[src - 'A'][Top[src - 'A']];
	return;

}
/***************************************************************************
�������ƣ�plateMoving
��    �ܣ�
���������srclevel��sdtlevel�ֱ�����ʼ�����ͽ�������,size�����ӵĴ�С
�� �� ֵ��
˵    �����ƶ�����
***************************************************************************/
void plateMoving(char src, char dst, int srclevel, int dstlevel, int size)
{
	int i, color[10][2] = colorBoard, direction = dst - src;

	cct_gotoxy(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - srclevel + 1);
	//������
	//Sleep(10000);
	//������
	//������
	//cout << "������" <<"*"<<size-1;
	//������
	for (i = bmclycoo - srclevel; i >= bmclycoo - clht; i--) {

		cct_showch(mdclxcoo + (src - 'B') * clxcoodif - size, i, ' ', background, 2 * size + 1);
		//������
		if (i != bmclycoo - clht)
			cct_showch(mdclxcoo + (src - 'B') * clxcoodif, i, ' ', columnColor, 1);
		//����
		speedcontrol();
		cct_showch(mdclxcoo + (src - 'B') * clxcoodif - size, i - 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
		//����
		speedcontrol();
	}
	if (direction > 0) {
		for (i = mdclxcoo + (src - 'B') * clxcoodif - size; i < mdclxcoo + (dst - 'B') * clxcoodif - size; i++) {
			cct_showch(i, bmclycoo - clht - 1, ' ', background, 2 * size + 1);
			//������
			speedcontrol();
			cct_showch(i + 1, bmclycoo - clht - 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
			//����
			speedcontrol();
		}
	}
	else {
		for (i = mdclxcoo + (src - 'B') * clxcoodif - size; i > mdclxcoo + (dst - 'B') * clxcoodif - size; i--) {
			cct_showch(i, bmclycoo - clht - 1, ' ', background, 2 * size + 1);
			//������
			speedcontrol();
			cct_showch(i - 1, bmclycoo - clht - 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
			//����
			speedcontrol();
		}
	}


	for (i = bmclycoo - clht - 1; i < bmclycoo - dstlevel - 1; i++) {
		cct_showch(mdclxcoo + (dst - 'B') * clxcoodif - size, i, ' ', background, 2 * size + 1);
		//������
		if (i > bmclycoo - clht)
			cct_showch(mdclxcoo + (dst - 'B') * clxcoodif, i, ' ', columnColor, 1);
		//����
		speedcontrol();
		cct_showch(mdclxcoo + (dst - 'B') * clxcoodif - size, i + 1, ' ', color[size - 1][0], color[size - 1][1], 2 * size + 1);
		//����
		speedcontrol();
	}
	cct_setcolor(defaultColor);
	cct_gotoxy endcoo;
	return;
}


/***************************************************************************
  �������ƣ�column
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ���������������
***************************************************************************/
void column()
{
	int i, j;
	for (i = -1; i < 2; i++) {
		cct_showch(mdclxcoo + i * clxcoodif - clsgwid, bmclycoo, ' ', columnColor, 2 * clsgwid + 1);
		prolong
			for (j = 0; j < clht; j++) {
				cct_showch(mdclxcoo + i * clxcoodif, bmclycoo - j, ' ', columnColor, 1);
				prolong
			}
	}
	cct_setcolor(defaultColor);
	cct_gotoxy endcoo;
	return;
}

/***************************************************************************
  �������ƣ�plategenerator
  ��    �ܣ�
  �����������Ͳ����ӵ������Լ�����
  �� �� ֵ��
  ˵    ����������������
***************************************************************************/
void plategenerator(int xcoordinate, int ycoordinate, int level)
{
	int i, color[10][2] = colorBoard;
	for (i = 0; i < level; i++) {
		cct_showch(xcoordinate - (level - i), ycoordinate - i, ' ', color[level - i - 1][0], color[level - i - 1][1], 2 * (level - i) + 1);
		//������
		//cout << "������$" << color[level - i-1][0]<< color[level - i-1][1]<<level-i-1;
		//������
		prolong
	}
	cct_setcolor(defaultColor);
	cct_gotoxy endcoo;
	return;
}

/***************************************************************************
  �������ƣ�hanoiplus
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����������ŵ������Լ�ͳ�Ʋ����ĺ���
***************************************************************************/
void hanoiplus(int level, char src, char tmp, char dst, char inputnumber)
{
	int x, y;
	switch (inputnumber) {
		case'1':
			cout << level << "# " << src << arrow << dst << endl;
			break;
		case'2':
			totalstep++;
			cout << "��" << setw(4) << totalstep << " ��( " << setw(2) << level << "#: " << src << "-->" << dst << ")" << endl;
			break;
		case'3':
			cct_getxy(x, y);
			totalstep++;
			horizontal(x, y, level, src, dst, false);
			break;
		case '4':
			totalstep++;
			horizontal(htxcoo, htycoo, level, src, dst, false);
			vertical(src, dst, level, vtBx, vtBy, false);
			speedcontrol();
			break;
		case '7':
			totalstep++;
			if (totalstep == 1)
				plateMoving(src, dst, Top[src - 'A'] + 1, Top[dst - 'A'] - 1, Stack[dst - 'A'][Top[dst - 'A'] - 1]);
			break;
		case '8':
			if (speed == 6)
				while (_getch() != 13)
					;
			totalstep++;
			horizontal(htxcoo, htycoo + offset, level, src, dst, false);
			vertical(src, dst, level, vtBx, vtBy + offset, false);
			plateMoving(src, dst, Top[src - 'A'] + 1, Top[dst - 'A'] - 1, Stack[dst - 'A'][Top[dst - 'A'] - 1]);
			break;
	}
	return;
}


/***************************************************************************
  �������ƣ�hanoi
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������ŵ���ݹ麯��
***************************************************************************/
void hanoi(int level, char src, char tmp, char dst, char inputnumber)
{
	if (level == 1) {
		Stack[dst - 'A'][Top[dst - 'A']++] = Stack[src - 'A'][--Top[src - 'A']];
		hanoiplus(level, src, tmp, dst, inputnumber);
		//	num++;
		//	cout << "��" << setw(4) << num << " ��" << "(1#: " << src << arrow << dst << ")  ";
		return;
	}
	hanoi(level - 1, src, dst, tmp, inputnumber);
	Stack[dst - 'A'][Top[dst - 'A']++] = Stack[src - 'A'][--Top[src - 'A']];
	hanoiplus(level, src, tmp, dst, inputnumber);
	//num++;
	//cout << "��" << setw(4) << num << " ��" << "(" << temp << "#: " << src << arrow << dst << ")  ";
	hanoi(level - 1, tmp, src, dst, inputnumber);
	return;
}






/***************************************************************************
  �������ƣ�module4
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    �����ڲ�������ʾ(����+����)
***************************************************************************/
void module4(char src, char dst, char tmp, int level)
{
	cct_cls();
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << level << " �㣬��ʱ����Ϊ " << speed << endl;
	horizontal(htxcoo, htycoo, level, src, dst, true);
	vertical(src, dst, level, vtBx, vtBy, true);
	speedcontrol();
	hanoi(level, src, tmp, dst, '4');
	cct_gotoxy(endxcoo, endycoo);
	return;
}



/***************************************************************************
  �������ƣ�module6
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ͼ�ν�-Ԥ��-����ʼ���ϻ�n������
***************************************************************************/
void module6(char src, char dst, char tmp, int level)
{
	cct_cls();
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << level << " ��" << endl;
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	return;
} 

/***************************************************************************
  �������ƣ�module7
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ͼ�ν�-Ԥ��-��һ���ƶ�
***************************************************************************/
void module7(char src, char dst, char tmp, int level)
{
	speed = 4;
	cct_cls();
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << level << " ��" << endl;
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	hanoi(level, src, tmp, dst, '7');
	return;
}

/***************************************************************************
  �������ƣ�module8
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ͼ�ν�-�Զ��ƶ��汾
***************************************************************************/
void module8(char src, char dst, char tmp, int level)
{
	if (speed == 0)
		speed = 6;
	cct_cls();
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << level << " ��" << endl;
	horizontal(htxcoo, htycoo + offset, level, src, dst, true);
	vertical(src, dst, level, vtBx, vtBy + offset, true);
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	hanoi(level, src, tmp, dst, '8');
	return;
}

/***************************************************************************
  �������ƣ�module9
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ͼ�ν�-��Ϸ��
***************************************************************************/
void module9(char src, char dst, char tmp, int level)
{
	char temp;
	int i = 0, x, y;
	speed = 4;
	char  input[19] = { 0 };
	cct_cls();
	cout << "�� " << src << " �ƶ��� " << dst << "���� " << level << " ��" << endl;
	horizontal(htxcoo, htycoo + offset, level, src, dst, true);
	vertical(src, dst, level, vtBx, vtBy + offset, true);
	column();
	plategenerator(mdclxcoo + (src - 'B') * clxcoodif, bmclycoo - 1, level);
	cct_gotoxy(htxcoo, htycoo + offset + 2);
	cout << "�������ƶ�������(������ʽ��AC=A���˵������ƶ���C��Q=�˳�) ��";

	while (1) {
		temp = _getche();
		if (temp == 8) {
			cct_getxy(x, y);
			cct_gotoxy(x + 1, y);
		}
		if ((temp <= 32 || temp >= 127) && temp != 13)
			continue;
		input[i] = temp;
		i++;
		if ((input[0] == 'q' || input[0] == 'Q') && input[1] == 13) {
			cout << endl << endl << "��Ϸ��ֹ!!!!!" << endl;//����peek�Ƿ񷵻ػس����ж��Ƿ�Ϊ���һ�������ַ�
			break;
		}
		//if (i == 2) {
		//	for (i = 0; i < 3; i++)
		//		input[i] = 0;
		//	i = 0;
		//	}
			//������
			//for (int j = 0; j < 3; j++)
			//	cout << input[j]<<j;
			//cout << "������" << endl;
			//������

		else if (temp == 13 || i == 19) {
			if (input[0] == 'a' || input[0] == 'b' || input[0] == 'c' || input[0] == 'A' || input[0] == 'B' || input[0] == 'C') {
				switch (input[0]) {
					case'a':
						input[0] = 'A';
						break;
					case'b':
						input[0] = 'B';
						break;
					case'c':
						input[0] = 'C';
						break;
				}
				if ((input[1] == 'a' || input[1] == 'b' || input[1] == 'c' || input[1] == 'A' || input[1] == 'B' || input[1] == 'C') && input[1] != input[0] && input[1] != (input[0] - 'A' + 'a') && input[2] == 13) {
					//cout << "������" << cin.peek() << endl;
					switch (input[1]) {
						case'a':
							input[1] = 'A';
							break;
						case'b':
							input[1] = 'B';
							break;
						case'c':
							input[1] = 'C';
							break;
					}
					if (Top[input[0] - 'A'] == 0) {
						cout << endl << endl << "Դ��Ϊ��";
						Sleep(delay);
						cct_showch(0, htycoo + offset + 4, ' ', background, 20);
						cct_setcolor(defaultColor);
					}
					else if (Top[input[1] - 'A'] != 0 && Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1] < Stack[input[0] - 'A'][Top[input[0] - 'A'] - 1]) {//��·�߼�ȷ�����ᳬ�����鷶Χ
						cout << endl << endl << "����ѹС��,�Ƿ��ƶ�!";
						Sleep(delay);
						cct_showch(0, htycoo + offset + 4, ' ', background, 20);
						cct_setcolor(defaultColor);
					}
					else {
						//������
						//cout << Top[input[1] - 'A'] - 1 << "@" << Top[input[0] - 'A'] - 1;
						//������
						totalstep++;
						Stack[input[1] - 'A'][Top[input[1] - 'A']++] = Stack[input[0] - 'A'][--Top[input[0] - 'A']];

						horizontal(htxcoo, htycoo + offset, Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1], input[0], input[1], false);
						vertical(input[0], input[1], Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1], vtBx, vtBy + offset, false);
						plateMoving(input[0], input[1], Top[input[0] - 'A'] + 1, Top[input[1] - 'A'] - 1, Stack[input[1] - 'A'][Top[input[1] - 'A'] - 1]);
						if (level == Top[input[1] - 'A']) {
							cout << "��Ϸ����!!!";
							break;
						}
					}
				}
			}
			input[0] = 0;
			input[1] = 0;
			input[2] = 0;
			i = 0;
			cct_showch(htxcoo + 60, htycoo + offset + 2, ' ', background, 20);
			cct_gotoxy(htxcoo + 60, htycoo + offset + 2);
			cct_setcolor(defaultColor);

		}
	}
	//����ָ����
	//��ȷָ��:ab,aC,Bc,q,Q
	//��Чָ��:abc,ABC,QQ,qq,ֱ�ӻس�
	return;
}