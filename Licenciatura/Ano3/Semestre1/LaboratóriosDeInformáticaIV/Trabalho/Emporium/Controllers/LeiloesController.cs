using Microsoft.AspNetCore.Mvc;
using Emporium.Repository;
using Emporium.Models;
using Emporium.Filters;
using System.Data.SqlClient;

namespace Emporium.Controllers
{
    [PaginaUserLogado]

    public class LeiloesController : Controller
    {
        
        public IActionResult Entrar()
        {
            LeiloesModel leiloes = new LeiloesModel();
            leiloes.listaLeilao();
            return View(leiloes);
        }

        public IActionResult FazerProposta(int leilao){
            Leilao l = new Leilao();
            l.getLeilao(leilao);
            return View(l);
        }

        public IActionResult atualizarValor(float Valor, int idLeilao)

        {
            Console.WriteLine("Prop:" + Valor + "id = "+idLeilao);
            SqlConnection cnn = new SqlConnection("Server=./;DataBase=Emporium;User Id=LI4;Password=123456");
            cnn.Open();
            SqlCommand cmd = new SqlCommand("UPDATE Leilao SET valor = " + Valor + " WHERE ID =" + idLeilao, cnn);
            SqlDataReader reader = cmd.ExecuteReader();
            reader.Close();
            cnn.Close();
            LeiloesModel leiloes = new LeiloesModel();
            leiloes.listaLeilao();
            return View(leiloes);
        }

    }
}
