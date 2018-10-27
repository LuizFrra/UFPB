
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Respostas
    {
        public string RespostaID { get; set; }
        public string Status { get; set; }
        public string UserImage { get; set; }
        public string UserID { get; set; }
        public string UserName { get; set; }

        [Required]
        public string Texto { get; set; }
    }
}