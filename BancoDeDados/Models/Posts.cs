
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Posts
    {   
        public string PublicacaoID { get; set; }
        
        public string UserImage { get; set; }
        
        public string UserID { get; set; }

        public string UserName { get; set; }

        public string ImagePath { get; set; }

        [MaxLength(500), MinLength(1)]
        public string Texto { get; set; }

        public string Status { get; set; }        


    }
}