/*program that encrypt string with alphabet letters only*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Z=26
#define N 26 
//A(m*m)
#define m 2
//string rows (the text/2)
#define n 6
char strfinal[n * 2 + 1];

char* door_encryption(char* ptext, char* key);
void door_attack(char* ptext, char* key);

int charToInt(char c);
void checkKey(int A[m][m]);
void calculate_A_matrix(int A[m][m]);
int mod(int a, int b);

void main() {
	char* ptext = "hadiabumaruf", *key = "road";
	char* s;
	printf("the text before encryption is: \n");
	printf("%s \n", ptext);

	door_encryption(ptext, key);
	door_attack("xaveahkgapkj", "road");
	getchar();
	return 0;
}

/*get text with key to encrypt*/
char* door_encryption(char* ptext, char* key) {
	int i = 0, j, k, sum;
	int A[m][m], temp[m][m];
	int matrixText[n][m];
	int matEncrypted[n][m];

	/*read the key and insert into matrix*/
	while (*key != '\0') {
		for (j = 0; j < m; j++) {
			if ((*key >= 'a' && *key <= 'z' || *key >= 'A' && *key <= 'Z')) {
				A[i][j] = charToInt(*key);
			}
			else {
				printf("the key must contain an letters only\n");
				exit(1);
			}
			key++;
		}
		i++;
	}

		checkKey(A); /*check if the key is acceptable*/
		calculate_A_matrix(A); /*calculate A^3+2A */

		/*read the ptext and insert into matrix*/
		i = 0;
		while (*ptext != '\0') {
			for (j = 0; j < m; j++) {
				if ((*ptext >= 'a'&& *ptext <= 'z') || (*ptext >= 'A'&& *ptext <= 'Z'))
					matrixText[i][j] = charToInt(*ptext);
				else {
					printf("the ptext must contain an letters only\n");
					exit(2);
				}
				ptext++;
			}
			i++;
		}
	/*that mean the string not even*/
		if (i % 2 != 0) {
			printf("the ptext must with EVEN number of letters \n");
			exit(3);
		}

		/* calculate x0*(A^3+2A)%N  */
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				sum = 0;
				for (k = 0; k < m; k++) {
					sum += matrixText[i][k] * A[k][j];
				}
				matEncrypted[i][j] = mod(sum,N);
			}
		}
		k = 0;
		printf("\nthe matrix after encryption is: \n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%c ", strfinal[k]=matEncrypted[i][j] + 'a');
				k++;
			}
			printf("\n");
		}
		strfinal[k] = '\0';

				//door_decryption(str, "road");
				return strfinal;

}



/*calculate the A matrix according to the formula A^3+2A */
void calculate_A_matrix(int A[m][m]) {
	int temp[m][m], temp2[m][m];
	int i, j, k, sum;
		for (i = 0; i < m; i++) 
			for (j = 0; j < m; j++) {
				temp[i][j] = A[i][j];
				temp2[i][j] = A[i][j];
			}
		//multiply A*A
		for (i = 0; i < m; i++) {
			for (j = 0; j < m; j++) {
				sum = 0;
				for (k = 0; k < m; k++) {
					sum += A[i][k] * A[k][j];
				}
				temp[i][j] = sum;
			}
		}
		//multiply A^2*A
		for (i = 0; i < m; i++) {
			for (j = 0; j < m; j++) {
				sum = 0;
				for (k = 0; k < m; k++) {
					sum += temp[i][k] * A[k][j];
				}
				temp2[i][j] = sum;
			}
		}
		/*sum A^3+2A*/
		for (i = 0; i < m; i++) 
			for (j = 0; j < m; j++) 
				A[i][j] = 2 * A[i][j]+ temp2[i][j];
}
/*convert the character to integer*/
int charToInt(char c) {
	if (c < 'a')
		return (c - 'A');
	return (c - 'a');
}

/*check if the key is admissible that mean det(A)!=0 and
det(A)%26!=0 <===> det(A)%13!=0 and det(A)%2!=0*/
void checkKey(int A[m][m]) {
	int det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
	if (det == 0 || det % 13 == 0 || det % 2 == 0) {
		printf("The key is not admissible\n");
		exit(7);
		}
}
/*return the module between a%b*/
int mod(int a, int b){
	int r = a % b;
	return r < 0 ? r + b : r;
}
/*function try to decrypt the encryption string by encrypt it k times
until we recieve the original string. that mean stop if the encrypted=the original*/
void door_attack(char* ptext, char* key) {
	int i, j = 0;
	char* str = "hadiabumaruf";
	printf("\nthe iterative attack begin\n");
	printf("the encrypted text is: %s\n",ptext);
	printf("the currect text have to be: %s\n", str);
	strcpy(strfinal, ptext);
	do{
		j++;
		door_encryption(strfinal, key);
	} while (!strcmp(str, strfinal)==0);
	//free(str);
	
	printf("number of attacks is: %d \n", j);
}