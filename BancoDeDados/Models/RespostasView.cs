using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class RespostasView
    {
        public string myID { get; set; }
        public string MuralUserIDPost { get; set; }
        public string AuthorIDPost { get; set; }
        public string AuthorIDCommnet { get; set; }
        public string comentarioID { get; set; }
        public List<Respostas> respostas { get; set; }

        public RespostasView()
        {
            respostas = new List<Respostas>();
        }
    }
}