using Microsoft.AspNetCore.Mvc;
using Emporium.Filters;
using Emporium.Models;

namespace Emporium.Controllers
{
    [PaginaUserLogado]

    public class CarrinhoController : Controller
    {
        public IActionResult Entrar(int quantidade, int idProd, int idUser)
        {
            CarrinhoModel c = new CarrinhoModel();
            c.getProdutos(idUser);
            Console.WriteLine("id do entrar:"+idUser);
            c.addProd(quantidade, idProd,idUser);
            c.IdUser= idUser;
            return View(c);
        }


        public IActionResult FinalizarCompra(int idUser)
        {
            CarrinhoModel c =new CarrinhoModel();
            Console.WriteLine("Fin compra " + idUser);
            c.IdUser = idUser;
            return View(c);
        }
        
        
        public IActionResult MetodoPagar(int idUser)
        {
            Console.WriteLine("id antes remove:" + idUser);
            CarrinhoModel c = new CarrinhoModel();
            c.IdUser = idUser;
            c.removeStock(idUser);
            c.atualizaHist(idUser);
            c.removeCarrinho(idUser);
            return View(c);
        }
    }
}