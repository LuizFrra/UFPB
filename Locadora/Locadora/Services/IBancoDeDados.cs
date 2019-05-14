using System.Collections.Generic;

namespace Locadora.Services
{
    public interface IBancoDeDados
    {
        bool addClient(Cliente cliente);

        bool addCategoria(string categoria);

        bool addFilme(Filme filme);

        bool addEstrela(Estrela estrela);

        bool addFita(int filme);

        bool Alugar(Alugar alugar);

        
        bool Devolver(Alugar devolver);

        List<FilmesEmprestados> GetFitasAlugadasClientes(int cliente);
    }
}