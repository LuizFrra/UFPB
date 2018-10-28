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
                string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
                data = dataBase.SearchForName(myID, name);
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
            relation.myID = myID;
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
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            CommentsView comments =  new CommentsView();
            comments = dataBase.GetComments(myID, postID);
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
    
        [HttpGet]
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
        public IActionResult BlockUser(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.BlockUser(myID, userID);
            return RedirectToAction("Index");
        }

        [HttpGet]
        public IActionResult UsersBlocks()
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            List<Relation> relations = dataBase.GetBlockUsers(myID);
            return View("usersblocks", relations);
        }
        
        [HttpGet]
        public IActionResult UnLockUser(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.UnLockUser(myID, userID);
            return RedirectToAction("UsersBlocks");
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
    
        [HttpGet]
        public IActionResult DeleteAnswer(string commentID, string answersID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.DeleteAnswer(myID, answersID);
            return RedirectToAction("ViewAnswers", new RouteValueDictionary(new {Controller = "Account", Action ="ViewAnswers", commentID = commentID}));
        }
    
        [HttpGet]
        public IActionResult DeleteComment(string postID, string commentID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.DeleteComment(myID, commentID);
            return RedirectToAction("ViewComments", new RouteValueDictionary(new{Controller = "Account", Action="ViewComments", postID = postID}));
        }

        [HttpGet]
        public IActionResult DeletePost(string muralID, string postID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.DeletePost(myID, postID);
            
            if(string.IsNullOrEmpty(muralID))
                return RedirectToAction("Index");

            return RedirectToAction("Profile", new RouteValueDictionary(new{Controller = "Account", Action="Profile", id = muralID}));
        }

        [HttpGet]
        public IActionResult Group()
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            List<Groups> groups = dataBase.GetGroups(myID);
            return View("groups", groups);
        }

        [HttpGet]
        public IActionResult CreateGroup()
        {
            return View("creategroups");
        }

        [HttpGet]
        public IActionResult DeleteGroup(string grupoID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.DeleteGroup(myID, grupoID);
            return RedirectToAction("Group");
        }

        [HttpPost]
        public IActionResult CreateGroup(Groups groups)
        {
            if(ModelState.IsValid)
            {
                string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
                dataBase.CreateGroup(myID, groups);
            }
            return RedirectToAction("Group");
        }

        [HttpGet]
        public IActionResult JoinGroup(string groupID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            
            if(!string.IsNullOrEmpty(groupID))
                dataBase.JoinGroup(myID, groupID);
            
            return RedirectToAction("Group");
        }

        [HttpGet]
        public IActionResult CancelJoinGroup(string groupID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            
            if(!string.IsNullOrEmpty(groupID))
                dataBase.RemoveStatusFromGroup(myID, groupID);
            
            return RedirectToAction("Group");
        }

        [HttpGet]
        public IActionResult OutGroup(string groupID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            
            if(!string.IsNullOrEmpty(groupID))
                dataBase.RemoveStatusFromGroup(myID, groupID);

            return RedirectToAction("Group");
        }

        [HttpGet]
        public IActionResult ManageGroup(string groupID)
        {
            
            if(!string.IsNullOrEmpty(groupID))
            {
                string myID =  HttpContext.User.FindFirst("UserID").Value.ToString();
                ManageGroup users = new ManageGroup();
                users = dataBase.ManageGroup(myID, groupID);
                return View("managegroup", users);
            }

            return RedirectToAction("Group");
        }

        [HttpGet]
        public IActionResult AcceptUserGroup(string userID, string groupID)
        {
            if(!string.IsNullOrEmpty(userID) && !string.IsNullOrEmpty(groupID))
                dataBase.ManageUserGroup(userID, groupID, 2);

            return RedirectToAction("ManageGroup", new RouteValueDictionary(new{Controller = "Account", Action = "ManageGroup",groupID = groupID}));
        }

        [HttpGet]
        public IActionResult BeAdmin(string userID, string groupID)
        {
            if(!string.IsNullOrEmpty(userID) && !string.IsNullOrEmpty(groupID))
                dataBase.ManageUserGroup(userID, groupID, 3);

            return RedirectToAction("ManageGroup", new RouteValueDictionary(new{Controller = "Account", Action = "ManageGroup",groupID = groupID}));   
        }

        [HttpGet]
        public IActionResult KickOut(string userID, string groupID)
        {
            if(!string.IsNullOrEmpty(userID) && !string.IsNullOrEmpty(groupID))
                dataBase.RemoveStatusFromGroup(userID, groupID);

            return RedirectToAction("ManageGroup", new RouteValueDictionary(new{Controller = "Account", Action = "ManageGroup",groupID = groupID}));          
        }

        [HttpGet]
        public IActionResult BlockUserGroup(string userID, string groupID)
        {
            if(!string.IsNullOrEmpty(userID) && !string.IsNullOrEmpty(groupID))
                dataBase.ManageUserGroup(userID, groupID, 4);

            return RedirectToAction("ManageGroup", new RouteValueDictionary(new{Controller = "Account", Action = "ManageGroup",groupID = groupID}));           
        }

        [HttpGet]
        public IActionResult UnblockUserGroup(string userID, string groupID)
        {         
            if(!string.IsNullOrEmpty(groupID) && !string.IsNullOrEmpty(userID))
                dataBase.RemoveStatusFromGroup(userID, groupID);  

            return RedirectToAction("ManageGroup", new RouteValueDictionary(new{Controller = "Account", Action = "ManageGroup",groupID = groupID}));          
        }

        [HttpGet]
        public IActionResult ChangeGroup(string groupID)
        {
            return View("changegroup", groupID);
        }

        [HttpPost]
        public IActionResult ChangeGroup(Groups group)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            dataBase.ChangeGroup(myID, group);
            return RedirectToAction("ChangeGroup", new RouteValueDictionary(new{Controller = "Account", Action = "ChangeGroup", groupID = group.groupID}));
        }

        [HttpGet]
        public IActionResult GetUserGroups(string userID)
        {
            string myID = HttpContext.User.FindFirst("UserID").Value.ToString();
            List<Groups> groups = dataBase.GetUserGroups(myID, userID);
            return View("usergroup", groups);
        }
    }
}