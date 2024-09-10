using Microsoft.AspNetCore.Mvc;
using Emporium.Models;
using Emporium.Repository;

namespace Emporium.Controllers
{
    public class UsersController : Controller
    {
        private readonly IUserRepository _userRepo;
        public UsersController(IUserRepository userRepo){
            _userRepo = userRepo;
        }

        public IActionResult Index (){
            List<UsersModel> users = _userRepo.BuscaTodos();

            return View(users);
        }

        public IActionResult Criar(){
            
            return View();
        }

        /*public IActionResult Editar(int id){
            UsersModel user = _userRepo.BuscaPorId(id);
            return View(user);
        }

        public IActionResult ApagarConfirmacao(int id){
            UsersModel user = _userRepo.BuscaPorId(id);
            return View(id);
        }


        /*[HttpPost]
        public IActionResult Criar(UsersModel user){
            _userRepo.Adicionar(user);
            return RedirectToAction("Index");
        }*/
        
    }
}
