using System.Collections.Generic;
using Microsoft.AspNetCore.Http;
using BancoDeDados.Models;

namespace BancoDeDados.Services.DataBase
{
    public interface IDataBase
    {
        bool Register(Users user);
        bool VerifyExistEmail(string email);
        bool AuthenticationLogin(HttpContext context, Login data);
        Dictionary<string,string> VerifyAuth(string email, string password);
        List<Dictionary<string, string>> SearchForName(string userName);
        Relation SearchUserByID(string myID, string userID);
        bool DoPost(string myID,string userID, string post, IFormFile image);
        List<Posts> GetPostsFriends(string myID);
        List<Comentarios> GetComments(string postID);
        bool DoComment(string userID, string postID, string text);
        List<Respostas> GetAnswer(string commentID);
        bool DoAnswer(string userID, string commentID, string texto);
        bool SendFriend(string myID, string userID);
        bool CancelFriendRequest(string myID, string userID);
        bool AcceptFriendRequest(string myID, string userID);
        bool UndoFriend(string myID, string userID);
        List<Posts> GetPostsMural(string myID, string userID);
        List<Friends> GetFriends(string userID);
        bool ChangePerfil(string userID, IFormFile image, string visibility, string city, string pass)
;    }
}