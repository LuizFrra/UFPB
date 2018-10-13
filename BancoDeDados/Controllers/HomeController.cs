using Microsoft.AspNetCore.Mvc;
using BancoDeDados.Models;

namespace BancoDeDados.Controllers
{
    public class HomeController : Controller
    {

        [HttpGet]
        public IActionResult Index()
        {
            return View("Index");
        }

        [HttpPost]
        public IActionResult Register(Users User)
        {
            return View("Index");
        }
        
        //[HttpPost]

    }
}