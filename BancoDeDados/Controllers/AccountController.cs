using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Authorization;

namespace BancoDeDados.Controllers
{
    [Authorize(Roles = "User")]
    public class AccountController : Controller
    {
        [HttpGet]
        public IActionResult Index()
        {
            return View("index");
        }
    }
}