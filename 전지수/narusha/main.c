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
		case 1:		//��� ���
			insertNode(&head);
			break;
		case 2:		//��� ��ü ��ȸ
			seeAllNode(&head);
			break;
		case 3:		//��� ��ȸ
			seeNode(&head);
			break;
		case 4:		//��� �ذ�
			deleteNode(&head);
			break;
		case 5:		//�μ� �̵�
			changeDepartment(&head);
			break;
		case 6:		//����
			printf("����Ǿ����ϴ�");
			Sleep(SLEEP_TIME);
			printf("\n\n");
			return;
		}

		system("cls");
	}

	return 0;
}