#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int month; //���� �Է� ����
int day; //���� �Է� ����
int lastday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //���� ������ ��

typedef struct { //���� ���� �̸��� ����� ����ü
	char eng[20];
	int num;
}Month;

typedef struct {
	int hour;
	int min;
	char todo[1000];
}Todo;

Todo todos[365][5]; //365�ϸ��� �ִ� 5���� ���� ����� �� �ִ� ����ü �迭

Month months[12] = { //���� ���� �ܾ�
	{"January", 1},
	{"February", 2},
	{"March", 3},
	{"April", 4},
	{"May", 5},
	{"June", 6},
	{"July", 7},
	{"August", 8},
	{"September", 9},
	{"October", 10},
	{"November", 11},
	{"December", 12}
};

int main() {
	int choice; //�޴� ����

	printf("\n            [ 2022�� ���� ���� ]           \n");
	printf("\n[1]������� [2]������� [3]����Ȯ�� [4]����\n\n");

	while (1) {
		printf("�޴��� �����ϼ���.(1-4): ");
		scanf("%d", &choice);

		while (getchar() != '\n') break; //���� �Է� �� ���� ����

		switch (choice) {
		case 1:
			showCalendar(); //������ ���� �޷��� ����ִ� �Լ�
			addTodo(); //������ ����ϴ� �Լ�
			sort(); //������ �ð� ������ �������� ��������
			break;
		case 2:
			showTodo(); //������ ��¥�� ������ ����ִ� �Լ�
			delTodo(); //������ ����ϴ� �Լ�
			break;
		case 3:
			showTodo(); //������ ��¥�� ������ ����ִ� �Լ�
			break;
		case 4:
			printf("���� ���� ���α׷��� �����մϴ�.");
			return 0;
		default:
			printf("�߸� �Է��ϼ̽��ϴ�. ");
			break;
		}
	}
	return 0;
}

int showCalendar() { //������ ���� �޷��� ����ִ� �Լ�
	int dayStart, sum = 0; //������ ���� ù ���� ��������� �Ǵ�

	printf("���ϴ� ���� �Է��ϼ���.(1-12��): ");
	scanf("%d", &month);

	if (month < 1 || month > 12) { //���� 1~12������ ����
		printf("�߸� �Է��ϼ̽��ϴ�. ");
		showCalendar(); //����Լ� ȣ��
	}
	else {
		for (int i = 0; i < month - 1; i++) { //������ ���� ���������� �� ���� ��� ��
			sum = sum + lastday[i];
		}

		dayStart = sum % 7; //������ ���� ���° ���Ϻ��� �����ϴ���

		printf("\n\t < %s >\n\n", months[month - 1].eng); //������ ���� ���� �ܾ� ���
		printf(" SUN MON TUE WED THU FRI SAT\n");

		if (dayStart == 0) { //1���� 10��
			for (int j = 0; j < 6; j++) {
				printf("    ");
			}
		}
		else { //1���� 10���� ������ ��
			for (int i = 0; i < dayStart - 1; i++) {
				printf("    ");
			}
		}

		for (int i = 1; i <= lastday[month - 1]; i++) { //1�Ϻ��� ������� �����
			printf("%4d", i);
			if ((((dayStart - 1) + i) % 7) == 0) { //�� �ְ� ��� ä������ ���� �ٷ� �̵�
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int showTodo() { //������ ���� ������ �����ִ� �Լ�
	int count = 0; //������ ������ �� ����
	int j = 1; //���� ��ȣ

	showCalendar(); //������ ���� �޷� ����ִ� �Լ�
	sort(); //���� �ð� ������ ������ �ִ� �Լ�

	printf("��¥�� �����ϼ���.(1-%d��): ", lastday[month - 1]);
	scanf("%d", &day);

	if (day > lastday[month - 1] || day < 1) { //1���� ���� ������ ���� ���� �� �Ǵ� ���
		printf("�߸� �Է��ϼ̽��ϴ�. ");
		showCalendar();// ������ ���� �޷� ����ִ� �Լ�
	}
	else {
		printf("\n[ 2022�� %d�� %d�� ���� ]\n\n", month, day);

		for (int i = 0; i < 5; i++) {
			if (strlen(todos[lastday[month - 2] + (day - 1)][i].todo) != 0) { //������ ������� �ʴٸ� ���
				printf("%d) %02d:%02d %s\n", j, todos[lastday[month - 2] + (day - 1)][i].hour, todos[lastday[month - 2] + (day - 1)][i].min, todos[lastday[month - 2] + (day - 1)][i].todo);
				//todos[lastday[month - 2] + (day - 1)][i]�� �Է��� ���� 365�� �߿� ��ĥ�� �������� ������
				j++; //������ �ϳ� ��� ������, ����
			}
			else {
				count++; //������ ��������� 1 ����
			}
		}

		if (count == 5) { //5���� ���� ����� ��� �������
			printf("��ϵ� ������ �����ϴ�.\n");
		}

		printf("\n");
	}
	
	return 0;
}

int addTodo() { //������ ����ϴ� �Լ�
	printf("������ �߰��� ��¥�� �����ϼ���.(1-%d��): ", lastday[month - 1]);
	scanf("%d", &day);

	if (day > lastday[month - 1] || day < 1) { //1���� ���� ������ ���� ���� �� �Ǵ� ���
		printf("�߸� �Է��ϼ̽��ϴ�. ");
		addTodo(); //����Լ� ȣ��
	}
	else {
		getTodoNum(month, day); //����� ������ ������ �޴� �Լ�
	}
	return 0;
}
 
int getTodoNum(int month, int day) { //����� ������ ������ �޴� �Լ�
	int regist = 0; //����ִ� ������ ��
	int count = 0; // ����� ������ ���� ����

	for (int i = 0; i < 5; i++) {
		if (strlen(todos[lastday[month - 2] + (day - 1)][i].todo) == 0) { //������ ����ִٸ�
			regist++; //���ǿ� �����ϸ� 1 ����
		}
	}

	if (regist == 0) { //5���� ������ ��� ��ϵǾ� ����
		printf("���� 5���� ��� ����߽��ϴ�. ���� ����ϱ� ���ؼ� ���� ������ �����ؾ� �մϴ�.\n");
	}
	else
	{
		again:
		printf("����� ������ ������ �Է��ϼ���.(��� ������ ��: %d): ", regist); //����ִ� ������ ��
		scanf("%d", &count);

		while (getchar() != '\n') break; //���ڿ� �ԷµǸ� ����

		if (count > regist || count < 1) {
			goto again; //again: ��ġ�� ���ư�
		}

		getTime(count); //������ �ð��� �Է¹޴� �Լ�
	}
	
	return 0;
}

int getTime(int count) { //������ �ð��� �Է¹޴� �Լ�
	char input[7]; //�ð� �Է� ����

	for (int i = 0; i < count; i++) {
		again:
		printf("�ð��� �Է��ϼ���.[��) 13:30]: ");
		scanf("%s", input);

		if (correct_str(input, day, i)) { //input�� �ð� ���°� �´��� �Ǻ�, 1�̸� ����
			printf("����� ������ �ۼ��ϼ���. : ");
			scanf(" %[^\n]", todos[lastday[month - 2] + (day - 1)][i].todo); //������ ���Ե� ���ڿ��� �޾���
			printf("2022�� %d�� %d�� %d�� %d��: %s ������ �߰� �Ǿ����ϴ�.\n\n", month, day, todos[lastday[month - 2] + (day - 1)][i].hour, todos[lastday[month - 2] + (day - 1)][i].min, todos[lastday[month - 2] + (day - 1)][i].todo);
		}
		else {
			printf("�߸� �Է��ϼ̽��ϴ�. ");
			goto again; //again: ���� ���ư�
		}
		
	}

	return 0;
}

int correct_str(char* time, int day, int i) { //�Է¹��� ���ڿ� �ð��� �´��� �Ǻ��ϴ� �Լ�
	if (strchr(time, ':') == NULL) { //':'�� ���ԵǾ� ���� ������ 0 ��ȯ
		return 0;
	}

	int str = strlen(time); //time�� ���� str�� �־���

	if (str != 5) { //�Է� ���� ���� ���̰� 5�� ������ 0 ��ȯ
		return 0;
	}

	todos[lastday[month - 2] + (day - 1)][i].hour = atoi(strtok(time, ":")); //':' ���� ���� �ش� ���� hour�� ����
	todos[lastday[month - 2] + (day - 1)][i].min = atoi(strtok(NULL, ":")); //':' ���� ���� �ش� ���� min���� ����

	if (todos[lastday[month - 2] + (day - 1)][i].hour > 24 || todos[lastday[month - 2] + (day - 1)][i].hour < 0) {
		//���� hour��  0 ��ȯ
		return 0;
	}

	if (todos[lastday[month - 2] + (day - 1)][i].hour == 0) { //hour�� 0�̸� 24�� �ٲ���
		todos[lastday[month - 2] + (day - 1)][i].hour = 24;
	}

	if (todos[lastday[month - 2] + (day - 1)][i].hour == 24 && todos[lastday[month - 2] + (day - 1)][i].min != 0) {
		//���� hour�� 24�ε� min�� 0�� �ƴ� ��, 0 ��ȯ
		return 0;
	}

	if (todos[lastday[month - 2] + (day - 1)][i].min > 59 || todos[lastday[month - 2] + (day - 1)][i].min < 0) {
		//���� hour�� 0���� 59�� ���Ե��� ������ 0 ��ȯ
		return 0;
	}

	return 1; //��� �Ϳ� ���Ե��� �ʴ´ٸ� 1 ��ȯ
}

int delTodo() { //������ �����ϴ� �Լ�
	int num, count = 0;

	for (int i = 0; i < 5; i++) { 
		if (strlen(todos[lastday[month - 2] + (day - 1)][i].todo) == 0) {
			count++; //������ ��������� 1 ����
		}
	}

	if (count == 5) { //��� ������ ��������� 0 ��ȯ
		return 0;
	}
	
	again:
	printf("�����ϰ� ���� ������ ��ȣ�� �Է��ϼ���.: ");
	scanf("%d", &num);

	if (num > 5 - count + 1 || num < 1) { //5�� �߿� ����ִ� ���� ������ ��ŭ�� ���ڸ� �Է� ����
		printf("�߸� �Է��ϼ̽��ϴ�. ");
		goto again; //again: ���� ���ư�
	}
	else { //����ִ� ������ ������ ��ȣ�� ���ϰ�, -1�� ���־ �迭�� ���° ������ �˾Ƴ� �� ����
		printf("2022�� %d�� %d�� %s(��)�� ��� �Ǿ����ϴ�.\n\n", month, day, todos[lastday[month - 2] + (day - 1)][count + num - 1].todo);
		strcpy(todos[lastday[month - 2] + (day - 1)][count + num - 1].todo, ""); //todo �����
		todos[lastday[month - 2] + (day - 1)][count + num - 1].hour = 0; //hour�� 0 ����
		todos[lastday[month - 2] + (day - 1)][count + num - 1].min = 0; //min�� 0 ����
	}

	return 0;
}

int sort() { //������ ���� ������ �ð� ������ �������� ������ �ִ� �Լ�
	Todo temp;
	int k = 1, j = 0;

	for (int i = 0; i < 365; i++) { //365�ϸ�ŭ �ݺ�
		for (k; k < 5; k++) { //���� ������� ��
			for (j; j < 4; j++) { //���° ��������
				if (todos[i][j].hour > todos[i][j + 1].hour) { 
					//���� ��Һ��� hour�� ũ�� ���� ��ġ �ٲ�
					temp = todos[i][j + 1];
					todos[i][j + 1] = todos[i][j];
					todos[i][j] = temp;
				}
				else if (todos[i][j].min > todos[i][j + 1].min) {
					//���� ��Һ��� min�� ũ�� ���� ��ġ �ٲ�
					temp = todos[i][j + 1];
					todos[i][j + 1] = todos[i][j];
					todos[i][j] = temp;
				}
			}
			j = 0;
		}
		k = 0;
	}
	return 0;
}