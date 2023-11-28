#include "lab.h"


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

}baralho;

typedef struct Jogador {

	char nome[50];
	int type;
	baralho mao;
	char apostaI;//O que cada jogador vai apostar
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
	}
	
	for (i = 18; i < 35; i++) {

		myB->cartas[i] = 'T';
		myB->size++;
	}

	
	for (i = 35; i < 48; i++) {

		myB->cartas[i] = 'W';
		myB->size++;
	}
	
	for (i = 48; i < 51; i++) {

		myB->cartas[i] = 'w';
		myB->size++;
	}
	
	for (i = 51; i <66 ; i++) {

		myB->cartas[i] = 'R';
		myB->size++;
	}

	for (i = 66; i < 81; i++) {

		myB->cartas[i] = 'C';
		myB->size++;
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


}

void scrambledeck(baralho* myB) {

	int i = 0;
	for (i = 0; i < myB->size; i++) {

		if (myB->size == 0) { return; }
		trocaChars(&(myB->cartas[i]), &(myB->cartas[rand() % myB->size]));
	}

}

void nomep1(jogador* P1) {

	printf("Introduza o nome do Player One: ");
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

void apostaInicial(jogador* P1, baralho* myB) {

	printf("\nTens estas cartas na tua mão:");
	for (int i = 0; i < 7; i++) {
		if (i == 6) {
			printf("%c", P1->mao.cartas[i]);
		}
		else
		printf("%c,", P1->mao.cartas[i]);
	}


	do {
		printf("\nEscolhe agora a tua carta da aposta inicial: ");
		(void)scanf(" %c", &P1->apostaI);
		
		switch (P1->apostaI) {

		case 'L':{
					int j = 0;
					for(j=0;j<7;j++){
			
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
		default:{
			printf("Escolhe uma carta válida!");
				}
}


	} while (P1->apostaI != 'L' && P1->apostaI != 'W' && P1->apostaI != 'w' && P1->apostaI != 'R' && P1->apostaI != 'C'&& P1->apostaI != 'T');
			
			printf(" Aposta principal: %c\n", P1->apostaI);
			printf("Ficaste com estas cartas no teu deck :");
			for (int i = 0; i < 7;i++) {
				if (i == 6) {
					printf("%c", P1->mao.cartas[i]);
				}else
				printf("%c,", P1->mao.cartas[i]);
			}
}

void novoJogo(){

	baralho myB;
	jogador P1;
	comecarbaralho(&myB);
	scrambledeck(&myB);
	scrambledeck(&myB);
	nomep1(&P1);
	
	FILE* fp = NULL;
	fopen_s(&fp, "maindeck.txt", "w");
	if (fp) {
		saveBaralho(fp, &myB, &P1);
		fclose(fp);
	}
	printbaralho(myB);
	system("pause");
	p1mao(&P1,&myB);


	fopen_s(&fp, "maindeck.txt","w");
	if (fp) {
		savedeckplusp1(fp, &myB, &P1);

		fclose(fp);
	}
	printbaralho(myB);
	system("pause");
	system("cls");
	printf("\n Player One: %s cartas na mão:\n", P1.nome);
	for (int i = 0; i < 7; i++) {
		printf("%c,",P1.mao.cartas[i]);
	}
	apostaInicial(&P1,&myB);

	}


int main(void){
	
	ecraInicial();
	setlocale(LC_ALL,"Portuguese");
	int escolha_menu;

		do{
			system("cls");
			gotoxy(10, 8); printf("Escolha agora o que deseja fazer:\n");
			gotoxy(10, 10);	printf("1-Jogar uma Partida do Jogo ""A Lebre e a Tartaruga""\n");//Escolha A
			gotoxy(10, 11);	printf("2-Carregar uma partida a partir de um ficheiro e continuar o jogo\n");//Escolha B
			gotoxy(10, 12);	printf("3-Descrição do jogo\n");//Escolha C | Opção configurada e concluida :CHECKMARK:
			gotoxy(10, 13); printf("0 -Sair\n");//Sair do jogo | Opção configurada e concluida :CHECKMARK:
					
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
								system("cls");
								printf("Descricao do jogo:");
								FILE* rules = fopen("rules.txt","r");
								int c;
								while ((c = fgetc(rules)) != EOF)
								{
									putchar(c);
								}
								fclose(rules);
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