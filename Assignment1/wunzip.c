#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) { //argc: 인자 개수, argv: 인자 배열
    if (argc < 2) { // 인자가 부족한 경우
        printf("wunzip: file1 [file2 ...]\n"); // 에러 메시지 출력
        return 1; // 지시 사항과 같이 1 반환
    }

    FILE *fp; // 파일 포인터, fopen을 담을 변수
    int count; // 카운터, 문자가 반복되는 횟수
    char c; // 반복된 문자

    for (int i = 1; i < argc; i++) {// 인자로 받은 파일들을 하나씩 처리
        fp = fopen(argv[i], "r"); // 인자로 받은 파일들을 하나씩 처리
        if (fp == NULL) {//열기 에러
            printf("wunzip: cannot open file\n"); //에러메시지 출력
            return 1; // 1반환해 에러 알림
        }

        while (fread(&count, sizeof(int), 1, fp) == 1) { // 압축 파일의 4바이트 하나씩 읽어나감. fread가 1을 반환하면 정상.
            fread(&c, sizeof(char), 1, fp); // 문자 하나 읽기
            for (int j = 0; j < count; j++) { // 해당 문자를 count번 출력하기
                fputc(c, stdout); // stdout으로 문자 출력
            }
        }
        fclose(fp); // 연 파일닫기
    }

    return 0;
}
