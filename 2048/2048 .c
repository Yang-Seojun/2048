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

// 플레이어 정보를 담을 구조체
typedef struct {
	char name[50];
	int score;
	int rank;
} Player;

Player players[PLAYERS];
int numPlayers = 0;
int score = 0; //점수
int act; //움직임 체크
int continueGame = 0; //클리어 후 4096진행
char name[50];
int rankView = 0; //랭킹다시보기 체크

int board[4][4] = {
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

void draw(void); //게임판 생성
void rand_num(void); //2or4 랜덤 생성
void after_act(void);//방향키 입력 후 게임진행
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

		if (act > 0) //act가 있는 경우에만
			after_act();
	}
}

void left(void) {
	int i, j, k, moved = 0;
	act = 0;  //act 초기화

	for (i = 0; i < 4; i++) { //왼족으로 타일 병합
		for (j = 0; j < 4; j++) {
			if (board[i][j] != 0) {
				for (k = j + 1; k < 4; k++) {
					if (board[i][k] == 0) continue; // 빈 타일 스킵
					if (board[i][k] == board[i][j]) {
						// 타일 병합
						board[i][j] *= 2;
						board[i][k] = 0;
						score += board[i][j];
						act = 1;
					}
					break; //행 당 하나의 병합만
				}
			}
		}

		//타일 옮기기
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
		rand_num();  // 빈칸에 새로운 숫자 추가
		draw();      // 다시 보드 그리기
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
	printf("게임 입력키(w,a,s,d) \n");

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
	draw(); //보드 업데이트
	if (check_game_over()) // 게임오버 체크
		game_end(players, numPlayers);
	if (check_game_clear()) {
		system("cls");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                                                      ■\n");
		printf("■                   게임 클리어! 계속해서 진행하시려면 이어 하기 메뉴를 선택해주세요.                  ■\n");
		printf("■                                                                                                      ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		Sleep(2000);
		game_end(players, numPlayers);
	}
}

void assignRanks(Player players[], int numPlayers) {
	// 점수에 따라 내림차순 정렬
	for (int i = 0; i < numPlayers - 1; i++) {
		for (int j = 0; j < numPlayers - i - 1; j++) {
			if (players[j].score < players[j + 1].score) {
				Player temp = players[j];
				players[j] = players[j + 1];
				players[j + 1] = temp;
			}
		}
	}

	// 순위 부여
	players[0].rank = 1;
	for (int i = 1; i < numPlayers; i++) {
		if (players[i].score == players[i - 1].score) {
			players[i].rank = players[i - 1].rank;
		}
		else {
			players[i].rank = i + 1;
		}
	}

	// 동일한 점수를 가진 사람들의 순위 번호 조정
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

			// 파일 읽기 완료 후 파일 닫기
			fclose(file);

			assignRanks(players, numPlayers);//숫자

			displayLeaderboard(players, numPlayers);// 순위표 출력
		}
		else {
			printf("파일을 열 수 없습니다.");
		}
	}
	else if (rankView == 1) {
		displayLeaderboard(players, numPlayers);
	}
}
void displayLeaderboard(Player players[], int numPlayers) {

	char i;

	printf("\n=================== 순위표 ===================\n");
	printf(" 순위 | 이름              |      점수  \n");

	// 파일에서 플레이어 정보를 순서대로 읽어 순위표에 출력
	for (int rank = 0; rank < numPlayers; rank++) {
		printf("%4d  | %-17s |      %d\n", rank + 1, players[rank].name, players[rank].score);
	}

	printf("=============================================\n");



	printf("메뉴창으로 돌아가시겠습니까? Y\n게임을 종료하시겠습니까? N\n");
	
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
			printf("다시 입력해주세요");
			getchar();
		}
	}
}

void saveScore(char name[50], int score) {
	FILE* file = fopen("player_info.txt", "a"); // 추가 쓰기, 밑에서부터 이어서 작성

	if (file != NULL) {
		fprintf(file, "%s %d\n", name, score); // 파일에 점수 기록
		fclose(file); // 파일 닫기
	}
	else {
		printf("파일을 열 수 없습니다.\n");
	}
}


int game_end(Player players[], int numPlayers) {


	int choice;

	while (1)
	{
		system("cls");

		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("■                                                                                                      ■\n");
		printf("■                                                                                                      ■\n");
		printf("■                                            점수 : %d                                                 ■\n", score);
		printf("■                                                                                                      ■\n");
		printf("■                                                                                                      ■\n");
		printf("■                              1. 새로  하기           2 . 이어  하기                                  ■\n");
		printf("■                                                                                                      ■\n");
		printf("■                                                                                                      ■\n");
		printf("■                              3. 랭킹  보기           4 . 게임  종료                                  ■\n");
		printf("■                                                                                                      ■\n");
		printf("■                                                                                                      ■\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
		printf("\n\n");

		printf("                                       메뉴를 선택하시오 : ");
		scanf_s("%d", &choice);


		if (choice >= 1 && choice <= 4) {
			break; // 올바른 범위에 있으면 루프 탈출
		}
		else {
			printf("올바른 번호를 입력하세요.\n");

			getchar();			//입력 버퍼 지우기
		}
	}

	switch (choice)
	{
	case 1:
		for (int i = 0; i < 4; i++) {			//보드 초기화
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
			printf("게임에 다시 도전해주세요");
			Sleep(2000);	//2초 정지
			ending_credits();
			break;
		}
		else if (continueGame == 1) {
			printf("\n                                   더 이상 플레이할 수 없습니다.\n\n");
			printf("                              랭킹 보기 or 종료 하기 메뉴를 선택해주세요.");
			break;
		}
		else if (check_game_clear() == 1) {
			continueGame = 1;
			game_start();
		}
		break;

	case 3:
		// 결과창함수 불러오기	
		system("cls");
		read_file(players, numPlayers);

		break;

	case 4:
		ending_credits();
		break;

	default:
		printf("올바른 번호를 입력하세요.\n");
		break;
	}

	return 0;
}

void ending_credits() {
	system("cls");
	printf("\n\n\n\n");
	printf("게임 : 2048 \n");
	printf("3조 : 김지훈 신지훈 양서준 정여진\n\n");
	printf("플레이해주셔서 감사합니다.");

	Sleep(1000);

	exit(0);
}

void get_user_info(char* name) {  //사용자로부터 이름을 입력받음
	printf("Enter your name: ");
	scanf("%s", name);
}

int main(void) {
	srand(time(NULL));
	get_user_info(name);
	game_start();

	read_file(players, numPlayers);

	// 게임 종료 및 랭킹 표시를 위한 game_end 함수 호출
	game_end(players, numPlayers);


	return 0;
}