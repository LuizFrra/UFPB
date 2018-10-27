using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class ManageGroup
    {
        public string groupID { get; set; }

        public List<UsersGroups> Users { get; set; }

        public ManageGroup()
        {
            Users = new List<UsersGroups>();
        }
    }
}