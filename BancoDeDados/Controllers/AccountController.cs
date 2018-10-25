using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.ActionConstraints;
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

        public AccountController(IDataBase _dataBase)
        {
            dataBase = _dataBase;

        }
        
        [HttpGet]
        public IActionResult Index()
        {

            PostsIndex postsIndex = new PostsIndex();
            
            postsIndex.UserLoggedID = HttpContext.User.FindFirst("UserID").Value.ToString();
            postsIndex.ImagePath = HttpContext.User.FindFirst("ImagePath").Value.ToString();
            postsIndex.UserLogged = HttpContext.User.FindFirst("Nome").Value.ToString();

            postsIndex.Posts = dataBase.GetPostsFriends(postsIndex.UserLoggedID);

            return View("index", postsIndex);
        }

        [HttpGet]
        public IActionResult Logout()
        {
            HttpContext.Response.Cookies.Delete("Auth");
            return RedirectToAction("Index", "Home");
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
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            Relation relation = new Relation();

            if(id != myID && !string.IsNullOrEmpty(id))
                relation = dataBase.SearchUserByID(myID, id);
            else
            {
                relation = dataBase.SearchUserByID(myID, id);
                relation.Status = "10";
            }
            
            relation.posts = dataBase.GetPostsMural(myID, id);

            return View("profile", relation);
        }

        [HttpPost]
        public IActionResult DoPost(string userID, string post, IFormFile image)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            if(string.IsNullOrEmpty(userID))
            {
                userID = myID;
                dataBase.DoPost(myID, userID, post, image);
                return RedirectToAction("Index");
            }
            if(!string.IsNullOrEmpty(post) || image != null)
                dataBase.DoPost(myID, userID, post, image);
                
            return RedirectToAction("Profile", new RouteValueDictionary(new {Controller = "Account", Action ="Profile", id = userID}));
        }

        [HttpPost]
        public IActionResult DoComment(string texto, string publicacaoID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            if(!string.IsNullOrEmpty(texto) && !string.IsNullOrEmpty(publicacaoID))
            {
                dataBase.DoComment(myID, publicacaoID, texto);
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
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            if(!string.IsNullOrEmpty(texto) && !string.IsNullOrEmpty(commentID))
                dataBase.DoAnswer(myID, commentID, texto);


            return RedirectToAction("ViewAnswers", new RouteValueDictionary( new {Controller = "Account", Action="ViewAnswers", commentID = commentID}));
        }

        [HttpGet]
        public IActionResult ViewAnswers(string commentID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            RespostasView respostas = new RespostasView();
            respostas = dataBase.GetAnswer(myID, commentID);
            
            return View("answers", respostas);
        }
    
        [HttpGet]
        public IActionResult SendFriend(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.SendFriend(myID, userID);
            return RedirectToAction("Profile", new RouteValueDictionary(new {Controller = "Account", Action ="Profile", id = userID}));
        }

        [HttpGet]
        public IActionResult CancelFriendRequest(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.CancelFriendRequest(myID, userID);
            return RedirectToAction("Profile", new RouteValueDictionary(new {Controller = "Account", Action ="Profile", id = userID}));
        }
    
        [HttpGet]
        public IActionResult AcceptFriendRequest(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.AcceptFriendRequest(myID, userID);
            return RedirectToAction("Profile", new RouteValueDictionary(new {Controller = "Account", Action ="Profile", id = userID}));
        }

        [HttpGet]
        public IActionResult UndoFriend(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.UndoFriend(myID, userID);
            return RedirectToAction("Profile", new RouteValueDictionary(new {Controller = "Account", Action ="Profile", id = userID}));
        }
    
        public IActionResult GetFriends(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            if(string.IsNullOrEmpty(userID))
                userID = myID;

            List<Friends> friends = new List<Friends>();

            friends = dataBase.GetFriends(userID);
            
            return View("Friends", friends);
        }
    
        [HttpGet]
        public IActionResult ChangePerfil()
        {
            return View("config");
        }

        [HttpPost]
        public IActionResult ChangePerfil(IFormFile image, string visibility, string cidade, string pass)
        {   
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();     
            if(image != null || !string.IsNullOrEmpty(visibility) || !string.IsNullOrEmpty(cidade))
                dataBase.ChangePerfil(myID, image, visibility, cidade, pass);
            
            return RedirectToAction("Logout");
        }
    }
}