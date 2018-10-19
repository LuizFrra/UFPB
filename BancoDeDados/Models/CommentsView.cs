using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class CommentsView
    {
        public List<Comentarios> comentarios { get; set; }

        public string PublicacaoID { get; set; }


        public CommentsView()
        {
            comentarios = new List<Comentarios>();
        }

    }
}