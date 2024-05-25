#include <iostream>
#include <fstream>
#include <string>
#include <limits>

struct Participante 
{
    int id;
    std::string nome;
    int semestre;
    int anoIngresso;
    std::string curso;
};

Participante* participantes = nullptr;
int totalParticipantes = 0;
int proximoID = 1;

void LimparBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void redimensionarParticipantes(int novoTamanho)
{
    Participante* novoArray = new Participante[novoTamanho];
    for (int i = 0; i < totalParticipantes; ++i)
    {
        novoArray[i] = participantes[i];
    }
    delete[] participantes;
    participantes = novoArray;
}

void inserirParticipante() 
{
    if (totalParticipantes % 10 == 0)
    {
        redimensionarParticipantes(totalParticipantes + 10);
    }

    Participante& p = participantes[totalParticipantes];
    p.id = proximoID++;
    std::cout << "Nome: ";
    std::getline(std::cin, p.nome);
    std::cout << "Semestre: ";
    std::cin >> p.semestre;
    std::cout << "Ano de Ingresso: ";
    std::cin >> p.anoIngresso;
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
                p.curso = "GE";
                break;
            case 2:
                p.curso = "SI";
                break;
            case 3:
                p.curso = "DSM";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcaoCurso < 1 || opcaoCurso > 3);

    ++totalParticipantes;
}

void editarParticipante() 
{
    int id;
    std::cout << "Editar Participante: \n";
    std::cout << "Insira o id: ";
    std::cin >> id;
    LimparBuffer();

    for (int i = 0; i < totalParticipantes; ++i) 
    {
        if (participantes[i].id == id) 
        {
            std::cout << "Nome: ";
            std::getline(std::cin, participantes[i].nome);
            std::cout << "Semestre: ";
            std::cin >> participantes[i].semestre;
            std::cout << "Ano de Ingresso: ";
            std::cin >> participantes[i].anoIngresso;
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
                        participantes[i].curso = "GE";
                        break;
                    case 2:
                        participantes[i].curso = "SI";
                        break;
                    case 3:
                        participantes[i].curso = "DSM";
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

void carregarParticipantes()
{
    std::ifstream arquivo("participantes.txt");
    if (!arquivo.is_open()) 
    {
        std::cout << "Não foi possível abrir o arquivo.\n";
        return;
    }

    totalParticipantes = 0;
    Participante p;
    while (arquivo >> p.id)
    {
        arquivo.ignore();
        std::getline(arquivo, p.nome, '\t');
        arquivo >> p.semestre >> p.anoIngresso;
        arquivo.ignore();
        std::getline(arquivo, p.curso);

        if (totalParticipantes % 10 == 0)
        {
            redimensionarParticipantes(totalParticipantes + 10);
        }

        participantes[totalParticipantes++] = p;

        if (p.id >= proximoID) {
            proximoID = p.id + 1;
        }
    }

    arquivo.close();
}

void gravarParticipantes()
{
    std::ofstream arquivo("participantes.txt");
    if (!arquivo.is_open())
    {
        std::cout << "Não foi possível abrir o arquivo.\n";
        return;
    }

    for (int i = 0; i < totalParticipantes; ++i)
    {
        arquivo << participantes[i].id << "\t" << participantes[i].nome << "\t" << participantes[i].semestre << "\t" << participantes[i].anoIngresso << "\t" << participantes[i].curso << "\n";
    }

    arquivo.close();
}

void menu()
{
    int opcao;
    do
    {
        std::cout << "Turma do Café! escolha sua opcao:\n";
        std::cout << "1. Inserir participante\n";
        std::cout << "2. Editar participante\n";
        std::cout << "3. Carregar participantes de arquivo\n";
        std::cout << "4. Gravar participantes em arquivo\n";
        std::cout << "0. Encerrar o programa\n";
        std::cout << "Opção: ";
        std::cin >> opcao;
        LimparBuffer();

        switch (opcao)
        {
            case 1:
                inserirParticipante();
                break;
            case 2:
                editarParticipante();
                break;
            case 3:
                carregarParticipantes();
                break;
            case 4:
                gravarParticipantes();
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
    carregarParticipantes();
    menu();
    delete[] participantes;
    return 0;
}
