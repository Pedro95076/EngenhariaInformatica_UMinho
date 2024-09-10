using Emporium.Models;
using System.Collections.Generic;

namespace Emporium.Repository{

    public interface ILeilaoRepository{
        LeiloesModel BuscaLeilao(string leilao);
        LeiloesModel Adicionar(LeiloesModel leilao);

        List<LeiloesModel> BuscaTodos();
        
        /*UsersModel BuscaID(int id);
        UsersModel Atualizar(UsersModel user);
        bool Apagar(int id);*/
    }

}