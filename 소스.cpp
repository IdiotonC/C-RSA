#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <cstdio>


int p = 0, q = 0, e = 0, n = 0, d = 0, compare = 0;
int i = 0, j = 0;

int primenum(int n) { //�������� �Ҽ� �̾��ִ� �Լ� 
	int last = n / 2;

	for ( i = 2; i < last; i++) {
		if ((n % i) == 0) return 0;
		else return 1;
	}
}

void find_e( int *e ,int  compare) { // 1 < e < compare �̸鼭 e �� compare �� ���μ� 

	int count = 1;
	
	for (i = 2; i < compare; i++) {
		for ( j = 1; j <= i; j++) {
			if (i % j == 0 && compare % j == 0) count = j;
		}
		if (count == 1) {
			*e = i; break;
		}
		count = 1;
	}
	
}

void find_d(int *d) {
	for ( i = 2; i < compare; i++) {
		*d = e * i;
		if (*d % compare) break;
		else *d = 0;
	}
}

int main() {
	int encrypt = 1, word;
	char original_document[501];
	char decrypt[502] = { 0, };
	FILE* output, * input, * output2;
	output = fopen("C:\\RSA\\encrypt.txt", "w"); // w �� write ���� ���� �ذ���
	srand(time(NULL));

	while (1) {
		p = rand() % 1024;
		if (primenum(p)) break;
		else p = 0;
	}

	while (1) {
		q = rand() % 1024;
		if (primenum(q)) break;
		else q = 0;
	}

	n = p * q;
	compare = (p - 1) * (q - 1);
	find_e(&e, compare);
	find_d(&d);
	printf("%d %d %d %d %d %d", p,q ,n, e, d, compare);

	printf("��ȣȭ�� ������ 500�� �̳��� �Է��Ͻʽÿ� :");
	gets_s(original_document);  // a , s, i, a, n 

	for (  i = 0; i < strlen(original_document); i++) { // ��ȣ�� C = ��������^e mod n 
		for (int j = 0; j < e; j++) {
			encrypt *= (int)original_document[i];
			encrypt %= n;
		}
		fprintf(output, "%d\n", encrypt);
		encrypt = 1;
	}
	printf("��ȣȭ ������ encrypt.txt �� ����");
	fclose(output);
	fflush(stdin); // �Է� ���� ����� �Լ� 

	printf("��ȣȭ �ϴ� �� \n");
	getchar();

	input = fopen("C:\\RSA\\encrypt.txt", "r");
	output = fopen("C:\\RSA\\original.txt", "w");

	int count = 0;

	while (!feof(input))
	{
		fscanf_s(input, "%d\n", &word);
		for (j = 0; j < d; j++) {  // ��ȣȭ M = C^d mod n 
			encrypt *= word; 
			encrypt %= n;
		}
		decrypt[count++] = (char)encrypt;
		encrypt = 1;
	}

	fputs(decrypt, output);
	printf("��ȣȭ�� ������ original.txt �� ����\n");


	_fcloseall();

}