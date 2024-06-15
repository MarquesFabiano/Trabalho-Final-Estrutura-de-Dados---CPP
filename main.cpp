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
};

struct AlunoNode {
    Aluno data;
    AlunoNode* next;
};

struct Contribuicao {
    int idAluno;
    int mes;
    int ano;
    float valor;
};

struct ContribuicaoNode {
    Contribuicao data;
    ContribuicaoNode* next;
};

AlunoNode* alunos = NULL;
ContribuicaoNode* contribuicoes = NULL;
int proximoID = 1;

void LimparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void inserirAluno() {
    AlunoNode* novoAluno = new AlunoNode;
    novoAluno->data.id = proximoID++;
    std::cout << "Nome: ";
    std::getline(std::cin, novoAluno->data.nome);
    std::cout << "Semestre: ";
    std::cin >> novoAluno->data.semestre;
    std::cout << "Ano de Ingresso: ";
    std::cin >> novoAluno->data.anoIngresso;
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
                novoAluno->data.curso = "GE";
                break;
            case 2:
                novoAluno->data.curso = "SI";
                break;
            case 3:
                novoAluno->data.curso = "DSM";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcaoCurso < 1 || opcaoCurso > 3);

    novoAluno->next = alunos;
    alunos = novoAluno;
}

void editarAluno() {
    int id;
    std::cout << "Editar Aluno: \n";
    std::cout << "Insira o id: ";
    std::cin >> id;
    LimparBuffer();

    AlunoNode* atual = alunos;
    while (atual != NULL) {
        if (atual->data.id == id) {
            std::cout << "Novo Nome: ";
            std::getline(std::cin, atual->data.nome);
            std::cout << "Novo Semestre: ";
            std::cin >> atual->data.semestre;
            std::cout << "Novo Ano de Ingresso: ";
            std::cin >> atual->data.anoIngresso;
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
                        atual->data.curso = "GE";
                        break;
                    case 2:
                        atual->data.curso = "SI";
                        break;
                    case 3:
                        atual->data.curso = "DSM";
                        break;
                    default:
                        std::cout << "Opção inválida! Tente novamente.\n";
                }
            } while (opcaoCurso < 1 || opcaoCurso > 3);
            break;
        }
        atual = atual->next;
    }
}

void carregarAlunos() {
    std::ifstream arquivo("alunos.txt");
    if (arquivo.is_open()) {
        while (!arquivo.eof()) {
            AlunoNode* novoAluno = new AlunoNode;
            arquivo >> novoAluno->data.id;
            arquivo.ignore();
            std::getline(arquivo, novoAluno->data.nome);
            arquivo >> novoAluno->data.semestre >> novoAluno->data.anoIngresso;
            arquivo.ignore();
            std::getline(arquivo, novoAluno->data.curso);

            novoAluno->next = alunos;
            alunos = novoAluno;

            if (novoAluno->data.id >= proximoID) {
                proximoID = novoAluno->data.id + 1;
            }

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
        AlunoNode* atual = alunos;
        while (atual != NULL) {
            arquivo << atual->data.id << "\n" << atual->data.nome << "\n" << atual->data.semestre << "\n" << atual->data.anoIngresso << "\n" << atual->data.curso << "\n";
            atual = atual->next;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir arquivo para gravação.\n";
    }
}

void cadastrarContribuicao() {
    ContribuicaoNode* novaContribuicao = new ContribuicaoNode;
    std::cout << "ID do Aluno: ";
    std::cin >> novaContribuicao->data.idAluno;
    std::cout << "Mês: ";
    std::cin >> novaContribuicao->data.mes;
    std::cout << "Ano: ";
    std::cin >> novaContribuicao->data.ano;
    std::cout << "Valor: ";
    std::cin >> novaContribuicao->data.valor;
    LimparBuffer();

    novaContribuicao->next = contribuicoes;
    contribuicoes = novaContribuicao;
}

void gravarContribuicoes() {
    std::ofstream arquivo("contribuicoes.txt");
    if (arquivo.is_open()) {
        ContribuicaoNode* atual = contribuicoes;
        while (atual != NULL) {
            arquivo << atual->data.idAluno << "\t" << atual->data.mes << "\t" << atual->data.ano << "\t" << atual->data.valor << "\n";
            atual = atual->next;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir arquivo para gravação de contribuições.\n";
    }
}

void gravarContribuicoesPorCurso() {
    std::ofstream arquivoDSM("contribuicoes_DSM.txt");
    std::ofstream arquivoSI("contribuicoes_SI.txt");
    std::ofstream arquivoGE("contribuicoes_GE.txt");

    ContribuicaoNode* atual = contribuicoes;
    while (atual != NULL) {
        AlunoNode* alunoAtual = alunos;
        while (alunoAtual != NULL) {
            if (alunoAtual->data.id == atual->data.idAluno) {
                if (alunoAtual->data.curso == "DSM") {
                    arquivoDSM << atual->data.idAluno << "\t" << atual->data.mes << "\t" << atual->data.ano << "\t" << atual->data.valor << "\n";
                } else if (alunoAtual->data.curso == "SI") {
                    arquivoSI << atual->data.idAluno << "\t" << atual->data.mes << "\t" << atual->data.ano << "\t" << atual->data.valor << "\n";
                } else if (alunoAtual->data.curso == "GE") {
                    arquivoGE << atual->data.idAluno << "\t" << atual->data.mes << "\t" << atual->data.ano << "\t" << atual->data.valor << "\n";
                }
                break;
            }
            alunoAtual = alunoAtual->next;
        }
        atual = atual->next;
    }

    arquivoDSM.close();
    arquivoSI.close();
    arquivoGE.close();
}

void limparMemoria() {
    AlunoNode* atualAluno = alunos;
    while (atualAluno != NULL) {
        AlunoNode* tempAluno = atualAluno;
        atualAluno = atualAluno->next;
        delete tempAluno;
    }

    ContribuicaoNode* atualContribuicao = contribuicoes;
    while (atualContribuicao != NULL) {
        ContribuicaoNode* tempContribuicao = atualContribuicao;
        atualContribuicao = atualContribuicao->next;
        delete tempContribuicao;
    }
}


void menu() {
    int opcao;
    do {
        std::cout << "Turma do CafÃ©! escolha sua opcao:\n";
        std::cout << "1. Inserir aluno\n";
        std::cout << "2. Editar aluno\n";
        std::cout << "3. Carregar alunos de arquivo\n";
        std::cout << "4. Salvar alunos em arquivo\n";
        std::cout << "5. Cadastrar contribuiÃ§Ã£o\n";
        std::cout << "6. Salvar contribuiÃ§Ãµes em arquivo\n";
        std::cout << "7. Salvar contribuiÃ§Ãµes por curso\n";
        std::cout << "0. Encerrar o programa\n";
        std::cout << "OpÃ§Ã£o: ";
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
                std::cout << "Foi cadatrada as contribuiÃ§Ãµes!\n";
                break;
            case 6:
                gravarContribuicoes();
                std::cout << "Salva todas as contribuiÃ§Ãµes\n";
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
