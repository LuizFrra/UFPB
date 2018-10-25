
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Comentarios
    {
        public string Status { get; set; }
        public string ComentarioID { get; set; }
        public string UserID { get; set; }
        public string UserName { get; set; }
        public string UserImage { get; set; }

        [Required]
        public string Texto { get; set; }


    }
}