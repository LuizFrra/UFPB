
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Posts
    {

        public int PublicacaoID { get; set; }
        
        public string UserImage { get; set; }
        public int UserID { get; set; }

        public string UserName { get; set; }

        public string ImagePath { get; set; }

        [MaxLength(500), MinLength(1)]
        public string Text { get; set; }

        


    }
}