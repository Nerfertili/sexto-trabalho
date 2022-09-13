#include <iostream>
#include <random>
#include <stdlib.h>

using namespace std;

std::mt19937 generator(14234);
std::uniform_int_distribution<int> dis(1, 1000);
std::uniform_int_distribution<int> dis_2(10, 26);
std::uniform_int_distribution<int> dis_3(1, 10);
std::uniform_int_distribution<int> dis_4(300, 576);

struct NO {
  int item;
  NO *esq;
  NO *dir;
};

class Tree {
public:
  NO *root;
  int i = 0;
  int k = 0;
  int t = 0;

  Tree() { root = NULL; }

  void inserir(int v) {
    NO *novo = new NO();
    novo->item = v;
    novo->dir = NULL;
    novo->esq = NULL;
    if (root == NULL)
      root = novo;
    else {
      NO *atual = root;
      NO *anterior;
      while (true) {
        anterior = atual;
        if (v <= atual->item) {
          atual = atual->esq;
          if (atual == NULL) {
            anterior->esq = novo;
            return;
          }
        } else {
          atual = atual->dir;
          if (atual == NULL) {
            anterior->dir = novo;
            return;
          }
        }
      }
    }
  }

  NO *buscar(int chave) {
    if (root == NULL)
      return NULL;
    NO *atual = root;
    while (atual->item != chave) {
      if (chave < atual->item)
        atual = atual->esq;
      else
        atual = atual->dir;
      if (atual == NULL)
        return NULL;
    }
    return atual;
  }

  bool remover(int v) {
    if (root == NULL)
      return false;
    NO *atual = root;
    NO *pai = root;
    bool filho_esq = true;
    while (atual->item != v) {
      pai = atual;
      if (v < atual->item) {
        atual = atual->esq;
        filho_esq = true;
      } else {
        atual = atual->dir;
        filho_esq = false;
      }
      if (atual == NULL)
        return false;
    }
    if (atual->esq == NULL && atual->dir == NULL) {
      if (atual == root)
        root = NULL;
      else if (filho_esq)
        pai->esq = NULL;
      else
        pai->dir = NULL;
    } else if (atual->dir == NULL) {
      if (atual == root)
        root = atual->esq;
      else if (filho_esq)
        pai->esq = atual->esq;
      else
        pai->dir = atual->esq;
    } else if (atual->esq == NULL) {
      if (atual == root)
        root = atual->dir;
      else if (filho_esq)
        pai->esq = atual->dir;
      else
        pai->dir = atual->dir;
    } else {
      NO *sucessor = no_sucessor(atual);
      if (atual == root)
        root = sucessor;
      else if (filho_esq)
        pai->esq = sucessor;
      else
        pai->dir = sucessor;
      sucessor->esq = atual->esq;
    }

    return true;
  }
  NO *no_sucessor(NO *apaga) {
    NO *paidosucessor = apaga;
    NO *sucessor = apaga;
    NO *atual = apaga->dir;
    while (atual != NULL) {
      paidosucessor = sucessor;
      sucessor = atual;
      atual = atual->esq;
    }
    if (sucessor != apaga->dir) {
      paidosucessor->esq = sucessor->dir;
      sucessor->dir = apaga->dir;
    }
    return sucessor;
  }

  void caminhar() {
    print_bonito(root);
    cout << "\nIn-Order: ";
    inOrder(root);
    cout << "\nPost-Order: ";
    posOrder(root);
    cout << "\nPre-Order: ";
    preOrder(root);
    cout << "\n Quantidade de folhas: ";
    folhas(root);
  }
  void print_bonito(NO *atual) {
    if (atual != NULL) {
      k++;
      if (k == 2) {
        i++;
        k = 0;
      }
      for (int w = 0; w < i; w++) {
        cout << "\t";
      }
      if ((atual->esq != NULL) || (atual->dir != NULL)) {
        cout << "+" << atual->item << endl;
      } else {
        cout << atual->item << endl;
      }

      print_bonito(atual->esq);
      print_bonito(atual->dir);
    }
  }

  void inOrder(NO *atual) {
    if (atual != NULL) {
      inOrder(atual->esq);
      cout << atual->item << " ";
      inOrder(atual->dir);
    }
  }

  int altura(NO *atual) {
    if (atual == NULL || (atual->esq == NULL && atual->dir == NULL))
      return 0;
    else {
      if (altura(atual->esq) > altura(atual->dir))
        return (1 + altura(atual->esq));
      else
        return (1 + altura(atual->dir));
    }
  }

  void folhas(NO *atual) {
    if (atual != NULL) {
      if ((atual->esq == NULL) and (atual->dir == NULL)) {
        cout << atual->item << " ";
      }
      folhas(atual->esq);
      folhas(atual->dir);
    }
  }

  int contarNos(NO *atual) {
    if (atual == NULL)
      return 0;
    else
      return (1 + contarNos(atual->esq) + contarNos(atual->dir));
  }

  void posOrder(NO *atual) {
    if (atual != NULL) {
      posOrder(atual->esq);
      posOrder(atual->dir);
      cout << atual->item << " ";
    }
  }

  void preOrder(NO *atual) {
    if (atual != NULL) {
      cout << atual->item << " ";
      preOrder(atual->esq);
      preOrder(atual->dir);
    }
  }

  int min() {
    NO *atual = root;
    NO *anterior = NULL;
    while (atual != NULL) {
      anterior = atual;
      atual = atual->esq;
    }
    return anterior->item;
  }
  void valida(NO *atual, int *bools,int *index) {
    if (atual != NULL) {
      valida(atual->dir,bools,index);
      if ((atual->dir != NULL || atual->dir == NULL) &&
          (atual->esq != NULL || atual->esq == NULL)) {
        bools[*index] = 1;
        *index+=1;
      } else {
        bools[*index] = 0;
        *index+=1;
      }
      valida(atual->dir,bools,index);
    }
  }
  int count_valids(NO *tree) {
    int nodes = contarNos(tree);
    int *bools;
    bools = (int *) malloc(10000);
    int ind=0;
    valida(tree,bools,&ind);
    int count;
    for(int i=0;i<nodes;i++){
      if (bools[i]) count++;
    }
    return count;
  }

  int max() {
    NO *atual = root;
    NO *anterior = NULL;
    while (atual != NULL) {
      anterior = atual;
      atual = atual->dir;
    }
    return anterior->item;
  }
};
int main() {
  Tree tree;
  int max_vert = dis_2(generator);
  cout << "Array gerado: ";

  for (int i = 0; i < max_vert; i++) {
    int numr = dis(generator);
    cout << numr << " ";
    tree.inserir(numr);
  }
  cout << endl;
  tree.caminhar();
  cout << endl;

  for (int i = 0; i < dis_3(generator); i++) {
    int val = dis_4(generator);
    if (tree.buscar(val)) {
      cout << "valor gerado: " << val << " Diagnostico: presente" << endl;
    } else {
      cout << "valor gerado: " << val << " Diagnostico: faltante" << endl;
    }
  }
  int validas_1 = tree.count_valids(tree.root);
  for (int i = 0; i < 9; i++) {
    int numr = dis(generator);
    tree.inserir(numr);
  }
  int validas_2 = tree.count_valids(tree.root);

  cout << "Inserções: 10;"<< "ávores geradas "<<validas_2 -validas_1<<"; árvores validadas "<<validas_2<<endl;

  validas_1 = tree.count_valids(tree.root);
  int inde=0;
  while(inde<10){
    int numr = dis(generator);
    if (tree.buscar(numr)){
      tree.remover(numr);
      inde++;
    }
  }
  validas_2 = tree.count_valids(tree.root);

  cout << "Exclusões: 10;"<< "ávores geradas "<<validas_1 -validas_2<<"; árvores validadas "<<validas_2<<endl;
}