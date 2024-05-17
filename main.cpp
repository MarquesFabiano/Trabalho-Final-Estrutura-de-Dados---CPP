#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Participante 
{
    int id;
    std::string nome;
    int semestre;
    int anoIngresso;
    std::string curso;
};

std::vector<Participante> participantes;

void inserirParticipante() 
{
    Participante p;
    std::cout << "ID: ";
    std::cin >> p.id;
    std::cout << "Nome: ";
    std::cin >> p.nome;
    std::cout << "Semestre: ";
    std::cin >> p.semestre;
    std::cout << "Ano de Ingresso: ";
    std::cin >> p.anoIngresso;
    std::cout << "Curso (DSM/SI/GE): ";
    std::cin >> p.curso;

    participantes.push_back(p);
}

void editarParticipante() 
{
    int id;
    std::cout << "Editar Participante: \n";
    std::cout << "Insira o id: ";
    std::cin >> id;

    for (auto &p : participantes) 
    {
        if (p.id == id) 
        {
            std::cout << "Nome: ";
            std::cin >> p.nome;
            std::cout << "Semestre: ";
            std::cin >> p.semestre;
            std::cout << "Ano de Ingresso: ";
            std::cin >> p.anoIngresso;
            std::cout << "Curso (DSM/SI/GE): ";
            std::cin >> p.curso;
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

    participantes.clear();
    Participante p;
    while (arquivo >> p.id >> p.nome >> p.semestre >> p.anoIngresso >> p.curso)
    {
        participantes.push_back(p);
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

    for (const auto &p : participantes)
    {
        arquivo << p.id << " " << p.nome << " " << p.semestre << " " << p.anoIngresso << " " << p.curso << "\n";
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
        std::cout << "0. Encerrar o programa";
        std::cin >> opcao;

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
                std::cout << "escolha uma opcao valida!\n";
        }
    } while (opcao != 0);
}

int main()
{
    menu();
    return 0;
}
