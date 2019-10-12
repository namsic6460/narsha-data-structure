#include "header.h"

int main() {
	StaffData head;
	head.link = NULL;

	int y = 1;

	while (1) {
		fflush(stdin);
		controlScreen(&y);
		printf("\n\n");

		switch (y) {
		case 1:		//사원 등록
			insertNode(&head);
			break;
		case 2:		//사원 전체 조회
			seeAllNode(&head);
			break;
		case 3:		//사원 조회
			seeNode(&head);
			break;
		case 4:		//사원 해고
			deleteNode(&head);
			break;
		case 5:		//부서 이동
			changeDepartment(&head);
			break;
		case 6:		//종료
			printf("종료되었습니다");
			Sleep(SLEEP_TIME);
			printf("\n\n");
			return;
		}

		system("cls");
	}

	return 0;
}