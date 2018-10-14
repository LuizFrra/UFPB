using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Login
    {
        [EmailAddress, Required]
        public string Email { get; set; }
        
        [DataType(DataType.Password), Required]
        public string Password { get; set; }
    }
}