
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Comentarios
    {
        
        public int ComentarioID { get; set; }

        [Required]
        public string PublicacaoID { get; set; }

        [Required]
        public int UserID { get; set; }

        [Required, MaxLength(500)]
        public string Texto { get; set; }


    }
}