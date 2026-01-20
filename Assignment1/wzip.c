#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { // 인자가 부족한 경우
        printf("wzip: file1 [file2 ...]\n"); // 에러 메시지 출력
        return 1; // 지시 사항과 같이 1 반환
    }

    FILE *fp; // 파일 포인터, fopen을 받음
    int count = 0; // 현재 문자가 얼마나 반복되는지
    int c, prev = EOF; // 각각, 새로 읽은 문자와 직전에 읽은 문자. EOF는 초기 값으로 아무 문자도 없음.

    for (int i = 1; i < argc; i++) { // 인자로 받은 파일을 하나씩 처리해나감
        fp = fopen(argv[i], "r"); // 현 파일을 READ 모드로 열음
        if (fp == NULL) { // 에러처리(열기 실패)
            printf("wzip: cannot open file\n"); // 에러메시지
            return 1; // 1반환하여 에러 알림
        }

        while ((c = fgetc(fp)) != EOF) { // 한글자씩 읽어가며 EOF 체킹
            if (c == prev) { // 만약 이전 문자와 같다면 count++;을 통해 문자가 반복됨을 기록
                count++;
            } else {
                if (prev != EOF) {
                    fwrite(&count, sizeof(int), 1, stdout); // 이전 문자와 다르다면 반복횟수를 4바이트 정수 int로 출력
                    fwrite(&prev, sizeof(char), 1, stdout); // 반복에 해당하는 문자를 1바이트 char로 출력
                }
                prev = c; // 이전 문자를 현 문자로 갱신
                count = 1; // 카운트 초기화 필요
            }
        }
        fclose(fp); // 연 파일 닫기
    }

    if (prev != EOF) { // 마지막 문자 그룹
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }

    return 0;
}
