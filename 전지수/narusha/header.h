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
	char employed_date[18]; //yyyy년 mm월 dd일
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
			printf("■");
			already_print = 1;
		}
		else
			printf("□");

		switch (j) {
		case 1:
			printf("     사원 등록\n");
			break;
		case 2:
			printf("   사원 전체 조회\n");
			break;
		case 3:
			printf("     사원 조회\n");
			break;
		case 4:
			printf("     사원 해고\n");
			break;
		case 5:
			printf("     부서 이동\n");
			break;
		case 6:
			printf("        종료\n");
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

		printf("사원 번호 : %d\n사원 이름 : %s\n", head->number, head->name);
		printf("사원 전화번호 : %s\n사원 부서 : ", head->phone_number);

		switch ((int)(head->department)) {
		case Personnel_Team:
			printf("인사팀");
			break;
		case Development_Team:
			printf("개발팀");
			break;
		case Design_Team:
			printf("디자인팀");
			break;
		};

		printf("\n사원 주소 : %s\n사원 입사일 : %s\n\n", head->address, head->employed_date);
	}

	printf("사원 전체 보기를 끝내시려면 아무키나 입력하세요...");
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

		printf("추가할 사원의 번호 : ");
		scanf("%s", anti_error);

		for (int i = 0; anti_error[i] != 0; i++) {
			if (anti_error[i] >= '0' && anti_error[i] <= '9')
				newNode->number = ((int)(anti_error[i])) - 48;

			else {
				printf("사원의 번호에는 숫자만 들어갈 수 있습니다\n");
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

	printf("추가할 사원의 이름 : ");
	scanf("%s", newNode->name);
	printf("추가할 사원의 전화번호 : ");
	scanf("%s", newNode->phone_number);
	printf("추가할 사원의 부서(%d : 인사팀, %d : 개발팀, %d : 디자인팀) : ", Personnel_Team, Development_Team, Design_Team);
	scanf("%d", &depart_mem);

	while (depart_mem < 1 || depart_mem > 3) {
		fflush(stdin);
		printf("부서는 1~3 만 입력 가능합니다\n");
		printf("추가할 사원의 부서(%d : 인사팀, %d : 개발팀, %d : 디자인팀) : ", Personnel_Team, Development_Team, Design_Team);
		scanf("%d", &depart_mem);
		fflush(stdin);
	}
	newNode->department = (Department)(depart_mem);

	fgets(anti_error, 100, stdin);
	printf("추가할 사원의 주소 : ");
	fgets(newNode->address, 100, stdin);

	for (int i = 0; i <= (signed)strlen(newNode->address); i++) {
		if (newNode->address[i] == '\n')
			newNode->address[i] = 0;
	}

	printf("추가할 사원의 입사일 : ");
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

	printf("\n추가 완료");

	Sleep(SLEEP_TIME);
}

void deleteNode(StaffData *head) {
	int yn, input_number;
	StaffData* mem;

	printf("해고할 사원의 사원 번호를 입력하세요 : ");
	scanf("%d", &input_number);

	do {
		printf("정말로 해고하시겠습니까?\n선택(네 : 1, 아니요 : 2) : ");
		scanf("%d", &yn);

		if (yn == 2) {
			printf("해고가 취소되었습니다");
			Sleep(SLEEP_TIME);
			return;
		}
	} while (yn != 1);

	if (head->link == NULL) {
		printf("해당 사원 번호의 사원을 찾을 수 없습니다");
		Sleep(SLEEP_TIME);
		return;
	}
	
	while ((head->link)->number != input_number) {
		if (head->link == NULL) {
			printf("해당 사원 번호의 사원을 찾을 수 없습니다");
			Sleep(SLEEP_TIME);
			return;
		}

		head = head->link;
	}

	mem = head->link;

	head->link = mem->link;
	free(mem);

	printf("해고가 완료되었습니다");
	Sleep(SLEEP_TIME);
	return;
}

void seeNode(StaffData *head) {
	int input_number;

	printf("조회할 사원의 사원 번호를 입력하세요 : ");
	scanf("%d", &input_number);

	while (head->number != input_number) {
		if (head->link == NULL) {
			printf("해당 사원 번호의 사원을 찾을 수 없습니다");
			Sleep(SLEEP_TIME);
			return;
		}

		head = head->link;
	}

	printf("\n사원 번호 : %d\n사원 이름 : %s\n", head->number, head->name);
	printf("사원 전화번호 : %s\n사원 부서 : ", head->phone_number);

	switch ((int)(head->department)) {
	case Personnel_Team:
		printf("인사팀");
		break;
	case Development_Team:
		printf("개발팀");
		break;
	case Design_Team:
		printf("디자인팀");
		break;
	};

	printf("\n사원 주소 : %s\n사원 입사일 : %s\n\n", head->address, head->employed_date);

	printf("사원 보기를 끝내시려면 아무키나 입력하세요...");
	getch();
}

void changeDepartment(StaffData *head) {
	int input_number;

	printf("조회할 사원의 사원 번호를 입력하세요 : ");
	scanf("%d", &input_number);

	while (head->number != input_number) {
		if (head->link == NULL) {
			printf("해당 사원 번호의 사원을 찾을 수 없습니다");
			Sleep(SLEEP_TIME);
			return;
		}

		head = head->link;
	}

	printf("현재 해당 사원의 부서는 ");
	switch (head->department) {
	case Personnel_Team:
		printf("인사팀");
		break;
	case Development_Team:
		printf("개발팀");
		break;
	case Design_Team:
		printf("디자인팀");
		break;
	}
	printf(" 입니다\n바꿀 부서를 입력해주세요(인사팀 : %d, 개발팀 : %d, 디자인팀 : %d) : ", Personnel_Team, Development_Team, Design_Team);
	scanf("%d", &input_number);

	while (input_number < 1 || input_number > 3) {
		printf("부서는 1~3 만 입력 가능합니다\n");
		printf("입력 : ");
		scanf("%d", &input_number);
	}

	if (head->department == input_number) {
		printf("현재 부서와 바꿀 부서가 같아 바꿀 수 없습니다");
		Sleep(SLEEP_TIME);
		return;
	}
	
	head->department = input_number;
	printf("부서 변경이 완료되었습니다");
	Sleep(SLEEP_TIME);
	return;
}