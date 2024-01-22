#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#define PLAYERS 10
#define LEFT 97 //'a'
#define RIGHT 100 //'d'
#define UP 119 //'w'
#define DOWN 115 //'s'

// �÷��̾� ������ ���� ����ü
typedef struct {
	char name[50];
	int score;
	int rank;
} Player;

Player players[PLAYERS];
int numPlayers = 0;
int score = 0; //����
int act; //������ üũ
int continueGame = 0; //Ŭ���� �� 4096����
char name[50];
int rankView = 0; //��ŷ�ٽú��� üũ

int board[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

void draw(void); //������ ����
void rand_num(void); //2or4 ���� ����
void after_act(void);//����Ű �Է� �� ��������
void left(void);
void right(void);
void up(void);
void down(void);
void ending_credits();
int game_end(Player players[], int numPlayers);
void assignRanks(Player players[], int numPlayers);
void displayLeaderboard(Player players[], int numPlayers);
void saveScore(char name[50], int score);
void get_user_info(char* name);

void game_start(void) {
	int key;
	rand_num(); rand_num();
	draw();

	while (1) {
		fflush(stdout);
		key = _getch();

		switch (key) {
		case LEFT: left();	//a
			break;

		case RIGHT: right();	//d
			break;

		case UP: up();	//w
			break;

		case DOWN: down();	//s
			break;

		default: act = 0;
			break;
		};

		if (act > 0) //act�� �ִ� ��쿡��
			after_act();
	}
}

void left(void) {
	int i, j, k, moved = 0;
	act = 0;  //act �ʱ�ȭ

	for (i = 0; i < 4; i++) { //�������� Ÿ�� ����
		for (j = 0; j < 4; j++) {
			if (board[i][j] != 0) {
				for (k = j + 1; k < 4; k++) {
					if (board[i][k] == 0) continue; // �� Ÿ�� ��ŵ
					if (board[i][k] == board[i][j]) {
						// Ÿ�� ����
						board[i][j] *= 2;
						board[i][k] = 0;
						score += board[i][j];
						act = 1;
					}
					break; //�� �� �ϳ��� ���ո�
				}
			}
		}

		//Ÿ�� �ű��
		for (j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				for (k = j + 1; k < 4; k++) {
					if (board[i][k] != 0) {
						board[i][j] = board[i][k];
						board[i][k] = 0;
						act = 1;
						break;
					}
				}
			}
		}
	}

	if (act > 0) {
		rand_num();  // ��ĭ�� ���ο� ���� �߰�
		draw();      // �ٽ� ���� �׸���
	}
}
void right(void) {
	int i, j, k;
	act = 0;

	for (i = 0; i < 4; i++) {
		for (j = 3; j >= 0; j--) {
			if (board[i][j] != 0) {
				for (k = j - 1; k >= 0; k--) {
					if (board[i][k] == 0) continue;
					if (board[i][k] == board[i][j]) {
						board[i][j] *= 2;
						board[i][k] = 0;
						score += board[i][j];
						act = 1;
						break;
					}
					break;
				}
			}
		}

		for (j = 3; j >= 0; j--) {
			if (board[i][j] == 0) {
				for (k = j - 1; k >= 0; k--) {
					if (board[i][k] != 0) {
						board[i][j] = board[i][k];
						board[i][k] = 0;
						act = 1;
						break;
					}
				}
			}
		}
	}

	if (act > 0) {
		rand_num();
		draw();
	}
}
void up(void) {
	int i, j, k;
	act = 0;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 4; i++) {
			if (board[i][j] != 0) {
				for (k = i + 1; k < 4; k++) {
					if (board[k][j] == 0) continue;
					if (board[k][j] == board[i][j]) {
						board[i][j] *= 2;
						board[k][j] = 0;
						score += board[i][j];
						act = 1;
						break;
					}
					break;
				}
			}
		}

		for (i = 0; i < 4; i++) {
			if (board[i][j] == 0) {
				for (k = i + 1; k < 4; k++) {
					if (board[k][j] != 0) {
						board[i][j] = board[k][j];
						board[k][j] = 0;
						act = 1;
						break;
					}
				}
			}
		}
	}

	if (act > 0) {
		rand_num();
		draw();
	}
}
void down(void) {
	int i, j, k;
	act = 0;

	for (j = 0; j < 4; j++) {
		for (i = 3; i >= 0; i--) {
			if (board[i][j] != 0) {
				for (k = i - 1; k >= 0; k--) {
					if (board[k][j] == 0) continue;
					if (board[k][j] == board[i][j]) {
						board[i][j] *= 2;
						board[k][j] = 0;
						score += board[i][j];
						act = 1;
						break;
					}
					break;
				}
			}
		}

		for (i = 3; i >= 0; i--) {
			if (board[i][j] == 0) {
				for (k = i - 1; k >= 0; k--) {
					if (board[k][j] != 0) {
						board[i][j] = board[k][j];
						board[k][j] = 0;
						act = 1;
						break;
					}
				}
			}
		}
	}

	if (act > 0) {
		rand_num();
		draw();
	}
}

int check_game_over(void) {
	int i, j;
	for (i = 0; i < 4; i++) for (j = 0; j < 4; j++)
		if (board[i][j] == 0)
			return 0;
	for (i = 0; i < 3; i++) for (j = 0; j < 3; j++)
		if (board[i][j] == board[i + 1][j] || board[i][j] == board[i][j + 1])
			return 0;
	for (i = 0; i < 3; i++)
		if (board[i][3] == board[i + 1][3])
			return 0;
	for (j = 0; j < 3; j++)
		if (board[3][j] == board[3][j + 1])
			return 0;
	printf("Game Over...\n");
	saveScore(name, score);
	return 1;
}
int check_game_clear(void) {
	int i, j;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (continueGame == 0) {
				if (board[i][j] >= 2048) {
					printf("Game Clear!!\n");
					saveScore(name, score);
					return 1;
				}
			}
			else if (continueGame == 1) {
				if (board[i][j] >= 4096) {
					printf("Game Clear!!\n");
					saveScore(name, score);
					return 1;
				}
			}
		}
	}

	return 0;
}
void draw(void) {
	int i, j;
	system("cls");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == 0)
				printf("    .");
			else
				printf("%5d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("Score : %d \n", score);
	printf("���� �Է�Ű(w,a,s,d) \n");

}
void rand_num(void) {
	int i, j;
	int cnt;
	int* generator[16] = { 0 };

	for (i = 0, cnt = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				generator[cnt] = &board[i][j];
				cnt++;
			}
		}
	}

	if (cnt > 0) {
		*generator[rand() % cnt] = (rand() % 100 < 70) ? 2 : 4;
	}
}
void after_act(void) {
	rand_num();
	draw(); //���� ������Ʈ
	if (check_game_over()) // ���ӿ��� üũ
		game_end(players, numPlayers);
	if (check_game_clear()) {
		system("cls");
		printf("������������������������������������������������������\n");
		printf("��                                                                                                      ��\n");
		printf("��                   ���� Ŭ����! ����ؼ� �����Ͻ÷��� �̾� �ϱ� �޴��� �������ּ���.                  ��\n");
		printf("��                                                                                                      ��\n");
		printf("������������������������������������������������������\n");
		Sleep(2000);
		game_end(players, numPlayers);
	}
}

void assignRanks(Player players[], int numPlayers) {
	// ������ ���� �������� ����
	for (int i = 0; i < numPlayers - 1; i++) {
		for (int j = 0; j < numPlayers - i - 1; j++) {
			if (players[j].score < players[j + 1].score) {
				Player temp = players[j];
				players[j] = players[j + 1];
				players[j + 1] = temp;
			}
		}
	}

	// ���� �ο�
	players[0].rank = 1;
	for (int i = 1; i < numPlayers; i++) {
		if (players[i].score == players[i - 1].score) {
			players[i].rank = players[i - 1].rank;
		}
		else {
			players[i].rank = i + 1;
		}
	}

	// ������ ������ ���� ������� ���� ��ȣ ����
	for (int i = 0; i < numPlayers; i++) {
		for (int j = i + 1; j < numPlayers; j++) {
			if (players[i].score == players[j].score && players[i].rank == players[j].rank) {
				players[j].rank++;
			}
		}
	}
}
void read_file(Player players[], int numPlayers) {
	if (rankView == 0) {
		FILE* file = fopen("player_info.txt", "r");

		if (file != NULL) {
			while (fscanf(file, "%s %d", players[numPlayers].name, &players[numPlayers].score) != EOF) {
				numPlayers++;
			}

			// ���� �б� �Ϸ� �� ���� �ݱ�
			fclose(file);

			assignRanks(players, numPlayers);//����

			displayLeaderboard(players, numPlayers);// ����ǥ ���
		}
		else {
			printf("������ �� �� �����ϴ�.");
		}
	}
	else if (rankView == 1) {
		displayLeaderboard(players, numPlayers);
	}
}
void displayLeaderboard(Player players[], int numPlayers) {

	char i;

	printf("\n=================== ����ǥ ===================\n");
	printf(" ���� | �̸�              |      ����  \n");

	// ���Ͽ��� �÷��̾� ������ ������� �о� ����ǥ�� ���
	for (int rank = 0; rank < numPlayers; rank++) {
		printf("%4d  | %-17s |      %d\n", rank + 1, players[rank].name, players[rank].score);
	}

	printf("=============================================\n");



	printf("�޴�â���� ���ư��ðڽ��ϱ�? Y\n������ �����Ͻðڽ��ϱ�? N\n");
	
	while (1) {

		getchar();

		scanf_s("%c", &i);

		if (i == 'Y' || i == 'y') {
			rankView = 1;
			game_end(players, numPlayers);
			break;
		}
		else if (i == 'N' || i == 'n') {
			ending_credits();
			break;
		}
		else {
			printf("�ٽ� �Է����ּ���");
			getchar();
		}
	}
}

void saveScore(char name[50], int score) {
	FILE* file = fopen("player_info.txt", "a"); // �߰� ����, �ؿ������� �̾ �ۼ�

	if (file != NULL) {
		fprintf(file, "%s %d\n", name, score); // ���Ͽ� ���� ���
		fclose(file); // ���� �ݱ�
	}
	else {
		printf("������ �� �� �����ϴ�.\n");
	}
}


int game_end(Player players[], int numPlayers) {


	int choice;

	while (1)
	{
		system("cls");

		printf("������������������������������������������������������\n");
		printf("��                                                                                                      ��\n");
		printf("��                                                                                                      ��\n");
		printf("��                                            ���� : %d                                                 ��\n", score);
		printf("��                                                                                                      ��\n");
		printf("��                                                                                                      ��\n");
		printf("��                              1. ����  �ϱ�           2 . �̾�  �ϱ�                                  ��\n");
		printf("��                                                                                                      ��\n");
		printf("��                                                                                                      ��\n");
		printf("��                              3. ��ŷ  ����           4 . ����  ����                                  ��\n");
		printf("��                                                                                                      ��\n");
		printf("��                                                                                                      ��\n");
		printf("������������������������������������������������������");
		printf("\n\n");

		printf("                                       �޴��� �����Ͻÿ� : ");
		scanf_s("%d", &choice);


		if (choice >= 1 && choice <= 4) {
			break; // �ùٸ� ������ ������ ���� Ż��
		}
		else {
			printf("�ùٸ� ��ȣ�� �Է��ϼ���.\n");

			getchar();			//�Է� ���� �����
		}
	}

	switch (choice)
	{
	case 1:
		for (int i = 0; i < 4; i++) {			//���� �ʱ�ȭ
			for (int j = 0; j < 4; j++) {
				board[i][j] = 0;
			}
		}
		score = 0;
		rankView = 0;
		srand(time(NULL));
		get_user_info(name);
		game_start();
		break;

	case 2:
		if (check_game_over() == 1) {
			printf("���ӿ� �ٽ� �������ּ���");
			Sleep(2000);	//2�� ����
			ending_credits();
			break;
		}
		else if (continueGame == 1) {
			printf("\n                                   �� �̻� �÷����� �� �����ϴ�.\n\n");
			printf("                              ��ŷ ���� or ���� �ϱ� �޴��� �������ּ���.");
			break;
		}
		else if (check_game_clear() == 1) {
			continueGame = 1;
			game_start();
		}
		break;

	case 3:
		// ���â�Լ� �ҷ�����	
		system("cls");
		read_file(players, numPlayers);

		break;

	case 4:
		ending_credits();
		break;

	default:
		printf("�ùٸ� ��ȣ�� �Է��ϼ���.\n");
		break;
	}

	return 0;
}

void ending_credits() {
	system("cls");
	printf("\n\n\n\n");
	printf("���� : 2048 \n");
	printf("3�� : ������ ������ �缭�� ������\n\n");
	printf("�÷������ּż� �����մϴ�.");

	Sleep(1000);

	exit(0);
}

void get_user_info(char* name) {  //����ڷκ��� �̸��� �Է¹���
	printf("Enter your name: ");
	scanf("%s", name);
}

int main(void) {
	srand(time(NULL));
	get_user_info(name);
	game_start();

	read_file(players, numPlayers);

	// ���� ���� �� ��ŷ ǥ�ø� ���� game_end �Լ� ȣ��
	game_end(players, numPlayers);


	return 0;
}