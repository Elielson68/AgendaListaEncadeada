
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Agenda{
    string nome;
    int telefone;
    struct Agenda *proximo;
    struct Agenda *anterior;
};

struct Lista{
    struct Agenda *primeiro;
    struct Agenda *ultimo;
    int tamanho;
}minhaLista;


void IniciarLista(){
  
  minhaLista.primeiro = NULL;
  minhaLista.ultimo = NULL;
  minhaLista.tamanho = 0;

}

bool ListaVazia(){
    if(minhaLista.tamanho == 0){
        return true;
    }
    else{
        return false;
    }
}

void ListarAgendaOrdemCrescente(){
    Agenda *agenda = (struct Agenda *)malloc(sizeof(Agenda));
    agenda = minhaLista.primeiro;
    while(agenda != NULL){
        cout << agenda->nome << "\n";
        agenda = agenda->proximo;
    }
}

void ListarAgendaOrdemDecrescente(){
    Agenda *agenda = (struct Agenda *)malloc(sizeof(Agenda));
    agenda = minhaLista.ultimo;
    while(agenda != NULL){
        cout << agenda->nome << "\n";
        agenda = agenda->anterior;
    }
}

void adicionaNoInicio(string nome, int numero) {
    Agenda *novaAgenda = (struct Agenda *)malloc(sizeof(Agenda));
    novaAgenda->nome = nome;
    novaAgenda->telefone = numero;
    novaAgenda->proximo = NULL;
    novaAgenda->anterior = NULL;
    if (minhaLista.primeiro == NULL) {
        minhaLista.primeiro = novaAgenda;
        minhaLista.ultimo = novaAgenda;
    }
    else{
        novaAgenda->proximo = minhaLista.primeiro;
        minhaLista.primeiro = novaAgenda;
        minhaLista.primeiro->proximo->anterior = minhaLista.primeiro;
    }
    minhaLista.tamanho++;
}

void adicionaNoFim(string nome, int numero) {
    Agenda *novaAgenda = (struct Agenda *)malloc(sizeof(Agenda));
    novaAgenda->nome = nome;
    novaAgenda->telefone = numero;
    novaAgenda->proximo = NULL;
    novaAgenda->anterior = NULL;
    if (minhaLista.primeiro == NULL) {
        minhaLista.primeiro = novaAgenda;
        minhaLista.ultimo = novaAgenda;
    }
    else{
      Agenda *agendaAux = (struct Agenda *)malloc(sizeof(Agenda));
      agendaAux = minhaLista.primeiro;
      while(agendaAux->proximo != NULL){
        agendaAux = agendaAux->proximo;
      }
      agendaAux->proximo = novaAgenda;
      novaAgenda->anterior = agendaAux;
      minhaLista.ultimo = novaAgenda;      
    }
    minhaLista.tamanho++;
}

void AdicionarPosicaoN(int posicao, string nome, int telefone){
  if(posicao == 1){
    adicionaNoInicio(nome, telefone);
  }
  else if (posicao > minhaLista.tamanho){
    cout << "Posição excede o tamanho da lista!";
  }
  else{
    int posicao_aux = 2;
    Agenda *agendaAux = (struct Agenda *)malloc(sizeof(Agenda));
    agendaAux = minhaLista.primeiro->proximo;
    Agenda *Anterior = (struct Agenda *)malloc(sizeof(Agenda));
    Agenda *Sucessor = (struct Agenda *)malloc(sizeof(Agenda));

    Agenda *NovaAgenda = (struct Agenda *)malloc(sizeof(Agenda));
    NovaAgenda->nome = nome;
    NovaAgenda->telefone = telefone;

    while(posicao_aux != posicao){
      agendaAux = agendaAux->proximo;
      posicao_aux++;
    }
    Anterior = agendaAux->anterior;
    Sucessor = agendaAux;
    Anterior->proximo = NovaAgenda;
    NovaAgenda->anterior = Anterior;

    NovaAgenda->proximo = Sucessor;
    Sucessor->anterior = NovaAgenda;
  }


}

void RetirarDoInicio(){
  if(!ListaVazia()){
    Agenda *SegundaAgenda = (struct Agenda *)malloc(sizeof(Agenda));
    SegundaAgenda = minhaLista.primeiro->proximo;
    free(minhaLista.primeiro);
    minhaLista.primeiro = SegundaAgenda;
    minhaLista.tamanho--;
  }
}

void RetirarDoFim(){
  if(!ListaVazia()){
    Agenda *PenultimaAgenda = (struct Agenda *)malloc(sizeof(Agenda));
    PenultimaAgenda = minhaLista.ultimo->anterior;
    free(minhaLista.ultimo);
    minhaLista.ultimo = PenultimaAgenda;
    minhaLista.tamanho--;
  }
}

void RetirarPosicaoN(int n){
  if(!ListaVazia() && n<=minhaLista.tamanho){
    if(n==1){
      RetirarDoInicio();
    }
    else if(n==minhaLista.tamanho){
      RetirarDoFim();
    }
    else{
      Agenda *RetirarAgenda = (struct Agenda *)malloc(sizeof(Agenda));
      Agenda *Anterior_a_AgendaRetirada = (struct Agenda *) malloc(sizeof(Agenda));
      Agenda *Posterior_a_AgendaRetirada = (struct Agenda *)  malloc(sizeof(Agenda));
      RetirarAgenda = minhaLista.primeiro;
      int contador = 1;
      while(contador != n){
        RetirarAgenda = RetirarAgenda->proximo;
        contador++;
      }
      Anterior_a_AgendaRetirada = RetirarAgenda->anterior;
      Posterior_a_AgendaRetirada = RetirarAgenda->proximo;
      Anterior_a_AgendaRetirada->proximo =  Posterior_a_AgendaRetirada;
      Posterior_a_AgendaRetirada->anterior =          Anterior_a_AgendaRetirada;
      free(RetirarAgenda);
    }
    
    minhaLista.tamanho--;
  }
}

void DestruirLista(){
  if(!ListaVazia()){
    Agenda *RetirarAgenda = (struct Agenda *)malloc(sizeof(Agenda));
    RetirarAgenda = minhaLista.primeiro;
    int contador = 1;
    while(RetirarAgenda != NULL){
      RetirarAgenda = RetirarAgenda->proximo;
      free(RetirarAgenda->anterior);
      contador++;
    }
    free(RetirarAgenda);
    IniciarLista();
  }
}

int BuscaporNome(string nome){
    if(ListaVazia()){
        cout << "Lista Vazia, Nao ha o que mostrar";
        return 0;
    }else{
      Agenda *AgendaBuscaNome = (struct Agenda *)malloc(sizeof(Agenda));
      AgendaBuscaNome = minhaLista.primeiro;
      int cont = 1;
      while(AgendaBuscaNome-> nome != nome && AgendaBuscaNome->proximo != NULL){
            AgendaBuscaNome = AgendaBuscaNome -> proximo;
            cont++;
      }
    return cont;  
    };
}

int main(int argc, char const *argv[]){
  IniciarLista();
  int programa = 1;
  string Nome;
  int telefone;
  int opcao;
  int posicao;
  while(programa){
    
    cout << "Digite a opção que deseja usar: \n";
    cout << "Opções para adicionar:\n1 - Adicionar no início.\n2 - Adicionar no fim.\n3 - Adicionar em posição N\n4 - Retirar elemento do início\n5 - Retirar do fim\n6 - Retirar de posição N\n7 - Imprimir do início ao fim\n8 - Imprimir do fim ao início\n9 - DESTRUIR LISTA!\n10- Busca por Nome\n0 - Sair do programa\nVocê: ";
    cin >> opcao;
    switch(opcao){
      case 0:
      programa = 0;
      break;
      case 1:
        system("clear");
        cout << "Nome do novo contato: ";
        cin >> Nome;
        cout << "Número do novo contato: ";
        cin >> telefone;
        adicionaNoInicio(Nome, telefone);
      break;
      case 2:
        system("clear");
        cout << "Nome do novo contato: ";
        cin >> Nome;
        cout << "Número do novo contato: ";
        cin >> telefone;
        adicionaNoFim(Nome, telefone);
      break;
      case 3:
        system("clear");
        cout << "Nome do novo contato: ";
        cin >> Nome;
        cout << "Número do novo contato: ";
        cin >> telefone;
        cout << "Posição do novo contato: ";
        cin >> posicao;
        AdicionarPosicaoN(posicao, Nome, telefone);
      break;
      case 4:
        system("clear");
        cout << "Elemento retirado!\n";
        RetirarDoInicio();
      break;
      case 5:
        system("clear");
        cout << "Elemento retirado!\n";
        RetirarDoFim();
      break;
      case 6:
        system("clear");
        cout << "Posição: ";
        cin >> posicao;
        RetirarPosicaoN(posicao);
        cout << "\nElemento retirado!\n";
      break;
      case 7:
        system("clear");
        cout << "\t\nLISTA DO INÍCIO AO FIM\n";
        ListarAgendaOrdemCrescente();
      break;
      case 8:
        system("clear");
        cout << "\t\nLISTA DO FIM AO INÍCIO\n";
        ListarAgendaOrdemDecrescente();
      break;
      case 9:
        system("clear");
        cout << "\t\nLISTA DESTRUÍDA!\n";
        DestruirLista();
      break;
      case 10:
        system("clear");
        cout << "Digite o nome a ser buscado: \n";
        cin >> Nome;
        cout << "Índice do nome buscado é: " << BuscaporNome(Nome)<< "\n";
        break;
      default:
        system("clear");
        cout << "\nNão há essa opção!\n\n";
        break;
    }  
  } 
  cout << "\t\n\n*FIM DO PROGRAMA*";  
};