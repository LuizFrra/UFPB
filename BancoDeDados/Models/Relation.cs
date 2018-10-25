using System.Collections.Generic;

namespace BancoDeDados.Models
{
    public class Relation
    {
        public string myID { get; set; }
        public string MuralUserID { get; set; }
        public string MuralUserName { get; set; }
        public string MuralUserCity { get; set; }
        public string MuralUserImagePath { get; set; }
        public string Visibility { get; set; }
        public string Status { get; set; }

        public List<Posts> posts { get; set; }
        enum RelationSatus  {FriendSend = 1, FriendWait = 2, Friends = 3, Block = 4}
        /* STATUS
        Can return :
        NULL : no relationship
        1 : Friend Send
        2 : Friend wait
        3 : Friends
        4 : Block
        */

        public Relation()
        {
            posts = new List<Posts>();
        }
    }
}