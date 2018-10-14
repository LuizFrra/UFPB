using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;
using System;

namespace BancoDeDados.Controllers
{
    [Authorize(Roles = "User")]
    public class AccountController : Controller
    {
        [HttpGet]
        public IActionResult Index()
        {
            var name = HttpContext.User.FindFirst("Nome").Value.ToString();
            return View("index", name);
        }
    }
}