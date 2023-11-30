#include "lab.h"
#include <stdbool.h>
#include <windows.h>

void ecraInicial(){
	
	setColor(MY_COLOR_CYAN, MY_COLOR_BLACK);
	setFullScreen(true);
	system("cls");
	showRectAt(40, 10, 30, 10);
	gotoxy(35, 10); printf("Bem vindo ao Jogo da lebre e da Tartaruga!\n");
	gotoxy(50, 14); printf("by Hugo Costa");

	gotoxy(10, 22); system("pause");
}

typedef struct BARALHO{
	int maxsize;
	char cartas[81];
	int size;
	char descarte[81];
	char apostasIniciais[6];

}baralho;

typedef struct Jogador {

	char nome[50];
	int type;
	baralho mao;
	char apostaI;//O que cada jogador vai apostar
	char apostafixa;
	int pontos;// Para a pontuação final
	

}jogador;


void comecarbaralho(baralho* myB) {

	//L,T,W,w,R,C
	myB->maxsize = 81;
	myB->size;
	int i = 0;
	myB->size = 0;
	for (i = 0; i < 18; i++) {

		myB->cartas[i] = 'L';
		myB->size++;
		if (i == 17) {
			myB->apostasIniciais[0] = 'L';
		}
	}

	for (i = 18; i < 35; i++) {

		myB->cartas[i] = 'T';
		myB->size++;
		if (i == 34) {
			myB->apostasIniciais[1] = 'T';
		}
	}


	for (i = 35; i < 48; i++) {

		myB->cartas[i] = 'W';
		myB->size++;
		if (i == 37) {
			myB->apostasIniciais[2] = 'W';
		}
	}

	for (i = 48; i < 51; i++) {

		myB->cartas[i] = 'w';
		myB->size++;
		if (i == 50) {
			myB->apostasIniciais[3] = 'w';
		}
	}

	for (i = 51; i < 66; i++) {

		myB->cartas[i] = 'R';
		myB->size++;
		if (i == 65) {
			myB->apostasIniciais[4] = 'R';
		}
	}

	for (i = 66; i < 81; i++) {

		myB->cartas[i] = 'C';
		myB->size++;
		if (i == 80) {
			myB->apostasIniciais[5] = 'C';
		}
	}

	
}

void printbaralho(baralho myB) {

	int i = 0;
	for (i = 0; i < 81; i++) //80 --> myB.size??
	{
		if (i == 80) {
			printf("%c", myB.cartas[i]);
		}
		else
			printf("%c,", myB.cartas[i]);
		

	}

	printf("\n");
}

void scrambledeck(baralho* myB) {

	int i = 0;
	for (i = 0; i < myB->size; i++) {

		if (myB->size == 0) { return; }
		trocaChars(&(myB->cartas[i]), &(myB->cartas[rand() % myB->size]));

	}

}

void embaralharapostainicial(baralho* myB, int tamanho,jogador* P1) {
	for (int i = tamanho - 1; i > 0; i--) {
		int j = rand() % (i + 1);

		// Troca as cartas i e j
		char temp = myB->apostasIniciais[i];
		myB->apostasIniciais[i] = myB->apostasIniciais[j];
		myB->apostasIniciais[j] = temp;
	}
	P1->apostafixa = myB->apostasIniciais[0];
}

void nomep1(jogador* P1) {
	gotoxy(40, 14);
	printf("Introduza o nome do Player One: \n");
	gotoxy(40, 16);
	(void)scanf("%s",P1->nome);

}

void p1mao(jogador* P1, baralho* myB) {
	int i;
	P1->mao.maxsize = 7;
	P1->mao.size = 0;
	for (i = 0; i < P1->mao.maxsize; i++) {
		P1->mao.size++;
		P1->mao.cartas[i] = myB->cartas[i];
		myB->cartas[i] = 'x';
		if (i == P1->mao.maxsize) {
			printf("%c", P1->mao.cartas[i]);
			
		}else
		printf("%c,",P1->mao.cartas[i]);
	}
	
}

void removerElemento(char vetor[], int tamanho, char elemento) {
	int i, j;

	// Procura o elemento no vetor
	for (i = 0; i < tamanho; i++) {
		if (vetor[i] == elemento) {
			// Move os elementos à direita do elemento a ser removido uma posição para a esquerda
			for (j = i; j < tamanho - 1; j++) {
				vetor[j] = vetor[j + 1];
			}

			// Reduz o tamanho do vetor
			tamanho--;

			// Decrementa o índice para evitar pular um elemento
			i--;
		}
	}
}

void jogadaInicial() {









}

void jogada(jogador* P1, baralho* myB) {





}

void saveBaralho(FILE* fp,baralho* myB,jogador* P1 ){

	int i = 0;
	fprintf(fp, "(");
	for (i = 0; i < 81; i++) {
		if (i == 80){
			fprintf(fp,"%c", myB->cartas[i]);
		}else
		fprintf(fp,"%c,", myB->cartas[i]);
							}
	fprintf(fp,")");
	fclose(fp);
}

void savedeckplusp1(FILE* fp, baralho* myB, jogador* P1) { //Função serve para verificar se está a guardar tudo bem no ficheiro txt

	int i = 0;
	fprintf(fp, "(");
	for (i = 0; i < 81; i++) {
		if(i==80){ 
			fprintf(fp, "%c", myB->cartas[i]);}
			else
			fprintf(fp, "%c,", myB->cartas[i]); //Imprimir tudo igual há função anterior e normal saveBaralho
	}
	fprintf(fp,")");
	fprintf(fp, "\n %s -> ", P1->nome);
	for (i = 0; i < 7; i++) {
		if (i == 6) {
			fprintf(fp, " %c ", P1->mao.cartas[i]);
		}else
			fprintf(fp, " %c,", P1->mao.cartas[i]);
	}
	fclose(fp);
	printf(" \n");
}

void readBaralho(FILE* fp, baralho* myB) {

	int i = 0;
	fgetc(fp); //descarta '('
	for (i = 0; i < 80; i++) {

		myB->cartas[i] = fgetc(fp);
	}
	fgetc(fp); //descarta ','
}

// Função para verificar se uma carta está na mão
bool cartaNaMao(char mao[], int tamanhoDaMao, char cartaProcurada) {
	for (int i = 0; i < tamanhoDaMao; i++) {
		if (mao[i] == cartaProcurada) {
			return true; // Carta encontrada na mão
		}
	}
	return false; // Carta não encontrada na mão
}

void apostaInicial(jogador* P1, baralho* myB) {

	int verdadeiro = 0;
	printf("\nTens estas cartas na tua mão:");
	for (int i = 0; i < 7; i++) {
		if (i == 6) {
			printf("%c", P1->mao.cartas[i]);
		}
		else
			printf("%c,", P1->mao.cartas[i]);
	}

	do {
		// Solicita uma carta para fazer de aposta Inicial
		printf("\nEscolhe agora a tua carta da aposta inicial: ");
		(void)scanf(" %c", &P1->apostaI);
		if (P1->apostaI == 'l') {
			P1->apostaI = 'L';
		}
		else {
			if (P1->apostaI == 'r') {
				P1->apostaI = 'R';
			}
			else {
				if (P1->apostaI == 'c') {
					P1->apostaI = 'C';
				}
				else
				{
					if (P1->apostaI == 't') {
						P1->apostaI = 'T';
					}
				}
			}
		}

		if (cartaNaMao(P1->mao.cartas,7, P1->apostaI))
		{
			printf("Carta encontrada na mao!\n");
			verdadeiro = 1;
			switch (P1->apostaI) {

			case 'L': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}

			case 'l': {
				int j = 0;
				P1->apostaI = 'L';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'W': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'w': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'R': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'r': {
				int j = 0;
				P1->apostaI = 'R';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'C': {
				int j = 0;
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'c': {
				int j = 0;
				P1->apostaI = 'C';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 'T': {

				int j = 0;

				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;
			}
			case 't': {
				int j = 0;
				P1->apostaI = 'T';
				for (j = 0; j < 7; j++) {

					if (P1->apostaI == P1->mao.cartas[j]) {

						P1->mao.cartas[j] = 'x';
						break;
					}
				}

				break;

			}
			}


			printf("Aposta principal: %c\n", P1->apostaI);
			printf("Ficaste com estas cartas no teu deck :");
			for (int i = 0; i < 7; i++) {
				if (i == 6) {
					printf("%c", P1->mao.cartas[i]);
				}
				else
					printf("%c,", P1->mao.cartas[i]);
			}
		}
		else {
			printf("Carta nao encontrada na mao.\n");
			
		}
	} while (verdadeiro != 1);
}


void printcartasparaapostaI(jogador P1) {
	printf("\n%s cartas na mão: ", P1.nome);
	for (int i = 0; i < 7; i++) {
		if (i == 6) {
			printf("%c ", P1.mao.cartas[i]);
		}
		else {
			printf("%c, ", P1.mao.cartas[i]);
		}
	}
	printf("\n");
}

void imprimirCartasNaMaoparajogada(jogador P1) {
	printf("\n%s cartas na mão: ", P1.nome);
	for (int i = 0; i < 6; i++) {
		if (i == 5) {
			printf("%c ", P1.mao.cartas[i]);
		}
		else {
			printf("%c, ", P1.mao.cartas[i]);
		}
	}
	printf("\n");
	printf("Cartas de aposta: %c, %c", P1.apostaI, P1.apostafixa);
}


void novoJogo() {

	baralho myB;
	jogador P1;
	
	comecarbaralho(&myB);
	scrambledeck(&myB);
	embaralharapostainicial(&myB,6,&P1);
	nomep1(&P1);
	system("cls");
	FILE* fp = NULL;
	fopen_s(&fp, "maindeck.txt", "w");
	if (fp) {
		saveBaralho(fp, &myB, &P1);
		fclose(fp);
	}
	gotoxy(40, 15);
	printf("Baralho inicial:\n");
	printbaralho(myB);
	system("pause");
	p1mao(&P1, &myB);


	fopen_s(&fp, "maindeck.txt", "w");
	if (fp) {
		savedeckplusp1(fp, &myB, &P1);

		fclose(fp);
	}
	printbaralho(myB);
	system("pause");
	system("cls");

	printcartasparaapostaI(P1);
	apostaInicial(&P1, &myB);

	removerElemento(&P1.mao.cartas, 7, 'x');

	imprimirCartasNaMaoparajogada(P1);

}

int main(void){
	
	ecraInicial();
	setlocale(LC_ALL,"Portuguese");
	int escolha_menu;
	char content[1000];
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, 0);


	FILE* Rules;

		do{
			system("cls");
			gotoxy(10, 8); printf("Escolha agora o que deseja fazer:\n");
			gotoxy(10, 10);	printf("1-Jogar uma Partida do Jogo ""A Lebre e a Tartaruga""\n");//Escolha A
			gotoxy(10, 11);	printf("2-Carregar uma partida a partir de um ficheiro e continuar o jogo\n");//Escolha B
			gotoxy(10, 12);	printf("3-Descrição do jogo\n");//Escolha C | Opção configurada e concluida :CHECKMARK:
			gotoxy(10, 13); printf("0-Sair\n");//Sair do jogo | Opção configurada e concluida :CHECKMARK:
					
			gotoxy(10, 15); printf("Escolha agora o que deseja fazer:");
			(void)scanf("%d",&escolha_menu);//Escolher a opção do menu

				switch(escolha_menu){ 
				
							case 1: {
								
								system("cls");//Limpar o texto anterior 
								novoJogo();
								
								printf("\nO programa foi bem executado até aqui\n");//Ponto de verificação
									system("pause");//Parar o programa para verificar
									break;//Não esquecer deste malandro
							}
				
							case 2: {
								setBackColor(MY_COLOR_DARK_GRAY);

								system("cls"); //Limpar o texto anterior 
								
								 //carregarjogo();
								int i = 0;
								for(i = 0; i < 15; i++) {
									setForeColor(0 + i,i+1);
									showRectAt(3+i*4, 5, 3, 3);

								}
								
								
								gotoxy(20, 20);
								printf("O programa foi bem executado ate aqui\n");//Ponto de verificação
									system("pause");//Parar o programa para verificar
									break;//Não esquecer deste malandro
							}
							
							case 3:{
								setlocale(LC_ALL, "pt_PT.UTF-8");// UTF-8 para ler ficheiros .txt para pt-pt
								system("cls");
								printf("Descricao do jogo:");
								Rules = fopen("rules.txt","r");
								while (fgets(content, sizeof(content), Rules) != NULL) {
									printf("%s", content);
								}
								fclose(Rules);
								system("pause");
								break;//Não esquecer deste malandro
							
							}
							
							case 0:{
									printf("Saiu do programa\n");//Sair do programa
									break;
									}
							default:{
								//Default para voltar ao ciclo e escolher novamente um número
								
								printf("Escolha um numero pertencente ha lista!\n");
								system("pause");
								break;

							}
				}

		} while (escolha_menu != 0);//Sair do jogo e fechar o programa



}