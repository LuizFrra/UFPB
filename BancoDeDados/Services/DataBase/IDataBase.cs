#region Using
using System.Collections.Generic;
using Microsoft.AspNetCore.Http;
using BancoDeDados.Models;
#endregion

namespace BancoDeDados.Services.DataBase
{
    public interface IDataBase
    {
        bool Register(Users user);
        bool VerifyExistEmail(string email);
        bool AuthenticationLogin(HttpContext context, Login data);
        Dictionary<string,string> VerifyAuth(string email, string password);
        List<Dictionary<string, string>> SearchForName(string myID, string userName);
        Relation SearchUserByID(string myID, string userID);
        bool DoPost(string myID,string userID, string post, IFormFile image);
        List<Posts> GetPostsFriends(string myID);
        CommentsView GetComments(string myID, string postID);
        bool DoComment(string userID, string postID, string text);
        RespostasView GetAnswer(string myID, string commentID);
        bool DoAnswer(string userID, string commentID, string texto);
        bool SendFriend(string myID, string userID);
        bool CancelFriendRequest(string myID, string userID);
        bool AcceptFriendRequest(string myID, string userID);
        bool UndoFriend(string myID, string userID);
        bool BlockUser(string myID, string userID);
        List<Relation> GetBlockUsers(string myID);
        bool UnLockUser(string myID, string userID);
        List<Posts> GetPostsMural(string myID, string userID);
        List<Friends> GetFriends(string userID);
        bool ChangePerfil(string userID, IFormFile image, string visibility, string city, string pass);
        bool DeleteAnswer(string myID, string answerID);
        bool DeleteComment(string myID, string commentID);
        bool DeletePost(string myID, string postID);
        bool CreateGroup(string myID, Groups groups);
        List<Groups> GetGroups(string myID);
        bool JoinGroup(string myID, string groupID);
        bool LetBeAdmin(string myID, string groupID);
        bool RemoveStatusFromGroup(string myID, string groupID);
        ManageGroup ManageGroup(string myID, string groupID);
        bool ManageUserGroup(string userID, string groupID, int status);
        bool ChangeGroup(string myID, Groups group);
        bool DeleteGroup(string userID, string groupID);
        List<Groups> GetUserGroups(string myID, string userID);
        bool DoPostGroup(string myID, string groupID, string post, IFormFile image);
        GroupView GetGroupContent(string myID, string groupID);
        bool DeletePostGroup(string postID);
   }
}