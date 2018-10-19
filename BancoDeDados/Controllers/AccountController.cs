using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using BancoDeDados.Services.DataBase;
using System.Collections.Generic;
using BancoDeDados.Models;
using Microsoft.AspNetCore.Http;

namespace BancoDeDados.Controllers
{
    [Authorize(Roles = "User")]
    public class AccountController : Controller
    {
        
        private readonly IDataBase dataBase;

        public AccountController(IDataBase _dataBase) => dataBase = _dataBase;
        
        [HttpGet]
        public IActionResult Index()
        {
            PostsIndex postsIndex = new PostsIndex();
            
            postsIndex.Posts = dataBase.GetPosts();
            
            postsIndex.UserLogged = HttpContext.User.FindFirst("Nome").Value.ToString();

            return View("index", postsIndex);
        }

        [HttpGet]
        public IActionResult SearchUser()
        {
            return View("searchuser");
        }

        [HttpPost]
        public IActionResult SearchUser(string name)
        {
            List<Dictionary<string,string>> data = new List<Dictionary<string,string>>();
            
            if(!string.IsNullOrEmpty(name))
            {
                data = dataBase.SearchForName(name);
                return View("searchuser", data);
            }
            
            return View("searchuser", null);
        }

        [HttpGet]
        public IActionResult Profile(string id)
        {
            
            Dictionary<string, string> data = new Dictionary<string, string>();

            if(!string.IsNullOrEmpty(id))
                data = dataBase.SearchUserByID(id);
            
            return View("profile", data);
        }
    
        public IActionResult DoPost(string post, IFormFile image)
        {
            string userID = HttpContext.User.FindFirst("UserID").Value.ToString();

            if(!string.IsNullOrEmpty(post) || image != null)
                dataBase.DoPost(userID, post, image);
                
            return RedirectToAction("Index");
        }
    }
}