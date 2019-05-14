using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Locadora.Services;
using Microsoft.AspNetCore.Mvc;

namespace Locadora.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LocadoraController : ControllerBase
    {
        private readonly IBancoDeDados _BancoDeDados;

        public LocadoraController(IBancoDeDados BancoDeDados) => _BancoDeDados = BancoDeDados;

        [HttpPost("Devolver")]
        public void Devolver([FromBody]Alugar devolver)
        {
            _BancoDeDados.Devolver(devolver);
        }

        [HttpPost("Alugar")]
        public void Alugar([FromBody]Alugar alugar)
        {
            _BancoDeDados.Alugar(alugar);
        }

        [HttpPost("addFita")]
        public void addFita([FromBody]int filme)
        {
            _BancoDeDados.addFita(filme);
        }

        [HttpPost("addEstrela")]
        public void addEstrela([FromBody] Estrela estrela)
        {
            _BancoDeDados.addEstrela(estrela);
        }

        [HttpPost("addFilme")]
        public void addFilme([FromBody] Filme filme)
        {
            _BancoDeDados.addFilme(filme);
        }

        [HttpPost("addCategoria")]
        public void addCategoria([FromBody] string categoria)
        {
            _BancoDeDados.addCategoria(categoria);
        }

        [HttpPost("addCliente")]
        public void addCliente([FromBody] Cliente cliente)
        {
            _BancoDeDados.addClient(cliente);
        }

        [HttpGet("{IDcliente}")]
        public List<FilmesEmprestados> GetFitasAlugadasClientes(int IDcliente)
        {
            var filmesEmprestados = _BancoDeDados.GetFitasAlugadasClientes(IDcliente);

            return filmesEmprestados;
        }

    }
}
