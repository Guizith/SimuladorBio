#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <math.h>

// SEM THREAD
//OBS: O programa com Thread e o BioT.cpp
using namespace std;
using namespace chrono;

struct Tanqueoleo{
	float qtd = 0;
};

struct Decantador{
	float qtd = 0;
};

struct TanqueNaEt{
	float qtdNa = 0;
	float qtdEt = 0;
};

struct TanqueEt{
	float qtd = 0;
};

struct TanqueGlicerina{
	float qtd = 0;
};
struct TanqueBio{
	float qtd = 0;
};

struct Secador{
	float qtd = 0;
};

struct Lavagem{
	float qtd = 0;
};

int orchestrator(int tempo);

int main(){
	seconds sec;
	cout<<"Digite o tempo de simulacao:\n";
	scanf("%d", &sec);

	int tempo = sec.count();
	int p = orchestrator(tempo);

}


int orchestrator(int tempo){
	
	struct Tanqueoleo tqol;
	struct TanqueNaEt tqnaet;
	struct Decantador decantador;
	struct TanqueGlicerina tqgli;
	struct Secador secador;
	struct Secador secadorLavagem;
	struct Lavagem lavagem;
	struct TanqueBio bio;
	
	int tmpst = 0;
	int jks = 1;
	int jkp = 3; 
	
	while(tmpst<tempo){
		
		//Inicio Orc Tranque Oleo
		if(jks == 5){
			tqol.qtd = tqol.qtd + (1 +  (float)rand()/(float)(RAND_MAX/1));
			printf("no tanque oleo tem %f\n",tqol.qtd);
			jks = 1;
		}else{
			printf("oleo nao recebeu abastecimento\n");
			jks++;
		}
		//Fim Orc Tranque Oleo
	
		//Inicio Orc Tranque NaEt
		tqnaet.qtdEt = tqnaet.qtdEt + 0.1;
		tqnaet.qtdNa = tqnaet.qtdNa + 0.3;
		printf("no tanque EtNa tem %f Et %f Na\n",tqnaet.qtdEt,tqnaet.qtdNa);
		//Fim Orc Tranque NaEt
		
		//Inicio reator
		if(decantador.qtd < 5.1){
			if((tqol.qtd > 1.25) && (tqnaet.qtdEt > 2.5) && (tqnaet.qtdNa > 1.25)){
				tqnaet.qtdEt = tqnaet.qtdEt - 2.5;
				tqnaet.qtdNa = tqnaet.qtdNa - 1.25;
				tqol.qtd = tqol.qtd - 1.25; 
				printf("Reator processou\n");
				decantador.qtd = decantador.qtd + 5; //mensagem
			}else{
				printf("Reator sem materia prima\n");
			}
		}else{
			printf("Decantador Cheio, Espera\n");
		}	
		//Fim reator
		
		//Inicio decantador
		if(jkp >= 3){
			if(decantador.qtd >= 3){
				decantador.qtd = decantador.qtd - 3;
				tqgli.qtd = tqgli.qtd + 0.15;	//mensagem
				secador.qtd = 0.39;	//mensagem
				lavagem.qtd = 2.46;	//mensagem
				printf("Decatandor processou\n");
				jkp = 1;
			}else{
				printf("Decatandor sem materia prima\n");
			}
	
		}else{
			jkp++;
			printf("Decantador em repouso\n");
		}
		//Fim decantador
		
		
		//Inicio SecadorET
		if(secador.qtd > 0){
			secador.qtd = secador.qtd - (secador.qtd*0.15);
			if(secador.qtd >= 0.3){
				secador.qtd - 0.3;
				tqnaet.qtdEt = tqnaet.qtdEt + 0.3;
				printf("Secador processou 0.3\n");
			}else if(secador.qtd < 0.3){
				tqnaet.qtdEt = tqnaet.qtdEt + secador.qtd;	
				printf("Secador processou apenas %f pois n tinha mais q isso\n",secador.qtd);
				secador.qtd = 0;
			}
		}else{
			printf("Secador nao possui materia prima\n");
		}
		//Fim SecadorET
		
		//Inicio lavagem
		if(	lavagem.qtd > 0 ){
	
			lavagem.qtd = lavagem.qtd - 2.46;
			secadorLavagem.qtd = secadorLavagem.qtd + 2.09;
			printf("Lavagem processou\n");
		}else{
			printf("Nao ha solucao para lavagem\n");
		}
		//Fim lavagem
		
		//Inicio secadorLavagem
		if(secadorLavagem.qtd > 0){
			secadorLavagem.qtd = secadorLavagem.qtd - (secadorLavagem.qtd*0.15);
			if(secadorLavagem.qtd >= 0.3){
				secadorLavagem.qtd - 0.3;
				bio.qtd = bio.qtd + 0.3;
				printf("SecadorLavagem processou 0.3\n");
			}else if(secador.qtd < 0.3){
				bio.qtd = bio.qtd + secadorLavagem.qtd;	
				printf("SecadorLavagem processou apenas %f pois n tinha mais q isso\n",secador.qtd);
				secador.qtd = 0;
			}
		}else{
			printf("SecadorLavagem nao possui materia prima\n");
		}
		
		
		//Fim secador Lavagem
		
		
		printf("Tanque de glicerina tem %f\n",tqgli.qtd);
		printf("Tanque de biodisel tem %f\n",bio.qtd);


		printf("---------------------\n");
		sleep(0.1);
		tmpst++;
		
		
		
	}

	
}







