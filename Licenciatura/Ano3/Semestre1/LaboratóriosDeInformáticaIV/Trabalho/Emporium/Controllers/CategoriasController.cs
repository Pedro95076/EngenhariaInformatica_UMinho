using Microsoft.AspNetCore.Mvc;
using Emporium.Filters;
namespace Emporium.Controllers
{
    [PaginaUserLogado]

    public class CategoriasController : Controller
    {

        public IActionResult Entrar()
        {
            return View();
        }

        public IActionResult Pesquisar(){
            return View();
        }
    }
}