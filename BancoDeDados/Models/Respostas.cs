
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados
{
    public class Respostas
    {
        public int RespostaID { get; set; }

        [Required]
        public int UserID { get; set; }

        [Required]
        public int ComentarioID { get; set; }

        [MaxLength(500), Required]
        public string Texto { get; set; }
    }
}