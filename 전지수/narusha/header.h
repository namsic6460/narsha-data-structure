#pragma once
#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"conio_copy.h"

#pragma warning(disable: 4996)
#define _CRT_NO_SECURE_WARNINGS

#define ARROW 224
#define UP_ASCII 72
#define DOWN_ASCII 80
#define ENTER_ASCII 13
#define UP 1
#define DOWN 2
#define ENTER 3
#define SLEEP_TIME 2000

typedef enum _Department {
	Personnel_Team = 1,
	Development_Team,
	Design_Team
} Department;

typedef struct _StaffData {
	int number;
	char name[30];
	char phone_number[15];
	Department department;
	char address[100];
	char employed_date[18]; //yyyy�� mm�� dd��
	struct _StaffData *link;
} StaffData;


int inputFunc() {
	int input;
	while (1) {
		input = getch();
		fflush(stdin);

		if (input == ARROW) {
			input = getch();
			fflush(stdin);

			if (input == UP_ASCII)
				return UP;
			else if (input == DOWN_ASCII)
				return DOWN;
		}
		else if (input == ENTER_ASCII)
			return ENTER;
	}
}

void printMenu(int y) {
	int already_print = 0;

	printf("---------------------\n");

	for (int j = 1; j <= 6; j++) {
		if (j == y && already_print == 0) {
			printf("��");
			already_print = 1;
		}
		else
			printf("��");

		switch (j) {
		case 1:
			printf("     ��� ���\n");
			break;
		case 2:
			printf("   ��� ��ü ��ȸ\n");
			break;
		case 3:
			printf("     ��� ��ȸ\n");
			break;
		case 4:
			printf("     ��� �ذ�\n");
			break;
		case 5:
			printf("     �μ� �̵�\n");
			break;
		case 6:
			printf("        ����\n");
		}
	}
	printf("---------------------");
}

void controlScreen(int *y) {
	int input;
	while (1) {
		system("cls");

		printMenu(*y);

		input = inputFunc();

		switch (input) {
		case UP:
			*y = *y - 1;
			*y = *y == 0 ? 6 : *y;
			break;
		case DOWN:
			*y = *y + 1;
			*y = *y == 7 ? 1 : *y;
			break;
		case ENTER:
			return;
			break;
		}
	}
}

StaffData *createNode() {
	return (StaffData*)malloc(sizeof(StaffData));
}

int getNodeSize(StaffData * head) {
	int count = 0;

	while (1) {
		if (head->link == NULL)
			return count;

		head = head->link;
		count++;
	}
}

void seeAllNode(StaffData *head) {
	while (1) {
		if (head->link == NULL)
			break;
		head = head->link;

		printf("��� ��ȣ : %d\n��� �̸� : %s\n", head->number, head->name);
		printf("��� ��ȭ��ȣ : %s\n��� �μ� : ", head->phone_number);

		switch ((int)(head->department)) {
		case Personnel_Team:
			printf("�λ���");
			break;
		case Development_Team:
			printf("������");
			break;
		case Design_Team:
			printf("��������");
			break;
		};

		printf("\n��� �ּ� : %s\n��� �Ի��� : %s\n\n", head->address, head->employed_date);
	}

	printf("��� ��ü ���⸦ �����÷��� �ƹ�Ű�� �Է��ϼ���...");
	getch();
}

void insertNode(StaffData * head) {
	StaffData* newNode = createNode();
	StaffData* mem = head;
	int number_anti_error;
	int depart_mem;
	char anti_error[100];

	do {
		number_anti_error = 0;

		printf("�߰��� ����� ��ȣ : ");
		scanf("%s", anti_error);

		for (int i = 0; anti_error[i] != 0; i++) {
			if (anti_error[i] >= '0' && anti_error[i] <= '9')
				newNode->number = ((int)(anti_error[i])) - 48;

			else {
				printf("����� ��ȣ���� ���ڸ� �� �� �ֽ��ϴ�\n");
				number_anti_error = 1;
				break;
			}
		}

		if (number_anti_error == 1)
			continue;

		while (mem->link != NULL) {
			mem = mem->link;
			if (mem->number == newNode->number) {
				number_anti_error = 1;
				break;
			}
		}
	} while (number_anti_error == 1);

	printf("�߰��� ����� �̸� : ");
	scanf("%s", newNode->name);
	printf("�߰��� ����� ��ȭ��ȣ : ");
	scanf("%s", newNode->phone_number);
	printf("�߰��� ����� �μ�(%d : �λ���, %d : ������, %d : ��������) : ", Personnel_Team, Development_Team, Design_Team);
	scanf("%d", &depart_mem);

	while (depart_mem < 1 || depart_mem > 3) {
		fflush(stdin);
		printf("�μ��� 1~3 �� �Է� �����մϴ�\n");
		printf("�߰��� ����� �μ�(%d : �λ���, %d : ������, %d : ��������) : ", Personnel_Team, Development_Team, Design_Team);
		scanf("%d", &depart_mem);
		fflush(stdin);
	}
	newNode->department = (Department)(depart_mem);

	fgets(anti_error, 100, stdin);
	printf("�߰��� ����� �ּ� : ");
	fgets(newNode->address, 100, stdin);

	for (int i = 0; i <= (signed)strlen(newNode->address); i++) {
		if (newNode->address[i] == '\n')
			newNode->address[i] = 0;
	}

	printf("�߰��� ����� �Ի��� : ");
	fgets(newNode->employed_date, 18, stdin);

	for (int i = 0; i <= (signed)strlen(newNode->employed_date); i++) {
		if (newNode->employed_date[i] == '\n')
			newNode->employed_date[i] = 0;
	}

	while (1) {
		if (head->link == NULL)
			break;

		head = head->link;
	}

	head->link = newNode;
	newNode->link = NULL;

	printf("\n�߰� �Ϸ�");

	Sleep(SLEEP_TIME);
}

void deleteNode(StaffData *head) {
	int yn, input_number;
	StaffData* mem;

	printf("�ذ��� ����� ��� ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &input_number);

	do {
		printf("������ �ذ��Ͻðڽ��ϱ�?\n����(�� : 1, �ƴϿ� : 2) : ");
		scanf("%d", &yn);

		if (yn == 2) {
			printf("�ذ� ��ҵǾ����ϴ�");
			Sleep(SLEEP_TIME);
			return;
		}
	} while (yn != 1);

	if (head->link == NULL) {
		printf("�ش� ��� ��ȣ�� ����� ã�� �� �����ϴ�");
		Sleep(SLEEP_TIME);
		return;
	}
	
	while ((head->link)->number != input_number) {
		if (head->link == NULL) {
			printf("�ش� ��� ��ȣ�� ����� ã�� �� �����ϴ�");
			Sleep(SLEEP_TIME);
			return;
		}

		head = head->link;
	}

	mem = head->link;

	head->link = mem->link;
	free(mem);

	printf("�ذ� �Ϸ�Ǿ����ϴ�");
	Sleep(SLEEP_TIME);
	return;
}

void seeNode(StaffData *head) {
	int input_number;

	printf("��ȸ�� ����� ��� ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &input_number);

	while (head->number != input_number) {
		if (head->link == NULL) {
			printf("�ش� ��� ��ȣ�� ����� ã�� �� �����ϴ�");
			Sleep(SLEEP_TIME);
			return;
		}

		head = head->link;
	}

	printf("\n��� ��ȣ : %d\n��� �̸� : %s\n", head->number, head->name);
	printf("��� ��ȭ��ȣ : %s\n��� �μ� : ", head->phone_number);

	switch ((int)(head->department)) {
	case Personnel_Team:
		printf("�λ���");
		break;
	case Development_Team:
		printf("������");
		break;
	case Design_Team:
		printf("��������");
		break;
	};

	printf("\n��� �ּ� : %s\n��� �Ի��� : %s\n\n", head->address, head->employed_date);

	printf("��� ���⸦ �����÷��� �ƹ�Ű�� �Է��ϼ���...");
	getch();
}

void changeDepartment(StaffData *head) {
	int input_number;

	printf("��ȸ�� ����� ��� ��ȣ�� �Է��ϼ��� : ");
	scanf("%d", &input_number);

	while (head->number != input_number) {
		if (head->link == NULL) {
			printf("�ش� ��� ��ȣ�� ����� ã�� �� �����ϴ�");
			Sleep(SLEEP_TIME);
			return;
		}

		head = head->link;
	}

	printf("���� �ش� ����� �μ��� ");
	switch (head->department) {
	case Personnel_Team:
		printf("�λ���");
		break;
	case Development_Team:
		printf("������");
		break;
	case Design_Team:
		printf("��������");
		break;
	}
	printf(" �Դϴ�\n�ٲ� �μ��� �Է����ּ���(�λ��� : %d, ������ : %d, �������� : %d) : ", Personnel_Team, Development_Team, Design_Team);
	scanf("%d", &input_number);

	while (input_number < 1 || input_number > 3) {
		printf("�μ��� 1~3 �� �Է� �����մϴ�\n");
		printf("�Է� : ");
		scanf("%d", &input_number);
	}

	if (head->department == input_number) {
		printf("���� �μ��� �ٲ� �μ��� ���� �ٲ� �� �����ϴ�");
		Sleep(SLEEP_TIME);
		return;
	}
	
	head->department = input_number;
	printf("�μ� ������ �Ϸ�Ǿ����ϴ�");
	Sleep(SLEEP_TIME);
	return;
}