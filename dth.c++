#include <cmath>
#include <iostream>
using namespace std;

// Tamanho da tabela hash
#define M 19 

struct Produto
{
    int matricula;
    char nome_produto[50];
};

// Tabela hash do tipo Produto
Produto tabelaHash[M];

// Inicializa a tabela hash com valores de matrícula -1
void inicializarTabela()
{
    for (int i = 0; i < M; i++)
    {
        tabelaHash[i].matricula = -1;
    }
}

// Função de espalhamento baseada no resto da divisão
int gerarCodigoHash(int chave)
{
    return chave % M;
}

// Lê e retorna um novo Produto
Produto lerProduto()
{
    Produto p;
    cout << "Digite a matricula: ";
    cin >> p.matricula;
    cin.ignore(); // Ignora o '\n' deixado pelo cin
    cout << "Digite o nome_produto: ";
    cin.getline(p.nome_produto, 50);
    return p;
}

// Insere um Produto na tabela hash tratando colisões linearmente
void inserir()
{
    Produto p = lerProduto();
    int indice = gerarCodigoHash(p.matricula);

    // Contador de tentativas para evitar loops infinitos
    int tentativas = 0;

    // Sondagem linear para encontrar um índice livre
    while (tabelaHash[indice].matricula != -1 && tentativas < M)
    {
        // Garante que o índice esteja dentro dos limites
        indice = (indice + 1) % M;
        tentativas++;
    }

    if (tentativas < M)
    {
        tabelaHash[indice] = p;
    }
    else
    {
        cout << "Tabela cheia, não foi possível inserir o produto.\n";
    }
}

// Busca um Produto por matrícula, tratando colisões linearmente
Produto *buscar(int chave)
{
    int indice = gerarCodigoHash(chave);
    int tentativas = 0;

    // Sondagem linear para encontrar o produto
    while (tabelaHash[indice].matricula != -1 && tentativas < M)
    {
        if (tabelaHash[indice].matricula == chave)
        {
            return &tabelaHash[indice];
        }
        indice = (indice + 1) % M;
        // Garante que o índice esteja dentro dos limites
        tentativas++;
    }

    // Retorna NULL se o produto não for encontrado
    return NULL;
}

// Imprime todos os Produtos na tabela hash
void imprimir()
{
    cout << "\n------------------------TABELA---------------------------\n";
    for (int i = 0; i < M; i++)
    {
        if (tabelaHash[i].matricula != -1)
        {
            cout << i << " = " << tabelaHash[i].matricula << " \t " << tabelaHash[i].nome_produto << "\n";
        }
        else
        {
            cout << i << " =\n";
        }
    }
    cout << "\n----------------------------------------------------------\n";
}

int main()
{
    int op, chave;
    Produto *p;

    inicializarTabela();

    do
    {
        cout << "1 - Inserir\n2 - Buscar\n3 - Imprimir\n0 - Sair\n";
        cin >> op;

        switch (op)
        {
        case 0:
            cout << "Saindo...\n";
            break;
        case 1:
            inserir();
            break;
        case 2:
            cout << "Digite a matricula a ser buscada: ";
            cin >> chave;
            p = buscar(chave);

            if (p)
            {
                cout << "\n\tMatricula: " << p->matricula << " \tNome: " << p->nome_produto << "\n";
            }
            else
            {
                cout << "\nMatricula nao encontrada!\n";
            }
            break;
        case 3:
            imprimir();
            break;
        default:
            cout << "Opcao invalida!\n";
        }
    } while (op != 0);

    return 0;
}
