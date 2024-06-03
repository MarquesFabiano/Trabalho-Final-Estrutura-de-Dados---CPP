#include <iostream>
#include <fstream>
#include <string>
#include <limits>

struct Aluno 
{
    int id;
    std::string nome;
    int semestre;
    int anoIngresso;
    std::string curso;
};

struct Contribuicao 
{
    int idAluno;
    int mes;
    int ano;
    float valor;
    Contribuicao* proximo;
};

Aluno* alunos = nullptr;
int totalAlunos = 0;
int proximoID = 1;
Contribuicao* contribuicoes = nullptr;

void LimparBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void redimensionarAlunos(int novoTamanho)
{
    Aluno* novoArray = new Aluno[novoTamanho];
    for (int i = 0; i < totalAlunos; ++i)
    {
        novoArray[i] = alunos[i];
    }
    delete[] alunos;
    alunos = novoArray;
}

void inserirAluno() 
{
    if (totalAlunos % 10 == 0)
    {
        redimensionarAlunos(totalAlunos + 10);
    }

    Aluno& a = alunos[totalAlunos];
    a.id = proximoID++;
    std::cout << "Nome: ";
    std::getline(std::cin, a.nome);
    std::cout << "Semestre: ";
    std::cin >> a.semestre;
    std::cout << "Ano de Ingresso: ";
    std::cin >> a.anoIngresso;
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

        switch (opcaoCurso)
        {
            case 1:
                a.curso = "GE";
                break;
            case 2:
                a.curso = "SI";
                break;
            case 3:
                a.curso = "DSM";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcaoCurso < 1 || opcaoCurso > 3);

    ++totalAlunos;
}

void editarAluno() 
{
    int id;
    std::cout << "Editar Aluno: \n";
    std::cout << "Insira o id: ";
    std::cin >> id;
    LimparBuffer();

    for (int i = 0; i < totalAlunos; ++i) 
    {
        if (alunos[i].id == id) 
        {
            std::cout << "Nome: ";
            std::getline(std::cin, alunos[i].nome);
            std::cout << "Semestre: ";
            std::cin >> alunos[i].semestre;
            std::cout << "Ano de Ingresso: ";
            std::cin >> alunos[i].anoIngresso;
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

                switch (opcaoCurso)
                {
                    case 1:
                        alunos[i].curso = "GE";
                        break;
                    case 2:
                        alunos[i].curso = "SI";
                        break;
                    case 3:
                        alunos[i].curso = "DSM";
                        break;
                    default:
                        std::cout << "Opção inválida! Tente novamente.\n";
                }
            } while (opcaoCurso < 1 || opcaoCurso > 3);

            return;
        }
    }

    std::cout << "Não foi possível encontrar este id.\n";
}

void carregarAlunos()
{
    std::ifstream arquivo("alunos.txt");
    if (!arquivo.is_open()) 
    {
        std::cout << "Não foi possível abrir o arquivo.\n";
        return;
    }

    totalAlunos = 0;
    Aluno a;
    while (arquivo >> a.id)
    {
        arquivo.ignore();
        std::getline(arquivo, a.nome, '\t');
        arquivo >> a.semestre >> a.anoIngresso;
        arquivo.ignore();
        std::getline(arquivo, a.curso);

        if (totalAlunos % 10 == 0)
        {
            redimensionarAlunos(totalAlunos + 10);
        }

        alunos[totalAlunos++] = a;

        if (a.id >= proximoID) {
            proximoID = a.id + 1;
        }
    }

    arquivo.close();
}

void gravarAlunos()
{
    std::ofstream arquivo("alunos.txt");
    if (!arquivo.is_open())
    {
        std::cout << "Não foi possível abrir o arquivo.\n";
        return;
    }

    for (int i = 0; i < totalAlunos; ++i)
    {
        arquivo << alunos[i].id << "\t" << alunos[i].nome << "\t" << alunos[i].semestre << "\t" << alunos[i].anoIngresso << "\t" << alunos[i].curso << "\n";
    }

    arquivo.close();
}

bool verificarIdAluno(int id) 
{
    for (int i = 0; i < totalAlunos; ++i) 
    {
        if (alunos[i].id == id) 
        {
            return true;
        }
    }
    return false;
}

void cadastrarContribuicao() 
{
    int id;
    std::cout << "Insira o ID do aluno: ";
    std::cin >> id;
    LimparBuffer();

    if (!verificarIdAluno(id)) 
    {
        std::cout << "ID do aluno não encontrado.\n";
        return;
    }

    Contribuicao* novaContribuicao = new Contribuicao;
    novaContribuicao->idAluno = id;

    std::cout << "Mês (1-12): ";
    std::cin >> novaContribuicao->mes;
    std::cout << "Ano (>= 2024): ";
    std::cin >> novaContribuicao->ano;
    std::cout << "Valor da contribuição: ";
    std::cin >> novaContribuicao->valor;
    LimparBuffer();

    novaContribuicao->proximo = contribuicoes;
    contribuicoes = novaContribuicao;

    std::cout << "Contribuição cadastrada com sucesso.\n";
}

void gravarContribuicoes() 
{
    std::ofstream arquivo("contribuintes.txt");
    if (!arquivo.is_open())
    {
        std::cout << "Não foi possível abrir o arquivo.\n";
        return;
    }

    Contribuicao* atual = contribuicoes;
    while (atual != nullptr) 
    {
        arquivo << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
        atual = atual->proximo;
    }

    arquivo.close();
}

void gravarContribuicoesPorCurso()
{
    std::ofstream arquivoDSM("contribuintes_DSM.txt");
    std::ofstream arquivoSI("contribuintes_SI.txt");
    std::ofstream arquivoGE("contribuintes_GE.txt");

    if (!arquivoDSM.is_open() || !arquivoSI.is_open() || !arquivoGE.is_open())
    {
        std::cout << "Não foi possível abrir um dos arquivos.\n";
        return;
    }

    Contribuicao* atual = contribuicoes;
    while (atual != nullptr) 
    {
        std::string curso;
        for (int i = 0; i < totalAlunos; ++i) 
        {
            if (alunos[i].id == atual->idAluno) 
            {
                curso = alunos[i].curso;
                break;
            }
        }

        if (curso == "DSM")
        {
            arquivoDSM << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
        }
        else if (curso == "SI")
        {
            arquivoSI << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
        }
        else if (curso == "GE")
        {
            arquivoGE << atual->idAluno << "\t" << atual->mes << "\t" << atual->ano << "\t" << atual->valor << "\n";
        }

        atual = atual->proximo;
    }

    arquivoDSM.close();
    arquivoSI.close();
    arquivoGE.close();
}

void menu()
{
    int opcao;
    do
    {
        std::cout << "Turma do Café! escolha sua opcao:\n";
        std::cout << "1. Inserir aluno\n";
        std::cout << "2. Editar aluno\n";
        std::cout << "3. Carregar alunos de arquivo\n";
        std::cout << "4. Gravar alunos em arquivo\n";
        std::cout << "5. Cadastrar contribuição\n";
        std::cout << "6. Gravar contribuições em arquivo\n";
        std::cout << "7. Gravar contribuições por curso\n";
        std::cout << "0. Encerrar o programa\n";
        std::cout << "Opção: ";
        std::cin >> opcao;
        LimparBuffer();

        switch (opcao)
        {
            case 1:
                inserirAluno();
                break;
            case 2:
                editarAluno();
                break;
            case 3:
                carregarAlunos();
                break;
            case 4:
                gravarAlunos();
                break;
            case 5:
                cadastrarContribuicao();
                break;
            case 6:
                gravarContribuicoes();
                break;
            case 7:
                gravarContribuicoesPorCurso();
                break;
            case 0:
                std::cout << "Adeus! :)\n";
                break;
            default:
                std::cout << "Escolha uma opcao valida!\n";
        }
    } while (opcao != 0);
}

int main()
{
    menu();
    delete[] alunos;

    Contribuicao* atual = contribuicoes;
    while (atual != nullptr) 
    {
        Contribuicao* temp = atual;
        atual = atual->proximo;
        delete temp;
    }

    return 0;
}
