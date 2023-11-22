#include "lab.h"


void ecraInicial(){
	
	setColor(MY_COLOR_CYAN, MY_COLOR_LIGTH_GREEN);
	setFullScreen(true);
	system("cls");
	showRectAt(20, 10, 20, 10);
	gotoxy(10, 10); printf("Bem vindo ao Jogo da lebre e da Tartaruga!\n");
	gotoxy(10, 12); printf("by Hugo Costa");

	gotoxy(10, 22); system("pause");
}


typedef struct BARALHO{
	char cartas[81];
	int size;
	char descarte[81];

}baralho;

typedef struct Jogador {

	char nome[50];
	int type;
	baralho mao[7];

}jogador;




void comecarbaralho(baralho* myB) {

	//L,T,W,w,R,C

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

	printf("Introduza o nome do Player 1: ");
	(void)scanf("%s",P1->nome);

}

void p1mao(jogador *P1,baralho *myB) {


	int i = 0;
	for (i = 0; i < 7; i++) {

		P1->mao[i] = myB->cartas[i];
		
	}


}

void jogada(jogador* P1, baralho* myB) {





}


void saveBaralho(FILE* fp,baralho* myB,jogador* P1 ) {

	int i = 0;
	fprintf(fp, "(");
	for (i = 0; i < 81; i++) {
		fprintf(fp, "%c,", myB->cartas[i]);

	}
	fprintf(fp, ")");
	fprintf(fp, "\n%s", P1->nome);
	for (i = 0; i < 7; i++) {

		fprintf(fp, "%s,", P1->mao);
	}
}

void readBaralho(FILE* fp, baralho* myB) {

	int i = 0;
	fgetc(fp); //descarta '('
	for (i = 0; i < 80; i++) {

		myB->cartas[i] = fgetc(fp);
	}
	fgetc(fp); //descarta ','
}

void novoJogo(){

	baralho myB;
	jogador P1;
	comecarbaralho(&myB);
	scrambledeck(&myB);
	nomep1(&P1);
	p1mao(&P1, &myB);
	printbaralho(myB);

	FILE* fp = NULL;
	fopen_s(&fp, "maindeck.txt","w");
	if (fp) {
		saveBaralho(fp,&myB,&P1);
		fclose(fp);
	}
	printbaralho(myB);


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