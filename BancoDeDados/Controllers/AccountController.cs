using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using BancoDeDados.Services.DataBase;
using System.Collections.Generic;
using BancoDeDados.Models;
using Microsoft.AspNetCore.Http;
using System;
using Microsoft.AspNetCore.Routing;

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

        [HttpPost]
        public IActionResult DoPost(string post, IFormFile image)
        {
            string userID = HttpContext.User.FindFirst("UserID").Value.ToString();

            if(!string.IsNullOrEmpty(post) || image != null)
                dataBase.DoPost(userID, post, image);
                
            return RedirectToAction("Index");
        }

        [HttpPost]
        public IActionResult DoComment(string texto, string publicacaoID)
        {
            if(!string.IsNullOrEmpty(texto) && !string.IsNullOrEmpty(publicacaoID))
            {
                string UserID  = HttpContext.User.FindFirst("UserID").Value.ToString();
                dataBase.DoComment(UserID, publicacaoID, texto);
            }
            
            return RedirectToAction("ViewComments", new RouteValueDictionary( new {Controller = "Account", Action="Viewcomments", postID = publicacaoID}));
        }
        /*https://stackoverflow.com/questions/1257482/redirecttoaction-with-parameter -> explicção desse redirectoaction */

        [HttpGet]
        public IActionResult ViewComments(string postID)
        {
            CommentsView comments =  new CommentsView();
            comments.comentarios = dataBase.GetComments(postID);
            comments.PublicacaoID = postID;
            return View("comentarios", comments);
        }

        [HttpPost]
        public IActionResult DoAnswer(string texto, string commentID)
        {
            string userID = HttpContext.User.FindFirst("UserID").Value.ToString();

            if(!string.IsNullOrEmpty(texto) && !string.IsNullOrEmpty(commentID))
                dataBase.DoAnswer(userID, commentID, texto);


            return RedirectToAction("ViewAnswers", new RouteValueDictionary( new {Controller = "Account", Action="ViewAnswers", commentID = commentID}));
        }

        [HttpGet]
        public IActionResult ViewAnswers(string commentID)
        {
            RespostasView respostas = new RespostasView();
            respostas.comentarioID = commentID;
            respostas.respostas = dataBase.GetAnswer(commentID);
            
            return View("answers", respostas);
        }
    }
}