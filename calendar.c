#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int month; //월을 입력 받음
int day; //일을 입력 받음
int lastday[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //월별 마지막 일

typedef struct { //월별 영어 이름을 담아줄 구조체
	char eng[20];
	int num;
}Month;

typedef struct {
	int hour;
	int min;
	char todo[1000];
}Todo;

Todo todos[365][5]; //365일마다 최대 5개의 일정 등록할 수 있는 구조체 배열

Month months[12] = { //월별 영어 단어
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
	int choice; //메뉴 선택

	printf("\n            [ 2022년 일정 관리 ]           \n");
	printf("\n[1]일정등록 [2]일정취소 [3]일정확인 [4]종료\n\n");

	while (1) {
		printf("메뉴를 선택하세요.(1-4): ");
		scanf("%d", &choice);

		while (getchar() != '\n') break; //문자 입력 시 오류 차단

		switch (choice) {
		case 1:
			showCalendar(); //선택한 달의 달력을 띄워주는 함수
			addTodo(); //일정을 등록하는 함수
			sort(); //일정을 시간 단위로 오름차순 정렬해줌
			break;
		case 2:
			showTodo(); //선택한 날짜의 일정을 띄워주는 함수
			delTodo(); //일정을 취소하는 함수
			break;
		case 3:
			showTodo(); //선택한 날짜의 일정을 띄워주는 함수
			break;
		case 4:
			printf("일정 관리 프로그램을 종료합니다.");
			return 0;
		default:
			printf("잘못 입력하셨습니다. ");
			break;
		}
	}
	return 0;
}

int showCalendar() { //선택한 달의 달력을 띄워주는 함수
	int dayStart, sum = 0; //선택한 달의 첫 날이 몇요일인지 판단

	printf("원하는 달을 입력하세요.(1-12월): ");
	scanf("%d", &month);

	if (month < 1 || month > 12) { //달은 1~12월까지 선택
		printf("잘못 입력하셨습니다. ");
		showCalendar(); //재귀함수 호출
	}
	else {
		for (int i = 0; i < month - 1; i++) { //선택한 달의 전날까지의 일 수의 모든 합
			sum = sum + lastday[i];
		}

		dayStart = sum % 7; //선택한 달이 몇번째 요일부터 시작하는지

		printf("\n\t < %s >\n\n", months[month - 1].eng); //선택한 달의 영어 단어 출력
		printf(" SUN MON TUE WED THU FRI SAT\n");

		if (dayStart == 0) { //1월과 10월
			for (int j = 0; j < 6; j++) {
				printf("    ");
			}
		}
		else { //1월과 10월을 제외한 달
			for (int i = 0; i < dayStart - 1; i++) {
				printf("    ");
			}
		}

		for (int i = 1; i <= lastday[month - 1]; i++) { //1일부터 순서대로 찍어줌
			printf("%4d", i);
			if ((((dayStart - 1) + i) % 7) == 0) { //한 주가 모두 채워지면 다음 줄로 이동
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}

int showTodo() { //선택한 날의 일정을 보여주는 함수
	int count = 0; //공백인 일정의 수 저장
	int j = 1; //일정 번호

	showCalendar(); //선택한 달의 달력 띄워주는 함수
	sort(); //일정 시간 단위로 정렬해 주는 함수

	printf("날짜를 선택하세요.(1-%d일): ", lastday[month - 1]);
	scanf("%d", &day);

	if (day > lastday[month - 1] || day < 1) { //1부터 달의 마지막 날에 포함 안 되는 경우
		printf("잘못 입력하셨습니다. ");
		showCalendar();// 선택한 달의 달력 띄워주는 함수
	}
	else {
		printf("\n[ 2022년 %d월 %d일 일정 ]\n\n", month, day);

		for (int i = 0; i < 5; i++) {
			if (strlen(todos[lastday[month - 2] + (day - 1)][i].todo) != 0) { //일정이 비어있지 않다면 출력
				printf("%d) %02d:%02d %s\n", j, todos[lastday[month - 2] + (day - 1)][i].hour, todos[lastday[month - 2] + (day - 1)][i].min, todos[lastday[month - 2] + (day - 1)][i].todo);
				//todos[lastday[month - 2] + (day - 1)][i]는 입력한 날이 365일 중에 며칠이 지났는지 구해줌
				j++; //일정을 하나 출력 했으니, 증감
			}
			else {
				count++; //일정이 비어있으면 1 증감
			}
		}

		if (count == 5) { //5개의 일정 목록이 모두 비어있음
			printf("등록된 일정이 없습니다.\n");
		}

		printf("\n");
	}
	
	return 0;
}

int addTodo() { //일정을 등록하는 함수
	printf("일정을 추가할 날짜를 선택하세요.(1-%d일): ", lastday[month - 1]);
	scanf("%d", &day);

	if (day > lastday[month - 1] || day < 1) { //1부터 달의 마지막 날에 포함 안 되는 경우
		printf("잘못 입력하셨습니다. ");
		addTodo(); //재귀함수 호출
	}
	else {
		getTodoNum(month, day); //등록할 일정의 개수를 받는 함수
	}
	return 0;
}
 
int getTodoNum(int month, int day) { //등록할 일정의 개수를 받는 함수
	int regist = 0; //비어있는 일정의 수
	int count = 0; // 등록할 일정의 개수 받음

	for (int i = 0; i < 5; i++) {
		if (strlen(todos[lastday[month - 2] + (day - 1)][i].todo) == 0) { //일정이 비어있다면
			regist++; //조건에 만족하면 1 증감
		}
	}

	if (regist == 0) { //5개의 일정이 모두 등록되어 있음
		printf("일정 5개를 모두 등록했습니다. 새로 등록하기 위해선 기존 일정을 삭제해야 합니다.\n");
	}
	else
	{
		again:
		printf("등록할 일정의 개수를 입력하세요.(등록 가능한 수: %d): ", regist); //비어있는 일정의 수
		scanf("%d", &count);

		while (getchar() != '\n') break; //문자열 입력되면 멈춤

		if (count > regist || count < 1) {
			goto again; //again: 위치로 돌아감
		}

		getTime(count); //일정의 시간을 입력받는 함수
	}
	
	return 0;
}

int getTime(int count) { //일정의 시간을 입력받는 함수
	char input[7]; //시간 입력 받음

	for (int i = 0; i < count; i++) {
		again:
		printf("시간을 입력하세요.[예) 13:30]: ");
		scanf("%s", input);

		if (correct_str(input, day, i)) { //input이 시간 형태가 맞는지 판별, 1이면 실행
			printf("등록할 일정을 작성하세요. : ");
			scanf(" %[^\n]", todos[lastday[month - 2] + (day - 1)][i].todo); //공백이 포함된 문자열을 받아줌
			printf("2022년 %d월 %d일 %d시 %d분: %s 일정이 추가 되었습니다.\n\n", month, day, todos[lastday[month - 2] + (day - 1)][i].hour, todos[lastday[month - 2] + (day - 1)][i].min, todos[lastday[month - 2] + (day - 1)][i].todo);
		}
		else {
			printf("잘못 입력하셨습니다. ");
			goto again; //again: 으로 돌아감
		}
		
	}

	return 0;
}

int correct_str(char* time, int day, int i) { //입력받은 문자열 시간이 맞는지 판별하는 함수
	if (strchr(time, ':') == NULL) { //':'이 포함되어 있지 않으면 0 반환
		return 0;
	}

	int str = strlen(time); //time의 길이 str에 넣어줌

	if (str != 5) { //입력 받은 값의 길이가 5가 넘으면 0 반환
		return 0;
	}

	todos[lastday[month - 2] + (day - 1)][i].hour = atoi(strtok(time, ":")); //':' 전의 값은 해당 날의 hour에 저장
	todos[lastday[month - 2] + (day - 1)][i].min = atoi(strtok(NULL, ":")); //':' 뒤의 값은 해당 날의 min으로 저장

	if (todos[lastday[month - 2] + (day - 1)][i].hour > 24 || todos[lastday[month - 2] + (day - 1)][i].hour < 0) {
		//받은 hour이  0 반환
		return 0;
	}

	if (todos[lastday[month - 2] + (day - 1)][i].hour == 0) { //hour이 0이면 24로 바꿔줌
		todos[lastday[month - 2] + (day - 1)][i].hour = 24;
	}

	if (todos[lastday[month - 2] + (day - 1)][i].hour == 24 && todos[lastday[month - 2] + (day - 1)][i].min != 0) {
		//받은 hour이 24인데 min이 0이 아닐 시, 0 반환
		return 0;
	}

	if (todos[lastday[month - 2] + (day - 1)][i].min > 59 || todos[lastday[month - 2] + (day - 1)][i].min < 0) {
		//받은 hour이 0부터 59에 포함되지 않으면 0 반환
		return 0;
	}

	return 1; //모든 것에 포함되지 않는다면 1 반환
}

int delTodo() { //일정을 삭제하는 함수
	int num, count = 0;

	for (int i = 0; i < 5; i++) { 
		if (strlen(todos[lastday[month - 2] + (day - 1)][i].todo) == 0) {
			count++; //일정이 비어있으면 1 증감
		}
	}

	if (count == 5) { //모든 일정이 비어있으면 0 반환
		return 0;
	}
	
	again:
	printf("삭제하고 싶은 일정의 번호를 입력하세요.: ");
	scanf("%d", &num);

	if (num > 5 - count + 1 || num < 1) { //5개 중에 비어있는 일정 제외한 만큼의 숫자만 입력 가능
		printf("잘못 입력하셨습니다. ");
		goto again; //again: 으로 돌아감
	}
	else { //비어있는 일정에 선택한 번호를 더하고, -1을 해주어서 배열의 몇번째 열인지 알아낼 수 있음
		printf("2022년 %d월 %d일 %s(이)가 취소 되었습니다.\n\n", month, day, todos[lastday[month - 2] + (day - 1)][count + num - 1].todo);
		strcpy(todos[lastday[month - 2] + (day - 1)][count + num - 1].todo, ""); //todo 비워줌
		todos[lastday[month - 2] + (day - 1)][count + num - 1].hour = 0; //hour에 0 대입
		todos[lastday[month - 2] + (day - 1)][count + num - 1].min = 0; //min에 0 대입
	}

	return 0;
}

int sort() { //선택한 날의 일정을 시간 단위로 오름차순 정렬해 주는 함수
	Todo temp;
	int k = 1, j = 0;

	for (int i = 0; i < 365; i++) { //365일만큼 반복
		for (k; k < 5; k++) { //일정 순서대로 비교
			for (j; j < 4; j++) { //몇번째 일정인지
				if (todos[i][j].hour > todos[i][j + 1].hour) { 
					//다음 요소보다 hour이 크면 둘의 위치 바꿈
					temp = todos[i][j + 1];
					todos[i][j + 1] = todos[i][j];
					todos[i][j] = temp;
				}
				else if (todos[i][j].min > todos[i][j + 1].min) {
					//다음 요소보다 min이 크면 둘의 위치 바꿈
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