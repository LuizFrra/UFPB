using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class RespostasView
    {
        public string comentarioID { get; set; }
        public List<Respostas> respostas { get; set; }

        public RespostasView()
        {
            respostas = new List<Respostas>();
        }
    }
}