using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class Users
    {
        public int UserID { get; set; }
        
        [Required, MaxLength(100)]
        public string Name { get; set; }
        
        [Required, EmailAddress, MaxLength(100)]
        public string Email { get; set; }
        
        [Required, DataType(DataType.Password), MaxLength(25)]
        public string Password { get; set; }
        
        [MaxLength(25)]
        public string City { get; set; }
        
        [MaxLength(1024)]
        public string ImagePath { get; set; }
        
        public int Visibility { get; set; }

        
    }    
}