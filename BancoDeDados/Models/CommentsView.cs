using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class CommentsView
    {
        public string myID { get; set; }
        public string MUserID { get; set; }
        public string AuthorIDPublicacao { get; set; }
        public string PublicacaoID { get; set; }
        
        public List<Comentarios> comentarios { get; set; }

        public CommentsView()
        {
            comentarios = new List<Comentarios>();
        }

    }
}