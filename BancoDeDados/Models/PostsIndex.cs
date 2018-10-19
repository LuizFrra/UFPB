

using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace BancoDeDados.Models
{
    public class PostsIndex
    {
        public string UserLogged { get; set; }

        public List<Posts> Posts { get; set; }

        public PostsIndex()
        {
            Posts = new List<Posts>();
        }
    }
}