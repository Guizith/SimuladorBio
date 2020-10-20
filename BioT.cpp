#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <vector>
#include <chrono>
#include <math.h>

using namespace std;
using namespace chrono;

FILE * sc = fopen("LogBio.txt","w");
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

int orchestrator(int tempo);

void tanqueO(){
	if(jks == 5){
			tqol.qtd = tqol.qtd + (1 +  (float)rand()/(float)(RAND_MAX/1));
			fprintf(sc,"Tanque de oleo recebeu abastecimento\n");
			jks = 1;
		}else{
			fprintf(sc,"Tanque de oleo nao recebeu abastecimento\n");
			jks++;
		}
}
void tanqueETNA(){
	tqnaet.qtdEt = tqnaet.qtdEt + 0.1;
	tqnaet.qtdNa = tqnaet.qtdNa + 0.3;
	fprintf(sc,"Tanque Et Na recebeu abastecimento\n",tqnaet.qtdEt,tqnaet.qtdNa);
}
void tranqueR(){
		if(decantador.qtd < 5.1){
			if((tqol.qtd > 1.25) && (tqnaet.qtdEt > 2.5) && (tqnaet.qtdNa > 1.25)){
				tqnaet.qtdEt = tqnaet.qtdEt - 2.5;
				tqnaet.qtdNa = tqnaet.qtdNa - 1.25;
				tqol.qtd = tqol.qtd - 1.25; 
				fprintf(sc,"Reator processou\n");
				decantador.qtd = decantador.qtd + 5; //mensagem
			}else{
				fprintf(sc,"Reator sem materia prima\n");
			}
		}else{
			fprintf(sc,"Decantador Cheio, Espera\n");
		}	
}
void tranqueDec(){
		if(jkp >= 3){
			if(decantador.qtd >= 3){
				decantador.qtd = decantador.qtd - 3;
				tqgli.qtd = tqgli.qtd + 0.15;	//mensagem
				secador.qtd = 0.39;	//mensagem
				lavagem.qtd = 2.46;	//mensagem
				fprintf(sc,"Decatandor processou\n");
				jkp = 1;
			}else{
				fprintf(sc,"Decatandor sem materia prima\n");
			}
	
		}else{
			jkp++;
			fprintf(sc,"Decantador em repouso\n");
		}
}
void secaET(){
		if(secador.qtd > 0){
			secador.qtd = secador.qtd - (secador.qtd*0.015);
			if(secador.qtd >= 0.3){
				secador.qtd - 0.3;
				tqnaet.qtdEt = tqnaet.qtdEt + 0.3;
				fprintf(sc,"Secador processou 0.3\n");
			}else if(secador.qtd < 0.3){
				tqnaet.qtdEt = tqnaet.qtdEt + secador.qtd;	
				fprintf(sc,"Secador processou apenas %f pois n tinha mais q isso\n",secador.qtd);
				secador.qtd = 0;
			}
		}else{
			fprintf(sc,"Secador nao possui materia prima\n");
		}
}
void lavag(){
		if(	lavagem.qtd > 0 ){
			secadorLavagem.qtd = secadorLavagem.qtd + (lavagem.qtd - (lavagem.qtd*0.15));
			lavagem.qtd = 0;
			fprintf(sc,"Lavagem processou\n");
			
		}else{
			fprintf(sc,"Nao ha solucao para lavagem\n");
		}
	
}
void secaLav(){
	if(secadorLavagem.qtd > 0){
		secadorLavagem.qtd = secadorLavagem.qtd - (secadorLavagem.qtd*0.015);
		if(secadorLavagem.qtd >= 0.3){
			secadorLavagem.qtd - 0.3;
			bio.qtd = bio.qtd + 0.3;
			fprintf(sc,"SecadorLavagem processou 0.3\n");
		}else if(secador.qtd < 0.3){
			bio.qtd = bio.qtd + secadorLavagem.qtd;	
			fprintf(sc,"SecadorLavagem processou apenas %f pois n tinha mais q isso\n",secadorLavagem.qtd);
			secadorLavagem.qtd = 0;
		}
	}else{
		fprintf(sc,"SecadorLavagem nao possui materia prima\n");
	}
}


int main(){
	seconds sec;
	cout<<"Digite o tempo de simulacao:\n";
	scanf("%d", &sec);
	
	int tempo = sec.count();
	int p = orchestrator(tempo);
}


int orchestrator(int tempo){
	while(tmpst<tempo){
		//Inicio Orc Tranque Oleo
		std::thread TQOOIL(tanqueO);
		TQOOIL.join();
		//Fim Orc Tranque Oleo
	
		//Inicio Orc Tranque NaEt
		std::thread TQETNA(tanqueETNA);
		TQETNA.join();
		//Fim Orc Tranque NaEt
		
		//Inicio reator
		std::thread TQRE(tranqueR);
		TQRE.join();
		//Fim reator
		
		//Inicio decantador
		std::thread TQDE(tranqueDec);
		TQDE.join();
		//Fim decantador
		
		//Inicio SecadorET
		std::thread TQSETE(secaET);
		TQSETE.join();
		//Fim SecadorET
		
		//Inicio lavagem
		std::thread TQLA(lavag);
		TQLA.join();
		//Fim lavagem
		
		//Inicio secadorLavagem
		std::thread TQSELA(secaLav);
		TQSELA.join();
		//Fim secador Lavagem
		fprintf(sc,"-Status dos Tanques:\n");
		fprintf(sc,"Tanque de Oleo tem: %f\n",tqol.qtd);
		fprintf(sc,"Tanque de EtNa tem, Et: %f \t Na: %f\n",tqnaet.qtdEt,tqnaet.qtdNa);
		fprintf(sc,"Tanque Decantador tem: %f\n",decantador.qtd);
		fprintf(sc,"Tanques de Lavagem tem ao total %f\n",lavagem.qtd);
		fprintf(sc,"O secadorET tem: %f\n",secador.qtd);
		fprintf(sc,"O secadorLavagem tem: %f\n",secadorLavagem.qtd);
		fprintf(sc,"Tanque de glicerina tem %f\n",tqgli.qtd);
		fprintf(sc,"Tanque de biodiesel tem %f\n",bio.qtd);
		

		fprintf(sc,"-------------------------------------------------\n");
		sleep(0.1);
		tmpst++;	
	}
}







