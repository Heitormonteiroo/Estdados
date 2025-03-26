#include <cstdio>

class Celula;
class TabelaDispersao;

class Celula
{
  friend TabelaDispersao;
  
public:
  Celula(int chave, Celula *prox = nullptr) : chave(chave), prox(prox) { }
  
private:
  int chave;
  Celula *prox;
};

class TabelaDispersao
{
public:
  TabelaDispersao(int tamanho);
  ~TabelaDispersao();
  void insere(int x);
  bool busca(int x);
  bool remove(int x);
  double fator_carga();
  int elementos(); // devolve a quantidade de elementos
  void escreve();
  
private:
  int h(int x);
  int m;
  Celula **tabela;
};

int main(void)
{
    TabelaDispersao tabela(5); // Tabela com 5 buckets

  // Inserindo elementos
  tabela.insere(1);
  tabela.insere(6);  // Vai colidir com 1 (1 % 5 == 1, 6 % 5 == 1)
  tabela.insere(11); // Também colide na posição 1
  tabela.insere(3);

  printf("Tabela após inserções:\n");
  tabela.escreve();
  
bool teste=tabela.busca(10);
if(teste==true){
    printf("achou");
}else{
    printf("Nao achou\n");
}
int teste2=tabela.elementos();
printf("Numero de elementos na tabela:%d\n",teste2);
  
  printf("Removendo 6...\n");
  tabela.remove(6);
  tabela.escreve();

  printf("Removendo 10 (não existe)...\n");
  tabela.remove(10);
  tabela.escreve();

  // Teste de fator de carga
  // printf("Fator de carga: %.2f\n", tabela.fator_carga());


  return 0;
}

TabelaDispersao::TabelaDispersao(int tamanho) :
  m(tamanho)
{
  tabela = new Celula*[tamanho];
  for (int i = 0; i < tamanho; i++)
    tabela[i] = nullptr;
}

TabelaDispersao::~TabelaDispersao()
{
  // FAZER: varrer cada lista deletando as células
  delete[] tabela;
}

void TabelaDispersao::insere(int x)
{
  Celula *nova = new Celula(x, tabela[h(x)]);
  tabela[h(x)] = nova;
}

bool TabelaDispersao::busca(int x)
{
  Celula *aux;
  for(aux=tabela[h(x)];aux!=nullptr && aux->chave!=x;aux=aux->prox);
  if (aux!=nullptr){
    return true;}else{
    return false;}
}

bool TabelaDispersao::remove(int x)
{
  Celula *aux,*aux2;
  for(aux=tabela[h(x)];aux!=nullptr && aux->chave!=x;aux2=aux,aux=aux->prox);
  if (aux!=nullptr){
    if(aux2==nullptr){
      tabela[h(x)]=aux->prox;
    }else{
      aux2->prox=aux->prox;
      delete aux;}
    return true;
  }else{
    return false;}
}

double TabelaDispersao::fator_carga()
{
  return elementos() / (double) m;
}

int TabelaDispersao::elementos()
{
    Celula *aux;
    int c=0;
    for(int i=0;i<m;i++){
        for(aux=tabela[i];aux!=nullptr;aux=aux->prox){
            c+=1;
        }
    }
  return c;
}

int TabelaDispersao::h(int x)
{
  return x % m;
}
void TabelaDispersao :: escreve(){
    Celula *aux;
    for(int i=0;i<m;i++){
        for(aux=tabela[i];aux!=nullptr;aux=aux->prox){
            printf("%d ",aux->chave);
        }
    }
}
