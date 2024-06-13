#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_USERS 100

// Definição de estruturas
typedef struct
{
    char titulo[100];
    char autor[100];
    char genero[100];
    int ano;
    int disponivel;
    int indice;
    time_t data_emprestimo;
} Livro;

typedef struct
{
    char nome[100];
    char tipo[100];
    int id;
    int livros_emprestados[MAX_BOOKS];
    int num_livros_emprestados;
} Usuario;

// Variáveis globais
Livro biblioteca[MAX_BOOKS];
Usuario usuarios[MAX_USERS];
int numLivros = 0;
int numUsuarios = 0;

// Funções
int compararTitulo(const void *a, const void *b);
void usuarioValido(int indiceUsuario);
void verificadorUsuario();
void adicionarLivros();
void exibirLivros();
void atualizarLivro();
void deletarLivro();
void emprestarLivro();
void devolverLivro();
void calcularMulta();
void menuLivros();
void adicionarUsuario();
int compararNome(const void *a, const void *b);
void exibirUsuarios();
void atualizarUsuario();
void deletarUsuario();
void menuUsuario();

int main(){
    int escolha;
    do
    {
        printf("______________________________________________________________\n");
        printf("|#     #           #####                         #    #  #### | \n");
        printf("|#     # #    # # #     #   ##   #####  # ###### ##   # #     | \n");
        printf("|#     # ##   # # #        #  #  #    # # #      # #  #  #### | \n");
        printf("|#     # # #  # #  #####  #    # #    # # #####  #  # #      #| \n");
        printf("|#     # #  # # #       # ###### #####  # #      #   ## #    #| \n");
        printf("|#     # #   ## # #     # #    # #      # #      #   ## #    #| \n");
        printf("| #####  #    # #  #####  #    # #      # ###### #    #  #### | \n");
        printf("|_____________________________________________________________|\n");
        printf("           __________________________________________\n");
        printf("           |Sistema de Gerenciamento de Biblioteca   |\n");
        printf("           |_________________________________________|\n");
        printf("           |1. Menu de Livros                        |\n");
        printf("           |2. Menu de Usuários                      |\n");
        printf("           |0. Sair                                  |\n");
        printf("           |_________________________________________|\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &escolha);

        getchar(); // Limpa o buffer do teclado

        switch (escolha)
        {
        case 1:
            menuLivros();
            break;
        case 2:
            menuUsuario();
            break;
        case 0:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            break;
        }

        printf("\n");
    } while (escolha != 0);
    return 0;
}

void menuLivros()
{
    int escolha;
    do
    {
        printf("______________________________________________________________\n");
        printf("|#     #           #####                         #    #  #### | \n");
        printf("|#     # #    # # #     #   ##   #####  # ###### ##   # #     | \n");
        printf("|#     # ##   # # #        #  #  #    # # #      # #  #  #### | \n");
        printf("|#     # # #  # #  #####  #    # #    # # #####  #  # #      #| \n");
        printf("|#     # #  # # #       # ###### #####  # #      #   ## #    #| \n");
        printf("|#     # #   ## # #     # #    # #      # #      #   ## #    #| \n");
        printf("| #####  #    # #  #####  #    # #      # ###### #    #  #### | \n");
        printf("|_____________________________________________________________|\n");
        printf("           __________________________________________\n");
        printf("           |             Menu de Usuário             |\n");
        printf("           |_________________________________________|\n");
        printf("           |1. Adicionar livro                       |\n");
        printf("           |2. Visualizar livros                     |\n");
        printf("           |3. Atualizar livro                       |\n");
        printf("           |4. Deletar livro                         |\n");
        printf("           |5. Emprestar livro                       |\n");
        printf("           |6. Devolver livro                        |\n");
        printf("           |7. Calcular multa                        |\n");
        printf("           |0. Voltar                                |\n");
        printf("           |_________________________________________|\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        getchar(); // Limpa o buffer do teclado

        switch (escolha)
        {
            case 1:
                adicionarLivros();
                break;
            case 2:
                exibirLivros();
                break;
            case 3:
                atualizarLivro();
                break;
            case 4:
                deletarLivro();
                break;
            case 5:
                emprestarLivro();
                break;
            case 6:
                devolverLivro();
                break;
            case 7:
                calcularMulta();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (escolha != 0);
}

void menuUsuario()
{
    int escolha;

    do
    {
        printf("______________________________________________________________\n");
        printf("|#     #           #####                         #    #  #### | \n");
        printf("|#     # #    # # #     #   ##   #####  # ###### ##   # #     | \n");
        printf("|#     # ##   # # #        #  #  #    # # #      # #  #  #### | \n");
        printf("|#     # # #  # #  #####  #    # #    # # #####  #  # #      #| \n");
        printf("|#     # #  # # #       # ###### #####  # #      #   ## #    #| \n");
        printf("|#     # #   ## # #     # #    # #      # #      #   ## #    #| \n");
        printf("| #####  #    # #  #####  #    # #      # ###### #    #  #### | \n");
        printf("|_____________________________________________________________|\n");
        printf("           ________________________________________\n");
        printf("          |             Menu de Usuário            |\n");
        printf("          |________________________________________|\n");
        printf("          |1. Criar usuário                        |\n");
        printf("          |2. Ver usuários                         |\n");
        printf("          |3. Atualizar usuário                    |\n");
        printf("          |4. Deletar usuário                      |\n");
        printf("          |0. Voltar                               |\n");
        printf("          |________________________________________|\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        getchar(); // Limpa o buffer do teclado

        switch (escolha)
        {
            case 1:
                adicionarUsuario();
                break;
            case 2:
                exibirUsuarios();
                break;
            case 3:
                atualizarUsuario();
                break;
            case 4:
                deletarUsuario();
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        printf("\n");
    } while (escolha != 0);
}

int compararTitulo(const void *a, const void *b) {
    Livro *livroA = (Livro *)a;
    Livro *livroB = (Livro *)b;
    return strcmp(livroA->titulo, livroB->titulo);
}

void adicionarLivros(){
    if (numLivros >= MAX_BOOKS)
    {
        printf("O número máximo de livros foi atingido. Não é possível adicionar mais livros.\n");
        return;
    }

    Livro novoLivro;
    printf("Digite o título do livro: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

    printf("Digite o gênero do livro: ");
    fgets(novoLivro.genero, sizeof(novoLivro.genero), stdin);
    novoLivro.genero[strcspn(novoLivro.genero, "\n")] = '\0';

    printf("Digite o ano de publicação do livro: ");
    scanf("%d", &novoLivro.ano);

    novoLivro.disponivel = 1;
    novoLivro.indice = numLivros + 1;

    biblioteca[numLivros++] = novoLivro;

    printf("Livro adicionado com sucesso!\n");

}

void exibirLivros()
{
    if (numLivros == 0)
    {
        printf("A biblioteca está vazia.\n");
        return;
    }

    qsort(biblioteca, numLivros, sizeof(Livro), compararTitulo);

    printf("Livros cadastrados:\n");
    for (int i = 0; i < numLivros; i++)
    {
        printf("Livro: %d\n", biblioteca[i].indice);
        printf("Título: %s\n", biblioteca[i].titulo);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Gênero: %s\n", biblioteca[i].genero);
        printf("Ano de publicação: %d\n", biblioteca[i].ano);
        printf("Disponível: %s\n", biblioteca[i].disponivel ? "Sim" : "Não");
    }
}

void atualizarLivro()
{
    if (numLivros == 0)
    {
        printf("A biblioteca está vazia.\n");
        return;
    }

    int indiceLivro;
    printf("Digite o número do livro que deseja atualizar: ");
    scanf("%d", &indiceLivro);

    if (indiceLivro < 1 || indiceLivro > numLivros)
    {
        printf("Número de livro inválido.\n");
        return;
    }

    Livro *livro = &biblioteca[indiceLivro - 1];

    printf("Digite o novo título do livro: ");
    getchar(); // Limpa o buffer do teclado
    fgets(livro->titulo, sizeof(livro->titulo), stdin);
    livro->titulo[strcspn(livro->titulo, "\n")] = '\0';

    printf("Digite o novo autor do livro: ");
    fgets(livro->autor, sizeof(livro->autor), stdin);
    livro->autor[strcspn(livro->autor, "\n")] = '\0';

    printf("Digite o novo gênero do livro: ");
    fgets(livro->genero, sizeof(livro->genero), stdin);
    livro->genero[strcspn(livro->genero, "\n")] = '\0';

    printf("Digite o novo ano de publicação do livro: ");
    scanf("%d", &livro->ano);

    printf("Livro atualizado com sucesso!\n");
};

void deletarLivro()
{
    if (numLivros == 0)
    {
        printf("A biblioteca está vazia.\n");
        return;
    }

    int indiceLivro;
    printf("Digite o número do livro que deseja deletar: ");
    scanf("%d", &indiceLivro);

    if (indiceLivro < 1 || indiceLivro > numLivros)
    {
        printf("Número de livro inválido.\n");
        return;
    }

    for (int i = indiceLivro - 1; i < numLivros - 1; i++)
    {
        biblioteca[i] = biblioteca[i + 1];
    }

    numLivros--;

    printf("Livro deletado com sucesso!\n");
}

void emprestarLivro()
{
    if (numLivros == 0)
    {
        printf("A biblioteca está vazia.\n");
        return;
    }

    void verificadorUsuario();

    int indiceLivro;
    printf("Digite o número do livro que deseja emprestar: ");
    scanf("%d", &indiceLivro);

    if (indiceLivro < 1 || indiceLivro > numLivros)
    {
        printf("Número de livro inválido.\n");
        return;
    }

    int indiceUsuario;
    printf("Digite o número do usuário que deseja emprestar o livro: ");
    scanf("%d", &indiceUsuario);

    void usuarioValido(int indiceUsuario);

    Livro *livro = &biblioteca[indiceLivro - 1];
    Usuario *usuario = &usuarios[indiceUsuario - 1];

    if (livro->disponivel == 0)
    {
        printf("O livro selecionado não está disponível para empréstimo.\n");
        return;
    }

    if (usuario->num_livros_emprestados >= MAX_BOOKS)
    {
        printf("O usuário já atingiu o limite de livros emprestados.\n");
        return;
    }

    livro->disponivel = 0;
    time(&livro->data_emprestimo);
    usuario->livros_emprestados[usuario->num_livros_emprestados++] = indiceLivro;

    printf("Livro emprestado com sucesso!\n");
}

void devolverLivro()
{
    if (numLivros == 0)
    {
        printf("A biblioteca está vazia.\n");
        return;
    }

    void verificadorUsuario();

    int indiceUsuario;
    printf("Digite o número do usuário que deseja devolver o livro: ");
    scanf("%d", &indiceUsuario);

    void usuarioValido(int indiceUsuario);

    Usuario *usuario = &usuarios[indiceUsuario - 1];

    if (usuario->num_livros_emprestados == 0)
    {
        printf("O usuário não possui livros emprestados.\n");
        return;
    }

    int indiceLivro;
    printf("Digite o número do livro que deseja devolver: ");
    scanf("%d", &indiceLivro);

    if (indiceLivro < 1 || indiceLivro > usuario->num_livros_emprestados)
    {
        printf("Número de livro inválido.\n");
        return;
    }

    Livro *livro = &biblioteca[usuario->livros_emprestados[indiceLivro - 1] - 1];

    livro->disponivel = 1;

    for (int i = indiceLivro - 1; i < usuario->num_livros_emprestados - 1; i++)
    {
        usuario->livros_emprestados[i] = usuario->livros_emprestados[i + 1];
    }

    usuario->num_livros_emprestados--;

    printf("Livro devolvido com sucesso!\n");
}

void calcularMulta()
{
    void verificadorUsuario();

    int indiceUsuario;
    printf("Digite o número do usuário para calcular a multa: ");
    scanf("%d", &indiceUsuario);

    void usuarioValido(int indiceUsuario);

    Usuario *usuario = &usuarios[indiceUsuario - 1];

    if (usuario->num_livros_emprestados == 0)
    {
        printf("O usuário não possui livros emprestados.\n");
        return;
    }

    time_t now;
    time(&now);

    double multaTotal = 0.0;

    for (int i = 0; i < usuario->num_livros_emprestados; i++)
    {
        Livro *livro = &biblioteca[usuario->livros_emprestados[i] - 1];

        double diasAtraso = difftime(now, livro->data_emprestimo) / (60 * 60 * 24); // quando for testar da pra manpular o tempo
        double multa = diasAtraso * 0.5;                                            // 50 centavos por dia de atraso
        multaTotal += multa;
    }
    printf("O usuário deve pagar uma multa de R$%.2f.\n", multaTotal);
}



void adicionarUsuario()
{
    if (numUsuarios >= MAX_USERS)
    {
        printf("O número máximo de usuários foi atingido. Não é possível adicionar mais usuários.\n");
        return;
    }

    Usuario novoUsuario;
    printf("Digite o nome do usuário: ");
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0';

    printf("Digite o tipo do usuário (administrador, funcionario, leitor): ");
    fgets(novoUsuario.tipo, sizeof(novoUsuario.tipo), stdin);
    novoUsuario.tipo[strcspn(novoUsuario.tipo, "\n")] = '\0';

    novoUsuario.num_livros_emprestados = 0;
    novoUsuario.id = numUsuarios + 1;

    usuarios[numUsuarios++] = novoUsuario;

    printf("Usuário adicionado com sucesso!\n");
}

int compararNome(const void *a, const void *b) {
    Usuario *userA = (Usuario *)a;
    Usuario *userB = (Usuario *)b;
    return strcmp(userA->nome, userB->nome);
}

void exibirUsuarios()
{
    void verificadorUsuario();

    qsort(usuarios, numUsuarios, sizeof(Usuario), compararNome);

    printf("Usuários cadastrados:\n");
    for (int i = 0; i < numUsuarios; i++)
    {
        printf("Usuário %d:\n", usuarios[i].id);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Tipo: %s\n", usuarios[i].tipo);
        printf("\n");
    }
}

void atualizarUsuario()
{
    void verificadorUsuario();

    int indiceUsuario;
    printf("Digite o número do usuário que deseja atualizar: ");
    scanf("%d", &indiceUsuario);

    void usuarioValido(int indiceUsuario);

    Usuario *usuario = &usuarios[indiceUsuario - 1];

    printf("Digite o novo nome do usuário: ");
    getchar(); // Limpa o buffer do teclado
    fgets(usuario->nome, sizeof(usuario->nome), stdin);
    usuario->nome[strcspn(usuario->nome, "\n")] = '\0';

    printf("Digite o novo tipo do usuário: ");
    fgets(usuario->tipo, sizeof(usuario->tipo), stdin);
    usuario->tipo[strcspn(usuario->tipo, "\n")] = '\0';

    printf("Usuário atualizado com sucesso!\n");
}

void deletarUsuario()
{
    void verificadorUsuario();

    int indiceUsuario;
    printf("Digite o número do usuário que deseja deletar: ");
    scanf("%d", &indiceUsuario);

    void usuarioValido(int indiceUsuario);

    for (int i = indiceUsuario - 1; i < numUsuarios - 1; i++)
    {
        usuarios[i] = usuarios[i + 1];
    }

    numUsuarios--;

    printf("Usuário deletado com sucesso!\n");
}

void usuarioValido(int indiceUsuario)
{
    if (indiceUsuario < 1 || indiceUsuario > numUsuarios)
    {
        printf("Número de usuário inválido.\n");
        return;
    }
}
void verificadorUsuario(){
    if (numUsuarios == 0)
    {
        printf("Não há usuários cadastrados.\n");
        return;
    }
}


