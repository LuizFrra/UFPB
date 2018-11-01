using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class GroupView
    {
        public string myID { get; set; }
        public string groupID { get; set; }
        public string GroupName { get; set; }
        public string GroupImage { get; set; }
        public string staff { get; set; }
        public List<Posts> posts { get; set; }

        public GroupView()
        {
            posts = new List<Posts>();
        }

    }
}