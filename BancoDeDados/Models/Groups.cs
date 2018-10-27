using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Http;

namespace BancoDeDados.Models
{
    public class Groups
    {
        public string ImagePath { get; set; }
        public string groupID { get; set; }

        [Required, MaxLength(30)]
        public string Nome { get; set; }

        public string Descricao { get; set; }

        public IFormFile Image { get; set; }

        public string Visibility { get; set; }

        public string Status { get; set; }

    }
}