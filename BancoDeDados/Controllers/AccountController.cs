using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using BancoDeDados.Services.DataBase;
using System;
using System.Collections.Generic;

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
            var name = HttpContext.User.FindFirst("Nome").Value.ToString();
            return View("index", name);
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
        public string Profile(string id)
        {
            return "oi " + id;
        }
    }
}