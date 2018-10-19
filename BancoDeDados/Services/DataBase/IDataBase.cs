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
        Dictionary<string, string> SearchUserByID(string id);
        bool DoPost(string userID, string post, IFormFile image);
        List<Posts> GetPosts();
    }
}