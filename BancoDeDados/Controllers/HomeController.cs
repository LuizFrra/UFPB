using Microsoft.AspNetCore.Mvc;
using BancoDeDados.Models;
using BancoDeDados.Services.LoginRegister;

namespace BancoDeDados.Controllers
{
    public class HomeController : Controller
    {

        private readonly IDataBase _dataBase;

        public HomeController(IDataBase dataBase) => _dataBase = dataBase;

        [HttpGet]
        public IActionResult Index()
        {
            if(HttpContext.User.Identity.IsAuthenticated)
                return RedirectToAction("Index", "Account");

            return View("Index");
        }

        [HttpPost]
        public IActionResult Register(Users user)
        {
            if(ModelState.IsValid)
            {
                if(_dataBase.Register(user))
                {
                    Login data = new Login();
                    data.Email = user.Email;
                    data.Password = user.Password;
                    
                    if(_dataBase.AuthenticationLogin(HttpContext, data))
                        return RedirectToAction("Index", "Account");   
                }
            }

            return View("Index");
        }
        
        [HttpGet]
        public IActionResult Login()
        {
            if(HttpContext.User.Identity.IsAuthenticated)
                return RedirectToAction("Index", "Account");

            return View("login");
        }

        [HttpPost]
        public IActionResult Login(Login data)
        {
            
            if(ModelState.IsValid)
            {
                if(_dataBase.AuthenticationLogin(HttpContext, data)) return RedirectToAction("Index", "Account");
            }

            return View("login");
        }

    }
}