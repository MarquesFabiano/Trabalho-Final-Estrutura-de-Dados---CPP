#include <iostream>
#include <fstream>
#include <string>
#include <limits>

struct Aluno {
    int id;
    std::string nome;
    int semestre;
    int anoIngresso;
    std::string curso;
    Aluno* proximo;
};

struct Contribuicao {
    int idAluno;
    int mes;
    int ano;
    float valor;
    Contribuicao* proximo;
};

Aluno* alunos = NULL;
int proximoID = 1;
Contribuicao* contribuicoes = NULL;

void LimparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void inserirAluno() {
    Aluno* novoAluno = new Aluno;
    novoAluno->id = proximoID++;
    std::cout << "Nome: ";
    std::getline(std::cin, novoAluno->nome);
    std::cout << "Semestre: ";
    std::cin >> novoAluno->semestre;
    std::cout << "Ano de Ingresso: ";
    std::cin >> novoAluno->anoIngresso;
    LimparBuffer();

    int opcaoCurso;
    do {
        std::cout << "Curso (escolha uma opção): \n";
        std::cout << "1. GE\n";
        std::cout << "2. SI\n";
        std::cout << "3. DSM\n";
        std::cout << "Opção: ";
        std::cin >> opcaoCurso;
        LimparBuffer();

        switch (opcaoCurso) {
            case 1:
                novoAluno->curso = "GE";
                break;
            case 2:
                novoAluno->curso = "SI";
                break;
            case 3:
                novoAluno->curso = "DSM";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcaoCurso < 1 || opcaoCurso > 3);

    novoAluno->proximo = alunos;
    alunos = novoAluno;
}

void editarAluno() {
    int id;
    std::cout << "Editar Aluno: \n";
    std::cout << "Insira o id: ";
    std::cin >> id;
    LimparBuffer();

    Aluno* atual = alunos;
    while (atual != NULL) {
        if (atual->id == id) {
            std::cout << "Novo Nome: ";
            std::getline(std::cin, atual->nome);
            std::cout << "Novo Semestre: ";
            std::cin >> atual->semestre;
            std::cout << "Novo Ano de Ingresso: ";
            std::cin >> atual->anoIngresso;
            LimparBuffer();

            int opcaoCurso;
            do {
                std::cout << "Novo Curso (escolha uma opção): \n";
                std::cout << "1. GE\n";
                std::cout << "2. SI\n";
                std::cout << "3. DSM\n";
                std::cout << "Opção: ";
                std::cin >> opcaoCurso;
                LimparBuffer();

                switch (opcaoCurso) {
                    case 1:
                        atual->curso = "GE";
                        break;
                    case 2:
                        atual->curso = "SI";
                        break;
                    case 3:
                        atual->curso = "DSM";
                        break;
                    default:
                        std::cout << "Opção inválida! Tente novamente.\n";
                }
            } while (opcaoCurso < 1 || opcaoCurso > 3);
            break;
        }
        atual = atual->proximo;
    }
}

void carregarAlunos() {
    std::ifstream arquivo("alunos.txt");
    if (arquivo.is_open()) {
        while (!arquivo.eof()) {
            Aluno* novoAluno = new Aluno;
            arquivo >> novoAluno->id;
            arquivo.ignore();
            std::getline(arquivo, novoAluno->nome);
            arquivo >> novoAluno->semestre >> novoAluno->anoIngresso;
            arquivo.ignore();
            std::getline(arquivo, novoAluno->curso);

           
            if (novoAluno->id >= proximoID) { //novo id agora é auto
                proximoID = novoAluno->id + 1;
            }

            novoAluno->proximo = alunos;
            alunos = novoAluno;

            if (arquivo.peek() == EOF) break;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir arquivo para leitura.\n";
    }
}

void gravarAlunos() {
    std::ofstream arquivo("alunos.txt");
    if (arquivo.is_open()) {
        Aluno* atual = alunos;
        while (atual != NULL) {
            arquivo << atual->id << "\n" << atual->nome << "\n" << atual->semestre << "\n" << atual->anoIngresso << "\n" << atual->curso << "\n";
            atual = atual->proximo;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir arquivo para gravação.\n";
    }
}


void cadastrarContribuicao() {
    Contribuicao* novaContribuicao = new Contribuicao;
    std::cout << "ID do Aluno: ";
    std::cin >> novaContribuicao->idAluno;
    std::cout << "Mês: ";
    std::cin >> novaContribuicao->mes;
    std::cout << "Ano: ";
    std::cin >> novaContribuicao->ano;
    std::cout << "Valor: ";
    std::cin >> novaContribuicao->valor;
    LimparBuffer();

    novaContribuicao->proximo = contribuicoes;
    contribuicoes = novaContribuicao;
}

void gravarContribuicoes() {
    std::ofstream arquivo("contribuicoes.txt");
    Contribuicao* atual = contribuicoes;
    while (atual != NULL) {
        arquivo << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
        atual = atual->proximo;
    }
}

void gravarContribuicoesPorCurso() {
    std::ofstream arquivoDSM("contribuicoes_DSM.txt");
    std::ofstream arquivoSI("contribuicoes_SI.txt");
    std::ofstream arquivoGE("contribuicoes_GE.txt");

    Contribuicao* atual = contribuicoes;
    while (atual != NULL) {
        Aluno* aluno = alunos;
        while (aluno != NULL) {
            if (aluno->id == atual->idAluno) {
                if (aluno->curso == "DSM") {
                    arquivoDSM << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
                } else if (aluno->curso == "SI") {
                    arquivoSI << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
                } else if (aluno->curso == "GE") {
                    arquivoGE << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
                }
                break;
            }
            aluno = aluno->proximo;
        }
        atual = atual->proximo;
    }

    arquivoDSM.close();
    arquivoSI.close();
    arquivoGE.close();
}

void limparMemoria() {
    Aluno* atualAluno = alunos;
    while (atualAluno != NULL) {
        Aluno* tempAluno = atualAluno;
        atualAluno = atualAluno->proximo;
        delete tempAluno;
    }

    Contribuicao* atualContribuicao = contribuicoes;
    while (atualContribuicao != NULL) {
        Contribuicao* tempContribuicao = atualContribuicao;
        atualContribuicao = atualContribuicao->proximo;
        delete tempContribuicao;
    }
}


void menu() {
    int opcao;
    do {
        std::cout << "Turma do Café! escolha sua opcao:\n";
        std::cout << "1. Inserir aluno\n";
        std::cout << "2. Editar aluno\n";
        std::cout << "3. Carregar alunos de arquivo\n";
        std::cout << "4. Salvar alunos em arquivo\n";
        std::cout << "5. Cadastrar contribuição\n";
        std::cout << "6. Salvar contribuições em arquivo\n";
        std::cout << "7. Salvar contribuições por curso\n";
        std::cout << "0. Encerrar o programa\n";
        std::cout << "Opção: ";
        std::cin >> opcao;
        LimparBuffer();

        switch (opcao) {
            case 1:
                inserirAluno();
                break;
            case 2:
                editarAluno();
                std::cout << "Edite o alunon";
                break;
            case 3:
                carregarAlunos();
                std::cout << "Arquivo carregado com sucesso)\n";
                break;
            case 4:
                gravarAlunos();
                std::cout << "Salvado com sucesso!\n";
                break;
            case 5:
                cadastrarContribuicao();
                std::cout << "Foi cadatrada as contribuições!\n";
                break;
            case 6:
                gravarContribuicoes();
                std::cout << "Salva todas as contribuições\n";
                break;
            case 7:
                gravarContribuicoesPorCurso();
                std::cout << "Cadastrado por curso\n";
                break;
            case 0:
                std::cout << "Adeus! :)\n";
                break;
            default:
                std::cout << "Escolha uma opcao valida!\n";
        }
    } while (opcao != 0);
}

int main() {
    carregarAlunos();
    menu();
    limparMemoria();
    return 0;
}
